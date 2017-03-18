#ifndef PhysicsModel_h
#define PhysicsModel_h

#include "Misc/GameMath.h"

class PhysicsModel
{
public:
  int mass;
  int length;
  int width;

  Vector position;
  Vector velocity;

  float maxSpeed;
  float currentSpeed;
  
  float thrust;
  float minimumThrust; // the vehicle must at least use this much thrust to menuver

  int angle;
  float maxForce;
  int maxAngle;
};

#endif