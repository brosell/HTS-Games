#pragma warning (disable : 4786)

#include "Skin.h"

Skin::Skin():
m_currentTexture(0)
{
  m_loopEvent.skin = this;
  m_frameEvent.skin = this;
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
      if (ti == 0)
      {
        lassert(ti != 0);
      }
      else
      {
        display->blit(texture, x-(ti->w/2), y-(ti->h/2));
      }
    }
    else
    {
      display->blit(texture, x, y);
    }
  }
}


void Skin::skinLooped()
{
  set<SkinListener*>::iterator i;
  for (i=m_listeners.begin(); i!=m_listeners.end(); i++)
  {
    (*i)->skinLooped(&m_loopEvent);
  }
}

void Skin::frameChanged()
{
  set<SkinListener*>::iterator i;
  for (i=m_listeners.begin(); i!=m_listeners.end(); i++)
  {
    (*i)->frameChanged(&m_frameEvent);
  }
}  