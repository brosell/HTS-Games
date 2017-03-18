#include "CommandLineParser.h"
#include "Log.h"
#include <iostream>
using std::cerr;
using std::endl;

/*
[-|/]name=int
[-|/]name[+|-]
[-|/]name=string
*/

void CommandLineParser::parse(int argc, char** argv)
{
  char buf[256];
  std::map<string, int>::iterator inti;
  std::map<string, bool>::iterator booli;
  std::map<string, string>::iterator stringi;

  m_passedArgs.clear();

  if (argc < 2) return;

  for (int c=1; c<argc; c++)
  {
    char* arg = argv[c];

    if (strlen(argv[c]) == 2 && arg[0] == '-')
    {
      m_flagArgs[&arg[1]] = true;
      continue;
    }

    if (arg[0] == '-' || arg[0] == '/')
    {
      arg++;
    }

    // check for flag (no equals, and must have a plus or minus at the end

    if ( strchr(arg, '=') == 0 && 
          (isLastChar(arg, '+') || isLastChar(arg, '-')) )
    {
      // is flag like
      int flag = getLastChar(arg);
      arg[strlen(arg)-1] = '\0';
      m_flagArgs[arg] = (flag=='+'?true:false);
      m_passedArgs.insert(arg);
      sprintf(buf, "FLAG: %s = %s", arg, (char*)(m_flagArgs[arg]?"True":"False"));
      logError(buf, Inform);
    }
    else
    {
      if (strstr(arg, "=") == 0)
      {
        sprintf(buf, "NAME: %s", arg);
        logError(buf, Inform);
        m_names.push_back(arg);
        m_currentName = m_names.begin();
        continue;
      }
      StringTokenizer st(arg, "=");
      string sarg = st.nextToken();
      string val = (char*)(strstr(arg, "=")+1); //st.nextToken();

      m_passedArgs.insert(sarg);
      m_stringArgs[sarg] = val;
      sprintf(buf, "STR: %s = %s", sarg.c_str(), m_stringArgs[sarg].c_str());
      logError(buf, Inform);
    }
    
  }
}

int CommandLineParser::getLastChar(const char* str)
{
  return *((str+strlen(str)) - 1);
}

bool CommandLineParser::isLastChar(const char* str, int ch)
{
  char* loc=strchr(str, ch);
  return (loc == (str+strlen(str)) - 1);
}

string CommandLineParser::getNextName()
{
  if (m_names.size() == 0)
  {
    return "";
  }
  string ret = "";
  if (m_currentName != m_names.end())
  {
    ret = (*m_currentName);
    m_currentName++;
  }
  return ret;
}