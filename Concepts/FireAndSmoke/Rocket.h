#ifndef Rocket_h
#define Rocket_h

#include "Misc/Gamemath.h"

#include "Misc/ParticleSystem.h"

#include "CoroutineDelegates.h"

#include "Globals.h"


class SmokeData
{
public:
  int lifespan;
  int curlDir; // 1 or -1
  SharedRotateSkin* skin;
  SharedRotateSkin* fireSkin;
  Vector toOrigin;
};

class SmokeTraits: public ParticleTraits
{
public:
  SmokeTraits(Vector shipVec);
  void setShipVec(Vector shipVec);

  virtual void init(Particle* particle);
  virtual void deinit(Particle* particle);
  virtual void decay(Particle* particle);
  virtual void draw(Particle* particle, Display* display);

  virtual int getFps(Particle* particle);
  virtual int getLifespan(Particle* particle);

private:
  Vector m_shipVec;
  Vector m_perpa;
  Vector m_perpb;

  

  int rot;

  SharedRotateSkin* m_smokeSkin;
};

class Rocket
{
public:
  Rocket(Point origin, Vector velocity);
  
  void draw(Display* display);

private:
  Vector m_velocity;
  Point m_location;
  void co_rocketScript();
  GameCoroutineTypeDelegate<Rocket> m_co_rocketScript;
  SharedRotateSkin* m_skin;
};


#endif