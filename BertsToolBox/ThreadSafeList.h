#ifndef ThreadSafeList_h
#define ThreadSafeList_h

#include "Mutex.h"
#include <deque>
#include <algorithm>

using namespace std;

template <typename Kind>
class ThreadSafeList
{
public:
  ThreadSafeList(): m_mutex() {}
  void push_back(Kind item)
  {
    lock();
    m_theList.push_back(item);
    unlock();
  }
  void push_front(Kind item)
  {
    lock();
    m_theList.push_front(item);
    unlock();
  }
  Kind back()
  {
    Kind ret;
    lock();
    ret = m_theList.back();
    unlock();
    return ret;
  }
  Kind front()
  {
    Kind ret;
    lock();
    ret = m_theList.front();
    unlock();
    return ret;
  }
  void pop_back()
  {
    lock();
    m_theList.pop_back();
    unlock();
  }
  void pop_front()
  {
    lock();
    m_theList.pop_front();
    unlock();
  }
  int size()
  {
    int size;
    lock();
    size = m_theList.size();
    unlock();
    return size;
  }
  void clear()
  {
    lock();
    m_theList.clear();
    unlock();
  }

  void lock()
  {
    m_mutex.lock();
  }
  void unlock()
  {
    m_mutex.unlock();
  }

  template <typename ContKind>
  void copyTo(ContKind& cont)
  {
    lock();
    deque<Kind>::iterator i;
    for (i=m_theList.begin(); i!=m_theList.end(); i++)
    {
      cont.push_back(*i);
    }
    unlock();
  }

protected:
private:
  deque<Kind> m_theList;

  Mutex m_mutex;
};

#endif