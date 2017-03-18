#pragma warning (disable: 4786)
#include "UISystem.h"
#include "Log.h"

UISystem::UISystem(): 
Container(),
m_firstChanceDelegate(0)
{

}

UISystem::initialize()
{
}

/** 
  * Many event handlers to be overridden.
  */

void UISystem::onMousePress(MousePressEvent* event) 
{
  // let any first chancers have a wack at it
//  UIThing::onMousePress(event);
  DialogBox* db = (m_modalStack.size()>0?m_modalStack.back():0);
  if (db != 0)
  {
    Rect r = db->getTranslatedPosition();
    if (r.containsPoint(Point(event->x, event->y)))
    {
      db->onMousePress(event);
    }
    else
    {
      // maybe set the mouse to an hourglass?
    }
  }
  else
  {
    Container::onMousePress(event);
  }
}

void UISystem::onMouseRelease(MouseReleaseEvent* event) 
{ 
    // let any first chancers have a wack at it
//  UIThing::onMouseRelease(event);
  DialogBox* db = (m_modalStack.size()>0?m_modalStack.back():0);
  if (db != 0)
  {
    Rect r = db->getTranslatedPosition();
    if (r.containsPoint(Point(event->x, event->y)))
    {
      db->onMouseRelease(event);
    }
    else
    {
      // maybe set the mouse to an hourglass?
    }
  }
  else
  {
    Container::onMouseRelease(event);
  }

}
void UISystem::onMouseClick(MouseClickEvent* event) 
{
    // let any first chancers have a wack at it
//  UIThing::onMouseClick(event);
  DialogBox* db = (m_modalStack.size()>0?m_modalStack.back():0);
  if (db != 0)
  {
    Rect r = db->getTranslatedPosition();
    if (r.containsPoint(Point(event->x, event->y)))
    {
      db->onMouseClick(event);
    }
    else
    {
      // maybe set the mouse to an hourglass?
    }
  }
  else
  {
    Container::onMouseClick(event);
  }
}

void UISystem::onMouseDblClick(MouseDblClickEvent* event) 
{ 
    // let any first chancers have a wack at it
//  UIThing::onMouseDblClick(event);
  DialogBox* db = (m_modalStack.size()>0?m_modalStack.back():0);
  if (db != 0)
  {
    Rect r = db->getTranslatedPosition();
    if (r.containsPoint(Point(event->x, event->y)))
    {
      db->onMouseDblClick(event);
    }
    else
    {
      // maybe set the mouse to an hourglass?
    }
  }
  else
  {
    Container::onMouseDblClick(event);
  }
}
void UISystem::onMouseMove(MouseMoveEvent* event) 
{ 
  // let any first chancers have a wack at it
//  UIThing::onMouseMove(event);
  DialogBox* db = (m_modalStack.size()>0?m_modalStack.back():0);
  if (db != 0)
  {
    Rect r = db->getTranslatedPosition();
    if (r.containsPoint(Point(event->x, event->y)))
    {
      db->onMouseMove(event);
    }
    else
    {
      // maybe set the mouse to an hourglass?
    }
  }
  else
  {
    Container::onMouseMove(event);
  }
}
void UISystem::onMouseEnter(MouseEnterEvent* event) 
{ 
  //lassert(false);
  // not at this scope?
}
void UISystem::onMouseExit(MouseExitEvent* event) 
{ 
  //lassert(false);
  // not at this scope?
}

void UISystem::onKeyPress(KeyPressEvent* event) 
{ 
  // let any first chancers have a wack at it
  UIThing::onKeyPress(event);
  DialogBox* db = (m_modalStack.size()>0?m_modalStack.back():0);
  if (db != 0)
  {
    db->onKeyPress(event);
  }
  else
  {
    if (m_things.size() > 0)
    {
      UIThing* top = m_things.back();
      if (top != 0)
      {
        top->onKeyPress(event);
      }
    }
  }
}
void UISystem::onKeyRelease(KeyReleaseEvent* event) 
{
  // let any first chancers have a wack at it
  UIThing::onKeyRelease(event);
  DialogBox* db = (m_modalStack.size()>0?m_modalStack.back():0);
  if (db != 0)
  {
    db->onKeyRelease(event);
  }
  else
  {
    if (m_things.size() > 0)
    {
      UIThing* top = m_things.back();
      if (top != 0)
      {
        top->onKeyRelease(event);
      }
    }
  }
}  


void UISystem::draw(Display* surface)
{
  deque<DialogBox*>::iterator i;
  list<UIThing*>::reverse_iterator ri;
  ri = m_things.rbegin();
  if (!m_things.empty())
  {
    UIThing* thing = *ri;
    thing->draw(surface);
  }

  for (i=m_modalStack.begin(); i!=m_modalStack.end(); i++)
  {
    (*i)->draw(surface);
  }

  if (m_mouseShowing)
  {
    if (s_mouseOver != 0)
    {
      s_mouseOver->drawMouseCursor(surface);
    }
    else
    {
      drawMouseCursor(surface);
    }
  }
}

void UISystem::pushModal(DialogBox* cont)
{
  m_modalStack.push_back(cont);
}

void UISystem::popModal()
{
  m_modalStack.pop_back();
}

DialogBox* UISystem::topModal() 
{ 
  if (m_modalStack.size() > 0)
  {
    return m_modalStack.back(); 
  }
  return 0;
}

bool UISystem::showCursor(bool show)
{
  bool old = m_mouseShowing;
  m_mouseShowing = show;
  return old;

}