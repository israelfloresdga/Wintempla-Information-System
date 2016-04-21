#include "stdafx.h"  //________________________________________ SharingLv.cpp
#include "SharingLv.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	SharingLv app;
	return app.BeginDialog(IDI_SHARINGLV, hInstance);
}

void SharingLv::Window_Open(Win::Event& e)
{
	//________________________________________________________ ddMain
	ddMain.Items.Add(L"Category", 10);
	ddMain.Items.Add(L"Brand", 20);
	ddMain.SelectedIndex= 0;
	//________________________________________________________ lvMain
	lvMain.Cols.Add(0, LVCFMT_RIGHT, 200, L"Name");
	updateItems();
}

void SharingLv::ddMain_SelChange(Win::Event& e)
{
	updateItems();
}

void SharingLv::updateItems()
{
	if(ddMain.SelectedIndex<0) return; 
	wstring sqlcmd;
	
	if(ddMain.SelectedIndex==0) 
		Sys::Format(sqlcmd, L"SELECT category_id, descr FROM category");
	if(ddMain.SelectedIndex==1) 
		Sys::Format(sqlcmd, L"SELECT brand_id, descr FROM brand");

	Sql::SqlConnection conn;
	Win::HourGlassCursor hgc(true);
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD);
		conn.OpenSession(hWnd, CONNECTION_STRING);
		lvMain.SetRedraw(false);//stop redrawing the control when inserting items
		lvMain.Items.DeleteAll();
		conn.ExecuteSelect(sqlcmd, 100, lvMain);
		lvMain.SetRedraw(true);
	}
	catch(Sql::SqlException ex)
	{
		this->MessageBox(ex.GetDescription(), L"ERROR", MB_OK | MB_ICONERROR);
	}
}