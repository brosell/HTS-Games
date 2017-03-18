#ifndef CullFaces_h
#define CullFaces_h

#include "GameMath.h"
#include "2dVector.h"
#include <list>
using namespace std;

list<Line> cullFaces(list<Line>& faces);
bool cullable(Line l1, Line l2);


#endif