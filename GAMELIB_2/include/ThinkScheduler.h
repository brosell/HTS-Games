#ifndef ThinkScheduler_h
#define ThinkScheduler_h

#include <list>
#include <map>
#include <set>
using namespace std;

#include "Utils.h"
#include "Log.h"
#include "ThinkDelegate.h"



class ThinkScheduler: hts::Noncopyable
{
public:
  typedef set<ThinkDelegate*> TaskBucket;
  typedef unsigned long frame_t;
  typedef map<frame_t, TaskBucket> TaskList;

  static frame_t currentFrame() { return s_currentFrame; }
  static bool doAt(frame_t frame, ThinkDelegate* task);
  static bool doUntil(frame_t frame, ThinkDelegate* task);

  /**
  causes the current coroutine task to be suspended until the specisifed frame
  */
  static void resumeAt(frame_t frame);
  /**
  causes the current coroutine task to be run every frame until specified frame
  */
  static void resumeUntil(frame_t frame);

  static void remove(ThinkDelegate* task);
  
  static void newFrame();

  static void forward(void* vp);

  static frame_t thisFrame() { return s_currentFrame; }
  static frame_t nextFrame() { return s_currentFrame + 1; }
  

private:

  static ThinkDelegate* s_currentTask;
  static TaskList s_taskList;
  static frame_t s_currentFrame;
};

//////////////////
// inlines
//////////////////

inline void ThinkScheduler::resumeAt(frame_t frame)
{
  lassert2(s_currentTask != 0, "Is this a GamewTask?");
  doAt(frame, s_currentTask);
}

inline void ThinkScheduler::resumeUntil(frame_t frame)
{
  lassert2(s_currentTask != 0, "Is this a GamewTask?");
  doUntil(frame, s_currentTask);
}

inline bool ThinkScheduler::doAt(frame_t frame, ThinkDelegate* task)
{
  lassertWithReturn(frame>s_currentFrame, "Requested frame to run to expired already", false);

  s_taskList[frame].insert(task);

  return true;
}

inline bool ThinkScheduler::doUntil(frame_t frame, ThinkDelegate* task)
{
  lassertWithReturn(frame>s_currentFrame, "Requested frame to run until expired already", false);

  for (frame_t c=s_currentFrame+1; c<=frame; c++)
  {
    doAt(c, task);
  }
  return true;
}


#endif