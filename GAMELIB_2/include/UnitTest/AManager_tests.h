//#ifndef AManager_tests_h
//#define AManager_tests_h
//
//#include "TestSuite.h"
//#include "AManager.h"
//#include "FileManager.h"
//
//#include "SoundMixer.h"
//
//class AManager_tests: public hts::TestFixture
//{
//  START_TEST_MAP(AManager_tests)
//    TEST_CASE(Empty);
//    TEST_CASE(UseSound);
//    TEST_CASE(Limit);
//  END_TEST_MAP
//
//protected:
//  void Empty()
//  {
//    CHECK(AManager::getAlloced(SOUND_EFFECT) == 0);
//  }
//
//  void UseSound()
//  {
//    SDL_Init(SDL_INIT_AUDIO);
//    SoundMixer::initialize(22050, AUDIO_S16, 2, 2048);
//    SoundEffectHandle snd = AManager::getSoundEffect("snd_sound");
//    snd->play();
//    CHECK(AManager::getAlloced(SOUND_EFFECT) == fm_fileSize("wav.wav"));
//  }
//
//  void Limit()
//  {
//    AManager::setLimit(SOUND_EFFECT, 1);
//    SoundEffectHandle snd = AManager::getSoundEffect("snd_sound");
//    snd->play();
//    CHECK(AManager::getAlloced(SOUND_EFFECT) == fm_fileSize("wav.wav"));
//    snd = AManager::getSoundEffect("snd_sound2");
//    snd->play();
//    CHECK(AManager::getAlloced(SOUND_EFFECT) == fm_fileSize("wav2.wav"));
//  }
//};
//
//
//#endif