#ifndef _Font_h
#define _Font_h

#include <string>
#include <vector>
using namespace std;

#include "Display.h"

class Display;

Uint32 getPixel(SDL_Surface *Surface, Sint32 X, Sint32 Y);

typedef struct {
	SDL_Surface *Surface;	
  vector<int> CharPos;
	int h;
} SFont_FontInfo;

typedef struct
{
  HTexture textureId;
  int offset;
  int width;
} FontInfo;
 
class Font
{
public:
  Font(string filename);
  ~Font();

  virtual int getTextWidth(string str);
  virtual int getTextWidth(string str, int offset, int count);
  virtual int getFontHeight();
  
  virtual int drawLine(Display* surface, string s, int x, int y, bool centerCoords = false);

  virtual int drawLine(SDL_Surface* surface, string s, int x, int y);

  void loadToGL(char aChar);

  size_t getSize() { return m_size; }
private:
  size_t m_size;
  bool m_isValid;
  HTexture m_texture;
  SDL_Surface* m_surface;

  SFont_FontInfo m_fontInfo;
  

  void init(string filename);
  
  void putString(SDL_Surface* surface, string str, int x, int y);
  
  int putString(string str, int x, int y);

  int getGLTextWidth(string str);
  
  vector<FontInfo> m_font;
  int m_spaceSize;
//  static string s_chars;
};


#endif