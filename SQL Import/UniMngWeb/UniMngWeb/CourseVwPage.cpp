#include "stdafx.h"  //_____________________________________________ CourseVwPage.cpp
#include "CourseVwPage.h"

void CourseVwPage::Window_Open(Web::HttpConnector& h)
{
		//________________________________________________________ lvClassroom
	lvCourse.Cols.Add(LVCFMT_LEFT, 16, L"Code");
	lvCourse.Cols.Add(LVCFMT_LEFT, 24, L"Name");
	lvCourse.MultipleSelection= false;
	if(h.FirstTime==true) fillListView();
}


void CourseVwPage::btInsert_Click(Web::HttpConnector& h)
{
	hdCourseID.Data= L"-1";
	h.NavigateTo(L"CoursePage");
	fillListView();
}

void CourseVwPage::btEdit_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvCourse.SelectedIndex;
	if(selectedIndex<0)
	{
		fillListView();
		return;
	}
	const int course_id= Sys::Convert::ToInt(lvCourse.SelectedData);
	if(course_id<0) return;
	hdCourseID.Data= lvCourse.SelectedData;
	h.NavigateTo(L"CoursePage");
	fillListView();
}

void CourseVwPage::btDelete_Click(Web::HttpConnector& h)
{
	const int selectedIndex= lvCourse.GetSelectedIndex();
	if(selectedIndex<0) return; //________________________Nothing is selected

	lvCourse.AjaxUpdate=true;
	Sql::SqlConnection conn;
	wstring sqlcmd;
	const int item_id= Sys::Convert::ToInt(lvCourse.Items[selectedIndex].Data); //Get the Primary Key
	int rows= 0;

	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(sqlcmd, L"DELETE FROM course WHERE course_id=%d", item_id);
		rows = conn.ExecuteNonQuery(sqlcmd);
		if (rows!=1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"Error: number of deleted rows", MB_OK | MB_ICONERROR);
		}
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	fillListView();
}

void CourseVwPage::btHome_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"Index");
}

void CourseVwPage::fillListView()
{
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(NULL, CONNECTION_STRING);
		lvCourse.Items.DeleteAll();
		conn.ExecuteSelect(L"SELECT course_id, code, descr FROM vw_Course", 100, lvCourse);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
}
