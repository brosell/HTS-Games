#ifndef UI_h
#define UI_h

#include "BR_Game.h"

extern IniBasedDialog* dia_mainMenu;
extern IniBasedDialog* dia_gameScreen;

void initUI();
void cleanUI();
void showMainMenu();
void showGameScreen();

class UIListener: public ActionListener
{
public:
  virtual void actionPerformed(ActionEvent* event);
};

#endif