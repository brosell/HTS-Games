#pragma warning (disable : 4786 4503 4530)

#include "ToggleButton.h"
#include "BR_Game.h"
#include "SDL_rotozoom.h"
#include "AssetManager.h"

ToggleButton::ToggleButton(): 
m_isChecked(false)
{
}

ToggleButton::ToggleButton(StringMap& attributes): 
m_isChecked(false)
{
  string skin=attributes["CheckedTexture"];
  if (skin != "")
  {
    setCheckedTexture(skin);
  }

  skin=attributes["UncheckedTexture"];
  if (skin != "")
  {
    setUncheckedTexture(skin);
  }

  skin=attributes["DisabledTexture"];
  if (skin != "")
  {
    setDisabledTexture(skin);
  }


  m_isChecked = ((attributes["Checked"]=="1")?true:false);

}

void ToggleButton::setChecked(bool c) 
{
  setDirty(true);
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
  if (m_checked.isValid())
  {
    m_checked->removeListener(this);
  }
  m_checked=theGame.am->getSkin(assetName);
  if (m_checked.isValid())
  {
    m_checked->addListener(this);
  }
  setDirty(true); 
}

void ToggleButton::setUncheckedTexture(string assetName)
{
  if (m_unchecked.isValid())
  {
    m_unchecked->removeListener(this);
  }
  m_unchecked=theGame.am->getSkin(assetName);
  if (m_unchecked.isValid())
  {
    m_unchecked->addListener(this);
  }

  setDirty(true); 
}

void ToggleButton::setDisabledTexture(string assetName)
{
  if (m_disabled.isValid())
  {
    m_disabled->removeListener(this);
  }
  m_disabled=theGame.am->getSkin(assetName);
  if (m_disabled.isValid())
  {
    m_disabled->addListener(this);
  }
  setDirty(true); 
}


ToggleButton::~ToggleButton()
{
}

void ToggleButton::onMouseClick(MouseClickEvent* event)
{
  if (isEnabled() && event->button == LEFT_BUTTON)
  {
    setChecked(!m_isChecked);
  }
  Button::onMouseClick(event);
}

void ToggleButton::paint(Display* surface)
{
  Rect r = getPosition();
  if (!isEnabled() && m_disabled.isValid())
  {
    m_disabled->blit(surface, r.x, r.y, false);
    return;
  }

  if (m_isChecked)
  {
    if (m_checked.isValid())
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
    if (m_unchecked.isValid())
    {
      m_unchecked->blit(surface, r.x, r.y, false);
    }
  }
}