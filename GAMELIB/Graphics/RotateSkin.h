#ifndef RotateSkin_h
#define RotateSkin_h

#include "Graphics/Display.h"
#include "Graphics/Skin.h"
#include "CollisionBitMask.h"

#include "Timer.h"

class RotateSkin: public Skin, public TimerListener
{
public:
  RotateSkin(int numOfRotations);
  ~RotateSkin();

  void setFPS(int fps) { m_fps = fps; reset(); }
  void addImage(const char* filename, int count = 1);  
  void addImage(SDL_Surface* orig, int count);
  
  virtual HTexture currentFrame() { return m_skins[m_currentFrame][m_currentRotation]; }

  const CollisionBitMask* getCollisionBitMask()
  {
    return m_bitMasks[m_currentFrame][m_currentRotation];
  }

  void setRotation(int r) { m_currentRotation = r; }
  void setAngle(int angle) { m_currentRotation = (angle/(360/m_numberRotations)); }

  virtual void timeout(TimerEvent* event);

  int getNumFrames() { return m_numFrames; }

  // starts the anaimation over
  void reset() 
  { 
    m_currentFrame = 0; 
    Timer::destroy(m_frameTimer);
    m_frameTimer = Timer::create("RotateSkin", 0, 1000/m_fps, this, 0, true);
  }


private:
  HTexture m_skins[64][36]; // m_skins[frame][rotInc]
  CollisionBitMask* m_bitMasks[64][36];

  int m_fps;
  HTimer m_frameTimer;

  int m_numberRotations;

  int m_currentFrame;
  int m_currentRotation;
  int m_numFrames;

  set<SDL_Surface*> m_manipulated;
};

#endif