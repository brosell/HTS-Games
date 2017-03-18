#pragma warning (disable : 4786 4503 4530)
#include "GameMath.h"
#include "Log.h"
#include "StringTokenizer.h"

float sintable[360];
float costable[360];


static class SINTABLEINITER
{
public:
  SINTABLEINITER()
  {
    float temp;
    for( int i = 0; i<360; i++ )
    {
      temp = ((float)(i)/180);
      
      temp *= BR_PI;
      
      costable[i] = (float)cos( temp );
      sintable[i] = (float)sin( temp );
    }
  }
} sinTableIniter;

Point::Point(string s):x(-1), y(-1)
{
  StringTokenizer st(s, ", ");
  if (st.countTokens() > 0)
  {
    x = atoi(st.nextToken());
  }
  if (st.countTokens() > 0)
  {
    y = atoi(st.nextToken());
  }
}

float Point::distanceTo(Point& p)
{
  long aSquared=(p.x-x)*(p.x-x);
  long bSquared=(p.y-y)*(p.y-y);
  
  return (float)sqrt(aSquared+bSquared);
}

int Point::distanceToSquared(Point& p)
{
  int aSquared=(p.x-x)*(p.x-x);
  int bSquared=(p.y-y)*(p.y-y);

  return aSquared + bSquared;
}

Point::Point(const FPoint& other)
{
  x = other.x;
  y = other.y;
}


FPoint::FPoint(string s):x(-1), y(-1)
{
  StringTokenizer st(s, ", ");
  if (st.countTokens() > 0)
  {
    x = atof(st.nextToken());
  }
  if (st.countTokens() > 0)
  {
    y = atof(st.nextToken());
  }
}

float FPoint::distanceTo(FPoint& p)
{
  float aSquared=(p.x-x)*(p.x-x);
  float bSquared=(p.y-y)*(p.y-y);
  
  return (float)sqrt(aSquared+bSquared);
}

float FPoint::distanceToSquared(FPoint& p)
{
  float aSquared=(p.x-x)*(p.x-x);
  float bSquared=(p.y-y)*(p.y-y);

  return aSquared + bSquared;
}


bool Point::isShortestDistance(Point& p)
{
  float aSquared=(p.x-x)*(p.x-x);
  float bSquared=(p.y-y)*(p.y-y);
  
  float dist=aSquared+bSquared;

  if (dist < shortest)
  {
    shortest = dist;
    return true;
  }
  return false;
}

bool FPoint::isShortestDistance(FPoint& p)
{
  float aSquared=(p.x-x)*(p.x-x);
  float bSquared=(p.y-y)*(p.y-y);
  
  float dist=aSquared+bSquared;
  if (dist < shortest)
  {
    shortest = dist;
    return true;
  }
  return false;
}

Rect::Rect(string rep)
{
  StringTokenizer st(rep, ", ()");
  if (st.hasMoreTokens())
  {
    x = atoi(st.nextToken());
  }
  if (st.hasMoreTokens())
  {
    y = atoi(st.nextToken());
  }
  if (st.hasMoreTokens())
  {
    w = atoi(st.nextToken());
  }
  if (st.hasMoreTokens())
  {
    h = atoi(st.nextToken());
  }
}

/*static*/ bool Rect::checkOverlap(Rect* r1, Rect* r2)
{
  int x=r1->x;
  int y=r1->y;
  int bx=(r1->x+r1->w);
  int by=(r1->y+r1->h);

  int ox=r2->x;
  int oy=r2->y;
  int obx=(r2->x+r2->w);
  int oby=(r2->y+r2->h);

  bool xOverlaps=((x <= ox && ox <= bx) || 
                  (x <= obx && obx <= bx) || 
                  (ox <= x && x <= obx) ||
                  (ox < bx && bx <= obx));

  
  bool yOverlaps=((y <= oy && oy <= by) || 
                  (y <= oby && oby <= by) || 
                  (oy <= y && y <= oby) ||
                  (oy < by && by <= oby));

  return (xOverlaps && yOverlaps);
}


