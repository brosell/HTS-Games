#pragma warning (disable : 4786 4503 4530)
#include "Level.h"
#include "IniFile.h"
#include "StdString.h"
#include "FileManager.h"
#include "AM.h"

#include "OscillatingFan.h"
#include "Switch.h"
#include "Star.h"
#include "Door.h"
#include "Teleporter.h"


class BGTile: public Thing
{
public:
  BGTile(string asset, int x, int y):
      Thing(1)
  {
    m_skin = Globals::am->getRotateSkin(asset);
    setSkin(m_skin);
    setPosition(FPoint(x, y));
  }
  ~BGTile()
  {
    
  }

private:
  RotateSkinHandle m_skin;
};

// entities
#include "Tee.h"
#include "UpWind.h"

Level::Level(string filename):
m_ball(0), 
m_valid(true), 
m_world(0), 
m_worldSize(0, 0, 0, 0),
m_solved(false)
{
  Globals::console->println("Loading %s", filename.c_str());
  if (!fm_fileExists(filename))
  {
    Globals::console->println("Map file not found");
    m_valid = false;
    return;
  }

  IniFile ini(filename);
  ini.read();

  Point p(ini["Level"]["Size"]);

  if (p.x == -1 || p.y == -1)
  {
    Globals::console->println("Invalid map (no size)");
    m_valid = false;
    return;
  }

  Point ws(ini["Level"]["WorldSize"]);

  if (ws.x == -1 || ws.y == -1)
  {
    Globals::console->println("Invalid map (no world size)");
    m_valid = false;
    return;
  }

  m_gravity = ini.getFloat("Level", "Gravity");

  m_worldSize = Rect(0, 0, ws.x, ws.y);

//  World* world = new World(ws.x, ws.y);

  loadTiles(ini);
  loadEntities(ini);
  loadFaces(ini);

  loadBackground(ini);

  Globals::console->println("Loaded");
}

void Level::loadBackground(IniFile& ini)
{
  for_each(m_background.begin(), m_background.end(), hts::Delete());
  m_background.clear();

  string sky=ini["Level"]["Sky"];
  for (int x=0; x<m_worldSize.w*1.5; x+=400)
  {
    for (int y=0; y<m_worldSize.h*1.5; y+=400)
    {
      CStdString skytile;
      int num = (rand()%4>0)?1:(rand()%4)+1;
      skytile.Format("bg_%s%d", sky.c_str(), num);
      BGTile* tile = new BGTile(skytile, x, y);
      Globals::world->addThing(*tile);
      m_background.insert(tile);
    }
  }
}

void Level::loadEntities(IniFile& ini)
{
  int c = 1;
  while (true)
  {
    CStdString section;
    section.Format("Entity%d", c);
    if (!ini.hasSection(section))
    {
      break;
    }

    string type = ini[section]["Type"];
    
    int x = ini.getInt(section, "X");
    int y = ini.getInt(section, "Y");

    int state = ini.getInt(section, "InitialState");
    int id = ini.getInt(section, "Id");
    int z = ini.getInt(section, "Z");

    int angle = ini.getInt(section, "Angle");

    Entity* ent = 0;
    if (type == "Tee")
    {
      //ent = new Tee;

      GolfBall* ball = new GolfBall;
      ball->setPosition(Point(x, y));//-60)); // FIXME: constant
      m_ball = ball;

//      m_club = new Club;
      
    }
    else if (type == "Goal")
    {
      Goal* goal = new Goal;
      goal->addListener(this);
      ent = goal;
    }
    else if (type == "WindMachine")
    {
      UpWind* wind = new UpWind;
      
      int power = ini.getInt(section, "Power");
      wind->setBlow(angle, power);
      ent = wind;
    }
    else if (type == "OscillatingFan")
    {
      OscillatingFan* of = new OscillatingFan;
      int power = ini.getInt(section, "Power");
      of->setPower(power);
      ent = of;
    }
    else if (type == "Switch")
    {
      ent = new Switch;
    }
    else if (type == "Door")
    {
      ent = new Door;
    }
    else if (type == "Star")
    {
      ent = new Star;
    }
    else if (type == "Teleporter")
    {
      ent = new Teleporter(ini[section]);
    }

    if (ent)
    {
      if (z > 0)
      {
        ent->setZ(z);
      }
      ent->setDrawAngle(angle);
      ent->setPosition(Point(x, y));
      ent->setId(id);
      ent->setState(state);
      m_entities.insert(ent);
    }
    c++;
  }


}

