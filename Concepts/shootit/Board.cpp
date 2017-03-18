#pragma warning (disable : 4503 4530 4786)
#include "Board.h"
#include "Globals.h"

#include "Misc/GameMath.h"

const int BOARDSIZE = 32;
const int HALF_BOARDSIZE = BOARDSIZE/2;

Board::Board():
m_origin(320, 240),
m_gunsight(320, 22),
m_grid(9, BOARDSIZE, BOARDSIZE),
m_co_boardScript(*this, Board::co_boardScript, "BoardScript"),
m_co_shooter(*this, Board::co_shooter, "Shooter")
{
  m_ball[1] = globals->assetManager->getSkin("gfx_Ball_1");
  m_ball[2] = globals->assetManager->getSkin("gfx_Ball_2");
  m_ball[3] = globals->assetManager->getSkin("gfx_Ball_3");
  m_ball[4] = globals->assetManager->getSkin("gfx_Ball_4");

  m_target = globals->assetManager->getSkin("gfx_Target");

  for (int x=0; x<BOARDSIZE; x++)
  {
    for (int y=0; y<BOARDSIZE; y++)
    {
      m_grid.setOccupant(x, y, 0);
    }
  }

  m_grid.setOccupant(HALF_BOARDSIZE, HALF_BOARDSIZE, 1);

  m_grid.setWorldOffset(Point(88, 25));
  
  FPoint p(-225, 0);
  for (int c=0; c<360; c+=4)
  {
    p = rotate(p, 4); //.rotate(1);
    Shooter shooter;
    shooter.color = (rand()%3) + 2;
    shooter.screenLocation = Point(p.x+225+95, p.y+225+7);
    m_outerBoundry.push_back(shooter);
  }

  m_co_boardScript.spawn();
    
}

void Board::draw(Display* display)
{
//  display->drawHLine(0, 640, 240, 0, 0, 255, 255);
//  display->drawVLine(320, 0, 480, 0, 0, 255, 255);

  // center point
//  Point s = m_grid.worldCoord(HALF_BOARDSIZE, HALF_BOARDSIZE);
//  m_ball[1]->blit(display, s.x, s.y, false);
  
  // draw balls
  for(int x=0; x<BOARDSIZE; x++)
  {
    for (int y=0; y<BOARDSIZE; y++)
    {
      int o=m_grid.getOccupant(x, y);
      if (o != 0)
      {
        Point s = m_grid.worldCoord(x, y);
        m_ball[o]->blit(display, s.x, s.y, false);
      }
    }
  }

  // get mouse coords. find closest spot to mouse and draw a ball
  // DRAWING TARGET
  m_target->blit(display, m_gunsight.x, m_gunsight.y, false);
  
  // draw outer boundry
  list<Shooter>::iterator is;
  for (is=m_outerBoundry.begin(); is!=m_outerBoundry.end(); is++)
  {
    Shooter shooter = *is;
    m_ball[shooter.color]->blit(display, shooter.screenLocation.x, shooter.screenLocation.y, false);
  }

  // draw shooter
  m_target->blit(display, m_closestShooter.screenLocation.x, m_closestShooter.screenLocation.y, false);
  
  // draw shots
  set<Shooter*>::iterator i2;
  for (i2 = m_toBeDrawn.begin(); i2!=m_toBeDrawn.end(); i2++)
  {
    m_ball[(*i2)->color]->blit(display, (*i2)->screenLocation.x, (*i2)->screenLocation.y, false);
  }





}

void Board::prepareForNewGame()
{
}


void Board::co_boardScript()
{
  while (true)
  {
    // find closest shooter
    m_closestShooter = closestShooter();
    m_gunsight = closestTarget();
    Coroutine::waitUntilFromStart(1000/30);
  }
}

Shooter Board::closestShooter()
{
  Shooter ret;
  Point m = theGame.getMousePos();
  list<Shooter>::iterator is;
  for (is=m_outerBoundry.begin(); is!=m_outerBoundry.end(); is++)
  {
    Point p = (*is).screenLocation;
    if (m.isShortestDistance(p))
    {
      ret = *is;
    }
  }
  return ret;
}

Point Board::closestTarget()
{
  Point m = theGame.getMousePos();

  Line theLine(m, FPoint(320, 240));

  set<Point> points;
  getPossableTargets(points);
  Point winner;
  set<Point>::iterator i;
  
  float dist = FLT_MAX;
  for (i=points.begin(); i!=points.end(); i++)
  {
    Point p = m_grid.worldCoord((*i).x, (*i).y);
    //if (m.isShortestDistance(p))
    float d = distToSegmentSquared(p.x, p.y, theLine.p1.x, theLine.p1.y, theLine.p2.x, theLine.p2.y);
    if (d < dist)
    {
      winner = p;
      dist = d;
    }
  }
  return winner;
}

void Board::getPossableTargets(set<Point>& ret)
{
  list<Point> neighbors;
  list<Point>::iterator i;

  for (int x=0; x<BOARDSIZE; x++)
  {
    for (int y=0; y<BOARDSIZE; y++)
    {
      int o = m_grid.getOccupant(x, y);
      if (o != 0)
      {
        neighbors = m_grid.getNeighbors(x, y);
        for (i=neighbors.begin(); i!=neighbors.end(); i++)
        {
          if (m_grid.getOccupant((*i).x, (*i).y) == 0)
          {
            ret.insert( (*i) );
          }
        }
      }
    }
  }
}

void Board::fire()
{
  m_co_shooter.spawn();
}

void Board::co_shooter()
{
  Shooter* shooter = new Shooter;
  shooter->color = m_closestShooter.color;
  shooter->screenLocation = m_closestShooter.screenLocation;

  m_toBeDrawn.insert(shooter);

  Point target = m_gunsight;
  Point origin = m_closestShooter.screenLocation;
  int color = m_closestShooter.color;

  Vector v(target.x - origin.x, target.y - origin.y);
  v = v.normalize();
  v = v.multiply(10);
  
  FPoint loc(origin);

  FPoint dest(m_gunsight);
  while(dest.distanceToSquared(loc) > 100)
  {
    loc.x+=v.x;
    loc.y+=v.y;
    shooter->screenLocation.x = loc.x;
    shooter->screenLocation.y = loc.y;
    Coroutine::waitUntilFromStart(50);
  }

  Point p = m_grid.getCoord(target.x, target.y);
  m_grid.setOccupant(p.x, p.y, color);
  m_toBeDrawn.erase(shooter);
  delete shooter;
}