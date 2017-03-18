#include "MessageCenter.h"

set<MessageFilter*> MessageCenter::s_filters;
ObjectCache<MessageFilter> MessageCenter::s_filterCache;
set<Link*> MessageCenter::s_links;

set<MessageObserver*> MessageCenter::s_observers;


bool MessageCenter::deliverMessage(Message* msg)
{
  bool wasSent = false;
  set<MessageFilter*>::iterator i;
  for (i = s_filters.begin(); i!=s_filters.end(); i++)
  {
    MessageFilter* mf=*i;
    if ( mf->tester->test(msg) )
    {
      wasSent = true;
      mf->delegate->invoke(msg);
    }
  }

  set<MessageObserver*>::iterator ob;
  for (ob=s_observers.begin(); ob!=s_observers.end(); ob++)
  {
    (*ob)->observeMessage(msg);
    wasSent = true;
  }

  return wasSent;
}

HMessageFilter MessageCenter::registerFilter(MessageTester* mt, Delegate* d)
{
  MessageFilter* mf = s_filterCache.acquire();
  mf->tester = mt;
  mf->delegate = d;
  s_filters.insert(mf);
  return (HMessageFilter)mf;
}

void MessageCenter::registerObserver(MessageObserver* observer)
{
  s_observers.insert(observer);
}

void MessageCenter::unregisterObserver(MessageObserver* observer)
{
  s_observers.erase(observer);
}

void MessageCenter::unregisterFilter(HMessageFilter handle)
{
  MessageFilter* mf = (MessageFilter*)handle;
  s_filters.erase(mf);
  s_filterCache.release(mf);
}

void MessageCenter::registerLink(Link* link)
{
  s_links.insert(link);
}

void MessageCenter::unregisterLink(Link* link)
{
  s_links.erase(link);
}

void MessageCenter::tick()
{
  set<Link*>::iterator i;
  for (i=s_links.begin(); i!=s_links.end(); i++)
  {
    drainLink(*i);
  }
}

void MessageCenter::drainLink(Link* link)
{
  Message* msg = 0;
  while (link->isReceiveReady())
  {
    msg = link->receiveMessage();
    if (msg)
    {
      deliverMessage(msg);
      delete msg;
    }
    else
    {
      break;
    }
  }
}