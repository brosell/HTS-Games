#ifndef ExplodingBarrelSkin_h
#define ExplodingBarrelSkin_h

#include "Skin.h"

class ExplodingBarrelSkin: public Skin
{
public:
  ExplodingBarrelSkin();
  
  virtual HTexture currentFrame() = 0;

  virtual int getNumFrames() = 0;
};

#endif