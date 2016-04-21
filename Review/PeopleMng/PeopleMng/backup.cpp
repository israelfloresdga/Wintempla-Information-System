#include "stdafx.h"  //________________________________________ PeopleMng.cpp
#include "PeopleMng.h"
#include "ClientDlg.h"
#include "EmployeeDlg.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	PeopleMng app;
	return app.BeginDialog(IDI_PEOPLEMNG, hInstance);
}

void PeopleMng::Window_Open(Win::Event& e)
{
	//________________________________________________________ toolbMain
	TBBUTTON tbButton[10];//<< EDIT HERE THE NUMBER OF BUTTONS

	toolbMain.imageList.Create(20, 20, 10);//<< EDIT HERE THE NUMBER OF IMAGES
	toolbMain.imageList.AddIcon(this->hInstance, IDI_INSERT);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_EDIT);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_DELETE);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_PRINT);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_CLIENT);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_EMPLOYEE);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_COPY);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_MSEXCEL);
	toolbMain.SendMessage(TB_BUTTONSTRUCTSIZE, (WPARAM)(int)sizeof(TBBUTTON), 0); 
	toolbMain.SetImageList(toolbMain.imageList);
	//_____________________________________
	tbButton[0].iBitmap=MAKELONG(0, 0); //<< IMAGE INDEX
	tbButton[0].idCommand=IDM_INSERT;
	tbButton[0].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[0].fsStyle=BTNS_BUTTON;
	tbButton[0].dwData=0L; 
	tbButton[0].iString= (LONG_PTR)L"Insert";
	//_____________________________________
	tbButton[1].iBitmap=MAKELONG(1, 0); //<< IMAGE INDEX
	tbButton[1].idCommand=IDM_EDIT;
	tbButton[1].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[1].fsStyle=BTNS_BUTTON;
	tbButton[1].dwData=0L; 
	tbButton[1].iString= (LONG_PTR)L"Edit";
	//_____________________________________
	tbButton[2].iBitmap=MAKELONG(2, 0); //<< IMAGE INDEX
	tbButton[2].idCommand=IDM_DELETE;
	tbButton[2].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[2].fsStyle=BTNS_BUTTON;
	tbButton[2].dwData=0L; 
	tbButton[2].iString= (LONG_PTR)L"Delete";
	//_____________________________________
	tbButton[3].iBitmap=MAKELONG(3, 0); //<< IMAGE INDEX
	tbButton[3].idCommand=IDM_PRINT;
	tbButton[3].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[3].fsStyle=BTNS_BUTTON;
	tbButton[3].dwData=0L; 
	tbButton[3].iString= (LONG_PTR)L"Print";
	//________________________ A separator
	tbButton[4].iBitmap=-1;
	tbButton[4].idCommand=0;  
	tbButton[4].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[4].fsStyle=BTNS_SEP;  
	tbButton[4].dwData=0L;  
	tbButton[4].iString=0;  
	//_____________________________________
	tbButton[5].iBitmap=MAKELONG(4, 0); //<< IMAGE INDEX
	tbButton[5].idCommand=IDM_CLIENT;
	tbButton[5].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[5].fsStyle=BTNS_BUTTON;
	tbButton[5].dwData=0L; 
	tbButton[5].iString= (LONG_PTR)L"Client";
	//_____________________________________
	tbButton[6].iBitmap=MAKELONG(5, 0); //<< IMAGE INDEX
	tbButton[6].idCommand=IDM_EMPLOYEE;
	tbButton[6].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[6].fsStyle=BTNS_BUTTON;
	tbButton[6].dwData=0L; 
	tbButton[6].iString= (LONG_PTR)L"Employee";
	//________________________ A separator
	tbButton[7].iBitmap=-1;
	tbButton[7].idCommand=0;  
	tbButton[7].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[7].fsStyle=BTNS_SEP;  
	tbButton[7].dwData=0L;  
	tbButton[7].iString=0;  
	//_____________________________________
	tbButton[8].iBitmap=MAKELONG(6, 0); //<< IMAGE INDEX
	tbButton[8].idCommand=IDM_COPY;
	tbButton[8].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[8].fsStyle=BTNS_BUTTON;
	tbButton[8].dwData=0L; 
	tbButton[8].iString= (LONG_PTR)L"Copy";
	//_____________________________________
	tbButton[9].iBitmap=MAKELONG(7, 0); //<< IMAGE INDEX
	tbButton[9].idCommand=IDM_MSEXCEL;
	tbButton[9].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[9].fsStyle=BTNS_BUTTON;
	tbButton[9].dwData=0L; 
	tbButton[9].iString= (LONG_PTR)L"Export";
	
	toolbMain.SetBitmapSize(20, 20);
	toolbMain.SetButtonSize(24, 24);
	toolbMain.AddButtons(tbButton, 10);// << EDIT HERE THE NUMBER OF BUTTONS
	toolbMain.SendMessage(TB_AUTOSIZE, 0, 0);
	toolbMain.SetMaxTextRows(0);// EDIT HERE TO DISPLAY THE BUTTON TEXT
	toolbMain.Show(SW_SHOWNORMAL);
	//____________________________________________________Set enable/disable buttons
	toolbMain.EnableButton(IDM_INSERT, false);
	toolbMain.EnableButton(IDM_EDIT, false);
	toolbMain.EnableButton(IDM_DELETE, false);
	toolbMain.EnableButton(IDM_PRINT, true);
	toolbMain.EnableButton(IDM_CLIENT, true);
	toolbMain.EnableButton(IDM_EMPLOYEE, true);
	toolbMain.EnableButton(IDM_COPY, true);
	toolbMain.EnableButton(IDM_MSEXCEL, true);
	fillListViewCols();
}

