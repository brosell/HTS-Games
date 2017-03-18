#include "TCPLink.h"

#include "Log.h"

TCPLink::TCPLink(BSocket* socket): Link("TCPLink (Server)"), m_socket(socket), m_address(""), m_port(-1)
{

}

TCPLink::TCPLink(string address, int port): Link("TCPLink (Client)"), m_socket(0), m_address(address), m_port(port)
{
  m_socket=new BSocket(address, port);
}

void TCPLink::doSend(Message* msg)
{
  // relies on Message::operator UBYTE*...
  lassert(msg != 0);
  lassert(m_socket->isWriteReady());
  UBYTE* bytes = *msg;
  m_socket->write((char*)bytes, getSize(bytes));
}

Message* TCPLink::doReceive()
{
  lassert(m_socket->isReadReady());
  
  UBYTE buffer[2]; // only want the size for now;
  
  int got = m_socket->read((char*)buffer, 2);
  
  if (got == 0)
  {
    return 0;
  }
  if (got == 1)
  {
    m_socket->unread((char*)buffer, 1);
    return 0;
  }
  if (got < 0)
  {
    logError("unexpected socket error", Error);
    return 0;
  }

  int msgSize = unpackDblByte(&(buffer[0]));
  UBYTE* bytes = new UBYTE[msgSize];
  bytes[0] = buffer[0];
  bytes[1] = buffer[1];

  got = m_socket->read((char*)&(bytes[2]), msgSize-2);
  if (got < msgSize-2)
  {
    // put it back and try later
    m_socket->unread((char*)bytes, got);
    return 0;
  }

  lassert(got == msgSize-2);

  Message* msg = Message::unpack(bytes);

  return msg;
}
  

//void TCPLink::receiveMessages()
//{
//  UBYTE buffer[256];
//  while (m_socket->isReadReady())
//  {
//    int got = m_socket->read(buffer, 256);
//    //assert(got > 0);
//    if (got == 0)
//    {
//      //m_socket->isReadReady();
//      return;
//    }
//    int msgSize = unpackDblByte(&(buffer[0]));
//    if (got < msgSize)
//    {
//      // put it back, we'll try again later
//      m_socket->unread(buffer, got);
//      return;
//    }
//
//    // put back the "overrun"
//    if (got > msgSize)
//    {
//      m_socket->unread(&(buffer[msgSize]), got - msgSize);
//    }
//    
//    Message* msg = Message::unpack(buffer);
//    newIncoming(msg);
//  }
//  return;
//}

//void TCPLink::deliverMessages()
//{
//  // relies on operator UBYTE*...
//  while (m_outgoingQueue.size() > 0 && m_socket->isWriteReady())
//  {
//    UBYTE* msg = *(m_outgoingQueue.front());
//    m_outgoingQueue.pop_front();
//
//    int size = getSize(msg);
//    assert(size > 0);
//
//    m_socket->write(msg, size);
////    delete [] msg;
//  }
//
//  return;
//}
