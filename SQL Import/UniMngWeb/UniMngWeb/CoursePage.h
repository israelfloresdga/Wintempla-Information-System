#pragma once   //_____________________________________________ CoursePage.h  
#include "resource.h"

class CoursePage: public Web::Page
{
public:
	CoursePage()
	{
		course_id= -1;
	}
	~CoursePage()
	{
	}
	int course_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::HiddenValue hdCourseID;
	Web::Textbox tbxCode;
	Web::Textbox tbxDescr;
	Web::Button btCancel;
	Web::Button btOK;
protected:
	void InitializeGui()
	{
		this->ID=L"CoursePage";
		this->Title=L"CoursePage";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"CoursePage.js";
		this->hdCourseID.ID=L"hdCourseID";
		this->tbxCode.ID=L"tbxCode";
		this->tbxDescr.ID=L"tbxDescr";
		this->btCancel.ID=L"btCancel";
		this->btOK.ID=L"btOK";
		this->btCancel.Text=L"&nbsp;Cancel&nbsp;";
		this->btOK.Text=L"&nbsp;OK&nbsp;";
		this->hdCourseID.Data=L"-1";
		this->tbxCode.css.width=-100;
		this->tbxCode.BeginHtml=L"<table><tr><td style=\"text-align:left\">Code</td><td>";
		this->tbxCode.EndHtml=L"</td></tr>";
		this->tbxCode.RowCount=1;
		this->tbxCode.ColCount=5;
		this->tbxCode.MaxLength=5;
		this->tbxDescr.css.width=-100;
		this->tbxDescr.BeginHtml=L"<tr><td style=\"text-align:left\">Descr</td><td>";
		this->tbxDescr.EndHtml=L"</td></tr></table>";
		this->tbxDescr.RowCount=1;
		this->tbxDescr.ColCount=32;
		this->tbxDescr.MaxLength=32;
		this->btCancel.BeginHtml=L"&nbsp;&nbsp;&nbsp;";
		this->btOK.BeginHtml=L"&nbsp;&nbsp;&nbsp;";
		this->AddChild(hdCourseID);
		this->AddChild(tbxCode);
		this->AddChild(tbxDescr);
		this->AddChild(btOK);
		this->AddChild(btCancel);
	}
	//_________________________________________________
	void btCancel_Click(Web::HttpConnector& h);
	void btOK_Click(Web::HttpConnector& h);
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
		if (btCancel.IsEvent(h, HTML_CLICK)) {btCancel_Click(h);}
		if (btOK.IsEvent(h, HTML_CLICK)) {btOK_Click(h);}
	}
};
