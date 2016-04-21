#include "stdafx.h"  //_____________________________________________ SchedulePage.cpp
#include "SchedulePage.h"

void SchedulePage::Window_Open(Web::HttpConnector& h)
{
	this->Title=L"Schedule";
	schedule_id = Sys::Convert::ToInt(hdSchedule.Data);
	Sql::SqlConnection conn;
	wstring cmd;
	conn.OpenSession(NULL, CONNECTION_STRING);
    conn.ExecuteSelect(L"SELECT professor_id, last_name FROM professor", 100, ddProfessor);
    conn.ExecuteSelect(L"SELECT course_id, descr FROM course", 100, ddCourse);
    conn.ExecuteSelect(L"SELECT period_id, descr FROM period", 100, ddPeriod);
    conn.ExecuteSelect(L"SELECT time_block_id, descr FROM time_block", 100, ddTime_block);
    conn.ExecuteSelect(L"SELECT classroom_id, descr FROM classroom", 100, ddClassroom);
	if (schedule_id < 0) return; 
	if (h.FirstTime == false) return;
	
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		conn.ExecuteSelect(L"SELECT professor_id, last_name FROM professor", 100, ddProfessor);
		conn.ExecuteSelect(L"SELECT course_id, descr FROM course", 100, ddCourse);
		conn.ExecuteSelect(L"SELECT period_id, descr FROM period", 100, ddPeriod);
		conn.ExecuteSelect(L"SELECT time_block_id, descr FROM time_block", 100, ddTime_block);
		conn.ExecuteSelect(L"SELECT classroom_id, descr FROM classroom", 100, ddClassroom);
		Sys::Format(cmd, L"SELECT professor_id, course_id, period_id, time_block_id, classroom_id FROM schedule WHERE schedule_id=%d", schedule_id);
		/*conn.ExecuteSelect(L"SELECT professor_id, name FROM vw_Schedule", 100, ddProfessor);
		conn.ExecuteSelect(L"SELECT course_id, descr FROM vw_Course", 100, ddCourse);
		conn.ExecuteSelect(L"SELECT period_id, descr FROM vw_Period", 100, ddPeriod);
		conn.ExecuteSelect(L"SELECT time_block_id, descr FROM vw_Time_block", 100, ddTime_block);
		conn.ExecuteSelect(L"SELECT classroom_id, descr FROM vw_Classroom", 100, ddClassroom);*/
		conn.ExecuteSelect(cmd);
		conn.BindColumn(1, ddProfessor, 32);
		conn.BindColumn(2, ddCourse, 32);
		conn.BindColumn(3, ddPeriod, 32);
		conn.BindColumn(4, ddTime_block, 32);
		conn.BindColumn(5, ddClassroom, 32);
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

void SchedulePage::btOK_Click(Web::HttpConnector& h)
{
	//_____________________________________________________________ Validate

	const int schedule_id = Sys::Convert::ToInt(hdSchedule.Data);
	Sql::StringBuilder sb(L"schedule", L"schedule_id", schedule_id);
	sb.Bind(L"professor_id", ddProfessor);
	sb.Bind(L"course_id", ddCourse);
	sb.Bind(L"period_id", ddPeriod);
	sb.Bind(L"time_block_id", ddTime_block);
	sb.Bind(L"classroom_id", ddClassroom);
	Sql::SqlConnection conn;
	int rows = 0;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
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
	h.NavigateTo(L"ScheduleVwPage");
}

void SchedulePage::btCancel_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"ScheduleVwPage");
}

