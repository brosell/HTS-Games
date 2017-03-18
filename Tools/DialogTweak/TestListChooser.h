#include "TestSuite.h"

#include "ListChooser.h"

class TestListChooser1: public hts::TestFixture
{
  typedef TestListChooser1 THIS_TYPE;
public:
  virtual void registerTestCases();

  virtual void setUp();
  virtual void tearDown();

  void CreateFromScratch();
  void CreateFromIterators();

private:
  ListChooser* m_chooser;
};


class TestListChooser2_Position: public hts::TestFixture
{
  typedef TestListChooser2_Position THIS_TYPE;
public:
  virtual void registerTestCases();

  virtual void setUp();
  virtual void tearDown();

  void TestHeight();
  void TestWidth();
  void TestInitialPosition();
  void TestInitialPositionWithMargin();
  void TestInitialPositionTooFarRight();
  void TestInitialPositionTooLow();
  void TestInitialPositionBoth();
  void TestInitialPositionList();
    

private:
  ListChooser* m_chooser;
};
