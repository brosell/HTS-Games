#ifndef _GameMath_h
#define _GameMath_h

#include <float.h>
#include <math.h>
#include <windows.h>
#include "SDL.h"

#include "Utils.h"
using namespace hts;

#include <string>
using namespace std;

extern float sintable[360];
extern float costable[360];

#define BR_PI 3.141592654

const int bTOP = 1;
const int bBOTTOM = 2;
const int bRIGHT = 4;
const int bLEFT = 8;

class Angle
{
public:
  Angle(int angle = 0): m_angle(angle) { }
  float toRadians()
  {
    return 0;
  }

  Angle& operator=(int a)
  {
    m_angle = 0;
    return (*this)+=a;
  }

  operator int() { return m_angle; }

  Angle& operator+=(int a) 
  { 
    m_angle+=a;
    if (m_angle > 359)
    {
      m_angle = m_angle-360;
    }
    if (m_angle < 0)
    {
      m_angle = 360 + m_angle;
    }
    return *this;
  }

  Angle& operator-=(int a)
  {
    return (*this)+=(-a);
  }

private:
  int m_angle;
};


/////////////////////
//  Point
/////////////////////
class FPoint;
class Point
{
public:
  Point(int x, int y): x(x), y(y), shortest(FLT_MAX) {}
  Point(): x(0), y(0), shortest(FLT_MAX) {}
  Point(const Point& other): x(other.x), y(other.y), shortest(other.shortest) { }
  Point(const FPoint& other);

  Point(string s);

  void rotate(Angle angle)
  {
    x = costable[(int)angle]*x - sintable[(int)angle]*y;
    y = sintable[(int)angle]*x + costable[(int)angle]*y;
  }


  int x;
  int y;
  
  float distanceTo(Point& p);
  int distanceToSquared(Point& p);
  bool isShortestDistance(Point& p);

private:
  float shortest;
};

inline bool operator == (const Point& p1, const Point& p2)
{
  return (p1.x == p2.x && p1.y == p2.y);
}

inline bool operator < (const Point& p1, const Point& p2)
{
  if (p1.x < p2.x)
  {
    return true;
  }
  if (p1.x == p2.x)
  {
    return p1.y < p2.y;
  }
  return false;
}

inline bool operator != (const Point& p1, const Point& p2)
{
  return (p1.x != p2.x || p1.y != p2.y);
}


/////////////////////
//  FPoint
/////////////////////

class FPoint
{
public:
  FPoint(float x=0, float y=0): x(x), y(y), shortest(FLT_MAX) {}
  FPoint(Point p):x(p.x), y(p.y), shortest(FLT_MAX) {}

  FPoint(string s);

  void rotate(Angle angle)
  {
    x = costable[(int)angle]*x - sintable[(int)angle]*y;
    y = sintable[(int)angle]*x + costable[(int)angle]*y;
  }

  float x;
  float y;

  float distanceTo(FPoint& p);
  float distanceToSquared(FPoint& p);
  

bool isShortestDistance(FPoint& p);

private:
  float shortest;

};

inline bool operator == (const FPoint& p1, const FPoint& p2)
{
  return (p1.x == p2.x && p1.y == p2.y);
}

inline bool operator != (const FPoint& p1, const FPoint& p2)
{
  return (p1.x != p2.x || p1.y != p2.y);
}


/////////////////////
//  Rect 
/////////////////////
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
  
/////////////////////
//  PowerOf2
/////////////////////

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


/////////////////////
//  Geometry
/////////////////////

inline int dirToChange(int angle1, int angle2)
{
  int ans1 = 0;

  int t=angle1;
  while (t != angle2)
  {
    t++;
    if (t>359)
    {
      t = 0;
    }
    ans1++;
    if (ans1 >= 180)
    {
      return -1;
    }
  }
  return 1;
}


