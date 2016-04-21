#pragma once   //_____________________________________________ EmployeePage.h  
#include "resource.h"

class EmployeePage: public Web::Page
{
public:
	EmployeePage()
	{
		employee_id= -1;
	}
	~EmployeePage()
	{
	}
	int employee_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::HiddenValue hdEmployeeID;
	Web::Textbox tbxFirst_name;
	Web::Textbox tbxLast_name;
	Web::Textbox tbxUsername;
	Web::Textbox tbxUser_pass;
	Web::Textbox tbxPhone;
	Web::CheckBox ckIs_admi;
	Web::Button btOK;
	Web::Button btCancel;
	Web::Textbox tbxUser_pass_retype;
protected:
	void InitializeGui()
	{
		this->ID=L"EmployeePage";
		this->Title=L"EmployeePage";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"EmployeePage.js";
		this->hdEmployeeID.ID=L"hdEmployeeID";
		this->tbxFirst_name.ID=L"tbxFirst_name";
		this->tbxLast_name.ID=L"tbxLast_name";
		this->tbxUsername.ID=L"tbxUsername";
		this->tbxUser_pass.ID=L"tbxUser_pass";
		this->tbxPhone.ID=L"tbxPhone";
		this->ckIs_admi.ID=L"ckIs_admi";
		this->btOK.ID=L"btOK";
		this->btCancel.ID=L"btCancel";
		this->tbxUser_pass_retype.ID=L"tbxUser_pass_retype";
		this->ckIs_admi.Text=L"Is admi";
		this->btOK.Text=L"OK";
		this->btCancel.Text=L"Cancel";
		this->hdEmployeeID.Data=L"-1";
		this->tbxFirst_name.css.width=-100;
		this->tbxFirst_name.BeginHtml=L"<table><tr><td style=\"text-align:left\">First name</td><td>";
		this->tbxFirst_name.EndHtml=L"</td>";
		this->tbxFirst_name.RowCount=1;
		this->tbxFirst_name.ColCount=32;
		this->tbxFirst_name.MaxLength=32;
		this->tbxLast_name.css.width=-100;
		this->tbxLast_name.BeginHtml=L"<tr><td style=\"text-align:left\">Last name</td><td>";
		this->tbxLast_name.EndHtml=L"</td>";
		this->tbxLast_name.RowCount=1;
		this->tbxLast_name.ColCount=32;
		this->tbxLast_name.MaxLength=32;
		this->tbxUsername.css.width=-100;
		this->tbxUsername.BeginHtml=L"<tr><td style=\"text-align:left\">Username</td><td>";
		this->tbxUsername.EndHtml=L"</td><td>&nbsp;</td></tr>";
		this->tbxUsername.RowCount=1;
		this->tbxUsername.ColCount=32;
		this->tbxUsername.MaxLength=32;
		this->tbxUser_pass.css.width=-100;
		this->tbxUser_pass.BeginHtml=L"<tr><td style=\"text-align:left\">Password</td><td>";
		this->tbxUser_pass.EndHtml=L"</td><td>&nbsp;</td></tr>";
		this->tbxUser_pass.RowCount=1;
		this->tbxUser_pass.ColCount=32;
		this->tbxUser_pass.MaxLength=32;
		this->tbxUser_pass.Password=true;
		this->tbxPhone.css.width=-100;
		this->tbxPhone.BeginHtml=L"<tr><td style=\"text-align:left\">Phone</td><td>";
		this->tbxPhone.EndHtml=L"</td><td>&nbsp;</td></tr>";
		this->tbxPhone.RowCount=1;
		this->tbxPhone.ColCount=16;
		this->tbxPhone.MaxLength=16;
		this->ckIs_admi.BeginHtml=L"<tr><td style=\"text-align:left\">&nbsp;</td><td>";
		this->ckIs_admi.EndHtml=L"</td><td>&nbsp;</td></tr></table>";
		this->btOK.BeginHtml=L"<hr/<tr><td>";
		this->btOK.EndHtml=L"</td>";
		this->btCancel.BeginHtml=L"<td>";
		this->btCancel.EndHtml=L"</td></tr></table>";
		this->tbxUser_pass_retype.BeginHtml=L"<tr><td style=\"text-align:left\">Retype Password</td><td>";
		this->tbxUser_pass_retype.EndHtml=L"</td><td>&nbsp;</td></tr>";
		this->tbxUser_pass_retype.RowCount=1;
		this->tbxUser_pass_retype.ColCount=16;
		this->tbxUser_pass_retype.MaxLength=32;
		this->tbxUser_pass_retype.Password=true;
		this->AddChild(hdEmployeeID);
		this->AddChild(tbxFirst_name);
		this->AddChild(tbxLast_name);
		this->AddChild(tbxUsername);
		this->AddChild(tbxUser_pass);
		this->AddChild(tbxUser_pass_retype);
		this->AddChild(tbxPhone);
		this->AddChild(ckIs_admi);
		this->AddChild(btOK);
		this->AddChild(btCancel);
	}
	//_________________________________________________
	void btOK_Click(Web::HttpConnector& h);
	void btCancel_Click(Web::HttpConnector& h);
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
		if (btOK.IsEvent(h, HTML_CLICK)) {btOK_Click(h);}
		if (btCancel.IsEvent(h, HTML_CLICK)) {btCancel_Click(h);}
	}
};
