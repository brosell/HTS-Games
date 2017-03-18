
#ifndef Tile_h
#define Tile_h

#include "GameMath.h"
//#include "NewThing.h"
#include "Utils.h"
#include "IniFile.h"
#include <list>
#include <string>
#include "Globals.h"
#include "Face.h"


/**
  tiles are what the level is made out of. Tiles provide the GlofBall
  something to bounce off.

  Each tile has certain characteristics like how much force is absorbed
  and what the rolling resistance is (really the same thing I think).

  Somethings a tile can do (theoretic): add force to the ball, take all 
  the x force or the y force or both, cause the shot to be bad (ie water muligan)

  Because the shape of the tile is not set in stone, each tile will have a 
  collection of Faces. A Face is just a line segment. It is used to determin how
  The Ball will react and bounce off of the face.
  */

#define TILE_ID 12

class Tile: public Thing, Noncopyable
{
public:
  Tile(string type);
  virtual ~Tile();

  float getAbsorbFactor();
  void setAbsorbFactor();

  bool inRange(Point p, float radius, Line& ret);

  void addFace(Line l, float x, float y) { m_faces.push_back(Face(l, x, y)); }
  
  string getType() { return m_type; }

  static list<string> getTypes();

  virtual void draw(Display* display, int x, int y);

  typedef list<Face>::iterator faceIterator;
  faceIterator fbegin() { return m_faces.begin(); }
  faceIterator fend() { return m_faces.end(); }

private:
  RotateSkinHandle m_skin;
  list<Face> m_faces;
  string m_type;

  float m_xForceFactor;
  float m_yForceFactor;


  Line parseLine(string line);

  static IniFile s_ini;
  
};

class TileBackground: public Thing
{
public:
  TileBackground(): Thing(0)
  {
    m_skin = Globals::am->getRotateSkin("skn_World_Background");
    setSkin(m_skin);
  }

private:
  RotateSkinHandle m_skin;
};

#endif