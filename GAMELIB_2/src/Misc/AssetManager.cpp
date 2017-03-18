#pragma warning (disable : 4503 4786 4530)

#include "AssetManager.h"
#include "FileUtils.h"
#include "FileManager.h"
#include "StdString.h"
#include "StringTokenizer.h"

#include "boost/format.hpp"

AssetManager::AssetManager(string assetIniFn)
{
  m_ini = new IniFile(assetIniFn);
  m_ini->read();
  load();
}

AssetManager::~AssetManager()
{
  unload();
  delete m_ini;
}

void AssetManager::setAssetFn(string fn)
{
  unload();
  if (m_ini != 0)
  {
    delete m_ini;
    m_ini = 0;
  }
  m_ini = new IniFile(fn);
  m_ini->read();
  load();
}

void AssetManager::load()
{
  IniFile::iterator pair;
  for (pair = m_ini->begin(); pair!=m_ini->end(); pair++)
  {
    if (pair->first == "Includes")
    {
      continue;
    }
    if ((*m_ini)[pair->first]["Type"] == "Relevant")
    {
      continue;
    }

    Asset* asset = new Asset;
    asset->asset = 0;
    asset->type = UNDEF;
    asset->used = false;
    asset->name = pair->first;
    asset->references = 0;
    m_assetMap[asset->name] = asset;

    if (m_ini->getInt(pair->first, "PreCache") != 0)
    {
      load(asset->name);
    }
  }
}

bool AssetManager::verify()
{
  list<string> missingFiles;

  IniFile::iterator pair;
  for (pair = m_ini->begin(); pair!=m_ini->end(); pair++)
  {
    string assetName = pair->first;
    if (assetName == "Includes" || assetName == "None")
    {
      continue;
    }

    if ((*m_ini)[assetName]["Type"] == "Skin" ||
      (*m_ini)[assetName]["Type"] == "RotateSkin")
    {
      // we have to iterate over the frames
      int frameCount = m_ini->getInt(assetName, "Frames");
      if (frameCount == 0)
        frameCount = 1;
      
      char fn[255];
      for (int c=1; c<=frameCount; c++)
      {
        sprintf(fn, "Frame%02d", c);
        string frameFn = (*m_ini)[assetName][fn];
        if (frameFn != "")
        {
          if(!fm_fileExists(frameFn))
          {
            missingFiles.push_back(frameFn);
          }
        }
        else
        {
          // it's OK, blank frames are OK
        }
      }
      
    }
    else if ((*m_ini)[assetName]["Type"] == "Text")
    {
      // just skip this one because text is stored in the assets.ini
    }
    else if ((*m_ini)[assetName]["Type"] == "MouseCursor")
    {
      // skip this one too
      string skin = (*m_ini)[assetName]["Skin"];
      if ( !m_ini->hasSection(skin))
      {
        missingFiles.push_back(skin);
      }
    }
    else
    {
      if(!fm_fileExists((*m_ini)[assetName]["Filename"]))
      {
        missingFiles.push_back((*m_ini)[assetName]["Filename"]);
      }
    }
  }

  list<string>::iterator i;
  for (i=missingFiles.begin(); i!=missingFiles.end(); i++)
  {
    logError(Error, "Required file missing (%s)", (*i).c_str());
  }

  return (missingFiles.size() == 0);
}

void AssetManager::load2(string assetName)
{
  Asset* asset = load(assetName);
  if (asset != 0)
  {
    m_assetMap[asset->name] = asset;
  }
}

Asset* AssetManager::load(string assetName)
{
  string type = (*m_ini)[assetName]["Type"];
  if (type == "SoundEffect")
  {
    return loadSoundEffect(assetName);
  }
  else if (type == "Music")
  {
    return loadMusic(assetName);
  }
  else if (type == "Skin")
  {
    return loadSkin(assetName);
  }
  else if (type == "RotateSkin")
  {
    return loadRotateSkin(assetName);
  }
  else if (type == "Font")
  {
    return loadFont(assetName);
  }
  else if (type == "Texture")
  {
    return loadTexture(assetName);
  }
  else if (type == "MouseCursor")
  {
    return loadMouseCursor(assetName);
  }
  else if (type == "Relevant")
  {
    // kinda like a remark. makes sure files get where they belong
    return 0;
  }
  else if (type == "Text")
  {
    return loadText(assetName);
  }
  else
  {
    logError(Error, "Unknown asset type(%s) for %s", type.c_str(), assetName.c_str());
  }

  return 0;
}

