#ifndef SpaceTileMap_h
#define SpaceTileMap_h

#include "BR_Game.h"
#include "SpaceTile.h"
#include <map>
#include <set>
#include <algorithm>
using namespace std;

const int MAX_MAPSIZE = 1024;

enum
{
  UP_RIGHT = 0,
  RIGHT,
  DOWN_RIGHT,
  DOWN_LEFT,
  LEFT,
  UP_LEFT
};

enum
{
  DIR_X = 0,
  DIR_Y = 1
};



class SpaceTileMap: public map<int, map<int, SpaceTile*> >, 
                    public ConsoleListener, 
                    public MouseListener,
                    public KeyListener
{
public:

  SpaceTileMap(int sideLength);

  void setType(int x, int y, int owner, TileType type);

  // prepare - after all the tiles are set, call this to add to the world
  void prepare();

  virtual void consoleCommand(ConsoleEvent* event);
  virtual void mouseClicked(MouseClickEvent* event);
  virtual void mouseMoved(MouseMoveEvent* event);

  virtual void keyPressed(KeyPressEvent* event);

  Point getCoord(int worldX, int worldY);
  TileType getTypeAt(int worldX, int worldY);

  int getPixelWidth() { return m_width*m_a; }
  int getPixelHeight() { return m_height*(m_sideLength + m_h); }

  void removeAll();
  void setSize(int w, int h);

  void saveMap(string mapname);
  void loadMap(string mapname);
  void listMaps();
  void delMap(string mapname);

  void test(int x1, int y1, int x2, int y2);

  int neighborsInRadius(int x, int y, int r, SpaceTile** ret);

private:
  int m_width; // in tiles
  int m_height; // in tiles
  int m_r;
  int m_a;
  int m_b;
  int m_h;
  float m_m;
  int m_sideLength;

//  unsigned char* m_pixelMap;

  SpaceTile* m_selected;
  TileType lastType;
};

#endif