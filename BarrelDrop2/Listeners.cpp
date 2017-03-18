#pragma warning (disable : 4786 4503 4530)

#include "Listeners.h"
#include "GameUI.h"

#include "SDLDisplay.h"

extern IniBasedDialog* dia_areYouSure;

void MenuListener::actionPerformed(ActionEvent* ev)
{ 
  switch (ev->commandId)
  {
  case 100:
    //startGame();
    showChooseMode();
    break;
  case 101:
    showCredits();
    break;
  case 102:
    //showInstruction();
    break;
  case 103: // quit button
    Globals::console->execute("quit");
    break;
  case 104:
    showHighScores();
    break;
  case 105:
    showOptions();
    break;
//  case 109:
  case 110:
    //showMainScreen();
    break;
  }
}



GameConsoleListener::GameConsoleListener(): consoleShowing(false)
{
  
}

void GameConsoleListener::keyPressed(KeyPressEvent* event)
{
  switch(event->keySym)
  {
  case SDLK_m:
    {
      theGame.am->report(inform);
      break;
    }
  }

//  case SDLK_BACKQUOTE:
//    {
//      if (!Globals::console->isShowing())
//      {
//        Globals::console->show();
//      }
//      else
//      {
//        Globals::console->hide();
//      }
//      
//    }
//    break;
//  case SDLK_g:
//    {
//      theGame.capture(true);
//    }
//    break;
//  case SDLK_h:
//    {
//      theGame.capture(false);
//    }
//    break;
//  case SDLK_s:
//    {
//      ((SDLDisplay*)(theGame.screen))->reportTextureInfo();
//    }
//    break;
//  case SDLK_w:
//    {
//      theGame.screen->setWindowed(!theGame.screen->isWindowed());
//    }
//    break;
//  case SDLK_r:
//    {
//      theGame.timeReport();
//    }
//
//  }
  
}


void GameConsoleListener::consoleCommand(ConsoleEvent* event)
{
  if (event->command == "quit")
  {
    bool prev = theGame.showCursor(true);
    if (dia_areYouSure->doModal() == 123)
    {
      Globals::run = false;
      Globals::endGame = true;
    }
    theGame.showCursor(prev);
  }

  if (event->command == "quitgame")
  {
    board->pause(true);
    theGame.showCursor(true);
    if (dia_areYouSure->doModal() == 123)
    {
      //Shape::instance().endGame();
      board->gameOver();
      return;
    }
    theGame.showCursor(false);
    board->pause(false);
  }

  if (event->command == "pausegame")
  {
    board->pause(!board->isPaused());
  }

  if (event->command == "musicvolume")
  {
    char buf[255];
    if (event->args.size() >= 1)
    {
      int v = atoi(event->args.front().c_str());
      Mix_VolumeMusic(v);
    }

    sprintf(buf, "Music Volume: %d", Mix_VolumeMusic(-1));
    Globals::console->println(buf);
  }

  if (event->command == "effectvolume")
  {
    char buf[255];
    if (event->args.size() >= 1)
    {
      int v = atoi(event->args.front().c_str());
      Mix_Volume(-1, v);
    }

    sprintf(buf, "EffectVolume: %d", Mix_Volume(-1, -1));
    Globals::console->println(buf);
  }
}
void GameListener::keyPressed(KeyPressEvent* ev) 
{ 
  switch (ev->keySym)
  {
  case SDLK_UP:
  case SDLK_LCTRL:
    Shape::instance().rotateLeft();
    break;
  case SDLK_LALT:
    Shape::instance().rotateRight();
    break;
  case SDLK_LEFT:
    Shape::instance().moveLeft();
    break;
  case SDLK_RIGHT:
    Shape::instance().moveRight();
    break;
  case SDLK_DOWN:
    Shape::instance().nudgeDown();
    break;
  case SDLK_o:
    board->pause(true);
    showOptions();
    board->pause(false);
    break;
  case SDLK_p:
    Globals::console->execute("pausegame");
    break;
  case SDLK_q:
    Globals::console->execute("quitgame");
    break;
  }
}

void GameListener::actionPerformed(ActionEvent* event)
{
  switch(event->commandId)
  {
  case 111:
    theGame.showCursor(true);
    board->pause(true);
    if (dia_areYouSure->doModal() == 123)
    {
      Shape::instance().endGame();
      return;
    }
    theGame.showCursor(false);
    board->pause(false);
    break;
  }
}


void AppFocus::appLostFocus()
{
  m_haveFocus = false;
  if (board != 0)
  {
    if (board->isRunning())
    {
      board->pause(true);
    }
  }
}

void AppFocus::appQuitRequest()
{
  if (board != 0)
  {
    board->pause(true);
    theGame.showCursor(true);
    if (dia_areYouSure->doModal() == 123)
    {
      //Shape::instance().endGame();
      board->gameOver();
      return;
    }
    theGame.showCursor(false);
    board->pause(false);
  }
  else
  {
    DialogBox* top = theGame.uiSystem.topModal();
    if (top)
    {
      top->terminateModal(0);
    }
    Globals::console->execute("quit");
  }
}
