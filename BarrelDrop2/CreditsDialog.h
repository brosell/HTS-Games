#ifndef CreditsDialog_h
#define CreditsDialog_h

#include "BusyDialog.h"
#include "CoroutineDelegates.h"
#include "ParticleSystem.h"
#include "SoundEffect.h"

class CreditsDialog: public BusyDialog
{
public:
  CreditsDialog(IniFile& ini, string name);
  ~CreditsDialog();

  void specialPaint(Display* display);

  void co_barrelDropper();

  virtual int doModal(Delegate* loop = 0);

private:
  SpawnableCoroutineTypeDelegate<CreditsDialog> m_co_barrelDropper;
  ParticleSystem m_particleSystem;
  SoundEffect* m_explodeSound;
};

#endif