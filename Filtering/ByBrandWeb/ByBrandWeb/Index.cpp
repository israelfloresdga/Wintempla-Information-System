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
			conn.ExecuteSelect(L"SELECT brand_id, descr FROM brand", 100,ddBrand);
		}
		catch(Sql::SqlException ex)
		{
			this->MessageBoxW(ex.GetDescription(),L"ERROR", MB_OK|MB_ICONERROR);
			return;
		}
		//_______________________________________________________Select by default the first category
		ddBrand.SelectedIndex= 0;
		updateItems();
	}
}


void Index::ddBrand_Change(Web::HttpConnector& h)
{
	updateItems();
	ddBrand.AjaxUpdate= false;
	lvItem.AjaxUpdate= true;
}

void Index::updateItems()
{
	if(ddBrand.SelectedData.length() <= 0) return;
	const int brand_id= Sys::Convert::ToInt(ddBrand.SelectedData);
	wstring sqlcmd;
	Sys::Format(sqlcmd,
		L"SELECT item_id,  [item descr], model, [brand descr], [category descr] FROM vw_Item WHERE brand_id= %d", 
		brand_id);
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD);
		conn.OpenSession(NULL, CONNECTION_STRING);
		lvItem.AjaxUpdate= false;
		lvItem.Items.DeleteAll();
		conn.ExecuteSelect(sqlcmd, 100, lvItem);
		lvItem.AjaxUpdate= true;
	}
	catch(Sql::SqlException ex)
	{
		this->MessageBox(ex.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}