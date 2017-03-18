#ifndef GameDialog_h
#define GameDialog_h

#include "BR_Game.h"
#include "Timer.h"

#include "Score.h"

class GameDialog: public IniBasedDialog, public ScoreListener, public MouseListener, public TimerListener
{
public:
  GameDialog(IniFile& ini, string name);

  ~GameDialog();

  virtual void levelChanged(LevelChangeEvent* ev)
  {
    m_background->setFPS(ev->currentLevel);
  }

  virtual void show()
  {
    m_background->setFPS(Score::getCurrentLevel());
    IniBasedDialog::show();
  }

  virtual void timeout(TimerEvent* event);

  virtual void onMouseMove(MouseMoveEvent* event);

  virtual void actionPerformed(ActionEvent* event);


private:
  SharedSkinHandle m_background;
  bool m_mouseShowing;

  HTimer m_showMouseTimer;
};

#endif