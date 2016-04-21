#include "stdafx.h"  //________________________________________ UniMng.cpp
#include "UniMng.h"
#include "ClassroomDlg.h"
#include "CourseDlg.h"
#include "DepartmentDlg.h"
#include "PeriodDlg.h"
#include "ProfessorDlg.h"
#include "ScheduleDlg.h"
#include "TimeBlockDlg.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow)
{
	UniMng app;
	return app.BeginDialog(IDI_UNIMNG, hInstance);
}

void UniMng::Window_Open(Win::Event& e)
{
//________________________________________________________ toolbMain
	TBBUTTON tbButton[15];//<< EDIT HERE THE NUMBER OF BUTTONS

	toolbMain.imageList.Create(20, 20, 13);//<< EDIT HERE THE NUMBER OF IMAGES
	toolbMain.imageList.AddIcon(this->hInstance, IDI_INSERT);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_EDIT);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_DELETE);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_PRINT);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_CLASSROOM);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_COURSE);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_DEPARTMENT);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_PERIOD);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_PROFESSOR);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_SCHEDULE);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_TIMEBLOCK);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_COPY);
	toolbMain.imageList.AddIcon(this->hInstance, IDI_MSEXCEL);
	toolbMain.SendMessage(TB_BUTTONSTRUCTSIZE, (WPARAM)(int)sizeof(TBBUTTON), 0); 
	toolbMain.SetImageList(toolbMain.imageList);
	int i=0;
	//_____________________________________
	tbButton[i].iBitmap=MAKELONG(0, 0); //<< IMAGE INDEX
	tbButton[i].idCommand=IDM_INSERT;
	tbButton[i].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[i].fsStyle=BTNS_BUTTON;
	tbButton[i].dwData=0L; 
	tbButton[i].iString= (LONG_PTR)L"Insert";
	//_____________________________________
	++i;
	tbButton[i].iBitmap=MAKELONG(1, 0); //<< IMAGE INDEX
	tbButton[i].idCommand=IDM_EDIT;
	tbButton[i].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[i].fsStyle=BTNS_BUTTON;
	tbButton[i].dwData=0L; 
	tbButton[i].iString= (LONG_PTR)L"Edit";
	//_____________________________________
	++i;
	tbButton[i].iBitmap=MAKELONG(2, 0); //<< IMAGE INDEX
	tbButton[i].idCommand=IDM_DELETE;
	tbButton[i].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[i].fsStyle=BTNS_BUTTON;
	tbButton[i].dwData=0L; 
	tbButton[i].iString= (LONG_PTR)L"Delete";
	//_____________________________________
	++i;
	tbButton[i].iBitmap=MAKELONG(3, 0); //<< IMAGE INDEX
	tbButton[i].idCommand=IDM_PRINT;
	tbButton[i].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[i].fsStyle=BTNS_BUTTON;
	tbButton[i].dwData=0L; 
	tbButton[i].iString= (LONG_PTR)L"Print";
	//________________________ A separator
	++i;
	tbButton[i].iBitmap=-1;
	tbButton[i].idCommand=0;  
	tbButton[i].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[i].fsStyle=BTNS_SEP;  
	tbButton[i].dwData=0L;  
	tbButton[i].iString=0;  
	//____________________________________
	++i;
	tbButton[i].iBitmap=MAKELONG(4, 0); //<< IMAGE INDEX
	tbButton[i].idCommand=IDM_CLASSROOM;
	tbButton[i].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[i].fsStyle=BTNS_BUTTON;
	tbButton[i].dwData=0L; 
	tbButton[i].iString= (LONG_PTR)L"Classroom";
	//____________________________________
	++i;
	tbButton[i].iBitmap=MAKELONG(5, 0); //<< IMAGE INDEX
	tbButton[i].idCommand=IDM_COURSE;
	tbButton[i].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[i].fsStyle=BTNS_BUTTON;
	tbButton[i].dwData=0L; 
	tbButton[i].iString= (LONG_PTR)L"Course";
	//____________________________________
	++i;
	tbButton[i].iBitmap=MAKELONG(6, 0); //<< IMAGE INDEX
	tbButton[i].idCommand=IDM_DEPARTMENT;
	tbButton[i].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[i].fsStyle=BTNS_BUTTON;
	tbButton[i].dwData=0L; 
	tbButton[i].iString= (LONG_PTR)L"Department";
	//____________________________________
	++i;
	tbButton[i].iBitmap=MAKELONG(7, 0); //<< IMAGE INDEX
	tbButton[i].idCommand=IDM_PERIOD;
	tbButton[i].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[i].fsStyle=BTNS_BUTTON;
	tbButton[i].dwData=0L; 
	tbButton[i].iString= (LONG_PTR)L"Period";
	//____________________________________
	++i;
	tbButton[i].iBitmap=MAKELONG(8, 0); //<< IMAGE INDEX
	tbButton[i].idCommand=IDM_PROFESSOR;
	tbButton[i].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[i].fsStyle=BTNS_BUTTON;
	tbButton[i].dwData=0L; 
	tbButton[i].iString= (LONG_PTR)L"Professor";
	//____________________________________
	++i;
	tbButton[i].iBitmap=MAKELONG(9, 0); //<< IMAGE INDEX
	tbButton[i].idCommand=IDM_SCHEDULE;
	tbButton[i].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[i].fsStyle=BTNS_BUTTON;
	tbButton[i].dwData=0L; 
	tbButton[i].iString= (LONG_PTR)L"Schedule";
	//____________________________________
	++i;
	tbButton[i].iBitmap=MAKELONG(10, 0); //<< IMAGE INDEX
	tbButton[i].idCommand=IDM_TIMEBLOCK;
	tbButton[i].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[i].fsStyle=BTNS_BUTTON;
	tbButton[i].dwData=0L; 
	tbButton[i].iString= (LONG_PTR)L"Time Block";
	//________________________ A separator
	++i;
	tbButton[i].iBitmap=-1;
	tbButton[i].idCommand=0;  
	tbButton[i].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[i].fsStyle=BTNS_SEP;  
	tbButton[i].dwData=0L;  
	tbButton[i].iString=0;  
	//_____________________________________
	++i;
	tbButton[i].iBitmap=MAKELONG(11, 0); //<< IMAGE INDEX
	tbButton[i].idCommand=IDM_COPY;
	tbButton[i].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[i].fsStyle=BTNS_BUTTON;
	tbButton[i].dwData=0L; 
	tbButton[i].iString= (LONG_PTR)L"Copy";
	//_____________________________________
	++i;
	tbButton[i].iBitmap=MAKELONG(12, 0); //<< IMAGE INDEX
	tbButton[i].idCommand=IDM_MSEXCEL;
	tbButton[i].fsState=TBSTATE_ENABLED; // | TBSTATE_WRAP
	tbButton[i].fsStyle=BTNS_BUTTON;
	tbButton[i].dwData=0L; 
	tbButton[i].iString= (LONG_PTR)L"Export";
	
	toolbMain.SetBitmapSize(20, 20);
	toolbMain.SetButtonSize(22, 20);
	toolbMain.AddButtons(tbButton, 15);// << EDIT HERE THE NUMBER OF BUTTONS
	toolbMain.SendMessage(TB_AUTOSIZE, 0, 0);
	toolbMain.SetMaxTextRows(1);// EDIT HERE TO DISPLAY THE BUTTON TEXT
	toolbMain.Show(SW_SHOWNORMAL);
	//____________________________________________________Set enable/disable buttons
	enableButtons();
	toolbMain.EnableButton(IDM_INSERT, false);
	toolbMain.EnableButton(IDM_PRINT, false);
	toolbMain.EnableButton(IDM_COPY, false);
	toolbMain.EnableButton(IDM_MSEXCEL, false);
	//________________________________________________________ lvMain
	lvMain.Cols.Add(0, LVCFMT_CENTER, 300, L"Select an option.");
}

