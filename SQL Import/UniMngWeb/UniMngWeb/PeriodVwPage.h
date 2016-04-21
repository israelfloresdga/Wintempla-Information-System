#pragma once   //_____________________________________________ PeriodVwPage.h  
#include "resource.h"

class PeriodVwPage: public Web::Page
{
public:
	PeriodVwPage()
	{
	}
	~PeriodVwPage()
	{
	}
	void fillListView();
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::Button btInsert;
	Web::Button btEdit;
	Web::Button btDelete;
	Web::Button btHome;
	Web::ListView lvPeriod;
	Web::HiddenValue hdPeriodID;
protected:
	void InitializeGui()
	{
		this->ID=L"PeriodVwPage";
		this->Title=L"PeriodVwPage";
		this->CssFile=L"green.css";
		this->JavascriptFile=L"PeriodVwPage.js";
		this->btInsert.ID=L"btInsert";
		this->btEdit.ID=L"btEdit";
		this->btDelete.ID=L"btDelete";
		this->btHome.ID=L"btHome";
		this->lvPeriod.ID=L"lvPeriod";
		this->hdPeriodID.ID=L"hdPeriodID";
		this->btInsert.Text=L"Insert";
		this->btEdit.Text=L"Edit";
		this->btDelete.Text=L"Delete";
		this->btHome.Text=L"Home";
		this->btInsert.EndHtml=L"&nbsp;&nbsp;&nbsp;";
		this->btEdit.EndHtml=L"&nbsp;&nbsp;&nbsp;";
		this->btDelete.EndHtml=L"&nbsp;&nbsp;&nbsp;";
		this->btDelete.Submit=false;
		this->btDelete.OnClick=true;
		this->btHome.EndHtml=L"&nbsp;&nbsp;&nbsp;<hr/>";
		this->lvPeriod.cssClass=L"Data";
		this->lvPeriod.Height=10;
		this->lvPeriod.FontSize=16;
		this->AddChild(btInsert);
		this->AddChild(btEdit);
		this->AddChild(btDelete);
		this->AddChild(btHome);
		this->AddChild(lvPeriod);
		this->AddChild(hdPeriodID);
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
