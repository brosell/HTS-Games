#ifndef string_tokenizer_tests_h
#define string_tokenizer_tests_h

#include "TestSuite.h"
#include <string>

using namespace std;
using namespace hts;

class string_tokenizer_tests: public hts::TestFixture
{
  typedef string_tokenizer_tests THIS_TYPE;
public:
  virtual void registerTestCases()
  {
    FIXTURE_INIT();
    TEST_CASE(Creation);
//    TEST_CASE(TestOneToken);
  }

  /** test creating a string_tokenizer */
  void Creation()
  {
    string_tokenizer st("Test");
    CHECK(true);
  }

//  void TestOneToken()
//  {
//    string str="THIS";
//    string_tokenizer st(str, " ");
//
//    CHECK(st.size() == 1);
//    CHECK(st.empty() == false);
//
//    string_tokenizer::iterator begin, end;
//    begin = st.begin();
//    end = st.end();
//    
//    CHECK( (*begin) == "THIS");
//    begin++;
//    CHECK( begin == end );
//  }
};




};

#endif