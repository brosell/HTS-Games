#pragma warning (disable : 4786 4503 4530)
#include "UI.h"
#include "Globals.h"
#include "Level.h"
#include "Game.h"

IniBasedDialog* dia_mainMenu = 0;
IniBasedDialog* dia_gameScreen = 0;

UIListener* uiListener = 0;

void initUI()
{
  uiListener = new UIListener;

  IniFile ini("UI\\dialogs.ini");
  ini.read();
  dia_gameScreen = new IniBasedDialog(ini, "Game");
  Globals::worldCanvas = (WorldCanvas*)dia_gameScreen->getControlByName("WorldCanvas");

  dia_mainMenu = new IniBasedDialog(ini, "Main");
  ((Button*)dia_mainMenu->getControlByName("Start"))->addActionListener(uiListener);
  ((Button*)dia_mainMenu->getControlByName("Quit"))->addActionListener(uiListener);
}

void cleanUI()
{
  delete uiListener;
  delete dia_mainMenu;
  delete dia_gameScreen;
}

void showMainMenu()
{
  dia_gameScreen->hide();
  dia_mainMenu->show();
}

void showGameScreen()
{
  dia_mainMenu->hide();
  dia_gameScreen->show();
}

void UIListener::actionPerformed(ActionEvent* event)
{
  string name = event->thing->getControlName();
  if (name == "Start")
  {
    showGameScreen();
    Game game("Game1");
    game.go();
    showMainMenu();
  }
  else if (name == "Quit")
  {
    Globals::console->execute("quit");
  }
}