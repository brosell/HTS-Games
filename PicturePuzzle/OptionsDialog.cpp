#pragma warning (disable : 4786 4503 4530)
#include "OptionsDialog.h"

#include "SoundEffect.h"
#include "Convert.h"
#include "AssetManager.h"

#include "SDL_Mixer.h"

OptionsDialog::OptionsDialog(IniFile& ini, string name):
m_originalFXVolume(0),
m_originalMusicVolume(0),
IniBasedDialog(ini, name)
{
  m_iniFilename = ini[name]["OptionsFilename"];
  IniFile options(m_iniFilename);
  options.read();

  int fxv = options.getInt("Sound", "FXVolume");
  int mv = options.getInt("Sound", "MusicVolume");

  SoundEffect::setVolume("FX", fxv);
  //SoundEffect::setVolume("Music", mv);
  Mix_VolumeMusic(mv);

  m_originalFXVolume = SoundEffect::getVolume("FX");
  //m_originalMusicVolume = SoundEffect::getVolume("Music");
  m_originalMusicVolume = Mix_VolumeMusic(-1);

  m_fx = (HSlider*)getControlByName("hs_FXVolume");
  m_fx->setScrollPosition(fxv);
  m_fx->addAdjustmentListener(this);

  m_music = (HSlider*)getControlByName("hs_MusicVolume");
  m_music->setScrollPosition(mv);
  m_music->addAdjustmentListener(this);

  m_fs = (Button*)getControlByName("btn_Fullscreen");
  m_win = (Button*)getControlByName("btn_Windowed");
  
  setButtonHandler(120, this);
  setButtonHandler(121, this);
  setButtonHandler(122, this);
  setButtonHandler(123, this);
  setButtonHandler(124, this);
  setButtonHandler(125, this);

  setButton();
}

void OptionsDialog::setButton()
{
  if (theGame.screen->isWindowed())
  {
    m_fs->show();
    m_win->hide();
  }
  else
  {
    m_fs->hide();
    m_win->show();
  }
}
int OptionsDialog::doModal(Delegate* loop)
{
  m_originalFXVolume = SoundEffect::getVolume("FX");
  //m_originalMusicVolume = SoundEffect::getVolume("Music");
  m_originalMusicVolume = Mix_VolumeMusic(-1);
  m_fx->setScrollPosition(m_originalFXVolume);
  m_music->setScrollPosition(m_originalMusicVolume);

  m_originallyWindowed = theGame.screen->isWindowed();

  return IniBasedDialog::doModal(loop);
}


void OptionsDialog::onOK()
{
  IniFile options(m_iniFilename);
  options.read();
  options["Sound"]["FXVolume"] = toString(m_fx->getScrollPosition());
  options["Sound"]["MusicVolume"] = toString(m_music->getScrollPosition());
  options["Video"]["Fullscreen"] = toString(theGame.screen->isWindowed()?0:1);
  options.write();
  IniBasedDialog::onOK();
}

void OptionsDialog::paint(Display* display)
{

  IniBasedDialog::paint(display);
}

void OptionsDialog::onCancel()
{
  SoundEffect::setVolume("FX", m_originalFXVolume);
  //SoundEffect::setVolume("Music", m_originalMusicVolume);
  Mix_VolumeMusic(m_originalMusicVolume);
  if (m_originallyWindowed != theGame.screen->isWindowed())
  {
    theGame.setWindowed(m_originallyWindowed);
  }
  IniBasedDialog::onCancel();
}

void OptionsDialog::adjustmentValueChanged(AdjustmentEvent* event)
{
  if (event->thing == m_fx)
  {
    SoundEffect::setVolume("FX", m_fx->getScrollPosition());
//    theGame.am->getSoundEffect("snd_Bonus_Multi_1")->play();
  }
  else if (event->thing == m_music)
  {
    //SoundEffect::setVolume("Music", m_music->getScrollPosition());
    Mix_VolumeMusic(m_music->getScrollPosition());
  }
}

void OptionsDialog::actionPerformed(ActionEvent* event)
{
  switch (event->commandId)
  {
  case 120:
    m_music->tickDown();
    break;
  case 121:
    m_music->tickUp();
    break;
  case 122:
    m_fx->tickDown();
    break;
  case 123:
    m_fx->tickUp();
    break;
  case 124:
    theGame.setWindowed(false);
    setDirty(true);
    break;
  case 125:
    theGame.setWindowed(true);
    setDirty(true);
    break;
  default:
    IniBasedDialog::actionPerformed(event);
    break;
  }
  setButton();
}
