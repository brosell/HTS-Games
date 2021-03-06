#include "Ship.h"
#include "MotionBehaviour.h"
#include "SpaceTile.h"
#include "SpaceTileMap.h"
#include "Engine.h"

#include "CommandPrimitives.h"

set<Ship*> Ship::s_allShips;

Ship::Ship(int owner): 
GameThing(owner, 15, ID_SHIP, true, true, 36),
m_selected(false),
m_spawned(false),
m_currentOrders(ORDERS_NONE),
m_attackingShip(0),
m_attackShip(0),
m_defendShip(0),
m_fleeDistance(1),
m_selfDefenseDistance(1),
m_holdPosition(Point(-1, -1)),
m_speed(1),
m_occupying(0),
m_nextTile(0),
m_nextPrimitive(PRIM_NONE),
m_hitPoints(15)
{
  m_weaponSystem=new WeaponSystem(this);
  s_allShips.insert(this);

  static RotateSkin* skin = 0;

  if (skin == 0)
  {
    skin = new RotateSkin(36);
    skin->addImage("images\\f22-s.bmp", 1);
  }

  setSkin("Skin", skin);

  showSkin("Skin");
}

Ship::~Ship()
{
  s_allShips.erase(this);
}

void Ship::damage(int dam)
{
  m_hitPoints-=dam;
  if (m_hitPoints < 1)
  {
    Engine::instance->theWorld->removeThing(*this);
    //Thing::safeDelete(this);
    m_spawned = false;
  }
}


//static 
Ship* Ship::getClosestEnemy(Ship* toThis)
{
  Point myPos = toThis->getPositioni();
  set<Ship*>::iterator i;
  Ship* closest = 0;
  for (i=s_allShips.begin(); i!=s_allShips.end(); i++)
  {
    if ( (*i)->m_spawned && *i != toThis && (*i)->m_owner != toThis->m_owner)
    {
      if (myPos.isShortestDistance( (*i)->getPositioni()))
      {
        closest = *i;
      }
    }
  }

  return closest;
}

//static 
void Ship::getEnemiesInRadius(Ship* toThis, int radius, list<Ship*>& ret)
{
  int radiusSquared = radius*radius;

  Point myPos = toThis->getPositioni();
  set<Ship*>::iterator i;

  Ship* closest = 0;
  for (i=s_allShips.begin(); i!=s_allShips.end(); i++)
  {
    if ( *i != toThis && (*i)->m_spawned && (*i)->m_owner != toThis->m_owner)
    {
      if ( myPos.distanceToSquared( (*i)->getPositioni()) <= radiusSquared )
      {
        ret.push_back(*i);
      }
    }
  }
}


void Ship::tick()
{
  if (!m_spawned)
  {
    return;
  }

  FPoint pos=getPositionf();
  SpaceTile* start = Engine::instance->theMap->getTileAt(pos.x, pos.y);

  start->setOccupant(this);

  /////////////////////////// TEMP
//  if (m_waypoints.size())
//  {
//    
//    Point wp = m_waypoints.front();
//    SpaceTile* start = Engine::instance->theMap->getTileAt(getX(), getY());
//    //SpaceTile* end = Engine::instance->theMap[wp.x][wp.y];
//    bool success = Engine::instance->theMap->calculateRoute(start->getCoords().x, start->getCoords().y,
//                                             wp.x, wp.y, route);
//  }    
//  return;
  /////////////////////////END TEMP

  if (m_nextPrimitive != PRIM_NONE)
  {
    switch (m_nextPrimitive)
    {
    case PRIM_MOVE:
      {
        continueMoveOneSect();
      }
      break;
    case PRIM_SHOOT:
      {
        continueShoot();
      }
      break;
    default:
      {
        logError(Error, "Unknown Primitive %d", m_nextPrimitive);
      }
      break;
    }
    return;
  }


  switch(m_currentOrders)
  {
  case ORDERS_NONE:
    {
      doNone();
    }
    break;
  case ORDERS_ATTACK:
    {
      if (m_attackShip != 0)
      {
        doAttackShip();
      }
      else if (m_attackPoint != Point(-1, -1))
      {
        doAttackPoint();
      }
      else
      {
        m_currentOrders = ORDERS_NONE;
      }
    }
    break;
  case ORDERS_HOLD_POSITION:
    {
      doHoldPosition();
    }
    break;
  case ORDERS_DEFEND:
    {
      doDefend();
    }
    break;
  case ORDERS_MOVE:
  case ORDERS_COMBAT_MOVE:
    {
      doMove();
    }
    break;
  case ORDERS_PATROL:
    {
      doPatrol();
    }
    break;
  default:
    {
      logError(Error, "Unknown Orders %d", m_currentOrders);
    }
    break;
  }
}

