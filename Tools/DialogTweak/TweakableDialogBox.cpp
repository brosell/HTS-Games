#pragma warning (disable : 4786 4530 4503)

#include "TweakableDialogBox.h"
#include <algorithm>

#include "boost/Format.hpp"


TweakableDialogBox::TweakableDialogBox(IniFile& ini, std::string section):
IniBasedDialog(ini, section),
m_selected(0),
m_haveSelection(false),
m_section(section),
m_ini(ini)
{

}

TweakableDialogBox::~TweakableDialogBox()
{

}

//void TweakableDialogBox::actionPerformed(ActionEvent* event)
//{
//
//}

const UIThing* TweakableDialogBox::getSelectedItem()
{
  return m_selected;
}

void TweakableDialogBox::onMousePress(MousePressEvent* event)
{
  if (event->button == LEFT_BUTTON)
  {
    m_selected = findByPoint(Point(event->x, event->y));
    if (m_selected != 0) 
    {
      m_haveSelection = true;
    }
    else
    {
      m_haveSelection = false;
    }
  }
}

void TweakableDialogBox::onMouseMove(MouseMoveEvent* event)
{
  if (!m_haveSelection)
  {
    return;
  }
  assert(m_selected != 0);
  Rect r = m_selected->getPosition();
  r.x+=event->relx;
  r.y+=event->rely;

  m_selected->setPosition(r);
}

void TweakableDialogBox::onMouseRelease(MouseReleaseEvent* event)
{
  if (event->button == LEFT_BUTTON)
  {
    m_haveSelection = false;
    if (m_selected)
    {
      UIThing* thing = findByPoint(Point(event->x, event->y));
      if (thing != m_selected)
      {
        m_selected = 0;
      }
    }
  }
}

void TweakableDialogBox::paint(Display* surface)
{
  Drawer drawer;
  IniBasedDialog::paint(surface);

  drawer.surface = surface;
  std::for_each(m_things.begin(), m_things.end(), drawer);
  
  if (m_selected != 0)
  {
    Rect r = m_selected->getTranslatedPosition();
    surface->fillRect(r.x, r.y, r.w, r.h, 0, 255, 0, 127);
    string sr = (boost::format("(%d, %d, %d, %d)") % r.x % r.y % r.w % r.h).str();
    getFont()->drawLine(surface, sr, 320, 240);
  }
}
