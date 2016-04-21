#pragma once  //______________________________________ CategoryDropList.h  
#include "Resource.h"
class CategoryDropList: public Win::Dialog
{
public:
	CategoryDropList()
	{
	}
	~CategoryDropList()
	{
	}
protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::DropDownList dd1;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(662);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(484);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"CategoryDropList";
		dd1.Create(NULL, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_WINNORMALCASE, 9, 8, 633, 456, hWnd, 1000);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		dd1.Font = fontArial014A;
	}
	//_________________________________________________
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		return false;
	}
};
