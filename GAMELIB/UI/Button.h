#ifndef _Button_h
#define _Button_h

#include "UIThing.h"
#include "Graphics/Display.h"

#include "Graphics/SharedSkin.h"

/**
a GUI button
*/
class Button: public UIThing
{
public:
  Button();
  virtual ~Button();

  virtual string getName() { return "Button"; }

  /** Skin for unpressed button */
  void setUpTexture(string assetName);
  /** Skin for pressed button */
  void setDownTexture(string assetName);
  /** Skin for button with focus*/
  void setFocusTexture(string assetName);
  /** Skin for mouseovered button */
  void setOverTexture(string assetName);

  void setLink(string link) { m_link = link; }

  void addActionListener(ActionListener* listener) { m_actionListeners.insert(listener); }
  void removeActionListener(ActionListener* listener) { m_actionListeners.erase(listener); }

  virtual void onMousePress(MousePressEvent* event);
  virtual void onMouseRelease(MouseReleaseEvent* event);
  virtual void onMouseClick(MouseClickEvent* event);

  virtual void onMouseExit(MouseExitEvent* event);

  void paint(Display* surface);

protected:

private:
  bool m_isDown;

  set<ActionListener*> m_actionListeners;
  ActionEvent m_actionEvent;

  string m_link;
  
  Skin* m_buttonUp;
  Skin* m_buttonDown;
  Skin* m_buttonFocus;
  Skin* m_buttonOver;
};

#endif