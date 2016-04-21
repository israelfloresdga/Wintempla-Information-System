#include "stdafx.h"  //_____________________________________________ ItemDlg.cpp
#include "ItemDlg.h"

void ItemDlg::Window_Open(Win::Event& e)
{
	this->Text= L"Item";
	//____________________________________________________Fill the category ddlist and the brand ddlist
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		conn.ExecuteSelect(L"SELECT category_id, descr FROM category", 100, ddCategory);
		conn.ExecuteSelect(L"SELECT brand_id, descr FROM brand", 100, ddBrand);
	}
	catch (Sql::SqlException ex)
	{
		this->MessageBox(ex.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	//____________________________________________________Select default values
	ddBrand.SelectedIndex= 0;
	ddCategory.SelectedIndex= 0;
}



void ItemDlg::btOk_Click(Win::Event& e)
{
	//________________________________________Extract
	wstring name= tbxName.Text;
	wstring model= tbxModel.Text;
	const int brand_id= ddBrand.SelectedData;
	const int category_id= ddCategory.SelectedData;

	//________________________________________Validate (you may use regular expressions)
	if(name.length()<=2)
	{
		tbxName.ShowBalloonTip(L"Item Name", L"The item name must containt at least three characters", TTI_ERROR);
		return;
	}
	if(model.length()<=2)
	{
		tbxModel.ShowBalloonTip(L"Item Model", L"The item model must containt at least three characters", TTI_ERROR);
		return;
	}
	//_________________________________________Insert
	Sql::SqlConnection conn;
	wstring cmd;
	int rows = 0;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		Sys::Format(cmd, L"INSERT INTO item (descr, model, brand_id, category_id) VALUES('%s','%s',%d,%d)", 
			name.c_str(), model.c_str(), brand_id, category_id);
		rows = conn.ExecuteNonQuery(cmd);
		if (rows!=1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"Error: inserted rows", MB_OK | MB_ICONERROR);
		}
		this->EndDialog(TRUE);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}

}

void ItemDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}