//_________________________________________________________Table Buttons
void UniMng::enableButtons()
{
	toolbMain.EnableButton(IDM_INSERT, true);
	toolbMain.EnableButton(IDM_EDIT, false);
	toolbMain.EnableButton(IDM_DELETE, false);
	toolbMain.EnableButton(IDM_PRINT, true);
	toolbMain.EnableButton(IDM_CLASSROOM, true);
	toolbMain.EnableButton(IDM_COURSE, true);
	toolbMain.EnableButton(IDM_DEPARTMENT, true);
	toolbMain.EnableButton(IDM_PERIOD, true);
	toolbMain.EnableButton(IDM_PROFESSOR, true);
	toolbMain.EnableButton(IDM_SCHEDULE, true);
	toolbMain.EnableButton(IDM_TIMEBLOCK, true);
	toolbMain.EnableButton(IDM_COPY, true);
	toolbMain.EnableButton(IDM_MSEXCEL, true);
}

void UniMng::Cmd_Classroom(Win::Event& e)
{
	enableButtons();
	toolbMain.EnableButton(IDM_CLASSROOM, false);
	fillListView();
}

void UniMng::Cmd_Course(Win::Event& e)
{
	enableButtons();
	toolbMain.EnableButton(IDM_COURSE, false);
	fillListView();
}

