#pragma once   //_____________________________________________ ClassroomPage.h  
#include "resource.h"

class ClassroomPage: public Web::Page
{
public:
	ClassroomPage()
	{
		classroom_id= -1;
	}
	~ClassroomPage()
	{
	}
	int classroom_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::HiddenValue hdClassroomID;
	Web::Textbox tbxDescr;
	Web::Textbox tbxSeat_count;
	Web::CheckBox ckHas_projector;
	Web::Button btOK;
	Web::Button btCancel;
	Web::Textbox tbxBuilding;
protected:
	void InitializeGui()
	{
		this->ID=L"ClassroomPage";
		this->Title=L"ClassroomPage";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"ClassroomPage.js";
		this->hdClassroomID.ID=L"hdClassroomID";
		this->tbxDescr.ID=L"tbxDescr";
		this->tbxSeat_count.ID=L"tbxSeat_count";
		this->ckHas_projector.ID=L"ckHas_projector";
		this->btOK.ID=L"btOK";
		this->btCancel.ID=L"btCancel";
		this->tbxBuilding.ID=L"tbxBuilding";
		this->ckHas_projector.Text=L"Has projector";
		this->btOK.Text=L"OK";
		this->btCancel.Text=L"Cancel";
		this->hdClassroomID.Data=L"-1";
		this->tbxDescr.css.width=-100;
		this->tbxDescr.css.text_align=Web::CssType::TextAlignRight;
		this->tbxDescr.BeginHtml=L"<table><tr><td style=\"text-align:left\">Classroom</td><td>";
		this->tbxDescr.EndHtml=L"</td>";
		this->tbxDescr.RowCount=1;
		this->tbxDescr.ColCount=16;
		this->tbxDescr.MaxLength=32;
		this->tbxSeat_count.css.width=-100;
		this->tbxSeat_count.css.text_align=Web::CssType::TextAlignRight;
		this->tbxSeat_count.BeginHtml=L"<tr><td style=\"text-align:left\">Number of seats</td><td>";
		this->tbxSeat_count.EndHtml=L"</td></tr>";
		this->tbxSeat_count.RowCount=1;
		this->tbxSeat_count.ColCount=16;
		this->tbxSeat_count.MaxLength=32;
		this->ckHas_projector.css.text_align=Web::CssType::TextAlignCenter;
		this->ckHas_projector.BeginHtml=L"<tr><td style=\"text-align:left\">&nbsp;</td><td>";
		this->ckHas_projector.EndHtml=L"</td><td>&nbsp;</td></tr></table><hr/>";
		this->tbxBuilding.css.text_align=Web::CssType::TextAlignRight;
		this->tbxBuilding.BeginHtml=L"<tr><td style=\"text-align:left\">Building</td><td>";
		this->tbxBuilding.EndHtml=L"</td><td>&nbsp;</td></tr></table>";
		this->tbxBuilding.RowCount=1;
		this->tbxBuilding.ColCount=16;
		this->tbxBuilding.MaxLength=32;
		this->AddChild(hdClassroomID);
		this->AddChild(tbxDescr);
		this->AddChild(tbxSeat_count);
		this->AddChild(tbxBuilding);
		this->AddChild(ckHas_projector);
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
