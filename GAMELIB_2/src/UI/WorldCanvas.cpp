#pragma warning (disable : 4786 4503 4530)
#include "WorldCanvas.h"

void WorldCanvas::paint(Display* surface)
{
  if (m_world)
  {
    Rect r=getTranslatedPosition();
    m_world->setViewportPhysical(r.x, r.y, r.w, r.h);
    
    m_world->draw(surface);
  }
}
