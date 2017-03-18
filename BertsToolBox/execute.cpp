
// Execute.cpp: implementation of the CExecute class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "gurueditor.h"
#include "Execute.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DWORD GetApplicationInfo( LPCTSTR lpFullPath )
{
	SHFILEINFO sfi;

	return SHGetFileInfo( lpFullPath, 0, &sfi, sizeof(sfi), SHGFI_EXETYPE );
}

CString ExtractFilePath( LPCTSTR lpFullPath )
{
	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	TCHAR fname[_MAX_FNAME];
	TCHAR ext[_MAX_EXT];

	_tsplitpath( lpFullPath, drive, dir, fname, ext );
	if( dir[_tcslen(dir)-1]==_T('\\') )
		dir[_tcslen(dir)-1] = _T('\0');

	CString lpPath = drive;
	lpPath += dir;
	return lpPath;
}

CExecute::CExecute()
{
	hChildStdinRd = INVALID_HANDLE_VALUE;
	hChildStdinWrDup = INVALID_HANDLE_VALUE;
	hChildStdoutWr = INVALID_HANDLE_VALUE;
	hChildStdoutRdDup = INVALID_HANDLE_VALUE;
	
	hWaitEvent = NULL;

	dwProcessId = DWORD(-1);
	m_pReadThread = NULL;
	exitCode=NULL;
}

CExecute::~CExecute()
{
	CloseAllRedirecthandles();
}

BOOL CExecute::Execute( LPCTSTR szApplication, LPCTSTR szParameter,
			LPCTSTR szWorkDir, int nShow, BOOL bCapture  )
{
	if( hWaitEvent )
		return FALSE;

	DWORD dwAttr;
	if( szApplication!=NULL )
		dwAttr = GetApplicationInfo( szApplication );
	else
		dwAttr = GetApplicationInfo( szParameter );

//	if( !ISVALIDAPP(dwAttr) )
//		return FALSE;

	if( bCapture && ISCONSOLE(dwAttr) )
	{
		if( !PrepareRedirect(szApplication,szParameter,szWorkDir) )
		{
			if( m_pReadThread )
			{
				TerminateThread( m_pReadThread->m_hThread,0 );
				delete m_pReadThread;
				m_pReadThread = NULL;
			}
			CloseAllRedirecthandles();
			TRACE0( _T("PrepareRedirect return FALSE\n") );
			return FALSE;
		}
	}
	else
	{
		if( !CreateChildProcess(dwProcessId, szApplication, 
				szParameter, szWorkDir, nShow ) )
			return FALSE;
	}
	if( !CreateMoniterThread() )
	{
		CloseAllRedirecthandles();
		return FALSE;
	}
	return TRUE;
}

