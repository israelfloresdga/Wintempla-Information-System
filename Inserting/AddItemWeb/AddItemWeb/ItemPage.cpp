#include "stdafx.h"  //_____________________________________________ ItemPage.cpp
#include "ItemPage.h"

void ItemPage::Window_Open(Web::HttpConnector& h)
{
	//___________________________________________Fill the category ddlist and the brand ddlist
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN,USERNAME,PASSWORD);
		conn.OpenSession(NULL, CONNECTION_STRING);
		conn.ExecuteSelect(L"SELECT category_id, descr FROM category", 100, ddCategory);
		conn.ExecuteSelect(L"SELECT brand_id, descr FROM brand", 100, ddBrand);
	}
	catch(Sql::SqlException ex)
	{
		this->MessageBoxW(ex.GetDescription(),L"ERROR", MB_OK|MB_ICONERROR);
		return;
	}
	//_______________________________________________________Selected by default 
	if(h.FirstTime==true)
	{
		ddCategory.SelectedIndex= 0;
		ddBrand.SelectedIndex= 0;
	}
}


void ItemPage::btOk_Click(Web::HttpConnector& h)
{
	//_____________________________________________________Extract
	wstring name= tbxName.Text;
	wstring model= tbxModel.Text;
	const int brand_id= Sys::Convert::ToInt(ddBrand.SelectedData);
	const int category_id= Sys::Convert::ToInt(ddCategory.SelectedData);

	//____________________________________________________Validate (you may use regular expressions)
	if(name.length()<=2)
	{
		tbxName.ShowBalloonTip(L"Item Name", L"The item name must cointain at least three characters", TTI_ERROR);
		return;
	}
	if(model.length()<=2)
	{
		this->MessageBox(L"The item model must contain at least three characters",L"Item Model", MB_OK|MB_ICONERROR);
		return;
	}

	//________________________________________Insert
	Sql::SqlConnection conn;
	wstring cmd;
	int rows = 0;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(cmd, L"INSERT INTO item(descr,model,brand_id,category_id) VALUES('%s','%s',%d,%d)", 
			name.c_str(), model.c_str(), brand_id, category_id);
		rows = conn.ExecuteNonQuery(cmd);
		if (rows!=1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"Error - inserted rows", MB_OK | MB_ICONERROR);
		}
		h.NavigateTo(L"Index");
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}

}

void ItemPage::btCancel_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"Index");
}

