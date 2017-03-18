#pragma warning (disable:4786 4530 4503)
#include "BR_Game.h"
#include "UIThing.h"
#include "Misc/AssetManager.h"

#include "Audio/SoundEffect.h"

bool UIThing::s_ocheck=true;
UIThing* UIThing::s_mouseOver = 0;

UIThing::UIThing(): 
m_haveFocus(false), 
m_visible(true), 
m_parent(0),
m_id(-1),
m_haveMouse(false),
m_font(0),
m_controlName("Unnamed"),
m_red(0),
m_green(0),
m_blue(0),
m_alpha(0),
m_snd_onMousePress(0),
m_snd_onMouseRelease(0),
m_snd_onMouseClick(0),
m_snd_onMouseDblClick(0),
m_snd_onMouseMove(0),
m_snd_onMouseEnter(0),
m_snd_onMouseExit(0),
m_snd_mouseOver(0),
m_snd_onKeyPress(0),
m_snd_onKeyRelease(0),
m_mouse(0, 0, 0)
{

}

#define releaseSound(snd) if (snd!=0) {theGame.assetManager->releaseSoundEffect(snd); snd = 0; }

UIThing::~UIThing()
{
  if (s_mouseOver == this)
  {
    s_mouseOver = 0;
  }

  releaseSound(m_snd_onMousePress);
  releaseSound(m_snd_onMouseRelease);
  releaseSound(m_snd_onMouseClick);
  releaseSound(m_snd_onMouseDblClick);
  releaseSound(m_snd_onMouseMove);
  releaseSound(m_snd_onMouseEnter);
  releaseSound(m_snd_onMouseExit);
  releaseSound(m_snd_mouseOver);
  releaseSound(m_snd_onKeyPress);
  releaseSound(m_snd_onKeyRelease);

  setMouseCursor("");

}


Font* UIThing::getFont() 
{ 
  if (m_font == 0)
  {
    if (m_parent)
    {
      if (m_parent->getFont() == 0)
      {
        return Font::getDefault();
      }
      return m_parent->getFont();
    }
    return Font::getDefault();
  }
  return m_font; 
}

void UIThing::setMouseCursor(string assetName)
{
  if (m_mouse != 0)
  {
    theGame.assetManager->releaseMouseCursor(m_mouse);
    m_mouse = 0;
  }

  if (assetName != "")
  {
    m_mouse = theGame.assetManager->getMouseCursor(assetName);
  }
}

MouseCursor* UIThing::getMouseCursor() 
{ 
  if (m_mouse == 0)
  {
    if (m_parent != 0)
    {
      return m_parent->getMouseCursor();
    }
    else
    {
      return theGame.uiSystem.getMouseCursor();
    }
  }
  return m_mouse; 
}

void UIThing::drawMouseCursor(Display* surface)
{
  MouseCursor* mouse = getMouseCursor();
  if (mouse == 0)
  {
    return;
  }

  Point p = theGame.getMousePos();
  int realX = p.x - mouse->hotX;
  int realY = p.y - mouse->hotY;
  
  mouse->skin->blit(theGame.screen, realX, realY, false);
}

void UIThing::draw(Display* surface)
{
  Rect r = getTranslatedPosition();
  if (!s_ocheck)
  {
    if (m_alpha != 0)
    {
      surface->fillRect(r.x, r.y, r.w+1, r.h+1, m_red, m_green, m_blue, m_alpha);
    }      
    paint(surface);
    return;
  }

  if (!isObscured())
  {
    if (m_alpha != 0)
    {
      surface->fillRect(r.x, r.y, r.w+1, r.h+1, m_red, m_green, m_blue, m_alpha);
    }      
    paint(surface);
  }
}


Rect UIThing::getTranslatedPosition()
{
  Rect ret = getPosition();
  Rect p;
  if (m_parent != 0)
  {
    p=m_parent->getTranslatedPosition();
    ret.x += p.x;
    ret.y += p.y;
  }
  
  return ret;
}

bool UIThing::isObscured()
{
  // if we aren't part of a container, we assume we are not obscured
  if (m_parent)
  {
    return m_parent->isObscured(this);
  }
  return false;
}

bool UIThing::isObscuredBy(UIThing* thing)
{
  Rect me=getTranslatedPosition();
  Rect other=thing->getTranslatedPosition();

  Rect overlap=Rect::findOverlap(&me, &other);
  if (overlap.x == -1)
  {
    //there is no overlap, so we are not obscured by thing
    return false;
  }
  if (/*overlap.w == other.w && overlap.h == other.h) || */
       (overlap.w == me.w && overlap.h == me.h) )
  {
    return true;
  }
  // this is a partial overlap. Now we let Z order do the clipping :)
  return false;
}


void UIThing::show()
{
  if (m_parent)
  {
    m_parent->addUIThing(this);
  }
  else
  {
    theGame.uiSystem.addUIThing(this);
  }
}

void UIThing::hide()
{
  if (m_parent)
  {
    m_parent->removeUIThing(this);
  }
  else
  {
    theGame.uiSystem.removeUIThing(this);
  }
}

void UIThing::setOnMousePressSFX(string asset)
{
  releaseSound(m_snd_onMousePress);
  m_snd_onMousePress = theGame.assetManager->getSoundEffect(asset);
}

void UIThing::setOnMouseReleaseSFX(string asset)
{
  releaseSound(m_snd_onMouseRelease);
  m_snd_onMouseRelease = theGame.assetManager->getSoundEffect(asset);
}

