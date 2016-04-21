#pragma once  //______________________________________ UniMng.h  
#include "Resource.h"
class UniMng: public Win::Dialog
{
public:
	UniMng()
	{
	}
	~UniMng()
	{
	}
	void enableButtons();
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
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(792);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(428);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"UniMng";
		toolbMain.Create(NULL, NULL, WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE | CCS_NOPARENTALIGN | CCS_ADJUSTABLE | CCS_NODIVIDER | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS | TBSTYLE_WRAPABLE, 18, 16, 754, 95, hWnd, 1000);
		lvMain.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_SINGLESEL | LVS_REPORT, 18, 115, 753, 293, hWnd, 1001);
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
	void Cmd_Classroom(Win::Event& e);
	void Cmd_Course(Win::Event& e);
	void Cmd_Department(Win::Event& e);
	void Cmd_Period(Win::Event& e);
	void Cmd_Professor(Win::Event& e);
	void Cmd_Schedule(Win::Event& e);
	void Cmd_Timeblock(Win::Event& e);
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
		if (this->IsEvent(e, IDM_CLASSROOM)) {Cmd_Classroom(e); return true;}
		if (this->IsEvent(e, IDM_COURSE)) {Cmd_Course(e); return true;}
		if (this->IsEvent(e, IDM_DEPARTMENT)) {Cmd_Department(e); return true;}
		if (this->IsEvent(e, IDM_PERIOD)) {Cmd_Period(e); return true;}
		if (this->IsEvent(e, IDM_PROFESSOR)) {Cmd_Professor(e); return true;}
		if (this->IsEvent(e, IDM_SCHEDULE)) {Cmd_Schedule(e); return true;}
		if (this->IsEvent(e, IDM_TIMEBLOCK)) {Cmd_Timeblock(e); return true;}
		if (this->IsEvent(e, IDM_PRINT)) {Cmd_Print(e); return true;}
		if (this->IsEvent(e, IDM_INSERT)) {Cmd_Insert(e); return true;}
		if (this->IsEvent(e, IDM_DELETE)) {Cmd_Delete(e); return true;}
		if (this->IsEvent(e, IDM_EDIT)) {Cmd_Edit(e); return true;}
		if (this->IsEvent(e, IDM_COPY)) {Cmd_Copy(e); return true;}
		if (this->IsEvent(e, IDM_MSEXCEL)) {Cmd_Msexcel(e); return true;}
		return false;
	}
};
