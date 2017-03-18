#ifndef IGMapperEntity_h
#define IGMapperEntity_h

#include "BR_Game.h"

class IGMapperEntity: public Thing
{
public:
  IGMapperEntity(string type);
  ~IGMapperEntity();

  void adjustProperties();

  string getType() { return m_type; }

  void toIni(StringMap& theMap);
  void readProperties(StringMap& theMap);

private:
  RotateSkinHandle m_skin;
  string m_type;
  map<string, string> m_properties;
};

#endif