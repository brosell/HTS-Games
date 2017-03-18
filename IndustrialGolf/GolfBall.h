#ifndef GolfBall_h
#define GolfBall_h

#include "BR_Game.h"
#include "ThinkScheduler.h"
#include "Face.h"


enum GolfBallState
{
  GBS_UNDEF,
  GBS_AT_REST,   // not moving, wait to be wacked
  GBS_IN_FLIGHT,
  GBS_ROLLING,
  GBS_CONTROLED
};


/**
  The golfball class is the ball that gets wacked around the course.
  It interacts with the Tiles (ground, water, wall, etc). It is 
  assaulted with vearious Force's (ie wind, air resistance, gravity,
  getting wacked by the club, etc.)

  When the ball comes to rest on the play field, it signals the club
  to come and load it up.
  */

class GolfBall: public Thing, public MouseListener
{
public:
  GolfBall();
  ~GolfBall();

  /** external entities call this to change the balls velocity */
//  void applyForce(Force* theForce);

  /** or maybe this is the interface :) */
  void applyForce(Vector theForce);

  void addFace(Face f) { m_faces.push_back(f); }

  virtual void draw(Display* display, int x, int y);

  float getSpeed() { return m_velocity.length(); }

  Vector getVelocity() { return m_velocity; }
  void setVelocity(Vector v) { m_velocity = v; }

  virtual void logic(float factor);

  void reflect(Line l);

  GolfBallState getGBState() { return m_state; }
  bool atRest() { return m_state == GBS_AT_REST; }

  virtual void mousePressed(MousePressEvent* event);
  virtual void mouseReleased(MouseReleaseEvent* event);

protected:
  bool isInBounds();
  void mulligan();
private:
  Point m_mouseDown;
  unsigned int m_mouseDownFrame;

  list<Face> m_faces;
  Face closestFace();
  Face closest;

  PointDist m_pd;

  FPoint m_lastSolidGround;

  bool faceBelow(Face& ret);

  RotateSkinHandle m_skin;

  float rollingForce;
  Vector rollingVelocity;

  GolfBallState m_state;


  Vector m_velocity;

  TypeThinkDelegate<GolfBall> m_logic;
  void logic();
  void logic_inFlight();
  void logic_rolling();

  float m_fuel;
  int m_refuelFrame;

  bool m_firing;
  bool m_recovering;
};

#endif
