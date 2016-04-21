#pragma once  //______________________________________ Sharing.h  
#include "Resource.h"
class Sharing: public Win::Dialog
{
public:
	Sharing()
	{
	}
	~Sharing()
	{
	}
protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Tab tabMain;
	Win::ListView lvCategory;
	Win::ListView lvBrand;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(798);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(493);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"Sharing";
		tabMain.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | TCS_SINGLELINE | TCS_TABS | TCS_RAGGEDRIGHT, 13, 9, 765, 464, hWnd, 1000);
		lvCategory.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_REPORT, 25, 44, 735, 412, hWnd, 1001);
		lvBrand.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_REPORT, 25, 43, 734, 413, hWnd, 1002);
		lvCategory.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		lvBrand.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		tabMain.Font = fontArial014A;
		lvCategory.Font = fontArial014A;
		lvBrand.Font = fontArial014A;
	}
	//_________________________________________________
	void tabMain_SelChange(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (tabMain.IsEvent(e, TCN_SELCHANGE)) {tabMain_SelChange(e); return true;}
		return false;
	}
};
