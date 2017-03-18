#pragma warning (disable : 4786 4503 4530)
#include "TextArea.h"
#include "Font.h"
#include "SDL_gfxPrimitives.h"
#include "StringTokenizer.h"

TextArea::TextArea(): 
UIThing(), 
m_margin(5),
m_dirty(true),
m_indent(true)
{ 
  m_textEvent.thing = this;
  updateTextListeners(); 
}

int TextArea::getVisibleLines()
{
  Font* font=getFont();
  Rect r=getPosition();
  return ((r.h - (m_margin + m_margin))/font->getFontHeight());
}


void TextArea::paint(Display* surface)
{

  if (m_dirty)
  {
    formatText();
  }

  m_topIndex = m_formattedLines.size() - getVisibleLines();
  //m_topIndex--;
  if (m_topIndex < 0) 
  {
    m_topIndex = 0;
  }

  Rect r=getTranslatedPosition();

  // uncomment to see the actual text space with regards to margins
//  surface->fillRect(r.x+m_margin, r.y+m_margin, r.w-(2*m_margin), r.h-(2*m_margin), 255, 255, 255, 255);

  int x2=r.x+r.w - 1;
  int y2=r.y+r.h - 1 ;

  list<string>::iterator i;

  int curIndex = 0;
  list<string> toBeDrawn;
  for (i = m_formattedLines.begin(); i!=m_formattedLines.end(); i++, curIndex++)
  {
    if (curIndex < m_topIndex)
    {
      continue;
    }
    toBeDrawn.push_front(*i);
  }
  drawLines(surface, toBeDrawn);

}

void TextArea::drawLines(Display* surface, list<string>& lines)
{
  int space = 0;
  Rect r=getPosition();
  Font* font = getFont(); //Font::getDefault();
  int y = m_margin + ((lines.size()-1) * font->getFontHeight()) + r.y;
  list<string>::iterator i;
  for (i=lines.begin(); i!=lines.end(); i++)
  {
    string line = (*i);
    font->drawLine(surface, (*i), m_margin + r.x, y);
    y-=font->getFontHeight();
  }
}

void TextArea::formatText()
{
  m_formattedLines.clear();
  Font* font=getFont();
  Rect r = getTranslatedPosition();
  StringTokenizer st(getText(), "\r\n");
  while (st.hasMoreTokens())
  {
    string toFormat = st.nextToken();
    StringTokenizer words(toFormat, " ");
    int textWidth = 0;
    string line = "";
    if (m_indent) line = " ";
    CStdString proposedLine;
    while(words.hasMoreTokens())
    {
      string word = words.nextToken();
      if (word == "<BR>")
      {
        m_formattedLines.push_back(line);
//        m_formattedLines.push_back("<BR>");
        if (m_indent) line = " ";
        else line = "";
        continue;
      }

      if (line.size() > 0)
      {
        proposedLine.Format("%s %s", line.c_str(), word.c_str());
      }
      else
      {
        proposedLine = word;
      }

      
      if (font->getTextWidth(proposedLine) > (r.w - (m_margin*2)))
      {
        m_formattedLines.push_back(line);
        line = "";
        if (m_indent) line = " ";
        line += word;
      }
      else
      {
        if (line.size() > 0)
          line+=" ";
        line+=word;
      }
    }
    m_formattedLines.push_back(line);
//    m_formattedLines.push_back("<BR>");
  }
  m_dirty = false;
}

void TextArea::updateTextListeners()
{
  m_textEvent.commandId = getId();
  set<TextListener*> setCopy(m_textListeners);
  set<TextListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->textChanged(&m_textEvent);
  }
}
