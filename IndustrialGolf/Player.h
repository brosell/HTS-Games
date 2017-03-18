/* ****************************************************************************
 *
 *  Player.h
 *  Created by Bert Rosell, on Mon Nov 03 2003, 11:17:06 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the Player component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__PLAYER_H
#define ATC__PLAYER_H

#include "Utils.h"
#include "EventGenerator.h"

 /** Purpose: TODO: Describe the purpose of the class.
 *  (Everything that you write here will show up in the
 *  doc++ generated documentation.)
*/
class Player: hts::Noncopyable
{
public:
  /// Constructor.
  Player();
  virtual ~Player();
private:
  EventGenerator* m_eventGenerator;
};
#endif // #ifndef ATC__PLAYER_H
 
