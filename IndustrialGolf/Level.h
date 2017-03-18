#ifndef Level_h
#define Level_h

#include "BR_Game.h"
#include <list>
#include <set>
#include "Tile.h"
#include "Entity.h"
#include "GolfBall.h"
#include "Goal.h"
#include "Club.h"
#include "Face.h"

class Level: public GoalListener
{
public:
  Level(string filename);
  ~Level();

  void toWorld(World* world);
  void removeFromWorld();

  float getGravity() { return m_gravity; }

  bool isValid();

  virtual void goalAchieved(Goal* goal);

  bool isSolved() { return m_solved; }

  typedef set<Entity*>::iterator iterator;
  iterator ebegin() { return m_entities.begin(); }
  iterator eend() { return m_entities.end(); }

  typedef set<Tile*>::iterator tileIterator;
  tileIterator tbegin() { return m_tiles.begin(); }
  tileIterator tend() { return m_tiles.end(); }

protected:
  void loadEntities(IniFile& ini);
  void loadTiles(IniFile& ini);
  void loadFaces(IniFile& ini);
  void loadBackground(IniFile& ini);

private:
  bool m_solved;
  float m_gravity;
  World* m_world;
  bool m_valid;
  set<Tile*> m_tiles;
  set<Entity*> m_entities;
  list<Face> m_faces;

  set<Thing*> m_background;

  GolfBall* m_ball;
//  Club* m_club;

  Rect m_worldSize;
};

#endif