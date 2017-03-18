#pragma warning (disable: 4503 4530 4786)
#include "BR_Game.h"
#include "OpenGLDisplay.h"
#include <iostream>
using namespace std;

#include "SDL_rotozoom.h"
#include "Utils.h"

map<int, int> numTexDrawn;

int OpenGLDisplay::maxTextureSize = 256;

/* OpenGL
1) texture width and heights must be powers of 2.
2) maximum size is 256X256
3) dimensions smaller that 256 will be scaled up 
  to the next power of 2. they will be shunk again 
  when they get drawn to the screen.
4) bigger images must be split into smaller ones.
5) maybe it makes sense to take all images and chop 
  them into pieces that are powers of two, not just 
  big ones... that way there is no stretching and 
  shrinking which may distort the texture badly...

6) Alpha- we can use the alpha channel (see old surface code)
7) Fake Alpha - using the colorkey of 0xf000f0. whenever we see
    that color in an image, we will set the alpha of that
    pixel to transparent
  */

void checkGLError(const char* file, int line);
#define CheckErr() checkGLError(__FILE__, __LINE__)

OpenGLDisplay::OpenGLDisplay(int width, int height, int bpp, Uint32 flags):
m_numberToDraw(0)
{
  flags |= SDL_OPENGL;

//  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 0 );

  m_surface = SDL_SetVideoMode(width, height, bpp, flags);
  if(!m_surface)
  {
    isValid(false);
    return;
  }
  isValid(true);


  glViewport(0, 0, width, height);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
  //glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// Reset The Projection Matrix

  float r = (GLfloat)width/(GLfloat)height;
  gluPerspective(45.0f, r, 0.1f, 100.0f);	// Calculate The Aspect Ratio Of The Window

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_SCISSOR_TEST);
  CheckErr();

  glTranslatef(0.0f, 0.0f, -2.81); //-1.81f);
  setDimensions(width, height);
  pushClipRect(Rect(0, 0, width, height));
}

void OpenGLDisplay::clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
}

