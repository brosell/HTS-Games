#ifndef PlayerStuff_h
#define PlayerStuff_h

#include "Ship.h"
#include "SpaceTile.h"

class PlayerStuff
{
public:
  static PlayerStuff* get(int num);

  list<Ship*> shipList;

  SpaceTile* flagBase;
  RotateSkin* flagSkin;

private:
  PlayerStuff();
  PlayerStuff(const PlayerStuff& other);

  static map<int, PlayerStuff*> s_players;
};

#endif