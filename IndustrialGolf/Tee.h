#ifndef Tee_h
#define Tee_h

#include "Entity.h"
#include "GolfBall.h"

class Tee: public Entity
{
public:
  Tee();
  ~Tee();

private:
  void co_logic();
  
  RotateSkinHandle m_skin;
};

#endif