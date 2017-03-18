#pragma warning (disable : 4503 4530 4786)
#include "FireworksDialog.h"

#include "Globals.h"

FireworksDialog::FireworksDialog(IniFile& ini, string name):
BusyDialog(ini, name),
m_co_barrelDropper(*this, FireworksDialog::co_barrelDropper, "Credits:BarrelDropper")
{
  m_explodeSound = Globals::am->getSoundEffect("snd_Fireworks_Explode");
  m_launchSound =  Globals::am->getSoundEffect("snd_Fireworks_Launch");
  m_traits[0] = new ExplodingBlockParticleTraits(0);
  m_traits[1] = new ExplodingBlockParticleTraits(1);
  m_traits[2] = new ExplodingBlockParticleTraits(2);

  m_fwTraits[0] = new FireWorkBarrelTraits(0);
  m_fwTraits[1] = new FireWorkBarrelTraits(1);
  m_fwTraits[2] = new FireWorkBarrelTraits(2);
}

FireworksDialog::~FireworksDialog()
{
  delete m_traits[0];
  delete m_traits[1];
  delete m_traits[2];

  delete m_fwTraits[0];
  delete m_fwTraits[1];
  delete m_fwTraits[2];
}

void FireworksDialog::specialPaint(Display* display)
{
  m_particleSystem.draw(display);
}

void FireworksDialog::co_barrelDropper()
{
  int thisColor = 0;
  //FireWorkBarrelTraits* fwbt = new FireWorkBarrelTraits(thisColor);
  ParticleSystemWaitable psw;

  if (m_launchSound.isValid())
  {
    m_launchSound->play();
  }
  
  m_particleSystem.fire(Point(320, 480), 1, m_fwTraits[thisColor], &psw);
  while (true)
  {
    Coroutine::waitFor(&psw);
    Point p = psw.finalLocations.front();
//    delete fwbt;
    
    m_particleSystem.fire(p, 20, m_traits[thisColor], 0);

    thisColor = rand()%3;
    
//    fwbt = new FireWorkBarrelTraits(thisColor);
    
    if (m_explodeSound.isValid())
    {
      m_explodeSound->play();
    }
    
    psw.reset();

    Coroutine::pause(250+(rand()%1000));

    if (m_launchSound.isValid())
    {
      m_launchSound->play();
    }

    m_particleSystem.fire(Point(320, 480), 1, m_fwTraits[thisColor], &psw);
  }
}

int FireworksDialog::doModal(Delegate* loop)
{
  m_co_barrelDropper.spawn();
  int ret = DialogBox::doModal(loop);
  m_co_barrelDropper.destroy();
  return ret;
}