#pragma warning (disable : 4786)
#include "Timer.h"
#include "Log.h"

set<Timer*, CompareTimer> Timer::s_activeTimers;

HTimer Timer::create(string str, int id, int millis, TimerListener* listener, void* param, bool recurring)
{
  if (listener == 0)
  {
    logError(Error, "Timer - NULL TimerListener (%s)", str.c_str());
    return 0;
  }
  if (millis <= 0)
  {
    logError(Error, "Timer - Millis invalid (%d)", millis);
    //return 0;
  }

  Timer* timer = new Timer;
  lassert(timer != 0);
  timer->m_event.id = id;
  timer->m_event.param = param;
  timer->m_event.timer = (HTimer)timer;
  timer->m_millis = millis;
  timer->m_expires = timeGetTime() + millis;
  timer->m_listener = listener;
  timer->m_recurring = recurring;
  timer->m_str = str;

  s_activeTimers.insert(timer);

  return (HTimer)timer;
}

HTimer Timer::create(int id, int millis, TimerListener* listener, void* param, bool recurring)
{
  return Timer::create("Anon", id, millis, listener, param, recurring);
}

int Timer::tick()
{
  int ret = 0;

  if (s_activeTimers.size() == 0)
  {
    return ret;
  }

  DWORD now = timeGetTime();
  set<Timer*, CompareTimer>::iterator iTimer = s_activeTimers.begin();
  Timer* timer = *iTimer;
  while (s_activeTimers.size() != 0 && timer->m_expires <= now)
  {
    s_activeTimers.erase(iTimer);
    timer->expire();
    iTimer = s_activeTimers.begin();
    timer = *iTimer;
    ret++;
  }
  return ret;
}

void Timer::report()
{
  logError(Inform, "");
  logError(Inform, "Timer report");
  logError(Inform, "--------------------");
  logError(Inform, "There are %d active timers", getRunningTimerCount());
  set<Timer*, CompareTimer>::iterator i;
  for (i=s_activeTimers.begin(); i!=s_activeTimers.end(); i++)
  {
    Timer* timer = (*i);
    logError(Inform, "Timer (%10s) expires: %d %s", timer->m_str.c_str(), timer->getExpires(), (char*)(timer->m_recurring?"Recurring":""));
  }
  logError(Inform, "--------------------");

}

void Timer::cleanup()
{
  set<Timer*, CompareTimer>::iterator i;
  for (i=s_activeTimers.begin(); i!= s_activeTimers.end(); i++)
  {
    Timer* timer = (*i);
    Timer::destroy((HTimer)timer);
    delete timer;
  }

  s_activeTimers.clear();
}
//
//bool stopTest(Message* e);
//bool timeFunc(Message* e);
//
//bool ___timerTesting = false;
//NonTypeDelegate timeDel(timeFunc);
//NonTypeDelegate testDone(stopTest);
//
//bool stopTest(Message* e)
//{
//  ___timerTesting = false;
//  return  true;
//}
//
//bool timeFunc(Message* e)
//{
//  static unsigned int count = 0;
//  count++;
//  if (count % 10000 == 0)
//  {
//    cerr << ".";
//  }
//  Timer::create(1, rand()%1000, &timeDel, false);
//  return true;
//}

class TimerTester: public TimerListener
{
public:
  TimerTester(): m_killTimer(0), m_running(true) { }

  void setKillTimer(HTimer timer) { m_killTimer = timer; }
  virtual void timeout(TimerEvent* event)
  {
    if(event->timer == m_killTimer)
    {
      m_running = false;
    }
    else
    {
      static unsigned int count = 0;
      count++;
      if (count % 10000 == 0)
      {
        cerr << ".";
      }
      Timer::create(1, rand()%1000, this, false);
    }
  }

  bool isRunning() { return m_running; }

private:
  HTimer m_killTimer;
  bool m_running;
};

void testTimer(int count)
{
  srand(1234); // need consistancy
  char buf[255];
  int c;

  TimerTester tester;

  // let test run for 30 seconds
  HTimer killTimer = Timer::create(10000, 30000, &tester, false);
  tester.setKillTimer(killTimer);


  StopWatch phase1;
  for (c=0; c<count; c++)
  {
    phase1.start();
    Timer::create(c, rand()%1000, &tester, false);
    phase1.stop();
  }
  

  sprintf(buf, "Phase1: ElapsedTime: %d (average: %f)", phase1.getElapsedTime(), phase1.getAverage());
  logError(buf, Inform);

  sprintf(buf, "Number of Active Timers: %d", Timer::getRunningTimerCount());
  logError(buf, Inform);


  int totalFires=0;
  StopWatch phase2;
  
  
  while (tester.isRunning())
  {
    phase2.start();
    totalFires += Timer::tick();
    phase2.stop();
  }
  

  cerr << endl;

  sprintf(buf, "Phase2: ElapsedTime: %d (average of %d times: %f)\nTotalFires = %d", phase2.getElapsedTime(), phase2.getRunCount(), phase2.getAverage(), totalFires);
  logError(buf, Inform);

  sprintf(buf, "Number of Active Timers: %d", Timer::getRunningTimerCount());
  logError(buf, Inform);


}

