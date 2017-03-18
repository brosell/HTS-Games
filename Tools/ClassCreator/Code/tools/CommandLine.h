/* ****************************************************************************
 *
 *  CommandLine.h
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
 *  File Contents: Interface and documentation of the CommandLine class.
 *
 * %version: 2.38 %
 * %date_modified: Fri Aug 10 14:00:02 2001 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */
#ifndef ATD_TOOLS_COMMANDLINE_H
#define ATD_TOOLS_COMMANDLINE_H

#include <string>
#include <map>
#include <sstream>

namespace tools
{
/**
<pre>
  Purpose:  This class encapsulates the arguments that are passed to
			a command-line-based program.  By defining a few constraints
			for the program arguments, it is possible to handle such
			arguments in a very generic way, and thus achieve some
			code re-use: CommandLine is meant to be a highly re-usable
			class.

  USE:		A CommandLine object is created by feeding the classic
			argc and argv arguments (supplied by ANSI-standard main() )
			directly to the CommandLine constructor.

			To retrieve the values, use the GetByName() method, and
			specify the "name" of the argument.  This method throws
			a descriptive string as an exception if the argument does
			not exist, or if the argument has no value.  Therefore,
			the Exists() method is supplied, to allow you to check
			for the existence only.  In example 1, the Exists()
			method is the only way to know that the "g" argument exists:

			Example 1: some_program -g


  CONSTRAINTS:  Here are the rules that program arguments must follow:

			1. Each argument must have a "name".  The name is preceded
			by a dash (-).  Because names are allowed to be any length,
			multiple options may NOT be combined ("someprogram -dr" is
			very different from "someprogram -d -r").

			  Example 2:  myprogram -r 50 -confirm yes

			In the above example, the first program argument (ignoring
			the program name) is named "r", and is preceded by a dash.
			The value of the first argument is "50". Note that all values
			are strings; it is the client code's responsibility to
			call atoi or its equivalent, if the numeric value is
			desired.

			2. There is only one value allowed per argument.

			3. Here are some valid examples:

				Example 3: myprogram -g -h 3 -k hello -m "hi there"
				Example 4: yetanotherprogram -quit when_done
				Example 5: myprogram -me "John F. Hubbard" -you someone_else -how_many 12
				Example 6: myprogram -settings_file settings.ini
				Example 7: myprogram -settings_file settings.ini -time now_and_then
				Example 8: myprogram -settings_file settings.ini -time now_and_then -lots of_things
</pre>
 */
    class CommandLine
    {
    public:
        typedef std::map<std::string, std::string> ARGMAPTYPE;

/** A CommandLine object is created by feeding the classic argc and argv
 * arguments (supplied by ANSI-standard main() ) directly to the CommandLine
 * constructor.  If you include a -settings_file <filename> pair of arguments,
 * then <filename> will be opened and read for further command line arguments.
 */
		CommandLine(int argc, char* argv[]) throw (std::string);

/** Command line arguments may also be supplied in a file. You can distribute
 *  the arguments any way you like: zero or more arguments may exist in the
 *  settings file, and zero or more arguments may exist on the command line.
 */
		CommandLine(int argc, char* argv[], const std::string& strFileName)
													    throw (std::string);
/** Command line arguments may also be supplied exclusively from a file.
 */
		CommandLine(const std::string& strFileName) throw (std::string);

        virtual ~CommandLine();

		/// Provides lookup of a command-line argument's value, given its name.
		std::string GetByName( const std::string& strArgName ) const
							   throw (std::string);
		/// Because GetByName() does not check for existence, Exists() does.
		inline bool Exists( const std::string& strArgName ) const;

		/// Returns a count of the command-line parameters, ignoring parameter values.
		inline int Count() const;

		/// This is a formatted string, suitable for display to the end user.
		virtual std::string Usage();

		/// This lists all of the command line arguments that were found.
        void DumpDiagnostics() const;

		/// This is a convenient method when reporting errors.
		inline std::string GetProgramName() const;

    private:
        inline bool 		IsParamName(const std::string& strValue) const;
		inline std::string 	GetParamName(const std::string& strWord) const;

		void 		ParseCommandLine(int argc, char* argv[])  throw (std::string);
		void 		ParseSettings(const std::string& strInput) throw (std::string);
		std::string LoadSettingsFile(const std::string& strFileName) throw (std::string);
		void		TranslateQuotes(std::istringstream& ist, std::string& strWord);

		int     		mnParameterCount;
        ARGMAPTYPE  	mArgMap;
		std::string		mstrProgramName;
        // No copying or assignment is supported, at this point:
        CommandLine(const CommandLine&);
        CommandLine& operator=(const CommandLine&);
    };
} //end of tools namespace
#include "CommandLine.icc"
#endif // #ifndef ATD_TOOLS_COMMANDLINE_H
