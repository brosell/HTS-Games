#include "LibraryTest.h"

#include "TestSuite.h"
#include "Log.h"

#include "TextBox_tests.h"
#include "ToggleButtonGroup_tests.h"


hts::TestSuite* getGameLibTests()
{
  hts::TestSuite* suite = new hts::TestSuite("GameLibTests");
  suite->addFixture(new TextBox_tests);
  suite->addFixture(new ToggleButtonGroup_tests);

  return suite;
}
