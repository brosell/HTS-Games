/* ****************************************************************************
 *
 *  InlineFileGen.h
 *  Created by John F. Hubbard, on Sat Aug 12 2000, 16:48:50 PST
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
 *  File Contents: Interface and documentation of the InlineFileGen class.
 *
 * %version: 2.27 %
 * %date_modified: Sun Oct 29 10:35:56 2000 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */
#ifndef ATD_CODE_GEN_INLINEFILEGEN_H
#define ATD_CODE_GEN_INLINEFILEGEN_H

#include "CodeGenerator.h"
#include "WriteSentry.h"

namespace code_gen
{
/** Purpose: InlineFileGen encapsulates the way that the inline file for the
 *  class is generated.  (The inline file is included from the header file. It
 *  contains implementation code for inline and template methods.) InlineFileGen
 *  inherits both a required interface (so that ClassCreator can call it) and
 *  some helper methods, from CodeGenerator.
 */

class InlineFileGen : public CodeGenerator
{
public:
	InlineFileGen(const DigestedCommands& commands) throw(std::string);
    virtual ~InlineFileGen();

	virtual void GenCommentHeader() 	throw(std::string);
	virtual void GenCodeBody(const std::string& strClassName) throw(std::string);

protected:
	/// GetOstream overrides the pure virtual method from the CodeGenerator class.
	virtual std::ostream& 	GetOstream();

private:
// No copying or assignment is supported, at this point:
    InlineFileGen(const InlineFileGen&);
    InlineFileGen& operator=(const InlineFileGen&);

	WriteSentry mWriter; // The WriteSentry ctor can throw a std::string
};
} // end of code_gen namespace

#endif // ifndef ATD_CODE_GEN_INLINEFILEGEN_H
