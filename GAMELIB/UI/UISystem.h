#ifndef _UISystem_h
#define _UISystem_h

#include "UI/NewEventModel.h"
#include "UI/Container.h"
#include "UI/DialogBox.h"

#include <deque>
using std::deque;

class UISystem: public Container
{
public:
  UISystem();
  initialize();

  void draw(Display* surface);

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

  /**
    * set the First Chance delegate if you want to see events before
    * anything else.
    */
  void setFirstChanceDelegate(Delegate* d) { m_firstChanceDelegate = d; }

  void pushModal(DialogBox* cont);
  void popModal();
  DialogBox* topModal();
  bool doModalEvent(Message* event);

  bool showCursor(bool show);

  virtual MouseCursor* getMouseCursor()
  {
    return m_mouse;
  }

private:
  bool m_showing;
  bool m_mouseShowing;

  Delegate* m_firstChanceDelegate;

  UIThing* m_lastFocus;

  deque<DialogBox*> m_modalStack;
  
};


#endif
