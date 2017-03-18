#ifndef Canvas_h
#define Canvas_h

#include "UIThing.h"

// this is fairly useless.
// the WorldCanvas subclasses it, but thats all...

class Canvas: public UIThing
{
public:
  Canvas(): UIThing(), m_image(0) { };
  virtual ~Canvas() { };

  virtual bool acceptsFocus() { return false; }
  virtual string getName() { return "Canvas"; }

  void setImage(HTexture texture) { setDirty(true); m_image = texture; }

  virtual void paint(Display* surface);

private:
  HTexture m_image;
};

#endif