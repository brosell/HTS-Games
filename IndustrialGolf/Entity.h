#ifndef Entity_h
#define Entity_h

#include "BR_Game.h"

/**
The Entity class is an abstract basclass for all the entities 
or things in the game. I'm not sure if he ball will be an entity
but it might.

  Each entity will be given the opertunity to mess with the ball
  at every game tick

  Each entity may include a coroutine that performs any longterm
  logic.... To be designed
  */
class Entity: public Thing
{
public:
  Entity(int z);
  virtual ~Entity();

  virtual void logic(float factor) { }

  virtual void setState(int state) { m_state = state; }
  int getState() { return m_state; }
//  int getId() { return m_id; }

  static list<string> getTypes();

private:
  int m_state;
};

#endif