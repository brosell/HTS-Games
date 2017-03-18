#pragma warning (disable : 4503)

#include "Engine.h"

Engine* Engine::instance;

Engine::Engine()
{
  theGame.console->addCallback("route", this);
  theRecord = 0;
  theMap = 0;
  theWorld = 0;
}

void Engine::consoleCommand(ConsoleEvent* event)
{
  if (event->command == "route")
  {
    if (event->args.size() != 1 || (event->args.front() != "show") && (event->args.front() != "hide"))
    {
      theGame.console->println("Error: route [show | hide]\n");
      return;
    }

    Ship::s_showRoute = (event->args.front() == "show");
    string res = "Route ";
    res += (char*)(Ship::s_showRoute?"Showing":"Hidden");
    res += "\n";
    theGame.console->println(res);
  }
}

void Engine::recordStart(string filename)
{
//  recordStop();
//  theRecord = new IniFile(filename);
}

void Engine::record(string str)
{
//  static int lasttick = 0;
//  static char lastletter = 'a';
//  int gametick = BR_Game.ticknum;
//
//  if (gametick == lasttick)
//  {
//    lastletter+=1;
//  }
//  else
//  {
//    lastletter = 'a';
//    lasttick = gametick;
//  }
//
//  char buf[255];
//  sprintf(buf, "%06d-%c", gametick, lastletter);
}

void Engine::recordStop()
{
//  if (theRecord != 0)
//  {
//    theRecord->write();
//    delete theRecord;
//    theRecord = 0;
//  }
}
