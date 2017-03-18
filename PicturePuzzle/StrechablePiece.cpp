#include "StretchablePiece.h"
#include "SDL_rotozoom.h"

#include "LayoutSwapper2.h"

StretchablePiece::StretchablePiece(Sector* sector, SDL_Surface* image, bool rot):
m_rot(rot),
m_cRot(0),
m_correctSector(sector)
{
  m_textures[0] = Display::getInstance()->prepare(image);

  if (m_rot)
  {
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

StretchablePiece::~StretchablePiece()
{
  Display::getInstance()->release(m_textures[0]);
  if (m_rot)
  {
    Display::getInstance()->release(m_textures[1]);
    Display::getInstance()->release(m_textures[2]);
    Display::getInstance()->release(m_textures[3]);
  }
}

void StretchablePiece::draw(Display* display, Rect r)
{
  display->stretchBlit(m_textures[m_cRot], r);
}

void StretchablePiece::rotate()
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