void UniMng::Cmd_Department(Win::Event& e)
{
	enableButtons();
	toolbMain.EnableButton(IDM_DEPARTMENT, false);
	fillListView();
}

void UniMng::Cmd_Period(Win::Event& e)
{
	enableButtons();
	toolbMain.EnableButton(IDM_PERIOD, false);
	fillListView();
}

void UniMng::Cmd_Professor(Win::Event& e)
{
	enableButtons();
	toolbMain.EnableButton(IDM_PROFESSOR, false);
	fillListView();
}

void UniMng::Cmd_Schedule(Win::Event& e)
{
	enableButtons();
	toolbMain.EnableButton(IDM_SCHEDULE, false);
	fillListView();
}

void UniMng::Cmd_Timeblock(Win::Event& e)
{
	enableButtons();
	toolbMain.EnableButton(IDM_TIMEBLOCK, false);
	fillListView();
}

//________________________________________________________External funtions
void UniMng::Cmd_Print(Win::Event& e)
{
	toolbMain.EnableButton(IDM_PRINT, false);
	//___________________________________________________Build document
	Win::PrintDoc doc;
	doc.Create(L"PeopleMng");
	doc.Add(500,lvMain.Items.Count+1,lvMain);//0.5cm
	//___________________________________________________Print doc
	Win::PrintPreviewDlg dlg;
	dlg.BeginDialog_(hWnd, &doc);
	toolbMain.EnableButton(IDM_PRINT, true);
}

void UniMng::Cmd_Copy(Win::Event& e)
{
	toolbMain.EnableButton(IDM_COPY, false);
	lvMain.CopyToClipboard();
	toolbMain.EnableButton(IDM_COPY, true);
}

void UniMng::Cmd_Msexcel(Win::Event& e)
{
	toolbMain.EnableButton(IDM_MSEXCEL, false);
	Win::FileDlg filedlg;
	filedlg.SetFilter(L"Excel Files(*.xlsx)\0*.xlsx\0All Files(*.*)\0*.*\0\0",0,L"xlsx");
	if(filedlg.BeginDialog(hWnd,L"Save a Ms Excel File", true))
	{
		lvMain.ExportToMsExcel(filedlg.GetFileNameFullPath());	
	}
	toolbMain.EnableButton(IDM_MSEXCEL, true);
	//______________________Edit WintemplaWin.cpp Line 14201
	//______________________Line Before: ActiveSheet.Method(L"SaveAs", filename, result);
	//______________________ActiveSheet.Method(L"Paste");
}

//_______________________________________________________Commands Buttons\Actions 
void UniMng::Cmd_Insert(Win::Event& e)
{
	insertItem();
}

void UniMng::Cmd_Delete(Win::Event& e)
{
	deleteItem();
}

void UniMng::Cmd_Edit(Win::Event& e)
{
	editItem();
}

void UniMng::lvMain_ItemChanged(Win::Event& e)
{
	if(lvMain.GetSelectedIndex() >=0)
	{
		this->toolbMain.EnableButton(IDM_DELETE,true);
		this->toolbMain.EnableButton(IDM_EDIT,true);
	}
	else
	{
		this->toolbMain.EnableButton(IDM_DELETE,false);
		this->toolbMain.EnableButton(IDM_EDIT,false);
	}
}

