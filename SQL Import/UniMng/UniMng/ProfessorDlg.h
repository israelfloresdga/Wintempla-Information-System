#pragma once   //_____________________________________________ ProfessorDlg.h  
#include "resource.h"

class ProfessorDlg: public Win::Dialog
{
public:
	ProfessorDlg()
	{
		professor_id= -1;
	}
	~ProfessorDlg()
	{
	}
	int professor_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Label lbFirst_name;
	Win::Textbox tbxFirst_name;
	Win::Label lbLast_name;
	Win::Textbox tbxLast_name;
	Win::Label lbDepartment;
	Win::DropDownList ddDepartment;
	Win::Label lbUsername;
	Win::Textbox tbxUsername;
	Win::Label lbUser_pass;
	Win::Textbox tbxUser_pass;
	Win::Button btOK;
	Win::Button btCancel;
	Win::Label lb6;
	Win::Textbox tbxUser_pass_retype;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(442);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(234);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		lbFirst_name.Create(NULL, L"First name", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 14, 100, 25, hWnd, 1000);
		tbxFirst_name.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 120, 10, 200, 25, hWnd, 1001);
		lbLast_name.Create(NULL, L"Last name", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 49, 100, 25, hWnd, 1002);
		tbxLast_name.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 120, 45, 200, 25, hWnd, 1003);
		lbDepartment.Create(NULL, L"Department", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 84, 100, 25, hWnd, 1004);
		ddDepartment.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 120, 80, 200, 25, hWnd, 1005);
		lbUsername.Create(NULL, L"Username", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 119, 100, 25, hWnd, 1006);
		tbxUsername.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 120, 115, 200, 25, hWnd, 1007);
		lbUser_pass.Create(NULL, L"Password", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 154, 100, 25, hWnd, 1008);
		tbxUser_pass.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_PASSWORD | ES_LEFT | ES_WINNORMALCASE, 120, 150, 200, 25, hWnd, 1009);
		btOK.Create(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 342, 76, 80, 28, hWnd, 1010);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 342, 115, 80, 28, hWnd, 1011);
		lb6.Create(NULL, L"Retype password", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 189, 114, 25, hWnd, 1012);
		tbxUser_pass_retype.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_PASSWORD | ES_LEFT | ES_WINNORMALCASE, 120, 185, 200, 25, hWnd, 1013);
		this->SetDefaultButton(btOK);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lbFirst_name.Font = fontArial014A;
		tbxFirst_name.Font = fontArial014A;
		lbLast_name.Font = fontArial014A;
		tbxLast_name.Font = fontArial014A;
		lbDepartment.Font = fontArial014A;
		ddDepartment.Font = fontArial014A;
		lbUsername.Font = fontArial014A;
		tbxUsername.Font = fontArial014A;
		lbUser_pass.Font = fontArial014A;
		tbxUser_pass.Font = fontArial014A;
		btOK.Font = fontArial014A;
		btCancel.Font = fontArial014A;
		lb6.Font = fontArial014A;
		tbxUser_pass_retype.Font = fontArial014A;
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
