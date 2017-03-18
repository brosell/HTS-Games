#pragma warning (disable : 4503 4530 4786)
#include "BR_Game.h"
#include "audio/SoundMixer.h"

#include "Globals.h"
#include "Shape.h"
#include "GameScreen.h"
#include "Quadrant.h"

#include "CoroutineDelegates.h"

void initEngine();
void gameLoop();

Globals* globals = 0;
int main(int a, char** v)
{
  initEngine();
  globals = new Globals;

  IniFile ini("UI/Dialogs.ini");
  ini.read();
  GameScreen screen(ini, "GameScreen");

  theGame.setMouse(globals->assetManager->getSkin("mouse_Default"), 7, 7);

  screen.show();

  gameLoop();

  return 0;
}

class QuitListener: public KeyListener
{
public:
  void keyPressed(KeyPressEvent* event)
  {
    if (event->keySym == SDLK_q)
    {
      exit(0);
    }
  }
}quitListener;

void gameLoop()
{
  theGame.uiSystem.addKeyListener(&quitListener);
  while(true)
  {
    theGame.pump();
  }
}
void initEngine()
{
#ifdef _DEBUG
  //MaintLog::get().setFilter(AllDebug);
  BR_Game::initialize(640, 480, 16, SDL, SDL_DOUBLEBUF);
#else
  MaintLog::get().setFilter(Errors);
  BR_Game::initialize(640, 480, 16, SDL, SDL_DOUBLEBUF | SDL_FULLSCREEN );
#endif

  SoundMixer::initialize(22050, AUDIO_S16, 2, 1024);
}
