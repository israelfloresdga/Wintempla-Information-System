#pragma once  //______________________________________ Deleteitem.h  
#include "Resource.h"
//#include "AboutDlg.h"

class Deleteitem: public Win::Dialog
{
public:
	Deleteitem()
	{
	}
	~Deleteitem()
	{
	}
	void deleteItem();
	void fillListView();
protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Toolbar toolbMain;
	Win::ListView lvItems;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(831);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(465);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"Deleteitem";
		toolbMain.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | CCS_NORESIZE | CCS_NOPARENTALIGN | CCS_ADJUSTABLE | CCS_NODIVIDER | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS, 9, 9, 802, 44, hWnd, 1000);
		lvItems.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_REPORT, 9, 61, 801, 384, hWnd, 1001);
		lvItems.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lvItems.Font = fontArial014A;
	}
	//_________________________________________________
	void lvItems_ItemChanged(Win::Event& e);
	void lvItems_KeyDown(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (lvItems.IsEvent(e, LVN_ITEMCHANGED)) {lvItems_ItemChanged(e); return true;}
		if (lvItems.IsEvent(e, LVN_KEYDOWN)) {lvItems_KeyDown(e); return true;}
		return false;
	}
};
