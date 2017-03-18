/* ****************************************************************************
 *
 *  LayoutPuzzle.cpp
 *  Created by Bert Rosell, on Sun Nov 16 2003, 19:34:25 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the LayoutPuzzle component.
 *  Please see LayoutPuzzle.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "LayoutPuzzle.h"

#include "GameDialog.h"
#include "PieceBucket.h"

/* ********************************* 
 * LayoutPuzzle
 ***********************************/
LayoutPuzzle::LayoutPuzzle(bool rot):
m_rot(rot)
{
 
}

LayoutPuzzle::~LayoutPuzzle()
{
 
}

void LayoutPuzzle::setPicture(Picture* picture)
{
  Layout::setPicture(picture);
  //PieceBucket* buckets[6];
  m_buckets.push_back(dynamic_cast<PieceBucket*>(m_dialog->getControlByName("cus_PlayScreen_OnDeck1")));
  m_buckets.push_back(dynamic_cast<PieceBucket*>(m_dialog->getControlByName("cus_PlayScreen_OnDeck2")));
  m_buckets.push_back(dynamic_cast<PieceBucket*>(m_dialog->getControlByName("cus_PlayScreen_OnDeck3")));
  m_buckets.push_back(dynamic_cast<PieceBucket*>(m_dialog->getControlByName("cus_PlayScreen_OnDeck4")));
  m_buckets.push_back(dynamic_cast<PieceBucket*>(m_dialog->getControlByName("cus_PlayScreen_OnDeck5")));
  m_buckets.push_back(dynamic_cast<PieceBucket*>(m_dialog->getControlByName("cus_PlayScreen_OnDeck6")));

  int curBucket = 0;

  vector<Piece*>::iterator i;
  vector<Piece*> copy;
  picture->chop(m_rot);
  std::copy(picture->begin_piece(), picture->end_piece(), back_inserter(copy));
  
  std::random_shuffle(copy.begin(), copy.end());

  for(i=copy.begin(); i!=copy.end(); i++)
  {
    if (m_buckets[curBucket]->isFull())
    {
      curBucket++;
    }
    m_buckets[curBucket]->piece_push(*i);
  }
}

void LayoutPuzzle::doHelp()
{
  if (m_helped.w != 0 && m_helped.h != 0) // != Rect(0, 0, 0, 0))
  {
    MessageBeep(-1);
    return;
  }
  if (rand()%2 == 0)
  {
    if (! (helpTryBucket() || helpTryBoard()))
    {
      MessageBeep(-1);
    }
  }
  else
  {
    if (! (helpTryBoard() || helpTryBucket()))
    {
      MessageBeep(-1);
    }
  }

  m_parent->setDirty(true);

  Layout::doHelp();
}

bool LayoutPuzzle::helpTryBucket()
{
  Piece* piece = 0;
  PieceBucket* pb = 0;
  std::random_shuffle(m_buckets.begin(), m_buckets.end());
  vector<PieceBucket*>::iterator i;
  for (i=m_buckets.begin(); i!=m_buckets.end(); i++)
  {
    pb = *i;
    piece = pb->piece_pop();
    if (piece != 0)
    {
      break;
    }
  }

  if (piece == 0)
  {
    return false;
  }

  Point coord = piece->getCoord();

  if (m_pieces[coord.x][coord.y] != 0)
  {
    pb->piece_push(m_pieces[coord.x][coord.y]);
  }

  m_pieces[coord.x][coord.y] = piece;
  while (!piece->isStraight())
  {
    piece->rotate();
  }

  m_helped = Rect(coord.x*50, coord.y*50, 50, 50);
  ThinkScheduler::doAt(ThinkScheduler::thisFrame() + 30, &d_clearHelped);
  return true;
}

bool LayoutPuzzle::helpTryBoard()
{
  vector<Point> wrongPieces;
  for (int x=0; x<8; x++)
  {
    for (int y=0; y<6; y++)
    {
      Piece* p = m_pieces[x][y];
      Point coord = Point(x, y);
      if (p != 0 && (p->getCoord() != coord || !p->isStraight()))
      {
        wrongPieces.push_back(coord);
      }
    }
  }

  if (wrongPieces.empty())
  {
    return false;
  }

  std::random_shuffle(wrongPieces.begin(), wrongPieces.end());

  Point& pt = wrongPieces[0];
  Piece* p = m_pieces[pt.x][pt.y];
  Point cp = p->getCoord();

  std::swap(m_pieces[pt.x][pt.y], m_pieces[cp.x][cp.y]);

  while (!p->isStraight())
  {
    p->rotate();
  }

  m_helped = Rect(cp.x*50, cp.y*50, 50, 50);
  ThinkScheduler::doAt(ThinkScheduler::thisFrame() + 30, &d_clearHelped);

  return true;
}




void LayoutPuzzle::onMouseClick(MouseClickEvent* event)
{
  setDirty();
  Piece* cp = m_dialog->cPiece();

  Point coord = coordFromScreen(event->x, event->y);
  // reference to a pointer... how cool is that?
  Piece*& pieceAtCoord = m_pieces[coord.x][coord.y];
  
  if (cp == 0 && pieceAtCoord != 0 && event->button == RIGHT_BUTTON)
  {
    pieceAtCoord->rotate();
    return;
  }

  if (event->button != LEFT_BUTTON)
  {
    return;
  }

  if (cp == 0)
  {
    if (pieceAtCoord != 0)
    {
      // pick up
      m_dialog->cPiece(pieceAtCoord);
      pieceAtCoord = 0;
      theGame.am->getSoundEffect("snd_Button")->play();
    }
  }
  else
  {
    if (pieceAtCoord == 0)
    {
      // drop off
      pieceAtCoord = cp;
      m_dialog->cPiece(0);
      theGame.am->getSoundEffect("snd_OnPuzzle")->play();
      madeMove();
    }
    else
    {
      theGame.am->getSoundEffect("snd_NotHere")->play();
    }
  }
}
