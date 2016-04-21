#include "stdafx.h"  //________________________________________ AddItem.cpp
#include "AddItem.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	AddItem app;
	return app.BeginDialog(IDI_ADDITEM, hInstance);
}

void AddItem::Window_Open(Win::Event& e)
{
	//________________________________________________________ lvItems: Column Setup
	lvItems.Cols.Add(0, LVCFMT_LEFT, 200, L"Item name");
	lvItems.Cols.Add(1, LVCFMT_LEFT, 120, L"Model");
	lvItems.Cols.Add(2, LVCFMT_LEFT, 120, L"Brand");
	lvItems.Cols.Add(3, LVCFMT_LEFT, 120, L"Category");

	fillListView();
}

void AddItem::fillListView()
{
	lvItems.SetRedraw(false);
	lvItems.Items.DeleteAll();

	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		conn.ExecuteSelect(L"SELECT item_id, [item descr], model, [brand descr], [category descr] FROM vw_Item", 100, lvItems);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	lvItems.SetRedraw(true);
}

void AddItem::btInsert_Click(Win::Event& e)
{
	ItemDlg dlg;
	dlg.BeginDialog(hWnd);
	fillListView();
}