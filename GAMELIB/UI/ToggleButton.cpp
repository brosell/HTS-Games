#pragma warning (disable : 4786 4503 4530)

#include "ToggleButton.h"
#include "BR_Game.h"
#include "SDL_rotozoom.h"
#include "Misc/AssetManager.h"

ToggleButton::ToggleButton(): m_isChecked(false), m_checked(0), m_unchecked(0)
{
}

void ToggleButton::setChecked(bool c) 
{
  ToggleButton* other = 0;
  if (m_parent != 0)
  {
    other = dynamic_cast<ToggleButton*>(m_parent->getControl(m_other));
  }

  if (other)
  {
    // there is another, so toggle correctly
    if (c == false)
    {
      // can't un check when there is another
      return;
    }
    other->uncheck();
  }
  
  m_isChecked = c;
}

void ToggleButton::setCheckedTexture(string assetName)
{
  if (m_checked != 0) theGame.assetManager->releaseSkin(m_checked);
  m_checked=theGame.assetManager->getSkin(assetName);
}

void ToggleButton::setUncheckedTexture(string assetName)
{
  if (m_unchecked != 0) theGame.assetManager->releaseSkin(m_unchecked);
  m_unchecked=theGame.assetManager->getSkin(assetName);
}


ToggleButton::~ToggleButton()
{
  if (m_checked != 0) theGame.assetManager->releaseSkin(m_checked);
  if (m_unchecked != 0) theGame.assetManager->releaseSkin(m_unchecked);
}

void ToggleButton::onMouseClick(MouseClickEvent* event)
{
  setChecked(!m_isChecked);
  Button::onMouseClick(event);
}

void ToggleButton::paint(Display* surface)
{
  Rect r = getPosition();
  if (m_isChecked)
  {
    if (m_checked != 0)
    {
      m_checked->blit(surface, r.x, r.y, false);
    }
    else
    {
      lassert(0 && "ToggleButton checked has no skin");
    }
  }
  else
  {
    if (m_unchecked != 0)
    {
      m_unchecked->blit(surface, r.x, r.y, false);
    }
  }
}