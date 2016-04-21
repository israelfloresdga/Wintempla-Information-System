#include "stdafx.h"  //________________________________________ ByBoth.cpp
#include "ByBoth.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	ByBoth app;
	return app.BeginDialog(IDI_BYBOTH, hInstance);
}

void ByBoth::Window_Open(Win::Event& e)
{
	//________________________________________________________ lvItem Colums Setup
	lvItem.Cols.Add(0, LVCFMT_RIGHT, 200, L"Item name");
	lvItem.Cols.Add(1, LVCFMT_RIGHT, 100, L"Model");
	lvItem.Cols.Add(2, LVCFMT_RIGHT, 100, L"Brand");
	lvItem.Cols.Add(3, LVCFMT_RIGHT, 100, L"Category");
	//________________________________________________________ ddCategory
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		conn.ExecuteSelect(L"SELECT category_id, descr FROM category", 100, ddCategory);
		conn.ExecuteSelect(L"SELECT brand_id, descr FROM brand", 100, ddBrand);
	}
	catch (Sql::SqlException ex)
	{
		this->MessageBox(ex.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}

void ByBoth::ddCategory_SelChange(Win::Event& e)
{
	updateItems();
}

void ByBoth::ddBrand_SelChange(Win::Event& e)
{
	updateItems();
}

void ByBoth::updateItems()
{
	if(ddCategory.SelectedIndex<0 | ddBrand.SelectedIndex<0) return;
	const int category_id= ddCategory.SelectedData;
	const int brand_id= ddBrand.SelectedData;
	wstring sqlcmd;
	Sys::Format(sqlcmd, 
		L"SELECT item_id, [item descr], model, [brand descr], [category descr] FROM vw_Item WHERE category_id= %d AND brand_id= %d", 
		category_id, brand_id);
	Sql::SqlConnection conn;
	Win::HourGlassCursor hgc(true);
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD);
		conn.OpenSession(hWnd, CONNECTION_STRING);
		lvItem.SetRedraw(false);//stop redrawing the control when inserting items
		lvItem.Items.DeleteAll();
		conn.ExecuteSelect(sqlcmd, 100, lvItem);
		lvItem.SetRedraw(true);
	}
	catch(Sql::SqlException ex)
	{
		this->MessageBox(ex.GetDescription(), L"ERROR", MB_OK | MB_ICONERROR);
	}
}
