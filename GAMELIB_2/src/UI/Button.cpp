#pragma warning (disable : 4786 4503 4530)

#include "Button.h"
#include "SDL_gfxPrimitives.h"
#include "Font.h"
#include "BR_Game.h"

#include "AssetManager.h"


Button::Button(): 
UIThing(), 
m_isDown(false),
m_link("")
{
  m_actionEvent.thing = this;
}

Button::~Button()
{
}

void Button::onMousePress(MousePressEvent* event)
{
  setDirty(true);
  if (event->button == LEFT_BUTTON)
  {
    m_isDown=true;
  }
  UIThing::onMousePress(event);
}
void Button::onMouseRelease(MouseReleaseEvent* event)
{
  setDirty(true);
  if (event->button == LEFT_BUTTON)
  {
    m_isDown=false;
  }
  UIThing::onMouseRelease(event);
}

void Button::onMouseEnter(MouseEnterEvent* event)
{
  setDirty(true);
  UIThing::onMouseEnter(event);
}

void Button::onMouseExit(MouseExitEvent* event)
{
  setDirty(true);
  m_isDown = false;
  UIThing::onMouseExit(event);
}


void Button::onMouseClick(MouseClickEvent* event)
{
  if (event->button == LEFT_BUTTON)
  {
    UIThing::onMouseClick(event);
    m_actionEvent.commandId = getId();
    
    set<ActionListener*> setCopy(m_actionListeners);
    set<ActionListener*>::iterator i;
    for (i=setCopy.begin(); i!=setCopy.end(); i++)
    {
      (*i)->actionPerformed(&m_actionEvent);
    }
    
    if (m_link != "")
    {
      ShellExecute(NULL, "open", m_link.c_str(), NULL, NULL, SW_SHOW);
    }
  }
}

void Button::frameChanged(SkinFrameChangeEvent* event)
{
  setDirty(true);
}

void Button::paint(Display* surface)
{
  Rect r=getTranslatedPosition();
  r.x+= (r.w/2);
  r.y+= (r.h/2);

  if (m_isDown && m_buttonDown.isValid())
  {
    m_buttonDown->blit(surface, r.x, r.y);
  }
  else
  {
    if (this == s_mouseOver && m_buttonOver.isValid())
    {
      m_buttonOver->blit(surface, r.x, r.y);
    }
    else if (this->hasFocus() && m_buttonFocus.isValid())
    {
      m_buttonFocus->blit(surface, r.x, r.y);
    }
    else if (m_buttonUp.isValid())
    {
      m_buttonUp->blit(surface, r.x, r.y);
    }
  }

  string text = getText();
  if (text != "")
  {
    FontHandle font = getFont();
    if (font.isValid())
    {
      r = getTranslatedPosition();
      int tx = r.x + ((r.w/2) - (font->getTextWidth(text)/2));
      int ty = r.y + ((r.h/2) - (font->getFontHeight()/2));
      font->drawLine(surface, text, tx, ty);
    }
    else
    {
      err_NoFont();
    }
  }
}

void Button::setUpTexture(string assetName) 
{ 
  if (m_buttonUp.isValid())
  {
    m_buttonUp->removeListener(this);
  }
  m_buttonUp=theGame.am->getSkin(assetName);
  if (m_buttonUp.isValid())
  {
    m_buttonUp->addListener(this);
  }
  setDirty(true);
}

void Button::setDownTexture(string assetName) 
{ 
  if (m_buttonDown.isValid())
  {
    m_buttonDown->removeListener(this);
  }
  m_buttonDown=theGame.am->getSkin(assetName);
  if (m_buttonDown.isValid())
  {
    m_buttonDown->addListener(this);
  }
  setDirty(true);
}
void Button::setFocusTexture(string assetName) 
{ 
  if (m_buttonFocus.isValid())
  {
    m_buttonFocus->removeListener(this);
  }
  m_buttonFocus=theGame.am->getSkin(assetName);
  if (m_buttonFocus.isValid())
  {
    m_buttonFocus->addListener(this);
  }
  setDirty(true);
}
void Button::setOverTexture(string assetName) 
{ 
  if (m_buttonOver.isValid())
  {
    m_buttonOver->removeListener(this);
  }
  m_buttonOver=theGame.am->getSkin(assetName);
  if (m_buttonOver.isValid())
  {
    m_buttonOver->addListener(this);
  }

  setDirty(true);
}

