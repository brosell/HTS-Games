/* ****************************************************************************
 *
 *  OnDeck.cpp
 *  Created by Bert Rosell, on Sat Nov 15 2003, 10:04:45 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the OnDeck component.
 *  Please see OnDeck.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "OnDeck.h"

#include "GameDialog.h"

/* ********************************* 
 * OnDeck
 ***********************************/
OnDeck::OnDeck():
m_dialog(0)
{
 
}

OnDeck::~OnDeck()
{
 
}

struct OnDeckDrawPiece: public std::unary_function<Piece*, void>
{
  OnDeckDrawPiece(int xoff): m_x(xoff), m_iter(0) { }
  void operator()(Piece* piece)
  {
    Display* display = Display::getInstance();
    piece->draw(display, m_x+m_iter, m_iter);
    m_iter+=2;
  }

private:
  int m_x;
  int m_iter;
};

void OnDeck::paint(Display* display)
{
  Rect r = getTranslatedPosition();
  display->fillRect(r.x, r.y, r.w, r.h, 255, 0, 0, 255);

  for (int c=0; c<8; c++)
  {
    for_each(m_stacks[c].begin(), m_stacks[c].end(), OnDeckDrawPiece(r.x+(c*72)));
  }
}

void OnDeck::setPicture(Picture* picture)
{
  vector<Piece*> shuffler;
  std::copy(picture->begin_piece(), picture->end_piece(), back_inserter(shuffler));
  random_shuffle(shuffler.begin(), shuffler.end());
  random_shuffle(shuffler.begin(), shuffler.end());
  random_shuffle(shuffler.begin(), shuffler.end());
  random_shuffle(shuffler.begin(), shuffler.end());
  lassert(shuffler.size() == 8*6);

  vector<Piece*>::iterator i = shuffler.begin();
  for (int c=0; c<8; c++)
  {
    for (int d=0; d<6; d++)
    {
      m_stacks[c].push_back(*i);
      i++;
    }
  }
}

void OnDeck::onMouseClick(MouseClickEvent* event)
{
  lassert(m_dialog != 0);

  if (event->button != LEFT_BUTTON)
  {
    return;
  }
  int stack = (event->x-31)/72;
  lassert(stack >=0 && stack < 8);
  if (stack >= 8 || stack < 0) return;

  Piece* cp = m_dialog->cPiece();
  if (cp != 0 && m_stacks[stack].size() < 6)
  {
    m_stacks[stack].push_back(cp);
    m_dialog->cPiece(0);
    return;
  }

  if (cp == 0 && m_stacks[stack].size() > 0)
  {
    cp = m_stacks[stack].back();
    m_stacks[stack].pop_back();
    m_dialog->cPiece(cp);
    return;
  }
}
