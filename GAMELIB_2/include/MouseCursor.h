#pragma warning (disable : 4786) 
#ifndef MouseCursor_h
#define MouseCursor_h

#include "AM.h"

class MouseCursor
{
public:
  MouseCursor(string name);

  MouseCursor() { }

  bool isValid() { return skin.isValid(); }

  SharedSkinHandle skin;
  int hotX;
  int hotY;
};

#endif