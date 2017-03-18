/* ****************************************************************************
 *
 *  MakefileGen.cpp
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
 *  File Contents: Implementation of the MakefileGen class.
 *  Please see MakefileGen.h for documentation of this class.
 *
 * %version: 2.38 %
 * %date_modified: Fri Aug 10 14:00:02 2001 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "MakefileGen.h"

namespace code_gen
{

using std::endl;

MakefileGen::MakefileGen(const DigestedCommands& commands)
						 throw(std::string)
	: 	CodeGenerator	(commands),
		mWriter			(commands.GetMakefile(),
					 	 commands.GetWriteSentryMode(),
						 commands.WillCreateMakefile())
{
}


MakefileGen::~MakefileGen()
{

}

std::ostream&
MakefileGen::GetOstream()
{
	return mWriter.GetOstream();
}

void
MakefileGen::GenCommentHeader() 	throw(std::string)
{
	GetOstream() <<
	"#########################################################################" 	<< endl <<
    "#  " << mCommands.GetMakefile() << ""							 			   	<< endl <<
    "#  Created by " << mCommands.GetAuthor() << " on " << DateStamp()				<< endl <<
	"#" 	  																		<< endl <<
	"#  Copyright (c) 2001, ATD Azad Technology Development Corporation" 			<< endl <<
	"#" 																			<< endl <<
	"#            The Reliable Software Outsource Resource" 						<< endl <<
	"#        You hire us, we do it for you, and we do it right." 					<< endl <<
	"#" 																			<< endl <<
	"#                       www.azadtech.com" 										<< endl <<
	"#" 																			<< endl <<
	"#  Permission is granted to use this code without restriction," 				<< endl <<
	"#  as long as this copyright notice appears in all source files." 				<< endl <<
	"#" 																			<< endl <<
	"#" 																			<< endl <<
	"#  File Contents: makefile for the ClassCreator project." 						<< endl <<
	"#" 																			<< endl <<
	"# BASIC USAGE:  This is easy!  As long as you set the TARGET variable" 		<< endl <<
	"#               (either in your environmental variables, or by un-commenting" 	<< endl <<
	"#               one of the \"TARGET=xxx\" lines below), the makefile will" 	<< endl <<
	"#               work for you (just type \"make\" or \"make all\")." 			<< endl <<
	"#               In addition, here are a few refinements:" 						<< endl <<
	"#" 																			<< endl <<
	"# ADVANCED USAGE:" 															<< endl <<
	"#    1. You can add new class files by adding the associated object file" 		<< endl <<
	"#    name to the list of object files in the CPP_OBJS variable, below." 		<< endl <<
	"#    That is, if you add a new class Blue, add \"${TARGET}/Blue.o\" to the list." << endl <<
	"#" 																			<< endl <<
	"#    2. Similarly, you can add additional unit tests by adding to the list of" << endl <<
	"#    object files in the UNIT_TEST_OBJS variable." 							<< endl <<
	"#" 																			<< endl <<
	"#    3. If you need to change any of the compile or link flags, they are" 		<< endl <<
	"#    subdivided into groups, in order to make this easy.  For example," 		<< endl <<
	"#    you could type \"make TARGET=SOLARIS_SPARC DEBUG_FLAGS= \" in order" 		<< endl <<
	"#    to turn off the -g option (which adds debug symbols)." 					<< endl <<
	"#" 																			<< endl <<
	"#    4. You can use a different C++ library by changing just two" 				<< endl <<
	"#    variables: CPP_LINK_LIBRARY and CPP_INCLUDE_DIRECTORY.  Currently," 		<< endl <<
	"#    these are pointing to a typical location for the STLport Standard" 		<< endl <<
	"#    C++ Library.  I recommend that you stick with this, as it is free," 		<< endl <<
	"#    portable, thread-safe, and highly standards-compliant (as of July, 2001);"<< endl <<
	"#    you can download STLport from http://www.stlport.org . The" 				<< endl <<
	"#    C/C++ Users Journal also has an article on libraries that shows STLport" 	<< endl <<
	"#    in a good light; see http://www.cuj.com ." 								<< endl <<
	"#    -- John F. Hubbard, 27 July 2001." 										<< endl <<
	"#" 																			<< endl <<
	"#  $" "Version: 1.0 $" 			   											<< endl <<
	"#  $" "Date: " 	<< DateStamp() 				<< " $ "		 				<< endl <<
	"#  $" "Author: " 	<< mCommands.GetAuthor() 	<< " $" 						<< endl <<
	"#" 																			<< endl <<
	"#########################################################################" 	<< endl <<
    endl																			<< endl;
}

void
MakefileGen::GenPreface() 			throw(std::string)
{

	std::string coreName = mCommands.GetBaseFilename();

	GetOstream() <<
	"PROGRAM=ut" << coreName																		<< endl <<
	"" 																								<< endl <<
	"CPP_OBJS=            ${TARGET}/"   << coreName << ".o   "										<< endl <<
	"" 																								<< endl <<
	"UNIT_TEST_OBJS=      ${TARGET}/ut" << coreName << ".o" 					  					<< endl <<
	"" 																								<< endl <<
	"# Uncomment the target that you are building for. Alternatively, you can use" 					<< endl <<
	"# the command: make TARGET=LINUX_X86 ." 														<< endl <<
	"" 																								<< endl <<
	"#TARGET=SOLARIS_SPARC" 																		<< endl <<
	"#TARGET=SOLARIS_X86" 																			<< endl <<
	"#TARGET=LINUX_X86" 																			<< endl <<
	"#TARGET=LYNXOS_X86" 																			<< endl <<
	"#TARGET=LYNXOS_PPC" 																			<< endl <<
	"#TARGET=WIN32_GCC" 																			<< endl <<
	"" 																								<< endl <<
	"# Change the value of these two directories to point to a standards-compliant C++" 			<< endl <<
	"# Library.  If you are using STL Port (free, from http://www.stlport.org), then no" 			<< endl <<
	"# changes are necessary." 																		<< endl <<
	"" 																								<< endl <<
	"CPP_LINK_LIBRARY=${HOME}/cvs_wa/atc/thirdparty/STLport-4.0/lib/${TARGET}/libstlport_gcc.a" 	<< endl <<
	"CPP_INCLUDE_DIRECTORY=${HOME}/cvs_wa/atc/thirdparty/STLport-4.0/stlport" 						<< endl <<
	"" 																								<< endl <<
	"INCLUDES=-I${CPP_INCLUDE_DIRECTORY} -I." 														<< endl <<
	"LIBS:=  ${CPP_LINK_LIBRARY}" 																	<< endl <<
	"" 																								<< endl <<
	"LOCAL_CXX:=gcc" 																				<< endl <<
	"LINK:=gcc" 																					<< endl <<
	"" 																								<< endl <<
	"LINK_FLAGS= -lgcc -lm -fno-builtin" 															<< endl <<
	"" 																								<< endl <<
	"OPTIMIZE_FLAGS=           -O2" 																<< endl <<
	"DEBUG_FLAGS=              -g" 																	<< endl <<
	"WARNING_LEVEL_FLAGS=      -Wall -Wno-unknown-pragmas -Wno-unused" 								<< endl <<
	"THIRD_PARTY_STL_FLAGS=    -fno-builtin -static" 												<< endl <<
	"PLATFORM_SPECIFIC_FLAGS=" 																		<< endl <<
	"" 																								<< endl <<
	"ifeq (${TARGET},SOLARIS_SPARC)" 																<< endl <<
	"	# Change or add any Solaris-specific flags here" 											<< endl <<
	"endif" 																						<< endl <<
	"" 																								<< endl <<
	"ifeq (${TARGET},LINUX_X86)" 																	<< endl <<
	"	# Change or add any Linux-specific flags here" 												<< endl <<
	"endif" 																						<< endl <<
	"" 																								<< endl <<
	"ifeq (${TARGET},LYNXOS_X86)" 																	<< endl <<
	"	# Change or add any LynxOS-specific flags here" 											<< endl <<
	"	LINK_FLAGS= -lgcc -lm" 																		<< endl <<
	"	PLATFORM_SPECIFIC_FLAGS=-D__Lynx__" 														<< endl <<
	"endif" 																						<< endl <<
	"" 																								<< endl <<
	"ifeq (${TARGET},LYNXOS_PPC)" 																	<< endl <<
	"	# Change or add any LynxOS-specific flags here" 											<< endl <<
	"	LINK_FLAGS= -lgcc -lm" 																		<< endl <<
	"	PLATFORM_SPECIFIC_FLAGS=-D__Lynx__" 														<< endl <<
	"endif" 																						<< endl <<
	"" 																								<< endl <<
	"CXX_FLAGS:=-D${TARGET}                \\" 														<< endl <<
	"           -D_REENTRANT               \\" 														<< endl <<
	"           ${OPTIMIZE_FLAGS}          \\" 														<< endl <<
	"           ${DEBUG_FLAGS}             \\" 														<< endl <<
	"           ${THIRD_PARTY_STL_FLAGS}   \\" 														<< endl <<
	"           ${WARNING_LEVEL_FLAGS}     \\" 														<< endl <<
	"           ${PLATFORM_SPECIFIC_FLAGS}"  														<< endl <<
	"" 																								<< endl <<
	"default: ${TARGET}/${PROGRAM}" 																<< endl <<
	"" 																								<< endl <<
	"all: ${TARGET}/${PROGRAM} doc" 																<< endl <<
	"" 																								<< endl <<
	"doc:" 																							<< endl <<
	"	@if [ ! -d html ];then mkdir html;fi" 														<< endl <<
	"	-@ doc++ -d html -H -u *.h" 																<< endl <<
	"" 																								<< endl <<
	"cleandoc:"  															    					<< endl <<
	"	-@if [ -d html ];then rm -r html;fi"  														<< endl <<
	""  															   								<< endl <<
	"setup:"  															   							<< endl <<
	"	@echo \"Building the ${PROGRAM} program...\""  												<< endl <<
	"	@if [ ! -d ${TARGET} ];then mkdir ${TARGET};fi" 											<< endl <<
	"" 																								<< endl <<
	"${TARGET}/${PROGRAM}: setup ${CPP_OBJS} ${UNIT_TEST_OBJS}" 									<< endl <<
	"	${LINK} ${CPP_OBJS} ${UNIT_TEST_OBJS} ${LIBS} ${LINK_FLAGS} -o ${TARGET}/${PROGRAM}" 		<< endl <<
	"" 																								<< endl <<
	"${UNIT_TEST_OBJS}: ${TARGET}/%.o: %.cpp" 														<< endl <<
	"	${LOCAL_CXX} -c ${CXX_FLAGS} $< -o $@ ${INCLUDES}" 											<< endl <<
	"" 																								<< endl <<
	"${CPP_OBJS}: ${TARGET}/%.o: %.cpp %.h %.icc" 													<< endl <<
	"	${LOCAL_CXX} -c ${CXX_FLAGS} $< -o $@ ${INCLUDES}" 											<< endl <<
	"" 																								<< endl <<
	"cleanall: cleandoc clean" 																		<< endl <<
	"" 																								<< endl <<
	"clean:" 																						<< endl <<
	"	-@if [ -d html ];then rm html/*;fi" 														<< endl <<
	"	-@if [ -d ${TARGET} ];then rm -r ${TARGET} ;fi" 											<< endl <<
	"" 																								<< endl <<
	"test: all" 																					<< endl <<
	"	@$(TARGET)/$(PROGRAM) > $(PROGRAM).out" 													<< endl <<
	"" 																								<< endl <<
	"	@if cmp -s $(PROGRAM).sig $(PROGRAM).out; then                          	        \\" 			<< endl <<
	"		echo \"UnitTest $(PROGRAM):	SUCCESS\";                                       \\" 			<< endl <<
	"	else                                                                    	        \\" 			<< endl <<
	"		if [ -x $(PROGRAM).sig ]; then                                      	        \\" 			<< endl <<
	"			echo \"UnitTest $(PROGRAM):	FAILED\";                                \\" 			<< endl <<
	"			diff $(PROGRAM).sig $(PROGRAM).out;                                     \\" 			<< endl <<
	"		else                                                                	        \\" 			<< endl <<
	"			echo \"UnitTest $(PROGRAM):	UNKNOWN (no signature file exists)\"; 	\\" 			<< endl <<
	"		fi                                                                              \\" 			<< endl <<
	"	fi" 																						<< endl <<
	"" 																								<< endl;
}

} //end of code_gen namespace
