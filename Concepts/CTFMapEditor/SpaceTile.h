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
//  SpaceTile(int owner, TileType type); // top left
  SpaceTile();
  ~SpaceTile();

  virtual bool isNavigable() { return m_type != TILE_SOLID; }
  TileType getType() { return m_type; }
  void setType(TileType t);

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

  virtual void draw(Display* d, int x, int y);

private:
  int m_mapx;
  int m_mapy;

  TileType m_type;

  bool m_selected;

  static set<SpaceTile*> s_allTiles;
  static RotateSkin* s_baseSkin;
  static RotateSkin* s_selectedSkin;
  static RotateSkin* s_asteroidSkin;
  static RotateSkin* s_nebulaSkin;
  static RotateSkin* s_solidSkin;
  static RotateSkin* s_spawnSkin;
  static RotateSkin* s_flagbaseSkin;

  static RotateSkin* s_player1Skin;
  static RotateSkin* s_player2Skin;


  // hide

};

#endif