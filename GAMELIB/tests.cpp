#include "Misc/GameMath.h"
#include "Log.h"

void testOverlapping()
{
  { // 1
    Rect overlappee(2, 2, 4, 3);
    Rect overlapper(1, 1, 6, 6);
    bool t=Rect::checkOverlap(&overlapper, &overlappee);
    lassert(t);
    Rect overlap = Rect::findOverlap(&overlapper, &overlappee);
    lassert(overlap.x==0);
    lassert(overlap.y==0);
    lassert(overlap.w==4);
    lassert(overlap.h==3);
  }
  { // 2
    Rect overlappee(1, 1, 6, 6);
    Rect overlapper(2, 2, 4, 3);
    bool t=Rect::checkOverlap(&overlapper, &overlappee);
    lassert(t);
    Rect overlap = Rect::findOverlap(&overlapper, &overlappee);
    lassert(overlap.x==0);
    lassert(overlap.y==0);
    lassert(overlap.w==4);
    lassert(overlap.h==3);
  }

  { //3
    Rect overlappee(2, 3, 7, 7);
    Rect overlapper(4, 1, 2, 4);
    bool t=Rect::checkOverlap(&overlapper, &overlappee);
    lassert(t);
    Rect overlap = Rect::findOverlap(&overlapper, &overlappee);
    lassert(overlap.x==0);
    lassert(overlap.y==2);
    lassert(overlap.w==2);
    lassert(overlap.h==2);
  }

  { //4
    Rect overlappee(2, 3, 6, 6);
    Rect overlapper(6, 5, 4, 2);
    bool t=Rect::checkOverlap(&overlapper, &overlappee);
    Rect overlap = Rect::findOverlap(&overlapper, &overlappee);
    lassert(overlap.x==0);
    lassert(overlap.y==0);
    lassert(overlap.w==2);
    lassert(overlap.h==2);
  }


  { //5
    Rect overlappee(2, 3, 8, 6);
    Rect overlapper(5, 7, 2, 4);
    bool t=Rect::checkOverlap(&overlapper, &overlappee);
    Rect overlap = Rect::findOverlap(&overlapper, &overlappee);
    lassert(overlap.x==0);
    lassert(overlap.y==0);
    lassert(overlap.w==2);
    lassert(overlap.h==2);
  }

  { //6
    Rect overlappee(3, 3, 6, 5);
    Rect overlapper(2, 4, 3, 2);
    bool t=Rect::checkOverlap(&overlapper, &overlappee);
    Rect overlap = Rect::findOverlap(&overlapper, &overlappee);
    lassert(overlap.x==1);
    lassert(overlap.y==0);
    lassert(overlap.w==2);
    lassert(overlap.h==2);
  }

  { //7
    Rect overlappee(3, 2, 5, 5);
    Rect overlapper(2, 1, 3, 3);
    bool t=Rect::checkOverlap(&overlapper, &overlappee);
    Rect overlap = Rect::findOverlap(&overlapper, &overlappee);
    lassert(overlap.x==1);
    lassert(overlap.y==1);
    lassert(overlap.w==2);
    lassert(overlap.h==2);
  }

  { //8
    Rect overlappee(3, 2, 5, 5);
    Rect overlapper(7, 1, 3, 3);
    bool t=Rect::checkOverlap(&overlapper, &overlappee);
    Rect overlap = Rect::findOverlap(&overlapper, &overlappee);
    lassert(overlap.x==0);
    lassert(overlap.y==1);
    lassert(overlap.w==1);
    lassert(overlap.h==2);
  }

  { //9
    Rect overlappee(2, 1, 4, 5);
    Rect overlapper(4, 4, 4, 4);
    bool t=Rect::checkOverlap(&overlapper, &overlappee);
    Rect overlap = Rect::findOverlap(&overlapper, &overlappee);
    lassert(overlap.x==0);
    lassert(overlap.y==0);
    lassert(overlap.w==2);
    lassert(overlap.h==2);
  }

  { //10
    Rect overlappee(4, 1, 4, 4);
    Rect overlapper(3, 4, 4, 3);
    bool t=Rect::checkOverlap(&overlapper, &overlappee);
    Rect overlap = Rect::findOverlap(&overlapper, &overlappee);
    lassert(overlap.x==1);
    lassert(overlap.y==0);
    lassert(overlap.w==3);
    lassert(overlap.h==1);
  }

  { //11
    Rect overlappee(3, 3, 6, 4);
    Rect overlapper(5, 2, 2, 8);
    bool t=Rect::checkOverlap(&overlapper, &overlappee);
    Rect overlap = Rect::findOverlap(&overlapper, &overlappee);
    lassert(overlap.x==0);
    lassert(overlap.y==1);
    lassert(overlap.w==2);
    lassert(overlap.h==4);
  }

  { //12
    Rect overlappee(3, 1, 4, 6);
    Rect overlapper(1, 3, 9, 2);
    bool t=Rect::checkOverlap(&overlapper, &overlappee);
    Rect overlap = Rect::findOverlap(&overlapper, &overlappee);
    lassert(overlap.x==2);
    lassert(overlap.y==0);
    lassert(overlap.w==4);
    lassert(overlap.h==2);
  }

  { // 13
    Rect overlappee(3, 2, 4, 4);
    Rect overlapper(1, 1, 9, 2);
    bool t=Rect::checkOverlap(&overlapper, &overlappee);
    Rect overlap = Rect::findOverlap(&overlapper, &overlappee);
    lassert(overlap.x==2);
    lassert(overlap.y==1);
    lassert(overlap.w==4);
    lassert(overlap.h==1);
  }
  { // 14
    Rect overlappee(3, 2, 4, 4);
    Rect overlapper(2, 5, 7, 2);
    bool t=Rect::checkOverlap(&overlapper, &overlappee);
    Rect overlap = Rect::findOverlap(&overlapper, &overlappee);
    lassert(overlap.x==1);
    lassert(overlap.y==0);
    lassert(overlap.w==4);
    lassert(overlap.h==1);
  }
  { //15
    Rect overlappee(3, 2, 3, 3);
    Rect overlapper(2, 1, 2, 5);
    bool t=Rect::checkOverlap(&overlapper, &overlappee);
    Rect overlap = Rect::findOverlap(&overlapper, &overlappee);
    lassert(overlap.x==1);
    lassert(overlap.y==1);
    lassert(overlap.w==1);
    lassert(overlap.h==3);
  }
  { //16
    Rect overlappee(2, 2, 3, 4);
    Rect overlapper(3, 1, 3, 8);
    bool t=Rect::checkOverlap(&overlapper, &overlappee);
    Rect overlap = Rect::findOverlap(&overlapper, &overlappee);
    lassert(overlap.x==0);
    lassert(overlap.y==1);
    lassert(overlap.w==2);
    lassert(overlap.h==4);
  }
}