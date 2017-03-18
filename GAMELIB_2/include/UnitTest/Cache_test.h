#ifndef Cache_test_h
#define Cache_test_h

#include "Cache.h"
#include "SoundEffect.h"
#include "SharedSkin.h"
#include "TestSuite.h"
#include "FileManager.h"

#include "boost/format.hpp"

#include "SoundEffectLoader.h"


class CacheTester1: public hts::TestFixture
{
  START_TEST_MAP(CacheTester1)
    TEST_CASE(Empty);
    TEST_CASE(Cache1);
    TEST_CASE(Cache2);
    TEST_CASE(Cache3);
    TEST_CASE(Cache4);
  END_TEST_MAP

protected:
  void Empty()
  {
    IniFile ini("Assets.ini");
    ini.read();

    Cache<SoundEffect, SoundEffectLoader> cache(1);
    cache.setIni(ini);
    CHECK(cache.getAlloced() == 0);
  }

  void Cache1()
  {
    IniFile ini("Assets.ini");
    ini.read();

    Cache<SoundEffect, SoundEffectLoader> cache(1);
    cache.setIni(ini);
    CHECK(cache.getAlloced() == 0);

    CacheId id = cache.add("snd_sound");
    CHECK(cache.getAlloced() == 0);

    SoundEffect* snd = cache.get(id);
    CHECK(snd != 0);
    CHECK(cache.getAlloced() == fm_fileSize("wav.wav"));

  }

  void Cache2()
  {
    IniFile ini("Assets.ini");
    ini.read();

    Cache<SoundEffect, SoundEffectLoader> cache(1);
    cache.setIni(ini);
    CHECK(cache.getAlloced() == 0);

    CacheId id1 = cache.add("snd_sound");
    CacheId id2 = cache.add("snd_sound2");
    
    CHECK(cache.getAlloced() == 0);

    SoundEffect* snd = cache.get(id1);
    CHECK(snd != 0);
    CHECK(cache.getAlloced() == fm_fileSize("wav.wav"));

    SoundEffect* snd2 = cache.get(id2);
    CHECK(snd != snd2);
    CHECK(snd2 != 0);
    CHECK(cache.getAlloced() == fm_fileSize("wav2.wav"));
  }

  void Cache3()
  {
    IniFile ini("Assets.ini");
    ini.read();

    Cache<SoundEffect, SoundEffectLoader> cache(1);
    cache.setIni(ini);

    CHECK(cache.getAlloced() == 0);

    CacheId id1 = cache.add("snd_sound");
    CacheId id2 = cache.add("snd_sound2");
    
    CHECK(cache.getAlloced() == 0);

    SoundEffect* snd = cache.get(id1);
    CHECK(snd != 0);
    CHECK(cache.getAlloced() == fm_fileSize("wav.wav"));

    SoundEffect* snd2 = cache.get(id1);
    CHECK(snd == snd2);
    CHECK(snd2 != 0);
    CHECK(cache.getAlloced() == fm_fileSize("wav.wav"));

    snd2 = cache.get(id2);
    CHECK(snd != snd2);
    CHECK(snd2 != 0);
    CHECK(cache.getAlloced() == fm_fileSize("wav2.wav"));
  }

  void Cache4()
  {
    IniFile ini("Assets.ini");
    ini.read();

    Cache<SoundEffect, SoundEffectLoader> cache(1000);
    cache.setIni(ini);

    CHECK(cache.getAlloced() == 0);

    CacheId id1 = cache.add("snd_sound");
    CacheId id2 = cache.add("snd_sound2");
    
    CHECK(cache.getAlloced() == 0);

    SoundEffect* snd = cache.get(id1);
    CHECK(snd != 0);
    CHECK(cache.getAlloced() == fm_fileSize("wav.wav"));

    SoundEffect* snd2 = cache.get(id2);
    CHECK(snd != snd2);
    CHECK(snd2 != 0);
    CHECK(cache.getAlloced() == fm_fileSize("wav2.wav") + fm_fileSize("wav.wav"));
  }

};



#endif