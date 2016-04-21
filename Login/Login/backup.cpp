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
	
	//________________________________________________________ lv1
	lv1.Cols.Add(0, LVCFMT_LEFT, 100, L"Day");
	lv1.Cols.Add(1, LVCFMT_RIGHT, 200, L"Activity");
	lv1.Items.Add(0, L"Monday");
	lv1.Items[0][1].Text = L"Math Class";
}

