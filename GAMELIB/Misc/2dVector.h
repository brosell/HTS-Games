#ifndef Vector_h
#define Vector_h

#include "GameMath.h"

/////////////////////
//  Vector
/////////////////////
class Vector
{
public:
  Vector(float x=0.0, float y=0.0, float z=0.0):x(x), y(y), z(z) { }

  Vector(Line l) { x = l.p2.x - l.p1.x; y = l.p2.y - l.p1.y; z = 0; }
  static Vector createFromAngle(int angle, float length)
  {
    Vector v;
    angle-=90;
    if (angle < 0)
    {
      angle = 360 + angle;
    }

    v.x = costable[angle]*length;
    v.y = sintable[angle]*length;
    v.z = 0;
    return v;
  }

  float x;
  float y;
  float z;

  Vector add(Vector& other)
  {
    Vector ret;
    ret.x = x+other.x;
    ret.y = y+other.y;
    ret.z = z+other.z;
    return ret;
  }

  Vector subtract(Vector& other)
  {
    Vector ret;
    ret.x = x-other.x;
    ret.y = y-other.y;
    ret.z = z-other.z;
    return ret;
  }

  Vector divide(float div)
  {
    Vector ret;
    ret.x = x/div;
    ret.y = y/div;
    ret.z = z/div;
    return ret;
  }

  Vector multiply(float mult)
  {
    Vector ret;
    ret.x = x*mult;
    ret.y = y*mult;
    ret.z = z*mult;
    return ret;
  }

  Vector normalize()
  {
    Vector ret;
    float t = 1/length();
    ret.x = x*t;
    ret.y = y*t;
    ret.z = z*t;
    return ret;
  }

  Vector parallel(float dist);
  
  Vector normal()
  {
    Vector N;
    N.x = -(y);
    N.y = (x);
    N = N.normalize();
    return N;
  }


  float anglef()
  {
    float h = sqrtf( (x*x) + (y*y) );
    float s = (y / h);
    float as = asin(s); // radians
    float angle = (180/BR_PI * as) + 90;
    
    if (x < 0)
    {
      angle = 180 + (180 - angle);
    }
    return angle;
  }

  int anglei()
  {
    return (int)anglef();
  }

  float dotProduct(Vector& other)
  {
    return (x*other.x) + (y*other.y) + (z*other.z);
  }
  
  Vector crossProduct(Vector &other)
  {
    Vector ret;
    ret.x = ( y * other.z ) - ( z * other.y );
    ret.y = ( z * other.x ) - ( x * other.z );
    ret.z = ( x * other.y ) - ( y * other.x );
    return ret;
  }

  Vector negate()
  {
    Vector ret;
    ret.x = -x;
    ret.y = -y;
    ret.z = -z;
    return ret;
  }

  float length()
  {
    return sqrtf((x*x) + (y*y));
  }

  float lengthSquared()
  {
    return (x*x) + (y*y);
  }

};

inline bool operator == (const Vector& v1, const Vector& v2)
{
  return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}


Vector reflection(Vector A, Vector P);
Vector reflection(Vector A, Line l);

Vector normal(Line l);

#endif