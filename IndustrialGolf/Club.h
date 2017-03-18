#ifndef Club_h
#define Club_h

#include "BR_Game.h"
#include "ThinkScheduler.h"

class Club: public Thing, public KeyListener
{
public:
  Club();
  ~Club();

  virtual void draw(Display* display, int x, int y);

  virtual void keyPressed(KeyPressEvent* event);
  virtual void keyReleased(KeyReleaseEvent* event);

protected:
  void shoot();
  void adjustAim();
private:
  RotateSkinHandle m_skin;
  RotateSkinHandle m_ballSkin;
  TypeThinkDelegate<Club> m_logic;
  void logic();

  Vector m_dirToShoot;
  int m_power;
  bool m_isSpace;
  bool m_goingUp;
};

#endif