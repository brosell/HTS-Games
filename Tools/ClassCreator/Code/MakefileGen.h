/* ****************************************************************************
 *
 *  MakefileGen.h
 *  Created by John F. Hubbard, on Sat Aug 12 2000, 16:49:08 PST
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
 *  File Contents: Interface and documentation of the MakefileGen class.
 *
 * %version: 2.27 %
 * %date_modified: Sun Oct 29 10:36:00 2000 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */
#ifndef ATD_CODE_GEN_MAKEFILEGEN_H
#define ATD_CODE_GEN_MAKEFILEGEN_H

#include "CodeGenerator.h"
#include "WriteSentry.h"

namespace code_gen
{
/** Purpose: MakefileGen encapsulates the way that the makefile for the
 *  class is generated.  MakefileGen inherits both a required interface (so that
 *  ClassCreator can call it) and some helper methods, from CodeGenerator.
 */

class MakefileGen : public CodeGenerator
{
public:
	MakefileGen(const DigestedCommands& commands) throw(std::string);
    virtual ~MakefileGen();

	virtual void GenCommentHeader() 	throw(std::string);
	virtual void GenPreface() 			throw(std::string);

protected:
	/// GetOstream overrides the pure virtual method from the CodeGenerator class.
	virtual std::ostream& 	GetOstream();

private:
// No copying or assignment is supported, at this point:
    MakefileGen(const MakefileGen&);
    MakefileGen& operator=(const MakefileGen&);

	WriteSentry mWriter; // The WriteSentry ctor can throw a std::string
};
} // end of code_gen namespace

#endif // ifndef ATD_CODE_GEN_MAKEFILEGEN_H
