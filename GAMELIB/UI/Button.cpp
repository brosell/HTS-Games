#pragma warning (disable : 4786 4503 4530)

#include "Button.h"
#include "SDL_gfxPrimitives.h"
#include "Font.h"
#include "BR_Game.h"

#include "Misc/AssetManager.h"


Button::Button(): 
UIThing(), 
m_isDown(false),
m_buttonUp(0),
m_buttonDown(0),
m_buttonFocus(0),
m_buttonOver(0),
m_link("")
{
  m_actionEvent.thing = this;
}

Button::~Button()
{
  if (m_buttonUp != 0)
    theGame.assetManager->releaseSkin(m_buttonUp);

  if (m_buttonDown != 0)
    theGame.assetManager->releaseSkin(m_buttonDown);

  if (m_buttonFocus != 0)
    theGame.assetManager->releaseSkin(m_buttonFocus);

  if (m_buttonOver != 0)
    theGame.assetManager->releaseSkin(m_buttonOver);
}

void Button::onMousePress(MousePressEvent* event)
{
  if (event->button == 1)
  {
    m_isDown=true;
  }
  UIThing::onMousePress(event);
}
void Button::onMouseRelease(MouseReleaseEvent* event)
{
  if (event->button == 1)
  {
    m_isDown=false;
  }
  UIThing::onMouseRelease(event);
}


void Button::onMouseExit(MouseExitEvent* event)
{
  m_isDown = false;
  UIThing::onMouseExit(event);
}


void Button::onMouseClick(MouseClickEvent* event)
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

void Button::paint(Display* surface)
{
  Rect r=getTranslatedPosition();
  r.x+= (r.w/2);
  r.y+= (r.h/2);

  if (m_isDown && m_buttonDown != 0)
  {
    m_buttonDown->blit(surface, r.x, r.y);
  }
  else
  {
    if (this == s_mouseOver && m_buttonOver != 0)
    {
      m_buttonOver->blit(surface, r.x, r.y);
    }
    else if (this->hasFocus() && m_buttonFocus != 0)
    {
      m_buttonFocus->blit(surface, r.x, r.y);
    }
    else if (m_buttonUp != 0)
    {
      m_buttonUp->blit(surface, r.x, r.y);
    }
  }

  string text = getText();
  if (text != "")
  {
    Font* font = getFont();
    r = getTranslatedPosition();
    int tx = r.x + ((r.w/2) - (font->getTextWidth(text)/2));
    int ty = r.y + ((r.h/2) - (font->getFontHeight()/2));
    font->drawLine(surface, text, tx, ty);
  }
}

void Button::setUpTexture(string assetName) 
{ 
  m_buttonUp = theGame.assetManager->getSkin(assetName);
}

void Button::setDownTexture(string assetName) 
{ 
  m_buttonDown = theGame.assetManager->getSkin(assetName);
}
void Button::setFocusTexture(string assetName) 
{ 
  m_buttonFocus = theGame.assetManager->getSkin(assetName);
}
void Button::setOverTexture(string assetName) 
{ 
  m_buttonOver = theGame.assetManager->getSkin(assetName);
}