void OpenGLDisplay::drawQuad(int id, int x1, int y1, int x2, int y2)
{
  static int lastId = 0;
  if (lastId != id)
  {
    lastId = id;
    glBindTexture(GL_TEXTURE_2D, id);
  }

  glEnable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  FPoint topLeft = translate(x1, y1);
  FPoint topRight = translate(x2, y1);
  FPoint bottomLeft = translate(x1, y2);
  FPoint bottomRight = translate(x2, y2);

  glTexCoord2f(0, 0);
  glVertex3f(bottomLeft.x, bottomLeft.y, 1.0f);

  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(bottomRight.x, bottomRight.y, 1.0f);

  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(topRight.x, topRight.y, 1.0f);
  
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(topLeft.x, topLeft.y, 1.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
}

void OpenGLDisplay::scissor(int id, int x1, int y1, int x2, int y2)
{
  // openGL Viewports are upside down (0,0) is lower left.
  glScissor(x1, getHeight()-(y1+y2), x2, y2);
}

void OpenGLDisplay::flip()
{
  SDL_GL_SwapBuffers();
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  
}

void OpenGLDisplay::blit(HTexture textureId, int destX, int destY)
{
//  lassert(textureId >= 0);



  list<GLSubTexture>::iterator i;

  GLTexture* tex = (GLTexture*)textureMap[textureId];

  if (tex == 0)
  {
    return;
  }

  int texX = destX;
  int texY = destY;

  for (i=tex->begin(); i!=tex->end(); i++)
  {
    GLSubTexture& subT = (*i);
    
    int finX = texX + subT.x;
    int finY = texY + subT.y;

    drawQuad(subT.glId, finX, finY, finX+subT.w, finY+subT.h);
  }
}

void OpenGLDisplay::setClipRectPeer(int x, int y, int w, int h)
{
  glScissor(x, getHeight()-(y+h), w, h);
}

SDL_Surface* adjustSize(SDL_Surface* orig, int w, int h)
{
  SDL_Surface* ret = createSDLSurface(w, h);
  if (ret != 0)
  {
    SDL_Rect sr;
    sr.x=0;
    sr.y=0;
    sr.w=orig->w;
    sr.h=orig->h;
    
    br_blit(orig, sr, ret);
  }
  return ret;
}

HTexture OpenGLDisplay::loadTexture(SDL_Surface* surface)
{
  HTexture ret = 0;
  lassert(surface != 0);
  if (!surface)
  {
    return 0;
  }
  
  int w = surface->w;
  int h = surface->h;

  SDL_Surface* zoomed = 0;

  /* we multiply by 4 because we don't want a crappy lookng zoomed surface. So we zoomfarther than we need for looks */
  if (surface->w <= maxTextureSize && surface->h <=maxTextureSize)
  {
    double newW = hts::min(nextPowerOf2(w*4, maxTextureSize), maxTextureSize);
    double newH = hts::min(nextPowerOf2(h*4, maxTextureSize), maxTextureSize);
    zoomed = zoomSurface(surface, newW/w, newH/h, 0);
    SDL_Surface* conv = SDL_DisplayFormatAlpha(zoomed);
    swap(conv, zoomed);
    SDL_FreeSurface(conv);
    if (newW != zoomed->w || newH != zoomed->h)
    {
      SDL_Surface* temp = adjustSize(zoomed, newW, newH);
      swap(zoomed, temp);
      SDL_FreeSurface(temp);
    }
    ret = loadTexture(zoomed->pixels, zoomed->w, zoomed->h, w, h);
  }
  else if (surface->w <= maxTextureSize)
  {
    double newW = hts::min(nextPowerOf2(w*4, maxTextureSize), maxTextureSize);
    double newH = h;
    zoomed = zoomSurface(surface, newW/w, newH/h, 0);
    SDL_Surface* conv = SDL_DisplayFormatAlpha(zoomed);
    swap(conv, zoomed);
    SDL_FreeSurface(conv);
    if (newW != zoomed->w || newH != zoomed->h)
    {
      SDL_Surface* temp = adjustSize(zoomed, newW, newH);
      swap(zoomed, temp);
      SDL_FreeSurface(temp);
    }

    ret = loadTexture(zoomed->pixels, zoomed->w, zoomed->h, w, h);
  }
  else if (surface->h <= maxTextureSize)
  {
    double newW = w;
    double newH = hts::min(nextPowerOf2(h*4, maxTextureSize), maxTextureSize);
    zoomed = zoomSurface(surface,  newW/w, newH/h, 0);
    SDL_Surface* conv = SDL_DisplayFormatAlpha(zoomed);
    swap(conv, zoomed);
    SDL_FreeSurface(conv);
    if (newW != zoomed->w || newH != zoomed->h)
    {
      SDL_Surface* temp = adjustSize(zoomed, newW, newH);
      swap(zoomed, temp);
      SDL_FreeSurface(temp);
    }

    ret = loadTexture(zoomed->pixels, zoomed->w, zoomed->h, w, h);
  }
  else // both bigger
  {
    SDL_Surface* conv = SDL_DisplayFormatAlpha(surface);
//    if (conv != surface)
//    {
////      swap(conv, surface);
////      SDL_FreeSurface(conv);
//      surface = conv;
//    }
    ret = loadTexture(conv->pixels, surface->w, surface->h, surface->w, surface->h);
    SDL_FreeSurface(conv);
  }

  if (zoomed)
  {
    SDL_FreeSurface(zoomed);  
  }

  return ret;

}

HTexture OpenGLDisplay::loadTexture(const char* filename)
{
  HTexture ret = 0;

  SDL_Surface* surface = loadSDLSurface(filename);

  ret = loadTexture(surface);

  SDL_FreeSurface(surface);

  return ret;
}

HTexture OpenGLDisplay::loadTexture(const void* pixels, int width, int height, int realW, int realH)
{
  GLTexture* tex=new GLTexture(realW, realH);

  // have to bust it up in to dimension that are powers of 2 and
  //  no bigger then maxTextureSize..

  // first make list of w's and h's
  int w=width;
  int sw = width;
  int w2=0;
  list<int> xs;
  list<int> ys;

  while (w>0)
  {
    int q=previousPowerOf2(w, maxTextureSize);
    xs.push_back(q);
    w-=q;
    w2+=q;
  }
  lassert(sw == w2);

  int h=height;
  int sh = height;
  int h2=0;
  while (h>0)
  {
    int q=previousPowerOf2(h, maxTextureSize);
    ys.push_back(q);
    h-=q;
    h2+=q;
  }
  lassert(sh == h2);

  // next, iterate through lists and alloc some buffers with the sub textures
  list<int>::iterator ix;
  list<int>::iterator iy;
  
  int curX=0;
  for (ix=xs.begin(); ix!=xs.end(); ix++)
  {
    int curY=0;
    for(iy=ys.begin(); iy!=ys.end(); iy++)
    {
      int iw = (*ix);
      int ih = (*iy);
      Uint8* glPixels = copyBits((Uint8*)pixels, width, curX, curY, iw, ih);
      // create subTexture
      GLSubTexture subT;
      subT.x = curX;
      subT.y = curY;
      subT.w = (*ix)*((float)realW/(float)width);
      subT.h = (*iy)*((float)realH/(float)height);
      subT.glId = setTexture(glPixels, (*ix), (*iy));
      tex->push_back(subT);
      curY+=(*iy);  
      delete [] glPixels; ///????
    }
    curX+=(*ix);
  }

  HTexture id = nextTextureId++;
  textureMap[id] = (void*)tex;
  CheckErr();

  addTextureInfo(id, new TextureInfo(realW, realH));
  return id;
}

void OpenGLDisplay::freeTexture(HTexture textureId)
{
  GLTexture* tex = (GLTexture*)textureMap[textureId];
  lassert (tex != 0);

  list<GLSubTexture>::iterator i;
  for (i=tex->begin(); i!=tex->end(); i++)
  {
    glDeleteTextures(1, &(*i).glId);
  }

  delete tex;
  textureMap.erase(textureId);
}  

Uint8* OpenGLDisplay::copyBits(const Uint8* src, int sWidth, int sx, int sy, int w, int h)
{
  Uint8* pixels = new Uint8[w*h*4];
  int dy=0;

  Uint8* destp = pixels;
  
  for (int y = sy; y<sy+h; y++)
  {
    int offset = (y*sWidth*4) + (sx*4);
    const Uint8* srcp = &(src[offset]);
    memcpy(destp, srcp, w*4);
    destp += (w*4);
    dy++;
  }
  return pixels;
}

Uint8* OpenGLDisplay::copyBitsWithBorder(const Uint8* src, int sWidth, int sx, int sy, int w, int h)
{
  Uint8* pixels = new Uint8[(w+2)*(h+2)*4];
  
  int dy=1;
  int y=0;
  Uint8* destp = pixels + 4;
  
  for (y = sy; y<sy+h; y++)
  {
    int offset = (y*sWidth*4) + (sx*4);
    const Uint8* srcp = &(src[offset]);
    memcpy(destp, srcp, w*4);
    destp += (w*4)+8;
    dy++;
  }

  // make top and bottom border;

  Uint8* srow = &(pixels[1*(w+2)*4]); // first data row;
  Uint8* drow = pixels;
  memcpy(drow, srow, (w+2)*4);

  srow = &(pixels[(h+1)*(w+2)*4]); // last data row;
  drow = &(pixels[(h+2)*(w+2)*4]);
  memcpy(drow, srow, (w+2)*4);


  // make left and right border
  for (y = 1; y<h; y++)
  {
    int offset = 0;
    Uint8* row;
    row = &(pixels[y*(w+2)*4]);
    row[0+0] = row[4+0];
    row[0+1] = row[4+1];
    row[0+2] = row[4+2];
    row[0+3] = row[4+3];

    offset = (w+1)*4;
    row[offset+0] = row[(offset-4)+0];
    row[offset+1] = row[(offset-4)+1];
    row[offset+2] = row[(offset-4)+2];
    row[offset+3] = row[(offset-4)+3];
  }



  return pixels;
}



unsigned int OpenGLDisplay::setTexture(const void* pixels, int width, int height)
{	
  Uint8 *rowhi, *rowlo;
  Uint8 *tmpbuf;
  Uint8 tmpch;

  int pitch = width*4;
  

  int i, j;
    /* GL surfaces are upsidedown and RGB, not BGR :-) */
  tmpbuf = new Uint8[pitch];
  if ( tmpbuf == NULL ) {
    fprintf(stderr, "Out of memory\n");
    return 0;
  }

  int size = width*height*4;
  Uint8* glPixels = new Uint8[size];
  memcpy(glPixels, pixels, size);
  int a, r, g, b;

  rowhi = (Uint8 *)glPixels;
  rowlo = rowhi + (height * pitch) - pitch;
  for ( i=0; i<height/2; ++i ) {
    for ( j=0; j<width; j++ ) {
      b = rowhi[j*4 + 0];
      g = rowhi[j*4 + 1];
      r = rowhi[j*4 + 2];
      a = rowhi[j*4 + 3];


//      a = 255;
//      if (r == 0xf0 && g == 0x00 && b == 0xf0)
//      {
//        a = 0;
//      }
      
      rowhi[j*4 + 0] = r;
      rowhi[j*4 + 1] = g;
      rowhi[j*4 + 2] = b;
      rowhi[j*4 + 3] = a;

      b = rowlo[j*4 + 0];
      g = rowlo[j*4 + 1];
      r = rowlo[j*4 + 2];
      a = rowlo[j*4 + 3];

//      a = 255;
//      if (r == 0xf0 && g == 0x00 && b == 0xf0)
//      {
//        a = 0;
//      }
      
      
      rowlo[j*4 + 0] = r;
      rowlo[j*4 + 1] = g;
      rowlo[j*4 + 2] = b;
      rowlo[j*4 + 3] = a;
    }
    memcpy(tmpbuf, rowhi, pitch);
    memcpy(rowhi, rowlo, pitch);
    memcpy(rowlo, tmpbuf, pitch);
    rowhi += pitch;
    rowlo -= pitch;
  }
  delete tmpbuf;

  GLuint glTexture;
  // Create Texture	
  glGenTextures(1, &glTexture);
  glBindTexture(GL_TEXTURE_2D, glTexture);   // 2d texture (x and y size)

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
  
  // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
  // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
  glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, glPixels);
  delete glPixels;

  CheckErr();

  return glTexture;
}

