#pragma warning (disable : 4503)

#include "HexGrid.h"
#include "Misc/GameMath.h"


int dirsYOdd[6][2] = 
{
  {1, -1}, // upRight
  {1, 0}, // Right
  {1, 1}, // downRight
  {0, 1}, // DownLeft
  {-1, 0}, // Left
  {0, -1} // UpLeft
};

int dirsYEven[6][2] =
{
  {0, -1}, // upRight
  {1, 0}, // Right
  {0, 1}, // downRight
  {-1, 1}, // DownLeft
  {-1, 0}, // Left
  {-1, -1} // UpLeft
};

int travelDirs[6] = 
{
  RIGHT,
  DOWN_RIGHT,
  DOWN_LEFT,
  LEFT,
  UP_LEFT,
  UP_RIGHT
};

//template <typename Kind> Point HexGrid<Kind>::getCoord(int worldX, int worldY)
//{
//  worldX+=m_r;
//  worldY+=(m_b/2);
//
//// see gamedev.net - Coordinates in Hexagon-Based Tile Maps
//  int xSect = worldX / (2*m_r);
//  int ySect = worldY / (m_h + m_sideLength);
//
//
//  int xSectPixel = worldX % (2 * m_r);
//  int ySectPixel = worldY % (m_h + m_sideLength);
//
//  int arrayX;
//  int arrayY;
//
//  if ( (ySect & 1) == 0)
//  {
//    // sectType = A
//    arrayX = xSect;
//    arrayY = ySect;
//    
//    if (ySectPixel < ((xSectPixel * (-m_m)) + m_h ) )
//    {
//      // topLeft
//      arrayX--;
//      arrayY--;
//    }
//    else if (ySectPixel < ((xSectPixel * (m_m)) -m_h) )
//    {
//      // top Right
//      arrayY--;
//    }
//  }
//  else
//  {
//    // sectType = B
//    if (xSectPixel >= m_r)
//    {
//      if (ySectPixel < ( (xSectPixel * (-m_m)) + (2*m_h) ))
//      {
//        arrayX = xSect;// - 1;
//        arrayY = ySect - 1;
//      }
//      else
//      {
//        arrayX = xSect;
//        arrayY = ySect;
//      }
//    }
//    else
//    {
//      if (ySectPixel < (xSectPixel * (m_m)) )
//      {
//        arrayY = ySect - 1;
//        arrayX = xSect;
//      }
//      else
//      {
//        arrayY = ySect;
//        arrayX = xSect - 1;
//      }
//    }
//  }  
//  return Point(arrayX, arrayY);
//}
//
//template <typename Kind> Point HexGrid<Kind>::worldCoord(int x, int y)
//{
//  Point ret;
///* even
//xpixel = xfield * 2 r 
//ypixel = yfield * ( h + s ) 
//*/
//  /* odd
//  xpixel = xfield * 2 r + r 
//ypixel = yfield * ( h + s ) 
//*/
//  ret.y = y*(m_h + m_s);
//
//  if (y%2 == 0)
//  {
//    ret.x = x*(2*m_r);
//  }
//  else
//  {
//    ret.x = (x*(2*m_r)) + m_r;
//  }
//  return ret;
//}
//
//
//template <typename Kind> list<Point> HexGrid<Kind>::neighborsInRadius(int x, int y, int r)
//{
//  list<Point> ret;
//  int retCount = 0;
//  int c = 0;
//  int yy=y;
//  int xx=x;
//
//  int startY = y;
//  int startX = x;
//
//  // find start block
//  for (c = 0; c<r-1; c++)
//  {
//    yy = y+c;
//    if ( (yy & 1) == 1)
//    {
//      // odd
//      startX += dirsYOdd[UP_LEFT][DIR_X];
//      startY += dirsYOdd[UP_LEFT][DIR_Y];
//    }
//    else
//    {
//      // even
//      startX += dirsYEven[UP_LEFT][DIR_X];
//      startY += dirsYEven[UP_LEFT][DIR_Y];
//    }
//  }
//
//  if (startX >= 0 && startY >= 0 && startX < m_width && startY < m_height)
//  {
//    //ret[retCount++] = m_map(startX, startY);
//    ret.push_back(Point(startX, startY));
//  }
//
//  int dirX;
//  int dirY;
//  int curX = startX;
//  int curY = startY;
//  for (c = 0; c < 6; c++)
//  {
//    for (int t=0; t<r-1; t++)
//    {
//      if ( (curY & 1) == 1)
//      {
//        dirX = dirsYOdd[travelDirs[c]][DIR_X];
//        dirY = dirsYOdd[travelDirs[c]][DIR_Y];
//      }
//      else
//      {
//        dirX = dirsYEven[travelDirs[c]][DIR_X];
//        dirY = dirsYEven[travelDirs[c]][DIR_Y];
//      }
//
//      curX+=dirX;
//      curY+=dirY;
//      if (curX >=0 && curY >=0 && curX < m_width && curY < m_height)
//      {
//        //ret[retCount++] = m_map(curX, curY);
//        ret.push_back(Point(curX, curY));
//      }
//    }
//  }
//  return ret;
//}