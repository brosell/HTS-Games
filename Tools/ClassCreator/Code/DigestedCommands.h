/* ****************************************************************************
 *
 *  DigestedCommands.h
 *  Created by John F. Hubbard, on Fri Aug 25 2000, 10:25:35 PST
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
 *  File Contents: Interface and documentation of the DigestedCommands class.
 *
 * %version: 2.29 %
 * %date_modified: Wed Nov 15 18:45:58 2000 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */

#ifndef ATD_CODE_GEN_DIGESTEDCOMMANDS_H
#define ATD_CODE_GEN_DIGESTEDCOMMANDS_H

#include "tools/CommandLine.h"

namespace code_gen
{
/** Purpose: DigestedCommands is a specialization of CommandLine. Given a generic
 * CommandLine object (the base part of this class), DigestedCommands extracts
 * and stores information that is specific to--in this case--the ClassCreator
 * system.
 */
class DigestedCommands : public tools::CommandLine
{
public:
    /// Constructor.
    DigestedCommands(int argc, char* argv[])
					 throw (std::string);
    virtual ~DigestedCommands();

	virtual std::string Usage();
	inline std::string GetClassList() 	 const;
	inline std::string GetHeaderFile() 	 const;
	inline std::string GetImplFile()  	 const;
	inline std::string GetInlineFile()   const;
	inline std::string GetMakefile()	 const;
	inline std::string GetUnitTestFile() const;
	inline std::string GetNamespace()	 const;
	inline std::string GetAuthor()	     const;
	inline std::string GetProjectName()	 const;
	inline bool	WillCreateMakefile()	  const;
	inline bool	WillCreateUnitTestFile()  const;
	inline int	GetWriteSentryMode() 	  const;

	inline bool			SccsKeywords()	 	  		const;
	inline bool			ContinuusKeywords()  		const;
	inline bool			CVS_Keywords()     			const;
	inline bool			OpenSourceNotice()   		const;
	inline std::string	GetCopyright() 	  			const;
	inline std::string	GetBaseFilename() 			const;
	inline bool			AssignmentOperator() 		const;
	inline bool			Ctor() 				   		const;
	inline bool			CopyCtor() 					const;
	inline bool			Dtor() 						const;
	inline bool			IccFile()					const;
	inline bool			UseCheckValid()				const;
	inline bool			UseDumpDiagnostics()		const;
	inline bool			UseNamespace()				const;
	inline bool			PublicCopyCtor() 			const;
	inline bool			PublicAssignmentOperator() 	const;

  bool Singleton() const { return mbSingleton; }

private:
// No copying or assignment is supported, at this point:
    DigestedCommands(const DigestedCommands&);
    DigestedCommands& operator=(const DigestedCommands&);

	std::string mstrClassList;
	std::string mstrHeaderFile;
	std::string mstrImplFile;
	std::string mstrInlineFile;
	std::string mstrMakefile;
	std::string mstrUnitTestFile;
	std::string mstrNamespace;
	std::string mstrAuthor;
	std::string mstrProjectName;

	bool	mbMakefile;
	bool	mbUnitTestFile;
	int		mfWriteSentryMode;

	// Added to support multiple classes per file, and control of copy/assignment:
	bool	   	mbSccsKeywords;
	bool	   	mbContinuusKeywords;
	bool	   	mbCVS_Keywords;
	bool	   	mbOpenSourceNotice;
	std::string mstrCopyright;
	std::string mstrBaseFilename;
	bool	   	mbAssignmentOperator;
	bool	   	mbCtor;
	bool	   	mbCopyCtor;
	bool	   	mbDtor;
	bool	   	mbIccFile;
	bool	   	mbCheckValid;
	bool	   	mbDumpDiagnostics;
	bool	   	mbNamespace;
	bool	   	mbPublicCopyCtor;
	bool	   	mbPublicAssignmentOperator;

  bool      mbSingleton;
};

} // end of the code_gen namespace
#include "DigestedCommands.icc"

#endif // #ifndef ATD_CODE_GEN_DIGESTEDCOMMANDS_H

