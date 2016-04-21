#include "stdafx.h"  //_____________________________________________ Index.cpp
#include "Index.h"

void Index::Window_Open(Web::HttpConnector& h)
{
	//________________________________________________________ lvItems: Column Setup
	lvItems.Cols.Add(LVCFMT_LEFT, 24, L"Item name");
	lvItems.Cols.Add(LVCFMT_LEFT, 12, L"Model");
	lvItems.Cols.Add(LVCFMT_LEFT, 12, L"Brand");
	lvItems.Cols.Add(LVCFMT_LEFT, 18, L"Category");
	if(h.FirstTime==true) fillListView();
}

void Index::btInsert_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"ItemPage");
}

void Index::fillListView()
{
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		lvItems.Items.DeleteAll();
		conn.ExecuteSelect(L"SELECT item_id, [item descr], model, [brand descr], [category descr] FROM vw_Item", 100, lvItems);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}

