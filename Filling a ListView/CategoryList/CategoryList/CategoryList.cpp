#include "stdafx.h"  //________________________________________ CategoryList.cpp
#include "CategoryList.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	CategoryList app;
	return app.BeginDialog(IDI_CATEGORYLIST, hInstance);
}

void CategoryList::Window_Open(Win::Event& e)
{
	//________________________________________________________ lvCategory
	lvCategory.Cols.Add(0, LVCFMT_LEFT, 200, L"Category");
	//Drag and drop SELECT list view template
	Sql::SqlConnection conn;
	try
	{
		conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create my_database;
		//conn.OpenSession(hWnd, CONNECTION_STRING);
		conn.ExecuteSelect(L"SELECT category_id, descr FROM category", 100, lvCategory);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}

