/* ****************************************************************************
 *
 *  OscillatingFan.h
 *  Created by Bert Rosell, on Sat Oct 25 2003, 15:01:33 Eastern Daylight Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *

 *
 *
 *  File Contents: Interface and documentation of the OscillatingFan component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__OSCILLATINGFAN_H
#define ATC__OSCILLATINGFAN_H

#include "Entity.h"
#include "ThinkScheduler.h"
 
/** Implements an oscillating fan obsticle
 */
class OscillatingFan: public Entity
{
public:
    /// Constructor.
    OscillatingFan();
    virtual ~OscillatingFan();

    void setPower(int p) { m_power = p; }
    void setRange(int r) { m_range = r; }

    virtual void logic(float factor);

    virtual void setState(int state);
private:
  RotateSkinHandle m_skin;
//  RotateSkinHandle m_off;
  
  TypeThinkDelegate<OscillatingFan> m_logic;
  void logic();

  Vector m_dirToShoot;
  int m_power;
  int m_range;


	// Copying of this class is prohibited:
    OscillatingFan(const OscillatingFan&);
	// Assignment to this class is prohibited:
    OscillatingFan& operator=(const OscillatingFan&);

};
#endif // #ifndef ATC__OSCILLATINGFAN_H
 
