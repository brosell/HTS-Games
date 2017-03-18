#pragma warning (disable : 4786 4503 4530)
#include "BR_Game.h"
#include "IniFile.h"
#include "StdString.h"

#include "Globals.h"
#include "IGMapperListeners.h"
#include "IGMapperGlobals.h"

#include "ThinkScheduler.h"

IniBasedDialog* dlg_game = 0;

void initUI();
void initWorld();
void gameLoop();

Skin* mouse = 0;

void testCullable();

int main(int argc, char** argv)
{
  BR_Game::initialize(640, 480, 32, SDL, 0);

  Globals::init();

  initUI();
  initWorld();

//  mouse = Globals::assetManager->getSkin("mouse_Square");
//
//  theGame.setMouse("mouse_Default", 7, 7);
  theGame.uiSystem.setMouseCursor("mouse_Default");
  theGame.uiSystem.setFont(Globals::am->getFont("fnt_Default"));
  theGame.showCursor(true);

  dlg_game->show();
  gameLoop();

  return 0;
}

void initUI()
{
  IniFile ini("UI\\dialogs.ini");
  ini.read();
  dlg_game = new IniBasedDialog(ini, "Game");
  Globals::worldCanvas = (WorldCanvas*)dlg_game->getControlByName("WorldCanvas");
}
  

void initWorld()
{
//  Globals::world = new World(640, 480, 0, 0, 640, 480);
//  wc_worldCanvas->setWorld(Globals::world);
//  Globals::world->setViewportPos(0, 0);
//
//  Level* lvl = new Level("TestLevel.ini");
//
//  lvl->toWorld(Globals::world);
//  Globals::world->optimize();
}

//void co_screenScroller();
//void co_screenScroller()
//{
//  while (true)
//  {
//    GameScheduler::resumeAt(NEXT_FRAME);
//    
//    if (Globals::world == 0)
//    {
//      continue;
//    }
//    Point mouse = theGame.getMousePos();
//    if (mouse.x > 638)
//    {
//      if (Globals::viewX < Globals.world->getWorldDimensions().w - 640)
//      {
//        Globals::viewX+=10;
//      }
//      // shift map to the right
//    }
//    if (mouse.y > 478)
//    {
//      if (Globals::viewY < Globals.world->getWorldDimensions().h - 480)
//      {
//        Globals::viewY+=10;
//      }
//      // shift map to the down
//    }
//    if (mouse.x < 2)
//    {
//      if (Globals::viewX > 0)
//      {
//        Globals::viewX-=(min(10, Globals::viewX));
//      }
//    }
//    if (mouse.y < 2)
//    {
//      if (Globals::viewY > 0)
//      {
//        Globals::viewY-=(min(10, Globals::viewY));
//      }
//    }
//  }
//}

class ScreenScroller: public ThinkDelegate
{
public:
  virtual void invoke()
  {
    if (Globals::world == 0)
    {
      ThinkScheduler::resumeAt(ThinkScheduler::nextFrame());
      return;
    }
    //Globals::world->optimize();

    Rect r = Globals::world->getWorldDimensions();

    Point mouse = theGame.getMousePos();
    if (mouse.x > 638)
    {
      Globals::lastViewChangeWasMouse = true;
      if (Globals::viewX < Globals.world->getWorldDimensions().w - 640)
      {
        Globals::viewX+=10;
      }
      // shift map to the right
    }
    if (mouse.y > 478)
    {
      Globals::lastViewChangeWasMouse = true;
      if (Globals::viewY < Globals.world->getWorldDimensions().h - 480)
      {
        Globals::viewY+=10;
      }
      // shift map to the down
    }
    if (mouse.x < 2)
    {
      Globals::lastViewChangeWasMouse = true;
      if (Globals::viewX > 0)
      {
        Globals::viewX-=(min(10, Globals::viewX));
      }
    }
    if (mouse.y < 2)
    {
      Globals::lastViewChangeWasMouse = true;
      if (Globals::viewY > 0)
      {
        Globals::viewY-=(min(10, Globals::viewY));
      }
    }
    
//    if (Globals::theBall && 
//      (Globals::lastViewChangeWasMouse != true) )
//    {
//      Point p = Globals::theBall->getPositioni();
//      Rect r = Globals::world->getWorldDimensions();
//      int vx=p.x - (640/2);
//      int vy=p.y - (480/4);
//      if (vx < 0) vx=0;
//      if (vy < 0) vy=0;
//      if (vx > r.w - 640) vx = r.w - 640;
//      if (vy > r.h - 480) vy = r.h - 480;
//      
//      Globals::viewX = vx;
//      Globals::viewY = vy;
//      //theWorld->setViewport(vx, vy, 640, 480);
//    }

    ThinkScheduler::resumeAt(ThinkScheduler::nextFrame());
  }
};

//class PostDraw: public DrawListener
//{
//public:
//  virtual void postDraw()
//  {
//    int tileSize = Globals::tileSize;
//    int halfSize = tileSize/2;
//
//    Point m = theGame.getMousePos();
//    CStdString s;
//    s.Format("(%d, %d)", Globals::viewX, Globals::viewY);
//    Font::getDefault()->drawLine(Display::getInstance(), s, 320, 240);
//
////    m.x = (m.x/tileSize)*tileSize;
////    m.y = (m.y/tileSize)*tileSize;
////    mouse->blit(Display::getInstance(), m.x+halfSize, m.y+halfSize);
//
//    if (IGMapperGlobals::cur != 0)
//    {
//      IGMapperGlobals::cur->draw(Display::getInstance(), m.x, m.y);
//    }
//  }
//};


void gameLoop()
{
  
  ScreenScroller scroller;  
  ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &scroller);

  IGMapperConsoleListener list;

  theGame.uiSystem.addKeyListener(&list);
  Globals::worldCanvas->addMouseListener(&list);
  theGame.setDrawListener(&list);
  
  
  while(true)
  {
    if (Globals::world != 0)
    {
      Globals::world->setViewportPos(Globals::viewX, Globals::viewY);
    }
    theGame.pump();
  }
}

#include "CullFaces.h"

void testCullable()
{
  Line l1(FPoint(0, 0), FPoint(100, 0));
  Line l2(FPoint(100, 0), FPoint(200, 0));
  Line l3(FPoint(100, 20), FPoint(200, 0));

  list<Line> lines;
  lines.push_back(l1);
  lines.push_back(l2);
  lines.push_back(l3);
  lines.push_back(Line(FPoint(200, 200), FPoint(400, 400)));
  lines.push_back(Line(FPoint(400, 400), FPoint(800, 800)));

  list<Line> ans = cullFaces(lines);

  list<Line>::iterator i;
  for (i=ans.begin(); i!=ans.end(); i++)
  {
    Line line = *i;
    printf("Line ((%f, %f), (%f, %f))\n", line.p1.x, line.p1.y, line.p2.x, line.p2.y);
  }

}

