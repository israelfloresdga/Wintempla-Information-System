#include "stdafx.h"  //_____________________________________________ CategoryPage.cpp
#include "CategoryPage.h"

void CategoryPage::Window_Open(Web::HttpConnector& h)
{
	category_id= Sys::Convert::ToInt(hdCategory_id)
}


void CategoryPage::btOk_Click(Web::HttpConnector& h)
{
}

void CategoryPage::btCancel_Click(Web::HttpConnector& h)
{
}

