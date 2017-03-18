/* ****************************************************************************
 *
 *  MainMenuDlg.h
 *  Created by Bert Rosell, on Fri Nov 21 2003, 22:45:27 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the MainMenuDlg component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__MAINMENUDLG_H
#define ATC__MAINMENUDLG_H
 
#include "IniBasedDialog.h"
#include "Utils.h"

#include "PictureBrowser.h"
#include "List.h"

#include "PakFile.h"

/** Purpose: TODO: Describe the purpose of the class.
 *  (Everything that you write here will show up in the
 *  doc++ generated documentation.)
 */
class MainMenuDlg: public IniBasedDialog, public ItemListener, hts::Noncopyable
{
public:
  /// Constructor.
  MainMenuDlg(IniFile& ini, string name);
  virtual ~MainMenuDlg();

  virtual void actionPerformed(ActionEvent* event);
  virtual void itemStateChanged(ItemStateChangeEvent* event);

  string getSelected() { return m_selected; }

  virtual int doModal(Delegate* loop=0);

  virtual void paint(Display* display);

protected:
  void init();
  void addPackage(string name);

private:
  PictureBrowser* m_browser;
  List* m_list;
  Label* m_pageNum;
  Label* m_pageCount;
  string m_selected;
};
#endif // #ifndef ATC__MAINMENUDLG_H
 
