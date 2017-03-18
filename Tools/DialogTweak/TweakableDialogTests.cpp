#pragma warning (disable : 4786 4530 4503)

#include "TweakableDialogTests.h"
#include "TweakableDialogTest2.h"
#include "TestListChooser.h"
#include "ChooserInteration.h"

void testTweakableDialog()
{
  MaintLog& log = MaintLog::get("_TweakableDialogTests.log");
  log.setFilter(All);
  hts::TestSuite suite("TweakableDialogTests");
  suite.addFixture(new TweakableDialogTest1);
  suite.addFixture(new TweakableDialogTest2);
  suite.addFixture(new TestListChooser1);
  suite.addFixture(new TestListChooser2_Position);
  suite.addFixture(new ChooserInteration);
  suite.run(log.stream(Inform));
  suite.report(log.stream(Inform));
}

void TweakableDialogTest1::registerTestCases()
{
  FIXTURE_INIT();
  TEST_CASE(EnsureLoad);
  TEST_CASE(AddItem);
  TEST_CASE(RemoveItem);
};

void TweakableDialogTest1::setUp()
{
  IniFile ini("TweakTests.ini");
  ini.read();

  m_dialog = new TweakableDialogBox(ini, "TweakableDialogTest1");
}

void TweakableDialogTest1::tearDown()
{
  delete m_dialog;
  m_dialog = 0;
}

void TweakableDialogTest1::EnsureLoad()
{
  CHECK(m_dialog->getPosition() == Rect(0, 0, 640, 480));
  Button* b = dynamic_cast<Button*>(m_dialog->getControlByName("Button1"));
  CHECK(b != 0);
  if (b == 0) return;
  CHECK(b->getText() == "Hi");
  CHECK(m_dialog->countControls() == 1);
}

void TweakableDialogTest1::AddItem()
{
  Button* button = new Button;
  button->setText("Goodbye");
  button->setControlName("Button2");
  button->setPosition(Rect(50, 50, 10, 10));
  m_dialog->addUIThing(button);

  Button* b = dynamic_cast<Button*>(m_dialog->getControlByName("Button2"));
  CHECK(b != 0);
  CHECK(button == b);
  if (b == 0) return;
  CHECK(b->getText() == "Goodbye");
  CHECK(m_dialog->countControls() == 2);

  delete button;
}

void TweakableDialogTest1::RemoveItem()
{
  Button* b = dynamic_cast<Button*>(m_dialog->getControlByName("Button1"));
  CHECK(b!=0);
  m_dialog->removeUIThing(b);
  b = dynamic_cast<Button*>(m_dialog->getControlByName("Button1"));
  CHECK(b == 0);
}

