#pragma warning (disable : 4786)

#include "Skin.h"

Skin::Skin():
m_currentTexture(0)
{
}

Skin::~Skin()
{
  m_listeners.clear();
}

void Skin::addListener(SkinListener* listener)
{
  m_listeners.insert(listener);
}
void Skin::removeListener(SkinListener* listener)
{
  m_listeners.erase(listener);
}

void Skin::blit(Display* display, int x, int y, bool centerCoords)
{
  HTexture texture = currentFrame();
  if (texture != 0)
  {
    if (centerCoords)
    {
      const TextureInfo* ti = display->getTextureInfo(texture);
      display->blit(texture, x-(ti->w/2), y-(ti->h/2));
    }
    else
    {
      display->blit(texture, x, y);
    }
  }
}


void Skin::skinLooped()
{
  m_loopEvent.skin = this;
  set<SkinListener*>::iterator i;
  set<SkinListener*> copy(m_listeners);
  for (i=copy.begin(); i!=copy.end(); i++)
  {
    (*i)->skinLooped(&m_loopEvent);
  }
}