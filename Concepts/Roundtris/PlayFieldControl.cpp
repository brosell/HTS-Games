#pragma warning (disable : 4503 4530 4786)
#include "PlayFieldControl.h"
#include "Globals.h"

extern Globals* globals;

PlayFieldControl::PlayFieldControl():
UIThing()
{
  m_board = new Board;
}

PlayFieldControl::~PlayFieldControl()
{
  delete m_board;
}


void PlayFieldControl::paint(Display* display)
{
  m_board->draw(display);
}

void PlayFieldControl::onKeyPress(KeyPressEvent* event)
{
  switch(event->keySym)
  {
  case SDLK_UP:
  case SDLK_LCTRL:
    m_board->rotateShapeLeft();
    break;
  case SDLK_LALT:
    m_board->rotateShapeRight();
    break;
  case SDLK_LEFT:
    m_board->moveShapeLeft();
    break;
  case SDLK_RIGHT:
    m_board->moveShapeRight();
    break;
  case SDLK_DOWN:
    m_board->moveShapeDown();
    break;
  }
}

void PlayFieldControl::onMouseMove(MouseMoveEvent* event)
{
//  m_board->chaseMouse(Point(event->x, event->y));
}