/*static*/ Rect Rect::findOverlap(Rect* overlapper, Rect* overlappee)
{
  int overlapperX=overlapper->x;
  int overlapperY=overlapper->y;
  int overlapperBX=overlapper->x + overlapper->w;
  int overlapperBY=overlapper->y + overlapper->h;

  int overlappeeX=overlappee->x;
  int overlappeeY=overlappee->y;
  int overlappeeBX=overlappee->x + overlappee->w;
  int overlappeeBY=overlappee->y + overlappee->h;

  Rect ret(-1, -1, -1, -1);

  //3
  if (overlapperX  >= overlappeeX &&
      overlapperY  <= overlappeeY &&
      overlapperBX <= overlappeeBX &&
      overlapperBY <= overlappeeBY)
  {
    ret.x=0;
    ret.y=overlappeeY - overlapperY;
    ret.w=overlapper->w;
    ret.h=overlapperBY - overlappeeY;
    return ret;
  }

  //4
  if (overlapperX  >= overlappeeX &&
      overlapperY  >= overlappeeY &&
      overlapperBX >= overlappeeBX &&
      overlapperBY <= overlappeeBY)
  {
    ret.x=0;
    ret.y=0;
    ret.w=overlappeeBX - overlapperX;
    ret.h=overlapper->h;
    return ret;
  }

  //5
  if (overlapperX  >= overlappeeX &&
      overlapperY  >= overlappeeY &&
      overlapperBX <= overlappeeBX &&
      overlapperBY >= overlappeeBY)
  {
    ret.x=0;
    ret.y=0;
    ret.w=overlapper->w;
    ret.h=overlapperBY-overlappeeBY;
    return ret;
  }

  //6
  if (overlapperX  <= overlappeeX &&
      overlapperY  >= overlappeeY &&
      overlapperBX <= overlappeeBX &&
      overlapperBY <= overlappeeBY)
  {
    ret.x=overlappeeX - overlapperX;
    ret.y=0;
    ret.w=overlapperBX - overlappeeX;
    ret.h=overlapper->h;
    return ret;
  }

  //7
  if (overlapperX  <= overlappeeX &&
      overlapperY  <= overlappeeY &&
      overlapperBX <= overlappeeBX &&
      overlapperBY <= overlappeeBY)
  {
    ret.x=overlappeeX - overlapperX;
    ret.y=overlappeeY - overlapperY;
    ret.w=overlapperBX - overlappeeX;
    ret.h=overlapperBY - overlappeeY;
    return ret;
  }

  //8
  if (overlapperX  >= overlappeeX &&
      overlapperY  <= overlappeeY &&
      overlapperBX >= overlappeeBX &&
      overlapperBY <= overlappeeBY)
  {
    ret.x=0;
    ret.y=overlappeeY - overlapperY;
    ret.w=overlappeeBX - overlapperX;
    ret.h=overlapperBY - overlappeeY;
    return ret;
  }

  //9
  if (overlapperX  >= overlappeeX &&
      overlapperY  >= overlappeeY &&
      overlapperBX >= overlappeeBX &&
      overlapperBY >= overlappeeBY)
  {
    ret.x=0;
    ret.y=0;
    ret.w=overlappeeBX - overlapperX;
    ret.h=overlappeeBY - overlapperY;
    return ret;
  }
  //10
  if (overlapperX  <= overlappeeX &&
      overlapperY  >= overlappeeY &&
      overlapperBX <= overlappeeBX &&
      overlapperBY >= overlappeeBY)
  {
    ret.x=overlappeeX - overlapperX;
    ret.y=0;
    ret.w=overlapperBX - overlappeeX;
    ret.h=overlappeeBY - overlapperY;
    return ret;
  }
  /////////////////////////////////////

  //11
  if (overlapperX  >= overlappeeX &&
      overlapperY  <= overlappeeY &&
      overlapperBX <= overlappeeBX &&
      overlapperBY >= overlappeeBY)
  {
    ret.x=0;
    ret.y=overlappeeY - overlapperY;
    ret.w=overlapper->w;
    ret.h=overlappee->h;
    return ret;
  }

  //12
  if (overlapperX  <= overlappeeX &&
      overlapperY  >= overlappeeY &&
      overlapperBX >= overlappeeBX &&
      overlapperBY <= overlappeeBY)
  {
    ret.x=overlappeeX - overlapperX;
    ret.y=0;
    ret.w=overlappee->w;
    ret.h=overlapper->h;
    return ret;
  }

  //13 ok
  if (overlapperX  <= overlappeeX &&
      overlapperY  <= overlappeeY &&
      overlapperBX >= overlappeeBX &&
      overlapperBY <= overlappeeBY)
  {
    ret.x=overlappeeX - overlapperX;
    ret.y=overlappeeY - overlapperY;
    ret.w=overlappee->w;
    ret.h=overlapperBY - overlappeeY;
    return ret;
  }
  //14
  if (overlapperX  <= overlappeeX &&
      overlapperY  >= overlappeeY &&
      overlapperBX >= overlappeeBX &&
      overlapperBY >= overlappeeBY)
  {
    ret.x=overlappeeX - overlapperX;
    ret.y=0;
    ret.w=overlappee->w;
    ret.h=overlappeeBY - overlapperY;
    return ret;
  }
  //15
  if (overlapperX  <= overlappeeX &&
      overlapperY  <= overlappeeY &&
      overlapperBX <= overlappeeBX &&
      overlapperBY >= overlappeeBY)
  {
    ret.x=overlappeeX - overlapperX;
    ret.y=overlappeeY - overlapperY;
    ret.w=overlapperBX - overlappeeX;
    ret.h=overlappee->h;
    return ret;
  }
  //16 ok
  if (overlapperX  >= overlappeeX &&
      overlapperY  <= overlappeeY &&
      overlapperBX >= overlappeeBX &&
      overlapperBY >= overlappeeBY)
  {
    ret.x=0;
    ret.y=overlappeeY - overlapperY;
    ret.w=overlappeeBX - overlapperX;
    ret.h=overlappee->h;
    return ret;
  }

    //1
  if (overlapperX  <= overlappeeX && 
      overlapperY  <= overlappeeY &&
      overlapperBX >= overlappeeBX &&
      overlapperBY >= overlappeeBY)
  {
    ret.x=0;
    ret.y=0;
    ret.w=overlappee->w;
    ret.h=overlappee->h;
    return ret;
  }
  //2
  if (overlapperX  >= overlappeeX &&
      overlapperY  >= overlappeeY &&
      overlapperBX <= overlapperBX &&
      overlapperBY <= overlappeeBY)
  {
    ret.x=0;
    ret.y=0;
    ret.w=overlapper->w;
    ret.h=overlapper->h;
    return ret;
  }


  
  lassert(false);
  return ret;
}

