// DShow8.h: interface for the CDShow8 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSHOW8_H__287A0C20_8133_11D5_9DFF_ECF45C627F43__INCLUDED_)
#define AFX_DSHOW8_H__287A0C20_8133_11D5_9DFF_ECF45C627F43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <streams.h>

#define WM_GRAPHEVENT	WM_USER	

#define HELPER_RELEASE(x)   if (x != NULL) \
                            { \
                                x->Release(); \
                                x = NULL; \
                            }
 

class CDShow8  
{
public:
	int Load(char* filename);
	void OnGraphEvent();
	void Play();
	void Stop();
	int Init(HWND g_AppWindow);

	bool        g_Looping; 

	CDShow8();
	virtual ~CDShow8();
private:
	void Kill();         
};

#endif // !defined(AFX_DSHOW8_H__287A0C20_8133_11D5_9DFF_ECF45C627F43__INCLUDED_)
