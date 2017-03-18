#pragma warning (disable : 4786 4503 4530)
#include "UpWind.h"
#include "Globals.h"
#include "AssetManager.h"
#include "GolfBall.h"

UpWind::UpWind():
Entity(10),
m_logic(*this, UpWind::logic)
{
  //ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &m_logic);
  m_skin = Globals::am->getRotateSkin("skn_WindMachine");
  setSkin(m_skin);
}

UpWind::~UpWind()
{

}

void UpWind::logic(float factor)
{
  if (getState() == 0)
  {
    return;
  }

  GolfBall* ball = Globals::theBall;

  setDrawAngle(m_toBlow.anglei());
  FPoint bp = ball->getPositionf();
  FPoint mp = getPositionf();
  float dist = bp.distanceTo(mp);
  
  if (dist < m_toBlow.length()*4)
  {
    if (bp.x > mp.x-30 && bp.x < mp.x+30)
    {
      float affect = (m_toBlow.length() - (dist/4))*factor;
      
      ball->applyForce(m_toBlow.normalize().multiply(affect));
    }
  }
}

void UpWind::logic()
{
  GolfBall* ball = Globals::theBall;

//  while(true)
  {
    ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &m_logic);
    setDrawAngle(m_toBlow.anglei());
    FPoint bp = ball->getPositionf();
    FPoint mp = getPositionf();
    float dist = bp.distanceTo(mp);

    if (dist < m_toBlow.length()*4)
    {
      if (bp.x > mp.x-30 && bp.x < mp.x+30)
      {
        float affect = (m_toBlow.length()) - (dist/4);
        
        ball->applyForce(m_toBlow.normalize().multiply(affect));
      }
    }
  }
}

