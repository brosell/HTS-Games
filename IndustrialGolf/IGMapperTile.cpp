#pragma warning (disable : 4786 4503 4530)
#include "IGMapperTile.h"
#include "Globals.h"
#include "StdString.h"
#include "StringTokenizer.h"
#include "propertiesDialog.h"

IGMapperTile::IGMapperTile(string type):
Thing(10)
{
  loadSkins();

  m_type = type;
  setSkin(m_skins[type]);
}

void IGMapperTile::loadSkins()
{
  IniFile ini("TileDef.ini");
  ini.read();
  IniFile::iterator pair;
  for (pair = ini.begin(); pair!=ini.end(); pair++)
  {
    string type = pair->first;
    RotateSkinHandle skin = Globals::am->getRotateSkin(ini[type]["Skin"]);
    m_skins[type] = skin;
  }

  m_properties["Z"] = "-1";

//  setSkin("skin", Globals::assetManager->getRotateSkin(s_ini[type]["Skin"]));
}

IGMapperTile::~IGMapperTile()
{
}

void IGMapperTile::adjustProperties()
{
  PropertiesDialog props(m_properties);
  props.doModal();
  int z = atoi(m_properties["Z"].c_str());
  if (z>0)
  {
    setZ(z);
    Globals::world->optimize();
  }
}


void IGMapperTile::setType(string type)
{
  m_type = type;
  setSkin(m_skins[type]);
}

Line IGMapperTile::parseLine(string line)
{
  Line l(FPoint(-1, -1), FPoint(-1, -1));
  StringTokenizer st(line, ", ");
  if (st.countTokens() == 4)
  {
    l.p1.x = atoi(st.nextToken());
    l.p1.y = atoi(st.nextToken());
    l.p2.x = atoi(st.nextToken());
    l.p2.y = atoi(st.nextToken());
  }
  else
  {
    line = line;
  }
  return l;
}

void IGMapperTile::toIni(StringMap& theMap)
{
  map<string, string>::iterator pair;
  for (pair = m_properties.begin(); pair!=m_properties.end(); pair++)
  {
    theMap[pair->first] = pair->second;
  }
}

void IGMapperTile::readProperties(StringMap& theMap)
{
  map<string, string>::iterator pair;
  for (pair = m_properties.begin(); pair!=m_properties.end(); pair++)
  {
    string val = theMap[pair->first];
    if (val != "")
    {
      m_properties[pair->first] = val;
    }

  }

  int z = atoi(m_properties["Z"].c_str());
  if (z>0)
  {
    setZ(z);
    Globals::world->optimize();
  }

}