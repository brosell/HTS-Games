#ifndef Listeners_h
#define Listeners_h

#include "BR_Game.h"
#include "Shape.h"

#include "HighScores.h"
#include "Board.h"
#include "Globals.h"

void startGame();
void endGame();
void showCredits();
void showMainScreen();
void showHighScores();
void showOptions();

extern Board* board;

class StartGameListener: public ActionListener
{
public:
  virtual void actionPerformed(ActionEvent* ev)
  { 
    // must be start button!
    startGame();
  }
};

class AppFocus: public AppListener
{
public:
  AppFocus(): m_haveFocus(true) { }
  virtual void appLostFocus();
  virtual void appQuitRequest();
  virtual void appGainedFocus() { m_haveFocus = true; }

  bool haveFocus() { return m_haveFocus; }
private:
  bool m_haveFocus;
};

class MenuListener: public ActionListener
{
public:
  virtual void actionPerformed(ActionEvent* ev);
};

class OptionsListener: public DialogListener
{
public:
  virtual void onOk(DialogEvent* event) 
  {
    showMainScreen();
  }
  virtual void onCancel(DialogEvent* event)  
  {
    showMainScreen();
  }
};


class GameListener: public KeyListener, public ActionListener
{
public:
  virtual void keyPressed(KeyPressEvent* ev);


  virtual void actionPerformed(ActionEvent* event);
};

extern IniBasedDialog* dia_enterHighScoreScreen;
extern HighScores g_highScores;
extern TextBox* txt_highScoreName;
extern int g_lastScore;
extern int g_lastLevel;

class EnterHighScoreListener: public ActionListener, public KeyListener
{
  virtual void actionPerformed(ActionEvent* ev)
  {
    // must be OK button
    setHighScore();
  }

  virtual void keyPressed(KeyPressEvent* ev)
  {
    if (ev->keySym == SDLK_RETURN)
    {
      Button* but = dynamic_cast<Button*>(dia_enterHighScoreScreen->getControlByName("OkButton"));
      MouseClickEvent ev1;
      but->onMouseClick(&ev1);
    }
  }

  void setHighScore()
  {
    g_highScores.addScore(txt_highScoreName->getText(), g_lastLevel, g_lastScore, Globals::skill, !Globals::clearBlocksAtLevelUp);
    g_highScores.save("HighScores.ini");
  }

};

class GameConsoleListener: public KeyListener, public ConsoleListener
{
public:
  GameConsoleListener();

  virtual void keyPressed(KeyPressEvent* event);

  virtual void consoleCommand(ConsoleEvent* event);
private:
  bool consoleShowing;

};


#endif