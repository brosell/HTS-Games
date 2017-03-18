#ifndef DropDownList_h
#define DropDownList_h

#include "UI/List.h"

class DropDownList: public List
{
public:
  DropDownList();
  virtual void paint(Display* surface);

  virtual void onKeyPress(KeyPressEvent* event);
  virtual void onMouseClick(MouseClickEvent* event);

protected:
private:
};

#endif