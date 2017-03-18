#pragma warning (disable : 4786 4503 4530)
#include "UI/SkinCanvas.h"
#include "BR_Game.h"
#include "Misc/AssetManager.h"

SkinCanvas::~SkinCanvas()
{
  if (m_skin)
  {
    theGame.assetManager->releaseSkin(m_skin);
  }
}

void SkinCanvas::setSkin(string assetName)
{
  if (m_skin)
  {
    theGame.assetManager->releaseSkin(m_skin);
    m_skin = 0;
  }
  m_skin = theGame.assetManager->getSkin(assetName);
}

void SkinCanvas::paint(Display* display)
{
  if (m_skin!=0)
  {
    Rect r = getTranslatedPosition();
    m_skin->blit(display, r.x, r.y, false);
  }
}
