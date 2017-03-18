#ifndef NextShapeCanvas_h
#define NextShapeCanvas_h

#include "BR_Game.h"

#include "Board.h"

class SharedSkin;

class  NextShapeCanvas: public Canvas
{
public:
  NextShapeCanvas();
  ~NextShapeCanvas();

  virtual void paint(Display* display);

private:
  SharedSkinHandle m_blockSkins[BLOCK_COUNT];
  SharedSkinHandle m_wildUpDownSkin;
  SharedSkinHandle m_wildLeftRightSkin;
};

#endif