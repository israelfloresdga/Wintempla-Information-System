#include "stdafx.h"  //_____________________________________________ ProfessorVwPage.cpp
#include "ProfessorVwPage.h"

void ProfessorVwPage::Window_Open(Web::HttpConnector& h)
{
	//________________________________________________________ lvProfessor
	lvProfessor.Cols.Add(LVCFMT_LEFT, 32, L"Name");
	lvProfessor.Cols.Add(LVCFMT_LEFT, 32, L"Department");
	lvProfessor.Cols.Add(LVCFMT_LEFT, 16, L"Username");
	if(h.FirstTime==true) fillListView();
}



void ProfessorVwPage::btInsert_Click(Web::HttpConnector& h)
{
	hdProfessorID.Data= L"-1";
	h.NavigateTo(L"ProfessorPage");
	fillListView();
}

void ProfessorVwPage::btEdit_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvProfessor.SelectedIndex;
	if(selectedIndex<0)
	{
		fillListView();
		return;
	}
	const int item_id= Sys::Convert::ToInt(lvProfessor.SelectedData);
	if(item_id<0) return;
	hdProfessorID.Data= lvProfessor.SelectedData;
	h.NavigateTo(L"ProfessorPage");
	fillListView();
}

void ProfessorVwPage::btDelete_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvProfessor.GetSelectedIndex();
	if(selectedIndex<0) return; //________________________Nothing is selected

	lvProfessor.AjaxUpdate=true;
	Sql::SqlConnection conn;
	wstring sqlcmd;
	const int item_id= Sys::Convert::ToInt(lvProfessor.Items[selectedIndex].Data); //Get the Primary Key
	int rows= 0;

	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(sqlcmd, L"DELETE FROM professor WHERE professor_id=%d", item_id);
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

void ProfessorVwPage::btHome_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"Index");
}

void ProfessorVwPage::fillListView()
{
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		lvProfessor.Items.DeleteAll();
		conn.ExecuteSelect(L"SELECT professor_id, name, department_descr, username FROM vw_Professor", 100, lvProfessor);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}