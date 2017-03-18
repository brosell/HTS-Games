#pragma warning (disable:4786 4530 4503)
#include "Font.h"

#include "BR_Game.h"
#include "StdString.h"

Font::Font(string filename):
m_isValid(true),
m_surface(0)
{
  m_surface = loadSDLSurface(filename.c_str());
  if (!m_surface)
  {
    logError(Error, "Unable to load SFont: %s", filename.c_str());
    m_isValid = false;
    return;
  }

  m_size = m_surface->h * m_surface->pitch;

  m_fontInfo.Surface = m_surface;

  init(filename);
  
  // we don't free the SDL_Surface (unless we are in gl mode!)
}

class FontReleaseTexture: public std::unary_function<FontInfo&, void>
{
public:
  void operator() (FontInfo& fi)
  {
    Display::getInstance()->release(fi.textureId);
  }
};

Font::~Font()
{
  SDL_FreeSurface(m_surface);

  if (Display::getInstance()->getType() == OPENGL)
  {
    for_each(m_font.begin(), m_font.end(), FontReleaseTexture());
  }
}

int Font::drawLine(Display* surface, string s, int x, int y, bool centerCoords)
{
  int fx = x;
  int fy = y;
  if (m_isValid)
  {
    if (centerCoords)
    {
      fx = (x-(getTextWidth(s)/2));
      fy = (y-(getFontHeight()/2));
    }

    Vector v=theGame.screen->getDrawOffsetAmount();
    SDL_Surface* disp = surface->getSDLSurface();
    return putString(s, fx+v.x, fy+v.y);
  }
  return -1;
}

int Font::drawLine(SDL_Surface* surface, string s, int x, int y)
{
  if (m_isValid)
  {
    Vector v=theGame.screen->getDrawOffsetAmount();
    return putString(s, x+v.x, y+v.y);
  }
  return -1;
}

class StringWidthCalc: public std::unary_function<char, void>
{
public:
  StringWidthCalc(vector<FontInfo>& info): m_info(info), width(0) { }
  void operator()(char aChar)
  {
    if (aChar == ' ')
    {
      width += m_info[0].width;
      return;
    }
    int ofs=((unsigned char)aChar-33);//*2+1;
    width += m_info[ofs].width;
  }
  int width;
  
private:
  vector<FontInfo>& m_info;
};

int Font::getTextWidth(string str) 
{
  return for_each(str.begin(), str.end(), StringWidthCalc(m_font)).width;
}

int Font::getTextWidth(string str, int offset, int count)
{
  string::iterator start = str.begin();
  start+=offset;

  return for_each(start, start+count, StringWidthCalc(m_font)).width;
}

int Font::getFontHeight() 
{ 
  if (m_isValid)
    return m_fontInfo.Surface->h; 

  return -1;
}


/*  SFont: a simple font-library that uses special .pngs as fonts
    Copyright (C) 2003 Karl Bartel

    License: GPL or LGPL (at your choice)
    WWW: http://www.linux-games.com/sfont/

    This program is free software; you can redistribute it and/or modify        
    it under the terms of the GNU General Public License as published by        
    the Free Software Foundation; either version 2 of the License, or           
    (at your option) any later version.                                         
                                                                                
    This program is distributed in the hope that it will be useful,       
    but WITHOUT ANY WARRANTY; without even the implied warranty of              
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               
    GNU General Public License for more details.                
                                                                               
    You should have received a copy of the GNU General Public License           
    along with this program; if not, write to the Free Software                 
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA   
                                                                                
    Karl Bartel
    Cecilienstr. 14                                                    
    12307 Berlin
    GERMANY
    karlb@gmx.net                                                      
*/                                                                            

