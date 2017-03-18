/* ****************************************************************************
 *
 *  LayoutSwapper.h
 *  Created by Bert Rosell, on Sun Nov 16 2003, 19:30:27 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the LayoutSwapper component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__LAYOUTSWAPPER_H
#define ATC__LAYOUTSWAPPER_H
 
#include "Layout.h"
#include "GameDialog.h"

/** Purpose: impliments the swapper style layout
 */
class LayoutSwapper: public Layout
{
public:
  /// Constructor.
  LayoutSwapper();
  virtual ~LayoutSwapper();

  virtual void onMouseClick(MouseClickEvent* event);
  virtual void setPicture(Picture* picture);

  virtual void paint(Display* display);
private:
  Point m_click1;
};
#endif // #ifndef ATC__LAYOUTSWAPPER_H
 