void UniMng::lvMain_KeyDown(Win::Event& e)
{
	LPNMLVKEYDOWN p = (LPNMLVKEYDOWN) e.lParam;
	if (p->wVKey == VK_DELETE)
	{
		deleteItem();
	}
}

void UniMng::lvMain_DblClk(Win::Event& e)
{
	editItem();
}

//_______________________________________________________Commands
void UniMng::fillListViewCols()
{
	lvMain.SetRedraw(false);
	lvMain.Cols.DeleteAll();
	if(toolbMain.IsButtonEnabled(IDM_CLASSROOM)==false)
	{
		this->Text=L"Classroom Table";
		lvMain.Cols.Add(0, LVCFMT_LEFT, 120, L"Classroom");
		lvMain.Cols.Add(1, LVCFMT_LEFT, 120, L"Seat count");
		lvMain.Cols.Add(2, LVCFMT_LEFT, 120, L"Has projector");
		lvMain.Cols.Add(3, LVCFMT_LEFT, 120, L"Building");
	}
	else if(toolbMain.IsButtonEnabled(IDM_COURSE)==false)
	{
		this->Text=L"Course Table";
		lvMain.Cols.Add(0, LVCFMT_LEFT, 150, L"Code");
		lvMain.Cols.Add(1, LVCFMT_LEFT, 250, L"Course");
	}
	else if(toolbMain.IsButtonEnabled(IDM_DEPARTMENT)==false)
	{
		this->Text=L"Department Table";
		lvMain.Cols.Add(0, LVCFMT_LEFT, 200, L"Department");
	}
	else if(toolbMain.IsButtonEnabled(IDM_PERIOD)==false)
	{
		this->Text=L"Period Table";
		lvMain.Cols.Add(0, LVCFMT_LEFT, 120, L"Period");
		lvMain.Cols.Add(1, LVCFMT_LEFT, 120, L"Begin date");
		lvMain.Cols.Add(2, LVCFMT_LEFT, 120, L"End date");
	}
	else if(toolbMain.IsButtonEnabled(IDM_PROFESSOR)==false)
	{
		this->Text=L"Professor Table";
		lvMain.Cols.Add(0, LVCFMT_LEFT, 200, L"Name");
		lvMain.Cols.Add(1, LVCFMT_LEFT, 200, L"Department");
		lvMain.Cols.Add(2, LVCFMT_LEFT, 120, L"Username");
	}
	else if(toolbMain.IsButtonEnabled(IDM_SCHEDULE)==false)
	{
		this->Text=L"Schedule Table";
		lvMain.Cols.Add(0, LVCFMT_LEFT, 180, L"Professor name");
		lvMain.Cols.Add(1, LVCFMT_LEFT, 180, L"Course");
		lvMain.Cols.Add(2, LVCFMT_LEFT, 120, L"Period");
		lvMain.Cols.Add(3, LVCFMT_LEFT, 150, L"Time block");
		lvMain.Cols.Add(4, LVCFMT_LEFT, 100, L"Classroom");
	}
	else
	{
		this->Text=L"Time block Table";
		lvMain.Cols.Add(0, LVCFMT_LEFT, 150, L"Description");
		lvMain.Cols.Add(1, LVCFMT_CENTER, 90, L"Monday");
		lvMain.Cols.Add(2, LVCFMT_CENTER, 90, L"Tuesday");
		lvMain.Cols.Add(3, LVCFMT_CENTER, 90, L"Wednesday");
		lvMain.Cols.Add(4, LVCFMT_CENTER, 90, L"Thursday");
		lvMain.Cols.Add(5, LVCFMT_CENTER, 90, L"Friday");
		lvMain.Cols.Add(6, LVCFMT_CENTER, 90, L"Saturday");
	}
	lvMain.SetRedraw(true);
}


