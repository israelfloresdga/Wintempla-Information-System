#pragma once   //_____________________________________________ ScheduleDlg.h  
#include "resource.h"

class ScheduleDlg: public Win::Dialog
{
public:
	ScheduleDlg()
	{
		schedule_id= -1;
	}
	~ScheduleDlg()
	{
	}
	int schedule_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Label lbProfessor;
	Win::DropDownList ddProfessor;
	Win::Label lbCourse;
	Win::DropDownList ddCourse;
	Win::Label lbPeriod;
	Win::DropDownList ddPeriod;
	Win::Label lbTime_block;
	Win::DropDownList ddTime_block;
	Win::Label lbClassroom;
	Win::DropDownList ddClassroom;
	Win::Button btOK;
	Win::Button btCancel;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(438);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(199);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		lbProfessor.Create(NULL, L"Professor", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 14, 100, 25, hWnd, 1000);
		ddProfessor.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 120, 10, 200, 25, hWnd, 1001);
		lbCourse.Create(NULL, L"Course", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 49, 100, 25, hWnd, 1002);
		ddCourse.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 120, 45, 200, 25, hWnd, 1003);
		lbPeriod.Create(NULL, L"Period", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 84, 100, 25, hWnd, 1004);
		ddPeriod.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 120, 80, 200, 25, hWnd, 1005);
		lbTime_block.Create(NULL, L"Time block", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 119, 100, 25, hWnd, 1006);
		ddTime_block.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 120, 115, 200, 25, hWnd, 1007);
		lbClassroom.Create(NULL, L"Classroom", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 10, 154, 100, 25, hWnd, 1008);
		ddClassroom.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 120, 150, 200, 25, hWnd, 1009);
		btOK.Create(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 338, 10, 80, 28, hWnd, 1010);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 338, 49, 80, 28, hWnd, 1011);
		this->SetDefaultButton(btOK);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lbProfessor.Font = fontArial014A;
		ddProfessor.Font = fontArial014A;
		lbCourse.Font = fontArial014A;
		ddCourse.Font = fontArial014A;
		lbPeriod.Font = fontArial014A;
		ddPeriod.Font = fontArial014A;
		lbTime_block.Font = fontArial014A;
		ddTime_block.Font = fontArial014A;
		lbClassroom.Font = fontArial014A;
		ddClassroom.Font = fontArial014A;
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
