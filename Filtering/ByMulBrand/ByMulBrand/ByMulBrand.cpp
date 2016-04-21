#include "stdafx.h"  //________________________________________ ByMulBrand.cpp
#include "ByMulBrand.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	ByMulBrand app;
	return app.BeginDialog(IDI_BYMULBRAND, hInstance);
}

void ByMulBrand::Window_Open(Win::Event& e)
{
	//________________________________________________________ lvItems: Colums Setup
	lvItems.Cols.Add(0, LVCFMT_LEFT, 180, L"Item name");
	lvItems.Cols.Add(1, LVCFMT_LEFT, 110, L"Model");
	lvItems.Cols.Add(2, LVCFMT_LEFT, 110, L"Brand");
	lvItems.Cols.Add(3, LVCFMT_LEFT, 110, L"Category");
	//________________________________________________________ clBrand: Column Setup
	clBrand.Cols.Add(0, LVCFMT_LEFT, 120, L"Brand");
	
	//________________________________________________________clBrand: Fill the check box list
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		conn.ExecuteSelect(L"SELECT category_id, descr FROM category", 100, clBrand);
	}
	catch (Sql::SqlException ex)
	{
		this->MessageBox(ex.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	//__________________________________________________________Select by default the first category
	clBrand.Items[0].Checked= true;
	updateItems();
}

void ByMulBrand::clBrand_ItemChanged(Win::Event& e)
{
	updateItems();
}

bool ByMulBrand::buildSqlQuery(wstring& sqlcmd)
{
	const int itemCount= clBrand.Items.Count;
	int count= 0;
	int i;
	//_________________________________________________________count how many are checked
	for(i=0; i<itemCount; i++)
	{
		if(clBrand.Items[i].Checked==true) count++;
	}
	//_________________________________________________________Build the SQL query
	if(count==0) return false;
	else
	{
		bool isFirst= true;
		wstring text;
		for(i=0; i<itemCount; i++)
		{
			if(clBrand.Items[i].Checked==true)
			{
				if(isFirst==true)
				{
					isFirst= false;
					Sys::Format(sqlcmd,
						L"SELECT item_id, [item descr], model, [brand descr], [category descr] FROM vw_Item WHERE brand_id= %d", clBrand.Items[i].Data);
				}
				else
				{
					Sys::Format(text, L"OR brand_id= %d", clBrand.Items[i].Data);
					sqlcmd+= text;
				}
			}
		}
	}
	return true;
}

void ByMulBrand::updateItems()
{
	Win::HourGlassCursor hgc(true);
	wstring sqlcmd;
	if(buildSqlQuery(sqlcmd)==false)
	{
		lvItems.Items.DeleteAll();
		return;
	}

	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD);
		conn.OpenSession(hWnd, CONNECTION_STRING);
		lvItems.SetRedraw(false); //stop redrawing the control when inserting items
		lvItems.Items.DeleteAll();
		conn.ExecuteSelect(sqlcmd,100,lvItems);
		lvItems.SetRedraw(true);
	}
	catch(Sql::SqlException ex)
	{
		this->MessageBox(ex.GetDescription(), L"ERROR", MB_OK|MB_ICONERROR);
	}
}