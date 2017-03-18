/* ****************************************************************************
 *
 *  BoardStates.h
 *  Created by Bert Rosell, on Sat Oct 25 2003, 23:22:47 Eastern Daylight Time
 *
 *  Copyright (c) 2003, Bert Rosell
 *
 *
 *
 *  File Contents: Interface and documentation of the BoardStates component.
 *
 *************************************************************************** */
 
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#ifndef ATC__BOARDSTATES_H
#define ATC__BOARDSTATES_H
 
#include <memory>

class Board;
class Display;

class BoardState
{
public:
  virtual ~BoardState() { }
  virtual void draw(Board* board, Display* display, int x, int y) = 0;
  virtual void think(Board* board) = 0;
  virtual void timeout(Board* board, int id) { }
};

/** Purpose: TODO: Describe the purpose of the class.
 *  (Everything that you write here will show up in the
 *  doc++ generated documentation.)
 */
class BoardStopped: public BoardState
{
public:
  static BoardStopped* instance(); 

  void draw(Board* board, Display* display, int x, int y);
  void think(Board* board);
  
public:
    virtual ~BoardStopped();
private:
	// Copying of this class is prohibited:
    BoardStopped(const BoardStopped&);
private:
	// Assignment to this class is prohibited:
    BoardStopped& operator=(const BoardStopped&);
private:
  /// Constructor.
  BoardStopped();
  static std::auto_ptr<BoardStopped> s_instance; 

};


/** Purpose: TODO: Describe the purpose of the class.
 *  (Everything that you write here will show up in the
 *  doc++ generated documentation.)
 */
class BoardPlaying: public BoardState
{
public:
  static BoardPlaying* instance(); 

  void draw(Board* board, Display* display, int x, int y);
  void think(Board* board);

  void timeout(Board* board, int id);
public:
    virtual ~BoardPlaying();
private:
	// Copying of this class is prohibited:
    BoardPlaying(const BoardPlaying&);
private:
	// Assignment to this class is prohibited:
    BoardPlaying& operator=(const BoardPlaying&);
private:
  /// Constructor.
  BoardPlaying();
  static std::auto_ptr<BoardPlaying> s_instance; 

};

/** Purpose: TODO: Describe the purpose of the class.
 *  (Everything that you write here will show up in the
 *  doc++ generated documentation.)
 */
class BoardPaused: public BoardState
{
public:
  static BoardPaused* instance(); 

  void draw(Board* board, Display* display, int x, int y);
  void think(Board* board);
public:
    virtual ~BoardPaused();
private:
	// Copying of this class is prohibited:
    BoardPaused(const BoardPaused&);
private:
	// Assignment to this class is prohibited:
    BoardPaused& operator=(const BoardPaused&);
private:
  /// Constructor.
  BoardPaused();
  static std::auto_ptr<BoardPaused> s_instance; 

};

/** Purpose: TODO: Describe the purpose of the class.
 *  (Everything that you write here will show up in the
 *  doc++ generated documentation.)
 */
class BoardGameOver: public BoardState
{
public:
  static BoardGameOver* instance(); 

  void draw(Board* board, Display* display, int x, int y);
  void think(Board* board);
public:
    virtual ~BoardGameOver();
private:
	// Copying of this class is prohibited:
    BoardGameOver(const BoardGameOver&);
private:
	// Assignment to this class is prohibited:
    BoardGameOver& operator=(const BoardGameOver&);
private:
  /// Constructor.
  BoardGameOver();
  static std::auto_ptr<BoardGameOver> s_instance; 

};

/** Purpose: TODO: Describe the purpose of the class.
 *  (Everything that you write here will show up in the
 *  doc++ generated documentation.)
 */
class BoardBonus: public BoardState
{
public:
  static BoardBonus* instance(); 

  void draw(Board* board, Display* display, int x, int y);
  void think(Board* board);
public:
    virtual ~BoardBonus();
private:
	// Copying of this class is prohibited:
    BoardBonus(const BoardBonus&);
private:
	// Assignment to this class is prohibited:
    BoardBonus& operator=(const BoardBonus&);
private:
  /// Constructor.
  BoardBonus();
  static std::auto_ptr<BoardBonus> s_instance; 

};

/** Purpose: TODO: Describe the purpose of the class.
 *  (Everything that you write here will show up in the
 *  doc++ generated documentation.)
 */
class BoardPreLevel: public BoardState
{
public:
  static BoardPreLevel* instance(); 

  void draw(Board* board, Display* display, int x, int y);
  void think(Board* board);
public:
    virtual ~BoardPreLevel();
private:
	// Copying of this class is prohibited:
    BoardPreLevel(const BoardPreLevel&);
private:
	// Assignment to this class is prohibited:
    BoardPreLevel& operator=(const BoardPreLevel&);
private:
  /// Constructor.
  BoardPreLevel();
  static std::auto_ptr<BoardPreLevel> s_instance; 

};
#endif // #ifndef ATC__BOARDSTATES_H
 