Asset* AssetManager::loadMouseCursor(string assetName)
{
  logError(Debug, "AssetManager::loadMouseCursor(%s)", assetName.c_str());
  
  Asset* a = m_assetMap[assetName];
  if (!a)
  {
    logError(Error, "Asset not found (%s)", assetName.c_str());
    return 0;
  }

  Point p = getPointAttribute(assetName, "HotSpot");
  string skinName = (*m_ini)[assetName]["Skin"];

  MouseCursor* mouse = 0;
  if (skinName != "")
  {
    mouse = new MouseCursor;
    mouse->hotX = p.x;
    mouse->hotY = p.y;
    //mouse->skin = getSkin(skinName);

    a->asset = mouse;
    a->name = assetName;
    a->type = MOUSE;
    a->used = false;
  }
  return a;
}


Asset* AssetManager::loadText(string assetName)
{
  logError(Debug, "AssetManager::loadText(%s)", assetName.c_str());
  
  Asset* a = m_assetMap[assetName];
  if (!a)
  {
    logError(Error, "Asset not found (%s)", assetName.c_str());
    return 0;
  }

  int lines = m_ini->getInt(assetName, "Lines");

  string* asstr = 0;
  if (lines > 0)
  {
    CStdString ts = "";
    asstr = new string;
    a->asset = asstr;
    a->name = assetName;
    a->type = TEXT;
    a->used = false;

    CStdString lineStr;
    CStdString value;
    for (int c=0; c<lines; c++)
    {
      lineStr.Format("Line%02d", c+1);
      value.Format("%s\n", (*m_ini)[assetName][lineStr].c_str());
      ts = ts + value;
    }
    (*asstr) = ts.Trim();

  }
  return a;
}

Asset* AssetManager::loadSoundEffect(string assetName)
{
  logError(Debug, "AssetManager::loadSoundEffect(%s)", assetName.c_str());

  Asset* a = m_assetMap[assetName];
  if (!a)
  {
    logError(Error, "Asset not found (%s)", assetName.c_str());
    return 0;
  }

  string fn = (*m_ini)[assetName]["Filename"];
  string group = (*m_ini)[assetName]["Group"];
  if (fm_fileExists(fn))
  {
    SoundEffect* se = new SoundEffect(group, fn);
    a->asset = se;
    a->name = assetName;
    a->type = SOUND_EFFECT;
  }
  else
  {
    logError(Error, "AssetManager::loadSoundEffect(%s) file not found (%s)", assetName.c_str(), fn.c_str());
  }

  return a;
}

Asset* AssetManager::loadMusic(string assetName)
{
  logError(Debug, "AssetManager::loadMusic(%s)", assetName.c_str());

  Asset* a = m_assetMap[assetName];
  if (!a)
  {
    logError(Error, "Asset not found (%s)", assetName.c_str());
    return 0;
  }

  string fn = (*m_ini)[assetName]["Filename"];
  if (fm_fileExists(fn))
  {
    Music* mus = new Music(fn);
    a->asset = mus;
    a->name = assetName;
    a->type = MUSIC;
  }
  else
  {
    logError(Error, "AssetManager::loadMusic(%s) file not found (%s)", assetName.c_str(), fn.c_str());
  }
  return a;
}

