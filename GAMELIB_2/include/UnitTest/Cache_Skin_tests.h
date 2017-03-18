#ifndef Cache_Skin_tests_h
#define Cache_Skin_tests_h

#include "Cache.h"
#include "SoundEffect.h"
#include "SharedSkin.h"
#include "TestSuite.h"
#include "FileManager.h"

#include "SkinLoader.h"

#include "BR_Game.h"


class Cache_Skin_tests: public hts::TestFixture
{
  IniFile m_ini;
  Cache<SharableSkin, SkinLoader> m_cache;
public:
  Cache_Skin_tests():
  m_ini("Assets.ini"),
  m_cache(1000)
  {
    m_ini.read();
    m_cache.setIni(m_ini);
  }

  START_TEST_MAP(Cache_Skin_tests)
    TEST_CASE(Test1);
    TEST_CASE(Test2);
  END_TEST_MAP


protected:
  void setUp()
  {
    BR_Game::initialize(640, 480, 32, SDL, 0);
  }
  void tearDown()
  {
    m_cache.reset();
    delete &theGame;
  }

  void Test1()
  {
    CacheId id = m_cache.add("skn_skin1");
    SharableSkin* ss = m_cache.get(id);
    CHECK(ss != 0);
  }

  void Test2()
  {
    CHECK(true);
  }
};

#endif