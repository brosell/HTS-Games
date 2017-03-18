#ifndef Engine_h
#define Engine_h

#include "Game/World.h"
#include "SpaceTileMap.h"
//#include "Ship.h"

class Engine
{
public:
  static Engine* instance;
  World* theWorld;
  SpaceTileMap* theMap;

  int spawnTileWait;
};

extern Engine* g_engine;

enum THING_ID
{
  ID_NONE,
  ID_SHIP,
  ID_TILE,
  ID_PROJECTILE
};


enum GAME_TIMERS
{
  GT_SPAWNPOINT_READY,
  GT_WEAPONSYSTEM_READY
};


#endif