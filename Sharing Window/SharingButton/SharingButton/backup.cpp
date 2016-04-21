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
	radioItems.SetChecked(true);
	radioClient.SetChecked(false); 
	//________________________________________________________ lvMain
	fillListView();
}


void SharingButton::fillListView()
{
	lvMain.SetRedraw(false);
	lvMain.Items.DeleteAll();

	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		if(radioItems.Checked==true)
			conn.ExecuteSelect(L"SELECT item_id, [item descr], model, [brand descr], [category descr] FROM vw_Item", 100, lvMain);
		if(radioClient.Checked==true)
			conn.ExecuteSelect(L"SELECT client_id, Name, Age, City FROM vw_Client", 100, lvMain);

	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	lvMain.SetRedraw(true);
	toolbMain.EnableButton(IDM_DELETE,false);
}

void SharingButton::radioClient_Click(Win::Event& e)
{
	radioItems.SetChecked(false);
	radioClient.SetChecked(true);
}

void SharingButton::radioItems_Click(Win::Event& e)
{
	radioItems.SetChecked(true);
	radioClient.SetChecked(false);
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

