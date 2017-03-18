#include "World.h"
#include "Thing.h"

#include "Log.h"

#include <vector>
#include <algorithm>


World::World(int w, int h, int physX, int physY, int vw, int vh):
m_width(w), 
m_height(h),
m_viewportPhysicalX(physX),
m_viewportPhysicalY(physY),
m_viewportWidth(vw),
m_viewportHeight(vh)
{
  for (int c=0; c<16; c++) m_parallaxAmount[c] = 1;
}

void World::addThing(Thing& thing)
{
  m_things.push_back(&thing);
}

void World::addMovingThing(Thing& thing)
{
  m_things.push_back(&thing);
}

void World::removeThing(Thing& thing)
{
  m_things.erase(std::remove(m_things.begin(), m_things.end(), &thing));
}

void World::optimize()
{
  std::sort(m_things.begin(), m_things.end(), SortThingByZ());
}

#include "BR_Game.h"

class DrawThing: std::unary_function<Thing*, void>
{
public:
  DrawThing(World* w, ThingOverlapsRect2 p): m_world(w), m_p(p) 
  { 
    m_viewport = m_world->getViewportDimensions();
    m_viewportPhysical = m_world->getPhysicleViewport();
  }
  void operator()(Thing* thing)
  {
    if (m_p(thing))
    {
      Point p=thing->getPositioni();
      
      int screenRelativeX = p.x - (m_viewport.x*m_world->getParallaxScroll(thing->getZ())) + m_viewportPhysical.x;
      int screenRelativeY = p.y - (m_viewport.y*m_world->getParallaxScroll(thing->getZ())) + m_viewportPhysical.y;
      
      thing->draw(Display::getInstance(), screenRelativeX, screenRelativeY);
      //m_world->drawThing(thing);
    }
  }
private:
  World* m_world;
  ThingOverlapsRect2 m_p;
  Rect m_viewport;
  Rect m_viewportPhysical;
  float m_para;
};

void World::drawThing(Thing* thing)
{
  Point p=thing->getPositioni();

  int screenRelativeX = p.x - (m_viewportX*m_parallaxAmount[thing->getZ()]) + m_viewportPhysicalX;
  int screenRelativeY = p.y - (m_viewportY*m_parallaxAmount[thing->getZ()]) + m_viewportPhysicalY;
  
  thing->draw(Display::getInstance(), screenRelativeX, screenRelativeY);
}

void World::draw(Display* surface)
{
#ifdef _DEBUG
  StopWatch sw;
  sw.start();
#endif

  Display* display = surface;
  display->pushClipRect(Rect(m_viewportPhysicalX, m_viewportPhysicalY, m_viewportWidth, m_viewportHeight));

  static Rect vr;
  vr.w=m_viewportWidth * m_parallaxAmount[1];
  vr.h=m_viewportHeight * m_parallaxAmount[1];
  
  vr.x = m_viewportX;
  vr.y = m_viewportY;

  for_each(m_things.begin(), m_things.end(), DrawThing(this, ThingOverlapsRect2(&vr, 0, 15)));

  display->popClipRect();

#ifdef _DEBUG
  sw.stop();
  theGame.setWorldDraw(sw.getElapsedTime());
#endif
  
}



Thing* World::movingThingAt(int x, int y)
{
//  Point trans = translateScreenPoint(Point(x, y));
//  Rect r(trans.x, trans.y, 0, 0);
//  Thing* array[15];
//  //int count = movingThings.getByRect(&r, array, 15);
//  vector<Thing*> v;
//  movingThings.getByRect(&r, back_inserter(v));
//  ThingCollection::VTI i;
//  for (i=v.begin(); i!=v.end(); i++)
//  {
//    Thing* thing = *i;
//    int mx = trans.x - (thing->getTopLeftX());
//    int my = trans.y - (thing->getTopLeftY());
//    if (thing->getCurrentCollisionBitMask()->isPointCollision(mx, my))
//    {
//      return thing;
//    }
//  }
  return 0;
}

Thing* World::getThingAt(int x, int y, int z)
{
//  Point trans = translateScreenPoint(Point(x, y));
//  Rect r(trans.x, trans.y, 0, 0);
//  vector<Thing*> v;
//  movingThings.getByRect(&r, back_inserter(v), z, z);
//  ThingCollection::VTI i;
//  for (i=v.begin(); i!=v.end(); i++)
//  {
//    Thing* thing = *i;
//    int mx = trans.x - (thing->getTopLeftX());
//    int my = trans.y - (thing->getTopLeftY());
//    if (thing->getCurrentCollisionBitMask()->isPointCollision(mx, my))
//    {
//      return thing;
//    }
//  }
  return 0;
}

bool World::isThingVisable(Thing* thing)
{
  Rect r(thing->getTopLeftX(), thing->getTopLeftY(), thing->getWidth(), thing->getHeight());
  Rect wv = getViewportDimensions();
  return Rect::checkOverlap(&r, &wv);
}