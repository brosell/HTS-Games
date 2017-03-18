#pragma warning (disable : 4786 4503 4530)
#include "Listeners.h"
#include "Globals.h"
#include "GolfBall.h"
#include "Level.h"

IGConsoleListener::IGConsoleListener()
{
  Globals::console->addCallback("quit", this);
  Globals::console->addCallback("load", this);
}

IGConsoleListener::~IGConsoleListener()
{
  
}

void IGConsoleListener::consoleCommand(ConsoleEvent* event)
{
  if (event->command == "quit")
  {
    Globals::run = false;
  }

  if (event->command == "load")
  {
    loadMap(event);
  }
}

void IGConsoleListener::keyPressed(KeyPressEvent* event)
{
  if (event->keySym == SDLK_BACKQUOTE)
  {
    if (!Globals::console->isShowing())
    {
      Globals::console->show();
    }
    else
    {
      Globals::console->hide();
    }
  }

  if (Globals::console->isShowing())
  {
    return;
  }

  switch(event->keySym)
  {
  case SDLK_w:
    {
      theGame.screen->setWindowed(!theGame.screen->isWindowed());
    }
    break;
  case SDLK_r:
    {
      theGame.timeReport();
    }
    break;
//  case SDLK_SPACE:
//    {
//      if (Globals::theBall != 0)
//      {
//        Globals::theBall->applyForce(Vector(8, -16));
//      }
//    }
  case SDLK_d:
    {
      StopWatch sw;
      sw.start();
      Globals::world->draw(Display::getInstance());
      sw.stop();
      logError(Inform, "Wow %3d", sw.getElapsedTime());
    }
  }
}

void IGConsoleListener::loadMap(ConsoleEvent* event)
{
  
  if (event->args.size() != 1)
  {
    Globals::console->println("Usage: save mapFilename");
    return;
  }

  if (Globals::theLevel != 0)
  {
    delete Globals::theLevel;
    Globals::theLevel = 0;
  }

  Globals::theLevel = new Level(event->args.front());

}