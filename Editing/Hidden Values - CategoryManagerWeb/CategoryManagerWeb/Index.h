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
	void updateListView();
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::ListView lvCategory;
	Web::Button btInsert;
	Web::Button btEdit;
	Web::HiddenValue hdCategoryID;
protected:
	void InitializeGui()
	{
		this->ID=L"Index";
		this->Title=L"Index";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"Index.js";
		this->lvCategory.ID=L"lvCategory";
		this->btInsert.ID=L"btInsert";
		this->btEdit.ID=L"btEdit";
		this->hdCategoryID.ID=L"hdCategoryID";
		this->btInsert.Text=L"Insert";
		this->btEdit.Text=L"Edit";
		this->lvCategory.cssClass=L"Data";
		this->lvCategory.BeginHtml=L"<table><tr style=\"vertical-align:top\"><td>";
		this->lvCategory.EndHtml=L"</td>";
		this->lvCategory.Height=10;
		this->lvCategory.FontSize=16;
		this->btInsert.css.width=-100;
		this->btInsert.BeginHtml=L"<td>";
		this->btInsert.EndHtml=L"<br />";
		this->btEdit.css.width=-100;
		this->btEdit.EndHtml=L"</td></tr></table>";
		this->AddChild(lvCategory);
		this->AddChild(btInsert);
		this->AddChild(btEdit);
		this->AddChild(hdCategoryID);
	}
	//_________________________________________________
	void btInsert_Click(Web::HttpConnector& h);
	void btEdit_Click(Web::HttpConnector& h);
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
		if (btInsert.IsEvent(h, HTML_CLICK)) {btInsert_Click(h);}
		if (btEdit.IsEvent(h, HTML_CLICK)) {btEdit_Click(h);}
	}
};
