/* ****************************************************************************
 *
 *  Piece.cpp
 *  Created by Bert Rosell, on Fri Nov 14 2003, 16:34:20 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the Piece component.
 *  Please see Piece.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "Piece.h"


/* ********************************* 
 * Piece
 ***********************************/
Piece::Piece(HTexture texture, Point coord, bool rot): 
m_coord(coord),
m_rot(rot),
m_cRot(0)
{
  m_textures[0] = texture;//Display::getInstance()->prepare(image);

  // OK: no OpenGL now for sure. 
  if (m_rot)
  {
    SDL_Surface* image = (SDL_Surface*)texture;

    SDL_Surface* rot1 = rot90(image);
    SDL_Surface* rot2 = rot90(rot1);    
    SDL_Surface* rot3 = rot90(rot2);    

    m_textures[1] = Display::getInstance()->prepare(rot1);
    m_textures[2] = Display::getInstance()->prepare(rot2);
    m_textures[3] = Display::getInstance()->prepare(rot3);
    
    SDL_FreeSurface(rot1);
    SDL_FreeSurface(rot2);
    SDL_FreeSurface(rot3);

    m_cRot = rand()%4;
  }

}

Piece::~Piece() 
{
  if (m_rot)
  {
    Display::getInstance()->release(m_textures[1]);
    Display::getInstance()->release(m_textures[2]);
    Display::getInstance()->release(m_textures[3]);
  }
}
  
void Piece::rotate()
{
  if (m_rot)
  {
    m_cRot++;
    if (m_cRot > 3)
    {
      m_cRot = 0;
    }
  }
}

void Piece::draw(Display* display, int x, int y)
{
  display->blit(m_textures[m_cRot], x, y);
}
  