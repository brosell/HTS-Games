#pragma warning (disable : 4503 4530 4786)
#include "BR_Game.h"
#include "audio/SoundMixer.h"

#include "Globals.h"

#include "CoroutineDelegates.h"
#include "Tasking/GameScheduler.h"

#include "Rocket.h"

#include <vector>
using namespace std;

vector<Rocket*> rockets;

void initEngine();
void gameLoop();

void co_tickGameFrame();


int main(int a, char** v)
{
  initEngine();
  globals = new Globals;

  IniFile ini("UI/Dialogs.ini");
  ini.read();

  theGame.setMouse("mouse_Default", 7, 7);

  gameLoop();

  return 0;
}

class QuitListener: public KeyListener
{
public:
  void keyPressed(KeyPressEvent* event)
  {
    switch (event->keySym)
    {
    case SDLK_SPACE:
      {
        Rocket* rocket = new Rocket(Point(rand()%640, rand()%480), Vector(3, 3));
        rockets.push_back(rocket);
      }
      break;
    case SDLK_q:
      {
        exit(0);
      }
      break;
    case SDLK_r:
      {
        theGame.timeReport();
      }
      break;
    case SDLK_t:
      {
        Timer::report();
      }
      break;
    case SDLK_w:
      {
        theGame.screen->setWindowed(!theGame.screen->isWindowed());
      }
      break;
    }
  }

}quitListener;

#include "StdString.h"

class PostDraw: public DrawListener
{
public:
  PostDraw()
  {
    m_background = globals->assetManager->getSkin("skn_Background");
  }

  void preDraw()
  {
//    m_background->blit(theGame.screen, 0, 0, false);
  }

  void postDraw()
  {
    globals->particleSystem.draw(theGame.screen);

    vector<Rocket*>::iterator i;
    for (i=rockets.begin(); i!= rockets.end(); i++)
    {
      (*i)->draw(theGame.screen);
    }
  }

  Skin* m_background;
};
void gameLoop()
{
  PostDraw postDraw;
  theGame.uiSystem.addKeyListener(&quitListener);
  theGame.setDrawListener(&postDraw);

  while(true)
  {
    theGame.screen->clear();
    theGame.pump();
  }
}
void initEngine()
{
  BR_Game::initialize(640, 480, 16, SDL, 0);

  SoundMixer::initialize(22050, AUDIO_S16, 2, 1024);
}
