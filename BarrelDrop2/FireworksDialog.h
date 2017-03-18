#ifndef FireworksDialog_h
#define FireworksDialog_h

#include "BusyDialog.h"
#include "CoroutineDelegates.h"
#include "ParticleSystem.h"
#include "SoundEffect.h"
#include "ParticleTraits.h"

class FireworksDialog: public BusyDialog
{
public:
  FireworksDialog(IniFile& ini, string name);
  virtual ~FireworksDialog();

  virtual void specialPaint(Display* display);

  void co_barrelDropper();

  virtual int doModal(Delegate* loop = 0);
private:
  SpawnableCoroutineTypeDelegate<FireworksDialog> m_co_barrelDropper;
  ParticleSystem m_particleSystem;
  
  SoundEffectHandle m_explodeSound;
  SoundEffectHandle m_launchSound;

  ExplodingBlockParticleTraits* m_traits[3];

  FireWorkBarrelTraits* m_fwTraits[3];

};

#endif