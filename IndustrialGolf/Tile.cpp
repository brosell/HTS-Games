#pragma warning (disable : 4786 4503 4530)

#include "Tile.h"
#include "Globals.h"
#include "StdString.h"
#include "StringTokenizer.h"
#include "Globals.h"

IniFile Tile::s_ini("TileDef.ini");

Tile::Tile(string type):
Thing(10),
m_type(type)
{
  setId(TILE_ID);
  //m_skin = Globals::assetManager->getSkin("skn_Tile");
  if (!s_ini.isRead())
  {
    s_ini.read();
  }

  m_xForceFactor = s_ini.getInt(type, "XForceFactor");
  m_yForceFactor = s_ini.getInt(type, "YForceFactor");

  int numFaces = s_ini.getInt(type, "Faces");
//  lassert(numFaces > 0);

  for (int c=1; c<=numFaces; c++)
  {
    CStdString s;
    s.Format("Face%02d", c);
    addFace(parseLine(s_ini[type][s]), m_xForceFactor, m_yForceFactor);
  }

  m_skin = Globals::am->getRotateSkin(s_ini[type]["Skin"]);
  setSkin(m_skin);

}

list<string> Tile::getTypes()
{
  list<string> ret;
  if (!s_ini.isRead())
  {
    s_ini.read();
  }

  IniFile::iterator pair;
  for (pair = s_ini.begin(); pair!=s_ini.end(); pair++)
  {
    ret.push_back(pair->first);
  }

  return ret;
}

Tile::~Tile()
{
  //Globals::assetManager->releaseSkin(m_skin);
}

//bool Tile::inRange(Point p, float radius, Line& ret)
//{
//  float radSquared = radius * radius;
//
//  list<Line>::iterator i;
//  float closestDist = FLT_MAX;
//  Line closest;
//
//  for (i=m_faces.begin(); i!=m_faces.end(); i++)
//  {
//    Line l = *i;
//    l.p1.x+=getTopLeftX();
//    l.p1.y+=getTopLeftY();
//    l.p2.x+=getTopLeftX();
//    l.p2.y+=getTopLeftY();
//
//    float dist = distToSegment(p, l);
//    if(dist <= radius)
//    {
//      if (dist < closestDist)
//      {
//        closest = l;
//        closestDist = dist;
//      }
//    }
//  }
//  
//  if (closestDist < FLT_MAX)
//  {
//    ret = closest;
//    return true;
//  }
//  
//  return false;
//}

void Tile::draw(Display* display, int x, int y)
{
  //m_skin->blit(display, x, y, true);
  Thing::draw(display, x, y);

  list<Face>::iterator i;
  for (i=m_faces.begin(); i!=m_faces.end(); i++)
  {
    Line l = (*i).getLine();
    l.p1.x+=getTopLeftX();
    l.p1.y+=getTopLeftY();
    l.p2.x+=getTopLeftX();
    l.p2.y+=getTopLeftY();

//    // this draws the normal on the screen
//    int x = l.p1.x + ((l.p2.x - l.p1.x)/2);
//    int y = l.p1.y + ((l.p2.y - l.p1.y)/2);
//    FPoint center(x, y);
//
//    Vector n = normal(l);
//    n = n.normalize().multiply(30);
//    FPoint normal(center.x+n.x, center.y+n.y);
//    
//    
//    center = Globals::world->translateToScreen(center);
//    normal = Globals::world->translateToScreen(normal);
//
//    display->drawLine(center.x, center.y, normal.x, normal.y, 255, 0, 0, 255);

    l.p1 = Globals::world->translateToScreen(l.p1);
    l.p2 = Globals::world->translateToScreen(l.p2);
    display->drawLine(l.p1.x, l.p1.y, l.p2.x, l.p2.y, 255, 0, 0, 255);
    
  }
}

Line Tile::parseLine(string line)
{
  Line l(FPoint(-1, -1), FPoint(-1, -1));
  StringTokenizer st(line, ", ");
  if (st.countTokens() == 4)
  {
    l.p1.x = atoi(st.nextToken());
    l.p1.y = atoi(st.nextToken());
    l.p2.x = atoi(st.nextToken());
    l.p2.y = atoi(st.nextToken());
  }
  else
  {
    line = line;
  }
  return l;
}