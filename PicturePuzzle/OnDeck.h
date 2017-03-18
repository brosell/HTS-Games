/* ****************************************************************************
 *
 *  OnDeck.h
 *  Created by Bert Rosell, on Sat Nov 15 2003, 10:04:45 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the OnDeck component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__ONDECK_H
#define ATC__ONDECK_H
 
#include "UIThing.h"
#include "Utils.h"

#include "Piece.h"
#include "Picture.h"
//#include "GameDialog.h"
class GameDialog;

#include <list>
using namespace std;

/** Purpose: inplements a UI control that holds the unplaced pieces
 */
class OnDeck: public UIThing, hts::Noncopyable
{
public:
  /// Constructor.
  OnDeck();
  virtual ~OnDeck();

  void setDialog(GameDialog* gd) { m_dialog = gd; }

  void setPicture(Picture* picture);

  virtual void paint(Display* display);

  /** when LEFT clicked either pick up a piece (if over a piece or
      drop off piece is over stack with space */
  virtual void onMouseClick(MouseClickEvent* event);

private:
  list<Piece*> m_stacks[8];

  GameDialog* m_dialog;
};
#endif // #ifndef ATC__ONDECK_H
 
