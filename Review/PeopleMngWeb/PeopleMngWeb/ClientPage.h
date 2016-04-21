#pragma once   //_____________________________________________ ClientPage.h  
#include "resource.h"

class ClientPage: public Web::Page
{
public:
	ClientPage()
	{
		client_id= -1;
	}
	~ClientPage()
	{
	}
	int client_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::HiddenValue hdClientID;
	Web::Textbox tbxFirst_name;
	Web::Textbox tbxLast_name;
	Web::DateTimeBox dtboxBirthdate;
	Web::Textbox tbxCity;
	Web::Button btOK;
	Web::Button btCancel;
protected:
	void InitializeGui()
	{
		this->ID=L"ClientPage";
		this->Title=L"ClientPage";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"ClientPage.js";
		this->hdClientID.ID=L"hdClientID";
		this->tbxFirst_name.ID=L"tbxFirst_name";
		this->tbxLast_name.ID=L"tbxLast_name";
		this->dtboxBirthdate.ID=L"dtboxBirthdate";
		this->tbxCity.ID=L"tbxCity";
		this->btOK.ID=L"btOK";
		this->btCancel.ID=L"btCancel";
		this->btOK.Text=L"OK";
		this->btCancel.Text=L"Cancel";
		this->hdClientID.Data=L"-1";
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
		this->dtboxBirthdate.BeginHtml=L"<tr><td style=\"text-align:left\">Birthdate</td><td>";
		this->dtboxBirthdate.EndHtml=L"</td><td>&nbsp;</td></tr>";
		this->dtboxBirthdate.CssFile=L"cyan.css";
		this->tbxCity.css.width=-100;
		this->tbxCity.BeginHtml=L"<tr><td style=\"text-align:left\">City</td><td>";
		this->tbxCity.EndHtml=L"</td><td>&nbsp;</td></tr></table>";
		this->tbxCity.RowCount=1;
		this->tbxCity.ColCount=32;
		this->tbxCity.MaxLength=32;
		this->btOK.BeginHtml=L"</tr><hr/><tr><td>";
		this->btOK.EndHtml=L"</td>";
		this->btCancel.BeginHtml=L"<td>";
		this->btCancel.EndHtml=L"</td></tr></table>";
		this->AddChild(hdClientID);
		this->AddChild(tbxFirst_name);
		this->AddChild(tbxLast_name);
		this->AddChild(dtboxBirthdate);
		this->AddChild(tbxCity);
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
