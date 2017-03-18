#pragma warning (disable:4786 4530 4503)
#ifndef RealSDLDisplay_h
#define RealSDLDisplay_h


#include "SDL.h"
#include <list>
#include <map>

#include "Log.h"
#include "Misc/2dVector.h"

using namespace std;

typedef unsigned int HTexture;

extern map<HTexture, void*> textureMap;
extern HTexture nextTextureId;

HTexture loadTexture(const char* filename);
SDL_Surface* loadSDLSurface(const char* filename);
SDL_Surface* createSDLSurface(int w, int h, SDL_Surface* inspiration);


class TextureInfo
{
public:
  TextureInfo(int w, int h): w(w), h(h) { }
  int w;
  int h;
};

class TextureCacheEntry
{
public:
  TextureCacheEntry(HTexture id): id(id), references(0) {}
  HTexture id;
  int references;
};


enum DisplayType
{
  UNDEFTYPE,
  SDL,
  OPENGL,
  D3D
};

class Display
{
public:
  Display(int width, int height, int bpp, Uint32 flags);

  virtual ~Display();
  void clear();
  void flip();
  void blit(HTexture textureId, int destX, int destY);

  SDL_Surface* getSDLSurface() { return m_surface; }

  bool setWindowed(bool w);
  bool isWindowed() { return (m_surface->flags & SDL_FULLSCREEN) != SDL_FULLSCREEN; }

  void setClipRect(int x, int y, int w, int h)
  {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;

    SDL_SetClipRect(m_surface, &r);
  }

  void pushClipRect(Rect& clipRect)
  {
    m_clipRects.push_back(clipRect);
    setClipRect(clipRect.x, clipRect.y, clipRect.w, clipRect.h);
  }

  void popClipRect()
  {
    m_clipRects.pop_back();
    Rect clipRect = m_clipRects.back();
    setClipRect(clipRect.x, clipRect.y, clipRect.w, clipRect.h);
  }
    
  Rect getClipRect()
  {
    return m_clipRects.back();
  }

  
  void setDrawOffsetAmount(int dx, int dy) {setDrawOffsetAmount(Vector(dx, dy)); }
  void setDrawOffsetAmount(Vector o) { m_drawOffset = o; }
  Vector getDrawOffsetAmount() { return m_drawOffset; }

  
  // drawing primitives //////
  void drawVLine(int x, int y, int h, int red, int green, int blue, int alpha = 255);
  void drawHLine(int x, int w, int y, int red, int green, int blue, int alpha = 255);
  void fillRect(int x, int y, int w, int h, int red, int green, int blue, int alpha = 255);
  ////////////////////////////

  void drawLine(int x1, int y1, int x2, int y2, int red, int green, int blue, int alpha = 255);


  SDL_Surface* createSDLSurface(int w, int h);
  
  void isValid(bool b) { m_isValid = b; }
  bool isValid() { return m_isValid; }

  static Display* create(int width, int height, int bpp = 0, DisplayType type = SDL, Uint32 flags = 0);

  static Display* getInstance() { return instance; }

  const TextureInfo* getTextureInfo(HTexture id)
  {
    TextureInfo* ret = 0;
    map<HTexture, TextureInfo*>::iterator pair;
    pair = m_textureInfo.find(id);
    if (pair != m_textureInfo.end())
    {
      ret = pair->second;
    }
    return ret;
  }

  int getWidth() { return m_width; }
  int getHeight() { return m_height; }
  Uint32 getFlags() { return m_flags; }
  int getBpp() { return m_bpp; }


  int getTextureCount(){
    return m_textureInfo.size();
  }

  void screenshot(string fn);

  HTexture acquire(string filename);
  HTexture prepare(SDL_Surface* surface);
  void release(HTexture id);

  void report();
  void reportTextureInfo();

protected:
  void sanityCheck();
  HTexture loadTexture(const char* filename);
  HTexture loadTexture(SDL_Surface* surface);
  void freeTexture(HTexture textureId);

  void setDimensions(int w, int h)
  {
    m_width = w;
    m_height = h;
  }

  
  void addTextureInfo(HTexture id, TextureInfo* ti) { m_textureInfo[id] = ti; }
  void removeTextureInfo(HTexture id) { m_textureInfo.erase(id); }
  
  SDL_Surface* m_surface;

  map<string, TextureCacheEntry*> m_imageCache;
  map<HTexture, string> m_filenameMap; 
  map<HTexture, TextureInfo*> m_textureInfo;
  
private:
  int m_width;
  int m_height;
  Uint32 m_flags;
  int m_bpp;

  Vector m_drawOffset;

  static Display* instance;

  list<Rect> m_clipRects;

  bool m_isValid;

  bool isDoubleBuffered() { return m_dblBuf != m_surface; }
private:
  SDL_Surface* m_dblBuf;
  Uint32 m_colorKey;

  
};

inline SDL_Surface* createSDLSurface(int w, int h)
{
  return Display::getInstance()->createSDLSurface(w, h);
}



#endif