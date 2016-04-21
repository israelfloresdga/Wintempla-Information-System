#include "stdafx.h"  //________________________________________ BrandManager.cpp
#include "BrandManager.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	BrandManager app;
	return app.BeginDialog(IDI_BRANDMANAGER, hInstance);
}

void BrandManager::Window_Open(Win::Event& e)
{
	//________________________________________________________ toolbMain
	TBBUTTON tbButton[2];//<< EDIT HERE THE NUMBER OF BUTTONS

	toolbMain.imageList.Create(20, 20, 2);//<< EDIT HERE THE NUMBER OF IMAGES
	toolbMain.imageList.AddIcon(this->hInstance, IDI_ADD);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_EDIT);
	toolbMain.SendMessage(TB_BUTTONSTRUCTSIZE, (WPARAM)(int)sizeof(TBBUTTON), 0); 
	toolbMain.SetImageList(toolbMain.imageList);
	//_____________________________________

	tbButton[0].iBitmap=MAKELONG(0, 0); //<< IMAGE INDEX
	tbButton[0].idCommand=IDM_INSERT;
	tbButton[0].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[0].fsStyle=BTNS_BUTTON;
	tbButton[0].dwData=0L; 
	tbButton[0].iString= (LONG_PTR)L"Add";
	//_____________________________________
	tbButton[1].iBitmap=MAKELONG(1, 0); //<< IMAGE INDEX
	tbButton[1].idCommand=IDM_EDIT;
	tbButton[1].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[1].fsStyle=BTNS_BUTTON;
	tbButton[1].dwData=0L; 
	tbButton[1].iString= (LONG_PTR)L"Edit";
	
	toolbMain.SetBitmapSize(20, 20);
	toolbMain.SetButtonSize(22, 22);
	toolbMain.AddButtons(tbButton, 2);// << EDIT HERE THE NUMBER OF BUTTONS
	toolbMain.SendMessage(TB_AUTOSIZE, 0, 0);
	toolbMain.SetMaxTextRows(0);// EDIT HERE TO DISPLAY THE BUTTON TEXT
	toolbMain.Show(SW_SHOWNORMAL);
	//________________________________________________________ lvBrand
	lvBrand.Cols.Add(0, LVCFMT_LEFT, 100, L"Name");
	//
	toolbMain.EnableButton(IDM_EDIT,false);

	updateListview();
}


void BrandManager::lvBrand_ItemChanged(Win::Event& e)
{
	if(lvBrand.GetSelectedIndex() >=0)
		this->toolbMain.EnableButton(IDM_EDIT,true);
	else
		this->toolbMain.EnableButton(IDM_EDIT,false);
}


void BrandManager::Cmd_Insert(Win::Event& e)
{
	insertBrand();
}

void BrandManager::Cmd_Edit(Win::Event& e)
{
	editBrand();
}

void BrandManager::insertBrand()
{
	BrandDlg dlg;
	dlg.BeginDialog(hWnd);
	updateListview();
}

void BrandManager::editBrand()
{
	const int selectedIndex= lvBrand.GetSelectedIndex();
	if(selectedIndex<0) return;
	//____________________________________________________Ask the user
	if(this->MessageBox(L"Are you sure you want to modify the selected item?", L"Edit item", 
		MB_YESNO|MB_ICONQUESTION)!=IDYES) return;
	//___________________________________________________Edit
	const int brand_id= lvBrand.Items[selectedIndex].Data;
	BrandDlg dlg;
	dlg.brand_id= brand_id;
	dlg.BeginDialog(hWnd);
	updateListview();
}

void BrandManager::updateListview()
{
	//if(lvBrand.GetSelectedIndex<0) return;
	//int selectedIndex;
	//const int brand_id= lvBrand.Items[selectedIndex].Data;

	Sql::SqlConnection conn;
	Win::HourGlassCursor hgc(true);
	wstring cmd;
	try
	{
		toolbMain.EnableButton(IDM_EDIT, false);
		lvBrand.SetRedraw(false);
		lvBrand.Items.DeleteAll();
		//
		conn.OpenSession(hWnd, CONNECTION_STRING);
		Sys::Format(cmd, L"SELECT brand_id, descr FROM brand");
		conn.ExecuteSelect(cmd, 100, lvBrand);
		//
		lvBrand.SetRedraw(true);
	}
	catch(Sql::SqlException ex)
	{
		this->MessageBox(ex.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}
