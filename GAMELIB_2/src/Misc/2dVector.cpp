
/* google for Bouncing on Angles in groups*/

#include "2dVector.h"

Vector reflection(Vector A, Line l)
{
  Vector P(l.p2.x - l.p1.x, l.p2.y - l.p1.y);
  return reflection(A, P);
}

Vector reflection(Vector A, Vector P)
{
  Vector N = P.normal();

  Vector B = N.multiply(2*(A.negate().dotProduct(N))).add(A);
  
  return B;
}

Vector normal(Line l)
{
  Vector P(l.p2.x - l.p1.x, l.p2.y - l.p1.y);
  return P.normal();
}

