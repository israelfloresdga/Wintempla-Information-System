#include "stdafx.h"  //_____________________________________________ ItemPage.cpp
#include "ItemPage.h"

void ItemPage::Window_Open(Web::HttpConnector& h)
{
	//________________________________________________________ ddBrand
	ddBrand.Items.Add(L"Item 0", L"10", false);
	ddBrand.Items.Add(L"Item 1", L"20", true);
	//________________________________________________________ ddCategory
	ddCategory.Items.Add(L"Item 0", L"10", false);
	ddCategory.Items.Add(L"Item 1", L"20", true);
}



void ItemPage::btOk_Click(Web::HttpConnector& h)
{
}