BOOL CExecute::PrepareRedirect(LPCTSTR szApplication, LPCTSTR szParameter,
			LPCTSTR szWorkDir)
{
	SECURITY_ATTRIBUTES saAttr;
	BOOL fSuccess;
	HANDLE hChildStdinWr, hChildStdoutRd;
	HANDLE hSaveStdin, hSaveStdout;  

	// Set the bInheritHandle flag so pipe handles are inherited.
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	// The steps for redirecting child process's STDOUT: 
	//     1. Save current STDOUT, to be restored later. 
	//     2. Create anonymous pipe to be STDOUT for child process. 
	//     3. Set STDOUT of the parent process to be write handle to 
	//	  the pipe, so it is inherited by the child process. 
	//     4. Create a noninheritable duplicate of the read handle and
	//	  close the inheritable read handle.  
	
	// Save the handle to the current STDOUT.  
	hSaveStdout = GetStdHandle(STD_OUTPUT_HANDLE);	
	
	// Create a pipe for the child process's STDOUT.  
	if( !CreatePipe( &hChildStdoutRd, &hChildStdoutWr, &saAttr, 0) )
	{
		TRACE0( _T("Stdout pipe creation failed\n") );
		return FALSE;
	}

	// Set a write handle to the pipe to be STDOUT.  
	if( !SetStdHandle(STD_OUTPUT_HANDLE, hChildStdoutWr) )
	{
		TRACE0( _T("Redirecting STDOUT failed\n") );
		return FALSE;
	}
   
	// Create noninheritable read handle and close the inheritable read handle. 
	fSuccess = DuplicateHandle( GetCurrentProcess(), hChildStdoutRd,
	    GetCurrentProcess(),  &hChildStdoutRdDup , 
		0,  FALSE,
	    DUPLICATE_SAME_ACCESS );
	if( !fSuccess )
	{
		TRACE0( _T("DuplicateHandle failed\n") );
	    return FALSE;
	}
	CloseHandle( hChildStdoutRd );
	
	// The steps for redirecting child process's STDIN: 
	//     1.  Save current STDIN, to be restored later. 
	//     2.  Create anonymous pipe to be STDIN for child process. 
	//     3.  Set STDIN of the parent to be the read handle to the 
	//	   pipe, so it is inherited by the child process. 
	//     4.  Create a noninheritable duplicate of the write handle, 
	//	   and close the inheritable write handle.  

	// Save the handle to the current STDIN. 
	hSaveStdin = GetStdHandle(STD_INPUT_HANDLE);  

	// Create a pipe for the child process's STDIN.  
	if( !CreatePipe(&hChildStdinRd, &hChildStdinWr, &saAttr, 0) )
	{
		TRACE0( _T("Stdin pipe creation failed\n") );
		return FALSE;
	}
	// Set a read handle to the pipe to be STDIN.  
	if( !SetStdHandle(STD_INPUT_HANDLE, hChildStdinRd) ) 
	{
		TRACE0( _T("Redirecting Stdin failed\n") );
		return FALSE;
	}
	// Duplicate the write handle to the pipe so it is not inherited.  
	fSuccess = DuplicateHandle(GetCurrentProcess(), hChildStdinWr, 
		GetCurrentProcess(), &hChildStdinWrDup, 
		0, FALSE,		   // not inherited	  
		DUPLICATE_SAME_ACCESS ); 
	if( !fSuccess ) 
	{
		TRACE0( _T("DuplicateHandle failed\n") );
		return FALSE;
	}
	CloseHandle(hChildStdinWr);  
	
	m_pReadThread = AfxBeginThread( (AFX_THREADPROC)ReadPipeThreadProc,(LPVOID)this );
	if( !m_pReadThread )
	{
		TRACE0( _T("Cannot start read-redirect thread!\n") );
		return FALSE;
	}
	// Now create the child process. 
	if( !CreateConsoleProcess(dwProcessId,szApplication,szParameter, szWorkDir) )
	{
		TRACE0( _T("CreateChildProcess failed\n") );
		return FALSE;
	}
	// After process creation, restore the saved STDIN and STDOUT.	
	if( !SetStdHandle(STD_INPUT_HANDLE, hSaveStdin) )
	{
		TRACE0( _T("Re-redirecting Stdin failed\n") );
		return FALSE;
	}
	if( !SetStdHandle(STD_OUTPUT_HANDLE, hSaveStdout) )
	{
		TRACE0( _T("Re-redirecting Stdout failed\n") );
		return FALSE;
	}
	return TRUE;
}

#define BUFSIZE 2048

UINT CExecute::ReadPipeThreadProc( LPVOID pParam )
{
	DWORD dwRead;
	BYTE chBuf[BUFSIZE]; 
	CExecute* pOwner = (CExecute*)pParam;

	TRACE0( _T("ReadPipe Thread begin run\n") );
	for( ;; )    
	{ 
		if( !ReadFile( pOwner->hChildStdoutRdDup, chBuf, 
			BUFSIZE, &dwRead, NULL) || dwRead == 0) 
			break; 
		chBuf[dwRead] = '\0';
		if( !pOwner->RedirectedStream(chBuf,dwRead) )
			break;
	} 
	pOwner->CloseAllRedirecthandles();
	pOwner->m_pReadThread = NULL;
	return 1;
}


BOOL CExecute::CreateConsoleProcess(DWORD &dwProcessId, LPCTSTR szApplication,
									LPCTSTR szParameter, LPCTSTR szDir )
{
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;  

	// Set up members of STARTUPINFO structure.  
	ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
	siStartInfo.cb = sizeof(STARTUPINFO);  
	
	siStartInfo.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
	siStartInfo.wShowWindow = SW_HIDE;
	siStartInfo.hStdInput = hChildStdinRd;
	siStartInfo.hStdOutput = hChildStdoutWr;
	siStartInfo.hStdError = hChildStdoutWr;

	// Create the child process.  
	BOOL ret = CreateProcess( szApplication,
			(LPTSTR)szParameter,	   // applicatin name
			NULL,	       // process security attributes 
			NULL,	       // primary thread security attributes 
			TRUE,	       // handles are inherited 
			0,	//DETACHED_PROCESS, // creation flags 
			NULL,	       // use parent's environment 
			szDir,		// use parent's current directory 
			&siStartInfo,  // STARTUPINFO pointer 
			&piProcInfo);  // receives PROCESS_INFORMATION 
	if( ret )
		dwProcessId = piProcInfo.dwProcessId;
	else
		dwProcessId = (DWORD)(-1);
	return ret;
}

