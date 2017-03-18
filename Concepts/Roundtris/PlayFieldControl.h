#ifndef PlayFieldControl_h
#define PlayFieldControl_h

#include "UI.h"
#include "Board.h"

class PlayFieldControl: public UIThing, public MouseListener
{
public:
  PlayFieldControl();
  ~PlayFieldControl();

  virtual string getName() { return "PlayFieldControl"; }

  virtual void paint(Display* surface);

  virtual void onKeyPress(KeyPressEvent* event);
  virtual void onMouseMove(MouseMoveEvent* event);

private:
  // FIXME:
  // ptr to board so we can draw it
  
  Board* m_board;

};

#endif