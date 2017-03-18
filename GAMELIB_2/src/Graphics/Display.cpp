#pragma warning (disable : 4786 4530 4503)
#include "Display.h"
#include "SDLDisplay.h"
#include "OpenGLDisplay.h"
#include "SDL_image.h"
#include "FileManager.h"
#include "StdString.h"
#include "Log.h"
#include <iostream>
#include "SDL_rotozoom.h"
#include <string>
#include "StringTokenizer.h"

Display* theScreen;

Display* Display::instance = 0;

map<HTexture, void*> textureMap;
HTexture nextTextureId = 1;

// OpenGL will use ptr to GLTexture
// SDL will use ptr to SDL_Surface

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

  switch(type)
  {
  case OPENGL:
    {
      ret = new OpenGLDisplay(width, height, bpp, flags);
    }
    break;
  case SDL:
    {
      ret = new SDLDisplay(width, height, bpp, flags);
    }
    break;
  case D3D:
    {
      //ret = new D3DDisplay(width, height, bpp, flags);
      lassert(false);
    }
    break;
  default:
    lassert(false);
    break;
  }
  if (ret)
  {
    ret->m_type = type;
    ret->m_width = width;
    ret->m_height = height;
    ret->m_flags = flags;
    ret->m_bpp = bpp;
  }

  instance = ret;
  return ret;
}

Display::~Display()
{
  if (m_imageCache.size() > 0)
  {
    logError(Error, "not all textures released");
    map<string, TextureCacheEntry*>::iterator pair;
    for (pair = m_imageCache.begin(); pair!=m_imageCache.end(); pair++)
    {
      logError(Error, "++++ %s", pair->first.c_str());
    }
  }
  instance = 0;
}

SDL_Surface* loadSDLSurface(string filename)
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

  Uint32 colorKey = SDL_MapRGB(ret->format, 0xf0, 0x00, 0xf0);
  SDL_SetColorKey(ret, SDL_SRCCOLORKEY |SDL_RLEACCEL, colorKey);

  return ret;
}

SDL_Surface* loadSDLSurfaceResize(string filename, int w, int h)
{
  SDL_Surface* img = loadSDLSurface(filename);
  double xscale = (double)w/img->w;
  double yscale = (double)h/img->h;
  SDL_Surface* zoomed = zoomSurface(img, xscale, yscale, 0);
  SDL_FreeSurface(img);
  return zoomed;
}

extern "C" int pygame_AlphaBlit (SDL_Surface *src, SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect);


void br_blit(SDL_Surface* src, SDL_Rect sr, SDL_Surface* dst)
{
  SDL_Rect dr;
  dr.x = 0;
  dr.y = 0;
  dr.w = sr.w;
  dr.h = sr.h;
  pygame_AlphaBlit(src, &sr, dst, &dr);
//  // assume start at top left
//  int numPixelsOnLine = sr.w;
//  int bytesToMove = numPixelsOnLine * 4;
//  unsigned char* srcPixels = static_cast<unsigned char*>(src->pixels);
//  unsigned char* dstPixels = static_cast<unsigned char*>(dst->pixels);
//
//  for (int y=0; y<sr.h; y++)
//  {
//    unsigned char* destP = &dstPixels[y*bytesToMove];
//    unsigned char* srcP = &srcPixels[((sr.y+y)*src->w*4)+sr.x*4];
//    memcpy(destP, srcP, bytesToMove);
//  }
}



SDL_Surface* Display::createSDLSurface(int w, int h, SDL_Surface* inspiration)
{
  if (inspiration == 0)
  {
    inspiration = m_surface;
  }
  Uint32 rmask, gmask, bmask, amask = 0;
  
  rmask = inspiration->format->Rmask;
  gmask = inspiration->format->Gmask;
  bmask = inspiration->format->Bmask;
  amask = inspiration->format->Amask;


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

HTexture Display::prepare(SDL_Surface* surface, string name)
{
  static int count = 0;
  TextureCacheEntry* tce = 0;
  HTexture ret = 0;

  lassert2(surface != 0, "null surface?");
  CStdString s;
  if (name == "")
  {
    count++;
    s.Format("Prepared%03d", count);
  }
  else
  {
    s = name;
  }

  map<string, TextureCacheEntry*>::iterator pair;
  pair=m_imageCache.find(s);
  if ( pair == m_imageCache.end())
  {
    ret = loadTexture(surface);
    tce = new TextureCacheEntry(ret);
    m_imageCache[s] = tce;
    m_filenameMap[ret] = s;
  }
  else
  {
    tce = pair->second;
    ret = tce->id;
  }
  tce->references++;

  return ret;
}

HTexture Display::acquire(string filename)
{
  debug << "Display::acquire:" << filename << endl;
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
    lassert2(pair != m_imageCache.end(), filename.c_str());
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

void Display::purge()
{
  map<string, TextureCacheEntry*>::iterator pair;
  map<string, TextureCacheEntry*> copy(m_imageCache);

  for (pair=copy.begin(); pair!=copy.end(); pair++)
  {
    TextureCacheEntry* tce = pair->second;
    if (tce->references == 0)
    {
      freeTexture(tce->id);
      m_filenameMap.erase(tce->id);
      m_imageCache.erase(pair->first);
      printf("- %d\n", m_filenameMap.size());
    }
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

void parseColor(string color, int& red, int& green, int& blue, int &alpha)
{
  red = green = blue = alpha = 0;
  StringTokenizer st(color.c_str(), ", ");
  if (st.countTokens() > 0)
  {
    red = atoi(st.nextToken().c_str());
  }

  if (st.countTokens() > 0)
  {
    green = atoi(st.nextToken().c_str());
  }

  if (st.countTokens() > 0)
  {
    blue = atoi(st.nextToken().c_str());
  }

  if (st.countTokens() > 0)
  {
    alpha = atoi(st.nextToken().c_str());
  }
  else
  {
    alpha = 255;
  }
}

/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}


/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

SDL_Surface* rot90(SDL_Surface* src)
{
  SDL_Surface* dst = createSDLSurface(src->h, src->w);
  if ( SDL_MUSTLOCK(src) ) 
  {
        SDL_LockSurface(src);
  }
  if ( SDL_MUSTLOCK(dst) ) 
  {
        SDL_LockSurface(dst);
  }

  int sy, sx, dy, dx;
  for (sy=0, dx=(src->h-1); sy<src->h; sy++, dx--)
  {
    for (sx=0, dy=0; sx<src->w; sx++, dy++)
    {
      if (sx >= src->w || sy >= src->h || dx >= dst->w || dy >= dst->h)
      {
        __asm int 3 ;
      }
      if (sx < 0 || sy < 0 || dx < 0 || dy < 0)
      {
        __asm int 3 ;
      }

      Uint32 c=getpixel(src, sx, sy);
      putpixel(dst, dx, dy, c);
    }
  }

  if ( SDL_MUSTLOCK(src) ) 
  {
        SDL_UnlockSurface(src);
  }
  if ( SDL_MUSTLOCK(dst) ) 
  {
        SDL_UnlockSurface(dst);
  }
  return dst;
}      
