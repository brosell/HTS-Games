
#ifndef _NDIRIT_H_
#define _NDIRIT_H_

#include "enumeration.hpp"
#include <windows.h>

class CDirEnumeration: public CEnumeration<CStdString>
{
public:
	CDirEnumeration(CStdString startDir, CStdString spec="*.*")
		:startDir(startDir), spec(spec), more(true), searchHandle(INVALID_HANDLE_VALUE), inited(false)
	{
		//init();
	}

	~CDirEnumeration()
	{
		if (searchHandle!=INVALID_HANDLE_VALUE)
		{
			FindClose(searchHandle);
		}
	}


	bool hasMoreElements() { if (!inited) init(); return more; };
	
	CStdString nextElement()
	{
		ASSERT(more);
		CStdString next(findData.cFileName);
		more=prepareNext();
		return next;
	}

protected:
	virtual bool filter(LPWIN32_FIND_DATA fd)
	{
		ASSERT(fd);
		return true;
	}

	virtual bool prepareNext()
	{
		ASSERT(searchHandle!=INVALID_HANDLE_VALUE);
		int good=0;
		good=FindNextFile(searchHandle, &findData);
		
		while (good && !filter(&findData))
		{
			good=FindNextFile(searchHandle, &findData);
		}
		return (good!=0);
	}
	
private:
	void init()
	{
		inited=true;
		more=false;
		CStdString fullSpec;
		fullSpec.Format("%s\\%s", (LPCTSTR)startDir, (LPCTSTR)spec);
		
		searchHandle=FindFirstFile(fullSpec, &findData);
		if ( (more=(searchHandle!=INVALID_HANDLE_VALUE)) )
		{
			if (!filter(&findData))
			{
				more = prepareNext();
			}
		}
		
	}

	CStdString startDir;
	CStdString spec;

	WIN32_FIND_DATA findData;
	HANDLE searchHandle;
	bool more;
	bool inited;
};


class CFolderEnumeration:public CDirEnumeration
{
public:
	CFolderEnumeration(CStdString startDir)
		:CDirEnumeration(startDir, "*.*")
	{
	}

protected:
	virtual bool filter(LPWIN32_FIND_DATA fd)
	{
		ASSERT(fd);
		CStdString n(fd->cFileName);
		return (n!="." && n!=".." && (fd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) );
	}
};

#endif
