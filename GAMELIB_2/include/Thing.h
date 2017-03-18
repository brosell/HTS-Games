#ifndef _Thing_h
#define _Thing_h

#pragma warning (disable: 4786 4503 4530)

#include "AM.h"

/**
  Things are entities. This class provide many methods to manage
  Entities.
  */
class Thing
{
public:
  Thing(int z, int id, bool strikable, bool visible, int rotations);
  Thing(int z);
  virtual ~Thing();

  static void safeDelete(Thing* thing);

  /**
    @return the X coord of the center as an int rounded
    */
  int getX() { return (m_position.x + 0.5); }
  /**
    @return the Y coord of the center  as an int rounded
    */
  int getY() { return (m_position.y + 0.5); }
  /**
    @return the Z order of this Thing
    */
  int getZ() { return m_z; }
  void setZ(int z) { m_z = z; }

  float getXf() { return m_position.x; }
  float getYf() { return m_position.y; }
  void setXf(float x) { m_position.x = x; }
  void setYf(float y) { m_position.y = y; }
  void setPosition(float x, float y) { m_position.x = x; m_position.y = y; }

  /**
    returns the X coord of the topleft hand corner. It takes into account
    the current rotation of the image
    */
  int getTopLeftX() { return getX() - (getWidth()/2); }
  /**
    returns the Y coord of the topleft hand corner. It takes into account
    the current rotation of the image
    */
  int getTopLeftY() { return getY() - (getHeight()/2); }

  /** returns the width of the current rotation of the image */
  virtual int getWidth() { return m_currentSkin->getWidth(); }
  /** returns the height of the current rotation of the image */
  virtual int getHeight() { return m_currentSkin->getHeight(); }

  Rect getPositionr()
  {
//    tRect.x=cur->getX()-(cur->getWidth()/2);
//    tRect.y=cur->getY()-(cur->getHeight()/2);
//    tRect.w=cur->getWidth();
//    tRect.h=cur->getHeight();
    return Rect(getTopLeftX(), getTopLeftY(), getWidth(), getHeight());
  }

  int getId() const { return m_id; }
  void setId(int i) { m_id = i; }

  bool isStrikable() const { return m_strikable; }
  void setStrikable(bool s) { m_strikable = s; }

  bool isVisible() const { return m_visible; }
  void setVisible(bool v) { m_visible = v; }

  /**
    empty implementation of the interface to the tick mechanism. 
    Probably deprecated in lue of coroutines
    */
  virtual void tick() { }
  
  /**
    draws the current image to the display
    */
  virtual void draw(Display* display, int x, int y);

  void setPosition(FPoint pos) { m_position = pos; }
  FPoint getPositionf() const { return m_position; }
  Point getPositioni() const { return Point(m_position.x+0.5, m_position.y+0.5); }

  void setDrawAngle(int a) { m_angle = a; }
  int getDrawAngle() { return m_angle; }

  /**
  Skin management:
  needs revamping. A script driven solution is to be developed
  */
  //void showSkin(string skinName);
  //void setSkin(string skinName, AM::RotateSkinHandle skin) { m_skins[skinName]=skin; }
  RotateSkinHandle& getCurrentSkin() { return m_currentSkin; }
  void setSkin(RotateSkinHandle& skin) { m_currentSkin = skin; }

  const CollisionBitMask* getCurrentCollisionBitMask();
  
  /**
    called when this thing is hit by another via checkCollisions
    */
  virtual void hit(Thing& other, Point where) { }

  /**
    checks for collision between two Things
    */
  static
  bool checkCollision(Thing* thing1, Thing* thing2, Point& p1 = Point(), Point& p2 = Point());

  /**
    loops through all instanciated Things and calls its tick method
    */
  static
  void tickAll();

  /**
    checks for collisions between all the things
    */
  static
  void checkCollisions();

  /**
    compiles a list of all the Things within distance units of this Thing
    */
  void getByDistance(int distance, list<Thing*>& aList);

  void getByDistance(int distance, list<Thing*>& aList, int id);
  /**
    determins is thing is withing radius units of this Thing
    */
  bool isThingClose(Thing* thing, int radius);
  /**
    determins whether the World coord p hits this Thing taking into account
    the Collision mask
    */
  bool doesPointHit(Point p);

protected:
  void init();
private:
  int m_z;
  int m_id;
  bool m_strikable;
  bool m_visible;

  map<string, RotateSkinHandle> m_skins;
  RotateSkinHandle m_currentSkin;
  int m_rotations;

  FPoint m_position;
  int m_angle;


  static set<Thing*> s_things;
  static list<Thing*> s_safeDeleteList;
  static void processSafeDeletes();
  
};

inline bool checkCollision(Thing* thing1, Thing* thing2) { return Thing::checkCollision(thing1, thing2); }
#endif
