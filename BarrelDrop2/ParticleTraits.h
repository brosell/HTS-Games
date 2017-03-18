#ifndef ParticleTraits_h
#define ParticleTraits_h

#include "ParticleSystem.h"
#include "AssetManager.h"
#include "2dVector.h"

class SpecialTextParticleTraits: public ParticleTraits
{
public:

  SpecialTextParticleTraits(string assetName = "")
  {
    if (assetName != "")
    {
      m_skin=theGame.am->getSkin(assetName);
    }
    else
    {
      m_skin = SharedSkinHandle();
    }
  }
  ~SpecialTextParticleTraits()
  {
  }
  virtual void init(Particle* particle) 
  { 
    Vector v(0, -30);
    particle->setVelocity(v);
  }

  virtual void decay(Particle* particle) 
  {
    Vector v=particle->getVelocity();
    v.y+=2;
    particle->setVelocity(v);
  }

  virtual void draw(Particle* particle, Display* display) 
  { 
    if (m_skin.isValid())
    {
      FPoint l = particle->getLocation();
      m_skin->blit(display, l.x, l.y);
    }
  }

  virtual int getFps() { return 30; }
  virtual int getLifespan() { return 30; }

private:
  SharedSkinHandle m_skin;
};

class PrintStringParticleTraits: public SpecialTextParticleTraits, public ParticleListener
{
public:
  PrintStringParticleTraits(string tosay="", string fontAsset=""): 
      SpecialTextParticleTraits(),
      m_string(tosay)
  {
    m_font = theGame.am->getFont(fontAsset);
  }

  virtual void init(Particle* particle) 
  { 
    Vector v(0, -30);
    particle->setVelocity(v);
  }


  virtual void draw(Particle* particle, Display* display) 
  { 
    if (m_font.isValid())
    {
      FPoint l = particle->getLocation();
      int ts = m_font->getTextWidth(m_string);
      int x = l.x-(ts/2);
      int y = l.y-(m_font->getFontHeight()/2);
      m_font->drawLine(display, m_string, x, y);
    }
  }

  virtual int getLifespan() { return 30; }

  virtual void particlesDone(ParticleEvent* event) 
  { 
    //delete this;
  }

  void setString(std::string str)
  {
    m_string = str;
  }

  void setFont(std::string assetName)
  {
    m_font = theGame.am->getFont(assetName);
  }

private:
  FontHandle m_font;
  string m_string;
};

extern string scolors[];

class ExplodingBlockParticleTraits: public ParticleTraits, public ParticleListener
{
public:

  ExplodingBlockParticleTraits(string assetName = "skn_Exploding_Barrel")
  {
    m_skin=theGame.am->getRotateSkin(assetName);
  }

  ExplodingBlockParticleTraits(int color)
  {
    char assetName[128];
    if (color < 10)
    {
      sprintf(assetName, "skn_Exploding_Barrel_%s", scolors[color].c_str());
    }
    else
    {
      sprintf(assetName, "skn_Exploding_Barrel_Black");
    }

    
    m_skin=theGame.am->getRotateSkin(assetName);
  }


  ~ExplodingBlockParticleTraits()
  {
  }
  virtual void init(Particle* particle);

  virtual void decay(Particle* particle) 
  {
    Vector v=particle->getVelocity();
    v.x*= (float)0.9;
    v.y+=2;
    particle->setVelocity(v);
    
    int r=m_skin->currentRotation();
    r++;
    if (r >= m_skin->getNumRotations())
    {
      r=0;
    }
    m_skin->setRotation(r);
  }

  virtual void draw(Particle* particle, Display* display) 
  { 
    if (m_skin.isValid())
    {
      FPoint l = particle->getLocation();
      m_skin->blit(display, l.x, l.y);
    }
  }

  virtual int getFps() { return 30; }
  virtual int getLifespan() { return 30; }

  virtual void particlesDone(ParticleEvent* event) 
  { 
    delete this;
  }


private:
  RotateSkinHandle m_skin;
};


class FireWorkBarrelTraits: public ParticleTraits, public ParticleListener
{
public:

  FireWorkBarrelTraits(int color)
  {
    char assetName[128];
    sprintf(assetName, "gfx_Block_%s_Firework", scolors[color].c_str());
    
    m_skin=theGame.am->getRotateSkin(assetName);

  }

  ~FireWorkBarrelTraits()
  {
  }
  virtual void init(Particle* particle);

  virtual void decay(Particle* particle);

  virtual void draw(Particle* particle, Display* display) 
  { 
    if (m_skin.isValid())
    {
      FPoint l = particle->getLocation();
      m_skin->blit(display, l.x, l.y);
    }
  }

  virtual int getFps(Particle* particle);
  virtual int getLifespan(Particle* particle);

  virtual void particlesDone(ParticleEvent* event) 
  { 
    delete this;
  }


private:
  RotateSkinHandle m_skin;
};


#endif
