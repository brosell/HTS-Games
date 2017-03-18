#ifndef nocase_compare_tests_h
#define nocase_compare_tests_h

#include "nocase_compare.h"
#include "TestSuite.h"
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

class nocase_compare_tests: public hts::TestFixture
{
  typedef nocase_compare_tests THIS_TYPE;
public:
  virtual void registerTestCases()
  {
    FIXTURE_INIT();
    TEST_CASE(Test);
  }

  void Test()
  {
    vector<string> m_set;
    m_set.push_back("B");
    m_set.push_back("a");
    m_set.push_back("c");

    std::sort(m_set.begin(), m_set.end(), hts::nocase_compare<string>());

    CHECK(m_set[0] == "a");
    CHECK(m_set[1] == "B");
    CHECK(m_set[2] == "c");

    
    
  }
};



#endif