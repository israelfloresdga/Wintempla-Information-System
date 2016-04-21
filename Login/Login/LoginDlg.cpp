#include "stdafx.h"  //_____________________________________________ LoginDlg.cpp
#include "LoginDlg.h"

void LoginDlg::Window_Open(Win::Event& e)
{
	this->Text= L"Login";
}

void LoginDlg::btOk_Click(Win::Event& e)
{
	if(tryCount>=3)
	{
		tbxPassword.ShowBalloonTip(L"ERROR",L"Incorrect Password",TTI_ERROR);
		this->EndDialog(FALSE);
		return;
	}
	if(tbxUsername.Text.length()<=2) 
	{
		tbxUsername.ShowBalloonTip(L"ERROR", L"The password must contain more than 2 characters", TTI_ERROR);
		return;
	}
	if(tbxPassword.Text.length()<=2)
	{
		tbxUsername.ShowBalloonTip(L"ERROR", L"The password must contain more than 2 characters", TTI_ERROR);
		return;
	}
	Sql::SqlConnection conn;
	int count= 0;
	wstring sqlcmd;
	try
	{
		conn.OpenSession(hWnd,CONNECTION_STRING);
		Sys::Format(sqlcmd,L"SELECT count(*) FROM employee WHERE username= '%s' AND user_pass= '%s'",tbxUsername.Text,tbxPassword.Text);
		if(count==1)
		{
			this->EndDialog(TRUE);
			return;
		}
		else
		{
			//...
			return;
		}
	}
	catch(Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}

void LoginDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}

