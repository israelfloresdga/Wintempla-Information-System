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
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::ListView lvCategory;
protected:
	void InitializeGui()
	{
		this->ID=L"Index";
		this->Title=L"Index";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"Index.js";
		this->lvCategory.ID=L"lvCategory";
		this->lvCategory.cssClass=L"Data";
		this->lvCategory.Height=10;
		this->lvCategory.FontSize=16;
		this->AddChild(lvCategory);
	}
	//_________________________________________________
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
	}
};
