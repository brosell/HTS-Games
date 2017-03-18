#ifndef _Tile_h
#define _Tile_h

#include "Thing.h"

class BGTile: public Thing
{
public:
  Tile(SharedRotateSkin* texture, int x, int y):Thing(1, -1, false, true, 1)
  {
    //Rect r(x, y, w, h);
    setPosition(FPoint(x, y));
    setSkin("Tile", texture);
    showSkin("Tile");
  }

  virtual ~Tile() { }
protected:
  virtual void hit(Thing& other) {};

};

    

#endif