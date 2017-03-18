#pragma warning (disable : 4503 4530 4786)
#include "Board.h"

Board::Board():
m_currentShape(0),
m_nextShape(0),
m_currentQuadrant(0),
m_co_shapeMover(*this, Board::co_shapeMover, "ShapeMover")
{
  m_quadrants[0].setOrientation(OR_TOP);
  m_quadrants[1].setOrientation(OR_RIGHT);
  m_quadrants[2].setOrientation(OR_BOTTOM);
  m_quadrants[3].setOrientation(OR_LEFT);

  prepareForNewGame();
}

void Board::draw(Display* display)
{
  for(int c=0; c<4; c++)
  {
    m_quadrants[c].draw(display);
  }

  // FIXME: draw on deck shape

  // draw currentShape
  if (m_currentShape != 0)
  {
    m_currentShape->draw(display, &m_quadrants[m_currentQuadrant]);
  }
}

void Board::prepareForNewGame()
{
  m_quadrants[0].clear();
  m_quadrants[1].clear();
  m_quadrants[2].clear();
  m_quadrants[3].clear();

  getNextShape();

  m_co_shapeMover.spawn();
}

void Board::getNextShape()
{
  if (m_nextShape == 0)
  {
    m_nextShape = new Shape;
  }
  if (m_currentShape != 0)
  {
    delete m_currentShape;
    m_currentShape = 0;
  }

  m_currentQuadrant = 0;
  m_currentShape = m_nextShape;
  m_currentShape->setPosition(13, 0);
  m_nextShape = new Shape;
}

void Board::rotateShapeLeft()
{
  if(m_currentShape != 0)
  {
    m_currentShape->rotateLeft();
    // does it fit?
    if (!m_currentShape->canShapeFit(&m_quadrants[m_currentQuadrant]))
    {
      // i guess not
      m_currentShape->rotateRight();
    }
  }
}

void Board::rotateShapeRight()
{
  if(m_currentShape != 0)
  {
    m_currentShape->rotateRight();
    if (!m_currentShape->canShapeFit(&m_quadrants[m_currentQuadrant]))
    {
      m_currentShape->rotateLeft();
    }
  }
}

void Board::moveShapeLeft()
{
  if(m_currentShape != 0)
  {
    Point p = m_currentShape->getPosition();
    p.x -= 1;
    if ( (p.x > 0) && m_currentShape->canShapeFit(&m_quadrants[m_currentQuadrant], p))
    {
      m_currentShape->setPosition(p.x, p.y);
    }
    else
    {
      m_currentQuadrant-=1;
      if (m_currentQuadrant < 0)
      {
        m_currentQuadrant = 3;
      }
      int dx = m_quadrants[m_currentQuadrant].endColumnForRow(p.y);
      while (!m_currentShape->canShapeFit(&m_quadrants[m_currentQuadrant], Point(dx, p.y)))
      {
        dx--;
      }
      m_currentShape->setPosition(dx, p.y);
    }

  }
}

void Board::moveShapeRight()
{
  if(m_currentShape != 0)
  {
    Point p = m_currentShape->getPosition();
    p.x += 1;
    if (m_currentShape->canShapeFit(&m_quadrants[m_currentQuadrant], p))
    {
      m_currentShape->setPosition(p.x, p.y);
    }
    else
    {
      m_currentQuadrant+=1;
      if (m_currentQuadrant > 3)
      {
        m_currentQuadrant = 0;
      }
      int dx = p.y;
      while (!m_currentShape->canShapeFit(&m_quadrants[m_currentQuadrant], Point(dx, p.y)))
      {
        dx++;
      }
      m_currentShape->setPosition(dx, p.y);
    }
  }
}

void Board::moveShapeDown()
{
  if(m_currentShape != 0)
  {
    Point p = m_currentShape->getPosition();
    p.y += 1;
    if (m_currentShape->canShapeFit(&m_quadrants[m_currentQuadrant], p))
    {
      m_currentShape->setPosition(p.x, p.y);
    }
    else
    {
      list<Point> points = m_currentShape->getPositions();
      list<Point>::iterator i;
      for (i=points.begin(); i!=points.end(); i++)
      {
        Point p = *i;
        m_quadrants[m_currentQuadrant].setBlock(p.x, p.y, 1);
      }
      getNextShape();
    }
  }
}

void Board::co_shapeMover()
{
  while (true)
  {
    Coroutine::pause(1000);
//    moveShapeDown();
  }
}

void Board::chaseMouse(Point m)
{
  if (m.x < 95)
  {
    m_currentQuadrant = 3; // LEFT
  }
  else if (m.x > 545)
  {
    m_currentQuadrant = 1; // RIGHT
  }
  else if (m.y < 15)
  {
    m_currentQuadrant = 0; // TOP
  }
  else if (m.y > 465)
  {
    m_currentQuadrant = 2; // BOTTOM
  }
  else
  {
    // have to ask each quad of the mouse points to it
    for (int c=0; c<4; c++)
    {
      if (m_quadrants[c].isScreenCoordHere(m.x, m.y))
      {
        m_currentQuadrant = c;
        break;
      }
    }
    lassert2(false, "ut-oh");
  }

}