#include "ThreadSafeList.h"
#include <list>
#include <iostream>

void testThreadSafeList()
{
  ThreadSafeList<char> testList;
  list<char> rec;

  testList.push_back('a');
  testList.push_back('b');
  testList.push_back('c');

  testList.copyTo(rec);

  list<char>::iterator i;
  for (i=rec.begin(); i!=rec.end(); i++)
  {
    cout << (*i);
  }
  cout << endl;
}
