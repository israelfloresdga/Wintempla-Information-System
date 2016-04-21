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
	Web::Textbox tbxX;
	Web::Textbox tbxY;
	Web::Textbox tbxResult;
	Web::Button btCalculate;
protected:
	void InitializeGui()
	{
		this->ID=L"Index";
		this->Title=L"Index";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"Index.js";
		this->tbxX.ID=L"tbxX";
		this->tbxY.ID=L"tbxY";
		this->tbxResult.ID=L"tbxResult";
		this->btCalculate.ID=L"btCalculate";
		this->btCalculate.Text=L"Calculate";
		this->tbxX.EndHtml=L"+";
		this->tbxX.RowCount=1;
		this->tbxX.ColCount=16;
		this->tbxX.MaxLength=32;
		this->tbxY.EndHtml=L"=";
		this->tbxY.RowCount=1;
		this->tbxY.ColCount=16;
		this->tbxY.MaxLength=32;
		this->tbxResult.RowCount=1;
		this->tbxResult.ColCount=16;
		this->tbxResult.MaxLength=32;
		this->AddChild(tbxX);
		this->AddChild(tbxY);
		this->AddChild(tbxResult);
		this->AddChild(btCalculate);
	}
	//_________________________________________________
	void btCalculate_Click(Web::HttpConnector& h);
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
		if (btCalculate.IsEvent(h, HTML_CLICK)) {btCalculate_Click(h);}
	}
};
