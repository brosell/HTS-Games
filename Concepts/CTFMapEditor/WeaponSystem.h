#ifndef WeaponSystem_h
#define WeaponSystem_h

class Ship;

#include "Timer.h"

class WeaponSystem: public TimerListener
{
public:
  WeaponSystem(Ship* ship);

  void shoot(Ship* target);

  bool isShipInRange(Ship* other);

  virtual void timeout(TimerEvent* event);

protected:
  Ship* m_ship;
  int m_rateOfFire;
  int m_rangeOfFire; // the arc that the weapon can fire in
private:

  HTimer m_reloadTimer;
};

#endif