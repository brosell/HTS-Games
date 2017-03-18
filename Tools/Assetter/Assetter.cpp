// load asset file and move everything to the staging area.

#include "IniFile.h"
#include "CommandLineParser.h"
#include "StringTokenizer.h"

#include "FileUtils.h"
#include "Log.h"
#include "PakFile.h"

void usage();
void processAsset(string assetName, string fn);
void doit();
void addToPak(string fn);

bool testOnly = false;
bool wasError = false;
bool createPakFile = false;

string pakfilename = "";
string assetfilename = "";
string destination = "";

PakFile* pak = 0;

MaintLog* log = 0;

int _count = 0;

int main(int argc, char** argv)
{
  log = &(MaintLog::get("assetter.log"));

  log->setFilter(AllDebug);

  CommandLineParser clp;

  clp.setFlagDef("h", false);

  clp.parse(argc, argv);

  if (clp.getFlagArg("h"))
  {
    usage();
  }

  int req = 2;
  if (clp.getFlagArg("pak"))
  {
    req = 3;
    createPakFile = true;
  }

  if (clp.countNames() != req)
  {
    usage();
  }



  assetfilename = clp.getNextName();
  
  destination = clp.getNextName();
  
  if (createPakFile)
  {
    pakfilename = clp.getNextName();
    pak = new PakFile(pakfilename, false);
  }

  log->logError(Inform, "assetfilename : %s", assetfilename.c_str());
  log->logError(Inform, "destination   : %s", destination.c_str());
  log->logError(Inform, "testOnly      : %s", (testOnly?"True":"False"));

  doit();

  if (createPakFile)
  {
    pak->commit();  
  }
  
  if (!wasError)
  {
    log->logError(Inform, "%d file(s) successfully processed", _count);
    exit(0);
  }
  else
  {
    log->logError(Error, "%d file(s) processed - There were errors", _count);
    exit(-1);
  }
  return 0;
}
    
void usage()
{
  log->logError(Inform, "Assetter [-h+]                  (This Help)");
  log->logError(Inform, "Assetter [-test+] assetfilename (Verify files exist)");
  log->logError(Inform, "Assetter assetfilename destination  (Do it!)");
  log->logError(Inform, "Assetter -pak+ assetfilename pakfilename (create pak file!)");
  exit(1);
}

void doit()
{
  if (!fileExists(assetfilename))
  {
    log->logError(Error, "%s - file not found", assetfilename.c_str());
    exit (-1);
  }

  IniFile ini(assetfilename);
  ini.read();

  if (ini.size() == 0)
  {
    log->logError(Error, "%s contains no assets", assetfilename.c_str());
    exit(-1);
  }

  // makesure destination dir exists
  if (!testOnly && !makeDir(destination))
  {
    log->logError(Error, "Couldn't make destination directory (%s)", destination.c_str());
    log->logError(Error, "cya");
    exit (-1);
  }

  IniFile::iterator pair;
  for (pair = ini.begin(); pair!=ini.end(); pair++)
  {
    string assetName = pair->first;
    if (assetName == "Includes" || assetName == "None")
    {
      continue;
    }

    if (ini[assetName]["Type"] == "Skin" ||
      ini[assetName]["Type"] == "RotateSkin")
    {
      // we have to iterate over the frames
      int frameCount = ini.getInt(assetName, "Frames");
      if (frameCount == 0)
        frameCount = 1;
      
      char fn[255];
      for (int c=1; c<=frameCount; c++)
      {
        sprintf(fn, "Frame%02d", c);
        string frameFn = ini[assetName][fn];
        if (frameFn != "")
        {
          if (ini.getInt(assetName, "NoArchive") != 0 || createPakFile == false)
          {
            processAsset(assetName, frameFn);
          }
          else
          {
            addToPak(frameFn);
          }
        }
        else
        {
          // it's OK, blank frames are OK
        }
      }
      
    }
    else if (ini[assetName]["Type"] == "Text")
    {
      // just skip this one because text is stored in the assets.ini
    }
    else if(ini[assetName]["Type"] == "MouseCursor")
    {
      // skip this since there is no file (it uses a Skin)
    }
    else if(assetName == "RelevantFiles")
    {
      StringMap& fileMap = ini[assetName];
      StringMap::iterator pair;
      for(pair=fileMap.begin(); pair!=fileMap.end(); pair++)
      {
        if (ini.getInt(assetName, "NoArchive") != 0 || createPakFile == false)
        {
          processAsset(assetName, pair->first);
        }
        else
        {
          addToPak(pair->first);
        }
      }
    }
    else
    {
      if (ini.getInt(assetName, "NoArchive") != 0 || createPakFile == false)
      {
        processAsset(assetName, ini[assetName]["Filename"]);
      }
      else
      {
        addToPak(ini[assetName]["Filename"]);
      }
    }
  }
}

void addToPak(string fn)
{
  if (fn == "")
  {
    log->logError(Error, "Blank Filename!!");
    return;
  }
  if (pak->contains(fn))
  {
    return;
  }
  PakFileElement pfe(fn);
  log->logError(Inform, "to PakFile: %s", fn.c_str());

  (*pak)[fn] = pfe;
  _count++;
}

void processAsset(string assetName, string fn)
{
  if (fn == "")
  {
    log->logError(Error, "asset (%s) has no filename", assetName.c_str());
    wasError = true;
    return;
  }

  if (!fileExists(fn))
  {
    log->logError(Error, "asset (%s) file not found (%s)", assetName.c_str(), fn.c_str());
    wasError = true;
    return;
  }

  log->logError(Inform, "asset (%s) filename (%s) - seems to be valid", assetName.c_str(), fn.c_str());

  /*
  separate reletive dir from filename
  make sure destination+reletiveDir exist
  copy file
  */

  string filename = "";
  string relativeDir = "";
  CStdString destPath = "";
  CStdString destFolder = "";

  StringTokenizer st(fn.c_str(), "\\/");
  while (st.countTokens() > 1)
  {
    relativeDir += st.nextToken();
    relativeDir += "\\";
  }

  filename = st.nextToken();

  destPath.Format("%s\\%s%s", destination.c_str(), relativeDir.c_str(), filename.c_str());
  destFolder.Format("%s\\%s", destination.c_str(), relativeDir.c_str());

  log->logError(Inform, "%s -> %s", fn.c_str(), destPath.c_str());
  
  if (!testOnly)
  {
    if (!makeDir(destFolder))
    {
      log->logError(Error, "Couldn't make folder (%s)", destFolder.c_str());
      wasError = true;
    }
    else
    {
      if (0 == CopyFile(fn.c_str(), destPath.c_str(), false))
      {
        log->logError(Error, "CopyFile failed");
        wasError = true;
        LPVOID lpMsgBuf;
        if (!FormatMessage( 
          FORMAT_MESSAGE_ALLOCATE_BUFFER | 
          FORMAT_MESSAGE_FROM_SYSTEM | 
          FORMAT_MESSAGE_IGNORE_INSERTS,
          NULL,
          GetLastError(),
          MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
          (LPTSTR) &lpMsgBuf,
          0,
          NULL ))
        {
          // Handle the error.
          MessageBox(NULL, "ACK", "ACK", MB_OK);
          return;
        }
        
        // Process any inserts in lpMsgBuf.
        // ...
        
        // Display the string.
        MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
        
        // Free the buffer.
        LocalFree( lpMsgBuf );

      }
    }

  }
  _count++;
}

