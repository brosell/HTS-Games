#include "UnitTest/LibraryTest.h"

#include "TestSuite.h"
#include "Log.h"

#include "UnitTest/TextBox_tests.h"
#include "UnitTest/ToggleButtonGroup_tests.h"
#include "UnitTest/AManager_tests.h"

#include "UnitTest/Cache_test.h"
#include "UnitTest/Cache_Skin_tests.h"

#include "UnitTest/AM_tests.h"


hts::TestSuite* getGameLibTests()
{
  hts::TestSuite* suite = new hts::TestSuite("GameLibTests");
  suite->addFixture(new TextBox_tests);
  suite->addFixture(new ToggleButtonGroup_tests);
//  suite->addFixture(new AManager_tests);

  suite->addFixture(new CacheTester1);
  suite->addFixture(new Cache_Skin_tests);

  suite->addFixture(new AM_tests1);


  return suite;
}
