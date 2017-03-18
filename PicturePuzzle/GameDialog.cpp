/* ****************************************************************************
 *
 *  GameDialog.cpp
 *  Created by Bert Rosell, on Sat Nov 15 2003, 10:15:03 Eastern Standard Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the GameDialog component.
 *  Please see GameDialog.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "GameDialog.h"

#include "LayoutPuzzle.h"
#include "LayoutSlider.h"
#include "LayoutSwapper.h"
#include "LayoutSwapper2.h"
#include "PieceBucket.h"

#include "Convert.h"

bool areYouSure();
void doUpSell();

/* ********************************* 
 * GameDialog
 ***********************************/
GameDialog::GameDialog(IniFile& ini, string name, ChooseModeDlg& mode):
IniBasedDialog(ini, name),
m_currentPiece(0),
m_showGhost(false),
m_picture(0),
m_layout(0),
m_quit(false),
m_startTime(0),
m_moves(0),
m_time(0),
m_hint(0),
m_state(GS_PLAYING),
d_timeUpdater(*this, GameDialog::updateTime),
d_finished(*this, GameDialog::finished)
{
  Canvas* placeholder = 0;

  m_hint = dynamic_cast<Canvas*>(getControlByName("cvs_PlayScreen_Hint"));

  int dif = 0;

  if (mode.mode() == 100) // puzzle
  {
    setBackground("skn_dlg_PlayScreen_Puzzle");
    setUpPieceBuckets();
    m_layout = new LayoutPuzzle(mode.rotate());
  }
  else
  {
    setBackground("skn_dlg_PlayScreen_Swapper");
    hidePieceBuckets();
    dif = mode.difficulty()-300;
    m_layout = new LayoutSwapper2(dif, mode.rotate());
  }

  if (mode.showHint())
  {
    m_hint->setVisible(true);
  }
  else
  {
    m_hint->setVisible(false);
  }

  m_showGhost = mode.showGhost();

  Button* quit = dynamic_cast<Button*>(getControlByName("btn_PlayScreen_Quit"));
  if (quit != 0)
  {
    quit->addActionListener(this);
  }

  Button* hint = dynamic_cast<Button*>(getControlByName("btn_PlayScreen_Hint"));
  if (hint)
  {
    hint->addActionListener(this);
  }

  placeholder = dynamic_cast<Canvas*>(getControlByName("cvs_PlayScreen_Layout"));
  
  m_layout->setPosition(placeholder->getPosition());
  addUIThing(m_layout);
  m_layout->setDialog(this);
  removeUIThing(placeholder);

  m_time = dynamic_cast<Label*>(getControlByName("lbl_PlayScreen_Time"));
  m_startTime = time(0);

  m_hints = dynamic_cast<Label*>(getControlByName("lbl_PlayScreen_Hints"));

  m_moves = dynamic_cast<Label*>(getControlByName("lbl_PlayScreen_Moves"));

  m_showGrid = dynamic_cast<ToggleButton*>(getControlByName("tgl_PlayScreen_ShowGrid"));
  m_showGrid->addActionListener(this);

  ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &d_timeUpdater);
}

GameDialog::~GameDialog()
{
  if (m_layout != 0)
  {
    removeUIThing(m_layout);
    delete m_layout;
  }
}


string GameDialog::getTimeString()
{
  time_t now = time(0);
  int seconds = (now-m_startTime)%60;
  int minutes = ((now-m_startTime)/60)%60;
  int hours = ((now-m_startTime)/60)/60;

  return (boost::format("%d:%02d:%02d")%hours%minutes%seconds).str();
}

void GameDialog::updateTime()
{
  if (m_time != 0 && m_state != GS_FINISHED)
  {
    m_time->setText(getTimeString());
  }
  ThinkScheduler::resumeAt(ThinkScheduler::thisFrame()+15);
}


void GameDialog::setUpPieceBuckets()
{
  for (int c=0; c<6; c++)
  {
    setUpPieceBucket(c+1);
  }
}

