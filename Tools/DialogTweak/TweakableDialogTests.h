#ifndef TweakableDialogTests_h
#define TweakableDialogTests_h

#include "TestSuite.h"

#include "TweakableDialogBox.h"


class TweakableDialogTest1: public hts::TestFixture
{
  typedef TweakableDialogTest1 THIS_TYPE;
public:
  virtual void registerTestCases();

  virtual void setUp();
  virtual void tearDown();

  void EnsureLoad();
  void AddItem();
  void RemoveItem();

private:
  TweakableDialogBox* m_dialog;
};

#endif