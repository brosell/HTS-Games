#ifndef Shape_h
#define Shape_h

#include "Misc/GameMath.h"
#include "CoroutineDelegates.h"
#include "BR_Game.h"

#include <list>
using namespace std;


#include "Quadrant.h"

/**
Shapes are the pieces that the player shifts around the board
trying to place.<p>
Each shape made up of four blocks aranged like this:
<pre>
xxxx

xx
 xx

 xx
xx
 
 x
xxx

xxx
  x

  x
xxx
</pre>
And can be rotated around a pivot.<p>

  Shapes are moved left and right by the mouse. It can cross the boundries
  to other quadrants.
*/
class Shape
{
public:
  Shape();
  ~Shape();

  void setPosition(int x, int y) { m_position = Point(x, y); }
  Point getPosition() { return m_position; }
  list<Point> getPositions(Point relativeTo = Point(-1, -1));

  void rotateLeft();
  void rotateRight();

  void draw(Display* display, Quadrant* quad);

  /**
  determins whether the shape in its current orientation can fit
  at the point requested
  */
  bool canShapeFit(Quadrant* quad, Point location = Point(-1, -1));

protected:
  /** 
  causes the Shapes blocks to become the quadrants blocks at the current location
  */
  void settle(Quadrant* quad);

  
private:
  int m_blocks[4][4];
  // used by the rotate functions
  int m_rotateBuffer[4][4];

  /* top left corner relative to the quadrant */
  Point m_position;

  Skin* m_ball;
};


#endif