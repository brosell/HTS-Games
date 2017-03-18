#ifndef AM_h
#define AM_h

#include "Utils.h"
#include "Cache.h"

#include "SoundEffectLoader.h"
#include "SkinLoader.h"
#include "RotateSkinLoader.h"
#include "FontLoader.h"

class Handle;
class SoundEffectHandle;
class SharedSkinHandle;
class RotateSkinHandle;
class FontHandle;


class AM: hts::Noncopyable
{
  Cache<SoundEffect, SoundEffectLoader> m_soundCache;
  Cache<SharableSkin, SkinLoader> m_skinCache;
  Cache<SharableRotateSkin, RotateSkinLoader> m_rotateSkinCache;
  Cache<Font, FontLoader> m_fontCache;

public:
  AM(IniFile& ini);

  enum AssetType
  {
    UNDEF,
    SOUND_EFFECT,
    MUSIC,
    SKIN,
    ROTATESKIN,
    FONT,
    MOUSE,
    TEXTURE,
    RELEVANT,
    TEXT
  };


  size_t getAlloced() 
  { 
    return(getSoundEffectAlloced() 
         + getSkinAlloced()
         + getRotateSkinAlloced()
         + getFontAlloced()
          );
  }
  void flush();

  // sound effects
  SoundEffectHandle getSoundEffect       (std::string name, bool precache = false);
  size_t            getSoundEffectAlloced() { return m_soundCache.getAlloced(); }
  void              flushSoundEffects    () { m_soundCache.flush(); }
  void              setSoundEffectLimit  (size_t limit) { m_soundCache.setLimit(limit); }
  
  // Skins
  SharedSkinHandle  getSkin              (std::string name, bool precache = false);
  size_t            getSkinAlloced       () { return m_skinCache.getAlloced(); }
  void              flushSkins           () { m_skinCache.flush(); }
  void              setSkinLimit         (size_t limit) { m_skinCache.setLimit(limit); }
  
  RotateSkinHandle  getRotateSkin        (std::string name, bool precache = false);
  size_t            getRotateSkinAlloced () { return m_rotateSkinCache.getAlloced(); }
  void              flushRotateSkins     () { m_rotateSkinCache.flush(); }
  void              setRotateSkinLimit   (size_t limit) { m_rotateSkinCache.setLimit(limit); }

  // FONT
  FontHandle        getFont              (std::string name, bool precache = false);
  size_t            getFontAlloced       () { return m_fontCache.getAlloced(); }
  void              flushFonts           () { m_fontCache.flush(); }
  void              setFontLimit         (size_t limit) { m_fontCache.setLimit(limit); }

  string getText(string name) { return m_ini["Text"][name]; }

  string getAttribute(string name, string attr) { return m_ini[name][attr]; }

  void report(ostream& strm);
private:
  IniFile& m_ini;
  void init();
  void loadCache(std::string name);

  map<std::string, CacheId> m_assets;

  // called from handle classes
  SoundEffect* getSoundEffect(CacheId id) { return m_soundCache.get(id); }
  SharableSkin* getSkin(CacheId id) { return m_skinCache.get(id); }
  SharableRotateSkin* getRotateSkin(CacheId id) { return m_rotateSkinCache.get(id); }
  Font* getFont(CacheId id) { return m_fontCache.get(id); }

  friend class SoundEffectHandle;
  friend class SharedSkinHandle;
  friend class RotateSkinHandle;
  friend class FontHandle;
};

class Handle
{
public:
  Handle(AM* am, CacheId id): m_id(id), m_am(am) { }
  virtual ~Handle() { }
  bool isValid() { return m_am != 0; }
  CacheId getId() const { return m_id; }
protected:
  AM* m_am;
  CacheId m_id;
};

/** handle for sound effects */
class SoundEffectHandle: public Handle
{
public:
  SoundEffectHandle(AM* am=0, CacheId id=0): Handle(am, id) { }
  SoundEffect* operator->() { return ptr(); }
  
  SoundEffect* ptr()
  { 
    if (m_am != 0) 
      return m_am->getSoundEffect(m_id); 
    return 0;
  }
};

class FontHandle: public Handle
{
public:
  FontHandle(AM* am=0, CacheId id=0): Handle(am, id) { }
  Font* operator->() { return ptr(); }
  
  Font* ptr()
  { 
    if (m_am != 0)
      return m_am->getFont(m_id); 
    return 0;
  }
};

class SharedSkinHandle: public Skin, public TimerListener, public Handle
{
public:
  SharedSkinHandle(AM* am=0, CacheId id=0, int fps=0, int numFrames=0): 
  Handle(am, id),
  m_numFrames(numFrames),
  m_currentFrame(0),
  m_frameTimer(0),
  m_fps(fps)
  {
    reset();
  }

