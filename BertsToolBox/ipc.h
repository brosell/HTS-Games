#ifndef ipc_h
#define ipc_h

#include "Types.h"

const int HEADER_SIZE = 8;
const int SIZE_OFFSET = 0;
const int TYPE_OFFSET = 2;
const int SEQNUM_OFFSET = 4;
const int DATA_OFFSET = 8;
const int STATUS_SIZE = 2;
const int STATUS_OFFSET = DATA_OFFSET;
const int ACK_DATA_OFFSET = DATA_OFFSET + STATUS_SIZE;

const UDBLBYTE ACK_BIT = 0x8000;


#endif
