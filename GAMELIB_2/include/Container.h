#ifndef _Container_h
#define _Container_h

#include "UIThing.h"


class Container: public UIThing
{
public:
  Container();
  virtual ~Container() { }
  
  virtual string getName() { return "Container"; }
  virtual bool isContainer() { return true; }

  virtual void setDirty(bool d = true);
  
  void addUIThing(UIThing* thing);
  void removeUIThing(UIThing* thing);

  void moveToTop(UIThing* thing)
  {
    removeUIThing(thing);
    addUIThing(thing);
  }

  /**
  * get the control on this dialog with the id=id
  */
  UIThing* getControl(int id);

  /** get the control named name */
  UIThing* getControlByName(string name);

  virtual bool isDirty();


  // from UIThing
  virtual void show();
  
  /**
    * determins whether "thing" is obscured
    */
  virtual bool isObscured(UIThing* thing);
  
  // FOCUS STUFF
  virtual bool setFocus(UIThing* thing);
  virtual bool nextFocus();

  // from UIThing
  virtual bool hasFocus() { return true; }
  virtual void takeFocus() { return; }
  virtual void loseFocus() { return; }
  virtual bool acceptsFocus() { return true; }
  // end UIThing


  /**
    * return the thing that has focus
    */
  virtual UIThing* getFocus();

  // END FOCUS STUFF

  virtual void paint(Display* surface);


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

  size_t countControls() { return m_things.size(); }
protected:

  /**
    * return the UIThing under point
    */
  UIThing* findByPoint(Point point);

  /**
    * translates screen to container relative
    */
  Point translatePoint(int x, int y);

  list<UIThing*> m_things;
  
  // FOCUS
  list<UIThing*>::iterator m_currentFocus;


  bool m_acceptFocus; // seet to true if at least one control want focus
};


#endif