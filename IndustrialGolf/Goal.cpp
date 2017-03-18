#pragma warning (disable : 4786 4530 4503)
#include "Goal.h"
#include "Globals.h"
#include "GolfBall.h"

Goal::Goal():
//m_logic(*this, Goal::logic),
Entity(10),
m_run(true)
{
  m_skin = Globals::am->getRotateSkin("skn_Goal");
  setSkin(m_skin);

//  ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &m_logic);

  theGame.uiSystem.addKeyListener(this);
}

Goal::~Goal()
{
  theGame.uiSystem.removeKeyListener(this);
}

void Goal::logic(float factor)
{
  if (m_run)
  {
//    ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &m_logic);
//    if (getPositionf().distanceTo(Globals::theBall->getPositionf()) < 60)
//    {
    if (Thing::checkCollision(this, Globals::theBall))
    {
      goalAchieved();
      m_run = false;
    }
  }
}

//void Goal::tick()
//{
//}

void Goal::goalAchieved()
{
  set<GoalListener*> copy(m_listeners);
  
  set<GoalListener*>::iterator i;
  for (i=copy.begin(); i!=copy.end(); i++)
  {
    (*i)->goalAchieved(this);
  }
}
