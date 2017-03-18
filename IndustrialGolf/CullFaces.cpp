#pragma warning (disable : 4786 4530 4503)
#include "CullFaces.h"

list<Line> cullFaces(list<Line>& faces)
{
  
  list<Line> out;
  list<Line>::iterator i;

  list<Line> copy(faces);
  while (true)
  {
    Line face = copy.front();
    
    i=copy.begin();
    i++;
    for (; i!=copy.end(); i++)
    {
      Line line = *i;
      if (cullable(face, line))
      {
        copy.erase(i); // get rid of (*i)
        copy.pop_front(); // get rid of "face"
        Line culled;
        culled.p1 = face.p1;
        culled.p2 = line.p2;
        copy.push_back(culled);
        goto loop;
      }
    }

    return copy;

loop:
    continue;
  }
}


bool cullable(Line l1, Line l2)
{
  Vector vl1(l1);
  Vector vl2(l2);


  return ((l1.p2 == l2.p1) && (vl1.normalize() == vl2.normalize()));
}
