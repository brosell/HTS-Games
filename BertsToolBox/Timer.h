#ifndef Timer_h
#define Timer_h

#include <time.h>
#include <windows.h>
#include <mmsystem.h>

#include <set>
#include <list>
#include <string>
using namespace std;

#include "Delegate.h"

typedef void* HTimer;

class Timer;

class CompareTimer
{
public:
  bool operator() (const Timer* t1, const Timer* t2) const;
};

class StopWatch
{
public:
  StopWatch()
  {
    reset();
  }
  ~StopWatch()
  {
  }

  void start()
  {
    m_startTime = timeGetTime();
  }

  void stop()
  {
    m_elapsedTime += (timeGetTime() - m_startTime);
    m_runCount++;
  }

  void reset()
  {
    m_runCount = 0;
    m_startTime = 0;
    m_elapsedTime = 0;
  }

  DWORD getCurrentTime() { return (timeGetTime() - m_startTime); }

  DWORD getElapsedTime() { return m_elapsedTime; }
  float getAverage() { return (float)m_elapsedTime/(float)m_runCount; }

  size_t getRunCount() { return m_runCount; }

  
private:
  DWORD m_startTime;
  DWORD m_elapsedTime;
  size_t m_runCount;
};


class TimerEvent
{
public:
  HTimer timer;
  int id;
  void* param;
};

class TimerListener
{
public:
  virtual void timeout(TimerEvent* event) = 0;
};



class Timer
{
public:
  Timer(): m_markedForDeath(false) {}
  
  static HTimer create(int id, int millis, TimerListener* listener, void* param, bool recurring = false);
  static HTimer create(string str, int id, int millis, TimerListener* listener, void* param, bool recurring = false);

  static void destroy(HTimer timer)
  {
    ((Timer*)timer)->m_markedForDeath = true;
  }

  static void cleanup();
  
  static int tick();

  static void report();

  void expire()
  {
    if (m_markedForDeath)
    {
      delete this;
      return;
    }

    m_listener->timeout(&m_event);

    if (m_markedForDeath)
    {
      int yyy=0;
    }
    
    if (m_recurring && !m_markedForDeath)
    {
      m_expires = m_expires + m_millis;
      s_activeTimers.insert(this);
    }
    else
    {
      delete this;
    }
    
  }


  DWORD getExpires() const { return m_expires; }
  static size_t getRunningTimerCount() { return s_activeTimers.size(); }

protected:

  bool isExpired(DWORD now) const { return m_expires >= now; }
  bool isRecurring() const { return m_recurring; }
  TimerListener* getListener() const { return m_listener; }

private:
  TimerEvent m_event;
  int m_millis;
  DWORD m_expires;
  bool m_recurring;
  TimerListener* m_listener;
  string m_str;

  static set<Timer*, CompareTimer> s_activeTimers;

  bool m_markedForDeath;

  Timer(const Timer&);
};

inline bool CompareTimer::operator() (const Timer* t1, const Timer* t2) const
{
  if (t1->getExpires() < t2->getExpires())
  {
    return true;
  }
  if (t1->getExpires() == t2->getExpires())
  {
    return t1 < t2;
  }
  return false;
//  return (t1->getExpires() < t2->getExpires());
}



#endif