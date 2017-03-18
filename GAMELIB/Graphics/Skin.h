#ifndef _Skin_h
#define _Skin_h

#include <set>
using namespace std;

#include "Display.h"
#include "CollisionBitMask.h"

class Skin;

/**
This event is sent to registered listeners when the skins animation start over
*/
class SkinLoopEvent
{
public:
  Skin* skin;
};

/**
Objects interested in SkinEvents must subclass this
*/
class SkinListener
{
public:
  virtual void skinLooped(SkinLoopEvent* event) { }
};


class Skin
{
public:
  
  void blit(Display* display, int x, int y, bool centerCoords = true);

  void addListener(SkinListener* listener);
  void removeListener(SkinListener* listener);

  virtual HTexture currentFrame() = 0;
  virtual CollisionBitMask* currentCollisionMask() = 0;

  int getWidth()
  {
    const TextureInfo* ti = Display::getInstance()->getTextureInfo(currentFrame());
    if (ti != 0)
    {
      return ti->w;
    }
    return 0;
  }

  int getHeight()
  {
    const TextureInfo* ti = Display::getInstance()->getTextureInfo(currentFrame());
    if (ti != 0)
    {
      return ti->h;
    }
    return 0;
  }

  virtual void setFPS(int f) = 0;
  virtual int getNumFrames() = 0;
  virtual void reset() = 0;

protected:
  void setCurrentTexture(HTexture t) { m_currentTexture = t; }
  void skinLooped();
  Skin();
  virtual ~Skin();
private:
  HTexture m_currentTexture;
  set<SkinListener*> m_listeners;
  SkinLoopEvent m_loopEvent;
};

#endif
