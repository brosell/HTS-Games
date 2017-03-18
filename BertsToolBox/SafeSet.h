#ifndef SafeSet_h
#define SafeSet_h

#include <set>

template <typename Kind>
class DynSetIterator: public std::set<Kind>::iterator
{
  DynSetIterator(std::set<Kind>& theSet, std::set<Kind>& toBeDeleted, std::set<Kind>& toBeAdded):
  m_theSet(theSet),
  m_toBeDeleted(toBeDeleted),
  m_toBeAdded(toBeAdded)
  { }
    
  DynSetIterator& operator++ ()
  {
    SafeSetIterator& me = *this;
    if (me == theSet.end())
    {
      return me;
    }
    me++;
    while ((me != theSet.end()) && (m_toBeDeleted.find(*me) != m_toBeDeleted.end()))
    {
      me++;
    }
    return me;
  }

private:
  std::set<Kind>& m_theSet;
  std::set<Kind>& m_toBeDeleted;
  std::set<Kind>& m_toBeAdded;
};

template <typename Kind>
class DynSet: public std::set<Kind>
{
public:
  typedef DynSetIterator<Kind> iterator;

  iterator dynBegin()
  {
    dynClean();
    return DynSetIterator(*this, toBeRemoved, toBeAdded);
  }

  void dynClean()
  {
    std::set<Kind>::iterator i;
    for (i=toBeRemoved.begin(); i!=toBeRemoved.end(); i++)
    {
      std::set<Kind>::erase(*i);
    }
    for (i=toBeAdded.begin(); i!=toBeAdded.end(); i++)
    {
      std::set<Kind>::insert(*i);
    }
  }

  void erase(const Kind& k)
  {
    toBeRemoved.insert(k);
  }
  void insert(const Kind& k)
  {
    toBeAdded.insert(k);
  }

private:
  std::set<Kind> toBeRemoved;
  std::set<Kind> toBeAdded;
};


#endif