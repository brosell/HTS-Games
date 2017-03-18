/* ****************************************************************************
 *
 *  Playfield.h
 *  Created by Bert Rosell, on Fri Nov 14 2003, 21:06:24 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the Playfield component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__PLAYFIELD_H
#define ATC__PLAYFIELD_H
 
#include "Utils.h"
#include "Piece.h"

/** Purpose: TODO: Describe the purpose of the class.
 *  (Everything that you write here will show up in the
 *  doc++ generated documentation.)
 */
class Playfield: hts::Noncopyable
{
public:
  /// Constructor.
  Playfield();
public:
  virtual ~Playfield();
private:
  Piece* pieces[8 * 6];
};
#endif // #ifndef ATC__PLAYFIELD_H
 
