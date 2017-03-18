/* ****************************************************************************
 *
 *  Picture.cpp
 *  Created by Bert Rosell, on Fri Nov 14 2003, 21:19:32 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the Picture component.
 *  Please see Picture.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "Picture.h"

#include "SDL_gfxprimitives.h"
#include "SDL_rotozoom.h"

#include "FileUtils.h"

/* ********************************* 
 * Picture
 ***********************************/
Picture::Picture(string filename)
{
  m_name = prettyName(filename);
  SDL_Surface* picture = loadSDLSurface(filename);
  if (picture == 0)
  {
    throw string("bad picture");
  }

  SDL_Surface* t = 0;
  if (picture->w != 400 && picture->h != 300)
  {
    t = resize(picture);
    SDL_FreeSurface(picture);
    if (t == 0)
    {
      throw string("bad resize");
    }
    picture = t;
  }

//  chop(picture);

  // make hint
  SDL_Surface* shrunk = zoomSurface(picture, .5, .5, 1);
  if (shrunk == 0)
  {
    throw string("couldn't prepare hint");
  }
  m_hint = Display::getInstance()->prepare(shrunk);
  SDL_FreeSurface(shrunk);


  m_picture = Display::getInstance()->prepare(picture);

  
  //SDL_FreeSurface(picture);
  m_pictureSurface = picture;
  if (m_picture < 1)
  {
    throw string("couldn't prepare picture");
  }
}


Picture::~Picture()
{
  for_each(m_tids.begin(), m_tids.end(), ReleaseTexture());
  m_tids.clear();
  for_each(m_pieces.begin(), m_pieces.end(), hts::Delete());
  m_pieces.clear();

  ReleaseTexture()(m_picture);

  SDL_FreeSurface(m_pictureSurface);
}

void Picture::copyPart(SDL_Surface* dest, Rect dr, Rect sr)
{
  SDL_BlitSurface(m_pictureSurface, sr, dest, dr);
}

void Picture::chop(bool rot)
{
  SDL_Surface* picture = m_pictureSurface;
  int x, y;
  SDL_Rect sr;
  sr.w = 50;
  sr.h = 50;

  SDL_Rect dr;
  dr.x = 0;
  dr.y = 0;
  dr.w = 50;
  dr.h = 50;

  for (x=0; x<8; x++)
  {
    for (y=0; y<6; y++)
    {
      sr.x = x * 50;
      sr.y = y * 50;

      SDL_Surface* dest = createSDLSurface(50, 50);
      SDL_BlitSurface(picture, &sr, dest, &dr);

      HTexture tid = Display::getInstance()->prepare(dest);
      m_tids.push_back(tid);
      SDL_FreeSurface(dest);

      Piece* piece = new Piece(tid, Point(x, y), rot);
      m_pieces.insert(piece);
    }
  }
}

SDL_Surface* Picture::resize(SDL_Surface* surface)
{
  // use rotozoom to resize the picture
  return 0;
}

void Picture::draw(Display* display, int x, int y)
{
  display->blit(m_picture, x, y);
}

void Picture::drawHint(Display* display, int x, int y)
{
  display->blit(m_hint, x, y);
}