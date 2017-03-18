/* ****************************************************************************
 *
 *  Picture.h
 *  Created by Bert Rosell, on Fri Nov 14 2003, 21:19:32 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the Picture component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__PICTURE_H
#define ATC__PICTURE_H
 
#include "Utils.h"
#include <string>
#include <set>

#include "Piece.h"

using namespace std;
/** Purpose: 
 *  Represents the picture. Creates all the pieces.
 */
class Picture: hts::Noncopyable
{
public:
  /// Constructor.
  Picture(string filename);
  virtual ~Picture();
  
  typedef set<Piece*>::iterator piece_iterator;
  piece_iterator begin_piece() { return m_pieces.begin(); }
  piece_iterator end_piece() { return m_pieces.end(); }

  void chop(bool rot);
  void copyPart(SDL_Surface* dest, Rect dr, Rect sr);

  void draw(Display* display, int x, int y);

  void drawHint(Display* display, int x, int y);

  HTexture getPicture() { return m_picture; }
  HTexture getHint() { return m_hint; }

  string getName() { return m_name; }

protected:
  SDL_Surface* resize(SDL_Surface* surface);
  
private:
  set<Piece*> m_pieces;
  vector<HTexture> m_tids;

  SDL_Surface* m_pictureSurface;
  HTexture m_picture;
  HTexture m_hint;

  string m_name;
};
#endif // #ifndef ATC__PICTURE_H
 