void Ship::doNone()
{
  Point myPos = Engine::instance->theMap->getCoord(getX(), getY());
  if (m_attackingShip != 0 && m_waypoints.size() == 0)
  {
    // being shot at!
    // 1
    Point en = m_attackingShip->getPositioni();
    Point myWPos = getPositioni();

    SpaceTile* tiles[6];
    int count = Engine::instance->theMap->getNeighbors(myPos.x, myPos.y, tiles);

    SpaceTile* furthest = 0;
    int distSq = 0;

    for (int c=0; c<count; c++)
    {
      if (tiles[c]->isNavigable() && tiles[c]->getOccupant() == 0)
      {
        int d = en.distanceToSquared(tiles[c]->getPositioni());
        if (d > distSq)
        {
          distSq = d;
          furthest = tiles[c];
        }
      }
    }

    if (furthest != 0)
    {
      m_waypoints.push_back(furthest->getCoords());
      m_currentOrders = ORDERS_MOVE;
      doMove();
    }
    else
    {
      // nowhere to run!
      // act as if holding this position
      Point savePos = m_holdPosition;
      m_holdPosition = myPos;
      doHoldPosition();
      m_holdPosition = savePos;
    }
  }
  else
  {
    Ship* closestEnemy = Ship::getClosestEnemy(this);
    if (closestEnemy && distanceTo(closestEnemy) <= 100)
    {
      // act as if holding this position
      Point savePos = m_holdPosition;
      m_holdPosition = myPos;
      doHoldPosition();
      m_holdPosition = savePos;
    }
  }
}

void Ship::doHoldPosition()
{
  Point myPos = getPositioni();
  Point mySector = mySect(); 
  SpaceTile* loc = (*Engine::instance->theMap)[m_holdPosition.x][m_holdPosition.y];

  if (mySector != m_holdPosition)
  {
    createMovePrimitive(m_holdPosition);
    return;
  }

  // in position

  list<Ship*> enemiesInSensorRange;
  Ship::getEnemiesInRadius(this, 200, enemiesInSensorRange);

  list<Ship*>::iterator i;

  for (i=enemiesInSensorRange.begin(); i!=enemiesInSensorRange.end(); i++)
  {
    if (m_weaponSystem->isShipInRange( (*i) ) )
    {
      Ship* other = *i;
      m_weaponSystem->shoot( (*i) );
      return;
    }
  }

  // no body in range :(

  Ship* closestEnemy = Ship::getClosestEnemy(this);

  if (closestEnemy != 0)
  {
    FaceBehaviour(m_physicsModel, closestEnemy->getPositioni());
  }
}


void Ship::doMove()
{
  if (m_waypoints.size() == 0)
  {
    m_currentOrders = ORDERS_NONE;
    return;
  }

  Point wp = m_waypoints.front();
  Point mySector = mySect();
  if (mySector == wp)
  {
    // we made it this far!
    m_waypoints.pop_front();
    doMove();
    return;
  }

  // if we get this far, there is at least one waypoint and it is in wp
  createMovePrimitive(wp);  
}

void Ship::doAttackShip()
{
  if ( !m_attackShip->m_spawned)
  {
    // must have been destroyed...
    m_currentOrders = ORDERS_NONE;
    return;
  }

  if (!m_weaponSystem->isShipInRange(m_attackShip))
  {
    if (m_attackShip->m_attackingShip == this)
    {
      m_attackShip->m_attackingShip = 0;
    }

    Point en = m_attackShip->getPositioni();
    Point enPos = Engine::instance->theMap->getCoord(en.x, en.y);
    
    createMovePrimitive(enPos);    
  }
  else
  {      
    m_attackShip->m_attackingShip = this;
    m_weaponSystem->shoot(m_attackShip);
  }
}


void Ship::doAttackPoint()
{

}

void Ship::doDefend()
{

}

void Ship::doPatrol()
{
  /*
    if (getClosestEnemy is in sensor range)
    {
      doAttack(closest enemy)
      return;
    }

    if (mySect == m_patrolRoute1)
    {
      swap(m_patrolRoute1, m_patrolRoute2)
    }
    
    move to m_patrolRoute1
  */
  Ship* enemy = getClosestEnemy(this);
  if (enemy != 0 && distanceTo(enemy) < getSensorRange())
  {
    m_attackShip = enemy;
    doAttackShip();
    m_attackShip = 0;
    return;
  }

  if (mySect() == m_patrolRoute1)
  {
    swap (m_patrolRoute1, m_patrolRoute2);
  }

  Point next = getNextSectTo(m_patrolRoute1);
  createMovePrimitive(next);
}

///////////////////////////////
// COMMANDS
///////////////////////////////

void Ship::holdPosition(Point p)
{
  m_currentOrders = ORDERS_HOLD_POSITION;
  if (p.x == -1)
  {
    m_holdPosition = getPositioni();
  }
  else
  {
    m_holdPosition = p;
  }
}

void Ship::setWaypoint(Point p)
{
  m_currentOrders = ORDERS_MOVE;
  m_waypoints.push_back(p);

  m_defendShip = 0;
  m_attackShip = 0;
  m_attackPoint = Point(-1, -1);
  m_holdPosition = Point(-1, -1);
}

void Ship::clearWaypoints()
{
  m_currentOrders = ORDERS_NONE;
  m_waypoints.clear();
  
  m_defendShip = 0;
  m_attackShip = 0;
  m_attackPoint = Point(-1, -1);
  m_holdPosition = Point(-1, -1);

}

