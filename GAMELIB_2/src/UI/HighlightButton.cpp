#pragma warning (disable : 4786 4503 4530)

#include "HighlightButton.h"
#include "BR_Game.h"
#include "SDL_rotozoom.h"

HighlightButton::HighlightButton(): m_glass(-1)
{
}

HighlightButton::~HighlightButton()
{
  if (m_glass > 0)
  {
    theGame.screen->release(m_glass);
  }
}

void HighlightButton::createHighlight()
{
  SDL_Surface* glass = loadSDLSurface(m_highlight.c_str());
  double zoomX = (double)(getPosition().w) / (double)glass->w;
  double zoomY = (double)(getPosition().h) / (double)glass->h;

  SDL_Surface* zoomed = zoomSurface(glass, zoomX, zoomY, 1);

  m_glass = theGame.screen->prepare(zoomed); //->pixels, zoomed->w, zoomed->h);
  SDL_FreeSurface(glass);
  SDL_FreeSurface(zoomed);
}


void HighlightButton::paint(Display* surface)
{
  if (m_glass == -1)
  {
    createHighlight();
  }

  if (isMouseOver())
  {
    Rect r=getTranslatedPosition();
    surface->blit(m_glass, r.x, r.y);
  }
}