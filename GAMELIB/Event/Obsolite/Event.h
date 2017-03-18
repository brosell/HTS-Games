#ifndef _Event_h
#define _Event_h

//#include <list>
//#include <string>
//using namespace std;
//
//#include "Message.h"
//
//
//enum
//{
//  UNDEF_EVENT = FIRST_FREE_MESSAGE_ID,
//  MouseClick,
//  MouseDblClick,
//  MouseUp,
//  MouseDown,
//  MouseMove,
//  MouseDrag,
//  MouseEnter,
//  MouseExit,
//  KeyDown,
//  KeyUp,
//  KeyRepeat,
//  ConsoleCommand,
//  USER_MESSAGE
//};
//
//////////////
//// MOUSE
//////////////
//
//DEF_MSG(MouseDown, 5)
//NAMED_DBLBYTE(X, 0)
//NAMED_DBLBYTE(Y, 2)
//NAMED_BYTE(Button, 4)
//END_MSG
//
//DEF_MSG(MouseUp, 5)
//NAMED_DBLBYTE(X, 0)
//NAMED_DBLBYTE(Y, 2)
//NAMED_BYTE(Button, 4)
//END_MSG
//
//DEF_MSG(MouseClick, 5)
//NAMED_DBLBYTE(X, 0)
//NAMED_DBLBYTE(Y, 2)
//NAMED_BYTE(Button, 4)
//END_MSG
//
//DEF_MSG(MouseDblClick, 5)
//NAMED_DBLBYTE(X, 0)
//NAMED_DBLBYTE(Y, 2)
//NAMED_BYTE(Button, 4)
//END_MSG
//
//DEF_MSG(MouseMove, 8)
//NAMED_DBLBYTE(X, 0)
//NAMED_DBLBYTE(Y, 2)
//NAMED_DBLBYTE(RelX, 4)
//NAMED_DBLBYTE(RelY, 6)
//END_MSG
//
//DEF_MSG(MouseDrag, 8)
//NAMED_DBLBYTE(X, 0)
//NAMED_DBLBYTE(Y, 2)
//NAMED_DBLBYTE(RelX, 4)
//NAMED_DBLBYTE(RelY, 6)
//END_MSG
//
//DEF_MSG(MouseEnter, 8)
//NAMED_DBLBYTE(X, 0)
//NAMED_DBLBYTE(Y, 2)
//NAMED_DBLBYTE(RelX, 4)
//NAMED_DBLBYTE(RelY, 6)
//END_MSG
//
//DEF_MSG(MouseExit, 8)
//NAMED_DBLBYTE(X, 0)
//NAMED_DBLBYTE(Y, 2)
//NAMED_DBLBYTE(RelX, 4)
//NAMED_DBLBYTE(RelY, 6)
//END_MSG
//
//
////////////////
//// KEY
////////////////
//DEF_MSG(KeyUp, 2)
//NAMED_DBLBYTE(KeySym, 0)
//END_MSG
//
//DEF_MSG(KeyDown, 2)
//NAMED_DBLBYTE(KeySym, 0)
//END_MSG
//
//DEF_MSG(KeyRepeat, 2)
//NAMED_DBLBYTE(KeySym, 0)
//END_MSG
//
////////////////
//// CONSOLE COMMAND
////////////////
///* FIXME: messages that don't have to go on network? */
//DEF_MSG(ConsoleCommand, 64)
//NAMED_STRING(Command, 64, 0)
//END_MSG

#endif