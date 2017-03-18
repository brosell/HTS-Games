#pragma warning (disable : 4786 4503 4530)
#include "BusyDialog.h"


BusyDialog::BusyDialog(IniFile& ini, string name):
IniBasedDialog(ini, name)
{

}

BusyDialog::~BusyDialog()
{

}

void BusyDialog::paint(Display* display)
{
  Rect r=getTranslatedPosition();
  lassert(getBackground().isValid());  
  if (getBackground().isValid())
  {
    getBackground()->blit(display, r.x, r.y, false);
  }
  
  specialPaint(display);

  Container::paint(display);

}