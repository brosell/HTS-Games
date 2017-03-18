#ifndef AM_tests_h
#define AM_tests_h

#include "AM.h"

class AM_tests1: public hts::TestFixture
{
  START_TEST_MAP(AM_tests1);
    TEST_CASE(Empty);
    TEST_CASE(UseSound);
    TEST_CASE(Limit);
    TEST_CASE(Skin1);
    TEST_CASE(RSkin1);
    TEST_CASE(Font1);
    TEST_CASE(Text);
//    BENCHMARK(RSkinTime1, 5);
//    BENCHMARK(RSkinTime2, 5);
  END_TEST_MAP

  AM* m_am;
  IniFile m_ini;

public:
  AM_tests1(): m_ini("Assets.ini") 
  {
    m_ini.read();
  }


  void setUp()
  {
    BR_Game::initialize(640, 480, 32, SDL, 0);    
    m_am = new AM(m_ini);
  }
  void tearDown()
  {
    delete m_am;
    m_am = 0;
    delete &theGame;
  }

protected:
  void Empty()
  {
    CHECK(m_am->getAlloced() == 0);
  }

  void UseSound()
  {
    SDL_Init(SDL_INIT_AUDIO);
    SoundMixer::initialize(22050, AUDIO_S16, 2, 2048);
    SoundEffectHandle snd = m_am->getSoundEffect("snd_sound");
    snd->play();
    CHECK(m_am->getAlloced() == fm_fileSize("wav.wav"));

    m_am->flushSoundEffects();
    CHECK(m_am->getAlloced() == 0);

  }

  void Limit()
  {
    m_am->setSoundEffectLimit(1);
    SoundEffectHandle snd = m_am->getSoundEffect("snd_sound");
    snd->play();
    CHECK(m_am->getAlloced() == fm_fileSize("wav.wav"));
    snd = m_am->getSoundEffect("snd_sound2");
    snd->play();
    CHECK(m_am->getAlloced() == fm_fileSize("wav2.wav"));

    m_am->setSoundEffectLimit(0);
    snd = m_am->getSoundEffect("snd_sound", true);

    size_t size = m_am->getAlloced();
    CHECK(m_am->getAlloced() == fm_fileSize("wav2.wav") + fm_fileSize("wav.wav"));
  }

  void Skin1()
  {
    SharedSkinHandle skn = m_am->getSkin("skn_skin1", true);
    CHECK(m_am->getAlloced() > 0);
    skn->blit(theGame.screen, 200, 200, true);
    theGame.screen->flip();
    Sleep(1000);
    m_am->flush();
    CHECK(m_am->getAlloced() == 0);
    skn->blit(theGame.screen, 300, 200, true);
    theGame.screen->flip();
    CHECK(m_am->getAlloced() > 0);
    Sleep(1000);
  }

  void RSkin1()
  {
    RotateSkinHandle skn = m_am->getRotateSkin("skn_skin1", true);
    CHECK(m_am->getAlloced() > 0);
    for (int r=0; r<30; r++)
    {
      theGame.screen->clear();
      skn->setRotation(r);
      skn->blit(theGame.screen, 200, 200, true);
      theGame.screen->flip();
      Sleep(100);
      m_am->flush();
    }
    CHECK(m_am->getAlloced() == 0);
  }

  void RSkinTime1()
  {
    RotateSkinHandle skn = m_am->getRotateSkin("skn_skin1", true);
    CHECK(m_am->getAlloced() > 0);
    for (int r=0; r<30; r++)
    {
      skn->setRotation(r);
      skn->blit(theGame.screen, 200, 200, true);
      theGame.screen->flip();
      m_am->flush();
    }
    CHECK(m_am->getAlloced() == 0);
  }
  
  void RSkinTime2()
  {
    RotateSkinHandle skn = m_am->getRotateSkin("skn_skin1", true);
    CHECK(m_am->getAlloced() > 0);
    for (int r=0; r<30; r++)
    {
      skn->setRotation(r);
      skn->blit(theGame.screen, 200, 200, true);
      theGame.screen->flip();
    }
  }

  void Font1()
  {
    FontHandle font = m_am->getFont("fnt_font1", true);
    CHECK(m_am->getAlloced() > 0);
    for (int x=0; x<400; x+=10)
    {
      font->drawLine(theGame.screen, "Hello World!", x, x);
      theGame.screen->flip();
      m_am->flush();
    }
  }

  void Text()
  {
    string t1 = m_am->getText("t1");
    CHECK(t1 == "Howdy Pard!");
    
    string t2 = m_am->getText("t2");
    CHECK(t2 == "A\nWhole\nLotta\nText");

    string t3 = m_am->getText("t3");
    CHECK(t3 == "Go Away!");
  }
};

#endif