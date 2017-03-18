/* ****************************************************************************
 *
 *  LayoutSlider.h
 *  Created by Bert Rosell, on Sun Nov 16 2003, 19:30:36 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the LayoutSlider component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__LAYOUTSLIDER_H
#define ATC__LAYOUTSLIDER_H
 
#include "Layout.h"
#include "GameDialog.h"

/** Purpose: impliments Slider style layout
 */
class LayoutSlider: public Layout
{
public:
  /// Constructor.
  LayoutSlider();
  virtual ~LayoutSlider();
  
  virtual void onMouseClick(MouseClickEvent* event);
  virtual void setPicture(Picture* picture);

  virtual bool isDone();

private:

};
#endif // #ifndef ATC__LAYOUTSLIDER_H
 
