#pragma warning (disable : 4503 4530 4786)
#include "Globals.h"

Globals::Globals()
{
  assetManager = new AssetManager("Assets.ini");
  theGame.assetManager = assetManager;
  console = new Console;
}

Globals* globals = 0;