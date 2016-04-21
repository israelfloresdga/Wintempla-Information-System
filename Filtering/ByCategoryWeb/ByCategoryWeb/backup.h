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
	void updateView(); 
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::DropDownList ddCategory;
	Web::ListView lvItem;
protected:
	void InitializeGui()
	{
		this->ID=L"Index";
		this->Title=L"Index";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"Index.js";
		this->ddCategory.ID=L"ddCategory";
		this->lvItem.ID=L"lvItem";
		this->ddCategory.BeginHtml=L"Category&nbsp;";
		this->ddCategory.EndHtml=L"<br/><br/>";
		this->ddCategory.OnChange=true;
		this->lvItem.cssClass=L"Data";
		this->lvItem.Height=10;
		this->lvItem.FontSize=16;
		this->AddChild(ddCategory);
		this->AddChild(lvItem);
	}
	//_________________________________________________
	void ddCategory_Change(Web::HttpConnector& h);
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
		if (ddCategory.IsEvent(h, HTML_CHANGE)) {ddCategory_Change(h);}
	}
};
