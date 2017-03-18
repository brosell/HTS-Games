#pragma warning (disable : 4786 4503 4530)
#include "Face.h"
#include "BR_Game.h"
#include "Globals.h"

#include "AM.h"

#include "sdl_gfxprimitives.h"


IniFile Face::s_ini("FaceDef.ini");

Face::Face(string type, Line l):
line(l),
type(type)
{
  if (!s_ini.isRead())
  {
    s_ini.read();
  }

  xForceFactor = s_ini.getFloat(type, "XForceFactor");
  yForceFactor = s_ini.getFloat(type, "YForceFactor");
  parseColor(s_ini[type]["Color"], color[0], color[1], color[2], color[3]);
}

bool Face::isPointInHotSpot(Point p)
{
  return (line.middle().distanceTo(FPoint(p)) < 10);
}

void Face::draw()
{
  Point p1 = Globals::world->translateToScreen(line.p1);
  Point p2 = Globals::world->translateToScreen(line.p2);
  Display::getInstance()->drawLine(p1.x, p1.y, p2.x, p2.y, color[0], color[1], color[2], color[3]);
  Point m = Globals::world->translateToScreen(line.middle());
  circleRGBA(Display::getInstance()->getSDLSurface(), m.x, m.y, 10, color[0], color[1], color[2], color[3]);
  //Globals::am->getFont("fnt_Default")->drawLine(Display::getInstance(), type, m.x, m.y) ;
}

list<string> Face::getTypes()
{
  if (!s_ini.isRead())
  {
    s_ini.read();
  }

  list<string> ret;
  
  IniFile::iterator pair;
  for (pair = s_ini.begin(); pair!=s_ini.end(); pair++)
  {
    ret.push_back(pair->first);
  }

  return ret;
}