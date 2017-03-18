#pragma warning (disable : 4503 4530 4786)
#include "CreditsDialog.h"
#include "ParticleTraits.h"
#include "Globals.h"

CreditsDialog::CreditsDialog(IniFile& ini, string name):
BusyDialog(ini, name),
m_co_barrelDropper(*this, CreditsDialog::co_barrelDropper, "Credits:BarrelDropper")
{
  m_explodeSound = Globals::assetManager->getSoundEffect("snd_Blocks_Disappearing");
}

CreditsDialog::~CreditsDialog()
{
}

void CreditsDialog::specialPaint(Display* display)
{
  m_particleSystem.draw(display);
}

void CreditsDialog::co_barrelDropper()
{
  /*
    launch firework
    while (true)
      wait until particle done
      blow up barrel
      launch firework
    end while
    */
  
  
  int thisColor = 0;
  FireWorkBarrelTraits* fwbt = new FireWorkBarrelTraits(thisColor);
  ParticleSystemWaitable psw;
  m_particleSystem.fire(Point(320, 480), 1, fwbt, &psw);
  while (true)
  {
    Coroutine::waitFor(&psw);
    Point p = psw.finalLocations.front();
    delete fwbt;
    
    ExplodingBlockParticleTraits* ebt= new ExplodingBlockParticleTraits(thisColor);
    

    // blow em up
    m_particleSystem.fire(p, 6, ebt, ebt);

    // new one
    thisColor = rand()%3;
    
    fwbt = new FireWorkBarrelTraits(thisColor);
    m_explodeSound->play();
    psw.reset();
    m_particleSystem.fire(Point(320, 480), 1, fwbt, &psw);
  }
}

int CreditsDialog::doModal(Delegate* loop)
{
  m_co_barrelDropper.spawn();
  int ret = DialogBox::doModal(loop);
  m_co_barrelDropper.destroy();
  return ret;
}