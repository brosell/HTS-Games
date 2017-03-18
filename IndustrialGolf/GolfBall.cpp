#pragma warning (disable : 4786 4530 4503)
#include "GolfBall.h"

#include "Globals.h"
#include "Tile.h"
#include "Level.h"

#include <string>
using namespace std;

GolfBall::GolfBall():
Thing(15),
m_logic(*this, GolfBall::logic),
closest("Grass", Line(FPoint(), FPoint())),
m_refuelFrame(0),
m_fuel(30),
m_firing(false),
m_recovering(false)
{
  string skinName = Globals::entityDefs["GolfBall"]["Skin"];

  m_skin = Globals::am->getRotateSkin(skinName);
  setSkin(m_skin);

  ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &m_logic);

  m_state = GBS_AT_REST;
  m_velocity = Vector(0, 0);

  Globals::worldCanvas->addMouseListener(this);
}

GolfBall::~GolfBall()
{
  Globals::worldCanvas->removeMouseListener(this);
}

void GolfBall::mousePressed(MousePressEvent* event)
{
  m_mouseDown.x = event->x;
  m_mouseDown.y = event->y;
  m_mouseDownFrame = ThinkScheduler::currentFrame();
}

void GolfBall::mouseReleased(MouseReleaseEvent* event)
{
  unsigned int now = ThinkScheduler::currentFrame();
  Vector vel(0, 0, 0);
  vel.x = event->x - m_mouseDown.x;
  vel.y = event->y - m_mouseDown.y;

  float speed = vel.length() / (now - m_mouseDownFrame);
  int angle = vel.anglei();
  if (angle > 0 && angle < 90)
  {
    vel=Vector::createFromAngle(25, speed);
  }
  else if (angle >=90 && angle <360)
  {
    vel=Vector::createFromAngle(325, speed);
  }
    
  vel = vel.normalize().multiply(speed*Globals::hurlStrength);
  m_velocity = vel;
  Globals::lastViewChangeWasMouse = false;
}

void GolfBall::draw(Display* display, int x, int y)
{
//  if (m_state == GBS_IN_FLIGHT && m_velocity.length() > 10)
//  {
//    inform << "-(" << getPositioni().x << ", " << getPositioni().y << ") " << endl;
//  }
  Thing::draw(display, x, y);
//  display->drawLine(x, y, m_pd.point.x-Globals::viewX, m_pd.point.y-Globals::viewY, 255, 0, 0, 255);
//  Line l = closest.getLine();
//  display->drawLine(l.p1.x-Globals::viewX, l.p1.y-Globals::viewY, 
//                    l.p2.x-Globals::viewX, l.p2.y-Globals::viewY, 
//                    255, 255, 255, 255);

  int fuelLen = m_fuel * 5;
  int barHeight = m_fuel * 5;
  int bary = (30*5) - barHeight;

  display->fillRect(0, bary, 30, barHeight, 255, 0, 0, 127);

//  display->fillRect(0, 480, 30, fuelLen, 255, 0, 0, 127);
}

void GolfBall::applyForce(Vector theForce)
{
  m_velocity = m_velocity.add(theForce);
}



void GolfBall::logic()
{
//  if (ThinkScheduler::currentFrame() >= m_refuelFrame)
//  {
//    m_refuelFrame = ThinkScheduler::currentFrame() + 5 * 15;
//    m_fuel = 30;
//  }

  if (!m_firing && !m_recovering && theGame.isKey(SDLK_SPACE))
  {
    m_firing = true;
    Globals::lastViewChangeWasMouse = false;
  }

  if (m_firing && m_fuel <= 0)
  {
    m_firing = false;
    m_recovering = true;
    m_refuelFrame = ThinkScheduler::currentFrame() + 5*15;
  }

  if (m_recovering && ThinkScheduler::currentFrame() >= m_refuelFrame)
  {
    m_fuel = 30;
    m_recovering = false;
    m_firing = false;
  }

  
//  if (theGame.isKey(SDLK_UP) && m_fuel > 0)
//  {
//    applyForce(Vector(0, -2));
//    m_fuel--;
//  }
  if (m_firing)
  {
//    applyForce(Vector(0, -2));
//    m_fuel--;
    m_fuel = 0;
    applyForce(Vector(0, -60));
  }
      
  if (theGame.isKey(SDLK_LEFT))
  {
    applyForce(Vector(-1, 0));
  }
  if (theGame.isKey(SDLK_RIGHT))
  {
    applyForce(Vector(1, 0));
  }

//  if (m_velocity.length() > 30)
//  {
//    m_velocity = m_velocity.normalize().multiply(30);
//  }
 
  logic_inFlight();
  ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &m_logic);

