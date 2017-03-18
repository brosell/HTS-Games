#pragma warning (disable : 4786 4503 4530)
#include "IGMapperListeners.h"
#include "Globals.h"
#include "Tile.h"
#include "Entity.h"

#include "PropertiesDialog.h"

#include "StdString.h"
#include "Convert.h"

#include "boost/format.hpp"

//#include "sdl_gfxprimitives.h"


#include "IGMapperChooseTileDlg.h"

IGMapperConsoleListener::IGMapperConsoleListener():
m_width(0),
m_height(0),
m_state(ES_NONE),
cur(0),
curTile(0),
m_backgroundType("BlueSky")
{
  Globals::console->addCallback("quit", this);
  Globals::console->addCallback("new", this);
  Globals::console->addCallback("load", this);
  Globals::console->addCallback("save", this);
  Globals::console->addCallback("size", this);
}

IGMapperConsoleListener::~IGMapperConsoleListener()
{
  
}

void IGMapperConsoleListener::consoleCommand(ConsoleEvent* event)
{
  if (event->command == "quit")
  {
    exit(0);
  }

  if (event->command == "load")
  {
    loadMap(event);
  }
  else if (event->command == "save")
  {
    saveMap(event);
  }
  else if (event->command == "new")
  {
    newMap(event);
  }
  else if (event->command == "size")
  {
    sizeMap(event);
  }
}

void IGMapperConsoleListener::keyPressed(KeyPressEvent* event)
{
  if (event->keySym == SDLK_BACKQUOTE)
  {
    if (!Globals::console->isShowing())
    {
      Globals::console->show();
    }
    else
    {
      Globals::console->hide();
    }
  }

  if (Globals::console->isShowing())
  {
    return;
  }

  switch(event->keySym)
  {
  case SDLK_w:
    {
      theGame.screen->setWindowed(!theGame.screen->isWindowed());
    }
    break;
  case SDLK_t:
    {
      showChooseTile();
      m_state = ES_TILE;
    }
    break;
  case SDLK_e:
    {
      showEntities();
      m_state = ES_ENTITY;
    }
    break;
  case SDLK_f:
    {
      showChooseFace();
      m_state = ES_FACE_CLICK1;
    }
    break;
  case SDLK_l:
    {
      showLevelProperties();
    }
    break;
  case SDLK_ESCAPE:
    {
      m_state = ES_NONE;
    }
    break;
  }
}

void IGMapperConsoleListener::showLevelProperties()
{
  map<string, string> props;
  props["Sky"] = m_backgroundType;
  props["Gravity"] = (boost::format("%f")%m_gravity).str();
  PropertiesDialog prop(props);
  if (prop.doModal() != -1)
  {
    m_backgroundType = props["Sky"];
    m_gravity = atof(props["Gravity"].c_str());
  }
}

void IGMapperConsoleListener::clearMap()
{
  if (Globals::world)
  {
    delete Globals::world;
  }

  m_faces.clear();

//  if (m_tiles)
//  {
//    for (int x=0; x<m_width; x++)
//    {
//      for(int y=0; y<m_height; y++)
//      {
//        delete tileAt(x, y);
//      }
//    }
//
//    delete [] m_tiles;
//    m_tiles = 0;
//  }
  set<IGMapperTile*>::iterator it;
  for (it=m_tiles.begin(); it!=m_tiles.end(); it++)
  {
    delete *it;
  }
  m_tiles.clear();

  set<IGMapperEntity*>::iterator i;
  for (i=m_ents.begin(); i!=m_ents.end(); i++)
  {
    delete *i;
  }
  m_ents.clear();
}

void IGMapperConsoleListener::initMap(int w, int h)
{
//  int size = Globals::tileSize;
//  int halfSize = size / 2;
//  m_tiles = new IGMapperTile*[w*h];
//  IGMapperTile* tile = 0;
//  for (int x=0; x<m_width; x++)
//  {
//    for(int y=0; y<m_height; y++)
//    {
//      Point loc((x*size) + halfSize , (y*size) + halfSize);
//      tile = new IGMapperTile("None");
//      tileAt(x, y) = tile;
//      tile->setPosition(loc);
//      Globals::world->addThing(*tile);
//    }
//  }
}

void IGMapperConsoleListener::sizeMap(ConsoleEvent* event)
{
  if (event->args.size() != 2)
  {
    Globals::console->println("usage: size widthInTiles heightInTiles");
    return;
  }

  m_width = atoi(event->args.front().c_str());
  event->args.pop_front();

  m_height = atoi(event->args.front().c_str());
  event->args.pop_front();

  int pWidth = m_width;// * Globals::tileSize;
  int pHeight = m_height; // * Globals::tileSize;

  Globals::world->setWorldDimensions(Rect(0, 0, pWidth, pHeight));
}

