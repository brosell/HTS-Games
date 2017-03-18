#ifndef Label_h
#define Label_h

#include "UI/UIThing.h"
#include "Font.h"

#include "Log.h"

enum HJUST_TYPE
{
  JUST_LEFT,
  JUST_CENTER,
  JUST_RIGHT
};

enum VJUST_TYPE
{
  JUST_TOP,
  JUST_MIDDLE,
  JUST_BOTTOM
};

class Label: public UIThing
{
public:
  Label(): 
  UIThing(), 
  m_horizJust(JUST_LEFT), 
  m_vertJust(JUST_TOP), 
  m_drawBorder(false)
  { }

  virtual void paint(Display* surface);
  
  void setHorizJust(HJUST_TYPE just) { m_horizJust = just; }
  HJUST_TYPE getHorizJust() { return m_horizJust; }

  void setVertJust(VJUST_TYPE just) { m_vertJust = just; }
  VJUST_TYPE getVertJust() { return m_vertJust; }
  
  void setDrawBorder(bool b) { m_drawBorder = b; }
  bool getDrawBorder() { return m_drawBorder; }

  virtual bool acceptsFocus() { return false; }

private:
  HJUST_TYPE m_horizJust;
  VJUST_TYPE m_vertJust;
  bool m_drawBorder;
};

#endif