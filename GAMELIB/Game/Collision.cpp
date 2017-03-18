//#include "Collision.h"
//#include "Misc/GameMath.h"

//Collision::Collision(Thing& hitter, Thing& hittee, bool useProportionalSides)
//: m_hitter(hitter), m_hittee(hittee), m_useProportionalSides(useProportionalSides)
//{
//  int hitterX=hitter.getX();
//  int hitterY=hitter.getY();
//  int hitterWidth=hitter.getWidth();
//  int hitterHeight=hitter.getHeight();
//
//  int hitteeX=hittee.getX();
//  int hitteeY=hittee.getY();
//  int hitteeWidth=hittee.getWidth();
//  int hitteeHeight=hittee.getHeight();
//
//  bool useProportionalTopAndBottom = false;
//  bool useProportionalRightAndLeft = false;
//  
//  if (hitteeWidth > hitteeHeight && m_useProportionalSides)
//  {
//    useProportionalTopAndBottom = true;
//  }
//  else if (hitteeWidth < hitteeHeight && m_useProportionalSides)
//  {
//    useProportionalRightAndLeft = true;
//  }
//
//
//  Point hitterCenter;
//  hitterCenter.x = hitterX + (hitterWidth * 0.5);
//  hitterCenter.y = hitterY + (hitterHeight * 0.5);
//
//
////// hittee TOP
//  Point hitteeTop;
//  hitteeTop.x = hitteeX + (hitteeWidth * 0.5);
//  hitteeTop.y = hitteeY;
//
//  Point hitteeTopRight;
//  hitteeTopRight.x = (hitteeX + hitteeWidth) - (hitteeHeight * 0.5);
//  hitteeTopRight.y = hitteeY;
//
//  Point hitteeTopLeft;
//  hitteeTopLeft.x = hitteeX + (hitteeHeight * 0.5);
//  hitteeTopLeft.y = hitteeY;
//
//
////// Hittee BOTTOM
//  Point hitteeBottom;
//  hitteeBottom.x = hitteeX + (hitteeWidth * 0.5);
//  hitteeBottom.y = hitteeY + hitteeHeight;
//
//  Point hitteeBottomRight;
//  hitteeBottomRight.x = (hitteeX + hitteeWidth) - (hitteeHeight * 0.5);
//  hitteeBottomRight.y = hitteeY + hitteeHeight;
//
//  Point hitteeBottomLeft;
//  hitteeBottomLeft.x = hitteeX + (hitteeHeight * 0.5);
//  hitteeBottomLeft.y = hitteeY + hitteeHeight;
//
//
////// Hittee RIGHT
//  Point hitteeRight;
//  hitteeRight.x = hitteeX + hitteeWidth;
//  hitteeRight.y = hitteeY + (hitteeHeight * 0.5);
//
//  Point hitteeRightTop;
//  hitteeRightTop.x = hitteeX + hitteeWidth;
//  hitteeRightTop.y = hitteeY + (hitteeWidth * 0.5);
//
//  Point hitteeRightBottom;
//  hitteeRightBottom.x = hitteeX + hitteeWidth;
//  hitteeRightBottom.y = hitteeY + hitteeWidth - (hitteeHeight * 0.5);
//
////// hittee LEFT
//  Point hitteeLeft;
//  hitteeLeft.x = hitteeX;
//  hitteeLeft.y = hitteeY + (hitteeHeight * 0.5);
//
//  Point hitteeLeftTop;
//  hitteeLeftTop.x = hitteeX;
//  hitteeLeftTop.y = hitteeY + (hitteeWidth * 0.5);
//
//  Point hitteeLeftBottom;
//  hitteeLeftBottom.x = hitteeX;
//  hitteeLeftBottom.y = hitteeY + hitteeWidth - (hitteeHeight * 0.5);
//
//  Side whichOne;
//
//  //// TOP
//  if (hitterCenter.isShortestDistance(hitteeTop))
//  {
//    whichOne = TOP;
//  }
//  if (useProportionalTopAndBottom)
//  {
//    if (hitterCenter.isShortestDistance(hitteeTopRight))
//    {
//      whichOne = TOP;
//    }
//    if (hitterCenter.isShortestDistance(hitteeTopLeft))
//    {
//      whichOne = TOP;
//    }
//  }
//
//
//  //// BOTTOM
//  if (hitterCenter.isShortestDistance(hitteeBottom))
//  {
//    whichOne = BOTTOM;
//  }
//  if (useProportionalTopAndBottom)
//  {
//    if (hitterCenter.isShortestDistance(hitteeBottomRight))
//    {
//      whichOne = BOTTOM;
//    }
//    if (hitterCenter.isShortestDistance(hitteeBottomLeft))
//    {
//      whichOne = BOTTOM;
//    }
//  }
//
//  //// RIGHT
//  if (hitterCenter.isShortestDistance(hitteeRight))
//  {
//    whichOne = RIGHT;
//  }
//  if (useProportionalRightAndLeft)
//  {
//    if (hitterCenter.isShortestDistance(hitteeRightTop))
//    {
//      whichOne = RIGHT;
//    }
//    if (hitterCenter.isShortestDistance(hitteeRightBottom))
//    {
//      whichOne = RIGHT;
//    }
//  }
//
//  //// LEFT
//  if (hitterCenter.isShortestDistance(hitteeLeft))
//  {
//    whichOne = LEFT;
//  }
//  if (useProportionalRightAndLeft)
//  {
//    if (hitterCenter.isShortestDistance(hitteeLeftTop))
//    {
//      whichOne = LEFT;
//    }
//    if (hitterCenter.isShortestDistance(hitteeLeftBottom))
//    {
//      whichOne = LEFT;
//    }
//  }
//
//
//  m_hitteeSide = whichOne;
//}
