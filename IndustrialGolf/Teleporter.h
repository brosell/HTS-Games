/* ****************************************************************************
*
*  Teleporter.h
*  Created by Bert Rosell, on Sat Nov 01 2003, 12:48:58 Eastern Standard Time
*
*  Copyright (c) 2003, Bert Rosell
*
*
*
*  File Contents: Interface and documentation of the Teleporter component.
*
*************************************************************************** */

#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__TELEPORTER_H
#define ATC__TELEPORTER_H

#include "Entity.h"
#include "AM.h"
#include "Globals.h"
#include "GolfBall.h"
#include "IniFile.h"

/** Purpose: TODO: Describe the purpose of the class.
*  (Everything that you write here will show up in the
*  doc++ generated documentation.)
*/
class Teleporter: public Entity, public TimerListener
{
public:
  /// Constructor.
  Teleporter();
  Teleporter(StringMap& parameters);
  virtual ~Teleporter();

  virtual void logic(float factor);
  
  void setOther(int id) { m_otherId = id; }
  void setReleaseAngle(int a) { m_angle = a; }
  void setReleaseSpeed(int s) { m_speed = s; }
  void setEnterOnly(bool b) { m_enterOnly = b; }
  void setExitOnly(bool b) { m_exitOnly = b; }

  virtual void timeout(TimerEvent* event);
  
protected:
  // called by other when it is delivering
  void takeBall();
  void findOther();
private:
  // Copying of this class is prohibited:
  Teleporter(const Teleporter&);
private:
  // Assignment to this class is prohibited:
  Teleporter& operator=(const Teleporter&);

  Teleporter* m_other;
  
  int m_otherId;
  int m_angle;
  int m_speed;
  bool m_enterOnly;
  bool m_exitOnly;

  HTimer m_inactiveTimer;

  RotateSkinHandle m_skin;
};
#endif // #ifndef ATC__TELEPORTER_H
 
