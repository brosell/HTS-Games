/* ****************************************************************************
 *
 *  GameDialog.h
 *  Created by Bert Rosell, on Sat Nov 15 2003, 10:15:03 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the GameDialog component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__GAMEDIALOG_H
#define ATC__GAMEDIALOG_H

#include "Utils.h"
#include "IniBasedDialog.h"
#include "ToggleButton.h"

#include "OnDeck.h"
#include "Layout.h"

#include "Picture.h"
#include "ChooseModeDlg.h"

#include "ThinkScheduler.h"
//#include "ThinkDelegates.h"

enum GAME_STATE
{
  GS_UNDEF,
  GS_PLAYING,
  GS_FINISHED,
  GS_DONE
};


/** Purpose: TODO: Describe the purpose of the class.
 *  (Everything that you write here will show up in the
 *  doc++ generated documentation.)
 */
class GameDialog: public IniBasedDialog, hts::Noncopyable
{
public:
  /// Constructor.
  GameDialog(IniFile& ini, string name, ChooseModeDlg& mode);
  virtual ~GameDialog();

  bool isDone();// { return m_layout->isDone(); }
  bool isQuit() { return m_quit==true; }

  void madeMove(int m);

  /** handles right click which causes the current piece to rotate */
  virtual void onMouseClick(MouseClickEvent* event);

  void setPicture(Picture* picture);

  Piece* cPiece() { return m_currentPiece; }
  void cPiece(Piece* piece);

  bool showPic() { return m_showGhost; }

  string getTimeString();
  size_t nMoves() { return m_layout->nMoves(); }
  size_t nHints() { return m_layout->nHints(); }

  virtual void paint(Display* display);

  virtual void actionPerformed(ActionEvent* event);

  
private:
  void setUpPieceBuckets();
  void setUpPieceBucket(int c);

  void hidePieceBuckets();
  void hidePieceBucket(int c);

  

  Layout* m_layout;
  Canvas* m_hint;

  ToggleButton* m_showGrid;

  Label* m_moves;
  Label* m_hints;
  Label* m_time;
  time_t m_startTime;
  
  bool m_showGhost;

  Piece* m_currentPiece;
  Picture* m_picture;

  bool m_quit;

  GAME_STATE m_state;

  TypeThinkDelegate<GameDialog> d_timeUpdater;
  void updateTime();

  TypeThinkDelegate<GameDialog> d_finished;
  void finished();
  int m_finishedFrame;
  bool m_finishedShow;
};
#endif // #ifndef ATC__GAMEDIALOG_H
 
