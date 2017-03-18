#ifndef RotateSkinLoader_h
#define RotateSkinLoader_h


#include "boost/format.hpp"
#include "SharedRotateSkin.h"

/** the shared skin needs to "get" the sharable eachtime it uses it */
class RotateSkinLoader
{
public:
  static SharableRotateSkin* load(IniFile& ini, string name)
  {
    int rotations = ini.getInt(name, "Rotations");
    if (rotations == 0)
      rotations = 1;
    
    bool mask = ini.getInt(name, "UseMask")==1?true:false;
    
    SharableRotateSkin* skin = new SharableRotateSkin(rotations, mask);
        
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
  
  static void unload(SharableRotateSkin* skin)
  {
    delete skin;
  }
};

#endif