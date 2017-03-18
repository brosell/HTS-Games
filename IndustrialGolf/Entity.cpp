#pragma warning (disable : 4503 4530 4786)
#include "Entity.h"

Entity::Entity(int z):
Thing(z)
{

}

Entity::~Entity()
{

}

list<string> Entity::getTypes()
{
  IniFile ini("EntityDef.ini");
  ini.read();
  
  list<string> ret;
  
  IniFile::iterator pair;
  for (pair = ini.begin(); pair!=ini.end(); pair++)
  {
    ret.push_back(pair->first);
  }
  
  return ret;
}
