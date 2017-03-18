#pragma warning (disable : 4786 4503 4530)
#include "CollisionBitMask.h"
#include <memory.h>
#include "malloc.h"
#include "GameMath.h"

CollisionBitMask::CollisionBitMask(const void* sourcePixels, int w, int h):
m_width(w),
m_height(h)
{
  const char* pixels = (const char*)sourcePixels;
  m_bits = new char[m_width*m_height];
  for (int y=0; y<m_height; y++)
  {
//    printf("\n");
    for (int x=0; x<m_width; x++)
    {
      int pixelOffset = x*4+3; // we only want the alpha val from the 32 bit ARGB value
      m_bits[y*m_width + x] = (pixels[y*m_width*4 + pixelOffset]==0?0:0xff);
//      char t = m_bits[y*m_width + x]==0?' ':'X';
//      printf("%c", t);
    }
  }
}


CollisionBitMask::~CollisionBitMask()
{
  delete [] m_bits;
}

 
bool testCollision(const CollisionBitMask* ent1, int ent1x, int ent1y, const CollisionBitMask* ent2, int ent2x, int ent2y, Point& loc1, Point& loc2)
{
  /* 
    this can be optimized. it should only need to work with the 
    overlapped portion instead of the whole thing
    */

  Rect r1(ent1x, ent1y, ent1->getWidth(), ent1->getHeight());
  Rect r2(ent2x, ent2y, ent2->getWidth(), ent2->getHeight());

  if (Rect::checkOverlap(&r1, &r2) == false)
  {
    return false;
  }

  // ok the rects overlap, now we have to see if the bits overlap



  // first the bounding box and offset coords
  Rect boundingBox;
  int ent1XOffset, ent1YOffset;
  int ent2XOffset, ent2YOffset;

  if (r1.x <= r2.x)
  {
    boundingBox.x = r1.x;
    boundingBox.w = r1.w + r2.w; //(r2.x - r1.x) + r2.w;

    ent1XOffset = 0;
    ent2XOffset = r2.x - r1.x;
  }
  else
  {
    boundingBox.x = r2.x;
    boundingBox.w = r1.w + r2.w; // (r1.x - r2.x) + r1.w;
    
    ent1XOffset = r1.x - r2.x;
    ent2XOffset = 0;
  }

  if (r1.y <= r2.y)
  {
    boundingBox.y = r1.y;
    boundingBox.h = r1.h + r2.h; // (r2.y - r1.y) + r2.h;

    ent1YOffset = 0;
    ent2YOffset = r2.y - r1.y;
  }
  else
  {
    boundingBox.y = r2.y;
    boundingBox.h = r1.h + r2.h; // (r1.y - r2.y) + r1.h;

    ent1YOffset = r1.y - r2.y;
    ent2YOffset = 0;
  }

  // now create a scrath area
  char* dest = new char[boundingBox.w * boundingBox.h];
  memset(dest, 0, boundingBox.w*boundingBox.h);

  int sx, sy;
  int dx, dy;
  const char* bits;
  bool collision = false;
  
  // "draw" first
  bits = ent1->getBits();
  for (dy=ent1YOffset, sy=0; dy<ent1YOffset+r1.h; dy++, sy++)
  {
    for (dx=ent1XOffset, sx=0; dx<ent1XOffset+r1.w; dx++, sx++)
    {
      dest[dy*boundingBox.w + dx] = bits[sy*r1.w + sx];
    }
  }

    // "draw" second
  bits = ent2->getBits();
  for (dy=ent2YOffset, sy=0; dy<ent2YOffset+r2.h && collision == false; dy++, sy++)
  {
    for (dx=ent2XOffset, sx=0; dx<ent2XOffset+r2.w && collision == false; dx++, sx++)
    {
      int v=dest[dy*boundingBox.w + dx] ;
      if (v != 0 && bits[sy*r2.w + sx] != 0)
      {
        loc1.x = dx-ent1XOffset;
        loc1.y = dy-ent1YOffset;

        loc2.x = sx;
        loc2.y = sy;

        collision = true;
      }
      else
      {
        dest[dy*boundingBox.w + dx] = bits[sy*r2.w + sx];
      }
    }
  }



  delete [] dest;
  return collision;
}

bool CollisionBitMask::isPointCollision(int x, int y) const
{
  return (m_bits[y*m_width + x] != 0);
}