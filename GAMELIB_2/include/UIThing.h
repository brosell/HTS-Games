#ifndef _UIThing_h
#define _UIThing_h

#include "NewEventModel.h"
#include "Display.h"
#include "SharedSkin.h"
#include "Font.h"

#include "MouseCursor.h"

#include "AM.h"

#include "IniFile.h"

class SoundEffect;

#include "GameMath.h"
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
  UIThing(StringMap& attributes);
  virtual ~UIThing();

  void init(StringMap& attributes);
  void doSFX(StringMap& attributes);

  bool isInited() { return m_inited; }

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

  virtual void setText(const string& s) { setDirty(); m_text=s;}
  virtual string getText() {return m_text; }
  
  Container* getParent() { return m_parent; }
  void setParent(Container* parent) { m_parent = parent; }

  bool isMouseOver() { return s_mouseOver == this; }

  /**
    * causes the UIThing to be drawn to the screen by calling paint(surface)
    * it will first check to see if this is obscured and dirty.
    */
  void draw(Display* surface);

  virtual bool isDirty() { return m_dirty; }
  virtual void setDirty(bool d = true) { m_dirty = d; }

  void setBackgroundColor(int r, int g, int b, int a)
  {
    setDirty();
    m_red = r;
    m_green = g;
    m_blue = b;
    m_alpha = a;
  }

  void setMouseCursor(string asset);
  virtual MouseCursor getMouseCursor();

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
  void setVisible(bool v) { setDirty(); m_visible = v; }

  bool isEnabled() { return m_enabled; }
  void setEnabled(bool e) { setDirty(); m_enabled = e; }

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
  virtual void setPosition(Rect& pos) { setDirty(); m_position = pos; }
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
  
  void setFont(FontHandle font) { m_font = font; }
  virtual FontHandle getFont(); // { return m_font; }

  static bool s_ocheck;
  static bool s_smartDraw;

  SDL_Surface* m_under;
  void saveUnder(Display* display);

protected:
  
  string m_controlName;
  bool m_haveFocus;

  string m_text;

  FontHandle m_font;

  Rect m_position;
  Container* m_parent;

  void err_NoFont() { error << getControlName() << " has no font" << endl; }
private:
  bool m_visible;
  bool m_enabled;
  bool m_dirty;
  int m_id;

  int m_red;
  int m_green;
  int m_blue;
  int m_alpha;

  int m_dred;
  int m_dgreen;
  int m_dblue;
  int m_dalpha;

  set<MouseListener*> m_mouseListeners;
  set<KeyListener*> m_keyListeners;

  bool m_haveMouse;

  SoundEffectHandle m_snd_onMousePress;
  SoundEffectHandle m_snd_onMouseRelease;
  SoundEffectHandle m_snd_onMouseClick;
  SoundEffectHandle m_snd_onMouseDblClick;
  SoundEffectHandle m_snd_onMouseMove;
  SoundEffectHandle m_snd_onMouseEnter;
  SoundEffectHandle m_snd_onMouseExit;
  
  SoundEffectHandle m_snd_onKeyPress;
  SoundEffectHandle m_snd_onKeyRelease;

  SoundEffectHandle m_snd_mouseOver;
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

  static int s_drawCount;
protected:
  static UIThing* s_mouseOver;
  bool m_inited;
  MouseCursor m_mouse;
};

#endif