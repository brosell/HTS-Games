#ifndef BouncyBall_h
#define BouncyBall_h

#include "BR_Game.h"
#include "Tasking/GameScheduler.h"

class BouncyBall
{
public:
  BouncyBall();
  ~BouncyBall();

  void addReflector(Line l) { m_reflectors.push_back(l); }

  void draw(Display* display);

private:
  GameCoroutineTypeDelegate<BouncyBall> m_co_logic;
  void co_logic();
  void applyGravity();

  list<Line> m_reflectors;

  Skin* m_skin;

  FPoint m_location;
  Vector m_velocity;
};


#endif