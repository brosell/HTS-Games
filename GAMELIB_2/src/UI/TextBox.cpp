#pragma warning (disable : 4786 4503 4530)
#include "BR_Game.h"
#include "TextBox.h"
#include "Font.h"
#include "Keyboard-utils.h"

#include "SDL_gfxPrimitives.h"

#include <algorithm>

#include "Log.h"

TextBox::TextBox():
UIThing(),
m_cursorPosition(0),
m_physCursorPosition(0),
m_leftMargin(5),
m_rightMargin(5),
m_topMargin(5),
m_bottomMargin(5),
m_maxSize(-1)
{
  m_textEvent.thing = this;
}

void TextBox::setIterAtCursor()
{
  m_iterBeforeCursor = m_currentLine.begin();
  for(int c=0; c<m_cursorPosition-1; c++)
  {
    m_iterBeforeCursor++;
  }
  m_iterAtCursor = m_iterBeforeCursor;
  if (m_iterAtCursor != m_currentLine.end())
  {
    m_iterAtCursor++;
  }
}

void TextBox::paint(Display* surface)
{
  int c = 0;
  string text = getText();  
  FontHandle font=getFont();
  Rect r=getTranslatedPosition();

  surface->pushClipRect(r);

  int usablePixels = r.w - (m_leftMargin - m_rightMargin);
  int stringPixels = font->getTextWidth(text);
  
  char* buf = new char[m_cursorPosition + 1];
  memset(buf, 0, m_cursorPosition + 1);
  for (c=0; c<m_cursorPosition; c++)
  {
    buf[c] = getText().at(c);
  }

  int cursorPixelLocation = font->getTextWidth(buf) + font->getTextWidth(" ") + r.x;
  
  // draw the text
  Point textLocation(r.x+m_leftMargin, r.y+m_topMargin);
  // case 1: the text fits
  if (stringPixels <= usablePixels)
  {
    // just draw it
    font->drawLine(surface, text, textLocation.x, textLocation.y);
  }
  else if (cursorPixelLocation < usablePixels)
  {
    // just draw it letting the clip rect clip it
    font->drawLine(surface, text, textLocation.x, textLocation.y);
  }
  else
  {
    for (c=0; c<m_cursorPosition; c++)
    {
      if (font->getTextWidth(&buf[c]) < usablePixels)
      {
        cursorPixelLocation = font->drawLine(surface, &buf[c], textLocation.x, textLocation.y);
        break;
      }
    }
  }

  // if focus, draw the cursor
  if (this->hasFocus())
  {
    surface->drawVLine(cursorPixelLocation, textLocation.y, font->getFontHeight(), 127, 127, 127);
  }

  delete [] buf;

  surface->popClipRect();
}


void TextBox::onKeyPress(KeyPressEvent* ke)
{
  setDirty(true);
  UIThing::onKeyPress(ke);
  lassert(this->hasFocus());
  setIterAtCursor();
  bool shifted=false;
  lassert(m_cursorPosition <= m_currentLine.size());

  switch(ke->keySym)
  {
  case SDLK_LEFT:
    {
      if (m_cursorPosition != 0)
      {
        m_cursorPosition--;
      }
    }
    break;
  case SDLK_RIGHT:
    {
      if (m_cursorPosition < m_currentLine.size())
      {
        m_cursorPosition++;
      }
    }
    break;
  case SDLK_DELETE:
    {
      if(m_cursorPosition != m_currentLine.size() && m_currentLine.size() > 0)
      {
        m_currentLine.erase(m_iterBeforeCursor);
      }
    }
    break;
  case SDLK_BACKSPACE:
    {
      if (m_cursorPosition != 0)
      {
        m_currentLine.erase(m_iterBeforeCursor);
        m_cursorPosition--;
      }
    }
    break;
  case SDLK_HOME:
    {
      m_cursorPosition = 0;
    }
    break;
  case SDLK_END:
    {
      m_cursorPosition = m_currentLine.size();
    }
    break;
  default:
    {
      if (m_currentLine.size() >= m_maxSize)
      {
        return;
      }
      if (theGame.isKey(SDLK_RSHIFT) || theGame.isKey(SDLK_LSHIFT))
      {
        shifted=true;
      }
      
      if (ke->keySym >= 0x20 && ke->keySym <=0x7E)
      {
        char key=ke->keySym;
        if (shifted) key=upperof(key);
        
        m_currentLine.insert(m_iterAtCursor, key);
        m_cursorPosition++;
        updateTextListeners();
      }
    }
    break;
  }
}

void TextBox::updateTextListeners()
{
  m_textEvent.commandId = getId();
  
  set<TextListener*> setCopy(m_textListeners);
  set<TextListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->textChanged(&m_textEvent);
  }

}

void TextBox::setMaxSize(size_t m) 
{ 
  m_maxSize = m; 
  if (m_maxSize < m_currentLine.size())
  {
    string t(m_currentLine.begin(), m_currentLine.begin()+m_maxSize);
    swap(m_currentLine, t);
    m_cursorPosition=hts::min(m_cursorPosition, m_maxSize);
    setDirty(true);
  }
}


