#ifndef SpaceTile_h
#define SpaceTile_h

#include "Game/Thing.h"
#include "GameThing.h"
/* SpaceTile
    Hexagon shaped tile that has certain characteristics based on the type
  */


/* FIXME: It would be neat if these tiles could have 2 textures. One base texture
         and one upper texture. Then the ships would be sandwiched between them...
        Well, the Tile can have another Thing created at Z-16. That sould do it...

  A cool effect of this is that ships are harder to see by the player because of
    extra graphics drawn above it, therefor (and henceforth) it may add to the strategy.
*/


enum TileType
{
  TILE_EMPTY,
  TILE_ASTEROID,
  TILE_NEBULA,
  TILE_SOLID,
  TILE_SPAWN,
  TILE_FLAG
};

class SpaceTile: public GameThing
{
public:
  SpaceTile(int owner, TileType type); // top left
  ~SpaceTile();

  virtual bool isNavigable() { return m_type != TILE_SOLID; }
  TileType getType() { return m_type; }

  void setCoords(int x, int y)
  {
    m_mapx = x;
    m_mapy = y;
  };

  Point getCoords()
  {
    return Point(m_mapx, m_mapy);
  }

  void setSelected(bool s) { m_selected = s; }

  GameThing* getOccupant() { return m_occupant; }
  void setOccupant(GameThing* thing) 
  { 
    lassert (thing == 0 || getOccupant() == 0 || getOccupant() == thing);
    m_occupant = thing;
  }

  virtual void draw(Display* d, int x, int y);

  /////////////////////////////
  // ASTAR
  ////////////////////////////
  int astar_doH(SpaceTile* end); // here to end

  int astar_children(SpaceTile** nodes, int max, SpaceTile* end);

  SpaceTile* astar_parent;
  int astar_cost; // cost of this node
  int astar_g; // cost to get to this node
  int astar_h; 

  int m_flag; // 0 or player number


  //////////////////////////////
  // FOG OF WAR
  //////////////////////////////
  bool fog_nowVisible;
  bool fog_everVisible;

private:
  int m_mapx;
  int m_mapy;

  TileType m_type;

  bool m_selected;

  GameThing* m_occupant;

  static set<SpaceTile*> s_allTiles;
  static RotateSkin* s_baseSkin;
  static RotateSkin* s_selectedSkin;
  static RotateSkin* s_tileSolid;
  static RotateSkin* s_solidFog;
  static RotateSkin* s_partialFog;

  // hide
  SpaceTile();
};

#endif