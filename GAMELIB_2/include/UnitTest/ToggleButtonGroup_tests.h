#include "TestSuite.h"
#include "ToggleButton.h"
#include "Container.h"


class ToggleButtonGroup_tests: public hts::TestFixture
{
  Container cont;
  ToggleButton tb1;
  ToggleButton tb2;

protected:
  START_TEST_MAP(ToggleButtonGroup_tests)
    TEST_CASE(Init);
    TEST_CASE(ToggleTB1);
    TEST_CASE(NoUntoggle);
  END_TEST_MAP

  void setUp()
  {
    tb1.setId(12);
    tb2.setId(21);
    tb1.setOther(tb2.getId());
    tb2.setOther(tb1.getId());
    cont.addUIThing(&tb1);
    cont.addUIThing(&tb2);
  }
  void tearDown()
  {
    tb1.setId(0);
    tb2.setId(0);
    cont.removeUIThing(&tb1);
    cont.removeUIThing(&tb2);

  }
    
  void Init()
  {
    CHECK(tb1.getOther() == tb2.getId());
    CHECK(tb2.getOther() == tb1.getId());
  }

  void ToggleTB1()
  {
    tb1.setChecked(true);
    CHECK(tb1.isChecked() == true);
    CHECK(tb2.isChecked() == false);

    tb2.setChecked(true);
    CHECK(tb1.isChecked() == false);
    CHECK(tb2.isChecked() == true);
  }
  
  void NoUntoggle()
  {
    tb1.setChecked(true);
    CHECK(tb1.isChecked() == true);
    CHECK(tb2.isChecked() == false);

    tb1.setChecked(false);
    CHECK(tb1.isChecked() == true);
    CHECK(tb2.isChecked() == false);
  }

};
