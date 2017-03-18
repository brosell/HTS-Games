#ifndef PackFunctions_h
#define PackFunctions_h

#include "ipc.h"
#include <memory.h>

UQUADBYTE unpackQuadByte(UBYTE* payload);
void packQuadByte(UQUADBYTE qb, UBYTE* payload);

UDBLBYTE unpackDblByte(UBYTE* payload);
void packDblByte(UDBLBYTE seqNum, UBYTE* payload);


inline void setSeqNum(UBYTE* msg, UQUADBYTE seqNum)
{
  packQuadByte(seqNum, &(msg[SEQNUM_OFFSET]));
}

inline UQUADBYTE getSeqNum(UBYTE* msg)
{
  return unpackQuadByte(&(msg[SEQNUM_OFFSET]));
}

inline void setType(UBYTE* msg, UDBLBYTE type)
{
  packDblByte(type, &(msg[TYPE_OFFSET]));
}

inline UDBLBYTE getType(UBYTE* msg)
{
  return unpackDblByte(&(msg[TYPE_OFFSET]));
}

inline void setSize(UBYTE* msg, UDBLBYTE size)
{
  packDblByte(size, &(msg[SIZE_OFFSET]));
}

inline UDBLBYTE getSize(UBYTE* msg)
{
  return unpackDblByte(&(msg[SIZE_OFFSET]));
}

inline UDBLBYTE getDataSize(UBYTE* msg)
{
  return getSize(msg) - HEADER_SIZE;
}

inline void setData(UBYTE* msg, UBYTE* data)
{
  memcpy(&(msg[DATA_OFFSET]), data, getDataSize(msg));
}

inline void getData(UBYTE* msg, UBYTE* data)
{
  memcpy(data, &(msg[DATA_OFFSET]), getDataSize(msg));
}

inline UBYTE* getDataPtr(UBYTE* msg)
{
  return &(msg[DATA_OFFSET]);
}


inline UBYTE getAckDataSize(UBYTE* msg)
{
  return getSize(msg) - (HEADER_SIZE + STATUS_SIZE);
}

inline void setAckData(UBYTE* msg, UBYTE* data)
{
  memcpy(&(msg[ACK_DATA_OFFSET]), data, getAckDataSize(msg));
}

inline void getAckData(UBYTE* msg, UBYTE* data)
{
  memcpy(data, &(msg[ACK_DATA_OFFSET]), getAckDataSize(msg));
}

inline UBYTE* getAckDataPtr(UBYTE* msg)
{
  return &(msg[ACK_DATA_OFFSET]);
}

inline void setStatus(UBYTE* msg, UDBLBYTE status)
{
  packDblByte(status, &(msg[STATUS_OFFSET]));
}

inline UDBLBYTE getStatus(UBYTE* msg)
{
  return unpackDblByte(&(msg[STATUS_OFFSET]));
}

inline UBYTE* newMsg(UDBLBYTE type, UDBLBYTE dataSize)
{
  UBYTE* msg = new UBYTE[dataSize + HEADER_SIZE];
  setType(msg, type);
  setSize(msg, dataSize + HEADER_SIZE);
  return msg;
}

inline UBYTE* makeAck(UBYTE* msg, UDBLBYTE status, UBYTE extraData = 0)
{
  int ackSize = HEADER_SIZE + STATUS_SIZE + extraData;
  UBYTE* ack = new UBYTE[ackSize];
  setSize(ack, ackSize);
  setType(ack, getType(msg) | ACK_BIT); // set MSB
  setSeqNum(ack, getSeqNum(msg));
  setStatus(ack, status);
  return ack; 
}

inline UBYTE* copyMsg(UBYTE* msg)
{
  int size = getSize(msg);
  UBYTE* ret = new UBYTE[size];
  memcpy(ret, msg, size);
  return ret;
}

inline 
bool isAck(UBYTE* msg)
{
  return ((getType(msg) & ACK_BIT) == ACK_BIT);
}

#endif
