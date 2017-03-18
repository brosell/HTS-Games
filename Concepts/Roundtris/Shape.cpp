#pragma warning (disable : 4503 4530 4786)
#include "Shape.h"
#include "Log.h"

#include <memory.h>
#include "Globals.h"

extern Globals* globals;

int blockS[4][4] = {
  { 0, 0, 0, 0 },
  { 0, 1, 1, 0 },
  { 1, 1, 0, 0 },
  { 0, 0, 0, 0 }
};

int blockZ[4][4] = {
  { 0, 0, 0, 0 },
  { 1, 1, 0, 0 },
  { 0, 1, 1, 0 },
  { 0, 0, 0, 0 }
};

int blockT[4][4] = {
  { 0, 0, 0, 0 },
  { 0, 1, 0, 0 },
  { 1, 1, 1, 0 },
  { 0, 0, 0, 0 }
};

int blockI[4][4] = {
  { 0, 1, 0, 0 },
  { 0, 1, 0, 0 },
  { 0, 1, 0, 0 },
  { 0, 1, 0, 0 }
};

int blockL[4][4] = {
  { 0, 1, 0, 0 },
  { 0, 1, 0, 0 },
  { 0, 1, 1, 0 },
  { 0, 0, 0, 0 }
};

int block7[4][4] = {
  { 0, 1, 1, 0 },
  { 0, 0, 1, 0 },
  { 0, 0, 1, 0 },
  { 0, 0, 0, 0 }
};


Shape::Shape():
m_ball(0)
{
  // just make an s shape block for now
  memcpy(m_blocks, blockT, sizeof(blockS));
  m_ball = globals->assetManager->getSkin("gfx_Ball");
}

Shape::~Shape()
{
  if (m_ball != 0)
  {
    delete m_ball;
    m_ball = 0;
  }
}

void Shape::rotateLeft()
{
  memcpy(m_rotateBuffer, m_blocks, sizeof(m_blocks));
  m_blocks[0][0] = m_rotateBuffer[3][0];
  m_blocks[0][1] = m_rotateBuffer[2][0];
  m_blocks[0][2] = m_rotateBuffer[1][0];
  m_blocks[0][3] = m_rotateBuffer[0][0];

  m_blocks[1][0] = m_rotateBuffer[3][1];
  m_blocks[1][1] = m_rotateBuffer[2][1];
  m_blocks[1][2] = m_rotateBuffer[1][1];
  m_blocks[1][3] = m_rotateBuffer[0][1];
  
  m_blocks[2][0] = m_rotateBuffer[3][2];
  m_blocks[2][1] = m_rotateBuffer[2][2];
  m_blocks[2][2] = m_rotateBuffer[1][2];
  m_blocks[2][3] = m_rotateBuffer[0][2];
  
  m_blocks[3][0] = m_rotateBuffer[3][3];
  m_blocks[3][1] = m_rotateBuffer[2][3];
  m_blocks[3][2] = m_rotateBuffer[1][3];
  m_blocks[3][3] = m_rotateBuffer[0][3];
}

void Shape::rotateRight()
{
  memcpy(m_rotateBuffer, m_blocks, sizeof(m_blocks));
  m_blocks[0][0] = m_rotateBuffer[0][3];
  m_blocks[0][1] = m_rotateBuffer[1][3];
  m_blocks[0][2] = m_rotateBuffer[2][3];
  m_blocks[0][3] = m_rotateBuffer[3][3];

  m_blocks[1][0] = m_rotateBuffer[0][2];
  m_blocks[1][1] = m_rotateBuffer[1][2];
  m_blocks[1][2] = m_rotateBuffer[2][2];
  m_blocks[1][3] = m_rotateBuffer[3][2];
  
  m_blocks[2][0] = m_rotateBuffer[0][1];
  m_blocks[2][1] = m_rotateBuffer[1][1];
  m_blocks[2][2] = m_rotateBuffer[2][1];
  m_blocks[2][3] = m_rotateBuffer[3][1];
  
  m_blocks[3][0] = m_rotateBuffer[0][0];
  m_blocks[3][1] = m_rotateBuffer[1][0];
  m_blocks[3][2] = m_rotateBuffer[2][0];
  m_blocks[3][3] = m_rotateBuffer[3][0];
}

list<Point> Shape::getPositions(Point relativeTo)
{
  if (relativeTo.x == -1)
  {
    relativeTo = m_position;
  }

  list<Point> ret;
  for (int x=0; x<4; x++)
  {
    for (int y=0; y<4; y++)
    {
      if (m_blocks[x][y] != 0)
      {
        ret.push_back(Point(relativeTo.x+x, relativeTo.y+y));
      }
    }
  }

  return ret;
}

void Shape::draw(Display* display, Quadrant* quad)
{
  list<Point> points = getPositions();
  list<Point>::iterator i;
  for (i=points.begin(); i!=points.end(); i++)
  {
    Point p = *i;
    Point sp;

    sp = quad->getScreenPoint(p.x, p.y);

    m_ball->blit(display, sp.x, sp.y, false);
  }
}

bool Shape::canShapeFit(Quadrant* quad, Point location)
{
  if (location.x == -1)
  {
    location = getPosition();
  }

  list<Point> proposedPoints = getPositions(location);
  list<Point>::iterator i;
  for (i=proposedPoints.begin(); i!=proposedPoints.end(); i++)
  {
    Point p = *i;
    if (!quad->validCoord(p.x, p.y))
    {
      return false;
    }

    if (quad->getBlock(p.x, p.y) != 0)
    {
      return false;
    }
  }
  return true;
}

