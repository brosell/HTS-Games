#ifndef _GraphicPrimitives_h
#define _GraphicPrimitives_h

#include <float.h>
#include <math.h>
#include <windows.h>
#include "SDL.h"

#include <string>


const int bTOP = 1;
const int bBOTTOM = 2;
const int bRIGHT = 4;
const int bLEFT = 8;


class Point
{
public:
  Point(int x, int y): x(x), y(y), shortest(FLT_MAX) {}
  Point(): x(0), y(0), shortest(FLT_MAX) {}
  int x;
  int y;
  
  float distanceTo(Point& p);
  bool isShortestDistance(Point& p);

private:
  float shortest;
};

inline bool operator == (const Point& p1, const Point& p2)
{
  return (p1.x == p2.x && p1.y == p2.y);
}

class FPoint
{
public:
  FPoint(float x=0, float y=0): x(x), y(y) {}
  float x;
  float y;

  float distanceTo(FPoint& p);
  
  static FPoint translate(float x, float y)
  {
    FPoint ret;
    ret.x = (((x/640)*2) - 1);
    ret.y = -(((y/480)*1.5) - .75);
    return ret;
  }
};

inline bool operator == (const FPoint& p1, const FPoint& p2)
{
  return (p1.x == p2.x && p1.y == p2.y);
}


struct Rect
{
  Rect(int x, int y, int w, int h): x(x), y(y), w(w), h(h) {}
  Rect() {}
  Rect(const Rect& other)
  {
    x=other.x;
    y=other.y;
    w=other.w;
    h=other.h;
  }
  int x;
  int y;
  int w;
  int h;

  bool containsPoint(Point& p)
  {
    return ( (p.x >= x) && 
             (p.x < x+w) &&
             (p.y >= y) &&
             (p.y < y+h) );
  }

  operator SDL_Rect*()
  {
    m_sdl.x = x;
    m_sdl.y = y;
    m_sdl.w = w;
    m_sdl.h = h;
    return &m_sdl;
  }

  static bool checkOverlap(Rect* r1, Rect* r2);
  
  
  // returns the portion of overlapper that overlaps into overlappee
  static Rect findOverlap(Rect* overlapper, Rect* overlappee);
  static int impactSide(Rect* hitter, Rect* hittee);
  static Rect parseRect(std::string strRect);

private:
  SDL_Rect m_sdl;
};

inline bool operator == (const Rect& r1, const Rect& r2)
{
  return ( (r1.x == r2.x) &&
       (r1.y == r2.y) &&
       (r1.w == r2.w) &&
       (r1.h == r2.h) );
}
  

inline int nextPowerOf2(int x, int max = pow(2, 11))
{
  int p2 = 1;
  while (p2 < x && p2 <= max)
  {
    p2 *= 2;
  }
  return p2;
}

inline int previousPowerOf2(int x, int max)
{
  int p=nextPowerOf2(x, max) ;
  if (p!=1 && p!=x)
  {
    p = p / 2;
  }

  return p;
}

inline void planeFromPoints(double x1, double y1, double z1,
                     double x2, double y2, double z2,
                     double x3, double y3, double z3,
                     double& A, double& B, double& C, double& D)
{
  A = (y1 * (z2 - z3)) + (y2 * (z3 - z1)) + (y3 * (z1 - z2));
  B = (z1 * (x2 - x3)) + (z2 * (x3 - x1)) + (z3 * (x1 - x2));
  C = (x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2));
  //- 
  D = (x1 * (y2 * z3 - y3 * z2) + x2 * (y3 * z1 - y1 * z3) + x3 * (y1 * z2 - y2 * z1));
}


#endif

