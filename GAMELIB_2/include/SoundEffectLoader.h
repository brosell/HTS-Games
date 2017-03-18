#ifndef SoundEffectLoader_h
#define SoundEffectLoader_h

#include "SoundEffect.h"
#include <string>
#include "IniFile.h"

class SoundEffectLoader
{
public:
  static SoundEffect* load(IniFile& ini, std::string name)
  {
    SoundEffect* se = new SoundEffect(ini[name]["Group"], ini[name]["Filename"]);
    return se;
  }

  static void unload(SoundEffect* effect)
  {
    delete effect;
  }
};

#endif