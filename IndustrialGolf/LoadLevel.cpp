#pragma warning (disable : 4786 4503 4530)
#include "BR_Game.h"
#include "Globals.h"
#include "FileManager.h"
#include "StdString.h"

#include "Tile.h"
#include "Entity.h"
#include "Tee.h"
#include "GolfBall.h"

World* loadLevel(string filename)
{
  Globals::console->println("Loading %s", filename.c_str());
  if (!fm_fileExists(filename))
  {
    Globals::console->println("Map file not found");
    return 0;
  }

  IniFile ini(filename);
  ini.read();

  Point p(ini["Level"]["Size"]);

  if (p.x == -1 || p.y == -1)
  {
    Globals::console->println("Invalid map");
    return 0;
  }

  Point ws(ini["Level"]["WorldSize"]);

  if (ws.x == -1 || ws.y == -1)
  {
    Globals::console->println("Invalid map");
    return 0;
  }

  World* world = new World(ws.x, ws.y);

  int c=1;
  while (true)
  {
    CStdString section;
    section.Format("Tile%d", c);
    if (ini.find(section) == ini.end())
    {
      break;
    }

    string type = ini[section]["Type"];
    
    int x = (ini.getInt(section, "X") * Globals::tileSize) + (Globals::tileSize/2);
    int y = (ini.getInt(section, "Y") * Globals::tileSize) + (Globals::tileSize/2);

    Tile* tile = new Tile(type);
    tile->setPosition(FPoint(x, y));

    world->addThing(*tile);
    c++;
  }

  c = 1;
  while (true)
  {
    CStdString section;
    section.Format("Entity%d", c);
    if (ini.find(section) == ini.end())
    {
      break;
    }

    string type = ini[section]["Type"];
    
    int x = ini.getInt(section, "X");
    int y = ini.getInt(section, "Y");

    Entity* ent = 0;
    if (type == "Tee")
    {
      ent = new Tee;

      GolfBall* ball = new GolfBall;
      ball->setPosition(Point(x, y-30)); // FIXME: constant
      world->addMovingThing(*ball);
      Globals::theBall = ball;
    }

    if (ent)
    {
      ent->setPosition(Point(x, y));
      world->addMovingThing(*ent);
    }
    c++;
  }

  if (Globals::theBall != 0)
  {
    c = 1;
    while (true)
    {
      CStdString section;
      section.Format("Face%d", c);
      c++;
      if (ini.find(section) == ini.end())
      {
        break;
      }
      
      int x1 = ini.getInt(section, "X1");
      int y1 = ini.getInt(section, "Y1");
      int x2 = ini.getInt(section, "X2");
      int y2 = ini.getInt(section, "Y2");
      Globals::theBall->addFace(Line(FPoint(x1, y1), FPoint(x2, y2)));
    }
  }
  Globals::console->println("Loaded");

  return world;

}

