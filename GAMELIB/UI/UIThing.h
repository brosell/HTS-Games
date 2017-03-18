#ifndef _UIThing_h
#define _UIThing_h

#include "UI/NewEventModel.h"
#include "Graphics/Display.h"
#include "Graphics/SharedSkin.h"
#include "UI/Font.h"

#include "MouseCursor.h"

class SoundEffect;

#include "Misc/GameMath.h"
#include <string>
#include <list>
#include <set>
#include <iostream>
using namespace std;

class Container;

class UIThing
{
public:
  UIThing();
  virtual ~UIThing();

  /**
  override this to give your control a usefull name string
  */
  virtual string getName() { return "UITHing"; }

  /**
  this sets the name dynamicly. The IniBasedDialog calls this
  with the name of the control from the ini file
  */
  void setControlName(string name) { m_controlName = name; }
  string getControlName() { return m_controlName; }

  void setId(int id) { m_id = id; }
  int getId() { return m_id; }

  virtual bool isContainer() { return false; }

  virtual void setText(const string& s) { m_text=s;}
  virtual string getText() {return m_text; }
  
  Container* getParent() { return m_parent; }
  void setParent(Container* parent) { m_parent = parent; }

  bool isMouseOver() { return s_mouseOver == this; }

  /**
    * causes the UIThing to be drawn to the screen by calling paint(surface)
    * it will first check to see if this is obscured.
    */
  void draw(Display* surface);

  void setBackgroundColor(int r, int g, int b, int a)
  {
    m_red = r;
    m_green = g;
    m_blue = b;
    m_alpha = a;
  }

  void setMouseCursor(string asset);
  virtual MouseCursor* getMouseCursor();

  void drawMouseCursor(Display* surface);

  /**
    * pure virtual function that will draw the UIThing to the screen when overridded
    */
  virtual void paint(Display* surface) = 0;

  /**
    * add this to its parent container (or the UISystem if no parent)
    */
  virtual void show();
  /**
    * removes from parent container (or the UISystem if no parent)
    */
  virtual void hide();

  /**
    * used to set and to determin current visiblity.
    * UIThings that are not visible will not get drawn
    * or receive events
    */
  bool isVisible() { return m_visible; }
  void setVisible(bool v) { m_visible = v; }

  /**
    * determines whether the UIThing is totaly obscured
    * by other UIThings.
    */
  virtual bool isObscured();
  virtual bool isObscuredBy(UIThing* thing);
  

  
  // FOCUS STUFF
  virtual bool hasFocus() { return m_haveFocus; }
  virtual void takeFocus() { m_haveFocus = true; }
  virtual void loseFocus() { m_haveFocus = false; }
  virtual bool acceptsFocus() { return true; }
  // END FOCUS STUFF
  
  
  
  /**
  * the position relative to the parent container
  */
  virtual void setPosition(Rect& pos) { m_position = pos; }
  Rect getPosition() { return m_position; }
  
  /**
  * converts the relative position of this control
  * to screen position
  * 
  * @return a Rect with the screen position
  */
  Rect getTranslatedPosition();
  
  
  void addMouseListener(MouseListener* listener) { m_mouseListeners.insert(listener); }
  void removeMouseListener(MouseListener* listener) { m_mouseListeners.erase(listener); }
  void addKeyListener(KeyListener* listener) { m_keyListeners.insert(listener); }
  void removeKeyListener(KeyListener* listener) { m_keyListeners.erase(listener); }
  
  
  /** 
  * Many event handlers to be overridden.
  */
  
  virtual void onMousePress(MousePressEvent* event);
  virtual void onMouseRelease(MouseReleaseEvent* event);
  
  virtual void onMouseClick(MouseClickEvent* event);
  virtual void onMouseDblClick(MouseDblClickEvent* event);
  virtual void onMouseMove(MouseMoveEvent* event);
  virtual void onMouseEnter(MouseEnterEvent* event);
  
  virtual void onMouseExit(MouseExitEvent* event);
  virtual void onKeyPress(KeyPressEvent* event);
  
  virtual void onKeyRelease(KeyReleaseEvent* event);
  
  void setFont(Font* font) { m_font = font; }
  virtual Font* getFont(); // { return m_font; }

  static bool s_ocheck;

protected:
  string m_controlName;
  bool m_haveFocus;

  string m_text;

  Font* m_font;

  Rect m_position;
  Container* m_parent;
private:
  bool m_visible;
  int m_id;

  int m_red;
  int m_green;
  int m_blue;
  int m_alpha;

  set<MouseListener*> m_mouseListeners;
  set<KeyListener*> m_keyListeners;

  bool m_haveMouse;

  

  SoundEffect* m_snd_onMousePress;
  SoundEffect* m_snd_onMouseRelease;
  SoundEffect* m_snd_onMouseClick;
  SoundEffect* m_snd_onMouseDblClick;
  SoundEffect* m_snd_onMouseMove;
  SoundEffect* m_snd_onMouseEnter;
  SoundEffect* m_snd_onMouseExit;
  
  SoundEffect* m_snd_onKeyPress;
  SoundEffect* m_snd_onKeyRelease;

  SoundEffect* m_snd_mouseOver;
  bool m_snd_mouseOverLoop;

public:
  void setOnMousePressSFX(string asset);
  void setOnMouseReleaseSFX(string asset);
  void setOnMouseClickSFX(string asset);
  void setOnMouseDblClickSFX(string asset);
  void setOnMouseMoveSFX(string asset);
  void setOnMouseEnterSFX(string asset);
  void setOnMouseExitSFX(string asset);
  void setMouseOverSFX(string asset, bool loop);
  void setOnKeyPressSFX(string asset);
  void setOnKeyReleaseSFX(string asset);

protected:
  static UIThing* s_mouseOver;
  MouseCursor* m_mouse;
};

#endif