#include "SoundMixer.h"

map<int, ChannelListener*> SoundMixer::s_listeners;
bool SoundMixer::s_isOpen = false;

int SoundMixer::s_audioRate;
Uint16 SoundMixer::s_audioFormat;
int SoundMixer::s_numChannels;
int SoundMixer::s_bufferSize;

bool SoundMixer::initialize(int audioRate, Uint16 audioFormat, int numChannels, int bufferSize)
{
  s_isOpen = true;
  if(Mix_OpenAudio(audioRate, audioFormat, numChannels, bufferSize) != 0) 
  {
    logError(Error, "Failed to initialize SDL_Mixer");
    s_isOpen = false;
    return false;
  }
  Mix_ChannelFinished(SoundMixer::channelDone);
  return s_isOpen;
  s_audioRate = audioRate;
  s_audioFormat = audioFormat;
  s_numChannels = numChannels;
  s_bufferSize = bufferSize;
}

void SoundMixer::shutdown()
{
  Mix_CloseAudio();
}

void SoundMixer::bounce()
{
  if (isOpen())
  {
    shutdown();
    initialize(s_audioRate, s_audioFormat, s_numChannels, s_bufferSize);
  }
}

int SoundMixer::play(Mix_Chunk* effect, int loopCount, ChannelListener* listener)
{
  int channel = Mix_PlayChannel(-1, effect, loopCount);
  if (listener)
  {
    //s_listeners[channel] = listener;
  }
  return channel;
}

int SoundMixer::play(Mix_Music* music, int loopCount)
{
  int res = Mix_PlayMusic(music, loopCount);
  return res;
}



void SoundMixer::halt(int channel)
{
  Mix_HaltChannel(channel);
}

void SoundMixer::fadeOut(int channel, int millis)
{
  Mix_FadeOutChannel(channel, millis);
}

void SoundMixer::channelDone(int channel)
{
  static ChannelFinishedEvent event;
  
  map<int, ChannelListener*>::iterator pair;
  pair = s_listeners.find(channel);
  if (pair != s_listeners.end())
  {
    event.channel = channel;
    ChannelListener* listener = pair->second;
    s_listeners.erase(pair);
    if (listener != 0)
    {
      listener->channelFinished(&event);
    }
  }
}
