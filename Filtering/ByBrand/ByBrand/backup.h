#pragma once  //______________________________________ ByBrand.h  
#include "Resource.h"
class ByBrand: public Win::Dialog
{
public:
	ByBrand()
	{
	}
	~ByBrand()
	{
	}	
	void updateItems();
protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Label lbCategory;
	Win::DropDownList ddCategory;
	Win::ListView lv1;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(821);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(463);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"ByBrand";
		lbCategory.Create(NULL, L"Category:", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 8, 11, 103, 25, hWnd, 1000);
		ddCategory.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 118, 11, 327, 25, hWnd, 1001);
		lv1.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_REPORT, 7, 52, 794, 391, hWnd, 1002);
		lv1.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lbCategory.Font = fontArial014A;
		ddCategory.Font = fontArial014A;
		lv1.Font = fontArial014A;
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
