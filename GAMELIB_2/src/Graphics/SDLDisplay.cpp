#pragma warning (disable : 4786 4530 4503)
#include "SDLDisplay.h"

#include "SDL_gfxPrimitives.h"
#include "SDL_rotozoom.h"

#include <iostream>
using namespace std;


SDLDisplay::SDLDisplay(int width, int height, int bpp, Uint32 flags):
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
  logError(Inform, "SDLDisplay created.");
}

SDLDisplay::~SDLDisplay()
{
  logError(Inform, "Tearing down SDLDisplay");
  map<HTexture, void*>::iterator pair;
  while(textureMap.size())
  {
    pair = textureMap.begin();
    freeTexture(pair->first);
  }
}

bool SDLDisplay::setWindowed(bool w)
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

void SDLDisplay::clear()
{
  static SDL_Rect r;
  r.x=0;
  r.y=0;
  r.w=m_dblBuf->w;
  r.h=m_dblBuf->h;

  SDL_FillRect(m_dblBuf, &r, SDL_MapRGBA(m_dblBuf->format, 0x00, 0x00, 0x00, 0xff));
}
void SDLDisplay::flip()
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

void SDLDisplay::blit(HTexture textureId, int destX, int destY)
{

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

int stretchBlit(SDL_Surface * src, SDL_Surface * dst, SDL_Rect* dstr);

void SDLDisplay::stretchBlit(HTexture textureId, Rect& dest)
{
  if (dest.w == 0 && dest.h == 0)
  {
    return;
  }
  SDL_Surface* toBeBlitted = (SDL_Surface*)textureId;
  if (toBeBlitted->w == dest.w && toBeBlitted->h == dest.h)
  {
    // same size, no need to stretch/shrink
    blit(textureId, dest.x, dest.y);
  }
  else
  {
//    ::stretchBlit(toBeBlitted, m_dblBuf, dest);
    float xscale = (float)dest.w/(float)toBeBlitted->w;
    float yscale = (float)dest.h/(float)toBeBlitted->h;
    
    SDL_Surface* stretched = zoomSurface(toBeBlitted, xscale, yscale, 0);
    
    static SDL_Rect sr;
    sr.x=0;
    sr.y=0;
    sr.w=stretched->w;
    sr.h=stretched->h;
    
    SDL_BlitSurface(stretched, &sr, m_dblBuf, dest);
    SDL_FreeSurface(stretched);
  }
}

HTexture SDLDisplay::loadTexture(const char* filename)
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

HTexture SDLDisplay::loadTexture(SDL_Surface* img)
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


void SDLDisplay::freeTexture(HTexture textureId)
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

void SDLDisplay::drawVLine(int x, int y, int h, int red, int green, int blue, int alpha)
{
  Vector v = getDrawOffsetAmount();
  x+=v.x;
  y+=v.y;
  vlineRGBA(m_dblBuf, x, y, y+h, red, green, blue, alpha);
}

void SDLDisplay::drawLine(int x1, int y1, int x2, int y2, int red, int green, int blue, int alpha)
{
  lineRGBA(m_dblBuf, x1, y1, x2, y2, red, green, blue, alpha);
}

void SDLDisplay::drawHLine(int x, int w, int y, int red, int green, int blue, int alpha)
{
  Vector v = getDrawOffsetAmount();
  x+=v.x;
  y+=v.y;
  hlineRGBA(m_dblBuf, x, x+w, y, red, green, blue, alpha);
}
void SDLDisplay::fillRect(int x, int y, int w, int h, int red, int green, int blue, int alpha)
{
  Vector v = getDrawOffsetAmount();
  x+=v.x;
  y+=v.y;
  
  boxRGBA(m_dblBuf, x, y, x+(w), y+(h), red, green, blue, alpha);
}

void SDLDisplay::reportTextureInfo()
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

int stretchBlit(SDL_Surface * src, SDL_Surface * dst, SDL_Rect* dstr)
{
  int x, y, sx, sy, *sax, *say, *csax, *csay, csx, csy, ex, ey, t1, t2, sstep;
  tColorRGBA *c00, *c01, *c10, *c11;
  tColorRGBA *sp, *csp, *dp;
  int sgap, dgap;
  
  /*
  * Variable setup 
  */
  sx = (int) (65536.0 * (float) src->w / (float) dstr->w);
  sy = (int) (65536.0 * (float) src->h / (float) dstr->h);
  
  /*
  * Allocate memory for row increments 
  */
  if ((sax = (int *) malloc((dst->w + 1) * sizeof(Uint32))) == NULL) {
    return (-1);
  }
  if ((say = (int *) malloc((dst->h + 1) * sizeof(Uint32))) == NULL) {
    free(sax);
    return (-1);
  }
  
  /*
  * Precalculate row increments 
  */
  csx = 0;
  csax = sax;
  for (x = 0; x <= dstr->w; x++) {
    *csax = csx;
    csax++;
    csx &= 0xffff;
    csx += sx;
  }
  csy = 0;
  csay = say;
  for (y = 0; y <= dstr->h; y++) {
    *csay = csy;
    csay++;
    csy &= 0xffff;
    csy += sy;
  }
  
  /*
  * Pointer setup 
  */
  sp = csp = (tColorRGBA *) src->pixels;
  dp = (tColorRGBA *) dst->pixels;
  sgap = src->pitch - src->w * 4;
  dgap = dst->pitch - dst->w * 4;
  
/*
  * Non-Interpolating Zoom 
  */
  
  csay = say;
  for (y = 0; y < dstr->h; y++) 
  {
    int offset = ((dstr->y + y) * dst->pitch)+(dstr->x*4);
    dp = (tColorRGBA*)(((char*)dst->pixels) + offset);
    sp = csp;
    csax = sax;
    for (x = 0; x < dstr->w; x++) {
    /*
    * Draw 
      */
      *dp = *sp;
      /*
      * Advance source pointers 
      */
      csax++;
      sp += (*csax >> 16);
      /*
      * Advance destination pointer 
      */
      dp++;
    }
    /*
    * Advance source pointer 
    */
    csay++;
    csp = (tColorRGBA *) ((Uint8 *) csp + (*csay >> 16) * src->pitch);
    /*
    * Advance destination pointers 
    */
    dp = (tColorRGBA *) ((Uint8 *) dp + dgap);
  }
  
  /*
  * Remove temp arrays 
  */
  free(sax);
  free(say);
  
  return (0);
}
