#pragma once   //_____________________________________________ LoginDlg.h  
#include "resource.h"

class LoginDlg: public Win::Dialog
{
public:
	LoginDlg()
	{
		tryCount= 0;
	}
	~LoginDlg()
	{
	}
	int tryCount;
public: //private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Label lb1;
	Win::Label lb2;
	Win::Textbox tbxUsername;
	Win::Textbox tbxPassword;
	Win::Button btOk;
	Win::Button btCancel;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(433);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(89);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		lb1.Create(NULL, L"Username", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 9, 10, 93, 25, hWnd, 1000);
		lb2.Create(NULL, L"Password", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 9, 44, 93, 25, hWnd, 1001);
		tbxUsername.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 119, 10, 166, 25, hWnd, 1002);
		tbxPassword.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_PASSWORD | ES_LEFT | ES_WINNORMALCASE, 119, 44, 166, 25, hWnd, 1003);
		btOk.Create(NULL, L"Ok", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 315, 10, 98, 25, hWnd, 1004);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 315, 44, 98, 25, hWnd, 1005);
		this->SetDefaultButton(btOk);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lb1.Font = fontArial014A;
		lb2.Font = fontArial014A;
		tbxUsername.Font = fontArial014A;
		tbxPassword.Font = fontArial014A;
		btOk.Font = fontArial014A;
		btCancel.Font = fontArial014A;
	}
	//_________________________________________________
	void btOk_Click(Win::Event& e);
	void btCancel_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (btOk.IsEvent(e, BN_CLICKED)) {btOk_Click(e); return true;}
		if (btCancel.IsEvent(e, BN_CLICKED)) {btCancel_Click(e); return true;}
		return false;
	}
};
