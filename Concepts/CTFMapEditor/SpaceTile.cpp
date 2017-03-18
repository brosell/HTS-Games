#include "SpaceTile.h"
#include "Game/World.h"

#include "Engine.h"

extern World* g_world;

set<SpaceTile*> SpaceTile::s_allTiles;
RotateSkin* SpaceTile::s_baseSkin = 0;
RotateSkin* SpaceTile::s_selectedSkin = 0;
RotateSkin* SpaceTile::s_asteroidSkin;
RotateSkin* SpaceTile::s_nebulaSkin;
RotateSkin* SpaceTile::s_solidSkin;
RotateSkin* SpaceTile::s_spawnSkin;
RotateSkin* SpaceTile::s_flagbaseSkin;

RotateSkin* SpaceTile::s_player1Skin;
RotateSkin* SpaceTile::s_player2Skin;


SpaceTile::SpaceTile():
GameThing(0, 2, -1, false, true, 1),
m_type(TILE_EMPTY),
m_selected(false)
{
  if (s_baseSkin == 0)
  {
    s_baseSkin = new RotateSkin(1);
    s_baseSkin->addImage("images\\MapEditor\\tile_Empty.bmp", 1);

    s_player1Skin = new RotateSkin(1);
    s_player1Skin->addImage("images\\MapEditor\\marker_Player1.bmp", 1);

    s_player2Skin = new RotateSkin(1);
    s_player2Skin->addImage("images\\MapEditor\\marker_Player2.bmp", 1);


    s_selectedSkin = new RotateSkin(1);
    s_selectedSkin->addImage("images\\MapEditor\\marker_Selected.bmp", 1);
    
    s_asteroidSkin = new RotateSkin(1);
    s_asteroidSkin->addImage("images\\MapEditor\\tile_asteroid.bmp", 1);

    s_nebulaSkin = new RotateSkin(1);
    s_nebulaSkin->addImage("images\\MapEditor\\tile_nebula.bmp", 1);
    
    s_solidSkin = new RotateSkin(1);
    s_solidSkin->addImage("images\\MapEditor\\tile_solid.bmp", 1);
    
    s_spawnSkin = new RotateSkin(1);
    s_spawnSkin->addImage("images\\MapEditor\\tile_spawn.bmp", 1);

    s_flagbaseSkin = new RotateSkin(1);
    s_flagbaseSkin->addImage("images\\MapEditor\\tile_flagbase.bmp", 1);
  }

  // FIXME: set us up the graphics
  s_allTiles.insert(this);
  setSkin("Empty", s_baseSkin);
  setSkin("Selected", s_selectedSkin);

  setSkin("Asteroid", s_asteroidSkin);
  setSkin("Nebula", s_nebulaSkin);
  setSkin("Solid", s_solidSkin);
  setSkin("Spawn", s_spawnSkin);
  setSkin("Flag", s_flagbaseSkin);

  showSkin("Empty");
}

SpaceTile::~SpaceTile()
{
  s_allTiles.erase(this);
}

void SpaceTile::setType(TileType t)
{
  m_type = t;
  switch(m_type)
  {
  case TILE_EMPTY:
    {
      showSkin("Empty");
    }
    break;
  case TILE_ASTEROID:
    {
      showSkin("Asteroid");
    }
    break;
  case TILE_NEBULA:
    {
      showSkin("Nebula");
    }
    break;
  case TILE_SOLID:
    {
      showSkin("Solid");
    }
    break;
  case TILE_SPAWN:
    {
      showSkin("Spawn");
    }
    break;
  case TILE_FLAG:
    {
      showSkin("Flag");
    }
    break;
  default:
    {
      logError("Unknown Tile Type %d", m_type);
      showSkin("Empty");
    }
    break;
  }
}

void SpaceTile::draw(Display* d, int x, int y)
{
  Thing::draw(d, x, y);
  if (m_selected)
  {
    s_selectedSkin->blit(d, x, y);
  }

  if (getOwner() == 1)
  {
    s_player1Skin->blit(d, x, y);
  }
  else if (getOwner() == 2)
  {
    s_player2Skin->blit(d, x, y);
  }

}
