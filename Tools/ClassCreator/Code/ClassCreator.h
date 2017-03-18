/* ****************************************************************************
 *
 *  ClassCreator.h
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
 *  File Contents: Interface and documentation of the ClassCreator class.
 *
 * %version: 2.27 %
 * %date_modified: Sun Oct 29 10:35:27 2000 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */
#ifndef ATD_CODE_GEN_CLASSCREATOR_H
#define ATD_CODE_GEN_CLASSCREATOR_H

#include <string>
#include "DigestedCommands.h"

// This forward declaration is outside of the namespace only because this allows
// doc++ to generate documentation a little better:
class CodeGenerator;

namespace code_gen
{
/**Purpose: Generate C++ code to the programmer's specifications.
 * Note that ClassCreator is within the code_gen namespace.
 */
class ClassCreator
{
public:
	/// Constructor
	ClassCreator(const DigestedCommands& commands);
	virtual ~ClassCreator();

	/// This is how to generate code with ClassCreator.
	virtual void GenerateCode()  const throw (std::string);

private:
	#ifndef WIN32
		// The preferred approach, for fully ISO-compliant C++ compilers:
		template<typename T> void GenerateFile() const;
	#else
		// Work around for yet another Microsoft compiler bug.
		// Microsoft bug report: Q240871: Explicitly Specified Template
		// Functions Not Overloaded Correctly
		// Reference: http://support.microsoft.com/support/kb/articles/Q240/8/71.ASP
		template<typename T> void GenerateFile(T& generator) const;
	#endif // #ifndef WIN32

// No copying or assignment is supported, at this point:
    ClassCreator(const ClassCreator&);
    ClassCreator& operator=(const ClassCreator&);

	const DigestedCommands& 	mCommands;
};
} // end of code_gen namespace

#endif // ifndef ATD_CODE_GEN_CLASSCREATOR_H
