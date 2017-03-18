#ifndef CollisionBitMask_h
#define CollisionBitMask_h

#include "GameMath.h"

/**
CollisionBitMask is used to test for collisions between objects based on 
their images
*/
class CollisionBitMask
{
public:
  /**
    Constructs a CollisionBitMask from pixel data
    @param sourcePixels 32bit alpha channeled pixels
    @param w the width of the image
    @param h the height of the image
    */
  CollisionBitMask(const void* sourcePixels, int w, int h);
  ~CollisionBitMask();

  /**
    return the array of bits
    */
  const char* getBits() const { return m_bits; }
  int getWidth() const { return m_width; }
  int getHeight() const { return m_height; }

  /**
    Tests whether a point colides with this mask
    */
  bool isPointCollision(int x, int y) const;

private:
  char* m_bits;
  int m_width;
  int m_height;
};

/**
  Test for collision between two CollisionBitMaks
  @param ent1 the first mask
  @param ent1x the world X position of ent 1
  @param ent1y the world y position or ent 1
  @param ent2 the second mask
  @param ent2x the world X position of ent 2
  @param ent2y the world y position or ent 2
  */
bool testCollision(const CollisionBitMask* ent1, int ent1x, int ent1y, 
                   const CollisionBitMask* ent2, int ent2x, int ent2y, 
                   Point& loc1, Point& loc2);

#endif