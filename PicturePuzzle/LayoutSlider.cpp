/* ****************************************************************************
 *
 *  LayoutSlider.cpp
 *  Created by Bert Rosell, on Sun Nov 16 2003, 19:30:36 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the LayoutSlider component.
 *  Please see LayoutSlider.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "LayoutSlider.h"


/* ********************************* 
 * LayoutSlider
 ***********************************/
LayoutSlider::LayoutSlider()
{
 
}

LayoutSlider::~LayoutSlider()
{
 
}

void LayoutSlider::onMouseClick(MouseClickEvent* event)
{
  if (event->button != LEFT_BUTTON)
  {
    return;
  }

  Point c = coordFromScreen(event->x, event->y);
  Point empty(-1, -1);

  if (c.x > 0 && m_pieces[c.x-1][c.y] == 0)
  {
    empty = Point(c.x-1, c.y);
  }
  else if (c.x < 7 && m_pieces[c.x+1][c.y] == 0)
  {
    empty = Point(c.x+1, c.y);
  }
  else if (c.y > 0 && m_pieces[c.x][c.y-1] == 0)
  {
    empty = Point(c.x, c.y-1);
  }
  else if (c.y < 5 && m_pieces[c.x][c.y+1] == 0)
  {
    empty = Point(c.x, c.y+1);
  }

  if (empty == Point(-1, -1))
  {
    MessageBeep(-1);
    return;
  }

  m_pieces[empty.x][empty.y] = m_pieces[c.x][c.y];
  m_pieces[c.x][c.y] = 0;
}

void LayoutSlider::setPicture(Picture* picture)
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

  m_pieces[7][5] = 0; // the initially blank spot
}

bool LayoutSlider::isDone() 
{ 
  int numEmpty = 0;
  for (int x=0; x<8; x++)
  {
    for (int y=0; y<6; y++)
    {
      if (m_pieces[x][y] == 0)
      {
        if (numEmpty > 0)
        {
          return false;
        }
        numEmpty++;
      }
      if (m_pieces[x][y]->getCoord() != Point(x, y))
      {
        return false;
      }
    }
  }
  return true;
}