#include "stdafx.h"  //________________________________________ SharingButton.cpp
#include "SharingButton.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	SharingButton app;
	return app.BeginDialog(IDI_SHARINGBUTTON, hInstance);
}

void SharingButton::Window_Open(Win::Event& e)
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

	toolbMain.SetBitmapSize(21, 21);
	toolbMain.SetButtonSize(22, 22);
	toolbMain.AddButtons(tbButton, 1);// << EDIT HERE THE NUMBER OF BUTTONS
	toolbMain.SendMessage(TB_AUTOSIZE, 0, 0);
	toolbMain.SetMaxTextRows(0);// EDIT HERE TO DISPLAY THE BUTTON TEXT
	toolbMain.Show(SW_SHOWNORMAL);

	//________________________________________________________Disable the Delete Button
	toolbMain.EnableButton(IDM_DELETE, false);
	//________________________________________________________checkButtons
	radioItems.SetChecked(false);
	radioClient.SetChecked(true); 
	//________________________________________________________ lvMain
	fillListView();
}

void SharingButton::fillListViewCols()
{
	lvMain.SetRedraw(false);
	lvMain.Cols.DeleteAll();
	if(radioItems.Checked==true)
	{
		lvMain.Cols.Add(0, LVCFMT_LEFT, 200, L"Name");
		lvMain.Cols.Add(1, LVCFMT_LEFT, 120, L"Model");
		lvMain.Cols.Add(2, LVCFMT_LEFT, 120, L"Brand");
		lvMain.Cols.Add(3, LVCFMT_LEFT, 120, L"Category");
	}
	if(radioClient.Checked==true)
	{
		lvMain.Cols.Add(0, LVCFMT_LEFT, 250, L"Name");
		lvMain.Cols.Add(1, LVCFMT_LEFT, 120, L"Age");
		lvMain.Cols.Add(2, LVCFMT_LEFT, 120, L"City");
	}
	lvMain.SetRedraw(true);
}

void SharingButton::fillListView()
{
	fillListViewCols();
	lvMain.SetRedraw(false);
	lvMain.Items.DeleteAll();

	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		if(radioItems.Checked==true)
			conn.ExecuteSelect(L"SELECT item_id, [item descr], model, [brand descr], [category descr] FROM vw_Item", 100, lvMain);
		else if(radioClient.Checked==true)
			conn.ExecuteSelect(L"SELECT client_id, name, age, city FROM vw_Client", 100, lvMain);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	lvMain.SetRedraw(true);
	toolbMain.EnableButton(IDM_DELETE,false);
}

void SharingButton::deleteItem()
{
	Win::HourGlassCursor hgc(true);
	const int selectedIndex= lvMain.GetSelectedIndex();
	if(selectedIndex<0) return; 
	//_________________________________________________________Ask the user
	if(this->MessageBox(L"Are you sure you want to delete the selected item?", L"Delete item",
		MB_YESNO|MB_ICONQUESTION)!=IDYES) return;
	//________________________________________________________Delete;
	Sql::SqlConnection conn;
	wstring cmd;
	const int element_id= lvMain.Items[selectedIndex].Data; //Get the Primary Key; 
	int rows = 0;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		if(radioItems.Checked==true) Sys::Format(cmd, L"DELETE FROM item WHERE item_id= %d", element_id);
		else if(radioClient.Checked==true) Sys::Format(cmd,L"DELETE FROM client WHERE client_id= %d", element_id);
		rows = conn.ExecuteNonQuery(cmd);
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

void SharingButton::radioClient_Click(Win::Event& e)
{
	radioItems.SetChecked(false);
	radioClient.SetChecked(true);
	fillListView();
}

void SharingButton::radioItems_Click(Win::Event& e)
{
	radioItems.SetChecked(true);
	radioClient.SetChecked(false);
	fillListView();
}

void SharingButton::lvMain_ItemChanged(Win::Event& e)
{
	if(lvMain.GetSelectedIndex() >=0)
		this->toolbMain.EnableButton(IDM_DELETE,true);
	else
		this->toolbMain.EnableButton(IDM_DELETE,false);
}

void SharingButton::lvMain_KeyDown(Win::Event& e)
{
	LPNMLVKEYDOWN p = (LPNMLVKEYDOWN) e.lParam;
	if (p->wVKey == VK_DELETE)
	{
		deleteItem();
	}
}

void SharingButton::Cmd_Delete(Win::Event& e)
{
	deleteItem();
}

