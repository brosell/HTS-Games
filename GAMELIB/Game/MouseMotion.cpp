#include "MouseMotion.h"

int MouseMotion::s_x=100;

void MouseMotion::tickAndMove(int &retX, int& retY)
{
  int x;
  SDL_GetMouseState(&x, NULL);
  retX=x-(m_w/2);
  if (retX < 0) retX=0;
  if (retX > (640-m_w)) retX=640-m_w;
  retY=(int)m_y;
  setMoved(true);
}

