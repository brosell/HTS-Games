/* ****************************************************************************
 *
 *  ChooseModeDlg.h
 *  Created by Bert Rosell, on Sat Nov 22 2003, 09:06:54 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the ChooseModeDlg component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__CHOOSEMODEDLG_H
#define ATC__CHOOSEMODEDLG_H
 
#include "IniBasedDialog.h"
#include "Utils.h"
#include "RadioButton.h"
#include "ToggleButton.h"

#include "Picture.h"

/** Purpose: 
 */
class ChooseModeDlg: public IniBasedDialog, public RadioButtonGroupListener, hts::Noncopyable
{
public:
  /// Constructor.
  ChooseModeDlg(IniFile& ini, string name, Picture& picture);
  virtual ~ChooseModeDlg();

  virtual void actionPerformed(ActionEvent* event);
  virtual void radioEvent(RadioButtonEvent* event);

  int mode() { return m_modeGroup->getCheckedId(); }
  int difficulty() { return m_difGroup->getCheckedId(); }
  bool showGhost() { return m_showGhost->isChecked(); }
  bool rotate() { return m_rotate->isChecked(); }
  bool showHint() { return m_showHint->isChecked(); }

private:
  void updateUI(int id);
  Picture& m_picture;

  RadioButton* m_easy;
  RadioButton* m_medium;
  RadioButton* m_hard;

  ToggleButton* m_showGhost;
  ToggleButton* m_rotate;
  ToggleButton* m_showHint;

  RadioButtonGroup* m_modeGroup;
  RadioButtonGroup* m_difGroup;

  Label* m_title;
};
#endif // #ifndef ATC__CHOOSEMODEDLG_H
 
