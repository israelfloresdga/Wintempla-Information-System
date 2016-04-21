#pragma once  //__________________________________________ AboutDlg.h  
#include "resource.h"

class AboutDlg: public Win::Dialog
{
public:
	AboutDlg()
	{
	}
	~AboutDlg()
	{
	}
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Label lbInfo;
	Win::Button btOk;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(318);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(152);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		lbInfo.Create(NULL, L"About this project.", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_WINNORMAL, 55, 35, 243, 49, hWnd, 1000);
		btOk.Create(NULL, L"OK", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 114, 102, 106, 30, hWnd, 1001);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lbInfo.Font = fontArial014A;
		btOk.Font = fontArial014A;
	}
	//_________________________________________________
	void btOk_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (btOk.IsEvent(e, BN_CLICKED)) {btOk_Click(e); return true;}
		return false;
	}
};
