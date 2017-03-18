#include "TweakableDialogTest2.h"

void TweakableDialogTest2::registerTestCases()
{
  FIXTURE_INIT();
  TEST_CASE(SelectItem);
  TEST_CASE(SelectItem2);
  TEST_CASE(SelectNothing);
  TEST_CASE(MoveItem);
};

void TweakableDialogTest2::setUp()
{
  IniFile ini("TweakTests.ini");
  ini.read();

  m_dialog = new TweakableDialogBox(ini, "TweakableDialogTest2");
  m_dialog->show();
}

void TweakableDialogTest2::tearDown()
{
  m_dialog->hide();
  delete m_dialog;
  m_dialog = 0;
}


/* select one and ensure it is selected */
void TweakableDialogTest2::SelectItem()
{
  click(15, 15);
  
  const UIThing* thing = m_dialog->getSelectedItem();

  CHECK(thing != 0);
  Button* b = const_cast<Button*>(dynamic_cast<const Button*>(thing));
  CHECK(b != 0);

  if (b==0) return;
  CHECK(b->getText() == "Hi");
}

/* select one and ensure it is selected, then select another */
void TweakableDialogTest2::SelectItem2()
{
  click(15, 15);
  
  const UIThing* thing = m_dialog->getSelectedItem();

  CHECK(thing != 0);
  Button* b = const_cast<Button*>(dynamic_cast<const Button*>(thing));
  CHECK(b != 0);

  if (b==0) return;

  CHECK(b->getText() == "Hi");
  
  click(55, 55);
  
  thing = m_dialog->getSelectedItem();

  CHECK(thing != 0);
  b = const_cast<Button*>(dynamic_cast<const Button*>(thing));
  CHECK(b != 0);

  if (b==0) return;

  CHECK(b->getText() == "Goodbye");
}


void TweakableDialogTest2::SelectNothing()
{
  click(15, 15);
  
  const UIThing* thing = m_dialog->getSelectedItem();

  CHECK(thing != 0);
  Button* b = const_cast<Button*>(dynamic_cast<const Button*>(thing));
  CHECK(b != 0);

  if (b==0) return;

  CHECK(b->getText() == "Hi");

  click(95, 300);

  thing = m_dialog->getSelectedItem();
  CHECK(thing == 0);
}

void TweakableDialogTest2::MoveItem()
{
  press(15, 15);
  
  UIThing* thing = const_cast<UIThing*>(m_dialog->getSelectedItem());
  CHECK(thing != 0);
  if (thing == 0) return;

  Rect origPos = thing->getPosition();
  CHECK(origPos == Rect(10, 10, 10, 10));
  
  move(35, 35, +20, +20);
  
  thing = const_cast<UIThing*>(m_dialog->getSelectedItem());
  CHECK(thing != 0);
  if (thing == 0) return;

  release(35, 35);

  thing = const_cast<UIThing*>(m_dialog->getSelectedItem());
  CHECK(thing != 0);
  if (thing == 0) return;

  Rect newPos = thing->getPosition();

  CHECK(newPos == Rect(origPos.x+20, origPos.y+20, origPos.w, origPos.h));

  move(45, 45, +10, +10);
  
  thing = const_cast<UIThing*>(m_dialog->getSelectedItem());
  CHECK(thing != 0);
  if (thing == 0) return;

  CHECK(newPos == thing->getPosition());
}