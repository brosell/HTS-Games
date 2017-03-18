#ifndef Mutex_h
#define Mutex_h

#include <windows.h>

class Mutex {
private:
  CRITICAL_SECTION m_lock;

public:
  Mutex(void) {
    InitializeCriticalSection(&m_lock);
  }

  void lock(void) {
    EnterCriticalSection(&m_lock);
  }

  void unlock(void) {
    LeaveCriticalSection(&m_lock);
  }
};

class Thread_Sync
{
public:
  Thread_Sync(Mutex& theMutex): m_mutex(theMutex)
  {
    m_mutex.lock();
  }

  ~Thread_Sync()
  {
    m_mutex.unlock();
  }
private:
  Mutex& m_mutex;
};

#define synchronized(x) Thread_Sync mut(x)


#endif
