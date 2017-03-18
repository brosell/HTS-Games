#include "Thing.h"

set<Thing*> Thing::s_things;
list<Thing*> Thing::s_safeDeleteList;

Thing::Thing(int z, int id, bool strikable, bool visible, int rotations):
m_z(z), 
m_id(id), 
m_strikable(strikable),
m_visible(visible),
m_currentSkin(0),
m_position(-1, -1),
m_angle(0),
m_rotations(rotations)
{
  init();
}

Thing::Thing(int z):
m_z(z), 
m_id(-1), 
m_strikable(false),
m_visible(true),
m_currentSkin(0),
m_position(-1, -1),
m_angle(0),
m_rotations(1)
{
  init();
}

void Thing::init()
{
  lassert( (m_z >= 0 && m_z<=15) );
  lassert(m_rotations > 0 && m_rotations <=72);
  if (m_z > 1)
  {
    s_things.insert(this);
  }
}

Thing::~Thing()
{
  m_skins.clear();
  s_things.erase(this);
}

//static 
void Thing::safeDelete(Thing* thing)
{
  s_safeDeleteList.push_back(thing);
}
void Thing::processSafeDeletes()
{
  list<Thing*>::iterator li;
  for (li=s_safeDeleteList.begin(); li!=s_safeDeleteList.end(); li++)
  {
    delete (*li);
  }
  s_safeDeleteList.clear();
}

void Thing::draw(Display* display, int x, int y)
{
  if (m_currentSkin != 0 && m_visible)
  {
    m_currentSkin->blit(display, x, y);
  }
}

void Thing::showSkin(string skinName)
{
  map<string, SharedRotateSkin*>::iterator pair;
  pair = m_skins.find(skinName);
  if (pair != m_skins.end())
  {
    m_currentSkin = pair->second;
    m_currentSkin->setAngle(m_angle);
  }
  else
  {
    m_currentSkin = 0;
  }
}


const CollisionBitMask* Thing::getCurrentCollisionBitMask() const
{
  if (m_currentSkin != 0)
  {
    return m_currentSkin->currentCollisionMask();
  }
  return 0;
}

bool Thing::checkCollision(Thing* thing1, Thing* thing2, Point& p1, Point& p2)
{
  const CollisionBitMask* thing1BM = thing1->m_currentSkin->currentCollisionMask();
  const CollisionBitMask* thing2BM = thing2->m_currentSkin->currentCollisionMask();

  Point thing1Pos = thing1->getPositioni();
  Point thing2Pos = thing2->getPositioni();

  // compensate for fact that position is the center position not the top left
  thing1Pos.x-=(thing1BM->getWidth()/2);
  thing1Pos.y-=(thing1BM->getHeight()/2);

  thing2Pos.x-=(thing2BM->getWidth()/2);
  thing2Pos.y-=(thing2BM->getHeight()/2);

  return testCollision(thing1BM, thing1Pos.x, thing1Pos.y,
                       thing2BM, thing2Pos.x, thing2Pos.y,
                       p1, p2);
}

void Thing::tickAll()
{
  set<Thing*>::iterator i;
  for (i=s_things.begin(); i!=s_things.end(); i++)
  {
    (*i)->tick();
  }

  processSafeDeletes();
}

void Thing::checkCollisions()
{
  set<Thing*>::iterator i1;
  set<Thing*>::iterator i2;

  Thing* thing1 = 0;
  Thing* thing2 = 0;

  Point p1;
  Point p2;
  int end=(s_things.size()/2) + 1;
  int t;
  for (i1=s_things.begin(), t=0; t<end; i1++, t++)
  {
    thing1 = *i1;
    if ( thing1->isStrikable() == false)
    {
      continue;
    }
    
    i2 = i1;
    i2++;
    for (; i2!=s_things.end(); i2++)
    {
      thing2 = *i2;
      if ( thing2->isStrikable() == false)
      {
        continue;
      }
      
      if (Thing::checkCollision(thing1, thing2, p1, p2))
      {
        thing1->hit(*thing2, p1);
        thing2->hit(*thing1, p2);
      }
    }
  }

  processSafeDeletes();
}

void Thing::getByDistance(int distance, list<Thing*>& aList, int id)
{
  set<Thing*>::iterator i1;
  set<Thing*>::iterator i2;

  Thing* thing = 0;

  Point p1;
  Point p2;

  int t;
  for (i1=s_things.begin(); i1!=s_things.end(); i1++)
  {
    thing = *i1;
    if ( thing->getId() != id)
    {
      continue;
    }

    if (isThingClose(thing, distance))
    {
      aList.push_back(thing);
    }
  }
}

void Thing::getByDistance(int distance, list<Thing*>& aList)
{
  set<Thing*>::iterator i1;
  set<Thing*>::iterator i2;

  Thing* thing = 0;

  Point p1;
  Point p2;

  int t;
  for (i1=s_things.begin(); i1!=s_things.end(); i1++)
  {
    thing = *i1;
    if ( thing->isStrikable() == false)
    {
      continue;
    }

    if (isThingClose(thing, distance))
    {
      aList.push_back(thing);
    }
  }
}

bool Thing::isThingClose(Thing* thing, int radius)
{
  int x, y;
  int w, h;
  int distToCenter;

  int m = getX();
  int n = getY();

  if (m+radius < thing->getTopLeftX())
  {
    return false;
  }
  if (m-radius > thing->getTopLeftX()+thing->getWidth())
  {
    return false;
  }
  if (n+radius < thing->getTopLeftY())
  {
    return false;
  }
  if (n-radius > thing->getTopLeftY() + thing->getHeight())
  {
    return false;
  }

  return true;
}

bool Thing::doesPointHit(Point p)
{
  Rect r(getTopLeftX(), getTopLeftY(), getWidth(), getHeight());
  if (r.containsPoint(p))
  {
    int mx = p.x - (getTopLeftX());
    int my = p.y - (getTopLeftY());
    return (getCurrentCollisionBitMask()->isPointCollision(mx, my));
  }
  return false;
}
