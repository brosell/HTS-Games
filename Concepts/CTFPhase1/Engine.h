#ifndef Engine_h
#define Engine_h

#include "Game/World.h"
#include "sqSpaceTileMap.h"

class SpaceTileMap;

class Engine: public ConsoleListener
{
public:
  Engine();
  static Engine* instance;
  World* theWorld;
  SpaceTileMap* theMap;

  IniFile* theRecord;

  virtual void consoleCommand(ConsoleEvent* event);

  void recordStart(string filename);
  void record(string str);
  void recordStop();

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

#include "Ship.h"
#include "PlayerStuff.h"
#include "GameThing.h"


#endif