void checkGLError(const char* file, int line)
{
  GLenum err = glGetError();
  if (err != 0)
  {
    char buf[1024];
    sprintf(buf, "GLError: %02x - %s(%d)", err, file, line);
    logError(buf, Error);
  }

}
//
void OpenGLDisplay::drawVLine(int x, int y, int h, int red, int green, int blue, int alpha)
{
//  fillRect(x, y, 1, h, red, green, blue);
  drawLine(x, y, x, y+h, red, green, blue, alpha);
}
void OpenGLDisplay::drawHLine(int x, int w, int y, int red, int green, int blue, int alpha)
{
  drawLine(x, y, w+w, y, red, green, blue, alpha);
//  fillRect(x, y, w, 1, red, green, blue);
}

void OpenGLDisplay::drawLine(int x1, int y1, int x2, int y2, int red, int green, int blue, int alpha)
{
  glBegin(GL_LINES);
  FPoint topLeft = translate(x1, y1);
  FPoint topRight = translate(x2, y2);
  
  glColor4ub(red, green, blue, alpha);
  glVertex3f(topLeft.x, topLeft.y, 1.0f);
  
  glColor4ub(red, green, blue, alpha);
  glVertex3f(topRight.x, topRight.y, 1.0f);
  glEnd();
}

void OpenGLDisplay::fillRect(int x, int y, int w, int h, int red, int green, int blue, int alpha)
{
  static OpenGLDisplay* disp= 0;
  if (disp == 0)
  {
    disp = (OpenGLDisplay*)Display::getInstance();
  }

  int x1 = x;
  int y1 = y;
  int x2 = x + w;
  int y2 = y + h;

  glBegin(GL_QUADS);
  FPoint topLeft = disp->translate(x1, y1);
  FPoint topRight = disp->translate(x2, y1);
  FPoint bottomLeft = disp->translate(x1, y2);
  FPoint bottomRight = disp->translate(x2, y2);


  glColor4ub(red, green, blue, alpha);
  glVertex3f(bottomLeft.x, bottomLeft.y, 1.0f);

  glColor4ub(red, green, blue, alpha);
  glVertex3f(bottomRight.x, bottomRight.y, 1.0f);

  glColor4ub(red, green, blue, alpha);
  glVertex3f(topRight.x, topRight.y, 1.0f);
  
  glColor4ub(red, green, blue, alpha);
  glVertex3f(topLeft.x, topLeft.y, 1.0f);

  glEnd();
}
