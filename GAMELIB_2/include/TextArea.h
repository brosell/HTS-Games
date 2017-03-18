#ifndef _TextArea_h
#define _TextArea_h

#include "UIThing.h"
#include "Font.h"

#include <list>
using namespace std;

class Surface;

class TextArea: public UIThing
{
public:
  TextArea();
  virtual string getName() { return "TextArea"; }

  virtual void paint(Display* surface);

  virtual bool acceptsFocus() { return false; }

  virtual void setPosition(Rect& pos) { setDirty(true); UIThing::setPosition(pos); }
  virtual void setText(const string& s) { setDirty(true); UIThing::setText(s); updateTextListeners(); }

  void appendText(const char* s) { setDirty(true); m_text+="\n"; m_text+=s; updateTextListeners(); }

  void setIndent(bool i) { setDirty(true); m_indent = i; }

  void addTextListener(TextListener* listener) { m_textListeners.insert(listener); }
  void removeTextListener(TextListener* listener) { m_textListeners.erase(listener); }

  int getVisibleLines();

protected:
  void updateTextListeners();
  void drawLines(Display* surface, list<string>& lines);
  void formatText();
private:
  set<TextListener*> m_textListeners;
  list<string> m_formattedLines;
  int m_margin;
  bool m_dirty;
  int m_topIndex;

  bool m_indent;

  TextChangeEvent m_textEvent;

};
#endif