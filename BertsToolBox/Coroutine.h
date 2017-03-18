#ifndef Coroutine_h
#define Coroutine_h

#include "pcl.h"
#include "Timer.h"
#include <string>
#include <set>
using namespace std;

typedef int HCoroutine;

class CoroutineDelegate {
public:
  virtual void invoke()=0;
  virtual ~CoroutineDelegate(){}
protected:
  CoroutineDelegate(){}
}; 

class CoroutineEvent
{
public:
  HCoroutine id;
};

class CoroutineListener
{
public:
  virtual void coroutineStarted(CoroutineEvent*) {}
  virtual void coroutineFinished(CoroutineEvent*) {}
};

class Waitable
{
public:
  virtual bool isWaitOver() = 0;
};


class CoroutineRep
{
public:
  coroutine_t handle;
  int priority;
  DWORD startTime;
  DWORD nextRunTime;
  bool active;
  CoroutineDelegate* delegate;
  string name;
  CoroutineListener* listener;

};

class CompareCoroutine
{
public:
  bool operator() (const CoroutineRep* c1, const CoroutineRep* c2) const;
};

class Coroutine
{
public:
  static HCoroutine create(CoroutineDelegate* d, string name, CoroutineListener* listener);
  static void destroy(int handle);

  static void pause(int millis);
  static void waitUntil(int timeout);

  static void waitUntilFromStart(int timeout);

  static void waitFor(Waitable* waitable);

  static void resume();

  static void call(HCoroutine handle);


  static bool anyRunning();
  static void forward(void* vp);
  static void schedule();

private:
  Coroutine();
  Coroutine(const Coroutine& other);
  ~Coroutine();

  static set<CoroutineRep*, CompareCoroutine> s_activeCoroutines;
  static CoroutineRep* s_current;
};


inline
bool CompareCoroutine::operator() (const CoroutineRep* c1, const CoroutineRep* c2) const
{
  if (c1->nextRunTime < c2->nextRunTime)
  {
    return true;
  }
  if (c1->nextRunTime == c2->nextRunTime)
  {
    return c1 < c2;
  }
  return false;
}

#endif