#ifndef CommandLineParser_h
#define CommandLineParser_h

#include "StringTokenizer.h"
#include <string>
#include <map>
#include <list>
#include <set>
using namespace std;

class CommandLineParser
{
public:
  typedef list<string>::iterator name_iterator;
  void parse(int argc, char** argv);

 /** return true if arg was really passed */
  bool isSet(string argname) 
  { 
    std::set<string>::iterator i;
    return  m_passedArgs.find(argname) != m_passedArgs.end(); 
  }
  
  void setFlagDef(string argname, bool defval) { m_flagArgs[argname] = defval; }
  void setStringDef(string argname, string defval) { m_stringArgs[argname] = defval; }

  int getIntArg(string argname) { return atoi(m_stringArgs[argname].c_str()); }
  float getFloatArg(string argname) { return atof(m_stringArgs[argname].c_str()); }
  bool getFlagArg(string argname) { return m_flagArgs[argname]; }
  string getStringArg(string argname) { return m_stringArgs[argname]; }

  string getNextName();

  int countNames() { return m_names.size(); }

  size_t size_name() { return m_names.size(); }
  name_iterator begin_name() { return m_names.begin(); }
  name_iterator end_name() { return m_names.end(); }

protected:
  int getLastChar(const char* str);
  bool isLastChar(const char* str, int ch);

private:
  set<string> m_passedArgs;
  map<string, bool> m_flagArgs;
  map<string, string> m_stringArgs;
  list<string> m_names;
  list<string>::iterator m_currentName;
};


#endif