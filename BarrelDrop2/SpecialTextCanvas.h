#ifndef SpecialTextCanvas_h
#define SpecialTextCanvas_h

#include "BR_Game.h"
#include "Timer.h"
#include "AssetManager.h"
#include "SharedSkin.h"
#include "ParticleTraits.h"

#include <list>

class SpecialTextCanvas: public Canvas, public ParticleListener
{
public:
  SpecialTextCanvas();
  virtual string getName() { return "SpecialTextCanvas"; }


  void showText(string str, int x, int y, string font = "font_Default");

  void blowUpBlock(int x, int y)
  {
    ExplodingBlockParticleTraits* traits = new ExplodingBlockParticleTraits;
    m_particleSystem.fire(Point(x, y), 6, traits, traits);
  }

  void fire(Point origin, int count, ParticleTraits* traits, ParticleListener* listener = 0)
  {
    m_particleSystem.fire(origin, count, traits, listener);
  }

//  virtual void particlesDone(ParticleEvent* event) 
//  { 
//    std::map<int, PrintStringParticleTraits*>::iterator pair;
//    pair = m_printTraits.find(event->id);
//    if (pair != m_printTraits.end())
//    {
//      m_printTraits.erase(event->id);
//      delete pair->second;
//    }
//  }

  virtual void paint(Display* display)
  {
    m_particleSystem.draw(display);
  }
  
private:
  ParticleSystem m_particleSystem;

  std::list<PrintStringParticleTraits*> m_traits;
};

#endif