#pragma warning (disable : 4786 4503 4530)
#include "GameModeDialog.h"
#include "Globals.h"

GameModeDialog::GameModeDialog(IniFile& ini, string name):
IniBasedDialog(ini, name)
{
  setButtonHandler(10, this);
  setButtonHandler(11, this);
  setButtonHandler(12, this);
//  setButtonHandler(13, this);
  setButtonHandler(14, this);

  Button* button = 0;

  button = (Button*)getControl(10);
  button->addMouseListener(this);

  button = (Button*)getControl(11);
  button->addMouseListener(this);
  
  button = (Button*)getControl(12);
  button->addMouseListener(this);
  
  button = (Button*)getControl(213);
  button->addMouseListener(this);
  button->setVisible(false);
  
  button = (Button*)getControl(214);
  button->addMouseListener(this);
  button->setVisible(false);
  
  button = (Button*)getControl(14);
  button->addMouseListener(this);

  m_textArea = dynamic_cast<TextArea*>(getControlByName("DescriptionArea"));
  m_survivorToggle = dynamic_cast<ToggleButton*>(getControl(213));
}

void GameModeDialog::actionPerformed(ActionEvent* event)
{
  if (event->commandId != 14)
  {
    terminateModal(event->commandId);
  }
//  else if (event->commandId == 13)
//  {
//    return;
//  }
  else
  {
    terminateModal(-1);
  }
}

void GameModeDialog::mouseEntered(MouseEnterEvent* event)
{
  switch(event->commandId)
  {
  case 10:
    m_textArea->setText(Globals::am->getText("txt_Level1").c_str());
    break;
  case 11:
    if (Globals::isDemo)
    {
      m_textArea->setText("Medium is not available in DEMO");
    }
    else
    {
      m_textArea->setText(Globals::am->getText("txt_Level5").c_str());
    }
    break;
  case 12:
    if (Globals::isDemo)
    {
      m_textArea->setText("Hard is not available in the DEMO");
    }
    else
    {
      m_textArea->setText(Globals::am->getText("txt_Level10").c_str());
    }
    break;
  case 213:
    m_textArea->setText(Globals::am->getText("txt_Normal_desc").c_str());
    break;
  case 214:
    if (Globals::isDemo)
    {
      m_textArea->setText("Survivor Mode is not available in the DEMO");
    }
    else
    {
      m_textArea->setText(Globals::am->getText("txt_Survivor_desc").c_str());
    }
    break;
  }

}

void GameModeDialog::mouseClicked(MouseClickEvent* event)
{
  if (event->commandId == 13)
  {
    MouseEnterEvent ev;
    ev.commandId = 13;
    mouseEntered(&ev);
  }
  else if (event->commandId == 214 && Globals::isDemo)
  {
    m_survivorToggle->setChecked(true);
  }

}

void GameModeDialog::mouseExited(MouseExitEvent* event)
{
  m_textArea->setText("");
}