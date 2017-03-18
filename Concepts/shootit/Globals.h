#ifndef Globals_h
#define Globals_h

#include "Misc/AssetManager.h"

class Globals
{
public:
  Globals();

  AssetManager* assetManager;
  Console* console;

};

extern Globals* globals;

#endif