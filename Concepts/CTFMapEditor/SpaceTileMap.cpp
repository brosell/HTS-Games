#pragma warning (disable : 4503)

#include "SpaceTileMap.h"
#include "Misc/GameMath.h"
#include "Game/World.h"
#include "Engine.h"
#include "StringTokenizer.h"

#include "SpawnTile.h"

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
m_sideLength(sideLength),
m_selected(0),
lastType(TILE_EMPTY)
{
  m_h = sintable[30] * sideLength;
  m_r = costable[30] * sideLength;
  m_b = sideLength + (2 * m_h);
  m_a = 2 * m_r;
  m_m = (float)m_h / (float)m_r;

  theGame.console->addCallback("size", this);
  theGame.console->addCallback("save", this);
  theGame.console->addCallback("load", this);
  theGame.console->addCallback("list", this);
  theGame.console->addCallback("del", this);
  theGame.console->addCallback("test", this);

}

void SpaceTileMap::setType(int x, int y, int owner, TileType type)
{
  (*this)[x][y]->setType(type);
}

void SpaceTileMap::prepare()
{
  int worldX=-1;
  int worldY=-1;

  for (int x=0; x<m_width; x++)
  {
    for (int y=0; y<m_height; y++)
    {
      SpaceTile* tile = (*this)[x][y];
      lassert(tile != 0);
      worldX = (x * (2 * m_r)) + ((y & 1) * m_r);
      worldY = y * (m_h + m_sideLength);
      //tile->setPosition(FPoint(worldX+m_r, worldY+(m_b/2)));
      tile->setPosition(FPoint(worldX, worldY));
      Engine::instance->theWorld->addThing(*tile);
    }
  }
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

TileType SpaceTileMap::getTypeAt(int worldX, int worldY)
{
  Point p = getCoord(worldX, worldY);
  return (*this)[p.x][p.y]->getType();
}

void SpaceTileMap::removeAll()
{
  for (int x=0; x<m_width; x++)
  {
    for (int y=0; y<m_height; y++)
    {
      SpaceTile* tile = (*this)[x][y];
      Engine::instance->theWorld->removeThing(*tile);
      delete tile;
    }
  }
  m_selected = 0;
  clear(); // map::clear
}

void SpaceTileMap::setSize(int w, int h)
{
  int worldX;
  int worldY;
  removeAll();
  m_width = w;
  m_height = h;

  for (int x=0; x<m_width; x++)
  {
    for (int y=0; y<m_height; y++)
    {
      SpaceTile* tile = new SpaceTile;
      (*this)[x][y] = tile;
      worldX = (x * (2 * m_r)) + ((y & 1) * m_r);
      worldY = y * (m_h + m_sideLength);
      tile->setPosition(FPoint(worldX, worldY));
      
      Engine::instance->theWorld->addThing(*tile);
    }
  }
  Engine::instance->theWorld->optimize();
}

void SpaceTileMap::mouseClicked(MouseClickEvent* event)
{
  Point mouse = Engine::instance->theWorld->translateScreenPoint(Point(event->x, event->y));
  Point sector = getCoord(mouse.x, mouse.y);
  SpaceTile* tile = (*this)[sector.x][sector.y];

  if (event->button == 1)
  {
    if (tile)
    {
      tile->setSelected(true);
      if (m_selected != tile && m_selected != 0)
      {
        m_selected->setSelected(false);
      }
    }
    m_selected = tile;
  }
  if (event->button == 3)
  {
    if (tile)
    {
      tile->setType(lastType);
    }
  }
}

void SpaceTileMap::mouseMoved(MouseMoveEvent* event)
{
  if (theGame.getButtonState(3))
  {
    Point mouse = Engine::instance->theWorld->translateScreenPoint(Point(event->x, event->y));
    Point sector = getCoord(mouse.x, mouse.y);
    SpaceTile* tile = (*this)[sector.x][sector.y];
    if (tile)
    {
      tile->setType(lastType);
    }
  }
}

void SpaceTileMap::keyPressed(KeyPressEvent* event)
{
  if (!m_selected)
  {
    return;
  }

  TileType type;

  switch (event->keySym)
  {
  case SDLK_e:
    {
      type = TILE_EMPTY;
    }
    break;
  case SDLK_a:
    {
      type = TILE_ASTEROID;
    }
    break;
  case SDLK_n:
    {
      type = TILE_NEBULA;
    }
    break;
  case SDLK_s:
    {
      type = TILE_SOLID;
    }
    break;
  case SDLK_q:
    {
      type = TILE_SPAWN;
    }
    break;
  case SDLK_f:
    {
      type = TILE_FLAG;
    }
    break;
  case SDLK_1:
    {
      m_selected->setOwner(1);
      return;
    }
    break;
  case SDLK_2:
    {
      m_selected->setOwner(2);
      return;
    }
    break;
  case SDLK_0:
    {
      m_selected->setOwner(0);
      return;
    }
    break;
  default:
    {
      return;
    }
  }

  lastType = type;

  m_selected->setType(type);
      
}



void SpaceTileMap::consoleCommand(ConsoleEvent* event)
{
  char buf[255];
  string cmd = event->command;

  if (cmd == "test")
  {
    if (event->args.size() != 4)
    {
      theGame.console->println("error");
      return;
    }
    int x1 = atoi(event->args.front().c_str());
    event->args.pop_front();
    int y1 = atoi(event->args.front().c_str());
    event->args.pop_front();
    int x2 = atoi(event->args.front().c_str());
    event->args.pop_front();
    int y2 = atoi(event->args.front().c_str());
    event->args.pop_front();
    
    test(x1, y1, x2, y2);
  }
  
  if (cmd == "size")
  {
    if (event->args.size() != 2)
    {
      theGame.console->println("Error: size w h");
      theGame.console->println("   w - width");
      theGame.console->println("   h - height");
      theGame.console->println("");
      return;
    }
    int w = atoi(event->args.front().c_str());
    event->args.pop_front();
    int h = atoi(event->args.front().c_str());
    event->args.pop_front();

    if (w<=0 || h<=0)
    {
      theGame.console->println("Error: size w h");
      theGame.console->println("   w and h must be greater than zero");
      theGame.console->println("");
      return;
    }
    
    setSize(w, h);
    sprintf(buf, "Gameboard now %dx%d", m_width, m_height);
    theGame.console->println(buf);
  }
  if (cmd == "save")
  {
    if (event->args.size() != 1)
    {
      theGame.console->println("Error: save mapname");
      theGame.console->println("");
      return;
    }

    saveMap(event->args.front());
  }
  if (cmd == "del")
  {
    if (event->args.size() != 1)
    {
      theGame.console->println("Error: del mapname");
      theGame.console->println("");
      return;
    }

    delMap(event->args.front());
    listMaps();
  }
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
      (*this)[x][y]->setType(type);
      (*this)[x][y]->setOwner(owner);
    }
  }

  sprintf(buf, "loaded \"%s\"", mapname.c_str());
  theGame.console->println(buf);
}

