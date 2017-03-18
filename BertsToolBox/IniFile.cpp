#pragma warning (disable : 4503 4786)
#include "IniFile.h"
#include "StringTokenizer.h"
#include <fstream>
#include "FileManager.h"
#include "StdString.h"

#include "Log.h"

/*
map<string, IniFile*> IniFile::s_map;

IniFile& IniFile::get(string filename)
{
  IniFile* ret = 0;
  map<string, IniFile*>::iterator pair = s_map.find(filename);
  if (pair == s_map.end())
  {
    ret = new IniFile(filename);
    s_map[filename] = ret;
  }
  else
  {
    ret = pair->second;
  }

  return *ret;
}
*/

IniFile::IniFile(string filename):
m_read(false)
{
  m_filenames.push_back(filename);
}

void IniFile::addIniFile(string filename)
{
  m_filenames.push_back(filename);
}


bool IniFile::read()
{
  list<string>::iterator i;
  for (i=m_filenames.begin(); i!= m_filenames.end(); i++)
  {
    read(*i);
  }
  m_read = true;
  return true;
}

bool IniFile::read(string filename)
{
  char* fileContents;
  int size = loadFileToMemory(filename, (void**)&fileContents);
  if (size <= 0)
  {
    return false;
  }

  string currentSection = "None";

  StringTokenizer st(fileContents, "\r\n");
  while (st.hasMoreTokens())
  {
    CStdString nl = st.nextToken();
    nl.Trim();
    if (nl == "")
    {
      continue;
    }
    if (nl.at(0) == '[')
    {
      StringTokenizer sectionTok(nl, "[]");
      currentSection = sectionTok.nextToken();
      continue;
    }

    if (nl.at(0) == ':' || nl.at(0) == '\'' || (nl.at(0) == '/' && nl.at(1) == '/'))
    {
      // this is a comment
      continue;
    }

    StringTokenizer keyValueTok(nl, "=");

    CStdString key = "";
    CStdString value = "";
    if (keyValueTok.countTokens())
    {
      key = keyValueTok.nextToken();
    }
    if (keyValueTok.countTokens())
    {
      value = keyValueTok.nextToken();
    }

    key.Trim();
    value.Trim();
    if (value == "<pre>")
    {
      value = "";
      CStdString v = "";
      while (st.hasMoreTokens())
      {
        v = st.nextToken();
        v.Trim();
        if (v == "</pre>")
        {
          break;
        }
        value += v;
        value+="\n";
      }
      value.Trim();
    }

    debug << "IniFile: " << currentSection << ": " << key << ": " << value << endl;
    
    m_map[currentSection][key] = value;

    if (currentSection == "Includes")
    {
      read(key);
    }
  }
  free(fileContents);
  return true;
}


bool IniFile::write(string filename)
{
  ofstream out(filename.c_str());
  lassert(out.is_open());

  if (!out.is_open())
  {
    return false;
  }

  iterator pair;
  StringMap::iterator p2;
  for (pair = m_map.begin(); pair!=m_map.end(); pair++)
  {
    string currentSection = pair->first;
    out << endl << "[" << currentSection << "]" << endl;
    for(p2 = pair->second.begin(); p2!=pair->second.end(); p2++)
    { 
      out << p2->first << " = " << p2->second << endl;
    }
  }
  return true;
}

      
