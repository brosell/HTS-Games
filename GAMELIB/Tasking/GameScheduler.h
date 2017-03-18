#ifndef GameScheduler_h
#define GameScheduler_h

#include <list>
#include <map>
using namespace std;

#include "Utils.h"
#include "Coroutine.h"

class CoroutineTask
{
public:
  coroutine_t handle;
  bool active;
  CoroutineDelegate* delegate;
  string name;
  CoroutineListener* listener;
private:
};

typedef set<CoroutineTask*> TaskBucket;
typedef unsigned long frame_t;
typedef map<frame_t, TaskBucket> TaskList;

class GameScheduler: hts::Noncopyable
{
public:
  static frame_t currentFrame() { return s_currentFrame; }
  static bool doAt(frame_t frame, CoroutineTask* task);
  static bool doUntil(frame_t frame, CoroutineTask* task);

  static HCoroutine createCoroutine(CoroutineDelegate* d, string name, CoroutineListener* listener);
  static void destroyCoroutine(HCoroutine handle);

  /**
  causes the current coroutine task to be suspended until the specisifed frame
  */
  static void resumeAt(frame_t frame);
  /**
  causes the current coroutine task to be run every frame until specified frame
  */
  static void resumeUntil(frame_t frame);

  /**
  causes the task to switch back to the caller
  */
  static void resume();
  
  static void newFrame();

  static void forward(void* vp);

  

private:

  static CoroutineTask* s_currentTask;
  static TaskList s_taskList;
  static frame_t s_currentFrame;

};

#define THIS_FRAME (GameScheduler::currentFrame())
#define NEXT_FRAME (THIS_FRAME + 1)

template <typename T>
class GameCoroutineTypeDelegate: public CoroutineDelegate, public CoroutineListener, hts::Noncopyable
{
public:
  GameCoroutineTypeDelegate(T &t, void (T::*pfn)(), string name, CoroutineListener* listener = 0):
  m_t(t),
  m_pfn(pfn),
  m_name(name),
  m_shuttingDown(false),
  m_listener(listener)
  {
    
  }

  int spawn()
  {
    int handle = GameScheduler::createCoroutine(this, m_name, this);
    if (handle != 0)
    {
      m_spawnedHandles.insert(handle);
    }
    return handle;
  }

  void destroy()
  {
    m_shuttingDown = true;
    set<int>::iterator i;
    for (i=m_spawnedHandles.begin(); i!=m_spawnedHandles.end(); i++)
    {
      GameScheduler::destroyCoroutine(*i);
    }
    m_spawnedHandles.clear();
  }

  virtual void coroutineFinished(CoroutineEvent* ev)
  {
    if (!m_shuttingDown)
    {
      m_spawnedHandles.erase(ev->id);
    }
    if (m_listener != 0)
    {
      m_listener->coroutineFinished(ev);
    }

  }

  virtual void invoke()
  {
    (m_t.*m_pfn)();
  }

  virtual ~GameCoroutineTypeDelegate()
  {
    destroy();
  }
  
private:
  bool m_shuttingDown;
  string m_name;
  set<int> m_spawnedHandles;
  T& m_t;
  void (T::*m_pfn)();
  CoroutineListener* m_listener;
};

class GameCoroutineNonTypeDelegate: public CoroutineDelegate, public CoroutineListener, hts::Noncopyable
{
public:
  GameCoroutineNonTypeDelegate(void (*pfn)(), string name):
  m_pfn(pfn),
  m_name(name),
  m_shuttingDown(false)
  {
    
  }

  void spawn()
  {
    int handle = GameScheduler::createCoroutine(this, m_name, this);
    if (handle != 0)
    {
      m_spawnedHandles.insert(handle);
    }
  }

  void destroy()
  {
    m_shuttingDown = true;
    set<int>::iterator i;
    for (i=m_spawnedHandles.begin(); i!=m_spawnedHandles.end(); i++)
    {
      Coroutine::destroy(*i);
    }
    m_spawnedHandles.clear();
  }

  virtual void coroutineFinished(CoroutineEvent* ev)
  {
    if (!m_shuttingDown)
    {
      m_spawnedHandles.erase(ev->id);
    }
  }

  virtual void invoke()
  {
    (*m_pfn)();
  }

  virtual ~GameCoroutineNonTypeDelegate()
  {
    destroy();
  }
  
private:
  bool m_shuttingDown;
  string m_name;
  set<int> m_spawnedHandles;
  void (*m_pfn)();
};


#endif