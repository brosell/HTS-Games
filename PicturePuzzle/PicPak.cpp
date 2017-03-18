#pragma warning (disable : 4786)
#include "CommandLineParser.h"
#include "PakFile.h"
#include "IniFile.h"
#include "Log.h"
#include "FileManager.h"
#include "NDirIt.hpp"

#include "boost/Format.hpp"

void addToPak(PakFile* pak, string fn, string pfn)
{
  if (fn == "")
  {
    error << "Blank Filename!!" << endl;
    return;
  }
  if (pak->contains(fn))
  {
    error << "duplicate filename:" << fn << " (ignored)" << endl;
    return;
  }
  PakFileElement pfe(fn);
  pfe.setLocation(pfn);
  inform << "Added to PakFile: " << fn << endl;

  (*pak)[fn] = pfe;
}

void usage()
{
  inform << "PicPak [options] name dirToScan" << endl;
  inform << "options:" << endl;
  inform << " -ow[-|+] overwite existing pakfile is present (default no)" << endl;
}

int main(int c, char** v)
{
  MaintLog::get().setFilter(All);
  CommandLineParser clp;
  clp.setFlagDef("ow", false);

  clp.parse(c, v);

  if (clp.getFlagArg("h"))
  {
    usage();
    return -1;
  }

  if (clp.size_name() != 2)
  {
    usage();
    return -1;
  }

  //string manifestName = *(clp.begin_name());
  string picpakName = *(clp.begin_name());
  string dirToScan = *(++clp.begin_name());
  

  string pakName = (boost::format("%s.picpak") % picpakName).str();

  if (FileManager::fileExists(pakName) && !(clp.getFlagArg("ow")))
  {
    error << pakName << " already exists." << endl;
    error << "Use \"-ow+\" to overwrite" << endl;
    return -1;
  }

  CDirEnumeration files(dirToScan, "*.jpg");

  if (!files.hasMoreElements())
  {
    error << dirToScan << " has no jpgs." << endl;
    return -1;
  }

  unlink(pakName.c_str());
  PakFile pak(pakName, false);

  string manifestFiles = "<pre>\r\n";

  while(files.hasMoreElements())
  {
    string tname = files.nextElement();
    string fn=(boost::format("%s\\%s") % dirToScan % tname).str();
    string pfn=(boost::format("%s\\%s") % picpakName % tname).str();
    inform << "Adding: " << fn << " as " << pfn << endl;
    addToPak(&pak, fn, pfn);
    manifestFiles += (pfn + "\r\n");
  }
  manifestFiles += "</pre>\r\n";

  IniFile ini("__manifest.tmp");
  ini["Package"]["Name"] = picpakName;
  ini["Package"]["Files"] = manifestFiles;
  ini.write();

  addToPak(&pak, "__manifest.tmp", (picpakName+"\\manifest.ini"));

  pak.commit();
  unlink("__manifest.tmp");
  inform << "done." << endl;

  return 0;
}
