#pragma warning (disable : 4503 4530 4786)
#include "GameScreen.h"

GameScreen::GameScreen(IniFile& ini, string name):
IniBasedDialog(ini, name)
{
  m_playFieldControl.setPosition(Rect::parseRect(ini[name]["PlayFieldPosition"]));
  addUIThing(&m_playFieldControl);
  setFocus(&m_playFieldControl);
  addMouseListener(&m_playFieldControl);
}

GameScreen::~GameScreen()
{

}