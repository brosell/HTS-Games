/* ****************************************************************************
 *
 *  HeaderFileGen.h
 *  Created by John F. Hubbard, on Fri Aug 11 2000, 16:04:24 PST
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
 *  File Contents: Interface and documentation of the HeaderFileGen class.
 *
 * %version: 2.27 %
 * %date_modified: Sun Oct 29 10:35:48 2000 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */
#ifndef ATD_CODE_GEN_HEADERFILEGEN_H
#define ATD_CODE_GEN_HEADERFILEGEN_H

#include "CodeGenerator.h"
#include "WriteSentry.h"

namespace code_gen
{
/** Purpose: HeaderFileGen encapsulates the way that the header file for the
 *  class is generated.  It inherits both a required interface (so that
 *  ClassCreator can call it) and some helper methods, from CodeGenerator.
 */

class HeaderFileGen : public CodeGenerator
{
public:
	HeaderFileGen(const DigestedCommands& commands) throw(std::string);
    virtual ~HeaderFileGen();

	virtual void GenCommentHeader() 	throw(std::string);
	virtual void GenPreface() 			throw(std::string);
	virtual void GenCodeBody(const std::string& strClassName) throw(std::string);
	virtual void GenEpilog() 			throw(std::string);

protected:
	/// GetOstream overrides the pure virtual method from the CodeGenerator class.
	virtual std::ostream& 	GetOstream();

private:
// No copying or assignment is supported, at this point:
    HeaderFileGen(const HeaderFileGen&);
    HeaderFileGen& operator=(const HeaderFileGen&);

	WriteSentry mWriter; // The WriteSentry ctor can throw a std::string
};
} // end of code_gen namespace

#endif // ifndef ATD_CODE_GEN_HEADERFILEGEN_H
