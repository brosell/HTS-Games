#ifndef ObjectCache_h
#define ObjectCache_h

#include "Log.h"
#include <list>
#include <set>
using namespace std;

class HasReclaim
{
public:
  template <typename Kind>
  static void reclaim(Kind* k) { k->reclaim(); }
};

class NoReclaim
{
public:
  static void reclaim(void* k) { return; }
};


template <typename Kind, typename Reclaim = NoReclaim>
class ObjectCache
{
public:
  ObjectCache(size_t initialSize = 32, size_t hardLimit = -1): m_size(initialSize), m_hardLimit(hardLimit)
  {
    for (int c=0; c<m_size; c++)
    {
      Kind* k = new Kind;
      Reclaim::reclaim(k);
      m_available.push_back(k);
    }
  }

  Kind* acquire()
  {
    if (m_hardLimit != -1 && m_size >= m_hardLimit)
    {
      return 0;
    }

    Kind* k = 0;

    if (m_available.size() == 0)
    {
      m_size++;
      k = new Kind;
      Reclaim::reclaim(k);
    }
    else
    {
      k = m_available.front();
      lassert(m_inUse.find(k) == m_inUse.end());
      m_available.pop_front();
    }

    m_inUse.insert(k);
    return k;
  }

  void release(Kind* k)
  {
    lassert(m_inUse.find(k) != m_inUse.end());
    m_inUse.erase(k);
    Reclaim::reclaim(k);
    m_available.push_back(k);
  }

private:
  size_t m_hardLimit;
  size_t m_size;
  list<Kind*> m_available;
  set<Kind*> m_inUse;
};


#endif