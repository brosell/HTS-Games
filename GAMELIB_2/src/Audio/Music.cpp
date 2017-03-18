#pragma warning (disable : 4786)

#include "Music.h"
#include "Log.h"
#include "FileManager.h"

Music::Music(string filename) :
m_soundData(0)
{ 
  load(filename.c_str()); 
}


Music::~Music()
{
  if (m_soundData)
  {
    Mix_FreeMusic(m_soundData);
  }
}

void Music::load(const char* filename)
{
  FILE* fp = FileManager::FP(filename);
  long h = ftell(fp);
  m_soundData = Mix_LoadOGG(fp);
//  m_soundData = Mix_LoadMUS(filename);
  
  if (m_soundData == 0)
  {
    logError(Error, "Failed to load Music (%s) - %s", filename, Mix_GetError());
  }
}

void Music::play(int loops)
{
  if (m_soundData == 0)
  {
    return;
  }
  SoundMixer::play(m_soundData, loops);
}

void Music::halt()
{
  Mix_HaltMusic();
}

