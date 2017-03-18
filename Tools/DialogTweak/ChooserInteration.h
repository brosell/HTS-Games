#ifndef ChooserInteration_h
#define ChooserInteration_h

#include "TestSuite.h"

#include "ListChooser.h"

class ChooserInteration: public hts::TestFixture
{
  typedef ChooserInteration THIS_TYPE;
public:
  ChooserInteration();
  ~ChooserInteration();

  virtual void setUp();
  virtual void tearDown();

  virtual void registerTestCases();

  void MouseOverHighlights();
  void MouseClickChooses();
  void HumanTest();

private:
  ListChooser* m_chooser;
};

#endif
