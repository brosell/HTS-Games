/* ****************************************************************************
 *
 *  BrowserItem.h
 *  Created by Bert Rosell, on Sat Nov 22 2003, 13:00:19 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the BrowserItem component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__BROWSERITEM_H
#define ATC__BROWSERITEM_H
 
#include "Utils.h"
#include "Display.h"

/** Purpose: Represents an item in the browser. Can load or unload itself
 */
class BrowserItem: hts::Noncopyable
{
public:
  /// Constructor.
  BrowserItem(string filename);
  virtual ~BrowserItem();

  HTexture getTexture();
  
  bool loaded() { return m_texture > 0; }
  void load();
  void unload(); 

  string getName() { return m_name; }
private:
  void attemptDiskLoad();
  string m_filename;
  string m_name; // just the name with no path or extension
  HTexture m_texture;

  static HTexture s_placeHolder;
};


//////////////////////////////////////
/// INLINES
//////////////////////////////////////
inline HTexture BrowserItem::getTexture()
{
  if (m_texture > 0)
  {
    return m_texture;
  }
  return s_placeHolder;
}

inline void BrowserItem::unload()
{
  if (m_texture > 0)
  {
    Display::getInstance()->release(m_texture);
    m_texture = 0;
  }
}

#endif // #ifndef ATC__BROWSERITEM_H
 
