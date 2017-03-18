#ifndef _ThingCollection_h
#define _ThingCollection_h

#include "Thing.h"
#include "Misc/GameMath.h"

#include <vector>
#include <algorithm>
using namespace std;



class ThingCollection
{
public:
  typedef vector<Thing*> VT;
  typedef VT::iterator VTI;
  typedef VT::reverse_iterator VTRI;
  ThingCollection();
  ~ThingCollection();

  bool add(Thing* thing);
  void remove(Thing* thing);
  void clear();
  
  template<typename OutputIterator>
    void getByRect(Rect* r, OutputIterator dest, int minZ = 0, int maxZ = 15)
  {
    copy_if(m_things.begin(), m_things.end(), dest, ThingOverlapsRect2(r, minZ, maxZ));
  }

  bool canThingFit(Rect* r, int minZ = 0, int maxZ = 15)
  {
    return (find_if(m_things.begin(), m_things.end(), ThingOverlapsRect(r)) == m_things.end());
  }

  Thing* getByPoint(Point& p, int minZ = 0, int maxZ = 15)
  {
    VTRI lbz = find_if(m_things.rbegin(), m_things.rend(), PointHitsThing(p));
    if (lbz != m_things.rend())
    {
      return *lbz;
    }
    return 0;
  }

  void sort();
  int count();

  bool empty() { return m_things.empty(); }

protected:

private:
  VT m_things;
};

#ifndef min
#define min(x,y) (x<y?x:y)
#endif

#endif