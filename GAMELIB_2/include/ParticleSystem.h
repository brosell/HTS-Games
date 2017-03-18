#ifndef ParticleSystem_h
#define ParticleSystem_h

#include "2dVector.h"
#include "Timer.h"
#include "ThinkScheduler.h"
#include "BR_Game.h"

#include <list>
using namespace std;

class Particle;
class ParticleGroup;

class ParticleTraits
{
public:
  virtual void init(Particle* particle) { }
  virtual void deinit(Particle* particle) { }
  virtual void decay(Particle* particle) { }
  virtual void draw(Particle* particle, Display* display) { }

  virtual int getFps(Particle* particle) { return 30; }
  virtual int getLifespan(Particle* particle) { return 30; }
};

class Particle: hts::Noncopyable
{
public:
  Particle(Point origin, ParticleTraits* traits, ParticleGroup* group);
  ~Particle();

  void setParam(void* p) { m_param = p; }
  void* getParam() { return m_param; }
  
  void draw(Display* display) { m_traits->draw(this, display); }


  void decay();


  bool isDecayed() { return m_age > m_traits->getLifespan(this); }

  void setLocation(FPoint p) { m_location = p; }
  FPoint getLocation() { return m_location; }

  void setVelocity(Vector v) { m_velocity = v; }
  Vector getVelocity() { return m_velocity; }

  int getAge() { return m_age; }

private:

  FPoint m_location;
  Vector m_velocity;
  int m_age;

  ParticleTraits* m_traits;
  ParticleGroup* m_group;
  
  void* m_param;

};

class ParticleEvent
{
public:
  int id;
  list<Point> finalLocations;
};

class ParticleListener
{
public:
  virtual void particlesDone(ParticleEvent* event) { }
};

class ParticleSystem;
class ParticleGroup
{
public:
  ParticleGroup(ParticleSystem* system): m_system(system) { }

  void add(Particle* p)
  {
    m_particles.insert(p);
  }
  void remove(Particle* p);

  list<Point> getFinalLocations() { return m_finalLocations; }

private:
  list<Point> m_finalLocations;
  set<Particle*> m_particles;
  ParticleSystem* m_system;
};


class ParticleSystem: hts::Noncopyable
{
public:
  ParticleSystem():
  m_think(*this, ParticleSystem::think)
  {
    ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &m_think);
  }

  int fire(Point origin, int count, ParticleTraits* traits, ParticleListener* listener = 0)
  {
    ParticleGroup* group = new ParticleGroup(this);
    for(int c=0; c<count; c++)
    {
      Particle* particle = new Particle(origin, traits, group);
      group->add(particle);
      m_particles.insert(particle);
    }
    if (listener != 0)
    {
      m_listeners[group] = listener;
    }
    return (int)group;
  }

  void draw(Display* display);

  void groupDone(ParticleGroup* group)
  {
    ParticleEvent event;
    event.id = (int)group;
    event.finalLocations = group->getFinalLocations();

    ParticleListener* listener = m_listeners[group];
    if (listener != 0)
    {
      listener->particlesDone(&event);
    }
    m_listeners.erase(group);
    delete group;
  }

  void tick();
  
  void remove(Particle* p);

private:
  set<Particle*> m_particles;
  map<ParticleGroup*, ParticleListener*> m_listeners;
  TypeThinkDelegate<ParticleSystem> m_think;
  void think();
};


class ParticleSystemWaitable: public ParticleListener, public Waitable
{
public:
  ParticleSystemWaitable() : m_done(false) { }
  virtual bool isWaitOver() { return m_done; }
  virtual void particlesDone(ParticleEvent* event) { m_done = true; finalLocations = event->finalLocations;}

  void reset() { m_done = false; }
  list<Point> finalLocations;
private:
  bool m_done;
};

#endif