void IGMapperConsoleListener::newMap(ConsoleEvent* event)
{
  if (event->args.size() != 2)
  {
    Globals::console->println("usage: new widthInTiles heightInTiles");
    return;
  }

  clearMap();

  m_width = atoi(event->args.front().c_str());
  event->args.pop_front();

  m_height = atoi(event->args.front().c_str());
  event->args.pop_front();

  int pWidth = m_width;// * Globals::tileSize;
  int pHeight = m_height; // * Globals::tileSize;

  Globals::world = new World(pWidth, pHeight, 0, 0, 640, 480);
  Globals::worldCanvas->setWorld(Globals::world);

  initMap(m_width, m_height);

  Globals::world->optimize();

  Globals::console->println("World created");

  m_backgroundType = "BlueSky";
  m_gravity = 0.085;
}

void IGMapperConsoleListener::loadMap(ConsoleEvent* event)
{
  if (event->args.size() != 1)
  {
    Globals::console->println("Usage: load mapFilename");
    return;
  }

  IniFile ini(event->args.front());
  ini.read();

  Point p(ini["Level"]["Size"]);

  if (p.x == -1 || p.y == -1)
  {
    Globals::console->println("Invalid map");
    return;
  }

  //Globals::console->execute("new %d, %d", p.x*60, p.y*60); // FIXME
  Globals::console->execute("new %d, %d", p.x, p.y);

  m_backgroundType = ini["Level"]["Sky"];
  if (m_backgroundType == "")
  {
    m_backgroundType = "BlueSky";
  }

  m_gravity = ini.getFloat("Level", "Gravity");
  if (m_gravity == 0)
  {
    m_gravity = 0.085;
  }

  int c=1;
  while (true)
  {
    CStdString section;
    section.Format("Tile%d", c);
    c++;
    if (!ini.hasSection(section))
    {
      break;
    }

    string type = ini[section]["Type"];
    
    int x = ini.getInt(section, "X");
    int y = ini.getInt(section, "Y");
    
    IGMapperTile* tile = new IGMapperTile(type);
    //tile->setPosition(Point(x*60+30, y*60+30)); // FIXME
    tile->setPosition(Point(x, y));
    tile->readProperties(ini[section]);
    Globals::world->addThing(*tile);
    m_tiles.insert(tile);
//    if (x>=m_width || y>=m_height)
//    {
//      Globals::console->println("Invalid tile: %d, %d", x, y);
//      continue;
//    }
//    tileAt(x, y)->setType(type);
    
  }

  c=1;
  while (true)
  {
    CStdString section;
    section.Format("Entity%d", c);
    c++;
    if (!ini.hasSection(section))
    {
      break;
    }

    string type = ini[section]["Type"];
    
    int x = ini.getInt(section, "X");
    int y = ini.getInt(section, "Y");

    IGMapperEntity* ent = new IGMapperEntity(type);
    ent->readProperties(ini[section]);
    ent->setPosition(Point(x, y));
    Globals::world->addThing(*ent);
    m_ents.insert(ent);
  }

  c=1;
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

    Line line(FPoint(x1, y1), FPoint(x2, y2));

    string type = ini[section]["Type"];
    if (type == "")
    {
      type = "Grass";
    }

    m_faces.push_back(Face(type, line));
  }

  Globals::world->optimize();
}

