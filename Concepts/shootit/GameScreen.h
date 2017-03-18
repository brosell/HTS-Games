#ifndef GameScreen_h
#define GameScreen_h

#include "UI.h"
#include "PlayFieldControl.h"

class GameScreen: public IniBasedDialog
{
public:
  GameScreen(IniFile& ini, string name);
  ~GameScreen();

  virtual string getName() { return "GameScreen"; }

private:
  PlayFieldControl m_playFieldControl;
};

#endif