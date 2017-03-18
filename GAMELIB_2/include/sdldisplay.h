#ifndef SDLDisplay_h
#define SDLDisplay_h

#include "Display.h"

class SDLDisplay: public Display
{
public:
  SDLDisplay(int width, int height, int bpp, Uint32 flags);
  ~SDLDisplay();
  virtual void clear();
  virtual void flip();

  virtual SDL_Surface* getSDLSurface() { return m_dblBuf; }

  virtual void blit(HTexture textureId, int destX, int destY);
  virtual void stretchBlit(HTexture textureId, Rect& dest);
  virtual void setClipRectPeer(int x, int y, int w, int h)
  {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;

    SDL_SetClipRect(m_surface, &r);
  }

  virtual bool setWindowed(bool w);
  virtual bool isWindowed() { return (m_surface->flags & SDL_FULLSCREEN) != SDL_FULLSCREEN; }
  // drawing primitives //////
  virtual void drawVLine(int x, int y, int h, int red, int green, int blue, int alpha = 255);
  virtual void drawHLine(int x, int w, int y, int red, int green, int blue, int alpha = 255);
  virtual void fillRect(int x, int y, int w, int h, int red, int green, int blue, int alpha = 255);
  ////////////////////////////

  virtual void drawLine(int x1, int y1, int x2, int y2, int red, int green, int blue, int alpha = 255);

  virtual void reportTextureInfo();

protected:
  virtual HTexture loadTexture(const char* filename);
  virtual HTexture loadTexture(SDL_Surface* surface);
  virtual void freeTexture(HTexture textureId);

  bool isDoubleBuffered() { return m_dblBuf != m_surface; }
private:
  SDL_Surface* m_dblBuf;
  Uint32 m_colorKey;
};


#endif
