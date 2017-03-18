/* ****************************************************************************
 *
 *  Layout.cpp
 *  Created by Bert Rosell, on Sat Nov 15 2003, 10:04:51 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the Layout component.
 *  Please see Layout.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "Layout.h"

#include "GameDialog.h"


/* ********************************* 
 * Layout
 ***********************************/
Layout::Layout():
m_picture(0),
m_showGrid(true),
m_helped(0, 0, 0, 0),
d_clearHelped(*this, Layout::clearHelped)
{
  reset();
}

Layout::~Layout()
{
 
}

void Layout::reset()
{
  m_moves = 0;
  m_hints = 0;
  m_picture = 0;
  for (int y=0; y<6; y++)
  {
    for (int x=0; x<8; x++)
    {
      m_pieces[x][y] = 0;
    }
  }
}

void Layout::paint(Display* display)
{
  Rect r = getTranslatedPosition();
//  display->fillRect(r.x, r.y, r.w, r.h, 255, 0, 0, 255);
  if (m_picture != 0 && m_dialog->showPic())
  {
    m_picture->draw(display, r.x, r.y);
    // white out a bit;
    display->fillRect(r.x, r.y, r.w, r.h, 255, 255, 255, 127);
  }
  else
  {
    //display->fillRect(r.x, r.y, r.w-1, r.h-1, 0, 0, 0, 255);
  }
  drawPieces(display);

  drawHelped(display);
}

void Layout::drawHelped(Display* display)
{
  Rect r = getTranslatedPosition();
  if (m_helped != Rect(0, 0, 0, 0))
  {
    display->fillRect(r.x+m_helped.x, r.y+m_helped.y, m_helped.w, m_helped.h, 255, 0, 0, 127);
  }
}

void Layout::drawPieces(Display* display)
{
  Rect r = getTranslatedPosition();
  for (int y=0; y<6; y++)
  {
    for (int x=0; x<8; x++)
    {
      Rect grid(r);
      grid.x+=x*50;
      grid.y+=y*50;
      grid.w = 50;
      grid.h = 50;
      
      if (m_pieces[x][y] != 0)
      {
        m_pieces[x][y]->draw(display, grid.x, grid.y);
      }
      if (isGridShowing())
      {
        display->drawHLine(grid.x, grid.w, grid.y, SectorLineColor);
        display->drawHLine(grid.x, grid.w, grid.y+grid.h, SectorLineColor);
        display->drawVLine(grid.x, grid.y, grid.h, SectorLineColor);
        display->drawVLine(grid.x+grid.w, grid.y, grid.h, SectorLineColor);
      }
    }
  }
}

Point Layout::coordFromScreen(int x, int y)
{
  Rect r = getTranslatedPosition();
  Point m(x-r.x, y-r.y);
  Point closest( ((m.x/50)*50)+25, ((m.y/50)*50)+25);
  return Point(closest.x/50, closest.y/50);
}

bool Layout::isDone() 
{ 
  for (int x=0; x<8; x++)
  {
    for (int y=0; y<6; y++)
    {
      if (m_pieces[x][y] == 0)
      {
        return false;
      }
      if (m_pieces[x][y]->getCoord() != Point(x, y))
      {
        return false;
      }
      if (!m_pieces[x][y]->isStraight())
      {
        return false;
      }
    }
  }
  return true;
}

void Layout::madeMove() 
{ 
  m_moves++; 
  m_dialog->madeMove(m_moves); 
}

void Layout::clearHelped()
{
  m_helped = Rect(0, 0, 0, 0);
  setDirty(true);
}