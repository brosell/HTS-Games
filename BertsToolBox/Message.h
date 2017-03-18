#ifndef Message_h
#define Message_h

#include "ipc.h"
#include "packFunctions.h"

#include <string>
#include <map>
using std::string;
using std::map;

class Link;
class Message;

typedef Message* UnpackFuncType(const UBYTE*);

const UDBLBYTE MAX_MSG_TAG = 0xffff;

enum
{
  ACK_ACK,
  ACK_NACK,
  ACK_TIMEOUT,
  ACK_INTERNAL_ERROR,
  ACK_UNEXPECTED,
  ACK_USER
};

class Message
{
public:
  Message(UDBLBYTE type, UDBLBYTE dataSize);
  Message(const Message& other);


  virtual ~Message();

  void send(Link* link);

  virtual UDBLBYTE getType() { return ::getType(m_data); }
  virtual UDBLBYTE getDataSize() { return ::getDataSize(m_data); }

  unsigned int getSeqNum() { return ::getSeqNum(m_data); }
  void setSeqNum(unsigned int s) { ::setSeqNum(m_data, s); }
  
  bool is(int type) { return (type == ::getType(m_data)); }

  bool isAck() { return ::isAck(m_data); }

  virtual bool hasAck() { return true; }

  UBYTE* getPackage() const { return m_data;}
  operator UBYTE* () const { return getPackage(); }

  string getHexString() const;

  virtual string getName() const { return "Message"; }


  static map<int, void*> s_unpackArray;
  static Message* unpack(const UBYTE* package);

  Link* link;
  Message* original;
  
protected:
  UBYTE* m_data;

  Message(const UBYTE* package):original(0), link(0) { m_data = ::copyMsg((UBYTE*)package); }
private:
  //string m_name;

public:
  static int s_numMessagesCreated;
  static int s_numMessagesCreatedFromCopy;
  static int s_numMessagesDeleted;
};

class Ack: public Message
{
public:
  Ack(UDBLBYTE type, UDBLBYTE dataSize);
  Ack(const UBYTE* package): Message(package) { }
  
  virtual ~Ack();

  void from(Message* msg) { setSeqNum(msg->getSeqNum()); }

  virtual bool hasAck() { return false; }

  virtual string getName() const { return "Ack"; }

  UDBLBYTE getStatus() { return ::getStatus(m_data); }
  void setStatus(UDBLBYTE status) { ::setStatus(m_data, status); }

  virtual UDBLBYTE getDataSize() { return ::getAckDataSize(m_data); }

protected:
private:
};


inline bool operator == (const Message& m1, const Message& m2)
{
  return (memcmp(m1.getPackage(), m2.getPackage(), ::getSize(m1.getPackage())) == 0);
}



#define DEF_MSG(name, size)  \
class MSG_##name : public Message \
{\
public:\
  MSG_##name(): Message(name, size) { }\
  MSG_##name(const UBYTE* package): Message(package) { }\
  virtual string getName() const { return #name; }\
  static Message* unpackFn(const UBYTE* package) { return new MSG_##name(package); }

#define DEF_MSG_NO_ACK(name, size) \
DEF_MSG(name, size)\
virtual bool hasAck() { return false; }


#define DEF_ACK(name, size)\
  const UDBLBYTE AckOf##name = name | ACK_BIT; \
class ACK_##name : public Ack \
{\
public:\
  ACK_##name(): Ack(AckOf##name, size) { } \
  ACK_##name(const UBYTE* package): Ack(package) { }\
  virtual string getName() const { return #name; }\
  static Message* unpackFn(const UBYTE* package) { return new MSG_##name(package); }


#define NAMED_BYTE(name, offset)\
public:\
UBYTE get##name() { return m_data[DATA_OFFSET+offset]; } \
void set##name(UBYTE x) { m_data[DATA_OFFSET+offset] = x; }


#define NAMED_DBLBYTE(name, offset)\
public:\
UDBLBYTE get##name() { return unpackDblByte(&(m_data[DATA_OFFSET+offset])); } \
void set##name(UDBLBYTE x) { packDblByte(x, &(m_data[DATA_OFFSET+offset])); }


#define NAMED_QUADBYTE(name, offset)\
public:\
UQUADBYTE get##name() { return unpackQuadByte(&(m_data[DATA_OFFSET+offset])); } \
void set##name(UQUADBYTE x) { packQuadByte(x, &(m_data[DATA_OFFSET+offset])); }


#define NAMED_BYTEARRAY(name, size, offset)\
public:\
void get##name(UBYTE* ret) { memcpy(ret, &(m_data[DATA_OFFSET+offset]), size); }\
void set##name(const UBYTE* data) { memcpy(&(m_data[DATA_OFFSET+offset]), data, size); }\
const UBYTE* getPtrTo##name() { return &(m_data[DATA_OFFSET+offset]); }

#define NAMED_STRING(name, size, offset)\
public:\
void get##name(char* ret) { strncpy((char*)ret, (const char*)&(m_data[DATA_OFFSET+offset]), size);  }\
void set##name(const char* data) { strncpy((char*)&(m_data[DATA_OFFSET+offset]), (const char*)data, size); m_data[DATA_OFFSET+offset+(size-1)] = '\0'; }\
const char* getPtrTo##name() { return (char*)&(m_data[DATA_OFFSET+offset]); }


#define END_MSG };

#define END_ACK };

#define SET_UNPACK(name) \
Message::s_unpackArray[name] = MSG_##name::unpackFn; \
Message::s_unpackArray[name | ACK_BIT] = ACK_##name::unpackFn;

#define SET_UNPACK_NO_ACK(name) \
Message::s_unpackArray[name] = MSG_##name::unpackFn;

//////////////////////////////
// Lib Messages
//////////////////////////////
enum
{
  Timeout = 1,
  FIRST_FREE_MESSAGE_ID
};

DEF_MSG_NO_ACK(Timeout, 6)
NAMED_DBLBYTE(Id, 0)
NAMED_QUADBYTE(Param, 2)
END_MSG

DEF_ACK(Timeout, 0)
END_ACK;

#endif