BOOL CExecute::CreateChildProcess(DWORD &dwProcessId, LPCTSTR szApplication,
		LPCTSTR szParameter, LPCTSTR szDir, int nShow )
{
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;  

	// Set up members of STARTUPINFO structure.  
	ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
	siStartInfo.cb = sizeof(STARTUPINFO);  
	
	siStartInfo.dwFlags = STARTF_USESHOWWINDOW;
	siStartInfo.wShowWindow = nShow;

	// Create the child process.  
	BOOL ret = CreateProcess( szApplication,
			(LPTSTR)szParameter,	   // applicatin name
			NULL,	       // process security attributes 
			NULL,	       // primary thread security attributes 
			TRUE,	       // handles are inherited 
			0,	//DETACHED_PROCESS, // creation flags 
			NULL,	       // use parent's environment 
			szDir,		// use parent's current directory 
			&siStartInfo,  // STARTUPINFO pointer 
			&piProcInfo);  // receives PROCESS_INFORMATION 
	if( ret )
	{
		dwProcessId = piProcInfo.dwProcessId;
		hProcessId = piProcInfo.hProcess;
	}
		
	return ret;
}

BOOL CExecute::CreateMoniterThread()
{
	hWaitEvent = CreateEvent( NULL,FALSE,FALSE,NULL );
	if( !hWaitEvent )
	{
		TRACE0( _T("CreateEvent() failed!\n") );
		return FALSE;
	}
	if( AfxBeginThread( (AFX_THREADPROC)WaitProcessThreadProc,(LPVOID)this ) )
		return TRUE;
	return FALSE;
}

UINT CExecute::WaitProcessThreadProc( LPVOID pParam )
{
	CExecute* pOwner = (CExecute*)pParam;
	if( pOwner->dwProcessId==DWORD(-1) )
		return 1;

	HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, pOwner->dwProcessId );
	if( hProcess )
	{	// maybe the process has been already termianted
		HANDLE handles[2];
		handles[0] = hProcess;
		handles[1] = pOwner->hWaitEvent;

		if( 0==(WaitForMultipleObjects(2,handles,FALSE,INFINITE)-WAIT_OBJECT_0)  )
		{	// the process terminated
			CloseHandle( hProcess );
		}
		else	// user termination
		{
			TerminateProcess( hProcess,0 ); // terminate the process
			CloseHandle( hProcess );
		}
	}
	else
	{
		TRACE0( _T("OpenProcess() failed, process maybe already terminated!\n") );
		Sleep( 2000 ); // maybe I should sleep for a while...
	}
	if( pOwner->m_pReadThread )
	{
		TerminateThread( pOwner->m_pReadThread->m_hThread,0 );
		delete pOwner->m_pReadThread;
		pOwner->m_pReadThread = NULL;
	}
	GetExitCodeProcess((pOwner->hProcessId), &(pOwner->exitCode) );
	pOwner->dwProcessId = DWORD(-1);
	CloseHandle( pOwner->hWaitEvent );
	pOwner->hWaitEvent = NULL;
	pOwner->CloseAllRedirecthandles();
	return 0;
}

void CExecute::CloseAllRedirecthandles()
{
	if( hChildStdinRd!=INVALID_HANDLE_VALUE )
		CloseHandle( hChildStdinRd );
	if( hChildStdinWrDup!=INVALID_HANDLE_VALUE )
		CloseHandle( hChildStdinWrDup );
	if( hChildStdoutWr!=INVALID_HANDLE_VALUE )
		CloseHandle( hChildStdoutWr );
	if( hChildStdoutRdDup!=INVALID_HANDLE_VALUE )
		CloseHandle( hChildStdoutRdDup );

	hChildStdinRd = INVALID_HANDLE_VALUE;
	hChildStdinWrDup = INVALID_HANDLE_VALUE;
	hChildStdoutWr = INVALID_HANDLE_VALUE;
	hChildStdoutRdDup = INVALID_HANDLE_VALUE;
}

BOOL CExecute::StopExec()
{
	return SetEvent( hWaitEvent );
}

BOOL CExecute::RedirectedStream(BYTE *stream, int nLen)
{
	return TRUE;
}
