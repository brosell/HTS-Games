/* ****************************************************************************
 *
 *  PictureBrowser.cpp
 *  Created by Bert Rosell, on Fri Nov 21 2003, 20:31:24 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the PictureBrowser component.
 *  Please see PictureBrowser.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "PictureBrowser.h"


#include "ThinkScheduler.h"


/* ********************************* 
 * PictureBrowser
 ***********************************/
PictureBrowser::PictureBrowser():
m_currentPage(0),
m_selectedOffset(-1),
m_thinker(*this, PictureBrowser::loadThinker),
m_paused(true),
m_margin(0)
{
  ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &m_thinker);
}

PictureBrowser::PictureBrowser(StringMap& properties):
m_currentPage(0),
m_selectedOffset(-1),
m_thinker(*this, PictureBrowser::loadThinker),
m_paused(true)
{
  ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &m_thinker);
  m_margin = atoi(properties["Margin"].c_str());
}

PictureBrowser::~PictureBrowser()
{
  clear();
}

void PictureBrowser::clear()
{
  for_each(m_items.begin(), m_items.end(), hts::Delete());
  m_items.clear();
  m_filenames.clear();
  m_currentPage = 0;
}

void PictureBrowser::addPicture(string filename)
{
  m_items.push_back(new BrowserItem(filename));
  m_filenames.push_back(filename);
  setDirty();
}

inline int PictureBrowser::rowsPerPage()
{
  Rect r = getPosition();
  return (r.h - (m_margin*2)) / YDIST; // buffer
}

inline int PictureBrowser::colsPerPage()
{
  Rect r = getPosition();
  return (r.w - (m_margin*2)) / XDIST; // buffer
}

int PictureBrowser::numPages()
{
  int s = m_items.size();
  int rs = rowsPerPage();
  int cs = colsPerPage();

  int ret = s/(rs*cs);
  if (s%(rs*cs) != 0)
  {
    ret++;
  }

  return ret;
}
  

void PictureBrowser::incPage()
{
  int maxpages = numPages();
  if (m_currentPage < maxpages-1)
  {
    unloadItems();
    m_currentPage++;
    setDirty();
  }
}

void PictureBrowser::decPage()
{
  if (m_currentPage > 0)
  {
    unloadItems();
    m_currentPage--;
    setDirty();
  }
}

void PictureBrowser::unloadItems()
{
  vector<BrowserItem*>::iterator i;
  for (i=m_items.begin(); i!=m_items.end(); i++)
  {
    (*i)->unload();
  }
  setDirty();
}

inline int PictureBrowser::startOffsetOfPage(int p)
{
  int rows=rowsPerPage();
  int cols=colsPerPage();

  return p*rows*cols;
}

inline int PictureBrowser::endOffsetOfPage(int p)
{
  int rows=rowsPerPage();
  int cols=colsPerPage();

  int startOff = p*rows*cols;
  return hts::min(startOff+(rows*cols), (int)m_items.size());
}


void PictureBrowser::loadThinker()
{
  if (!m_paused)
  {
    for(int o=startOffsetOfPage(m_currentPage); o<endOffsetOfPage(m_currentPage); o++)
    {
      if (!m_items[o]->loaded())
      {
        m_items[o]->load();
        setDirty();
        break;
      }
    }
  }
  ThinkScheduler::resumeAt(ThinkScheduler::thisFrame()+1);
}



void PictureBrowser::paint(Display* display)
{
  Rect r=getTranslatedPosition();
  
  int rows=rowsPerPage();
  int cols=colsPerPage();

  int startOff = startOffsetOfPage(m_currentPage);
  int endOff = endOffsetOfPage(m_currentPage);

  lassert(startOff < m_items.size());


  int xm=(r.w-(2*m_margin))/cols;
  int ym=(r.h-(2*m_margin))/rows;

  int curOff = startOff;  
  for (int y=0; y<rows && curOff < endOff; y++)
  {
    for (int x=0; x<cols && curOff < endOff; x++, curOff++)
    {
      int dx=r.x+(x*xm) + m_margin;
      int dy=r.y+(y*ym) + m_margin;
      
      display->blit(m_items[curOff]->getTexture(), dx, dy);

      //getFont()->drawLine(display, m_items[curOff]->getName(), dx, dy+85);
    }
  }
}

void PictureBrowser::onMouseClick(MouseClickEvent* event)
{
  UIThing::onMouseClick(event);
  Rect r=getTranslatedPosition();
  int x=event->x - r.x;
  int y=event->y - r.y;

  int rows=rowsPerPage();
  int cols=colsPerPage();

  int xm=r.w/cols;
  int ym=r.h/rows;


  int xx = x/xm;
  int yy = y/ym;

  m_selectedOffset = (m_currentPage*numPerPage()) + (yy * colsPerPage()) + xx;
  if (m_selectedOffset > m_items.size())
  {
    m_selectedOffset = -1;
  }
  else
  {
    fireEvent();
  }
}

void PictureBrowser::fireEvent()
{
  m_event.commandId = getId();
  m_event.thing = this;
  
  set<ActionListener*> copy(m_listeners);
  set<ActionListener*>::iterator i;
  for (i=copy.begin(); i!=copy.end(); i++)
  {
    (*i)->actionPerformed(&m_event);
  }
}
