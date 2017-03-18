/* ****************************************************************************
 *
 *  Door.cpp
 *  Created by Bert Rosell, on Sat Nov 01 2003, 09:21:19 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the Door component.
 *  Please see Door.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "Door.h"

#include "GolfBall.h"

/* ********************************* 
 * Door
 ***********************************/
Door::Door(): Entity(10)
{
  m_openSkin = Globals::am->getRotateSkin("skn_OpenDoor"); 
  m_closedSkin = Globals::am->getRotateSkin("skn_ClosedDoor");
  setSkin(m_openSkin);
}

Door::~Door()
{
 
}

void Door::setState(int state)
{
  if (state == 0)
  {
    setSkin(m_closedSkin);
  }
  else
  {
    setSkin(m_openSkin);
  }
  Entity::setState(state);
}

void Door::logic(float factor)
{
  Point pointOnDoor;
  Point pointOnBall;
  if (Thing::checkCollision(this, Globals::theBall, pointOnDoor, pointOnBall))
  {
    pointOnBall.x+=Globals::theBall->getTopLeftX();
    pointOnBall.y+=Globals::theBall->getTopLeftY();

    Line reflect(pointOnBall, Globals::theBall->getPositionf());
    Globals::theBall->reflect(normal(reflect));
  }
}
