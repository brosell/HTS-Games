/* ****************************************************************************
 *
 *  BrowserItem.cpp
 *  Created by Bert Rosell, on Sat Nov 22 2003, 13:00:19 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the BrowserItem component.
 *  Please see BrowserItem.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>

#include "FileManager.h"
#include "FileUtils.h"

#include "BrowserItem.h"
#include "SDL_rotozoom.h"

#include "boost/Format.hpp"

#include "FileUtils.h"


HTexture BrowserItem::s_placeHolder = 0;

/* ********************************* 
 * BrowserItem
 ***********************************/
BrowserItem::BrowserItem(string filename):
m_filename(filename),
m_texture(0)
{
  if (s_placeHolder == 0)
  {
    s_placeHolder = Display::getInstance()->acquire("images\\placeholder.png");
  }
  m_name = prettyName(filename);
}

BrowserItem::~BrowserItem()
{
  unload(); 
}

void BrowserItem::attemptDiskLoad()
{
  Display* display=Display::getInstance();
  SDL_Surface* big=loadSDLSurface(m_filename);
  if (big != 0)
  {
    SDL_Surface* shrunk=zoomSurface(big, .25, .25, 1); // 100x75
    if (shrunk != 0)
    {
      m_texture = display->prepare(shrunk, m_filename+"shrunk");
      SDL_FreeSurface(shrunk);
    }
    SDL_FreeSurface(big);
  }
}

void BrowserItem::load()
{
  Display* display=Display::getInstance();
  
  string dir = (boost::format("cache\\browser\\%s\\") % m_filename).str();
  string sName = dir + "small.bmp";
  
  if (!FileManager::fileExists(sName))
  {
    // not yet
    SDL_Surface* big=loadSDLSurface(m_filename);
    if (big != 0)
    {
      SDL_Surface* shrunk=zoomSurface(big, .25, .25, 1); // 100x75
      if (shrunk != 0)
      {
        makeDir(dir);
        SDL_SaveBMP(shrunk, sName.c_str());
        SDL_FreeSurface(shrunk);
      }
      SDL_FreeSurface(big);
    }
  }

  m_texture=display->acquire(sName);
}