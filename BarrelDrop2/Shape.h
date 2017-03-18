#ifndef Shape_h
#define Shape_h

#include "BR_Game.h"
#include "Timer.h"
#include "SoundEffect.h"

#include "GameMath.h"
#include "CoroutineDelegates.h"

class Board;
class Block;

#include "Score.h"

class ShapePrimitive
{
public:
  ShapePrimitive(Board* board);
  ~ShapePrimitive();

  Block* getBlock(int o) { return m_blocks[o]; }
  bool isStraight() { return m_isStraight; }
  bool isSpecial() { return m_isSpecial; }
  int getOrientation() { return m_orientation; }

  void rotateLeft();
  void rotateRight();

  Point getBlock1Pos(Point p, int orientation);
  Point getBlock2Pos(Point p, int orientation);
  Point getBlock3Pos(Point p, int orientation);

  Point getBlock1Pos(Point p)
  {
    return getBlock1Pos(p, m_orientation);
  }
  Point getBlock2Pos(Point p)
  {
    return getBlock2Pos(p, m_orientation);
  }
  Point getBlock3Pos(Point p)
  {
    return getBlock3Pos(p, m_orientation);
  }



private:
  static bool s_lastWasSpecial;
  Block* m_blocks[3];
  int m_orientation;
  Board* m_board;
  bool m_isStraight;
  bool m_isSpecial;
};

class Shape: public TimerListener, public ScoreListener
{
public:
  static Shape& instance()
  {
    if(s_instance.get() == 0)
    {
      auto_ptr<Shape> temp(new Shape);
      s_instance=temp;
    }
    return *s_instance.get();
  }

  /* sets the location to top of screen and creates 3 random colored blocks */
  void reset();

  void newGame();

  /* if the shape hasn;t settled to the bottom yet, the isInPlay == true */
  bool isInPlay();
  
  /* checks timeout and moves block */
  void tick();

  void doSpecial();
  void doUpDownWild();
  void doLeftRightWild();

  /* called by the timer */
  virtual void timeout(TimerEvent* ev);

  virtual void levelChanged(LevelChangeEvent* ev);

  void draw(Display* display);
  void drawStraight(Display* display);
  void drawBent(Display* display);
  

  void rotateLeft();
  void rotateRight();

  void moveLeft();
  void moveRight();
  void nudgeDown();

  bool isMoveSafe(Point p, int orientation);
  bool isMoveSafe(int orientation)
  {
    return isMoveSafe(m_blockPosition, orientation);
  }

  void setBoard(Board* b)
  {
    m_board = b;
  }

  void setSpeed(int level);
  int getSpeed() { return m_millis; }

  ShapePrimitive* getNextShape() { return m_nextShape; }

  void endGame();

protected:

  Point getBlock1Pos() { return m_currentShape->getBlock1Pos(m_blockPosition, m_currentShape->getOrientation()); }
  Point getBlock2Pos() { return m_currentShape->getBlock2Pos(m_blockPosition, m_currentShape->getOrientation()); }
  Point getBlock3Pos() { return m_currentShape->getBlock3Pos(m_blockPosition, m_currentShape->getOrientation()); }
  
  ShapePrimitive* createShape();
  bool isBelowClear();

private:
  ShapePrimitive* m_currentShape;
  ShapePrimitive* m_nextShape;

  Point m_blockPosition;

  HTimer m_moveTimer;

  int m_millis;

  bool m_run;
  bool m_doingSpecial;

  bool m_inPlay;

  Board* m_board;

  Shape();
  Shape(const Shape& other);

  static auto_ptr<Shape> s_instance;

  SoundEffectHandle m_moveSound;
  SoundEffectHandle m_settleSound;
};

#endif