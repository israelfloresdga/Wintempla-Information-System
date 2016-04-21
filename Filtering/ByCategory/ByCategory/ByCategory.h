#pragma once  //______________________________________ ByCategory.h  
#include "Resource.h"
//#include "AboutDlg.h"
class ByCategory: public Win::Dialog
{
public:
	ByCategory()
	{
	}
	~ByCategory()
	{
	}
	void updateItems();
protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::ListView lvItem;
	Win::DropDownList ddCategory;
	Win::Label lb1;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(802);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(268);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"ByCategory";
		lvItem.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_REPORT, 19, 51, 763, 197, hWnd, 1000);
		ddCategory.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 101, 13, 681, 25, hWnd, 1001);
		lb1.Create(NULL, L"Category:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 16, 13, 76, 25, hWnd, 1002);
		lvItem.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lvItem.Font = fontArial014A;
		ddCategory.Font = fontArial014A;
		lb1.Font = fontArial014A;
	}
	//_________________________________________________
	void ddCategory_SelChange(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (ddCategory.IsEvent(e, CBN_SELCHANGE)) {ddCategory_SelChange(e); return true;}
		return false;
	}
};
