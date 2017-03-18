#pragma warning (disable : 4503 4530 4786)
#include "BR_Game.h"
#include "audio/SoundMixer.h"

#include "Globals.h"

#include "CoroutineDelegates.h"
#include "Tasking/GameScheduler.h"

using namespace std;
#include <list>
#include "StdString.h"
#include "BouncyBall.h"

list<BouncyBall*> balls;


void initEngine();
void gameLoop();

void co_tickGameFrame();

Line deflector(FPoint(100, 200), FPoint(500, 200));
//Line deflector2(FPoint(200, 400), FPoint(400, 200));

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
    case SDLK_q:
      {
        exit(0);
      }
      break;
    case SDLK_SPACE:
      {
        BouncyBall* ball = new BouncyBall;
        ball->addReflector(deflector);
        ball->addReflector(Line(FPoint(0, 0), FPoint(640, 0)));
        ball->addReflector(Line(FPoint(0, 0), FPoint(0, 480)));
        ball->addReflector(Line(FPoint(640, 0), FPoint(640, 480)));
        ball->addReflector(Line(FPoint(0, 480), FPoint(640, 480)));
        balls.push_back(ball);
      }
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


class PostDraw: public DrawListener
{
public:
  PostDraw()
  {
    //m_background = globals->assetManager->getSkin("skn_Background");
   
  }

  void preDraw()
  {
//    m_background->blit(theGame.screen, 0, 0, false);
  }

  void postDraw()
  {
        Display::getInstance()->drawLine(deflector.p1.x, deflector.p1.y,
                                     deflector.p2.x, deflector.p2.y,
                                     255, 0, 0, 255);

        list<BouncyBall*>::iterator i;
        for (i=balls.begin(); i!= balls.end(); i++)
        {
          (*i)->draw(Display::getInstance());
        }
  }


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


/*
logic
each tick move ball, if distToSegment < radius, reflect
*/
