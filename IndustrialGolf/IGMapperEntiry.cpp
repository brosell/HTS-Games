#include "IGMapperEntity.h"
#include "Globals.h"
#include "StringTokenizer.h"
#include "PropertiesDialog.h"
#include "Convert.h"

IGMapperEntity::IGMapperEntity(string type):
Thing(15)
{
  IniFile ini("EntityDef.ini");
  ini.read();

  m_skin=Globals::am->getRotateSkin(ini[type]["Skin"]);
  setSkin(m_skin);

  m_type = type;

  string props = ini[type]["Properties"];
  StringTokenizer st(props, " ,");
  while (st.hasMoreTokens())
  {
    m_properties[st.nextToken()] = "";
  }
  m_properties["Id"] = "";
  m_properties["InitialState"] = "1";
  m_properties["Z"] = "-1";

}

IGMapperEntity::~IGMapperEntity()
{
  
}

void IGMapperEntity::adjustProperties()
{
  PropertiesDialog props(m_properties);
  props.doModal();
  map<string, string>::iterator pair = m_properties.find("Angle");
  if (pair != m_properties.end())
  {
    setDrawAngle(atoi(pair->second.c_str()));
  }

  int z = atoi(m_properties["Z"].c_str());
  if (z>0)
  {
    setZ(z);
    Globals::world->optimize();
  }
}

void IGMapperEntity::toIni(StringMap& theMap)
{
  theMap["X"] = toString(getX());
  theMap["Y"] = toString(getY());
  theMap["Type"] = m_type;

  map<string, string>::iterator pair;
  for (pair = m_properties.begin(); pair!=m_properties.end(); pair++)
  {
    theMap[pair->first] = pair->second;
  }
}

void IGMapperEntity::readProperties(StringMap& theMap)
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
  pair = m_properties.find("Angle");
  if (pair != m_properties.end())
  {
    setDrawAngle(atoi(pair->second.c_str()));
  }

  int z = atoi(m_properties["Z"].c_str());
  if (z>0)
  {
    setZ(z);
    Globals::world->optimize();
  }
}