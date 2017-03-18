#ifndef Link_h
#define Link_h

#pragma warning (disable:4786)

typedef unsigned char UBYTE;
typedef unsigned short UDBLBYTE;

#include "ipc.h"

#include <string>
#include "ThreadSafeList.h"
#include <list>
#include <set>
#include <map>
#include <time.h>

const int MESSAGE_TIMEOUT = 15;

#include "Message.h"
#include "Timer.h"
#include "Event.h"

#include "ObjectCache.h"

class SentMessage
{
public:
  HTimer timer;
  Message* message;
};

class LinkEvent: public Event
{
public:
  Link* link;
};

class LinkUpEvent: public LinkEvent
{ /* empty */ };

class LinkDownEvent: public LinkEvent
{ /* empty */ };

class LinkMessageEvent: public LinkEvent
{
public:
  Message* message;
};

class LinkAckEvent: public LinkEvent
{
public:
  Message* original;
  Ack* ack;
};

class LinkListener
{
public:
  virtual void linkUp(LinkUpEvent* event) { }
  virtual void linkDown(LinkDownEvent* event) { }
  virtual void linkMessage(LinkMessageEvent* event) { }
  virtual void linkAck(LinkAckEvent* event) { }
};

class Link: public TimerListener
{
public:
  Link(std::string name);
  virtual ~Link();

  static
  void processLinks();
  
  void addListener(LinkListener* listener) { m_linkListeners.insert(listener); }
  void removeListener(LinkListener* listener) { m_linkListeners.erase(listener); }

  void sendMessage(Message* msg);
  void sendMessage(Message& msg) { sendMessage(&msg); }

  Message* receiveMessage(); // reads from the q
  

  virtual bool isReceiveReady() = 0;
  virtual void doSend(Message* msg) = 0;
  virtual Message* doReceive() = 0;

  virtual bool isValid() = 0;

  string getName() {return m_name; }

  /* TimerListener */
  virtual void timeout(TimerEvent* event);

protected:

  void clearTimeout(Message* msg);

  void processLinkDown();
  void processReceivedMessage(Message* msg);

  void process();

  std::list<Message*> m_incomingQueue;
  static UDBLBYTE s_seqNum;



private:
  std::string m_name;
  void checkTimeouts();
  
  ObjectCache<SentMessage> m_smCache;
  map<UQUADBYTE, SentMessage*> m_outstanding; // seqnum

  set<LinkListener*> m_linkListeners;

  static set<Link*> s_links;

  bool m_linkUp;
};

#endif
