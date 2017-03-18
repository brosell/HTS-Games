#include "BR_Game.h"
#include "Event.h"
#include "Console.h"
#include "ConsoleCommand.h"


void initConsoleCommands()
{
//  static NonTypeDelegate surfaceCommandDel(surfaceCommand);
//  theGame.console->addCallback("surface", &surfaceCommandDel);

//  static NonTypeDelegate uithingCommandDel(UIThing::doConsoleCommand);
//  theGame.console->addCallback("uithing", &uithingCommandDel);
//
//  static NonTypeDelegate buttonCommandDel(buttonCommand);
//  theGame.console->addCallback("button", &buttonCommandDel);

}

//bool buttonCommand(Event* evt)
//{
//  ConsoleCommand* cc=(ConsoleCommand*) evt;
//
//  if (cc->args.size() == 0)
//  {
//    theGame.console->println("button [use_pc[+|-] | ?]");
//    return true;
//  }
//
//  string arg1=*(cc->args.begin());
//  if (arg1 == "?")
//  {
//    theGame.console->println("-");
//    theGame.console->println("button use_pc+ - buttons to use pre rendered surfaces");
//    theGame.console->println("button use_pc- - buttons to draw surfaces as it goes");
//    theGame.console->println("button ? - show this");
//    theGame.console->println("-");
//    return true;
//  }
//
//  if (arg1 == "use_pc+")
//  {
//    theGame.console->println("Enabling pre rendered surfaces for buttons");
//    Button::s_usePreCreated = true;
//  }
//  else if (arg1 == "use_pc-")
//  {
//    theGame.console->println("Disabling pre rendered surfaces for buttons");
//    Button::s_usePreCreated = false;
//  }
//  else
//  {
//    theGame.console->println("uh..");
//  }
//
//  return true;
//}


//bool surfaceCommand(Event* evt)
//{
//  ConsoleCommand* cc=(ConsoleCommand*) evt;
//  char buf[255];
//  if (cc->args.size() == 0)
//  {
//    theGame.console->println("surface [hw | ?]");
//    return true;
//  }
//
//  string arg1=*(cc->args.begin());
//  if (arg1 == "?")
//  {
//    theGame.console->println("-");
//    theGame.console->println("surface hw - show if surfaces are Hardware based");
//    theGame.console->println("surface ? - show this");
//    theGame.console->println("-");
//    return true;
//  }
//
//  if (arg1 == "hw")
//  {
//    set<Surface*>::iterator i;
//    theGame.console->println("-");
//    theGame.console->println("Begin Surface Dump");
//    for (i=Surface::s_surfaces.begin(); i!=Surface::s_surfaces.end(); i++)
//    {
//      Surface* surface=(*i);
//      sprintf(buf, "ptr: %x (\"%s\") %sware", surface->getSDLSurface(), surface->getName().c_str(), (const char*)(surface->isHardware()?"Hard":"Soft"));
//      theGame.console->println(buf);
//    }
//    theGame.console->println("End Surface Dump");
//    theGame.console->println("-");
//    return true;
//  }
//
//  if (arg1 == "blit+")
//  {
//    theGame.console->println("-");
//    theGame.console->println("Enabling blit list");
//    theGame.console->println("-");
//    Surface::s_recordBlits = true;
//    return true;
//  }
//
//  if (arg1 == "blit-")
//  {
//    theGame.console->println("-");
//    theGame.console->println("Disabling and clearing blit list");
//    theGame.console->println("-");
//    Surface::s_recordBlits = false;
//    Surface::s_blits.clear();
//    return true;
//  }
//
//  if (arg1 == "blits")
//  {
//    list<string>::iterator i;
//    theGame.console->println("-");
//    theGame.console->println("begin blit dump");
//    for (i=Surface::s_blits.begin(); i!=Surface::s_blits.end(); i++)
//    {
//      theGame.console->println(*i);
//    }
//    theGame.console->println("end blit dump");
//    theGame.console->println("-");
//    return true;
//  }
//
//  theGame.console->println("Unrecognized surface command");
//
//  return true;
//}
//

