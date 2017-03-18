/* ****************************************************************************
 *
 *  Piece.h
 *  Created by Bert Rosell, on Fri Nov 14 2003, 16:34:20 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the Piece component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__PIECE_H
#define ATC__PIECE_H

#include "Utils.h"
#include "Display.h"

/** Purpose: TODO: Describe the purpose of the class.
 *  (Everything that you write here will show up in the
 *  doc++ generated documentation.)
 */
class Piece: hts::Noncopyable
{
public:
  /// Constructor.
  Piece(HTexture texture, Point coord, bool rot);
  virtual ~Piece();
  
  /** rotates the piece one rotation */
  void rotate();
  
  Point getCoord() { return m_coord; }

  bool isStraight() { return m_cRot==0; }
  
  void draw(Display* display, int x, int y);

  HTexture cTexture() { return m_textures[m_cRot]; }
  
private:
  /* the coord to the puzzle */
  Point m_coord;
  /* the current rotation. 
  Pieces can be in any of 4 orientations
  */
  int m_cRot;
  bool m_rot;

//  RotateSkinHandle m_skin; // rotations handled by RotateSkin

  HTexture m_textures[4];
};
#endif // #ifndef ATC__PIECE_H
 
