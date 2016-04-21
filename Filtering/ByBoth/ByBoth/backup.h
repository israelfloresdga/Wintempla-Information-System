#pragma once  //______________________________________ ByBoth.h  
#include "Resource.h"
class ByBoth: public Win::Dialog
{
public:
	ByBoth()
	{
	}
	~ByBoth()
	{
	}
	updateItems();
protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Label lbCategory;
	Win::DropDownList ddCategory;
	Win::Label lbBrand;
	Win::DropDownList ddBrand;
	Win::ListView lvItems;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(812);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(473);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"ByBoth";
		lbCategory.Create(NULL, L"Category", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 8, 9, 88, 25, hWnd, 1000);
		ddCategory.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 98, 9, 293, 25, hWnd, 1001);
		lbBrand.Create(NULL, L"Brand", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 410, 9, 69, 25, hWnd, 1002);
		ddBrand.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 485, 9, 305, 25, hWnd, 1003);
		lvItems.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_REPORT, 8, 44, 784, 409, hWnd, 1004);
		lvItems.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lbCategory.Font = fontArial014A;
		ddCategory.Font = fontArial014A;
		lbBrand.Font = fontArial014A;
		ddBrand.Font = fontArial014A;
		lvItems.Font = fontArial014A;
	}
	//_________________________________________________
	void ddCategory_SelChange(Win::Event& e);
	void ddBrand_SelChange(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (ddCategory.IsEvent(e, CBN_SELCHANGE)) {ddCategory_SelChange(e); return true;}
		if (ddBrand.IsEvent(e, CBN_SELCHANGE)) {ddBrand_SelChange(e); return true;}
		return false;
	}
};
