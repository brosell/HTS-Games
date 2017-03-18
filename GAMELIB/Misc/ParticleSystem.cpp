#pragma warning (disable : 4786 4503 4530)

#include "ParticleSystem.h"

#include "Misc/AssetManager.h"

Particle::Particle(Point origin, ParticleTraits* traits, ParticleGroup* group):
m_age(0),
m_location(origin),
m_velocity(0, 0),
m_traits(traits),
m_group(group)
{
  if (m_traits != 0)
  {
    m_traits->init(this);
  }
  else
  {
    m_velocity.x = (rand()%60) - 30;
    m_velocity.y = (rand()%60) - 30;
  }
}

Particle::~Particle()
{
}

void Particle::decay() 
{ 
  m_location.x += m_velocity.x;
  m_location.y += m_velocity.y;
  m_age++;
  if (m_age > m_traits->getLifespan(this))
  {
    m_traits->deinit(this);
    m_group->remove(this);
    
    return;
  }
  m_traits->decay(this);
}

void ParticleSystem::draw(Display* display)
{
  set<Particle*>::iterator i;
  set<Particle*> copy(m_particles);
  for (i=copy.begin(); i!=copy.end(); i++)
  {
    Particle* particle = (*i);
    if (!particle->isDecayed())
    {
      particle->draw(display);
    }
  }
}

void ParticleSystem::remove(Particle* p)
{
  m_particles.erase(p);
  delete p;
}

void ParticleSystem::tick()
{
  list<Particle*> toBeWacked;
  set<Particle*>::iterator i;
  for (i=m_particles.begin(); i!=m_particles.end(); i++)
  {
    Particle* particle = (*i);
    particle->decay();
    if (particle->isDecayed())
    {
      toBeWacked.push_back(particle);
    }
  }

  list<Particle*>::iterator ii;
  for (ii=toBeWacked.begin(); ii!=toBeWacked.end(); ii++)
  {
    m_particles.erase(*ii);
    delete (*ii);
  }
}

void ParticleSystem::co_runner()
{
  while(true)
  {
    tick();
    GameScheduler::resumeAt(NEXT_FRAME);
  }
}

void ParticleGroup::remove(Particle* p)
{
  m_particles.erase(p);
  m_finalLocations.push_back(Point(p->getLocation().x, p->getLocation().y));
  //m_system->remove(p);
  if (m_particles.size() == 0)
  {
    //must have been the last one
    m_system->groupDone(this);
  }

}
