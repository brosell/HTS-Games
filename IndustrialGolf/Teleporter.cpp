/* ****************************************************************************
 *
 *  Teleporter.cpp
 *  Created by Bert Rosell, on Sat Nov 01 2003, 12:48:59 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the Teleporter component.
 *  Please see Teleporter.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "Teleporter.h"
#include "Level.h"


/* ********************************* 
 * Teleporter
 ***********************************/
Teleporter::Teleporter():
Entity(10),
m_inactiveTimer(0),
m_other(0)
{
  m_skin = Globals::am->getRotateSkin("skn_Teleporter");
  setSkin(m_skin);
}

Teleporter::Teleporter(StringMap& parameters):
Entity(10),
m_inactiveTimer(0),
m_other(0)
{
  m_otherId = atoi(parameters["Other"].c_str());
  m_angle = atoi(parameters["ReleaseAngle"].c_str());
  m_speed = atoi(parameters["ReleaseSpeed"].c_str());
  m_enterOnly = atoi(parameters["EnterOnly"].c_str());
  m_exitOnly = atoi(parameters["ExitOnly"].c_str());
  m_skin = Globals::am->getRotateSkin("skn_Teleporter");
  setSkin(m_skin);
}

Teleporter::~Teleporter()
{
  if (m_inactiveTimer != 0)
  {
    Timer::destroy(m_inactiveTimer);
    m_inactiveTimer = 0;
  }
}

void Teleporter::findOther()
{
  Level::iterator i;
  for (i=Globals::theLevel->ebegin(); i!=Globals::theLevel->eend(); i++)
  {
    Teleporter* tele = dynamic_cast<Teleporter*>(*i);
    if (tele != 0 && tele->getId() == m_otherId && tele->m_enterOnly == false)
    {
      m_other = tele;
      return;
    }
  }
}

void Teleporter::logic(float factor)
{
  if (m_other == 0)
  {
    findOther();
  }
  if (m_other == 0)
  {
//    lassert(m_other != 0);
    return;
  }

  if (m_exitOnly)
  {
    return;
  }
  if (m_inactiveTimer != 0)
  {
    return;
  }
  if (Thing::checkCollision(this, Globals::theBall))
  {
    // teleport!
    m_other->takeBall();
    m_inactiveTimer = Timer::create("Tele", 100, 3000, this, 0, false);
  }
}

void Teleporter::takeBall()
{
  GolfBall* gb = Globals::theBall;
  gb->setPosition(getPositionf());
  Vector v = gb->getVelocity();
  float speed = v.length();
  
  if (m_angle >= 0)
  {
    v = Vector::createFromAngle(m_angle, speed);
  }
  if (m_speed >= 0)
  {
    v = v.normalize().multiply(m_speed);
  }
  gb->setVelocity(v);
  m_inactiveTimer = Timer::create("Tele", 100, 3000, this, 0, false);
}

void Teleporter::timeout(TimerEvent* event)
{
  lassert(event->timer = m_inactiveTimer);
  m_inactiveTimer = 0;
}