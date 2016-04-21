#include "stdafx.h"  //_____________________________________________ ClientPage.cpp
#include "ClientPage.h"

void ClientPage::Window_Open(Web::HttpConnector& h)
{
	this->Title=L"Client";
	client_id= Sys::Convert::ToInt(hdClientID.Data);
	if (client_id < 0) return; 

	if (h.FirstTime == false) return;
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(cmd, L"SELECT last_name, first_name, birthdate, city FROM client WHERE client_id=%d", client_id);
		conn.ExecuteSelect(cmd);
		tbxLast_name.MaxLength=32;
		conn.BindColumn(1, tbxLast_name, 32);
		tbxFirst_name.MaxLength=32;
		conn.BindColumn(2, tbxFirst_name, 32);
		conn.BindColumn(3, dtboxBirthdate);
		tbxCity.MaxLength=32;
		conn.BindColumn(4, tbxCity, 32);
		if (conn.Fetch() == false)
		{
			this->MessageBox(L"No data was returned", L"Error", MB_OK);
		}
	}
	catch(Sql::SqlException ex)
	{
		this->MessageBox(ex.GetDescription(),L"ERROR", MB_OK|MB_ICONERROR);
	}
}


void ClientPage::btOK_Click(Web::HttpConnector& h)
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
	//____________________________________________________Build cmd
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
	}
	h.NavigateTo(L"ClientVwPage");
}

void ClientPage::btCancel_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"ClientVwPage");
}

