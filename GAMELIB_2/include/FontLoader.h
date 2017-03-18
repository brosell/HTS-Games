#ifndef FontLoader_h
#define FontLoader_h

#include "Font.h"
#include <string>
#include "IniFile.h"

class FontLoader
{
public:
  static Font* load(IniFile& ini, std::string name)
  {
    Font* font = new Font(ini[name]["Filename"]);
    return font;
  }

  static void unload(Font* font)
  {
    delete font;
  }
};

#endif