#include "stdafx.h"  //_____________________________________________ ProfessorDlg.cpp
#include "ProfessorDlg.h"

void ProfessorDlg::Window_Open(Win::Event& e)
{
	this->Text=L"Professor";
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		conn.ExecuteSelect(L"SELECT department_id, descr FROM department", 100, ddDepartment);
		if (professor_id < 0) return;
		Sys::Format(cmd, L"SELECT last_name, first_name, department_id, username, user_pass, user_pass FROM professor WHERE professor_id=%d", professor_id);
		conn.ExecuteSelect(cmd);
		tbxFirst_name.MaxText = 32;
		conn.BindColumn(1, tbxLast_name, 128);
		tbxLast_name.MaxText = 32;
		conn.BindColumn(2, tbxFirst_name, 128);
		conn.BindColumn(3, ddDepartment);
		tbxUsername.MaxText = 32;
		conn.BindColumn(4, tbxUsername, 128);
		tbxUser_pass.MaxText = 32;
		conn.BindColumn(5, tbxUser_pass, 128);
		tbxUser_pass_retype.MaxText= 32;
		conn.BindColumn(6, tbxUser_pass_retype, 128);
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

void ProfessorDlg::btOK_Click(Win::Event& e)
{
	//_____________________________________________________________ Validate
	tr1::wregex regexName(L"[A-Z¡…Õ”⁄—][a-z·ÈÌÛ˙Ò]*(\\s[A-Z¡…Õ”⁄—][a-z·ÈÌÛ˙Ò]*)?");
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
	if(ddDepartment.SelectedIndex<0)
	{
		lbDepartment.MessageBox(L"Please provide a department", L"Invalid", TTI_ERROR);
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

void ProfessorDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}

