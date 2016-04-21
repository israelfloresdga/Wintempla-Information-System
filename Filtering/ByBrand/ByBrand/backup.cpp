#include "stdafx.h"  //________________________________________ ByBrand.cpp
#include "ByBrand.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	ByBrand app;
	return app.BeginDialog(IDI_BYBRAND, hInstance);
}

void ByBrand::Window_Open(Win::Event& e)
{
	//________________________________________________________ ddCategory
	ddCategory.Items.Add(L"Item 0 with value 10", 10);
	ddCategory.Items.Add(L"Item 1 with value 20", 20);
	//________________________________________________________ lv1
	lv1.Cols.Add(0, LVCFMT_LEFT, 100, L"Day");
	lv1.Cols.Add(1, LVCFMT_RIGHT, 200, L"Activity");
	lv1.Items.Add(0, L"Monday");
	lv1.Items[0][1].Text = L"Math Class";
}

void ByBrand::ddCategory_SelChange(Win::Event& e)
{
}

