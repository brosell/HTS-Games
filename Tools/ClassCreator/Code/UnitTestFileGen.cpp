/* ****************************************************************************
 *
 *  UnitTestFileGen.cpp
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
 *  File Contents: Implementation of the UnitTestFileGen class.
 *  Please see UnitTestFileGen.h for documentation of this class.
 *
 * %version: 2.31 %
 * %date_modified: Sat Nov 18 21:00:02 2000 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "UnitTestFileGen.h"

namespace code_gen
{

using std::endl;

UnitTestFileGen::UnitTestFileGen(const DigestedCommands& commands)
								 throw(std::string)
	: 	CodeGenerator	(commands),
		mWriter			(commands.GetUnitTestFile(),
		 				 commands.GetWriteSentryMode(),
						 commands.WillCreateUnitTestFile())
{
}

UnitTestFileGen::~UnitTestFileGen()
{

}

std::ostream&
UnitTestFileGen::GetOstream()
{
	return mWriter.GetOstream();
}

void
UnitTestFileGen::GenCommentHeader() 	throw(std::string)
{
	std::ostringstream ostCustom;
	ostCustom <<
    " *" 																		   				<< endl <<
    " *  File Contents: Unit test for the the " << mCommands.GetBaseFilename() << " component."		<< endl <<
    " *  Please see " << mCommands.GetHeaderFile() << " for full documentation of this class."	<< endl <<
    " *"																						<< endl;
	GenerateDefaultCommentHeader(mCommands.GetUnitTestFile(), ostCustom);
}

void
UnitTestFileGen::GenPreface() 			throw(std::string)
{
	std::ostringstream ostCustom;
	if(mCommands.GetProjectName() == "atc")
	{
		ostCustom <<
   		"#include \"tools/AtcTracer.h\""  << endl;
	}
	GenerateDefaultPreface(mCommands.GetUnitTestFile(), ostCustom);

	GetOstream() <<
	"int main(int argc, char* argv[])"									   	<< endl <<
    "{"																	   	<< endl;
}


void
UnitTestFileGen::GenCodeBody(const std::string& strClassName) throw(std::string)
{
	if(mCommands.UseNamespace())
	{
		GetOstream() <<
    	"    " << mCommands.GetNamespace() << "::";
	}
	GetOstream() <<
	strClassName << " obj" << strClassName << ";"	 		<< endl;

	if(mCommands.UseDumpDiagnostics())
	{
		GetOstream() <<
		"    obj" << strClassName << ".DumpDiagnostics();"		<< endl;
	}

	GetOstream() <<
    " "														<< endl;
}

void
UnitTestFileGen::GenEpilog() throw(std::string)
{
	GetOstream() <<
    "    return 0;"													<< endl <<
    "}"																<< endl;
}

} //end of code_gen namespace
