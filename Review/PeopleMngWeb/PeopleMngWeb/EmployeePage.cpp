#include "stdafx.h"  //_____________________________________________ EmployeePage.cpp
#include "EmployeePage.h"

void EmployeePage::Window_Open(Web::HttpConnector& h)
{
	this->Title=L"Employee";
	employee_id = Sys::Convert::ToInt(hdEmployeeID.Data);
	if (employee_id < 0) return; 
	if (h.FirstTime == false) return;
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(cmd, L"SELECT last_name, first_name, username, user_pass, user_pass, phone, is_admi FROM employee WHERE employee_id=%d", employee_id);
		conn.ExecuteSelect(cmd);
		tbxLast_name.MaxLength=32;
		conn.BindColumn(1, tbxLast_name, 32);
		tbxFirst_name.MaxLength=32;
		conn.BindColumn(2, tbxFirst_name, 32);
		tbxUsername.MaxLength=32;
		conn.BindColumn(3, tbxUsername, 32);
		tbxUser_pass.MaxLength=32;
		conn.BindColumn(4, tbxUser_pass, 32);
		tbxUser_pass_retype.MaxLength=32;
		conn.BindColumn(5, tbxUser_pass_retype, 32);
		tbxPhone.MaxLength=16;
		conn.BindColumn(6, tbxPhone, 32);
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

void EmployeePage::btOK_Click(Web::HttpConnector& h)
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
	//____________________________________________________End Regex
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
		conn.OpenSession(NULL, CONNECTION_STRING);
		rows = conn.ExecuteNonQuery(sb.GetString());
		if (rows!=1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of affected rows", MB_OK | MB_ICONERROR);
			return;
		}
		h.NavigateTo(L"EmployeeVwPage");
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}

void EmployeePage::btCancel_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"EmployeeVwPage");
}

