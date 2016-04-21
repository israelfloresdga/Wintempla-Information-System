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
	updateItems();
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::DropDownList ddCategory;
	Web::DropDownList ddBrand;
	Web::ListView lvItem;
protected:
	void InitializeGui()
	{
		this->ID=L"Index";
		this->Title=L"Seach by Both Categories";
		this->CssFile=L"green.css";
		this->JavascriptFile=L"Index.js";
		this->ddCategory.ID=L"ddCategory";
		this->ddBrand.ID=L"ddBrand";
		this->lvItem.ID=L"lvItem";
		this->ddCategory.BeginHtml=L"Category&nbsp;";
		this->ddCategory.OnChange=true;
		this->ddBrand.BeginHtml=L"Brand&nbsp;";
		this->ddBrand.EndHtml=L"<br /><br />";
		this->ddBrand.OnChange=true;
		this->lvItem.cssClass=L"Data";
		this->lvItem.Height=10;
		this->lvItem.FontSize=16;
		this->AddChild(ddCategory);
		this->AddChild(ddBrand);
		this->AddChild(lvItem);
	}
	//_________________________________________________
	void ddCategory_Change(Web::HttpConnector& h);
	void ddBrand_Change(Web::HttpConnector& h);
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
		if (ddCategory.IsEvent(h, HTML_CHANGE)) {ddCategory_Change(h);}
		if (ddBrand.IsEvent(h, HTML_CHANGE)) {ddBrand_Change(h);}
	}
};
