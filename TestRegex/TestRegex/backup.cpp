#include "stdafx.h"  //________________________________________ TestRegex.cpp
#include "TestRegex.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	TestRegex app;
	app.CreateMainWindow(L"TestRegex", cmdShow, IDI_TESTREGEX, NULL, (HBRUSH)(COLOR_WINDOW+1), hInstance);
	return app.MessageLoop(IDC_TESTREGEX);
}

void TestRegex::Window_Open(Win::Event& e)
{
}

void TestRegex::btMatch_Click(Win::Event& e)
{
    //tr1::wregex reg(L"[0123456789]");//Problem 2
	//tr1::wregex reg(L"a[0123456789][0123456789]");//Problem 3
	//tr1::wregex reg(L"[12345]\\d\\d");//Problem 4: 100-599
	//tr1::wregex reg(L"-\\d+");//Problem 5: -[0-9]+
	//tr1::wregex reg(L"(\\+?[123456789])|(\\+?[123456789]\\d+)");//Problem 6: a positive integer number with the first digit on the left be different from zero.
	//tr1::wregex reg(L"(A\\d)|(B\\d\\d)");//Problem 7: (A[0-9])|(B[0-9][0-9])
	//tr1::wregex reg(L"([02468]+)|(-[02468]+)|(\\d+[02468]$)|(-\\d+[02468]$)");//Problem 8: an even number.//optimizar	
	/*	Review */
	//tr1::wregex reg(L"([a-z]{2}[0-9]{2})");//Problem 1
	//tr1::wregex reg(L"([A-z]{2}-[0-9]{3})");//Problem 2
	//tr1::wregex reg(L"([A-Z][a-z]*\\s[A-Z][a-z]*)");//Problem 3
	//tr1::wregex reg(L"(\\w+.(edu|com|org))");//Problem 4
	//tr1::wregex reg(L"([0-9]{2})");//Problem 5
	//tr1::wregex reg(L"(SUN|MON|TUE|WED|THU|FRI|SAT)");//Problem 6
	//tr1::wregex reg(L"((Jan|Feb|Mar|Apr|May|Jun|Jul|Agu|Sep|Oct|Nov|Dec)\\s[0-9]+)");//Problem 7
	//tr1::wregex reg(L"(([A-z]|[0-9]|-|_|\\.)+@([A-z]|[0-9]|-|_|\\.)+)");//Problem 8
	//tr1::wregex reg(L"([\\+-]?[0-9]+(\\.[0-9]+)?([eE][\\+-]?[0-9]+)?)");//Problem 9
	//tr1::wregex reg(L"([0-9]{3}-[0-9]{2}-[0-9]{4})");//Problem 10
	//tr1::wregex reg(L"([A-Z]{4}[0-9]{6}-([A-Z0-9]){3})");//Problem 11
	//------tr1::wregex reg(L"((.*(\\s|\\.|@))?(ABS|abs)(.*(\\s|\\.|@))?");//Problem 12
	//tr1::wregex reg(L"([A-Z]{5}|[a-z]{5}|[0-9]{5})");//Problem 13
	//tr1::wregex reg(L"(S.-[0-9]{4}(ES)?)");//Problem 14
	//tr1::wregex reg(L"([\\+-]?\\$[0-9]+(\\.[0-9]+)?)");//Problem 16
	//tr1::wregex reg(L"(\\w+@.+\\.(edu|com|net|org))");//Problem 16
	//tr1::wregex reg(L"(^A.*$)");//Problem 17
	//tr1::wregex reg(L"(.*Z$)");//Problem 18
	tr1::wregex reg(L"((^.*$)+^Edgar.*$(^.*$)+)");//Problem 19

	//tr1::wregex reg(L"()");//Problem

	if (tr1::regex_match(tbxInput.Text, reg) == true)
     {
          tbxInput.ShowBalloonTip(L"TestRegex", L"The string matches", TTI_NONE);
     }
     else
     {
          tbxInput.ShowBalloonTip(L"TestRegex", L"The string does NOT match", TTI_ERROR);
     }
}

