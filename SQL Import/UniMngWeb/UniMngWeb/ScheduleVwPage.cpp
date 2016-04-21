#include "stdafx.h"  //_____________________________________________ ScheduleVwPage.cpp
#include "ScheduleVwPage.h"

void ScheduleVwPage::Window_Open(Web::HttpConnector& h)
{
	//________________________________________________________ lvSchedule
	lvSchedule.Cols.Add(LVCFMT_LEFT, 32, L"Professor name");
	lvSchedule.Cols.Add(LVCFMT_LEFT, 16, L"Course name");
	lvSchedule.Cols.Add(LVCFMT_LEFT, 16, L"Period");
	lvSchedule.Cols.Add(LVCFMT_LEFT, 16, L"Time block");
	lvSchedule.Cols.Add(LVCFMT_LEFT, 16, L"Classroom");
	if(h.FirstTime==true) fillListView();
}



void ScheduleVwPage::btInsert_Click(Web::HttpConnector& h)
{
	hdScheduleID.Data= L"-1";
	h.NavigateTo(L"SchedulePage");
	fillListView();
}

void ScheduleVwPage::btEdit_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvSchedule.SelectedIndex;
	if(selectedIndex<0)
	{
		fillListView();
		return;
	}
	const int item_id= Sys::Convert::ToInt(lvSchedule.SelectedData);
	if(item_id<0) return;
	hdScheduleID.Data= lvSchedule.SelectedData;
	h.NavigateTo(L"SchedulePage");
	fillListView();
}

void ScheduleVwPage::btDelete_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvSchedule.GetSelectedIndex();
	if(selectedIndex<0) return; //________________________Nothing is selected

	lvSchedule.AjaxUpdate=true;
	Sql::SqlConnection conn;
	wstring sqlcmd;
	const int item_id= Sys::Convert::ToInt(lvSchedule.Items[selectedIndex].Data); //Get the Primary Key
	int rows= 0;

	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(sqlcmd, L"DELETE FROM schedule WHERE schedule_id=%d", item_id);
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

void ScheduleVwPage::btHome_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"Index");
}

void ScheduleVwPage::fillListView()
{
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		lvSchedule.Items.DeleteAll();
		conn.ExecuteSelect(L"SELECT schedule_id, professor_name,course_name,period,time_block,classroom FROM vw_Schedule", 100, lvSchedule);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}

