#include "SpawnTile.h"
#include "Engine.h"

RotateSkin* SpawnTile::s_skin = 0;

SpawnTile::SpawnTile(int owner, list<Ship*>& ships):
SpaceTile(owner, TILE_SPECIAL),
m_waitTimer(0),
m_shipList(ships)
{
  if (s_skin == 0)
  {
    s_skin = new RotateSkin(1);
    s_skin->addImage("images\\SSTile.bmp", 1);
  }
  setSkin("Spawn", s_skin);
  showSkin("Spawn");
}

SpawnTile::~SpawnTile()
{

}

void SpawnTile::tick()
{
  if (m_shipList.size() > 0)
  {
    if (getOccupant() == 0)
    {
      if (m_waitTimer == 0)
      {
        // ok to spawn!
        Ship* ship = m_shipList.front();
        m_shipList.pop_front();
        ship->setPosition(getPositionf());
        Engine::instance->theWorld->addMovingThing(*ship);
        ship->spawn();
        m_waitTimer = Timer::create(GT_SPAWNPOINT_READY, 1000, this, 0, false);
      }
    }
  }
}

void SpawnTile::timeout(TimerEvent* event)
{
  lassert(event->id == GT_SPAWNPOINT_READY);
  m_waitTimer = 0;
}

