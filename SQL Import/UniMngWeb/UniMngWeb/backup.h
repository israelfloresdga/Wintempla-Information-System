#pragma once   //_____________________________________________ SchedulePage.h  
#include "resource.h"

class SchedulePage: public Web::Page
{
public:
	SchedulePage()
	{
		schedule_id= -1;
	}
	~SchedulePage()
	{
	}
	int schedule_id;
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Web::HiddenValue hdSchedule;
	Web::DropDownList ddProfessor;
	Web::DropDownList ddCourse;
	Web::DropDownList ddPeriod;
	Web::DropDownList ddTime_block;
	Web::DropDownList ddClassroom;
	Web::Button btOK;
	Web::Button btCancel;
protected:
	void InitializeGui()
	{
		this->ID=L"SchedulePage";
		this->Title=L"SchedulePage";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"SchedulePage.js";
		this->hdSchedule.ID=L"hdSchedule";
		this->ddProfessor.ID=L"ddProfessor";
		this->ddCourse.ID=L"ddCourse";
		this->ddPeriod.ID=L"ddPeriod";
		this->ddTime_block.ID=L"ddTime_block";
		this->ddClassroom.ID=L"ddClassroom";
		this->btOK.ID=L"btOK";
		this->btCancel.ID=L"btCancel";
		this->btOK.Text=L"&nbsp;&nbsp;OK&nbsp;&nbsp;";
		this->btCancel.Text=L"&nbsp;Cancel&nbsp;";
		this->hdSchedule.Data=L"-1";
		this->ddProfessor.css.width=-100;
		this->ddProfessor.BeginHtml=L"<table><tr><td style=\"text-align:left\">Professor</td><td>";
		this->ddProfessor.EndHtml=L"</td></tr>";
		this->ddCourse.css.width=-100;
		this->ddCourse.BeginHtml=L"<tr><td style=\"text-align:left\">Course</td><td>";
		this->ddCourse.EndHtml=L"</td></tr>";
		this->ddPeriod.css.width=-100;
		this->ddPeriod.BeginHtml=L"<tr><td style=\"text-align:left\">Period</td><td>";
		this->ddPeriod.EndHtml=L"</td><td>&nbsp;</td></tr>";
		this->ddTime_block.css.width=-100;
		this->ddTime_block.BeginHtml=L"<tr><td style=\"text-align:left\">Time block</td><td>";
		this->ddTime_block.EndHtml=L"</td><td>&nbsp;</td></tr>";
		this->ddClassroom.css.width=-100;
		this->ddClassroom.BeginHtml=L"<tr><td style=\"text-align:left\">Classroom</td><td>";
		this->ddClassroom.EndHtml=L"</td><td>&nbsp;</td></tr></table>";
		this->btOK.BeginHtml=L"<hr/>";
		this->btOK.EndHtml=L"&nbsp;&nbsp;&nbsp;";
		this->AddChild(hdSchedule);
		this->AddChild(ddProfessor);
		this->AddChild(ddCourse);
		this->AddChild(ddPeriod);
		this->AddChild(ddTime_block);
		this->AddChild(ddClassroom);
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
