#pragma warning (disable : 4786 4503 4530)
#include "ThinkScheduler.h"
#include "Log.h"

ThinkDelegate* ThinkScheduler::s_currentTask = 0;
ThinkScheduler::TaskList ThinkScheduler::s_taskList;
ThinkScheduler::frame_t ThinkScheduler::s_currentFrame = 0;


void ThinkScheduler::newFrame()
{
  list<ThinkDelegate*> toBeWacked;
  s_currentFrame++;
  TaskBucket& bucket = s_taskList[s_currentFrame];
  //TaskBucket bucket(s_taskList[s_currentFrame]);
  TaskBucket::iterator i;
  for (i=bucket.begin(); i!=bucket.end(); i++)
  {
    ThinkDelegate* task = *i;
    ThinkDelegate* prev = s_currentTask;
    s_currentTask = task;
    s_currentTask->invoke();
    s_currentTask = prev;
  }
  s_taskList.erase(s_currentFrame);
}

void ThinkScheduler::remove(ThinkDelegate* task)
{
  TaskList::iterator pair;
  for (pair = s_taskList.begin(); pair!=s_taskList.end(); pair++)
  {
    TaskBucket& tb = pair->second;
    tb.erase(task);
  }
}
