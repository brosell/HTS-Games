#pragma warning (disable : 4503)

#include "SpaceTile.h"
#include "Game/World.h"

#include "Engine.h"

extern World* g_world;

set<SpaceTile*> SpaceTile::s_allTiles;

RotateSkin* SpaceTile::s_baseSkin = 0;
RotateSkin* SpaceTile::s_selectedSkin = 0;
RotateSkin* SpaceTile::s_tileSolid = 0;
RotateSkin* SpaceTile::s_solidFog = 0;
RotateSkin* SpaceTile::s_partialFog = 0;

SpaceTile::SpaceTile(int owner, TileType type):
GameThing(owner, 2, -1, false, true, 1),
m_type(type),
m_selected(false),
m_occupant(0),
astar_cost(1),
m_flag(0),
fog_everVisible(false),
fog_nowVisible(false)
{

  if (s_baseSkin == 0)
  {
    s_baseSkin = new RotateSkin(1);
    s_baseSkin->addImage("images\\LittleHexRed.bmp", 1);
    s_selectedSkin = new RotateSkin(1);
    s_selectedSkin->addImage("images\\LittleHexBlue.bmp", 1);

    s_tileSolid = new RotateSkin(1);
    s_tileSolid->addImage("images\\MapEditor\\tile_solid.bmp", 1);

    s_solidFog = new RotateSkin(1);
    s_solidFog->addImage("images\\solidFog.bmp", 1);

    s_partialFog = new RotateSkin(1);
    s_partialFog->addImage("images\\partialFog.bmp", 1);
  }

  // FIXME: set us up the graphics
  s_allTiles.insert(this);
  setSkin("BareHex", s_baseSkin);
  setSkin("BareHexBlue", s_selectedSkin);
  setSkin("Solid", s_tileSolid);

  showSkin("BareHex");
  if (type == TILE_SOLID)
  {
    showSkin("Solid");
  }
  
}

SpaceTile::~SpaceTile()
{
  s_allTiles.erase(this);
}

int SpaceTile::astar_doH(SpaceTile* end) // here to end
{
  int dx = (end->m_mapx - m_mapx);
  int dy = (end->m_mapy - m_mapy);
  astar_h = (abs(dx) + abs(dy));
  return astar_h;
}

int SpaceTile::astar_children(SpaceTile** nodes, int max, SpaceTile* end)
{
  SpaceTile* tiles[6];
  int count = Engine::instance->theMap->getNeighbors(m_mapx, m_mapy, tiles);
  int rc = 0;
  for (int c=0; c<count; c++)
  {
    if (tiles[c]->isNavigable())
    {
      if (!(tiles[c]->m_occupant != 0 && tiles[c] != end))
      {
        nodes[rc++] = tiles[c]; 
      }
    }
    else
    {
      c=c;
    }
  }
  return rc;
}

void SpaceTile::draw(Display* d, int x, int y)
{
  if (fog_everVisible)
  {
    GameThing::draw(d, x, y);
    if (!fog_nowVisible)
    {
      s_partialFog->blit(d, x, y);
    }
  }
  else
  {
    s_solidFog->blit(d, x, y);
  }

  if (m_flag != 0)
  {
    PlayerStuff* ps = PlayerStuff::get(m_flag);
    Point p = Engine::instance->theWorld->translateToScreen(getPositioni());
    ps->flagSkin->blit(d, p.x, p.y);
  }

//  if (m_selected)
//  {
//    s_selectedSkin->blit(d, x, y);
//  }


}
