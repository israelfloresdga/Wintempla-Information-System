#pragma once   //_____________________________________________ Index.h  
#include "resource.h"

class Index: public Web::Page
{
public:
	Index()
	{
	}
	~Index()
	{
	}
	void fillListView();
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::ListView lvItems;
	Web::Button btInsert;
protected:
	void InitializeGui()
	{
		this->ID=L"Index";
		this->Title=L"Index";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"Index.js";
		this->lvItems.ID=L"lvItems";
		this->btInsert.ID=L"btInsert";
		this->btInsert.Text=L"Insert";
		this->lvItems.cssClass=L"Data";
		this->lvItems.BeginHtml=L"<table><tr style= \"vertical-align:top\"><td>";
		this->lvItems.EndHtml=L"</td>";
		this->lvItems.Height=10;
		this->lvItems.FontSize=16;
		this->btInsert.BeginHtml=L"<td>";
		this->btInsert.EndHtml=L"</td></tr></table>";
		this->AddChild(lvItems);
		this->AddChild(btInsert);
	}
	//_________________________________________________
	void btInsert_Click(Web::HttpConnector& h);
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
		if (btInsert.IsEvent(h, HTML_CLICK)) {btInsert_Click(h);}
	}
};
