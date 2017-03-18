#pragma warning (disable : 4503)
#include "Projectile.h"
#include "Engine.h"

RotateSkin* Projectile::skin = 0;

Projectile::Projectile(int owner):
GameThing(owner, 10, ID_PROJECTILE, true, true, 36),
m_targetThing(0),
m_targetPoint(-1, -1),
m_range(250), // pixels
m_speed(3), // pixels
m_turnForce(2) // degrees per tick
{
  if (skin == 0)
  {
    skin = new RotateSkin(36);
    skin->addImage("images\\shot.bmp", 1);
  }

  setSkin("skin", skin);
  showSkin("skin");
}

Projectile::~Projectile()
{

}

Vector Projectile::getVectorToTarget()
{
  FPoint enPos;
  if (m_targetThing != 0)
  {
    SpaceTile* tile = Engine::instance->theMap->getTileAt(m_targetThing->getX(), m_targetThing->getY());
    enPos = tile->getPositionf();
  }
  else if (m_targetPoint.x != -1)
  {
    SpaceTile* tile = Engine::instance->theMap->get(m_targetPoint.x, m_targetPoint.y);
    enPos = tile->getPositionf();
  }

  FPoint myPos = getPositionf();
  return Vector(enPos.x - myPos.x, enPos.y - myPos.y);
}

void Projectile::tick()
{
  if (!hasTarget())
  {
    return;
    setVisible(false);
  }

  SpaceTile* target = 0;
  if(m_targetThing != 0)
  {
    target = Engine::instance->theMap->getTileAt(m_targetThing->getX(), m_targetThing->getY());
  }
  else if (m_targetPoint.x != -1)
  {
    // shoot sector. when it hits, anything in it will be shot
    target = Engine::instance->theMap->get(m_targetPoint.x, m_targetPoint.y);
  }

    
  Vector norm = m_prevVector.normalize();
  m_prevVector = getVectorToTarget();
  setDrawAngle(m_prevVector.anglei());

  FPoint pos = getPositionf();
  FPoint tPos = target->getPositionf();

  for (int c=0; c<m_speed && m_distanceTraveled <= m_range; c++, m_distanceTraveled++)
  {
    pos.x+=norm.x;
    pos.y+=norm.y;
    setPosition(pos);

    if (pos.distanceToSquared(tPos) <= 2)
    {
      setPosition(tPos);
      MessageBeep(-1);
      m_targetThing->damage(2);
      Engine::instance->theWorld->removeThing(*this);
      //delete this;
      Thing::safeDelete(this);
      return;
    }
  }

  if (m_distanceTraveled > m_range)
  {
    Engine::instance->theWorld->removeThing(*this);
    //delete this;
    Thing::safeDelete(this);
    return;
  }

}
