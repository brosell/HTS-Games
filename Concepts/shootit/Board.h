#ifndef Board_h
#define Board_h

#include "BR_Game.h"
#include "HexGrid.h"
#include "Shooter.h"

#include <set>
using namespace std;

#include "CoroutineDelegates.h"

class Board
{
public:
  Board();
  void prepareForNewGame();
  void draw(Display* display);

  void fire();

protected:

  
private:
  Point m_origin;
  Point m_gunsight;
  Shooter m_closestShooter;

  list<Point> m_targets;

  set<Shooter*> m_toBeDrawn;

  Skin* m_ball[5];
  Skin* m_target;

  HexGrid<int> m_grid;

  list<Shooter> m_outerBoundry;

  SpawnableCoroutineTypeDelegate<Board> m_co_boardScript;
  void co_boardScript();
  Shooter closestShooter();
  Point closestTarget();
  void getPossableTargets(set<Point>& ret);

  SpawnableCoroutineTypeDelegate<Board> m_co_shooter;
  void co_shooter();
};


#endif