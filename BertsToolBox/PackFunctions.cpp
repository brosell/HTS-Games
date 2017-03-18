#include "PackFunctions.h"


UDBLBYTE unpackDblByte(UBYTE* payload)
{
  UDBLBYTE qb = 0;
  qb = (payload[0] << 8) +
       (payload[1]);

  return qb;
}

void packDblByte(UDBLBYTE db, UBYTE* payload)
{
  unsigned int t=db;
  payload[0] = (t & 0xff00) >> 8;
  payload[1] = (t & 0x00ff);
}


UQUADBYTE unpackQuadByte(UBYTE* payload)
{
  UQUADBYTE qb;
  qb = (payload[0] << 24) +
           (payload[1] << 16) +
           (payload[2] << 8) +
           (payload[3]);

  return qb;
}

void packQuadByte(UQUADBYTE qb, UBYTE* payload)
{
  unsigned int t=qb;
  payload[0] = (t & 0xff000000) >> 24;
  payload[1] = (t & 0x00ff0000) >> 16;
  payload[2] = (t & 0x0000ff00) >> 8;
  payload[3] = (t & 0x000000ff);
}