void PeopleMng::Cmd_Client(Win::Event& e)
{
	toolbMain.EnableButton(IDM_INSERT, true);
	toolbMain.EnableButton(IDM_CLIENT, false);
	toolbMain.EnableButton(IDM_EMPLOYEE, true);
	toolbMain.EnableButton(IDM_EDIT, false);
	toolbMain.EnableButton(IDM_DELETE, false);
	fillListView();
}

void PeopleMng::Cmd_Employee(Win::Event& e)
{
	toolbMain.EnableButton(IDM_INSERT, true);
	toolbMain.EnableButton(IDM_EMPLOYEE, false);
	toolbMain.EnableButton(IDM_CLIENT, true);
	toolbMain.EnableButton(IDM_EDIT, false);
	toolbMain.EnableButton(IDM_DELETE, false);
	fillListView();
}

void PeopleMng::Cmd_Print(Win::Event& e)
{
	//___________________________________________________Build document
	Win::PrintDoc doc;
	doc.Create(L"PeopleMng");
	doc.Add(500,lvMain.Items.Count+1,lvMain);//0.5cm
	//___________________________________________________Print doc
	Win::PrintPreviewDlg dlg;
	dlg.BeginDialog_(hWnd, &doc);
}

void PeopleMng::Cmd_Insert(Win::Event& e)
{
	insertItem();
}

void PeopleMng::Cmd_Delete(Win::Event& e)
{
	deleteItem();
}

void PeopleMng::Cmd_Edit(Win::Event& e)
{
	editItem();
}

void PeopleMng::Cmd_Copy(Win::Event& e)
{
}

void PeopleMng::Cmd_Msexcel(Win::Event& e)
{
}

void PeopleMng::fillListViewCols()
{
	lvMain.SetRedraw(false);
	lvMain.Cols.DeleteAll();
	if(toolbMain.IsButtonEnabled(IDM_CLIENT)==false)
	{
		lvMain.Cols.Add(0, LVCFMT_LEFT, 200, L"Name");
		lvMain.Cols.Add(1, LVCFMT_LEFT, 150, L"Birthdate");
		lvMain.Cols.Add(2, LVCFMT_LEFT, 150, L"City");
	}
	else if(toolbMain.IsButtonEnabled(IDM_EMPLOYEE)==false)
	{
		lvMain.Cols.Add(0, LVCFMT_LEFT, 200, L"Name");
		lvMain.Cols.Add(1, LVCFMT_LEFT, 150, L"Username");
		lvMain.Cols.Add(2, LVCFMT_LEFT, 150, L"Phone");
	}
	else
	{
		lvMain.Cols.Add(0, LVCFMT_LEFT, 200, L"Name");
		lvMain.Cols.Add(1, LVCFMT_LEFT, 150, L"Columna");
		lvMain.Cols.Add(2, LVCFMT_LEFT, 150, L"Columna");
	}
	lvMain.Width= width;
	lvMain.Height= height;
	lvMain.SetRedraw(true);
}

void PeopleMng::fillListView()
{
	fillListViewCols();
	lvMain.SetRedraw(false);
	lvMain.Items.DeleteAll();
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		if(toolbMain.IsButtonEnabled(IDM_CLIENT)==false)
			conn.ExecuteSelect(L"SELECT client_id, name, birthdate, city FROM vw_Client", 100, lvMain);
		else if(toolbMain.IsButtonEnabled(IDM_EMPLOYEE)==false)
			conn.ExecuteSelect(L"SELECT employee_id, name, username, phone FROM vw_Employee", 100, lvMain);
		else return;
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	lvMain.SetRedraw(true);
}