void UIThing::setOnMouseClickSFX(string asset)
{
  releaseSound(m_snd_onMouseClick);
  m_snd_onMouseClick = theGame.assetManager->getSoundEffect(asset);
}


void UIThing::setOnMouseDblClickSFX(string asset)
{
  releaseSound(m_snd_onMouseDblClick);
  m_snd_onMouseDblClick = theGame.assetManager->getSoundEffect(asset);
}

void UIThing::setOnMouseMoveSFX(string asset)
{
  releaseSound(m_snd_onMouseMove);
  m_snd_onMouseMove = theGame.assetManager->getSoundEffect(asset);
}

void UIThing::setOnMouseEnterSFX(string asset)
{
  releaseSound(m_snd_onMouseEnter);
  m_snd_onMouseEnter = theGame.assetManager->getSoundEffect(asset);
}

void UIThing::setOnMouseExitSFX(string asset)
{
  releaseSound(m_snd_onMouseExit);
  m_snd_onMouseExit = theGame.assetManager->getSoundEffect(asset);
}

void UIThing::setMouseOverSFX(string asset, bool loop)
{
  releaseSound(m_snd_mouseOver);
  m_snd_mouseOver = theGame.assetManager->getSoundEffect(asset);
  m_snd_mouseOverLoop = loop;
}

void UIThing::setOnKeyPressSFX(string asset)
{
  releaseSound(m_snd_onKeyPress);
  m_snd_onKeyPress = theGame.assetManager->getSoundEffect(asset);
}

void UIThing::setOnKeyReleaseSFX(string asset)
{
  releaseSound(m_snd_onKeyRelease);
  m_snd_onKeyRelease = theGame.assetManager->getSoundEffect(asset);
}


void UIThing::onMousePress(MousePressEvent* event) 
{
  if (m_snd_onMousePress != 0)
  {
    m_snd_onMousePress->play();
  }
  event->commandId = getId();
  event->thing = this;
  set<MouseListener*> setCopy(m_mouseListeners);
  set<MouseListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->mousePressed(event);
  }
}
void UIThing::onMouseRelease(MouseReleaseEvent* event)
{
  if (m_snd_onMouseRelease != 0)
  {
    m_snd_onMouseRelease->play();
  }
  event->commandId = getId();
  event->thing = this;
  set<MouseListener*> setCopy(m_mouseListeners);
  set<MouseListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->mouseReleased(event);
  }
}

void UIThing::onMouseClick(MouseClickEvent* event)
{ 
  if (m_snd_onMouseClick != 0)
  {
    m_snd_onMouseClick->play();
  }
  
  event->commandId = getId();
  event->thing = this;
  set<MouseListener*> setCopy(m_mouseListeners);
  set<MouseListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->mouseClicked(event);
  }
}

void UIThing::onMouseDblClick(MouseDblClickEvent* event)
{ 
  if (m_snd_onMouseDblClick != 0)
  {
    m_snd_onMouseDblClick->play();
  }
  
  event->commandId = getId();
  event->thing = this;
  set<MouseListener*> setCopy(m_mouseListeners);
  set<MouseListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->mouseDblClicked(event);
  }
}


void UIThing::onMouseMove(MouseMoveEvent* event)
{ 
  if (m_snd_onMouseMove != 0)
  {
    m_snd_onMouseMove->play();
  }
  
  event->commandId = getId();
  
  if (s_mouseOver != this)
  {
    if (s_mouseOver != 0)
    {
      MouseExitEvent exit;
      s_mouseOver->onMouseExit(&exit);
    }
    
    MouseEnterEvent enter;
    onMouseEnter(&enter);
    s_mouseOver = this;
  }
  event->thing = this;
  set<MouseListener*> setCopy(m_mouseListeners);
  set<MouseListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->mouseMoved(event);
  }
}

void UIThing::onMouseEnter(MouseEnterEvent* event)
{ 
  if (m_snd_onMouseEnter != 0)
  {
    m_snd_onMouseEnter->play();
  }
  
  if (m_snd_mouseOver != 0)
  {
    int loops = -1;
    if (m_snd_mouseOverLoop != true)
    {
      loops = 0;
    }
    m_snd_mouseOver->play(loops);
  }
  
  event->commandId = getId();
  event->thing = this;
  set<MouseListener*> setCopy(m_mouseListeners);
  set<MouseListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->mouseEntered(event);
  }
}

void UIThing::onMouseExit(MouseExitEvent* event)
{ 
  if (m_snd_onMouseExit != 0)
  {
    m_snd_onMouseExit->play();
  }
  
  if (m_snd_mouseOver != 0)
  {
    m_snd_mouseOver->fadeOut(250);
  }
  
  event->commandId = getId();
  event->thing = this;
  set<MouseListener*> setCopy(m_mouseListeners);
  set<MouseListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->mouseExited(event);
  }
}

void UIThing::onKeyPress(KeyPressEvent* event)
{
  if (m_snd_onKeyPress != 0)
  {
    m_snd_onKeyPress->play();
  }
  
  event->commandId = getId();
  event->thing = this;
  set<KeyListener*> setCopy(m_keyListeners);
  set<KeyListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->keyPressed(event);
  }
}

void UIThing::onKeyRelease(KeyReleaseEvent* event)
{
  if (m_snd_onKeyRelease != 0)
  {
    m_snd_onKeyRelease->play();
  }
  
  event->commandId = getId();
  event->thing = this;
  set<KeyListener*> setCopy(m_keyListeners);
  set<KeyListener*>::iterator i;
  for (i=setCopy.begin(); i!=setCopy.end(); i++)
  {
    (*i)->keyReleased(event);
  }
}
