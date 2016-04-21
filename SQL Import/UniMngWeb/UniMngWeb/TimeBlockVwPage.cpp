#include "stdafx.h"  //_____________________________________________ TimeBlockVwPage.cpp
#include "TimeBlockVwPage.h"

void TimeBlockVwPage::Window_Open(Web::HttpConnector& h)
{
	//________________________________________________________ lvTime_block
	lvTime_block.Cols.Add(LVCFMT_LEFT, 16, L"Description");
	lvTime_block.Cols.Add(LVCFMT_LEFT, 10, L"Monday");
	lvTime_block.Cols.Add(LVCFMT_LEFT, 10, L"Tuesday");
	lvTime_block.Cols.Add(LVCFMT_LEFT, 10, L"Wednesday");
	lvTime_block.Cols.Add(LVCFMT_LEFT, 10, L"Thursday");
	lvTime_block.Cols.Add(LVCFMT_LEFT, 10, L"Friday");
	lvTime_block.Cols.Add(LVCFMT_LEFT, 10, L"Saturday");
	if(h.FirstTime==true) fillListView();
}


void TimeBlockVwPage::btInsert_Click(Web::HttpConnector& h)
{
	hdTime_blockID.Data= L"-1";
	h.NavigateTo(L"TimeBlockPage");
	fillListView();
}

void TimeBlockVwPage::btEdit_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvTime_block.SelectedIndex;
	if(selectedIndex<0) 
	{
		fillListView();
		return;
	}
	const int item_id= Sys::Convert::ToInt(lvTime_block.SelectedData);
	if(item_id<0) return;
	hdTime_blockID.Data= lvTime_block.SelectedData;
	h.NavigateTo(L"TimeBlockPage");
	fillListView();
}

void TimeBlockVwPage::btDelete_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvTime_block.GetSelectedIndex();
	if(selectedIndex<0) return; //________________________Nothing is selected

	lvTime_block.AjaxUpdate=true;
	Sql::SqlConnection conn;
	wstring sqlcmd;
	const int item_id= Sys::Convert::ToInt(lvTime_block.Items[selectedIndex].Data); //Get the Primary Key
	int rows= 0;

	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(sqlcmd, L"DELETE FROM time_block WHERE time_block_id=%d", item_id);
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

void TimeBlockVwPage::btHome_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"Index");
}

void TimeBlockVwPage::fillListView()
{
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		lvTime_block.Items.DeleteAll();
		conn.ExecuteSelect(L"SELECT time_block_id, descr, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday FROM vw_Time_block", 100, lvTime_block);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}
