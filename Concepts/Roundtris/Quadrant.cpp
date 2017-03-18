#pragma warning (disable : 4503 4530 4786)
#include "Quadrant.h"

#include "Globals.h"

extern Globals* globals;


Quadrant::Quadrant(Orientation orientation)
{
  m_orientation = orientation;
  clear();
  m_ball = globals->assetManager->getSkin("gfx_Ball");
}

bool Quadrant::validCoord(int x, int y)
{
  if (x < 0 || x >= 29)
    return false;
  if (y < 0 || y >= 10)
    return false;

  int width = 29 - (y*2);
  int svx = y;
  int evx = svx + (width-1);
  return (x>=svx && x<=evx);
}

void Quadrant::clear()
{
  memset(m_blocks, 0, sizeof(m_blocks));
}

Point Quadrant::getScreenPoint(int x, int y)
{
  lassert(validCoord(x, y));
  int t=0;
  Point screenPoint(0, 0);
  switch(m_orientation)
  {
  case OR_TOP:
    // no transposing required
    screenPoint.x = (x*15) + 95; // FIXME: use CONSTANTS
    screenPoint.y = (y*15) + 15;
    break;
  case OR_BOTTOM:
    x = 29 - (x);
    y = 10 - (y + 1);
    screenPoint.x = (x*15) + 95;
    screenPoint.y = (y*15) + 315;
    break;
  case OR_LEFT:
    t = x;
    x = y;
    y = 29 - (t);
    screenPoint.x = (x*15) + 95;
    screenPoint.y = (y*15) + 15;
    break;
  case OR_RIGHT:
    t = x;
    x = 10 - (y + 1);
    y = t;
    screenPoint.x = (x*15) + 395;
    screenPoint.y = (y*15) + 15;
    break;
  }

  return screenPoint;
}

bool Quadrant::isScreenCoordHere(int x, int y)
{
  Point p(-1, -1);
  int t = 0;
  switch(m_orientation)
  {
  case OR_TOP:
    // no transposing required
    p.x = (x-95)/15;
    p.y = (y-15)/15;
    return validCoord(p.x, p.y);
    break;
  case OR_BOTTOM:
    p.x = (x-95)/15;
    p.y = (y-315)/15;

    p.x = 29 - (p.x);
    p.y = 10 - (p.y + 1);

    return validCoord(p.x, p.y);
    break;
  case OR_LEFT:
    p.x = (x-95)/15;
    p.y = (y-15)/15;

    t = p.x;
    p.x = p.y;
    p.y = 29 - (t);

    return validCoord(p.x, p.y);
    break;
  case OR_RIGHT:
    p.x = (x-395)/15;
    p.y = (y-15)/15;

    t = p.x;
    p.x = 10 - (p.y + 1);
    p.y = t;

    return validCoord(p.x, p.y);
    break;
  default:
    lassert(false);
  }

}


void Quadrant::draw(Display* display)
{
  for (int x=0; x<29; x++)
  {
    for (int y=0; y<10; y++)
    {
      if (m_blocks[x][y] != 0)
      {
        Point sp = getScreenPoint(x, y);
        m_ball->blit(display, sp.x, sp.y, false);
      }
    }
  }
}

int Quadrant::getBlock(int x, int y)
{
  return m_blocks[x][y];
}

bool Quadrant::setBlock(int x, int y, int b)
{
  lassert(validCoord(x, y));
  lassert(m_blocks[x][y] == 0);
  m_blocks[x][y] = b;

  return true;
}

Point Quadrant::getNeighborToLeft(Point p)
{
  return p;
}

Point Quadrant::getNeighborToRight(Point p)
{
  return p;
}
