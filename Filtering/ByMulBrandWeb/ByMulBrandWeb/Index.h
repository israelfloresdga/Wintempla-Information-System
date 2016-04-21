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
	void updateItems();
	bool buildSqlQuery(wstring& sclcmd);
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::CheckBoxList clBrand;
	Web::ListView lvItems;
protected:
	void InitializeGui()
	{
		this->ID=L"Index";
		this->Title=L"By CheckBox List";
		this->CssFile=L"blue.css";
		this->JavascriptFile=L"Index.js";
		this->clBrand.ID=L"clBrand";
		this->lvItems.ID=L"lvItems";
		this->clBrand.EndHtml=L"&nbsp;&nbsp;";
		this->clBrand.OnChange=true;
		this->lvItems.cssClass=L"Data";
		this->lvItems.Height=10;
		this->lvItems.FontSize=16;
		this->AddChild(clBrand);
		this->AddChild(lvItems);
	}
	//_________________________________________________
	void clBrand_Change(Web::HttpConnector& h);
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
		if (clBrand.IsEvent(h, HTML_CHANGE)) {clBrand_Change(h);}
	}
};
