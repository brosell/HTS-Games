#ifndef SharedRotateSkin_h
#define SharedRotateSkin_h

#include "Graphics/Display.h"
#include "Graphics/Skin.h"
#include "Timer.h"

#include <vector>
#include <list>
#include <string>
using namespace std;

class SharableRotateSkin;

class SharedRotateSkin: public Skin, public TimerListener
{
public:

  virtual HTexture currentFrame();
  virtual CollisionBitMask* currentCollisionMask();

  void setRotation(int r);
  
  void setAngle(int a);

  virtual void setFPS(int f) { m_fps = f; reset(); }

  void reset();
  virtual void timeout(TimerEvent* ev);

  void setFrame(int f);

  virtual int getNumFrames() { return m_numFrames; }
  int getNumRotations();

  int currentRotation() { return m_currentRotation; }

private:
  friend class SharableRotateSkin;
  SharedRotateSkin(SharableRotateSkin* parent);
  ~SharedRotateSkin();

  SharedRotateSkin(const SharedRotateSkin& other); // hidden copy

  SharableRotateSkin* m_parent;
  int m_currentFrame;
  int m_numFrames;

  int m_currentRotation;

  HTimer m_frameTimer;
  int m_fps;
};

class SharableRotateSkin
{
public:
  SharableRotateSkin(int rotations, bool generateCollisionMask = false);
  ~SharableRotateSkin();

  SharedRotateSkin* acquire();
  void release(SharedRotateSkin* skin);

  
  void addImage(const char* filename, int count = 1);

  HTexture getFrame(int r, int f);

  CollisionBitMask* getCollisionMask(int r, int f)
  {
    lassert(m_generateMasks);
    return m_collisionMasks[r][f];
  }
  
  void setFPS(int fps) { m_fps = fps; }
  int getFPS() { return m_fps; }

  /** 
  @param w the forced width or -1 for actual
  @param h the forced height or -1 for actual
  */
  void forceSize(int w, int h) { m_forcedW = w; m_forcedH = h; }
  
  virtual int getNumFrames() { return m_images[0].size(); }
  int getNumRotations() { return m_rotations; }

  int references() { return m_references; }

  void load();
  void unload();

protected:
  void load(SDL_Surface* surface, string fn);

private:
  int m_fps;
  int m_rotations;

  int m_forcedW;
  int m_forcedH;
  
  vector<HTexture> m_images[72];
  vector<CollisionBitMask*> m_collisionMasks[72];

  int m_references;
  bool m_loaded;
  bool m_generateMasks;
  list<string> m_filenames;

#ifdef _DEBUG
  set<Skin*> m_acquired;
#endif
};

#endif