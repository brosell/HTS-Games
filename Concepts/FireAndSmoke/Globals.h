#ifndef Globals_h
#define Globals_h

#include "Misc/AssetManager.h"
#include "Misc/ParticleSystem.h"

class Globals
{
public:
  Globals();

  AssetManager* assetManager;
  Console* console;
  ParticleSystem particleSystem;

};

extern Globals* globals;

#endif