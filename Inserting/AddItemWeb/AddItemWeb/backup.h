#pragma once   //_____________________________________________ ItemPage.h  
#include "resource.h"

class ItemPage: public Web::Page
{
public:
	ItemPage()
	{
	}
	~ItemPage()
	{
	}
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::Textbox tbxName;
	Web::Textbox tbxModel;
	Web::DropDownList ddBrand;
	Web::DropDownList ddCategory;
	Web::Button btOk;
protected:
	void InitializeGui()
	{
		this->ID=L"ItemPage";
		this->Title=L"ItemPage";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"ItemPage.js";
		this->tbxName.ID=L"tbxName";
		this->tbxModel.ID=L"tbxModel";
		this->ddBrand.ID=L"ddBrand";
		this->ddCategory.ID=L"ddCategory";
		this->btOk.ID=L"btOk";
		this->btOk.Text=L"Ok";
		this->tbxName.css.width=-100;
		this->tbxName.BeginHtml=L"<table><tr><td>Name</td><td>";
		this->tbxName.EndHtml=L"<td></tr>";
		this->tbxName.RowCount=1;
		this->tbxName.ColCount=16;
		this->tbxName.MaxLength=32;
		this->tbxModel.css.width=-100;
		this->tbxModel.BeginHtml=L"<tr><td>Model</td><td>";
		this->tbxModel.EndHtml=L"</td></tr>";
		this->tbxModel.RowCount=1;
		this->tbxModel.ColCount=16;
		this->tbxModel.MaxLength=32;
		this->ddBrand.css.width=-100;
		this->ddBrand.BeginHtml=L"<tr><td>Brand</td><td>";
		this->ddBrand.EndHtml=L"</td></tr>";
		this->ddCategory.css.width=-100;
		this->ddCategory.BeginHtml=L"<tr><td>Category</td><td>";
		this->ddCategory.EndHtml=L"</td></tr></table>";
		this->AddChild(tbxName);
		this->AddChild(tbxModel);
		this->AddChild(ddBrand);
		this->AddChild(ddCategory);
		this->AddChild(btOk);
	}
	//_________________________________________________
	void btOk_Click(Web::HttpConnector& h);
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
		if (btOk.IsEvent(h, HTML_CLICK)) {btOk_Click(h);}
	}
};
