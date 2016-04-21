#include "stdafx.h"  //________________________________________ Sharing.cpp
#include "Sharing.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	Sharing app;
	return app.BeginDialog(IDI_SHARING, hInstance);
}

void Sharing::Window_Open(Win::Event& e)
{
	//________________________________________________________ tabMain
	tabMain.Items.Add(0, L"Category");
	tabMain.Items.Add(1, L"Brand");
	tabMain.SelectedIndex=0;
	lvCategory.Visible= true;
	lvBrand.Visible= false;
	//________________________________________________________ lvCategory
	lvCategory.Cols.Add(0, LVCFMT_RIGHT, 150, L"Category");
	//________________________________________________________ lvBrand
	lvBrand.Cols.Add(0, LVCFMT_RIGHT, 100, L"Brand");
	
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		conn.ExecuteSelect(L"SELECT category_id, descr FROM category", 100, lvCategory);
		conn.ExecuteSelect(L"SELECT brand_id, descr FROM brand", 100, lvBrand);
	}
	catch (Sql::SqlException ex)
	{
		this->MessageBox(ex.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}

void Sharing::tabMain_SelChange(Win::Event& e)
{
	switch (tabMain.SelectedIndex)
	{
	case 0:
		lvCategory.Visible= true;
		lvBrand.Visible= false;
		break;

	case 1:
		lvCategory.Visible= false;
		lvBrand.Visible= true;
		break;

	default:
		break;
	}
}

