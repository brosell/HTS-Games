#include "BR_Game.h"
#include "Console.h"
#include "StringTokenizer.h"

Console::Console(): 
DialogBox("skn_ConsoleBackground"), 
m_lineTime(3),
m_numVisibleLines(3),
m_changed(true),
m_showing(false)
{ 
  setPosition(Rect(0, 0, 640, 480));
  addCallback("help", this);
//  addCallback("hide", this);

  m_output.setPosition(Rect(0, 0, 640, 450));
  m_input.setPosition(Rect(0, 451, 639, 29));

  m_input.addKeyListener(this);
  
  addUIThing(&m_output);
  addUIThing(&m_input);
  setFocus(&m_input);
}

void Console::onKeyPress(KeyPressEvent* event)
{
  if (/*event->thing == &m_input &&*/ event->keySym == 13)
  {
    doCommand();
  }
  else if (event->keySym != SDLK_BACKQUOTE)
  {
    DialogBox::onKeyPress(event);
  }
}

void Console::execute(string s, ...)
{
  va_list vl;
  va_start( vl, s );
  char buf[1024];

  vsprintf(buf, s.c_str(), vl);
  va_end( vl );

  m_input.setText(buf);
  doCommand();
}

void Console::doCommand()
{
  ConsoleEvent cc;
  cc.thing = this;
  cc.commandId = getId();

  ConsoleListener* listener = 0;
      
  string s=m_input.getText();
  m_input.setText("");

  StringTokenizer st(s.c_str());
  if (st.countTokens() >0 )
  {
    cc.command = st.nextToken();
  }
  else
  {
    // blank line?
    return;
  }

  map<string, ConsoleListener*>::iterator pair = m_listeners.find(cc.command);
  if (pair != m_listeners.end())
  {
    listener = pair->second;
  }
  else
  {
    string errMsg="no command delegate for ";
    errMsg+=cc.command;
    println(errMsg);
    return;
  }
  
  while (st.hasMoreTokens())
  {
    string arg = st.nextToken();
    cc.args.push_back(arg);
  }

  listener->consoleCommand(&cc);
}


void Console::drawWhileHidden(Surface* surface)
{
}

void Console::println(string s, ...)
{
  va_list vl;
  va_start( vl, s );
  char buf[1024];

  vsprintf(buf, s.c_str(), vl);
  va_end( vl );

  m_changed=true;
  m_lines.push_front(ConsoleLine(buf));
  int lines=m_output.getVisibleLines();
  string str="";
  deque<ConsoleLine>::iterator i=m_lines.begin();
  for (int c=0; c<lines && i!=m_lines.end(); c++, i++)
  {
    string g=str;
    str=(*i).line;
    str+="\r\n";
    str+=g;
  }


  m_output.setText(str.c_str());

}

void Console::addCallback(string cmd, ConsoleListener* listener)
{
  m_listeners[cmd]=listener;
}

void Console::consoleCommand(ConsoleEvent* cc)
{
  if (cc->command == "hide")
  {
    hide();
  }
  else if (cc->command == "help")
  {
    println("Available commands:");
    map<string, ConsoleListener*>::iterator pair;
    for (pair=m_listeners.begin(); pair!=m_listeners.end(); pair++)
    {
      println(pair->first);
    }
  }
}

void Console::show()
{
  DialogBox::show();
  m_previousMouseState = theGame.showCursor(true);
  setFocus(&m_input);
  m_showing = true;
}

void Console::hide()
{
  theGame.showCursor(m_previousMouseState);
  DialogBox::hide();
  m_showing = false;
}
