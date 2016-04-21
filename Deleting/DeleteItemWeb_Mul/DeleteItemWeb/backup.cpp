#include "stdafx.h"  //_____________________________________________ Index.cpp
#include "Index.h"

void Index::Window_Open(Web::HttpConnector& h)
{
	//________________________________________________________ lvItems: Column Setup
	lvItems.Cols.Add(0, LVCFMT_LEFT, 200, L"Item name");
	lvItems.Cols.Add(1, LVCFMT_LEFT, 120, L"Model");
	lvItems.Cols.Add(2, LVCFMT_LEFT, 120, L"Brand");
	lvItems.Cols.Add(3, LVCFMT_LEFT, 120, L"Category");
}
void Index::btDelete_Click(Web::HttpConnector& h)
{
}

