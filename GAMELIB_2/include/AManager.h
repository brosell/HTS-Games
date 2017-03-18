//#ifndef AManager_h
//#define AManager_h
//
//#include <string>
//#include <map>
//
//#include "Utils.h"
//#include "IniFile.h"
//
//#include "SoundEffect.h"
//#include "SharedSkin.h"
//#include "SharedRotateSkin.h"
//#include "Font.h"
//#include "Display.h"
//
//
//enum ASSET_TYPE_2
//{
//  UNDEF,
//  SOUND_EFFECT,
//  MUSIC,
//  SKIN,
//  ROTATESKIN,
//  FONT,
//  MOUSE,
//  TEXTURE,
//  RELEVANT,
//  TEXT
//};
//
//inline ASSET_TYPE_2 typeFromString(std::string s)
//{
//  static std::map<string, ASSET_TYPE_2> map;
//  if (map.empty())
//  {
//    map["SoundEffect"] = SOUND_EFFECT;
//    map["Music"] = MUSIC;
//    map["Skin"] = SKIN;
//    map["RotateSkin"] = ROTATESKIN;
//    map["Font"] = FONT;
//    map["Mouse"] = MOUSE;
//    map["Texture"] = TEXTURE;
//    map["Relevant"] = RELEVANT;
//    map["Text"] = TEXT;
//  }
//
//  std::map<string, ASSET_TYPE_2>::iterator pair;
//  pair = map.find(s);
//  if (pair != map.end())
//  {
//    return pair->second;
//  }
//  return UNDEF;
//}
//
//inline std::string stringFromType(ASSET_TYPE_2 type)
//{
//  static std::map<ASSET_TYPE_2, std::string> map;
//  if (map.empty())
//  {
//    map[SOUND_EFFECT] = "SoundEffect";
//    map[MUSIC] = "Music";
//    map[SKIN] = "Skin";
//    map[ROTATESKIN] = "RotateSkin";
//    map[FONT] = "Font";
//    map[MOUSE] = "Mouse";
//    map[TEXTURE] = "Texture";
//    map[RELEVANT] = "Relevant";
//    map[TEXT] = "Text";
//  }
//
//  std::map<ASSET_TYPE_2, string>::iterator pair;
//  pair = map.find(type);
//  if (pair != map.end())
//  {
//    return pair->second;
//  }
//  return "Undef";
//}
//
//  
//enum CacheLevel
//{
//  CL_UNDEF,
//  CL_FRAME,    // free if not used in a frame
//  CL_INSTRUCT, // don't free unless told to
//  CL_LIMIT     // free if limit reached and at end of list
//};
//
//class Asset_2
//{
//public:
//  Asset_2():used(false), asset(0) {}
//  /** the name from the ini file */
//  string name;
//  /** the type derived from the inifile */
//  ASSET_TYPE_2 type;
//  /** the asset */
//  void* asset;
//  bool used;
//  /** size in K of the asset (on disk at the moment) */
//  size_t size;
//
//  /** is this isn't used in a frame, release it. */
//  bool freeIfNotUsed;
//};
//
//typedef Asset_2* HAsset;
//
///////////////////////////////
//// HANDLES
////////////////////////////////
//
//class SoundEffectHandle
//{
//public:
//  SoundEffectHandle(HAsset handle): m_asset(handle) { }
//  SoundEffect* operator->();
//private:
//  HAsset m_asset;
//};
//
//class SkinHandle
//{
//public:
//  SkinHandle(HAsset handle): m_asset(handle) { }
//  Skin* operator->();
//private:
//  HAsset m_asset;
//};
//
//class RotateSkinHandle
//{
//public:
//  RotateSkinHandle(HAsset handle): m_asset(handle) { }
//  SharedRotateSkin* operator->();
//private:
//  HAsset m_asset;
//};
//
//class FontHandle
//{
//public:
//  FontHandle(HAsset handle): m_asset(handle) { }
//  Font* operator->();
//private:
//  HAsset m_asset;
//};
//
//class MouseHandle
//{
//public:
//  MouseHandle(HAsset handle): m_asset(handle) { }
//  MouseCursor* operator->();
//private:
//  HAsset m_asset;
//};
//
//class TextureHandle
//{
//public:
//  TextureHandle(HAsset handle): m_asset(handle) { }
//  HTexture operator->();
//private:
//  HAsset m_asset;
//};
///////////////////////
//// END HANDLES
////////////////////////
//
//class AManager: hts::Noncopyable
//{
//public:
//  ~AManager();
//
//  static SoundEffectHandle getSoundEffect(std::string name) { return SoundEffectHandle(instance()->getHandle(name)); }
//  static SkinHandle getSkin(std::string name) { return SkinHandle(instance()->getHandle(name)); }
//  static RotateSkinHandle getRotateSkin(std::string name) { return RotateSkinHandle(instance()->getHandle(name)); }
//  static FontHandle getFont(std::string name) { return FontHandle(instance()->getHandle(name)); }
//  static MouseHandle getMouseCursor(std::string name) { return MouseHandle(instance()->getHandle(name)); }
//  static TextureHandle getTexture(std::string name) { return TextureHandle(instance()->getHandle(name)); }
//
//  /**
//  @param limit the size in K
//  */
//  static void setLimit(ASSET_TYPE_2 type, size_t limit)
//  {
//    instance()->m_limits[type] = (limit * 1024);
//  }
//
//  static size_t getLimit(ASSET_TYPE_2 type)
//  {
//    return instance()->m_limits[type];
//  }
//
//  static size_t getAlloced(ASSET_TYPE_2 type)
//  {
//    return instance()->m_alloced[type];
//  }
//
//private:
//  AManager();
//  
//  static AManager* instance();
//  static auto_ptr<AManager> s_instance;
//
//  HAsset getHandle(std::string name);
//
//  /* I include the unused param of type T so we can avoid a MSVC compiler bug that 
//        explicit STATIC template instanciations don;t work. If we add a (T)0 to the 
//        fn call we get IMPLICIT instanciation and it works */
//  template <typename T>
//  static T getAsset(HAsset handle, T)
//  {
//    if (handle->asset == 0)
//    {
//      load(handle);   
//    }
//    return (T)(handle->asset);
//  }
//
//  static void load(HAsset handle);
//
//  void loadSoundEffect(HAsset handle);
//  void loadSkin(HAsset handle);
//  void loadRotateSkin(HAsset handle);
//  void loadFont(HAsset handle);
//  void loadMouseCursor(HAsset handle);
//  void loadTexture(HAsset handle);
//
//  void freeAsset(HAsset handle);
//
//  void makeRoomAndAdd(HAsset handle);
//
//
//  // reads Assets.ini and inits the data structures
//  void init();
//
//  typedef std::map<std::string, Asset_2*> NameMap;
//  typedef std::map<ASSET_TYPE_2, list<Asset_2*> > FifoMap;
//  typedef std::map<ASSET_TYPE_2, size_t> LimitMap;
//
//  NameMap m_assets;
//  FifoMap m_fifos;
//  LimitMap m_limits;
//  LimitMap m_alloced;
//
//  IniFile* m_ini;
//
//  friend class SoundEffectHandle;
//  friend class SkinHandle;
//  friend class RotateSkinHandle;
//  friend class FontHandle;
//  friend class TextureHandle;
//  friend class MouseHandle;
//};
//
///////////////////////////
//// NON MEMBERS
///////////////////////////
//inline void AM_fileNotFound(HAsset handle, std::string fn)
//{
//  error << "Asset (" << handle->name <<") file not found (" << fn << ")" << endl;
//}
//
//
//////////////////////////////
//// HANDLE INLINES
//////////////////////////////
//inline SoundEffect* SoundEffectHandle::operator->(){ return AManager::getAsset(m_asset, (SoundEffect*)0); }
//inline Skin*        SkinHandle::operator->() { return AManager::getAsset(m_asset, (SharedSkin*)0); }
//inline SharedRotateSkin* RotateSkinHandle::operator->() { return AManager::getAsset(m_asset, (SharedRotateSkin*)0); }
//inline Font*        FontHandle::operator->() { return AManager::getAsset(m_asset, (Font*)0); }
//inline MouseCursor* MouseHandle::operator->() { return AManager::getAsset(m_asset, (MouseCursor*)0); }
//inline HTexture     TextureHandle::operator->() { return AManager::getAsset(m_asset, (HTexture)0); }
//
/////////////////////////
//// AMANAGER inlines
/////////////////////////
//inline AManager* AManager::instance()
//{
//  if (s_instance.get() == 0)
//  {
//    auto_ptr<AManager> temp(new AManager);
//    s_instance = temp;
//  }
//  return s_instance.get();
//}
//
////inline SoundEffect* AManager::getSoundEffect(HAsset handle)
////{
////  if (handle->asset == 0)
////  {
////    instance()->loadSoundEffect(handle);
////  }
////  return static_cast<SoundEffect*>(handle->asset);
////}
//
//
//
//
//
//#endif
