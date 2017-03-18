#pragma warning (disable : 4786 4503 4530)

#include "BR_Game.h"
#include "Log.h"
#include "Convert.h"
#include "IniFile.h"

#include "Listeners.h"
#include "Board.h"

#include "SoundMixer.h"
#include "Music.h"
#include "AssetManager.h"
#include "CommandLineParser.h"

#include "HighScores.h"

#include "Globals.h"
#include "GameUI.h"
#include "SplashScreen.h"

World* g_world = 0;

CommandLineParser g_clp;

void initEngine();
void initWorld();
void gameLoop();
void initConsoleCommands();
void cleanup();
void showFinally();

int g_lastScore = 0;
int g_lastLevel = 0;

Board* board = 0;
bool deleteBoard = false;

SoundEffect* music = 0;

HighScores g_highScores;

int main(int ac, char** av)
{
  MaintLog::get().setFilter(All);

  g_clp.setFlagDef("gl", false);
  g_clp.setStringDef("bpp", "32");
  g_clp.setStringDef("skincache", "3");
  g_clp.setStringDef("soundcache", "0");
  g_clp.setStringDef("fontcache", "0");
  g_clp.parse(ac, av);

  Globals::assetManager = new AssetManager("Assets.ini");

//  if (!Globals::assetManager->verify())
//  {
//    delete Globals::assetManager;
//    MessageBox(0, "Required files are missing!\nPlease reinstall Barrel Drop!", "Can't start", MB_OK | MB_ICONEXCLAMATION);
//    return -1;
//  }

  
  Globals::init("Scoring.ini");
  
  initEngine();

  theGame.assetManager = Globals::assetManager;
  IniFile assets("Assets.ini");
  assets.read();
  theGame.am = new AM(assets);
  theGame.am->setSkinLimit(g_clp.getFloatArg("skincache")*1024);
  theGame.am->setSoundEffectLimit(g_clp.getFloatArg("soundcache")*1024);
  theGame.am->setFontLimit(g_clp.getFloatArg("fontcache")*1024);

  Globals::am = theGame.am;

  SplashScreen* ss = new SplashScreen("tx_Splash");
  ss->setPosition(Rect(0, 0, 630, 480));
  theGame.uiSystem.addUIThing(ss);
  theGame.draw();

  initUI();
  
  initWorld();

  theGame.uiSystem.removeUIThing(ss);
  delete ss;
  
  dia_mainScreen->show();

  music = Globals::assetManager->getSoundEffect("mus_Background");
  if (music != 0)
  {
    music->play(-1);
  }

  g_highScores.load("HighScores.ini");

  AppFocus appFocusListener;
  theGame.setAppListener(&appFocusListener);

  while(Globals::run)
  {
    if (!appFocusListener.haveFocus())
    {
      Sleep(100);
    }
    theGame.pump();
    if (Globals::run == true && Globals::endGame == true)
    {
      endGame();
    }
  }


  theGame.setAppListener(0);

  if (music != 0)
  {
    music->halt();
  }

  if (!theGame.isWindowed())
    theGame.setWindowed(true);


  dia_mainScreen->hide();
  if (Globals::isDemo)
  {
    ShellExecute(NULL, "open", "http://www.htsgames.com/BDDemoRefer.cfm", NULL, NULL, SW_SHOW);
  }
  showFinally();

  cleanup();

  return 0;
}

void showFinally()
{
  IniFile ini("UI\\Dialogs.ini");
  ini.read();
  IniBasedDialog fin(ini, "dlg_Finally");
  fin.doModal();
}

void cleanup()
{
  logError(Inform, "Cleaning up");
  

  cleanupUI();

  delete Globals::console;
  
  
  delete g_world;
  if (board)
    delete board;

  theGame.screen->report();

  Timer::cleanup();
  delete Globals::am;
  Globals::am = 0;
  
  delete &theGame;

  
//  delete Globals::assetManager;

//  MaintLog::closeall();
}


void initWorld()
{
  g_world = new World(480, 480, 0, 0, 480, 480);
  
  wc_worldCanvas->setWorld(g_world);

  g_world->setViewportPos(0, 0);

}

void initEngine()
{
  Uint32 flags = 0; //SDL_DOUBLEBUF;
  IniFile options("options.ini");
  options.read();
  if (options.getInt("Video", "Fullscreen") == 1)
  {
    flags |= SDL_FULLSCREEN;
  }

  DisplayType type = SDL;
  if (g_clp.getFlagArg("gl"))
  {
    type = OPENGL;
  }

  int bpp = g_clp.getIntArg("bpp");

//  MaintLog::get().setFilter(AllDebug);
  BR_Game::initialize(640, 480, bpp, type, flags);

//  theGame.showFPS(true);
  
  SoundMixer::initialize(22050, AUDIO_S16, 2, 2048);

  SDL_Surface* icon = loadSDLSurface("images\\icon.png");
  theGame.setWindowInfo(icon, "Barrel Drop!");

  UIThing::s_smartDraw = false;
}

void initConsoleCommands()
{
  Globals::console->addCallback("quit", &consoleListener);
  Globals::console->addCallback("musicvolume", &consoleListener);
  Globals::console->addCallback("effectvolume", &consoleListener);
  Globals::console->addCallback("quitgame", &consoleListener);
  Globals::console->addCallback("pausegame", &consoleListener);
}

void startGame()
{
  dia_mainScreen->hide();
  dia_gameScreen->show();

  dia_current = dia_gameScreen;

  prg_progress->setValue(0);

  Globals::endGame = false;

  theGame.uiSystem.addKeyListener(&gameListener);
  theGame.showCursor(false);

  board = new Board;
  deleteBoard = false;
  FPoint pos(wc_worldCanvas->getPosition().x, wc_worldCanvas->getPosition().y);
  board->setPosition(pos);
  g_world->addThing(*board);

  g_world->optimize();
  
  board->start();
}

void endGame()
{
  Globals::endGame = false;
  dia_gameScreen->hide();
  dia_mainScreen->show();

  g_lastScore = Score::getCurrentScore();
  g_lastLevel = Score::getCurrentLevel();

  g_world->removeThing(*board);
  delete board;
  board = 0;
  
    
  theGame.uiSystem.removeKeyListener(&gameListener);

  theGame.showCursor(true);

  if (Globals::isDemo && Score::getCurrentLevel() > DEMO_LEVELS)
  {
    showDemoOver();
  }

  if (g_highScores.isHighScore(g_lastScore))
  {
    showEnterHighScoreScreen();
  }
  else
  {
    showGameOver();
  }
//  deleteBoard = true;
}


void gameLoop()
{

  while(Globals::run)
  {
    theGame.pump();
    if (Globals::run == true && Globals::endGame == true)
    {
      endGame();
    }
  }
}

