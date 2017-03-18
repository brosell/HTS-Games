#ifndef Face_h
#define Face_h

#include <list>
#include <string>
using namespace std;

#include "IniFile.h"

#include "GameMath.h"

class Face
{
public:
  Face(string type, Line l);

  Face(Line l, float x, float y): line(l), xForceFactor(x), yForceFactor(y) { }

  float getXForceFactor() { return xForceFactor; }
  float getYForceFactor() { return yForceFactor; }
  Line getLine() { return line; }
  string getType() { return type; }

  /** hot spot is a square dead center and is 10 pixel radius*/
  bool isPointInHotSpot(Point p);

  void draw();

  static list<string> getTypes();
private:
  int color[4];
  string type;
  Line line;
  float xForceFactor;
  float yForceFactor;

  static IniFile s_ini;
};

#endif