Uint32 getPixel(SDL_Surface *Surface, Sint32 X, Sint32 Y)
{

   Uint8  *bits;
   Uint32 Bpp;

   if (X<0) puts("SFONT ERROR: x too small in GetPixel. Report this to <karlb@gmx.net>");
   if (X>=Surface->w) puts("SFONT ERROR: x too big in GetPixel. Report this to <karlb@gmx.net>");
   
   Bpp = Surface->format->BytesPerPixel;

   bits = ((Uint8 *)Surface->pixels)+Y*Surface->pitch+X*Bpp;

   // Get the pixel
   switch(Bpp) {
      case 1:
         return *((Uint8 *)Surface->pixels + Y * Surface->pitch + X);
         break;
      case 2:
         return *((Uint16 *)Surface->pixels + Y * Surface->pitch/2 + X);
         break;
      case 3: { // Format/endian independent 
         Uint8 r, g, b;
         r = *((bits)+Surface->format->Rshift/8);
         g = *((bits)+Surface->format->Gshift/8);
         b = *((bits)+Surface->format->Bshift/8);
         return SDL_MapRGB(Surface->format, r, g, b);
         }
         break;
      case 4:
         return *((Uint32 *)Surface->pixels + Y * Surface->pitch/4 + X);
         break;
   }

    return -1;
}




void Font::init(string filename)
{
  int h = m_fontInfo.h = m_fontInfo.Surface->h;

  CStdString texname;
  
  int x = 0, i = 0;
  Uint32 pixel;
  Uint32 pink = SDL_MapRGB(m_fontInfo.Surface->format,255,0,255);
  if ( m_fontInfo.Surface==NULL ) {
    logError(Error, "The font has not been loaded!");
    return;
  }
  
  if (SDL_MUSTLOCK(m_fontInfo.Surface)) SDL_LockSurface(m_fontInfo.Surface);
  
  while ( x < m_fontInfo.Surface->w ) 
  {
    while (( x < m_fontInfo.Surface->w-1) && (getPixel(m_fontInfo.Surface,x,0)==pink))
    {
      // chew up pink
      x++;
    }
    m_fontInfo.CharPos.push_back(x);
    int xx = x;
    int w = 0;
    do
    {
      w++;
      x++;
    } while (( x < m_fontInfo.Surface->w-1) && (getPixel(m_fontInfo.Surface,x,0)!=pink));

    // at this point x and w are set... y = 0 and height is known
    /* create the correct surface, blit letter, load to gl */
    FontInfo fi;
    fi.width = w;
    fi.offset = xx;

    if(Display::getInstance()->getType() == OPENGL)
    {      
      SDL_Rect sr;
      sr.x = xx;
      sr.y = 0;
      sr.w = w;
      sr.h = h;
      
      SDL_Rect dr;
      dr.x=0;
      dr.y=0;
      dr.w=w;
      dr.h=h;
      
      SDL_Surface* surface = createSDLSurface(w, h, m_fontInfo.Surface);
      
      if (w==49)
      {
        w=w;
      }
      br_blit(m_fontInfo.Surface, sr, surface);
      
      texname.Format("%s %d", filename.c_str(), m_font.size());
      
      fi.textureId = Display::getInstance()->prepare(surface, texname);
      SDL_FreeSurface(surface);
    }

    m_font.push_back(fi);
  }
  
  pixel = getPixel(m_fontInfo.Surface, 0, m_fontInfo.Surface->h-1);
  if (SDL_MUSTLOCK(m_fontInfo.Surface)) SDL_UnlockSurface(m_fontInfo.Surface);  
  
  if(Display::getInstance()->getType() != OPENGL)
  {
    SDL_SetColorKey(m_fontInfo.Surface, SDL_SRCCOLORKEY, pixel);
  }
  
  int s=m_font.size();
  s=s;
}


class PutGLStringHelper: public std::unary_function<char, void>
{
public:
  PutGLStringHelper(vector<FontInfo>& fontInfo, int x, int y): m_fontInfo(fontInfo), m_x(x), m_y(y)
  { }
  void operator()(char aChar)
  {
    if (aChar == ' ')
    {
      m_x += m_fontInfo[0].width;

      return;
    }
    int ofs=((unsigned char)aChar-33);//*2+1;
    FontInfo& fi = m_fontInfo[ofs];
    Display::getInstance()->blit(fi.textureId, m_x, m_y);
    m_x+=fi.width;
  }

