#include "TestListChooser.h"

void TestListChooser1::registerTestCases()
{
  FIXTURE_INIT();
  TEST_CASE(CreateFromScratch);
  TEST_CASE(CreateFromIterators);
}

void TestListChooser1::setUp()
{

}

void TestListChooser1::tearDown()
{

}

void TestListChooser1::CreateFromScratch()
{
  ListChooser lc;
  CHECK(lc.countItems() == 0);
  lc.addItem(1, "one");
  CHECK(lc.countItems() == 1);
  lc.addItem(2, "two");
  CHECK(lc.countItems() == 2);
  lc.addItem(3, "three");
  CHECK(lc.countItems() == 3);

  lc.removeItem(1);
  CHECK(lc.countItems() == 2);
  lc.removeItem(2);
  CHECK(lc.countItems() == 1);
  lc.removeItem(3);
  CHECK(lc.countItems() == 0);
}

void TestListChooser1::CreateFromIterators()
{
  vector<string> items;
  items.push_back("one");
  items.push_back("two");
  items.push_back("three");

  ListChooser lc(items.begin(), items.end());
  CHECK(lc.countItems() == 3);
}

///////////////////////////////////////////////////

void TestListChooser2_Position::registerTestCases()
{
  FIXTURE_INIT();
  TEST_CASE(TestHeight);
  TEST_CASE(TestWidth);
  TEST_CASE(TestInitialPosition);
  TEST_CASE(TestInitialPositionWithMargin);
  TEST_CASE(TestInitialPositionTooLow);
  TEST_CASE(TestInitialPositionTooFarRight);
  TEST_CASE(TestInitialPositionBoth);
  TEST_CASE(TestInitialPositionList);

}

void TestListChooser2_Position::setUp()
{
  m_chooser = new ListChooser;
  m_chooser->addItem(1, "one");
  m_chooser->addItem(2, "two");
  m_chooser->addItem(3, "three");
}

void TestListChooser2_Position::tearDown()
{
  delete m_chooser;
  m_chooser = 0;
}

void TestListChooser2_Position::TestHeight()
{
  CHECK(m_chooser->getItemsHeight() == 3*Font::getDefault()->getFontHeight());
}

void TestListChooser2_Position::TestWidth()
{
  CHECK(m_chooser->getItemsWidth() == Font::getDefault()->getTextWidth("three"));

  m_chooser->addItem(123, "This is a test");

  CHECK(m_chooser->getItemsWidth() == Font::getDefault()->getTextWidth("This is a test"));
}

void TestListChooser2_Position::TestInitialPosition()
{
  int w = m_chooser->getItemsWidth();
  int h = m_chooser->getItemsHeight();

  m_chooser->popUp(100, 100, true);
  Rect r = m_chooser->getPosition();
  CHECK(r == Rect(100, 100, w, h));
}


void TestListChooser2_Position::TestInitialPositionWithMargin()
{
  m_chooser->setMargin(5);
  int w = m_chooser->getItemsWidth() + 10;
  int h = m_chooser->getItemsHeight() + 10;

  m_chooser->popUp(100, 100, true);
  Rect r = m_chooser->getPosition();
  CHECK(r == Rect(100, 100, w, h));

}

void TestListChooser2_Position::TestInitialPositionTooLow()
{
  m_chooser->setMargin(5);
  int w = m_chooser->getItemsWidth() + 10;
  int h = m_chooser->getItemsHeight() + 10;

  int x = 100;
  int y = theGame.screen->getHeight() - h;

  m_chooser->popUp(100, 470, true);
  Rect r = m_chooser->getPosition();
  CHECK(r == Rect(x, y, w, h));

}

void TestListChooser2_Position::TestInitialPositionTooFarRight()
{
  m_chooser->setMargin(5);
  int w = m_chooser->getItemsWidth() + 10;
  int h = m_chooser->getItemsHeight() + 10;

  int x = theGame.screen->getWidth() - w;
  int y = 100;

  m_chooser->popUp(630, 100, true);
  Rect r = m_chooser->getPosition();
  CHECK(r == Rect(x, y, w, h));

}

void TestListChooser2_Position::TestInitialPositionBoth()
{
  m_chooser->setMargin(5);
  int w = m_chooser->getItemsWidth() + 10;
  int h = m_chooser->getItemsHeight() + 10;

  int x = theGame.screen->getWidth() - w;
  int y = theGame.screen->getHeight() - h;

  m_chooser->popUp(630, 470, true);
  Rect r = m_chooser->getPosition();
  CHECK(r == Rect(x, y, w, h));

}

void TestListChooser2_Position::TestInitialPositionList()
{
  size_t margin = m_chooser->getMargin();
  m_chooser->popUp(100, 100, true);
  List* list = dynamic_cast<List*>(m_chooser->getControlByName("TheList"));
  CHECK(list != 0);
  if (list == 0) return;

  Rect lr = list->getTranslatedPosition();
  Rect cr = m_chooser->getPosition();

  CHECK(lr == Rect(cr.x+margin, cr.y+margin, cr.w-(2*margin), cr.h-(2*margin)));
}