#pragma once  //______________________________________ SharingButton.h  
#include "Resource.h"
class SharingButton: public Win::Dialog
{
public:
	SharingButton()
	{
	}
	~SharingButton()
	{
	}
	void deleteItem();
	void fillListViewCols();
	void fillListView();
protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Toolbar toolbMain;
	Win::ListView lvMain;
	Win::Button radioClient;
	Win::Button radioItems;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(796);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(466);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"SharingButton";
		toolbMain.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | CCS_NORESIZE | CCS_NOPARENTALIGN | CCS_ADJUSTABLE | CCS_NODIVIDER | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS, 7, 8, 106, 45, hWnd, 1000);
		lvMain.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_SINGLESEL | LVS_REPORT, 7, 77, 769, 369, hWnd, 1001);
		radioClient.Create(NULL, L"Client", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTORADIOBUTTON | BS_LEFT | BS_VCENTER, 133, 17, 152, 26, hWnd, 1002);
		radioItems.Create(NULL, L"Items", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTORADIOBUTTON | BS_LEFT | BS_VCENTER, 298, 17, 152, 26, hWnd, 1003);
		lvMain.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lvMain.Font = fontArial014A;
		radioClient.Font = fontArial014A;
		radioItems.Font = fontArial014A;
	}
	//_________________________________________________
	void lvMain_ItemChanged(Win::Event& e);
	void lvMain_KeyDown(Win::Event& e);
	void radioClient_Click(Win::Event& e);
	void radioItems_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	void Cmd_Delete(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (lvMain.IsEvent(e, LVN_ITEMCHANGED)) {lvMain_ItemChanged(e); return true;}
		if (lvMain.IsEvent(e, LVN_KEYDOWN)) {lvMain_KeyDown(e); return true;}
		if (radioClient.IsEvent(e, BN_CLICKED)) {radioClient_Click(e); return true;}
		if (radioItems.IsEvent(e, BN_CLICKED)) {radioItems_Click(e); return true;}
		if (this->IsEvent(e, IDM_DELETE)) {Cmd_Delete(e); return true;}
		return false;
	}
};
