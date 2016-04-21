#pragma once   //_____________________________________________ ProfessorVwPage.h  
#include "resource.h"

class ProfessorVwPage: public Web::Page
{
public:
	ProfessorVwPage()
	{
	}
	~ProfessorVwPage()
	{
	}
	void fillListView();
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::Button btInsert;
	Web::Button btEdit;
	Web::Button btDelete;
	Web::Button btHome;
	Web::ListView lvProfessor;
	Web::HiddenValue hdProfessorID;
protected:
	void InitializeGui()
	{
		this->ID=L"ProfessorVwPage";
		this->Title=L"ProfessorVwPage";
		this->CssFile=L"green.css";
		this->JavascriptFile=L"ProfessorVwPage.js";
		this->btInsert.ID=L"btInsert";
		this->btEdit.ID=L"btEdit";
		this->btDelete.ID=L"btDelete";
		this->btHome.ID=L"btHome";
		this->lvProfessor.ID=L"lvProfessor";
		this->hdProfessorID.ID=L"hdProfessorID";
		this->btInsert.Text=L"Insert";
		this->btEdit.Text=L"Edit";
		this->btDelete.Text=L"Delete";
		this->btHome.Text=L"&nbsp;Home&nbsp;";
		this->btInsert.EndHtml=L"&nbsp;&nbsp;&nbsp;";
		this->btEdit.EndHtml=L"&nbsp;&nbsp;&nbsp;";
		this->btDelete.EndHtml=L"&nbsp;&nbsp;&nbsp;";
		this->btDelete.Submit=false;
		this->btDelete.OnClick=true;
		this->btHome.EndHtml=L"<hr/>";
		this->lvProfessor.cssClass=L"Data";
		this->lvProfessor.Height=10;
		this->lvProfessor.FontSize=16;
		this->AddChild(btInsert);
		this->AddChild(btEdit);
		this->AddChild(btDelete);
		this->AddChild(btHome);
		this->AddChild(lvProfessor);
		this->AddChild(hdProfessorID);
	}
	//_________________________________________________
	void btInsert_Click(Web::HttpConnector& h);
	void btEdit_Click(Web::HttpConnector& h);
	void btDelete_Click(Web::HttpConnector& h);
	void btHome_Click(Web::HttpConnector& h);
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
		if (btInsert.IsEvent(h, HTML_CLICK)) {btInsert_Click(h);}
		if (btEdit.IsEvent(h, HTML_CLICK)) {btEdit_Click(h);}
		if (btDelete.IsEvent(h, HTML_CLICK)) {btDelete_Click(h);}
		if (btHome.IsEvent(h, HTML_CLICK)) {btHome_Click(h);}
	}
};
