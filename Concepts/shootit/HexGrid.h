#ifndef HexGrid_h
#define HexGrid_h

const int MAX_MAPSIZE = 450/15;

#include "Misc/GameMath.h"
#include <list>
#include <map>
using namespace std;

enum
{
  UP_RIGHT = 0,
  RIGHT,
  DOWN_RIGHT,
  DOWN_LEFT,
  LEFT,
  UP_LEFT
};

enum
{
  DIR_X = 0,
  DIR_Y = 1
};

extern int dirsYOdd[6][2];
extern int dirsYEven[6][2];
extern int travelDirs[6];

template <typename Kind>
class HexGrid
{
public:
  HexGrid(int sideLength, int w, int h):
  m_width(0),
  m_height(0),
  m_sideLength(sideLength),
  m_worldOffset(0, 0)
  {
    m_h = sintable[30] * sideLength;
    m_r = costable[30] * sideLength;
    m_b = sideLength + (2 * m_h);
    m_a = 2 * m_r;
    m_m = (float)m_h / (float)m_r;

    m_width = w;
    m_height = h;
    m_map = new Kind[h*w];
  }

  void setWorldOffset(Point o)
  {
    m_worldOffset = o;
  }

  Point getCoord(int worldX, int worldY)
  {
    worldX-=m_worldOffset.x;
    worldY-=m_worldOffset.y;
    worldX+=m_r;
    worldY+=(m_b/2);
    
    // see gamedev.net - Coordinates in Hexagon-Based Tile Maps
    int xSect = worldX / (2*m_r);
    int ySect = worldY / (m_h + m_sideLength);
    
    
    int xSectPixel = worldX % (2 * m_r);
    int ySectPixel = worldY % (m_h + m_sideLength);
    
    int arrayX;
    int arrayY;
    
    if ( (ySect & 1) == 0)
    {
      // sectType = A
      arrayX = xSect;
      arrayY = ySect;
      
      if (ySectPixel < ((xSectPixel * (-m_m)) + m_h ) )
      {
        // topLeft
        arrayX--;
        arrayY--;
      }
      else if (ySectPixel < ((xSectPixel * (m_m)) -m_h) )
      {
        // top Right
        arrayY--;
      }
    }
    else
    {
      // sectType = B
      if (xSectPixel >= m_r)
      {
        if (ySectPixel < ( (xSectPixel * (-m_m)) + (2*m_h) ))
        {
          arrayX = xSect;// - 1;
          arrayY = ySect - 1;
        }
        else
        {
          arrayX = xSect;
          arrayY = ySect;
        }
      }
      else
      {
        if (ySectPixel < (xSectPixel * (m_m)) )
        {
          arrayY = ySect - 1;
          arrayX = xSect;
        }
        else
        {
          arrayY = ySect;
          arrayX = xSect - 1;
        }
      }
    }  
    return Point(arrayX, arrayY);
  }

  
  Point worldCoord(int x, int y)
  {
    Point ret;
    /* even
    xpixel = xfield * 2 r 
    ypixel = yfield * ( h + s ) 
    */
    /* odd
    xpixel = xfield * 2 r + r 
    ypixel = yfield * ( h + s ) 
    */
    ret.y = y*(m_h + m_sideLength);
    
    if (y%2 == 0)
    {
      ret.x = x*(2*m_r);
    }
    else
    {
      ret.x = (x*(2*m_r)) + m_r;
    }
    ret.x+=m_worldOffset.x;
    ret.y+=m_worldOffset.y;
    return ret;
  }


  list<Point> getNeighbors(int x, int y) { return neighborsInRadius(x, y, 2); }
  
  int getPixelWidth() { return (m_width-1)*m_a; }
  int getPixelHeight() { return (m_height-1)*(m_sideLength + m_h); }
  
  
  Kind getOccupant(int x, int y)
  {
    return m_map[(y*m_width) + x];
  }
  
  void setOccupant(int x, int y, Kind o)
  {
    m_map[(y*m_width) + x] = o;
  }
  
  //////////////////////////
  // Neighbors
  //////////////////////////
  list<Point> neighborsInRadius(int x, int y, int r)
  {
    list<Point> ret;
    int retCount = 0;
    int c = 0;
    int yy=y;
    int xx=x;
    
    int startY = y;
    int startX = x;
    
    // find start block
    for (c = 0; c<r-1; c++)
    {
      yy = y+c;
      if ( (yy & 1) == 1)
      {
        // odd
        startX += dirsYOdd[UP_LEFT][DIR_X];
        startY += dirsYOdd[UP_LEFT][DIR_Y];
      }
      else
      {
        // even
        startX += dirsYEven[UP_LEFT][DIR_X];
        startY += dirsYEven[UP_LEFT][DIR_Y];
      }
    }
    
    if (startX >= 0 && startY >= 0 && startX < m_width && startY < m_height)
    {
      //ret[retCount++] = m_map(startX, startY);
      ret.push_back(Point(startX, startY));
    }
    
    int dirX;
    int dirY;
    int curX = startX;
    int curY = startY;
    for (c = 0; c < 6; c++)
    {
      for (int t=0; t<r-1; t++)
      {
        if ( (curY & 1) == 1)
        {
          dirX = dirsYOdd[travelDirs[c]][DIR_X];
          dirY = dirsYOdd[travelDirs[c]][DIR_Y];
        }
        else
        {
          dirX = dirsYEven[travelDirs[c]][DIR_X];
          dirY = dirsYEven[travelDirs[c]][DIR_Y];
        }
        
        curX+=dirX;
        curY+=dirY;
        if (curX >=0 && curY >=0 && curX < m_width && curY < m_height)
        {
          //ret[retCount++] = m_map(curX, curY);
          ret.push_back(Point(curX, curY));
        }
      }
    }
    return ret;
  }


private:
  int m_width; // in tiles
  int m_height; // in tiles
  int m_r;
  int m_a;
  int m_b;
  int m_h;
  float m_m;
  int m_sideLength;

  Point m_worldOffset;
  

  //map<int, map<int, Kind> > m_map;
  Kind* m_map;
};

#endif