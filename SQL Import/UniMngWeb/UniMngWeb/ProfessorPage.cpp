#include "stdafx.h"  //_____________________________________________ ProfessorPage.cpp
#include "ProfessorPage.h"

void ProfessorPage::Window_Open(Web::HttpConnector& h)
{
	this->Title=L"Professor";
	professor_id = Sys::Convert::ToInt(hdProfessorID.Data);
	
	Sql::SqlConnection conn;
	wstring cmd;
	conn.OpenSession(NULL, CONNECTION_STRING);
	conn.ExecuteSelect(L"SELECT department_id, descr FROM department", 100, ddDepartment);

	if (professor_id < 0) return; 
	if (h.FirstTime == false) return;

	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		conn.ExecuteSelect(L"SELECT department_id, descr FROM department", 100, ddDepartment);
		Sys::Format(cmd, L"SELECT last_name, first_name, department_id, username, user_pass, user_pass FROM professor WHERE professor_id=%d", professor_id);
		conn.ExecuteSelect(cmd);
		tbxLast_name.MaxLength=32;
		conn.BindColumn(1, tbxLast_name, 32);
		tbxFirst_name.MaxLength=32;
		conn.BindColumn(2, tbxFirst_name, 32);
		conn.BindColumn(3, ddDepartment, 32);
		tbxUsername.MaxLength=32;
		conn.BindColumn(4, tbxUsername, 32);
		tbxUser_pass.MaxLength=32;
		conn.BindColumn(5, tbxUser_pass, 32);
		tbxUser_pass_retype.MaxLength=32;
		conn.BindColumn(6, tbxUser_pass_retype, 32);
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

void ProfessorPage::btOK_Click(Web::HttpConnector& h)
{
	//_____________________________________________________________ Validate
	tr1::wregex regexName(L"[A-ZÁÉÍÓÚÑ][a-záéíóúñ]*(\\s[A-ZÁÉÍÓÚÑ][a-záéíóúñ]*)?");
	if (tr1::regex_match(tbxFirst_name.Text, regexName) == false)
	{
		tbxFirst_name.ShowBalloonTip(L"Invalid First name", L"Please provide one or more characters [A-z] First character in MAYUS. Can be two words", TTI_ERROR);
		return;
	}
	if (tr1::regex_match(tbxLast_name.Text, regexName) == false)
	{
		tbxLast_name.ShowBalloonTip(L"Invalid Last name", L"Please provide one or more characters [A-z] First character in MAYUS. Can be two words", TTI_ERROR);
		return;
	}
	tr1::wregex regextbxUsername(L".{6,32}");
	if (tr1::regex_match(tbxUsername.Text, regextbxUsername) == false)
	{
		tbxUsername.ShowBalloonTip(L"Invalid Username", L"Please provide six or more characters", TTI_ERROR);
		return;
	}
	if (tr1::regex_match(tbxUser_pass.Text, regextbxUsername) == false)
	{
		tbxUser_pass.ShowBalloonTip(L"Invalid User pass", L"Please provide six or more characters", TTI_ERROR);
		return;
	}
	if(tbxUser_pass.Text!=tbxUser_pass_retype.Text)
	{
		tbxUser_pass_retype.ShowBalloonTip(L"Invalid password", L"It must be the same than above", TTI_ERROR);
		return;
	}

	const int professor_id = Sys::Convert::ToInt(hdProfessorID.Data);
	Sql::StringBuilder sb(L"professor", L"professor_id", professor_id);
	sb.Bind(L"last_name", tbxLast_name);
	sb.Bind(L"first_name", tbxFirst_name);
	sb.Bind(L"department_id", ddDepartment);
	sb.Bind(L"username", tbxUsername);
	sb.Bind(L"user_pass", tbxUser_pass);
	
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
	h.NavigateTo(L"ProfessorVwPage");
}

void ProfessorPage::btCancel_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"ProfessorVwPage");
}

