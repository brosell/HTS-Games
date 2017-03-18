#include "GameDialog.h"
#include "Globals.h"

GameDialog::GameDialog(IniFile& ini, string name): IniBasedDialog(ini, name), m_showMouseTimer(0), m_mouseShowing(false)
{
  m_background = getBackground();
  Score::addListener(this);
  m_showMouseTimer = Timer::create("MouseHider", 100, 1000, this, 0, true);

  Button* pause = dynamic_cast<Button*>(getControlByName("GamePauseButton"));
  if (pause != 0)
  {
    pause->setId(200);
    pause->addActionListener(this);
  }

  Button* quit = dynamic_cast<Button*>(getControlByName("GameQuitButton"));
  if (quit != 0)
  {
    quit->setId(201);
    quit->addActionListener(this);
  }
}

GameDialog::~GameDialog()
{
  if (m_showMouseTimer != 0)
  {
    Timer::destroy(m_showMouseTimer);
  }

  Score::removeListener(this);
}

void GameDialog::actionPerformed(ActionEvent* event)
{
  switch(event->commandId)
  {
  case 200:
    Globals::console->execute("pausegame");
    break;
  case 201:
    Globals::console->execute("quitgame");
    break;
  default:
    lassert(0 && "unexpect action id");
    break;
  }
}



void GameDialog::timeout(TimerEvent* event)
{
  UIThing* mouseOver = s_mouseOver;
  while(mouseOver != 0 && mouseOver != dynamic_cast<GameDialog*>(this)) 
  {
    mouseOver = mouseOver->getParent();
  } 

  if (mouseOver == dynamic_cast<GameDialog*>(this) && theGame.uiSystem.topModal() == 0)
  {
    if (theGame.isCursorShowing())
    {
      if (m_mouseShowing == true)
      {
        theGame.showCursor(false);
      }
      else
      {
        m_mouseShowing = true;
      }
    }
  }
}

void GameDialog::onMouseMove(MouseMoveEvent* event)
{
  theGame.showCursor(true);
  IniBasedDialog::onMouseMove(event);
}