/* ****************************************************************************
 *
 *  main.cpp
 *  Created by John F. Hubbard, on Sun Aug 06 2000, 18:06:15 PST
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
 *  File Contents: Command-line program to generate C++ code.
 *  Used for creating C++ classes.
 *
 * %version: 2.27 %
 * %date_modified: Sun Oct 29 10:36:09 2000 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <iostream>
#include <string>
#include "ClassCreator.h"

int main(int argc, char* argv[])
{
	try
	{
		using namespace code_gen;
		DigestedCommands commands(argc, argv);
		ClassCreator creator(commands);
		creator.GenerateCode();
	}
	catch(std::string& strErrorMessage)
	{
		std::cout << strErrorMessage << std::endl;
	}
	return 0;
}
