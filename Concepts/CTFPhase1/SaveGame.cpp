#include "SaveGame.h"

SaveGame::SaveGame(string filename): m_file(filename)
{
  m_lastTick = 0;
  m_lastPostfix = 'a';
}

SaveGame::~SaveGame()
{

}

void SaveGame::read()
{

}

void SaveGame::write()
{

}

void SaveGame::record(string str)
{
  int gametick = BR_Game.ticknum;

  if (gametick == lasttick)
  {
    lastletter+=1;
  }
  else
  {
    lastletter = 'a';
    lasttick = gametick;
  }

  char buf[255];
  sprintf(buf, "%06d-%c", gametick, lastletter);

  m_file["SaveGame"][buf] = str;
}

void SaveGame::doTick(int gametick)
{

}



