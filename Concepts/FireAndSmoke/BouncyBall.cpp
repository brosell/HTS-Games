#include "BouncyBall.h"
#include "Globals.h"

BouncyBall::BouncyBall():
m_co_logic(*this, BouncyBall::co_logic, "Ball Logic")
{
  m_skin = globals->assetManager->getSkin("skn_Ball_60");
  m_co_logic.spawn();
}

BouncyBall::~BouncyBall()
{
  globals->assetManager->releaseSkin(m_skin);
}

void BouncyBall::co_logic()
{
  //m_velocity = Vector(rand()%5, rand()%5);
  //m_location = FPoint(rand()%300 + 100, rand()%300 + 100);

  m_velocity = Vector(0, 0);
  m_velocity = m_velocity.normalize().multiply(4);
  m_location = FPoint(300, 170);

  int radiusSquared = 30 * 30;
  list<Line>::iterator i;
  while(true)
  {
    Vector uV = m_velocity.normalize();
    float l = m_velocity.length();
    if (l >= 1)
    {
      
      for (int c=0; c<l; c++)
      {
        m_location.x += uV.x;
        m_location.y += uV.y;
        
        for (i=m_reflectors.begin(); i!=m_reflectors.end(); i++)
        {
          Line l = *i;
          if (distToSegmentSquared(m_location, l) <= radiusSquared)
          {
            // reflect!
            Vector newV = reflection(m_velocity, l);
            newV = newV.normalize();
            uV = newV;
            newV = newV.multiply(m_velocity.length()*.95);
            m_velocity = newV;
            if (m_velocity.length() < 1) break;
            
            m_location.x += uV.x;
            m_location.y += uV.y;
          }
        }
      }
    }
    else
    {

    applyGravity();
    GameScheduler::resumeAt(NEXT_FRAME);
  }
}

void BouncyBall::draw(Display* display)
{
  m_skin->blit(display, m_location.x, m_location.y, true);
}

void BouncyBall::applyGravity()
{
  m_velocity.y += 2;
}
