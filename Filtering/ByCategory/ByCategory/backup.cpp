#include "stdafx.h"  //________________________________________ ByCategory.cpp
#include "ByCategory.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	ByCategory app;
	return app.BeginDialog(IDI_BYCATEGORY, hInstance);
}

void ByCategory::Window_Open(Win::Event& e)
{
	//________________________________________________________ lvItem
	lvItem.Cols.Add(0, LVCFMT_LEFT, 100, L"Day");
	lvItem.Cols.Add(1, LVCFMT_RIGHT, 200, L"Activity");
	lvItem.Items.Add(0, L"Monday");
	lvItem.Items[0][1].Text = L"Math Class";
	//________________________________________________________ ddCategory
	ddCategory.Items.Add(L"Item 0 with value 10", 10);
	ddCategory.Items.Add(L"Item 1 with value 20", 20);
}

void ByCategory::ddCategory_Closeup(Win::Event& e)
{
}

void ByCategory::ddCategory_SelChange(Win::Event& e)
{
}