void Level::loadFaces(IniFile& ini)
{
  int c = 1;
  while (true)
  {
    CStdString section;
    section.Format("Face%d", c);
    c++;
    if (!ini.hasSection(section))
    {
      break;
    }
    
    int x1 = ini.getInt(section, "X1");
    int y1 = ini.getInt(section, "Y1");
    int x2 = ini.getInt(section, "X2");
    int y2 = ini.getInt(section, "Y2");

    string type = ini[section]["Type"];
    if (type == "")
    {
      type = "Grass";
    }

    m_faces.push_back(Face(type, Line(FPoint(x1, y1), FPoint(x2, y2))));
  }
  
}

void Level::loadTiles(IniFile& ini)
{
  int c=1;
  while (true)
  {
    CStdString section;
    section.Format("Tile%d", c);
    if (!ini.hasSection(section))
    {
      break;
    }

    string type = ini[section]["Type"];
    
    int x = (ini.getInt(section, "X"));
    int y = (ini.getInt(section, "Y"));
    int z = (ini.getInt(section, "Z"));

    Tile* tile = new Tile(type);
    tile->setPosition(FPoint(x, y));
    if (z > 0)
    {
      tile->setZ(z);
    }

    m_tiles.insert(tile);
    c++;
  }

}

bool Level::isValid()
{
  return (m_valid && (m_ball != 0));
}

Level::~Level()
{
  if (m_world!=0)
  {
    removeFromWorld();
    m_world->optimize();
    m_world = 0;
  }

  set<Tile*>::iterator it;
  for (it=m_tiles.begin(); it!=m_tiles.end(); it++)
  {
    delete (*it);
  }
  m_tiles.clear();

  set<Entity*>::iterator ie;
  for (ie=m_entities.begin(); ie!=m_entities.end(); ie++)
  {
    delete (*ie);
  }
  m_entities.clear();

  set<Thing*>::iterator i;
  for (i=m_background.begin(); i!=m_background.end(); i++)
  {
    delete *i;
  }
  m_background.clear();

  delete m_ball;

//  delete m_club;

  m_faces.clear();
}


void Level::toWorld(World* world)
{
  lassert(world != 0);
  lassert(m_world == 0);
  
  m_world = world;
  m_world->setWorldDimensions(m_worldSize);

  set<Tile*>::iterator i;
  for (i=m_tiles.begin(); i!=m_tiles.end(); i++)
  {
    m_world->addThing( *(*i) );
  }

  set<Entity*>::iterator ie;
  for (ie=m_entities.begin(); ie!=m_entities.end(); ie++)
  {
    m_world->addMovingThing(*(*ie));
  }

  if (m_ball)
  {
    m_world->addMovingThing(*m_ball);
    Globals::theBall = m_ball;
    
    // FIXME: doesn't belong here
    list<Face>::iterator i;
    for (i=m_faces.begin(); i!=m_faces.end(); i++)
    {
      m_ball->addFace(*i);
    }

//    m_world->addMovingThing(*m_club);
  }
}

void Level::removeFromWorld()
{
  lassert(m_world != 0);
  set<Tile*>::iterator it;
  for (it=m_tiles.begin(); it!=m_tiles.end(); it++)
  {
    m_world->removeThing(*(*it));
  }

  set<Entity*>::iterator ie;
  for (ie=m_entities.begin(); ie!=m_entities.end(); ie++)
  {
    m_world->removeThing(*(*ie));
  }

  m_world->removeThing(*m_ball);
  Globals::theBall = 0;

//  m_world->removeThing(*m_club);

  set<Thing*>::iterator i;
  for (i=m_background.begin(); i!=m_background.end(); i++)
  {
    m_world->removeThing(*(*i));
  }
}

void Level::goalAchieved(Goal* goal)
{
  //MessageBeep(-1);
  m_solved = true;
  theGame.uiSystem.draw(theGame.screen);
}

