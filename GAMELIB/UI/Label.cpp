#pragma warning (disable : 4786 4503 4530)
#include "Label.h"

#include "SDL_gfxPrimitives.h"

void Label::paint(Display* surface)
{
  Rect r = getTranslatedPosition();
  Font* font = getFont();
  int dx, dy;

  surface->pushClipRect(r);
  
  switch(m_vertJust)
  {
  case JUST_TOP:
    dy = r.y;
    break;
  case JUST_BOTTOM:
    dy = (r.y+r.h) - font->getFontHeight();
    break;
  case JUST_MIDDLE:
    dy = (r.y+(r.h/2)) - (font->getFontHeight()/2);
    break;
  default:
    lassert(false);
  }

  switch(m_horizJust)
  {
  case JUST_LEFT:
    dx = r.x;
    break;
  case JUST_RIGHT:
    dx = (r.x+r.w) - (font->getTextWidth(m_text));
    break;
  case JUST_CENTER:
    dx = (r.x+(r.w/2)) - (font->getTextWidth(m_text)/2);
    break;
  default:
    lassert(false);
  }

  font->drawLine(surface, m_text, dx, dy);
  surface->popClipRect();
}

