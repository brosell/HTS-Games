/*

$Log: fileutils.h,v $
Revision 1.1  2004-01-17 09:25:02-05  hey_now
<>

Revision 1.0  2003-09-27 14:45:55-04  hey_now
Initial revision

Revision 1.1  2003-09-08 11:26:43-04  hey_now
<>

Revision 1.0  2003-01-23 21:22:59-05  hey_now
Initial revision

 * 
 *    Rev 1.4   31 May 2000 14:08:14   BRosell
 * added createTextFile()
 * 
 *    Rev 1.3   10 Apr 2000 09:49:34   BRosell
 * fixes
 * 
 *    Rev 1.2   27 Mar 2000 08:44:40   BRosell
 * Added dirExists() and makeDir()
 * 
 *    Rev 1.1   Nov 17 1999 14:41:56   BRosell
 * code cleanup

*/

#ifndef _FILEUTILS_H_
#define _FILEUTILS_H_

#include <stdio.h>
#include <windows.h>
#include "StdString.h"

FILE* fileExclusiveOpen(char* filename, char* mode="a+", BOOL report=TRUE);
void fileExclusiveClose(FILE* file);
void fileExclusiveUnlock(int handle);
int fileExclusiveLock(char* filename, BOOL report=TRUE);

void makeTextFile(const char* filename, const char* contents, const char* delims="\r\n \t\v");


bool makeDir(CStdString dir);
bool dirExists(CStdString d);
bool fileExists(CStdString d);

int fileSize(CStdString file);

string prettyName(string filepath);

#endif