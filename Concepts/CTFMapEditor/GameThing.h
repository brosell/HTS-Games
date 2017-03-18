#ifndef GameThing_h
#define GameThing_h

#include "Game/Thing.h"

class GameThing: public Thing
{
public:
  virtual void damage(int dam) { }

  void setOwner(int o) { m_owner = o; }
  int getOwner() { return m_owner; }

protected:
  GameThing(int owner, int z, int id, bool strikable, bool visible, int rotations):
    Thing(z, id, strikable, visible, rotations),
    m_owner(owner)
    {
    }


protected:
  int m_owner; // which player
};


#endif