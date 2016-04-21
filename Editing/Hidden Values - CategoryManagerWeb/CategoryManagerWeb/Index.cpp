#include "stdafx.h"  //_____________________________________________ Index.cpp
#include "Index.h"

void Index::Window_Open(Web::HttpConnector& h)
{
	//________________________________________________________ lvCategory
	lvCategory.Cols.Add(LVCFMT_LEFT, 24, L"Name");
	updateListView();
}


void Index::btInsert_Click(Web::HttpConnector& h)
{
	hdCategoryID.Data= L"-1";
	h.NavigateTo(L"CategoryPage");
}

void Index::btEdit_Click(Web::HttpConnector& h)
{
	const int selecetedIndex= lvCategory.SelectedIndex;
	if(selecetedIndex<0) return;
	const int category_id= Sys::Convert::ToInt(lvCategory.SelectedData);
	if(category_id<0) return;
	hdCategoryID.Data= lvCategory.SelectedData;
	h.NavigateTo(L"CategoryPage");
}

void Index::updateListView()
{
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		conn.ExecuteSelect(L"SELECT category_id, descr FROM category", 100, lvCategory);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}

