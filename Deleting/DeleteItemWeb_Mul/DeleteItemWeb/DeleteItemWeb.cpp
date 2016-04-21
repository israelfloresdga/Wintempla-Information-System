#include "stdafx.h"  //________________________________________ DeleteItemWeb.cpp
#include "DeleteItemWeb.h"

//_______________________________________________________ Web Application
Gdiplus::GdiplusStartupInput g_si;
ULONG_PTR g_token;

BOOL WINAPI DllMain( HINSTANCE hInst, DWORD reason, LPVOID lpReserved)
{
	return TRUE;
}

BOOL WINAPI GetExtensionVersion(HSE_VERSION_INFO* pVer)
{
    	pVer->dwExtensionVersion = 
        MAKELONG (HSE_VERSION_MINOR, HSE_VERSION_MAJOR);
	strcpy_s(pVer->lpszExtensionDesc, HSE_MAX_EXT_DLL_NAME_LEN, "DeleteItemWeb ISAPI Extension");
	//__________________________________ Load Gdiplus for Barchart, Piechart, PolarChart and XyChart
	Gdiplus::GdiplusStartup(&g_token, &g_si, NULL);
	//
	return (TRUE);
}

BOOL WINAPI TerminateExtension(DWORD dwFlags)
{
	Gdiplus::GdiplusShutdown(g_token);
	return TRUE;
}

DWORD WINAPI HttpExtensionProc(EXTENSION_CONTROL_BLOCK* pECB)
{
	Web::HttpConnector h(pECB);
	int count = 0;
	while (h.HasRequestBeenHandled() == false)
	{
		SelectWindow(h.GetWindowID(), h);
		count++;
		if (count >= 10) break;  // Prevent Infinite Loop
	}
	return h.SendResponse(pECB);
}

void SelectWindow(const wchar_t* windowID, Web::HttpConnector& h)
{
	if (wcslen(windowID) == 0 || wcscmp(windowID, L"Index") == 0)
	{
		Index page;
		page.Run(h);
	}
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	else if(wcscmp(windowID, L"Index") == 0) {Index page; page.Run(h);}
}