void SpaceTileMap::saveMap(string mapname)
{
  string filename="map.ini";
  IniFile file(filename);
  file.read();

  char buf[2048];

  sprintf(buf, "%d", m_width);
  file[mapname]["Width"] = buf;
  sprintf(buf, "%d", m_height);
  file[mapname]["Height"] = buf;

  for (int y=0; y<m_height; y++)
  {
    string row = "Row";
    sprintf(buf, "%d", y);
    row += buf;

    buf[0]='\0';
    char* pbuf = buf;
    for (int x=0; x<m_width; x++)
    {
      SpaceTile* tile = (*this)[x][y];
      pbuf+=sprintf(pbuf, "%d,%d ", tile->getType(), tile->getOwner());
    }
    file[mapname][row] = buf;
  }

  file.write();

  theGame.console->println("wrote map.ini");
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

void SpaceTileMap::delMap(string mapname)
{
  string filename="map.ini";
  IniFile file(filename);
  file.read();

  file.erase(mapname); 
  file.write();
}

void SpaceTileMap::test(int x1, int y1, int x2, int y2)
{
  for (int x=0; x<m_width; x++)
  {
    for (int y=0; y<m_height; y++)
    {
      SpaceTile* tile = (*this)[x][y];
      tile->setSelected(false);
    }
  }

  (*this)[x1][y1]->setType(TILE_SOLID);

  neighborsInRadius(x1, y1, x2, 0);

//  Point p1 = (*this)[x1][y1]->getPositioni();
//  Point p2 = (*this)[x2][y2]->getPositioni();
//
//  Point srcCoord = p1;
//  Point destCoord = p2;
//
//  int deltaX = destCoord.x - srcCoord.x;
//  int deltaY = destCoord.y - srcCoord.y;
//
////  if (deltaX > deltaY)
//  {
//    int b = (int)getB(srcCoord, destCoord);
//    float m = getM(srcCoord, destCoord);
//    for(float x=srcCoord.x; x<destCoord.x; x+=m_r)
//    {
//      int y=(x*m) + b;
//      Point p = getCoord(x, y);
//      (*this)[p.x][p.y]->setSelected(true);
//    }
//  }

}

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

  if (startX >= 0 && startY >= 0)
  {
    (*this)[startX][startY]->setSelected(true);
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
        (*this)[curX][curY]->setSelected(true);
      }
    }
  }
  return 0;
}