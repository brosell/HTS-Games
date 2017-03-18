#pragma warning (disable:4786 4530 4503)
#include "RealSDLDisplay.h"

#include "SDL_gfxPrimitives.h"
//#include "audio/SoundMixer.h"

#include "SDL_image.h"
#include "FileManager.h"
#include "StdString.h"
#include "Log.h"
#include <iostream>
#include <string>

#include <iostream>
using namespace std;

Display* theScreen;

Display* Display::instance = 0;

map<HTexture, void*> textureMap;
HTexture nextTextureId = 1;

Display* Display::create(int width, int height, int bpp, DisplayType type, Uint32 flags)
{

  const SDL_VideoInfo* vi;
  vi = SDL_GetVideoInfo();
  logError(Inform, "HW Available: %d", vi->hw_available);
  logError(Inform, "Accelerated HW->HW Blits: %d", vi->blit_hw);
  logError(Inform, "Accelerated HW->HW Colorkey Blits: %d", vi->blit_hw_CC);
  logError(Inform, "Accelerated HW->HW ALPHA Blits: %d", vi->blit_hw_A);
  logError(Inform, "Accelerated SW->HW Blits: %d", vi->blit_sw);
  logError(Inform, "Accelerated SW->HW Colorkey Blits: %d", vi->blit_sw_CC);
  logError(Inform, "Accelerated SW->HW ALPHA Blits: %d", vi->blit_sw_A);
  logError(Inform, "Accelerated Fills :%d", vi->blit_fill);

  
  Display* ret = 0;

  ret = new Display(width, height, bpp, flags);

  if (ret)
  {
    ret->m_width = width;
    ret->m_height = height;
    ret->m_flags = flags;
    ret->m_bpp = bpp;
  }

  instance = ret;
  return ret;
}


Display::Display(int width, int height, int bpp, Uint32 flags):
m_colorKey(0)
{
//  flags -= SDL_DOUBLEBUF; // uncomment for FAST FAST FAST drawing
  lassert( (flags & SDL_OPENGL) == 0);
  
  m_surface = SDL_SetVideoMode(width, height, bpp, flags);
  
  if(!m_surface)
  {
    logError(Error, "Failed to initialize Video");
    isValid(false);
    return;
  }
  isValid(true);

  logError(Inform, "Screen is %s surface", (char*)((m_surface->flags%2)==1?"HW":"SW"));

  m_dblBuf = m_surface;
  if ((m_surface->flags%2)==1)
  {
    // hardware surface... map a back buffer
    m_dblBuf = createSDLSurface(width, height);
  }
  

  logError(Inform, "Rmask %08x", m_dblBuf->format->Rmask);
  logError(Inform, "Gmask %08x", m_dblBuf->format->Gmask);
  logError(Inform, "Bmask %08x", m_dblBuf->format->Bmask);
  logError(Inform, "Amask %08x", m_dblBuf->format->Amask);

  m_colorKey = SDL_MapRGB(m_surface->format, 0xf0, 0x00, 0xf0);
//  SDL_SetColorKey(m_surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, m_colorKey);

  pushClipRect(Rect(0, 0, width, height));
  logError(Inform, "Display created.");
}

Display::~Display()
{
  logError(Inform, "Tearing down Display");
  map<HTexture, void*>::iterator pair;
  while(textureMap.size())
  {
    pair = textureMap.begin();
    freeTexture(pair->first);
  }

  if (m_imageCache.size() > 0)
  {
    logError(Error, "not all textures released");
    map<string, TextureCacheEntry*>::iterator pair;
    for (pair = m_imageCache.begin(); pair!=m_imageCache.end(); pair++)
    {
      logError(Error, "++++ %s", pair->first.c_str());
    }
  }
}

bool Display::setWindowed(bool w)
{
  /* 
  unset display mode
    set using same parameters
    convert all loaded textures to new format
*/
  // unset
  if (m_dblBuf != m_surface)
  {
    // we have a back buffer... free it
    SDL_FreeSurface(m_dblBuf);
    m_dblBuf = 0;
  }

  SDL_QuitSubSystem(SDL_INIT_VIDEO);
  m_surface = 0;

  // reset
  SDL_InitSubSystem(SDL_INIT_VIDEO);
  Uint32 flags = getFlags();
  if (flags & SDL_FULLSCREEN) flags-=SDL_FULLSCREEN;

  if (!w)
  {
    flags |= SDL_FULLSCREEN;
  }

  m_surface = SDL_SetVideoMode(getWidth(), getHeight(), getBpp(), flags);

  if (!m_surface)
  {
    logError(Error, "Unable to set video mode. Expect to die soon.");
    return false;
  }
  m_colorKey = SDL_MapRGB(m_surface->format, 0xf0, 0x00, 0xf0);

  if (m_surface->flags & SDL_HWSURFACE)
  {
    // hardware surface... map a back buffer
    m_dblBuf = createSDLSurface(getWidth(), getHeight());
  }
  else
  {
    m_dblBuf = m_surface;
  }

  SDL_ShowCursor(false);
//  SoundMixer::bounce();
  
  // FIXME: now convert all the loaded textures to the new format
  return true;
}