void Ship::move() // uses waypoints
{
  m_defendShip = 0;
  m_attackShip = 0;
  m_attackPoint = Point(-1, -1);
  m_holdPosition = Point(-1, -1);
  m_patrolRoute1 = Point(-1, -1);
  m_patrolRoute2 = Point(-1, -1);

  if (m_waypoints.size() > 0)
  {
    m_currentOrders = ORDERS_MOVE;
  }
  else
  {
    logError(Error, "recieved MOVE command and there are no waypoints");
  }
}

void Ship::attack(Point p)
{
  m_currentOrders = ORDERS_ATTACK;
  m_attackShip = 0;
  m_attackPoint = p;

  m_defendShip = 0;
  m_holdPosition = Point(-1, -1);
  m_waypoints.clear();
  m_patrolRoute1 = Point(-1, -1);
  m_patrolRoute2 = Point(-1, -1);

}

void Ship::attack(Ship* ship)
{
  m_currentOrders = ORDERS_ATTACK;
  m_attackShip = ship;
  m_attackPoint = Point(-1, -1);

  m_defendShip = 0;
  m_holdPosition = Point(-1, -1);
  m_waypoints.clear();
  m_patrolRoute1 = Point(-1, -1);
  m_patrolRoute2 = Point(-1, -1);

}

void Ship::defend(Ship* ship)
{
  m_currentOrders = ORDERS_DEFEND;
  m_defendShip = ship;

  m_attackShip = 0;
  m_attackPoint = Point(-1, -1);
  m_holdPosition = Point(-1, -1);
  m_waypoints.clear();
  m_patrolRoute1 = Point(-1, -1);
  m_patrolRoute2 = Point(-1, -1);
  
}

void Ship::patrol(Point farEnd)
{
  m_patrolRoute1 = farEnd;
  m_patrolRoute2 = mySect();
  m_currentOrders = ORDERS_PATROL;
  m_attackShip = 0;
  m_attackPoint = Point(-1, -1);
  m_holdPosition = Point(-1, -1);
  m_waypoints.clear();
}

int Ship::distanceTo(Ship* other)
{
  int a=getX() - other->getX();
  int b=getY() - other->getY();
  a=a*a;
  b=b*b;

  return sqrt(a+b);
}

void Ship::setDestinationAngle(int x, int y)
{
  FPoint pos = getPositionf();
  Vector vDest(x-(pos.x), y-(pos.y));
  m_destAngle = vDest.anglei();
}

void Ship::spawn()
{
  m_spawned = true;
}

void Ship::continueMoveOneSect()
{
  FPoint myPos = getPositionf();
  SpaceTile* start = Engine::instance->theMap->getTileAt(myPos.x, myPos.y);
  SpaceTile* dest = 0;
  dest = (*Engine::instance->theMap)[m_movePrimitive.destSector.x][m_movePrimitive.destSector.y];
  if (dest->getOccupant() != 0 && dest->getOccupant() != this)
  {
    swap(m_movePrimitive.destSector, m_movePrimitive.srcSector);
    dest = (*Engine::instance->theMap)[m_movePrimitive.destSector.x][m_movePrimitive.destSector.y];
  }

  FPoint destPos = dest->getPositionf();

  Vector toDest(destPos.x - myPos.x, destPos.y - myPos.y);
  toDest = toDest.normalize();
  setDrawAngle(toDest.anglei());
  
  SpaceTile* t = 0;
  for (int c=0; c<m_speed; c++)
  {
    myPos.x+=toDest.x;
    myPos.y+=toDest.y;
    setPosition(myPos);

    t = Engine::instance->theMap->getTileAt(myPos.x, myPos.y);
    if (t != start)
    {
      start->setOccupant(0);
      dest->setOccupant(this);
    }

    if (myPos.distanceToSquared(destPos) <= 2)
    {
      // made it
      setPosition(destPos);
      m_nextPrimitive = PRIM_NONE;
    }
  }
}

void Ship::createMovePrimitive(Point destSect)
{
  Point myPos = mySect();
  Point next = getNextSectTo(destSect);
  if (next.x == -1)
  {
    // can't get there from here
    return;
  }
  
  m_nextPrimitive = PRIM_MOVE;
  m_movePrimitive.destSector = next;
  m_movePrimitive.srcSector = myPos;

  continueMoveOneSect();
}


Point Ship::getNextSectTo(Point dest)
{
  static list<SpaceTile*> route;
  route.clear();

  Point myPos = getPositioni();
  Point startSect = Engine::instance->theMap->getCoord(myPos.x, myPos.y);

  bool success = Engine::instance->theMap->calculateRoute(startSect.x, startSect.y, dest.x, dest.y, route);
  
  if (!success)
  {
    // couldn't find route, try again next turn
    return Point(-1, -1);
  }
  
  if (route.size() == 0)
  {
    //lassert(false); // bad for some reason....
    return Point(-1, -1);
  }
  
  return route.front()->getCoords();
}

void Ship::continueShoot()
{

}