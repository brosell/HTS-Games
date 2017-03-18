#pragma warning (disable:4786)
#include "Container.h"
#include "Log.h"
#include <algorithm>

Container::Container():
UIThing(), 
m_acceptFocus(false) 
{ 
  m_currentFocus=m_things.end();
}

void Container::addUIThing(UIThing* thing)
{
  thing->setParent(this);
  m_things.push_back(thing);
}

void Container::removeUIThing(UIThing* thing)
{
  m_things.remove(thing);
  m_currentFocus=m_things.end();
}

void Container::show()
{
  m_currentFocus = m_things.begin();
  UIThing::show();
}

/** 
  * Many event handlers to be overridden.
  */
void Container::onMousePress(MousePressEvent* event) 
{
  Point clickPoint = translatePoint(event->x, event->y);
  UIThing* thing=findByPoint(clickPoint);
  if (thing != 0)
  {
    if (thing->acceptsFocus())
    {
      setFocus(thing);
    }
    thing->onMousePress(event);
  }
  else
  {
    UIThing::onMousePress(event);
  }
}
void Container::onMouseRelease(MouseReleaseEvent* event) 
{ 
  Point clickPoint = translatePoint(event->x, event->y);
  UIThing* thing=findByPoint(clickPoint);
  if (thing != 0)
  {
    if (thing->acceptsFocus())
    {
      setFocus(thing);
    }
    thing->onMouseRelease(event);
  }
  else
  {
    UIThing::onMouseRelease(event);
  }
}
void Container::onMouseClick(MouseClickEvent* event) 
{
  Point clickPoint = translatePoint(event->x, event->y);
  UIThing* thing=findByPoint(clickPoint);
  if (thing != 0)
  {
    if (thing->acceptsFocus())
    {
      setFocus(thing);
    }
    thing->onMouseClick(event);
  }
  else
  {
    UIThing::onMouseClick(event);
  }
}
void Container::onMouseDblClick(MouseDblClickEvent* event) 
{
  Point clickPoint = translatePoint(event->x, event->y);
  UIThing* thing=findByPoint(clickPoint);
  if (thing != 0)
  {
    if (thing->acceptsFocus())
    {
      setFocus(thing);
    }
    thing->onMouseDblClick(event);
  }
  else
  {
    UIThing::onMouseDblClick(event);
  }
}
void Container::onMouseMove(MouseMoveEvent* event) 
{
  Point clickPoint = translatePoint(event->x, event->y);
  UIThing* thing=findByPoint(clickPoint);
  if (thing != 0)
  {
    thing->onMouseMove(event);
  }
  else
  {
    UIThing::onMouseMove(event);
  }
}
void Container::onMouseEnter(MouseEnterEvent* event) 
{ 
  Point clickPoint = translatePoint(event->x, event->y);
  UIThing* thing=findByPoint(clickPoint);
  if (thing != 0)
  {
    thing->onMouseEnter(event);
  }
  else
  {
    UIThing::onMouseEnter(event);
  }
}
void Container::onMouseExit(MouseExitEvent* event) 
{ 
  Point clickPoint = translatePoint(event->x, event->y);
  UIThing* thing=findByPoint(clickPoint);
  if (thing != 0)
  {
    thing->onMouseExit(event);
  }
  else
  {
    UIThing::onMouseExit(event);
  }
}

void Container::onKeyPress(KeyPressEvent* event) 
{ 
  if (event->keySym == SDLK_TAB)
  {
    if (!nextFocus())
    {
      if (getParent())
      {
        getParent()->nextFocus();
      }
    }
  }
  else
  {
    if (m_currentFocus != m_things.end())
    {
      (*m_currentFocus)->onKeyPress(event);
    }
  }
}
void Container::onKeyRelease(KeyReleaseEvent* event) 
{ 
  if (m_currentFocus != m_things.end())
  {
    (*m_currentFocus)->onKeyRelease(event);
  }
}

inline Point Container::translatePoint(int x, int y)
{
  Point ret;
  ret.x = x - m_position.x;
  ret.y = y - m_position.y;
  return ret;
}

UIThing* Container::findByPoint(Point point)
{
  list<UIThing*>::iterator i;
  for (i=m_things.begin(); i!=m_things.end(); i++)
  {
    UIThing* thing = (*i);
    Rect r=thing->getPosition();
    if (r.containsPoint(point))
    {
      return thing;
    }
  }
  return 0;
}

void Container::paint(Display* surface)
{
  list<UIThing*>::iterator i;
  for (i=m_things.begin(); i!=m_things.end(); i++)
  {
    (*i)->draw(surface);
  }
}


////////////////
/// FOCUS //////
////////////////


UIThing* Container::getFocus()
{
  if (m_currentFocus != m_things.end())
  {
    UIThing* thing=(*m_currentFocus);
    if ( thing->isContainer())
    {
      Container* cont=(Container*)thing;
      return cont->getFocus();
    }
    return *m_currentFocus;
  }
  return 0;
}

bool Container::nextFocus()
{
  list<UIThing*>::iterator foc=m_currentFocus;
  list<UIThing*>::iterator i;
  if (foc==m_things.end())
  {
    foc=m_things.begin();
  }
  else
  {
    (*foc)->loseFocus();
    foc++;
  }
  for (i=foc; i!=m_things.end(); i++)
  {
    if ( (*i)->acceptsFocus() )
    {
      (*i)->takeFocus();
      m_currentFocus=i;
      return true;
    }
  }

  for (i=m_things.begin(); i!=foc; i++)
  {
    if ( (*i)->acceptsFocus() )
    {
      (*i)->takeFocus();
      m_currentFocus=i;
      return true;
    }
  }
  lassert(false); // nothing takes focus ?!?!
  return false;
}

bool Container::setFocus(UIThing* thing)
{
  lassert(thing->acceptsFocus());

  list<UIThing*>::iterator i=find(m_things.begin(), m_things.end(), thing);
  list<UIThing*>::iterator oldFocus = m_currentFocus;

  if (i==m_things.end())
  {
    lassert(false);
    return false;
  }
  
  if (oldFocus != m_things.end())// && oldFocus != m_currentFocus)
  {
    UIThing* t=*oldFocus;
    t->loseFocus();
  }

  m_currentFocus=i;
  thing->takeFocus();

  m_haveFocus=true;

  
//  if (getParent()!=0)
//  {
//    return getParent()->setFocus(this);
//  }

  return true;
}


/////// VISIBILTY
bool Container::isObscured(UIThing* thing)
{
  list<UIThing*>::iterator iThing = find(m_things.begin(), m_things.end(), thing);
  
  if(iThing == m_things.end())
  {
    // must be modal?
    return false;
  }

  if (m_parent)
  {
    if (m_parent->isObscured(this))
    {
      return true;
    }
  }

  iThing++; // of course we obscure ourself, so skip!

  list<UIThing*>::iterator i;
  for (i=iThing; i!=m_things.end(); i++)
  {
    if ( thing->isObscuredBy(*i) )
    {
      return true;
    }
  }
  return false;
}

UIThing* Container::getControl(int id)
{
  list<UIThing*>::iterator i;
  for (i=m_things.begin(); i!=m_things.end(); i++)
  {
    if ( (*i)->getId() == id)
    {
      return (*i);
    }
  }
  return 0;
}

UIThing* Container::getControlByName(string name)
{
  list<UIThing*>::iterator i;
  for (i=m_things.begin(); i!=m_things.end(); i++)
  {
    if ( (*i)->getControlName() == name)
    {
      return (*i);
    }
  }
  return 0;
}
