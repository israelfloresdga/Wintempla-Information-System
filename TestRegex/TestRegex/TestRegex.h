#pragma once  //______________________________________ TestRegex.h  
#include "Resource.h"
class TestRegex: public Win::Window
{
public:
	TestRegex()
	{
	}
	~TestRegex()
	{
	}
	const wchar_t * GetClassName(){return L"TESTREGEX";}
protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Label lb1;
	Win::Textbox tbxInput;
	Win::Button btMatch;
protected:
	Win::Gdi::Font fontArial014A;
	void GetWindowInformation(CREATESTRUCT& createStruct)
	{
		createStruct.style = WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"TestRegex";
		lb1.Create(NULL, L"Input", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_WINNORMAL, 20, 17, 51, 28, hWnd, 1000);
		tbxInput.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_MULTILINE | ES_LEFT | ES_WINNORMALCASE, 72, 17, 291, 55, hWnd, 1001);
		btMatch.Create(NULL, L"Match", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 372, 17, 89, 28, hWnd, 1002);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		lb1.Font = fontArial014A;
		tbxInput.Font = fontArial014A;
		btMatch.Font = fontArial014A;
	}
	//_________________________________________________
	void btMatch_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (btMatch.IsEvent(e, BN_CLICKED)) {btMatch_Click(e); return true;}
		return false;
	}
};
