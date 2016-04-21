#include "stdafx.h"  //_____________________________________________ TimeBlockPage.cpp
#include "TimeBlockPage.h"

void TimeBlockPage::Window_Open(Web::HttpConnector& h)
{
	this->Title=L"Time block";
	time_block_id = Sys::Convert::ToInt(hdTime_blockID.Data);
	if (time_block_id < 0) return; 
	if (h.FirstTime == false) return;
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(cmd, L"SELECT descr, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday FROM time_block WHERE time_block_id=%d", time_block_id);
		conn.ExecuteSelect(cmd);
		tbxDescr.MaxLength=16;
		conn.BindColumn(1, tbxDescr, 32);
		conn.BindColumn(2, ckMonday);
		conn.BindColumn(3, ckTuesday);
		conn.BindColumn(4, ckWednesday);
		conn.BindColumn(5, ckThursday);
		conn.BindColumn(6, ckFriday);
		conn.BindColumn(7, ckSaturday);
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

void TimeBlockPage::btOK_Click(Web::HttpConnector& h)
{
	//_____________________________________________________________ Validate
	tr1::wregex regextbxDescr(L"((Mon)|(Tue)|(Wed)|(Thu)|(Fri)|(Sat))(\\-((Mon)|(Tue)|(Wed)|(Thu)|(Fri)|(Sat)))*");
	if (tr1::regex_match(tbxDescr.Text, regextbxDescr) == false)
	{
		tbxDescr.ShowBalloonTip(L"Invalid Descr", L"Please provide one or more characters", TTI_ERROR);
		return;
	}

	const int time_block_id = Sys::Convert::ToInt(hdTime_blockID.Data);
	Sql::StringBuilder sb(L"time_block", L"time_block_id", time_block_id);
	sb.Bind(L"descr", tbxDescr);
	sb.Bind(L"Monday", ckMonday);
	sb.Bind(L"Tuesday", ckTuesday);
	sb.Bind(L"Wednesday", ckWednesday);
	sb.Bind(L"Thursday", ckThursday);
	sb.Bind(L"Friday", ckFriday);
	sb.Bind(L"Saturday", ckSaturday);
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
	h.NavigateTo(L"TimeBlockVwPage");
}

void TimeBlockPage::btCancel_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"TimeBlockVwPage");
}

