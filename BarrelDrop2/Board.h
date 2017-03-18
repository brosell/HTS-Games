#ifndef Board_h
#define Board_h

#include "BR_Game.h"
#include "SoundEffect.h"
#include "Coroutine.h"
#include "CoroutineDelegates.h"

#include "Shape.h"
#include "Block.h"

#include "Score.h"

const int WIDTH = 8;
const int HEIGHT = 10;

const int BLOCK_SIZE = 45; //480 / WIDTH; // 60
const int HALF_BLOCK_SIZE = BLOCK_SIZE / 2;

const int BLOCK_COUNT = 3; // red, green, blue, purple

enum BoardState
{
  BS_UNDEF,
  BS_STOPPED,
  BS_PLAYING,
  BS_PAUSED,
  BS_LEVEL_BONUS,
  BS_PRE_LEVEL,
  BS_GAME_OVER,
  BS_DEMO_OVER
};

class Board: public Thing, public TimerListener, public ScoreListener, public CoroutineListener
{
public:
  Board();
  ~Board();

  void start();
  void stop();
  void gameOver();
  void demoOver();

  int moveNum() { return m_currentMove; }
  void incMoveNum() { m_currentMove++; }

  /** returns true if there is any pending activity like barrels going away, etc */
  bool anyActivity();

  void tick();
  virtual void draw(Display* dispay, int x, int y);

  // TimerLIstern
  virtual void timeout(TimerEvent* ev);

  //ScoreListener
  virtual void scoreChanged(ScoreChangeEvent* ev);
  virtual void levelChanged(LevelChangeEvent* ev);

  virtual void coroutineFinished(CoroutineEvent* ev);

  bool isBlockType(int x, int y, int t);
  int getBlockType(int x, int y);
  void setBlockType(int x, int y, int t);

  Block* getBlock(int x, int y) { return m_blocks[x][y]; }

  void checkTile(int x, int y, list<Point>& toBeWacked, bool first);

  bool isRunning() { return m_state == BS_PLAYING; }
  bool isPaused() { return m_state == BS_PAUSED; }
  void pause(bool p); 

  bool isEmpty();
  int getBlockCount();

  void findMatchingBlocks();
  void removeTiles(list<Point>& points);
  void setScoreLocation(list<Point>& points);
  void checkClearBoard();
  int clearDoneBlocks();

  void doWild();

  void horizontalWild(int x, int y);
  void verticalWild(int x, int y);

  Point getPixelPoint(int x, int y)
  {
    Point ret;
    ret.x = (x*BLOCK_SIZE) + (BLOCK_SIZE / 2) + 100;
    ret.y = (y*BLOCK_SIZE) + (BLOCK_SIZE / 2) + 15;
    return ret;
  }

  void doLevelBonus();
  void co_clearDoneBlocks();
  void co_doSettle();
  void co_gameOver();

protected:
  void doLevel();

  void startLevelBonus();
  bool continueLevelBonus();
  void endLevelBonus();
  void preLevel();

  void co_levelText();
private:
  BoardState m_state;

  int m_currentMove;

  Block* m_blocks[WIDTH][HEIGHT];

  Label* m_lbl_score;
  Label* m_lbl_level;

  Shape& m_shape;

  HTimer m_tickTimeout;
//  HTimer m_levelBonusTimer;
//  HTimer m_levelBonusPauseTimer;
  
  SoundEffectHandle m_disappearSound;
  SoundEffectHandle m_levelSound;
  SoundEffectHandle m_multiSound;
  SoundEffectHandle m_wildSound;
  SoundEffectHandle m_clearBoardSound;
  SoundEffectHandle m_levelBonusSound;

  RotateSkinHandle m_boardStubSkin;

  FontHandle m_pauseFont;
  Point m_pausePoint;

  Point m_lastScorePoint;

  list<Point> m_levelBonusEmptySpots;
  int m_levelBonusCX;
  int m_levelBonusCY;
  SharedSkinHandle m_levelBonusSkin;
  SharedSkinHandle m_calcLevelBonusSkin;
  SharedSkinHandle m_bigBarrel;
  Point m_calcLevelBonusLocation;

  SpawnableCoroutineTypeDelegate<Board> d_levelBonus;
  SpawnableCoroutineTypeDelegate<Board> d_clearBlocks;
  SpawnableCoroutineTypeDelegate<Board> d_gameOver;
  SpawnableCoroutineTypeDelegate<Board> d_levelText;
  
  Point m_gameOver;
};

#endif