void UniMng::fillListView()
{
	fillListViewCols();
	lvMain.SetRedraw(false);
	lvMain.Items.DeleteAll();
	Sql::SqlConnection conn;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		if(toolbMain.IsButtonEnabled(IDM_CLASSROOM)==false)
			conn.ExecuteSelect(L"SELECT classroom_id, descr, seat_count, has_projector, building FROM vw_Classroom", 100, lvMain);
		else if(toolbMain.IsButtonEnabled(IDM_COURSE)==false)
			conn.ExecuteSelect(L"SELECT course_id, code, descr FROM vw_Course", 100, lvMain);
		else if(toolbMain.IsButtonEnabled(IDM_DEPARTMENT)==false)
			conn.ExecuteSelect(L"SELECT department_id, descr FROM vw_Department", 100, lvMain);
		else if(toolbMain.IsButtonEnabled(IDM_PERIOD)==false)
			conn.ExecuteSelect(L"SELECT period_id, descr, begin_date, end_date FROM vw_Period", 100, lvMain);
		else if(toolbMain.IsButtonEnabled(IDM_PROFESSOR)==false)
			conn.ExecuteSelect(L"SELECT professor_id, name, department_descr, username FROM vw_Professor", 100, lvMain);
		else if(toolbMain.IsButtonEnabled(IDM_SCHEDULE)==false)
			conn.ExecuteSelect(L"SELECT schedule_id, professor_name,course_name,period,time_block,classroom FROM vw_Schedule", 100, lvMain);
		else
			conn.ExecuteSelect(L"SELECT time_block_id,descr, Monday,Tuesday,Wednesday,Thursday,Friday,Saturday FROM vw_Time_block", 100, lvMain);
	}
	catch (Sql::SqlException e)
	{
		this->MessageBox(e.GetDescription(), L"Error", MB_OK | MB_ICONERROR);
	}
	lvMain.SetRedraw(true);
}

void UniMng::deleteItem()
{
	toolbMain.EnableButton(IDM_DELETE,false);
	Win::HourGlassCursor hgc(true);
	const int selectedIndex= lvMain.GetSelectedIndex();
	if(selectedIndex<0) return; //_____________________________Nothing is selected
	//_________________________________________________________Ask the user
	if(this->MessageBox(L"Are you sure you want to delete the selected item?", L"Delete item",
		MB_YESNO|MB_ICONQUESTION)!=IDYES) return;
	//________________________________________________________Delete;
	Sql::SqlConnection conn;
	wstring cmd;
	const int item_id= lvMain.Items[selectedIndex].Data; //Get the Primary Key; 
	int rows = 0;
	try
	{
		//conn.OpenSession(DSN, USERNAME, PASSWORD); //Control Panel>Administrative Tools>Data Sources (ODBC)>Create dsn_myDatabase
		conn.OpenSession(hWnd, CONNECTION_STRING);
		if(toolbMain.IsButtonEnabled(IDM_CLASSROOM)==false)
			Sys::Format(cmd, L"DELETE FROM classroom WHERE classroom_id= %d", item_id);
		else if(toolbMain.IsButtonEnabled(IDM_COURSE)==false)
			Sys::Format(cmd, L"DELETE FROM course WHERE course_id= %d", item_id);
		else if(toolbMain.IsButtonEnabled(IDM_DEPARTMENT)==false)
			Sys::Format(cmd, L"DELETE FROM department WHERE department_id= %d", item_id);
		else if(toolbMain.IsButtonEnabled(IDM_PERIOD)==false)
			Sys::Format(cmd, L"DELETE FROM period WHERE period_id= %d", item_id);
		else if(toolbMain.IsButtonEnabled(IDM_PROFESSOR)==false)
			Sys::Format(cmd, L"DELETE FROM professor WHERE professor_id= %d", item_id);
		else if(toolbMain.IsButtonEnabled(IDM_SCHEDULE)==false)
			Sys::Format(cmd, L"DELETE FROM schedule WHERE schedule_id= %d", item_id);
		else
			Sys::Format(cmd, L"DELETE FROM time_block WHERE time_block_id= %d", item_id);
		rows = conn.ExecuteNonQuery(cmd);
		if (rows!=1)
		{
			this->MessageBox(Sys::Convert::ToString(rows), L"ERROR: number of deleted rows", MB_OK | MB_ICONERROR);
		}
	}
	catch (Sql::SqlException ex)
	{
		this->MessageBox(ex.GetDescription(), L"ERROR", MB_OK | MB_ICONERROR);
	}
	fillListView();
}

