#include "stdafx.h"  //________________________________________ Deleteitem.cpp
#include "Deleteitem.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	Deleteitem app;
	return app.BeginDialog(IDI_DELETEITEM, hInstance);
}

void Deleteitem::Window_Open(Win::Event& e)
{
	//________________________________________________________ toolbMain
	TBBUTTON tbButton[1];//<< EDIT HERE THE NUMBER OF BUTTONS

	toolbMain.imageList.Create(20, 20, 1);//<< EDIT HERE THE NUMBER OF IMAGES
	toolbMain.imageList.AddIcon(this->hInstance, IDI_DELETE);

	toolbMain.SendMessage(TB_BUTTONSTRUCTSIZE, (WPARAM)(int)sizeof(TBBUTTON), 0); 
	toolbMain.SetImageList(toolbMain.imageList);
	//_____________________________________
	tbButton[0].iBitmap=MAKELONG(0, 0); //<< IMAGE INDEX
	tbButton[0].idCommand=IDM_DELETE;
	tbButton[0].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[0].fsStyle=BTNS_BUTTON;
	tbButton[0].dwData=0L; 
	tbButton[0].iString= (LONG_PTR)L"Delete";

	toolbMain.SetBitmapSize(20, 20);
	toolbMain.SetButtonSize(24, 24);
	toolbMain.AddButtons(tbButton, 1);// << EDIT HERE THE NUMBER OF BUTTONS
	toolbMain.SendMessage(TB_AUTOSIZE, 0, 0);
	toolbMain.SetMaxTextRows(0);// EDIT HERE TO DISPLAY THE BUTTON TEXT
	toolbMain.Show(SW_SHOWNORMAL);
	//________________________________________________________ lvItems: Column Setup
	lvItems.Cols.Add(0, LVCFMT_LEFT, 200, L"Item name");
	lvItems.Cols.Add(1, LVCFMT_LEFT, 120, L"Model");
	lvItems.Cols.Add(2, LVCFMT_LEFT, 120, L"Brand");
	lvItems.Cols.Add(3, LVCFMT_LEFT, 120, L"Category");

	//________________________________________________________Disable the Delete Button
	toolbMain.EnableButton(IDM_DELETE, false);

	fillListView(); //Fill the list view control wit the items
}

void Deleteitem::deleteItem()
{
	Win::HourGlassCursor hgc(true);
	const int selectedCount= lvItems.GetSelectedCount();
	if(selectedCount<0) return; //_____________________________Nothing is selected
	//_________________________________________________________Ask the user
	if(this->MessageBox(L"Are you sure you want to delete the selected item(s)?", L"Delete item",
		MB_YESNO|MB_ICONQUESTION)!=IDYES) return;
	//________________________________________________________Delete;
	Sql::SqlConnection conn;
	wstring cmd;
	int item_id= 0; //Get the Primary Key; 
	int rows= 0;
	int index= -1;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		
		for(int i=0; i<selectedCount; i++)
		{
			index= lvItems.GetNextSelectedIndex(index);
			if(index<0) break;
			item_id= lvItems.Items[index].Data;
			Sys::Format(cmd, L"DELETE FROM item WHERE item_id= %d", item_id);
			rows = conn.ExecuteNonQuery(cmd);
			if (rows!=1)
			{
				this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of deleted rows", MB_OK | MB_ICONERROR);
			}
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	fillListView();
	toolbMain.EnableButton(IDM_DELETE,false);
}

void Deleteitem::fillListView()
{
	lvItems.SetRedraw(false);
	lvItems.Items.DeleteAll();

	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		conn.ExecuteSelect(L"SELECT item_id, [item descr], model, [brand descr], [category descr] FROM vw_Item", 100, lvItems);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	lvItems.SetRedraw(true);
	toolbMain.EnableButton(IDM_DELETE,false);
}
void Deleteitem::lvItems_ItemChanged(Win::Event& e)
{
	if(lvItems.GetSelectedCount() >=0)
		this->toolbMain.EnableButton(IDM_DELETE,true);
	else
		this->toolbMain.EnableButton(IDM_DELETE,false);
}

void Deleteitem::lvItems_KeyDown(Win::Event& e)
{
	LPNMLVKEYDOWN p = (LPNMLVKEYDOWN) e.lParam;
	if (p->wVKey == VK_DELETE)
	{
		deleteItem();
	}
}

void Deleteitem::Cmd_Delete(Win::Event& e)
{
	deleteItem();
}

