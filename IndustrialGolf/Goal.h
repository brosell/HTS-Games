#ifndef Goal_h
#define Goal_h

#include <set>
using namespace std;

#include "Log.h"

#include "ThinkScheduler.h"

#include "Entity.h"


class Goal;

class GoalListener
{
public:
  virtual void goalAchieved(Goal* goal) = 0;
};


/**
  Goal represents the hole. When the ball comes in contact 
  with the goal, the endLevel event is triggered causing
  the next level to load and start.
*/
class Goal: public Entity, public KeyListener
{
public:
  Goal();
  ~Goal();

  void addListener(GoalListener* listener) 
  { 
    lassert(m_listeners.find(listener) == m_listeners.end());
    m_listeners.insert(listener); 
  }
  void removeListener(GoalListener* listener) 
  { 
    lassert(m_listeners.find(listener) != m_listeners.end());
    m_listeners.erase(listener); 
  }

  virtual void keyPressed(KeyPressEvent* event)
  {
    if (event->keySym == SDLK_g)
    {
      goalAchieved();
    }
  }

//  virtual void tick();
  virtual void logic(float factor);

protected:
  void goalAchieved();

private:

  RotateSkinHandle m_skin;

  set<GoalListener*> m_listeners;

//  TypeThinkDelegate<Goal> m_logic;
  void logic();

  bool m_run;
};

#endif