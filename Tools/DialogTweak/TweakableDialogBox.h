#ifndef TweakableDialogBox_h
#define TweakableDialogBox_h

#include "BR_Game.h"

class TweakableDialogBox: public IniBasedDialog
{
  typedef std::map<std::string, std::string> Properties;
public:
  TweakableDialogBox(IniFile& ini, std::string section);
  ~TweakableDialogBox();


//  virtual void actionPerformed(ActionEvent* event);
  virtual void onMousePress(MousePressEvent* event);
  virtual void onMouseMove(MouseMoveEvent* event);
  virtual void onMouseRelease(MouseReleaseEvent* event);

  virtual void paint(Display* surface);

  const UIThing* getSelectedItem();

private:
  UIThing* m_selected;
  bool m_haveSelection;

  IniFile& m_ini;
  string m_section;

  class Drawer;

//  std::map<UITHing*, Properties> m_thingsProperties;
//
//  std::map<string, Properties> m_typeProperties;
//  void loadTypeProperties();

};


class TweakableDialogBox::Drawer
{
public:
  Display* surface;
  void operator()(UIThing* thing)
  {
    Rect r = thing->getTranslatedPosition();
    surface->drawHLine(r.x, r.w, r.y, 255, 0, 0, 255);
    surface->drawHLine(r.x, r.w, r.y+r.h, 255, 0, 0, 255);
    surface->drawVLine(r.x, r.y, r.h, 255, 0, 0, 255);
    surface->drawVLine(r.x+r.w, r.y, r.h, 255, 0, 0, 255);
    surface->fillRect(r.x, r.y, r.w, r.h, 255, 0, 0, 127);
  }
};

#endif