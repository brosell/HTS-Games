#ifndef _WorldCanvas_h
#define _WorldCanvas_h

// this special canvas will be tied to the world and will be the viewport.
// if it is completely obscured, no draw will occur
// if it is visable, the world will draw directly to the screen

// using the canvas allows the world to be drawn in the propper z order
// compared to other UI elements

#include "UI.h"
#include "Game/World.h"

class WorldCanvas: public UIThing
{
public:
  WorldCanvas(World* world): UIThing(), m_world(world) { };
  virtual ~WorldCanvas() { };

  virtual bool acceptsFocus() { return false; }
  virtual string getName() { return "WorldCanvas"; }

  void setWorld(World* w) { m_world = w; }

  virtual void paint(Display* surface);

private:
  World* m_world;
};


#endif