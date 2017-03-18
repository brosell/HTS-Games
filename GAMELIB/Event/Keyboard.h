#ifndef _Keyboard_h
#define _Keyboard_h

struct KeyMapEntry
{
  int makeScancode;
  int breakScancode; // makeScancode + 0x80
  int defaultAscii;
  int shiftedAscii;
  int ctrlAscii; // ?
  int altAscii; // ?
  bool isDown;
};

/* index's:
      is not escaped add nothing (tab 0x0f)
      if escaped with 0xe0 (ie RCTRL = 0xe0 0x1d) add 0x100 to LSB (ie 0x11d)
      if escaped with 0xe1 add 0x200 to LSB
  */

inline int convertScancode(int scancode)
{
  if ( (scancode & 0xe000) == 0xe000)
  {
    return (scancode & 0xff) + 0x100;
  }
  if ( (scancode & 0xe100) == 0xe100)
  {
    return (scancode & 0xff) + 0x200;
  }
  return (scancode & 0xff);
}

int getAsciiFromKey(int scancode, bool isShifted);
int isKeyDown(int scancode);

#endif