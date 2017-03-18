#pragma warning (disable : 4786 4503 4530)
#include "SpecialTextCanvas.h"

SpecialTextCanvas::SpecialTextCanvas()
{
  for (int c=0; c<10; c++)
  {
    m_traits.push_back(new PrintStringParticleTraits);
  }
}


void SpecialTextCanvas::showText(string str, int x, int y, string font)
{
  PrintStringParticleTraits* traits = m_traits.front();
  m_traits.pop_front();
  m_traits.push_back(traits);
  traits->setFont(font);
  traits->setString(str);

  m_particleSystem.fire(Point(x, y), 1, traits, 0);
}
