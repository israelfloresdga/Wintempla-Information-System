#include "stdafx.h"  //________________________________________ Sharing.cpp
#include "Sharing.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	Sharing app;
	return app.BeginDialog(IDI_SHARING, hInstance);
}

void Sharing::Window_Open(Win::Event& e)
{
	//________________________________________________________ tabMain
	tabMain.Items.Add(0, L"Category");
	tabMain.Items.Add(1, L"Brand");
	//________________________________________________________ lvCategory
	lvCategory.Cols.Add(0, LVCFMT_LEFT, 100, L"Day");
	lvCategory.Cols.Add(1, LVCFMT_RIGHT, 200, L"Activity");
	lvCategory.Items.Add(0, L"Monday");
	lvCategory.Items[0][1].Text = L"Math Class";
	//________________________________________________________ lvBrand
	lvBrand.Cols.Add(0, LVCFMT_LEFT, 100, L"Day");
	lvBrand.Cols.Add(1, LVCFMT_RIGHT, 200, L"Activity");
	lvBrand.Items.Add(0, L"Monday");
	lvBrand.Items[0][1].Text = L"Math Class";
}

