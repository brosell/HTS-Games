#ifndef HighlightButton_h
#define HighlightButton_h

#include "Button.h"

class HighlightButton: public Button
{
public:
  HighlightButton();
  ~HighlightButton();
  void setHighlight(string filename) { m_highlight = filename; }
  virtual void paint(Display* surface);

protected:
  void createHighlight();

private:
  HTexture m_glass;
  string m_highlight;
};

#endif