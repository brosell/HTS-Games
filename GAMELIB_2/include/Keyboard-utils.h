#ifndef _Keyboard_Utils_h
#define _Keyboard_Utils_h

const char keymap[]  = "`1234567890-=qwertyuiop[]\\asdfghjkl;’zxcvbnm,./";
const char ukeymap[] = "~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?";

const char allKeys[] = "`1234567890-=qwertyuiop[]\\asdfghjkl;\'zxcvbnm,./ ~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>? ";


int theoffsetof(char ch);
char upperof(char ch);

inline char upperof(char ch)
{
  for (int c=0; c<sizeof(keymap); c++)
  {
    if (keymap[c] == ch)
    {
      return ukeymap[c];
    }
  }
  return 0;
}
inline int theoffsetof(char ch)
{
  for (int c=0; c<sizeof(keymap); c++)
  {
    if (keymap[c] == ch || ukeymap[c] == ch)
    {
      return c;
    }
  }
  return 0;
}

#endif