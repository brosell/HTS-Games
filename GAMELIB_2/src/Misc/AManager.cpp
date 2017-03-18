//#pragma warning (disable : 4786)
//#include "AManager.h"
//
//#include "FileManager.h"
//
//#include <string>
//using std::string;
//
//auto_ptr<AManager> AManager::s_instance;
//
//AManager::AManager()
//{
//  m_ini = new IniFile("Assets.ini");
//  m_ini->read();
//
//  init();
//}
//
//AManager::~AManager()
//{
//
//}
//
//void AManager::init()
//{
//  // read the ini file and get file sizes
//  IniFile::iterator pair;
//  for (pair = m_ini->begin(); pair!=m_ini->end(); pair++)
//  {
//    if (pair->first == "Includes")
//    {
//      continue;
//    }
//    string type = (*m_ini)[pair->first]["Type"];
//    if (type == "Relevant")
//    {
//      continue;
//    }
//
//    Asset_2* asset = new Asset_2;
//    asset->asset = 0;
//    asset->type = typeFromString(type);
//    asset->size = 0;
//    asset->used = false;
//    asset->name = pair->first;
//
//    m_assets[asset->name] = asset;
//
//  }
//}
//
//HAsset AManager::getHandle(std::string name)
//{
//  NameMap::iterator pair;
//  pair = m_assets.find(name);
//  if (pair == m_assets.end())
//  {
//    return 0;
//  }
//
//  Asset_2* asset = pair->second;
//  return static_cast<HAsset>(asset);
//}
//
//void AManager::load(HAsset handle)
//{
//  switch(handle->type)
//  {
//  case SOUND_EFFECT:
//    instance()->loadSoundEffect(handle);
//    break;
//  case SKIN:
//    instance()->loadSkin(handle);
//    break;
//  case ROTATESKIN:
//    instance()->loadRotateSkin(handle);
//    break;
//  case FONT:
//    instance()->loadFont(handle);
//    break;
//  case TEXTURE:
//    instance()->loadTexture(handle);
//    break;
//  case MOUSE:
//    instance()->loadMouseCursor(handle);
//    break;
//  default:
//    error << "AManager unknown asset type " << handle->type << endl;
//    break;
//  }
//}
//
//
//void AManager::loadSoundEffect(HAsset handle)
//{
//  string fn = (*m_ini)[handle->name]["Filename"];
//  string group = (*m_ini)[handle->name]["Group"];
//  if (fm_fileExists(fn))
//  {
//    SoundEffect* se = new SoundEffect(group, fn);
//    handle->asset = se;
//    handle->size = fm_fileSize(fn);
//    
//    makeRoomAndAdd(handle);
//  }
//  else
//  {
//    AM_fileNotFound(handle, fn);
//  }
//}
//
//void AManager::loadSkin(HAsset handle)
//{
//
//}
//
//void AManager::loadRotateSkin(HAsset handle)
//{
//
//}
//
//void AManager::loadFont(HAsset handle)
//{
//
//}
//
//void AManager::loadMouseCursor(HAsset handle)
//{
//
//}
//
//void AManager::loadTexture(HAsset handle)
//{
//
//}
//
//void AManager::makeRoomAndAdd(HAsset handle)
//{
//  m_alloced[handle->type]+=handle->size;
//  m_fifos[handle->type].push_back(handle);
//  
//  // have to do limits here
//  size_t limit = m_limits[handle->type];
//  if (limit > 0)
//  {
//    while (m_alloced[handle->type] > limit)
//    {
//      HAsset front = m_fifos[handle->type].front();
//      if (front == handle)
//      {
//        // this one os top and still the limit is used?
//        // must be a big 'un
//        break; // out of while
//      }
//      // release front of list (if not us)
//      m_fifos[handle->type].pop_front();
//      freeAsset(front);
//      m_alloced[handle->type]-=front->size;
//    }
//  }
//}
//
//void AManager::freeAsset(HAsset handle)
//{
////  switch(handle->type)
////  {
////  case SOUND_EFFECT:
////
////    delete (static_cast<SoundEffect*>(handle->asset));
////    handle->asset = 0;
////    break;
////  case SKIN:
////    delete (static_cast<SharedSkin*>(handle->asset));
////    handle->asset = 0;
////    break;
////  case ROTATESKIN:
////    delete (static_cast<SharedRotateSkin*>(handle->asset));
////    handle->asset = 0;
////    break;
////  case FONT:
////    delete (static_cast<Font*>(handle->asset));
////    handle->asset = 0;
////    break;
////  case TEXTURE:
////    Display::getInstance()->release((HTexture)handle->asset);
////    handle->asset = 0;
////    break;
////  case MOUSE:
////    delete (static_cast<MouseCursor*>(handle->asset));
////    handle->asset = 0;
////    break;
////  default:
////    error << "AManager unknown asset type " << handle->type << endl;
////    break;
////  }
//}