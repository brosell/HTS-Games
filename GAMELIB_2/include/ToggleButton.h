#ifndef ToggleButton_h
#define ToggleButton_h

#include "Button.h"


class ToggleButton: public Button
{
public:
  ToggleButton();
  ToggleButton(StringMap& attributes);
  ~ToggleButton();
  virtual void paint(Display* surface);

  bool isChecked() { return m_isChecked; }
  void setChecked(bool c);

  virtual void onMouseClick(MouseClickEvent* event);

  void setOther(int id) { m_other = id; }
  int getOther() { return m_other; }

  void setCheckedTexture(string assetName);
  void setUncheckedTexture(string assetName);
  void setDisabledTexture(string assetName);

private:
  void check() { m_isChecked = true; }
  void uncheck() { m_isChecked = false; }

  bool m_isChecked;
  SharedSkinHandle m_unchecked;
  SharedSkinHandle m_checked;
  SharedSkinHandle m_disabled;

  /** id of the other in a radio button setup */
  int m_other;

};


#endif