Asset* AssetManager::loadSkin(string assetName)
{
  logError(Debug, "AssetManager::loadSkin(%s)", assetName.c_str());
  Asset* a = m_assetMap[assetName];
  if (!a)
  {
    logError(Error, "Asset not found (%s)", assetName.c_str());
    return 0;
  }

  bool mask = m_ini->getInt(assetName, "UseMask");
  
  SharableSkin* skin = new SharableSkin(mask);
  int fps = m_ini->getInt(assetName, "FPS");
//  if (fps == 0)
//    fps = 15;

  skin->setFPS(fps);

  Point forcedSize = getPointAttribute(assetName, "ForcedSize");
  if (forcedSize.x > 0 && forcedSize.y > 0)
  {
    skin->forceSize(forcedSize.x, forcedSize.y);
  }
  else
  {
    skin->forceSize(-1, -1);
  }
  int frameCount = m_ini->getInt(assetName, "Frames");
  if (frameCount == 0)
    frameCount = 1;

  char fn[255];
  for (int c=1; c<=frameCount; c++)
  {
    sprintf(fn, "Frame%02d", c);
    string frameFn = (*m_ini)[assetName][fn];
    if (frameFn != "")
    {
      skin->addImage(frameFn.c_str(), 1);
    }
  }

  a->asset = skin;
  a->name = assetName;
  a->type = SKIN;

  return a;
}

Asset* AssetManager::loadRotateSkin(string assetName)
{
  Asset* a = m_assetMap[assetName];
  if (!a)
  {
    logError(Error, "Asset not found (%s)", assetName.c_str());
    return 0;
  }
  
  int rotations = m_ini->getInt(assetName, "Rotations");
  if (rotations == 0)
    rotations = 1;

  bool mask = m_ini->getInt(assetName, "UseMask");

  SharableRotateSkin* skin = new SharableRotateSkin(rotations, mask);

  int fps = m_ini->getInt(assetName, "FPS");

  skin->setFPS(fps);

  Point forcedSize = getPointAttribute(assetName, "ForcedSize");
  if (forcedSize.x > 0 && forcedSize.y > 0)
  {
    skin->forceSize(forcedSize.x, forcedSize.y);
  }
  else
  {
    skin->forceSize(-1, -1);
  }


  int frameCount = m_ini->getInt(assetName, "Frames");
  if (frameCount == 0)
    frameCount = 1;

  char fn[255];
  for (int c=1; c<=frameCount; c++)
  {
    sprintf(fn, "Frame%02d", c);
    string frameFn = (*m_ini)[assetName][fn];
    if (frameFn != "")
    {
      skin->addImage(frameFn.c_str(), 1);
    }
  }
  a->asset = skin;
  a->name = assetName;
  a->type = ROTATESKIN;

  return a;

}

Asset* AssetManager::loadTexture(string assetName)
{
  logError(Debug, "AssetManager::loadTexture(%s)", assetName.c_str());
  Asset* a = m_assetMap[assetName];
  if (!a)
  {
    logError(Error, "Asset not found (%s)", assetName.c_str());
    return 0;
  }

  string fn = (*m_ini)[assetName]["Filename"];
  if (fm_fileExists(fn))
  {
    HTexture texture = Display::getInstance()->acquire(fn.c_str());
    if (texture == 0)
    {
      logError(Error, "Couldn't load texture (%s)", fn.c_str());
    }
    else
    {
      a->asset = (void*)texture;
      a->name = assetName;
      a->type = TEXTURE;
    }
  }
  else
  {
    logError(Error, "AssetManager::loadTexture(%s) file not found (%s)", assetName.c_str(), fn.c_str());
  }
  return a;
}

Asset* AssetManager::loadFont(string assetName)
{
  logError(Debug, "AssetManager::loadFont(%s)", assetName.c_str());
  Asset* a = m_assetMap[assetName];
  if (!a)
  {
    logError(Error, "Asset not found (%s)", assetName.c_str());
    return 0;
  }

  string fn = (*m_ini)[assetName]["Filename"];
  if (fm_fileExists(fn))
  {
    Font* f = new Font(fn);
    if (f!=0)
    {
      a = new Asset;
      a->asset = f;
      a->name = assetName;
      a->type = FONT1;
    }
  }
  
  if (a == 0)
  {
    logError(Error, "AssetManager::loadFont(%s) error (%s)", assetName.c_str(), fn.c_str());
  }

  return a;
}

