#include "stdafx.h"  //_____________________________________________ Index.cpp
#include "Index.h"

void Index::Window_Open(Web::HttpConnector& h)
{

	//________________________________________________________ ddCategory
	ddCategory.Items.Add(L"Item 0", L"10", false);
	ddCategory.Items.Add(L"Item 1", L"20", true);
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
	//______________________________________________Column Setup
	lvItem.Cols.Add(LVCFMT_LEFT,20,L"Item name");
	lvItem.Cols.Add(LVCFMT_LEFT,20,L"Model");
	lvItem.Cols.Add(LVCFMT_LEFT,20,L"Brand");
	lvItem.Cols.Add(LVCFMT_LEFT,20,L"Category");
	//______________________________________________ddCategory: Fill the drop down list
	if(h.FirstTime==true)
	{
		Sql::SqlConnection conn;
		try
		{
			//conn.OpenSession(DSN,USERNAME,PASSWORD);
			conn.OpenSession(NULL, CONNECTION_STRING);
			conn.ExecuteSelect(L"SELECT category_id, descr FROM category", 100,ddCategory);
		}
		catch(Sql::SqlException ex)
		{
			this->MessageBoxW(e.GetDescription(),L"ERROR", MB_OK|MB_ICONERROR);
			return;
		}
		//_______________________________________________________Select by default the first category
		ddCategory.SelectedIndex= 0;
		updateView();
}

