#pragma once  //______________________________________ ByMulBrand.h  
#include "Resource.h"
class ByMulBrand: public Win::Dialog
{
public:
	ByMulBrand()
	{
	}
	~ByMulBrand()
	{
	}
	void updateItems();
	bool buildSqlQuery(wstring& sqlcmd);
protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::ListView clBrand;
	Win::ListView lvItems;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(830);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(481);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"ByMulBrand";
		clBrand.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_LIST, 9, 9, 155, 452, hWnd, 1000);
		lvItems.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_REPORT, 173, 9, 637, 452, hWnd, 1001);
		clBrand.SetExtStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		lvItems.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		clBrand.Font = fontArial014A;
		lvItems.Font = fontArial014A;
	}
	//_________________________________________________
	void clBrand_ItemChanged(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (clBrand.IsEvent(e, LVN_ITEMCHANGED)) {clBrand_ItemChanged(e); return true;}
		return false;
	}
};
