#ifndef SharedSkin_h
#define SharedSkin_h

#include "Display.h"
#include "Skin.h"
#include "Timer.h"

#include <vector>
#include <list>
#include <string>
using namespace std;

class SharableSkin;

class SharedSkin: public Skin, public TimerListener
{
public:

  virtual HTexture currentFrame();
  virtual CollisionBitMask* currentCollisionMask();

  virtual void setFPS(int f) { m_fps = f; reset(); }
  void reset();
  virtual void timeout(TimerEvent* ev);

  virtual int getNumFrames() { return m_numFrames; }

private:
  friend class SharableSkin;
  SharedSkin(SharableSkin* parent);
  ~SharedSkin();

  SharedSkin(const SharedSkin& other); // hidden copy

  SharableSkin* m_parent;
  int m_currentFrame;
  int m_numFrames;

  HTimer m_frameTimer;
  int m_fps;
};

class SharableSkin
{
public:
  SharableSkin(bool generateCollisionMasks = false);
  ~SharableSkin();

  Skin* acquire();
  void release(Skin* skin);

  
  void addImage(const char* filename, int count = 1);

  HTexture getFrame(int o);
  CollisionBitMask* getCollisionMask(int o);
  
  void setFPS(int fps) { m_fps = fps; }
  int getFPS() { return m_fps; }

  size_t getSize() { return m_size; }

  /** 
  @param w the forced width or -1 for actual
  @param h the forced height or -1 for actual
  */
  void forceSize(int w, int h) { m_forcedW = w; m_forcedH = h; }
  
  virtual int getNumFrames() { return m_images.size(); }

  int references() { return m_references; }

  void load();
  void unload();

protected:

  void loadFile(string filename);

private:
  size_t m_size;
  int m_fps;

  int m_forcedW;
  int m_forcedH;
  
  vector<HTexture> m_images;
  vector<CollisionBitMask*> m_collisionMasks;

  int m_references;
  bool m_loaded;
  bool m_generateMasks;
  list<string> m_filenames;

#ifdef HTS_DEBUG
  set<Skin*> m_acquired;
#endif
};

#endif