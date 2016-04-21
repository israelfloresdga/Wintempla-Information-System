#pragma once   //_____________________________________________ TimeBlockPage.h  
#include "resource.h"

class TimeBlockPage: public Web::Page
{
public:
	TimeBlockPage()
	{
		time_block_id= -1;
	}
	~TimeBlockPage()
	{
	}
	int time_block_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::HiddenValue hdTime_blockID;
	Web::Textbox tbxDescr;
	Web::CheckBox ckMonday;
	Web::CheckBox ckTuesday;
	Web::CheckBox ckWednesday;
	Web::CheckBox ckThursday;
	Web::CheckBox ckFriday;
	Web::CheckBox ckSaturday;
	Web::Button btOK;
	Web::Button btCancel;
protected:
	void InitializeGui()
	{
		this->ID=L"TimeBlockPage";
		this->Title=L"TimeBlockPage";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"TimeBlockPage.js";
		this->hdTime_blockID.ID=L"hdTime_blockID";
		this->tbxDescr.ID=L"tbxDescr";
		this->ckMonday.ID=L"ckMonday";
		this->ckTuesday.ID=L"ckTuesday";
		this->ckWednesday.ID=L"ckWednesday";
		this->ckThursday.ID=L"ckThursday";
		this->ckFriday.ID=L"ckFriday";
		this->ckSaturday.ID=L"ckSaturday";
		this->btOK.ID=L"btOK";
		this->btCancel.ID=L"btCancel";
		this->ckMonday.Text=L"On Monday";
		this->ckTuesday.Text=L"On Tuesday";
		this->ckWednesday.Text=L"On Wednesday";
		this->ckThursday.Text=L"On Thursday";
		this->ckFriday.Text=L"On Friday";
		this->ckSaturday.Text=L"On Saturday";
		this->btOK.Text=L"&nbsp;&nbsp;OK&nbsp;&nbsp;";
		this->btCancel.Text=L"&nbsp;Cancel&nbsp;";
		this->hdTime_blockID.Data=L"-1";
		this->tbxDescr.css.width=-100;
		this->tbxDescr.BeginHtml=L"<table><tr><td style=\"text-align:left\">Descr</td><td>";
		this->tbxDescr.EndHtml=L"</td></tr>";
		this->tbxDescr.RowCount=1;
		this->tbxDescr.ColCount=16;
		this->tbxDescr.MaxLength=16;
		this->ckMonday.BeginHtml=L"<tr><td style=\"text-align:left\">&nbsp;</td><td>";
		this->ckMonday.EndHtml=L"</td></tr>";
		this->ckTuesday.BeginHtml=L"<tr><td style=\"text-align:left\">&nbsp;</td><td>";
		this->ckTuesday.EndHtml=L"</td><td>&nbsp;</td></tr>";
		this->ckWednesday.BeginHtml=L"<tr><td style=\"text-align:left\">&nbsp;</td><td>";
		this->ckWednesday.EndHtml=L"</td><td>&nbsp;</td></tr>";
		this->ckThursday.BeginHtml=L"<tr><td style=\"text-align:left\">&nbsp;</td><td>";
		this->ckThursday.EndHtml=L"</td><td>&nbsp;</td></tr>";
		this->ckFriday.BeginHtml=L"<tr><td style=\"text-align:left\">&nbsp;</td><td>";
		this->ckFriday.EndHtml=L"</td><td>&nbsp;</td></tr>";
		this->ckSaturday.BeginHtml=L"<tr><td style=\"text-align:left\">&nbsp;</td><td>";
		this->ckSaturday.EndHtml=L"</td><td>&nbsp;</td></tr></table>";
		this->btOK.BeginHtml=L"<hr/>";
		this->btOK.EndHtml=L"&nbsp;&nbsp;&nbsp;";
		this->btCancel.EndHtml=L"&nbsp;&nbsp;&nbsp;";
		this->AddChild(hdTime_blockID);
		this->AddChild(tbxDescr);
		this->AddChild(ckMonday);
		this->AddChild(ckTuesday);
		this->AddChild(ckWednesday);
		this->AddChild(ckThursday);
		this->AddChild(ckFriday);
		this->AddChild(ckSaturday);
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