  int getWidth() { return m_x; }

private:
  vector<FontInfo>& m_fontInfo;
  int m_x;
  int m_y;
};

class PutSDLStringHelper: public std::unary_function<char, void>
{
public:
  PutSDLStringHelper(SDL_Surface* fontSurface, vector<FontInfo>& fontInfo, int x, int y, int h): 
      m_fontInfo(fontInfo),
      m_surface(fontSurface),
      m_x(x), 
      m_y(y), 
      m_h(h)
  { }
  void operator()(char aChar)
  {
    if (aChar == ' ')
    {
      m_x += m_fontInfo[0].width;
      return;
    }

    int ofs=((unsigned char)aChar-33);//*2+1;
    FontInfo& fi = m_fontInfo[ofs];
    

    SDL_Rect sr;
    sr.x=fi.offset;
    sr.y=0;
    sr.w=fi.width;
    sr.h=m_h;

    SDL_Rect dr;
    dr.x=m_x;
    dr.y=m_y;
    dr.w=fi.width;
    dr.h=m_h;

    SDL_BlitSurface(m_surface, &sr, Display::getInstance()->getSDLSurface(), &dr); 

    //Display::getInstance()->blit(fi.textureId, m_x, m_y);
    m_x+=fi.width;
  }

  int getWidth() { return m_x; }

private:
  vector<FontInfo>& m_fontInfo;
  SDL_Surface* m_surface;
  int m_x;
  int m_y;
  int m_h;
};


int Font::putString(string str, int x, int y)
{
  if (Display::getInstance()->getType() == OPENGL)
  {
    return for_each(str.begin(), str.end(), PutGLStringHelper(m_font, x, y)).getWidth();
  }
  else
  {
    return for_each(str.begin(), str.end(), PutSDLStringHelper(m_fontInfo.Surface, m_font, x, y, m_fontInfo.h)).getWidth();
  }
}





//void Font::putString(SDL_Surface* surface, string str, int x, int y)
//{
//  Display* display = Display::getInstance();
//  if (display->getType() == OPENGL)
//  {
//    putStringGL(str, x, y);
//    return;
//  }
//
//  const char* text = str.c_str();
//  int ofs;
//  int i=0;
//  SDL_Rect srcrect,dstrect; 
//  
//  
//
//  while (text[i]!='\0') {
//    if (text[i]==' ') {
//      x+=m_spaceSize; //m_fontInfo.CharPos[2]-m_fontInfo.CharPos[1];
//      i++;
//    }
//    else {
//      //	    printf("-%c- %c - %u\n",228,text[i],text[i]);
//      ofs=((unsigned char)text[i]-33)*2+1;
//      //	    ofs=(text[i]-33)*2+1;
//      //	    printf("printing %c %d\n",text[i],ofs);
//      srcrect.w = dstrect.w = (m_fontInfo.CharPos[ofs+2]+m_fontInfo.CharPos[ofs+1])/2-(m_fontInfo.CharPos[ofs]+m_fontInfo.CharPos[ofs-1])/2;
//      srcrect.h = dstrect.h = m_fontInfo.Surface->h-1;
//      srcrect.x = (m_fontInfo.CharPos[ofs]+m_fontInfo.CharPos[ofs-1])/2;
//      srcrect.y = 1;
//      dstrect.x = x-(float)(m_fontInfo.CharPos[ofs]-m_fontInfo.CharPos[ofs-1])/2;
//      dstrect.y = y;
//      
//      SDL_BlitSurface(m_fontInfo.Surface, &srcrect, surface, &dstrect); 
//      
//      x+=m_fontInfo.CharPos[ofs+1]-m_fontInfo.CharPos[ofs];
//      i++;
//    }
//  }
//}
//
