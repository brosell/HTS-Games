#pragma warning (disable : 4786 4530 4503)

#include "Tee.h"
#include "Globals.h"

Tee::Tee():
Entity(14)
{
  string skinName = Globals::entityDefs["Tee"]["Skin"];

  m_skin = Globals::am->getRotateSkin(skinName);
  setSkin(m_skin);
}

Tee::~Tee()
{
  
}

void Tee::co_logic()
{
  // no logic? just a place holder so the level loader knows where to put the ball?
}
