#pragma once  //______________________________________ AddItem.h  
#include "Resource.h"
#include "ItemDlg.h"

class AddItem: public Win::Dialog
{
public:
	AddItem()
	{
	}
	~AddItem()
	{
	}
	void fillListView();
	void edit();

protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::ListView lvItems;
	Win::Button btInsert;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(818);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(479);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"AddItem";
		lvItems.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_ALIGNLEFT | LVS_REPORT, 6, 8, 699, 451, hWnd, 1000);
		btInsert.Create(NULL, L"Insert", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 710, 8, 88, 28, hWnd, 1001);
		lvItems.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		this->SetDefaultButton(btInsert);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lvItems.Font = fontArial014A;
		btInsert.Font = fontArial014A;
	}
	//_________________________________________________
	void btInsert_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (btInsert.IsEvent(e, BN_CLICKED)) {btInsert_Click(e); return true;}
		return false;
	}
};
