/* ****************************************************************************
 *
 *  InlineFileGen.cpp
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
 *  File Contents: Implementation of the InlineFileGen class.
 *  Please see InlineFileGen.h for documentation of this class.
 *
 * %version: 2.30 %
 * %date_modified: Thu Nov 16 20:04:13 2000 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "InlineFileGen.h"

namespace code_gen
{

using std::endl;

InlineFileGen::InlineFileGen(const DigestedCommands& commands)
							 throw(std::string)
	: 	CodeGenerator	(commands),
		mWriter			(commands.GetInlineFile(),
						 commands.GetWriteSentryMode())
{
}

InlineFileGen::~InlineFileGen()
{

}

std::ostream&
InlineFileGen::GetOstream()
{
	return mWriter.GetOstream();
}

void
InlineFileGen::GenCommentHeader() 	throw(std::string)
{
	std::ostringstream ostCustom;
	ostCustom <<
    " *" 																			   			<< endl <<
    " *  File Contents: Inline definitions for the " << mCommands.GetBaseFilename() << " component."	<< endl <<
    " *  Please see " << mCommands.GetHeaderFile() << " for full documentation of this class."	<< endl <<
    " *"																						<< endl;
	GenerateDefaultCommentHeader(mCommands.GetInlineFile(), ostCustom);
}

void
InlineFileGen::GenCodeBody(const std::string& strClassName) throw(std::string)
{
	if (mCommands.UseCheckValid())
	{
		GetOstream() <<
		"inline void" 													<< endl <<
    	strClassName << "::CheckValid() const"							<< endl <<
    	"{"															   	<< endl <<
    	"    // TODO: Fill in with class invariant assertions for "
					<< strClassName << "." 								<< endl <<
    	""																<< endl <<
    	"}"																<< endl;
	}

  if (mCommands.Singleton() && mCommands.IccFile())
  {
    GetOstream() <<
      strClassName << "* "<< strClassName << "::instance()" << endl <<
      "{" << endl <<
      "  if (s_instance.get() == 0){ " << endl <<
      "    std::auto_ptr<" << strClassName << "> temp(new " << strClassName << ");" << endl <<
      "    s_instance = temp;" << endl <<
      "  }" << endl <<
      "  return s_instance.get(); " << endl <<
      "}" << endl;
  }

}


} //end of code_gen namespace
