#pragma warning (disable : 4786 4503 4530)
#include "Globals.h"
#include "BR_Game.h"
#include "GolfBall.h"
#include "Level.h"

GolfBall* Globals::theBall = 0;
Level* Globals::theLevel = 0;

AssetManager* Globals::assetManager = 0;
IniFile* Globals::s_assets = 0;
AM* Globals::am = 0;
World* Globals::world = 0;

Console* Globals::console = 0;

int Globals::viewX = 0;
int Globals::viewY = 0;

float Globals::hurlStrength = 2;

bool Globals::lastViewChangeWasMouse = false;

bool Globals::run = true;

int Globals::tileSize = 30;

IniFile Globals::entityDefs("EntityDef.ini");

WorldCanvas* Globals::worldCanvas = 0;

void Globals::init()
{
  assetManager = new AssetManager("Assets.ini");
  s_assets = new IniFile("Assets.ini");
  s_assets->read();
  am = new AM(*s_assets);

  assetManager->verify();

  theGame.assetManager = assetManager;
  theGame.am = am;
  console = new Console;
  console->setFont(theGame.am->getFont("fnt_Default"));

  IniFile defaults("Defaults.ini");
  defaults.read();
  tileSize = defaults.getInt("Tile", "Size");

  hurlStrength = defaults.getInt("Hurl", "HurlStrength");

  entityDefs.read();
}

void Globals::clean()
{
  delete console;
  assetManager->unload();
  delete assetManager;
}
