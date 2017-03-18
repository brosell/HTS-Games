// Token.h: interface for the CToken class.
//
//
//	MFC Simple CString Tokenizer (Version 1)
//	
//	Written by Richard Case (case@dcs.kcl.ac.uk)
//  Copyright (c) 1999
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name and all copyright 
// notices remains intact. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
// Expect bugs!
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 
//
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOKEN_H__7CEAEBEE_D15D_11D2_9CA9_444553540000__INCLUDED_)
#define AFX_TOKEN_H__7CEAEBEE_D15D_11D2_9CA9_444553540000__INCLUDED_

#include "StdString.h"

class CToken
{
public:
	virtual CStdString nextToken(); // Returns the next token
	virtual bool hasMoreTokens();				// Do we have any more tokens to retrieve
	void SetToken(CStdString tok) { m_strToken = tok; };
	CToken(CStdString str, CStdString delims);
	virtual ~CToken();

protected:
	CStdString m_strToToken;	// The  original string to tokenize
	CStdString m_strLeft;		// The string we have left after taking tokens out
	CStdString m_strToken;		// What is the value to tokenize on?
	bool	m_bFoundAny;	// Have we found any tokens
	bool	m_bFinalToken;	// There might be one last token?
};

#endif // !defined(AFX_TOKEN_H__7CEAEBEE_D15D_11D2_9CA9_444553540000__INCLUDED_)
