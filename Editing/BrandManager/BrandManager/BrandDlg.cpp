#include "stdafx.h"  //_____________________________________________ BrandDlg.cpp
#include "BrandDlg.h"

void BrandDlg::Window_Open(Win::Event& e)
{
	this->Text= L"Brand";
	if(brand_id<0) return; //if INSERT, just return
	Sql::SqlConnection conn;
	wstring cmd;
	wstring name;
	int count=0;
	Sys::Format(cmd, L"SELECT descr FROM brand WHERE brand_id= %d", brand_id);

	try
	{
		//conn.OpenSession(DSN,USERNAME,PASSWORD);
		conn.OpenSession(hWnd, CONNECTION_STRING);
		conn.ExecuteSelect(cmd);
		conn.BindColumn(1,tbxBrand,64);
		if(conn.Fetch()==false)
			this->MessageBox(L"No data was returned", L"ERROR", MB_OK|MB_ICONERROR);
	}
	catch(Sql::SqlException ex)
	{
		this->MessageBox(ex.GetDescription(), L"ERROR", MB_OK|MB_ICONERROR);
	}
}


void BrandDlg::btOk_Click(Win::Event& e)
{
	Sql::StringBuilder sb(L"brand", L"brand_id", brand_id);
	sb.Bind(L"descr", tbxBrand);

	Sql::SqlConnection conn;
	int rows= 0;
	try
	{
		conn.OpenSession(hWnd,CONNECTION_STRING);
		rows= conn.ExecuteNonQuery(sb.GetString());
		if(rows!=1) this->MessageBox(Sys::Convert::ToString(rows), L"ERROR number of rows", MB_OK|MB_ICONERROR);
	}
	catch(Sql::SqlException ex)
	{
		this->MessageBox(ex.GetDescription(), L"ERROR", MB_OK|MB_ICONERROR);
	}
	this->EndDialog(TRUE);
	/*
	Sql::SqlConnection conn;
	wstring cmd;
	wstring descr= tbxBrand.Text;
	if(descr.length()<=2)
	{
		this->tbxBrand.ShowBalloonTip(L"Brand",L"The brand name must be at least two characters", TTI_ERROR);
		return;
	}
	int rows= 0;
	
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		if(brand_id<0)	Sys::Format(cmd, L"INSERT INTO brand(descr) VALUES('%s')",descr.c_str());
		else Sys::Format(cmd, L"UPDATE brand SET descr='%s' WHERE brand_id=%d", descr.c_str(), brand_id);
	
		rows = conn.ExecuteNonQuery(cmd);
		if (rows!=1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of inserted rows", MB_OK | MB_ICONERROR);
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	this->EndDialog(TRUE);
	*/
}


void BrandDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}

