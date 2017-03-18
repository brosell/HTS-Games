#ifndef _StraitLineMotion_h
#define _StraitLineMotion_h

#include "Motion.h"
#include <math.h>

#include "Misc/2dVector.h"

class StraitLineMotion: public Motion
{
public:
  StraitLineMotion(float x, float y, int w, int h, float vx, float vy, float vel) // goemetric vector and velocity
    :Motion(x, y, w, h)
  {
    setVector(vx, vy, vel);
  }

  void setVector(float vx, float vy, float vel)
  {
    m_vx=vx;
    m_vy=vy;
    m_vel=vel;
    makeUnitVector(vx, vy, m_uvx, m_uvy);
  }

  void setVector(float vx, float vy)
  {
    setVector(vx, vy, m_vel);
  }

  void setXVector(float vx)
  {
    m_vx=vx;
    makeUnitVector(vx, m_vy, m_uvx, m_uvy);
  }

  void incVelocity(int v)
  {
    m_vel+=v;
    setVector(m_vx, m_vy, m_vel);
  }

  void tickAndMove(int& retX, int& retY);


  void bounceVirtSurface()
  {
    setVector(-m_vx, m_vy, m_vel);
  }
  
  void bounceHorizSurface()
  {
    setVector(m_vx, -m_vy, m_vel);
  }

  void makeUnitVector(float vx, float vy, float& uvx, float& uvy);


private:
  float m_vx;
  float m_vy;
  float m_vel;

  float m_length;

  float m_uvx;
  float m_uvy;

};


#endif
