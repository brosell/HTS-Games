/* ****************************************************************************
 *
 *  Door.h
 *  Created by Bert Rosell, on Sat Nov 01 2003, 09:21:19 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the Door component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__DOOR_H
#define ATC__DOOR_H
 
#include "Entity.h"
#include "Globals.h"
#include "AM.h"

/** Purpose: It's a door that can be opened or closed with
  * a switch.
 */
class Door: public Entity
{
public:
    /// Constructor.
    Door();

    void setClosedSkin(string skn) { m_closedSkin = Globals::am->getRotateSkin(skn); }
    void setOpenSkin(string skn) { m_openSkin = Globals::am->getRotateSkin(skn); }

    virtual void setState(int state);

    void logic(float factor);
public:
    virtual ~Door();

private:
	// Copying of this class is prohibited:
    Door(const Door&);

  enum DoorState
  {
    DS_UNDEF,
    DS_CLOSED,
    DS_OPENING,
    DS_OPEN,
    DS_CLOSING
  };

  RotateSkinHandle m_closedSkin;
  RotateSkinHandle m_openSkin;

	// Assignment to this class is prohibited:
    Door& operator=(const Door&);

};
#endif // #ifndef ATC__DOOR_H
 
