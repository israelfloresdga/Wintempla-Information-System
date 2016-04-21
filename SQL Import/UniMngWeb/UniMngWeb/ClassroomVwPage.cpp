#include "stdafx.h"  //_____________________________________________ ClassroomVwPage.cpp
#include "ClassroomVwPage.h"

void ClassroomVwPage::Window_Open(Web::HttpConnector& h)
{
	//________________________________________________________ lvClassroom
	lvClassroom.Cols.Add(LVCFMT_LEFT, 16, L"Classroom");
	lvClassroom.Cols.Add(LVCFMT_LEFT, 16, L"Number of seats");
	lvClassroom.Cols.Add(LVCFMT_LEFT, 16, L"Has projector");
	lvClassroom.Cols.Add(LVCFMT_LEFT, 16, L"Building");
	if(h.FirstTime==true) fillListView();
}


void ClassroomVwPage::btInsert_Click(Web::HttpConnector& h)
{
	hdClassroomID.Data= L"-1";
	h.NavigateTo(L"ClassroomPage");
	fillListView();
}

void ClassroomVwPage::btEdit_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvClassroom.SelectedIndex;
	if(selectedIndex<0)
	{
		fillListView();
		return;
	}
	const int item_id= Sys::Convert::ToInt(lvClassroom.SelectedData);
	if(item_id<0) return;
	hdClassroomID.Data= lvClassroom.SelectedData;
	h.NavigateTo(L"ClassroomPage");
	fillListView();
}

void ClassroomVwPage::btDelete_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvClassroom.GetSelectedIndex();
	if(selectedIndex<0) return; //________________________Nothing is selected

	lvClassroom.AjaxUpdate=true;
	Sql::SqlConnection conn;
	wstring sqlcmd;
	const int item_id= Sys::Convert::ToInt(lvClassroom.Items[selectedIndex].Data); //Get the Primary Key
	int rows= 0;

	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(sqlcmd, L"DELETE FROM classroom WHERE classroom_id=%d", item_id);
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

void ClassroomVwPage::btHome_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"Index");
}

void ClassroomVwPage::fillListView()
{
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		lvClassroom.Items.DeleteAll();
		conn.ExecuteSelect(L"SELECT classroom_id, descr, seat_count, has_projector, building FROM vw_Classroom", 100, lvClassroom);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}
