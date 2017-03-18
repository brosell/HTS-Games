/* ****************************************************************************
 *
 *  Star.cpp
 *  Created by Bert Rosell, on Sat Nov 01 2003, 12:24:37 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the Star component.
 *  Please see Star.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "Star.h"
#include "GolfBall.h"
#include "Globals.h"

/* ********************************* 
 * Star
 ***********************************/
Star::Star():
Entity(10)
{
  m_skin = Globals::am->getRotateSkin("skn_Star");
  setSkin(m_skin);
}

Star::~Star()
{
 
}

void Star::logic(float factor)
{
  if (Thing::checkCollision(this, Globals::theBall))
  {
    // FIXME: remove from world and delete
    this->setVisible(false);
  }
}