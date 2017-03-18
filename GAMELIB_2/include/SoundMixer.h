#ifndef SoundMixer_h
#define SoundMixer_h

#include "SDL_mixer.h"
#include <map>
using namespace std;;
/*
  We need to keep track of what channels are playing music
  and which are playing sfx. When the user changes volume on one
  we don;t want to change for the other, too.

  */

class ChannelFinishedEvent
{
public:
  int channel;
};

class ChannelListener
{
public:
  virtual void channelFinished(ChannelFinishedEvent* event) { }
};


class SoundMixer
{
public:

  static bool isOpen() { return s_isOpen; }

  static bool initialize(int audioRate, Uint16 audioFormat, int numChannels, int bufferSize = 4096);
  static void shutdown();

  static void bounce();

  static void allocateChannels(int channels)
  {
    Mix_AllocateChannels(channels);
  }

  /**
    play the loaded sound effect on the next available channel

    @param effect - the effect to play
    @param loopCount - the number of times to loop playback (0 means play the sound once, 1 means loop once, playing twice)
    @listener - if non-zero, this will be called when playback is finished

    @return the channel used
    */
  static int play(Mix_Chunk* effect, int loopCount, ChannelListener* listener = 0);

  static int play(Mix_Music* music, int loopCount);
  static void fadeOut(int channel, int millis);

  static void halt(int channel);

  static void channelDone(int channel);

private:
  static map<int, ChannelListener*> s_listeners;
  static bool s_isOpen;

  static int s_audioRate;
  static Uint16 s_audioFormat;
  static int s_numChannels;
  static int s_bufferSize;
};

#endif