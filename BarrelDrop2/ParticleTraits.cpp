#pragma warning (disable : 4786 4503 4530)

#include "ParticleTraits.h"
void ExplodingBlockParticleTraits::init(Particle* particle) 
{ 
  Vector v;
  v.x = (rand()%50) - 25;
  v.y = -(rand()%30);
  particle->setVelocity(v);
}

void FireWorkBarrelTraits::init(Particle* particle)
{ 
  Vector v;
  v.x = (rand()%50) - 25;
  v.y = -36;
  particle->setVelocity(v);
}

void FireWorkBarrelTraits::decay(Particle* particle) 
{
  Vector v=particle->getVelocity();
  v.x*= (float)0.9;
  v.y+=1.5;
  particle->setVelocity(v);

  m_skin->setAngle(v.anglei());
}

int FireWorkBarrelTraits::getFps(Particle* particle) { return 25; }
int FireWorkBarrelTraits::getLifespan(Particle* particle) { return 20; }
