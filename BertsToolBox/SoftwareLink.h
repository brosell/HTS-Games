#ifndef SoftwareLink_h
#define SoftwareLink_h

#include "Link.h"

class SoftwareLink: public Link
{
public:
  SoftwareLink();

  bool connect(SoftwareLink* other);
  
  virtual bool isReceiveReady() { return isValid() && (m_incomingQueue.size() > 0); }

  virtual void doSend(Message* msg);
  virtual Message* doReceive();

  virtual bool isValid() { return m_other != 0; }

private:
  SoftwareLink* m_other;
};

#endif