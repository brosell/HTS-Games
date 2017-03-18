// DShow8.cpp: implementation of the CDShow8 class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include <windows.h>
#include "DShow8.h"

IGraphBuilder*	g_pGraphBuilder = NULL;
IMediaControl*	g_pMediaControl = NULL;
IMediaEventEx*	g_pMediaEvent = NULL;
IMediaPosition*	g_pMediaPosition = NULL;

char        g_ExecuteDir[MAX_PATH]; 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDShow8::CDShow8()
{

}

CDShow8::~CDShow8()
{
	Kill();
}

int CDShow8::Init(HWND g_AppWindow)
{
	HRESULT hr;

	Kill();

	CoInitialize(NULL);
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder,
        (void**)&g_pGraphBuilder);
    if (FAILED(hr))
        return -1;
	g_pGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&g_pMediaControl);
	g_pGraphBuilder->QueryInterface(IID_IMediaEvent, (void**)&g_pMediaEvent);
	g_pGraphBuilder->QueryInterface(IID_IMediaPosition, (void**)&g_pMediaPosition);

	g_pMediaEvent->SetNotifyWindow((OAHWND)g_AppWindow, WM_GRAPHEVENT, 0);
	g_pMediaEvent->SetNotifyFlags(0);	// turn on notifications

    return 0;
}

void CDShow8::Kill()
{
    HELPER_RELEASE(g_pMediaPosition);
    HELPER_RELEASE(g_pMediaEvent);
    HELPER_RELEASE(g_pMediaControl);
    HELPER_RELEASE(g_pGraphBuilder);
}
int CDShow8::Load(char* filename)
{
	int	    length;		// length of filename
	WCHAR*	wfilename;	// where we store WCHAR version of filename
    HRESULT hr;
    HANDLE  logfile;                  // log file for graphbuilder
    char    logfilename[MAX_PATH];    // full path and name of log file

    // create graphbuilder's log file;  we must give it a full path or
    // else it will create the log file in the directory the media file is
    // located in
    sprintf(logfilename, "%s\\graph.log", g_ExecuteDir);
    logfile = CreateFile(logfilename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, NULL);
    g_pGraphBuilder->SetLogFile((unsigned long)logfile);

    // attempt to build a graph
	length = strlen(filename)+1;
	wfilename = new WCHAR[length];
	MultiByteToWideChar(CP_ACP, 0, filename, -1, wfilename, length);
    hr = g_pGraphBuilder->RenderFile(wfilename, NULL);
    CloseHandle(logfile);
	if (FAILED(hr))
		return -1;
	else
		return 0;
}
void CDShow8::OnGraphEvent()
{
	long EventCode, Param1, Param2;
	while (g_pMediaEvent->GetEvent(&EventCode, &Param1, &Param2, 0) != E_ABORT)
	{
		switch (EventCode)
		{
        case EC_COMPLETE:            
            // here when media is completely done playing
            if (!g_Looping)
                g_pMediaControl->Stop();
            g_pMediaPosition->put_CurrentPosition(0);   // reset to beginning
            break;
		default:
			break;
		}	
		g_pMediaEvent->FreeEventParams(EventCode, Param1, Param2);
	}
}

void CDShow8::Play()
{
	if (g_pMediaControl)
		g_pMediaControl->Run();
}
void CDShow8::Stop()
{
	g_pMediaControl->Stop();
	g_pMediaPosition->put_CurrentPosition(0);   // return to beginning
}