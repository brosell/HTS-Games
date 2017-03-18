#ifndef Quadrant_h
#define Quadrant_h

#include "BR_Game.h"
/**
The Quadrant class represents one of four quadrant or sections
of the board. Each quadrant is 29 blocks wide at the "top" and
11 blocks wide at the "bottom". Each is 10 blocks "high"
like so:<p>
<textarea>
OOOOOOOOOOOOOOOOOOOOOOOOOOOOO
 OOOOOOOOOOOOOOOOOOOOOOOOOOO
  OOOOOOOOOOOOOOOOOOOOOOOOO
   OOOOOOOOOOOOOOOOOOOOOOO
    OOOOOOOOOOOOOOOOOOOOO
     OOOOOOOOOOOOOOOOOOO
      OOOOOOOOOOOOOOOOO
       OOOOOOOOOOOOOOO
        OOOOOOOOOOOOO
         OOOOOOOOOOO
</textarea>

  to find the width of any row (zero based row index):
  <pre> width = 29 - (rowNum*2) </pre>
  and start offset
  <pre> startOffset = rowNum </pre>
  That means the first legal spot on row is (x=row, y=row)
  and the last legal spot is <pre> startOffset+width </pre><p>
  
    This class will need to be able to translate its coords when 
  oriented differently (just for drawing, all other operations 
  will act as if we are upside up) <p>
  
    The Quadrant is responseable for shifting any balls down...
*/

enum Orientation
{
  OR_UNDEF,
  OR_TOP,
  OR_RIGHT,
  OR_BOTTOM,
  OR_LEFT
};
class Quadrant
{
public:
  Quadrant(Orientation orientation = OR_UNDEF);

  /** temp */
  void setOrientation(Orientation o) { m_orientation = o; }

  void draw(Display* display);

  /**
  @return true is x, y is valid.
  */
  bool validCoord(int x, int y);

  /**
  set the spot to be a block
  @return true if success or false if out of range or occupied
  */
  bool setBlock(int x, int y, int b);
  /**
  returns the block at (x,y) or null if no block or x,y is out of range
  */
  int getBlock(int x, int y);

  Point getScreenPoint(int x, int y);

  bool isScreenCoordHere(int x, int y);

  /**
  clears out the quadrant for a new game or level
  */
  void clear();

  int widthAtRow(int r)
  {
    return (29 - (r*2));
  }
  int startColumnForRow(int r)
  {
    return r;
  }
  int endColumnForRow(int r)
  {
    return r + (widthAtRow(r) - 1);
  }

  Point getNeighborToLeft(Point p);
  Point getNeighborToRight(Point p);

protected:
  
private:
  int m_blocks[29][10];

  // 0 top, 1 right, 2 bottom, 3 left
  Orientation m_orientation;

  Skin* m_ball;

};


#endif