#include "stdafx.h"  //________________________________________ CategoryDropList.cpp
#include "CategoryDropList.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	CategoryDropList app;
	return app.BeginDialog(IDI_CATEGORYDROPLIST, hInstance);
}

void CategoryDropList::Window_Open(Win::Event& e)
{	
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

	//________________________________________________________ dd1
	dd1.Items.Add(L"Item 0 with value 10", 10);
	dd1.Items.Add(L"Item 1 with value 20", 20);
}

