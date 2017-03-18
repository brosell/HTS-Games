#include "ChooserInteration.h"

ChooserInteration::ChooserInteration()
{

}

ChooserInteration::~ChooserInteration()
{

}

void ChooserInteration::registerTestCases()
{
  FIXTURE_INIT();
  TEST_CASE(MouseOverHighlights);
  TEST_CASE(MouseClickChooses);
  TEST_CASE(HumanTest);
}

void ChooserInteration::setUp()
{
  m_chooser = new ListChooser;
  m_chooser->addItem(1, "one");
  m_chooser->addItem(2, "two");
  m_chooser->addItem(3, "three");
}

void ChooserInteration::tearDown()
{
  delete m_chooser;
  m_chooser = 0;
}

/** when the mouse hovers over the list, the item below the cursor needs to be selected */
void ChooserInteration::MouseOverHighlights()
{
  m_chooser->setMargin(0); // easier if we ignore margins
  m_chooser->popUp(100, 100, true);

  move(110, 110, 10, 10);
  string s = m_chooser->getChoice();
  CHECK(s == "one");

  size_t fh = m_chooser->getFont()->getFontHeight();
  move(110, 110 + fh, 0, fh);
  s = m_chooser->getChoice();
  CHECK(s == "two");
}

void ChooserInteration::MouseClickChooses()
{
  m_chooser->setMargin(0); // easier if we ignore margins
  m_chooser->popUp(100, 100, true);

  click(110, 110);
  string s = m_chooser->getChoice();
  CHECK(s == "one");

  size_t fh = m_chooser->getFont()->getFontHeight();
  click(110, 110 + fh);
  s = m_chooser->getChoice();
  CHECK(s == "two");
}

void ChooserInteration::HumanTest()
{
  m_chooser->setMargin(5); // easier if we ignore margins
  int ans = m_chooser->popUp(100, 100);

  string s = m_chooser->getChoice();
  CHECK(s == "one");
  CHECK(ans == 1);
}