#include "StraitLineMotion.h"
#include <math.h>

void StraitLineMotion::makeUnitVector(float vx, float vy, float& uvx, float& uvy)
{
  m_length=(float)(sqrt(vx*vx + vy*vy));
  if (m_length==0)
  {
    int x=0;
  }
  uvx=vx/m_length;
  uvy=vy/m_length;
}

void StraitLineMotion::tickAndMove(int& retX, int& retY)
{
  if (m_vel == 0 || (m_uvx==0 && m_uvy==0))
  {
    setMoved(false);
    return;
  }
  setMoved(true);

  m_x+=(m_uvx*m_vel);
  m_y+=(m_uvy*m_vel);
  
  if (m_x > 640-m_w)
  {
    bounceVirtSurface();
    m_x = (float)640-m_w;
  }

  if (m_x < 0)
  {
    bounceVirtSurface();
    m_x = 0;
  }

  if (m_y > 480-m_h)
  {
    bounceHorizSurface();
    m_y=(float)480-m_h;
  }

  if (m_y < 0)
  {
    bounceHorizSurface();
    m_y=0;
  }

  retX=(int)(m_x+0.5);
  retY=(int)(m_y+0.5);
}