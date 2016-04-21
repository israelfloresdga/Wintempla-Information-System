#include "stdafx.h"  //_____________________________________________ CoursePage.cpp
#include "CoursePage.h"

void CoursePage::Window_Open(Web::HttpConnector& h)
{
	this->Title=L"Course";
	course_id = Sys::Convert::ToInt(hdCourseID.Data);
	if (course_id < 0) return; 
	if (h.FirstTime == false) return;
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(cmd, L"SELECT code, descr FROM course WHERE course_id=%d", course_id);
		conn.ExecuteSelect(cmd);
		tbxCode.MaxLength=5;
		conn.BindColumn(1, tbxCode, 32);
		tbxDescr.MaxLength=32;
		conn.BindColumn(2, tbxDescr, 32);
		if (conn.Fetch() == false)
		{
			this->MessageBox(L"No data was returned", L"Error", MB_OK);
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}

void CoursePage::btCancel_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"CourseVwPage");
}

void CoursePage::btOK_Click(Web::HttpConnector& h)
{
	//_____________________________________________________________ Validate
	tr1::wregex regextbxCode(L"[A-Z]{3}[0-9]{2}");
	if (tr1::regex_match(tbxCode.Text, regextbxCode) == false)
	{
		tbxCode.ShowBalloonTip(L"Invalid Code", L"Please provide the next format CCC##", TTI_ERROR);
		return;
	}
	tr1::wregex regextbxDescr(L"[A-Za-z]+(\\s[A-Za-z]*)*");
	if (tr1::regex_match(tbxDescr.Text, regextbxDescr) == false)
	{
		tbxDescr.ShowBalloonTip(L"Invalid Descr", L"Please provide one or more characters", TTI_ERROR);
		return;
	}

	const int course_id = Sys::Convert::ToInt(hdCourseID.Data);
	Sql::StringBuilder sb(L"course", L"course_id", course_id);
	sb.Bind(L"code", tbxCode);
	sb.Bind(L"descr", tbxDescr);
	Sql::SqlConnection conn;
	int rows = 0;
	try
	{
		conn.OpenSession(NULL, CONNECTION_STRING);
		rows = conn.ExecuteNonQuery(sb.GetString());
		if (rows!=1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of affected rows", MB_OK | MB_ICONERROR);
			return;
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
		return;
	}
	h.NavigateTo(L"CourseVwPage");
}

