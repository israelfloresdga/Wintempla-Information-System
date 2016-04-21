#include "stdafx.h"  //_____________________________________________ EmployeeVwPage.cpp
#include "EmployeeVwPage.h"

void EmployeeVwPage::Window_Open(Web::HttpConnector& h)
{
	//________________________________________________________ lvEmployee
	lvEmployee.Cols.Add(LVCFMT_LEFT, 32, L"Name");
	lvEmployee.Cols.Add(LVCFMT_LEFT, 16, L"Username");
	lvEmployee.Cols.Add(LVCFMT_LEFT, 24, L"Phone");
	if(h.FirstTime==true) fillListView();
}

void EmployeeVwPage::btDelete_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvEmployee.GetSelectedIndex();
	if(selectedIndex<0) return; //________________________Nothing is selected

	lvEmployee.AjaxUpdate=true;
	Sql::SqlConnection conn;
	wstring sqlcmd;
	const int item_id= Sys::Convert::ToInt(lvEmployee.Items[selectedIndex].Data); //Get the Primary Key
	int rows= 0;

	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(sqlcmd, L"DELETE FROM employee WHERE employee_id=%d", item_id);
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

void EmployeeVwPage::btInsert_Click(Web::HttpConnector& h)
{
	hdEmployeeID.Data= L"-1";
	h.NavigateTo(L"EmployeePage");
	fillListView();
}

void EmployeeVwPage::btEdit_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvEmployee.GetSelectedIndex();
	if(selectedIndex<0) 
	{
		fillListView();
		return;
	}
	const int employee_id= Sys::Convert::ToInt(lvEmployee.SelectedData);
	if(employee_id<0) return;
	hdEmployeeID.Data= lvEmployee.SelectedData;
	h.NavigateTo(L"EmployeePage");
	fillListView();
}

void EmployeeVwPage::btHome_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"Index");
}


void EmployeeVwPage::fillListView()
{
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		lvEmployee.Items.DeleteAll();
		conn.ExecuteSelect(L"SELECT employee_id, name, username, phone FROM vw_Employee", 100, lvEmployee);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}