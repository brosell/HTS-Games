/* ****************************************************************************
 *
 *  PictureBrowser.h
 *  Created by Bert Rosell, on Fri Nov 21 2003, 20:31:24 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the PictureBrowser component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__PICTUREBROWSER_H
#define ATC__PICTUREBROWSER_H

#include "Utils.h"
#include "UI.h"

#include "BrowserItem.h"
#include "ThinkScheduler.h"

#include "IniFile.h"

#include <vector>
using namespace std;

#define XDIST 120
#define YDIST 80

/** Purpose: Impliments a control that "lists" a bunch of
  * images
 */
class PictureBrowser: public UIThing, hts::Noncopyable
{
public:
  /// Constructor.
  PictureBrowser();
  PictureBrowser(StringMap& properties);
  virtual ~PictureBrowser();

  virtual void paint(Display* surface);
  //virtual void setDirty(bool d = true) {UIThing::setDirty(true); }
  virtual void onMouseClick(MouseClickEvent* event);

  void addPicture(string filename);

  string getSelected() { return (m_selectedOffset>-1)?m_filenames[m_selectedOffset]:""; }
  void clear();

  void addActionListener(ActionListener* listener);
  void removeActionListener(ActionListener* listener);

  int rowsPerPage();
  int colsPerPage();
  int numPerPage() { return rowsPerPage()*colsPerPage(); }
  int numPages();
  int page() { return m_currentPage; }
  void incPage();
  void decPage();

  void unloadItems();
  void pause(bool b) { m_paused = b; }
private:
  bool m_paused;
  
  size_t m_margin;

  //vector<HTexture> m_images;
  vector<BrowserItem*> m_items;
  vector<string> m_filenames;
  int m_selectedOffset;
  int m_currentPage;

  set<ActionListener*> m_listeners;
  ActionEvent m_event;
  void fireEvent();

  int startOffsetOfPage(int p);
  int endOffsetOfPage(int p);

  TypeThinkDelegate<PictureBrowser> m_thinker;
  void loadThinker();
};

inline void PictureBrowser::addActionListener(ActionListener* listener)
{
  m_listeners.insert(listener);
}

inline void PictureBrowser::removeActionListener(ActionListener* listener)
{
  m_listeners.erase(listener);
}

#endif // #ifndef ATC__PICTUREBROWSER_H
 
