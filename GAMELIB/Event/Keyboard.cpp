#include "Keyboard.h"

KeyMapEntry keyboard[500];

inline void defKeyMapEntry(int c, int sc, int ascii, int sAscii, int cAscii)
{
  keyboard[c].makeScancode = c;
  keyboard[c].breakScancode = c+0x80;
  keyboard[c].defaultAscii = ascii;
  keyboard[c].shiftedAscii = sAscii;
  keyboard[c].ctrlAscii = cAscii;
}

void initKeyboard()
{
  defKeyMapEntry(1, 0, 0, 0, 0);
}
