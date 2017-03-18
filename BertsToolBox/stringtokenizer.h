/*
 StringTokenizer.h - definition of StringTokenizer

---------------------------------------------------
		Revision History
---------------------------------------------------

$Log: stringtokenizer.h,v $
Revision 1.0  2003-09-27 14:46:00-04  hey_now
Initial revision

Revision 1.1  2003-09-09 23:11:26-04  hey_now
<>

Revision 1.0  2003-01-23 21:23:02-05  hey_now
Initial revision

 * 
 *    Rev 1.3   21 Mar 2000 15:41:50   BRosell
 * the great const
 * 
 *    Rev 1.2   06 Jul 1999 15:44:48   BRosell
 * logging added

*/

#ifndef STRINGTOKENIZER
#define STRINGTOKENIZER

//const char* CONSTDelims="\t \n\r";
#include <list>
#include "StdString.h"
using namespace std;

class StringTokenizer
{
public:
	StringTokenizer(CStdString str, CStdString delims="\t \n\r");
	~StringTokenizer();

	bool hasMoreTokens();
	int countTokens();
  CStdString nextToken();

private:
	int currentPosition;
	int maxPostition;

  list<CStdString> m_tokens;
};

#endif

char* trim(char* str);
