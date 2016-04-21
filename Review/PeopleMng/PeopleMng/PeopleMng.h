#pragma once  //______________________________________ PeopleMng.h  
#include "Resource.h"
class PeopleMng: public Win::Dialog
{
public:
	PeopleMng()
	{
	}
	~PeopleMng()
	{
	}
	void fillListViewCols();
	void fillListView();
	void deleteItem();
	void insertItem();
	void editItem();
protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Toolbar toolbMain;
	Win::ListView lvMain;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(607);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(353);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"PeopleMng";
		toolbMain.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | CCS_NORESIZE | CCS_NOPARENTALIGN | CCS_ADJUSTABLE | CCS_NODIVIDER | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS, 12, 16, 575, 46, hWnd, 1000);
		lvMain.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_SINGLESEL | LVS_REPORT, 12, 69, 575, 264, hWnd, 1001);
		lvMain.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lvMain.Font = fontArial014A;
		toolbMain.SetDock(DOCK_BORDER, DOCK_BORDER, DOCK_BORDER, DOCK_BORDER);
		lvMain.SetDock(DOCK_BORDER, DOCK_BORDER, DOCK_BORDER, DOCK_BORDER);
	}
	//_________________________________________________
	void lvMain_ItemChanged(Win::Event& e);
	void lvMain_KeyDown(Win::Event& e);
	void lvMain_DblClk(Win::Event& e);
	void Window_Open(Win::Event& e);
	void Cmd_Client(Win::Event& e);
	void Cmd_Employee(Win::Event& e);
	void Cmd_Print(Win::Event& e);
	void Cmd_Insert(Win::Event& e);
	void Cmd_Delete(Win::Event& e);
	void Cmd_Edit(Win::Event& e);
	void Cmd_Copy(Win::Event& e);
	void Cmd_Msexcel(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (lvMain.IsEvent(e, LVN_ITEMCHANGED)) {lvMain_ItemChanged(e); return true;}
		if (lvMain.IsEvent(e, LVN_KEYDOWN)) {lvMain_KeyDown(e); return true;}
		if (lvMain.IsEvent(e, NM_DBLCLK)) {lvMain_DblClk(e); return true;}
		if (this->IsEvent(e, IDM_CLIENT)) {Cmd_Client(e); return true;}
		if (this->IsEvent(e, IDM_EMPLOYEE)) {Cmd_Employee(e); return true;}
		if (this->IsEvent(e, IDM_PRINT)) {Cmd_Print(e); return true;}
		if (this->IsEvent(e, IDM_INSERT)) {Cmd_Insert(e); return true;}
		if (this->IsEvent(e, IDM_DELETE)) {Cmd_Delete(e); return true;}
		if (this->IsEvent(e, IDM_EDIT)) {Cmd_Edit(e); return true;}
		if (this->IsEvent(e, IDM_COPY)) {Cmd_Copy(e); return true;}
		if (this->IsEvent(e, IDM_MSEXCEL)) {Cmd_Msexcel(e); return true;}
		return false;
	}
};
