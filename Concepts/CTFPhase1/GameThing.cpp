#pragma warning (disable : 4503)

#include "GameThing.h"
#include "Engine.h"

Point GameThing::mySect()
{ 
  return Engine::instance->theMap->getCoord(getX(), getY()); 
}