#include "stdafx.h"  //________________________________________ SharingLv.cpp
#include "SharingLv.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	SharingLv app;
	return app.BeginDialog(IDI_SHARINGLV, hInstance);
}

void SharingLv::Window_Open(Win::Event& e)
{

	//________________________________________________________ ddMain
	ddMain.Items.Add(L"Item 0 with value 10", 10);
	ddMain.Items.Add(L"Item 1 with value 20", 20);
	//________________________________________________________ lvMain
	lvMain.Cols.Add(0, LVCFMT_LEFT, 100, L"Day");
	lvMain.Cols.Add(1, LVCFMT_RIGHT, 200, L"Activity");
	lvMain.Items.Add(0, L"Monday");
	lvMain.Items[0][1].Text = L"Math Class";
}

void SharingLv::ddMain_SelChange(Win::Event& e)
{
}

