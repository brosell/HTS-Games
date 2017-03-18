#if 0

#include "STLFunctorDelegate.h"
#include "Utils.h"
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

class STLFunctorDelegateTester
{
public:
  typedef STLFunctorDelegateTester ThisType;
  
  void test1()
  {
    vector<int> vi;
    vector<int> dest;

    for(int c=0; c<1000; c++) vi.push_back(c);
    
    copy_if(vi.begin(), vi.end(), back_inserter(dest), 
      STLFunctorUnaryDelegate<ThisType, int, bool>(*this, &ThisType::isOdd));

    int s1 = vi.size();
    int s2 = dest.size();

    s1=s1;
  }

  void test2()
  {
    typedef STLFunctorBinaryDelegate<ThisType, int, int, bool> DelType;
    vector<int> vi;

    int c;

    for(c=0; c<1000; c++) vi.push_back(c);

    std::random_shuffle(vi.begin(), vi.end());
    
    std::sort(vi.begin(), vi.end(), DelType(*this, &ThisType::lessThan));
    
    int s1 = vi.size();

    c=0;
    while (c < (vi.size()-1))
    {
      assert(vi[c] < vi[c+1]);
      c++;
    }
  }

private:
  bool isOdd(int c) { return ((c%2) == 1); }

  bool lessThan(int i1, int i2) { return (i1 < i2); }
};
  

void STLFunctorDelegateTest()
{
  STLFunctorDelegateTester sfdt;
  sfdt.test1();
  sfdt.test2();
}
#endif