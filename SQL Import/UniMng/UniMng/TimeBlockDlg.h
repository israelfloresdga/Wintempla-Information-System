#pragma once   //_____________________________________________ TimeBlockDlg.h  
#include "resource.h"

class TimeBlockDlg: public Win::Dialog
{
public:
	TimeBlockDlg()
	{
		time_block_id= -1;
	}
	~TimeBlockDlg()
	{
	}
	int time_block_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Label lbDescr;
	Win::Textbox tbxDescr;
	Win::Button ckMonday;
	Win::Button ckTuesday;
	Win::Button ckWednesday;
	Win::Button ckThursday;
	Win::Button ckFriday;
	Win::Button ckSaturday;
	Win::Button btOK;
	Win::Button btCancel;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(340);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(315);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		lbDescr.Create(NULL, L"Descr", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 14, 100, 25, hWnd, 1000);
		tbxDescr.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 120, 10, 200, 25, hWnd, 1001);
		ckMonday.Create(NULL, L"On Monday", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFT | BS_VCENTER, 120, 45, 200, 26, hWnd, 1002);
		ckTuesday.Create(NULL, L"On Tuesday", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFT | BS_VCENTER, 120, 81, 200, 26, hWnd, 1003);
		ckWednesday.Create(NULL, L"On Wednesday", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFT | BS_VCENTER, 120, 117, 200, 26, hWnd, 1004);
		ckThursday.Create(NULL, L"On Thursday", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFT | BS_VCENTER, 120, 153, 200, 26, hWnd, 1005);
		ckFriday.Create(NULL, L"On Friday", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFT | BS_VCENTER, 120, 189, 200, 26, hWnd, 1006);
		ckSaturday.Create(NULL, L"On Saturday", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFT | BS_VCENTER, 120, 225, 200, 26, hWnd, 1007);
		btOK.Create(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 59, 267, 80, 28, hWnd, 1008);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 176, 267, 80, 28, hWnd, 1009);
		this->SetDefaultButton(btOK);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lbDescr.Font = fontArial014A;
		tbxDescr.Font = fontArial014A;
		ckMonday.Font = fontArial014A;
		ckTuesday.Font = fontArial014A;
		ckWednesday.Font = fontArial014A;
		ckThursday.Font = fontArial014A;
		ckFriday.Font = fontArial014A;
		ckSaturday.Font = fontArial014A;
		btOK.Font = fontArial014A;
		btCancel.Font = fontArial014A;
	}
	//_________________________________________________
	void btOK_Click(Win::Event& e);
	void btCancel_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (btOK.IsEvent(e, BN_CLICKED)) {btOK_Click(e); return true;}
		if (btCancel.IsEvent(e, BN_CLICKED)) {btCancel_Click(e); return true;}
		return false;
	}
};
