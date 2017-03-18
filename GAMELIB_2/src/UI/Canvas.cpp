#pragma warning (disable : 4786 4503 4530)
#include "Canvas.h"


void Canvas::paint(Display* surface)
{
  if (m_image != 0)
  {
    Rect r = getTranslatedPosition();
    surface->blit(m_image, r.x, r.y);
  }
}
