#pragma warning (disable : 4530 4503 4786)
#include "FileManager.h"
#include "PakFile.h"
#include "FileUtils.h"
#include "Log.h"
#include "Utils.h"

#include <sys/types.h>
#include <sys/stat.h>

vector<SP_PakFile> FileManager::s_loadedPaks;
bool FileManager::s_inited = false;

void FileManager::init()
{
  s_inited = true;
  CStdString pakfilename;

  for (int x=9; x>0; x--)
  {
    pakfilename.Format("pak%d.package", x);
    addPakFile(pakfilename);
  }
}

void FileManager::addPakFile(string pakfilename)
{
  if (::fileExists(pakfilename))
  {
    SP_PakFile pak(new PakFile(pakfilename, true));
    inform << "Loaded: " << pakfilename << endl;
    s_loadedPaks.push_back(pak);
  }
}

bool FileManager::fileExists(string filename)
{
  if (!s_inited) init();

  if (::fileExists(filename))
  {
    return true;
  }

  vector<SP_PakFile>::iterator i;
  for (i=s_loadedPaks.begin(); i!=s_loadedPaks.end(); i++)
  //for (int x=9; x>0; x--)
  {
    SP_PakFile pak = (*i); //s_loadedPaks[x];
    if (pak)
    {
      if (pak->contains(filename))
      {
        return true;
      }
    }
  }
  return false;
}

size_t FileManager::fileSize(string filename)
{
  if (!s_inited) init();

  if (::fileExists(filename))
  {
    // on disk... use stat?
    struct _stat buf;
    int result = _stat(filename.c_str(), &buf);
    if (result == 0)
    {
      return buf.st_size;
    }
    return 0;
  }

  vector<SP_PakFile>::iterator i;
  for (i=s_loadedPaks.begin(); i!=s_loadedPaks.end(); i++)
  //for (int x=9; x>0; x--)
  {
    SP_PakFile pak = *i; //s_loadedPaks[x];
    if (pak)
    {
      if (pak->contains(filename))
      {
        return pak->getSize(filename);
      }
    }
  }
  return 0;
}

FILE* FileManager::FP(string filename)
{
  if (!s_inited) init();

  if (::fileExists(filename))
  {
    logError(Debug, "loading %s from disk", filename.c_str());
    FILE* fp = fopen(filename.c_str(), "rb");
    fseek(fp, 0, SEEK_SET);
    long h=ftell(fp);
    return fp; //loadFile(filename, pto);
  }
  
  vector<SP_PakFile>::iterator i;
  for (i=s_loadedPaks.begin(); i!=s_loadedPaks.end(); i++)
  {
    SP_PakFile pak = (*i); //s_loadedPaks[x];
    if (pak)
    {
      if (pak->contains(filename))
      {
        debug << "loading " << filename << " from " << pak->getPakName() << endl;
//        int size = (*pak)[filename].getSize();
//        *pto = malloc(size+1);
//        memset(*pto, 0, size+1);
//        pak->toMemory(filename, *pto);
//        return size;
        return pak->toFP(filename);
      }
    }
  }

  logError(Error, "%s - file not found", filename.c_str());
  return 0;

}
  
int FileManager::loadFileToMemory(string filename, void** pto)
{
  if (!s_inited) init();

  if (::fileExists(filename))
  {
    logError(Debug, "loading %s from disk", filename.c_str());
    return loadFile(filename, pto);
  }
  
  vector<SP_PakFile>::iterator i;
  for (i=s_loadedPaks.begin(); i!=s_loadedPaks.end(); i++)
  {
    SP_PakFile pak = (*i); //s_loadedPaks[x];
    if (pak)
    {
      if (pak->contains(filename))
      {
        debug << "loading " << filename << " from " << pak->getPakName() << endl;
        int size = (*pak)[filename].getSize();
        *pto = malloc(size+1);
        memset(*pto, 0, size+1);
        pak->toMemory(filename, *pto);
        return size;
      }
    }
  }

  logError(Error, "%s - file not found", filename.c_str());
  return 0;
}

int FileManager::loadFile(string filename, void** pto)
{
  if (!s_inited) init();

  FILE* in=fopen(filename.c_str(), "rb");
  if (!in)
  {
    return 0;
  }

 
  int size = fileSize(filename);

  *pto = malloc(size+1);
  memset(*pto, 0, size+1);

  char* start = (char*)*pto;
  char* to=(char*)*pto;

  int read = 0;
  while (to < start+size)
  {
    int leftToRead = size-read;
    int toRead = hts::min(1024, leftToRead);
    int justRead = fread(to, 1, toRead, in);
    if (justRead <= 0)
    {
      free(*pto);
      return 0;
    }
    to+=justRead;
    read+=justRead;
  }

  fclose(in);
  return size;
}