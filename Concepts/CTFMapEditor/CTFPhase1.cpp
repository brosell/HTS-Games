#pragma warning (disable : 4503)

#include "BR_Game.h"
#include "Log.h"
#include "CommandLineParser.h"
#include "UI/IniBasedDialog.h"

#include "Engine.h"

void initEngine();
void initWorld();
void gameLoop();

void doScreenMove();

Uint32 startflags = 0;
Uint32 startBpp = 32;
DisplayType startType = SDL;

WorldCanvas* worldCanvas = 0;
DialogBox* db = 0;

int viewX = 0;
int viewY = 0;


class TheListener: public KeyListener, public TimerListener, public MouseListener, public DrawListener, public ConsoleListener
{
public:
  TheListener(): consoleShowing(false)
  { 
    
  }

  virtual void keyPressed(KeyPressEvent* event)
  {
    if (event->keySym == SDLK_ESCAPE)
    {
//      exit(0);
    }

    if (event->keySym == SDLK_BACKQUOTE)
    {
      if (!theGame.console->isShowing())
      {
        theGame.console->show();
      }
      else
      {
        theGame.console->hide();
      }
      return;
    }
  }


  virtual void mouseClicked(MouseClickEvent* event)
  {

  }


  virtual void timeout(TimerEvent* event)
  {

    Thing::tickAll();
    
    doScreenMove();
    Engine::instance->theWorld->setViewportPos(viewX, viewY);
  }

  virtual void consoleCommand(ConsoleEvent* event)
  {
    if (event->command == "quit")
    {
      exit(0);
    }
  }

private:
  bool consoleShowing;
} theListener;


int main(int argc, char** argv)
{
  MaintLog::get().setFilter(AllDebug);


  CommandLineParser clp;

  clp.setFlagDef("gl", true);
  clp.setFlagDef("fs", false);
  clp.setFlagDef("ded", false);
  clp.setStringDef("bpp", "32");
  clp.setStringDef("maxTextureSize", "256");
  clp.setStringDef("query", "");
  clp.parse(argc, argv);


  if (clp.getFlagArg("gl"))
  {
    startflags |= SDL_OPENGL;
    startType = OPENGL;
  }
  else
  {
    startflags |= SDL_DOUBLEBUF;
  }

  if (clp.getFlagArg("fs"))
  {
    startflags |= SDL_FULLSCREEN;
  }

  startBpp = clp.getIntArg("bpp");

  initEngine();
  initWorld();

  gameLoop();

  return 0;
}

void initWorld()
{
  Engine::instance = new Engine;
  Engine::instance->theWorld = new World(480*8, 480*8, 0, 0, 800, 600);
  //Engine::instance->theWorld = new World(480*8, 480*8, 0, 0, 640, 480);

  Engine::instance->theWorld->optimize();

  Engine::instance->theMap = new SpaceTileMap(32);

  worldCanvas = new WorldCanvas(Engine::instance->theWorld);
  worldCanvas->setPosition(Rect(0, 0, 800, 600)); 
  theGame.uiSystem.addUIThing(worldCanvas);
  worldCanvas->addMouseListener(Engine::instance->theMap);
  worldCanvas->addKeyListener(Engine::instance->theMap);

  Engine::instance->theWorld->setViewportPos(0, 0);
}

void initEngine()
{

  BR_Game::initialize(800, 600, startBpp, startType, startflags);
  //BR_Game::initialize(640, 480, startBpp, startType, startflags);

  theGame.console->addCallback("quit", &theListener);

  theGame.showFPS(false);
  Display* screen = theGame.screen;

  Skin* mouse=new Skin;
  mouse->addImage(screen->loadTexture("images\\BullsEye.bmp"));
  theGame.setMouse(mouse, 7, 7);
  theGame.showCursor(true);
}



void gameLoop()
{
  TheListener theListener;
  theGame.uiSystem.addKeyListener(&theListener);
  Timer::create(1, 1000/30, &theListener, 0, true); // Game Tick

  theGame.setDrawListener(&theListener);
  while(true)
  {
    theGame.pump();
  }
}

void doScreenMove()
{
  int maxX = Engine::instance->theMap->getPixelWidth() - worldCanvas->getPosition().w; //(480*4)-800;
  int maxY = Engine::instance->theMap->getPixelHeight() - worldCanvas->getPosition().h; //(480*4)-600;

  int ph = Engine::instance->theMap->getPixelHeight();
  int hh = worldCanvas->getPosition().h;

  Point mouse = theGame.getMousePos();
  if (mouse.x <= 1 && viewX > 0)
  {
    viewX -= 10;
    if (viewX < 0)
    {
      viewX = 0;
    }
  }
  else if (mouse.x >= (theGame.screen->getWidth()-1) && viewX < maxX)
  {
    viewX += 10;
    if (viewX > maxX)
    {
      viewX = maxX;
    }
  }

  if (mouse.y <= 1 && viewY > 0)
  {
    viewY -= 10;
    if (viewY < 0)
    {
      viewY = 0;
    }
  }
  else if (mouse.y >= (theGame.screen->getHeight()-1) && viewY < maxY)
  {
    viewY += 10;
    if (viewY > maxY)
    {
      viewY = maxY;
    }
  }
}