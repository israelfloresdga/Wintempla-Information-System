#pragma once  //______________________________________ BrandManager.h  
#include "Resource.h"
#include "BrandDlg.h"

class BrandManager: public Win::Dialog
{
public:
	BrandManager()
	{
	}
	~BrandManager()
	{
	}
	void insertBrand();
	void editBrand();
	void updateListview();
protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Toolbar toolbMain;
	Win::ListView lvBrand;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(800);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(480);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"BrandManager";
		toolbMain.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | CCS_NORESIZE | CCS_NOPARENTALIGN | CCS_ADJUSTABLE | CCS_NODIVIDER | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS, 8, 8, 254, 44, hWnd, 1000);
		lvBrand.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_SINGLESEL | LVS_REPORT, 8, 56, 772, 404, hWnd, 1001);
		lvBrand.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lvBrand.Font = fontArial014A;
	}
	//_________________________________________________
	void lvBrand_ItemChanged(Win::Event& e);
	void Window_Open(Win::Event& e);
	void Cmd_Insert(Win::Event& e);
	void Cmd_Edit(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (lvBrand.IsEvent(e, LVN_ITEMCHANGED)) {lvBrand_ItemChanged(e); return true;}
		if (this->IsEvent(e, IDM_INSERT)) {Cmd_Insert(e); return true;}
		if (this->IsEvent(e, IDM_EDIT)) {Cmd_Edit(e); return true;}
		return false;
	}
};
