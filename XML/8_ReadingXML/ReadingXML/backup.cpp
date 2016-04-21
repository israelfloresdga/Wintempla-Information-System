#include "stdafx.h"  //________________________________________ ReadingXML.cpp
#include "ReadingXML.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	ReadingXML app;
	return app.BeginDialog(IDI_READINGXML, hInstance);
}

void ReadingXML::Window_Open(Win::Event& e)
{
}

