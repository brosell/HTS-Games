#pragma warning (disable : 4786 4503 4530)

#include "DropDownList.h"
#include "BR_Game.h"
#include "SDL_rotozoom.h"

// FIXME: Font changes probalby screwed this up

DropDownList::DropDownList()
{
}

void DropDownList::onKeyPress(KeyPressEvent* event)
{
  int t = m_items.size();

  if (event->keySym == SDLK_LEFT && m_selectedItem > 0)
  {
    m_selectedItem--;
    updateItemListeners();
  }
  else if (event->keySym == SDLK_RIGHT && m_selectedItem < m_items.size() - 1)
  {
    m_selectedItem++;
    updateItemListeners();
  }
}

void DropDownList::onMouseClick(MouseClickEvent* event)
{
  FontHandle font = getFont();
  Rect r = getTranslatedPosition();

  int t = m_items.size();

  if (event->x < font->getTextWidth("<") && m_selectedItem > 0)
  {
    m_selectedItem--;
    updateItemListeners();
    // click left
  }
  else if (event->x > r.x + r.w - font->getTextWidth("<") && m_selectedItem < m_items.size() - 1)
  {
    m_selectedItem++;
    updateItemListeners();
  }
}


void DropDownList::paint(Display* surface)
{
  int t = m_items.size();

  FontHandle font = getFont();

  Rect r = getPosition();

  surface->fillRect(r.x, r.y, r.w, r.h, 127, 127, 127);

  if (!hasSelection())
  {
    if (m_items.size() > 0)
    {
      m_selectedItem = 0;
    }
  }

  if ( hasSelection() )
  {
    // draw the selected word
    // (clip the rect?)
    font->drawLine(surface, getSelectedString(), r.x + font->getTextWidth("<"), r.y);
  }
  if ( m_items.size() <= 1)
  {
    // draw two grey arrows
    // or none at all
  }
  else
  {
    if (m_selectedItem < m_items.size() -1 )
    {
      // draw grey left and reg right
      getFont()->drawLine(surface, ">", r.x + r.w - font->getTextWidth("<"), r.y);
    }
    if (m_selectedItem != 0)
    {
      getFont()->drawLine(surface, "<", r.x, r.y);
    }

  }
}