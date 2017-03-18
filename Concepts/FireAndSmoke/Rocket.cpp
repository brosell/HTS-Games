#pragma warning (disable : 4786 4503 4530)
#include "Rocket.h"
#include "SDL_gfxPrimitives.h"

SmokeTraits::SmokeTraits(Vector shipVec)
{
  //m_smokeSkin = globals->assetManager->getRotateSkin("rot_SmokeTrail");
  setShipVec(shipVec);
}

void SmokeTraits::setShipVec(Vector shipVec)
{
  Angle a = shipVec.anglei();
  rot = (a/10);

  
  a-=30;
  m_perpa = Vector::createFromAngle(a, 1);
  a+=60;
  m_perpb = Vector::createFromAngle(a, 1);
}
void SmokeTraits::init(Particle* particle) 
{
  SmokeData* data = new SmokeData;
  data->curlDir = 0;//((rand()%2)==0?1:-1);// * (rand()%2);
  data->lifespan = (rand()%50)+50;
  
  data->skin = globals->assetManager->getRotateSkin("rot_SmokeTrail");
  data->fireSkin = globals->assetManager->getRotateSkin("rot_Fire");
  data->skin->setFrame(rand()%3);
  data->fireSkin->setFrame(rand()%3);
  
  particle->setParam(data);
  FPoint l = particle->getLocation();
  FPoint origin(l);

  Vector perp;
  if (rand()%2)
  {
    perp=m_perpa.multiply(rand()%10);
  }
  else
  {
    perp=m_perpb.multiply(rand()%10);
  }
  
  l.x-=(perp.x);
  l.y-=(perp.y);
  particle->setLocation(l);

  data->toOrigin.x = origin.x - l.x;
  data->toOrigin.y = origin.y - l.y;
  float len = data->toOrigin.length();
  data->toOrigin = data->toOrigin.normalize();
  data->toOrigin = data->toOrigin.multiply(len/data->lifespan);

}

void SmokeTraits::deinit(Particle* particle)
{
  SmokeData* data = (SmokeData*)particle->getParam();
  globals->assetManager->releaseRotateSkin(data->fireSkin);
  globals->assetManager->releaseRotateSkin(data->skin);
  delete data;
}

void SmokeTraits::decay(Particle* particle) 
{
  SmokeData* data = (SmokeData*)particle->getParam();
//  Vector v = particle->getVelocity();
//  Angle a = v.anglei();
//  a+=data->curlDir;
//  particle->setVelocity(Vector::createFromAngle(a, 1));
  FPoint l = particle->getLocation();
  l.x+=data->toOrigin.x;
  l.y+=data->toOrigin.y;
  particle->setLocation(l);
  particle->setVelocity(Vector(0, 0));
}

void SmokeTraits::draw(Particle* particle, Display* display) 
{
  FPoint l=particle->getLocation();
  SmokeData* data = (SmokeData*)particle->getParam();
  data->skin->setRotation(rot);
  data->fireSkin->setRotation(rot);
  
  if ( ((float)particle->getAge() / (float)data->lifespan) > .75)
  {
    data->skin->blit(display, l.x, l.y, true);
  }
  else
  {
    data->fireSkin->blit(display, l.x, l.y, true);
  }

}

int SmokeTraits::getFps(Particle* particle) 
{ 
  return 30; 
}
int SmokeTraits::getLifespan(Particle* particle) 
{ 
  return ((SmokeData*)particle->getParam())->lifespan;
}


Rocket::Rocket(Point origin, Vector velocity):
m_location(origin),
m_velocity(velocity),
m_co_rocketScript(*this, Rocket::co_rocketScript, "Rocket")
{
  m_skin = globals->assetManager->getRotateSkin("rot_Rocket");
  m_skin->setAngle(0);
  m_co_rocketScript.spawn();
}

void Rocket::draw(Display* display)
{
  m_skin->blit(display, m_location.x, m_location.y, true);
}

void Rocket::co_rocketScript()
{

  int a=3;
  SmokeTraits smoke(m_velocity);

  m_skin->setAngle(m_velocity.anglei());

  Point o(320, 240);
  while (true)
  {
    m_location.x += m_velocity.x;
    m_location.y += m_velocity.y;

    if (m_location.x >= 640)
    {
      m_velocity.x = -a;
      smoke.setShipVec(m_velocity);
      m_skin->setAngle(m_velocity.anglei());
    }
    if (m_location.x <= 0)
    {
      m_velocity.x = a;
      smoke.setShipVec(m_velocity);
      m_skin->setAngle(m_velocity.anglei());
    }
    if (m_location.y >=480)
    {
      m_velocity.y = -a;
      smoke.setShipVec(m_velocity);
      m_skin->setAngle(m_velocity.anglei());
    }
    if (m_location.y <=0)
    {
      m_velocity.y = a;
      smoke.setShipVec(m_velocity);
      m_skin->setAngle(m_velocity.anglei());
    }

    Point sp;
    Vector v = m_velocity.normalize();
    sp.x = m_location.x - (v.x*33);
    sp.y = m_location.y - (v.y*33);

    globals->particleSystem.fire(sp, 1, &smoke, 0);

    GameScheduler::resumeAt(NEXT_FRAME);

  }
}