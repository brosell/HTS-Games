#pragma warning (disable : 4786 4503 4530)
#include "CommandLineParser.h"
#include "BR_Game.h"
#include "IniFile.h"

#include "Globals.h"

#include "Level.h"

#include "GameScheduler.h"

#include "Listeners.h"
#include "UI.h"

IniBasedDialog* dlg_game = 0;
WorldCanvas* wc_worldCanvas = 0;

void initWorld();
void cleanWorld();
void gameLoop();

int main(int argc, char** argv)
{
  CommandLineParser clp;
  clp.setFlagDef("gl", true);
  clp.setFlagDef("fs", false);
  clp.parse(argc, argv);
  DisplayType type = OPENGL;
  Uint32 flags = 0;

  if (!clp.getFlagArg("gl"))
  {
    type = SDL;
  }
  if (clp.getFlagArg("fs"))
  {
    flags = SDL_FULLSCREEN;
  }

  MaintLog::get().setFilter(All);
  BR_Game::initialize(640, 480, 32, type, flags); //SDL_FULLSCREEN);

  Globals::init();

  initUI();
  initWorld();

  theGame.uiSystem.setMouseCursor("mouse_Default");
  theGame.showCursor(true);

  showMainMenu();
  gameLoop();

  cleanWorld();
  cleanUI();

  Globals::clean();
  return 0;
}



void initWorld()
{
  Globals::world = new World(0, 0);
  Globals::worldCanvas->setWorld(Globals::world);
  Globals::world->parallaxScroll(1, 1.5);
}

void cleanWorld()
{
  delete Globals::world;
}

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
    
    if (Globals::theBall && 
      (Globals::lastViewChangeWasMouse != true) )
    {
      Point p = Globals::theBall->getPositioni();
      Rect r = Globals::world->getWorldDimensions();
      int vx=p.x - (640/2);
      int vy=p.y - (480/4);
      if (vx < 0) vx=0;
      if (vy < 0) vy=0;
      if (vx > r.w - 640) vx = r.w - 640;
      if (vy > r.h - 480) vy = r.h - 480;
      
      Globals::viewX = vx;
      Globals::viewY = vy;
      //theWorld->setViewport(vx, vy, 640, 480);
    }

    ThinkScheduler::resumeAt(ThinkScheduler::nextFrame());
  }
};


void gameLoop()
{
  ScreenScroller scroller;  
  ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &scroller);
  //HTimer timer = Timer::create("screenscroller", 1, 1000/30, &scroller, 0, true);

  IGConsoleListener list;

  theGame.uiSystem.addKeyListener(&list);
//  Globals::worldCanvas->addMouseListener(&list);

  while(Globals::run)
  {
    if (Globals::world != 0)
    {
      Globals::world->setViewportPos(Globals::viewX, Globals::viewY);
    }
    theGame.pump();
  }
  //Timer::destroy(timer);
}

