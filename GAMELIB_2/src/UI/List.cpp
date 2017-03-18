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
m_leftMargin(0),
m_selectedItem(-1),
m_topIndex(0),
m_allowScroll(true),
m_allowNoSelection(true)
{ 
  addUIThing(&m_scroll);
  m_scroll.addAdjustmentListener(this);
  isce.thing = this;
}

List::List(StringMap& attributes): 
Container(), 
m_margin(5),
m_leftMargin(0),
m_selectedItem(-1),
m_topIndex(0),
m_allowScroll(true),
m_allowNoSelection(true)
{ 
  addUIThing(&m_scroll);
  m_scroll.addAdjustmentListener(this);
  isce.thing = this;

  if (attributes["Margin"] != "")
  {
    m_margin = atoi(attributes["Margin"].c_str());
  }
  m_leftMargin = atoi(attributes["LeftMargin"].c_str());
  
  string asset;

  

  asset = attributes["HighlightFont"];
  if (asset != "")
  {
    m_highlightFont = theGame.am->getFont(asset);
  }

  asset = attributes["Highlight"];
  if (asset != "")
  {
    m_highlight = theGame.am->getSkin(asset);
  }

//  asset = attributes["HighlightColor"];
//  if (asset != "")
//  {

}


List::~List()
{
}


void List::paint(Display* surface)
{
  if (m_under == 0 && s_smartDraw)
  {
    saveUnder(surface);
  }
  
  int highBound = m_items.size() - getVisibleLines();
  if (highBound < 0)
    highBound = 0;
  m_scroll.setBounds(0, highBound);
    

  Rect r=getTranslatedPosition();
  if (m_allowScroll)
  {
    r.w -= 12; // scroll bar
  }
  FontHandle font = getFont();
  if (font.isValid())
  {
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
      
      if (cur != m_selectedItem)
      {
        font->drawLine(surface, (*i).str, (m_margin + m_leftMargin + r.x), y);
      }
      
      else //if (cur == m_selectedItem) // && isMouseOver())
      {
        if (m_highlightFont.isValid())
        {
          m_highlightFont->drawLine(surface, (*i).str, (m_margin + m_leftMargin + r.x), y);
        }
        if (m_highlight.isValid())
        {
          m_highlight->blit(surface, m_margin + r.x, y, false);
        }
        else
        {
          surface->fillRect(r.x, y, r.w, font->getFontHeight(), 255, 255, 255, 127);
        }
      }
      y+=font->getFontHeight();
    }
  }
  else
  {
    err_NoFont();
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
      setDirty(true);
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
      setDirty(true);
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
  int oldSel = m_selectedItem;
  FontHandle font = getFont();
  if (font.isValid())
  {
    if (event->button == 1)
    {
      setDirty(true);
      Rect r = getPosition();
      int x = event->x;
      Rect sr = m_scroll.getTranslatedPosition();
      if (!sr.containsPoint(Point(event->x, event->y)))
      {
        int y = event->y - r.y - m_parent->getPosition().y - 5;
        int listPos = y / font->getFontHeight();
        
        if (listPos > getVisibleLines() - 1)
        {
          if (m_allowNoSelection == true)
          {
            m_selectedItem = -1;
          }
        }
        else
        {
          if (m_topIndex+listPos < countItems())
          {
            m_selectedItem = m_topIndex + listPos;
          }
        }
        
      }
    }
  }
  else
  {
    err_NoFont();
  }
  if (oldSel != m_selectedItem)
  {
    updateItemListeners();
  }

  Container::onMouseClick(event);
}

void List::addItem(int id, string item) 
{ 
  m_items.push_back(ListItem(id, item)); 
  setDirty(true);
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
  setDirty(true);
}

void List::clear()
{
  m_items.clear();
  m_selectedItem = 0;
  m_topIndex = 0;
  m_scroll.setBounds(0, m_items.size());
  updateItemListeners();
  setDirty(true);
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
  setDirty(true);
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