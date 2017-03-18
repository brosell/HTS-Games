/* ****************************************************************************
 *
 *  UnitTestFileGen.h
 *  Created by John F. Hubbard, on Sat Aug 12 2000, 16:51:06 PST
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
 *  File Contents: Interface and documentation of the UnitTestFileGen class.
 *
 * %version: 2.27 %
 * %date_modified: Sun Oct 29 10:36:03 2000 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */
#ifndef ATD_CODE_GEN_UNITTESTFILEGEN_H
#define ATD_CODE_GEN_UNITTESTFILEGEN_H

#include "CodeGenerator.h"
#include "WriteSentry.h"

namespace code_gen
{
/** Purpose: UnitTestFileGen encapsulates the way that the unit test file for the
 *  class is generated.  The unit test file usually contains a main() function,
 *  which allows everything to be fully compiled, linked and executed.
 *  UnitTestFileGen inherits both a required interface (so that
 *  ClassCreator can call it) and some helper methods, from CodeGenerator.
 */

class UnitTestFileGen : public CodeGenerator
{
public:
	UnitTestFileGen(const DigestedCommands& commands) throw(std::string);
    virtual ~UnitTestFileGen();

	virtual void GenCommentHeader() 	throw(std::string);
	virtual void GenPreface()		 	throw(std::string);
	virtual void GenCodeBody(const std::string& strClassName) throw(std::string);
	virtual void GenEpilog() 			throw(std::string);

protected:
	/// GetOstream overrides the pure virtual method from the CodeGenerator class.
	virtual std::ostream& 	GetOstream();

private:
// No copying or assignment is supported, at this point:
    UnitTestFileGen(const UnitTestFileGen&);
    UnitTestFileGen& operator=(const UnitTestFileGen&);

	WriteSentry mWriter;  // The WriteSentry ctor can throw a std::string
};
} // end of code_gen namespace

#endif // ifndef ATD_CODE_GEN_UNITTESTFILEGEN_H
