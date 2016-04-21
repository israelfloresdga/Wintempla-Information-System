#include "stdafx.h"  //_____________________________________________ ClientDlg.cpp
#include "ClientDlg.h"

void ClientDlg::Window_Open(Win::Event& e)
{
	this->Text=L"Client";
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		if (client_id < 0) return;
		Sys::Format(cmd, L"SELECT last_name, first_name, birthdate, city FROM client WHERE client_id=%d", client_id);
		conn.ExecuteSelect(cmd);
		tbxLast_name.MaxText = 32;
		conn.BindColumn(1, tbxLast_name, 128);
		tbxFirst_name.MaxText = 32;
		conn.BindColumn(2, tbxFirst_name, 128);
		dtboxBirthdate.SetFormat(L"MMM dd, yyyy"); 
		conn.BindColumn(3, dtboxBirthdate);
		tbxCity.MaxText = 32;
		conn.BindColumn(4, tbxCity, 128);
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

void ClientDlg::btOK_Click(Win::Event& e)
{
	tr1::wregex regextbxFirst_name(L"[A-ZÁÉÍÓÚÑ][a-záéíóúñ]*(\\s[A-ZÁÉÍÓÚÑ][a-záéíóúñ]*)?");
	if (tr1::regex_match(tbxFirst_name.Text, regextbxFirst_name) == false)
	{
		tbxFirst_name.ShowBalloonTip(L"Invalid First name", L"Please provide one or more characters [A-z] First character in MAYUS. Two words", TTI_ERROR);
		return;
	}
	//_____________________________________________________________ Validate
	tr1::wregex regextbxLast_name(L"[A-ZÁÉÍÓÚÑ][a-záéíóúñ]*(\\s[A-ZÁÉÍÓÚÑ][a-záéíóúñ]*)?");
	if (tr1::regex_match(tbxLast_name.Text, regextbxLast_name) == false)
	{
		tbxLast_name.ShowBalloonTip(L"Invalid Last name", L"Please provide one or more characters [A-z] First character in MAYUS. Two words", TTI_ERROR);
		return;
	}
	tr1::wregex regextbxCity(L"[A-ZÁÉÍÓÚÑ][a-záéíóúñ]*(\\s[A-ZÁÉÍÓÚÑ][a-záéíóúñ]*)*");
	if (tr1::regex_match(tbxCity.Text, regextbxCity) == false)
	{
		tbxCity.ShowBalloonTip(L"Invalid City", L"Please provide one or more characters [A-z] First character in MAYUS", TTI_ERROR);
		return;
	}
	Sql::StringBuilder sb(L"client", L"client_id", client_id);
	sb.Bind(L"last_name", tbxLast_name);
	sb.Bind(L"first_name", tbxFirst_name);
	sb.BindMicrosoft(L"birthdate", dtboxBirthdate);
	sb.Bind(L"city", tbxCity);
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

void ClientDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}

