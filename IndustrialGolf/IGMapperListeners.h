#ifndef IGMapperListeners_h
#define IGMapperListeners_h

#include "BR_Game.h"
#include "IGMapperTile.h"
#include "IGMapperEntity.h"
#include "Face.h"
#include <set>
using namespace std;

enum EditorState
{
  ES_NONE,
  ES_TILE,
  ES_ENTITY,
  ES_FACE_CLICK1,
  ES_FACE_CLICK2
};


class IGMapperConsoleListener: public ConsoleListener, public KeyListener, public MouseListener, public DrawListener
{
public:
  IGMapperConsoleListener();
  ~IGMapperConsoleListener();

  virtual void consoleCommand(ConsoleEvent* event);
  virtual void keyPressed(KeyPressEvent* event);

  virtual void mouseClicked(MouseClickEvent* event);

  virtual void preDraw()
  {
    theGame.screen->clear();
  }
  virtual void postDraw();
  
protected:
  void newMap(ConsoleEvent* event);
  void loadMap(ConsoleEvent* event);
  void saveMap(ConsoleEvent* event);
  void sizeMap(ConsoleEvent* event);

  void showChooseTile();
  void showEntities();
  void showChooseFace();
  void showLevelProperties();

  IGMapperEntity* entAt(Point p);

  void clearMap();
  void initMap(int w, int h);
  IGMapperTile* tileAt(Point p);


//  IGMapperTile** m_tiles;
  set<IGMapperEntity*> m_ents;
  set<IGMapperTile*> m_tiles;
  int m_width;
  int m_height;

  float m_gravity;

  string currentTileType;
  string currentEntity;
  string currentFaceType;

  IGMapperEntity* cur;

  IGMapperTile* curTile;

  EditorState m_state;

  Point m_click1;

  list<Face> m_faces;
  string m_backgroundType;

};

#endif