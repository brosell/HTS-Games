#ifndef MotionBehaviour_h
#define MotionBehaviour_h

#include "PhysicsModel.h"

void ArriveBehaviour(PhysicsModel* model, Point destination, Vector destAngle=Vector(-1, -1));
void SeekBehaviour(PhysicsModel* model, Point destination, Vector destAngle=Vector(-1, -1));
void FaceBehaviour(PhysicsModel* model, Point destination, Vector destAngle=Vector(-1, -1));



#endif