/* ****************************************************************************
 *
 *  PieceBucket.h
 *  Created by Bert Rosell, on Sun Nov 23 2003, 16:48:06 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the PieceBucket component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__PIECEBUCKET_H
#define ATC__PIECEBUCKET_H
 
#include "UIThing.h"
#include "Utils.h"

#include "IniFile.h"

#include "GameDialog.h"

/** Purpose: holds pieces, rotates them, too
 */
class PieceBucket: public UIThing, public ActionListener, hts::Noncopyable
{
public:
  /// Constructor.
  PieceBucket(StringMap& attributes);
  virtual ~PieceBucket();

  /** puts the top piece on the bottom */
  void cycle();

  void setControls(Button* cycle, Label* count);

  virtual void actionPerformed(ActionEvent* event);

  void setDialog(GameDialog* gd) { m_dialog = gd; }

  size_t piece_count() { return m_stack.size(); }
  bool isFull() { return m_stack.size() >= m_maxCount; }
  bool piece_push(Piece* p);
  Piece* piece_pop();

  virtual void paint(Display* display);

  /** when LEFT clicked either pick up a piece (if over a piece or
      drop off piece is over stack with space */
  virtual void onMouseClick(MouseClickEvent* event);

private:
  list<Piece*> m_stack;
  size_t m_maxCount;

  GameDialog* m_dialog;
  Label* m_lbl_count;
};

inline bool PieceBucket::piece_push(Piece* p)
{
  if (m_stack.size() < m_maxCount)
  {
    m_stack.push_back(p);
    return true;
  }
  return false;
}

inline void PieceBucket::cycle()
{
  if (m_stack.size() > 1)
  {
    setDirty(true);
    Piece* p = m_stack.back();
    m_stack.pop_back();
    m_stack.push_front(p);
  }
}

#endif // #ifndef ATC__PIECEBUCKET_H
 
