#ifndef SpawnTile_h
#define SpawnTile_h

#include "SpaceTile.h"
#include "Ship.h"


#include "Timer.h"



class SpawnTile: public SpaceTile, public TimerListener
{
public:
  SpawnTile(int owner, list<Ship*>& ships);
  ~SpawnTile();

  virtual void tick();

  virtual void timeout(TimerEvent* event);

  virtual bool isNavigable() { return false; }

  virtual void draw(Display* s, int x, int y)
  {
    Thing::draw(s, x, y);
  }


protected:
  HTimer m_waitTimer;

  static RotateSkin* s_skin;

private:
  list<Ship*> m_shipList;
};

#endif