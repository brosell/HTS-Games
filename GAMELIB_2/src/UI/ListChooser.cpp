#pragma warning (disable : 4786 4530 4503)
#include "ListChooser.h"

void ListChooser::init()
{
  setBackgroundColor(127, 127, 127, 255);
  m_list = new List;
  m_list->setControlName("TheList");
  addUIThing(m_list);
  m_list->setMargin(0);
  m_list->allowScroll(false);
}

string ListChooser::getChoice()
{
  string ret = m_list->getSelectedString();
  if (ret == "")
  {
    ret = "None";
  }
  return ret;
}

int ListChooser::popUp(int x, int y, bool testOnly)
{
  int maxX = theGame.screen->getWidth() - myWidth();
  int maxY = theGame.screen->getHeight() - myHeight();

  if (x > maxX) x = maxX;
  if (y > maxY) y = maxY;

  Rect pos(x, y, getItemsWidth() + (2*m_margin), getItemsHeight() + (2*m_margin));
  setPosition(pos);

  Rect lpos(m_margin, m_margin, getItemsWidth(), getItemsHeight());
  m_list->setPosition(lpos);
  
  // will change to doModel
  if (!testOnly)
  {
    return doModal();
  }

  show();
  return 0;
}

void ListChooser::onMouseMove(MouseMoveEvent* event)
{
  Rect lpos = m_list->getTranslatedPosition();
  if (lpos.containsPoint(Point(event->x, event->y)))
  {
    MouseClickEvent click;
    click.button = LEFT_BUTTON;
    click.x = event->x;
    click.y = event->y;
    m_list->onMouseClick(&click);
  }
  DialogBox::onMouseMove(event);
}

void ListChooser::onMouseClick(MouseClickEvent* event)
{
  Rect lpos = m_list->getTranslatedPosition();
  if (lpos.containsPoint(Point(event->x, event->y)))
  {
    m_list->onMouseClick(event);
    if (m_list->hasSelection())
    {
      terminateModal(m_list->getSelectedId());
    }
  }
}

void ListChooser::onKeyPress(KeyPressEvent* event)
{
  if (event->keySym == SDLK_ESCAPE)
  {
    terminateModal(-1);
  }
}