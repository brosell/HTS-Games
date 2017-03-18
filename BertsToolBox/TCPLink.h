#ifndef TCPLink_h
#define TCPLink_h

#include "Link.h"
#include "BSocket.h"

class TCPLink: public Link
{
public:
  TCPLink(string address, int port);
  TCPLink(BSocket*);
  ~TCPLink() 
  {
    if (m_socket)
    {
      m_socket->close();
      delete m_socket;
    }
  }

  virtual bool isReceiveReady() { return (isValid() && m_socket->isReadReady()); }

  virtual void doSend(Message* msg);
  virtual Message* doReceive();

  virtual bool isValid() { return (m_socket != 0) && (m_socket->isValid()); }

private:
  BSocket* m_socket;

  string m_address;
  int m_port;

};

#endif