void GameDialog::setUpPieceBucket(int c)
{
  string bucketName = (boost::format("cus_PlayScreen_OnDeck%d") % c).str();
  string buttonName = (boost::format("btn_PlayScreen_OnDeck%d_Cycle") % c).str();
  string labelName = (boost::format("lbl_PlayScreen_OnDeck%d_Count") % c).str();

  PieceBucket* pb = dynamic_cast<PieceBucket*>(getControlByName(bucketName));
  Button* b = dynamic_cast<Button*>(getControlByName(buttonName));
  Label* l = dynamic_cast<Label*>(getControlByName(labelName));
  
  pb->setDialog(this);
  pb->setControls(b, l);
}

void GameDialog::hidePieceBuckets()
{
  for (int c=0; c<6; c++)
  {
    hidePieceBucket(c+1);
  }
}

void GameDialog::hidePieceBucket(int c)
{
  string bucketName = (boost::format("cus_PlayScreen_OnDeck%d") % c).str();
  string buttonName = (boost::format("btn_PlayScreen_OnDeck%d_Cycle") % c).str();
  string labelName = (boost::format("lbl_PlayScreen_OnDeck%d_Count") % c).str();

  PieceBucket* pb = dynamic_cast<PieceBucket*>(getControlByName(bucketName));
  Button* b = dynamic_cast<Button*>(getControlByName(buttonName));
  Label* l = dynamic_cast<Label*>(getControlByName(labelName));

  pb->hide();
  b->hide();
  l->hide();
}




void GameDialog::setPicture(Picture* picture)
{
  m_picture = picture;
//  m_showPic = show;
  m_layout->setPicture(picture);

  m_hint->setImage(m_picture->getHint());

}

void GameDialog::cPiece(Piece* piece)
{
  if (piece == 0)
  {
    //theGame.uiSystem.showCursor(true);
    theGame.uiSystem.setMouseSub(0);
  }
  else
  {
    //theGame.uiSystem.showCursor(false);
    theGame.uiSystem.setMouseSub(piece->cTexture());
  }
  m_currentPiece = piece; 
}

void GameDialog::paint(Display* display)
{
  Rect r = m_layout->getTranslatedPosition();
  Point m = theGame.getMousePos();
  IniBasedDialog::paint(display);

  if (m_state==GS_FINISHED && m_finishedShow == true)
  {
    //getFont()->drawLine(display, "Yay!!!", 320, 240);
    SharedSkinHandle skin=theGame.am->getSkin("skn_fx_YouDidIt");
    skin->blit(display, r.x, r.y, false);
  }
}

void GameDialog::actionPerformed(ActionEvent* event)
{
  if (event->commandId == -1 && cPiece() == 0)
  {
    if (areYouSure() == true)
    {
      m_quit = true;
    }
    else
    {
      setDirty(true);
    }
  }
  else if (event->commandId == 10001)
  {
    m_layout->doHelp();
    m_hints->setText(toString(m_layout->nHints()));
  }
  else if (event->commandId == 10002)
  {
    m_layout->setShowGrid(m_showGrid->isChecked());
  }
}

void GameDialog::onMouseClick(MouseClickEvent* event)
{
  if (event->button == RIGHT_BUTTON && cPiece() != 0)
  {
    cPiece()->rotate();
    theGame.uiSystem.setMouseSub(cPiece()->cTexture());
  }
  else
  {
    IniBasedDialog::onMouseClick(event);
  }
}

void GameDialog::madeMove(int m)
{
  if(m_moves != 0)
  {
    m_moves->setText(toString(m));
  }
}

bool GameDialog::isDone() 
{
  if (m_layout->isDone() && m_state == GS_PLAYING)
  {
    m_finishedFrame = 0;
    m_finishedShow = false;
    ThinkScheduler::doAt(ThinkScheduler::nextFrame(), &d_finished);  
  }

  return m_state == GS_DONE; 
}

void GameDialog::finished()
{
  setDirty(true);
  m_layout->setShowGrid(false);
  m_state = GS_FINISHED;
  if (m_finishedFrame > 6)
  {
    m_state = GS_DONE;
  }
  ThinkScheduler::resumeAt(ThinkScheduler::thisFrame() + 10);
  m_finishedShow = !m_finishedShow;
  m_finishedFrame++;
}
