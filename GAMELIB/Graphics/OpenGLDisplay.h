#ifndef OpenGLDisplay_h
#define OpenGLDisplay_h

#include "Display.h"

#include "Misc/GameMath.h"
#include "SDL.h"

#include "ObjectCache.h"

#include <windows.h>
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library


#include <list>
using namespace std;

enum GLPrimitive
{
  CLIP_RECT,
  TEXTURE
};

struct ToBeDrawn
{
  GLPrimitive type; // clip, texture
  int id;
  int x1, y1;
  int x2, y2;
};

//class GLElement
//{
//public:
//  virtual void draw() = 0;
//};
//
//class GLTextureElement: public GLElement
//{
//public:
//  virtual void draw();
//  void drawQuad(int x1, int y1, int x2, int y2);
//  int x;
//  int y;
//  HTexture texture;
//};
//
//
//class GLColorElement: public GLElement
//{
//public:
//  virtual void draw();
//  Rect screen;
//  int x;
//  int y;
//  int w;
//  int h;
//  int red;
//  int green;
//  int blue;
//  int alpha;
//};
//
//class GLLineElement: public GLElement
//{
//public:
//  virtual void draw();
//  int x1;
//  int y1;
//  int x2;
//  int y2;
//  int red, green, blue;
//};
//
//class GLClipRect: public GLElement
//{
//public:
//  virtual void draw();
//  int x;
//  int y;
//  int w;
//  int h;
//};

class OpenGLDisplay: public Display
{
public:
  OpenGLDisplay(int width, int height, int bpp, Uint32 flags);
  virtual void clear();
  virtual void flip();
  virtual void blit(HTexture textureId, int destX, int destY);

  virtual void setClipRectPeer(int x, int y, int w, int h);

  static int maxTextureSize;

  // drawing primitives //////
  virtual void drawVLine(int x, int y, int h, int red, int green, int blue, int alpha = 255);
  virtual void drawHLine(int x, int w, int y, int red, int green, int blue, int alpha = 255);
  virtual void fillRect(int x, int y, int w, int h, int red, int green, int blue, int alpha = 255);
  ////////////////////////////

  virtual void drawLine(int x1, int y1, int x2, int y2, int red, int green, int blue, int alpha = 255);

  FPoint translate(float x, float y)
  {
    static Display* display=0;
    if (display == 0)
    {
      display = Display::getInstance();
    }
    FPoint ret;
    ret.x = (((x/display->getWidth())*2) - 1);
    ret.y = -(((y/display->getHeight())*1.5) - .75);
    return ret;
  }


protected:
  virtual HTexture loadTexture(const char* filename);
  virtual HTexture loadTexture(const void* pixels, int width, int height)
  {
    return loadTexture(pixels, width, height, width, height);
  }

  virtual HTexture loadTexture(SDL_Surface* surface);

  virtual void freeTexture(HTexture textureId);

  HTexture loadTexture(const void* pixels, int width, int height, int realW, int realH);

  unsigned int setTexture(const void* pixels, int width, int height);

  Uint8* copyBits(const Uint8* src, int sWidth, int sx, int sy, int w, int h);
  Uint8* copyBitsWithBorder(const Uint8* src, int sWidth, int sx, int sy, int w, int h);

  void scissor(int id, int x1, int y1, int x2, int y2);
  void drawQuad(int id, int x1, int y1, int x2, int y2);
private:
//  GLElement m_toBeDrawn[2048];
  ToBeDrawn m_toBeDrawn[2048];
//  list<GLElement*> m_toBeDrawn;
  int m_numberToDraw;
//  ObjectCache<GLElement, HasReclaim> m_elementCache;
};

class GLSubTexture
{
public:
  int x;
  int y;
  int w;
  int h;
  unsigned int glId;
};

class GLTexture: public list<GLSubTexture>
{
public:
  GLTexture(int w, int h): m_width(w), m_height(h) { }
//  list<GLSubTexture> m_glTextureId;
  int m_width;
  int m_height;
};


#endif
