#ifndef Cache_h
#define Cache_h

#include <string>
#include <map>
#include <list>
using namespace std;

#include "boost/shared_ptr.hpp"

#include "IniFile.h"

typedef unsigned int CacheId;

template <typename T>
struct CacheItem
{
  CacheItem(CacheId id, string name): id(id), item(0), name(name) { }
  ~CacheItem()
  {
  }

  typedef boost::shared_ptr<CacheItem> SP;
  CacheId id;
  T* item;
  string name;
};



template<typename T, typename Loader>
class Cache
{
  typedef CacheItem<T>::SP ItemType;
  struct Unloader: public std::unary_function<ItemType&, void> {
    void operator()(ItemType& item){
      Loader::unload(item->item);
      item->item = 0;
    }
  };
public:
  explicit Cache(size_t kbytes = 0): 
    m_ini(0), 
    m_alloced(0),
    m_limit(kbytes*1024), 
    m_nextId(1) { }
  ~Cache() { reset(); }

  void setIni(IniFile& ini) { m_ini = &ini; }

  void flush() { clear(); }
  void clear() 
  { 
    for_each(m_fifo.begin(), m_fifo.end(), Cache::Unloader());
    m_fifo.clear(); 
    m_alloced = 0;
  }
  void reset() { 
    clear(); 
    m_items.clear(); 
  }

  CacheId add(string assetName)
  {
    m_nextId++;
    CacheItem<T>::SP item(new CacheItem<T>(m_nextId, assetName));
    
    m_items[m_nextId] = item;
    return m_nextId;
  }

  T* get(CacheId id)
  {
    assert(m_items.find(id) != m_items.end());
    CacheItem<T>::SP& item = m_items[id];
    if (item->item == 0)
    {
      item->item = Loader::load(*m_ini, item->name);

      m_alloced+=item->item->getSize();

      while ((!m_fifo.empty()) && (m_limit > 0) && (m_alloced > m_limit))
      {
        CacheItem<T>::SP front = m_fifo.front();
        if (front == item)
        {
          // this one os top and still the limit is used?
          // must be a big 'un
          break; // out of while
        }
        // release front of list (if not us)
        m_fifo.pop_front();
        m_alloced-=front->item->getSize();
        Loader::unload(front->item);
        front->item = 0;
      }
    }
    else
    {
      // get it out of the list
      list<CacheItem<T>::SP>::iterator i;
      m_fifo.remove(item);
    }
    m_fifo.push_back(item);
    return item->item;
  }

  void report(ostream& strm)
  {
    strm << "Alloced (" << m_alloced << " of " << m_limit << ") bytes" << endl;
    strm << "Cached  (" << m_fifo.size() << " of " << m_items.size() << ") Items" <<endl;
  }
  
  size_t getAlloced() { return m_alloced; }
  void setLimit(size_t limit) { m_limit = limit*1024; }
private:
  IniFile* m_ini;
  size_t m_limit;
  size_t m_alloced;
  CacheId m_nextId;
  map<CacheId, ItemType> m_items;
  //map<CacheId, Loader*>
  list<ItemType> m_fifo;
};

#endif
