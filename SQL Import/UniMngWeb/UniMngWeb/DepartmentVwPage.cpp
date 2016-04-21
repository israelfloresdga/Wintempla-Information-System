#include "stdafx.h"  //_____________________________________________ DepartmentVwPage.cpp
#include "DepartmentVwPage.h"

void DepartmentVwPage::Window_Open(Web::HttpConnector& h)
{
	//________________________________________________________ lvDepartment
	lvDepartment.Cols.Add(LVCFMT_LEFT, 32, L"Department");
	if(h.FirstTime==true) fillListView();
}


void DepartmentVwPage::btInsert_Click(Web::HttpConnector& h)
{
	hdDepartmentID.Data= L"-1";
	h.NavigateTo(L"DepartmentPage");
	fillListView();
}

void DepartmentVwPage::btEdit_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvDepartment.SelectedIndex;
	if(selectedIndex<0) 
	{
		fillListView();
		return;
	}
	const int item_id= Sys::Convert::ToInt(lvDepartment.SelectedData);
	if(item_id<0) return;
	hdDepartmentID.Data= lvDepartment.SelectedData;
	h.NavigateTo(L"DepartmentPage");
	fillListView();
}

void DepartmentVwPage::btDelete_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvDepartment.GetSelectedIndex();
	if(selectedIndex<0) return; //________________________Nothing is selected

	lvDepartment.AjaxUpdate=true;
	Sql::SqlConnection conn;
	wstring sqlcmd;
	const int item_id= Sys::Convert::ToInt(lvDepartment.Items[selectedIndex].Data); //Get the Primary Key
	int rows= 0;

	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(sqlcmd, L"DELETE FROM department WHERE department_id=%d", item_id);
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

void DepartmentVwPage::btHome_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"Index");
}

void DepartmentVwPage::fillListView()
{
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		lvDepartment.Items.DeleteAll();
		conn.ExecuteSelect(L"SELECT department_id, descr FROM vw_Department", 100, lvDepartment);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}
