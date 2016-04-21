#pragma once   //_____________________________________________ ItemDlg.h  
#include "resource.h"

class ItemDlg: public Win::Dialog
{
public:
	ItemDlg()
	{
	}
	~ItemDlg()
	{
	}
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Label lb1;
	Win::Label lb2;
	Win::Label lb3;
	Win::Label lb4;
	Win::Textbox tbxName;
	Win::Textbox tbxModel;
	Win::DropDownList ddBrand;
	Win::DropDownList ddCategory;
	Win::Button btOk;
	Win::Button btCancel;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(383);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(164);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		lb1.Create(NULL, L"Name", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 9, 10, 70, 25, hWnd, 1000);
		lb2.Create(NULL, L"Model", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 9, 47, 70, 25, hWnd, 1001);
		lb3.Create(NULL, L"Brand", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 9, 83, 70, 25, hWnd, 1002);
		lb4.Create(NULL, L"Category", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 9, 119, 70, 25, hWnd, 1003);
		tbxName.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 93, 10, 163, 25, hWnd, 1004);
		tbxModel.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_WINNORMALCASE, 93, 47, 163, 25, hWnd, 1005);
		ddBrand.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 93, 83, 163, 25, hWnd, 1006);
		ddCategory.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 93, 119, 163, 25, hWnd, 1007);
		btOk.Create(NULL, L"Ok", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 278, 37, 85, 28, hWnd, 1008);
		btCancel.Create(NULL, L"Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 278, 82, 85, 28, hWnd, 1009);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lb1.Font = fontArial014A;
		lb2.Font = fontArial014A;
		lb3.Font = fontArial014A;
		lb4.Font = fontArial014A;
		tbxName.Font = fontArial014A;
		tbxModel.Font = fontArial014A;
		ddBrand.Font = fontArial014A;
		ddCategory.Font = fontArial014A;
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
