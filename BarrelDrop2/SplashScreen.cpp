#pragma warning (disable : 4786 4503 4530)
#include "SplashScreen.h"
#include "Globals.h"

SplashScreen::SplashScreen(string background)
{
  m_background = Globals::assetManager->getTexture(background);
}

SplashScreen::~SplashScreen()
{

}

void SplashScreen::paint(Display* surface)
{
  surface->blit(m_background, 0, 0);
}
