#include "ThingCollection.h"
#include <stdlib.h>
#include <memory.h>
#include <functional>

#include "Utils.h"

#include "Thing.h"
#include "Misc/GameMath.h"


#include <algorithm>

ThingCollection::ThingCollection()
{
  clear();  
}

ThingCollection::~ThingCollection()
{

}

void ThingCollection::clear()
{
  m_things.clear();
}

bool ThingCollection::add(Thing* thing)
{
  m_things.push_back(thing);
  return true;
}

void ThingCollection::remove(Thing* thing)
{
  m_things.erase(std::remove(m_things.begin(), m_things.end(), thing), m_things.end());
}

int ThingCollection::count()
{
  return m_things.size();
}


void ThingCollection::sort()
{
  std::sort(m_things.begin(), m_things.end(), SortThingByZ());
}
