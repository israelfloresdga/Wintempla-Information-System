#pragma once   //_____________________________________________ ProfessorPage.h  
#include "resource.h"

class ProfessorPage: public Web::Page
{
public:
	ProfessorPage()
	{
		professor_id= -1;
	}
	~ProfessorPage()
	{
	}
	int professor_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::Textbox tbxFirst_name;
	Web::Textbox tbxLast_name;
	Web::DropDownList ddDepartment;
	Web::Textbox tbxUsername;
	Web::Textbox tbxUser_pass;
	Web::Textbox tbxUser_pass_retype;
	Web::Button btOK;
	Web::Button btCancel;
	Web::HiddenValue hdProfessorID;
protected:
	void InitializeGui()
	{
		this->ID=L"ProfessorPage";
		this->Title=L"ProfessorPage";
		this->CssFile=L"green.css";
		this->JavascriptFile=L"ProfessorPage.js";
		this->tbxFirst_name.ID=L"tbxFirst_name";
		this->tbxLast_name.ID=L"tbxLast_name";
		this->ddDepartment.ID=L"ddDepartment";
		this->tbxUsername.ID=L"tbxUsername";
		this->tbxUser_pass.ID=L"tbxUser_pass";
		this->tbxUser_pass_retype.ID=L"tbxUser_pass_retype";
		this->btOK.ID=L"btOK";
		this->btCancel.ID=L"btCancel";
		this->hdProfessorID.ID=L"hdProfessorID";
		this->btOK.Text=L"&nbsp;&nbsp;OK&nbsp;&nbsp;";
		this->btCancel.Text=L"Cancel";
		this->tbxFirst_name.css.width=-100;
		this->tbxFirst_name.BeginHtml=L"<table><tr><td style=\"text-align:left\">First name</td><td>";
		this->tbxFirst_name.EndHtml=L"</td></tr>";
		this->tbxFirst_name.RowCount=1;
		this->tbxFirst_name.ColCount=32;
		this->tbxFirst_name.MaxLength=32;
		this->tbxLast_name.css.width=-100;
		this->tbxLast_name.BeginHtml=L"<tr><td style=\"text-align:left\">Last name</td><td>";
		this->tbxLast_name.EndHtml=L"</td></tr>";
		this->tbxLast_name.RowCount=1;
		this->tbxLast_name.ColCount=32;
		this->tbxLast_name.MaxLength=32;
		this->ddDepartment.css.width=-100;
		this->ddDepartment.BeginHtml=L"<tr><td style=\"text-align:left\">Department</td><td>";
		this->ddDepartment.EndHtml=L"</td><td>&nbsp;</td></tr>";
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
		this->tbxUser_pass_retype.css.width=-100;
		this->tbxUser_pass_retype.BeginHtml=L"<tr><td style=\"text-align:left\">Retype password</td><td>";
		this->tbxUser_pass_retype.EndHtml=L"</td><td>&nbsp;</td></tr></table>";
		this->tbxUser_pass_retype.RowCount=1;
		this->tbxUser_pass_retype.ColCount=32;
		this->tbxUser_pass_retype.MaxLength=32;
		this->tbxUser_pass_retype.Password=true;
		this->btOK.BeginHtml=L"<hr/>";
		this->btOK.EndHtml=L"&nbsp;&nbsp;&nbsp;";
		this->hdProfessorID.Data=L"-1";
		this->AddChild(hdProfessorID);
		this->AddChild(tbxFirst_name);
		this->AddChild(tbxLast_name);
		this->AddChild(ddDepartment);
		this->AddChild(tbxUsername);
		this->AddChild(tbxUser_pass);
		this->AddChild(tbxUser_pass_retype);
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
