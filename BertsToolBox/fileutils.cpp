/*

$Log: fileutils.cpp,v $
Revision 1.2  2004-01-17 09:25:01-05  hey_now
<>

Revision 1.1  2003-10-05 10:32:27-04  hey_now
<>

Revision 1.0  2003-09-27 14:45:54-04  hey_now
Initial revision

Revision 1.2  2003-09-09 23:11:25-04  hey_now
<>

Revision 1.1  2003-09-08 11:26:43-04  hey_now
<>

Revision 1.0  2003-01-23 21:22:59-05  hey_now
Initial revision

   
      Rev 1.6   31 May 2000 14:06:44   BRosell
   added createTextFile()
   
      Rev 1.5   05 May 2000 14:49:56   BRosell
   continued development
   
      Rev 1.4   10 Apr 2000 09:50:10   BRosell
   fixes
   
      Rev 1.3   27 Mar 2000 08:44:22   BRosell
   Added dirExists() and makeDir()
   
      Rev 1.2   04 Feb 2000 14:28:22   BRosell
   Changed malloc to new and free to delete
   
      Rev 1.1   Nov 17 1999 14:36:54   BRosell
   removed redundant code from fileExclusiveOpen and fileExclusiveClose

*/


#include <windows.h>
#include <stdio.h>
#include <iostream>

// for exclusive file access routines
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>
#include <direct.h>
#include <fstream>
#include <errno.h>

#include <vector>
#include "stdstring.h"
#include "stringtokenizer.h"

#include "fileutils.h"

using namespace std;

struct OPENFILE
{
	FILE* fh;
	int handle;
	char* filename;
};

struct LOCKEDFILE
{
	int handle;
	char* filename;
};


vector<OPENFILE*> vecOpenFiles;
vector<LOCKEDFILE*> vecLockedFiles;
int nextFileHandle=0;


int fileExclusiveLock(char* filename, BOOL report)
{
	int ret = -1;
	float tries=0;
	char sema[MAX_PATH];
   
	LOCKEDFILE* pLockedFile;
	int handle=nextFileHandle++;	

	strcpy(sema, filename);
	strcat(sema, ".$$$");
			
	while (ret == -1)
	{
		ret = _open(sema, _O_CREAT | _O_EXCL, _S_IWRITE); // success if file doesn't exist
		tries++;
		if (tries>100)
			return -1;

		Sleep(30);

		if ( (tries/25) == floor(tries/25) )
			if (report)
				cout << " Waiting on reportfile..." << endl;
	}

	_close(ret); // create and run...	
	
	//pLockedFile=(LOCKEDFILE*)malloc(sizeof(LOCKEDFILE));
	pLockedFile=new LOCKEDFILE();
	pLockedFile->handle=handle;
	//pLockedFile->filename=(char*)malloc(strlen(filename)+1);
	pLockedFile->filename=new char[strlen(filename)+1];
	strcpy(pLockedFile->filename, filename);
	vecLockedFiles.push_back(pLockedFile);

	return handle;
}

void fileExclusiveUnlock(int handle)
{
	char sema[MAX_PATH];

	vector<LOCKEDFILE*>::iterator i;

	for(i=vecLockedFiles.begin(); i!=vecLockedFiles.end(); i++)
	{
		if (handle == (*i)->handle)
		{
			strcpy(sema, (*i)->filename);
			strcat(sema, ".$$$");
			DeleteFile(sema);
			//free( *i );
			delete [] (*i)->filename;
			delete (*i);

			vecLockedFiles.erase(i);
			return;
		}
	}
}

