#pragma once   //_____________________________________________ PeriodPage.h  
#include "resource.h"

class PeriodPage: public Web::Page
{
public:
	PeriodPage()
	{
		period_id= -1;
	}
	~PeriodPage()
	{
	}
	int period_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::HiddenValue hdPeriodID;
	Web::Textbox tbxDescr;
	Web::DateTimeBox dtboxBegin_date;
	Web::DateTimeBox dtboxEnd_date;
	Web::Button btOK;
	Web::Button btCancel;
protected:
	void InitializeGui()
	{
		this->ID=L"PeriodPage";
		this->Title=L"PeriodPage";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"PeriodPage.js";
		this->hdPeriodID.ID=L"hdPeriodID";
		this->tbxDescr.ID=L"tbxDescr";
		this->dtboxBegin_date.ID=L"dtboxBegin_date";
		this->dtboxEnd_date.ID=L"dtboxEnd_date";
		this->btOK.ID=L"btOK";
		this->btCancel.ID=L"btCancel";
		this->btOK.Text=L"&nbsp;OK&nbsp;";
		this->btCancel.Text=L"Cancel";
		this->hdPeriodID.Data=L"-1";
		this->tbxDescr.css.width=-100;
		this->tbxDescr.BeginHtml=L"<table><tr><td style=\"text-align:left\">Descr</td><td>";
		this->tbxDescr.EndHtml=L"</td></tr>";
		this->tbxDescr.RowCount=1;
		this->tbxDescr.ColCount=16;
		this->tbxDescr.MaxLength=16;
		this->dtboxBegin_date.BeginHtml=L"<tr><td style=\"text-align:left\">Begin date</td><td>";
		this->dtboxBegin_date.EndHtml=L"</td></tr>";
		this->dtboxBegin_date.CssFile=L"cyan.css";
		this->dtboxEnd_date.BeginHtml=L"<tr><td style=\"text-align:left\">End date</td><td>";
		this->dtboxEnd_date.EndHtml=L"</td><td>&nbsp;</td></tr></table>";
		this->dtboxEnd_date.CssFile=L"cyan.css";
		this->btOK.BeginHtml=L"&nbsp;&nbsp;&nbsp;";
		this->btOK.EndHtml=L"&nbsp;&nbsp;&nbsp;";
		this->AddChild(hdPeriodID);
		this->AddChild(tbxDescr);
		this->AddChild(dtboxBegin_date);
		this->AddChild(dtboxEnd_date);
		this->AddChild(btOK);
		this->AddChild(btCancel);
	}
	//_________________________________________________
	void btOK_Click(Web::HttpConnector& h);
	void btCancel_Click(Web::HttpConnector& h);
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
		if (btOK.IsEvent(h, HTML_CLICK)) {btOK_Click(h);}
		if (btCancel.IsEvent(h, HTML_CLICK)) {btCancel_Click(h);}
	}
};
