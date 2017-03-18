#pragma warning (disable : 4786)

#include "SoundEffect.h"
#include "FileManager.h"
#include "Log.h"

map<string, set<SoundEffect*> > SoundEffect::s_fx;
map<string, int> SoundEffect::s_volumes;

SoundEffect::SoundEffect(string group, string filename):
m_group(group),
m_channel(-1)
{ 
  load(filename.c_str()); 
  s_fx[m_group].insert(this);

  m_size = fm_fileSize(filename);
}

SoundEffect::~SoundEffect()
{
  if (m_channel != -1)
  {
    halt();
  }
  Mix_FreeChunk(m_soundData);
  s_fx[m_group].erase(this);
}

void SoundEffect::load(const char* filename)
{
  SDL_RWops* rw;
  void* buffer;
  int size = loadFileToMemory(filename, &buffer);
  if (size <= 0)
  {
    m_soundData = 0;
    return;
  }

  rw = SDL_RWFromMem(buffer, size);
  
  m_soundData = Mix_LoadWAV_RW(rw, 0);
  
  SDL_FreeRW(rw);
  free(buffer);

  if (m_soundData == 0)
  {
    logError(Error, "Failed to load SoundEffect (%s) - %s", filename, Mix_GetError());
  }
}


void SoundEffect::play(int loopcount)
{
  if (m_soundData == 0)
  {
    return;
  }
  m_channel = SoundMixer::play(m_soundData, loopcount, this);
  setVolume();
}

void SoundEffect::halt()
{
  if (m_channel != -1)
  {
    SoundMixer::halt(m_channel);
  }
}

void SoundEffect::fadeOut(int millis)
{
  SoundMixer::fadeOut(m_channel, millis);
}

void SoundEffect::channelFinished(ChannelFinishedEvent* event)
{
  m_channel = -1;
}

/*static*/
void SoundEffect::setVolume(string group, int volume)
{
  s_volumes[group] = volume;
  set<SoundEffect*>::iterator i;
  for (i=s_fx[group].begin(); i!=s_fx[group].end(); i++)
  {
    (*i)->setVolume(volume);
  }
}

/*static*/
int SoundEffect::getVolume(string group)
{
  return s_volumes[group];
//  int count = 0;
//  int total = 0;
//  
//  set<SoundEffect*>::iterator i;
//  for (i=s_fx[group].begin(); i!=s_fx[group].end(); i++)
//  {
//    count++;
//    total+=(*i)->getVolume();
//  }
//  if (count == 0)
//  {
//    return 0;
//  }
//  return total/count;
}

int SoundEffect::getVolume()
{
  return Mix_VolumeChunk(m_soundData, -1);
}

void SoundEffect::setVolume(int volume)
{
  Mix_VolumeChunk(m_soundData, volume);
}

void SoundEffect::setVolume()
{
  Mix_VolumeChunk(m_soundData, s_volumes[m_group]);
}
