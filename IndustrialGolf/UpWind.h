#ifndef UpWind_h
#define UpWind_h

#include "Entity.h"
#include "2dVector.h"
#include "ThinkScheduler.h"

class UpWind: public Entity
{
public:
  UpWind();
  ~UpWind();

  void setBlow(int a, int p)
  {
    m_toBlow = Vector::createFromAngle(a, p);
  }

  virtual void logic(float factor);

private:
  RotateSkinHandle m_skin;
  Vector m_toBlow;

  TypeThinkDelegate<UpWind> m_logic;
  void logic();
};

#endif