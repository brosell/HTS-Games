/* ****************************************************************************
 *
 *  CodeGenerator.cpp
 *  Created by John F. Hubbard, on Fri Aug 11 2000, 14:30:27 PST
 *
 *  Copyright (c) 2000, ATD Azad Technology Development Corporation
 *
 *            The Reliable Software Outsource Resource
 *        You hire us, we do it for you, and we do it right.
 *
 *                       www.azadtech.com
 *
 *  Permission is granted to use this code without restriction,
 *  as long as this copyright notice appears in all source files.
 *
 *  File Contents: Implementation of the CodeGenerator class, and also
 *  implementation of the Namespace class (a small helper class).
 *  Please see CodeGenerator.h for documentation of these classes.
 *
 * %version: 2.35b %
 * %date_modified: Fri Apr 20 11:05:02 2001 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <ctype.h>
#include <iostream>
#include <time.h>
#include "CodeGenerator.h"
#include "WriteSentry.h"

namespace code_gen
{
using std::endl;

CodeGenerator::CodeGenerator(const DigestedCommands& commands)
	:	mCommands			(commands)
{
}

CodeGenerator::~CodeGenerator()
{

}

void
CodeGenerator::GenerateDefaultCommentHeader(const std::string& strFileName,
											std::ostringstream& ostCustom)
{
	GetOstream() <<
    "/* ****************************************************************************"	<< endl <<
    " *"  																				<< endl <<
    " *  " << strFileName													 			<< endl <<
    " *  Created by " << mCommands.GetAuthor() << ", on " << DateStamp()				<< endl <<
    " *"	 																			<< endl <<
    " *  " << mCommands.GetCopyright() 													<< endl <<
    " *"	 																			<< endl;

	if(mCommands.OpenSourceNotice())
	{
		GetOstream() <<
    	" *  Permission is granted to use this code without restriction,"	 << endl <<
    	" *  as long as this copyright notice appears in all source files."  << endl <<
    	" *"  																 << endl;
	}

	GetOstream() << ostCustom.str();

	if(mCommands.ContinuusKeywords())
	{
		GetOstream() <<
		" *  %" "version: 1" " %"		  								<< endl <<
    	" *  %" "date_modified: " << DateStamp() << " %"	  			<< endl <<
    	" *  %" "created_by: " << mCommands.GetAuthor() << " %"		   	<< endl;

	}
	if(mCommands.CVS_Keywords())
	{
		GetOstream() <<
		" *  $" "Version: 1.0" " $"		  							<< endl <<
    	" *  $" "Date: " << DateStamp() << " $"	  					<< endl <<
    	" *  $" "Author: " << mCommands.GetAuthor() << " $"		   	<< endl;

	}
	if(mCommands.SccsKeywords())
	{
		GetOstream() <<
		" *  Version: %I" "%"  		   << endl <<
    	" *  Date modified: %G" "%"    << endl <<
    	" *"  						   << endl;
	}
	GetOstream() <<
    " *************************************************************************** */"	<< endl <<
    " "  																				<< endl;
}

void
CodeGenerator::GenerateDefaultPreface(const std::string& strFileName,
									 std::ostringstream& ostCustom)
{
	GetOstream() <<
	"#ifdef WIN32"					   						<< endl <<
	"#pragma warning (disable : 4786) // disable MSVC's useless template length warning"	<< endl <<
	"#endif // WIN32"					   					<< endl <<
	endl <<
    "#include <string>"						   				<< endl <<
    "#include <iostream>"					   				<< endl <<
	"#include \"" << mCommands.GetHeaderFile() << "\""		<< endl <<
	""														<< endl;

	GetOstream() << ostCustom.str() 						<< endl;
}

std::string
CodeGenerator::CreateUniqueName()
{
	return  std::string("ATC_")
		   + StringToUpper(mCommands.GetNamespace())
		   + std::string("_")
		   + StringToUpper(mCommands.GetBaseFilename())
		   + std::string("_H");
}

////////////////////////////////////////////////////////////////////////////////
// Non-member helper functions

std::string
DateStamp()
{
	using namespace std;
	char szBuf[100];
	time_t now = time(0);
 	strftime(szBuf, sizeof(szBuf), "%a %b %d %Y, %X %Z", localtime(&now));
	return szBuf;
}

std::string
StringToUpper(const std::string& strInput)
{
	using namespace std;
	char ch;
	string strOutput = strInput;

	for(string::iterator it = strOutput.begin();
		it != strOutput.end();
		++it)
	{
		ch = toupper(*it);
		strOutput.replace(it, it + 1, &ch, 1);
	}
	return strOutput;
}
} //end of code_gen namespace
