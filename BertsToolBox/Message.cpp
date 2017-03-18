#pragma warning (disable: 4786)
#include "Message.h"
#include "Link.h"


//void* Message::s_unpackArray[MAX_MSG_TAG];
map<int, void*> Message::s_unpackArray;

#include <sstream>
using std::stringstream;

int Message::s_numMessagesCreated = 0;
int Message::s_numMessagesCreatedFromCopy = 0;
int Message::s_numMessagesDeleted = 0;

// static
Message* Message::unpack(const UBYTE* package)
{
  UBYTE type = ::getType((UBYTE*)package);
  UnpackFuncType* pfn = (UnpackFuncType*)s_unpackArray[type];
  if (pfn)
  {
    return pfn(package);
  }
  return 0; //new Message(package);
}

Message::Message(UDBLBYTE type, UDBLBYTE dataSize):
m_data(0), original(0)
{
  m_data = new UBYTE[dataSize + HEADER_SIZE];
  ::setType(m_data, type);
  ::setSize(m_data, dataSize + HEADER_SIZE);
  s_numMessagesCreated++;
}

Message::Message(const Message& other)
{
  original = other.original;
  link = other.link;
  m_data = copyMsg(other.m_data);
  s_numMessagesCreatedFromCopy++;
}


Message::~Message()
{
  if (m_data)
  {
    delete [] m_data;
  }

  if (original != 0)
  {
    delete original;
  }
  s_numMessagesDeleted++;
}

string Message::getHexString() const
{
  stringstream strs;
  strs << getName() << ": ";
  int s=getSize(m_data);
  char buf[10];
  for (int c=0; c<s; c++)
  {
    sprintf(buf, "%02x", m_data[c]);
    strs << buf << " ";
  }
  return strs.str();
}

void Message::send(Link* link)
{
  link->sendMessage(this);
}


Ack::Ack(UDBLBYTE type, UDBLBYTE dataSize):
Message(type, dataSize + STATUS_SIZE)
{
}

Ack::~Ack()
{
}

