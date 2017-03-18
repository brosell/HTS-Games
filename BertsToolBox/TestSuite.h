#ifndef TestSuite_h
#define TestSuite_h

#pragma warning (disable : 4530 4786 4503)

#include "boost/shared_ptr.hpp"
#include "boost/format.hpp"
#include "Timer.h"
#include "Utils.h"

#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include "STLFunctorDelegate.h"

/** adds a test case to the list */
#define TEST_CASE_EX(classname, fn) addTestCase(*this, &classname::fn, #fn)

/** adds a timed test to the list */
#define TIME_CASE_EX(classname, fn, ct) addTimedTestCase(*this, &classname::fn, #fn, ct)

/** same as TEST_CASE_EX except assumes THIS_TYPE is a typedef of the current class */
#define TEST_CASE(fn) TEST_CASE_EX(THIS_TYPE, fn)
/** same as TIME_CASE_EX except assumes THIS_TYPE is a typedef of the current class */
#define TIME_CASE(fn, ct) TIME_CASE_EX(THIS_TYPE, fn, ct)
#define BENCHMARK(fn, ct) TIME_CASE(fn, ct)

/** macro that causes the RTTI name of the subclass to be discovered. Place 
      this at the top of your registerTestCases method
      */
#define FIXTURE_INIT() TestFixture::setName(typeid(*this).name())

#define START_TEST_MAP(cls) \
  private: \
  typedef cls THIS_TYPE; \
  protected: \
