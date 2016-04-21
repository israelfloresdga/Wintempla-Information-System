#include "stdafx.h"  //_____________________________________________ Index.cpp
#include "Index.h"

void Index::Window_Open(Web::HttpConnector& h)
{
	//________________________________________________________ ddCategory
	ddCategory.Items.Add(L"Item 0", L"10", false);
	ddCategory.Items.Add(L"Item 1", L"20", true);
	//________________________________________________________ ddBrand
	ddBrand.Items.Add(L"Item 0", L"10", false);
	ddBrand.Items.Add(L"Item 1", L"20", true);
	//________________________________________________________ lvItem
	lvItem.Cols.Add(LVCFMT_LEFT, 10, L"Day");
	lvItem.Cols.Add(LVCFMT_RIGHT, 20, L"Activity");
	lvItem.Items.Add(L"Monday", L"0");
	lvItem.Items[0].Text[1] = L"Math Class";
	lvItem.Items.Add(L"Tuesday", L"1");
	lvItem.Items[1].Text[1] = L"Science Class";
}



void Index::ddCategory_Change(Web::HttpConnector& h)
{
}

void Index::ddBrand_Change(Web::HttpConnector& h)
{
}

