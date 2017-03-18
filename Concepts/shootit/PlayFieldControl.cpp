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
    
    break;
  case SDLK_LALT:
    
    break;
  case SDLK_LEFT:
    break;
  case SDLK_RIGHT:
    break;
  case SDLK_DOWN:
    
    break;
  }
}

void PlayFieldControl::onMouseMove(MouseMoveEvent* event)
{

}

void PlayFieldControl::onMouseClick(MouseClickEvent* event)
{
  m_board->fire();
}