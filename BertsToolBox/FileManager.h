#ifndef FileManager_h
#define FileManager_h

#include "Utils.h"
#include "PakFile.h"

#include <string>
#include <map>
#include <vector>
using namespace std;

#include "boost/shared_ptr.hpp"
typedef boost::shared_ptr<PakFile> SP_PakFile;


class FileManager: hts::Noncopyable
{
public:
  static void init();
  static bool fileExists(string filename);
  static int loadFileToMemory(string filename, void** pto);

  static FILE* FP(string filename);
  static size_t fileSize(string filename);

  static void addPakFile(string pakfilename);
private:
  FileManager();
  static int loadFile(string filename, void** pto);
  static vector<SP_PakFile> s_loadedPaks;
  static bool s_inited;
};

inline void fm_init()
{
  FileManager::init();
}

inline bool fm_fileExists(string filename)
{
  return FileManager::fileExists(filename);
}

inline size_t fm_fileSize(string filename)
{
  return FileManager::fileSize(filename);
}

inline int loadFileToMemory(string filename, void** pto)
{
  return FileManager::loadFileToMemory(filename, pto);
}



#endif