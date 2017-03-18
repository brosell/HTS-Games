#pragma warning (disable : 4503)

#include "sqSpaceTileMap.h"
#include "Misc/GameMath.h"
#include "Game/World.h"
#include "Engine.h"

#include "sqSpawnTile.h"
#include "sqFlagBaseTile.h"
#include "AStar.h"

#include "StringTokenizer.h"

#define m_map(x, y) m_map[(y)*m_width + (x)]


SpaceTileMap::SpaceTileMap(int sideLength):
m_width(0),
m_height(0),
m_sideLength(sideLength)
{
  m_map = 0;

  theGame.console->addCallback("load", this);
  theGame.console->addCallback("list", this);
}

void SpaceTileMap::addTile(int x, int y, TileType type, int owner)
{
  SpaceTile* tile = m_map(x, y);
  if (tile != 0)
  {
    delete tile;
  }

  switch(type)
  {
  case TILE_EMPTY:
    {
      tile = new SpaceTile(owner, type);
    }
    break;
  case TILE_SPAWN:
    {
      SpawnTile* st = new SpawnTile(owner);
      tile = st;
    }
    break;
  case TILE_FLAG:
    {
      tile = new FlagBaseTile(owner);
      PlayerStuff::get(owner)->flagBase=tile;
    }
    break;
  default:
    {
      tile = new SpaceTile(owner, type);
    }
    break;
  }



  tile->setCoords(x, y);
  m_map(x, y) = tile;
}


void SpaceTileMap::prepare()
{
  int worldX=-1;
  int worldY=-1;

  for (int x=0; x<m_width; x++)
  {
    for (int y=0; y<m_height; y++)
    {
      SpaceTile* tile = m_map(x, y);
      lassert(tile != 0);
      worldX = ((x * m_sideLength) + (m_sideLength/2));
      worldY = ((y * m_sideLength) + (m_sideLength/2));

      tile->setPosition(FPoint(worldX, worldY));
      Engine::instance->theWorld->addThing(*tile);
    }
  }

  Engine::instance->theWorld->optimize();
}

bool SpaceTileMap::isNavigable(int worldX, int worldY)
{
  return getTypeAt(worldX, worldY) != TILE_SOLID; 
}

Point SpaceTileMap::getCoord(int worldX, int worldY)
{
  return Point(worldX/m_sideLength, worldY/m_sideLength);
}

SpaceTile* SpaceTileMap::getTileAt(int worldX, int worldY)
{
  Point p = getCoord(worldX, worldY);
  return m_map(p.x, p.y);
}


TileType SpaceTileMap::getTypeAt(int worldX, int worldY)
{
  return getTileAt(worldX, worldY)->getType();
}

int SpaceTileMap::getNeighbors(int x, int y, SpaceTile** ret)
{
  int count=0;
  
  if (y > 0)
  {
    if (x > 0)
    {
      ret[count++] = m_map(x-1, y-1);
      m_map(x-1, y-1)->astar_cost = 1.5;
    }
    ret[count++] = m_map(x, y-1);
    m_map(x, y-1)->astar_cost = 1;

    if (x < m_width-1)
    {
      ret[count++] = m_map(x+1, y-1);
      m_map(x+1, y-1)->astar_cost = 1.5;
    }
  }
  
  if (x > 0)
  {
    ret[count++] = m_map(x-1, y);
    m_map(x-1, y)->astar_cost = 1;
  }
  if (x < m_width-1)
  {
    ret[count++] = m_map(x+1, y);
    m_map(x+1, y)->astar_cost = 1;
  }
  
  if (y < m_height-1)
  {
    if (x > 0)
    {
      ret[count++] = m_map(x-1, y+1);
      m_map(x-1, y+1)->astar_cost = 1.5;
    }
    ret[count++] = m_map(x, y+1);
    m_map(x, y+1)->astar_cost = 1;
    if (x < m_width-1)
    {
      ret[count++] = m_map(x+1, y+1);
      m_map(x+1, y+1)->astar_cost = 1.5;
    }
  }
  
#ifdef _DEBUG
  for (int c=0; c<count; c++)
  {
    if (ret[c] == 0)
    {
      c=c;
    }
  }
#endif

  return count;

}

void SpaceTileMap::getTilesInRadius(int x, int y, int r, set<SpaceTile*>& ret)
{

}