void Display::clear()
{
  static SDL_Rect r;
  r.x=0;
  r.y=0;
  r.w=m_dblBuf->w;
  r.h=m_dblBuf->h;

  SDL_FillRect(m_dblBuf, &r, SDL_MapRGBA(m_dblBuf->format, 0x00, 0x00, 0x00, 0xff));
}
void Display::flip()
{
  static SDL_Rect sr;
  static SDL_Rect dest;
  
  if (m_dblBuf != m_surface)
  {
    sr.x=0;
    sr.y=0;
    sr.w=m_dblBuf->w;
    sr.h=m_dblBuf->h;
    
    
    dest.x=0;
    dest.y=0;
    SDL_BlitSurface(m_dblBuf, &sr, m_surface, &dest);
  }
  
  SDL_Flip(m_surface);
}

void Display::blit(HTexture textureId, int destX, int destY)
{
//  void* vp = textureMap[textureId];
//  if (vp == 0)
//  {
//    lassert2(false, "null SDL_Surface");
//    return;
//  }

  SDL_Surface* toBeBlitted = (SDL_Surface*)textureId;
  
  static SDL_Rect sr;
  sr.x=0;
  sr.y=0;
  sr.w=toBeBlitted->w;
  sr.h=toBeBlitted->h;

  static SDL_Rect dest;
  dest.x=destX + getDrawOffsetAmount().x;
  dest.y=destY + getDrawOffsetAmount().y;
  SDL_BlitSurface(toBeBlitted, &sr, m_dblBuf, &dest);
}

HTexture Display::loadTexture(const char* filename)
{
  SDL_Surface* img=loadSDLSurface(filename);

  if (!img)
  {
    logError(Error, "Failed to load \"%s\"", filename);
    lassert(false);
    return 0;
  }

  HTexture ret = loadTexture(img);
  
  SDL_FreeSurface(img);
  
  return ret;
}

HTexture Display::loadTexture(SDL_Surface* img)
{
  int id =0;
  SDL_Surface* convImg = 0;
  
  if (isDoubleBuffered())
  {
    convImg = SDL_ConvertSurface(img, img->format, SDL_SWSURFACE);
  }
  else
  {
    convImg = SDL_ConvertSurface(img, img->format, SDL_HWSURFACE);
  }

  if (convImg != 0)
  {
    //SDL_SetColorKey(convImg, SDL_SRCCOLORKEY |SDL_RLEACCEL, m_colorKey);
    id = (int)convImg; //nextTextureId++;
    textureMap[id] = (void*)convImg;
    addTextureInfo(id, new TextureInfo(convImg->w, convImg->h));
  }
  else
  {
    logError(Error, "Could not set color key on surface");
  }
  
  return id;
}


void Display::freeTexture(HTexture textureId)
{
  // only Free_surface since all the cache work has been done
  SDL_Surface* surface = (SDL_Surface*)textureMap[textureId];
  lassert(surface != 0);

  SDL_FreeSurface(surface);
  textureMap.erase(textureId);

  TextureInfo* ti = (TextureInfo*)getTextureInfo(textureId);
  if (ti)
  {
    delete ti;
    removeTextureInfo(textureId);
  }
  else
  {
    logError(Error, "Trying to free texture but TextureInfo for textureId %d is null", textureId);
  }
}

void Display::drawVLine(int x, int y, int h, int red, int green, int blue, int alpha)
{
  Vector v = getDrawOffsetAmount();
  x+=v.x;
  y+=v.y;
  vlineRGBA(m_dblBuf, x, y, y+h, red, green, blue, alpha);
}

void Display::drawLine(int x1, int y1, int x2, int y2, int red, int green, int blue, int alpha)
{
  lineRGBA(m_dblBuf, x1, y1, x2, y2, red, green, blue, alpha);
}

void Display::drawHLine(int x, int w, int y, int red, int green, int blue, int alpha)
{
  Vector v = getDrawOffsetAmount();
  x+=v.x;
  y+=v.y;
  hlineRGBA(m_dblBuf, x, x+w, y, red, green, blue, alpha);
}
void Display::fillRect(int x, int y, int w, int h, int red, int green, int blue, int alpha)
{
  Vector v = getDrawOffsetAmount();
  x+=v.x;
  y+=v.y;
  
  boxRGBA(m_dblBuf, x, y, x+w, y+h, red, green, blue, alpha);
}

void Display::reportTextureInfo()
{
  map<HTexture, string>::iterator pair;
  for (pair=m_filenameMap.begin(); pair!=m_filenameMap.end(); pair++)
  {
    SDL_Surface* surface = (SDL_Surface*)textureMap[pair->first];
    logError(Inform, "Texture %8d (%3dx%3d) %s",
      surface,
      surface->w,
      surface->h,
      (char*)((surface->flags&SDL_HWSURFACE)==SDL_HWSURFACE)?"HW":"SW");
  }
}

