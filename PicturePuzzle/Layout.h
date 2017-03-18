/* ****************************************************************************
 *
 *  Layout.h
 *  Created by Bert Rosell, on Sat Nov 15 2003, 10:04:51 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the Layout component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__LAYOUT_H
#define ATC__LAYOUT_H

#include "UIThing.h"
#include "Utils.h"
 
#include "Picture.h"

#include "ThinkScheduler.h"

class GameDialog;

#define SectorLineColor 100, 100, 100, 127

/** Purpose: The Playfield
 */
class Layout: public UIThing, hts::Noncopyable
{
public:
  /// Constructor.
  Layout();
  virtual ~Layout();

  void setDialog(GameDialog* gd) { m_dialog = gd; }
  
  virtual void paint(Display* display);

  virtual void setPicture(Picture* picture) { m_picture = picture; }
  
  /** handles left click to place piece */
  virtual void onMouseClick(MouseClickEvent* event) = 0;
  
  /** handles movement so we can "snap" the piece */
//  virtual void onMouseMove(MouseMoveEvent* event);

  virtual bool isDone();// { return false; } //= 0;

  size_t nMoves() { return m_moves; }
  size_t nHints() { return m_hints; }

  virtual void doHelp() { m_hints++; };

  void setShowGrid(bool s) { m_showGrid = s; setDirty(true); }
  bool isGridShowing() { return m_showGrid; }

protected:
  void madeMove();
  Point coordFromScreen(int x, int y);
  void reset();
  void drawPieces(Display* display);

  void drawHelped(Display* display);

  Picture* m_picture;
  int m_piecesIds[8][6]; // holds the piece id where they belong
  Piece* m_pieces[8][6]; // holds the piece maybe where they belong

  Rect m_helped;

  size_t m_moves;
  size_t m_hints;

  bool m_showGrid;

  GameDialog* m_dialog;

  TypeThinkDelegate<Layout> d_clearHelped;
  void clearHelped();
};
#endif // #ifndef ATC__LAYOUT_H
 
