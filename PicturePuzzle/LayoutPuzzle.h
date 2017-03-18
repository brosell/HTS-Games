/* ****************************************************************************
 *
 *  LayoutPuzzle.h
 *  Created by Bert Rosell, on Sun Nov 16 2003, 19:34:25 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the LayoutPuzzle component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__LAYOUTPUZZLE_H
#define ATC__LAYOUTPUZZLE_H
 
#include "Layout.h"
#include "PieceBucket.h"

/** Purpose: TODO: Describe the purpose of the class.
 *  (Everything that you write here will show up in the
 *  doc++ generated documentation.)
*/
class LayoutPuzzle: public Layout
{
public:
  /// Constructor.
  LayoutPuzzle(bool rot);
  virtual ~LayoutPuzzle();
  
  virtual void setPicture(Picture* picture);

  virtual void onMouseClick(MouseClickEvent* event);

  virtual void doHelp();

protected:
  bool helpTryBucket();
  bool helpTryBoard();
private:
  vector<PieceBucket*> m_buckets;
  bool m_rot;
};
#endif // #ifndef ATC__LAYOUTPUZZLE_H
 
