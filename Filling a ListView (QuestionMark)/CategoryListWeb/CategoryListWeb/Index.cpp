#include "stdafx.h"  //_____________________________________________ Index.cpp
#include "Index.h"

void Index::Window_Open(Web::HttpConnector& h)
{
	 //________________________________________________________ lvCategory
     lvCategory.Cols.Add(LVCFMT_LEFT, 30, L"Category");
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
