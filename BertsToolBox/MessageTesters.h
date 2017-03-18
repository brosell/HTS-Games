#ifndef MessageTesters_h
#define MessageTesters_h

#include "Message.h"
#include "ObjectCache.h"

class MessageTester
{
public:
  virtual bool test(Message*) = 0;
};

class IsMessageType: public MessageTester
{
public:
  IsMessageType(UDBLBYTE type = -1): m_type(type) { }
  void setType(UDBLBYTE type) { m_type = type; }

  virtual bool test(Message* msg)
  {
    return (msg->getType() == m_type);
  }

  void reclaim() { m_type = -1; }

  static
  IsMessageType* acquire() { return s_cache.acquire(); }
  static void release(IsMessageType* imt) { s_cache.release(imt); }

private:
  UDBLBYTE m_type;

  static ObjectCache<IsMessageType> s_cache;
};

#endif