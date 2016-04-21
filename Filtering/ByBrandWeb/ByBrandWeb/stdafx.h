// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#pragma once
/************************CONFIGURATION FILE ****************************/
//_________________________________________ GDI+
#define WIN_GDI_PLUS_ON
//_________________________________________ MIDI, Audio Card DAC's and ADC's (or GDI Game for timers)
//#define WIN_DAC_ADC_SUPPORT
//_________________________________________ Rich Edit Control
//#define WIN_RICHEDIT_SUPPORT
//_________________________________________ OpenGL
//#define WIN_OPENGL_SUPPORT
//_________________________________________ Sockets
//#define WIN_SOCKETS_SUPPORT
//_________________________________________ DirectX
//#define WIN_DIRECTX
//
//
// ******************************************************* Standard Headers
#define STRICT
//
#ifndef WIN_GDI_PLUS_ON
#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#endif
//
#define WINVER 0x0500
#define _WIN32_WINNT 0x0502   // for Mouse Wheel support & SysLink
//
//

#include "Wintempla.h"
using namespace std;

//#include <list>
//#include <map> //<hash_map>  <hash_multimap>
//#include <queue>
//#include <deque>
//#include <set> // <hash_set>
//#include <stack>
#include <regex>
//#include <random>
//#include <vector>
//#include <valarray> //example:valarray<double> x(10);
//#include <algorithm>
//#include <complex>  //example:complex<double> z(1.0, 3.5);

//Control Panel>Administrative Tools>Data Sources (ODBC)>System DSN>Add>SQL Native Client>Server: computer_name\SQLExpress
#define DSN L"dsn_circuit_city"
#define USERNAME L"root"
#define PASSWORD L"123"
#define CONNECTION_STRING L"DRIVER={SQL Server};server=ISRAELLSMT_M\\SQLEXPRESS;database=circuit_city;Trusted_Connection=yes"