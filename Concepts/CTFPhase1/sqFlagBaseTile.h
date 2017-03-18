#ifndef FlagBaseTile_h
#define FlagBaseTile_h

#include "sqSpaceTile.h"

class FlagBaseTile: public SpaceTile
{
public:
  FlagBaseTile(int owner);

  virtual void tick();
  virtual bool isNavigable() { return true; }

  
protected:

private:

};

#endif