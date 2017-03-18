// Execute.h: interface for the CExecute class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXECUTE_H__99CC6A13_E975_11D2_9B28_004005649FB5__INCLUDED_)
#define AFX_EXECUTE_H__99CC6A13_E975_11D2_9B28_004005649FB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CExecute  
{
private:
	HANDLE hChildStdinRd, hChildStdinWrDup, 
		hChildStdoutWr, hChildStdoutRdDup;
	CWinThread*	m_pReadThread;
	DWORD dwProcessId;

public:
	// constructors
	CExecute();
	virtual ~CExecute();
	DWORD exitCode;
	HANDLE hWaitEvent;
	HANDLE hProcessId;

	// operations
public:
	virtual BOOL RedirectedStream( BYTE* stream, int nLen );
	BOOL Execute( LPCTSTR szApplication, LPCTSTR szParameter=NULL,
			LPCTSTR szWorkDir=NULL, int nShow=SW_SHOW, BOOL bCapture=FALSE	);
	BOOL StopExec();
protected:
	void CloseAllRedirecthandles();
	BOOL CreateMoniterThread();
	BOOL CreateConsoleProcess(DWORD &dwProcessId, LPCTSTR szApplication, LPCTSTR szParameter, LPCTSTR
szDir );
	BOOL CreateChildProcess(DWORD &dwProcessId, LPCTSTR szApplication, LPCTSTR szParameter, LPCTSTR
szDir, int nShow );
	BOOL PrepareRedirect(LPCTSTR szApplication, LPCTSTR szParameter, LPCTSTR szWorkDir);
	static UINT ReadPipeThreadProc( LPVOID pParam );
	static UINT WaitProcessThreadProc( LPVOID pParam );
};

#define ISCONSOLE( attr ) ( (LOWORD(attr)=='ZM' || LOWORD(attr)=='EP') && HIWORD(attr)==0 )
#define ISVALIDAPP( attr ) ( attr!=0 )
#define ISWINAPP( attr ) ( (LOWORD(attr)=='EN' || LOWORD(attr)=='EP') && HIWORD(attr)!=0 )

DWORD GetApplicationInfo( LPCTSTR lpFullPath );
CString ExtractFilePath( LPCTSTR lpFullPath );

#endif // !defined(AFX_EXECUTE_H__99CC6A13_E975_11D2_9B28_004005649FB5__INCLUDED_)

