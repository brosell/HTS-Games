#ifndef CoroutineDelegate_h
#define CoroutineDelegate_h

#include "Coroutine.h"


class CoroutineNonTypeDelegate : public CoroutineDelegate  
{
public:
  CoroutineNonTypeDelegate(void (*pfn)()):
  m_pfn(pfn)
  {
  }
  
  virtual void invoke()
  {
    m_pfn();
  }
  
  virtual ~CoroutineNonTypeDelegate(){}
private:
  void (*m_pfn)();
};


template <typename T>
class CoroutineTypeDelegate : public CoroutineDelegate  
{
public:
  CoroutineTypeDelegate(T &t, void (T::*pfn)()):
  m_t(t),
  m_pfn(pfn)
  {
    
  }

  virtual void invoke()
  {
    (m_t.*m_pfn)();
  }

  virtual ~CoroutineTypeDelegate(){}
  
private:
  T& m_t;
  void (T::*m_pfn)();
};

template <typename T>
class SpawnableCoroutineTypeDelegate: public CoroutineDelegate, public CoroutineListener
{
public:
  SpawnableCoroutineTypeDelegate(T &t, void (T::*pfn)(), string name, CoroutineListener* listener = 0):
  m_t(t),
  m_pfn(pfn),
  m_name(name),
  m_shuttingDown(false),
  m_listener(listener)
  {
    
  }

  int spawn()
  {
    int handle = Coroutine::create(this, m_name, this);
    if (handle != 0)
    {
      m_spawnedHandles.insert(handle);
    }
    return handle;
  }

  void destroy()
  {
    logError(Debug, "SpawnableCoroutineTypeDelegate(%s) begin destroyed", m_name.c_str());
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
    logError(Debug, "SpawnableCoroutineTypeDelegate(%s) finished", m_name.c_str());
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
    if (m_name == "GameOver")
    {
      int l=0;
    }
  }

  virtual ~SpawnableCoroutineTypeDelegate()
  {
    logError(Debug, "SpawnableCoroutineTypeDelegate(%s) destructor", m_name.c_str());
    if (m_name == "GameOver")
    {
      int l=0;
    }

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

class SpawnableCoroutineNonTypeDelegate: public CoroutineDelegate, public CoroutineListener
{
public:
  SpawnableCoroutineNonTypeDelegate(void (*pfn)(), string name):
  m_pfn(pfn),
  m_name(name),
  m_shuttingDown(false)
  {
    
  }

  void spawn()
  {
    int handle = Coroutine::create(this, m_name, this);
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

  virtual ~SpawnableCoroutineNonTypeDelegate()
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
