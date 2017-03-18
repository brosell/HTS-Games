#include "SDL.h"
#include "GraphicPrimitives.h"
#include "Log.h"
#include "StringTokenizer.h"

float Point::distanceTo(Point& p)
{
  long aSquared=(p.x-x)*(p.x-x);
  long bSquared=(p.y-y)*(p.y-y);
  
  return (float)sqrt(aSquared+bSquared);
}

float FPoint::distanceTo(FPoint& p)
{
  float aSquared=(p.x-x)*(p.x-x);
  float bSquared=(p.y-y)*(p.y-y);
  
  return (float)sqrt(aSquared+bSquared);
}


bool Point::isShortestDistance(Point& p)
{
  float dist=distanceTo(p);
  if (dist < shortest)
  {
    shortest = dist;
    return true;
  }
  return false;
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


/*

A = y1 (z2 - z3) + y2 (z3 - z1) + y3 (z1 - z2) 
B = z1 (x2 - x3) + z2 (x3 - x1) + z3 (x1 - x2) 
C = x1 (y2 - y3) + x2 (y3 - y1) + x3 (y1 - y2) 
- D = x1 (y2 z3 - y3 z2) + x2 (y3 z1 - y1 z3) + x3 (y1 z2 - y2 z1)

*/

//void planeFromPoints(double x1, double y1, double z1,
//                     double x2, double y2, double z2,
//                     double x3, double y3, double z3,
//                     double& A, double& B, double& C, double& D)
//{
//A = (y1 * (z2 - z3)) + (y2 * (z3 - z1)) + (y3 * (z1 - z2));
//B = (z1 * (x2 - x3)) + (z2 * (x3 - x1)) + (z3 * (x1 - x2));
//C = (x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2));
////- 
//D = - (x1 * (y2 * z3 - y3 * z2) + x2 * (y3 * z1 - y1 * z3) + x3 * (y1 * z2 - y2 * z1));
//}
