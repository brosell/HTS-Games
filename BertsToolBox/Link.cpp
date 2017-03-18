#include "Link.h"
#include "Message.h"
#include "Log.h"
 
UDBLBYTE Link::s_seqNum = 0;
set<Link*> Link::s_links;


Link::Link(std::string name): 
m_name(name),
//d_onTimeout(*this, Link::onTimeout),
m_linkUp(false)
{
  s_links.insert(this);
}

Link::~Link()
{
  s_links.erase(this);
}

void Link::processLinks()
{
  set<Link*>::iterator i;
  for (i=s_links.begin(); i!=s_links.end(); i++)
  {
    (*i)->process();
  }
}

void Link::process()
{
  if (m_linkUp)
  {
    if (!isValid())
    {
      m_linkUp = false;
      processLinkDown();
    }
    else
    { // isValid() == true;
      Message* msg = 0;
      while ( isReceiveReady() && (msg=receiveMessage()) != 0)
      {
        processReceivedMessage(msg);
        delete msg;
      }
    }
  }
  else
  { // m_linkUp = false
    // FIXME: reestablish is necessary
    if (isValid())
    {
      LinkUpEvent linkUp;
      linkUp.link = this;
      set<LinkListener*> setCopy(m_linkListeners);
      set<LinkListener*>::iterator i;
      for (i=setCopy.begin(); i!=setCopy.end(); i++)
      {
        m_linkUp = true;
        (*i)->linkUp(&linkUp);
      }
    }   
  }
}

void Link::processLinkDown()
{
  LinkDownEvent linkDown;
  linkDown.link = this;
  set<LinkListener*> setCopy(m_linkListeners);
  set<LinkListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->linkDown(&linkDown);
  }
}

void Link::processReceivedMessage(Message* msg)
{
  set<LinkListener*> setCopy(m_linkListeners);
  set<LinkListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    if (msg->isAck())
    {
      LinkAckEvent ackEvent;
      ackEvent.link = this;
      ackEvent.original = msg->original;
      ackEvent.ack = (Ack*)msg;
      (*i)->linkAck(&ackEvent);
    }
    else
    {
      LinkMessageEvent messageEvent;
      messageEvent.link = this;
      messageEvent.message = msg;
      (*i)->linkMessage(&messageEvent);
    }
  }
}



void Link::sendMessage(Message* msg)
{
  // an ack will allready have a seqnum set.
  if (!msg->isAck())
  {
    msg->setSeqNum(s_seqNum++);
  }

  //Message* copy = new Message(*msg);
  Message* copy = Message::unpack(*msg);

  if (!copy->isAck() && copy->hasAck())
  {
    SentMessage* sm = m_smCache.acquire();
    sm->timer = Timer::create("Link:SendMessage", 0, MESSAGE_TIMEOUT*1000, this, sm, false);
    sm->message = copy;
    m_outstanding[msg->getSeqNum()] = sm;
  }
  doSend(msg);
}


Message* Link::receiveMessage() // reads from the q
{
  Message* msg = 0;
  if (m_incomingQueue.size() > 0)
  {
    msg = m_incomingQueue.front();
    m_incomingQueue.pop_front();
  }
  else
  {
    msg = doReceive();
  }

  if (msg)
  {
    clearTimeout(msg);
    msg->link = this;
  }
  return msg;
}

void Link::clearTimeout(Message* msg)
{
  if ( !msg->isAck() )
  {
    // only waiting for acks
    return;
  }

  map<UQUADBYTE, SentMessage*>::iterator pair;
  pair = m_outstanding.find(msg->getSeqNum());

  if (pair != m_outstanding.end())
  {
    // found it
    HTimer timer = pair->second->timer;
    Message* orig = pair->second->message;
    m_outstanding.erase(msg->getSeqNum());
    Timer::destroy(timer);
    msg->original = orig;
  }
  else
  {
    char buf[1024];
    sprintf(buf, "timeout wasn't cleared for ACK: %s - %s", msg->getName().c_str(), msg->getHexString().c_str());
    logError(buf, Inform);
  }

}

void Link::timeout(TimerEvent* event)
{
  SentMessage* sm = (SentMessage*)event->param;

  map<UQUADBYTE, SentMessage*>::iterator pair;

  UQUADBYTE seqNum = sm->message->getSeqNum();
  
#ifdef _DEBUG
  pair = m_outstanding.find(seqNum);
  lassert(pair != m_outstanding.end());
#endif

  m_outstanding.erase(seqNum);

  Ack* nack = new Ack(sm->message->getType() | ACK_BIT, 0);
  nack->setSeqNum(sm->message->getSeqNum());
  nack->setStatus(ACK_TIMEOUT);
  nack->original = sm->message;
  m_incomingQueue.push_back(nack);
  m_smCache.release(sm);

  char buf[255];
  sprintf(buf, "No Ack for: %s", sm->message->getName().c_str());
  logError(buf, Error);

}