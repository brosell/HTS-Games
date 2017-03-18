#ifndef Music_h
#define Music_h

#include "SoundMixer.h"

/**
midi music
*/
class Music
{
public:
  /**
  @param filename the midi filename
  */
  Music(const char* filename) { load(filename); }
  
  /**
  @param filename the midi filename
  */
  Music(string filename) { load(filename.c_str()); }

  /**
  starts playback opf the midi
  */
  void play(int loops);
  /**
  halts playback of the midi
  */
  void halt();

private:
  void load(const char* filename);
  Mix_Music* m_soundData;
};

#endif