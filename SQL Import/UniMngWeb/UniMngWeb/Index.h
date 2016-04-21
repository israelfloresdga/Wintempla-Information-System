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
	Web::ParentNode pndMain;
	Web::Image imgLogo;
	Web::ImageLink imkDepartment;
	Web::ImageLink imkClassroom;
	Web::ImageLink imkCourse;
	Web::ImageLink imkPeriod;
	Web::ImageLink imkProfessor;
	Web::ImageLink imkSchedule;
	Web::ImageLink imkTime_block;
protected:
	void InitializeGui()
	{
		this->ID=L"Index";
		this->Title=L"Index";
		this->CssFile=L"gray.css";
		this->JavascriptFile=L"Index.js";
		this->pndMain.ID=L"pndMain";
		this->imgLogo.ID=L"imgLogo";
		this->imkDepartment.ID=L"imkDepartment";
		this->imkClassroom.ID=L"imkClassroom";
		this->imkCourse.ID=L"imkCourse";
		this->imkPeriod.ID=L"imkPeriod";
		this->imkProfessor.ID=L"imkProfessor";
		this->imkSchedule.ID=L"imkSchedule";
		this->imkTime_block.ID=L"imkTime_block";
		this->imgLogo.Text=L"University";
		this->imkDepartment.Text=L"View and Manage Departments";
		this->imkClassroom.Text=L"View and Manage Classrooms";
		this->imkCourse.Text=L"View and Manage Courses";
		this->imkPeriod.Text=L"View and Manage Periods";
		this->imkProfessor.Text=L"View and Manage Professors";
		this->imkSchedule.Text=L"View and Manage Schedules";
		this->imkTime_block.Text=L"View and Manage Time blocks";
		this->pndMain.AddChild(imgLogo);
		this->pndMain.AddChild(imkClassroom);
		this->pndMain.AddChild(imkCourse);
		this->pndMain.AddChild(imkDepartment);
		this->pndMain.AddChild(imkPeriod);
		this->pndMain.AddChild(imkProfessor);
		this->pndMain.AddChild(imkSchedule);
		this->pndMain.AddChild(imkTime_block);
		this->pndMain.Type=HTML_PND_ONE_COLUMN_TABLE;
		this->imgLogo.css.width=-100;
		this->imgLogo.css.border_width=5;
		this->imgLogo.css.text_align=Web::CssType::TextAlignCenter;
		this->imgLogo.css.border_style=Web::CssType::BorderStyleSolid;
		this->imgLogo.src=L"university.gif";
		this->imkDepartment.BeginHtml=L"Department:<br/>";
		this->imkDepartment.src=L"department.png";
		this->imkDepartment.href=L"DepartmentVwPage";
		this->imkDepartment.imageCssClass=L"Clean";
		this->imkClassroom.BeginHtml=L"Classroom:<br/>";
		this->imkClassroom.src=L"classroom.png";
		this->imkClassroom.href=L"ClassroomVwPage";
		this->imkClassroom.imageCssClass=L"Clean";
		this->imkCourse.BeginHtml=L"Course:<br/>";
		this->imkCourse.src=L"course.png";
		this->imkCourse.href=L"CourseVwPage";
		this->imkCourse.imageCssClass=L"Clean";
		this->imkPeriod.BeginHtml=L"Period:<br/>";
		this->imkPeriod.src=L"period.png";
		this->imkPeriod.href=L"PeriodVwPage";
		this->imkPeriod.imageCssClass=L"Clean";
		this->imkProfessor.BeginHtml=L"Professor:<br/>";
		this->imkProfessor.src=L"professor.png";
		this->imkProfessor.href=L"ProfessorVwPage";
		this->imkProfessor.imageCssClass=L"Clean";
		this->imkSchedule.BeginHtml=L"Schedule:<br/>";
		this->imkSchedule.src=L"schedule.png";
		this->imkSchedule.href=L"ScheduleVwPage";
		this->imkSchedule.imageCssClass=L"Clean";
		this->imkTime_block.BeginHtml=L"Time block:<br/>";
		this->imkTime_block.src=L"time_block.png";
		this->imkTime_block.href=L"TimeBlockVwPage";
		this->imkTime_block.imageCssClass=L"Clean";
		this->AddChild(pndMain);
	}
	//_________________________________________________
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
	}
};
