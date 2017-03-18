/* ****************************************************************************
 *
 *  WriteSentry.cpp
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
 *  File Contents: Implementation of the WriteSentry class.
 *  Please see WriteSentry.h for documentation of this class.
 *
 * %version: 2.26 %
 * %date_modified: Fri Oct 20 18:36:56 2000 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include <ios>
#include <iostream>
#include <sstream>
#include "WriteSentry.h"

namespace code_gen
{

WriteSentry::WriteSentry(const std::string& strFileName,
						// modes include VERBOSE
						// and           OVERWRITE
						int mode,
						bool bReallyCreate)  throw(std::string)
{
	if(bReallyCreate)
	{
		using namespace std;
		bool bCreateTheFile = (mode & OVERWRITE) != 0;
		try
		{
			if (!bCreateTheFile)
			{
				FILE* fd = fopen(strFileName.c_str(), "r");
				if (fd)
				{
					if (mode & VERBOSE)
					{
						cerr << "Did NOT create " << strFileName
						    	<< " because it already exists." << endl;
					}
					fclose(fd);
				}
				else
				{
					bCreateTheFile = true;
				}
				// end if (fopen...)
			} // end if (mode & OVERWRITE)

			if (bCreateTheFile)
			{
				mOutputFile.open(strFileName.c_str(), std::ios_base::trunc);
				if (mode & VERBOSE)
				{
					cerr << "Created " << strFileName << endl;
				}
			} // end if (bCreateTheFile)
		}
		catch (ios_base::failure& failed)
		{
			string strMessage =  string("WriteSentry: Failed to open ") +
			 				    	strFileName + "\n" +
							   		string("Reason: ") + failed.what() + "\n";
			throw (strMessage);
		}
	} //end if(bReallyCreate)
}

WriteSentry::~WriteSentry()
{
	if(mOutputFile != NULL)
	{
		mOutputFile.close();
	}
}

} //end of code_gen namespace
