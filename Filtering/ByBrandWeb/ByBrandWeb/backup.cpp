#include "stdafx.h"  //_____________________________________________ Index.cpp
#include "Index.h"

void Index::Window_Open(Web::HttpConnector& h)
{
	//________________________________________________________ ddBrand
	ddBrand.Items.Add(L"Item 0", L"10", false);
	ddBrand.Items.Add(L"Item 1", L"20", true);
}



void Index::ddBrand_Change(Web::HttpConnector& h)
{
}

