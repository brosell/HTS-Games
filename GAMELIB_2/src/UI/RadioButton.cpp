/* ****************************************************************************
 *
 *  RadioButton.cpp
 *  Created by Bert Rosell, on Mon Nov 24 2003, 14:07:36 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the RadioButton component.
 *  Please see RadioButton.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "RadioButton.h"


/* ********************************* 
 * RadioButton
 ***********************************/
#include "RadioButton.h"
#include "BR_Game.h"
#include "SDL_rotozoom.h"
#include "AssetManager.h"

RadioButton::RadioButton(): 
m_isChecked(false)
{
}

RadioButton::RadioButton(StringMap& attributes): 
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

  string group=attributes["Group"];
  if (group != "")
  {
    m_group = RadioButtonGroup::get(group);
    if (m_group != 0)
    {
      m_group->addRadioButton(this);
    }
  }
}

void RadioButton::setCheckedTexture(string assetName)
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

void RadioButton::setUncheckedTexture(string assetName)
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

void RadioButton::setDisabledTexture(string assetName)
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


RadioButton::~RadioButton()
{
}

void RadioButton::onMouseClick(MouseClickEvent* event)
{
  if (isEnabled() && event->button == LEFT_BUTTON)
  {
    if (m_group != 0)
    {
      m_group->setChecked(this);
    }
    else
    {
      check();
    }
  }
  Button::onMouseClick(event);
}

void RadioButton::paint(Display* surface)
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
      lassert(0 && "RadioButton checked has no skin");
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

//////////////////////////////////////
/// RadioButtonGroup
//////////////////////////////////////
map<string, RadioButtonGroup*> RadioButtonGroup::s_groups;

RadioButtonGroup* RadioButtonGroup::get(string name)
{
  RadioButtonGroup* group = s_groups[name];
  if (group == 0)
  {
    group = new RadioButtonGroup;
    s_groups[name] = group;
  }
  return group;
}

void RadioButtonGroup::release(string name)
{
  map<string, RadioButtonGroup*>::iterator pair;
  pair = s_groups.find(name);
  if (pair != s_groups.end())
  {
    delete pair->second;
    s_groups.erase(name);
  }
}

void RadioButtonGroup::addRadioButton(RadioButton* button)
{
  m_buttons.push_back(button);
}

void RadioButtonGroup::setChecked(RadioButton* button)
{
  vector<RadioButton*>::iterator i;
  for (i=m_buttons.begin(); i!=m_buttons.end(); i++)
  {
    RadioButton* rb = *i;
    if (rb == button)
    {
      rb->check();
    }
    else
    {
      rb->uncheck();
    }
  }
  update();
}

void RadioButtonGroup::setChecked(int id)
{
  vector<RadioButton*>::iterator i;
  for (i=m_buttons.begin(); i!=m_buttons.end(); i++)
  {
    RadioButton* rb = *i;
    if (rb->getId() == id)
    {
      rb->check();
    }
    else
    {
      rb->uncheck();
    }
  }
  update();
}


int RadioButtonGroup::getCheckedId()
{
  vector<RadioButton*>::iterator i;
  for (i=m_buttons.begin(); i!=m_buttons.end(); i++)
  {
    RadioButton* rb = *i;
    if (rb->isChecked())
    {
      return rb->getId();
    }
  }
  return -1;
}

bool RadioButtonGroup::isChecked(int id)
{
  vector<RadioButton*>::iterator i;
  for (i=m_buttons.begin(); i!=m_buttons.end(); i++)
  {
    RadioButton* rb = *i;
    if (rb->getId() == id && rb->isChecked())
    {
      return true;
    }
  }

  return false;
}

void RadioButtonGroup::addRadioButtonGroupListener(RadioButtonGroupListener* listener)
{
  m_listeners.insert(listener);
}
void RadioButtonGroup::removeRadioButtonGroupListener(RadioButtonGroupListener* listener)
{
  m_listeners.erase(listener);
}

void RadioButtonGroup::update()
{
  RadioButtonEvent event;
  event.group = this;
  event.commandId = getCheckedId();
  set<RadioButtonGroupListener*> copy(m_listeners);
  set<RadioButtonGroupListener*>::iterator i;
  for (i=copy.begin(); i!=copy.end(); i++)
  {
    (*i)->radioEvent(&event);
  }
}