void AssetManager::unload()
{
  list<string> unused;
  map<string, Asset*>::iterator pair;
  for (pair = m_assetMap.begin(); pair!=m_assetMap.end(); pair++)
  {
    Asset* asset = pair->second;

    if (asset == 0)
    {
      continue;
    }

    if (asset->used == false)
    {
      unused.push_back(asset->name);
    }

    switch (asset->type)
    {
    case SOUND_EFFECT:
      delete (SoundEffect*)asset->asset;
      logError(Debug, "AssetManager::~ freed SoundEffect(%s)", asset->name.c_str());
      break;
    case MUSIC:
      delete (Music*)asset->asset;
      logError(Debug, "AssetManager::~ freed Music(%s)", asset->name.c_str());
      break;
    case SKIN:
      delete (SharableSkin*)asset->asset;
      logError(Debug, "AssetManager::~ freed Skin(%s)", asset->name.c_str());
      break;
    case ROTATESKIN:
      delete (SharableRotateSkin*)asset->asset;
      logError(Debug, "AssetManager::~ freed RotateSkin(%s)", asset->name.c_str());
      break;
    case FONT1:
      {
        Font* font = static_cast<Font*>(asset->asset);
        delete font;
        logError(Debug, "AssetManager::~ freed Font(%s)", asset->name.c_str());
      }
      break;
    case TEXTURE:
      Display::getInstance()->release((HTexture)asset->asset);
      logError(Debug, "AssetManager::~ freed Texture(%s)", asset->name.c_str());
      break;
    case TEXT:
      delete (string*)asset->asset;
      logError(Debug, "AssetManager::~ freed Text(%s)", asset->name.c_str());
      break;
    case MOUSE:
      {
        MouseCursor* mouse = static_cast<MouseCursor*>(asset->asset);
        delete mouse;
      }
      break;
    default:
      logError(Debug, "AssetManager::~ Asset type %d (%s) was probably never loaded", asset->type, asset->name.c_str());
      break;
    }

    delete asset;
  }
  m_assetMap.clear();

  list<string>::iterator i;
  for (i=unused.begin(); i!=unused.end(); i++)
  {
    logError(Error, "Asset \"%s\" was never used", (*i).c_str());
  }
}

bool AssetManager::isAssetLoaded(string name)
{
  Asset* a=m_assetMap[name];
  return (a != 0 && a->asset != 0);
}

