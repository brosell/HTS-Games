#include "IniFile.h"
#include "CommandLineParser.h"
#include "Convert.h"
#include "FileUtils.h"

#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
  CommandLineParser clp;
  clp.parse(argc, argv);

  int major = 1;
  int minor = 0;
  int build = 0;

  if (clp.isSet("major"))
  {
    major = clp.getIntArg("major");
  }
  if (clp.isSet("minor"))
  {
    minor = clp.getIntArg("minor");
  }

  if (clp.countNames() == 0)
  {
    cerr << "No ini file specified." << endl;
    return -1;
  }

  string iniName = clp.getNextName();
  IniFile ini(iniName);

  if (fileExists(iniName))
  {
    ini.read();
    build = ini.getInt("Version", "Build");
  }

  
  build++;

  cerr << "Setting build number to (" << major << ":" << minor << ":" << build << ")" << endl;

  ini["Version"]["Major"] = toString(major);
  ini["Version"]["Minor"] = toString(minor);
  ini["Version"]["Build"] = toString(build);

  char buf[128], buf2[128];

  CStdString datetime;
  datetime.Format("%s %s", _strdate(buf), _strtime(buf2));
  ini["Version"]["Timestamp"] = datetime;

  ini.write();

  return 0;
}