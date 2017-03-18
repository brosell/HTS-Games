#include "Music.h"

void Music::load(const char* filename)
{
  m_soundData = Mix_LoadMUS(filename);
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

