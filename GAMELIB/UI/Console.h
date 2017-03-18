#ifndef _Console_h
#define _Console_h

#include "UI.h"
#include <time.h>

#include <deque>
using std::deque;

class ConsoleLine
{
public:
  ConsoleLine(string s): line(s)
  {
    time = clock();
  }
  string line;
  clock_t time;
};

class Console: public DialogBox, public ConsoleListener, public KeyListener
{
public:
  Console();

  /**
    * when the console is not showing, we still want (in some cases)
    * to see the contents. This method will draw the last N lines to
    * the top of the screen
    */
  void drawWhileHidden(Surface* surface);
  
  /**
    * adds the line to the consoles buffer to be printed
    */
  void println(string s, ...); 

  /**
    * the console takes commands from the user. Use addCollback to
    * create a callback for a particular command
    */
  void addCallback(string cmd, ConsoleListener* d);
  
//  /**
//    * default callback for the help command.
//    * It list all the recognized commands
//    */
//  bool helpCallback(Message* event);
//  bool handleEvent(Message* event);

  virtual void consoleCommand(ConsoleEvent* event);
  virtual void onKeyPress(KeyPressEvent* event);

  virtual void show();
  virtual void hide();

  bool isShowing() { return m_showing; }

  void execute(string s, ...);
  
protected:
  void doCommand();

private:
  bool m_showing;

  bool m_previousMouseState;

  TextArea m_output;
  TextBox m_input;
  deque<ConsoleLine> m_lines;
  map<string, ConsoleListener*> m_listeners;

  int m_numVisibleLines; // when console is hidden
  int m_lineTime; // when console is hidden, how long to show each line. In milliseconds

  bool m_changed;
};

#endif