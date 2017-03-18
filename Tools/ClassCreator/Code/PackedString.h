/* ****************************************************************************
 *
 *  PackedString.h
 *  Created by John F. Hubbard, on Sun Oct 29 2000, 11:40:59 PST
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
 *  File Contents: Interface and documentation of the PackedString class.
 *
 * %version: 2.28 %
 * %date_modified: Thu Nov 02 18:11:08 2000 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */

#ifndef ATC_TOOLS_PACKEDSTRING_H
#define ATC_TOOLS_PACKEDSTRING_H

#include <string>
#include <list>

namespace tools
{

/** Purpose: Convert between packed strings and parsed lists. You can specify
 *  what delimiter to use between strings.
 *
 *  USAGE: This is useful any time data needs to be packed into a single string
 *  at one point, and extracted back into its component strings at another
 *  point.
 */
class PackedString
{
public:
    /// Constructors.
    PackedString(const std::string& strPackedString, char chDelimiter = ' ');
    virtual ~PackedString();

	/// Parse a single std::string into an std::list of strings. Stands alone.
	void UnPack();

	/// Return the number of strings in the list.
	inline int Count() const;

	/// Return the packed string
	inline std::string GetString() const;

	/// Return the parsed list:
	inline std::list<std::string>& GetList();

    /// DumpDiagnostics() dumps the object's state to standard output.
    void DumpDiagnostics() const;

private:
	std::string 			mstrPackedString;
	std::list<std::string>	mTheList;
	char					mchDelimiter;

// No copying or assignment is supported, at this point:
    PackedString(const PackedString&);
    PackedString& operator=(const PackedString&);
};

} // end of the tools namespace
#include "PackedString.icc"

#endif // #ifndef ATC_TOOLS_PACKEDSTRING_H

