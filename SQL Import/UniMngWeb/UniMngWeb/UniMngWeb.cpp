#include "stdafx.h"  //________________________________________ UniMngWeb.cpp
#include "UniMngWeb.h"
#include "ClassroomVwPage.h"
#include "ClassroomPage.h"
#include "CourseVwPage.h"
#include "CoursePage.h"
#include "DepartmentVwPage.h"
#include "DepartmentPage.h"
#include "PeriodVwPage.h"
#include "PeriodPage.h"
#include "ProfessorVwPage.h"
#include "ProfessorPage.h"
#include "TimeBlockVwPage.h"
#include "TimeBlockPage.h"
#include "ScheduleVwPage.h"
#include "SchedulePage.h"

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
	strcpy_s(pVer->lpszExtensionDesc, HSE_MAX_EXT_DLL_NAME_LEN, "UniMngWeb ISAPI Extension");
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
	else if(wcscmp(windowID, L"ClassroomVwPage") == 0) {ClassroomVwPage page; page.Run(h);}
	else if(wcscmp(windowID, L"ClassroomPage") == 0) {ClassroomPage page; page.Run(h);}
	else if(wcscmp(windowID, L"CourseVwPage") == 0) {CourseVwPage page; page.Run(h);}
	else if(wcscmp(windowID, L"CoursePage") == 0) {CoursePage page; page.Run(h);}
	else if(wcscmp(windowID, L"DepartmentVwPage") == 0) {DepartmentVwPage page; page.Run(h);}
	else if(wcscmp(windowID, L"DepartmentPage") == 0) {DepartmentPage page; page.Run(h);}
	else if(wcscmp(windowID, L"PeriodVwPage") == 0) {PeriodVwPage page; page.Run(h);}
	else if(wcscmp(windowID, L"PeriodPage") == 0) {PeriodPage page; page.Run(h);}
	else if(wcscmp(windowID, L"ProfessorVwPage") == 0) {ProfessorVwPage page; page.Run(h);}
	else if(wcscmp(windowID, L"ProfessorPage") == 0) {ProfessorPage page; page.Run(h);}
	else if(wcscmp(windowID, L"TimeBlockVwPage") == 0) {TimeBlockVwPage page; page.Run(h);}
	else if(wcscmp(windowID, L"TimeBlockPage") == 0) {TimeBlockPage page; page.Run(h);}
	else if(wcscmp(windowID, L"ScheduleVwPage") == 0) {ScheduleVwPage page; page.Run(h);}
	else if(wcscmp(windowID, L"SchedulePage") == 0) {SchedulePage page; page.Run(h);}
}
