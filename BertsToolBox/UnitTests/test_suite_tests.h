#ifndef TestSuiteTests_h
#define TestSuiteTests_h

#include "TestSuite.h"
#include "null_ostreambuf.h"
#include <iostream>

class TestSuiteTests: public hts::TestFixture
{
public:
  typedef TestSuiteTests THIS_TYPE;
  TestSuiteTests()
  {
    
  }

  void test1()
  {
    CHECK(true);
  }

  void test2()
  {
    CHECK(true);
  }

  void timedTest1()
  {
    Sleep(rand()%1000);
  }

private:
  virtual void registerTestCases() 
  { 
    FIXTURE_INIT();
    TEST_CASE(test1);
    TEST_CASE(test2);
    TIME_CASE(timedTest1, 10);
  }
};

class NestedTestSuiteTests: public hts::TestFixture
{
  typedef NestedTestSuiteTests THIS_TYPE;

  hts::TestSuite* m_suite;

  hts::null_ostreambuf<char> nulloutbuf;
  std::ostream nullout;
public:
  NestedTestSuiteTests(): nullout(&nulloutbuf) { }
  virtual void setUp()
  {
    m_suite = new hts::TestSuite("NestedTestSuiteTests");
  }
  virtual void tearFown()
  {
    delete (m_suite);
  }

  virtual void registerTestCases()
  {
    FIXTURE_INIT();

    TEST_CASE(NestingAllowed);
    TEST_CASE(CountingTests);
    TEST_CASE(CountingResults);
  }

  void NestingAllowed()
  {
    hts::TestSuite* nested = new hts::TestSuite("Nested1");
    m_suite->addFixture(nested);
    CHECK(m_suite->countFixtures() == 1);
  }

  void CountingTests()
  {
    hts::TestSuite* nested = new hts::TestSuite("Nested1");
    nested->addFixture(new TestSuiteTests);
    m_suite->addFixture(nested);
    CHECK(m_suite->countTests() == 2);

  }

  void CountingResults()
  {
    hts::TestSuite* nested = new hts::TestSuite("Nested1");
    nested->addFixture(new TestSuiteTests);
    m_suite->addFixture(nested);

    m_suite->run(nullout);
    CHECK(m_suite->countPass() == 2);
    CHECK(m_suite->countFail() == 0);

  }
};

#endif