/* ****************************************************************************
 *
 *  Switch.cpp
 *  Created by Bert Rosell, on Tue Oct 28 2003, 22:31:21 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the Switch component.
 *  Please see Switch.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "Switch.h"

#include "Globals.h"
#include "Golfball.h"
#include "GameMath.h"
#include "Level.h"


/* ********************************* 
 * Switch
 ***********************************/
Switch::Switch():
Entity(9),
m_beDeadTime(0)
{
  m_off = Globals::am->getRotateSkin("skn_Switch_off");
  m_on = Globals::am->getRotateSkin("skn_Switch_on");
  setSkin(m_off);
}
Switch::~Switch()
{
 
}

void Switch::logic(float factor)
{
  if (m_beDeadTime-- > 0)
  {
    return;
  }
  Point pointOnThis;
  Point pointOnBall;
  if (Thing::checkCollision(this, Globals::theBall, pointOnThis, pointOnBall))
  {
    pointOnBall.x+=Globals::theBall->getTopLeftX();
    pointOnBall.y+=Globals::theBall->getTopLeftY();

    Line reflect(pointOnBall, Globals::theBall->getPositionf());
    Globals::theBall->reflect(normal(reflect));
    hitTheSwitch();
  }
//  if (Thing::checkCollision(this, Globals::theBall))
//  {
//    Line reflect(FPoint(getTopLeftX(), getTopLeftY()), FPoint(getTopLeftX()+getWidth(), getTopLeftY()));
//    Globals::theBall->reflect(reflect);
//    hitTheSwitch();
//  }
}

void Switch::hitTheSwitch()
{
  //MessageBeep(-1);
  // triggered!
  Level::iterator i;
  for (i=Globals::theLevel->ebegin(); i!=Globals::theLevel->eend(); i++)
  {
    Entity* ent = (*i);
    if(ent->getId() == getId())
    {
      ent->setState(!ent->getState());
    }
  }
  m_beDeadTime = 30;
}

void Switch::setState(int state)
{
  if (state == 0)
  {
    setSkin(m_off);
  }
  else
  {
    setSkin(m_on);
  }
  Entity::setState(state);
}