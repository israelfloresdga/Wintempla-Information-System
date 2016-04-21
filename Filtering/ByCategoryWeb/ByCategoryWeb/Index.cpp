#include "stdafx.h"  //_____________________________________________ Index.cpp
#include "Index.h"

void Index::Window_Open(Web::HttpConnector& h)
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
			this->MessageBoxW(ex.GetDescription(),L"ERROR", MB_OK|MB_ICONERROR);
			return;
		}
		//_______________________________________________________Select by default the first category
		ddCategory.SelectedIndex= 0;
		updateItems();
	}
}


void Index::ddCategory_Change(Web::HttpConnector& h)
{
	updateItems();
	ddCategory.AjaxUpdate= false;
	lvItem.AjaxUpdate= true;
}

void Index::updateItems()
{
	if(ddCategory.SelectedData.length() <= 0) return;
	const int category_id= Sys::Convert::ToInt(ddCategory.SelectedData);
	wstring sqlcmd;
	Sys::Format(sqlcmd,
		L"SELECT item_id,  [item descr], model, [brand descr], [category descr] FROM vw_Item WHERE category_id= %d", 
		category_id);
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD);
		conn.OpenSession(NULL, CONNECTION_STRING);
		lvItem.AjaxUpdate= false;
		lvItem.Items.DeleteAll();
		conn.ExecuteSelect(cmd, 100, lvItem);
		lvItem.AjaxUpdate= true;
	}
	catch(Sql::SqlException ex)
	{
		this->MessageBox(ex.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}