void IGMapperConsoleListener::saveMap(ConsoleEvent* event)
{
  if (event->args.size() != 1)
  {
    Globals::console->println("Usage: save mapFilename");
    return;
  }

  IniFile ini(event->args.front());

  CStdString size;
  size.Format("%d, %d", m_width, m_height);
  ini["Level"]["Size"] = size;

  Rect r = Globals::world->getWorldDimensions();
  size.Format("%d, %d", r.w, r.h);
  ini["Level"]["WorldSize"] = size;

  ini["Level"]["Sky"] = m_backgroundType;
  ini["Level"]["Gravity"] = (boost::format("%f")%m_gravity).str();

  set<IGMapperTile*>::iterator it;
  int c = 1;
  for (it=m_tiles.begin(); it!=m_tiles.end(); it++)
  {
    IGMapperTile* tile = *it;

    CStdString section;
    section.Format("Tile%d", c);
    c++;

    ini[section]["X"] = toString(tile->getX());
    ini[section]["Y"] = toString(tile->getY());
    ini[section]["Type"] = tile->getType();

    tile->toIni(ini[section]);

    Globals::console->println("Tile (%s, %s) %s", ini[section]["X"].c_str(), ini[section]["Y"].c_str(), ini[section]["Type"].c_str());
  }

  set<IGMapperEntity*>::iterator i;
  c=1;
  for (i=m_ents.begin(); i!=m_ents.end(); i++)
  {
    CStdString section;
    section.Format("Entity%d", c);
    c++;

    (*i)->toIni(ini[section]);

    Globals::console->println("Entity (%s, %s) %s", ini[section]["X"].c_str(), ini[section]["Y"].c_str(), ini[section]["Type"].c_str());

  }

  list<Face>::iterator il;
  c=1;
  for (il=m_faces.begin(); il!=m_faces.end(); il++)
  {
    CStdString section;
    section.Format("Face%d", c);
    c++;
    
    Line l = (*il).getLine();
    ini[section]["X1"] = toString(l.p1.x);
    ini[section]["Y1"] = toString(l.p1.y);
    ini[section]["X2"] = toString(l.p2.x);
    ini[section]["Y2"] = toString(l.p2.y);

    ini[section]["Type"] = (*il).getType();

    Globals::console->println("Face (%s, %s), (%s, %s)", ini[section]["X1"].c_str(), ini[section]["Y1"].c_str(),  ini[section]["X2"].c_str(), ini[section]["Y2"].c_str());

  }

  ini.write();
  Globals::console->println("Wrote: %s", event->args.front().c_str());
}

void IGMapperConsoleListener::showChooseFace()
{
  IniFile ini("IGMapperDialogs.ini");
  ini.read();
  IGMapperChooseTileDlg dlg(ini, "Choose", Face::getTypes());
  dlg.doModal();

  currentFaceType = dlg.getChosedTile();  

  if (cur)
  {
    delete cur; 
    cur = 0;
  }

  if (curTile)
  {
    delete curTile;
    curTile = 0;
  }

}


void IGMapperConsoleListener::showChooseTile()
{
  IniFile ini("IGMapperDialogs.ini");
  ini.read();
  IGMapperChooseTileDlg dlg(ini, "Choose", Tile::getTypes());
  dlg.doModal();


  currentTileType = dlg.getChosedTile();  
  curTile = new IGMapperTile(currentTileType);
  
  if (cur)
  {
    delete cur; 
    cur = 0;
  }
  
}

void IGMapperConsoleListener::showEntities()
{
  IniFile ini("IGMapperDialogs.ini");
  ini.read();
  IGMapperChooseTileDlg dlg(ini, "Choose", Entity::getTypes());
  dlg.doModal();

  currentEntity = dlg.getChosedTile();  

  cur = new IGMapperEntity(dlg.getChosedTile());

  if (curTile)
  {
    delete curTile;
    curTile = 0;
  }
}

IGMapperTile* IGMapperConsoleListener::tileAt(Point p)
{
  set<IGMapperTile*>::iterator ie;
  for (ie=m_tiles.begin(); ie!=m_tiles.end(); ie++)
  {
    IGMapperTile* tile = *ie;
    if (tile->doesPointHit(p))
    {
      return tile;
    }
  }
  return 0;
}

IGMapperEntity* IGMapperConsoleListener::entAt(Point p)
{
  set<IGMapperEntity*>::iterator ie;
  for (ie=m_ents.begin(); ie!=m_ents.end(); ie++)
  {
    IGMapperEntity* ent = *ie;
    if (ent->doesPointHit(p))
    {
      return ent;
    }
  }
  return 0;
}

