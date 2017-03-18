#ifndef _PakFile_h_
#define _PakFile_h_

#ifdef _WIN32
#include <winsock.h>
#else
#include <sys/types.h>
#include <netinet/in.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <map>
#include <vector>
#include <string>
using namespace std;

#include "nocase_compare.h"

class NBULong
{
public:
  static NBULong fromNetwork(unsigned long val)
  {
    NBULong l;
    l.setFromNetwork(val);
    return l;
  };
  static NBULong fromHost(unsigned long val)
  {
    NBULong l;
    l.setFromHost(val);
    return l;
  };

  unsigned long getNetworkVal()
  {
    return hostOrder;//htonl(hostOrder);
  }
  unsigned long getHostVal()
  {
    return hostOrder;
  }

  operator unsigned long () { return hostOrder; }
private:
  void setFromNetwork(unsigned long val)
  {
    hostOrder=val; //ntohl(val);
  }

  void setFromHost(unsigned long val)
  {
    hostOrder=val;
  }

  unsigned long hostOrder;
  
};


class PakFileElement
{
public:
  //PakFileElement(const char*dirEntry, unsigned long offset, unsigned long length, const char* location);
  PakFileElement(): location(""), dirEntryName("")
  {
  }

  PakFileElement(string fn): location(""), dirEntryName(fn)
  {
  }
  
  bool isOnDisk()
  {
    return (location.c_str()[0]!=0);
  }

  string getLocation()
  {
    return location;
  }

  void setLocation(string loc)
  {
    location = loc;
  }


  void setOffset(unsigned long off)
  {
    offset=NBULong::fromHost(off);
  }
  NBULong getOffset()
  {
    return offset;
  }
  
  void setSize(unsigned long s)
  {
    length=NBULong::fromHost(s);
  }
  NBULong getSize()
  {
    return length;
  }

  void setName(const char* name)
  {
    dirEntryName = name;
  }

  string getName()
  {
    return dirEntryName;
  }

private:
  string dirEntryName;
  NBULong offset;
  NBULong length;
  string location;
};


class PakFile: public map<string, PakFileElement, hts::nocase_path_compare<string> >
{
public:
  PakFile(string pn, bool l);
  ~PakFile()
  {
  }

  bool exists();

//  bool add(const char* filename, const char* dirName, bool replaceOk);
//  bool remove(const char* dirName);

  bool commit();

  bool extract(PakFileElement elem); //, const char* whereTo);
  bool extract(PakFileElement elem, const char* to); //, const char* whereTo);

  bool toMemory(string name, void* destination);

  FILE* toFP(string name);

  bool contains(string name);

  void dump();
  void extractAll();

  size_t getSize(string name);

  typedef vector<string>::iterator iterator_name;
  iterator_name begin_name() { return m_filenames.begin(); }
  iterator_name end_name() { return m_filenames.end(); }

  string getPakName() { return packName; }

  
private:
  void load();

  unsigned long copy(const char* filename, FILE* fd);

  vector<string> m_filenames;
  string packName;
  NBULong dirLoc;
  NBULong dirSize;
};

#endif
