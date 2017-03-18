#ifndef IniFile_h
#define IniFile_h
#pragma warning (disable: 4786)

#include <map>
#include <iostream>
#include <list>
#include <string>

#include "nocase_compare.h"

using namespace std;

//typedef std::map<string, string> StringMap;


class StringMap
{
public:
  typedef map<string, string, hts::nocase_compare<string> > MAP_TYPE;
  typedef MAP_TYPE::iterator iterator;

  string& operator[](string s) { return m_map[s]; }
  iterator begin() { return m_map.begin(); }
  iterator end() { return m_map.end(); }
private:
  MAP_TYPE m_map;
};

typedef std::map<string, StringMap, hts::nocase_compare<string> > StringStringMap;


class IniFile
{
	StringStringMap m_map;
public:
  typedef StringStringMap::iterator iterator;

	StringMap& operator[](string s)
	{
		return m_map[s];
	}

  iterator begin() { return m_map.begin(); }
  iterator end() { return m_map.end(); }
	
//  static IniFile& get(string filename);
  IniFile(string filename);
  IniFile();
  ~IniFile() { }
  void addIniFile(string filename);

  bool read();
  bool readObsolite();
  bool write(string filename);
  bool write() { return write(m_filenames.front()); }

  int getInt(string section, string field)
  {
    return atoi( (*this)[section][field].c_str());
  }

  float getFloat(string section, string field)
  {
    return atof( (*this)[section][field].c_str());
  }

  bool hasSection(string section)
  {
    return (m_map.find(section)!=m_map.end());
  }

  int size() { return m_map.size(); }


  bool isRead() { return m_read; }

private:
  bool read(string filename);
  IniFile(const IniFile& other); // prevent copying
  
  list<string> m_filenames;

  bool m_dirty;
  bool m_read;
};

#endif