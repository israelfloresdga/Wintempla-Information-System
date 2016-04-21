#include "stdafx.h"  //_____________________________________________ CourseDlg.cpp
#include "CourseDlg.h"

void CourseDlg::Window_Open(Win::Event& e)
{
	this->Text=L"Course";
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		if (course_id < 0) return;
		Sys::Format(cmd, L"SELECT code, descr FROM course WHERE course_id=%d", course_id);
		conn.ExecuteSelect(cmd);
		tbxCode.MaxText = 5;
		conn.BindColumn(1, tbxCode, 128);
		tbxDescr.MaxText = 32;
		conn.BindColumn(2, tbxDescr, 128);
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

void CourseDlg::btOK_Click(Win::Event& e)
{
	//_____________________________________________________________ Validate
	tr1::wregex regextbxCode(L"[A-Z]{3}[0-9]{2}");
	if (tr1::regex_match(tbxCode.Text, regextbxCode) == false)
	{
		tbxCode.ShowBalloonTip(L"Invalid Code", L"Please provide the next format CCC##", TTI_ERROR);
		return;
	}
	tr1::wregex regextbxDescr(L"[A-Za-z]+(\\s[A-Za-z]*)*");
	if (tr1::regex_match(tbxDescr.Text, regextbxDescr) == false)
	{
		tbxDescr.ShowBalloonTip(L"Invalid Descr", L"Please provide one or more characters", TTI_ERROR);
		return;
	}

	Sql::StringBuilder sb(L"course", L"course_id", course_id);
	sb.Bind(L"code", tbxCode);
	sb.Bind(L"descr", tbxDescr);
	Sql::SqlConnection conn;
	int rows = 0;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
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
	this->EndDialog(TRUE);
}

void CourseDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}

