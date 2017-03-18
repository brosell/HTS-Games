#ifndef TweakableDialogTest2_h
#define TweakableDialogTest2_h

#include "TestSuite.h"

#include "TweakableDialogBox.h"


class TweakableDialogTest2: public hts::TestFixture
{
  typedef TweakableDialogTest2 THIS_TYPE;
public:
  virtual void registerTestCases();

  virtual void setUp();
  virtual void tearDown();

  void SelectItem();
  void SelectItem2();
  void SelectNothing();

  void MoveItem();


private:
  TweakableDialogBox* m_dialog;

  void click(int x, int y)
  {
    press(x, y);
    release(x, y);

    MouseClickEvent event;
    event.button = LEFT_BUTTON;
    event.x = x;
    event.y = y;
    theGame.uiSystem.onMouseClick(&event);
  }

  void press(int x, int y)
  {
    MousePressEvent event;
    event.button = LEFT_BUTTON;
    event.x = x;
    event.y = y;
    theGame.uiSystem.onMousePress(&event);
  }
  
  void release(int x, int y)
  {
    MouseReleaseEvent event;
    event.button = LEFT_BUTTON;
    event.x = x;
    event.y = y;
    theGame.uiSystem.onMouseRelease(&event);
  }

  void move(int x, int y, int rx, int ry)
  {
    MouseMoveEvent event;
    event.x = x;
    event.y = y;
    event.relx = rx;
    event.rely = ry;
    theGame.uiSystem.onMouseMove(&event);
  }
};

#endif