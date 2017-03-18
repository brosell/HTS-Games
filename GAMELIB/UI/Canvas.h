#ifndef Canvas_h
#define Canvas_h

#include "UIThing.h"

// this is fairly useless.
// the WorldCanvas subclasses it, but thats all...

class Canvas: public UIThing
{
public:
  Canvas(): UIThing() { };
  virtual ~Canvas() { };

  virtual bool acceptsFocus() { return false; }
  virtual string getName() { return "Canvas"; }

  virtual void paint(Display* surface) {}
};

#endif