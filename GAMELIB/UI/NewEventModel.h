#ifndef NewEventModel_h
#define NewEventModel_h

#include "Event.h"

class UIThing;
#include <string>
#include <list>
using std::string;
using std::list;

class UIEvent: public Event
{
public:
  UIThing* thing;
  int commandId; // some components will set this.
  unsigned short metaKeyState; // alt, ctrl, shift
};

class AppListener
{
public:
  virtual void appGainedFocus() { }
  virtual void appLostFocus() { }
  virtual void appQuitRequest() { }
};

//////////////////////////
//// MOUSE ///////////////
//////////////////////////
class MouseEvent: public UIEvent
{
public:
  int x;
  int y;
};

class MouseMoveEvent: public MouseEvent
{
public:
  int relx;
  int rely;
};

class MouseButtonEvent: public MouseEvent
{
public:
  int button;
};

class MouseClickEvent: public MouseButtonEvent
{ /* empty */ };

class MouseDblClickEvent: public MouseButtonEvent
{ /* empty */ };

class MousePressEvent: public MouseButtonEvent
{ /* empty */ };

class MouseReleaseEvent: public MouseButtonEvent
{ /* empty */ };

class MouseEnterEvent: public MouseEvent
{ /* empty */ };

class MouseExitEvent: public MouseEvent
{ /* empty */ };

class MouseDragEvent: public MouseEvent
{ /* empty */ };

class MouseListener
{
public:
  virtual void mouseMoved(MouseMoveEvent*) { }
  virtual void mouseClicked(MouseClickEvent*) { }
  virtual void mouseDblClicked(MouseDblClickEvent*) { }
  virtual void mousePressed(MousePressEvent*) { }
  virtual void mouseReleased(MouseReleaseEvent*) { }
  virtual void mouseEntered(MouseEnterEvent*) { }
  virtual void mouseExited(MouseExitEvent*) { }
  virtual void mouseDragged(MouseDragEvent*) { }
};


//////////////////////////
//// KEY /////////////////
//////////////////////////

class KeyEvent: public UIEvent
{
public:
  unsigned short keySym;
  unsigned short real;
};

class KeyPressEvent: public KeyEvent
{ /* empty */ };

class KeyReleaseEvent: public KeyEvent
{ /* empty */ };

class KeyRepeatEvent: public KeyEvent
{ /* empty */ };


class KeyListener
{
public:
  virtual void keyPressed(KeyPressEvent*) { }
  virtual void keyReleased(KeyReleaseEvent*) { }
  virtual void keyRepeated(KeyRepeatEvent*) { }
};


//////////////////////////
//// COMPONENT ///////////
//////////////////////////

// TextBox, TextArea
class TextChangeEvent: public UIEvent
{  /* empty */ };

class TextListener
{
public:
  virtual void textChanged(TextChangeEvent*) { }
};

// List(s)
class ItemStateChangeEvent: public UIEvent
{
public:
  int item;
 /* something more needs to happen */
};

class ItemListener
{
public:
  virtual void itemStateChanged(ItemStateChangeEvent*) { }
};

// Buttons
class ActionEvent: public UIEvent
{ /* empty */ };

class ActionListener
{
public:
  virtual void actionPerformed(ActionEvent*) { }
};

// Console
class ConsoleEvent: public UIEvent
{
public:
  string command;
  list<string> args;
};

class ConsoleListener
{
public:
  virtual void consoleCommand(ConsoleEvent* event) { }
};

// Scrollbar
class AdjustmentEvent: public UIEvent
{
public:
  enum AdjustmentType
  {
    ADJUSTMENT_FIRST,
    ADJUSTMENT_LAST,
    ADJUSTMENT_VALUE_CHANGED,
    BLOCK_DECREMENT,
    BLOCK_INCREMENT,
    TRACK,
    UNIT_DECRIMENT,
    UNIT_INCREMENT
  };

  AdjustmentType adjustmentType;
  int value;
};

class AdjustmentListener
{
public:
  virtual void adjustmentValueChanged(AdjustmentEvent*) { }
};


#endif