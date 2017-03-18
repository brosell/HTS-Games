#pragma warning (disable : 4503)
#include "SkinCanvas.h"


SkinCanvas::SkinCanvas():
m_showing(false),
m_currentSkin(0)
{
}

SkinCanvas::~SkinCanvas()
{
  map<string, SharedSkin*>::iterator pair;
  for (pair=m_skins.begin(); pair!=m_skins.end(); pair++)
  {
    delete pair->second;
  }
  m_skins.clear();
}

void SkinCanvas::addSkin(string assetName)
{
  SharedSkin* skin = theGame.assetManager->getSkin(assetName);
  if (skin)
  {
    if (m_skins[assetName] != 0)
    {
      delete m_skins[assetName];
    }
    m_skins[assetName] = skin;
  }
}

void SkinCanvas::removeSkin(string assetName)
{
  m_skins.erase(assetName);
}

void SkinCanvas::skinLooped(SkinLoopEvent* event)
{
  lassert (event->skin == m_currentSkin);
  
  event->skin->removeListener(this);
  m_currentSkin = 0;
}

void SkinCanvas::paint(Display* display)
{
  if (!m_currentSkin)
  {
    if (m_queue.size())
    {
      m_currentSkin = m_queue.front();
      m_currentSkin->addListener(this);
      m_currentSkin->reset();
      m_queue.pop_front();
    }
  }
  
  if (m_currentSkin)
  {
    Rect r = getPosition();
    m_currentSkin->blit(display, r.x, r.y, false);
  }
}
  
void SkinCanvas::show(string skinName)
{
  m_queue.push_back(m_skins[skinName]);
  m_skins[skinName]->reset();
}
