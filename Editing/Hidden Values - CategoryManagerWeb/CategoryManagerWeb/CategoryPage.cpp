#include "stdafx.h"  //_____________________________________________ CategoryPage.cpp
#include "CategoryPage.h"

void CategoryPage::Window_Open(Web::HttpConnector& h)
{
	category_id= Sys::Convert::ToInt(hdCategoryID.Data);
	if(category_id<0) return; //if INSERT, just return

	if(h.FirstTime==true)
	{
		Sql::SqlConnection conn;
		wstring cmd;
		Sys::Format(cmd, L"SELECT descr FROM category WHERE category_id= %d", category_id);

		try
		{
			//conn.OpenSession(DNS,USERNAME,PASSWORD);
			conn.OpenSession(NULL, CONNECTION_STRING);
			conn.ExecuteSelect(cmd);
			conn.BindColumn(1,tbxDescr,64);
			if(conn.Fetch()==false) this->MessageBox(L"No data was returned", L"ERROR", MB_OK|MB_ICONERROR);
		}
		catch(Sql::SqlException ex)
		{
			this->MessageBox(ex.GetDescription(),L"ERROR", MB_OK|MB_ICONERROR);
		}
	}
}


void CategoryPage::btOk_Click(Web::HttpConnector& h)
{
	Sql::StringBuilder sb(L"category", L"category_id", category_id);
	sb.Bind(L"descr", tbxDescr);

	Sql::SqlConnection conn;
	int rows = 0;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		rows = conn.ExecuteNonQuery(sb.GetString());
		if (rows!=1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"Error -number of rows", MB_OK | MB_ICONERROR);
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	h.NavigateTo(L"Index");
}

void CategoryPage::btCancel_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"Index");
}

