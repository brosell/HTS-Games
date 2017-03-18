/* ****************************************************************************
 *
 *  BoardStates.cpp
 *  Created by Bert Rosell, on Sat Oct 25 2003, 23:22:47 Eastern Daylight Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Implementation of the BoardStates component.
 *  Please see BoardStates.h for full documentation of this system.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "BoardStates.h"
#include "Board.h"

/* ********************************* 
 * BoardStopped
 ***********************************/
std::auto_ptr<BoardStopped> BoardStopped::s_instance; 

BoardStopped::BoardStopped()
{
 
}

BoardStopped::~BoardStopped()
{
 
}

BoardStopped* BoardStopped::instance()
{
  if (s_instance.get() == 0){ 
    std::auto_ptr<BoardStopped> temp(new BoardStopped);
    s_instance = temp;
  }
  return s_instance.get(); 
}

void BoardStopped::draw(Board* board, Display* display, int x, int y)
{
}

void BoardStopped::think(Board* board)
{
}


/* ********************************* 
 * BoardPlaying
 ***********************************/
std::auto_ptr<BoardPlaying> BoardPlaying::s_instance; 

BoardPlaying::BoardPlaying()
{
 
}

BoardPlaying::~BoardPlaying()
{
 
}

BoardPlaying* BoardPlaying::instance()
{
  if (s_instance.get() == 0){ 
    std::auto_ptr<BoardPlaying> temp(new BoardPlaying);
    s_instance = temp;
  }
  return s_instance.get(); 
}

void BoardPlaying::draw(Board* board, Display* display, int x, int y)
{
  board->drawPlayField(display);
  board->m_shape.draw(display);
}

void BoardPlaying::think(Board* board)
{
  board->doWild();
  board->findMatchingBlocks();
}

void BoardPlaying::timeout(Board* board, int id)
{
  if (id == 101)
  {
    board->tick();
  }
}

/* ********************************* 
 * BoardPaused
 ***********************************/
std::auto_ptr<BoardPaused> BoardPaused::s_instance; 

BoardPaused::BoardPaused()
{
 
}

BoardPaused::~BoardPaused()
{
 
}

BoardPaused* BoardPaused::instance()
{
  if (s_instance.get() == 0){ 
    std::auto_ptr<BoardPaused> temp(new BoardPaused);
    s_instance = temp;
  }
  return s_instance.get(); 
}

void BoardPaused::draw(Board* board, Display* display, int x, int y)
{
  board->m_pauseFont->drawLine(display, "Paused", board->m_pausePoint.x, board->m_pausePoint.y, true);
}

void BoardPaused::think(Board* board)
{
}

/* ********************************* 
 * BoardGameOver
 ***********************************/
std::auto_ptr<BoardGameOver> BoardGameOver::s_instance; 

BoardGameOver::BoardGameOver()
{
 
}

BoardGameOver::~BoardGameOver()
{
 
}

BoardGameOver* BoardGameOver::instance()
{
  if (s_instance.get() == 0){ 
    std::auto_ptr<BoardGameOver> temp(new BoardGameOver);
    s_instance = temp;
  }
  return s_instance.get(); 
}

void BoardGameOver::draw(Board* board, Display* display, int x, int y)
{
  board->drawPlayField(display);
  board->m_bigBarrel->blit(display, board->m_gameOver.x, board->m_gameOver.y, false);
}

void BoardGameOver::think(Board* board)
{
}

/* ********************************* 
 * BoardBonus
 ***********************************/
std::auto_ptr<BoardBonus> BoardBonus::s_instance; 

BoardBonus::BoardBonus()
{
 
}

BoardBonus::~BoardBonus()
{
 
}

BoardBonus* BoardBonus::instance()
{
  if (s_instance.get() == 0){ 
    std::auto_ptr<BoardBonus> temp(new BoardBonus);
    s_instance = temp;
  }
  return s_instance.get(); 
}

void BoardBonus::draw(Board* board, Display* display, int x, int y)
{
  board->drawPlayField(display);
  
  Point pos = board->getPositioni();
  
  list<Point>::iterator i;
  for (i=board->m_levelBonusEmptySpots.begin(); i!=board->m_levelBonusEmptySpots.end(); i++)
  {
    Point p=(*i);
    Point dest(pos);
    dest.x += (p.x*BLOCK_SIZE + HALF_BLOCK_SIZE);
    dest.y += (p.y*BLOCK_SIZE + HALF_BLOCK_SIZE);
    board->m_levelBonusSkin->blit(display, dest.x, dest.y);
  }
  board->m_calcLevelBonusSkin->blit(display, board->m_calcLevelBonusLocation.x, board->m_calcLevelBonusLocation.y, true);
  
}

void BoardBonus::think(Board* board)
{
}

/* ********************************* 
 * BoardPreLevel
 ***********************************/
std::auto_ptr<BoardPreLevel> BoardPreLevel::s_instance; 

BoardPreLevel::BoardPreLevel()
{
 
}

BoardPreLevel::~BoardPreLevel()
{
 
}

BoardPreLevel* BoardPreLevel::instance()
{
  if (s_instance.get() == 0){ 
    std::auto_ptr<BoardPreLevel> temp(new BoardPreLevel);
    s_instance = temp;
  }
  return s_instance.get(); 
}

void BoardPreLevel::draw(Board* board, Display* display, int x, int y)
{
  board->drawPlayField(display);
}

void BoardPreLevel::think(Board* board)
{
}
