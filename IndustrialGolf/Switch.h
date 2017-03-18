/* ****************************************************************************
 *
 *  Switch.h
 *  Created by Bert Rosell, on Tue Oct 28 2003, 22:31:21 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the Switch component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__SWITCH_H
#define ATC__SWITCH_H
 
#include "Entity.h"

/** Purpose: TODO: Describe the purpose of the class.
 *  (Everything that you write here will show up in the
 *  doc++ generated documentation.)
 */
class Switch: public Entity
{
public:
    /// Constructor.
    Switch();
    virtual ~Switch();

    virtual void logic(float factor);

    virtual void setState(int state);

protected:
  void hitTheSwitch();

private:
	// Copying of this class is prohibited:
    Switch(const Switch&);
private:
	// Assignment to this class is prohibited:
    Switch& operator=(const Switch&);

    RotateSkinHandle m_off;
    RotateSkinHandle m_on;

    int m_beDeadTime;
};
#endif // #ifndef ATC__SWITCH_H
 
