#pragma warning (disable: 4786 4530 4503)

#include "List.h"
#include "Font.h"
#include "SDL_gfxPrimitives.h"
#include "StringTokenizer.h"
#include "BR_Game.h"
#include "SDL_rotozoom.h"

#include "Utils.h"

#include <stdlib.h>

List::List(): 
Container(), 
m_margin(5),
m_selectedItem(-1),
m_topIndex(0),
m_allowScroll(true)
{ 
  addUIThing(&m_scroll);
  m_scroll.addAdjustmentListener(this);
  isce.thing = this;
}

List::~List()
{
}


void List::paint(Display* surface)
{
  int highBound = m_items.size() - getVisibleLines();
  if (highBound < 0)
    highBound = 0;
  m_scroll.setBounds(0, highBound);
    

  Rect r=getTranslatedPosition();
  if (m_allowScroll)
  {
    r.w -= 12; // scroll bar
  }
  Font* font = getFont();
  int y=r.y + m_margin;// + ((m_items.size()-1) * font->getHeight()) + r.y;
  vector<ListItem>::iterator i;
  int cur=0;
  for (i=m_items.begin(); i!=m_items.end(); i++, cur++)
  {
    if (cur < m_topIndex)
    {
      continue;
    }
    if (cur >= m_topIndex + getVisibleLines())
    {
      break;
    }

    font->drawLine(surface, (*i).str, m_margin + r.x, y);
        
    if (cur == m_selectedItem && isMouseOver())
    {
      surface->fillRect(r.x, y, r.w, font->getFontHeight(), 255, 255, 255, 127);
    }
    y+=font->getFontHeight();
  }

  if (m_allowScroll)
  {
    m_scroll.paint(surface);
  }
}

void List::adjustmentValueChanged(AdjustmentEvent* event)
{
  lassert(event->thing == &m_scroll);
  m_topIndex = event->value;
}

void List::onKeyPress(KeyPressEvent* event)
{
  if (event->keySym == SDLK_UP)
  {
    if (m_selectedItem > 0)
    {
      m_selectedItem--;
      updateItemListeners();
      if(m_selectedItem < m_topIndex)
      {
        m_topIndex--;
      }
    }
  }
  else if (event->keySym == SDLK_DOWN)
  {
    if (m_selectedItem < m_items.size() -1 )
    {
      m_selectedItem++;
      updateItemListeners();
      if (m_selectedItem > m_topIndex + hts::min(getVisibleLines()-1, (int)m_items.size()))
      {
        m_topIndex++;
      }
    }
  }
  Container::onKeyPress(event);
}

void List::onMouseClick(MouseClickEvent *event)
{
  if (event->button == 1)
  {
    Rect r = getPosition();
    int x = event->x;
    Rect sr = m_scroll.getTranslatedPosition();
    if (!sr.containsPoint(Point(event->x, event->y)))
    {
      int y = event->y - r.y - m_parent->getPosition().y - 5;
      int listPos = y/Font::getDefault()->getFontHeight();
      
      if (listPos > getVisibleLines() - 1)
      {
        m_selectedItem = -1;
      }
      else
      {
        m_selectedItem = m_topIndex + listPos;
      }
      updateItemListeners();
    }
  }
  Container::onMouseClick(event);
}

void List::addItem(int id, string item) 
{ 
  m_items.push_back(ListItem(id, item)); 
}

void List::removeItem(int id)
{
  vector<ListItem>::iterator i;
  for (i=m_items.begin(); i!=m_items.end(); i++)
  {
    if ((*i).id == id)
    {
      m_items.erase(i);
      if (m_selectedItem > m_items.size())
      {
        m_selectedItem = m_items.size() - 1;
        updateItemListeners();
      }
      if (m_topIndex > m_items.size())
      {
        m_topIndex = m_items.size() - 1;
      }
      m_scroll.setBounds(0, m_items.size());
      return;
    }
  }
}

void List::clear()
{
  m_items.clear();
  m_selectedItem = 0;
  m_topIndex = 0;
  m_scroll.setBounds(0, m_items.size());
  updateItemListeners();
}

void List::setSelected(int pos)
{
  lassert(pos < m_items.size());
  lassert(pos >= 0);

  m_selectedItem = pos;
  if (m_topIndex > m_selectedItem)
  {
    m_topIndex = m_selectedItem;
  }
  if (m_selectedItem > m_topIndex + getVisibleLines() - 1)
  {
    m_topIndex = m_selectedItem - getVisibleLines() - 1;
  }
  updateItemListeners();
}

bool List::hasSelection()
{
  if (m_items.size() == 0)
  {
    return false;
  }
  if (m_selectedItem == -1)
  {
    return false;
  }
  return true;
}

int List::getSelectedId()
{
  lassert(m_items.size() > 0);
  lassert(m_selectedItem < m_items.size());

  return m_items.at(m_selectedItem).id;
}

string List::getSelectedString()
{
  lassert(m_items.size() > 0);
  lassert(m_selectedItem < m_items.size());

  if (m_selectedItem < 0)
  {
    return "";
  }
  return m_items.at(m_selectedItem).str;
}

void List::updateItemListeners()
{
  isce.commandId = getId();
  isce.item = m_selectedItem;
  
  set<ItemListener*> setCopy(m_itemListeners);
  set<ItemListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->itemStateChanged(&isce);
  }
}