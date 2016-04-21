#include "stdafx.h"  //_____________________________________________ ScheduleDlg.cpp
#include "ScheduleDlg.h"

void ScheduleDlg::Window_Open(Win::Event& e)
{
	this->Text=L"Schedule";
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		conn.ExecuteSelect(L"SELECT professor_id, last_name FROM professor", 100, ddProfessor);
		conn.ExecuteSelect(L"SELECT course_id, descr FROM course", 100, ddCourse);
		conn.ExecuteSelect(L"SELECT period_id, descr FROM period", 100, ddPeriod);
		conn.ExecuteSelect(L"SELECT time_block_id, descr FROM time_block", 100, ddTime_block);
		conn.ExecuteSelect(L"SELECT classroom_id, descr FROM classroom", 100, ddClassroom);
		if (schedule_id < 0) return;
		Sys::Format(cmd, L"SELECT professor_id, course_id, period_id, time_block_id, classroom_id FROM schedule WHERE schedule_id=%d", schedule_id);
		conn.ExecuteSelect(cmd);
		conn.BindColumn(1, ddProfessor);
		conn.BindColumn(2, ddCourse);
		conn.BindColumn(3, ddPeriod);
		conn.BindColumn(4, ddTime_block);
		conn.BindColumn(5, ddClassroom);
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

void ScheduleDlg::btOK_Click(Win::Event& e)
{
	//_____________________________________________________________ Validate
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
		conn.OpenSession(hWnd, CONNECTION_STRING);
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
	this->EndDialog(TRUE);
}

void ScheduleDlg::btCancel_Click(Win::Event& e)
{
	this->EndDialog(FALSE);
}

