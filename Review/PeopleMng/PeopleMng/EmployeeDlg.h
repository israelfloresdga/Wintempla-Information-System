#pragma once   //_____________________________________________ EmployeeDlg.h  
#include "resource.h"

class EmployeeDlg: public Win::Dialog
{
public:
	EmployeeDlg()
	{
		employee_id= -1;
	}
	~EmployeeDlg()
	{
	}
	int employee_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Label lbFirst_name;
	Win::Textbox tbxFirst_name;
	Win::Label lbLast_name;
	Win::Textbox tbxLast_name;
	Win::Label lbUsername;
	Win::Textbox tbxUsername;
	Win::Label lbUser_pass;
	Win::Textbox tbxUser_pass;
	Win::Label lbPhone;
	Win::Textbox tbxUser_pass_retype;
	Win::Label lb6;
	Win::Textbox tbxPhone;
	Win::Button ckIs_admi;
	Win::Button btOK;
	Win::Button btCancel;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(521);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(282);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		lbFirst_name.Create(NULL, L"First name", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 9, 14, 248, 25, hWnd, 1000);
		tbxFirst_name.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 144, 14, 248, 25, hWnd, 1001);
		lbLast_name.Create(NULL, L"Last name", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 9, 51, 248, 25, hWnd, 1002);
		tbxLast_name.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 144, 51, 248, 25, hWnd, 1003);
		lbUsername.Create(NULL, L"Username", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 9, 88, 248, 26, hWnd, 1004);
		tbxUsername.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 144, 88, 248, 26, hWnd, 1005);
		lbUser_pass.Create(NULL, L"Password", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 9, 125, 248, 26, hWnd, 1006);
		tbxUser_pass.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_PASSWORD | ES_LEFT | ES_WINNORMALCASE, 144, 125, 248, 25, hWnd, 1007);
		lbPhone.Create(NULL, L"Phone", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 9, 199, 248, 26, hWnd, 1008);
		tbxUser_pass_retype.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_PASSWORD | ES_LEFT | ES_WINNORMALCASE, 144, 162, 248, 25, hWnd, 1009);
		lb6.Create(NULL, L"Retype password", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 9, 162, 132, 26, hWnd, 1010);
		tbxPhone.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 144, 199, 248, 26, hWnd, 1011);
		ckIs_admi.Create(NULL, L"Administrador", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFT | BS_VCENTER, 144, 236, 248, 26, hWnd, 1012);
		btOK.Create(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 421, 89, 80, 28, hWnd, 1013);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 421, 125, 80, 28, hWnd, 1014);
		this->SetDefaultButton(btOK);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lbFirst_name.Font = fontArial014A;
		tbxFirst_name.Font = fontArial014A;
		lbLast_name.Font = fontArial014A;
		tbxLast_name.Font = fontArial014A;
		lbUsername.Font = fontArial014A;
		tbxUsername.Font = fontArial014A;
		lbUser_pass.Font = fontArial014A;
		tbxUser_pass.Font = fontArial014A;
		lbPhone.Font = fontArial014A;
		tbxUser_pass_retype.Font = fontArial014A;
		lb6.Font = fontArial014A;
		tbxPhone.Font = fontArial014A;
		ckIs_admi.Font = fontArial014A;
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
