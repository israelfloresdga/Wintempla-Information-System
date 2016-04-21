#pragma once   //_____________________________________________ DepartmentPage.h  
#include "resource.h"

class DepartmentPage: public Web::Page
{
public:
	DepartmentPage()
	{
		department_id= -1;
	}
	~DepartmentPage()
	{
	}
	int department_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::HiddenValue hdDepartmentID;
	Web::Textbox tbxDescr;
	Web::Button btOK;
	Web::Button btCancel;
protected:
	void InitializeGui()
	{
		this->ID=L"DepartmentPage";
		this->Title=L"DepartmentPage";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"DepartmentPage.js";
		this->hdDepartmentID.ID=L"hdDepartmentID";
		this->tbxDescr.ID=L"tbxDescr";
		this->btOK.ID=L"btOK";
		this->btCancel.ID=L"btCancel";
		this->btOK.Text=L"OK";
		this->btCancel.Text=L"&nbsp;Cancel&nbsp;";
		this->hdDepartmentID.Data=L"-1";
		this->tbxDescr.css.width=-100;
		this->tbxDescr.BeginHtml=L"<table><tr><td style=\"text-align:left\">Descr</td><td>";
		this->tbxDescr.EndHtml=L"</td>";
		this->tbxDescr.RowCount=1;
		this->tbxDescr.ColCount=32;
		this->tbxDescr.MaxLength=32;
		this->btOK.css.width=-100;
		this->btOK.BeginHtml=L"<td>&nbsp;&nbsp;&nbsp;</td><td>";
		this->btOK.EndHtml=L"</td></tr>";
		this->btCancel.css.width=-100;
		this->btCancel.BeginHtml=L"<tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;&nbsp;&nbsp;</td><td>";
		this->btCancel.EndHtml=L"</td></tr></table>";
		this->AddChild(hdDepartmentID);
		this->AddChild(tbxDescr);
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
