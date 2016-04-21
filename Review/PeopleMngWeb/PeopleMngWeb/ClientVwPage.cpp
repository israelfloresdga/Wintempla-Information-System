#include "stdafx.h"  //_____________________________________________ ClientVwPage.cpp
#include "ClientVwPage.h"

void ClientVwPage::Window_Open(Web::HttpConnector& h)
{
	//________________________________________________________ lvEmployee
	lvClient.Cols.Add(LVCFMT_LEFT, 32, L"Name");
	lvClient.Cols.Add(LVCFMT_LEFT, 16, L"Birthdate");
	lvClient.Cols.Add(LVCFMT_LEFT, 24, L"City");
	if(h.FirstTime==true) fillListView();
}


void ClientVwPage::btDelete_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvClient.GetSelectedIndex();
	if(selectedIndex<0) return; //________________________Nothing is selected

	lvClient.AjaxUpdate=true;
	Sql::SqlConnection conn;
	wstring sqlcmd;
	const int item_id= Sys::Convert::ToInt(lvClient.Items[selectedIndex].Data); //Get the Primary Key
	int rows= 0;

	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(sqlcmd, L"DELETE FROM client WHERE client_id=%d", item_id);
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

void ClientVwPage::btInsert_Click(Web::HttpConnector& h)
{
	hdClientID.Data= L"-1";
	h.NavigateTo(L"ClientPage");
	fillListView();
}

void ClientVwPage::btEdit_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvClient.SelectedIndex;
	if(selectedIndex<0)
	{
		fillListView();
		return;
	}
	const int client_id= Sys::Convert::ToInt(lvClient.SelectedData);
	if(client_id<0) return;
	hdClientID.Data= lvClient.SelectedData;
	h.NavigateTo(L"ClientPage");
	fillListView();
}

void ClientVwPage::btHome_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"Index");
}


void ClientVwPage::fillListView()
{
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		lvClient.Items.DeleteAll();
		conn.ExecuteSelect(L"SELECT client_id, name, birthdate, city FROM vw_Client", 100, lvClient);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}