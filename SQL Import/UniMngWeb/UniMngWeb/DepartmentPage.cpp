#include "stdafx.h"  //_____________________________________________ DepartmentPage.cpp
#include "DepartmentPage.h"

void DepartmentPage::Window_Open(Web::HttpConnector& h)
{
	this->Title=L"Department";
	department_id = Sys::Convert::ToInt(hdDepartmentID.Data);
	if (department_id < 0) return; 
	if (h.FirstTime == false) return;
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(cmd, L"SELECT descr FROM department WHERE department_id=%d", department_id);
		conn.ExecuteSelect(cmd);
		tbxDescr.MaxLength=32;
		conn.BindColumn(1, tbxDescr, 32);
		if (conn.Fetch() == false)
		{
			this->MessageBox(L"No data was returned", L"Error", MB_OK);
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}

void DepartmentPage::btOK_Click(Web::HttpConnector& h)
{
	//_____________________________________________________________ Validate
	tr1::wregex regextbxDescr(L"[A-Z][a-z]*(\\s[A-Z][a-z]*)*");
	if (tr1::regex_match(tbxDescr.Text, regextbxDescr) == false)
	{
		tbxDescr.ShowBalloonTip(L"Invalid Descr", L"Please provide one or more characters", TTI_ERROR);
		return;
	}

	const int department_id = Sys::Convert::ToInt(hdDepartmentID.Data);
	Sql::StringBuilder sb(L"department", L"department_id", department_id);
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
			this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of affected rows", MB_OK | MB_ICONERROR);
			return;
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
		return;
	}
	h.NavigateTo(L"DepartmentVwPage");
}

void DepartmentPage::btCancel_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"DepartmentVwPage");
}

