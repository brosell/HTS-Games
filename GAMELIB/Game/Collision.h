#ifndef _Collision_h
#define _Collision_h

#include "Thing.h"

enum Side
{
  TOP,
  BOTTOM,
  RIGHT,
  LEFT
};

class Collision
{
public:
  Collision(Thing& hitter, Thing& hittee, bool useProportionalSides);

//  static getCollision(Thing& hitter, Thing& hittee);

  Side getHitterSide() { return m_hitterSide; }
  Side getHitteeSide() { return m_hitteeSide; }

private:
  bool m_useProportionalSides;
  Thing& m_hitter;
  Thing& m_hittee;

  Side m_hitterSide;
  Side m_hitteeSide;
  
};


#endif