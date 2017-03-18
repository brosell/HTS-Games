/* ****************************************************************************
 *
 *  utCommandLine.cpp
 *  Created by John F. Hubbard, on Thu Sep 07 2000, 15:28:34 PST
 *
 *  Copyright (c) 2000, ATD Azad Technology Development Corporation
 *
 *
 *  File Contents: Unit test for the the CommandLine class.
 *  Please see CommandLine.h for full documentation of this class.
 *
 * %version: 1 %
 * %date_modified: Thu Nov 02 16:31:58 2000 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */

#include <string>
#include <iostream>
#include "tools/CommandLine.h"

int main(int argc, char* argv[])
{
	try
	{
    	tools::CommandLine objCommandLine(argc, argv);
    	objCommandLine.DumpDiagnostics();
	}
	catch(std::string& strError)
	{
		std::cout << strError << std::endl;
	}

    return 0;
}
