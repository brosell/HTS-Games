/* ****************************************************************************
 *
 *  LayoutSwapper2.h
 *  Created by Bert Rosell, on Wed Nov 19 2003, 13:28:45 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the LayoutSwapper2 component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__LAYOUTSWAPPER2_H
#define ATC__LAYOUTSWAPPER2_H
 
#include "Layout.h"
#include "GameDialog.h"

#include "ThinkScheduler.h"

#include "StretchablePiece.h"

class Sector
{
public:
  Sector(SDL_Surface* image, bool rot, Layout* layout);
  ~Sector()
  {
    delete piece;
  }

  bool swapping() { return position.w != drawRect.w; }

  void setPiece(StretchablePiece* piece);
  void draw(Display* display, int topLeftX, int topLeftY);

  StretchablePiece* piece;
  Rect position;
  int correctId;

private:
  TypeThinkDelegate<Sector> m_thinker;
  void think();
  Rect drawRect;

  Layout* m_layout;
};

/** Purpose: impliments 2nd style of swapper
 *   layout. This one has different size boxes
 *   and causes the pieces to stretch or shrink 
 *   to fit.
 */
class LayoutSwapper2: public Layout
{
public:
  /// Constructor.
  LayoutSwapper2(int dif, bool rot);
  virtual ~LayoutSwapper2();
  
  virtual void onMouseClick(MouseClickEvent* event);
  virtual void setPicture(Picture* picture);
  
  virtual void paint(Display* display);

  virtual bool isDone();

  virtual void doHelp();

protected:
  void shufflePieces();

  void swap(Sector* s1, Sector* s2);
private:
  vector<Sector*> m_sectors;

  vector<vector<Rect> > m_sectorLayouts;

  Sector* m_click1;

  bool m_rot;
};
#endif // #ifndef ATC__LAYOUTSWAPPER2_H
 
