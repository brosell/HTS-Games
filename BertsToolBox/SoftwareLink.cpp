#include "SoftwareLink.h"
#include "Log.h"

SoftwareLink::SoftwareLink(): Link("SoftwareLink"), m_other(0)
{ 

}

bool SoftwareLink::connect(SoftwareLink* other)
{
  other->m_other = this;
  this->m_other = other;
  return (m_other != 0);
}


void SoftwareLink::doSend(Message* msg)
{
  lassert(isValid());
  m_other->m_incomingQueue.push_back(msg);
}

Message* SoftwareLink::doReceive()
{
  // this is all handled in the Link by Link
  return 0;
}

//void SoftwareLink::deliverMessages()
//{
//  if (m_other == 0)
//  {
//    return;
//  }
//  std::list<Message*>::iterator i;
//  //copy(m_outgoingQueue.begin(), m_outgoingQueue.end(), back_inserter(m_other->m_incomingQueue));
//  for (i = m_outgoingQueue.begin(); i!=m_outgoingQueue.end(); i++)
//  {
//    Message* msg = new Message(*(*i));
//    m_other->newIncoming(msg);
//    delete [] msg;
//  }
//  m_outgoingQueue.clear();
//  return;
//}
//void SoftwareLink::receiveMessages()
//{
//  return;
//  // when m_other delivers, we get them, so there is no need
//  // to do it here
//}