  SharedSkinHandle(const SharedSkinHandle& other): 
  Handle(other.m_am, other.m_id)
  {
    m_numFrames = other.m_numFrames;
    m_currentFrame = other.m_currentFrame;
    m_fps = other.m_fps;
    m_frameTimer = 0;
    reset();
  }

  operator=(const SharedSkinHandle& other)
  {
    m_am = other.m_am;
    m_id = other.m_id;
    m_numFrames = other.m_numFrames;
    m_currentFrame = other.m_currentFrame;
    m_fps = other.m_fps;
    if (m_frameTimer != 0)
    {
      Timer::destroy(m_frameTimer);
      m_frameTimer = 0;
    }
    reset();
  }

  ~SharedSkinHandle()
  {
    if (m_frameTimer != 0)
    {
      Timer::destroy(m_frameTimer);
      m_frameTimer = 0;
    }
  }

  SharedSkinHandle* ptr()
  { 
    if (m_am!=0) 
      return this; 
    return 0;
  }

  SharedSkinHandle* operator->() { return ptr(); }
  


  virtual HTexture currentFrame() { return m_am->getSkin(m_id)->getFrame(m_currentFrame); }
  virtual CollisionBitMask* currentCollisionMask() { return m_am->getSkin(m_id)->getCollisionMask(m_currentFrame); }

  virtual void setFPS(int f) { m_fps = f; reset(); }
  void reset();

  virtual void timeout(TimerEvent* ev);

  virtual int getNumFrames() { return m_numFrames; }

private:
  

  int m_currentFrame;
  int m_numFrames;

  HTimer m_frameTimer;
  int m_fps;

};

class RotateSkinHandle: public Skin, public TimerListener, public Handle
{
public:
  RotateSkinHandle(AM* am=0, CacheId id=0, int fps=0, int numFrames=0, int nRotations=0): 
  Handle(am, id),
  m_numFrames(numFrames),
  m_nRotations(nRotations),
  m_currentFrame(0),
  m_currentRotation(0),
  m_frameTimer(0),
  m_fps(fps)
  {
    reset();
  }

  RotateSkinHandle(const RotateSkinHandle& other): 
  Handle(other.m_am, other.m_id)
  {
    m_numFrames = other.m_numFrames;
    m_nRotations = other.m_nRotations;
    m_currentFrame = other.m_currentFrame;
    m_currentRotation = other.m_currentRotation;
    m_frameTimer = 0;
    m_fps = other.m_fps;
    reset();
  }

  operator=(const RotateSkinHandle& other)
  {
    m_am = other.m_am;
    m_id = other.m_id;
    m_numFrames = other.m_numFrames;
    m_nRotations = other.m_nRotations;
    m_currentFrame = other.m_currentFrame;
    m_currentRotation = other.m_currentRotation;
    m_fps = other.m_fps;

    if (m_frameTimer != 0)
    {
      Timer::destroy(m_frameTimer);
      m_frameTimer = 0;
    }
    
    reset();
  }



  ~RotateSkinHandle()
  {
    if (m_frameTimer != 0)
    {
      Timer::destroy(m_frameTimer);
      m_frameTimer = 0;
    }
  }


  RotateSkinHandle* ptr()
  { 
    if (m_am!=0) 
      return this; 
    return 0;
  }

  RotateSkinHandle* operator->() { return ptr(); }

  virtual HTexture currentFrame() 
  { 
    return m_am->getRotateSkin(m_id)->getFrame(m_currentRotation, m_currentFrame); 
  }

  int currentFrameNum() { return m_currentFrame; }

  virtual CollisionBitMask* currentCollisionMask() { return m_am->getRotateSkin(m_id)->getCollisionMask(m_currentRotation, m_currentFrame); }

  virtual void setFPS(int f) { m_fps = f; reset(); }
  void reset();

  void setAngle(int a) 
  { 
    m_currentRotation = ((float)a/360.0)*m_nRotations; 
  }
  
  void setRotation(int r) { m_currentRotation = r; }
  int currentRotation() { return m_currentRotation; }
  
  virtual void timeout(TimerEvent* ev);

  virtual int getNumFrames() { return m_numFrames; }
  int getNumRotations() { return m_nRotations; }

private:
  int m_currentFrame;
  int m_currentRotation;

  int m_numFrames;
  int m_nRotations;
 
  HTimer m_frameTimer;
  int m_fps;
};

inline operator<(const RotateSkinHandle& one, const RotateSkinHandle& two)
{
  return one.getId() < two.getId();
}

AM::AssetType typeFromString(std::string s);
std::string stringFromType(AM::AssetType type);



#endif