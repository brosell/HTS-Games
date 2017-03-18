#pragma warning (disable : 4786 4503 4530)
#include "SplashScreen.h"

SplashScreen::SplashScreen(string background)
{
  m_background = Display::getInstance()->acquire(background);
}

SplashScreen::~SplashScreen()
{
  Display::getInstance()->release(m_background);
}

void SplashScreen::paint(Display* surface)
{
  surface->blit(m_background, 0, 0);
}
