#include "OutputIteratorAdapters.h"
#include <vector>
#include <iostream>
#include <iterator>
using namespace std;

int testOutputIterators()
{
  int a[]={ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

  vector<int> vec;
  vector<int> vec2;

  copy(a, a+10, back_inserter(vec));
  copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));

  cout << endl;
  
  copy(a, a+10, multiOut(ostream_iterator<int>(cout, " "), back_inserter(vec2)));

  cout << endl;
  copy(vec2.begin(), vec2.end(), ostream_iterator<int>(cout, " "));
  return 0;
}