void IGMapperConsoleListener::mouseClicked(MouseClickEvent* event)
{
  if (Globals::world == 0)
  {
    return;
  }
  int size = Globals::tileSize;
  int halfSize = size/2;

  Point wp = Globals::world->translateScreenPoint(Point(event->x, event->y));

  if (event->button == RIGHT_BUTTON)
  {
    // lets do some properties on an entity
    IGMapperEntity* ent = entAt(wp);
    if (ent!=0)
    {
      ent->adjustProperties();
      return;
    }

    IGMapperTile* tile = tileAt(wp);
    if (tile != 0)
    {
      tile->adjustProperties();
      return;
    }
    
    return;
  }


  if (event->button == MIDDLE_BUTTON)
  {
    // delete something!
    // check faces
    list<Face>::iterator i;
    for (i=m_faces.begin(); i!=m_faces.end(); i++)
    {
      Face face = (*i);
      if (face.isPointInHotSpot(wp))
      {
        m_faces.erase(i);
        return;
      }
    }
    // check ents
    IGMapperEntity* ent = entAt(wp);
    if (ent!=0)
    {
      m_ents.erase(ent);
      Globals::world->removeThing(*ent);
      Globals::world->optimize();
      delete ent;
      return;
    }
  

    // check tiles
    int mx = (wp.x/size);
    int my = (wp.y/size);
      
    IGMapperTile* tile = tileAt(wp);
    if (tile)
    {
      m_tiles.erase(tile);
      Globals::world->removeThing(*tile);
      Globals::world->optimize();
      delete tile;
    }
    return;
  }

  switch (m_state)
  {
  case ES_NONE:
    {
      IGMapperEntity* ent = entAt(wp);
      if (ent)
      {
        cur = ent;
        m_ents.erase(ent);
        Globals::world->removeThing(*ent);
        Globals::world->optimize();
        m_state = ES_ENTITY;
        return;
      }
      IGMapperTile* tile = tileAt(wp);
      if (tile != 0)
      {
        curTile = tile;
        m_tiles.erase(tile);
        Globals::world->removeThing(*tile);
        Globals::world->optimize();
        m_state = ES_TILE;
        return;
      }
    }
    break;
  case ES_TILE:
    {
      if (curTile == 0)
      {
        return;
      }
      
//      int mx = (wp.x/size);
//      int my = (wp.y/size);
      
      IGMapperTile* tile = curTile;
      tile->setPosition(Point(wp.x/10*10, wp.y/10*10));
      Globals::world->addThing(*tile);
      Globals::world->optimize();
//      tileAt(mx, my)->setType(currentTileType);
      m_tiles.insert(tile);
      curTile = new IGMapperTile(tile->getType());
      return;
    }
    break;
  case ES_ENTITY:
    {
      // else is entity
      IGMapperEntity* ent = cur; 
      ent->setPosition(wp);
      Globals::world->addThing(*ent);
      Globals::world->optimize();
      m_ents.insert(ent);
      cur = new IGMapperEntity(ent->getType());
    }
    break;
  case ES_FACE_CLICK1:
    {
      m_click1 = Globals::world->translateScreenPoint(Point(event->x, event->y));
      m_state = ES_FACE_CLICK2;
    }
    break;
  case ES_FACE_CLICK2:
    {
      Point click2 = Globals::world->translateScreenPoint(Point(event->x, event->y));
      m_faces.push_back(Face(currentFaceType, Line(m_click1, click2)));
      m_click1 = click2;
      m_state = ES_FACE_CLICK2; // stay here until ESC
    }
    break;
  default:
    {
      MessageBeep(-1);
    }
    break;
  }
}

void IGMapperConsoleListener::postDraw()
{
  if (Globals::world == 0)
  {
    return;
  }

  if (Globals::console->isShowing())
  {
    return;
  }

  int tileSize = Globals::tileSize;
  int halfSize = tileSize/2;
  
  Point m = theGame.getMousePos();
  Point gm = Globals::world->translateScreenPoint(m);

  switch(m_state)
  {
  case ES_NONE:
    break;
  case ES_TILE:
    {
      // draw a ring around current mouse tile
      //Point topLeft( (m.x/tileSize)*tileSize)
      curTile->draw(Display::getInstance(), m.x/10*10, m.y/10*10);
    }
    break;
  case ES_ENTITY:
    {
      cur->draw(Display::getInstance(), m.x, m.y);
    }
    break;
  case ES_FACE_CLICK1:
    {
      // nothing special?
    }
    break;
  case ES_FACE_CLICK2:
    {
      // draw line from m_click1 to here
      Point p1 = Globals::world->translateToScreen(m_click1);
      Display::getInstance()->drawLine(p1.x, p1.y, m.x, m.y, 0, 255, 0, 255);
    }
    break;
  default:
    {
    }
  }
  
//  if (m_state == ES_FACE_CLICK1 || m_state == ES_FACE_CLICK2)
  if (theGame.uiSystem.topModal() == 0)
  {
    list<Face>::iterator i;
    for (i=m_faces.begin(); i!=m_faces.end(); i++)
    {
//      Line l = (*i).getLine();
//      Point p1 = Globals::world->translateToScreen(l.p1);
//      Point p2 = Globals::world->translateToScreen(l.p2);
//      Display::getInstance()->drawLine(p1.x, p1.y, p2.x, p2.y, 255, 0, 0, 255);
//      Point m = Globals::world->translateToScreen(l.middle());
//      circleRGBA(Display::getInstance()->getSDLSurface(), m.x, m.y, 10, 255, 0, 0, 255);
      Face& face = *i;
      face.draw();
    }
  }
  
}
