#include "stdafx.h"  //_____________________________________________ ItemDlg.cpp
#include "ItemDlg.h"

void ItemDlg::Window_Open(Win::Event& e)
{
	//________________________________________________________ ddBrand
	ddBrand.Items.Add(L"Item 0 with value 10", 10);
	ddBrand.Items.Add(L"Item 1 with value 20", 20);
	//________________________________________________________ ddCategory
	ddCategory.Items.Add(L"Item 0 with value 10", 10);
	ddCategory.Items.Add(L"Item 1 with value 20", 20);
}



void ItemDlg::btOk_Click(Win::Event& e)
{
}

void ItemDlg::btCancel_Click(Win::Event& e)
{
}

