#include "SafeSet.h"


void tSafeSet()
{
  DynSet<char> theSet;

  theSet.insert(1);
  theSet.insert(2);
  theSet.insert(3);
  theSet.insert(4);
  theSet.insert(5);
  theSet.insert(6);
  theSet.insert(7);

  DynSet<char>::iterator i;

  for (i=theSet.dynBegin(); i!=theSet.end(); i++)
  {

  }
}

