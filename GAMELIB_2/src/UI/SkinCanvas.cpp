#pragma warning (disable : 4786 4503 4530)
#include "SkinCanvas.h"
#include "BR_Game.h"

SkinCanvas::~SkinCanvas()
{
}

void SkinCanvas::setSkin(string assetName)
{
  if (m_skin.isValid())
  {
    m_skin->removeListener(this);
  }
  m_skin = theGame.am->getSkin(assetName);
  if (m_skin.isValid())
  {
    m_skin->addListener(this);
  }

  setDirty(true); 
}

void SkinCanvas::paint(Display* display)
{
  if (m_skin.isValid())
  {
    Rect r = getTranslatedPosition();
    m_skin->blit(display, r.x, r.y, false);
  }
}
