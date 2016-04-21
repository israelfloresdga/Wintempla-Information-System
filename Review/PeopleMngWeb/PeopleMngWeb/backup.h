#pragma once   //_____________________________________________ tmp.h  
#include "resource.h"

class tmp: public Web::Page
{
public:
	tmp()
	{
	}
	~tmp()
	{
	}
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
protected:
	void InitializeGui()
	{
		this->ID=L"tmp";
		this->Title=L"tmp";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"tmp.js";
	}
	//_________________________________________________
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
	}
};
