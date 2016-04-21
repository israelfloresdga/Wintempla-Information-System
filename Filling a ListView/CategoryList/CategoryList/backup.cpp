#include "stdafx.h"  //________________________________________ CategoryList.cpp
#include "CategoryList.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	CategoryList app;
	return app.BeginDialog(IDI_CATEGORYLIST, hInstance);
}

void CategoryList::Window_Open(Win::Event& e)
{
	//________________________________________________________ lv1
	lv1.Cols.Add(0, LVCFMT_LEFT, 100, L"Day");
	lv1.Cols.Add(1, LVCFMT_RIGHT, 200, L"Activity");
	lv1.Items.Add(0, L"Monday");
	lv1.Items[0][1].Text = L"Math Class";
}

