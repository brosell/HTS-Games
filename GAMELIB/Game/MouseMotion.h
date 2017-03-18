#ifndef _MouseMotion_h
#define _MouseMotion_h

#include "Motion.h"
#include "SDL.h"

class MouseMotion: public Motion
{
public:
  MouseMotion(float x, float y, int w, int h) : Motion(x, y, w, h)
  {
    
  }

  static void mouseMoved(int x, int y)
  {
    s_x=x;
  }

  void tickAndMove(int& retX, int& retY);

private:
  static int s_x;
};


#endif