sdfsdf#ifndef NewThing_h
#define NewThing_h

#include "Thing.h"
#include "BR_Game.h"
#include "Misc/AssetManager.h"

class NewThing: public Thing
{
public:
  NewThing(int z);
  virtual ~NewThing()
  {
  }

  virtual int getWidth() = 0;
  virtual int getHeight() = 0;

  virtual void draw(Display* display, int x, int y) = 0;
protected:
};

#endif