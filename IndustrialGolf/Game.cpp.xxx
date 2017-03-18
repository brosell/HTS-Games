#pragma warning (disable : 4786 4503 4530)
#include "Game.h"
#include "Globals.h"
#include "Level.h"
#include "StringTokenizer.h"

#include "BR_Game.h"

Game::Game(string game)
{
  IniFile ini("Games.ini");
  ini.read();
  string maps = ini[game]["Levels"];
  StringTokenizer st(maps, " \r\n,");
  while (st.hasMoreTokens())
  {
    m_levels.push_back(st.nextToken());
  }

  //m_levels.push_back("test8.ini");
//  m_levels.push_back("test5.ini");
//  m_levels.push_back("test1.ini");
//  m_levels.push_back("test2.ini");
//  m_levels.push_back("test3.ini");
//  m_levels.push_back("test4.ini");
}

Game::~Game()
{

}

void Game::go()
{
  IniFile ini("ui/dialogs.ini");
  ini.read();

  list<string>::iterator i;
  for (i=m_levels.begin(); i!=m_levels.end() && Globals::run; i++)
  {
    IniBasedDialog levelUp(ini, "NewLevel");
    levelUp.doModal();

    Globals::console->execute("load %s", (*i).c_str());
    if (Globals::theLevel->isValid())
    {
      Globals::lastViewChangeWasMouse = false;
      Globals::theLevel->toWorld(Globals::world);
      
      Globals::world->optimize();
      
      while (Globals::theLevel->isSolved() == false && Globals::run)
      {
        theGame.pump();
        Globals::world->setViewportPos(Globals::viewX, Globals::viewY);
      }
      delete Globals::theLevel;
      Globals::theLevel = 0;
    }
  }

  IniBasedDialog gameover(ini, "GameOver");
  gameover.doModal();
}
/*
for each level
{
  while (level not solved by all players)
  {
    curPlayer = farthest player not solved
    setWorld = curPlayer->aWorld
    doModal GameStatsDialog (includes Current Player)
    doModal PlayScreen(curPlayer)
  }
}

PlayScreen::doModal(Player)
{
  setKeyListener(Player)
  wc->setWorld(Player->world);
  IniBasedDialog::doModal();
  removeKeyListener(Player)
}

*/
