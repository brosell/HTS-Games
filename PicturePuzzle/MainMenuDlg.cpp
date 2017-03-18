/* ****************************************************************************
 *
 *  MainMenuDlg.cpp
 *  Created by Bert Rosell, on Fri Nov 21 2003, 22:45:27 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the MainMenuDlg component.
 *  Please see MainMenuDlg.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "MainMenuDlg.h"
#include "StringTokenizer.h"
#include "FileManager.h"
#include "NDirIt.hpp"

#include "Convert.h"

#include "boost/Format.hpp"

/* ********************************* 
 * MainMenuDlg
 ***********************************/
MainMenuDlg::MainMenuDlg(IniFile& ini, string name):
IniBasedDialog(ini, name)
{
  m_browser = dynamic_cast<PictureBrowser*>(getControlByName("cus_MainMenu_Browser"));
  m_browser->addActionListener(this);

  m_list = dynamic_cast<List*>(getControlByName("lst_MainMenu_PakList"));
  m_list->addItemListener(this);
  m_list->allowNoSelection(false);

  m_pageCount = dynamic_cast<Label*>(getControlByName("lbl_MainMenu_PageCount"));
  m_pageNum = dynamic_cast<Label*>(getControlByName("lbl_MainMenu_PageNum"));

  Button* button = 0;
  button = dynamic_cast<Button*>(getControlByName("btn_MainMenu_Quit"));
  button->setId(-1);
  button->addActionListener(this);

  button = dynamic_cast<Button*>(getControlByName("btn_MainMenu_PrevPage"));
  button->addActionListener(this);

  button = dynamic_cast<Button*>(getControlByName("btn_MainMenu_NextPage"));
  button->addActionListener(this);

  button = dynamic_cast<Button*>(getControlByName("btn_MainMenu_Credits"));
  button->addActionListener(this);

  button = dynamic_cast<Button*>(getControlByName("btn_MainMenu_Options"));
  button->addActionListener(this);

  init();
  m_list->setSelected(0);
}

MainMenuDlg::~MainMenuDlg()
{
 
}

void MainMenuDlg::actionPerformed(ActionEvent* event)
{
  switch(event->commandId)
  {
  case -1:
    {
      terminateModal(-1);
    }
    break;
  case 10000:
  case 10001:
    {
      terminateModal(event->commandId);
    }
    break;
  case 100:
    {
      debug << "Prev Page" << endl;
      m_browser->decPage();
    }
    break;
  case 101:
    {
      debug << "Next Page" << endl;
      m_browser->incPage();
    }
    break;
  default:
    {
      m_selected = m_browser->getSelected();
      terminateModal(1);
    }
    break;
  }
}

void MainMenuDlg::itemStateChanged(ItemStateChangeEvent* event)
{
  m_browser->clear();
  string item=m_list->getSelectedString();
  IniFile manifest((item+"\\manifest.ini"));
  manifest.read();
  lassert(manifest["Package"]["Name"] == item);
  string filelist=manifest["Package"]["Files"];
  StringTokenizer st(filelist, " ,\r\n\t");
  while(st.hasMoreTokens())
  {
    m_browser->addPicture(st.nextToken());
  }
}

int MainMenuDlg::doModal(Delegate* loop)
{
  m_browser->pause(false);
  int ret=IniBasedDialog::doModal(loop);
  m_browser->pause(true);
  m_browser->unloadItems();
  return ret;
}

void MainMenuDlg::paint(Display* display)
{
  //m_pages->setText( (boost::format("Page %d of %d") % (m_browser->page()+1) % (m_browser->numPages())).str());
  m_pageCount->setText(toString(m_browser->numPages()));
  m_pageNum->setText(toString(m_browser->page()+1));
  if (m_browser->page() < (m_browser->numPages()-1))
  {
    getControlByName("btn_MainMenu_NextPage")->setVisible(true);
  }
  else
  {
    getControlByName("btn_MainMenu_NextPage")->setVisible(false);
  }


  if (m_browser->page() > 0) 
  {
    getControlByName("btn_MainMenu_PrevPage")->setVisible(true);
  }
  else
  {
    getControlByName("btn_MainMenu_PrevPage")->setVisible(false);
  }

  IniBasedDialog::paint(display);
}

void MainMenuDlg::addPackage(string name)
{
  m_list->addItem(-1, name);
}

void MainMenuDlg::init()
{
#ifdef _DEMO
  CDirEnumeration picpaks(".", "Demo.picpak");
#else
  CDirEnumeration picpaks(".", "*.picpak");
#endif
  while(picpaks.hasMoreElements())
  {
    string pakname = picpaks.nextElement();
    FileManager::addPakFile(pakname);
    string packageName = "";
    string::iterator c;
    for (c=pakname.begin(); c!=pakname.end() && (*c)!='.'; c++)
    {
      packageName+=*c;
    }
    addPackage(packageName);
  }
}
