#include "stdafx.h"  //_____________________________________________ PeriodVwPage.cpp
#include "PeriodVwPage.h"

void PeriodVwPage::Window_Open(Web::HttpConnector& h)
{
	//________________________________________________________ lvPeriod
	lvPeriod.Cols.Add(LVCFMT_LEFT, 24, L"Period");
	lvPeriod.Cols.Add(LVCFMT_LEFT, 16, L"Begin date");
	lvPeriod.Cols.Add(LVCFMT_LEFT, 16, L"End date");
	if(h.FirstTime==true) fillListView();
}


void PeriodVwPage::btInsert_Click(Web::HttpConnector& h)
{
	hdPeriodID.Data= L"-1";
	h.NavigateTo(L"PeriodPage");
	fillListView();
}

void PeriodVwPage::btEdit_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvPeriod.SelectedIndex;
	if(selectedIndex<0)
	{
		fillListView();
		return;
	}
	const int item_id= Sys::Convert::ToInt(lvPeriod.SelectedData);
	if(item_id<0) return;
	hdPeriodID.Data= lvPeriod.SelectedData;
	h.NavigateTo(L"PeriodPage");
	fillListView();
}

void PeriodVwPage::btDelete_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvPeriod.GetSelectedIndex();
	if(selectedIndex<0) return; //________________________Nothing is selected

	lvPeriod.AjaxUpdate=true;
	Sql::SqlConnection conn;
	wstring sqlcmd;
	const int item_id= Sys::Convert::ToInt(lvPeriod.Items[selectedIndex].Data); //Get the Primary Key
	int rows= 0;

	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(sqlcmd, L"DELETE FROM period WHERE period_id=%d", item_id);
		rows = conn.ExecuteNonQuery(sqlcmd);
		if (rows!=1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of deleted rows", MB_OK | MB_ICONERROR);
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	fillListView();
}

void PeriodVwPage::btHome_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"Index");
}

void PeriodVwPage::fillListView()
{
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		lvPeriod.Items.DeleteAll();
		conn.ExecuteSelect(L"SELECT period_id, descr, begin_date, end_date FROM vw_Period", 100, lvPeriod);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}

