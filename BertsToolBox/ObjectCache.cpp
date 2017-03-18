#include "ObjectCache.h"


void testObjectCache()
{
  ObjectCache<int> ints;
  int c=0;
  int* test[100];
  for (c=0; c<15; c++)
  {
    test[c] = ints.acquire();
  }

  for (c=0; c<5; c++)
  {
    ints.release(test[c]);
  }

  for (c=20; c<30; c++)
  {
    test[c] = ints.acquire();
  }

}