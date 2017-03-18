/* ****************************************************************************
 *
 *  DownFacingSwitch.cpp
 *  Created by Bert Rosell, on Tue Oct 28 2003, 16:08:43 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the DownFacingSwitch component.
 *  Please see DownFacingSwitch.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "DownFacingSwitch.h"

#include "Globals.h"
#include "Golfball.h"
#include "GameMath.h"
#include "Level.h"


/* ********************************* 
 * DownFacingSwitch
 ***********************************/
DownFacingSwitch::DownFacingSwitch():
Entity(9),
m_beDeadTime(0)
{
  m_off = Globals::am->getRotateSkin("skn_DownFacingSwitch");
  m_on = Globals::am->getRotateSkin("skn_DownFacingSwitch_on");
  setSkin(m_off);
}

DownFacingSwitch::~DownFacingSwitch()
{
 
}

void DownFacingSwitch::logic(float factor)
{
  if (m_beDeadTime-- > 0)
  {
    return;
  }
  if (Thing::checkCollision(this, Globals::theBall))
  {
    Line reflect(FPoint(getTopLeftX(), getTopLeftY()), FPoint(getTopLeftX()+getWidth(), getTopLeftY()));
    Globals::theBall->reflect(reflect);
    hitTheSwitch();
  }
}

void DownFacingSwitch::hitTheSwitch()
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

  
//  FPoint gpos = Globals::theBall->getPositionf();
//
//  Line trigger(FPoint(getTopLeftX(), getTopLeftY()), FPoint(getTopLeftX()+getWidth(), getTopLeftY()));
//
//  float dist = distToSegment(gpos, trigger);
//    
//  if ( dist < 30)
//  {
//    MessageBeep(-1);
//    // triggered!
//    Level::iterator i;
//    for (i=Globals::theLevel->ebegin(); i!=Globals::theLevel->eend(); i++)
//    {
//      Entity* ent = (*i);
//      if(ent->getId() == getId())
//      {
//        ent->setState(!ent->getState());
//      }
//    }
//  }
//}