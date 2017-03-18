/* ****************************************************************************
 *
 *  ChooseModeDlg.cpp
 *  Created by Bert Rosell, on Sat Nov 22 2003, 09:06:54 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the ChooseModeDlg component.
 *  Please see ChooseModeDlg.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "ChooseModeDlg.h"


/* ********************************* 
 * ChooseModeDlg
 ***********************************/
ChooseModeDlg::ChooseModeDlg(IniFile& ini, string name, Picture& picture):
IniBasedDialog(ini, name),
m_picture(picture)
{
  Button* button;
  button = dynamic_cast<Button*>(getControlByName("btn_Preview_Play"));
  if (button)
  {
    button->addActionListener(this);
  }

  button = dynamic_cast<Button*>(getControlByName("btn_Preview_Back"));
  if (button)
  {
    button->addActionListener(this);
  }

  m_modeGroup = RadioButtonGroup::get("Mode");
  m_modeGroup->addRadioButtonGroupListener(this);
  m_difGroup = RadioButtonGroup::get("Difficulty");
  m_difGroup->addRadioButtonGroupListener(this);

  m_easy = dynamic_cast<RadioButton*>(getControl(300));
  m_medium = dynamic_cast<RadioButton*>(getControl(301));
  m_hard = dynamic_cast<RadioButton*>(getControl(302));

  m_showGhost = dynamic_cast<ToggleButton*>(getControl(200));
  
  m_rotate = dynamic_cast<ToggleButton*>(getControl(400));
  m_showHint = dynamic_cast<ToggleButton*>(getControl(500));

  m_title = dynamic_cast<Label*>(getControlByName("lbl_Preview_PictureName"));
  m_title->setText(picture.getName());

  updateUI(m_modeGroup->getCheckedId());

  Canvas* canvas = dynamic_cast<Canvas*>(getControlByName("cvs_Preview_Picture"));
  if (canvas != 0)
  {
    canvas->setImage(m_picture.getPicture());
  }
}

ChooseModeDlg::~ChooseModeDlg()
{
  RadioButtonGroup::release("Mode");
  RadioButtonGroup::release("Difficulty");
}

void ChooseModeDlg::updateUI(int id)
{
  switch(id)
  {
  case 100: // puzzle is selected
    {
      m_easy->setEnabled(false);
      m_medium->setEnabled(false);
      m_hard->setEnabled(false);
      
      m_showGhost->setEnabled(true);
    }
    break;
  case 101: // swap is selected
    {
      m_easy->setEnabled(true);
      m_medium->setEnabled(true);
      m_hard->setEnabled(true);
      
      m_showGhost->setEnabled(false);
    }
    break;
  default:
    lassert(0 && "Improper mode");
    break;
  }
}

void ChooseModeDlg::actionPerformed(ActionEvent* event)
{
  terminateModal(event->commandId);

  
}

void ChooseModeDlg::radioEvent(RadioButtonEvent* event)
{
  if (event->group == m_modeGroup)
  {
    updateUI(event->commandId);
  }
}