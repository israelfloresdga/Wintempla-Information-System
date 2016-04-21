#include "stdafx.h"  //_____________________________________________ Index.cpp
#include "Index.h"

void Index::Window_Open(Web::HttpConnector& h)
{
}



void Index::btCalculate_Click(Web::HttpConnector& h)
{
	const double x= tbxX.DoubleValue;
	const double y= tbxY.DoubleValue;
	tbxResult.DoubleValue= x+y;
}

