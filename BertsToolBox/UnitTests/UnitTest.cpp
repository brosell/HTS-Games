#include "TestSuite.h"
#include "ToolBoxTests.h"

#include "test_suite_tests.h"


hts::TestSuite* hts::getToolBoxTests()
{
  TestSuite* suite = new TestSuite("ToolBox");
//  suite->addFixture(new TestSuiteTests);
//  suite->addFixture(new NestedTestSuiteTests);

  return suite;
}

