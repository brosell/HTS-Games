#ifndef _World_h
#define _World_h

#include "Thing.h"
//#include "ThingCollection.h"
#include "Misc/GameMath.h"

#include "UI/Canvas.h"

class SortThingByX
{
public:
  operator()(Thing* one, Thing* two)
  {
    return one->getX() < two->getX();
  }
};

class SortThingByY
{
public:
  operator()(Thing* one, Thing* two)
  {
    return one->getY() < two->getY();
  }
};


class SortThingByZ
{
public:
  operator()(const Thing* one, const Thing* two) const
  {
    return const_cast<Thing*>(one)->getZ() < const_cast<Thing*>(two)->getZ();
  }
};

class ZLess: public std::unary_function<Thing*, bool>
{
public:
  ZLess(int z): m_z(z) { }
  bool operator()(Thing* t1)
  {
    return (t1->getZ() < m_z);
  }
private:
  int m_z;
};

class ZMore: public std::unary_function<Thing*, bool>
{
public:
  ZMore(int z): m_z(z) { }
  bool operator()(Thing* t1)
  {
    return (t1->getZ() > m_z);
  }
private:
  int m_z;
};

class PointHitsThing: public std::unary_function<Thing*, bool>
{
public:
  PointHitsThing(Point& p): m_p(p) { }
  bool operator()(Thing* t)
  {
    return (t->getPositionr().containsPoint(m_p));
  }
private:
  Point& m_p;
};

class ThingOverlapsRect: public std::unary_function<Thing*, bool>
{
public:
  ThingOverlapsRect(Rect* r) : m_r(r) { }
  bool operator()(Thing* t)
  {
    return Rect::checkOverlap(m_r, &(t->getPositionr()));
  }
private:
  Rect* m_r;
};

class ThingOverlapsRect2: public std::unary_function<Thing*, bool>
{
public:
  ThingOverlapsRect2(Rect* r, int min, int max) : m_r(r), m_minZ(min), m_maxZ(max) { }
  bool operator()(Thing* t) 
  {
    if (t->getZ() >= m_minZ && t->getZ() <= m_maxZ)
    {
      return Rect::checkOverlap(m_r, &(t->getPositionr()));
    }
    return false;
  }
private:
  Rect* m_r;
  int m_minZ;
  int m_maxZ;
};


class World
{
public:
  World(int w, int h, int physX=0, int physY=0, int vw=640, int vh=480);


  /** 
    Adds a static thing to the world.
    */
  void addThing(Thing& thing);
  /**
    Adds a moving thing to the world
    */
  void addMovingThing(Thing& thing);
  /** 
    removes a thing
    */
  void removeThing(Thing& thing);
  /**
    organizes the data structures to allow searching
    for things by location quicker
    */
  void optimize();

  bool isThingVisable(Thing* thing);

  void parallaxScroll(int z, float amount) { m_parallaxAmount[z] = amount; }
  float getParallaxScroll(int z) { return m_parallaxAmount[z]; }

  /** 
  finds the Thing in the Moving collection lacated at a point. The point passed
  in is reletive to the world canvas this worls live in.
  @param x the screen location
  @param y the screen location
  @return a thing from that location or 0 if non found
  */
  Thing* movingThingAt(int x, int y);

  /**
  Returns the thing at World coord x, y in the z layer
  */
  Thing* getThingAt(int x, int y, int z); // check z - zorder

  Thing* getThingAtScreenCoord(int x, int y, int z)
  {
    Point p = translateScreenPoint(Point(x, y));
    return getThingAt(p.x, p.y, z);
  }

  /**
    Draws the world
    */
  void draw(Display* surface = 0);

  /**
    Sets the top left corner of the viewable world.
    relative to world
    */
  void setViewportPos(int x, int y) 
  { 
    m_viewportX = x;
    m_viewportY = y;
  }

  /**
  relative to screen
  */
  void setViewportPhysical(int physX, int physY, int physW, int physH)
  {
    m_viewportPhysicalX=physX;
    m_viewportPhysicalY=physY;
    m_viewportWidth = physW;
    m_viewportHeight = physH;
  }

  Rect getWorldDimensions()
  {
    return Rect(0, 0, m_width, m_height);
  }

  void setWorldDimensions(Rect& r)
  {
    m_width = r.w;
    m_height = r.h;
  }

  Rect getViewportDimensions()
  {
    return Rect(m_viewportX, m_viewportY, m_viewportWidth, m_viewportHeight);
  }

  Rect getPhysicleViewport()
  {
    return Rect(m_viewportPhysicalX, m_viewportPhysicalY, m_viewportWidth, m_viewportHeight);
  }

  /**
    finds all the Things in the world bounded by a rectangle
    @param r the Rect
    @param array a pointer to a previously allocated array of Thing*
    @param max the maximun number of things to return
    @param ignoreZ0 true to ignore things at Z order zero (the background)
    @return number of Things returned in array
    */
//  int getByRect(Rect& r, Thing** array, int max, bool ignoreZ0 = false)
//  {
//    return getByRect(r, array, max, (int)(ignoreZ0?1:0));
//  }

  /**
    finds all the Things in the world bounded by a rectangle
    @param r the Rect
    @param array a pointer to a previously allocated array of Thing*
    @param max the maximun number of things to return
    @param minZ the base Z order to start search
    @param maxZ the maximum Z to search
    @return number of THings in the rect. This number may be more than
    max, in which case the array doesn't contain all the things
    */
//  int getByRect(Rect& r, Thing** array, int max, int minZ=0, int maxZ=15)
//  {
//    return things.getByRect(&r, array, max, minZ, maxZ);
//  }

  /**
    determins whether something can fit in the world 
    without hitting anything else. Seems to check only Z's 5-9?
    @return true if there is nothing in the way
    */
  bool canThingFit(Rect* r, int x, int y)
  {
    Rect hole(x, y, r->w-1, r->h-1);
    return true; //things.canThingFit(&hole, 5, 9);
  }
  
  /**
    adjusts a Rect so that it is completely in the world.
    */
  void constrainToWorld(Rect& r)
  {
    Rect worldDim=getWorldDimensions();
    if (r.x < 0) r.x=0;
    if (r.x+r.w > worldDim.w) r.x = worldDim.w - r.w;
    if (r.y < -100) 
      r.y=-100;
    if (r.y+r.h > worldDim.h) 
      r.y = worldDim.h - r.h;
  }

  bool computeMovement(Rect* thingRect, int startX, int startY, int destX, int destY, int& endX, int& endY);

  /**
    Translates a point reletive to the WorldCanvas to World coords
    */
  Point translateScreenPoint(Point p)
  {
    return Point(p.x+m_viewportX-m_viewportPhysicalX, p.y+m_viewportY-m_viewportPhysicalY);
  }

  /**
    translates a World coord to a screen coord
    */
  Point translateToScreen(Point p)
  {
    int viewportRelativeX=p.x - m_viewportX;
    int viewportRelativeY=p.y - m_viewportY;

    int screenRelativeX=viewportRelativeX + m_viewportPhysicalX;
    int screenRelativeY=viewportRelativeY + m_viewportPhysicalY;
    return Point(screenRelativeX, screenRelativeY);
  }

  void drawThing(Thing* t);

private:
  // world
  int m_width;
  int m_height;

  
  // top left corner relative to world
  int m_viewportX;
  int m_viewportY;
  
  // relative to screen
  int m_viewportPhysicalX;
  int m_viewportPhysicalY;
  int m_viewportWidth;
  int m_viewportHeight;

  float m_parallaxAmount[16];

  //ThingCollection things;
  vector<Thing*> m_things;
};

#endif
