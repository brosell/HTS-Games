#ifndef ToggleButton_h
#define ToggleButton_h

#include "UI/Button.h"

class ToggleButton: public Button
{
public:
  ToggleButton();
  ~ToggleButton();
  virtual void paint(Display* surface);

  bool isChecked() { return m_isChecked; }
  void setChecked(bool c);

  virtual void onMouseClick(MouseClickEvent* event);

  void setOther(int id) { m_other = id; }
  int getOther() { return m_other; }

  void setCheckedTexture(string assetName);
  void setUncheckedTexture(string assetName);

private:
  void check() { m_isChecked = true; }
  void uncheck() { m_isChecked = false; }

  bool m_isChecked;
  Skin* m_unchecked;
  Skin* m_checked;

  /** id of the other in a radio button setup */
  int m_other;

//  HTexture m_unchecked;
//  HTexture m_checked;
//  string m_highlight;
};

#endif