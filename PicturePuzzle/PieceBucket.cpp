/* ****************************************************************************
 *
 *  PieceBucket.cpp
 *  Created by Bert Rosell, on Sun Nov 23 2003, 16:48:06 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the PieceBucket component.
 *  Please see PieceBucket.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "PieceBucket.h"

#include "Convert.h"


/* ********************************* 
 * PieceBucket
 ***********************************/
PieceBucket::PieceBucket(StringMap& attributes)
{
  m_maxCount = atoi(attributes["MaxCount"].c_str());
}

PieceBucket::~PieceBucket()
{
 
}

void PieceBucket::setControls(Button* cycle, Label* count)
{
  cycle->addActionListener(this);
  m_lbl_count = count;
}

void PieceBucket::actionPerformed(ActionEvent* event)
{
  if (m_dialog->cPiece() == 0)
  {
    // only cycle if we aren't carying a piece
    cycle();
    theGame.am->getSoundEffect("snd_Button")->play();
    return;
  }
}


Piece* PieceBucket::piece_pop()
{
  Piece* p = 0;
  if (!m_stack.empty())
  {
    p = m_stack.back();
    m_stack.pop_back();
  }
  return p;
}

void PieceBucket::paint(Display* display)
{
  m_lbl_count->setText(toString(m_stack.size()));
  Rect r = getTranslatedPosition();
  if (!m_stack.empty())
  {
    Piece* p = m_stack.back();
    p->draw(display, r.x, r.y);
  }

}

void PieceBucket::onMouseClick(MouseClickEvent* event)
{
  lassert(m_dialog != 0);

  setDirty(true);
  if (event->button == RIGHT_BUTTON && m_dialog->cPiece() == 0 && !m_stack.empty())
  {
    m_stack.back()->rotate();
  }
  
  if (event->button != LEFT_BUTTON)
  {
    return;
  }

  
  if (m_dialog->cPiece() != 0)
  {
    if (m_stack.size() < m_maxCount)
    {
      m_stack.push_back(m_dialog->cPiece());
      m_dialog->cPiece(0);
      theGame.am->getSoundEffect("snd_Button")->play();
    }
    else
    {
      theGame.am->getSoundEffect("snd_NotHere")->play();
    }
    return;
  }

  if (!m_stack.empty())
  {
    m_dialog->cPiece(m_stack.back());
    m_stack.pop_back();
    theGame.am->getSoundEffect("snd_Button")->play();
  }
}