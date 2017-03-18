#ifndef SplashScreen_h
#define SplashScreen_h

#include "BR_Game.h"

class SplashScreen: public Canvas
{
public:
  SplashScreen(string background);
  ~SplashScreen();

  virtual void paint(Display* surface);

private:
  HTexture m_background;
};

#endif
