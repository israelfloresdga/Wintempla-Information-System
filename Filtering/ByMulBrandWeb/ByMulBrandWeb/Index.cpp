#include "stdafx.h"  //_____________________________________________ Index.cpp
#include "Index.h"

void Index::Window_Open(Web::HttpConnector& h)
{
	//________________________________________________________ lvItems: Colums Setup
	lvItems.Cols.Add(LVCFMT_LEFT, 25, L"Item name");
	lvItems.Cols.Add(LVCFMT_LEFT, 10, L"Model");
	lvItems.Cols.Add(LVCFMT_LEFT, 10, L"Brand");
	lvItems.Cols.Add(LVCFMT_LEFT, 15, L"Category");
	//________________________________________________________ clBrand: Column Setup
	clBrand.Cols.Add(LVCFMT_LEFT, L"Brand");
	clBrand.css.height= 190;
	//________________________________________________________clBrand: Fill the check box list
	if(h.ContentType==HTML_CONTENT_TYPE_TEXT_HTML)
	{
		Sql::SqlConnection conn;
		try
		{
			//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
			conn.OpenSession(NULL, CONNECTION_STRING);
			conn.ExecuteSelect(L"SELECT category_id, descr FROM category", 100, clBrand);
		}
		catch (Sql::SqlException ex)
		{
			this->MessageBox(ex.GetDescription(), L"ERROR", MB_OK | MB_ICONERROR);
		}
		//__________________________________________________________Select by default the first category
		clBrand.Items[0].Checked= true;
		updateItems();
	}
	else if(h.ContentType==HTML_CONTENT_TYPE_TEXT_XML)
	{
		lvItems.AjaxUpdate= true;
		clBrand.AjaxUpdate= false;
	}
}


void Index::clBrand_Change(Web::HttpConnector& h)
{
	updateItems();
}

bool Index::buildSqlQuery(wstring& sqlcmd)
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
				const int brand_id= Sys::Convert::ToInt(clBrand.Items[i].Data);
				if(isFirst==true)
				{
					isFirst= false;
					Sys::Format(sqlcmd,
						L"SELECT item_id, [item descr], model, [brand descr], [category descr] FROM vw_Item WHERE brand_id= %d", brand_id);
				}
				else
				{
					Sys::Format(text, L" OR brand_id= %d", brand_id);
					sqlcmd+= text;
				}
			}
		}
	}

	return true;
}

void Index::updateItems()
{
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
		conn.OpenSession(NULL, CONNECTION_STRING);
		lvItems.Items.DeleteAll();
		conn.ExecuteSelect(sqlcmd,100,lvItems);
	}
	catch(Sql::SqlException ex)
	{
		this->MessageBox(ex.GetDescription(), L"ERROR", MB_OK|MB_ICONERROR);
	}
}
