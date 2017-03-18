#pragma warning (disable : 4786 4530 4503)
#include "Coroutine.h"
#include "Log.h"
#include "Timer.h"
#include <set>


set<CoroutineRep*, CompareCoroutine> Coroutine::s_activeCoroutines;
CoroutineRep* Coroutine::s_current = 0;

HCoroutine Coroutine::create(CoroutineDelegate* d, string name, CoroutineListener* listener)
{
  logError(Debug, "Creating Coroutine %s", name.c_str());
  
  CoroutineRep* rep = new CoroutineRep;
  rep->delegate = d;
  rep->active = true;
  rep->priority = 0;
  rep->nextRunTime = 0;
  rep->startTime = 0;
  rep->name = name;
  rep->listener = listener;
  
  coroutine_t co = co_create(Coroutine::forward, rep, 0, 4096*2);
  if (co == 0)
  {
    logError(Error, "Failed to create Coroutine %s", rep->name.c_str());
    delete rep;
    return 0;
  }
  
  s_activeCoroutines.insert(rep);
  if (rep->listener != 0)
  {
    CoroutineEvent coroutineEvent;
    coroutineEvent.id = (int)rep;
    rep->listener->coroutineStarted(&coroutineEvent);
  }
  
  logError(Debug, "Coroutine %x (%s) spawned", (int)rep, rep->name.c_str());
  rep->handle = co;
 

  return (HCoroutine)rep;
}

void Coroutine::destroy(int handle)
{
  CoroutineRep* rep = (CoroutineRep*)handle;
  if (s_activeCoroutines.find(rep) != s_activeCoroutines.end())
  {
    if (rep->active)
    {
      logError(Debug, "Coroutine %x (%s) marked for destroy", (int)rep, rep->name.c_str());
      rep->active = false;
      if (rep->listener != 0)
      {
        CoroutineEvent coroutineEvent;
        coroutineEvent.id = (int)rep;
        rep->listener->coroutineFinished(&coroutineEvent);
      }
      
    }
    else
    {
      logError(Debug, "Coroutine destroyed twice?");
    }
  }
  else
  {
    logError(Debug, "Unknown Coroutine %x (destroy)", handle);
  }

  if (rep == s_current)
  {
    // need to end this NOW!
    Coroutine::resume();
  }
}

void Coroutine::forward(void* vp)
{
  CoroutineRep* rep = (CoroutineRep*)vp;
  rep->delegate->invoke();
  // when we get here, the routine is done
  logError(Debug, "Coroutine %x (%s) concluded", (int)rep, rep->name.c_str());
  Coroutine::destroy((int)rep);
}

/**
Gives all the active coroutines a chance to run.
The schedule algorithm is non-existant.
*/
void Coroutine::schedule()
{
  if (s_activeCoroutines.size() == 0)
  {
    return;
  }

  DWORD now = timeGetTime();
  set<CoroutineRep*, CompareCoroutine>::iterator iCoroutine = s_activeCoroutines.begin();
  CoroutineRep* rep = *iCoroutine;
  while (s_activeCoroutines.size() != 0 && rep->nextRunTime <= now)
  {
    if (rep->active == true)
    {
      CoroutineRep* prev = s_current;
      s_current = rep;
      if (rep->startTime == 0)
      {
        rep->startTime = now;
      }
      else
      {
        rep->startTime = rep->nextRunTime;
      }
      logError(Debug, "calling coroutine(%s) (there are %d in the queue)", rep->name.c_str(), s_activeCoroutines.size());
      co_call(rep->handle);
      logError(Debug, "Back from coroutine");
      // rep may have been wacked before returning so we can't report on it
      s_current = prev;

      // we erase using the iterator because the nextRunTime probably changed, so we can't look it uyp that way
      s_activeCoroutines.erase(iCoroutine);
      s_activeCoroutines.insert(rep);
    }
    else
    {
      s_activeCoroutines.erase(iCoroutine);
      logError(Debug, "Coroutine %x (%s) terminated", (int)rep, rep->name.c_str());
      delete rep;
    }
    s_current = 0;
    iCoroutine = s_activeCoroutines.begin();
    rep = *iCoroutine;
  }
}

bool Coroutine::anyRunning()
{
  return (s_activeCoroutines.size() > 0);
}

void Coroutine::waitUntil(int timeout)
{
  s_current->nextRunTime = timeout;
  resume();
}

void Coroutine::waitUntilFromStart(int timeout)
{
  s_current->nextRunTime=s_current->startTime + timeout;
  resume();
}

void Coroutine::pause(int millis)
{
  int timeout = timeGetTime() + millis;
  s_current->nextRunTime = timeout;
  resume();
}

void Coroutine::waitFor(Waitable* waitable)
{
  while(!waitable->isWaitOver())
  {
    pause(25);
  }
}

void Coroutine::resume()
{
  co_resume();
}

void Coroutine::call(HCoroutine handle)
{
  CoroutineRep* rep = (CoroutineRep*)handle;

  if (rep->active == true)
  {
    CoroutineRep* prevCurrent = s_current;
    s_current = rep;
    logError(Debug, "calling coroutine(%s)", rep->name.c_str());
    co_call(rep->handle);
    logError(Debug, "returned from coroutine(%s)", rep->name.c_str());
    s_current = prevCurrent;
  }
  else
  {
    logError(Debug, "Coroutine %x (%s) terminated", (int)rep, rep->name.c_str());
    delete rep;
  }
}
