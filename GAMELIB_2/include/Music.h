#ifndef Music_h
#define Music_h

#include "SoundMixer.h"
#include <string>
using namespace std;

/**
midi music
*/
class Music
{
public:
  /**
  @param filename the midi filename
  */
  Music(string filename);

  ~Music();

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