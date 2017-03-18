#ifndef Board_h
#define Board_h


#include "Quadrant.h"
#include "Shape.h"

/**
A Board is four Quadrants arainged like so:
<textarea>
   22222
  1122233
  111O333
  1144433
   44444
*/
class Board
{
public:
  Board();
  void prepareForNewGame();
  void draw(Display* display);

  void rotateShapeLeft();
  void rotateShapeRight();

  void moveShapeLeft();
  void moveShapeRight();

  void moveShapeDown();

  void chaseMouse(Point m);

protected:
  /**
  returns the next shape while putting one on deck
  */
  void getNextShape();
private:
  Quadrant m_quadrants[4];
  Shape* m_currentShape;
  int m_currentQuadrant;
  Shape* m_nextShape;

  SpawnableCoroutineTypeDelegate<Board> m_co_shapeMover;
  void co_shapeMover();
};


#endif