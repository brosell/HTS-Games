#ifndef SoundEffect_h
#define SoundEffect_h

#include "SoundMixer.h"
#include <set>
#include <string>
using namespace std;

class SoundEffect: public ChannelListener
{
public:
  SoundEffect(string group, string filename);
  ~SoundEffect();
  
  void play(int loopcount = 0);
  void halt();
  void fadeOut(int millis);

  int getVolume();
  void setVolume(int volume);
  
  static void setVolume(string group, int volume);
  static int getVolume(string group);
  
  virtual void channelFinished(ChannelFinishedEvent* event);

  size_t getSize() { return m_size; }
private:
  void setVolume();
  void load(const char* filename);

  Mix_Chunk* m_soundData;
  int m_channel;
  string m_group;

  size_t m_size;

  static map<string, set<SoundEffect*> > s_fx;
  static map<string, int> s_volumes;
};

#endif