/* ****************************************************************************
 *
 *  OscillatingFan.cpp
 *  Created by Bert Rosell, on Sat Oct 25 2003, 15:01:33 Eastern Daylight Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *

 *
 *
 *  File Contents: Implementation of the OscillatingFan component.
 *  Please see OscillatingFan.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "OscillatingFan.h"
#include "Globals.h"
#include "GolfBall.h"

OscillatingFan::OscillatingFan():
Entity(9),
m_logic(*this, OscillatingFan::logic),
m_power(100),
m_range(100)
{
  m_skin = Globals::am->getRotateSkin("skn_OscillatingFan_on");

  setSkin(m_skin);
}

OscillatingFan::~OscillatingFan()
{
 
}

void OscillatingFan::setState(int state)
{
  if (state == 0 && getState() != 0)
  {
    // flipped to off
    //showSkin("Off");
//    getCurrentSkin().setFPS(0);
    m_skin->setFPS(0);
  }
  else if (state != 0 && getState() == 0)
  {
    // flipped to on
    //showSkin("On");
//    getCurrentSkin().setFPS(10);
    m_skin->setFPS(10);
//    m_on->reset();
  }
  Entity::setState(state);
}


void OscillatingFan::logic(float factor)
{
  if (getState() == 0)
  {
    //m_skin->setFPS(0);
    return;
  }
  int f = m_skin->currentFrameNum();

  int blowDir = m_power;
  switch (f)
  {
  case 0:
  case 1:
  case 2:
    //blow left
    blowDir *= -1;
    break;
  case 6:
  case 7:
  case 8:
    // blow right
    break;
  default:
    return;
  }

  FPoint ballpos = Globals::theBall->getPositionf();
  FPoint mypos = getPositionf();
  if (ballpos.y < mypos.y && ballpos.y > mypos.y-75) // at correct height
  {
    float dist = mypos.distanceTo(ballpos);
    if (dist < m_range)
    {
      if (blowDir >= 0 && ballpos.x > mypos.x)
      {
        Globals::theBall->applyForce(Vector(1, 0).multiply(m_power*factor));
      }
      else
      {
        Globals::theBall->applyForce(Vector(-1, 0).multiply(m_power*factor));
      }
    }
  }

}
void OscillatingFan::logic()
{
  // frame 0 and 1 and 2 are blow left
  // frame 6, 7, 8 are blow right
  int f = m_skin->currentFrameNum();

  int blowDir = m_power;
  switch (f)
  {
  case 0:
  case 1:
  case 2:
    //blow left
    blowDir *= -1;
    break;
  case 6:
  case 7:
  case 8:
    // blow right
    break;
  default:
    ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &m_logic);
    return;
  }

  FPoint ballpos = Globals::theBall->getPositionf();
  FPoint mypos = getPositionf();
  if (ballpos.y < mypos.y && ballpos.y > mypos.y-75) // at correct height
  {
    float dist = mypos.distanceTo(ballpos);
    if (dist < m_range)
    {
      if (blowDir >= 0 && ballpos.x > mypos.x)
      {
        Globals::theBall->applyForce(Vector(1, 0).multiply(m_power));
      }
      else
      {
        Globals::theBall->applyForce(Vector(-1, 0).multiply(m_power));
      }
    }
  }

  ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &m_logic);
}
