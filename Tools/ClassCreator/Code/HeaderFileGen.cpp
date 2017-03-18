/* ****************************************************************************
 *
 *  HeaderFileGen.cpp
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
 *  File Contents: Implementation of the HeaderFileGen class.
 *  Please see HeaderFileGen.h for documentation of this class.
 *
 * %version: 2.30 %
 * %date_modified: Thu Nov 16 20:04:11 2000 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "HeaderFileGen.h"

namespace code_gen
{
using std::endl;

HeaderFileGen::HeaderFileGen(const DigestedCommands& commands)
							 throw(std::string)
	: 	CodeGenerator	(commands),
		mWriter			(commands.GetHeaderFile(),
						 commands.GetWriteSentryMode())
{
}

HeaderFileGen::~HeaderFileGen()
{

}

std::ostream&
HeaderFileGen::GetOstream()
{
	return mWriter.GetOstream();
}

void
HeaderFileGen::GenCommentHeader() 	throw(std::string)
{
	std::ostringstream ostCustom;
	ostCustom <<
    " *"														<< endl <<
    " *  File Contents: Interface and documentation of the "
		<< mCommands.GetBaseFilename() << " component."  		<< endl <<
    " *"														<< endl;

	GenerateDefaultCommentHeader(mCommands.GetHeaderFile(), ostCustom);
}

void
HeaderFileGen::GenPreface() 			throw(std::string)
{
	GetOstream() <<
	"#ifdef WIN32"					   						<< endl <<
	"#pragma warning (disable : 4786) // disable MSVC's useless template length warning"	<< endl <<
	"#endif // WIN32"					   					<< endl <<
	endl <<
    "#ifndef " << CreateUniqueName()				<< endl <<
    "#define " << CreateUniqueName() 				<< endl <<
    " " 											<< endl;

  if (mCommands.Singleton())
  {
    GetOstream() <<
    "#include <memory>" << endl;
  }
	if (mCommands.UseNamespace())
	{
		GetOstream() <<
    	"namespace " << mCommands.GetNamespace() << ""  << endl <<
    	"{" 								  		    << endl <<
    	" " 								  		    << endl;
	}
}

void
HeaderFileGen::GenCodeBody(const std::string& strClassName) throw(std::string)
{
	GetOstream() << endl <<
	"/** Purpose: TODO: Describe the purpose of the class."				  		<< endl <<
	" *  (Everything that you write here will show up in the"		  			<< endl <<
	" *  doc++ generated documentation.)"										<< endl <<
	" */"																		<< endl <<
	"class " << strClassName 									   				<< endl <<
    "{"  																		<< endl <<
    "public:"  																	<< endl;
  if (mCommands.Singleton())
  {
    GetOstream() <<
      "  static " << strClassName << "* instance(); " << endl;
  }

  else if (mCommands.Ctor())
	{
		GetOstream() <<
    "    /// Constructor." 														<< endl <<
    "    " << strClassName << "();" 							   				<< endl;
	}

	if (mCommands.Dtor())
	{
		GetOstream() <<
      "public:" << endl <<
    	"    virtual ~" << strClassName << "();" 					   				<< endl;
	}

	if (mCommands.UseCheckValid())
	{
		GetOstream() <<
		" "  																		<< endl <<
    	"    /// CheckValid() is designed to check the class invariants."			<< endl <<
    	"    inline void CheckValid() const;" 										<< endl;
	}
	if (mCommands.UseDumpDiagnostics())
	{
		GetOstream() <<
    	" "  																		<< endl <<
    	"    /// DumpDiagnostics() dumps the object's state to standard output."	<< endl <<
    	"    void DumpDiagnostics() const;" 										<< endl <<
    	" "  																		<< endl;
	}
	if (mCommands.PublicCopyCtor())
	{
	GetOstream() <<
    "public:"  																	<< endl <<
    "	// TODO: Provide an implementation for the copy constructor:"			<< endl <<
    "    " << strClassName << "(const " << strClassName << "&);"				<< endl;
	}
	else if (mCommands.CopyCtor())
	{
	GetOstream() <<
    "private:"  																<< endl <<
    "	// Copying of this class is prohibited:"								<< endl <<
    "    " << strClassName << "(const " << strClassName << "&);"				<< endl;
	}

	if (mCommands.PublicAssignmentOperator())
	{
	GetOstream() <<
    "public:"  																	<< endl <<
    "	// TODO: Provide an implementation for the assignment operator:"		<< endl <<
	"    " << strClassName << "& operator=(const " << strClassName << "&);"		<< endl;
	}
	else if (mCommands.AssignmentOperator())
	{
	GetOstream() <<
    "private:"  																<< endl <<
    "	// Assignment to this class is prohibited:"								<< endl <<
	"    " << strClassName << "& operator=(const " << strClassName << "&);"		<< endl;
	}

  if (mCommands.Singleton())
  {
    GetOstream() <<
      "private:" << endl <<
    "  /// Constructor." 														<< endl <<
    "  " << strClassName << "();" 							   				<< endl <<
    "  static std::auto_ptr<" << strClassName << "> s_instance; " << endl;
  }


	GetOstream() <<
    ""  																		<< endl <<
    "};"  																		<< endl;
}

void
HeaderFileGen::GenEpilog() throw(std::string)
{
	if (mCommands.IccFile())
	{
		GetOstream() <<
    	" "  														 	<< endl <<
    	"#include \"" << mCommands.GetInlineFile() << "\""				<< endl;
	}

	if (mCommands.UseNamespace())
	{
		GetOstream() <<
    	"} // end of the " << mCommands.GetNamespace() << " namespace"	<< endl <<
    	" "  									  						<< endl;
	}

	GetOstream() <<
    "#endif // #ifndef " << CreateUniqueName()						<< endl <<
    " " 															<< endl;
}

} //end of code_gen namespace
