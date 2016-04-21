#pragma once   //_____________________________________________ EmployeeVwPage.h  
#include "resource.h"

class EmployeeVwPage: public Web::Page
{
public:
	EmployeeVwPage()
	{
	}
	~EmployeeVwPage()
	{
	}
	void fillListView();
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::Button btInsert;
	Web::Button btEdit;
	Web::Button btDelete;
	Web::Button btHome;
	Web::ListView lvEmployee;
	Web::HiddenValue hdEmployeeID;
protected:
	void InitializeGui()
	{
		this->ID=L"EmployeeVwPage";
		this->Title=L"EmployeeVwPage";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"EmployeeVwPage.js";
		this->btInsert.ID=L"btInsert";
		this->btEdit.ID=L"btEdit";
		this->btDelete.ID=L"btDelete";
		this->btHome.ID=L"btHome";
		this->lvEmployee.ID=L"lvEmployee";
		this->hdEmployeeID.ID=L"hdEmployeeID";
		this->btInsert.Text=L"Insert";
		this->btEdit.Text=L"Edit";
		this->btDelete.Text=L"Delete";
		this->btHome.Text=L"Home";
		this->btDelete.Submit=false;
		this->btDelete.OnClick=true;
		this->btHome.EndHtml=L"<hr/>";
		this->lvEmployee.cssClass=L"Data";
		this->lvEmployee.Height=10;
		this->lvEmployee.FontSize=16;
		this->AddChild(btInsert);
		this->AddChild(btEdit);
		this->AddChild(btDelete);
		this->AddChild(btHome);
		this->AddChild(lvEmployee);
		this->AddChild(hdEmployeeID);
	}
	//_________________________________________________
	void btInsert_Click(Web::HttpConnector& h);
	void btEdit_Click(Web::HttpConnector& h);
	void btDelete_Click(Web::HttpConnector& h);
	void btHome_Click(Web::HttpConnector& h);
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
		if (btInsert.IsEvent(h, HTML_CLICK)) {btInsert_Click(h);}
		if (btEdit.IsEvent(h, HTML_CLICK)) {btEdit_Click(h);}
		if (btDelete.IsEvent(h, HTML_CLICK)) {btDelete_Click(h);}
		if (btHome.IsEvent(h, HTML_CLICK)) {btHome_Click(h);}
	}
};
