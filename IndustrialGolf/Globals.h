#ifndef Globals_h
#define Globals_h

#include "AssetManager.h"
#include "AM.h"
#include "BR_Game.h"

class Level;

class GolfBall;

class Globals
{
public:
  
  static AM* am;
  static World* world;
  static WorldCanvas* worldCanvas;
  static Console* console;

  static int viewX;
  static int viewY;

  static bool lastViewChangeWasMouse;

  static int tileSize;

  static float hurlStrength;

  static IniFile entityDefs;

  static GolfBall* theBall;

  static Level* theLevel;

  static bool run;
  static void init();
  static void clean();

private:
  static AssetManager* assetManager;
  static IniFile* s_assets;
};

#endif