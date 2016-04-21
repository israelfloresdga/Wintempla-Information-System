#include "stdafx.h"  //_____________________________________________ ClassroomPage.cpp
#include "ClassroomPage.h"

void ClassroomPage::Window_Open(Web::HttpConnector& h)
{
	this->Title=L"Classroom";
	classroom_id = Sys::Convert::ToInt(hdClassroomID.Data);
	if (classroom_id < 0) return; 
	if (h.FirstTime == false) return;
	Sql::SqlConnection conn;
	wstring cmd;
	try
	{
		conn.OpenSession(NULL, CONNECTION_STRING);
		Sys::Format(cmd, L"SELECT descr, seat_count, has_projector, building FROM classroom WHERE classroom_id=%d", classroom_id);
		conn.ExecuteSelect(cmd);
		tbxDescr.MaxLength= 32;
		conn.BindColumn(1, tbxDescr,32);
		tbxSeat_count.MaxLength=3;
		conn.BindColumn(2, tbxSeat_count,32);
		conn.BindColumn(3, ckHas_projector);
		tbxBuilding.MaxLength=2;
		conn.BindColumn(4,tbxBuilding,32);
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

void ClassroomPage::btOK_Click(Web::HttpConnector& h)
{
	//_____________________________________________________________ Validate
	tr1::wregex regexClassroom(L"[0-9]{3}");
	if (tr1::regex_match(tbxDescr.Text, regexClassroom) == false)
	{
		tbxDescr.ShowBalloonTip(L"Invalid Descr", L"Please provide an integer value of three numbers", TTI_ERROR);
		return;
	}
	tr1::wregex regexSeats(L"[01]?[0-9]{2}");
	if (tr1::regex_match(tbxSeat_count.Text, regexSeats) == false)
	{
		tbxSeat_count.ShowBalloonTip(L"Invalid Seat count", L"Please provide an integer value. Max: 199", TTI_ERROR);
		return;
	}
	tr1::wregex regextbxBuilding(L"[A-Z][a-z]?");
	if (tr1::regex_match(tbxBuilding.Text, regextbxBuilding) == false)
	{
		tbxBuilding.ShowBalloonTip(L"Invalid ", L"Please provide one or two characters", TTI_ERROR);
		return;
	}

	const int classroom_id = Sys::Convert::ToInt(hdClassroomID.Data);
	Sql::StringBuilder sb(L"classroom", L"classroom_id", classroom_id);
	sb.Bind(L"descr", tbxDescr);
	sb.Bind(L"seat_count", tbxSeat_count);
	sb.Bind(L"has_projector", ckHas_projector);
	sb.Bind(L"building", tbxBuilding);
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
	h.NavigateTo(L"ClassroomVwPage");
}

void ClassroomPage::btCancel_Click(Web::HttpConnector& h)
{
	h.NavigateTo(L"ClassroomVwPage");
}

