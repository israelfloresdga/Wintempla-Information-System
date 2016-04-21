#include "stdafx.h"  //_____________________________________________ EmployeeDlg.cpp
#include "EmployeeDlg.h"

void EmployeeDlg::Window_Open(Win::Event& e)
{
	this->Text=L"Employee";
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		if (employee_id < 0) return;
		Sys::Format(cmd, L"SELECT last_name, first_name, username, user_pass, user_pass, phone, is_admi FROM employee WHERE employee_id=%d", employee_id);
		conn.ExecuteSelect(cmd);
		tbxLast_name.MaxText = 32;
		conn.BindColumn(1, tbxLast_name, 128);
		tbxFirst_name.MaxText = 32;
		conn.BindColumn(2, tbxFirst_name, 128);
		tbxUsername.MaxText = 32;
		conn.BindColumn(3, tbxUsername, 128);
		tbxUser_pass.MaxText = 32;
		conn.BindColumn(4, tbxUser_pass, 128);
		tbxUser_pass_retype.MaxText = 32;
		conn.BindColumn(5, tbxUser_pass_retype, 128);
		tbxPhone.MaxText = 16;
		conn.BindColumn(6, tbxPhone, 128);
		conn.BindColumn(7, ckIs_admi);
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

void EmployeeDlg::btOK_Click(Win::Event& e)
{
	tr1::wregex regextbxFirst_name(L"[A-ZÁÉÍÓÚÑ][a-záéíóúñ]*(\\s[A-ZÁÉÍÓÚÑ][a-záéíóúñ]*)?");
	if (tr1::regex_match(tbxFirst_name.Text, regextbxFirst_name) == false)
	{
		tbxFirst_name.ShowBalloonTip(L"Invalid First name", L"Please provide one or more characters [A-z] First character in MAYUS. Can be two words", TTI_ERROR);
		return;
	}
	//_____________________________________________________________ Validate
	tr1::wregex regextbxLast_name(L"[A-ZÁÉÍÓÚÑ][a-záéíóúñ]*(\\s[A-ZÁÉÍÓÚÑ][a-záéíóúñ]*)?");
	if (tr1::regex_match(tbxLast_name.Text, regextbxLast_name) == false)
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
	tr1::wregex regextbxUser_pass(L".{6,32}");
	if (tr1::regex_match(tbxUser_pass.Text, regextbxUser_pass) == false)
	{
		tbxUser_pass.ShowBalloonTip(L"Invalid password", L"Please provide six or more characters", TTI_ERROR);
		return;
	}
	if(tbxUser_pass.Text!=tbxUser_pass_retype.Text)
	{
		tbxUser_pass_retype.ShowBalloonTip(L"Invalid password", L"It must be the same than above", TTI_ERROR);
		return;
	}
	tr1::wregex regextbxPhone(L"[0-9]{3}\\-[0-9]{3}\\-[0-9]{4}");
	if (tr1::regex_match(tbxPhone.Text, regextbxPhone) == false)
	{
		tbxPhone.ShowBalloonTip(L"Invalid Phone", L"Please provide the format: ###-###-####", TTI_ERROR);
		return;
	}
	Sql::StringBuilder sb(L"employee", L"employee_id", employee_id);
	sb.Bind(L"first_name", tbxFirst_name);
	sb.Bind(L"last_name", tbxLast_name);
	sb.Bind(L"username", tbxUsername);
	sb.Bind(L"user_pass", tbxUser_pass);
	sb.Bind(L"phone", tbxPhone);
	sb.Bind(L"is_admi", ckIs_admi);
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
	}
	this->EndDialog(TRUE);
}

void EmployeeDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}
