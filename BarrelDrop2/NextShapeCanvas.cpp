#pragma warning (disable : 4786 4503 4530)

#include "NextShapeCanvas.h"
#include "Shape.h"
#include "Board.h"
#include "SharedSkin.h"
#include "Globals.h"

extern Board* board;

string bcolors[] = 
{
  "Red",
  "Green",
  "Blue",
  "Yellow",
  "Purple"
};

NextShapeCanvas::NextShapeCanvas():
Canvas() 
{ 
  for (int c=0; c<BLOCK_COUNT; c++)
  {
    char assetName[128];
    sprintf(assetName, "gfx_Block_%s_Idle", bcolors[c].c_str());
    
    m_blockSkins[c] = Globals::am->getSkin(assetName);
  }
  m_wildUpDownSkin = Globals::am->getSkin("gfx_Block_Wild_Up_Down");
  m_wildLeftRightSkin = Globals::am->getSkin("gfx_Block_Wild_Left_Right");
}

NextShapeCanvas::~NextShapeCanvas()
{
}

void NextShapeCanvas::paint(Display* display)
{
  if (!board->isRunning())
  {
    return;
  }

  ShapePrimitive* nextShape = Shape::instance().getNextShape();
  
  Rect r = getTranslatedPosition();

  Point pb1 = nextShape->getBlock1Pos(Point(0, 0));
  Point pb2 = nextShape->getBlock2Pos(Point(0, 0));
  Point pb3 = nextShape->getBlock3Pos(Point(0, 0));

  pb1.x*=BLOCK_SIZE;
  pb1.y*=BLOCK_SIZE;
  pb2.x*=BLOCK_SIZE;
  pb2.y*=BLOCK_SIZE;
  pb3.x*=BLOCK_SIZE;
  pb3.y*=BLOCK_SIZE;

  Point pbs1(r.x+(pb1.x*BLOCK_SIZE), r.y+(pb1.y*BLOCK_SIZE));
  Point pbs2(r.x+(pb2.x*BLOCK_SIZE), r.y+(pb2.y*BLOCK_SIZE));
  Point pbs3(r.x+(pb3.x*BLOCK_SIZE), r.y+(pb3.y*BLOCK_SIZE));


  if (nextShape->getBlock(0)->getColor() == 999)
  {
    int x = r.x + ((r.w/2) - (45/2));
    int y = r.y + ((r.h/2) - (45/2));

    //m_wildUpDownSkin->blit(display, pbs1.x+=BLOCK_SIZE, pbs1.y, false);
    m_wildUpDownSkin->blit(display, x, y, false);
  }
  else if (nextShape->getBlock(0)->getColor() == 998)
  {
    int x = r.x + ((r.w/2) - (45/2));
    int y = r.y + ((r.h/2) - (45/2));

    //m_wildLeftRightSkin->blit(display, pbs1.x+=BLOCK_SIZE, pbs1.y, false);
    m_wildLeftRightSkin->blit(display, x, y, false);
  }
  else
  {
    int x, y;
    if (!nextShape->isStraight())
    {
      // shift the pieces over so they are centered
//      pbs1.x+=HALF_BLOCK_SIZE;
//      pbs2.x+=HALF_BLOCK_SIZE;
//      pbs3.x+=HALF_BLOCK_SIZE;
      x = r.x + ((r.w/2) - (45*2/2));
      y = r.y + ((r.h/2) - (45*2/2));
    }
    else
    {
      x = r.x + ((r.w/2) - (45*3/2));
      y = r.y + ((r.h/2) - (45/2));
    }

    nextShape->getBlock(0)->drawToScreen(display, pb1.x + x, pb1.y + y);
    nextShape->getBlock(1)->drawToScreen(display, pb2.x + x, pb2.y + y);
    nextShape->getBlock(2)->drawToScreen(display, pb3.x + x, pb3.y + y);
//    m_blockSkins[nextShape->getBlock(0)->getColor()]->blit(display, pbs1.x, pbs1.y, false);
//    m_blockSkins[nextShape->getBlock(1)->getColor()]->blit(display, pbs2.x, pbs2.y, false);
//    m_blockSkins[nextShape->getBlock(2)->getColor()]->blit(display, pbs3.x, pbs3.y, false);
  }
}
