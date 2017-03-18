#pragma warning (disable : 4503)
#include "sqFlagBaseTile.h"

FlagBaseTile::FlagBaseTile(int owner):
SpaceTile(owner, TILE_FLAG)
{
  static RotateSkin* skin = 0;
  if (skin == 0)
  {
    skin = new RotateSkin(1);
    skin->addImage("images\\Square\\tile_flagbase.bmp", 1);
  }

  setSkin("Skin", skin);
  showSkin("Skin");

  m_flag = owner;
}

void FlagBaseTile::tick()
{
  if (m_flag == 0)
  {
    // FIXME: announce lost flag
  }

}