bool SpaceTileMap::calculateRoute(int x1, int y1, int x2, int y2, list<SpaceTile*>& ret)
{
  AStar<SpaceTile, 8> astar;
  SpaceTile* start = m_map(x1, y1);
  SpaceTile* end = m_map(x2, y2);

  if ( !end->isNavigable())// || end->getOccupant() != 0)
  {
    return false;
  }

  bool success = astar.createRoute(start, end);
  if (success)
  {
    copy(astar.route.begin(), astar.route.end(), back_inserter(ret));
  }

  return success;
}

void SpaceTileMap::consoleCommand(ConsoleEvent* event)
{
  string cmd = event->command;

  if (cmd == "load")
  {
    if (event->args.size() != 1)
    {
      theGame.console->println("Error: load mapname");
      theGame.console->println("");
      return;
    }

    loadMap(event->args.front());
  }
  if (cmd == "list")
  {
    listMaps();
  }

}

void SpaceTileMap::loadMap(string mapname)
{
  string filename="map.ini";
  IniFile file(filename);
  file.read();
  
  char buf[255];

  if (!file.hasSection(mapname))
  {
    sprintf(buf, "Map \"%s\" not found in map.ini", mapname.c_str());
    theGame.console->println(buf);
    return;
  }

  int w=file.getInt(mapname, "Width");
  if (w <= 0 || w > MAX_MAPSIZE)
  {
    sprintf(buf, "Map \"%s\" invalid (width)", mapname.c_str());
    theGame.console->println(buf);
    return;
  }
  int h=file.getInt(mapname, "Height");
  if (h<=0 || h > MAX_MAPSIZE)
  {
    sprintf(buf, "Map \"%s\" invalid (height)", mapname.c_str());
    theGame.console->println(buf);
    return;
  }

  setSize(w, h);

  for (int y=0; y<m_height; y++)
  {
    sprintf(buf, "Row%d", y);
    string row = file[mapname][buf];
    StringTokenizer st(row.c_str());
    for (int x=0; x<m_width; x++)
    {
      string tiledata = st.nextToken();
      StringTokenizer st2(tiledata.c_str(), ",");
      if (st2.countTokens() != 2)
      {
        theGame.console->println("Error loading map");
        return;
      }

      TileType type=(TileType)atoi(st2.nextToken().c_str());
      int owner = atoi(st2.nextToken().c_str());
      
      addTile(x, y, type, owner);      
    }
  }

  //Engine::instance->theWorld->optimize();
  prepare();

  sprintf(buf, "loaded \"%s\"", mapname.c_str());
  theGame.console->println(buf);
  theGame.console->hide();
}

void SpaceTileMap::removeAll()
{
  if (m_map == 0)
  {
    return;
  }

  for (int x=0; x<m_width; x++)
  {
    for (int y=0; y<m_height; y++)
    {
      SpaceTile* tile = m_map(x, y);
      Engine::instance->theWorld->removeThing(*tile);
      delete tile;
    }
  }
  delete m_map;
}

void SpaceTileMap::setSize(int w, int h)
{
  removeAll();
  m_width = w;
  m_height = h;

  m_map = new SpaceTile*[w*h];
  memset(m_map, 0, w*h*sizeof(SpaceTile*));
}

void SpaceTileMap::listMaps()
{
  string filename="map.ini";
  IniFile file(filename);
  file.read();

  theGame.console->println("map list");
  theGame.console->println("--------");

  map<string, map<string, string> >::iterator pair;
  for (pair=file.begin(); pair!=file.end(); pair++)
  {
    theGame.console->println(pair->first);
  }
  theGame.console->println("--- end of list\n");
}

////////////////////////
// FOG OF WAR
////////////////////////