void PeopleMng::lvMain_ItemChanged(Win::Event& e)
{
	if(lvMain.GetSelectedIndex() >=0)
	{
		this->toolbMain.EnableButton(IDM_DELETE,true);
		this->toolbMain.EnableButton(IDM_EDIT,true);
	}
	else
	{
		this->toolbMain.EnableButton(IDM_DELETE,false);
		this->toolbMain.EnableButton(IDM_EDIT,false);
	}
}

void PeopleMng::lvMain_KeyDown(Win::Event& e)
{
	LPNMLVKEYDOWN p = (LPNMLVKEYDOWN) e.lParam;
	if (p->wVKey == VK_DELETE)
	{
		deleteItem();
	}
}

void PeopleMng::lvMain_DblClk(Win::Event& e)
{
	editItem();
}

void PeopleMng::deleteItem()
{
	Win::HourGlassCursor hgc(true);
	const int selectedIndex= lvMain.GetSelectedIndex();
	if(selectedIndex<0) return; //_____________________________Nothing is selected
	//_________________________________________________________Ask the user
	if(this->MessageBox(L"Are you sure you want to delete the selected item?", L"Delete item",
		MB_YESNO|MB_ICONQUESTION)!=IDYES) return;
	//________________________________________________________Delete;
	Sql::SqlConnection conn;
	wstring cmd;
	const int item_id= lvMain.Items[selectedIndex].Data; //Get the Primary Key; 
	int rows = 0;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		if(toolbMain.IsButtonEnabled(IDM_CLIENT)==false)
			Sys::Format(cmd, L"DELETE FROM client WHERE client_id= %d", item_id);
		else if(toolbMain.IsButtonEnabled(IDM_EMPLOYEE)==false)
			Sys::Format(cmd, L"DELETE FROM employee WHERE employee_id= %d", item_id);
		else return;
		rows = conn.ExecuteNonQuery(cmd);
		if (rows!=1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"ERROR: number of deleted rows", MB_OK | MB_ICONERROR);
		}
	}
	catch (Sql::SqlException ex)
	{
		this->MessageBox(ex.GetDescription(), L"ERROR", MB_OK | MB_ICONERROR);
	}
	fillListView();
	toolbMain.EnableButton(IDM_DELETE,false);
}

void PeopleMng::insertItem()
{
	toolbMain.EnableButton(IDM_INSERT,false);
	if(toolbMain.IsButtonEnabled(IDM_CLIENT)==false)
	{
		ClientDlg client_dlg;
		client_dlg.BeginDialog(hWnd);
	}
	else if(toolbMain.IsButtonEnabled(IDM_EMPLOYEE)==false)
	{
		EmployeeDlg employee_dlg;
		employee_dlg.BeginDialog(hWnd);
	}
	else return;
	fillListView();
	toolbMain.EnableButton(IDM_INSERT,true);
}

void PeopleMng::editItem()
{
	toolbMain.EnableButton(IDM_EDIT,false);
	const int selectedIndex= lvMain.GetSelectedIndex();
	if(selectedIndex<0) return;
	//____________________________________________________Ask the user
	if(this->MessageBox(L"Are you sure you want to modify the selected item?", L"Edit item", 
		MB_YESNO|MB_ICONQUESTION)!=IDYES) return;
	//___________________________________________________Edit
	const int item_id= lvMain.Items[selectedIndex].Data;
	if(toolbMain.IsButtonEnabled(IDM_CLIENT)==false)
	{
		ClientDlg client_dlg;
		client_dlg.client_id= item_id;
		client_dlg.BeginDialog(hWnd);
	}
	else if(toolbMain.IsButtonEnabled(IDM_EMPLOYEE)==false)
	{
		EmployeeDlg employee_dlg;
		employee_dlg.employee_id= item_id;
		employee_dlg.BeginDialog(hWnd);
	}
	else return;
	fillListView();
	toolbMain.EnableButton(IDM_EDIT,true);
}
/*
	if(toolbMain.IsButtonEnabled(IDM_CLIENT)==false)
	else if(toolbMain.IsButtonEnabled(IDM_EMPLOYEE)==false)
	else return;
*/


void PeopleMng::Window_Size(Win::Event& e)
{
}

