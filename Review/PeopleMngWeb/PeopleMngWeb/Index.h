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
	Web::ImageLink imkClient;
	Web::ImageLink imkEmployee;
protected:
	void InitializeGui()
	{
		this->ID=L"Index";
		this->Title=L"Index";
		this->CssFile=L"cyan.css";
		this->JavascriptFile=L"Index.js";
		this->pndMain.ID=L"pndMain";
		this->imgLogo.ID=L"imgLogo";
		this->imkClient.ID=L"imkClient";
		this->imkEmployee.ID=L"imkEmployee";
		this->imgLogo.Text=L"Circuit City";
		this->imkClient.Text=L"View and Manage Clients";
		this->imkEmployee.Text=L"View and Manage Employees";
		this->pndMain.AddChild(imgLogo);
		this->pndMain.AddChild(imkClient);
		this->pndMain.AddChild(imkEmployee);
		this->imgLogo.src=L"circuit_city.gif";
		this->imkClient.BeginHtml=L"Client:<br/>";
		this->imkClient.src=L"client.png";
		this->imkClient.href=L"ClientVwPage";
		this->imkClient.imageCssClass=L"Clean";
		this->imkEmployee.BeginHtml=L"Employee:<br/>";
		this->imkEmployee.src=L"employee.png";
		this->imkEmployee.href=L"EmployeeVwPage";
		this->imkEmployee.imageCssClass=L"Clean";
		this->AddChild(pndMain);
	}
	//_________________________________________________
	void Window_Open(Web::HttpConnector& h);
	void EventHandler(Web::HttpConnector& h)
	{
	}
};
