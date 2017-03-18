#include "PlayerStuff.h"

map<int, PlayerStuff*> PlayerStuff::s_players;


PlayerStuff::PlayerStuff(): 
flagBase(0) 
{
  static RotateSkin* skin = 0;
  if (skin == 0)
  {
    skin = new RotateSkin(1);
    skin->addImage("images\\flag.bmp", 1);
  }
  flagSkin = skin;
}

PlayerStuff* PlayerStuff::get(int num)
{
  PlayerStuff* ret = s_players[num];
  if (ret == 0)
  {
    ret = new PlayerStuff;
    s_players[num] = ret;
  }
  return ret;
}
