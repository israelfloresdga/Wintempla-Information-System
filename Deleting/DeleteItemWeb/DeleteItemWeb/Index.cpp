#include "stdafx.h"  //_____________________________________________ Index.cpp
#include "Index.h"

void Index::Window_Open(Web::HttpConnector& h)
{
	//________________________________________________________ lvItems: Column Setup
	lvItems.Cols.Add(LVCFMT_LEFT, 24, L"Item name");
	lvItems.Cols.Add(LVCFMT_LEFT, 10, L"Model");
	lvItems.Cols.Add(LVCFMT_LEFT, 10, L"Brand");
	lvItems.Cols.Add(LVCFMT_LEFT, 12, L"Category");
	if(h.FirstTime==true) fillListView();
}
void Index::btDelete_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvItems.GetSelectedIndex();
	if(selectedIndex<0) return; //________________________Nothing is selected

	lvItems.AjaxUpdate=true;
	Sql::SqlConnection conn;
	wstring sqlcmd;
	const int item_id= Sys::Convert::ToInt(lvItems.Items[selectedIndex].Data); //Get the Primary Key
	int rows= 0;

	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(sqlcmd, L"DELETE FROM item WHERE item_id=%d", item_id);
		rows = conn.ExecuteNonQuery(sqlcmd);
		if (rows!=1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of deleted rows", MB_OK | MB_ICONERROR);
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	fillListView();
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