SDL_Surface* loadSDLSurface(const char* filename)
{
  SDL_RWops* rw;
  void* buffer;
  int size = loadFileToMemory(filename, &buffer);
  if (size <= 0)
  {
    return 0;
  }

  rw = SDL_RWFromMem(buffer, size);
  
  SDL_Surface* ret = IMG_Load_RW(rw, 0);
  SDL_FreeRW(rw);
  free(buffer);


  return ret;
}

SDL_Surface* Display::createSDLSurface(int w, int h)
//SDL_Surface* createSDLSurface(int w, int h, SDL_Surface* inspiration)
{
  SDL_Surface* inspiration = m_surface;
  Uint32 rmask, gmask, bmask, amask = 0;
  
  /* SDL interprets each pixel as a 32-bit number, so our masks must depend
  on the endianness (byte order) of the machine */
  if (!inspiration)
  {
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
        amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
        amask = 0xff000000;
#endif
  }
  else
  {
    rmask = inspiration->format->Rmask;
    gmask = inspiration->format->Gmask;
    bmask = inspiration->format->Bmask;
    amask = inspiration->format->Amask;
  }



  SDL_Surface* surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
    rmask, gmask, bmask, amask);

  if (surface == 0)
  {
    logError("Failed to created SDL_Surface", Error);
    return 0;
  }

  Uint32 colorKey = SDL_MapRGB(surface->format, 0xf0, 0x00, 0xf0);
  SDL_SetColorKey(surface, SDL_SRCCOLORKEY |SDL_RLEACCEL, colorKey);
  
  return surface;
}



void Display::screenshot(string fn)
{
  int res = SDL_SaveBMP(m_surface, fn.c_str());
}

HTexture Display::prepare(SDL_Surface* surface)
{
  static int count = 0;
  lassert2(surface != 0, "null surface?");
  count++;
  CStdString s;
  s.Format("Prepared%03d", count);
  HTexture ret = loadTexture(surface);
  TextureCacheEntry* tce = new TextureCacheEntry(ret);
  tce->references++;
  m_imageCache[s] = tce;
  m_filenameMap[ret] = s;

  return ret;
}

HTexture Display::acquire(string filename)
{
  HTexture id = 0;
  TextureCacheEntry* tce = 0;
  map<string, TextureCacheEntry*>::iterator pair;
  pair=m_imageCache.find(filename);
  if ( pair == m_imageCache.end())
  {
    id = loadTexture(filename.c_str());
    tce = new TextureCacheEntry(id);
    m_imageCache[filename] = tce;
    m_filenameMap[id] = filename;
  }
  else
  {
    tce = pair->second;
  }
  tce->references++;

  return tce->id;

}

void Display::release(HTexture id)
{
  string filename = m_filenameMap[id];

  map<string, TextureCacheEntry*>::iterator pair;
  pair=m_imageCache.find(filename);
  
  if ( pair == m_imageCache.end())
  {
    lassert2(pair != m_imageCache.end(), "nothing to release?");
    return;
  }
  TextureCacheEntry* tce = pair->second;
  
  if (tce <=0 )
  {
    lassert2(tce > 0, "no refrences?");
    return;
  }
  
  tce->references--;

  if (tce->references == 0)
  {
    freeTexture(tce->id);
    m_imageCache.erase(filename);
    m_filenameMap.erase(tce->id);
    delete tce;
  }
}

void Display::sanityCheck()
{
  logError(Inform, "Perfroming sanity check on Display");
  map<string, TextureCacheEntry*>::iterator pair;
  for(pair=m_imageCache.begin(); pair!=m_imageCache.end(); pair++)
  {
    string filename = pair->first;
    TextureCacheEntry* tce = pair->second;
    lassert(m_filenameMap[tce->id] == filename);
    lassert(tce->references > 0);
  }
  logError(Inform, "Done");
}

void Display::report()
{
  sanityCheck();
  logError(Inform, "Dislpay Report");
  logError(Inform, "--------------");
  logError(Inform, "Loaded Textures: %d", m_imageCache.size());
  logError(Inform, "Loaded Filenames: %d", m_filenameMap.size());

  // count total references to textures
  int totalReferences = 0;
  TextureCacheEntry* mostReferences = 0;
  map<string, TextureCacheEntry*>::iterator pair;
  for(pair=m_imageCache.begin(); pair!=m_imageCache.end(); pair++)
  {
    totalReferences+=pair->second->references;
    if (mostReferences == 0 || pair->second->references > mostReferences->references)
    {
      mostReferences = pair->second;
    }
  }

  logError(Inform, "Total Texture References: %d", totalReferences);
  if (mostReferences != 0)
  {
    logError(Inform, "Greatest Number of references: %d for %s", 
      mostReferences->references, 
      m_filenameMap[mostReferences->id].c_str());
  }

  logError(Inform, "---------------");
}