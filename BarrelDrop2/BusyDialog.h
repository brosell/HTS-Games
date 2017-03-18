#ifndef BusyDialog_h
#define BusyDialog_h


#include "UI.h"

class BusyDialog: public IniBasedDialog
{
public:
  BusyDialog(IniFile& ini, string name);
  virtual ~BusyDialog();

  virtual void paint(Display* display);

  /**
  called after background skin is drawn but before
  controls are drawn
  */
  virtual void specialPaint(Display* display) { }
};


#endif