int Rect::impactSide(Rect* hitter, Rect* hittee)
{
  int ret=0;
  int hitterX = hitter->x;
  int hitterBX = hitter->x + hitter->w;
  int hitterY = hitter->y;
  int hitterBY = hitter->y + hitter->h;

  int hitteeX = hittee->x;
  int hitteeBX = hittee->x + hittee->w;
  int hitteeY = hittee->y;
  int hitteeBY = hittee->y + hittee->h;


  if (hitterX <= hitteeX &&
      hitterBX >= hitteeX)
  {
    ret |= bLEFT;
  }

  if (hitterX <= hitteeBX &&
      hitterBX >= hitteeBX)
  {
    ret |= bRIGHT;
  }

  if (hitterY <= hitteeY &&
      hitterBY >= hitteeY)
  {
    ret |= bTOP;
  }
  
  if (hitterY <= hitteeBY &&
      hitterBY >= hitteeBY)
  {
    ret |= bBOTTOM;
  }

  return ret;
}

Rect Rect::parseRect(std::string strRect)
{
  Rect ret(-1, -1, -1, -1);
  StringTokenizer st(strRect.c_str(), ", \t\r\n");
  if (st.countTokens() == 4)
  {
    ret.x = atoi(st.nextToken().c_str());
    ret.y = atoi(st.nextToken().c_str());
    ret.w = atoi(st.nextToken().c_str());
    ret.h = atoi(st.nextToken().c_str());
  }
  return ret;
}


#include "2dVector.h"
float distToSegmentSquared(float x, float y, float x0, float y0, float x1, float y1)
{
  Point P(x, y);

    Vector v(x1-x0, y1-y0);
    Vector w(x-x0, y-y0);

    double c1 = w.dotProduct(v);
    if ( c1 <= 0 )
        return Point(x, y).distanceToSquared(Point(x0, y0));//d(P, S.P0);

    double c2 = v.dotProduct(v);
    if ( c2 <= c1 )
      return Point(x, y).distanceToSquared(Point(x1, y1));//d(P, S.P1);
//        return Point(x, y).distanceToSquared(Point(x0, y0));//d(P, S.P1);

    double b = c1 / c2;
    Vector bv=v.multiply(b);

    Point Pb(x0+bv.x, y0+bv.y);// = S.P0 + b * v;
    return P.distanceToSquared(Pb);
}

float distToSegment(float x, float y, float x0, float y0, float x1, float y1)
{
  return sqrt(distToSegmentSquared(x, y, x0, y0, x1, y1));
}

PointDist closestPoint(float x, float y, float x0, float y0, float x1, float y1)
{
  Point P(x, y);
  
  Vector v(x1-x0, y1-y0);
  Vector w(x-x0, y-y0);
  
  double c1 = w.dotProduct(v);
  if ( c1 <= 0 )
  {
    PointDist pd;
    pd.point = Point(x0, y0);
    pd.dist = Point(x, y).distanceTo(Point(x0, y0));
    return pd;
  }//    return Point(x, y).distanceToSquared(Point(x0, y0));//d(P, S.P0);
  
  double c2 = v.dotProduct(v);
  if ( c2 <= c1 )
  {
    PointDist pd;
    pd.point = Point(x1, y1);
    pd.dist = Point(x, y).distanceTo(Point(x1, y1));
    return pd;
  }//    return Point(x, y).distanceToSquared(Point(x1, y1));//d(P, S.P0);

//    return Point(x, y).distanceToSquared(Point(x0, y0));//d(P, S.P1);
  
  double b = c1 / c2;
  Vector bv=v.multiply(b);
  
  Point Pb(x0+bv.x, y0+bv.y);// = S.P0 + b * v;
  PointDist pd;
  pd.point = Pb;
  pd.dist = P.distanceTo(Pb);
  return pd;
  //return P.distanceToSquared(Pb);
  
}

