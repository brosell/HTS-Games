/* ****************************************************************************
 *
 *  ImplFileGen.cpp
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
 *  File Contents: Implementation of the ImplFileGen class.
 *  Please see ImplFileGen.h for documentation of this class.
 *
 * %version: 2.30 %
 * %date_modified: Thu Nov 16 20:04:15 2000 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "ImplFileGen.h"

namespace code_gen
{

using std::endl;

ImplFileGen::ImplFileGen(const DigestedCommands& commands)
						 throw(std::string)
	: 	CodeGenerator	(commands),
		mWriter			(commands.GetImplFile(),
						 commands.GetWriteSentryMode())
{
}

ImplFileGen::~ImplFileGen()
{

}

std::ostream&
ImplFileGen::GetOstream()
{
	return mWriter.GetOstream();
}

void
ImplFileGen::GenCommentHeader() 	throw(std::string)
{
	std::ostringstream ostCustom;
	ostCustom <<
    " *" 																		   					<< endl <<
    " *  File Contents: Implementation of the " << mCommands.GetBaseFilename() << " component."		<< endl <<
    " *  Please see " << mCommands.GetHeaderFile() << " for full documentation of this system."		<< endl <<
    " *"																							<< endl;
	GenerateDefaultCommentHeader(mCommands.GetImplFile(), ostCustom);
}

void
ImplFileGen::GenPreface() 			throw(std::string)
{
	std::ostringstream ostCustom;
	if(mCommands.GetProjectName() == "atc")
	{
		ostCustom <<
   		"#include \"tools/AtcTracer.h\""   		<< endl;
	}
	GenerateDefaultPreface(mCommands.GetImplFile(), ostCustom);

	if (mCommands.UseNamespace())
	{
		GetOstream() <<
		"namespace " << mCommands.GetNamespace() << "" 	  		<< endl <<
    	"{" 								  				   	<< endl <<
    	" " 								  				   	<< endl;
	}
}

void
ImplFileGen::GenCodeBody(const std::string& strClassName) 			throw(std::string)
{
  GetOstream() <<
    "/* ********************************* " << endl <<
    " * " << strClassName << endl <<
    " ***********************************/" << endl;
  if (mCommands.Singleton())
  {
    GetOstream() << 
    "std::auto_ptr<" << strClassName << "> " << strClassName << "::s_instance; " << endl << endl;
  }


	if (mCommands.Ctor())
	{
		GetOstream() <<
		strClassName << "::" << strClassName << "()"  		 << endl <<
    	"{" 												 << endl <<
    	" " 												 << endl <<
    	"}" 												 << endl <<
		"" 													 << endl;
	}

	if (mCommands.Dtor())
	{
		GetOstream() <<
    	strClassName << "::~" << strClassName << "()"  		 << endl <<
    	"{" 												 << endl <<
    	" " 												 << endl <<
    	"}" 												 << endl <<
    	"" 													 << endl;
	}

	if (mCommands.UseDumpDiagnostics())
	{
		GetOstream() <<
    	"void"		 										   						<< endl <<
    	strClassName << "::DumpDiagnostics() const"		   							<< endl <<
    	"{" 												   						<< endl;

		if(mCommands.GetProjectName() == "atc")
		{
			GetOstream() <<
			"    ATC_TRACE(0x01, \"Tracing from " <<  strClassName
							<< "::DiagnosticsDump()\" "								<< endl <<
			"                    << atc::endl << atc::endl);"		   				<< endl;
		}
		else
		{
			GetOstream() <<
			"    std::cout << std::endl << std::endl << "					<< endl <<
			"    \"" << strClassName
					<< " Diagnostics dump \"<< std::endl << std::endl;"  	<< endl;
		}
		GetOstream() <<
		"}" 															  << endl <<
    	" "  														 	  << endl;
	}

  if (mCommands.Singleton() && !mCommands.IccFile())
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

void
ImplFileGen::GenEpilog() throw(std::string)
{
	if (mCommands.UseNamespace())
	{
		GetOstream() <<
    	" "  														 	<< endl <<
    	"} // end of the " << mCommands.GetNamespace() << " namespace"	<< endl;
	}
}

} //end of code_gen namespace
