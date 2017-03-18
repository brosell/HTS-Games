#ifndef SkinLoader_h
#define SkinLoader_h


#include "boost/format.hpp"
#include "SharedSkin.h"

/** the shared skin needs to "get" the sharable eachtime it uses it */
class SkinLoader
{
public:
  static SharableSkin* load(IniFile& ini, string name)
  {
    bool mask = ini.getInt(name, "UseMask")==1?true:false;
    
    SharableSkin* skin = new SharableSkin(mask);
    int fps = ini.getInt(name, "FPS");
    
    skin->setFPS(fps);
    
    Point forcedSize = Point(ini[name]["ForcedSize"]);
    if (forcedSize.x > 0 && forcedSize.y > 0)
    {
      skin->forceSize(forcedSize.x, forcedSize.y);
    }
    else
    {
      skin->forceSize(-1, -1);
    }
    int frameCount = ini.getInt(name, "Frames");
    if (frameCount == 0)
      frameCount = 1;
    

    for (int c=1; c<=frameCount; c++)
    {
      string frame = (boost::format("Frame%02d") % c).str();
      string frameFn = ini[name][frame];
      if (frameFn != "")
      {
        skin->addImage(frameFn.c_str(), 1);
      }
    }

    skin->load();

    return skin;
  }
  
  static void unload(SharableSkin* skin)
  {
    delete skin;
  }
};

#endif