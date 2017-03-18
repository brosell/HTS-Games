#pragma warning (disable : 4786 4503 4530)
#include "GameScheduler.h"
#include "Log.h"

CoroutineTask* GameScheduler::s_currentTask = 0;
TaskList GameScheduler::s_taskList;
frame_t GameScheduler::s_currentFrame = 0;

HCoroutine GameScheduler::createCoroutine(CoroutineDelegate* d, string name, CoroutineListener* listener)
{
  logError(Debug, "Creating Coroutine %s", name.c_str());
  
  CoroutineTask* rep = new CoroutineTask;
  rep->delegate = d;
  rep->active = true;
  rep->name = name;
  rep->listener = listener;
  
  coroutine_t co = co_create(GameScheduler::forward, rep, 0, 4096*2);
  if (co == 0)
  {
    logError(Error, "Failed to create Coroutine %s", rep->name.c_str());
    delete rep;
    return 0;
  }
  
  doAt(NEXT_FRAME, rep); 
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

void GameScheduler::forward(void* vp)
{
  CoroutineTask* rep = (CoroutineTask*)vp;
  rep->delegate->invoke();
  // when we get here, the routine is done
  logError(Debug, "GameScheduler Coroutine %x (%s) concluded", (int)rep, rep->name.c_str());
  GameScheduler::destroyCoroutine((HCoroutine)rep);
}

void GameScheduler::destroyCoroutine(HCoroutine handle)
{
  CoroutineTask* rep = (CoroutineTask*)handle;

  logError(Debug, "Coroutine %x (%s) marked for destroy", (int)rep, rep->name.c_str());
  rep->active = false;
//  co_delete(rep->handle);
  if (rep->listener != 0)
  {
    CoroutineEvent coroutineEvent;
    coroutineEvent.id = (int)rep;
    rep->listener->coroutineFinished(&coroutineEvent);
  }
}



bool GameScheduler::doAt(frame_t frame, CoroutineTask* task)
{
  lassertWithReturn(frame>s_currentFrame, "Requested frame to run to expired already", false);

  s_taskList[frame].insert(task);

  return true;
}

bool GameScheduler::doUntil(frame_t frame, CoroutineTask* task)
{
  lassertWithReturn(frame>s_currentFrame, "Requested frame to run until expired already", false);

  for (frame_t c=s_currentFrame+1; c<=frame; c++)
  {
    doAt(c, task);
  }
  return true;
}

void GameScheduler::newFrame()
{
  list<CoroutineTask*> toBeWacked;
  s_currentFrame++;
  TaskBucket& bucket = s_taskList[s_currentFrame];
  //TaskBucket bucket(s_taskList[s_currentFrame]);
  TaskBucket::iterator i;
  for (i=bucket.begin(); i!=bucket.end(); i++)
  {
    CoroutineTask* task = *i;
    if (task->active)
    {
      CoroutineTask* prev = s_currentTask;
      s_currentTask = task;
      co_call(task->handle);
      s_currentTask = prev;
    }
    else
    {
      toBeWacked.push_back(task);
    }
  }
  s_taskList.erase(s_currentFrame);
  TaskList::iterator pair;
  list<CoroutineTask*>::iterator ic;
  for (pair=s_taskList.begin(); pair!=s_taskList.end(); pair++)
  {
    TaskBucket& bucket = pair->second;
    for (ic=toBeWacked.begin(); ic!=toBeWacked.end(); ic++)
    {
      bucket.erase(*ic);
    }
  }

  for (ic=toBeWacked.begin(); ic!=toBeWacked.end(); ic++)
  {
    delete *ic;
  }
}


void GameScheduler::resumeAt(frame_t frame)
{
  lassert2(s_currentTask != 0, "Is this a GamewTask?");
  doAt(frame, s_currentTask);
  resume();
}

void GameScheduler::resumeUntil(frame_t frame)
{
  lassert2(s_currentTask != 0, "Is this a GamewTask?");
  doUntil(frame, s_currentTask);
  resume();
}

void GameScheduler::resume()
{
  lassert2(s_currentTask != 0, "Is this a GamewTask?");
  co_resume();
}

