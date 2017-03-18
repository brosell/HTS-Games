#include "BR_Game.h"
#include "CommandLineParser.h"
#include "Convert.h"

#include "GameDialog.h"
#include "Picture.h"

#include "PictureBrowser.h"
#include "MainMenuDlg.h"
#include "ChooseModeDlg.h"
#include "OptionsDialog.h"

#include "SplashScreen.h"

#include "Music.h"

#include "PieceBucket.h"

class GameListener: public KeyListener, public DrawListener
{
public:
#ifdef HTS_DEBUG
  virtual void keyPressed(KeyPressEvent* event)
  {
    switch(event->keySym)
    {
    case SDLK_f:
      {
        showDrawTime();
      }
      break;
    case SDLK_r:
      {
        sw_draw.reset();
      }
      break;
    case SDLK_a:
      {
        theGame.am->report(inform);
      }
      break;
    }
  }

  virtual void preDraw()
  {
    sw_draw.start();
  }
  virtual void postDraw()
  {
    sw_draw.stop();
  }

  void showDrawTime()
  {
    inform << "Draw time: " << sw_draw.getAverage() << endl;
    inform << "Last draw amount: " << UIThing::s_drawCount << endl;
  }

  StopWatch sw_draw;
#endif

} gameListener;

class PictureBrowserFactoryHelper: public IniDialogHelper
{
public:
  virtual UIThing* create(string type, StringMap& attributes)
  {
    if (type == "PictureBrowser")
    {
      return new PictureBrowser(attributes);
    }
    return 0;
  }
}pbHelper;

class OnDeckFactoryHelper: public IniDialogHelper
{
public:
  virtual UIThing* create(string type, StringMap& attributes)
  {
    if (type == "PieceBucket")
    {
      return new PieceBucket(attributes);
    }
    return 0;
  }
}odHelper;


void doArgs(CommandLineParser& clp, int c, char** v)
{
  clp.setStringDef("bpp", "0");
  
  clp.parse(c, v);
}

void initEngine(CommandLineParser& clp);
void gameLoop();
bool areYouSure();
void doRules(int mode);
void doUpSell();

IniBasedDialog* g_areYouSure = 0;
IniBasedDialog* g_rules = 0;

int main(int c, char** v)
{
  UIThing::s_ocheck = false;
#ifdef HTS_DEBUG
  MaintLog::get().setFilter(AllDebug);
#else
  MaintLog::get().setFilter(Inform);
#endif

  IniFile version("Version.ini");
  version.read();

  int major = version.getInt("Version", "Major");
  int minor = version.getInt("Version", "Minor");
  int build = version.getInt("Version", "Build");

  inform << "Puzzle Me This! version " << major
         << "." << minor << "." << build
#ifdef _DEMO
         << " DEMO"
#endif
  << endl;
  
  inform << "Built " << version["Version"]["Timestamp"] << endl;

  CommandLineParser clp;
  doArgs(clp, c, v);
  
  initEngine(clp);

#ifndef _DEMO
  IniFile assets("Assets_Full.ini");
#else
  IniFile assets("Assets_Demo.ini");
#endif
  assets.read();
  AM* am = new AM(assets);
  am->setFontLimit(1000);
  am->setSkinLimit(500);
  theGame.am = am;

  IniBasedDialog::setHelper("PictureBrowser", &pbHelper);
  IniBasedDialog::setHelper("PieceBucket", &odHelper);

  gameLoop();

  return 0;
}

Music* g_music = 0;

void startMusic()
{
  g_music = new Music("assets\\audio\\music\\MusicBakery19960617mag.ogg");
  if (g_music)
  {
    g_music->play(-1);
  }
}

void stopMusic()
{
  if (g_music)
  {
    // fade out music to finish 3 seconds from now
    Mix_FadeOutMusic(250);
  }

  if (g_music)
  {
    delete g_music;
    g_music = 0;
  }
}

SplashScreen* g_splash = 0;
time_t g_splashTime = 0;
void showSplash()
{
  g_splashTime = time(0);

  g_splash=new SplashScreen("Splash.jpg");
  g_splash->setPosition(Rect(0, 0, 630, 480));
  theGame.uiSystem.addUIThing(g_splash);
  theGame.draw();
}

void hideSplash()
{
  while (time(0) < g_splashTime+3) 
  { 
  }


  g_splash->hide();
  delete g_splash;
  g_splash = 0;
}


