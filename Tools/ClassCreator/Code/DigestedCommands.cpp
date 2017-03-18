/* ****************************************************************************
 *
 *  DigestedCommands.cpp
 *  Created by John F. Hubbard, on Fri Aug 25 2000, 10:25:35 PST
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
 *  File Contents: Implementation of the DigestedCommands class.
 *  Please see DigestedCommands.h for full documentation of this class.
 *
 * %version: 2.38 %
 * %date_modified: Fri Aug 10 14:05:02 2001 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <sstream>
#include <string>
#include <iostream>
#include "DigestedCommands.h"
#include "WriteSentry.h"
#include "PackedString.h"

namespace code_gen
{

DigestedCommands::DigestedCommands(int argc, char* argv[])
								   throw (std::string)
	:	CommandLine(argc, argv), mfWriteSentryMode(0)
{
	if (   Count() < 2       ||
		 (!Exists("class"))  ||
		 (!Exists("author")))
	{
		throw Usage();
	}
	mstrClassList 	   		= GetByName("class");
	mstrAuthor 		   		= GetByName("author");

	// Added to support multiple classes per file, and control of copy/assignment:
	mbSccsKeywords	   		=  Exists("sccs_keywords") || Exists("sccs");
	mbContinuusKeywords		=  Exists("continuus_keywords") || Exists("ct");
	mbCVS_Keywords	   		=  Exists("cvs_keywords") || Exists("cvs");
	mbOpenSourceNotice 		=  Exists("open_source_notice") || Exists("os");

	if (Exists("copyright"))
	{	mstrCopyright = GetByName("copyright");
	}
	else if (Exists("c"))
	{	mstrCopyright = GetByName("c");
	}
	else
	{
		mstrCopyright =
 			"Copyright (c) 2003, Bert Rosell" "\n"
 			" *";
	}

	mbUnitTestFile 	   	= !Exists("no_unit_test") && !Exists("no_ut");
	mbMakefile 		   	= !Exists("no_makefile") && !Exists("no_mf");
	mbCtor				= !Exists("no_ctor");
	mbDtor				= !Exists("no_dtor");
	mbIccFile			= !Exists("no_icc");
	mbCheckValid	 	= !Exists("no_check_valid") && !Exists("no_cv");
	mbDumpDiagnostics	= !Exists("no_dump_diagnostics") && !Exists("no_dd");
	mbNamespace			= Exists("namespace")  || Exists("ns");
	mbDtor				= !Exists("no_dtor");
	mbCopyCtor				= mbCtor  && !Exists("no_copy_ctor");
	mbAssignmentOperator 	= !Exists("no_assignment_operator") && !Exists("no_op=");
	mbPublicCopyCtor		=  Exists("public_copy_ctor") && mbCopyCtor;
	mbPublicAssignmentOperator		= (Exists("public_assignment_operator") ||
									  Exists("pub_op=")) &&
									  mbAssignmentOperator;

  mbSingleton = (Exists("singleton") || Exists("sing"));
	// end of addition.

	if (Exists("verbose") || Exists("v"))
	{	mfWriteSentryMode |= VERBOSE;
	}

	if (Exists("overwrite") || Exists("ow"))
	{	mfWriteSentryMode |= OVERWRITE;
	}

	if (Exists("project"))
	{	mstrProjectName = GetByName("project");
	}

	if (Exists("namespace"))
	{	mstrNamespace = GetByName("namespace");
	}
	else if (Exists("ns"))
	{	mstrNamespace = GetByName("ns");
	}

	tools::PackedString objClasses(mstrClassList);
	std::string strClassName = *objClasses.GetList().begin();

	if (Exists("base_filename"))
	{	mstrBaseFilename = GetByName("base_filename");
	}
	else if (Exists("file"))
	{	mstrBaseFilename = GetByName("file");
	}
	else
	{	mstrBaseFilename = strClassName;
	}

	mstrHeaderFile 		= mstrBaseFilename + ".h";
	mstrImplFile 		= mstrBaseFilename + ".cpp";
	mstrInlineFile 		= mstrBaseFilename + ".icc";
	mstrMakefile 		= "makefile";
	mstrUnitTestFile 	= std::string("ut") + mstrBaseFilename + ".cpp";
}

DigestedCommands::~DigestedCommands()
{

}

std::string
DigestedCommands::Usage()
{
	using std::endl;
	std::ostringstream ost;
	ost << endl <<
	"*******************************************************************************" 	<< endl <<
	"ClassCreator Version 2.38, Created by John F. Hubbard, 10 August 2001"	 	 	 	<< endl <<
	endl 																				<< endl <<
	"Usage: fcc -class <list_of_class_names> (see example below)"  		<< endl <<
	"           -author <authors_name>  "		 						<< endl <<
	"          [-namespace <namespace_name> | -ns <namespace_name>]"	<< endl <<
	"          [-overwrite | -ow]"					 					<< endl <<
	"          [-verbose | -v]"					   						<< endl <<
	"          [-no_unit_test | -no_ut]" 								<< endl <<
	"          [-no_makefile | -no_mf]"	  					   			<< endl <<
	"          [-project <project_name>]"  		   						<< endl <<
	"          [-sccs_keywords | -sccs]"  	   							<< endl <<
	"          [-continuus_keywords | -ct]"  			  				<< endl <<
	"          [-cvs_keywords | -cvs]"  			  			  		<< endl <<
	"          [-open_source_notice | -os]"  	  	  					<< endl <<
	"          [-copyright <copyright> | -c <copyright>]"  		  		<< endl <<
	"          [-base_filename <base_filename> | -file <base_filename>]"<< endl <<
	"          [-no_copy_ctor]"  			   	  						<< endl <<
	"          [-no_assignment_operator | -no_op=]"  	  				<< endl <<
	"          [-no_ctor]"  				   							<< endl <<
	"          [-no_dtor]"  				   							<< endl <<
	"          [-public_copy_ctor]"  									<< endl <<
	"          [-public_assignment_operator | -pub_op=]"  				<< endl <<
	"          [-no_dump_diagnostics | -no_dd]"  						<< endl <<
	"          [-no_check_valid | -no_cv]"				  				<< endl <<
	"          [-no_icc]"  	   											<< endl <<
  "          [-singleton | -sing]" << endl <<
	"          [-settings_file <filename>]"  	  						<< endl <<
	endl 										 				   		<< endl <<
	"Abbreviations: ctor = constructor, dtor = destructor"	 			<< endl <<
	endl 										    					<< endl <<
	"A simple example:" 												<< endl <<
	endl 										   						<< endl <<
	"    fcc -verbose -class Airplane -namespace airport -author \"John F. Hubbard\""			<< endl <<
	endl 										    											<< endl <<
	"This example generates several classes in the same set of FruitFiles.xxx files:" 			<< endl <<
	endl 										    											<< endl <<
	"    fcc -file FruitFiles -class \"Apple Orange Pear\" "
					"-ns fruits -author \"John F. Hubbard\""									<< endl <<
	endl 																						<< endl <<
	"*******************************************************************************" 			<< endl <<
	endl;
	return ost.str();
}

} // end of the code_gen namespace
