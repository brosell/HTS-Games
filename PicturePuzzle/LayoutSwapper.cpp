/* ****************************************************************************
 *
 *  LayoutSwapper.cpp
 *  Created by Bert Rosell, on Sun Nov 16 2003, 19:30:27 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the LayoutSwapper component.
 *  Please see LayoutSwapper.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "LayoutSwapper.h"


/* ********************************* 
 * LayoutSwapper
 ***********************************/
LayoutSwapper::LayoutSwapper():
m_click1(-1, -1)
{
 
}

LayoutSwapper::~LayoutSwapper()
{
 
}

void LayoutSwapper::onMouseClick(MouseClickEvent* event)
{
  if (event->button != LEFT_BUTTON)
  {
    return;
  }

  Point c = coordFromScreen(event->x, event->y);

  if (m_click1 == c)
  {
    m_click1 = Point(-1, -1);
    return;
  }

  if (m_click1 == Point(-1, -1))
  {
    m_click1 = c;
    return;
  }

  else
  {
    std::swap(m_pieces[m_click1.x][m_click1.y], m_pieces[c.x][c.y]);
    m_click1 = Point(-1, -1);
  }
}

void LayoutSwapper::setPicture(Picture* picture)
{
  Layout::setPicture(picture);
  vector<Piece*> shuffler;
  std::copy(picture->begin_piece(), picture->end_piece(), back_inserter(shuffler));
  random_shuffle(shuffler.begin(), shuffler.end());
  random_shuffle(shuffler.begin(), shuffler.end());
  random_shuffle(shuffler.begin(), shuffler.end());
  random_shuffle(shuffler.begin(), shuffler.end());

  lassert(shuffler.size() == 8*6);

  vector<Piece*>::iterator i = shuffler.begin();
  for (int x=0; x<8; x++)
  {
    for (int y=0; y<6; y++)
    {
      m_pieces[x][y] = (*i);
      i++;
    }
  }
}

void LayoutSwapper::paint(Display* display)
{
  Layout::paint(display);
  Rect r = getTranslatedPosition();
  if (m_click1 != Point(-1, -1))
  {
    display->fillRect(r.x+(m_click1.x*50), r.y+(m_click1.y*50), 50, 50, 255, 0, 0, 100);
  }
}