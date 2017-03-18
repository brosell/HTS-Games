#pragma warning (disable : 4786)

#include "AM.h"

AM::AssetType typeFromString(std::string s)
{
  static std::map<string, AM::AssetType> map;
  if (map.empty())
  {
    map["SoundEffect"] = AM::SOUND_EFFECT;
    map["Music"] = AM::MUSIC;
    map["Skin"] = AM::SKIN;
    map["RotateSkin"] = AM::ROTATESKIN;
    map["Font"] = AM::FONT;
    map["Mouse"] = AM::MOUSE;
    map["Texture"] = AM::TEXTURE;
    map["Relevant"] = AM::RELEVANT;
    map["Text"] = AM::TEXT;
  }

  std::map<string, AM::AssetType>::iterator pair;
  pair = map.find(s);
  if (pair != map.end())
  {
    return pair->second;
  }
  return AM::UNDEF;
}

std::string stringFromType(AM::AssetType type)
{
  static std::map<AM::AssetType, std::string> map;
  if (map.empty())
  {
    map[AM::SOUND_EFFECT] = "SoundEffect";
    map[AM::MUSIC] = "Music";
    map[AM::SKIN] = "Skin";
    map[AM::ROTATESKIN] = "RotateSkin";
    map[AM::FONT] = "Font";
    map[AM::MOUSE] = "Mouse";
    map[AM::TEXTURE] = "Texture";
    map[AM::RELEVANT] = "Relevant";
    map[AM::TEXT] = "Text";
  }

  std::map<AM::AssetType, string>::iterator pair;
  pair = map.find(type);
  if (pair != map.end())
  {
    return pair->second;
  }
  return "Undef";
}

AM::AM(IniFile& ini): m_ini(ini) 
{ 
  init();
  m_soundCache.setIni(m_ini);
  m_skinCache.setIni(m_ini);
  m_rotateSkinCache.setIni(m_ini);
  m_fontCache.setIni(m_ini);
}

void AM::report(ostream& strm)
{
  strm << "------------------------------------" << endl;
  strm << "AM report" << endl;
  strm << "----------------" << endl;
  strm << "---- Sounds ----" << endl;
  m_soundCache.report(strm);
  strm << "---- Skins  ----" << endl;
  m_skinCache.report(strm);
  strm << "---- RSkins ----" << endl;
  m_rotateSkinCache.report(strm);
  strm << "---- Fonts  ----" << endl;
  m_fontCache.report(strm);
  strm << "- Total Alloc  -" << endl;
  strm << getAlloced() << endl;
  strm << "------------------------------------" << endl;

  strm << endl;
}

void AM::init()
{
  IniFile::iterator i;
  for (i=m_ini.begin(); i!=m_ini.end(); i++)
  {
    if (i->first != "Text")
    {
      loadCache(i->first);
    }
  }
}

void AM::flush() 
{ 
  m_soundCache.flush(); 
  m_skinCache.flush();
  m_rotateSkinCache.flush();
  m_fontCache.flush();
}

void AM::loadCache(std::string name)
{
  AssetType type = typeFromString(m_ini[name]["Type"]);
  CacheId id;
  switch(type)
  {
  case SOUND_EFFECT:
    id = m_soundCache.add(name);
    break;
  case SKIN:
    id = m_skinCache.add(name);
    break;
  case ROTATESKIN:
    id = m_rotateSkinCache.add(name);
    break;
  case FONT:
    id = m_fontCache.add(name);
    break;
  }

  m_assets[name] = id;
}


SoundEffectHandle AM::getSoundEffect(std::string name, bool precache)
{
  CacheId id = m_assets[name];
  if (precache)
  {
    getSoundEffect(id);
  }

  return SoundEffectHandle(this, id);
}

SharedSkinHandle AM::getSkin(std::string name, bool precache)
{
  CacheId id = m_assets[name];
  int fps = m_ini.getInt(name, "FPS");
  int frames = m_ini.getInt(name, "Frames");
  if (precache)
  {
    getSkin(id);
  }
  return SharedSkinHandle(this, id, fps, frames);
}

RotateSkinHandle AM::getRotateSkin(std::string name, bool precache)
{
  CacheId id = m_assets[name];
  int fps = m_ini.getInt(name, "FPS");
  int frames = m_ini.getInt(name, "Frames");
  int rotations = m_ini.getInt(name, "Rotations");

  if (precache)
  {
    getRotateSkin(id);
  }
  return RotateSkinHandle(this, id, fps, frames, rotations);
}

FontHandle AM::getFont(std::string name, bool precache)
{
  CacheId id = m_assets[name];
  if (precache)
  {
    getFont(id);
  }
  return FontHandle(this, id);
}

////////////////
// SHARED SKIN HANDLE
////////////////
void SharedSkinHandle::reset()
{
  m_currentFrame = 0;
  
  if (m_frameTimer != 0)
  {
    Timer::destroy(m_frameTimer);
    m_frameTimer = 0;
  }
  
  if (m_fps > 0)
  {
    m_frameTimer = Timer::create("SharedSkin", -1, 1000/m_fps, this, 0, true);
  }
}

void SharedSkinHandle::timeout(TimerEvent* ev)
{
  m_currentFrame++;
  if (m_currentFrame >= m_numFrames)
  {
    skinLooped();
    m_currentFrame = 0;
  }
  frameChanged();
}

////////////////////////////
// ROTATE SKIN HANDLE
////////////////////////////
void RotateSkinHandle::reset()
{
//  m_currentFrame = 0;
//  m_currentRotation = 0;
  
  if (m_frameTimer != 0)
  {
    Timer::destroy(m_frameTimer);
    m_frameTimer = 0;
  }
  
  if (m_fps > 0)
  {
    m_frameTimer = Timer::create("SharedSkin", -1, 1000/m_fps, this, 0, true);
  }
}

void RotateSkinHandle::timeout(TimerEvent* ev)
{
  m_currentFrame++;
  if (m_currentFrame >= m_numFrames)
  {
    skinLooped();
    m_currentFrame = 0;
  }
  frameChanged();
}
