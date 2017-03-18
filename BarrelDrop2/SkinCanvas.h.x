#include "BR_Game.h"
#include "Timer.h"
#include "Misc/AssetManager.h"
#include "Graphics/SharedSkin.h"
#include "Misc/ParticleSystem.h"

class TextParticle
{
public:
  static int getFPS() { return 15; }
  static int getMaxLifespan() { return 30; }
  static int getCount() { return 1; }



  ~TextParticle()
  {
    if (m_skin)
    {
      delete m_skin;
    }
  }

  void decay()
  {
    if (isDecayed())
    {
      return;
    }
    m_age++;
    m_location.x += m_velocity.x;
    m_location.y += m_velocity.y;
  }

  bool isDecayed() { return m_age > m_lifespan; }
  void draw(Display* display) 
  { 
    m_skin->blit(display, m_location.x, m_location.y);
  }
protected:
  TextParticle(Point origin, string assetName): m_location(origin), m_age(0), m_lifespan(0), m_skin(0)
  {
    m_lifespan = 30;
    m_velocity.x = 0;
    m_velocity.y = 10;
    m_skin = theGame.assetManager->getSkin(assetName);
  }

private:
  Point m_location;
  Vector m_velocity;
  int m_age;
  int m_lifespan;
  Skin* m_skin;

  TextParticle(const TextParticle& o);
};

class LevelUpParticle: public TextParticle
{
public:
  LevelUpParticle(Point origin): TextParticle(origin, "skn_Level_Up") { }
};

class SkinCanvas: public Canvas, public SkinListener
{
public:
  SkinCanvas();
  ~SkinCanvas();
  virtual string getName() { return "SkinCanvas"; }

  void addSkin(string assetName);
  void removeSkin(string assetName);

  virtual void skinLooped(SkinLoopEvent* event);

  virtual void paint(Display* display);
    
  void show(string skinName);
  void stop();

private:
  map<string, SharedSkin*> m_skins;
  list<SharedSkin*> m_queue;
  
  SharedSkin* m_currentSkin;
  bool m_showing;

//  ParticleBlast<TextParticle<"skn_Level_Up"> > m_blast;
};