#define ASSET_TYPE_ASSERT(asset, t) \
  lassertWithReturn(asset->type == t, \
        (boost::format("Asset %s isn't " #t) % asset->name).str().c_str(), \
        0); \

SoundEffect* AssetManager::getSoundEffect(string assetName)
{
  error << "tried to use old asset manager for " << assetName << endl;
  if (!isAssetLoaded(assetName))
  {
    load2(assetName);
  }
  map<string, Asset*>::iterator pair;
  pair = m_assetMap.find(assetName);
  if (pair != m_assetMap.end())
  {
    Asset* asset = pair->second;
    if (asset != 0)
    {
      lassert2(asset != 0, "AssetManager asset is null (SoundEffect)");
      asset->used = true;
      asset->references++;
      ASSET_TYPE_ASSERT(asset, SOUND_EFFECT);
      m_assetToAssetMap[asset->asset] = asset;
      return (SoundEffect*)(asset->asset);
    }
  }
  logError(Error, "Tried to get SoundEffect (%s) but it was never loaded or there was a problem", assetName.c_str());
  return 0;
}

void AssetManager::releaseSoundEffect(SoundEffect* effect)
{
  Asset* asset = m_assetToAssetMap[effect];
  lassert(asset->references > 0);
  lassert(asset->asset == effect);
  asset->references--;
  if (asset->references <= 0)
  {
    logError(Inform, "Released Soundeffect (%s)", asset->name.c_str());
    asset->references = 0;
    m_assetToAssetMap.erase(asset->asset);
    asset->asset = 0;
    delete effect;
  }
}

Music* AssetManager::getMusic(string assetName)
{
  error << "tried to use old asset manager for " << assetName << endl;
  if (!isAssetLoaded(assetName))
  {
    load2(assetName);
  }

  map<string, Asset*>::iterator pair;
  pair = m_assetMap.find(assetName);
  if (pair != m_assetMap.end())
  {
    Asset* asset = pair->second;
    if (asset != 0)
    {
      lassert2(asset != 0, "AssetManager asset is null (Music)");
      asset->used = true;
      ASSET_TYPE_ASSERT(asset, MUSIC);
      return (Music*)(asset->asset);
    }
  }
  logError(Error, "Tried to get Music (%s) but it was never loaded or there was a problem", assetName.c_str());
  return 0;
}

MouseCursor* AssetManager::getMouseCursor(string assetName)
{
  error << "tried to use old asset manager for " << assetName << endl;
  if (!isAssetLoaded(assetName))
  {
    load2(assetName);
  }

  map<string, Asset*>::iterator pair;
  pair = m_assetMap.find(assetName);
  if (pair != m_assetMap.end())
  {
    Asset* asset = pair->second;
    if (asset != 0)
    {
      asset->used = true;
      asset->references++;
      ASSET_TYPE_ASSERT(asset, MOUSE);
      m_assetToAssetMap[asset->asset] = asset;
      return (MouseCursor*)(asset->asset);
    }
  }
  logError(Error, "Tried to get MouseCursor (%s) but it was never loaded or there was a problem", assetName.c_str());
  return 0;
}

void AssetManager::releaseMouseCursor(MouseCursor* mouse)
{
  Asset* asset = m_assetToAssetMap[mouse];
  lassert(asset->references > 0);
  lassert(asset->asset == mouse);
  asset->references--;
  if (asset->references <= 0)
  {
    logError(Inform, "Released MouseCursor (%s)", asset->name.c_str());
    asset->references = 0;
    m_assetToAssetMap.erase(asset->asset);
    delete static_cast<MouseCursor*>(asset->asset);
    asset->asset = 0;
    
  }
}


Skin* AssetManager::getSkin(string assetName)
{
  error << "tried to use old asset manager for " << assetName << endl;
/*
Skins are a special case in that they manage themselves
so we have to pass along most of the management to them
  */
  if (!isAssetLoaded(assetName))
  {
    load2(assetName);
  }

  map<string, Asset*>::iterator pair;
  pair = m_assetMap.find(assetName);
  if (pair != m_assetMap.end())
  {
    Asset* asset = pair->second;
    if (asset != 0)
    {
      asset->used = true;
      ASSET_TYPE_ASSERT(asset, SKIN);
      SharableSkin* ss = (SharableSkin*)(asset->asset);
      Skin* skin = ss->acquire();
      m_assetToAssetMap[skin] = asset;
      return skin;
    }
  }
  logError(Error, "Tried to get Skin (%s) but it was never loaded or there was a problem", assetName.c_str());
  return 0;
}

void AssetManager::releaseSkin(Skin* skin)
{
  logError(Debug, "Releasing SharedSkin (%08x)", skin);
  Asset* asset = m_assetToAssetMap[skin];
  
  if (asset == 0)
  {
    logError(Error, "Unknown Skin (%08x)", skin);
    return;
  }

  SharableSkin* ss = (SharableSkin*)asset->asset;
  ss->release(skin);
  m_assetToAssetMap.erase(skin);

  if (ss->references() == 0)
  {
    delete ss;
    asset->asset = 0;
  }
}

SharedRotateSkin* AssetManager::getRotateSkin(string assetName)
{
  error << "tried to use old asset manager for " << assetName << endl;
/*
Skins are a special case in that they manage themselves
so we have to pass along most of the management to them
  */
  if (!isAssetLoaded(assetName))
  {
    load2(assetName);
  }

  map<string, Asset*>::iterator pair;
  pair = m_assetMap.find(assetName);
  if (pair != m_assetMap.end())
  {
    Asset* asset = pair->second;
    if (asset != 0)
    {
      asset->used = true;
      ASSET_TYPE_ASSERT(asset, ROTATESKIN);
      SharableRotateSkin* ss = (SharableRotateSkin*)(asset->asset);
      SharedRotateSkin* skin = ss->acquire();
      m_assetToAssetMap[skin] = asset;
      return skin;
    }
  }
  logError(Error, "Tried to get RotateSkin (%s) but it was never loaded or there was a problem", assetName.c_str());
  return 0;
}

void AssetManager::releaseRotateSkin(SharedRotateSkin* skin)
{
  logError(Debug, "Releasing SharedSkin (%08x)", skin);
  Asset* asset = m_assetToAssetMap[skin];
  
  if (asset == 0)
  {
    logError(Error, "Unknown Skin (%08x)", skin);
    return;
  }

  SharableRotateSkin* ss = (SharableRotateSkin*)asset->asset;
  ss->release(skin);
  m_assetToAssetMap.erase(skin);

  if (ss->references() == 0)
  {
    delete ss;
    asset->asset = 0;
  }
}


Font* AssetManager::getFont(string assetName)
{
  error << "tried to use old asset manager for " << assetName << endl;
  if (!isAssetLoaded(assetName))
  {
    load2(assetName);
  }

  map<string, Asset*>::iterator pair;
  pair = m_assetMap.find(assetName);
  if (pair != m_assetMap.end())
  {
    Asset* asset = pair->second;
    if (asset != 0)
    {
      asset->used = true;
      ASSET_TYPE_ASSERT(asset, FONT1);
      return (Font*)(asset->asset);
    }
  }
  logError(Error, "Tried to get Font (%s) but it was never loaded or there was a problem", assetName.c_str());
  return 0;
}

HTexture AssetManager::getTexture(string assetName)
{
  error << "tried to use old asset manager for " << assetName << endl;
  if (!isAssetLoaded(assetName))
  {
    load2(assetName);
  }

  map<string, Asset*>::iterator pair;
  pair = m_assetMap.find(assetName);
  if (pair != m_assetMap.end())
  {
    Asset* asset = pair->second;
    if (asset != 0)
    {
      asset->used = true;
      ASSET_TYPE_ASSERT(asset, TEXTURE);
      return (HTexture)(asset->asset);
    }
  }
  logError(Error, "Tried to get Texture (%s) but it was never loaded or there was a problem", assetName.c_str());
  return 0;
}

string AssetManager::getText(string assetName)
{
  error << "tried to use old asset manager for " << assetName << endl;
  if (!isAssetLoaded(assetName))
  {
    load2(assetName);
  }

  map<string, Asset*>::iterator pair;
  pair = m_assetMap.find(assetName);
  if (pair != m_assetMap.end())
  {
    Asset* asset = pair->second;
    if (asset != 0)
    {
      asset->used = true;
      ASSET_TYPE_ASSERT(asset, TEXT);
      return *((string*)(asset->asset));
    }
  }
  logError(Error, "Tried to get Text (%s) but it was never loaded or there was a problem", assetName.c_str());
  return "";
}

int AssetManager::getIntAttribute(string name, string attribute)
{
  return m_ini->getInt(name, attribute);
}

float AssetManager::getFloatAttribute(string name, string attribute)
{
  return m_ini->getFloat(name, attribute);
}

string AssetManager::getStringAttribute(string name, string attribute)
{
  return (*m_ini)[name][attribute];
}

Point AssetManager::getPointAttribute(string name, string attribute)
{
  StringTokenizer st((*m_ini)[name][attribute], ", ");
  Point ret(-1, -1);
  if (st.countTokens())
  {
    ret.x = atoi(st.nextToken());
  }
  if (st.countTokens())
  {
    ret.y = atoi(st.nextToken());
  }
  return ret;
}

Rect AssetManager::getRectAttribute(string name, string attribute)
{
  StringTokenizer st((*m_ini)[name][attribute], ", ");
  Rect ret(-1, -1, -1, -1);
  if(st.countTokens())
  {
    ret.x = atoi(st.nextToken());
  }
  if(st.countTokens())
  {
    ret.y = atoi(st.nextToken());
  }
  if(st.countTokens())
  {
    ret.w = atoi(st.nextToken());
  }
  if(st.countTokens())
  {
    ret.h = atoi(st.nextToken());
  }
  return ret;
}