void registerTestCases() { \
  TestFixture::setName(#cls);

#define END_TEST_MAP }


/** The super macro that causes test results to be created. */
#define CHECK(cond) do_test(cond, #cond, __FILE__, __LINE__)

#define EXPECT_EXCEPTION(exp, excep) \
try{ (exp); /* should not get here */ CHECK(0 && "EXPECT_EXCEPTION"); } catch(excep & ) { /*success */ CHECK(1 && "EXPECT_EXCEPTION");}


namespace hts
{
  class TestSuite;
  class TestFixture;
  class TestCase;

  /* convienient typedefs */
  typedef boost::shared_ptr<TestFixture> SP_TestFixture;
  typedef boost::shared_ptr<TestSuite> SP_TestSuite;
  typedef boost::shared_ptr<TestCase> SP_TestCase;

  /**
  A test result. Whenever the CHECK macro is used, a TestResult 
  is created amd stored.
  */
  struct TestResult
  {
    /** the result (true == success, false == failure) */
    bool result;
    /** a string rep of the condition that was tested */
    string cond;
    /** the filename of the source file */
    string file;
    /** the line number of CHECK */
    size_t line;
    /** The name of the test. If TEST_CASE(_EX) is used, 
    it is the name of the function.*/
    string test;

    /** writes the result to a MaintLog */
    void log(std::ostream& strm) const;

    /** helper class to count successes. used by STL algorithms */
    struct CountPass;

    /** helper class to count failures. used by STL algorithms */
    struct CountFail;
  };

  /** A testcase. A test fixture will have many of these. A test case should test
      just one thing. TestCases are created on your behalf by the TestFixture 
      during testCase registration. Most (if not all) will be of the derived
      class TestCaseT. The use has no need to call any of the methods.
  */
  class TestCase
  {
  public:
    TestCase(std::string name, size_t timesToRun):m_name(name), m_timesToRun(timesToRun) {  }
    virtual void test() = 0;
    virtual ~TestCase() {}
    
    /** runs a timed test */
    void runTest();

    size_t getRunTimes() { return m_timesToRun; }
    
    size_t averageRunTime();
    size_t countRunTimes() { return m_runTimes.size(); }
    
    std::string getName() { return m_name; }

  private:
    size_t m_timesToRun;
    std::string m_name;
    int m_nRuns;
    std::vector<size_t> m_runTimes;
  };
  
  /** a templated subclass of TestCase. This allows any method of 
  any class instance to be used as a test case
  */
  template <typename TestType>
  class TestCaseT: public TestCase
  {
  public:
    TestCaseT(TestType &t, void (TestType::*pfn)(), std::string name, size_t timesToRun):
    TestCase(name, timesToRun),
    m_t(t),
    m_pfn(pfn)
    {
      assert(dynamic_cast<TestFixture*>(&t) != 0);
    }
        
    virtual void test() { (m_t.*m_pfn)(); }
        
  private:
    TestType& m_t;
    void (TestType::*m_pfn)();
  };


  /** 
  holds one or more test function (delegate) and setup/teardown.
  Users will create subclasses of TestFixture to organize their 
  tests.
  */
  class TestFixture
  {
    typedef STLVoidFunctorUnaryDelegate<TestFixture, SP_TestCase> D_TestFixtureMem;
  public:
    TestFixture()
    {
      m_name = "TestFixture";
    }

    void setName(string name) { m_name = name; }
    string getName() { return m_name; }

    virtual ~TestFixture() { };

    /** this virtual method will be called before each of this
    TestFixture tests are run. For every test, this will be call 
    once before running.
    */
    virtual void setUp() { }

    /** this virtual method will be called before each of this
    TestFixture tests are run. For every test, this will be call 
    once before running.
    */
    virtual void tearDown() { }

    virtual void report(std::ostream& strm);
    
    /** clears the results */
    virtual void reset();

    /** runs all of the tests. First the regualar tests are run, followed by the
    timed tests
    */
    virtual void run(std::ostream& strm);

    /** returns the number of successfull tests */
    virtual size_t countPass();
    /** returns the number of failed tests */
    virtual size_t countFail();
    /** returns the number of tests run */
    virtual size_t countTests() { return m_tests.size(); }

    virtual size_t countResults() { return m_results.size(); }

    /** Pure virtual method that subclasses override to register
    test cases.<p>
    Most will look something like this<br>
    <pre>
    void SomeTestFixture::registerTestCases()
    {
      FIXTURE_INIT(); // tell the base class what we are using RTTI.

      TEST_CASE(Test1); // assumes THIS_TYPE is a typedef for this class type and
                        // Test1 is a method of THIS_TYPE with the signature:
                        // void THIS_TYPE::Test1().
      TEST_CASE(Test2);
      TEST_CASE(Test3);
    }
    */
    virtual void registerTestCases() = 0;

  protected:
    bool do_test(bool cond, const string& lbl, const char* fname, long lineno);

    template<typename T>
    void addTestCase(T& t, void (T::*pfn)(), string name)
    {
      m_tests.push_back(SP_TestCase(new TestCaseT<T>(t, pfn, name, 1)));
    }

    template<typename T>
    void addTimedTestCase(T& t, void (T::*pfn)(), string name, size_t timesToRun)
    {
      m_timedTests.push_back(SP_TestCase(new TestCaseT<T>(t, pfn, name, timesToRun)));
    }

  private:
    void runTest(SP_TestCase testCase);

    vector<SP_TestCase> m_tests;
    vector<SP_TestCase> m_timedTests;
    vector<TestResult> m_results;


    
    SP_TestCase m_currentTest;
    void setCurrentTest(SP_TestCase test) { m_currentTest = test; }
    
    string m_name;

    struct TestCaseRunner;

    friend struct TestCaseRunner;
  };



  /**
    This class hold many TestFixtures and is the interface to the outside world.
  */
  class TestSuite: public TestFixture
  {
    /** convienient typedef hts::STLVoidFunctorUnaryDelegate adapts a member function
          to STL algorithms */
    typedef hts::STLVoidFunctorUnaryDelegate<TestSuite, SP_TestFixture> D_TestSuiteMem;
  public:
    /** Constructs an empty TestSuite*/
    TestSuite(std::string name): m_name(name) {}

    /** a do nothing override of TestFixture::registerTestCases */
    virtual void registerTestCases() { }
    
    /** adds a TestFixture to the queue */
    void addFixture(TestFixture* fixture);

    size_t countFixtures() { return m_tests.size(); }

    /** runs the tests */
    virtual void run(std::ostream& strm);
    
    /** writes a report to the MaintLog passed to the constructor */
    void report(std::ostream& strm);

//    /** After the tests are run, this returns the number of passed tests */
//    size_t countPass() { return m_nPass; }
//    /** After the tests are run, this returns the number of failed tests */
//    size_t countFail() { return m_nFail; }

    /** returns the number of successfull tests */
    virtual size_t countPass();
    /** returns the number of failed tests */
    virtual size_t countFail();
    /** returns the number of tests run */
    virtual size_t countTests();

    virtual size_t countResults();


  private:
    void report(SP_TestFixture testFixture);
    void runTestFixture(SP_TestFixture testFixture);
    void setTestFixtureLog(SP_TestFixture testFixture);

    std::vector<SP_TestFixture> m_tests;
    string m_name;

    int m_nPass;
    int m_nFail;

    struct TestFixtureRunner;
    struct TestFixtureReporter;

    struct FailCounter;
    struct PassCounter;
    struct TestCounter;
    struct ResultCounter;
  };

  /**************************** 
   *TestResult inlines 
   ****************************
   */

  inline void TestResult::log(std::ostream& strm) const
  {
    assert(log!=0);
    strm << boost::format("*** Test(%s): %s \"%s\" %s (%d)") % (char*)(result?"Passed":"Failed") %
      test % cond % file % line << endl;
  }

  struct TestResult::CountPass: public std::binary_function<size_t, TestResult&, size_t>{
  public:
    size_t operator()(size_t iv, TestResult& test) { if (test.result) return (iv+1); return iv;}
  };
  
  /** helper class to count failures. used by STL algorithms */
  struct TestResult::CountFail: public std::binary_function<size_t, TestResult&, size_t>{
  public:
    size_t operator()(size_t iv, TestResult& test) { if (!test.result) return (iv+1); return iv;}
  };
  
  /**************************** 
  *TestSuite inlines 
  ****************************
  */

  struct TestSuite::TestFixtureRunner
  {
    TestFixtureRunner(std::ostream& strm): m_strm(strm), m_nFail (0), m_nPass(0) { }
    void operator()(SP_TestFixture fixture)
    {
      fixture->run(m_strm);
      m_nPass += fixture->countPass();
      m_nFail += fixture->countFail();
    }

    size_t countPass() { return m_nPass; }
    size_t countFail() { return m_nFail; }
  private:
    std::ostream& m_strm;
    int m_nPass;
    int m_nFail;
  };

  struct TestSuite::TestFixtureReporter
  {
    TestFixtureReporter(std::ostream& strm): m_strm(strm) { }
    void operator()(SP_TestFixture fixture)
    {
      fixture->report(m_strm);
    }
  private:
    std::ostream& m_strm;
  };


  inline void TestSuite::addFixture(TestFixture* fixture)
  {
    fixture->registerTestCases();
    m_tests.push_back(SP_TestFixture(fixture));
  }


  inline void TestSuite::run(std::ostream& strm)
  {
    //TestSuite::TestFixtureRunner runner(strm);
    TestFixtureRunner ret = for_each(m_tests.begin(), m_tests.end(), TestFixtureRunner(strm));
    m_nPass = ret.countPass();
    m_nFail = ret.countFail();
  }

  inline void TestSuite::report(std::ostream& strm)
  {
    strm << endl;
    strm << "---------------------------------------------------------" << endl;
    strm << boost::format("Suite (%s) results:") % m_name << endl;
    for_each(m_tests.begin(), m_tests.end(), TestFixtureReporter(strm));
    strm << "---------------------------------------------------------" << endl;
    strm << boost::format("Suite (%s) Total: %03d (Pass: %03d, Fail %03d)") % m_name % (m_nPass+m_nFail) % m_nPass % m_nFail << endl;
    strm << "---------------------------------------------------------" << endl;
    strm << endl;
  }

  struct TestSuite::FailCounter: public std::binary_function<size_t, SP_TestFixture, size_t> {
    size_t operator()(size_t iv, SP_TestFixture fixture) {
      return (iv+fixture->countFail());
    }
  };
  inline size_t TestSuite::countFail()
  {
    return accumulate(m_tests.begin(), m_tests.end(), 0, TestSuite::FailCounter());
  }

  struct TestSuite::PassCounter: public std::binary_function<size_t, SP_TestFixture, size_t> {
    size_t operator()(size_t iv, SP_TestFixture fixture) {
      return (iv+fixture->countPass());
    }
  };
  inline size_t TestSuite::countPass()
  {
    return accumulate(m_tests.begin(), m_tests.end(), 0, TestSuite::PassCounter());
  }

  struct TestSuite::TestCounter: public std::binary_function<size_t, SP_TestFixture, size_t> {
    size_t operator()(size_t iv, SP_TestFixture fixture) {
      return (iv+fixture->countTests());
    }
  };
  inline size_t TestSuite::countTests()
  {
    return accumulate(m_tests.begin(), m_tests.end(), 0, TestSuite::TestCounter());
  }

  struct TestSuite::ResultCounter: public std::binary_function<size_t, SP_TestFixture, size_t> {
    size_t operator()(size_t iv, SP_TestFixture fixture) {
      return (iv+fixture->countResults());
    }
  };
  inline size_t TestSuite::countResults()
  {
    return accumulate(m_tests.begin(), m_tests.end(), 0, TestSuite::TestCounter());
  }

  

  /**************************** 
   *TestFixture inlines 
   ****************************
   */

  struct TestFixture::TestCaseRunner: public std::unary_function<SP_TestCase, void>
  {
  public:
    TestCaseRunner(std::ostream& strm, TestFixture* fixture): m_strm(strm), m_fixture(fixture) { }
    void operator()(SP_TestCase testCase)
    {
      m_fixture->setCurrentTest(testCase);
      for (int c=0; c<testCase->getRunTimes(); c++)
      {
        m_strm << boost::format("Starting %s:%s (iteration %d of %d)") % m_fixture->getName() % testCase->getName() % (c+1) % testCase->getRunTimes() << endl;
        m_fixture->setUp();
        testCase->runTest();
        m_fixture->tearDown();
      }
    }
  private:
    std::ostream& m_strm;
    TestFixture* m_fixture;
  };

  inline void TestFixture::run(std::ostream& strm)
  {
    for_each(m_tests.begin(), m_tests.end(), TestCaseRunner(strm, this));
    for_each(m_timedTests.begin(), m_timedTests.end(), TestCaseRunner(strm, this));
  }
  
  inline bool TestFixture::do_test(bool cond, const std::string& lbl, const char* fname, long lineno)
  {
    assert(m_currentTest);
    TestResult tf;
    tf.cond = lbl;
    tf.file = fname;
    tf.line = lineno;
    tf.result = cond;
    tf.test = m_currentTest->getName();

    m_results.push_back(tf);
//    if (!cond)
//    {
//      tf.log(std::cout);
//    }
    
    return cond;
  }

  inline void TestFixture::reset()
  {
    m_results.clear();
  }

  
  inline size_t TestFixture::countPass()
  {

    return std::accumulate(m_results.begin(), m_results.end(), 0, TestResult::CountPass());
  }

  inline size_t TestFixture::countFail()
  {
    return std::accumulate(m_results.begin(), m_results.end(), 0, TestResult::CountFail());
  }

//  inline void TestFixture::runTest(SP_TestCase testCase)
//  {
//    assert(m_log != 0);
//    m_currentTest = testCase;
//    for (int c=0; c<testCase->getRunTimes(); c++)
//    {
////      if (m_log != 0) 
////        m_log->logError(Inform, "Starting %s: %s (iteration %d of %d)", m_name.c_str(), testCase->getName().c_str(), c+1, testCase->getRunTimes());
//      m_strm << boost::format("Starting %s: %s (iteration %d of %d)") %m_name() % testCase->getName() % (c+1) % testCase->getRunTimes() << endl;
//      setUp();
//      testCase->runTest();
//      tearDown();
//    }
//  }

  inline void TestFixture::report(std::ostream& strm)
  {
    strm << "TestFixture: " << m_name << endl;
    strm << "---------------------------------------------" << endl;

    vector<TestResult>::const_iterator i;
    if (!m_results.empty())
    {
      for (i=m_results.begin(); i!=m_results.end(); i++)
      {
        const TestResult& test = (*i);
        if (!test.result)
        {
          test.log(strm);
        }
      }
    }
    int fail = countFail();
    int pass = countPass();

    strm << boost::format("Total: %03d (Pass: %03d, Fail %03d)") % (pass+fail) % pass % fail << endl;

    if (!m_timedTests.empty())
    {
      vector<SP_TestCase>::iterator itc;
      for (itc=m_timedTests.begin(); itc!=m_timedTests.end(); itc++)
      {
        SP_TestCase test=(*itc);
        strm << boost::format("--- Time(%03d millis): %s") % test->averageRunTime() % test->getName() << endl;
      }
    }
    strm << endl << endl;
  }
 
  /**************************** 
   *TestCase inlines 
   ****************************
   */
  
  inline
  void TestCase::runTest()
  {
    StopWatch sw;

    sw.start();
    test();
    sw.stop();
    
    m_runTimes.push_back(sw.getElapsedTime());
  }

  inline
  size_t TestCase::averageRunTime()
  {
    std::sort(m_runTimes.begin(), m_runTimes.end());
    vector<size_t>::iterator begin = m_runTimes.begin();
    int toCompare = m_runTimes.size();
    /* if we have more than 2 runs, get rid of the fastest and slowest */
    if(m_runTimes.size() > 2)
    {
      begin++;
      toCompare-=2;
    }

    size_t average = for_each(begin, begin+toCompare, hts::average<size_t>());
    return average;
  }

  
  
}


#endif