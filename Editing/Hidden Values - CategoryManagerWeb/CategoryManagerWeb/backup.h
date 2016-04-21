#pragma once   //_____________________________________________ CategoryPage.h  
#include "resource.h"


class CategoryPage: public Web::Page
{
public:
	CategoryPage()
	{
		category_id= -1;
	}
	~CategoryPage()
	{
	}
	int category_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::Textbox tbxDescr;
	Web::Button btOk;
	Web::Button btCancel;
	Web::HiddenValue hdCategoryId;
protected:
	void InitializeGui()
	{
		this->ID=L"CategoryPage";
		this->Title=L"CategoryPage";
		this->CssFile=L"purple.css";
		this->JavascriptFile=L"CategoryPage.js";
		this->tbxDescr.ID=L"tbxDescr";
		this->btOk.ID=L"btOk";
		this->btCancel.ID=L"btCancel";
		this->hdCategoryId.ID=L"hdCategoryId";
		this->btOk.Text=L"Ok";
		this->btCancel.Text=L"Cancel";
		this->tbxDescr.BeginHtml=L"Name&nbsp;<table><tr><td>";
		this->tbxDescr.EndHtml=L"</td>";
		this->tbxDescr.RowCount=1;
		this->tbxDescr.ColCount=16;
		this->tbxDescr.MaxLength=32;
		this->btOk.css.width=-100;
		this->btOk.BeginHtml=L"<td>";
		this->btOk.EndHtml=L"</td>";
		this->btCancel.css.width=-100;
		this->btCancel.BeginHtml=L"<td>";
		this->btCancel.EndHtml=L"</td></tr><table>";
		this->AddChild(tbxDescr);
		this->AddChild(btOk);
		this->AddChild(btCancel);
		this->AddChild(hdCategoryId);
	}
	//_________________________________________________
	void btOk_Click(Web::HttpConnector& h);
	void btCancel_Click(Web::HttpConnector& h);
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
		if (btOk.IsEvent(h, HTML_CLICK)) {btOk_Click(h);}
		if (btCancel.IsEvent(h, HTML_CLICK)) {btCancel_Click(h);}
	}
};