void UniMng::insertItem()
{
	toolbMain.EnableButton(IDM_INSERT,false);
	if(toolbMain.IsButtonEnabled(IDM_CLASSROOM)==false)
	{
		ClassroomDlg dlg;
		dlg.BeginDialog(hWnd);
	}
	else if(toolbMain.IsButtonEnabled(IDM_COURSE)==false)
	{
		CourseDlg dlg;
		dlg.BeginDialog(hWnd);
	}
	else if(toolbMain.IsButtonEnabled(IDM_DEPARTMENT)==false)
	{
		DepartmentDlg dlg;
		dlg.BeginDialog(hWnd);
	}
	else if(toolbMain.IsButtonEnabled(IDM_PERIOD)==false)
	{
		PeriodDlg dlg;
		dlg.BeginDialog(hWnd);
	}
	else if(toolbMain.IsButtonEnabled(IDM_PROFESSOR)==false)
	{
		ProfessorDlg dlg;
		dlg.BeginDialog(hWnd);
	}
	else if(toolbMain.IsButtonEnabled(IDM_SCHEDULE)==false)
	{
		ScheduleDlg dlg;
		dlg.BeginDialog(hWnd);
	}
	else 
	{
		TimeBlockDlg dlg;
		dlg.BeginDialog(hWnd);
	}

	fillListView();
	toolbMain.EnableButton(IDM_INSERT,true);
}

void UniMng::editItem()
{
	toolbMain.EnableButton(IDM_EDIT,false);
	const int selectedIndex= lvMain.GetSelectedIndex();
	if(selectedIndex<0) return;
	//____________________________________________________Ask the user
	if(this->MessageBox(L"Are you sure you want to modify the selected item?", L"Edit item", 
		MB_YESNO|MB_ICONQUESTION)!=IDYES) return;
	//___________________________________________________Edit
	const int item_id= lvMain.Items[selectedIndex].Data;
	if(toolbMain.IsButtonEnabled(IDM_CLASSROOM)==false)
	{
		ClassroomDlg dlg;
		dlg.classroom_id= item_id;
		dlg.BeginDialog(hWnd);
	}
	else if(toolbMain.IsButtonEnabled(IDM_COURSE)==false)
	{
		CourseDlg dlg;
		dlg.course_id= item_id;
		dlg.BeginDialog(hWnd);
	}
	else if(toolbMain.IsButtonEnabled(IDM_DEPARTMENT)==false)
	{
		DepartmentDlg dlg;
		dlg.department_id= item_id;
		dlg.BeginDialog(hWnd);
	}
	else if(toolbMain.IsButtonEnabled(IDM_PERIOD)==false)
	{
		PeriodDlg dlg;
		dlg.period_id= item_id;
		dlg.BeginDialog(hWnd);
	}
	else if(toolbMain.IsButtonEnabled(IDM_PROFESSOR)==false)
	{
		ProfessorDlg dlg;
		dlg.professor_id= item_id;
		dlg.BeginDialog(hWnd);
	}
	else if(toolbMain.IsButtonEnabled(IDM_SCHEDULE)==false)
	{
		ScheduleDlg dlg;
		dlg.schedule_id= item_id;
		dlg.BeginDialog(hWnd);
	}
	else
	{
		TimeBlockDlg dlg;
		dlg.time_block_id= item_id;
		dlg.BeginDialog(hWnd);
	}
	fillListView();
	toolbMain.EnableButton(IDM_EDIT,true);
}

/*
		if(toolbMain.IsButtonEnabled(IDM_CLASSROOM)==false)
		else if(toolbMain.IsButtonEnabled(IDM_COURSE)==false)
		else if(toolbMain.IsButtonEnabled(IDM_DEPARTMENT)==false)
		else if(toolbMain.IsButtonEnabled(IDM_PERIOD)==false)
		else if(toolbMain.IsButtonEnabled(IDM_PROFESSOR)==false)
		else if(toolbMain.IsButtonEnabled(IDM_SCHEDULE)==false)
		else (toolbMain.IsButtonEnabled(IDM_TIMEBLOCK)==false)
*/