inline 
void planeFromPoints(double x1, double y1, double z1,
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


///////////////////
/// LINES
///////////////////

class Line
{
public:
  Line(): p1(FPoint(0, 0)), p2(FPoint(0, 0)) { }
  Line(FPoint p1, FPoint p2): p1(p1), p2(p2) { }
  float length()
  {
    return sqrt(lengthSquared());
  }
  float lengthSquared()
  {
    return ((p1.x-p2.x)*(p1.x-p2.x)) + ((p1.y-p2.y)*(p1.y-p2.y));
  }

  FPoint middle()
  {
    FPoint ret;
    ret.x = p1.x + ((p2.x-p1.x)/2);
    ret.y = p1.y + ((p2.y-p1.y)/2);
    return ret;
  }

  FPoint p1;
  FPoint p2;
};

inline 
float inverse(float a)
{
  return (1/a);
}

inline
float getM(FPoint p1, FPoint p2)
{
  return (p1.y - p2.y) / (p1.x - p2.x);
}
inline
float getMx(FPoint p1, FPoint p2)
{
  return (p1.x - p2.x) / (p1.y - p2.y);
}
inline
float getB(FPoint lp1, FPoint lp2)
{
  float m = getM(lp1, lp2);
  return (lp1.y - (m * lp1.x));
}
inline
float getBx(FPoint lp1, FPoint lp2)
{
  float m = getMx(lp1, lp2);
  return (lp1.x - (m * lp1.y));
}



inline
bool areParallel(FPoint l1_1, FPoint l1_2, FPoint l2_1, FPoint l2_2)
{
  if (l1_1.x == l1_2.x && l2_1.x == l2_2.x)
  {
    return true;
  }

  // since they both arn't, then maybe one is and if so then thay arn't parallel
  if (l1_1.x == l1_2.x || l2_1.x == l2_2.x)
  {
    return false;
  }

  float m1 = getM(l1_1, l1_2);
  float m2 = getM(l2_1, l2_2);
  
  return m1==m2;
}

inline 
bool arePerpendicular(FPoint l1_1, FPoint l1_2, FPoint l2_1, FPoint l2_2)
{
  if (areParallel(l1_1, l1_2, l2_1, l2_2))
  {
    return false;
  }

  if (l1_1.x == l1_2.x)
  {
    // the first line is straight up and down
    float m2 = getM(l2_1, l2_2);
    return (m2 == 1 || m2 == -1);
  }
  else if (l2_1.x == l2_2.x)
  {
    float m1 = getM(l1_1, l1_2);
    return (m1 == 1 || m1 == -1);
  }

  // neither are up and down
  float m1 = getM(l1_1, l1_2);
  float m2 = getM(l2_1, l2_2);
  return (m1 * m2 == -1);
}


inline
bool linesIntersect(FPoint l1_1, FPoint l1_2, FPoint l2_1, FPoint l2_2, FPoint& ans)
{
  if (areParallel(l1_1, l1_2, l2_1, l2_2))
  {
    return false;
  }

  float m1 = getM(l1_1, l1_2);
  float m2 = getM(l2_1, l2_2);

  float b1 = (l1_1.y - (m1 * l1_1.x));
  float b2 = (l2_1.y - (m2 * l2_1.x));

  ans.x = (b2-b1) / (m1-m2);
  ans.y = (m1*ans.x) + b1;

  return true;
}

inline
bool couldPointOnLineSegment(Line l, FPoint p)
{
  return  ( (p.x >= hts::min(l.p1.x, l.p2.x)) &&
    (p.y >= hts::min(l.p1.y, l.p2.y)) &&
    (p.x <= hts::max(l.p1.x, l.p2.x)) &&
    (p.y <= hts::max(l.p1.y, l.p2.y))
       );
}

inline
bool doesLineIntersectRect(Line l, Rect r, FPoint& ans)
{
  FPoint A(r.x, r.y);
  FPoint B(r.x+r.w, r.y);
  FPoint C(r.x+r.w, r.y+r.h);
  FPoint D(r.x, r.y+r.h);
//  FPoint ans;

  if (linesIntersect(A, C, l.p1, l.p2, ans))
  {
    if (r.containsPoint(Point(ans.x, ans.y)) && couldPointOnLineSegment(l, ans))
    {
      return true;
    }
  }

  if (linesIntersect(B, D, l.p1, l.p2, ans))
  {
    if (r.containsPoint(Point(ans.x, ans.y)) && couldPointOnLineSegment(l, ans))
    {
      return true;
    }
  }
  return false;
}

float distToSegment(float px, float py, float X1, float Y1, float X2, float Y2);
float distToSegmentSquared(float px, float py, float X1, float Y1, float X2, float Y2);

inline float distToSegmentSquared(Point p, Line l) { return distToSegmentSquared(p.x, p.y, l.p1.x, l.p1.y, l.p2.x, l.p2.y); }
inline float distToSegment(Point p, Line l) { return distToSegment(p.x, p.y, l.p1.x, l.p1.y, l.p2.x, l.p2.y); }

inline
FPoint rotate(FPoint f, Angle angle)
{
  FPoint ret;
  ret.x = costable[(int)angle]*f.x - sintable[(int)angle]*f.y;
  ret.y = sintable[(int)angle]*f.x + costable[(int)angle]*f.y;
  return ret;
}


template <typename K> 
inline
K signOf(K v)
{
  return (v/abs(v));
}

#endif

