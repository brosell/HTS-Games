#pragma warning (disable : 4786 4530 4503)

#include <string>
using namespace std;

#include "BR_Game.h"
#include "CommandLineParser.h"
#include "Log.h"
#include "FileUtils.h"
#include "AM.h"

#include "TweakableDialogBox.h"

CommandLineParser g_clp;

string g_iniName = "";
string g_section = "";
IniFile* g_ini = 0;

bool g_run=true;

Console* g_console;

TweakableDialogBox* g_dialog = 0;

void testTweakableDialog();

struct MyConsoleListener: public ConsoleListener, public KeyListener
{
  MyConsoleListener()
  {
    theGame.uiSystem.addKeyListener(this);
    g_console->addCallback("quit", this);
  }

  virtual void consoleCommand(ConsoleEvent* event)
  {
    if (event->command == "quit")
    {
      g_run = false;
    }
  }

  virtual void keyPressed(KeyPressEvent* event)
  {
    switch(event->keySym)
    {
    case SDLK_BACKQUOTE:
//      if (g_console->isShowing())
//      {
//        g_console->hide();
//      }
//      else
//      {
//        g_console->show();
//      }
    
    case SDLK_ESCAPE:
      exit(0);
    }
  }

  void add(ConsoleEvent* event)
  {
    if (event->args.empty())
    {
      g_console->println("invalid command");
      return;
    }
    string type = event->args.front();
    event->args.pop_front();
  }

};

int main(int c, char** v)
{
  UIThing::s_ocheck = false;
  MaintLog::get().setFilter(All);

  g_clp.parse(c, v);

  if (!g_clp.getFlagArg("test"))
  {
    
    if (g_clp.countNames() != 2)
    {
      logError(Fatal, "Usage: DialogTweak inifile dialogname");
    }
    
    g_iniName = g_clp.getNextName();
    if (!fileExists(g_iniName))
    {
      logError(Fatal, "%s - file not found", g_iniName.c_str());
    }
    
    g_ini=new IniFile(g_iniName);
    g_ini->read();
    
    g_section = g_clp.getNextName();
    
    if(!g_ini->hasSection(g_section))
    {
      logError(Fatal, "%s exists but has no dialog named %s", g_iniName.c_str(), g_section.c_str());
    }
  }
    
  BR_Game::initialize(640, 480, 32, SDL, 0);

  IniFile assets("Assets.ini");
  assets.read();
  AM assetManager(assets);
  theGame.am = &assetManager;

  theGame.uiSystem.setMouseCursor("mouse_Default");
  theGame.uiSystem.setFont(theGame.am->getFont("fnt_Default"));
  theGame.showCursor(true);

//  if (g_clp.getFlagArg("test"))
//  {
//    testTweakableDialog();
//    return 0;
//  }


  g_console = new Console;
  MyConsoleListener listener;
  
  g_dialog = new TweakableDialogBox(*g_ini, g_section);

  g_dialog->show();

  while(g_run)
  {
    theGame.pump();
  }

  return 0;
}
