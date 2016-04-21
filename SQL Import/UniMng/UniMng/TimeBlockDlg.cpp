#include "stdafx.h"  //_____________________________________________ TimeBlockDlg.cpp
#include "TimeBlockDlg.h"

void TimeBlockDlg::Window_Open(Win::Event& e)
{
	this->Text=L"Time block";
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		if (time_block_id < 0) return;
		Sys::Format(cmd, L"SELECT descr, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday FROM time_block WHERE time_block_id=%d", time_block_id);
		conn.ExecuteSelect(cmd);
		tbxDescr.MaxText = 16;
		conn.BindColumn(1, tbxDescr, 128);
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

void TimeBlockDlg::btOK_Click(Win::Event& e)
{
	//_____________________________________________________________ Validate
	tr1::wregex regextbxDescr(L"((Mon)|(Tue)|(Wed)|(Thu)|(Fri)|(Sat))(\\-((Mon)|(Tue)|(Wed)|(Thu)|(Fri)|(Sat)))*");
	if (tr1::regex_match(tbxDescr.Text, regextbxDescr) == false)
	{
		tbxDescr.ShowBalloonTip(L"Invalid Descr", L"Please provide one or more characters", TTI_ERROR);
		return;
	}

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

void TimeBlockDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}

