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
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::DropDownList ddBrand;
protected:
	void InitializeGui()
	{
		this->ID=L"Index";
		this->Title=L"Search Items by Brand";
		this->CssFile=L"green.css";
		this->JavascriptFile=L"Index.js";
		this->ddBrand.ID=L"ddBrand";
		this->ddBrand.BeginHtml=L"Brand&nbsp;";
		this->ddBrand.EndHtml=L"<br /><br />";
		this->ddBrand.OnChange=true;
		this->AddChild(ddBrand);
	}
	//_________________________________________________
	void ddBrand_Change(Web::HttpConnector& h);
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
		if (ddBrand.IsEvent(h, HTML_CHANGE)) {ddBrand_Change(h);}
	}
};