void gameLoop()
{
  showSplash();

  IniFile ini("UI\\Dialogs.ini");
  ini.read();


  IniBasedDialog done(ini, "dlg_Finished");
  Canvas* finishedPic = dynamic_cast<Canvas*>(done.getControlByName("cvs_Finished_Pic"));
  Label* finishedTime = dynamic_cast<Label*>(done.getControlByName("lbl_Finished_Time"));
  Label* finishedMoves = dynamic_cast<Label*>(done.getControlByName("lbl_Finished_Moves"));
  Label* finishedHints = dynamic_cast<Label*>(done.getControlByName("lbl_Finished_Hints"));
  
  theGame.uiSystem.setMouseCursor("mouse_Default");
  theGame.uiSystem.setFont(theGame.am->getFont("fnt_Expo"));
  
  MainMenuDlg mainMenu(ini, "dlg_MainMenu");
  PictureBrowser* browser=dynamic_cast<PictureBrowser*>(mainMenu.getControlByName("cus_MainMenu_Browser"));

  g_areYouSure = new IniBasedDialog(ini, "dlg_AreYouSure");
  g_rules = new IniBasedDialog(ini, "dlg_Rules");

  startMusic();

  hideSplash();

  int ret = 0;
  while (true)
  {
    ret = mainMenu.doModal();
    if (-1 == ret)
    {
      if (areYouSure())
      {
        break;
      }
      else
      {
        continue;
      }
    }


    if (ret == 10000)
    {
      IniBasedDialog cd(ini, "dlg_Credits");
      cd.doModal();
      continue;
    }
    if (ret == 10001)
    {
      OptionsDialog od(ini, "dlg_Options");
      od.doModal();
      continue;
    }

    string pic = mainMenu.getSelected();
    inform << "picture is: " << pic << endl;
    Picture picture(pic);

    ChooseModeDlg chooser(ini, "dlg_Preview", picture);
    int m = chooser.doModal();
    
    if (m>=0)
    {
      doRules(chooser.mode());
      GameDialog gd(ini, "dlg_PlayScreen", chooser);
      
      gd.setPicture(&picture);
//      gd.showPic(clp.getFlagArg("showpic"));
//      gd.showHint(clp.getFlagArg("showhint"));
      gd.show();
      
      while (!gd.isDone() && !gd.isQuit())
      {
        theGame.pump();
      }
      gd.hide();
      
      if (gd.isDone())
      {
        finishedPic->setImage(picture.getPicture());
        finishedTime->setText(gd.getTimeString());
        finishedMoves->setText(toString(gd.nMoves()));
        finishedHints->setText(toString(gd.nHints()));
        done.doModal();
      }
#ifdef _DEMO
      doUpSell();
#endif
    }
  }

  stopMusic();

  if (!theGame.isWindowed())
  {
    theGame.setWindowed(true);
  }

#ifdef _DEMO
  IniBasedDialog finally(ini, "dlg_Finally_Demo");
#else
  IniBasedDialog finally(ini, "dlg_Finally");
#endif
  finally.doModal();


}

void doUpSell()
{
  IniFile ini("UI\\dialogs.ini");
  ini.read();
  
  string str = "";
  
  switch(rand()%3)
  {
  case 0:
    str = "dlg_Upsell_Demo_1";
    break;
  case 1:
    str = "dlg_Upsell_Demo_2";
    break;
  case 2:
    str = "dlg_Upsell_Demo_3";
    break;
  }

  IniBasedDialog dlg(ini, str);
  dlg.doModal();
}


void doRules(int mode)
{
  IniFile options("Options.ini");
  options.read();

  bool show = true;
  string cat="";
  if (mode == 100)
  {
    g_rules->setBackground("skn_dlg_Rules_Place");
    cat="DontShowPlace";
  }
  else
  {
    g_rules->setBackground("skn_dlg_Rules_Swap");
    cat = "DontShowSwap";
  }

  if (options["ShowRules"][cat] != "1")
  {
    ToggleButton* dont=dynamic_cast<ToggleButton*>(g_rules->getControlByName("tgl_Rules_DontShow"));
    dont->setChecked(false);
    g_rules->doModal();
    if (dont->isChecked())
    {
      options["ShowRules"][cat]="1";
      options.write();
    }
  }
}

bool areYouSure()
{
  return (g_areYouSure->doModal() == 1);
}

void initEngine(CommandLineParser& clp)
{
  Uint32 flags = 0; //SDL_HWSURFACE | SDL_DOUBLEBUF;
  IniFile options("options.ini");
  options.read();
  if (options.getInt("Video", "Fullscreen") == 1)
  {
    flags |= SDL_FULLSCREEN;
  }

  BR_Game::initialize(640, 480, clp.getIntArg("bpp"), SDL, flags);

//  SDL_Surface* icon = loadSDLSurface("icon.jpg");
  theGame.setWindowInfo(0, "Puzzle Me This!");

  //SDL_Surface* icon=(SDL_Surface*)Display::getInstance()->acquire("icon.jpg");
  //theGame.setWindowInfo(icon, "Puzzle Me This!");

  SoundMixer::initialize(22050, AUDIO_S16, 2, 2048);

  int fxv = options.getInt("Sound", "FXVolume");
  int mv = options.getInt("Sound", "MusicVolume");

  SoundEffect::setVolume("FX", fxv);
  Mix_VolumeMusic(mv);


  theGame.setDrawListener(&gameListener);
  theGame.uiSystem.addKeyListener(&gameListener);
} 
