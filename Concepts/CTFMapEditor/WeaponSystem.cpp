#pragma warning (disable : 4786)

#include "WeaponSystem.h"
#include "Ship.h"
#include "Projectile.h"

#include <windows.h>


#include "Misc/GameMath.h"

WeaponSystem::WeaponSystem(Ship* ship):
m_ship(ship)
{
  m_rangeOfFire = 200*200; // squared is faster
  m_rateOfFire = 1;
  m_reloadTimer = 0;
}

void WeaponSystem::shoot(Ship* target)
{
  if (m_reloadTimer == 0)
  {
    m_reloadTimer = Timer::create(GT_WEAPONSYSTEM_READY, 1000/m_rateOfFire, this, 0, false);
    Projectile* p = new Projectile(1);
    p->setPosition(m_ship->getPositionf());
    p->setTarget(target);
    p->setVisible(true);
    Engine::instance->theWorld->addMovingThing(*p);
  }
}

bool WeaponSystem::isShipInRange(Ship* other)
{
  Vector v(other->getX() - m_ship->getX(), other->getY() - m_ship->getY());
  return (v.lengthSquared() <= m_rangeOfFire);
}

void WeaponSystem::timeout(TimerEvent* event)
{
  lassert(event->id == GT_WEAPONSYSTEM_READY);
  m_reloadTimer = 0;
}