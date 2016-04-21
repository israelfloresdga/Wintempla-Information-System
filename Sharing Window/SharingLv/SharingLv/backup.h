#pragma once  //______________________________________ SharingLv.h  
#include "Resource.h"
class SharingLv: public Win::Dialog
{
public:
	SharingLv()
	{
	}
	~SharingLv()
	{
	}
protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::DropDownList ddMain;
	Win::ListView lvMain;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(388);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(467);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"SharingLv";
		ddMain.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 11, 10, 357, 25, hWnd, 1000);
		lvMain.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_REPORT, 11, 39, 357, 408, hWnd, 1001);
		lvMain.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		ddMain.Font = fontArial014A;
		lvMain.Font = fontArial014A;
	}
	//_________________________________________________
	void ddMain_SelChange(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (ddMain.IsEvent(e, CBN_SELCHANGE)) {ddMain_SelChange(e); return true;}
		return false;
	}
};
