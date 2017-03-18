/* ****************************************************************************
 *
 *  DownFacingSwitch.h
 *  Created by Bert Rosell, on Tue Oct 28 2003, 16:08:43 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the DownFacingSwitch component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__DOWNFACINGSWITCH_H
#define ATC__DOWNFACINGSWITCH_H
 
#include "Entity.h"



/** Purpose: This is a switch that toggles the state 
 *    of another entity(ies). When activated, it will toggle the
 *    the states of all entities with the same id
 */
class DownFacingSwitch: public Entity
{
public:
    /// Constructor.
    DownFacingSwitch();
    virtual ~DownFacingSwitch();

    virtual void logic(float factor);

    virtual void setState(int state);

protected:
  void hitTheSwitch();
private:
	// Copying of this class is prohibited:
    DownFacingSwitch(const DownFacingSwitch&);
private:
	// Assignment to this class is prohibited:
    DownFacingSwitch& operator=(const DownFacingSwitch&);

    AM::RotateSkinHandle m_off;
    AM::RotateSkinHandle m_on;

    int m_beDeadTime;
};
 
#include "DownFacingSwitch.icc"
#endif // #ifndef ATC__DOWNFACINGSWITCH_H
 
