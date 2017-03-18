/* ****************************************************************************
 *
 *  ClassCreator.cpp
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
 *  File Contents: Implementation of the ClassCreator class.
 *  Please see ClassCreator.h for documentation of this class.
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
#include <list>
#include "HeaderFileGen.h"
#include "ImplFileGen.h"
#include "InlineFileGen.h"
#include "MakefileGen.h"
#include "UnitTestFileGen.h"
#include "ClassCreator.h"
#include "PackedString.h"

namespace code_gen
{
ClassCreator::ClassCreator(const DigestedCommands& commands)
	:	mCommands 		  (commands) // this is a reference assignment, not a copy operation.
{
}

ClassCreator::~ClassCreator()
{

}

#ifndef WIN32

void
ClassCreator::GenerateCode() const throw (std::string)
{
	GenerateFile<HeaderFileGen>();
	GenerateFile<ImplFileGen>();

	if (mCommands.IccFile())
	{	GenerateFile<InlineFileGen>();
	}
	if (mCommands.WillCreateMakefile())
	{	GenerateFile<MakefileGen>();
	}
	if (mCommands.WillCreateUnitTestFile())
	{	GenerateFile<UnitTestFileGen>();
	}
}

template<typename T>
void ClassCreator::GenerateFile() const
{
	using std::list;
	using std::string;

	T generator(mCommands);

	generator.GenCommentHeader();	// The comment header with author, description, etc.
	generator.GenPreface();			// #ifdef directives, for example.

	tools::PackedString objClassList (mCommands.GetClassList());
	for (std::list<std::string>::const_iterator it = objClassList.GetList().begin();
		 it != objClassList.GetList().end();
		 ++it)
	{
		generator.GenCodeBody(*it);	 // generate each class.
	}

	generator.GenEpilog();			// #endif, for example.
}
#else
	// Work around for yet another Microsoft compiler bug.
	// Microsoft bug report: Q240871: Explicitly Specified Template
	// Functions Not Overloaded Correctly
	// Reference: http://support.microsoft.com/support/kb/articles/Q240/8/71.ASP
	#include "ClassCreatorMSBugWorkAround.icc"
#endif // #ifndef WIN32

} //end of code_gen namespace
