#include "stdafx.h"  //________________________________________ ByMulBrand.cpp
#include "ByMulBrand.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	ByMulBrand app;
	return app.BeginDialog(IDI_BYMULBRAND, hInstance);
}

void ByMulBrand::Window_Open(Win::Event& e)
{
	//________________________________________________________ lvItems: Colums Setup
	lvItems.Cols.Add(0, LVCFMT_LEFT, 180, L"Item name");
	lvItems.Cols.Add(1, LVCFMT_LEFT, 110, L"Model");
	lvItems.Cols.Add(2, LVCFMT_LEFT, 110, L"Brand");
	lvItems.Cols.Add(3, LVCFMT_LEFT, 110, L"Category");
	//________________________________________________________ clBrand: Column Setup
	clBrand.Cols.Add(0, LVCFMT_LEFT, 120, L"Brand");
	
	//________________________________________________________clBrand: Fill the check box list
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		conn.ExecuteSelect(L"SELECT category_id, descr FROM category", 100, clBrand);
	}
	catch (Sql::SqlException ex)
	{
		this->MessageBox(ex.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	//__________________________________________________________Select by default the first category
	clBrand.Items[0].Checked= true;
	updateItems();
}

