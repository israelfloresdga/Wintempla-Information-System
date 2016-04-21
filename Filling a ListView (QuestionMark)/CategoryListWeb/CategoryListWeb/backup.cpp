#include "stdafx.h"  //_____________________________________________ Index.cpp
#include "Index.h"

void Index::Window_Open(Web::HttpConnector& h)
{
	//________________________________________________________ lvCategory
	lvCategory.Cols.Add(LVCFMT_LEFT, 10, L"Day");
	lvCategory.Cols.Add(LVCFMT_RIGHT, 20, L"Activity");
	lvCategory.Items.Add(L"Monday", L"0");
	lvCategory.Items[0].Text[1] = L"Math Class";
	lvCategory.Items.Add(L"Tuesday", L"1");
	lvCategory.Items[1].Text[1] = L"Science Class";
}



