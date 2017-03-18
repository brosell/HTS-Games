#pragma warning (disable : 4503)

#include "SpaceTileMap.h"
#include "Misc/GameMath.h"
#include "Game/World.h"
#include "Engine.h"

#include "SpawnTile.h"
#include "FlagBaseTile.h"
#include "AStar.h"

#include "StringTokenizer.h"

#define m_map(x, y) m_map[(y)*m_width + (x)]

int dirsYOdd[6][2] = 
{
  {1, -1}, // upRight
  {1, 0}, // Right
  {1, 1}, // downRight
  {0, 1}, // DownLeft
  {-1, 0}, // Left
  {0, -1} // UpLeft
};

int dirsYEven[6][2] =
{
  {0, -1}, // upRight
  {1, 0}, // Right
  {0, 1}, // downRight
  {-1, 1}, // DownLeft
  {-1, 0}, // Left
  {-1, -1} // UpLeft
};

int travelDirs[6] = 
{
  RIGHT,
  DOWN_RIGHT,
  DOWN_LEFT,
  LEFT,
  UP_LEFT,
  UP_RIGHT
};


SpaceTileMap::SpaceTileMap(int sideLength):
m_width(0),
m_height(0),
m_sideLength(sideLength)
{
  m_map = 0;

  m_h = sintable[30] * sideLength;
  m_r = costable[30] * sideLength;
  m_b = sideLength + (2 * m_h);
  m_a = 2 * m_r;
  m_m = (float)m_h / (float)m_r;

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
      worldX = (x * (2 * m_r)) + ((y & 1) * m_r);
      worldY = y * (m_h + m_sideLength);
      //tile->setPosition(FPoint(worldX+m_r, worldY+(m_b/2)));
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
  worldX+=m_r;
  worldY+=(m_b/2);

// see gamedev.net - Coordinates in Hexagon-Based Tile Maps
  int xSect = worldX / (2*m_r);
  int ySect = worldY / (m_h + m_sideLength);


  int xSectPixel = worldX % (2 * m_r);
  int ySectPixel = worldY % (m_h + m_sideLength);

  int arrayX;
  int arrayY;

  

  if ( (ySect & 1) == 0)
  {
    // sectType = A
    arrayX = xSect;
    arrayY = ySect;
    
    if (ySectPixel < ((xSectPixel * (-m_m)) + m_h ) )
    {
      // topLeft
      arrayX--;
      arrayY--;
    }
    else if (ySectPixel < ((xSectPixel * (m_m)) -m_h) )
    {
      // top Right
      arrayY--;
    }
  }
  else
  {
    // sectType = B
    if (xSectPixel >= m_r)
    {
      if (ySectPixel < ( (xSectPixel * (-m_m)) + (2*m_h) ))
      {
        arrayX = xSect;// - 1;
        arrayY = ySect - 1;
      }
      else
      {
        arrayX = xSect;
        arrayY = ySect;
      }
    }
    else
    {
      if (ySectPixel < (xSectPixel * (m_m)) )
      {
        arrayY = ySect - 1;
        arrayX = xSect;
      }
      else
      {
        arrayY = ySect;
        arrayX = xSect - 1;
      }
    }
  }  
  return Point(arrayX, arrayY);
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

//void SpaceTileMap::getNeighbors(int x, int y, set<SpaceTile*>& ret)
int SpaceTileMap::getNeighbors(int x, int y, SpaceTile** ret)
{
  int count=0;
  if ( (y & 1) != 0)
  {
    if (x < (m_width-1) && y > 0)
      ret[count++] = m_map(x+1, y-1);
    
    if (x < (m_width-1))
      ret[count++] = m_map(x+1, y);
    
    if (x < (m_width-1) && y < (m_height-1))
      ret[count++] = m_map(x+1, y+1);
    
    if (y > 0)
      ret[count++] = m_map(x, y+1);
    
    if (x > 0)
      ret[count++] = m_map(x-1, y);
    
    if (y > 0)
      ret[count++] = m_map(x, y-1);
  }
  else
  {
    if (y > 0)
      ret[count++] = m_map(x, y-1);
    
    if (x < (m_width-1))
      ret[count++] = m_map(x+1, y);
    
    if (y < (m_height-1))
      ret[count++] = m_map(x, y+1);
    
    if (x > 0 && y < m_height - 1)
      ret[count++] = m_map(x-1, y+1);
    
    if (x > 0)
      ret[count++] = m_map(x-1, y);
    
    if (x > 0 && y > 0)
      ret[count++] = m_map(x-1, y-1);
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
  AStar<SpaceTile, 6> astar;
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

    Point shipPos = ship->getPositioni();
    Point shipSect = Engine::instance->theMap->getCoord(shipPos.x, shipPos.y);
    SpaceTile* shipTile = Engine::instance->theMap->getTileAt(shipPos.x, shipPos.y);
    shipTile->fog_everVisible = true;
    shipTile->fog_nowVisible = true;

    int sr = ship->getSensorRange();
    {
      int count = neighborsInRadius(shipSect.x, shipSect.y, sr, inRad);
      for (int cc = 0; cc<count; cc++)
      {
        isTileObscured(inRad[cc], shipTile);
      }
    }
  }
  return;
}


void SpaceTileMap::isTileObscured(SpaceTile* check, SpaceTile* from)
{
  if (check == from)
  {
    check->fog_everVisible = true;
    check->fog_nowVisible = true;
    return;
  }

  Point srcPos = from->getPositioni();
  Point destPos = check->getPositioni();

  int deltaX = abs(destPos.x - srcPos.x);
  int deltaY = abs(destPos.y - srcPos.y);

  if (deltaX >= deltaY)
  {
    int dir = (srcPos.x < destPos.x)?1:-1;
    int b = (int)getB(srcPos, destPos);
    float m = getM(srcPos, destPos);
    SpaceTile* cur = from;
    for(float x=srcPos.x; (dir*x)<=(dir*destPos.x) ; x+=m_r*dir)
    {
      int y=(x*m) + b;
      if (y < 0)
      {
        continue;
      }

      Point p = getCoord(x, y);
      
      cur = m_map(p.x, p.y);
      cur->fog_everVisible = true;
      cur->fog_nowVisible = true;
      if (cur->getType() == TILE_SOLID)
      {
        return;
      }
    }
  }
  else
  {
    int dir = (srcPos.y < destPos.y)?1:-1;
    int b = (int)getBx(srcPos, destPos);
    float m = getMx(srcPos, destPos);
    SpaceTile* cur = from;
    for(float y=srcPos.y; dir*y<= dir*destPos.y; y+=(m_b/4)*dir)
    {
      int x=(y*m) + b;
      if (x < 0)
      {
        continue;
      }

      Point p = getCoord(x, y);
      
      cur = m_map(p.x, p.y);
      cur->fog_everVisible = true;
      cur->fog_nowVisible = true;
      if (cur->getType() == TILE_SOLID)
      {
        return;
      }
    }
  }


}

//bool SpaceTileMap::isTileObscured(SpaceTile* dest, SpaceTile* src)
//{
//  const int THRESHOLD = m_r/2;
//
//  if (dest == src)
//  {
//    return false;
//  }
//  Point srcCoord = src->getCoords();
//  Point destCoord = dest->getCoords();
//
//  Point srcPos = src->getPositioni();
//  Point destPos = dest->getPositioni();
//
//  int deltaX = destPos.x - srcPos.x;
//  int deltaY = destPos.y - srcPos.y;
//
//  SpaceTile* current = 0;
//
//  if (deltaX >= deltaY)
//  {
//    int dir = (srcPos.x <= destPos.x)?1:-1;
//
//    int b = (int)getB(destPos, srcPos);
//    float m = getM(destPos, srcPos);
//    float x = srcPos.x;
//    while (current != dest && x > 0 && x < getPixelWidth())
//    {
//      int y=(x*m) + b;
//      if (y < 0 || y > getPixelHeight())
//      {
//        break;
//      }
//      current = getTileAt(x, y);
//      if (current != dest)
//      {
//        current->setSelected(true);
//        current->fog_everVisible = true;
//        current->fog_nowVisible = true;
//        if (current->getType() == TILE_SOLID)
//        {
//          //if (p.distanceToSquared(current->getPositioni()) < THRESHOLD*THRESHOLD)
//          {
//            return true;
//          }
//        }
//      }
//      x+=m_r*dir;
//    }
//  }
//  else
//  {
//    // deltaY > deltaX
//    int dir = (srcPos.y <= destPos.y)?1:-1;
//
//    int b = (int)getBx(srcPos, destPos);
//    float m = getMx(srcPos, destPos);
//
//    float y = srcPos.y;
//
//    while (current != dest && y > 0 && y < getPixelHeight())
//    {
//      int x=(y*m) + b;
//      if (x < 0 || x > getPixelWidth())
//      {
//        break;
//      }
//      current = getTileAt(x, y);
//      
//      if (current != dest)
//      {
//        current->setSelected(true);
//        current->fog_everVisible = true;
//        current->fog_nowVisible = true;
//        if (current->getType() == TILE_SOLID)
//        {
//          //if (p.distanceToSquared(current->getPositioni()) < THRESHOLD*THRESHOLD)
//          {
//            return true;
//          }
//        }
//      }
//      y+= (m_b/2)*dir;
//    }
//  }
//  return false;
//}

int SpaceTileMap::neighborsInRadius(int x, int y, int r, SpaceTile** ret)
{
  int retCount = 0;
  int c = 0;
  int yy=y;
  int xx=x;

  int startY = y;
  int startX = x;

  // find start block
  for (c = 0; c<r-1; c++)
  {
    yy = y+c;
    if ( (yy & 1) == 1)
    {
      // odd
      startX += dirsYOdd[UP_LEFT][DIR_X];
      startY += dirsYOdd[UP_LEFT][DIR_Y];
    }
    else
    {
      // even
      startX += dirsYEven[UP_LEFT][DIR_X];
      startY += dirsYEven[UP_LEFT][DIR_Y];
    }
  }

  if (startX >= 0 && startY >= 0 && startX < m_width && startY < m_height)
  {
    ret[retCount++] = m_map(startX, startY);
  }

  int dirX;
  int dirY;
  int curX = startX;
  int curY = startY;
  for (c = 0; c < 6; c++)
  {
    for (int t=0; t<r-1; t++)
    {
      if ( (curY & 1) == 1)
      {
        dirX = dirsYOdd[travelDirs[c]][DIR_X];
        dirY = dirsYOdd[travelDirs[c]][DIR_Y];
      }
      else
      {
        dirX = dirsYEven[travelDirs[c]][DIR_X];
        dirY = dirsYEven[travelDirs[c]][DIR_Y];
      }

      curX+=dirX;
      curY+=dirY;
      if (curX >=0 && curY >=0 && curX < m_width && curY < m_height)
      {
        ret[retCount++] = m_map(curX, curY);
      }
    }
  }
  return retCount;
}