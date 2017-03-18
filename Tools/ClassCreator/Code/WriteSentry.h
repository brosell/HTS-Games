/* ****************************************************************************
 *
 *  WriteSentry.h
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
 *  File Contents: Inline definitions for the WriteSentry class.
 *  Please see WriteSentry.h for documentation of this class.
 *
 * %version: 2.26 %
 * %date_modified: Fri Oct 20 18:36:59 2000 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */
#ifndef ATD_CODE_GEN_WRITESENTRY_H
#define ATD_CODE_GEN_WRITESENTRY_H

#include <fstream>

namespace code_gen
{
	const int VERBOSE	= 1;
	const int OVERWRITE	= 2;

/** Purpose: WriteSentry encapsulates the way an output file is written to.
 *  It also provides a convenient way to open, write to, and close a file,
 *  merely by declaring a WriteSentry object in a given C++ scope.  When the
 *  WriteSentry object goes out of scope, its destructor is called, and the
 *  file is written out and closed.
 */
class WriteSentry
{
public:
	WriteSentry(const std::string& strFileName,
						// modes include VERBOSE
						// and           OVERWRITE
						int mode,
						bool bReallyCreate = true) throw(std::string);

	virtual ~WriteSentry();
	inline std::ostream& GetOstream() throw(std::string);

private:
// No copying or assignment is supported, at this point:
    WriteSentry(const WriteSentry&);
    WriteSentry& operator=(const WriteSentry&);

	std::ofstream mOutputFile;
};

//////////////////////////////////////////////////////////////////////////////
// Inline method implementation code
// (too trivial to deserve it's own .icc file):

inline
std::ostream& WriteSentry::GetOstream() throw(std::string)
{
	// This is always a valid thing to do, even when the output file was not
	// opened:
	return mOutputFile;
}

} // end of code_gen namespace
#endif // ifndef ATD_CODE_GEN_WRITESENTRY_H
