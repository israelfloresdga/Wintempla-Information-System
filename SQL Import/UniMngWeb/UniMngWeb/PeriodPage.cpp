#include "stdafx.h"  //_____________________________________________ PeriodPage.cpp
#include "PeriodPage.h"

void PeriodPage::Window_Open(Web::HttpConnector& h)
{
	this->Title=L"Period";
	period_id = Sys::Convert::ToInt(hdPeriodID.Data);
	if (period_id < 0) return; 
	if (h.FirstTime == false) return;
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(cmd, L"SELECT descr, begin_date, end_date FROM period WHERE period_id=%d", period_id);
		conn.ExecuteSelect(cmd);
		tbxDescr.MaxLength=16;
		conn.BindColumn(1, tbxDescr, 16);
		conn.BindColumn(2, dtboxBegin_date);
		conn.BindColumn(3, dtboxEnd_date);
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

void PeriodPage::btOK_Click(Web::HttpConnector& h)
{
	//_____________________________________________________________ Validate
	tr1::wregex regextbxDescr(L"((Spring)|(Summer)|(Autumm)|(Winter))\\s20[0-9]{2}");
	if (tr1::regex_match(tbxDescr.Text, regextbxDescr) == false)
	{
		tbxDescr.ShowBalloonTip(L"Invalid Descr", L"Please provide the next format: Season 20XX", TTI_ERROR);
		return;
	}

	const int period_id = Sys::Convert::ToInt(hdPeriodID.Data);
	Sql::StringBuilder sb(L"period", L"period_id", period_id);
	sb.Bind(L"descr", tbxDescr);
	sb.BindMicrosoft(L"begin_date", dtboxBegin_date);
	sb.BindMicrosoft(L"end_date", dtboxEnd_date);
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
	h.NavigateTo(L"PeriodVwPage");
}

void PeriodPage::btCancel_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"PeriodVwPage");
}

