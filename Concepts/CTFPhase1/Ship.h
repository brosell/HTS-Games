#ifndef Ship_h
#define Ship_h

#include "Game/Thing.h"
#include "WeaponSystem.h"
#include "PhysicsModel.h"
#include "SpaceTile.h"
#include "Engine.h"

#include "CommandPrimitives.h"
#include "GameThing.h"
enum Orders
{
  ORDERS_NONE,
  ORDERS_ATTACK,
  ORDERS_COMBAT_MOVE,
  ORDERS_HOLD_POSITION,
  ORDERS_DEFEND,
  ORDERS_MOVE,
  ORDERS_PATROL
};

class Ship: public GameThing
{
public:

  Ship(int owner);
  ~Ship();
  
  void hit(Thing* other);
  void tick();

  int getSensorRange() { return 3; } // so the engine can draw the fog-o-war
  int getWeaponRange() { return 1;};
//  Command** getCommands();


  static Ship* getClosestEnemy(Ship* toThis);
  static Ship* getClosestShip(Point toThis);
  static void getEnemiesInRadius(Ship* toThis, int radius, list<Ship*>& ret);

// SHIP MANAGER STUFF
  
  void setSelected(bool s) { m_selected = s; }
  bool isSelected() { return m_selected; }

  void setDestination(int x, int y) { m_arrived = false; m_waypoints.clear(); addWaypoint(Point(x, y)); m_currentOrders = ORDERS_MOVE;}
  void setDestinationAngle(int x, int y);
  void addWaypoint(Point waypoint) { m_waypoints.push_back(Engine::instance->theMap->getCoord(waypoint.x, waypoint.y));  m_currentOrders = ORDERS_MOVE; }


  void spawn();
  bool isSpawned() { return m_spawned; }
  virtual void damage(int dam);


  virtual void draw(Display* d, int x, int y);
  list<SpaceTile*> route;

  ////////////////////
  // FLAG
  ////////////////////
  int m_flag;
protected:

  int m_mass;
  int m_availableMass; // starts as mass and adjusts because of ION blasts, FIXME: does it recharge?
  int m_driveDistribution;
  int m_sensorDistribution;
  int m_shieldDistribution;
  int m_weaponDistribution;
  int m_weaponRateOfFire;

  int m_speed;
  SpaceTile* m_occupying; //?????
  bool m_arrived;

  bool m_cloakable;
  bool m_cloacked;
  int m_availableCloakPower; // affected by ION blasts. cloaking uses cloak power. when there is no power the cloak fails
  
  bool m_cloakDetector;

  int m_hitPoints;  // does power drop with less HP?

  WeaponSystem* m_weaponSystem;

  PhysicsModel* m_physicsModel;


//  list<SpaceTile*> route;
  
  SpaceTile* m_nextTile;
  
  ////////////////////////////////
  // ORDERS
  ////////////////////////////////
  void doHoldPosition();
  void doMove();
  void doAttackShip();
  void doAttackPoint();
  void doDefend();
  void doNone();
  void doPatrol();

  Point m_holdPosition;
  list<Point> m_waypoints;
  
  Point m_attackPoint;
  Ship* m_attackShip;
  
  Ship* m_defendShip;

  Point m_patrolRoute1;
  Point m_patrolRoute2;

  Ship* m_attackingShip; // is attacking me!

  int m_fleeDistance; // the distance to try to flee to if we are under attack and not holding position
  int m_selfDefenseDistance; // if an enemy crosses this distance and the ship is in NONE mode and not being attacked, then the shiop will shoot at the enemey

  Orders m_currentOrders;

  ///////////////////////////////////
  // COMMAND PRIMITIVES
  ///////////////////////////////////
  void createMovePrimitive(Point destSect);
  void continueMoveOneSect();


  void continueShoot();

  enum PrimitiveType
  {
    PRIM_NONE,
    PRIM_MOVE,
    PRIM_SHOOT
  };

  PrimitiveType m_nextPrimitive;

  Point getNextSectTo(Point dest);
private:
  MoveOneSect m_movePrimitive;


  ///////////////////////////////////
  // COMMANDING
  ///////////////////////////////////
public:
  void holdPosition(Point p);
  
  void setWaypoint(Point p);
  void clearWaypoints();
  
  void move(); // uses waypoints

  void attack(Point p);
  void attack(Ship* ship);

  void defend(Ship* ship);

  void patrol(Point farEnd);

  static bool s_showRoute;

private:
  int distanceTo(Ship* other);

public:
  static list<Ship*> s_allShips;

private:



  // hide from public interface
  Ship(const Ship& other); // no copying
  operator = (const Ship& other); // no assigning


  // SHIP MANAGER STUFF
  bool m_selected;
  Angle m_destAngle;

  bool m_spawned;
};

#endif