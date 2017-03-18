#ifndef SaveGame_h
#define SaveGame_h

#include "Engine.h"

/*
  This is really a saved demo. It will play at game speed. when loaded

  */



class SaveGame
{
public:
  SaveGame(string filename);
  ~SaveGame();

  void read();
  void write();

  void record(string str);

  void doTick(int gametick);


private:
  SaveGame(); // hidden
  SaveGame(const SaveGame& other); // hidden


  IniFile m_file;

  int m_lastTick;
  char m_lastPostfix;
}

#endif