#ifndef IGMapperTile_h
#define IGMapperTile_h

#include "BR_Game.h"
#include <string>
#include <map>
using namespace std;

class IGMapperTile: public Thing
{
public:
  IGMapperTile(string type);
  ~IGMapperTile();

  void setType(string type);
  string getType() { return m_type; }

  void adjustProperties();

  void toIni(StringMap& theMap);
  void readProperties(StringMap& theMap);
  
private:
  Line parseLine(string line);

  void loadSkins();
  string m_type;
  map<string, RotateSkinHandle> m_skins;

  list<Line> m_faces;
  map<string, string> m_properties;
};

#endif