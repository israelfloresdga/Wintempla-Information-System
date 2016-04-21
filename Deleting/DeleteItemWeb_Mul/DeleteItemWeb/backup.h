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
	Web::ListView lvItem;
	Web::Button btDelete;
protected:
	void InitializeGui()
	{
		this->ID=L"Index";
		this->Title=L"Index";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"Index.js";
		this->lvItem.ID=L"lvItem";
		this->btDelete.ID=L"btDelete";
		this->btDelete.Text=L"Delete";
		this->lvItem.cssClass=L"Data";
		this->lvItem.BeginHtml=L"<table><tr style=\"vertical-align:top\"><td>";
		this->lvItem.EndHtml=L"</td>";
		this->lvItem.Height=10;
		this->lvItem.FontSize=16;
		this->btDelete.BeginHtml=L"<td>";
		this->btDelete.EndHtml=L"</td></tr></table>";
		this->btDelete.Submit=false;
		this->btDelete.OnClick=true;
		this->AddChild(lvItem);
		this->AddChild(btDelete);
	}
	//_________________________________________________
	void btDelete_Click(Web::HttpConnector& h);
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
		if (btDelete.IsEvent(h, HTML_CLICK)) {btDelete_Click(h);}
	}
};