FILE* fileExclusiveOpen(char* filename, char* mode, BOOL report)
{
	int ret = -1;
   
	OPENFILE* pOpenFile;
	FILE* lOut;
	
	ret=fileExclusiveLock(filename, report);
	if (ret==-1)
		return NULL;

			
	lOut = fopen(filename, mode);

	if (lOut!=NULL)
	{
		//pOpenFile=(OPENFILE*)malloc(sizeof(OPENFILE));
		pOpenFile=new OPENFILE();
		pOpenFile->handle=ret;
		pOpenFile->fh=lOut;
		//pOpenFile->filename=(char*)malloc(strlen(filename)+1);
		pOpenFile->filename=new char[strlen(filename)+1];
		strcpy(pOpenFile->filename, filename);
		vecOpenFiles.push_back(pOpenFile);
	}
	else
	{
		fileExclusiveUnlock(ret);
	}

	return lOut;
}


void fileExclusiveClose(FILE* file)
{
	vector<OPENFILE*>::iterator i;

	for(i=vecOpenFiles.begin(); i!=vecOpenFiles.end(); i++)
	{
		if (file == (*i)->fh)
		{
			fclose(file);
			fileExclusiveUnlock( (*i)->handle );
			//free( *i );
			delete [] (*i)->filename;
			delete (*i);
			vecOpenFiles.erase(i);
			return;
		}
	}
}


bool makeDirs(const char* dir);

bool makeDir(CStdString dir)
{
	vector<CStdString> parts;
	vector<CStdString>::iterator i;

	if (dirExists(dir) )
	{
		return true;
	}

	StringTokenizer st(dir, "\\/");
	while (st.hasMoreTokens())
	{
		parts.push_back(st.nextToken() );
	}
	
	bool direxists=false;
	int numParts=0;
	CStdString d="";
	
	int size=parts.size();
	
	for (numParts=size; numParts > 0 && !direxists; numParts--)
	{
		d="";
		i=parts.begin();
		for (int x=0; x<numParts; x++, i++)
		{
			d+=(*i);
			d+="\\";
		}
		direxists=dirExists(d);
	}
	char cwd[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, cwd);
		

	bool r;

	if (!direxists)
	{
		r=makeDirs(dir);
	}
	else
	{
		SetCurrentDirectory(d);
		d=".\\";
		while (i!=parts.end())
		{
			d+=(*i);
			d+="\\";
			i++;
		}
		r=makeDirs(d);
	}
	SetCurrentDirectory(cwd);
	return r;
	
	
}

bool dirExists(CStdString d)
{
	bool direxists=false;
	DWORD atr=GetFileAttributes(d);
	if (atr!=0xFFFFFFFF)
	{
		if (atr & FILE_ATTRIBUTE_DIRECTORY)
		{
			direxists=true;
		}
	}
	return direxists;
}

bool fileExists(CStdString d)
{
	DWORD atr=GetFileAttributes(d);
	return  (atr!=0xFFFFFFFF);
}


bool makeDirs(const char* dir)
{
	
	char path[MAX_PATH]="";
	char tok[64];
	int ret=0;
	StringTokenizer st(dir, "\\/");
	while (st.hasMoreTokens() )
	{
		strcat(path, "/");
		strcat(path, st.nextToken());
		ret=_mkdir(&path[1]);
	}
	//strcpy(dir, path);
	if (ret== -1 && errno==EEXIST)
		ret=0;
	
	return (!ret);

}

void makeTextFile(const char* filename, const char* contents, const char* delims /* ="\r\n \t\v" */)
{
	StringTokenizer st(contents, delims);
	ofstream file(filename);

	while (st.hasMoreTokens())
	{
		file << st.nextToken().c_str() << endl;
	}
	file.close();

}

int fileSize(CStdString file)
{
  struct _stat buf;
  int result;

  result = _stat(file, &buf);

  if (result == 0)
  {
    return buf.st_size;
  }
  return -1;
}

string prettyName(string filepath)
{
  StringTokenizer path(filepath, "\\/");
  if (path.countTokens() == 0)
  {
    return "";
  }

  CStdString filename = "";
  while (path.hasMoreTokens())
  {
    filename = path.nextToken();
  }

  int extPos = filename.find_last_of('.');
  if (extPos < 0)
  {
    return filename;
  }

  return filename.substr(0, extPos);
}
