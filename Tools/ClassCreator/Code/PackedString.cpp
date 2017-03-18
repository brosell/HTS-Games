/* ****************************************************************************
 *
 *  PackedString.cpp
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
 *  File Contents: Implementation of the PackedString class.
 *  Please see PackedString.h for full documentation of this class.
 *
 * %version: 2.28 %
 * %date_modified: Fri Nov 03 14:33:52 2000 %
 * %created_by: jhubbard %
 *
 *************************************************************************** */
#ifdef WIN32
#pragma warning (disable : 4786) // disable MSVC's useless template length warning
#endif // WIN32

#include <string>
#include <iostream>
#include "PackedString.h"

namespace tools
{

PackedString::PackedString(const std::string& strPackedString, char chDelimiter)
	: 	mstrPackedString 	(strPackedString),
		mchDelimiter		(chDelimiter)
{
	UnPack();
}

PackedString::~PackedString()
{
}



void
PackedString::UnPack()
{
	mTheList.clear();
	int nLen = mstrPackedString.length();

	for (int right = 0, left = 0; right <= nLen; ++right)
	{
		if (right == nLen || mstrPackedString[right] == mchDelimiter)
		{
			mTheList.push_back(mstrPackedString.substr(left, right - left));
			left = right + 1;
		}
	}
}

void
PackedString::DumpDiagnostics() const
{
	using std::cout;
	using std::endl;

    cout << endl << "PackedString Diagnostics dump" << endl << endl;

	cout << "Contents of the string: " << mstrPackedString << endl;
	cout << "Contents of the list (" << Count() << " elements):"
		 << endl << endl;

	int nElement = 0;
	for (std::list<std::string>::const_iterator it = mTheList.begin();
		 it != mTheList.end();
		 ++it, ++nElement)
	{
		cout << "Element # " << nElement << ": " << *it << endl;
	}
	if (mTheList.begin() == mTheList.end())
	{
		cout << "[empty list]";
	}
	cout << endl << endl;
}
} // end of the tools namespace
