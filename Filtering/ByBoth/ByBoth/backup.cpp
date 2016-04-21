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
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	//_________________________________________________________Select by default the first category
	ddCategory.SelectedIndex=0;
	updateItems();
	//________________________________________________________ ddBrand
	ddBrand.Items.Add(L"Item 0 with value 10", 10);
	ddBrand.Items.Add(L"Item 1 with value 20", 20);
	//________________________________________________________ lvItems
	lvItems.Cols.Add(0, LVCFMT_LEFT, 100, L"Day");
	lvItems.Cols.Add(1, LVCFMT_RIGHT, 200, L"Activity");
	lvItems.Items.Add(0, L"Monday");
	lvItems.Items[0][1].Text = L"Math Class";
}

void ByBoth::ddCategory_SelChange(Win::Event& e)
{
}

void ByBoth::ddBrand_SelChange(Win::Event& e)
{
}

