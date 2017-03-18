#ifndef OptionsDialog_h
#define OptionsDialog_h

#include "UI.h"

class OptionsDialog: public IniBasedDialog, public AdjustmentListener
{
public:
  OptionsDialog(IniFile& ini, string name);

  virtual void onOK();
  virtual void onCancel();

  virtual void adjustmentValueChanged(AdjustmentEvent* event);

  virtual void actionPerformed(ActionEvent* event);

  virtual int doModal(Delegate* loop = 0);

  virtual void paint(Display* display);

  virtual void setButton();

private:
  int m_originalFXVolume;
  int m_originalMusicVolume;

  bool m_originallyWindowed;

  string m_iniFilename;

  HSlider* m_fx;
  HSlider* m_music;

  Button* m_fs;
  Button* m_win;
};


#endif