void SpaceTileMap::calculateFogOfWar()
{
  int tileNum = 0;
  int numVis = 0;
  
  // reset fog visiblity
  for (tileNum=0; tileNum<m_width*m_height; tileNum++)
  {
    SpaceTile* tile = m_map[tileNum];
    tile->fog_nowVisible = false;
  }

  SpaceTile* inRad[1024]; // way to big?
  list<Ship*>::iterator i;
  for (i=Ship::s_allShips.begin(); i!=Ship::s_allShips.end(); i++)
  {
    Ship* ship = (*i);
    if (ship->isSpawned() != true)
    {
      continue;
    }

    Point shipSect = ship->getSect();
    SpaceTile* shipTile = m_map(shipSect.x, shipSect.y); //Engine::instance->theMap->getTileAt(shipPos.x, shipPos.y);
    shipTile->fog_everVisible = true;
    shipTile->fog_nowVisible = true;

    int sr = ship->getSensorRange();
    
    int count = neighborsInRadius(shipSect.x, shipSect.y, sr+1, inRad);
    for (int cc = 0; cc<count; cc++)
    {
      if (!isTileObscured(inRad[cc], shipTile))
      {
        if (inRad[cc]->getSect().distanceToSquared(shipSect) <= sr*sr)
        {
          inRad[cc]->fog_everVisible = true;
          inRad[cc]->fog_nowVisible = true;
        }
        else if (inRad[cc]->getSect().distanceToSquared(shipSect) <= (sr + 1)*(sr + 1))
        {
          inRad[cc]->fog_everVisible = true;
        }
      }
    }
  }
  return;
}




int SpaceTileMap::neighborsInRadius(int x, int y, int r, SpaceTile** ret)
{
  int retCount = 0;
  // brute force method
    
  int lowX = max(x-r, 0);
  int upperX = min(x+r+1, m_width);

  int lowY = max(y-r, 0);
  int upperY = min(y+r+1, m_height);
  
  int radiusSquared = r*r;
  
  for (int xi=lowX; xi<upperX; xi++)
  {
    int dx = (xi - x) * (xi - x); //squared
    for (int yi=lowY; yi<upperY; yi++)
    {
      int dy = (yi - y) * (yi - y); // squared
      if (dx + dy <= radiusSquared )
      {
        ret[retCount++] = m_map(xi, yi);
      }
    }
  }

  return retCount;
}

/* calculate fog of war

  for each ship set location by ship's (mapx, mapy) as (x, y)
  We will check all tiles in square that is defined
    by (x-(r+1), y-(r+1))-(x+(r+1), y+(r+1)).

    for each tile
      if the tile is not obscured by anything
        if dist<r then tile is visible
        else if dist<(r+1) then tile is partially visible
        else tile is not visible
      end if
    next tile
  next ship


  isObscured(source, target)
    if (deltaX >= deltaY)
      xdir = 1 or -1 (depends on ...)
      ydir = m (as in y=mx+b)
    else
      xdir = ym (m as if x=my+b)
      ydir = 1 or -1 (depends on ...)
    end if

    let curPoint = (x, y);
    while (curPoint != (x2, y2))
      if (tileAt(curPoint) is solid)
        return true
      end if
      curPoint += (xdir, ydir)
    loop
    return false;
  end
*/

template<typename kind>
kind babs(kind val)
{
  if (val < 0)
    return val * -1;
  return val;
}

bool SpaceTileMap::isTileObscured(SpaceTile* check, SpaceTile* from)
{
  Point start = from->getCoords();
  Point end = check->getCoords();
  
  int deltaX = babs(end.x - start.x);
  int deltaY = babs(end.y - start.y);

  float xDir, yDir;

  if (deltaX >= deltaY)
  {
    xDir = (start.x < end.x)?1:-1;
    if (deltaX != 0)
    {
      yDir = (float)(end.y - start.y) / (float)(end.x - start.x);
      if (start.y > end.y)
      {
        yDir = -1*babs(yDir);
      }
      else
      {
        yDir = babs(yDir);
      }
    }
    else
    {
      yDir = 0;
    }
  }
  else
  {
    if (deltaY != 0)
    {
      xDir = (float)(end.x - start.x) / (float)(end.y - start.y);
      if (start.x > end.x)
      {
        xDir = -1*babs(xDir);
      }
      else
      {
        xDir = babs(xDir);
      }

    }
    else
    {
      xDir = 0;
    }
    yDir = (start.y < end.y)?1:-1;
  }

  FPoint curPoint(start.x, start.y);
  FPoint fend(end.x, end.y);

  int steps = 0;
  if (deltaX >= deltaY)
  {
    steps = deltaX;
  }
  else
  {
    steps = deltaY;
  }

  for (int step=0; step<steps; step++)
  {
    if (m_map((int)curPoint.x, (int)curPoint.y)->getType() == TILE_SOLID)
    {
      return true;
    }
    curPoint = FPoint(curPoint.x + xDir, curPoint.y + yDir);
  }
  return false;
}