#include "stdafx.h"  //________________________________________ Login.cpp
#include "Login.h"
#include "LoginDlg.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	Login app;
	return app.BeginDialog(IDI_LOGIN, hInstance);
}

void Login::Window_Open(Win::Event& e)
{
	LoginDlg dlg;
	if(dlg.BeginDialog(hWnd)==TRUE) //____________________Give Access
	{
		this->Text= L"Welcome";
		this->Text+= dlg.tbxUsername.Text;
	}
	else
	{
		this->Destroy(); //_______________________________Deny Access
	}
	//____________________________________________________lvEmployee
	lvEmployee.Cols.Add(0, LVCFMT_LEFT, 100, L"First Name");
	lvEmployee.Cols.Add(1, LVCFMT_LEFT, 100, L"Last Name");
	lvEmployee.Cols.Add(2, LVCFMT_RIGHT, 100, L"Username");
	/*
	//____________________________________________________
	Sql::SqlConnection conn;
	wstring sqlcmd;
	try
	{
		conn.OpenSession(hWnd,CONNECTION_STRING);
		//_______________________________________________Is Admin?
		Sys::Format(sqlcmd,...);
		const bool isAdmin= conn.GetBool(sqlcmd);
		//
		if(isAdmin==true)
		{
			...
		}
		else
		{
			...
		}
	}
	catch(Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(),L"ERROR",MB_OK|MB_ICONERROR);
	}*/
}