//  static bool atRest = true;
//  static int zeroCount = 0;
//  
//  static int radiusSquared = 30 * 30;
//
//  
//
//  while(true)
//  {
//    ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &m_logic);
//
//    switch(m_state)
//    {
//    case GBS_AT_REST:
//      {
//        if (m_velocity.length() > 0)
//        {
//          m_state = GBS_IN_FLIGHT;
//          m_lastSolidGround = getPositionf();
//        }
//      }
//      break;
//    case GBS_IN_FLIGHT:
//      {
//        logic_inFlight();
//      }
//      break;
//    case GBS_CONTROLED:
//      {
//        // nothing to do
//      }
//      break;
//    default:
//      {
//        logError(Error, "Unexpected golfball state");
//      }
//      break;
//    }
//  }
}

Face GolfBall::closestFace()
{
//  Line closest;
  Point loc = getPositioni();
  float dist = FLT_MAX;
  list<Face>::iterator i;
  for (i=m_faces.begin(); i!=m_faces.end(); i++)
  {
    Line line = (*i).getLine();
    float d = distToSegment(loc, line);
    if (d < dist)
    {
      closest = *i;
      dist = d;
    }
  }

  return closest;
}

Vector downwardVector(Line l);

void GolfBall::logic_inFlight()
{
  float vlen = m_velocity.length();
  Line lb;
  bool fb = false;

  for (int c=0; c<vlen; c++)
  {
    FPoint location = getPositionf();

    Face face = closestFace();
    closest = face;

    vlen = m_velocity.length();
    Face f("Grass", Line(FPoint(), FPoint()));
    fb = faceBelow(f);
    lb = f.getLine();
    
    if (vlen <=.5 && fb)
    {
      m_state = GBS_AT_REST;
      m_velocity = Vector(0, 0);
      return;
    }

    Vector uV = m_velocity.normalize();
    // refect?
    Line line = face.getLine();
    m_pd = closestPoint(location, line);
    //if (distToSegment(location, line) <= 30)
    if (m_pd.dist <= 30)
    {
      Point t;
      t.x = location.x + (uV.x*15);
      t.y = location.y + (uV.y*15);
      // t is now r units forward of location. if t is still in range, we must be heading toward line
      if (distToSegment(t, line) <= 30)
      {
        // reflect!
        Vector newV = reflection(m_velocity, normal(Line(location, m_pd.point)));
        newV = newV.normalize();
        
        newV.y = newV.y*(m_velocity.length()*face.getYForceFactor());
        newV.x = newV.x*(m_velocity.length()*face.getXForceFactor());
        m_velocity = newV;
      }
    }
    
    uV = m_velocity.normalize();
    location.x += uV.x;
    location.y += uV.y;

//    if (fb)
//    {
//      m_lastSolidGround = location;
//    }
    setPosition(location);

    if (!isInBounds())
    {
      mulligan();
    }

    logic(1/vlen);

    m_velocity.y += Globals::theLevel->getGravity(); //.105; // gravity
  }
}

bool GolfBall::isInBounds()
{
  Rect r = Globals::world->getWorldDimensions();
  r.x-=30;
  r.y-=30;
  r.h+=60;
  r.w+=60;

  Point loc = getPositioni();

  return r.containsPoint(loc);
}

void GolfBall::mulligan()
{
  m_velocity = Vector(0, 0);
  setPosition(m_lastSolidGround);
  m_state = GBS_AT_REST;
}

void GolfBall::reflect(Line l)
{
  Vector newV = reflection(m_velocity, l);
  m_velocity = newV;
}

Vector downwardVector(Line l)
{
  Vector ret;
  if (l.p1.y == l.p2.y)
  {
    ret = Vector(0, 0);
  }
  else if(l.p1.y > l.p2.y)
  {
    // roll towards l.p1
    ret.x = l.p1.x - l.p2.x;
    ret.y = l.p1.y - l.p2.y;
  }
  else
  {
    // roll towards l.p2
    ret.x = l.p2.x - l.p1.x;
    ret.y = l.p2.y - l.p1.y;
  }
 
  return ret;
}

bool GolfBall::faceBelow(Face& ret)
{
  Line l = closestFace().getLine();
  FPoint b = getPositionf();
  FPoint d;
  float bd = distToSegment(b, l);
  if (bd <= 30)
  {
    float bc = b.distanceTo (l.p2);
    float dc = sqrt( (bc*bc) - (bd*bd) );

    Vector cToA(l.p1.x - l.p2.x, l.p1.y - l.p2.y);
    cToA = cToA.normalize().multiply(dc);
    d.x = l.p2.x + cToA.x;
    d.y = l.p2.y + cToA.y;
    
    ret = closestFace();

    return (d.y > b.y);
  }
  return false;
}


void GolfBall::logic(float factor)
{
  Level::iterator i;
  for (i=Globals::theLevel->ebegin(); i!=Globals::theLevel->eend(); i++)
  {
    (*i)->logic(factor);
  }
}
