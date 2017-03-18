#ifndef Projectile_h
#define Projectile_h

//#include "Game/Thing.h"
#include "GameThing.h"

class Projectile: public GameThing
{
public:
  Projectile(int owner);
  ~Projectile();

  void setTarget(GameThing* thing)
  {
    m_targetThing = thing; 
    m_targetPoint=Point(-1, -1);
    m_distanceTraveled = 0;
    m_prevVector = getVectorToTarget();
  }
  void setTarget(Point p)
  {
    m_targetPoint = p; 
    m_targetThing = 0;
    m_distanceTraveled = 0;
    m_prevVector = getVectorToTarget();
  }

  void tick();

  bool hasTarget() { return (m_targetThing != 0 || m_targetPoint.x != -1); }

protected:
  Vector getVectorToTarget();

private:
  GameThing* m_targetThing;
  Point m_targetPoint;

  int m_range;
  int m_speed;
  int m_turnForce;

  Angle m_prevAngle;
  int m_distanceTraveled;
  Vector m_prevVector;

  static RotateSkin* skin;


};

#endif