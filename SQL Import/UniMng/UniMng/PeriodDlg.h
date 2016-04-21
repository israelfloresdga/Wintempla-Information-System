#pragma once   //_____________________________________________ PeriodDlg.h  
#include "resource.h"

class PeriodDlg: public Win::Dialog
{
public:
	PeriodDlg()
	{
		period_id= -1;
	}
	~PeriodDlg()
	{
	}
	int period_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Label lbDescr;
	Win::Textbox tbxDescr;
	Win::Label lbBegin_date;
	Win::DateTimeBox dtboxBegin_date;
	Win::Label lbEnd_date;
	Win::DateTimeBox dtboxEnd_date;
	Win::Button btOK;
	Win::Button btCancel;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(440);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(129);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		lbDescr.Create(NULL, L"Period", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 14, 100, 25, hWnd, 1000);
		tbxDescr.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 120, 10, 200, 25, hWnd, 1001);
		lbBegin_date.Create(NULL, L"Begin date", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 49, 100, 25, hWnd, 1002);
		dtboxBegin_date.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | DTS_RIGHTALIGN, 120, 45, 200, 25, hWnd, 1003);
		lbEnd_date.Create(NULL, L"End date", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 84, 100, 25, hWnd, 1004);
		dtboxEnd_date.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | DTS_RIGHTALIGN, 120, 80, 200, 25, hWnd, 1005);
		btOK.Create(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 340, 23, 80, 28, hWnd, 1006);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 340, 62, 80, 28, hWnd, 1007);
		this->SetDefaultButton(btOK);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lbDescr.Font = fontArial014A;
		tbxDescr.Font = fontArial014A;
		lbBegin_date.Font = fontArial014A;
		dtboxBegin_date.Font = fontArial014A;
		lbEnd_date.Font = fontArial014A;
		dtboxEnd_date.Font = fontArial014A;
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
