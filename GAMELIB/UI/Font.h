#ifndef _Font_h
#define _Font_h

#include "Event/Keyboard-utils.h"
#include <string>
#include <vector>
using namespace std;

const int FONT_HEIGHT = 17;
const int FONT_WIDTH = 11;

#ifndef FontNoShift
#define FontNoShift "images\\LettersNoShift.bmp"
#define FontShift "images\\LettersShift.bmp"
#endif

#include "Graphics/Display.h"

class Display;

Uint32 getPixel(SDL_Surface *Surface, Sint32 X, Sint32 Y);

//#include "SFont.h"

typedef struct {
	SDL_Surface *Surface;	
	//int CharPos[512];
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

  //static Font* load(string filename);
  static Font* getDefault();

  void loadToGL(char aChar);
private:
  bool m_isValid;
  HTexture m_texture;
  SDL_Surface* m_surface;

  SFont_FontInfo m_fontInfo;
  

  static map<string, Font*> s_fonts;

  
  void init(string filename);
  
  void putString(SDL_Surface* surface, string str, int x, int y);
  
  int putString(string str, int x, int y);

  int getGLTextWidth(string str);
  
  vector<FontInfo> m_font;
  int m_spaceSize;
//  static string s_chars;
};


#endif