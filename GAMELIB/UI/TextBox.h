#ifndef _TextBox_h
#define _TextBox_h

#include "UIThing.h"
#include "Graphics/Display.h"
#include <vector>
#include <sstream>

class TextBox: public UIThing
{
public:
  TextBox();

  void paint(Display* surface);

  virtual void onKeyPress(KeyPressEvent* event);

  void addTextListener(TextListener* listener) { m_textListeners.insert(listener); }
  void removeTextListener(TextListener* listener) { m_textListeners.erase(listener); }

  void setMaxSize(size_t m);
  size_t getMaxSize() { return m_maxSize; }

  virtual string getText()
  {
    return m_currentLine;
  }

  virtual string getName() { return "TextBox"; }

  virtual void setText(const string& s)
  {
    size_t numChars = hts::min<size_t>(s.size(), m_maxSize);
    m_currentLine = string(s.begin(), s.begin()+numChars);
    m_cursorPosition=m_currentLine.size();
    updateTextListeners();
  }

protected:
//  void drawLine(Surface* surface, string s, int x, int y);
  void updateTextListeners();

private:
  set<TextListener*> m_textListeners;
  TextChangeEvent m_textEvent;

   int m_maxSize;
  
  int m_topMargin;
  int m_bottomMargin;
  int m_leftMargin;
  int m_rightMargin;
 
  string m_currentLine; // the chars that make up the line being typed
  string::iterator m_iterAtCursor;
  string::iterator m_iterBeforeCursor;

  int m_cursorPosition;
  int m_physCursorPosition;
  
  void setIterAtCursor();
};



#endif