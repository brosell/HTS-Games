#ifndef SpaceTileMap_h
#define SpaceTileMap_h

#include "SpaceTile.h"

#include "BR_Game.h"
#include "IniFile.h"

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



class SpaceTileMap: /*public map<int, map<int, SpaceTile*> >,*/ public ConsoleListener
{
public:
  
  SpaceTileMap(int sideLength);

  void addTile(int x, int y, TileType type, int owner);

  SpaceTile* get(int x, int y) { return m_map[y*m_width + x]; }
  
  // prepare - after all the tiles are set, call this to add to the world
  void prepare();

  Point getCoord(int worldX, int worldY);
  SpaceTile* getTileAt(int worldX, int worldY);
  TileType getTypeAt(int worldX, int worldY);
  bool isNavigable(int worldX, int worldY);

  int getNeighbors(int x, int y, SpaceTile** ret);
  void getTilesInRadius(int x, int y, int r, set<SpaceTile*>& ret);

  bool calculateRoute(int x1, int y1, int x2, int y2, list<SpaceTile*>& ret);

  int getPixelWidth() { return (m_width-1)*m_a; }
  int getPixelHeight() { return (m_height-1)*(m_sideLength + m_h); }

  void loadMap(string mapname);
  void listMaps();
  virtual void consoleCommand(ConsoleEvent* event);

  void removeAll();
  void setSize(int w, int h);

  void calculateFogOfWar();
  bool isInFog(int x, int y);

  //////////////////////////
  // Neighbors
  //////////////////////////
  int neighborsInRadius(int x, int y, int r, SpaceTile** ret);

protected:

  void isTileObscured(SpaceTile* dest, SpaceTile* src);

private:
  int m_width; // in tiles
  int m_height; // in tiles
  int m_r;
  int m_a;
  int m_b;
  int m_h;
  float m_m;
  int m_sideLength;

  SpaceTile** m_map;

  unsigned char* m_pixelMap;
};

#endif