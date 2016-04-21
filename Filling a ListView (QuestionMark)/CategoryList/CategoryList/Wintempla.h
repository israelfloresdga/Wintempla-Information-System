#pragma once

/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.  I ACCEPT NO LIABILITY FOR ANY DAMAGE OR LOSS
   OF BUSINESS THAT THIS SOFTWARE MAY CAUSE.

   Wintempla.h 
 
   © Copyright 2004 - 2013 Sergio Ledesma.  All Rights Reserved.

   THIS CODE IS PROTECTED BY COPYRIGHT LAW AND INTERNATIONAL TREATIES.
	UNAUTHORIZED REPRODUCTION OR DISTRIBUTION OF THIS CODE, OR ANY PORTION
	OF IT, MAY RESULT IN SEVERE CIVIL AND CRIMINAL PENALTIES, AND WILL BE
	PROSECUTED TO THE MAXIMUM EXTENT POSSIBLE UNDER THE LAW.

	ESTE CODIGO ESTA PROTEGIDO POR LAS LEYES Y TRATADOS DE DERECHO AUTOR
	INTERNACIONALES.  LA REPRODUCCION SIN AUTORIZACION O LA DISTRIBUCION
	DE ESTE CODIGO, O CUALQUIER PARTE DE ESTE, RESULTARA EN SEVERA
	PENALIDAD CIVIL Y CRIMINAL, Y SERA PERSEGUIDA HASTA SU MAXIMA 
	EXTENSION BAJO LO QUE PERMITA LA LEY.
***************************************************************************/

// Requires this before including windows.h 
#ifdef WIN_SOCKETS_SUPPORT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0502
#endif
#include <winsock2.h> 
#include <ws2tcpip.h> 
#pragma comment(lib, "ws2_32.lib")
#endif

#include <windows.h>
#ifdef WIN_GDI_PLUS_ON
	#include <gdiplus.h>
	#pragma comment(lib, "gdiplus.lib")
#endif

//____________________________________ STL Support of min and max
#undef max     
#undef min

#ifndef MAXIMUM
#define MAXIMUM(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef MINIMUM
#define MINIMUM(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef SS_WINNORMAL
	#define SS_WINNORMAL 0x0000L
#endif

#ifndef CBS_WINNORMALCASE
	#define CBS_WINNORMALCASE 0x0000L
#endif

#ifndef LBS_WINNORMAL
	#define LBS_WINNORMAL 0x0000L
#endif

#ifndef LBS_WINSINGLESEL
	#define LBS_WINSINGLESEL 0x0000L
#endif

#ifndef ES_WINNORMALCASE
	#define ES_WINNORMALCASE 0x0000L
#endif

#ifndef UDS_WINVERT
	#define UDS_WINVERT 0x0000L
#endif

//#define SYS_SOCKET_DATABUFFERSIZE 512
#ifndef WM_SOCKETNOTIFY
	#define WM_SOCKETNOTIFY (WM_USER+10)
#endif
//
#ifndef WM_SOCKETHOSTNAME
	#define WM_SOCKETHOSTNAME (WM_USER+11)
#endif

#define WIN_LANGUAGE_ENGLISH 0 
#define WIN_LANGUAGE_SPANISH 1
//
#define WIN_SOCKET_INITIAL 0
#define WIN_SOCKET_HOSTNAME 1
#define WIN_SOCKET_DISCONNECTED 2
#define WIN_SOCKET_CONNECTED 3
#define WIN_SOCKET_WELCOME 4
#define WIN_SOCKET_HELO 5
#define WIN_SOCKET_AUTH 6
#define WIN_SOCKET_USERNAME 7
#define WIN_SOCKET_PASSWORD 8
#define WIN_SOCKET_MAILFROM 9
#define WIN_SOCKET_RCPTTO 10
//_____________________________________________ DATA
#define WIN_SOCKET_DATA 11
#define WIN_SOCKET_TIMEHEADER 12
#define WIN_SOCKET_FROM 13
#define WIN_SOCKET_SENDER 14
#define WIN_SOCKET_REPLYTO 15
#define WIN_SOCKET_SUBJECT 16
#define WIN_SOCKET_TO 17
#define WIN_SOCKET_MIME 18
#define WIN_SOCKET_MULTIPART_MIXED 19
//____________________________________________ BODY
#define WIN_SOCKET_BODY_FRONTIER 20
#define WIN_SOCKET_BODY_CONTENT_TYPE 21
#define WIN_SOCKET_BODY_BLANK1 22
#define WIN_SOCKET_BODY 23
#define WIN_SOCKET_BODY_BLANK2 24
//____________________________________________ ATTACHMENT
#define WIN_SOCKET_ATTACH_FRONTIER 25
#define WIN_SOCKET_ATTACH_CONTENT_TYPE 26
#define WIN_SOCKET_ATTACH_CONTENT_DISPOSITION 27
#define WIN_SOCKET_ATTACH_TRANSFER_ENCODING 28
#define WIN_SOCKET_ATTACH_BLANK1 29
#define WIN_SOCKET_ATTACH 30
#define WIN_SOCKET_ATTACH_BLANK2 31
#define WIN_SOCKET_ATTACH_END 32
//
#define WIN_SOCKET_DATA_END 33
#define WIN_SOCKET_QUIT 34
#define WIN_SOCKET_DONE 35
#define WIN_SMTP_BOUNDARY "XYZ0K4L6UFD23QWEasdfkjlEERRE7899ZCKIUHW87YTW"

#define UPDATE_VALUE 1
#define UPDATE_TEXT 2
#define WM_WINADDCHILD (WM_USER+14)
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES 1
#endif
#include "httpext.h"  //_______________________________________Web
#define HTTP_METHOD_ERROR 0
#define HTTP_METHOD_GET 1
#define HTTP_METHOD_HEAD 2
#define HTTP_METHOD_POST 3
#define HTTP_METHOD_PUT 4
#define HTTP_METHOD_DELETE 5
#define HTTP_METHOD_TRACE 6
#define HTTP_METHOD_CONNECT 7
//
#define HTML_BARCHART 100
#define HTML_BUTTON 101
#define HTML_CHECKBOX 102
#define HTML_CHECKBOXLIST 103
#define HTML_CUSTOMCONTROL 104
#define HTML_DATETIMEBOX 105
#define HTML_DATEVIEW 106
#define HTML_DROPDOWNLIST 107
#define HTML_HIDDENVALUE 108
#define HTML_HISTOGRAM 109
#define HTML_IMAGE 110
#define HTML_IMAGELINK 111
#define HTML_LABEL 112
#define HTML_LISTBOX 113
#define HTML_LISTVIEW 114
#define HTML_PARENTNODE 115
#define HTML_PIECHART 116
#define HTML_PLUGIN 117
#define HTML_POLARCHART 118
#define HTML_RADIOBUTTON 119
#define HTML_TEXTBOX 120
#define HTML_TEXTLINK 121
#define HTML_XYCHART 122
//
#define HTML_PAGE 150
//_____________________________________ TEXT NODE
#define HTML_TND_SPAN 300
#define HTML_TND_P 301
#define HTML_TND_SMALL 302
#define HTML_TND_PRE 303
#define HTML_TND_TT 304
#define HTML_TND_B 305
#define HTML_TND_I 306
#define HTML_TND_U 307
#define HTML_TND_STRIKE 308
#define HTML_TND_Q 309
#define HTML_TND_H1 310
#define HTML_TND_H2 311
#define HTML_TND_H3 312
#define HTML_TND_H4 313
#define HTML_TND_H5 314
#define HTML_TND_H6 315
#define HTML_TND_NONE 316
//_____________________________________ PARENT NODE
#define HTML_PND_ONE_ROW_TABLE 400
#define HTML_PND_ONE_COLUMN_TABLE 401
#define HTML_PND_ROW_CONTAINER_TABLE 402
#define HTML_PND_UL 403
#define HTML_PND_OL 404
#define HTML_PND_DL 405
#define HTML_PND_ROW 406
#define HTML_PND_HR 407
#define HTML_PND_BR 408
#define HTML_PND_SPACE 409
#define HTML_PND_COMMA 410
#define HTML_PND_SEMICOLON 411
#define HTML_PND_PARENTHESIS 412
#define HTML_PND_BRACKETS 413
#define HTML_PND_NONE 414
//____________________________________ OTHER HTML TAGS
#define HTML_TD 450
#define HTML_TR 451
#define HTML_TH 452
#define HTML_DIV 453
#define HTML_LI 454
#define HTML_DD 455
#define HTML_FORM 456
#define HTML_BODY 457
#define HTML_HEAD 458
#define HTML_INPUT 459
#define HTML_BR 460
#define HTML_HR 461
#define HTML_SELECTX 462
#define HTML_TEXTAREA 463
#define HTML_META 464
#define HTML_HTML 465
#define HTML_DOCTYPE 466
#define HTML_TITLE 467
#define HTML_LINK 468
#define HTML_SCRIPT 469
#define HTML_IMG 470
#define HTML_A 471
#define HTML_OPTION 472
#define HTML_OBJECT 473
#define HTML_COMMENT 474
//________________________________________________ Events
//#define HTML_BUTTONSUBMIT 500
#define HTML_CLICK 501
#define HTML_DBLCLICK 502
#define HTML_MOUSEDOWN 503
#define HTML_MOUSEUP 504
#define HTML_MOUSEMOVE 505
#define HTML_MOUSEOUT 506
#define HTML_FOCUS 507
#define HTML_BLUR 508
#define HTML_KEYPRESS 509
#define HTML_KEYDOWN 510
#define HTML_KEYUP 511
#define HTML_SELECT 512
#define HTML_CHANGE 513
#define HTML_SUBMIT 514
#define HTML_RESET 515
#define HTML_LOAD 516
#define HTML_UNLOAD 517
//
#define HTML_JSCLICK 601
#define HTML_JSDBLCLICK 602
#define HTML_JSMOUSEDOWN 603
#define HTML_JSMOUSEUP 604
#define HTML_JSMOUSEMOVE 605
#define HTML_JSMOUSEOUT 606
#define HTML_JSFOCUS 607
#define HTML_JSBLUR 608
#define HTML_JSKEYPRESS 609
#define HTML_JSKEYDOWN 610
#define HTML_JSKEYUP 611
#define HTML_JSSELECT 612
#define HTML_JSCHANGE 613
#define HTML_JSSUBMIT 614
#define HTML_JSRESET 615
#define HTML_JSLOAD 616
#define HTML_JSUNLOAD 617
//
#define HTML_BROWSER_UNKNOWN 700
#define HTML_BROWSER_IE 701
#define HTML_BROWSER_SAFARI 702
#define HTML_BROWSER_CHROME 703
#define HTML_BROWSER_OPERA 704
#define HTML_BROWSER_FIREFOX 705
//
#define HTML_CONTENT_TYPE_TEXT_HTML 800
#define HTML_CONTENT_TYPE_TEXT_XML 801
#define HTML_CONTENT_TYPE_IMAGE_GIF 802
#define HTML_CONTENT_TYPE_IMAGE_PNG 803
#define HTML_CONTENT_TYPE_IMAGE_XPNG 804
#define HTML_CONTENT_TYPE_IMAGE_JPG 805
//
#define HTML_SIZE_AUTO -100000
#define CSS_COLOR_AUTO 0x1000000
//
typedef DWORD (WINAPI * HTTP_EXTENSION_PROC)(EXTENSION_CONTROL_BLOCK*);
typedef BOOL (WINAPI * TERMINATE_EXTENSION)(DWORD);
typedef BOOL  (WINAPI * GET_EXTENSION_VERSION)(HSE_VERSION_INFO*);

#include <pshpack1.h> // Property Sheets and Wizards
//
#include <tchar.h>
#include <set>
#include <iostream>
#include <cmath>
#include <string>  //example: wstring name;
#include <vector>
#include <list>
#include <valarray> //example:valarray<double> x(10);  #undef max     #undef min
#include <algorithm>
#include <complex> //example:complex<double> z(1.0, 3.5);
#include <iterator>
#include <numeric>
#include <deque>
#include <map>
#include <stack> // for Virtual Machine
#include <random>   //tr1 random for Neural Networks
//
#include <process.h> // for Multithread:  Project Properties- >C/C++-> Code Generation -> Runtime Library -> Multithread
#include <atlbase.h> //#include <atlstr.h>
#include <io.h>

#include <stdexcept>
//#include <ctime> //For DateAndTime
//#include <ocidl.h> // For SvgReader
//
//#include "htmlhelp.h"  // for help system
//#pragma comment(lib, "htmlhelp.lib")
using namespace std;
#include <sqlucode.h> 
#define WINCOM_MAX_ERROR 512
#define WINSQL_EXCEPT_MAX (2*(SQL_MAX_MESSAGE_LENGTH))
#define SQL_BINDCOL_MAX 256
#define SQL_NAME_MAX 256
#define MT_DEQUE_MAX_SIZE 2048
#define SIMANNEAL_INITIAL_ERROR 1.0e30
#define WT_MATH_CONJGRAD 0
#define WT_MATH_VARMETRIC 1
//
//
#define DATA_PARSING_MAX 32
#define DATA_FIRST_CODE 1
#define DATA_LAST_CODE 255
#define DATA_SVG_FILE 1
#define DATA_SVG_RES 2
#define DATA_SVG_NONE 3
#define DATA_HTML_MAX 1024
#define WIN_MULTIPLICATION_SIGN 0x00D7
#define WIN_DIVISION_SIGN 0x00F7
#define WIN_MINUS_SIGN 0x2212
#define WIN_DRAWARROW_NORTH 0
#define WIN_DRAWARROW_EAST 1
#define WIN_DRAWARROW_SOUTH 2
#define WIN_DRAWARROW_WEST 3
#define REMEZ_DENSITY 64
#define REMEZ_TYPE_I 1
#define REMEZ_TYPE_II 2
#define REMEZ_TYPE_III 3
#define REMEZ_TYPE_IV 4
#define REMEZ_BANDPASS 1
#define REMEZ_HILBERT 2
#define REMEZ_DIFFERENTIATOR 4
//
//________________________________________________ Neural Networks definitions
//________________ Nn namespace
#define NN_NEURAL_LAB_VERSION 4
#define NN_NEURAL_LAB_SUBVERSION 0
#define NN_AF_TABLE_LENGTH 2048
#define NN_AF_TANHLIM 5
#define NN_AF_LIM 0.999999999999
#define NN_LAYERNET_WEIGHTMAX 15.0
#define NN_LAYERNET_TEXTMAX 256
#define NN_LAYERNET_ON 0.9
#define NN_LAYERNET_OFF -0.9
#define NN_MIN_VARIANCE 0.0001
#define NN_BITS_PER_WEIGHT 16
#define NN_WEIGHT_RES 32767
//
#define MATH_MATRIX_TEXTDOUBLE 32
#define TIME_PREDICTOR_LENGTH 32
#include <limits>
//
#include <shlobj.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include "shellapi.h" // for the tray
//
#define SYS_INSTBUFF 1024
#define SYS_INSTALL_LVINDEX 10000
// Your must include Remove<ProductName>.exe in the package, that is in the final product folder
#define FORMAT _snwprintf_s(sz, SYS_INSTBUFF, _TRUNCATE, L
//
//vector<valarray<double> > x(rows , valarray<double>(cols) );
#define MATRIX vector<valarray<double> >
#define MATRIXC vector<valarray<complex<double> > >

//________________ Cpl namespace (Compiler)
#define LEX_ISI_METHOD 0
#define LEX_ISI_ARGUMENT 1
#define LEX_ISI_METHOD_ARG 2
#define LEX_ISI_LAST_ARGUMENT 3
#define LEX_ISI_ARGUMENT_SEL 4
#define LEX_ISI_LAST_ARGUMENT_SEL 5
//
#define LEX_STRINGMAX 128
#define LEX_ERROR_UNRECOGNIZED_CHAR -1
#define LEX_ERROR_STRING_TOO_LONG -2
#define LEX_ERROR_MISSING_COMMENT_TERMINATOR -3
#define LEX_ERROR_MISSING_STRING_TERMINATOR -4
//___________________________ Binary operators
#define LEX_PLUS 0
#define LEX_MINUS 1
#define LEX_ASTERISK 2
#define LEX_DIVISION 3
#define LEX_EQUAL 4
#define LEX_PERCENT_SIGN 5
//___________________________ Unary operators
#define LEX_MINUS_SIGN 100
#define LEX_PLUS_PLUS 101
#define LEX_MINUS_MINUS 102
//___________________________ Binary expressions
#define LEX_PLUS_EQUAL 200
#define LEX_MINUS_EQUAL 201
#define LEX_PRODUCT_EQUAL 202
#define LEX_DIVISION_EQUAL 203
//_____________________________ Separator
#define LEX_LEFT_PARENTHESIS 300
#define LEX_RIGHT_PARENTHESIS 301
#define LEX_LEFT_BRACKET 302
#define LEX_RIGHT_BRACKET 303
#define LEX_LEFT_CURLY_BRACKET 304
#define LEX_RIGHT_CURLY_BRACKET 305
#define LEX_COMMA 306
#define LEX_DOT 307
#define LEX_SEMICOLON 308
#define LEX_COLON 309
//____________________________ Relation
#define LEX_IS_BIGGER 400
#define LEX_IS_BIGGER_EQ 401
#define LEX_IS_LESS 402
#define LEX_IS_LESS_EQ 403
#define LEX_IS_EQUAL 404
#define LEX_IS_DIFFERENT 405 
//____________________________ Boolean operators
#define LEX_OR 500
#define LEX_AND 501
//____________________________ Control and General
#define LEX_IF 600
#define LEX_ELSE 601
#define LEX_FOR 602
#define LEX_WHILE 603
#define LEX_DO 604
#define LEX_SWITCH 605
#define LEX_CASE 606
#define LEX_BREAK 607
#define LEX_CONTINUE 608
#define LEX_RETURN 609
//_____________________
#define LEX_STRUCT 610
#define LEX_CLASS 611
#define LEX_PRIVATE 612
#define LEX_PROTECTED 613
#define LEX_PUBLIC 614
#define LEX_STATIC 615
#define LEX_NAMESPACE 616
#define LEX_CONST 617
#define LEX_UNSIGNED 618
#define LEX_NUMBER_SIGN 619
#define LEX_AMPERSAND 620
#define LEX_AT 621
#define LEX_APOSTROPHE 622
#define LEX_REVERSE_SOLIDUS 623
#define LEX_TILDE 624
#define LEX_QUESTION_MARK 625
#define LEX_EXCLAMATION_MARK 626
#define LEX_POINTER_ARROW 627
#define LEX_DEFINE 628
#define LEX_INCLUDE 629
#define LEX_BROKEN_BAR 630
//_____________________________ Datatype
#define LEX_DATATYPE_BOOL 700
#define LEX_DATATYPE_INTEGER 701
#define LEX_DATATYPE_DOUBLE 702
#define LEX_DATATYPE_VOID 703
#define LEX_DATATYPE_VECTOR 704
#define LEX_DATATYPE_MATRIX 705
#define LEX_DATATYPE_COMPLEX 706
#define LEX_DATATYPE_COMPLEX_VECTOR 707
#define LEX_DATATYPE_COMPLEX_MATRIX 708
#define LEX_DATATYPE_LAYERNET 709
#define LEX_DATATYPE_KOHONET 710
#define LEX_DATATYPE_PROBNET 711
#define LEX_DATATYPE_CONTROL 712 // For special use only
#define LEX_DATATYPE_CHAR 713
#define LEX_DATATYPE_WCHAR_T 714
#define LEX_DATATYPE_LONG 715
#define LEX_DATATYPE_COUNT (LEX_DATATYPE_PROBNET-LEX_DATATYPE_BOOL+1)
#define LEX_DATATYPE_ALL 799
//______________________________ Value
#define LEX_CONST_VALUE_BOOL 801
#define LEX_CONST_VALUE_INTEGER 802
#define LEX_CONST_VALUE_DOUBLE 803
#define LEX_CONST_VALUE_STRING 804
//_____________________________________  FUNCTION SUBTYPE
#define LEX_FUNC_SIN 900
#define LEX_FUNC_COS 901
#define LEX_FUNC_TAN 902
#define LEX_FUNC_ASIN 903
#define LEX_FUNC_ACOS 904
#define LEX_FUNC_ATAN 905
#define LEX_FUNC_SINH 906
#define LEX_FUNC_COSH 907
#define LEX_FUNC_TANH 908
#define LEX_FUNC_SQRT 909
#define LEX_FUNC_LOG10 910
#define LEX_FUNC_LOG 911
#define LEX_FUNC_EXP 912
#define LEX_FUNC_POW 913
#define LEX_FUNC_ABS 914
#define LEX_FUNC_SINC 915
#define LEX_FUNC_TRIANG 916
#define LEX_FUNC_SAW 917
#define LEX_FUNC_RECT 918
#define LEX_FUNC_CEIL 919
#define LEX_FUNC_FLOOR 920
#define LEX_FUNC_TOINT 921
#define LEX_FUNC_FFT 922
#define LEX_FUNC_IFFT 923
#define LEX_FUNC_REALFFT 924
#define LEX_FUNC_IREALFFT 925
#define LEX_FUNC_SPECTRUM 926
#define LEX_FUNC_CONVOLUTION 927
#define LEX_FUNC_SHORT_CONVOLUTION 928
#define LEX_FUNC_COMPUTE_MSE 929
#define LEX_FUNC_CONFUSION_MATRIX 930
#define LEX_FUNC_RAND 931
//____________________________________ Integer functions
#define LEX_FUNC_RANDI 932
#define LEX_FUNC_ISPRIME 933
//#define LEX_FUNC_BESSELJ0 923
//#define LEX_FUNC_BESSELJ1 924
//#define LEX_FUNC_BESSELY0 925
//#define LEX_FUNC_BESSELY1 926
//_____________________________________ ID
#define LEX_ID 1000
#define LEX_END_OF_FILE 1001

#define LEX_FUNC_LAYERNET_CREATE 1100
#define LEX_FUNC_LAYERNET_LOAD 1101
#define LEX_FUNC_LAYERNET_SAVE 1102
#define LEX_FUNC_LAYERNET_SET_WEIGHTS 1103
#define LEX_FUNC_LAYERNET_GET_WEIGHTS 1104
#define LEX_FUNC_LAYERNET_GET_INPUT_COUNT 1105
#define LEX_FUNC_LAYERNET_GET_OUTPUT_COUNT 1106
#define LEX_FUNC_LAYERNET_GET_HIDD1_NEU_COUNT 1107
#define LEX_FUNC_LAYERNET_GET_HIDD2_NEU_COUNT 1108
#define LEX_FUNC_LAYERNET_GET_LAYER_COUNT 1109
#define LEX_FUNC_LAYERNET_DELETE 1110
#define LEX_FUNC_LAYERNET_UNLEARN 1111
#define LEX_FUNC_LAYERNET_AUTO_SET_INPUT_SCALER 1112
#define LEX_FUNC_LAYERNET_AUTO_SET_OUTPUT_SCALER 1113
#define LEX_FUNC_LAYERNET_SET_INPUT_SCALER 1114
#define LEX_FUNC_LAYERNET_SET_OUTPUT_SCALER 1115
#define LEX_FUNC_LAYERNET_GET_INPUT_SCALER 1116
#define LEX_FUNC_LAYERNET_GET_OUTPUT_SCALER 1117
#define LEX_FUNC_LAYERNET_SET_TRAINING_SET 1118
#define LEX_FUNC_LAYERNET_TRAIN_GENETIC 1119
#define LEX_FUNC_LAYERNET_TRAIN_SIMULATE_ANNEALING 1120
#define LEX_FUNC_LAYERNET_TRAIN_CONJUGATE_GRADIENT 1121
#define LEX_FUNC_LAYERNET_TRAIN_VARIABLE_METRIC 1122
#define LEX_FUNC_LAYERNET_TRAIN_LEVENBERG_MARQUARDT 1123
#define LEX_FUNC_LAYERNET_TRAIN_REGRESSION 1124
#define LEX_FUNC_LAYERNET_GET_MIN_NUM_TRAIN_CASES 1125
#define LEX_FUNC_LAYERNET_RUN 1126
//
#define LEX_FUNC_KOHONET_CREATE 1201
#define LEX_FUNC_KOHONET_LOAD 1202
#define LEX_FUNC_KOHONET_SAVE 1203
//
#define LEX_FUNC_PROBNET_CREATE 1300
#define LEX_FUNC_PROBNET_LOAD 1301
#define LEX_FUNC_PROBNET_SAVE 1302
//
#define LEX_FUNC_MATRIX_CREATE 1500
#define LEX_FUNC_MATRIX_CREATE_RANDOM 1501
#define LEX_FUNC_MATRIX_SAVE 1502
#define LEX_FUNC_MATRIX_LOAD 1503
#define LEX_FUNC_MATRIX_APPEND_RIGHT 1504
#define LEX_FUNC_MATRIX_APPEND_DOWN 1505
#define LEX_FUNC_MATRIX_DELETE_ROW 1506
#define LEX_FUNC_MATRIX_DELETE_COL 1507
#define LEX_FUNC_MATRIX_INSERT_ROW 1508
#define LEX_FUNC_MATRIX_INSERT_COL 1509
#define LEX_FUNC_MATRIX_DELETE 1510
#define LEX_FUNC_MATRIX_GET_ROW_COUNT 1511
#define LEX_FUNC_MATRIX_GET_COL_COUNT 1512
#define LEX_FUNC_MATRIX_GET_SUM 1513
#define LEX_FUNC_MATRIX_GET_DIAGONAL_SUM 1514
#define LEX_FUNC_MATRIX_GET_MEAN 1515
#define LEX_FUNC_MATRIX_GET_VARIANCE 1516
#define LEX_FUNC_MATRIX_GET_MINIMUM 1517
#define LEX_FUNC_MATRIX_GET_MAXIMUM 1518
#define LEX_FUNC_MATRIX_GET_SUM_SQUARES 1519
#define LEX_FUNC_MATRIX_GET_ROWS 1520
#define LEX_FUNC_MATRIX_GET_COLS 1521
#define LEX_FUNC_MATRIX_DELETE_ROWS 1522
#define LEX_FUNC_MATRIX_DELETE_COLS 1523
#define LEX_FUNC_MATRIX_GET_CLASS 1524
#define LEX_FUNC_MATRIX_TRANSPOSE 1525
#define LEX_FUNC_MATRIX_NORM_ROWS 1526
#define LEX_FUNC_MATRIX_NORM_COLS 1527
#define LEX_FUNC_MATRIX_ROWS_VAR 1528
#define LEX_FUNC_MATRIX_COLS_VAR 1529
#define LEX_FUNC_MATRIX_GET_ROW 1530
#define LEX_FUNC_MATRIX_GET_COL 1531
//
#define LEX_FUNC_VECTOR_CREATE 1600
#define LEX_FUNC_VECTOR_CREATE_SERIES 1601
#define LEX_FUNC_VECTOR_CREATE_RANDOM 1602
#define LEX_FUNC_VECTOR_CREATE_BINARY 1603
#define LEX_FUNC_VECTOR_SAVE 1604
#define LEX_FUNC_VECTOR_LOAD 1605
#define LEX_FUNC_VECTOR_INSERT_CELL 1606
#define LEX_FUNC_VECTOR_DELETE_CELL 1607
#define LEX_FUNC_VECTOR_GET_SIZE 1608
#define LEX_FUNC_VECTOR_GET_SUM 1609
#define LEX_FUNC_VECTOR_GET_MEAN 1610
#define LEX_FUNC_VECTOR_GET_VARIANCE 1611
#define LEX_FUNC_VECTOR_GET_MINIMUM 1612
#define LEX_FUNC_VECTOR_GET_MAXIMUM 1613
#define LEX_FUNC_VECTOR_GET_SQUARED_SUM 1614
#define LEX_FUNC_VECTOR_CREATE_LOW_PASS_IMP_RESP 1615
#define LEX_FUNC_VECTOR_CREATE_LOW_PASS_FREQ_RESP 1616
#define LEX_FUNC_VECTOR_CREATE_HIGH_PASS_IMP_RESP 1617
#define LEX_FUNC_VECTOR_CREATE_HIGH_PASS_FREQ_RESP 1618
#define LEX_FUNC_VECTOR_CREATE_RANDOM_SET 1619
#define LEX_FUNC_VECTOR_WRAP 1620
#define LEX_FUNC_VECTOR_LINE_FIT 1621
//_____________________________ SQL DATATYPE
#define LEX_SQLTYPE_BIT 1700
//
#define LEX_SQLTYPE_INTEGER 1701
#define LEX_SQLTYPE_SMALLINT 1702
#define LEX_SQLTYPE_BIGINT 1703
#define LEX_SQLTYPE_TINYINT 1704
#define LEX_SQLTYPE_INT 1705
//
#define LEX_SQLTYPE_DOUBLE 1706
#define LEX_SQLTYPE_DECIMAL 1707
#define LEX_SQLTYPE_REAL 1708
#define LEX_SQLTYPE_NUMERIC 1709
#define LEX_SQLTYPE_MONEY 1710
#define LEX_SQLTYPE_SMALLMONEY 1711
//
#define LEX_SQLTYPE_VARCHAR2 1712
#define LEX_SQLTYPE_VARCHAR 1713
#define LEX_SQLTYPE_CHAR 1714
#define LEX_SQLTYPE_TEXT 1715
#define LEX_SQLTYPE_NVARCHAR 1716
#define LEX_SQLTYPE_NCHAR 1717
#define LEX_SQLTYPE_NTEXT 1718
//
#define LEX_SQLTYPE_DATETIME 1719
#define LEX_SQLTYPE_DATETIME2 1720
#define LEX_SQLTYPE_SMALLDATETIME 1721
#define LEX_SQLTYPE_DATE 1722
#define LEX_SQLTYPE_TIME 1723
#define LEX_SQLTYPE_TIMESTAMP 1724
//_____________________________ SQL MAIN
#define LEX_SQL_CREATE 1800
#define LEX_SQL_INSERT 1801
#define LEX_SQL_UPDATE 1802
#define LEX_SQL_SELECT 1803
#define LEX_SQL_DELETE 1804
#define LEX_SQL_DROP 1805
#define LEX_SQL_GRANT 1806
#define LEX_SQL_REVOKE 1807
#define LEX_SQL_ROLLBACK 1808
#define LEX_SQL_SAVEPOINT 1809
#define LEX_SQL_USE 1810
#define LEX_SQL_ALTER 1811
//_____________________________ SQL OBJECTS
#define LEX_SQL_TABLE 1900
#define LEX_SQL_VIEW 1901
#define LEX_SQL_TRIGGER 1902
#define LEX_SQL_INDEX 1903
#define LEX_SQL_PROCEDURE 1904
#define LEX_SQL_DATABASE 1905
#define LEX_SQL_CURSOR 1906
//_____________________________ SQL KEYWORDS
#define LEX_SQL_WHERE 2000
#define LEX_SQL_FROM 2001
#define LEX_SQL_AS 2002
#define LEX_SQL_GROUP 2003
#define LEX_SQL_ORDER 2004
#define LEX_SQL_CONSTRAINT 2005
#define LEX_SQL_IDENTITY 2006
#define LEX_SQL_AUTO_INCREMENT 2007
#define LEX_SQL_INNER 2008
#define LEX_SQL_JOIN 2009
#define LEX_SQL_ON 2010
#define LEX_SQL_UNIQUE 2011
#define LEX_SQL_BY 2012
#define LEX_SQL_HAVING 2013
#define LEX_SQL_UNION 2014
#define LEX_SQL_INTERSECT 2015
#define LEX_SQL_INTO 2016
#define LEX_SQL_VALUES 2017
#define LEX_SQL_REPLACE 2018
#define LEX_SQL_PRIMARY 2019
#define LEX_SQL_FOREIGN 2020
#define LEX_SQL_KEY 2021
#define LEX_SQL_REFERENCES 2022
#define LEX_SQL_CASCADE 2023
#define LEX_SQL_AND 2024
#define LEX_SQL_OR 2025
#define LEX_SQL_NOT 2026
#define LEX_SQL_BEGIN 2027
#define LEX_SQL_END 2028
#define LEX_SQL_DISTINCT 2029
#define LEX_SQL_LIKE 2030
#define LEX_SQL_CHECK 2031
#define LEX_SQL_READ 2032
#define LEX_SQL_ONLY 2033
#define LEX_SQL_READ_ONLY 2034
#define LEX_SQL_OPTION 2035
#define LEX_SQL_TRANSACTION 2036
#define LEX_SQL_COMMIT 2037
#define LEX_SQL_SET 2038
#define LEX_SQL_IF 2039
#define LEX_SQL_WITH 2040
#define LEX_SQL_RAISERROR 2041
#define LEX_SQL_GO 2042
#define LEX_SQL_DECLARE 2043
#define LEX_SQL_FOR 2044
#define LEX_SQL_OPEN 2045
#define LEX_SQL_CLOSE 2046
#define LEX_SQL_WHILE 2047
#define LEX_SQL_NEXT 2048
#define LEX_SQL_FETCH 2049
#define LEX_SQL_DEALLOCATE 2050
#define LEX_SQL_RETURN 2051
#define LEX_SQL_CASE 2052
#define LEX_SQL_FETCH_STATUS 2053
#define LEX_SQL_EXISTS 2054
#define LEX_SQL_DBO 2055
#define LEX_SQL_DEFAULT 2056
#define LEX_SQL_NULL 2057

//_____________________________ SQL FUNCTIONS
#define LEX_SQL_ABS 2100
#define LEX_SQL_MOD 2101
#define LEX_SQL_TRUNCATE 2102
#define LEX_SQL_POWER 2103
#define LEX_SQL_ROUND 2104
#define LEX_SQL_AVG 2105
#define LEX_SQL_MIN 2106
#define LEX_SQL_MAX 2107
#define LEX_SQL_SUM 2108
#define LEX_SQL_NVL 2109
#define LEX_SQL_TO_NUMBER 2110
#define LEX_SQL_TO_CHAR 2111
#define LEX_SQL_TO_DATE 2112
#define LEX_SQL_DATEFORMAT 2113
#define LEX_SQL_DATEPART 2114
#define LEX_SQL_DATEDIFF 2115
#define LEX_SQL_ISDATE 2116
#define LEX_SQL_CONVERT 2117
#define LEX_SQL_CAST 2118
#define LEX_SQL_GETDATE 2119
#define LEX_SQL_DB_NAME 2120
//_______________________ Virtual Machine
#define VM_ERROR 10000 
#define VM_CREATE 10001 
#define VM_VALUE 10002
#define VM_REFVALUE 10003
#define VM_SETVALUE 10004
#define VM_SET_VECTORCELL 10005
#define VM_SET_MATRIXCELL 10006
//#define VM_SETREF_VECTORCELL 10007
//#define VM_SETREF_MATRIXCELL 10008
#define VM_VECTOR_CELL 10009
#define VM_MATRIX_CELL 10010
#define VM_OPER 10011
#define VM_OPER_MONO 10012
#define VM_OPER_BINA 10013
#define VM_FUNC 10014
#define VM_OBJFUNC 10015
#define VM_GOTO 10016
#define VM_GOFALSE 10017
#define VM_GOTRUE 10018
#define VM_GUITYPE_LISTVIEW 11000
#define VM_GUITYPE_DROPDOWN 11001
//___________________
#define STERRORMAX 256
//_______________________ Error description
#define ERROR_SYNTAX 1
#define ERROR_VARIABLE_ALLREADY_DEFINED 2
#define ERROR_VARIABLE_NOEXISTS 3
#define ERROR_INVALID_OBJECT_FUNC 4
#define ERROR_VARIABLE_UNINIT 5
#define ERROR_INVALID_PARAM 6
#define ERROR_MISSING_TOKEN 7
#define ERROR_INCOMPLETE_COMMAND 8
#define ERROR_MISSING_VARIABLE 9
#define ERROR_LEX 10
#define ERROR_INVALID_VALUE -1

//________________ for com support
#include <comdef.h> 
#include <comdefsp.h>
#include <exdisp.h>

//__________________________ COM INTERFACES
_COM_SMARTPTR_TYPEDEF(IUnknown, __uuidof(IUnknown));
_COM_SMARTPTR_TYPEDEF(IOleObject, __uuidof(IOleObject));
_COM_SMARTPTR_TYPEDEF(IOleControl, __uuidof(IOleControl));
_COM_SMARTPTR_TYPEDEF(IOleInPlaceObject, __uuidof(IOleInPlaceObject));
_COM_SMARTPTR_TYPEDEF(IOleInPlaceObjectWindowless, __uuidof(IOleInPlaceObjectWindowless));
_COM_SMARTPTR_TYPEDEF(IViewObject, __uuidof(IViewObject));
_COM_SMARTPTR_TYPEDEF(IViewObject2, __uuidof(IViewObject2));
_COM_SMARTPTR_TYPEDEF(IViewObjectEx, __uuidof(IViewObjectEx));
_COM_SMARTPTR_TYPEDEF(IAdviseSink, __uuidof(IAdviseSink));
_COM_SMARTPTR_TYPEDEF(IDataObject, __uuidof(IDataObject));
_COM_SMARTPTR_TYPEDEF(IWebBrowser2, __uuidof(IWebBrowser2));
_COM_SMARTPTR_TYPEDEF(IBindCtx, __uuidof(IBindCtx));
_COM_SMARTPTR_TYPEDEF(IPersistStreamInit, __uuidof(IPersistStreamInit)); 
_COM_SMARTPTR_TYPEDEF(IPersistPropertyBag, __uuidof(IPersistPropertyBag));
_COM_SMARTPTR_TYPEDEF(IPersistPropertyBag2, __uuidof(IPersistPropertyBag2));


//_____________________________________________________________________ Com::Ini
namespace Com 
{

//_______________________________________________________________ ActiveXInfo
class ActiveXInfo
{
public:
	ActiveXInfo();
	~ActiveXInfo();
	wstring descr;
	wstring ProgID;
	wstring VersionIndependentProgID;
	bool operator<(const ActiveXInfo& input) const;
};

//_______________________________________________________________ Error
class Error
{
public:
	static wchar_t* GetDescription(HRESULT hr);
	static void Display(HWND hWnd, _com_error e, wchar_t* caption);
	static void Display(HWND hWnd, HRESULT hr, EXCEPINFO excepInfo, UINT argError, wchar_t * caption);
};

//_______________________________________________________________ ExceptionInfo
class ExceptionInfo
{
public:
	ExceptionInfo();
	ExceptionInfo(HRESULT hr, const wstring& caption);
	~ExceptionInfo();
	//Com::ExceptionInfo& operator =(const Com::ExceptionInfo& ei);
	Com::ExceptionInfo& operator =(const HRESULT hr);
	wstring caption;
	HRESULT hr;
	void GetDescription(wstring& result);
};

//_______________________________________________________________ Exception
class Exception
{
public:
	Exception();
	~Exception();
	//Exception& operator =(const Exception& init);
	//Exception& operator =(const HRESULT hr);
	Com::ExceptionInfo& operator[](wchar_t* caption);
protected:
	ExceptionInfo ei;
};

//-----------------------------------------------------------------------------
// Copyright (c) 2000-04 Mike Morearty <mike@morearty.com>
// Original source and docs: http://www.morearty.com/code/dispatch
//
// CDispatchPtr helper class
//
// Usage of this class:
//
// CDispatchPtr is a wrapper for an IDispatch pointer.  It inherits from, and
// thus shares capabilities with, the C runtime's IDispatchPtr class.
//
// What CDispatchPtr adds is member functions to make it very easy to get/put
// properties and invoke methods via IDispatch.  Some examples:
//
//		CDispatchPtr htmlDoc; // assume this points to an IE HTML document
//
//		_bstr_t title = htmlDoc.Get("title");
//		htmlDoc.Put("title", "new title");
//		htmldoc.Get("body").Get("firstChild").Invoke(
//						"insertAdjacentText", "afterBegin", "hello world");
//		_bstr_t html = htmldoc.Get("body").Get("innerHTML");
//		long height = htmldoc.Get("body").Get("clientHeight");
//		CDispatchPtr body = htmlDoc.Get("body");
//-----------------------------------------------------------------------------
class CDispatchVariant;

template <class Derived>
class CDispatchFunctions
{
public:

	// Throughout this class, for any function which is templated on type
	// <DispatchItem>, the DispatchItem identifies one method or property
	// of an object, and the value passed for the DispatchItem should be
	// either a (char*), a (wchar_t*), or a DISPID.

	// Get: get a property's value
	template <class DispatchItem>
	CDispatchVariant Get(DispatchItem property);

	// Put: put a property's value
	template <class DispatchItem>
	void Put(DispatchItem property, const _variant_t& value);

	// PutRef: put a reference to a property's value
	template <class DispatchItem>
	void PutRef(DispatchItem property, const _variant_t& value);

	// Invoke: invoke a method
	template <class DispatchItem>
	CDispatchVariant Invoke(DispatchItem method);

	template <class DispatchItem>
	CDispatchVariant Invoke(DispatchItem method,
							const _variant_t& arg1);

	template <class DispatchItem>
	CDispatchVariant Invoke(DispatchItem method,
							const _variant_t& arg1,
							const _variant_t& arg2);

	template <class DispatchItem>
	CDispatchVariant Invoke(DispatchItem method,
							const _variant_t& arg1,
							const _variant_t& arg2,
							const _variant_t& arg3);

	template <class DispatchItem>
	CDispatchVariant Invoke(DispatchItem method,
							const _variant_t& arg1,
							const _variant_t& arg2,
							const _variant_t& arg3,
							const _variant_t& arg4);

	template <class DispatchItem>
	CDispatchVariant Invoke(DispatchItem method,
							const _variant_t& arg1,
							const _variant_t& arg2,
							const _variant_t& arg3,
							const _variant_t& arg4,
							const _variant_t& arg5);

	template <class DispatchItem>
	CDispatchVariant Invoke(DispatchItem method,
							const _variant_t& arg1,
							const _variant_t& arg2,
							const _variant_t& arg3,
							const _variant_t& arg4,
							const _variant_t& arg5,
							const _variant_t& arg6);

	template <class DispatchItem>
	CDispatchVariant Invoke(DispatchItem method,
							const _variant_t& arg1,
							const _variant_t& arg2,
							const _variant_t& arg3,
							const _variant_t& arg4,
							const _variant_t& arg5,
							const _variant_t& arg6,
							const _variant_t& arg7);

	template <class DispatchItem>
	CDispatchVariant Invoke(DispatchItem method,
							const _variant_t& arg1,
							const _variant_t& arg2,
							const _variant_t& arg3,
							const _variant_t& arg4,
							const _variant_t& arg5,
							const _variant_t& arg6,
							const _variant_t& arg7,
							const _variant_t& arg8);

	template <class DispatchItem>
	CDispatchVariant Invoke(DispatchItem method,
							const _variant_t& arg1,
							const _variant_t& arg2,
							const _variant_t& arg3,
							const _variant_t& arg4,
							const _variant_t& arg5,
							const _variant_t& arg6,
							const _variant_t& arg7,
							const _variant_t& arg8,
							const _variant_t& arg9);

protected:
	void InvokeHelper(DISPID dispatchItem,
					  const VARIANT* params,
					  int cParams,
					  WORD invokeType,
					  VARIANT* result)
	{
		IDispatch* disp = *(Derived*)this;
		DISPPARAMS dispparams = { const_cast<VARIANT*>(params), 0, cParams, 0 };
		HRESULT hr;
		DISPID dispidPut;

		if (invokeType == DISPATCH_PROPERTYPUT ||
			invokeType == DISPATCH_PROPERTYPUTREF)
		{
			dispidPut = DISPID_PROPERTYPUT;

			dispparams.cNamedArgs = 1;
			dispparams.rgdispidNamedArgs = &dispidPut;
		}

		// A hard-coded assumption that "result" does NOT already
		// contain a valid variant!
		if (result)
			V_VT(result) = VT_EMPTY;

		hr = disp->Invoke(dispatchItem, IID_NULL, LOCALE_SYSTEM_DEFAULT,
			invokeType, &dispparams, result, NULL, NULL);
		if (FAILED(hr))
			_com_raise_error(hr);
	}

	// dispatchItem is (wchar_t*) -- convert it to a DISPID
	void InvokeHelper(LPCOLESTR dispatchItem,
					  const VARIANT* params,
					  int cParams,
					  WORD invokeType,
					  VARIANT* result)
	{
		IDispatch* disp = *(Derived*)this;
		DISPID dispid;
		HRESULT hr;

		hr = disp->GetIDsOfNames(IID_NULL, const_cast<LPOLESTR*>(&dispatchItem), 1,
			LOCALE_SYSTEM_DEFAULT, &dispid);
		if (FAILED(hr))
		{
			if (hr == DISP_E_UNKNOWNNAME && invokeType == DISPATCH_PROPERTYGET)
			{
				if (result)
					V_VT(result) = VT_EMPTY;
				return;
			}
			else
			{
				_com_raise_error(hr);
			}
		}

		// call the DISPID overload of InvokeHelper()
		InvokeHelper(dispid, params, cParams, invokeType, result);
	}

	// dispatchItem is an Ansi LPSTR  -- convert it to an LPOLESTR
	void InvokeHelper(LPCSTR dispatchItem,
					  const VARIANT* params,
					  int cParams,
					  WORD invokeType,
					  VARIANT* result)
	{
		OLECHAR nameBuff[256]; // try to avoid doing an allocation
		LPOLESTR wideName;

		int cch = lstrlen(dispatchItem) + 1;
		if (cch <= sizeof(nameBuff) / sizeof(OLECHAR))
			wideName = nameBuff;
		else
		{
			// dispatch item name is longer than our fixed-size buffer; allocate.
			// Do NOT use alloca() [or ATL's A2W(), which uses alloca()], because
			// this is function may be inlined (although that's not likely), and
			// that could cause a stack overflow if this function is called from
			// within a loop

			wideName = new OLECHAR[cch]; // cch may be just a bit bigger than necessary
			if (wideName == NULL)
				_com_raise_error(E_OUTOFMEMORY);
		}

		wideName[0] = '\0';
		MultiByteToWideChar(CP_ACP, 0, dispatchItem, -1, wideName, cch);

		// call the LPOLESTR overload of InvokeHelper()
		InvokeHelper(wideName, params, cParams, invokeType, result);

		if (wideName != nameBuff)
			delete[] wideName;
	}
};


//-----------------------------------------------------------------------------
// CDispatchVariant - a helper class for internal use, usually not needed by
// users of this code, but possibly useful on occasion.  This subclasses
// _variant_t and provides it with the Get/Put/PutRef/Invoke methods.  It only
// makes sense to do that if the _variant_t contains, or can be cast to, an
// IDispatch pointer -- that is, V_VT(variant) == VT_DISPATCH.
//
// In the Get/Put/PutRef/Invoke methods from CDispatchFunctions, the expression
// "*(Derived*)this" is used where an (IDispatch*) is needed.  In the case
// of CDispatchVariant, that expression will succeed if the variant contains
// (or can be cast to) and (IDispatch*), and will throw a _com_error object
// (with appropriate error code) if not.
//-----------------------------------------------------------------------------

class CDispatchVariant :
	public _variant_t,
	public CDispatchFunctions<CDispatchVariant>
{
public:

	// constructors -- just copied (with slight modifications) from _variant_t

	CDispatchVariant() throw() : _variant_t() { }

	CDispatchVariant(const VARIANT& varSrc) : _variant_t(varSrc) { }
	CDispatchVariant(const VARIANT* pSrc) : _variant_t(pSrc) { }
	CDispatchVariant(const _variant_t& varSrc) : _variant_t(varSrc) { }

	CDispatchVariant(VARIANT& varSrc, bool fCopy) : _variant_t(varSrc, fCopy) { }

	CDispatchVariant(IDispatch* pSrc, bool fAddRef = true) throw() : _variant_t(pSrc, fAddRef) { }
	CDispatchVariant(IUnknown* pSrc, bool fAddRef = true) throw() : _variant_t(pSrc, fAddRef) { }

	// operator=() -- just copied (with slight modifications) from _variant_t

	_variant_t& operator=(const VARIANT& varSrc)
		{ return _variant_t::operator=(varSrc); }
	_variant_t& operator=(const VARIANT* pSrc)
		{ return _variant_t::operator=(pSrc); }
	_variant_t& operator=(const _variant_t& varSrc)
		{ return _variant_t::operator=(varSrc); }

	_variant_t& operator=(IDispatch* pSrc)
		{ return _variant_t::operator=(pSrc); }
	_variant_t& operator=(IUnknown* pSrc)
		{ return _variant_t::operator=(pSrc); }

	// operator->()

	IDispatch* operator->() const
		{ return (IDispatch*)*this; }

	// operator bool()

	operator bool() const
	{
		if (vt == VT_DISPATCH)
			return (pdispVal != NULL);
		else
			return _variant_t::operator bool();
	}
};


//-----------------------------------------------------------------------------
// CDispatchPtr - the main class
//
// Use this class wherever you would have used IDispatchPtr.  Then, to get/put
// properties and invoke methods, use the Get, Set, and Invoke members
// inherited from CDispatchFunctions.
//-----------------------------------------------------------------------------

class CDispatchPtr :
	public IDispatchPtr,
	public CDispatchFunctions<CDispatchPtr>
{
public:

	// constructors -- just copied (with slight modifications) from _com_ptr_t

	template<typename _InterfacePtr> CDispatchPtr(const _InterfacePtr& p) : IDispatchPtr(p) { }
	CDispatchPtr() throw() { }
	CDispatchPtr(int null) : IDispatchPtr(null) { }
	CDispatchPtr(Interface* pInterface) throw() : IDispatchPtr(pInterface) { }
	CDispatchPtr(Interface* pInterface, bool fAddRef) throw() : IDispatchPtr(pInterface, fAddRef) { }
	explicit CDispatchPtr(const CLSID& clsid, IUnknown* pOuter = NULL, DWORD dwClsContext = CLSCTX_ALL)
		: IDispatchPtr(clsid, pOuter, dwClsContext) { }
	explicit CDispatchPtr(LPOLESTR str, IUnknown* pOuter = NULL, DWORD dwClsContext = CLSCTX_ALL)
		: IDispatchPtr(str, pOuter, dwClsContext) { }
	explicit CDispatchPtr(LPCSTR str, IUnknown* pOuter = NULL, DWORD dwClsContext = CLSCTX_ALL)
		: IDispatchPtr(str, pOuter, dwClsContext) { }

	// operator=() -- just copied (with slight modifications) from _com_ptr_t

	template<typename _InterfacePtr> CDispatchPtr& operator=(const _InterfacePtr& p)
		{ IDispatchPtr::operator=(p); return *this; }
	CDispatchPtr& operator=(Interface* pInterface) throw()
		{ IDispatchPtr::operator=(pInterface); return *this; }
	CDispatchPtr& operator=(int null)
		{ IDispatchPtr::operator=(null); return *this; }
};


//-----------------------------------------------------------------------------
// Inline functions from CDispatchFunctions
//-----------------------------------------------------------------------------

// Get: get a property's value
template <class Derived>
template <class DispatchItem>
CDispatchVariant CDispatchFunctions<Derived>::Get(DispatchItem property)
{
	VARIANT result;
	InvokeHelper(property, NULL, 0, DISPATCH_PROPERTYGET, &result);
	return result;
}

// Put: put a property's value
template <class Derived>
template <class DispatchItem>
void CDispatchFunctions<Derived>::Put(DispatchItem property, const _variant_t& value)
{
	InvokeHelper(property, &value, 1, DISPATCH_PROPERTYPUT, NULL);
}

// PutRef: put a reference to a property's value
template <class Derived>
template <class DispatchItem>
void CDispatchFunctions<Derived>::PutRef(DispatchItem property, const _variant_t& value)
{
	InvokeHelper(property, &value, 1, DISPATCH_PROPERTYPUTREF, NULL);
}

// Invoke: invoke a method
template <class Derived>
template <class DispatchItem>
CDispatchVariant CDispatchFunctions<Derived>::Invoke(DispatchItem method)
{
	VARIANT result;
	InvokeHelper(method, NULL, 0, DISPATCH_METHOD, &result);
	return result;
}

template <class Derived>
template <class DispatchItem>
CDispatchVariant CDispatchFunctions<Derived>::Invoke(DispatchItem method,
						const _variant_t& arg1)
{
	VARIANT result;
	InvokeHelper(method, &arg1, 1, DISPATCH_METHOD, &result);
	return result;
}

template <class Derived>
template <class DispatchItem>
CDispatchVariant CDispatchFunctions<Derived>::Invoke(DispatchItem method,
						const _variant_t& arg1,
						const _variant_t& arg2)
{
	VARIANT result;
	VARIANT args[2];

	args[0] = arg2;
	args[1] = arg1;

	InvokeHelper(method, args, 2, DISPATCH_METHOD, &result);
	return result;
}

template <class Derived>
template <class DispatchItem>
CDispatchVariant CDispatchFunctions<Derived>::Invoke(DispatchItem method,
						const _variant_t& arg1,
						const _variant_t& arg2,
						const _variant_t& arg3)
{
	VARIANT result;
	VARIANT args[3];

	args[0] = arg3;
	args[1] = arg2;
	args[2] = arg1;

	InvokeHelper(method, args, 3, DISPATCH_METHOD, &result);
	return result;
}

template <class Derived>
template <class DispatchItem>
CDispatchVariant CDispatchFunctions<Derived>::Invoke(DispatchItem method,
						const _variant_t& arg1,
						const _variant_t& arg2,
						const _variant_t& arg3,
						const _variant_t& arg4)
{
	VARIANT result;
	VARIANT args[4];

	args[0] = arg4;
	args[1] = arg3;
	args[2] = arg2;
	args[3] = arg1;

	InvokeHelper(method, args, 4, DISPATCH_METHOD, &result);
	return result;
}

template <class Derived>
template <class DispatchItem>
CDispatchVariant CDispatchFunctions<Derived>::Invoke(DispatchItem method,
						const _variant_t& arg1,
						const _variant_t& arg2,
						const _variant_t& arg3,
						const _variant_t& arg4,
						const _variant_t& arg5)
{
	VARIANT result;
	VARIANT args[5];

	args[0] = arg5;
	args[1] = arg4;
	args[2] = arg3;
	args[3] = arg2;
	args[4] = arg1;

	InvokeHelper(method, args, 5, DISPATCH_METHOD, &result);
	return result;
}

template <class Derived>
template <class DispatchItem>
CDispatchVariant CDispatchFunctions<Derived>::Invoke(DispatchItem method,
						const _variant_t& arg1,
						const _variant_t& arg2,
						const _variant_t& arg3,
						const _variant_t& arg4,
						const _variant_t& arg5,
						const _variant_t& arg6)
{
	VARIANT result;
	VARIANT args[6];

	args[0] = arg6;
	args[1] = arg5;
	args[2] = arg4;
	args[3] = arg3;
	args[4] = arg2;
	args[5] = arg1;

	InvokeHelper(method, args, 6, DISPATCH_METHOD, &result);
	return result;
}

template <class Derived>
template <class DispatchItem>
CDispatchVariant CDispatchFunctions<Derived>::Invoke(DispatchItem method,
						const _variant_t& arg1,
						const _variant_t& arg2,
						const _variant_t& arg3,
						const _variant_t& arg4,
						const _variant_t& arg5,
						const _variant_t& arg6,
						const _variant_t& arg7)
{
	VARIANT result;
	VARIANT args[7];

	args[0] = arg7;
	args[1] = arg6;
	args[2] = arg5;
	args[3] = arg4;
	args[4] = arg3;
	args[5] = arg2;
	args[6] = arg1;

	InvokeHelper(method, args, 7, DISPATCH_METHOD, &result);
	return result;
}

template <class Derived>
template <class DispatchItem>
CDispatchVariant CDispatchFunctions<Derived>::Invoke(DispatchItem method,
						const _variant_t& arg1,
						const _variant_t& arg2,
						const _variant_t& arg3,
						const _variant_t& arg4,
						const _variant_t& arg5,
						const _variant_t& arg6,
						const _variant_t& arg7,
						const _variant_t& arg8)
{
	VARIANT result;
	VARIANT args[8];

	args[0] = arg8;
	args[1] = arg7;
	args[2] = arg6;
	args[3] = arg5;
	args[4] = arg4;
	args[5] = arg3;
	args[6] = arg2;
	args[7] = arg1;

	InvokeHelper(method, args, 8, DISPATCH_METHOD, &result);
	return result;
}

template <class Derived>
template <class DispatchItem>
CDispatchVariant CDispatchFunctions<Derived>::Invoke(DispatchItem method,
						const _variant_t& arg1,
						const _variant_t& arg2,
						const _variant_t& arg3,
						const _variant_t& arg4,
						const _variant_t& arg5,
						const _variant_t& arg6,
						const _variant_t& arg7,
						const _variant_t& arg8,
						const _variant_t& arg9)
{
	VARIANT result;
	VARIANT args[9];

	args[0] = arg9;
	args[1] = arg8;
	args[2] = arg7;
	args[3] = arg6;
	args[4] = arg5;
	args[5] = arg4;
	args[6] = arg3;
	args[7] = arg2;
	args[8] = arg1;

	InvokeHelper(method, args, 9, DISPATCH_METHOD, &result);
	return result;
}
} //___________________________________________________ namespace Com::End

namespace Sys //________________________________________ namespace Sys::Ini
{

//_____________________________________________________________________IError
class IError
{
public:
	virtual void ReportError(bool error, wchar_t* description)=0;
};

//_____________________________________________________________________ Sample8
struct Sample8
{
	__int8 channel_1;
	__int8 channel_2;
};

//_____________________________________________________________________ Sample16
struct Sample16
{
	__int16 channel_1;
	__int16 channel_2;
};

//_____________________________________________________________________ IListFileDirectory
class IListFileDirectory
{
public:
	virtual bool Enumerate(_tfinddata_t& findData)=0; //return false to stop enumerating
};

//_____________________________________________________________________ IListFileDirRecursive
class IListFileDirRecursive
{
public:
	virtual bool Enumerate(const wchar_t* path, _tfinddata_t& findData)=0; //return false to stop enumerating
};

//_____________________________________________________________________ ITextWriterA
class ITextWriterA
{
public:
	virtual bool WriteText(const string& source)=0;
};

//_____________________________________________________________________ ITextWriterW
class ITextWriterW
{
public:
	virtual bool WriteText(const wstring& source)=0;
};

//_____________________________________________________________________ IStorer
class IStorer
{
public:
	virtual int Read(void *data, int bytesToRead) = 0;  // returns number of bytes read
	virtual int Write(const void* data, int bytesToWrite) = 0;  // returns number of bytes written	
};

//_____________________________________________________________________ IVisualStudio
class IVisualStudio
{
public:
	virtual bool GetActiveDocumentFileName(wstring& out_fileName) = 0;
	virtual bool SaveAll(HWND hWnd) = 0;
	virtual bool PasteFromClipboard(HWND hWnd, const wchar_t* fileName) = 0;
	virtual bool SetFileText(HWND hWnd, const wchar_t* fileName, const wchar_t* fileText) = 0;
	virtual bool GetFileText(HWND hWnd, const wchar_t* fileName, wstring& fileText) = 0;
};

//_____________________________________________________________________ Format
/* int - %d
   wchar_t - %c
   wchar_t* - %s
   double - %g
   double - %f */
//   wstring - %s  passing myString.c_str()
static wstring& Format(wstring& text, const wchar_t* format, ...)
{
	va_list arglist;
	va_start(arglist, format);
	int result = -1;
	int bufferSize = 64;
	do
	{
		text.resize(bufferSize);
		result = _vsnwprintf_s((wchar_t*)text.data(), bufferSize, _TRUNCATE, format, arglist);
		bufferSize*=2;
	}
	while(result==-1);
	text.resize(result);
	va_end(arglist);
	return text;
}

//_____________________________________________________________________ DisplayLastError
static void GetLastErrorInformation(wchar_t *buffer, int bufferSize)
{
	LPVOID lpMsgBuf;
	::FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		::GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);

	lstrcpyn(buffer, (wchar_t*)lpMsgBuf, bufferSize);
	buffer[bufferSize-1]='\0';
	::LocalFree( lpMsgBuf );
}

//_____________________________________________________________________ GetLastErrorInformation
static void GetLastErrorInformation(wstring& errorInformation)
{
	LPVOID lpMsgBuf;
	::FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		::GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);

	errorInformation = (wchar_t*)lpMsgBuf;
	::LocalFree( lpMsgBuf );
}

//_____________________________________________________________________ DisplayLastError
static void DisplayLastError(HWND hWndParent, const wchar_t* caption)
{
	if (caption==NULL) caption = L"Error";
	LPVOID lpMsgBuf;
	::FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		::GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);
	::MessageBox(hWndParent, (const wchar_t *)lpMsgBuf, caption, MB_OK | MB_ICONERROR);
	::LocalFree( lpMsgBuf );
}

//_____________________________________________________________________ DisplayLastError
static void DisplayLastError(HWND hWndParent, const wstring& caption)
{
	DisplayLastError(hWndParent, caption.c_str());
}

//_____________________________________________________________________ PointF
struct PointF
{
	double x;
	double y; 
};

//_____________________________________________________________________ Point2D
struct Point2D
{
	float x;
	float y; 
};

//_____________________________________________________________________ Bound2D
// Stores a 2D Point and additional information (dx and dy) that it is used internally for quick collision detection
// A line segment requires two Bound2D objects
// An irregular shape requires a set of Bound2D objects, the first and the last Bound2D object must be equal
class Bound2D
{
public:
	Bound2D();
	~Bound2D();
	float x;
	float y; 
	float dx;
	float dy;
	static bool DoIntersect(vector<Sys::Bound2D>& bounds1, vector<Sys::Bound2D>& bounds2);	
	static bool DoIntersect(Sys::Bound2D& b1, Sys::Bound2D& b2, Sys::Bound2D& b3, Sys::Bound2D& b4);
	static bool DoIntersect(vector<Sys::Bound2D>& bounds1, vector<Sys::Bound2D>& bounds2, Sys::Point2D& out_intersection);	
	static bool DoIntersect(Sys::Bound2D& b1, Sys::Bound2D& b2, Sys::Bound2D& b3, Sys::Bound2D& b4, Sys::Point2D& out_intersection);
	static float ShortestDistance(Sys::Point2D& p1, Sys::Point2D& p2, vector<Sys::Bound2D>& bounds);
	static float Distance(Sys::Point2D& p1, Sys::Point2D& p2);
};

//_____________________________________________________________________ Point3D
struct Point3D
{
	float x;
	float y; 
	float z; 
};
class Rectangle;
//_____________________________________________________________________ RotatedRectangle
class RotatedRectangle
{
public:
	RotatedRectangle();
	~RotatedRectangle();
	Sys::Point2D p1;
	Sys::Point2D p2;
	Sys::Point2D p3;
	Sys::Point2D p4;
	bool IsInsideRegion(const vector<Rectangle>& regionBig) const;
};

//_____________________________________________________________________ Rectangle
class Rectangle
{
public:
	Rectangle();
	~Rectangle();
	float left;
	float top;
	float right;
	float bottom;
	bool IsInside(const RotatedRectangle& rectSmall) const;
	bool IsInside(const Rectangle& rectSmall) const;
	bool IsInside(const Sys::Point2D& point) const;
	bool IsIntersected(const Rectangle& rect) const;
	bool IsInsideRegion(const vector<Rectangle>& regionBig) const;
};

#ifdef WIN_GDI_PLUS_ON
//_____________________________________________________________________ ImageStream
//#undef INTERFACE
//#define INTERFACE ImgStream
class ImageStream: public IStream
{
public:
	static int ImageStream::GetEncoderClsid(const wchar_t* format, CLSID* pClsid);
	//
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR *ppv);
	STDMETHOD_ (ULONG, AddRef) (THIS);
	STDMETHOD_ (ULONG, Release) (THIS);
	//
	STDMETHOD (Read) (THIS_ void *pv, ULONG cb, ULONG *pcbRead);
	STDMETHOD (Write) (THIS_ const void *pv, ULONG cb, ULONG *pcbWritten);
	STDMETHOD (Seek) (THIS_ LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition);
	STDMETHOD (SetSize) (THIS_ ULARGE_INTEGER libNewSize);
	STDMETHOD (CopyTo) (THIS_ IStream *pstm, ULARGE_INTEGER cb, 
		ULARGE_INTEGER *pcbRead, ULARGE_INTEGER *pcbWritten);
	STDMETHOD (Commit) (THIS_ DWORD grfCommitFlags);
	STDMETHOD (Revert) (THIS_);
	STDMETHOD (LockRegion)(THIS_ ULARGE_INTEGER libOffset, ULARGE_INTEGER cb,
		DWORD dwLockType);
	STDMETHOD (UnlockRegion)(THIS_ ULARGE_INTEGER libOffset, ULARGE_INTEGER cb,
		DWORD dwLockType);
	STDMETHOD (Stat)(THIS_ STATSTG *pstatstg, DWORD grfStatFlag);
	STDMETHOD (Clone)(THIS_ IStream **ppstm);
	//
	string *data; // Image data is stored here
#ifndef CINTERFACE
public:
	ImageStream();
	virtual ~ImageStream();
	static IStream* CreateAllocator(string* data);
private:
	ULONG m_nRefCount;
	STATSTG m_sta;
	FILETIME m_filetimeCreation;
	FILETIME m_filetimeLastWrite;
	FILETIME m_filetimeLastRead;
	ULARGE_INTEGER m_cb;
#endif
};
#endif
//_____________________________________________________________________ Stopwatch
class Stopwatch
{
public:
	Stopwatch(void)
	{
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&startTime);
	}

	void Start()
	{
		QueryPerformanceCounter(&startTime);
	}

	__int64 GetMicroseconds() // _snwprintf_s(..., L"%I64i", );
	{
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		return (((now.QuadPart - this->startTime.QuadPart)*1000000)/frequency.QuadPart);
	}

	__int64 GetMilliseconds()  // _snwprintf_s(..., L"%I64i", );
	{
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		return (((now.QuadPart - this->startTime.QuadPart)*1000)/frequency.QuadPart);
	}

	double GetSeconds()
	{
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		const double diff = (double)(now.QuadPart - this->startTime.QuadPart);
		return diff/(double)(frequency.QuadPart);
	}

	virtual ~Stopwatch(void)
	{
	}

private:
	LARGE_INTEGER frequency;
	LARGE_INTEGER startTime;
};

//________________________________________ RunProgram
/************
Sys::RunProgram rp;
string resultado;
rp.Execute(L"ping www.ingenierias.ugto.mx", resultado);
wstring wresultado;
Sys::Convert::FromStringToWstring(resultado, wresultado);
this->MessageBox(wresultado, L"hola", MB_OK);
*************************/
class RunProgram
{
public:
	RunProgram(void);
	virtual ~RunProgram(void);
	bool Execute(const wchar_t* programName);
	bool Execute(const wchar_t* programName, string& output);
	bool Execute(const wchar_t* programName, const wchar_t* workingDirectory, bool showWindow);
	bool Execute(const wchar_t* programName, const wchar_t* workingDirectory, bool showWindow, string& output);
	BOOL Read(LPVOID buffer, DWORD numberOfBytesToRead, LPDWORD numberOfBytesRead);
	void Close();

	// You may use this function by itself to run the default program that opens the specified file
	static bool OpenFile(const wchar_t* filename);
	static bool OpenFile(const wchar_t* filename, const wchar_t* workingDirectory);
	static bool OpenFile(const wstring& filename);
	static bool OpenFile(const wstring& filename, const wstring& workingDirectory);
private:
	HANDLE m_pipeRead;
	SECURITY_ATTRIBUTES m_sa;
	STARTUPINFO m_si;
	PROCESS_INFORMATION m_pi;
};

//________________________________________ Install
class Install
{
public:
	struct ProductInfo
	{
		bool allUsers;
		wchar_t *companyName;
		wchar_t *productName;  // (no spaces are allowed)
		unsigned int versionMayor;  // For Version 5.4 -> versionMayor = 5
		unsigned int versionMinor; // For Version 5.4 -> versionMinor = 4
		wchar_t *fileExtension;  //Required only for file association (starts with a dot followed by three letters)
		wchar_t *objectType;  //Required only for file association  (no spaces are allowed)
		wchar_t *objectDescription;  
		wchar_t *helpLink; //i.e. http://yahoo.com.mx
		wchar_t *description; //i.e. Provides templates to deploy applications
		unsigned int objectIconIndex; //Required only for file association i.e. 0, 1, etc.
	};
	Install(void);
	virtual ~Install(void);
	bool CanAccessRegistry();
	bool InstallSoftware(Sys::Install::ProductInfo& pi, Sys::IError& ierror);
	bool RemoveSoftware(Sys::Install::ProductInfo& pi, Sys::IError& ierror);
	wchar_t* CopyFileToApplicationFolder(Sys::Install::ProductInfo&pi, HINSTANCE hInst, int resourceId, const wchar_t* destinationFile);
	wchar_t *CopyFileTo(HINSTANCE hInst, int resource_id, const wchar_t* destinationFile);
	wchar_t *CopyDeleteFile(HINSTANCE hInst, int resource_id, const wchar_t* destinationFile, Sys::IError& ierror, bool isInstall);
	wchar_t* CopyFileToWindowsFolder(Sys::Install::ProductInfo&pi, HINSTANCE hInst, int resourceId, const wchar_t* destinationFile);
	bool CopyFileToApplicationFolder(Sys::Install::ProductInfo& pi, const wchar_t* sourceFile, const wchar_t* destinationFile);
	bool DeleteFileFromApplicationFolder(Sys::Install::ProductInfo& pi, const wchar_t* destinationFile);
	static bool RegistrySetStringValue(HKEY hkey, PCTSTR pszValueName, PCTSTR pszString);
	const wchar_t* RegistryReadString(HKEY hkey, LPCTSTR pszPathAndName, LPCTSTR pszValueName);
	const wchar_t* GetProgramFilesPath(void);
	const wchar_t* GetDesktopPath(void);
	const wchar_t* GetMyDocumentsPath(void);
	const wchar_t* GetStartupMenuProgramsPath(void);
	const wchar_t* GetCurrentDirectory_(void);
	const wchar_t* GetDestinationDirectory(const wchar_t* productName);
	const wchar_t* GetWindowsFolder();
	static bool CreateShortCut(const wchar_t* destinationFileName,  const wchar_t* description, 
		const wchar_t* shortcutFilename, const wchar_t* workingDirectory, const wchar_t* fileNameIco_exe, int iIcon);
	bool InstallSoftware1(Sys::Install::ProductInfo& pi, Sys::IError& ierror, bool isInstall);
	bool InstallSoftware2(Sys::Install::ProductInfo& pi, Sys::IError& ierror, bool isInstall);
	bool InstallSoftware3(Sys::Install::ProductInfo& pi, Sys::IError& ierror, bool isInstall);
	bool InstallSoftware4(Sys::Install::ProductInfo& pi, Sys::IError& ierror, bool isInstall, const wchar_t* fileNameIco_exe, int iIcon);
	bool InstallSoftware5(Sys::Install::ProductInfo& pi, Sys::IError& ierror, bool isInstall);
	bool InstallSoftware6(Sys::Install::ProductInfo& pi, Sys::IError& ierror, bool isInstall);
	bool ApplicationFolder(Sys::Install::ProductInfo& pi, Sys::IError& ierror, bool isInstall);
	bool ApplicationShortcut(Sys::Install::ProductInfo& pi, Sys::IError& ierror, bool isInstall);
	bool RemoveShortcut(const wchar_t* productName);
private:
	wchar_t buffer[SYS_INSTBUFF];
};

//_____________________________________________________________________ Key
class Key
{
public:
	Key(HKEY type, Sys::IError& ierror); //HKEY_LOCAL_MACHINE, HKEY_CURRENT_USER, HKEY_CLASSES_ROOT
	Key(HKEY type); 
	~Key(void);
	bool Create(wchar_t* name);
	bool Open(wchar_t* name);
	bool Open(wchar_t* name, REGSAM access); //KEY_READ, KEY_WRITE, KEY_SET_VALUE, KEY_CREATE_SUB_KEY, KEY_EXECUTE, KEY_ALL_ACCESS
	bool Close();
	bool Set(wchar_t* name, wchar_t* value);// To set the default use L"" or NULL in the name
	bool DeleteSubkey(wchar_t* name);// To delete the default use L"" or NULL in the name
	bool Set(wchar_t* name, DWORD value);// To set the default use L"" or NULL in the name
	wchar_t* ReadStringValue(const wchar_t* valueName);
	wchar_t* Enumerate(int index);
private:
	HKEY type;
	HKEY hkey;
	wchar_t name[SYS_INSTBUFF];
	Sys::IError * ierror;
};

//bool WizEnd::InstallSoftware(void)
//{
//	Sys::Install setup;
//	Sys::Install::ProductInfo pi;
//	::memset(&pi, 0, sizeof(Sys::Install::ProductInfo));
//	pi.allUsers =true;
//	pi.companyName =_T("Sergio Ledesma");
//	pi.fileExtension = NULL;  //_T(".txs");
//	pi.objectDescription = NULL;  //_T("Sergio object");
//	pi.objectType = NULL; //_T("SergioObject");
//	pi.productName = _T("Wintempla");
//	pi.versionMayor = 1;
//	pi.versionMinor = 0;
//	pi.helpLink = _T("http://www.fimee.ugto.mx");
// pi.objectIconIndex = 1;  // Edit the resource.h and Product.rc files, 0 is the proyect icon, 1 is the second icon in these files
//   To know the icon index you can create a shortcut and change the icon using the Product.exe file
//
//	const wchar_t *error = setup.InstallSoftware(pi);
//	if (error) 
//	{
//		this->MessageBox(error, _T("WizEnd::InstallSoftware"), MB_OK | MB_ICONERROR);
//	}
//	else
//	{
//		setup.CopyFileToApplicationFolder(pi, _T("Wintempla.ex_"), _T("Wintempla.exe"));
//		setup.CopyFileToApplicationFolder(pi, _T("Wintempla.ch_"), _T("Wintempla.chm"));
//	}
//
//	return true;
//}
//_____________________________________________________________________ FileDirectory
class FileDirectory
{
public:
	struct FileInfo
	{
		_tfinddata_t findData;
		wstring path;
	};
	static int GetFileList(const wchar_t* path, Sys::IListFileDirectory* ilfd);

	//vector<_tfinddata_t> result
	//Sys::FileDirectory::GetFileList(L"C:\\*.txt", result);
	static int GetFileList(const wchar_t* path, vector<_tfinddata_t>& result);
	static int GetFileListRecursive(const wchar_t* path, const wchar_t* filter, Sys::IListFileDirRecursive* ilfd);
	static int GetFileListRecursive(const wchar_t* path, const wchar_t* filter, vector<FileInfo>& result);
	static bool IsDirectory(_tfinddata_t& fd);
	static bool CopyFolderStructure(const wchar_t* sourcePath, const wchar_t* destinationPath); 
	static bool DeleteFolder(const wchar_t* folder);
};


//_____________________________________________________________________ Time
class Time : public SYSTEMTIME
{
public:
	Time();
	Time(SYSTEMTIME st);
	~Time();
	Time(const Sys::Time& init);
	Time& operator=(const Sys::Time& init);
	void SetToLocalTime();
	void SetToUtcTime();
	void Set(int day, int month, int year, int hour, int minute, int second, int milliseconds);

	//Since January 1, 1601.
	double GetSeconds() const ;
	Sys::Time& AddSeconds(double seconds);
	Sys::Time& AddMinutes(double minutes);
	Sys::Time& AddHours(double hours);
	Sys::Time& AddDays(double days);

	static Sys::Time Now();
	
	bool operator==(const Sys::Time& st) const;
	bool operator!=(const Sys::Time& st) const;
	bool operator<(const Sys::Time& st) const;
	bool operator<=(const Sys::Time& st) const;
	bool operator>(const Sys::Time& st) const;
	bool operator>=(const Sys::Time& st) const;
};

//_____________________________________________________________________ SqlTime
struct SqlTime
{
public:
	SqlTime();
	~SqlTime();
	WORD year;
	WORD month;
	WORD day;
	WORD hour;
	WORD minute;
	WORD second;
	WORD milliseconds;
	WORD empty;
	operator Sys::Time&();
private:
	Sys::Time systime;
};

//_____________________________________________________________________ LowResStopwatch
class LowResStopwatch
{
public:
	LowResStopwatch();
	~LowResStopwatch();
	void Start();
	double GetSeconds();
private:
	Sys::Time start;
};

//_____________________________________________ EMail
struct EMail
{
	wstring fromName;
	wstring fromEmail;
	wstring toName;
	wstring toEmail;
	wstring subject;
	wstring body;
	wstring attachmentFileName;
	bool isHtmlFormat;
};


#ifdef WIN_SOCKETS_SUPPORT
//_____________________________________________ Socket
class Socket
{
public:
	Socket(void);
	virtual ~Socket(void);
	//
	void Attach(SOCKET& inputSocket);
	//Socket (const Socket& init) // Copy constructor
	//Socket& operator =(const Socket& init) //Operator =
	char* GetStatus();
	char* GetVersion();
	wchar_t* Connect(SOCKADDR_IN& sockAddr);
	wchar_t* Connect(unsigned short port, const wchar_t* ipAddress);
	wchar_t* Connect(const wchar_t* serverName, unsigned short port);
	//
	wchar_t* ConnectAsync(HWND hWnd, SOCKADDR_IN& sockAddr); // Asyncronous connect, it will send WM_SOCKETNOTIFY to hWnd
	wchar_t* ConnectAsync(HWND hWnd, unsigned short port, const wchar_t* ipAddress); // Asyncronous connect, it will send WM_SOCKETNOTIFY to hWnd
	wchar_t* ConnectAsync(HWND hWnd, const wchar_t* serverName, unsigned short port); // Asyncronous connect, it will send WM_SOCKETNOTIFY to hWnd
	wchar_t* ConnectAsyncServer(HWND hWnd, unsigned short port, int numbClients);
	wchar_t* StartServer(unsigned short port, int numbClients);
	wchar_t* ConnectAsyncClient(HWND hWnd, unsigned short port, const wchar_t* ipAddress);
	//
	virtual void Disconnect();
	void Close();
	SOCKET Accept();
	//
	//int Send(char *buffer, bool removeReturn, bool addCtrl);
	int Send(const char *buffer);
	int Send(const char *buffer, int bufferSize, int flags);
	//
	int Receive(char* buffer, int bufferSize);
	int Receive( char* buffer, int bufferSize, int flags);
	int ReceiveCode();
	int ReceiveCodeAsync();
	int ReceiveLine(string& buffer);
	//
	LPHOSTENT GetHostByName(const wchar_t* serverName);
	LPSTR GetIpAddressByName(const wchar_t* serverName);
	int GetServicePortByName(const wchar_t* serviceName);
	//
	static wchar_t* ReadHttp(const wchar_t* serverName, const wchar_t* uri, wstring& result);
	//
	operator SOCKET();
	static void RemoveReturn(char* text);
	static wchar_t* GetErrorDescr(WORD error);
	static wchar_t* GetLastErrorDesc();
protected:
	static WSADATA wsdata;
	SOCKET hsocket;
	bool isCopy;
	void Constructor();
private:
	static int objectCount;
};

#endif

//_____________________________________________________________________ Brushes
class Brushes
{
public:
	static HBRUSH WhiteBrush();
	static HBRUSH DkGrayBrush();
	static HBRUSH HollowBrush();
	static HBRUSH LtGrayBrush();
	static HBRUSH GrayBrush();
	static HBRUSH BlackBrush();
	static HBRUSH NullBrush();
};

//_____________________________________________________________________ Colors
class Colors
{
public:
	static COLORREF WindowColor();
	static COLORREF ActiveBorderColor();
	static COLORREF ActiveCaptionColor();
	static COLORREF AppWorkspaceColor();
	static COLORREF BackgroundColor();
	static COLORREF BtnFaceColor();
	static COLORREF BtnShadowColor();
	static COLORREF BtnTextColor();
	static COLORREF BtnHighLightColor();
	static COLORREF ThreeDDkShadowColor();
	static COLORREF ThreeDLightColor();
	static COLORREF InfoTextColor();
	static COLORREF InfoBkColor();
	static COLORREF CaptionTextColor();
	static COLORREF InactiveCaptionTextColor() ;
	static COLORREF GrayTextColor();
	static COLORREF HighLightColor();
	static COLORREF HighLightTextColor();
	static COLORREF InactiveBorderColor();
	static COLORREF InactiveCaptionColor() ;
	static COLORREF MenuColor();
	static COLORREF MenuTextColor();
	static COLORREF ScrollbarColor();
	static COLORREF WindowFrameColor();
	static COLORREF WindowTextColor();
	static COLORREF HotLightColor();
	static COLORREF GradientActiveCatpionColor();
	static COLORREF GradientInactiveCaptionColor();
};

//_____________________________________________________________________ Metrics
class Metrics
{
public:
	static int GetMinimizedWindowType();
	static int GetSystemStartedType(); //0 Normal boot,1 Fail-safe boot, 2 Fail-safe with network boot
	static int GetMonitorCount();
	static int GetMouseButtonsCount();
	static int GetWindowBorderWidth();
	static int GetWindow3DBorderWidth();
	static int GetCursorWidth();
	static int GetDoubleClickWidth();
	static int GetDragWidth();
	static int GetFixedFrameThickness();
	static int GetFocusBorderWidth();
	static int GetFullScreenWidth();
	static int GetScreenWidth();
	static int GetHScrollWidth();
	static int GetHScrollThumbWidth();
	static int GetIconWidth();
	static int GetIconSpacingWidth();
	static int GetMaximinizedWindowWidth();
	static int GetMaxTrackWidth();
	static int GetMenuCheckWidth();
	static int GetMenuWidth();
	static int GetMinWindowWidth();
	static int GetMinimizedWindowWidth();
	static int GetMinSpacingWidth();
	static int GetMinTrackWidth();
	//static int GetPaddedBorderWidth();
	static int GetTitleBarButtonWidth();
	static int GetSizeFrameWidth();
	static int GetSmallIconWidth();
	static int GetSmallCaptionButtonWidth();
	static int GetVirtualScreenWidth();
	static int GetVScrollWidth();
	static int GetWindowBorderHeight();
	static int GetWindow3DBorderHeight();
	static int GetCaptionHeight();
	static int GetCursorHeight();
	static int GetDlgFrameHeight();
	static int GetDoubleClickHeight();
	static int GetDragHeight();
	static int GetFixedFrameHeight();
	static int GetFocusBorderHeight();
	static int GetFullScreenHeight();
	static int GetHScrollHeight();
	static int GetIconHeight();
	static int GetIconSpacingHeight();
	static int GetKanjiWindowHeight();
	static int GetMaximinzedWindowHeight();
	static int GetMaxTrackHeight();
	static int GetMenuHeight();
	static int GetMenuCheckHeight();
	static int GetMenuSizeHeight();
	static int GetMinWindowHeight();
	static int GetMinimizedWindowHeight();
	static int GetMinSpacingHeight();
	static int GetMinTrackHeight();
	static int GetScreenHeight();
	static int GetTitleBarHeight();
	static int GetSizeFrameHeight();
	static int GetSmallCaptionHeight();
	static int GetSmallIconHeight();
	static int GetSmallCaptionButtonHeight();
	static int GetVirtualScreenHeight();
	static int GetVScrollHeight();
	static int GetVScroolThumbHeight();
	static bool IsShuttingDown();
	static void GetTextMetricsFromDisplay(const wchar_t* fontname, int fontsize, TEXTMETRIC& result);
	static void GetTextMetricsFromDisplay(const wstring& fontname, int fontsize, TEXTMETRIC& result);
	static void GetTextMetricsFromDisplay(TEXTMETRIC& result);
};

//_____________________________________________________________________ Convert
class Convert
{
public:
	static int ToInt(const wchar_t* input);
	static int ToInt(const wstring& input);
	static double ToDouble(const wchar_t* input);
	static double ToDouble(const wstring& input);
	static bool ToBool(const wchar_t* input);
	static bool ToBool(const wstring& input);
	static complex<double> ToComplex(const wstring& input);
	static complex<double> ToComplex(const string& input);
	static MATRIX& ToMatrix(const wchar_t* input, MATRIX& output);
	static MATRIX& ToMatrix(const wstring& input, MATRIX& output);
	static MATRIX& ToMatrix(const char* input, MATRIX& output);
	static MATRIX& ToMatrix(const string& input, MATRIX& output);
	static MATRIX& ToMatrix(const valarray<double>& input, MATRIX& output);
	static MATRIXC& ToMatrix(const wchar_t* input, MATRIXC& output);
	static MATRIXC& ToMatrix(const wstring& input, MATRIXC& output);
	static MATRIXC& ToMatrix(const char* input, MATRIXC& output);
	static MATRIXC& ToMatrix(const string& input, MATRIXC& output);
	static MATRIXC& ToMatrix(const valarray<complex<double> >& input, MATRIXC& output);
	static valarray<double>& ToVector(const wchar_t* input, valarray<double>& output);
	static valarray<double>& ToVector(const wstring& input, valarray<double>& output);
	static valarray<double>& ToVector(const char* input, valarray<double>& output);
	static valarray<double>& ToVector(const string& input, valarray<double>& output);
	//
	static vector<double>& ToVector(const wchar_t* input, vector<double>& output);
	static vector<double>& ToVector(const wstring& input, vector<double>& output);
	static vector<double>& ToVector(const char* input, vector<double>& output);
	static vector<double>& ToVector(const string& input, vector<double>& output);
	//
	static wchar_t* ToVector(const MATRIX& input, int col_index, valarray<double>& output);
	static valarray<complex<double> >& ToVector(const wchar_t* input, valarray<complex<double> >& output);
	static valarray<complex<double> >& ToVector(const wstring& input, valarray<complex<double> >& output);
	static valarray<complex<double> >& ToVector(const char* input, valarray<complex<double> >& output);
	static valarray<complex<double> >& ToVector(const string& input, valarray<complex<double> >& output);
	static wchar_t* ToVector(const MATRIXC& input, int col_index, valarray<complex<double> >& output);
	static Sys::Time& ToTime(const wchar_t* input, Sys::Time& output);
	static Sys::Time& ToTime(const wstring& input, Sys::Time& output);
	static void SqlTimeToSysTime(const Sys::SqlTime& input, Sys::Time& output);
	static void SysTimeToSqlTime(const Sys::Time& input, Sys::SqlTime& output);
#ifdef WIN_SOCKETS_SUPPORT
	static Sys::Time& InternetTimeToSystemTime(unsigned int inputNetworkTime, Sys::Time& output);
#endif
	static int ToYear(wstring& text);
	static int ToMonth(wstring& text);
	static int ToMonthDay(wstring& text);
	//
	static wstring ToString(int input);
	static const wchar_t* ToString(bool input);
	static void ToString(int input, wchar_t* output, int output_size);
	static wstring ToString(double input);
	static wstring ToString(double input, const wchar_t* format);
	static void ToString(double input, wchar_t* output, int output_size, bool compactFormat);
	static void ToString(double input, const wchar_t* format, wchar_t* output, int output_size);
	static wstring ToStringCommaSeparated(int input);
	static void ToStringCommaSeparated(int input, wchar_t* output, int output_size);
	static wstring ToStringUsingCurrencyFormat(double input);
	static void ToStringUsingCurrencyFormat(double input, wchar_t* output, int output_size);
	static wstring& ToString(const MATRIX& input, wstring& output);
	static string& ToString(const MATRIX& input, string& output);
	static wstring& ToString(const MATRIXC& input, wstring& output);
	static string& ToString(const MATRIXC& input, string& output);
	//
	static wstring& ToString(const valarray<double>& input, wstring& output);
	static string& ToString(const valarray<double>& input, string& output);
	static wstring& ToString(const valarray<complex<double> >& input, wstring& output);
	static string& ToString(const valarray<complex<double> >& input, string& output);
	//
	static wstring& ToString(const vector<double>& input, wstring& output);
	static string& ToString(const vector<double>& input, string& output);
	static wstring& ToString(const vector<complex<double> >& input, wstring& output);
	static string& ToString(const vector<complex<double> >& input, string& output);

	// format:  L"ddd',' MMM dd yyyy"
	static wstring& DateToString(const Sys::Time& input, const wchar_t* format, wstring& output);
	static wstring ToString(const Sys::Time& input, const wchar_t* format);

	// format: L"hh':'mm':'ss tt"
	static wstring& TimeToString(const Sys::Time& input, const wchar_t* format, wstring& output);

	static string& WstringToString(const wchar_t* input, string& output);
	static string& WstringToString(const wstring& input, string& output);
	static wstring& StringToWstring(const char* input, wstring& output);
	static wstring& StringToWstring(const string& input, wstring& output);
	//__________________________________________________ The input string has several lines
	static vector<wstring>& ToVectorOfStrings(const wchar_t* input, vector<wstring>& output);
	static vector<wstring>& ToVectorOfStrings(const wstring& input, vector<wstring>& output);
	static vector<string>& ToVectorOfStrings(const char* input, vector<string>& output);
	static vector<string>& ToVectorOfStrings(const string& input, vector<string>& output);
	//
	static vector<wstring>& PathToVectorOfStrings(const wchar_t* input, vector<wstring>& output);
	static vector<wstring>& PathToVectorOfStrings(const wstring& input, vector<wstring>& output);
	//
	static bool WstringToUTF8(const wstring& input, string& output);
	static bool UTF8ToWstring(const string& input, wstring& output);
	//
	static bool HexRequiresCoding(char input); 
	static bool HexRequiresCoding(wchar_t input); 
	static int HexComputeLength(const char* input);
	static int HexComputeLength(const wchar_t* input);
	static bool UTF8ToHex(const char* input, string& output); //i.e.:  input: a_b  output: a%XXb
	static bool HexToUTF8(const char* input, string& output);//i.e.:  input: a%XXb  output: a_b
	static bool WstringToHex(const wchar_t* input, wstring& output); //i.e.:  input: a_b  output: a%XXb
	//
	static int FontPointToLogicUnits(double fontPoints);
	static int FontPointToLogicUnits(HDC hdc, double fontPoints);
	static double LogicUnitsToFontPoint(int logicUnits);
	static double LogicUnitsToFontPoint(HDC hdc, int logicUnits);
	//
	static int DlgUnitToPixelX(int dialogUnits);
	static int PixelToDlgUnitX(int pixels);
	static int DlgUnitToPixelY(int dialogUnits);
	static int PixelToDlgUnitY(int pixels);
	//
	static bool HiMetricToPixel(const SIZEL& inputHiMetric, SIZEL& resultPix);
	static bool PixelToHiMetric(const SIZEL& inputPix, SIZEL& resultHiMetric);
	//
	static COLORREF OleColorToColorRef(const OLE_COLOR input);
	static OLE_COLOR ColorRefToOleColor(const COLORREF input);
	//
	static COLORREF TextToColorRef(const wchar_t* text);
	static COLORREF TextToColorRef(const wstring& text);
	//
	static double MseToGrade(const double mse); //Mean squared error to Grade [0 to 100]
	//
	static void CppToHtml(const wchar_t* input_cppLine, wstring& output_html, bool indent, bool includeNeuralLabVariables);
	static void CppToHtml(wstring& in_out, bool indent, bool includeNeuralLabVariables);
	static wchar_t* ToHtml(wchar_t c);
	static void ToHtml(const wchar_t * input, wstring& output);
	//
	static wchar_t* ToXml(wchar_t c);
	static void ToXml(const wchar_t * input, wstring& output);
	static void ToXml(const wstring& input, wstring& output);
	//
	static void SqlToHtml(const wchar_t* input_sqlLine, wstring& output_html, bool indent);
	static void SqlToHtml(wstring& in_out, bool indent);
	//
	static bool ValarrayToVectorInt(const valarray<double>& input, valarray<int>& output);
	//
	static bool IsBase64(unsigned char input);
	static bool Base64BitEncode(const char* input, const int inputLen, string& output);
	static bool Base64BitDecode(const char* input, const int inputLen, string& output);


	static void QuotedSqlToHtml(const wchar_t* input_sqlLine, const wchar_t* cssStyle, wstring& output_html);
	static void QuotedCppToHtml(const wchar_t* input_sqlLine, const wchar_t* cssStyle, wstring& output_html);
private:
	Convert();
	~Convert();
};

//_____________________________________________________________________ Information
class Information
{
public:
static int getSystemWindowsDirectory(wstring& result)
{
	int size = ::GetSystemWindowsDirectory(NULL, 0);
	result.resize(size);
	::GetSystemWindowsDirectory((wchar_t*)result.data(), size);
	result.resize(size-1);
	return size;
}

static void getSystemInfo(SYSTEM_INFO& si)
{
	::GetSystemInfo(&si);
}

static int getSystemDirectory(wstring& result)
{
	int size = ::GetSystemDirectory(NULL, 0);
	result.resize(size);
	::GetSystemDirectory((wchar_t*)result.data(), size);
	result.resize(size-1);
	return size;
}

static BOOL getSystemPowerStatus(SYSTEM_POWER_STATUS& sps)
{
	return ::GetSystemPowerStatus(&sps);
}

static void getSystemTimeAsFileTime(FILETIME& ft)
{
	::GetSystemTimeAsFileTime(&ft);
}

static int getCurrentDirectory(wstring& result)
{
	int size = ::GetCurrentDirectory(0, NULL);
	result.resize(size);
	::GetCurrentDirectory(size, (wchar_t*)result.data());
	result.resize(size-1);
	return size;
}

static int getWindowsDirectory(wstring& result)
{
	int size = ::GetWindowsDirectory(NULL, 0);
	result.resize(size);
	::GetWindowsDirectory((wchar_t*)result.data(), size);
	result.resize(size-1);
	return size;
}

static const wchar_t* getCommandLine()
{
	return ::GetCommandLine();
}

//::GetComputerNameEx();
//::GetCompressedFileSize();
//::GetCurrencyFormat();
//::GetDateFormat();
//::GetDesktopWindow();
//::GetDiskFreeSpaceEx();
//::GetEnvironmentStrings();
//::GetEnvironmentVariable();
//::GetFileAttributes();
//::GetFullPathName();
//::GetGuiResources();
//::GetLocaleInfo();
//::GetLocalTime();
//::GetLogicalDrives();
//::GetModuleFileName();
//::GetNumberFormat();
//::GetPath();
//::GetSaveFileName();
//::GetTempFileName();
//::GetTempPath();
//::GetTickCount();
//::GetTimeFormat();
//::GetTitleBarInfo();
//::GetUserName();
//::GetUser
static int getEnvironmentVariable(const wchar_t* variableName, wstring& result)
{
	int size = ::GetEnvironmentVariable(variableName, NULL, 0);
	result.resize(size);
	::GetEnvironmentVariable(variableName, (wchar_t*)result.data(), size);
	result.resize(size-1);
	return size;
}

static int getEnvironmentVariable(wstring& variableName, wstring& result)
{
	return Sys::Information::getEnvironmentVariable(variableName.c_str(), result);
}

static int getAllUsersProfilePath(wstring& result)
{
	return Sys::Information::getEnvironmentVariable(L"ALLUSERSPROFILE", result);
}

// puedes usar el registro HKEY_LOCAL_MACHINE/Software/Microsoft/Windows/CurrentVersion/ProgramFilesDir
// puedes usar el registro HKEY_LOCAL_MACHINE/Software/Microsoft/Windows/CurrentVersion/Explorer/ShellFolders

static int getComputerName(wstring& result)
{
	return Sys::Information::getEnvironmentVariable(L"COMPUTERNAME", result);
}

static int getHomeDrive(wstring& result)
{
	return Sys::Information::getEnvironmentVariable(L"HOMEDRIVE", result);
}

static int getHomePath(wstring& result)
{
	return Sys::Information::getEnvironmentVariable(L"HOMEPATH", result);
}

static int getProgramFilesPath(wstring& result)
{
	return Sys::Information::getEnvironmentVariable(L"ProgramFiles", result);
}

static int getTempPath(wstring& result)
{
	return Sys::Information::getEnvironmentVariable(L"TEMP", result);
}

static int getUserDomain(wstring& result)
{
	return Sys::Information::getEnvironmentVariable(L"USERDOMAIN", result);
}

static int getUserName(wstring& result)
{
	return Sys::Information::getEnvironmentVariable(L"USERNAME", result);
}

static int getUserProfilePath(wstring& result)
{
	return Sys::Information::getEnvironmentVariable(L"USERPROFILE", result);
}

static int getWindowsPath(wstring& result)
{
	return Sys::Information::getEnvironmentVariable(L"windir", result);
}

static BOOL setCurrentDirectory(const wchar_t* newDirectory)
{
	return ::SetCurrentDirectory(newDirectory);
}

static BOOL setCurrentDirectory(const wstring& newDirectory)
{
	return ::SetCurrentDirectory(newDirectory.c_str());
}

static WORD getCacheLineSize()
{
	WORD cacheLineSize = 0;
	typedef BOOL (WINAPI *LPFN_GLPI)(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, PDWORD);
	HMODULE module = ::GetModuleHandle(L"kernel32");
	if (module==NULL) return -1;
	LPFN_GLPI Glpi = (LPFN_GLPI)::GetProcAddress(module, "GetLogicalProcessorInformation");
	if (Glpi == NULL) return -1;

	BOOL done = FALSE;
	BOOL rc;
	DWORD returnLength = 0;
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = NULL;

	while (!done) 
	{
		rc = Glpi(buffer, &returnLength);

		if (FALSE == rc) 
		{
			if (::GetLastError() == ERROR_INSUFFICIENT_BUFFER) 
			{
				if (buffer) ::free(buffer);
				buffer=(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(returnLength);
				if (NULL == buffer) return -2;
			} 
			else 
			{
				return -3;  // Call ::GetLastError() to get detailed information
			}
		} 
		else 
		{
			done = TRUE;
		}
	}

	DWORD procCoreCount = 0;
	DWORD byteOffset = 0;
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION	ptr=buffer;

	while (byteOffset < returnLength) 
	{
		switch (ptr->Relationship) 
		{
		case RelationProcessorCore:
			procCoreCount++;
			break;
		case RelationNumaNode:
			break;
		case RelationProcessorPackage:
			break;
		case RelationCache:
			cacheLineSize = ptr->Cache.LineSize;
			if (buffer) ::free(buffer);
			return cacheLineSize;
		default:
			break;
		}
		byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
		ptr++;
	}

	if (buffer) ::free(buffer);
	return 0;
}
};

//_____________________________________________________________________ Region
class Region
{
public:
	Region();
	~Region();
	void Delete();
	bool CreatePolygon(LPPOINT lpPoints, int count, int mode); 
	bool CreatePolyPolygon(const POINT *lppt, const int *polyCounts, int count, int polyFillMode);
	bool CreateElliptic(int x1, int y1, int x2, int y2);
	bool CreateRect(int x1, int y1, int x2, int y2);
	bool CreateRoundRect(int x1, int y1, int x2, int y2, int x3, int y3);
	bool CreateFromPath(HDC hdc);
private:
	HRGN hrgn;	
};

//_____________________________________________________________________ TextBufferA
class TextBufferA : public Sys::ITextWriterA
{
public:
	TextBufferA();
	~TextBufferA();
	string buffer;
	bool WriteText(const string& source);
};

//_____________________________________________________________________ TextBufferW
class TextBufferW : public Sys::ITextWriterW
{
public:
	TextBufferW();
	~TextBufferW();
	wstring buffer;
	bool WriteText(const wstring& source);
};

//_____________________________________________________________________ ByteBuffer
class ByteBuffer : public Sys::IStorer
{
public:
	ByteBuffer();
	~ByteBuffer();
	basic_string<unsigned char> buffer;
	int Write(const void* data, int  bytesToWrite);  // returns number of bytes written
	int Read(void *data, int  bytesToRead);  // returns number of bytes read
	void Reset();
	int Fwrite(void* data, size_t itemSizeInBytes, size_t ItemsToWriteCount);
	int Fread(void* data, size_t itemSizeInBytes, size_t maxItemsToRead);
private:
	int position;
};

//_____________________________________________________________________ File
class File : public Sys::IStorer, public Sys::ITextWriterA, public Sys::ITextWriterW
{
public:
	File(void);
	~File(void);
	bool CreateForWritting(const wchar_t* filename);
	bool CreateForReading(const wchar_t* filename);
	bool CreateForWritting(const wstring& filename);
	bool CreateForReading(const wstring& filename);
	void Close();
	bool IsOpen();
	//___________________ IStorer
	int Write(const void* data, int  bytesToWrite);
	int Read(void *data, int  bytesToRead);
	//
	int GetSizeInBytes();
	HANDLE GetHandle(); 
	bool WriteText(const wchar_t* source);
	//___________________ITextWriterA
	bool WriteText(const string& source);
	//___________________ITextWriterW
	bool WriteText(const wstring& source);
	//___________________ int
	bool Write(int data);
	bool Read(int& data);
	//___________________ double
	bool Write(double data);
	bool Read(double& data);
	//___________________ wstring
	bool Write(const wstring& data);
	bool Read(wstring& data);
	//___________________ bool
	bool Write(bool data);
	bool Read(bool& data);
	//___________________ Sys::Time
	bool Write(const Sys::Time& data);
	bool Read(Sys::Time& data);
protected:
	HANDLE hFile;
};

//_____________________________________________________________________ TextAssistant
class TextAssistant
{
public:
	// Deletes all ocurrecences of the the string that begins with start and ends with end
	static int SmartDelete(wstring& in_out, const wstring& start, const wstring& end);
	static int SmartDelete(string& in_out, const string& start, const string& end);

	// Deletes the text after the provided character
	static int DeleteAfter(wstring& in_out, const wchar_t character);
	static int DeleteAfter(string& in_out, const char character);
	//
	static wstring& TruncateToFit(HDC hdc, const wstring& input, wstring& output, int width, bool appendEllipses);
	static string& TruncateToFit(HDC hdc, const string& input, string& output, int width, bool appendEllipses);

	static wstring& FirstUppercase(wstring& in_out);
	static string& FirstUppercase(string& in_out);

	static wstring& ToUpper(wstring& in_out);
	static string& ToUpper(string& in_out);

	static wstring& ToLower(wstring& in_out);
	static string& ToLower(string& in_out);

	static wstring& RemoveTrailingSpaces(wstring& in_out);
	static string& RemoveTrailingSpaces(string& in_out);

	static wstring& RemoveExtraSpaces(wstring& in_out);
	static string& RemoveExtraSpaces(string& in_out);
	
	static int DeleteChar(wstring& in_out, wchar_t remove);
	static int DeleteChar(string& in_out, char remove);
	static int DeleteChar(wchar_t* in_out, wchar_t remove);

	static int ReplaceChar(wstring& in_out, wchar_t oldChar, wchar_t newChar);
	static int ReplaceChar(string& in_out, char oldChar, char newChar);
	static int ReplaceChar(wchar_t* in_out, wchar_t oldChar, wchar_t newChar);

	static int DeleteWord(wstring& in_out, const wstring& word, bool matchWholeWord);
	static int ReplaceWord(wstring& in_out, const wstring& oldWord, const wstring& newWord, bool matchWholeWord);
	static int ReplaceBiggerLessThan(const wchar_t* input, wstring& output);

	static int DeleteWord(string& in_out, const string& word, bool matchWholeWord);
	static int ReplaceWord(string& in_out, const string& oldWord, const string& newWord, bool matchWholeWord);	
	static int ExpandEscapeSequences(const wstring& input, wstring& output);

	static int GetWordCount(const wstring& input, const wstring& word, bool matchWholeWord);
	static int GetWordCount(const string& input, const string& word, bool matchWholeWord);

	//IDF_NAME    BIN    "items\\thread.txt"
	static bool LoadFromResource(HINSTANCE hInst, int resource_id, wstring& output);
	static bool LoadFromResource(HINSTANCE hInst, int resource_id, string& output);

	static bool IsUnicode(const void* input, int inputSize);
	//
	static bool IsSeparator(const wstring& input, int index);
	static bool IsSeparator(const string& input, int index);
	//
	static bool IsDigit(wchar_t input);
	static bool IsDigit(char input);
	static bool IsSeparator(wchar_t input);
	static bool IsSeparator(char input);
	static bool IsChar(wchar_t input);
	static bool IsChar(char input);
	static bool IsValidIdChar(wchar_t letter);
	static bool IsValidIdChar(char letter);
	static bool IsDouble(const wchar_t* input);
	static bool IsDouble(const char* input);
	//
	static bool ExtractFileName(const wchar_t* input, bool keepFileExt, wchar_t * buffer, int bufferSize);
	static bool ExtractFilePath(const wchar_t* input, wchar_t * buffer, int bufferSize);
	static bool ExtractFileExt(const wchar_t* input, wchar_t * buffer, int bufferSize);
private:
	TextAssistant(void);
	~TextAssistant(void);
};

//_____________________________________________________________________ SerialAssistant
class SerialAssistant
{
public:
	static bool Save(Sys::IStorer& destination, double source);
	static bool Load(Sys::IStorer& source, double& destination);
	//
	static bool Save(Sys::IStorer& destination, int source);
	static bool Load(Sys::IStorer& source, int& destination);
	//
	static bool Save(Sys::IStorer& destination, const wstring& source);
	static bool Save(Sys::IStorer& destination, const string& source);
	static bool Load(Sys::IStorer& source, wstring& destination);
	static bool Load(Sys::IStorer& source, string& destination);
	//
	static bool Save(Sys::IStorer& destination, const MATRIX& source);
	static bool Save(Sys::IStorer& destination, const valarray<double>& source);
	static bool Load(Sys::IStorer& source, MATRIX& destination);
	static bool Load(Sys::IStorer& source, valarray<double>& destination);
	//______________________________complex
	static bool Save(Sys::IStorer& destination, const MATRIXC& source);
	static bool Save(Sys::IStorer& destination, const valarray<complex<double> >& source);
	static bool Load(Sys::IStorer& source, MATRIXC& destination);
	static bool Load(Sys::IStorer& source, valarray<complex<double> >& destination);
private:
	SerialAssistant(void);
	~SerialAssistant(void);
};

//_____________________________________________________________________ FileAssistant
class FileAssistant
{
public:
	static bool Save(const wchar_t* filename, const wstring& input);
	static bool Save(const wstring& filename, const wstring& input);
	static bool Save(const wchar_t* filename, const string& input);
	static bool Save(const wstring& filename, const string& input);
	static bool Load(const wchar_t* filename, wstring& output);
	static bool Load(const wstring& filename, wstring& output);
	static bool Load(const wchar_t* filename, string& output);
	static bool Load(const wstring& filename, string& output);
	//
	static bool TextSave(const wchar_t* filename, const wstring& input, bool writeOrderByte);
	static bool TextSave(const wstring& filename, const wstring& input, bool writeOrderByte);
	static bool TextSave(const wchar_t* filename, const string& input);
	static bool TextSave(const wstring& filename, const string& input);
	static bool TextLoad(const wchar_t* filename, wstring& output);
	static bool TextLoad(const wstring& filename, wstring& output);
	static bool TextLoad(const wchar_t* filename, string& output);
	static bool TextLoad(const wstring& filename, string& output);
	//
	static bool Save(const wchar_t* filename, const MATRIX& input);
	static bool Save(const wstring& filename, const MATRIX& input);
	static bool Save(const wchar_t* filename, const valarray<double>& input);
	static bool Save(const wstring& filename, const valarray<double>& input);
	static bool Load(const wchar_t* filename, MATRIX& output);
	static bool Load(const wstring& filename, MATRIX& output);
	static bool Load(const wchar_t* filename, valarray<double>& output);
	static bool Load(const wstring& filename, valarray<double>& output);
	//
	static bool CsvSave(const wchar_t* filename, const MATRIX& input);
	static bool CsvSave(const wstring& filename, const MATRIX& input);
	static bool CsvSave(const wchar_t* filename, const valarray<double>& input, bool isRow);
	static bool CsvSave(const wstring& filename, const valarray<double>& input, bool isRow);
	static bool CsvLoad(const wchar_t* filename, MATRIX& output);
	static bool CsvLoad(const wstring& filename, MATRIX& output);
	static bool CsvLoad(const wchar_t* filename, valarray<double>& output);
	static bool CsvLoad(const wstring& filename, valarray<double>& output);
	//_________________________________________ complex
	static bool Save(const wchar_t* filename, const MATRIXC& input);
	static bool Save(const wstring& filename, const MATRIXC& input);
	static bool Save(const wchar_t* filename, const valarray<complex<double> >& input);
	static bool Save(const wstring& filename, valarray<complex<double> >& input);
	static bool Load(const wchar_t* filename, MATRIXC& output);
	static bool Load(const wstring& filename, MATRIXC& output);
	static bool Load(const wchar_t* filename, valarray<complex<double> >& output);
	static bool Load(const wstring& filename, valarray<complex<double> >& output);
	//
	static bool CsvSave(const wchar_t* filename, const MATRIXC& input);
	static bool CsvSave(const wstring& filename, const MATRIXC& input);
	static bool CsvSave(const wchar_t* filename, valarray<complex<double> >& input, bool isRow);
	static bool CsvSave(const wstring& filename, valarray<complex<double> >& input, bool isRow);
	static bool CsvLoad(const wchar_t* filename, MATRIXC& output);
	static bool CsvLoad(const wstring& filename, MATRIXC& output);
	static bool CsvLoad(const wchar_t* filename, valarray<complex<double> >& output);
	static bool CsvLoad(const wstring& filename, valarray<complex<double> >& output);
private:
	FileAssistant(void);
	~FileAssistant(void);
};

//_____________________________________________________________________ DLLibrary
class DLLibray
{
public:
	DLLibray(void);
	virtual ~DLLibray(void);
	bool Load(wchar_t* dllName);
	void Free(void);
	FARPROC GetProcAddress(LPCSTR functionName);
	HINSTANCE GetHinstance();
protected:
	HINSTANCE hLibrary;
};

//_____________________________________________________________________EncryptedFile
class EncryptedFile
{
public:
	EncryptedFile(void);
	virtual ~EncryptedFile(void);
	bool Encrypt(const wchar_t * lpOriginalFile, const wchar_t * lpDestinationFile, const char* pszKey);
	bool DeEncrypt(const wchar_t * lpOriginalFile, const wchar_t * lpDestinationFile, const char* pszKey);
protected:
	unsigned char Code(unsigned char nOneLetter);
private:
	bool m_bRestore;
	int m_nKey;
	int m_nKeySize;
	char* m_pszKey;
	bool Encryption(const wchar_t * lpOriginalFile, const wchar_t * lpDestinationFile, const char* pszKey);
	void Clear();
};

//_____________________________________________________________________Pipe
class Pipe
{
public:
	Pipe(void);

	// lpName = L"\\\\.\\pipe\\TimeService");
	// lpName = L"\\\\ServerName\\pipe\\TimeService");
	// nTimeout = 1000 millisec
	// nBufferSize = sizeof(struct to move through the pipe)
	// You may implement a Server as a Service
	bool CreateServer(const wchar_t * lpName, DWORD nBufferSize, DWORD nTimeout);
	virtual ~Pipe(void);
	bool Connect();
	BOOL Flush();
	BOOL Disconnect();
	void Close();
	BOOL Write(LPCVOID lpBuffer, DWORD nNumbOfBytesToWrite, LPDWORD lpNumbOfBytesWritten);
	BOOL Read(LPVOID lpBuffer, DWORD nNumbOfBytesToRead, LPDWORD lpNumbOfBytesRead);
	operator HANDLE();
	bool IsOpen();
	HANDLE GetHandle();
protected:
	HANDLE m_handle;
	OVERLAPPED m_o;
};
// To create a pipe client
//wchar_t buffer[256];
//HANDLE pipe = ::CreateFile(L"\\\\.\\pipe\\TimeService", GENERIC_READ, 0, NULL,
//					 OPEN_EXISTING, 0, NULL);
//if (pipe != INVALID_HANDLE_VALUE)
//{
//	Sys::Time st;
//	DWORD bytesLeidos = 0;
//	::ReadFile(pipe, &st, sizeof(st), &bytesLeidos, NULL);
//	// Do something with st
//	wstring fecha;
//	Sys::Convert::DateToString(st, NULL, fecha);
//	this->Text = fecha;
//	
//	::CloseHandle(pipe);
//}
//else
//{
//	Sys::DisplayLastError(hWnd, L"Time client");
//}

//_____________________________________________________________________SvgReader
class SvgReader
{
public:
	SvgReader(void);
	virtual ~SvgReader(void);
	bool CreateFromFile(const wstring& fileName);
	bool CreateFromResource(HINSTANCE hInst, int resource_id);
	void CreateFromText(const wchar_t* svgText);
	//
	bool GetBezierPoints(const wchar_t* svg_id, vector<Sys::Point2D>& out_points); // Do not include straigh lines in the path
	bool GetPolylinePoints(const wchar_t* svg_id, vector<Sys::Point2D>& out_points); 
	bool GetPolygonPoints(const wchar_t* svg_id, vector<Sys::Point2D>& out_points); 
	bool GetRectangle(const wchar_t* svg_id, Sys::Point2D& out_position, Sys::Point2D& out_size);
private:
	wstring svgText;
	size_t FindSvgObject(const wchar_t* type, const wchar_t* beginToken, const wchar_t* svg_id);
	bool GetPoints(size_t begin, vector<Sys::Point2D>& out_points);
	bool IsNumericValid(wchar_t c);
	double GetDouble(size_t& begin, size_t end, const wchar_t* key);
	void ProcessValue(bool isRelative, double value, int count, Sys::Point2D& point, Sys::Point2D& origin, bool& storePoint, vector<Sys::Point2D>& out_points);
};
// You can use Corel Draw to create SVG files
// In Corel Draw XV create the document in inches and export the document to millimeters to obtain
// a convenient scaling
// To assign a name to each object use Corel Draw > Tools > Object Data Manager 
//**************************************************** Bezier
// It does not work with straigh lines
//void SvgTest::Window_Open(Win::Event& e)
//{
//	svg.CreateFromFile(L"two.svg");
//	vector<Sys::Point2D> pointf;
//	svg.GetBezierPoints(L"dos", pointf);
//	count = pointf.size();
//	const double scale = 100.0;
//	point = new POINT[count]; // Member variable
//	for(int i = 0; i<count; i++)
//	{
//		point[i].x = (int)(scale * pointf[i].x + 0.5);
//		point[i].y = (int)(scale * pointf[i].y + 0.5);
//	}
//}

//void SvgTest::Window_Paint(Win::Event& e)
//{
//	Win::Gdi gdi(hWnd, true, false);
//	gdi.PolyBezier(point, count); 
//}


//********************************************** Polyline
//void SvgTest::Window_Open(Win::Event& e)
//{
//	svg.CreateFromFile(L"two.svg");
//	vector<Sys::Point2D> pointf;
//	svg.GetPolylinePoints(L"bonita", pointf);
//	count = pointf.size();
//	const double scale = 100.0;
//	point = new POINT[count]; // Member variable
//	for(int i = 0; i<count; i++)
//	{
//		point[i].x = (int)(scale * pointf[i].x + 0.5);
//		point[i].y = (int)(scale * pointf[i].y + 0.5);
//	}
//}
//
//void SvgTest::Window_Paint(Win::Event& e)
//{
//	Win::Gdi gdi(hWnd, true, false);
//	gdi.Polyline(point, count);
//}

//********************************************** Polygon
//void SvgTest::Window_Open(Win::Event& e)
//{
//	svg.CreateFromFile(L"two.svg");
//	vector<Sys::Point2D> pointf;
//	svg.GetPolygonPoints(L"pentagono", pointf);
//	count = pointf.size();
//	const double scale = 100.0;
//	point = new POINT[count]; // Member Variable
//	for(int i = 0; i<count; i++)
//	{
//		point[i].x = (int)(scale * pointf[i].x + 0.5);
//		point[i].y = (int)(scale * pointf[i].y + 0.5);
//	}
//}
//
//void SvgTest::Window_Paint(Win::Event& e)
//{
//	Win::Gdi gdi(hWnd, true, false);
//	gdi.Polygon(point, count);
//}


//***************************************************** Filling Beziers (GDI+)
//void SvgTest::Window_Open(Win::Event& e)
//{
//	svg.CreateFromFile(L"two.svg");
//	vector<Sys::Point2D> pointf;
//	svg.GetBezierPoints(L"dos", pointf);
//	count = pointf.size();
//	const double scale = 100.0;
//	point = new POINT[count]; // Member variable
//	for(int i = 0; i<count; i++)
//	{
//		point[i].x = (int)(scale * pointf[i].x + 0.5);
//		point[i].y = (int)(scale * pointf[i].y + 0.5);
//	}
//}
//
//void SvgTest::Window_Paint(Win::Event& e)
//{
//	Win::Gdi gdi(hWnd, true, true);
//	SolidBrush solidBrush(Color(255, 255, 0, 0));
//	Pen pen(Color(255, 0, 0, 255), 1);
//	Gdiplus::GraphicsPath path;
//
//   gdi.plus.graphics.SetSmoothingMode(SmoothingModeHighQuality);
//
//   Gdiplus::PointF* point = new Gdiplus::PointF[m_nCount];
//	for(int i = 0; i<m_nCount; i++)
//	{
//		point[i].X= m_ppf[i].x ;
//		point[i].Y = m_ppf[i].y;
//	}
//
//	path.AddBeziers(point, m_nCount);
//	gdi.plus.graphics.FillPath(&solidBrush, &path);
//
//	delete [] point;
//}


//***************************************************** Filling Beziers (GDI)
//void SvgTest::Window_Open(Win::Event& e)
//{
//	svg.CreateFromFile(L"two.svg");
//	vector<Sys::Point2D> pointf;
//	svg.GetBezierPoints(L"dos", pointf);
//	count = pointf.size();
//	const double scale = 100.0;
//	point = new POINT[count]; // Member variable
//	for(int i = 0; i<count; i++)
//	{
//		point[i].x = (int)(scale * pointf[i].x + 0.5);
//		point[i].y = (int)(scale * pointf[i].y + 0.5);
//	}
//}
//
//void SvgTest::Window_Paint(Win::Event& e)
//{
//	Win::Gdi gdi(hWnd, true, false);
//	Win::Gdi::Brush brush(RGB(100, 100, 244));
//	gdi.FillPolyBezier(point, count, brush);
//	gdi.PolyBezier(point, count);
//}

////_____________________________________________________________________XmlNode
//class XmlNodeList;
//class XmlNode
//{
//public:
//	XmlNode(void);
//	virtual ~XmlNode(void);
//	void Create(const wchar_t* pszNode, int nNodeLength);
//	bool GetTagName(wstring& ds);
//	bool GetValue(const wchar_t* pszTagName, wstring& ds, bool bRemoveTags);
//	int GetChildNodeCount(const wchar_t* pszTagName);
//	int GetChildNodeList(Data::XmlNodeList& xmlnl, const wchar_t* pszTagName);
//	void GetXml(wstring& ds);
//private:
//	wchar_t* m_pszNode;
//	int m_nLength;
//	void CleanValue(wchar_t* pszData, const wchar_t* pszReplaceThis, wchar_t cWithThis);
//};
//
////_____________________________________________________________________XmlNodeList
//class XmlNodeList
//{
//public:
//	XmlNodeList(void);
//	virtual ~XmlNodeList(void)
//	{
//	Clear();
//	}
//	bool Create(int size);
//	int GetNodeCount()
//	{
//		return m_nCount;
//	}
//	void Set(int index, const wchar_t* pszNode, int nNodeLength)
//	{
//		m_pNodes[index].Create(pszNode, nNodeLength);
//	}
//	Data::XmlNode* GetNode(int index)
//	{
//		if (index<0 || index>m_nCount-1) return NULL;
//		return &m_pNodes[index];
//	}
//private:
//	Data::XmlNode* m_pNodes;
//	int m_nCount;
//	void Clear();
////	friend class Data::XmlReader::CreateFromFile;
//};
//
////_____________________________________________________________________XmlReader
//class XmlReader
//{
//public:
//	XmlReader(void)
//	{
//		m_psz = NULL;
//	}
//	virtual ~XmlReader(void){};
//	bool CreateFromFile(const wchar_t* pszFileName);
//	int GetChildNodeList(Data::XmlNodeList& xmlnl, const wchar_t* pszTagName);
//	int GetChildNodeCount(const wchar_t* pszTagName);
//	wchar_t* GetXml(){return m_psz;}
//private:
//	Data::TextFile m_file;
//	wchar_t* m_psz;
//};

//_____________________________________________________________________ BoolArray
class BoolArray
{
public:
	BoolArray(void);
	BoolArray(const BoolArray& init); // Copy constructor
	BoolArray(int bitCount);
	~BoolArray(void);
	bool Create(int bitCount);
	bool GetBit(int bitIndex) const;
	void SetBit(int bitIndex, bool value);
	void FlipBit(int bitIndex);
	bool CopyBits(const BoolArray& source, int indexStart, int indexEnd);
	int GetActiveBitCount();
	virtual void Show(HWND hWnd, const wchar_t* caption);
	bool operator==(const Sys::BoolArray& vector) const;
	BoolArray& operator =(const BoolArray& init); //Operator =
	
	int GetCount() const;
	void GetString(wchar_t* buffer, int bufferSize);
	bool IsOk();
	void Delete(void);
	__int8 GetInt8(int arrayIndex) const;
	__int16 GetInt16(int arrayIndex) const;
	__int32 GetInt32(int arrayIndex) const;
	__int64 GetInt64(int arrayIndex) const;
	//
	void SetInt8(int arrayIndex, __int8 value);
	void SetInt16(int arrayIndex, __int16 value);
	void SetInt32(int arrayIndex, __int32 value);
	void SetInt64(int arrayIndex, __int64 value);
protected:
	void Copy(const BoolArray &init);
	int count;
	char* data;
};

//______________________________________________________________________ HhpFile
class HhpFile
{
public:
	HhpFile();
	~HhpFile();
	bool Create(const wchar_t* path, const wchar_t* productName, const wchar_t* title);
	bool Create(const wstring& path, const wstring& productName, const wstring& title);
	void AddItem(const wchar_t* filename);
	void AddItem(const wstring& filename);
protected:
	Sys::File file;
};

//______________________________________________________________________ HhcFile
class HhcFile
{
public:
	HhcFile();
	~HhcFile();
	bool Create(const wchar_t* filename, bool useFolderImage);
	bool Create(const wstring& filename, bool useFolderImage);
	void AddFolder(const wchar_t* name); // AddFolder > AddFolderItem >AddFolderItem... > CloseFolder
	void AddFolderItem(const wchar_t* name, const wchar_t* filename);
	void CloseFolder();
protected:
	void ListItem(const wchar_t* itemName, const wchar_t* filename);
	Sys::File file;
	void HhcFile::AddTabs();
	int indentLevel;
};

} //____________________________________________________ namespace Sys::End


namespace Mt //________________________________________ namespace Mt::Ini
{
	//____________________________________________________________OverlappedE
class OverlappedE : public OVERLAPPED
{
public:
	OverlappedE(void)
	{
		this->hEvent=::CreateEvent(NULL, TRUE, FALSE, NULL);
		this->Internal=0;
		this->InternalHigh=0;
		this->Offset=0;
		this->OffsetHigh=0;
		this->Pointer=NULL;
		if (this->hEvent==NULL)
		{
			Sys::DisplayLastError(NULL, L"Mt::OverlappedE unabled to create event");
		}
	}
	~OverlappedE(void)
	{
		if (this->hEvent) ::CloseHandle(this->hEvent);
	}
	 
	HANDLE GetEventHandle(void)
   {
	   return hEvent;
   }

	void ResetEvent(void)
	{
		::ResetEvent(this->hEvent);
	}
};

//___________________________________________________________Deque
class Deque
{
public:
	Deque(void)
	{
		::InitializeCriticalSection(&cs);
	}

	~Deque(void)
	{
		::DeleteCriticalSection(&cs);
	}

	int GetSpaceFree()
	{
		int size=0;
		::EnterCriticalSection(&cs);
		size = MT_DEQUE_MAX_SIZE-(int)queue.size();
		::LeaveCriticalSection(&cs);
		return (size<0) ? 0 : size;
	}

	int GetSpaceUsed()
	{
		int size=0;
		::EnterCriticalSection(&cs);
		size = (int)queue.size();
		::LeaveCriticalSection(&cs);
		return size;
	}

	int Insert(char c)
	{
		int value = -1;
		::EnterCriticalSection(&cs);
		if (queue.size()<MT_DEQUE_MAX_SIZE)
		{
			queue.push_back(c);
			value = c & 0xff;
		}
		::LeaveCriticalSection(&cs);
		return value;
	}

	int Insert(char *data, int count);
	int Extract(char *data, int max);
	int Peek(char *data, int max);
	int Extract(); //Extracts one letter
	void Clear()
	{
		::EnterCriticalSection(&cs);
		queue.clear();
		::LeaveCriticalSection(&cs);
	}
private:
	CRITICAL_SECTION cs;
	std::deque<char> queue;
};

//____________________________________________________________EventI
class EventI 
{
public:
	EventI() 
   { 
      m_hevt = ::CreateEvent(NULL, FALSE, FALSE, NULL); 
   }

   ~EventI() 
   { 
      if (m_hevt) ::CloseHandle(m_hevt); 
   }
   
   BOOL Set() 
   { 
	   return ::SetEvent(m_hevt); 
   }

    BOOL Reset() 
   { 
	   return ::ResetEvent(m_hevt); 
   }

    HANDLE GetHandle(void)
   {
	   return m_hevt;
   }

   //operator HANDLE(void)
   //{
	  // return m_hevt;
   //}
	
private:
    HANDLE m_hevt;
};

void DisplayLastError(HWND hWnd, wchar_t* pWhere);
//____________________________________________________________CriticalSection
class CriticalSection
{
public:
	CriticalSection(void)
	{
		InitializeCriticalSection(&cs);
	}
	virtual ~CriticalSection(void)
	{
		DeleteCriticalSection(&cs);
	}
	void Enter()
	{
		EnterCriticalSection(&cs);
	}
	void Leave()
	{
		LeaveCriticalSection(&cs);
	}
	bool Try()
	{
		return (TryEnterCriticalSection(&cs)!=0);
	}
protected:
	CRITICAL_SECTION cs;
};

//____________________________________________________________Gate
class Gate 
{
public:
	Gate() 
   { 
      m_hevt = ::CreateEvent(NULL, FALSE, TRUE, NULL); 
   }
   
	Gate(BOOL fInitiallyOpen) 
   { 
      m_hevt = ::CreateEvent(NULL, FALSE, fInitiallyOpen, NULL); 
   }

   Gate(BOOL fInitiallyOpen, PCTSTR pszName) 
   { 
      m_hevt = ::CreateEvent(NULL, FALSE, fInitiallyOpen, pszName); 
   }

   ~Gate() 
   { 
      ::CloseHandle(m_hevt); 
   }

   DWORD WaitToOpen(DWORD dwTimeout = INFINITE, BOOL fAlertable = FALSE) 
   {
      return(::WaitForSingleObjectEx(m_hevt, dwTimeout, fAlertable)); 
   }
   
   BOOL Open() 
   { 
	   return ::SetEvent(m_hevt); 
   }

private:
    HANDLE m_hevt;
};

////____________________________________________________________MultipleObjects
//class MultipleObjects
//{
//public:
//	MultipleObjects(int objectCount)
//	{
//		this->objectCount = objectCount;
//		handle = new HANDLE[objectCount];
//	}
//	~MultipleObjects(void)
//	{
//	}
//	inline DWORD WaitFor(BOOL bWaitAll, DWORD dwMilliseconds)
//	{
//		return ::WaitForMultipleObjects(objectCount, handle, bWaitAll, dwMilliseconds);
//	}
//
//	inline HANDLE& operator[](long index) // Subscript operator
//	{
//		return handle[index];
//	}
//
//	inline const HANDLE& operator[](long index) const// Subscript operator
//	{
//		return handle[index];
//	}
//private:
//	HANDLE * handle;
//	int objectCount;
//};

//____________________________________________________________LongTs
class LongTs //Long Thread Safe
{
public:
	LongTs(void)
	{
		value = 0;
	}
	~LongTs(void)
	{
	}
	LONG Add(LONG increment)
	{
		return ::InterlockedExchangeAdd(&value, increment);
	}
	LONG value;
};

//____________________________________________________________Bool
class BoolTs //Bool Thread Safe
{
public:
	BoolTs(void)
	{
		value = false;
		::InitializeCriticalSection(&cs);
	}
	~BoolTs(void)
	{
		::DeleteCriticalSection(&cs);
	}
	void Set(bool value)
	{
		::EnterCriticalSection(&cs);
		this->value = value;
		::LeaveCriticalSection(&cs);
	}
	bool Get(void)
	{
		bool b;
		::EnterCriticalSection(&cs);
		b=value;
		::LeaveCriticalSection(&cs);
		return b;
	}
	bool SetTry(bool value)
	{
		if (::TryEnterCriticalSection(&cs)==0) return false;
		this->value = value;
		::LeaveCriticalSection(&cs);
		return true;
	}
	bool GetTry(bool& value)
	{
		if (::TryEnterCriticalSection(&cs)==0) return false;
		value=this->value;
		::LeaveCriticalSection(&cs);
		return true;
	}
private:
	bool value;
	CRITICAL_SECTION cs;
};

//____________________________________________________________Double
class DoubleTs //Double Thread Safe
{
public:
	DoubleTs(void)
	{
		value = 0.0;
		::InitializeCriticalSection(&cs);
	}
	~DoubleTs(void)
	{
		::DeleteCriticalSection(&cs);
	}
	void Set(double value)
	{
		::EnterCriticalSection(&cs);
		this->value = value;
		::LeaveCriticalSection(&cs);
	}
	double Get(void)
	{
		double b;
		::EnterCriticalSection(&cs);
		b=value;
		::LeaveCriticalSection(&cs);
		return b;
	}
	bool SetTry(double value)
	{
		if (::TryEnterCriticalSection(&cs)==0) return false;
		this->value = value;
		::LeaveCriticalSection(&cs);
		return true;
	}
	bool GetTry(double& value)
	{
		if (::TryEnterCriticalSection(&cs)==0) return false;
		value=this->value;
		::LeaveCriticalSection(&cs);
		return true;
	}
private:
	double value;
	CRITICAL_SECTION cs;
};

//____________________________________________________________Int
class IntTs //Int Thread Safe
{
public:
	IntTs(void)
	{
		value = 0;
		::InitializeCriticalSection(&cs);
	}
	~IntTs(void)
	{
		::DeleteCriticalSection(&cs);
	}
	void Set(int value)
	{
		::EnterCriticalSection(&cs);
		this->value = value;
		::LeaveCriticalSection(&cs);
	}
	int Get(void)
	{
		int b;
		::EnterCriticalSection(&cs);
		b=value;
		::LeaveCriticalSection(&cs);
		return b;
	}
	bool SetTry(int value)
	{
		if (::TryEnterCriticalSection(&cs)==0) return false;
		this->value = value;
		::LeaveCriticalSection(&cs);
		return true;
	}
	bool GetTry(int& value)
	{
		if (::TryEnterCriticalSection(&cs)==0) return false;
		value=this->value;
		::LeaveCriticalSection(&cs);
		return true;
	}
private:
	int value;
	CRITICAL_SECTION cs;
};
//InterlockedExchange and InterlockedExchangePointer

//____________________________________________________________String
class StringTs //String Thread Safe
{
public:
	StringTs(void);
	~StringTs(void);
	bool Set(const wchar_t* text);
	int GetLength();
	bool CopyData(wchar_t* buffer, int bufferSize);
	int CreateCopyData(wchar_t** buffer); //It allocates new memory that must be released manually
	int ExtractCopyData(wchar_t** buffer); //It allocates new memory that must be released manually
private:
	wchar_t* pData;
	CRITICAL_SECTION cs;
};

//____________________________________________________________IOCport
class IOCport 
{
public:
	IOCport() 
   { 
      m_hIOCP = NULL; 
      Create(-1);
   }

   IOCport(int nMaxConcurrency) 
   { 
      m_hIOCP = NULL; 
      if (nMaxConcurrency != -1) (void) Create(nMaxConcurrency);
   }

   ~IOCport() 
   { 
      if (m_hIOCP != NULL) 
         CloseHandle(m_hIOCP); 
   }

   BOOL AssociateDevice(HANDLE hDevice, ULONG_PTR CompKey) 
   {
      return (CreateIoCompletionPort(hDevice, m_hIOCP, CompKey, 0) == m_hIOCP);
   }

   //BOOL AssociateSocket(SOCKET hSocket, ULONG_PTR CompKey) 
   //{
   //   return(AssociateDevice((HANDLE) hSocket, CompKey));
   //}

   BOOL PostStatus(ULONG_PTR CompKey, DWORD dwNumBytes = 0, OVERLAPPED* po = NULL) 
   {
      return PostQueuedCompletionStatus(m_hIOCP, dwNumBytes, CompKey, po);
   }

   BOOL GetStatus(ULONG_PTR* pCompKey, PDWORD pdwNumBytes,
      OVERLAPPED** ppo, DWORD dwMilliseconds = INFINITE) 
   {
      return(GetQueuedCompletionStatus(m_hIOCP, pdwNumBytes, 
         pCompKey, ppo, dwMilliseconds));
   }

private:
	HANDLE m_hIOCP;
	BOOL Create(int nMaxConcurrency = 0) 
	{
		m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, nMaxConcurrency);
		return(m_hIOCP != NULL);
	}
};

//____________________________________________________________IOCportTimer
class IOCportTimer
{
public:
	struct group_
	{
		bool running;
		IOCport* iocp;
		ULONG_PTR completionKey;
		HANDLE handle;
	};
	IOCportTimer(void);
	virtual ~IOCportTimer(void);
	bool Start(Mt::IOCport* iocp, ULONG_PTR completionKey, int iniMillisec, int repeatMillisec);
	void Stop();
	static void DisplayLastError(const wchar_t* pszWhere, bool bServiceNotification);
private:
	HANDLE m_h;
	void Destructor();
	group_ m_group;
	static void Repeat(PVOID pvoid);
};

//____________________________________________________________Service
class Service
{
public:
	Service(void);
	virtual ~Service(void);
	virtual wchar_t* GetName(); //Implement this fuction
	virtual wchar_t* GetDisplayName(); //Implement this fuction
	virtual wchar_t* GetDescription(); //Implement this function
	virtual void Run(const wchar_t* pszUserName, const wchar_t* pszPassword, wchar_t* lpCmdLine, LPSERVICE_MAIN_FUNCTION pServiceFunction);
	enum CompletionKey
	{ 
		Control, 
		Server
	};
	void WINAPI ServiceMain(DWORD dwArgc, PTSTR* pszArgv);
	static void DisplayLastError(const wchar_t* pszWhere, bool bServiceNotification);
protected:
	static DWORD WINAPI HandlerEx(DWORD control, DWORD type, PVOID pData, PVOID pContext);
	DWORD OnControlStop(DWORD type, PVOID pData);
	DWORD OnControlPause(DWORD type, PVOID pData);
	DWORD OnControlContinue(DWORD type, PVOID pData);
	DWORD OnControlShutdown(DWORD type, PVOID pData);
	DWORD OnControlInterrogate(DWORD type, PVOID pData);
	DWORD OnControlParamChange(DWORD type, PVOID pData);
	DWORD OnControlDeviceEvent(DWORD type, PVOID pData);
	DWORD OnControlHardwareProfileChange(DWORD type, PVOID pData);
	DWORD OnControlPowerEvent(DWORD type, PVOID pData);
	virtual void OnStart(DWORD dwArgc, PTSTR* pszArgv);
	virtual void OnStop();
	virtual void OnPause();
	virtual void OnContinue();
	virtual void OnRequestProcessing();  // This is where the actual work is done
	void DisplayLastError_(const wchar_t* pszWhere);
	SERVICE_STATUS m_ServiceStatus;
	SERVICE_STATUS_HANDLE m_hss;
	Mt::IOCport inputOutputCompletionPort;
	DWORD m_type;
	PVOID m_pData;
private:
	bool Install(const wchar_t* pszUserName, const wchar_t* pszPassword);
	bool Remove();
	static int m_nObjectCount;
	bool m_bDebug;
	static bool m_bFirstService;
	Mt::Gate m_gate;
};

//____________________________________________________________ IThread
class IThread
{
public:
	// Write your thread code inside this function stopping when running is false, report the thread progress using the progress variable
	// before completing ThreadFunc call running.Set(false);
	virtual DWORD ThreadFunc(Mt::BoolTs& running, Mt::DoubleTs& progress, Mt::BoolTs& resetTime)=0; 
};

//____________________________________________________________ ThreadObject
class ThreadObject
{
public:
	ThreadObject(void);
	~ThreadObject(void);
	bool StartThread(IThread& ithread); // Call this function to start the new thread
	void WaitForExit(); // Wait until this funcion completes to verify that the thread has finished
	Mt::BoolTs running;  // use this to stop the thread
	Mt::DoubleTs progress; // use this to report progress: 0.0 to 100.0
	Mt::BoolTs resetTime; // use this to reset the remaining time
	//
	wchar_t* GetTimeLeftText();
protected:
	static unsigned WINAPI PrivateThreadFunc(LPVOID param);
	HANDLE hThread;
	unsigned int threadId;
	Sys::LowResStopwatch stopwatch;
	wchar_t text[64];
	Mt::IThread* ithread;
};

#ifdef WIN_SOCKETS_SUPPORT

//_____________________________________________ Smtp
class Smtp : public Mt::IThread
{
public:
	Smtp();
	virtual ~Smtp();
	wchar_t* TestConnection(const wchar_t* smtpServerName);
	void Setup(const vector<Sys::EMail>& emailList, const wchar_t* smtpServerName, const wchar_t* username, const wchar_t* password);
	wchar_t* GetErrorDescr();
	//_______________________________________________________ Mt::IThread
	DWORD ThreadFunc(Mt::BoolTs& running, Mt::DoubleTs& progress, Mt::BoolTs& resetTime);
protected:
	wchar_t errorDescr[256];
	bool SendHELO(Sys::Socket& skt);
	bool SendAUTH(Sys::Socket& skt);
	bool SendUsername(Sys::Socket& skt);
	bool SendPassword(Sys::Socket& skt);
	bool SendMAILFrom(Sys::Socket& skt, const Sys::EMail& email);
	bool SendRCPTTo(Sys::Socket& skt, const Sys::EMail& email);
	bool SendTimeHeader(Sys::Socket& skt);
	bool SendFrom(Sys::Socket& skt, const Sys::EMail& email);
	bool SendSender(Sys::Socket& skt, const Sys::EMail& email);
	bool SendReplyTo(Sys::Socket& skt, const Sys::EMail& email);
	bool SendSubject(Sys::Socket& skt, const Sys::EMail& email);
	bool SendTo(Sys::Socket& skt, const Sys::EMail& email);
	bool SendMime(Sys::Socket& skt, const Sys::EMail& email);
	bool SendMultipartMixed(Sys::Socket& skt, const Sys::EMail& email);
	bool SendBodyFrontier(Sys::Socket& skt, const Sys::EMail& email);
	bool SendBodyContentType(Sys::Socket& skt, const Sys::EMail& email);
	bool SendBlankLine(Sys::Socket& skt);
	bool SendDATA(Sys::Socket& skt);
	bool SendBody(Sys::Socket& skt, const Sys::EMail& email);
	bool SendDATAEnd(Sys::Socket& skt);
	bool SendAttachmentFrontier(Sys::Socket& skt, const Sys::EMail& email);
	bool SendAttachmentContentType(Sys::Socket& skt, const Sys::EMail& email);
	bool SendAttachmentContentDisposition(Sys::Socket& skt, const Sys::EMail& email);
	bool SendAttachmentTransferEncoding(Sys::Socket& skt, const Sys::EMail& email);
	bool SendAttachment(Sys::Socket& skt, const Sys::EMail& email);
	bool SendAttachmentEnd(Sys::Socket& skt, const Sys::EMail& email);
	bool SendQuit(Sys::Socket& skt);
	string username;
	string password;
	string serverName;
	vector<Sys::EMail> emailList;
	int state;
};

//_______________ Example using Smtp
//void ClienteCorreo::Window_Open(Win::Event& e)
//{
//	Sys::EMail email;
//
//	email.toName = L"Sergio Ledesma";
//	email.toEmail = L"ledesmasergio@hotmail.com";
//	email.fromName = L"Sergio Ledesma";
//	email.fromEmail = L"selo@ugto.mx";
//	email.subject = L"Buena evaluacion al profesor";
//	email.body = L"00ABCDEFGHIJKLMNOPQRSTUVWXYZ0001ABCDEFGHIJKLMNOPQRSTUVWXYZ0102ABCDEFGHIJKLMNOPQRSTUVWXYZ0203ABCDEFGHIJKLMNOPQRSTUVWXYZ0304ABCDEFGHIJKLMNOPQRSTUVWXYZ0405ABCDEFGHIJKLMNOPQRSTUVWXYZ0506ABCDEFGHIJKLMNOPQRSTUVWXYZ0607ABCDEFGHIJKLMNOPQRSTUVWXYZ07";
//	email.isHtmlFormat = false;
//	email.attachmentFileName = L"C:\\hola.jpg"; //L"C:\\hola.gif";
//	vector<Sys::EMail> list;
//
//	list.push_back(email);
//	email.body = L"10ABCDEFGHIJKLMNOPQRSTUVWXYZ1011ABCDEFGHIJKLMNOPQRSTUVWXYZ1112ABCDEFGHIJKLMNOPQRSTUVWXYZ1213ABCDEFGHIJKLMNOPQRSTUVWXYZ1314ABCDEFGHIJKLMNOPQRSTUVWXYZ1415ABCDEFGHIJKLMNOPQRSTUVWXYZ1516ABCDEFGHIJKLMNOPQRSTUVWXYZ1617ABCDEFGHIJKLMNOPQRSTUVWXYZ17";
//	list.push_back(email);
//
//	smtp.Setup(list, L"mailhost.ugto.mx", L"selo@ugto.mx", L"myPassword"); // smtp is a member variable
//	threadObject.StartThread(smtp); // threadObject is a member variable
//	this->timer.Set(1, 1000);
//}
//
//void ClienteCorreo::Window_Timer(Win::Event& e)
//{
	//double progress = 0.0;
	//bool running = true;
	//switch(e.wParam)
	//{
	//case 1:
	//	if (threadObject.progress.GetTry(progress))
	//	{
	//		wchar_t text[256];
	//		_snwprintf_s(text, 256, _TRUNCATE, L"%.2f %%", progress);
	//		this->Text = text;
	//	}
	//	if (threadObject.running.GetTry(running))
	//	{
	//		if (running == false)
	//		{		
	//			this->timer.Kill(1);
	//			wchar_t * error = smtp.GetErrorDescr();
	//			if (error) this->MessageBox(error, L"Mail", MB_OK | MB_ICONERROR);
	//		}
	//	}
	//	break;
	//}
//}
//
//void ClienteCorreo::btStop_Click(Win::Event& e)
//{
//	threadObject.running.Set(false);
//}

//_____________________________________________ SmtpAsync
//class SmtpAsync : public Smtp
//{
//public:
//	SmtpAsync();
//	virtual ~SmtpAsync();
//	wchar_t* TestConnection(HWND hWnd, const wchar_t* smtpServerName);
//	bool SendEmail(HWND hWnd, const vector<Sys::EMail>& emailList, const wchar_t* smtpServerName, const wchar_t* username, const wchar_t* password);
//	//
//	int OnSocketNotify(LPARAM lParam);// Call this on Window_SocketNotify(Win::Event& e)
//	bool OnSocketHostname();// Call this on Window_SocketHostname(Win::Event& e)
//private:
//	bool OnFdConnect();
//	bool OnFdRead(int code);
//	bool OnFdWrite(bool write);
//	int state;
//	Sys::Socket sock;
//	int messageIndex;
//	HWND hWnd;
//	char buffer[MAXGETHOSTSTRUCT];
//};

#endif

// Example of asynchronous functions
//
//Sys::Socket g_gs;
//char g_szBuffer[MAXGETHOSTSTRUCT];
//
//LRESULT OnSocketHostname(HWND hWnd, WPARAM wParam, LPARAM lParam)
//{
//		pHost = (hostent*)g_szBuffer;	
//		pszIP =inet_ntoa(  *(LPIN_ADDR)*(pHost->h_addr_list) );
//		return 0;
//}
//
//LRESULT OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
//{
//		WSAAsyncGetHostByName(hWnd, WM_SOCKETHOSTNAME, "rocinante.ugto.mx",
//			g_szBuffer, MAXGETHOSTSTRUCT);
//		return 0;
//}

/* Example of reading time asynchronously
// Time Servers
time.nist.gov
time.windows.com
utcnist.colorado.edu
time.nist.gov
time-a.timefreq.bldrdoc.gov
time-b.timefreq.bldrdoc.gov
time-c.timefreq.bldrdoc.gov
time.nist.gov
time-a.nist.gov
time-b.nist.gov
time-nw.nist.gov
utcnist.reston.mci.net
nist1.data.com

void WintemplaProject3::Window_Open(Win::Event& e)
{
	wchar_t* error = socketAsync.ConnectAsync_(hWnd, WM_SOCKETNOTIFY, "utcnist.colorado.edu", IPPORT_TIMESERVER);
	if (error)
	{
		this->MessageBox(error, L"Socket", MB_OK | MB_ICONERROR);
	}
}

void WintemplaProject3::Window_SocketNotify(Win::Event& e)
{
	WORD socketEvent = WSAGETSELECTEVENT(e.lParam);
	WORD socketError = WSAGETSELECTERROR(e.lParam);

	e.returnValue = TRUE;
	if (socketError)
	{
		this->MessageBox(socketAsync.GetErrorDescr(socketError), L"Socket", MB_OK | MB_ICONERROR);
		return;
	}

	unsigned int utime;
	Sys::Time systime;
	wstring wdate, wtime;

	switch(socketEvent)
	{
	case FD_ACCEPT:		
		break;
	case FD_CONNECT: 
		// We are connected
		// Try to receive data.  The call will generate an error of WSAEWOULDBLOCK and FD_READ
		socketAsync.Receive((char*)&utime, 4, MSG_PEEK);
		break;
	case FD_READ:
		socketAsync.Receive((char*)&utime, 4, 0);
		Sys::Convert::InternetTimeToSystemTime(utime, systime);
		Sys::Convert::TimeToString(systime, NULL, wtime);
		Sys::Convert::DateToString(systime, NULL, wdate);
		this->MessageBox(wtime, wdate, MB_OK);
		break;
	case FD_WRITE:
		break;
	case FD_CLOSE:
		break;
	}
}

*/

/************************************************* Creating a Server using a socket
struct TemperatureInfo
{
	int m_nTemperature;
	TCHAR m_szInfo[255];
};

LRESULT Server::OnSocketNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WORD wEvent = WSAGETSELECTEVENT(lParam); // LOWORD
	WORD wError = WSAGETSELECTERROR(lParam); // HIWORD

	switch(wEvent)
	{
	case FD_ACCEPT:
		if (wError)
		{
			this->SetText(_T("There was an error during ACCEPT"));
			return TRUE;
		}
		m_socket.OnAcceptAsync();
		SetWindowText(hWnd, _T("Client is connected"));
		return TRUE;
	case FD_CONNECT://*****************************************************
		if (wError)
		{
			this->SetText(_T("There was an error during CONNECT"));
			return TRUE;
		}
		return TRUE;
	case FD_READ://**********************************************************
		if (wError)
		{
			this->SetText(_T("There was an error during READ"));
			return TRUE;
		}
		return TRUE;
	case FD_WRITE://*********************************************************
		this->SetText(_T("Sending temperature to client..."));
		::send(m_socket, (char*)&m_tempInfo, sizeof(TemperatureInfo), 0);
		this->SetText(_T("Temperature has been sent to client"));
		return TRUE;
	case FD_CLOSE://*********************************************************
		this->m_socket.Disconnect();
		this->SetText(_T("Client is disconnected"));
		this->m_socket.ConnectAsyncServer(hWnd, _T("10.3.2.23"), 80);
		return TRUE;
	}
	return FALSE;
}


LRESULT Server::OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	char sz[255];

	this->m_eb.Create(0, 0, 0, 0, 400, 200, hWnd, (HMENU)IDC_EDIT);
	::gethostname(sz, 255);
	lstrcat(sz, _T(" is waiting  for connection"));
	this->SetText(sz);

	this->m_tempInfo.m_nTemperature = 10;
	lstrcpy(m_tempInfo.m_szInfo, _T("Temperature inicial"));

	this->m_socket.ConnectAsyncServer(hWnd, _T("10.3.2.23"), 80);
	
	return 0;
}

LRESULT Server::OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	int nID = LOWORD(wParam);
	int nNotification = HIWORD(wParam);

	switch(nID)
	{
	case IDC_EDIT:
		if (nNotification==EN_CHANGE)
		{
			this->m_eb.GetText(this->m_tempInfo.m_szInfo, 255);
			return 0;
		}
		break;
	default:
		return DefWindowProc(hWnd, WM_COMMAND, wParam, lParam);
	}	
	return 0;
}
***************/

/****************************************** Creating a client using a socket
struct TemperatureInfo
{
	int m_nTemperature;
	TCHAR m_szInfo[255];
};

LRESULT Client::OnSocketNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WORD wEvent = WSAGETSELECTEVENT(lParam); // LOWORD
	WORD wError = WSAGETSELECTERROR(lParam); // HIWORD
	TemperatureInfo tempInfo;
	int iSize;
	TCHAR sz[255];

	switch(wEvent)
	{
	case FD_CONNECT://*****************************************************
		if (wError)
		{
			this->SetText(_T("There was an error during connection"));
			// There was an error
			this->m_socket.Disconnect();
			return TRUE;
		}
		iSize = ::recv(this->m_socket, (char*)&tempInfo, sizeof(tempInfo), MSG_PEEK);
		return TRUE;
	case FD_READ://**********************************************************
		if (wError)
		{
			this->SetText(_T("There was an error during reading from socket"));
			// There was an error
			this->m_socket.Disconnect();
			return TRUE;
		}
		iSize = ::recv(this->m_socket, (char*)&tempInfo, sizeof(tempInfo), 0);
		if (iSize >0)
		{
			_sntprintf(sz, 255, _T("Temperature is %i\r\n%s"), tempInfo.m_nTemperature,
				tempInfo.m_szInfo);
			this->m_eb.SetText(sz);
		}
		return TRUE;
	case FD_WRITE://*********************************************************
		return TRUE;
	case FD_CLOSE://*********************************************************
		this->m_socket.Disconnect();
		return TRUE;
	}
	return FALSE;
}

LRESULT Cliente::OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	this->m_eb.Create(0, WS_VISIBLE|WS_CHILD|ES_LEFT|ES_AUTOVSCROLL|WS_VSCROLL|ES_MULTILINE,
		0, 0, 400, 400, hWnd, (HMENU)IDC_EDIT);
	this->m_socket.ConnectAsyncClient(hWnd, _T("10.3.2.23"), 80);
	return 0;
}
**/

} //____________________________________________________ namespace Mt::End

namespace Math //________________________________________ namespace Math::Ini
{

//_____________________________________________________________________ IFunction
class IFunction // A function of one variable
{
public:
	virtual double EvaluateFunc(const double x)=0;
};

class IFunctionC // A function of one complex variable
{
public:
	virtual complex<double> EvaluateFunc(const double x)=0;
};

class IFunctionD : public Math::IFunction   // A function of one variable and its derivative
{
public:
	virtual double EvaluateDeri(const double x)=0;
};

class IMultiVarFunc // A function of several variables
{
public:
	virtual double EvaluateFunc(const valarray<double>& x)=0;
};

class IMultiVarFuncD : public Math::IMultiVarFunc // A function of several variables and its gradient
{
public:
	virtual void EvaluateGrad(const valarray<double>& x, valarray<double>& outGrad)=0;
};

//____________________________________________________________ Point
struct Point
{
	double x;
	double y;
};

//____________________________________________________________ DPoint
struct DPoint
{
	double x;
	double y;
	double dy;
};

//____________________________________________________________ ISimmAnneal
class ISimAnneal
{
public:
	virtual void SimAnnealInitialize()=0; //Initialize the solution
	virtual void SimAnnealPerturb(Math::ISimAnneal& original, double temperature, double initialTemperature)=0; //Perturb the solution
	virtual double SimAnnealGetError()=0; //Return the solution error
	virtual void SimAnnealCopy(const Math::ISimAnneal& source) = 0;  // Copy the solution 
};

//____________________________________________________________ SimAnnealParam
struct SimAnnealParam
{
	int numTemps;
	int numIterations;
	double initialTemp;
	double finalTemp;
	bool isCoolingScheduleLinear;
	int cycles;
	double goal;
};

//____________________________________________________________ IGenetic
class IGenetic
{
public:
	virtual void GeneticInitialize(Sys::BoolArray& bits)=0; //Initialize individual
	virtual double GeneticGetError(const Sys::BoolArray& bits)=0; //Return the individual error
	virtual void GeneticReportBestIndividual(const Sys::BoolArray& bits) = 0;  // it is called at the end of the algorithm to provide the optimization result
};

//____________________________________________________________ GeneticParam
struct GeneticParam
{
	int initPopulationSize;
	int numGenerations;
	double overPopulation;
	double mutationProbability;
	double crossoverProbability;
	double goal;
};

//_____________________________________________________________________ Oper
class Oper
{
public:
	static bool IsPrime(int x);
	static double Round(double value, int decimalCount);
	static double DotProduct(const valarray<double>& input_a, const valarray<double>& input_b);

	// returns a negative value if error
	static double ComputeMse(const MATRIX& input_a, const MATRIX& input_b);
	static wchar_t *ConfusionMatrix(const MATRIX& output, const MATRIX& target, MATRIX& confusionMatrix);
	static int GetClass(const valarray<double>& inputRow);
	static wchar_t* GetClass(const MATRIX input, valarray<int>& classes);
	static wchar_t* GetClass(const MATRIX input, valarray<double>& classes);
	static double GetMinimum(const MATRIX& input);
	static double GetMaximum(const MATRIX& input);
	static void AddValue(MATRIX& in_out, double value);
	static void MultiplyBy(MATRIX& in_out, double value);
	static void DivideBy(MATRIX& in_out, double value);
	static bool CopyToClipboard(HWND hWnd, const MATRIX& input);
	static bool CopyColToClipboard(HWND hWnd, const MATRIX& input, int col_index);
	static bool CopyRowToClipboard(HWND hWnd, const MATRIX& input, int row_index);
	static wchar_t* Product(const MATRIX& input_a, const valarray<double>& input_b, valarray<double>& output);
	static wchar_t* Product(const MATRIXC& input_a, const valarray<complex <double> >& input_b, valarray<complex <double> >& output);
	static wchar_t* Product(const MATRIX& input_a, const valarray<double>& input_b, MATRIX& output);
	static wchar_t* Product(const MATRIX& input_a, const MATRIX& input_b, MATRIX& output);
	static wchar_t* Product(const MATRIXC& input_a, const MATRIXC& input_b, MATRIXC& output);
	static wchar_t* Product(const valarray<double>& input_a, const MATRIX& input_b, int rowb_index, MATRIX& output);
	static wchar_t* Product(const valarray<complex<double> >& input_a, const MATRIXC& input_b, int rowb_index, MATRIXC& output);
	static bool Transpose(const MATRIX& input, MATRIX& output);
	static bool Transpose(const MATRIXC& input, MATRIXC& output);
	//
	static bool CreateMatrix(MATRIX& in_out, int rowCount, int colCount);
	static bool InsertRow(MATRIX& in_out, int rowIndex);
	static bool InsertCol(MATRIX& in_out, int colIndex);
	static bool InsertCell(valarray<double>& in_out, int index);
	static bool InsertCell(valarray<complex<double> >& in_out, int index);
	static bool DeleteRow(MATRIX& in_out, int rowIndex);
	static bool DeleteCol(MATRIX& in_out, int colIndex);
	static bool DeleteCell(valarray<double>& in_out, int index);
	static bool DeleteCell(valarray<complex<double> >& in_out, int index);
	static bool AppendDown(MATRIX& in_out, const MATRIX& in_B);
	static bool AppendRight(MATRIX& in_out, const MATRIX& in_B);
	static void NormalizeRows(MATRIX& in_out);
	static void NormalizeCols(MATRIX& in_out);
	//
	static bool CreateMatrix(MATRIXC& in_out, int rowCount, int colCount);
	static bool InsertRow(MATRIXC& in_out, int rowIndex);
	static bool InsertCol(MATRIXC& in_out, int colIndex);
	static bool DeleteRow(MATRIXC& in_out, int rowIndex);
	static bool DeleteCol(MATRIXC& in_out, int colIndex);
	static bool AppendDown(MATRIXC& in_out, const MATRIXC& in_B);
	static bool AppendRight(MATRIXC& in_out, const MATRIXC& in_B);
	//
	static bool GetRows(const MATRIX& input, MATRIX& output, const valarray<int> indexes);
	static bool GetCols(const MATRIX& input, MATRIX& output, const valarray<int> indexes);
	static bool DeleteRows(MATRIX& input, const valarray<int> indexes);
	static bool DeleteCols(MATRIX& input, const valarray<int> indexes);
	static bool DeleteRows(const MATRIX& input, MATRIX& output, const valarray<int> indexes);
	static bool DeleteCols(const MATRIX& input, MATRIX& output, const valarray<int> indexes);
	static bool GetRow(const MATRIX& input, valarray<double>& output, int index);
	static bool GetCol(const MATRIX& input, valarray<double>& output, int index);
	//
	static bool GetRows(const MATRIXC& input, MATRIXC& output, const valarray<int> indexes);
	static bool GetCols(const MATRIXC& input, MATRIXC& output, const valarray<int> indexes);
	static bool DeleteRows(MATRIXC& input, const valarray<int> indexes);
	static bool DeleteCols(MATRIXC& input, const valarray<int> indexes);
	static bool DeleteRows(const MATRIXC& input, MATRIXC& output, const valarray<int> indexes);
	static bool DeleteCols(const MATRIXC& input, MATRIXC& output, const valarray<int> indexes);
	static bool GetRow(const MATRIXC& input, valarray<complex<double> >& output, int index);
	static bool GetCol(const MATRIXC& input, valarray<complex<double> >& output, int index);
	//
	static double Sign(const double &a, const double &b);
	static double LineFitting(const valarray<double>& in_x, const valarray<double>& in_y, double &out_m, double &out_b);
	//
	static bool CreateRandomSet(valarray<double>& in_out, int length, int maxValue);
	static bool CreateRandom(MATRIX& in_out, int rowCount, int colCount, double minValue, double maxValue);
	static bool CreateRandom(valarray<double>& in_out, int length, double minValue, double maxValue);
	static bool WrapVector(const valarray<double>& input, int colCount, MATRIX& output);
	static bool WrapVector(const valarray<complex<double> >& input, int colCount, MATRIXC& output);
	Oper();
private:
	~Oper();
};

//____________________________________________________________ SimulatedAnnealing
class SimulatedAnnealing : public Math::SimAnnealParam, public Mt::IThread
{
public:
	SimulatedAnnealing(void);
	~SimulatedAnnealing(void);
	void SetStopWhenDone(bool stop);
	void Setup(Mt::DoubleTs& error, ISimAnneal& solution, ISimAnneal& work1, ISimAnneal& work2);
	//_____ IThread
	DWORD ThreadFunc(Mt::BoolTs& running, Mt::DoubleTs& progress, Mt::BoolTs& resetTime); 
private:
	double GetTemperature(int index);
	bool IsAcceptedByMetropolis(double temperature, double deltaError, double k);
	double EstimateK(int N, Mt::BoolTs& running);
	ISimAnneal *solution;
	ISimAnneal *work1; 
	ISimAnneal *work2;
	Mt::DoubleTs *error; 
	bool stopWhenDone;
};

//____________________________________________________________ GeneticIndividual
class GeneticIndividual
{
public:
	GeneticIndividual();
	~GeneticIndividual();
	Sys::BoolArray bits;
	double error;
	double fitness;
	GeneticIndividual(const GeneticIndividual& init);
	GeneticIndividual& operator=(const GeneticIndividual& init);
	void Copy(const GeneticIndividual &init);
	bool operator<(const GeneticIndividual& input) const;
};

//____________________________________________________________ GeneticAlgorithm
class GeneticAlgorithm : public Math::GeneticParam, public Mt::IThread
{
public:
	GeneticAlgorithm();
	~GeneticAlgorithm();
	bool Setup(Mt::DoubleTs& error, int bitsPerIndividual, Math::IGenetic& igenetic);
	void Delete();
	GeneticIndividual bestIndividual;
	//
	void ListIndividuals(HWND hWnd);
	void SetStopWhenDone(bool stopWhenDone);
	//____________________________________ IThread
	DWORD ThreadFunc(Mt::BoolTs& running, Mt::DoubleTs& progress, Mt::BoolTs& resetTime); 
protected:
	vector<Math::GeneticIndividual> poolA;
	vector<Math::GeneticIndividual> poolB;
	list<Math::GeneticIndividual> poolOverPop;
	//
	virtual void CreateNewGeneration(vector<Math::GeneticIndividual>& parents, vector<Math::GeneticIndividual>& children);
	virtual void ComputeFitness(vector<Math::GeneticIndividual>& pool);
	virtual void ComputeChoices(vector<Math::GeneticIndividual>& pool);
	virtual void Reproduce(const Math::GeneticIndividual& mother, const Math::GeneticIndividual& father, Math::GeneticIndividual& out_child, bool isFirstChild);
	virtual void SelectParents (int &count,  int &out_motherIndex, int &out_fatherIndex);
private:
	Math::IGenetic* igenetic;
	vector<int> selection;
	bool stopWhenDone;
	Mt::DoubleTs *error;
};




//_____________________________________________________________________FindMinimum
class FindMinimum
{
public:
	FindMinimum(void);
	static void Bracketing(Math::IFunction& func, Math::Point& a, Math::Point& b, Math::Point& c);
	static double BrentWithDerivative(Math::IFunctionD& func, const double a, const double b, const double c, const double tol, double &out_min_x);
private:
	virtual ~FindMinimum(void);
};

//_____________________________________________________________________ FindMinimumMV
// It finds the minimum of a multivariable function, i.e. y = f(x0, x2, ..., xn)
class FindMinimumMV : public Mt::IThread, public Math::IFunctionD
{
public:
	FindMinimumMV();
	virtual ~FindMinimumMV();
	bool Setup(Mt::DoubleTs& error, Math::IMultiVarFuncD& ifunc, const valarray<double>& startingPoint, int numIterations, double goal, int method); //method: WT_MATH_CONJGRAD, WT_MATH_VARMETRIC
	void SetStopWhenDone(bool stopWhenDone);
	valarray<double> solution;
	//____________________________________ IFunctionD
	double EvaluateFunc(const double x);
	double EvaluateDeri(const double x);
	//____________________________________ IThread
	DWORD ThreadFunc(Mt::BoolTs& running, Mt::DoubleTs& progress, Mt::BoolTs& resetTime); 
protected:
	int method;
	double ConjugateGradient(Mt::BoolTs& running, Mt::DoubleTs& progress);
	double VariableMetric(Mt::BoolTs& running, Mt::DoubleTs& progress);
	double MoveAlongDirection();
	valarray<double> xtmp, dertmp; // To reduce periodic memory allocation
	valarray<double> derivative;
	valarray<double> derg;
	valarray<double> derh;
	Math::IMultiVarFuncD* ifunc;
	bool stopWhenDone;
	Mt::DoubleTs *error;
	int numIterations;
	double goal;
	//______________________ Variable Metric
	MATRIX hessian;
	valarray<double> g;
};

//_____________________________________________________________________ SingValDecompos
class SingValDecompos
{
public:
	~SingValDecompos();
	static wchar_t* Decompose(MATRIX& in_out_a, valarray<double>& out_s, MATRIX& out_v); 
	static wchar_t* Decompose(const MATRIX& in_a, MATRIX& out_u, valarray<double>& out_s, MATRIX& out_v); 
	static bool BackSubstitution(const MATRIX& u, const valarray<double>& s, const MATRIX& v, const valarray<double>& b, valarray<double>& x); 
private:
	static double Module(double a, double b); 
	static double Sign(double a, double b);
	SingValDecompos();
};

//_____________________________________________________________________ Remez
class Remez // The Parks-McClellan Algorithm: Oppenheim & Schafer: section 7.6.3
{
public:
	struct Band
	{
		double w1; // Frequency 1 in radians:  0 to pi
		double w2; // Frequency 2 in radians:  0 to pi
		double gain; // Band gain: 0 to 1  (Oppenheim & Schafer: Hd) 
		double priory; // Band priority:  0 to 1 (Oppenheim & Schafer: W) 
	};
	static double ComputeImpulseResponse(const vector<Math::Remez::Band>& in_band, int length, valarray<double>& out_impulseResponse);
	static double ComputeHilbertImpulseResponse(int length, valarray<double>& out_impulseResponse);
	static double ComputeDifferentiatorImpulseResponse(int length, valarray<double>& out_impulseResponse);
	~Remez();
	//______________ This function is for debug only
	static double ImpulseResponse(const vector<Math::Remez::Band>& in_band, int length, int remezType, valarray<double>& out_impulseResponse, 
		valarray<double>& error, valarray<double>& freq);
private:
	static double ImpulseResponse(const vector<Math::Remez::Band>& in_band, int length, int remezType, valarray<double>& out_impulseResponse);
	
	struct BandPoint
	{
		double w; // Frequency in radians:  0 to pi
		double gain; // Gain: 0 to 1  (Oppenheim & Schafer: Hd) 
		double priority; // Priority:  0 to 1 (Oppenheim & Schafer: W) 
		double error;
		double x;
		bool isExtrema;
	};
	struct Extrema
	{
		int index;
		double error;
		bool operator<(const Extrema& extrema) const
		{
			return (fabs(error) < fabs(error));
		}
	};
	static void CreatePerformanceData(const vector<Math::Remez::Band> in_band, int type, int L, vector<BandPoint>& out_perfomanceData);
	static void AdjustPerformanceData(vector<BandPoint>& in_performanceData, int type);
	static void CreateInitialExtremaIndex(vector<BandPoint>& in_performanceData, int L, set<int>& out_extremaIndex);
	static double ComputeDelta(vector<BandPoint>& in_performanceData, set<int>& in_extremaIndex, valarray<double>& in_b);
	static void ComputeErrors(vector<BandPoint>& in_performanceData,  set<int>& in_extremaIndex, valarray<double>& in_C, valarray<double>& in_d);
	static void ComputeB(vector<BandPoint>& in_performanceData, set<int>& in_extremaIndex, valarray<double>& out_b);
	static double ComputeA(vector<BandPoint>& in_performanceData, set<int>& in_extremaIndex, double w, valarray<double>& in_C, valarray<double>& in_d);
	static void ComputeA(vector<BandPoint>& in_performanceData, set<int>& in_extremaIndex, valarray<double>& in_C, valarray<double>& in_d, valarray<double>& out_A);
	static void ComputeC(vector<BandPoint>& in_performanceData, set<int>& in_extremaIndex, double delta, valarray<double>& out_C);
	static void ComputeD(vector<BandPoint>& in_performanceData, set<int>& in_extremaIndex, valarray<double>& in_b, valarray<double>& out_d);
	static void UpdateExtremaIndex(vector<BandPoint>& in_performanceData, int L, set<int>& out_newExtremaIndex);
	static bool IsExtrema(double w, int index, int numPoints);
	static double ComputeMaxError(vector<BandPoint>& in_performanceData);
	static int ComputeType(int M, int remezType);
	static int ComputeL(int M, int type);
	static void FreqToTime(int length, valarray<double>& in_A_freq, valarray<double>& out_A_time, int type);
	Remez();
};

//_____________________________________________________________________ Dsp
class Dsp
{
public:
	static bool Convolution(const valarray<double>& input_x, const valarray<double>& input_y, valarray<double>& result);
	static bool ShortConvolution(const valarray<double>& input_x, const valarray<double>& input_y, valarray<double>& result);
	static bool IsPowerOfTwo(int input);
	static int FindNextPowerOfTwo(int input);
	static int FindPreviousPowerOfTwo(int input);
	static void FourierTransform(const valarray<complex<double> >& input, valarray<complex<double> >& output, bool inverse);
	static void FourierTransformRe(const valarray<double>& input, valarray<complex<double> >& output);
	static void InverseFourierTransformRe(const valarray<complex<double> >& input, valarray<double>& output);

	// output[0] is the lowest frequency (offset)
	// pi/m, 2pi/m, 3pi/m, ...pi,.....,2pi-3pi/m, 2pi-2pi/m, 2pi-pi/m
	// Let m = input.size()
	// Then output[m/2] is output[PI]
	// And output[m-1] is output[2PI - PI/m]
	// For real time series:  0, 3+3j, 2+2j, 5-6j, 0, 5+6j, 2-2j, 3-3j
	static wchar_t* Fft(valarray<complex<double> >& in_out, bool inverse);
	static wchar_t* Fft(const valarray<complex<double> >& input, valarray<complex<double> >& output, bool inverse);
	static wchar_t* Fft(const valarray<double>& input, valarray<complex<double> >& output, bool inverse);
	static wchar_t* Fft(MATRIXC& in_out, bool inverse);
	static wchar_t* Fft(const MATRIX& input, MATRIXC& output, bool inverse);
	static wchar_t* Fft(const MATRIXC& input, MATRIXC& output, bool inverse);
	static void SpectrumUnfold(valarray<complex<double> >& in_out);
	static void SpectrumUnfold(valarray<double>& in_out);
	//__________________________________________ Real and Imaginary parts are stored sequencially
	static wchar_t* RealFft(valarray<double>& in_out, bool inverse);
	static wchar_t* RealFft(const valarray<double>& input, valarray<double>& output, bool inverse);
	static wchar_t* RealFft(MATRIX& in_out, bool inverse);
	static wchar_t* RealFft(const MATRIX& input, MATRIX& output, bool inverse);
	//
	static wchar_t* Spectrum(const valarray<double>& input, valarray<double>& output);
	static wchar_t* Spectrum(const valarray<complex<double>>& input, valarray<double>& output);
	static wchar_t* Spectrum(const MATRIX& input, MATRIX& output);
	static wchar_t* Spectrum(const MATRIXC& input, MATRIX& output);
	//
	static wchar_t* Periodogram(const valarray<complex<double> >& input, valarray<double>& output);
	static void GetModulus(const valarray<complex<double> >& input, valarray<double>& output);
	
	// n is the discrete time d[n-delay]
	static double Impulse(int n, int delay);

	// n is the discrete time u[n-delay]
	static double Step(int n, int delay);

	// n is the discrete time Sin(kn-delay)
	static double Sin(int n, double k, int delay);

	// n is the discrete time Sin(kn-delay)
	static double Sinc(int n, double k, int delay);
	static double Sinc(double x);
	static double Sawtooth(double x, double period);
	static double Triangular(double x, double period);
	static double Rectangular(double x, double period);
	static double Pi(int n, int delay, int duration);

	static double bessi(int n, double x);
	static void KaiserWindow(double beta, int length, valarray<double>& out_window);
	static void WelchWindow(int length, valarray<double>& out_window);

	// cutFreqRad is in radians
	// cutFreqRad = 2 * pi * fc / fs;
	static void ImpulRespLowPass(double beta, int length, double cutFreqRad, valarray<double>& out_h);
	static void ImpulRespHighPass(double beta, int length, double cutFreqRad, valarray<double>& out_h);
	static void ImpulRespLowPass(double sampFreqHz, double cutFreqHz, double stopBandGaindB, double transitionWidthHz, valarray<double>& out_h);
	static void ImpulRespHighPass(double sampFreqHz, double cutFreqHz, double stopBandGaindB, double transitionWidthHz, valarray<double>& out_h);
	static void FreqRespLowPass(double beta, int length, double cutFreqRad, valarray<double>& out_H);
	static void FreqRespHighPass(double beta, int length, double cutFreqRad, valarray<double>& out_H);
	//
	static void ImpulRespHilbertTransform(double beta, int length, valarray<double>& out_h);
	static void ImpulRespHilbertTransform(double sampFreqHz, double rippleErrordB, double transitionWidthHz, valarray<double>& out_h);
	static void FreqRespHilbertTransform(double beta, int length, valarray<double>& out_H);
	static void FreqRespHilbertTransform(double sampFreqHz, double rippleErrordB, double transitionWidthHz, valarray<double>& out_H);
	//
	static bool LowPass(const valarray<double>& input, valarray<double>& output, double cutFreqRad);  
	static bool HighPass(const valarray<double>& input, valarray<double>& output, double cutFreqRad);
	//
	static double ComputeBeta(double stopBandGaindB);
	static int ComputeM(double stopBandGaindB, double transitionWidthRad);
	static double bessi0(double x);
	static double bessi1(double x);
	~Dsp();
private:
	Dsp();
};



//_____________________________________________________________________ PidController
class PidController 
{
public:
	PidController(void);
	~PidController(void);
	double Create(double kp, double ki, double kd, double target, double minControlValue, double maxControlValue);
	double GetControlValue(double currentOutput);
	double GetControlValue(double currentOutput, double amortiguamiento);
private:
	double kp;
	double ki;
	double kd;
	double error;
	double prev_error;
	double target;
	double minControlValue;
	double maxControlValue;
	double controlValue;
};

//_____________________________________________________________________ IIRFilter
class IIRFilter
{
public:
	virtual ~IIRFilter(void);
		IIRFilter(void);
		bool Create(valarray<double>& numerator, valarray<double>& denominator);
		double GenerateOutput(double input); //Call this function for each input value
private:
	int currentIndex;
	valarray<double> vectDelay;
	int order;
	valarray<double> numerator;
	valarray<double> denominator;
	int GoNext(int n);
	int GoPrevious(int n);
};

//_____________________________________________________________________ FIRFilter
class FIRFilter
{
public:
	virtual ~FIRFilter(void);
		FIRFilter(void);
		bool Create(valarray<double>& numerator);
		double GenerateOutput(double input); //Call this function for each input value
		void ClearTaps();
private:
	int currentIndex;
	valarray<double> vectDelay;
	int order;
	valarray<double> numerator;
	int GoNext(int n);
	int GoPrevious(int n);
};

//_____________________________________________________________________ NumericDerivative
class NumericDerivative
{
public:
	virtual ~NumericDerivative(void);
	static void FirstDerivative(double deltaX, const valarray<double>& in_y, valarray<double>& out_dy);
	static void SecondDerivative(double deltaX, const valarray<double>& in_y, valarray<double>& out_dy);
	static void ThirdDerivative(double deltaX, const valarray<double>& in_y, valarray<double>& out_dy);
private:
	NumericDerivative(void);
};
//valarray<double> y(11);
//for(int x = 0; x<= 11; x++)
//{
//	y[x] = 5.0*x*x*x+6.0*x*x-7*x-10;
//}
//valarray<double> dy;
//Math::NumericDerivative::FirstDerivative(1.0, y, dy);

//_____________________________________________________________________ NumericIntegration
class NumericIntegration
{
public:
	virtual ~NumericIntegration(void);
	static double Simpson(Math::IFunction* func, double a, double b, int steps, double& resultingError);
	static complex<double> Simpson(Math::IFunctionC* func, double a, double b, int steps, double& resultingError);
	static double Simpson(Math::IFunction* func, double a, double b, double& resultingError);
	static complex<double> Simpson(Math::IFunctionC* func, double a, double b, double& resultingError);
private:
	static double helper(Math::IFunction* func, double a, double b, int n);
	static complex<double> helper(Math::IFunctionC* func, double a, double b, int n);
	NumericIntegration(void);
};

//class Sin :
//	public Math::Integral
//{
//public:
//	Sin(void){};
//	~Sin(void){};
//	double Function(double x)
//	{
//		return sin(x);
//	}
//};


//_____________________________________________________________________ TimePredictor
class TimePredictor
{
public:
	TimePredictor(void);
	~TimePredictor(void);
	void AddValue(double value);
	int GetPredictionInSeconds(double targetValue);
	void Reset(void);
private:
	double data[TIME_PREDICTOR_LENGTH];
	int index;
	DWORD whenLast;
	double valueLast;
};

//_____________________________________________________________________ BinaryConverter
class BinaryConverter
{
public:
	BinaryConverter(void);
	~BinaryConverter(void);
	int Convert(int value); //Returns the number of bits
	bool GetBit(int bitIndex); //Returns the bit for that bitIndex
	static int Convert(const int value, const int bitCount, valarray<int>& output);
	static int Convert(const int value, const int bitCount, valarray<double>& output);
private:
	bool * data;
	int bitCount;
};

//_____________________________________________________________________Statistics
class Statistics
{
public:
	virtual ~Statistics(void);
	static std::tr1::mt19937 random_generator;
	static double GetMin(valarray<double>& input);
	static complex<double> GetMin(valarray<complex<double> >& input);
	static double GetMin(MATRIX& input);
	static complex<double> GetMin(MATRIXC& input);
	static double GetMax(valarray<double>& input);
	static complex<double> GetMax(valarray<complex<double> >& input);
	static double GetMax(MATRIX& input);
	static complex<double> GetMax(MATRIXC& input);
	static double MeanValue(valarray<double>& input);
	static complex<double> MeanValue(valarray<complex<double> >& input);
	static double MeanValue(MATRIX& input);
	static complex<double> MeanValue(MATRIXC& input);
	static double GetSum(valarray<double>& input);
	static complex<double> GetSum(valarray<complex<double> >& input);
	static double GetSum(MATRIX& input);
	static complex<double> GetSum(MATRIXC& input);
	static double GetDiagonalSum(MATRIX& input);
	static complex<double> GetDiagonalSum(MATRIXC& input);
	static double GetSumOfSquares(valarray<double>& input);
	static double GetSumOfSquares(valarray<complex<double> >& input);
	static double GetSumOfSquares(MATRIX& input);
	static double GetSumOfSquares(MATRIXC& input);
	static double Bias(valarray<double>& exact, valarray<double>& approx);
	static double Bias(valarray<double>& approx, double exact);
	static double Variance(valarray<double>& input);
	static complex<double> Variance(valarray<complex<double> >& input);
	static double Variance(MATRIX& input);
	static complex<double> Variance(MATRIXC& input);
	static void ColumnVariance(const MATRIX& input, valarray<double>& output);
	static void RowVariance(const MATRIX& input, valarray<double>& output);
	static double Covariance(valarray<double>& input_x, valarray<double>& input_y, bool bNormalDistr);
	static double Correlation(valarray<double>& input_x, valarray<double>& input_y);
	static double CorrelationCoeff(valarray<double>& input_x, valarray<double>& input_y);
	static double StandardDeviation(valarray<double>& input);
	static double AbsoluteRelativeError(valarray<double>& exact, valarray<double>& approx);
	static double MeanAbsoluteError(valarray<double>& exact, valarray<double>& approx);
	static double RootMeanSquaredError(valarray<double>& exact, valarray<double>& approx);
	static double MeanSquaredError(valarray<double>& exact, valarray<double>& approx);
	static double RelativeRootMeanSquareError(valarray<double>& exact, valarray<double>& approx);
	static void AbsoluteRelativeError(valarray<double>& exact, valarray<double>& approx,
											valarray<double>& outRelativeError);
	static double TheilIndex(valarray<double>& input);
	static double TheilUInequalityIndex(valarray<double>& input_x, valarray<double>& input_y);
private:
	Statistics(void);
};

//_____________________________________________________________________ Assessment
class Assessment
{
public:
	Assessment()
	{
		reset();
	}
	~Assessment()
	{
	}
	void reset()
	{
		count = 0;
		sum = 0.0;
		sumsqr = 0.0;
		minimum = 0.0;
		maximum = 0.0;
	}
	void add(double value)
	{
		if (count==0) 
		{
			minimum = value;
			maximum = value;
		}
		else 
		{
			if (value<minimum) minimum = value;
			if (value>maximum) maximum = value;
		}
		sum+=value;
		sumsqr +=(value*value);
		count++;
	}
	double getMean()
	{
		return sum/count;
	}
	double getVariance()
	{
		if (count<=1) return 0.0;
		return sumsqr/(count-1) - (sum*sum)/(count*(count-1));
	}
	double getMinimum()
	{
		return minimum;
	}
	double getMaximum()
	{
		return maximum;
	}
protected:
	int count;
	double sum;
	double sumsqr;
	double minimum;
	double maximum;
};

//_____________________________________________________________________Normalization
class Normalization
{
public:
	Normalization();
	~Normalization();
	void prestd(valarray<double>& values);
	void poststd(valarray<double>& values);
	double mean;
	double std;
};

//_____________________________________________________________________ Trender
// Eliminates trends in the data
class Trender // y = mx + b
{
public:
	Trender();
	~Trender();
	void pretrending(bool leastSquares, valarray<double>& source, valarray<double>& destination); //it calls CalculateMB internally
	void posttrending(valarray<double>& source, valarray<double>&  destination);
	double m;
	double b;
	void CalculateMB(bool bLeastSquares, valarray<double>& source);
};

//_____________________________________________________________________SyntheticDiv
class SyntheticDiv
{
public:
	virtual ~SyntheticDiv(void);
	static double Run(const valarray<double>& inputCoeff, valarray<double>& outputCoeff, double x);
	static double Run(const valarray<double>& inputCoeff, valarray<double>& outputCoeff, double x, double&out_dx);
	static double Newton(const valarray<double>& inputCoeff, valarray<double>& outputCoeff, double& int_out_x);
	//
	static complex<double> Run(const valarray<complex<double> >& inputCoeff, valarray<complex<double> >& outputCoeff, complex<double> x);
	static complex<double> Run(const valarray<complex<double> >& inputCoeff, valarray<complex<double> >& outputCoeff, complex<double> x, complex<double>&out_dx);
	static double Newton(const valarray<complex<double> >& inputCoeff, valarray<complex<double> >& outputCoeff, complex<double>& int_out_x);
private:
	SyntheticDiv(void);
};

} //____________________________________________________ namespace Math::End


namespace Nn //________________________________________ namespace Nn::Ini
{

struct ScalingInfo
{
	double minimum;
	double maximum;
	//double processingIndex;
};

//_____________________________________________________________________ Scaler
class Scaler
{
public:
	bool Create(int count);
	void Delete();
	int GetSize();
	bool Save(const wchar_t* filename);
	bool Load(const wchar_t* filename);
	bool Set(int index, double minimum, double maximum);
	bool Get(int index, double& minimum, double& maximum);
	wchar_t* ScaleToStandardRange(const MATRIX& input, MATRIX& output);
	wchar_t* ScaleToStandardRange(const valarray<double>& input, valarray<double>& output);
	wchar_t* ScaleFromStandardRange(const MATRIX& input, MATRIX& output);
	wchar_t* ScaleFromStandardRange(const valarray<double>& input, valarray<double>& output);
	bool AutoSet(MATRIX& matrix);
	//___________________________________
	Scaler();
	~Scaler();
	Scaler(const Scaler& init);
	Scaler& operator=(const Scaler& init);
	void Copy(const Scaler &init);
	void GetDescription(wchar_t* description, int length);
	bool Save(Sys::File& file);
	bool Load(Sys::File& file);
	bool Set(int index, ScalingInfo& si);
	bool GetScalingInfo(int index, ScalingInfo& si);
	bool operator==(const Scaler& init) const;
	bool operator!=(const Scaler& init) const;
	void GetText(int index, wchar_t* buffer, int buffer_length);
private:
	void Constructor();
	Nn::ScalingInfo* data;
	int size;
	//wchar_t errorDescr[256];
};

//__________________________________________________________________ Tanh
class Tanh
{
public:
	Tanh();
	~Tanh();
	double Func(double x);
	double GetExactValue(double x);
	double Derivative(double y);
	static double InverseFunc(double y);
	void ShowError(HWND hWnd);
	double GetNeuronOn();
	double GetNeuronOff();
	double GetClassificationThreshold();
private:
	static double scale;
	static double funcTable[NN_AF_TABLE_LENGTH];
	static double deriTable[NN_AF_TABLE_LENGTH];
};

//________________________________________________________ Layer
class Layer
{
public:
	Layer(void);
	~Layer(void);
	Layer(const Layer& init);
	Layer& operator=(const Layer& init);
	void Copy(const Layer &init);
	void ComputeOutput(const MATRIX& input, int rowInputIndex);
	void Agitate(double perturbRatio, Nn::Layer& source);
	void Initialize();
	double OutputDerivative(const int index);
	MATRIX weight;
	MATRIX output;
	void Delete();
protected:
	Tanh activation; 
};

//_____________________________________________________________________ LayerNet
class LayerNet : public Math::ISimAnneal, public Math::IGenetic, public Math::IMultiVarFuncD
{
public:
	LayerNet();
	~LayerNet();
	LayerNet(const LayerNet& init);
	LayerNet& operator=(const LayerNet& init);
	void Copy(const LayerNet &init);
	void GetDescription(wchar_t* description, int length);
	void Delete();
	bool Create(int inputCount, int hidden1Count, int hidden2Count, int outputCount);
	wchar_t* Load(const wchar_t* filename);
	wchar_t* Save(const wchar_t* filename);
	bool SetWeights(int layerIndex, const MATRIX& weights);
	bool GetWeights(int layerIndex, MATRIX& weights);
	void ComputeOutput(const MATRIX& input, int inputRowIndex, int layerCount);
	bool GetActivation(int layerIndex, valarray<double>& activation); 
	wchar_t* GetScaledOutput(MATRIX& scaledOutput);
	int GetInputCount() const;
	int GetOutputCount() const;
	int GetHidden1NeuronCount() const;
	int GetHidden2NeuronCount() const;
	int GetLayerCount() const;
	void Unlearn();
	bool AutoSetInputScaler(MATRIX& input);
	bool AutoSetOutputScaler(MATRIX& output);
	bool SetInputScaler(int index, double minimum, double maximum);
	bool SetOutputScaler(int index, double minimum, double maximum);
	bool GetInputScaler(int index, double& minimum, double& maximum);
	bool GetOutputScaler(int index, double& minimum, double& maximum);
	bool Run(const MATRIX& input, MATRIX& output);
	double ComputeTrueMse(const MATRIX& trainSet_in, const MATRIX& trainSet_target);
	double ComputeCurrentTrueMse();
	int GetMinNumTrainCases();
	//_______________________________________________________ training
	wchar_t* SetTrainingSet(const MATRIX& trainSetIn, const MATRIX& trainSetTarget, bool ignoreWarnings);
	wchar_t* TrainGenetic(Mt::BoolTs& running, Mt::DoubleTs& progress, Mt::DoubleTs& mse, Math::GeneticParam& param);
	wchar_t* TrainSimAnneal(Mt::BoolTs& running, Mt::DoubleTs& progress, Mt::DoubleTs& mse, Math::SimAnnealParam& param);
	wchar_t* TrainConjugateGradient(Mt::BoolTs& running, Mt::DoubleTs& progress, Mt::DoubleTs& mse, int epochs, double goal);
	wchar_t* TrainVariableMetric(Mt::BoolTs& running, Mt::DoubleTs& progress, Mt::DoubleTs& mse, int epochs, double goal);
	wchar_t* TrainLevenbergMarquardt(Mt::BoolTs& running, Mt::DoubleTs& progress, Mt::DoubleTs& mse, int epochs, double goal, bool stopWhenDone);
	wchar_t* TrainRegression(Mt::BoolTs& running, Mt::DoubleTs& progress, Mt::DoubleTs& mse);
	//____________________________________________________________ ISimAnneal
	void SimAnnealInitialize();
	void SimAnnealPerturb(Math::ISimAnneal& original, double temperature, double initialTemperature);
	double SimAnnealGetError();
	void SimAnnealCopy(const Math::ISimAnneal& source); 
	//____________________________________________________________ IGenetic
	void GeneticInitialize(Sys::BoolArray& bits);
	double GeneticGetError(const Sys::BoolArray& bits);
	void GeneticReportBestIndividual(const Sys::BoolArray& bits);
	//
	void GeneticCopyFromBits(const Sys::BoolArray& bits);
	//_____________________________________________________________________ IMultiVarFuncD
	double EvaluateFunc(const valarray<double>& x);
	void EvaluateGrad(const valarray<double>& x, valarray<double>& outGrad);
	//double EvaluateFuncAndGrad(const valarray<double>& x, valarray<double>& outGrad);
	//_____________________________________________________________________ LevenbergMarquardt
	double LevenMarComputeHessianAndGradient(valarray<double>& hid2delta, valarray<double>& grad, 
								MATRIX& hessian, valarray<double>& beta, Mt::BoolTs& running);
	double LevenMar(MATRIX & input, int inputRow, 
								int idep, double target, 
								MATRIX& alpha, valarray<double>& beta, 
							valarray<double>& hid2delta, valarray<double>& grad);
	void LevenMarMove(double step, valarray<double>& direction);
	//____________________________________________________________________
	wchar_t * ScaleInputDataSet(const MATRIX& input, MATRIX& scaledInput, bool ignoreWarnings);
	wchar_t * ScaleOutputDataSet(const MATRIX& output, MATRIX& scaledOutput, bool ignoreWarnings);
private:
	wchar_t * TrainCGVM(Mt::BoolTs& running, Mt::DoubleTs& progress, Mt::DoubleTs& mse, int epochs, double goal, int method);
	int GetWeightCount() const;
	void CopyThisToPoint(valarray<double>& point) const;
	void CopyPointToThis(const valarray<double>& point);
	void Constructor();
	//LayerNetInfo netInfo;
	Nn::Layer layerHid1;
	Nn::Layer layerHid2;
	Nn::Layer layerOut;
	Nn::Scaler scalerInput;
	Nn::Scaler scalerOutput;
	bool AreMatrixSameSize(const MATRIX& a, const MATRIX& b);
	wchar_t text[NN_LAYERNET_TEXTMAX];
	//
	static MATRIX trainSetScaledIn;
	static MATRIX trainSetScaledTarget;
	bool hasTrainSet;
	//double gradError; 
	//____________________ for SVD in Simulated Annealing and Genetic
	static MATRIX svd_a;
	static MATRIX svd_u;
	static MATRIX svd_v;
	static MATRIX svd_y;
	valarray<double> svd_s;
	bool SvdCreate();
	void SvdDelete();
	//___________________ For Conjugate Gradient and Variable Metric
	static valarray<double> deltaOutput;
	static valarray<double> deltaHidden2;
	bool DeltaCreate();
	void DeltaDelete();
};

//_____________________________________________________________________ KohoNet
class KohoNet
{
public:
	KohoNet();
	~KohoNet();
	bool Create(int numInputs, int numOutputs);
	KohoNet(const KohoNet& init);
	KohoNet& operator=(const KohoNet& init);
	void Copy(const KohoNet &init);
	void Delete();
	void GetDescription(wchar_t* description, int length);
private:
	void Constructor();
	MATRIX coefficients;
	MATRIX output;
};

//_____________________________________________________________________ ProbNet
class ProbNet
{
public:
	ProbNet();
	~ProbNet();
	ProbNet(const ProbNet& init);
	ProbNet& operator=(const ProbNet& init);
	void Copy(const ProbNet &init);
	void Delete();
	void GetDescription(wchar_t* description, int length);
private:
	void Constructor();
};

}//________________________________________ namespace Nn::End

namespace Cpl //________________________________________ namespace Cpl::Ini
{
//_____________________________________________________________________ LexicalAnalyzer
class LexicalAnalyzer
{
public:
	LexicalAnalyzer(void);
	~LexicalAnalyzer(void);
	struct Token
	{
		int type;
		int int_value;
		double double_value;
		wchar_t string_value[LEX_STRINGMAX];
		int line_number;
	};
	// To Run:
	// 1. Call Create
	// 2. Call GetNextToken repeatealy until the token.type be LEX_END_OF_FILE or LEX_ERROR
	bool Create(const wchar_t* inputString);
	bool Create(HWND hWndInput);
	void GetNextToken(Cpl::LexicalAnalyzer::Token& token);
	//
	// To Debug:
	// 1. Call Create
	// 2. Call Debug()
	void Debug(wstring& outputDebugString);
	void GetNextText(wchar_t* buffer, int buffer_len);
	//
	// To Get a vector of tokens
	static bool GetTokens(const wchar_t* inputString, vector<Cpl::LexicalAnalyzer::Token>& output);
	static bool GetTokens(HWND hWndInput, vector<Cpl::LexicalAnalyzer::Token>& output);
	//
	static wchar_t * GetTokenText(int type);
	static bool IsError(LexicalAnalyzer::Token& token);
protected:
	virtual bool ProcessComments(wchar_t& c, wchar_t& prev, Cpl::LexicalAnalyzer::Token& token, int& i);
	virtual bool ProcessKeywords(Cpl::LexicalAnalyzer::Token& token);
	bool CheckToken(LexicalAnalyzer::Token& token, const int first, const int last);
	bool CheckTokenNoCase(LexicalAnalyzer::Token& token, const int first, const int last);
	bool CheckToken(LexicalAnalyzer::Token& token, const wchar_t c, const wchar_t match, int lex_type);
	bool CheckToken(LexicalAnalyzer::Token& token, const wchar_t c, const wchar_t match1, const wchar_t match2, int lex_type);
	void Destroy();
	wchar_t* GetTokenDesc(int type);
	//
	void ExtractInt(wchar_t& c, int& index, int &i, Cpl::LexicalAnalyzer::Token& token);
	int index;
	int line_number;
	size_t length;
	wchar_t * inputString;
};

//_____________________________________________________________________ Compiler
class Compiler
{
public:
	Compiler(void);
	~Compiler(void);
	
	struct VariableInfo
	{
		int datatype; //LEX_DATATYPE_BOOL, LEX_DATATYPE_DOUBLE, ...
		int index;
	};

	//VM_CREATE: name, subtype = datatype, int_value = index
	//VM_VALUE: subtype = datatype, [int_value, double_value, name = text_value]
	//VM_REFVALUE: name, subtype = datatype, int_value = index
	//VM_OPER: subtype = operation_type, int_value = operant_count
	//VM_FUNC: subtype = func_type, int_value = argument_count
	//VM_OBJFUNC: int_value = argument_count
	//VM_GOTO: int_value = instruction_index
	//VM_GOFALSE: int_value = instruction_index
	//VM_GOTRUE: int_value = instruction_index
	struct Instruction
	{
		int type; //VM_CREATE, VM_VALUE, VM_OPER, ....
		int subtype; // datatype, operation_type, func_type
		int line_number; 
		int int_value;
		double double_value;
		wchar_t name[LEX_STRINGMAX];
	};

	struct Variable
	{
		VariableInfo vi;
		bool isReference; 
		bool bool_value; // LEX_DATATYPE_BOOL
		double double_value; // LEX_DATATYPE_DOUBLE
		int int_value; // LEX_DATATYPE_INTEGER
		MATRIX matrix_value; // LEX_DATATYPE_MATRIX
		valarray<double> vector_value; // LEX_DATATYPE_VECTOR
		valarray<complex<double> > vectorC_value; // LEX_DATATYPE_COMPLEX_VECTOR
		MATRIXC matrixC_value; // LEX_DATATYPE_COMPLEX_MATRIX
	};

	class IntelliSenseInfo
	{
	public:
		IntelliSenseInfo(){}
		~IntelliSenseInfo(){}
		wstring name;
		int func_id;
		int type; //LEX_ISI_METHOD, LEX_ISI_ARGUMENT, LEX_ISI_METHOD_ARG, LEX_ISI_LAST_ARGUMENT
		bool operator<(const IntelliSenseInfo& init)
		{
			return name<init.name;
		}
	};
	int memInfo[LEX_DATATYPE_COUNT];
	map<wstring, VariableInfo> variableInfo;
	bool Compile(const wchar_t* inputString, vector<Cpl::Compiler::Instruction>& outputMachineCode);
	bool Compile(HWND hWnd, vector<Cpl::Compiler::Instruction>& outputMachineCode);
	bool Debug(const wchar_t* inputString, wstring& outputDebugString);
	bool Debug(HWND hWnd, wstring& outputDebugString);
	void ListCode(vector<Compiler::Instruction>& inputMachineCode, wstring& outputDebugString);
	list<IntelliSenseInfo> intelliSenseInfo; // Provides object: list of functions and list of parameters
	//
	static wchar_t* GetFunctionDescr(int datatype, int func_id);
	static wchar_t* GetFunctionName(int datatype, int func_id);
	static int GetObjectFuncIndex(int datatype, const wchar_t* text);
	static int GetObjectFuncParamType(int func_id, int paramIndex);
	static wchar_t* GetObjectFuncParamName(int func_id, int paramIndex);
	static int GetFuncParamCount(int func_id);
	static int GetObjectFuncReturnType(int datatype, int func_id);
private:
	bool InternalCompile(vector<Compiler::Instruction>& outputMachineCode);
	void AddError(vector<Compiler::Instruction>& outputMachineCode, LexicalAnalyzer::Token& token, int error_type, int correct_token_type);
	LexicalAnalyzer lex;
	void Clean(vector<Compiler::Instruction>& machineCode);
	wchar_t* GetInstructionText(Compiler::Instruction& inst);
	LexicalAnalyzer::Token lookahead;
	void Next(vector<Compiler::Instruction>& machine_code);
	void Match(vector<Compiler::Instruction>& machine_code, int type);
	//void Match(vector<Compiler::Instruction>& machine_code, int type, int func_id, int datatype, int parameterIndex);
	bool IsValidId(LexicalAnalyzer::Token& token);
	Compiler::VariableInfo GetVariableInfo(LexicalAnalyzer::Token& token);
	void CreateVariable(vector<Compiler::Instruction>& machine_code, LexicalAnalyzer::Token& tokenDataType, LexicalAnalyzer::Token& tokenID);
	//
	void DataType(vector<Compiler::Instruction>& machineCode);
	void If(vector<Compiler::Instruction>& machineCode);
	void For(vector<Compiler::Instruction>& machineCode);
	void While(vector<Compiler::Instruction>& machineCode);
	void Do(vector<Compiler::Instruction>& machineCode);
	void Switch(vector<Compiler::Instruction>& machineCode);
	void VariableId(vector<Compiler::Instruction>& machineCode);
	void Statement(vector<Compiler::Instruction>& machineCode);
	void Expression(vector<Compiler::Instruction>& machineCode);
	void Factor(vector<Compiler::Instruction>& machineCode);
	void FactorId(vector<Compiler::Instruction>& machineCode);
	void Term(vector<Compiler::Instruction>& machineCode);
	void VariableSet(vector<Compiler::Instruction>& machineCode, LexicalAnalyzer::Token& tokenVariableId);
	void ObjectFunction(vector<Compiler::Instruction>& machineCode, LexicalAnalyzer::Token& tokenVariableId, VariableInfo vi);
	void VariableArray(vector<Compiler::Instruction>& machineCode, LexicalAnalyzer::Token& tokenVariableId, VariableInfo vi);
	void FunctionCall(vector<Compiler::Instruction>& machineCode);
	void OperMono(vector<Compiler::Instruction>& machineCode, LexicalAnalyzer::Token& tokenVariableId, VariableInfo vi);
	void OperBina(vector<Compiler::Instruction>& machineCode, LexicalAnalyzer::Token& tokenVariableId, VariableInfo vi);
	//
	void Block(vector<Compiler::Instruction>& machineCode);
	void Block_MultiLine(vector<Compiler::Instruction>& machineCode);
	void Block_SingleLine(vector<Compiler::Instruction>& machineCode);
	//
	void ListMethods(int func_id, int datatype, wchar_t* next_text, int parameterIndex);
	void ListParameters(int func_id, int datatype, int parameterIndex);
	//
	struct IntelliSenseFuncInfo
	{
		int func_id;
		int datatype;
		int parameterIndex;
	};
	stack<IntelliSenseFuncInfo> sisfi;
};

//_____________________________________________________________________ VirtualMachine
class VirtualMachine : public Mt::IThread
{
public:
	VirtualMachine(void);
	~VirtualMachine(void);
	struct Memory
	{
		int datatype; //LEX_DATATYPE_BOOL, LEX_DATATYPE_DOUBLE, LEX_DATATYPE_INTEGER, ...
		//bool isReference;
		bool bool_value; 
		double double_value; 
		int int_value; 
		MATRIX matrix_value; 
		valarray<double> vector_value; 
		complex<double> complex_value; 
		valarray<complex<double> > vectorC_value; 
		MATRIXC matrixC_value;
		wstring string_value;
	};

	void Setup(map<wstring, Cpl::Compiler::VariableInfo>& ids, vector<Cpl::Compiler::Instruction>& machineCode, const wchar_t* path);
	void GetMemoryInfo(HWND hWnd, int gui_type, int datatype);  // gui_type:  VM_GUITYPE_LISTVIEW, VM_GUITYPE_DROPDOWN
	Mt::IntTs line;
	Mt::DoubleTs progress;
	Mt::DoubleTs mse;
	wchar_t* GetErrorDescr();
	//
	wstring GetVariableName(int datatype, int index);
	//
	vector<bool> memBool;
	vector<double> memDouble;
	vector<int> memInteger;
	vector<MATRIX> memMatrix;
	vector<valarray<double> > memVector;
	vector<complex<double> > memComplex;
	vector<valarray<complex<double> > >memVectorC;
	vector<MATRIXC> memMatrixC;
	//vector<Nn::Scaler> memScaler;
	vector<Nn::LayerNet> memLayerNet;
	vector<Nn::KohoNet> memKohoNet;
	vector<Nn::ProbNet> memProbNet;
	void ClearMemory();
	set<wstring> variableName; //prevent a variable from being created more than once at run time
	//______ IThread
	DWORD ThreadFunc(Mt::BoolTs& running, Mt::DoubleTs& progress, Mt::BoolTs& resetTime);
private:
	wchar_t errorDescr[STERRORMAX];
	int instructionIndex;
	Mt::DoubleTs value;
	map<wstring, Compiler::VariableInfo> variableInfo;
	vector<Compiler::Instruction> machineCode;
	bool Execute(Compiler::Instruction& inst, Mt::BoolTs& running, Mt::DoubleTs& progress);
	bool VmCreate(Compiler::Instruction& inst);
	bool VmValue(Compiler::Instruction& inst);
	bool VmRefValue(Compiler::Instruction& inst);
	bool VmSetValue(Compiler::Instruction& inst);
	bool VmSetVectorCell(Compiler::Instruction& inst);
	bool VmSetMatrixCell(Compiler::Instruction& inst);
	//bool VmSetRefVectorCell(Compiler::Instruction& inst);
	//bool VmSetRefMatrixCell(Compiler::Instruction& inst);
	bool VmVectorCell(Compiler::Instruction& inst);
	bool VmMatrixCell(Compiler::Instruction& inst);
	bool VmOper(Compiler::Instruction& inst);
	bool VmOperMono(Compiler::Instruction& inst);
	bool VmOperBina(Compiler::Instruction& inst);
	bool VmFunc(Compiler::Instruction& inst);
	bool VmObjFunc(Compiler::Instruction& inst, Mt::BoolTs& running, Mt::DoubleTs& progress);
	bool VmGoto(Compiler::Instruction& inst);
	bool VmGoFalse(Compiler::Instruction& inst);
	bool VmGoTrue(Compiler::Instruction& inst);	
	//
	bool OperBinary(Compiler::Instruction& inst, VirtualMachine::Memory& operator1, VirtualMachine::Memory& operator2);
	bool OperBool(Compiler::Instruction& inst, VirtualMachine::Memory& operator1, VirtualMachine::Memory& operator2);
	bool OperRelational(Compiler::Instruction& inst, VirtualMachine::Memory& operator1, VirtualMachine::Memory& operator2);
	//
	bool FuncComplex(Compiler::Instruction& objectFunction, Cpl::VirtualMachine::Memory* param, int paramCount, Cpl::VirtualMachine::Memory& object);
	bool FuncMatrix(Compiler::Instruction& objectFunction, Cpl::VirtualMachine::Memory* param, int paramCount, Cpl::VirtualMachine::Memory& object, bool isComplex);
	bool FuncVector(Compiler::Instruction& objectFunction, Cpl::VirtualMachine::Memory* param, int paramCount, Cpl::VirtualMachine::Memory& object, bool isComplex);
	//bool FuncScaler(Compiler::Instruction& objectFunction, Cpl::VirtualMachine::Memory* param, int paramCount, Cpl::VirtualMachine::Memory& object);
	bool FuncLayerNet(Compiler::Instruction& objectFunction, Cpl::VirtualMachine::Memory* param, int paramCount, Cpl::VirtualMachine::Memory& object, Mt::BoolTs& running, Mt::DoubleTs& progress);
	bool FuncKohoNet(Compiler::Instruction& objectFunction, Cpl::VirtualMachine::Memory* param, int paramCount, Cpl::VirtualMachine::Memory& object, Mt::BoolTs& running, Mt::DoubleTs& progress);
	bool FuncProbNet(Compiler::Instruction& objectFunction, Cpl::VirtualMachine::Memory* param, int paramCount, Cpl::VirtualMachine::Memory& object, Mt::BoolTs& running, Mt::DoubleTs& progress);
	//
	stack<VirtualMachine::Memory> stack;
	//
	bool Convert(VirtualMachine::Memory& input_output, int datatypeTarget, wchar_t* caption);
	int GetResultingDatatype(int datatype1, int datatype2, int operation);
	void ReportConversionError(int datatypeFrom, int datatypeTo, wchar_t* caption);
	//
	wchar_t path[4*MAX_PATH];
};


} //____________________________________________________ namespace Cpl::End


namespace Sql //________________________________________ namespace Sql::Ini
{

//_____________________________________________________________________ ISqlNumerator
class ISqlNumerator
{
public:
	virtual void Enumerate(wchar_t** data, int colCount, int rowIndex)=0;
};

//_____________________________________________________________________ ISelect
class ISelect
{
	//When toGui is true, the GUI is updated from the storage
	//When toGui is false, the value from the Gui is updated to the storage
public:
	virtual void SqlUpdate(bool toGui) = 0;
};

//_____________________________________________________________________ ISelectString
class ISelectString : public Sql::ISelect
{
public:
	virtual wstring& SqlGetString() = 0;
};

//_____________________________________________________________________ ISelectSystime
class ISelectTime : public Sql::ISelect
{
public:
	virtual Sys::SqlTime& SqlGetTime() = 0;
	virtual Sys::Time& SqlGetSysTime() = 0;
};

//_____________________________________________________________________ ISelectInt
class ISelectInt : public Sql::ISelect
{
public:
	virtual LPARAM& SqlGetInt() = 0;
};

//_____________________________________________________________________ ISelectDouble
class ISelectDouble : public Sql::ISelect
{
public:
	virtual double& SqlGetDouble() = 0;
};

//_____________________________________________________________________ ISelectBool
class ISelectBool : public Sql::ISelect
{
public:
	virtual bool& SqlGetBool() = 0;
};

//_____________________________________________________________________ LexicalAnalyzer
class LexicalAnalyzer : public Cpl::LexicalAnalyzer
{
public:
	LexicalAnalyzer(void);
	~LexicalAnalyzer(void);
	static bool GetTokens(const wchar_t* inputString, vector<Cpl::LexicalAnalyzer::Token>& output);
protected:
	bool ProcessComments(wchar_t& c, wchar_t& prev, Cpl::LexicalAnalyzer::Token& token, int& i);
	bool ProcessKeywords(Cpl::LexicalAnalyzer::Token& token);
};

//_____________________________________________________________________ Column
class Column
{
public:
	Column();
	~Column();
	wchar_t name[SQL_NAME_MAX];
	bool isPK;
	bool allowsNull;
	wchar_t check[SQL_NAME_MAX];
	int type;  //LEX_SQLTYPE_INTEGER, LEX_SQLTYPE_DOUBLE
	wchar_t refTable[SQL_NAME_MAX];
	wchar_t refPK[SQL_NAME_MAX];
	wchar_t table_name[SQL_NAME_MAX]; // So that each control has access to the name of the table
	int size;
};


//_____________________________________________________________________ Table
class Table
{
public:
	Table();
	~Table();
	wchar_t name[SQL_NAME_MAX];
	vector<Sql::Column> column;
	bool selected;
};

//_____________________________________________________________________ Compiler
class Compiler
{
public:
	Compiler();
	~Compiler();
	bool Compile(const wchar_t* inputString, vector<Sql::Table>& output);
private:
	void AddError(vector<Sql::Table>& output, Cpl::LexicalAnalyzer::Token& token, int error_type, int correct_token_type);
	LexicalAnalyzer::Token lookahead;
	Sql::LexicalAnalyzer lex;
	void Next(vector<Sql::Table>& output);
	void Match(vector<Sql::Table>& output, int type);
	void Block_SingleLine(vector<Sql::Table>& output);
	//
	void Create(vector<Sql::Table>& output);
	void Insert(vector<Sql::Table>& output);
	void Update(vector<Sql::Table>& output);
	void Select(vector<Sql::Table>& output);
	void Delete(vector<Sql::Table>& output);
	void Drop(vector<Sql::Table>& output);
	void Grant(vector<Sql::Table>& output);
	void Revoke(vector<Sql::Table>& output);
	void Rollback(vector<Sql::Table>& output);
	void SavePoint(vector<Sql::Table>& output);
	void Use(vector<Sql::Table>& output);
	void Alter(vector<Sql::Table>& output);
	//
	void Table(vector<Sql::Table>& output);
	void View(vector<Sql::Table>& output);
	void Trigger(vector<Sql::Table>& output);
	void Index(vector<Sql::Table>& output);
	void Procedure(vector<Sql::Table>& output);
	void Database(vector<Sql::Table>& output);
	void Cursor(vector<Sql::Table>& output);
	//
	void Columns(vector<Sql::Table>& output);
	void Column(vector<Sql::Table>& output);
	void Constraint(vector<Sql::Table>& output);
	void References(vector<Sql::Table>& output);
	void Primary(vector<Sql::Table>& output);
	void Not(vector<Sql::Table>& output);
	void Null(vector<Sql::Table>& output);
	void Check(vector<Sql::Table>& output);
	void Identity(vector<Sql::Table>& output);
	void Auto_Increment(vector<Sql::Table>& output);
	void On(vector<Sql::Table>& output);
	void Unique(vector<Sql::Table>& output);
	void Default(vector<Sql::Table>& output);
	//
	bool IsColumnParam(Cpl::LexicalAnalyzer::Token& token);
	bool IsDataType(Cpl::LexicalAnalyzer::Token& token);
	bool RequiresSize(int datatype);
	bool RequiresDoubleSize(int datatype);
};

//_____________________________________________________________________ Tools
class Tools
{
public:
	~Tools();
	static bool ImportFromText(const wchar_t* inputSqlText, vector<Sql::Table>& output);
	static bool ImportFromFile(const wchar_t* fileName, vector<Sql::Table>& output);
private:
	Tools();
};

//_____________________________________________________________________ StringBuilder
class StringBuilder
{
public:
	StringBuilder(const wchar_t * table_name, const wchar_t * primary_key_name, int primary_key_value);
	~StringBuilder();
	const wchar_t* GetString();
	//
	int BindInt(const wchar_t* column_name, int value);
	double BindDouble(const wchar_t* column_name, double value);
	bool BindBool(const wchar_t* column_name, bool value);
	Sys::Time BindDateTime(const wchar_t* column_name, Sys::Time& value, const wchar_t* format);
	const wchar_t* BindString(const wchar_t* column_name, const wchar_t* value);
	const wchar_t* BindString(const wchar_t* column_name, const wstring& value);
	//
	LPARAM Bind(const wchar_t* column_name, Sql::ISelectInt& control);
	bool Bind(const wchar_t* column_name, Sql::ISelectBool& control);
	Sys::Time Bind(const wchar_t* column_name, Sql::ISelectTime& control, const wchar_t* format);
	const wchar_t* Bind(const wchar_t* column_name, Sql::ISelectString& control);
private:
	int primary_key_value;
	wstring primary_key_name;
	wstring sqlCommand;
	wstring sqlValues;
	wstring query;
	bool isFirstTime;
};

//____________________________________________________ SqlExceptInfo
struct SqlExceptInfo
{
	HENV henv;
	HDBC hdbc;
	HSTMT hstmt;
	RETCODE retcode;
};

//____________________________________________________ SqlException
class SqlException
{
public:
	SqlException(Sql::SqlExceptInfo& exceptInfo, const wchar_t* statement, const wchar_t* funcName);
	SqlException(const SqlException& init);
	virtual ~SqlException(void);
	wchar_t* GetDescription(void);
protected:
	RETCODE retcode;
	wchar_t description[WINSQL_EXCEPT_MAX];
};

//____________________________________________________ SqlConnection
class SqlConnection
{
public:
	SqlConnection();
	virtual ~SqlConnection();
	int ExecuteSelect(const wchar_t *statement);
	int ExecuteSelect(const wstring& statement);
	RETCODE ExecuteSelect(const wchar_t *statement, unsigned int maxNumberOfChar, Sql::ISqlNumerator& num);
	RETCODE ExecuteSelect(const wstring& statement, unsigned int maxNumberOfChar, Sql::ISqlNumerator& num);
	RETCODE ExecuteSelect(const wchar_t *statement, unsigned int maxNumberOfChar, vector<vector<wstring> >& output);
	RETCODE ExecuteSelect(const wstring& statement, unsigned int maxNumberOfChar, vector<vector<wstring> >& output);
	int ExecuteNonQuery(const wchar_t* statement); // returns the number of rows
	int ExecuteNonQuery(const wstring& statement); // returns the number of rows
	int ExecDirect(const wchar_t* statement); // returns the number of rows
	int ExecDirect(const wstring& statement); // returns the number of rows

	RETCODE BindParameter(SQLUSMALLINT ipar, SQLSMALLINT fParamType, SQLSMALLINT fCType, SQLSMALLINT fSqlType,
		SQLULEN cvColDef, SQLSMALLINT ibScale, SQLPOINTER rgbValue, SQLLEN cbValueMax, SQLLEN* pcvValue);

	RETCODE BindInputParameter(int parameterNumber, double& parameter);
	RETCODE BindOutputParameter(int parameterNumber, double& parameter);
	RETCODE BindInputParameter(int parameterNumber, int& parameter);
	RETCODE BindOutputParameter(int parameterNumber, int& parameter);
	RETCODE BindInputParameter(int parameterNumber, Sys::SqlTime& parameter);
	RETCODE BindOutputParameter(int parameterNumber, Sys::SqlTime& parameter);
	RETCODE BindInputParameter(int parameterNumber, const wchar_t* parameter);
	RETCODE BindOutputParameter(int parameterNumber, wchar_t* parameter, int maxNumberOfChar);
	RETCODE CreateStatement();
	RETCODE CloseCursor();
	void DestroyStatement();
	int GetColumCount(const wchar_t* statement);
	void BindClear();
	RETCODE BindColumn(int columnNumber, bool &value);
	RETCODE BindColumn(int columnNumber, int &value);
	RETCODE BindColumn(int columnNumber, double &value);
	RETCODE BindColumn(int columnNumber, Sys::SqlTime &value);
	RETCODE BindColumn(int columnNumber, wchar_t* value, int bufferLength);
	//RETCODE BindColumn(int columnNumber, wstring& value, int columnLength);
	RETCODE BindColumn(int columnNumber, Sql::ISelectString& control, int bufferLength);
	RETCODE BindColumn(int columnNumber, Sql::ISelectTime& control);
	RETCODE BindColumn(int columnNumber, Sql::ISelectInt& control);
	RETCODE BindColumn(int columnNumber, Sql::ISelectDouble& control);
	RETCODE BindColumn(int columnNumber, Sql::ISelectBool& control);
	bool Fetch(void);
	RETCODE GetString(const wchar_t* statement, wchar_t* buffer, int bufferLength);
	RETCODE GetString(const wstring& statement, wchar_t* buffer, int bufferLength);
	RETCODE GetString(const wstring& statement, wstring& buffer, int bufferLength);
	RETCODE GetColumn(const wchar_t* statement, int columnIndex, SQLSMALLINT targetType, SQLPOINTER targetValue, SQLINTEGER bufferLength);
	int GetInt(const wchar_t* statement);
	int GetInt(const wstring& statement);
	bool GetBool(const wchar_t* statement);
	bool GetBool(const wstring& statement);
	Sys::Time GetDate(const wchar_t* statement);
	Sys::Time GetDate(const wstring& statement);
	double GetDouble(const wchar_t* statement);
	double GetDouble(const wstring& statement);
	RETCODE OpenSession(const wchar_t* dsn, const wchar_t* username, const wchar_t* password); //ODBC
	RETCODE OpenSession(const wstring& dsn, const wstring& username, const wstring& password); //ODBC
	RETCODE OpenSession(HWND hwnd, const wchar_t* connectionString); // It does not required ODBC
	RETCODE OpenSession(HWND hwnd, const wstring& connectionString); // It does not required ODBC
	void CloseSession();
	//wchar_t* GetErrorInformation(RETCODE retcode);
	static bool IsOk(RETCODE retcode)
	{
		return ((retcode==SQL_SUCCESS) || (retcode==SQL_SUCCESS_WITH_INFO));
	}
	static int GetAttributeCount(const wchar_t* statement);
	static int GetAttributeNames(const wchar_t* statement, vector<wstring>& output);
private:
	HENV henv;
	HDBC hdbc;
	HSTMT hstmt;
	bool bConnected;
	SQLINTEGER bindColStr[SQL_BINDCOL_MAX];
	ISelect* iselect[SQL_BINDCOL_MAX];
};

} //____________________________________________________ namespace Sql::End

namespace Web //________________________________________ namespace Web::Ini
{

//__________________________________________________  CssType
class CssType
{
public:
	~CssType();
	//____________________________________________ Position
	enum Position//MB1: X000 0000
	{
		PositionAuto = 0x00000000, 
		PositionAbsolute = 0x10000000, 
		PositionRelative = 0x20000000
	};

	//____________________________________________ FontFamily
	enum FontFamily //MB1: 0XX0 0000
	{
		FontFamilyAuto = 0x00000000, 
		FontFamilyArial = 0x00100000, 
		FontFamilyCourier = 0x00200000, 
		FontFamilyTimesNewRoman = 0x00400000
	};

	//____________________________________________ TextAlign
	enum TextAlign //MB1: 000X 0000
	{
		TextAlignAuto = 0x00000000, 
		TextAlignCenter = 0x00010000, 
		TextAlignJustify = 0x00020000, 
		TextAlignLeft = 0x00040000, 
		TextAlignRight = 0x00080000
	};

	//____________________________________________ VerticalAlign
	enum VerticalAlign //MB1: 0000 XX00
	{
		VerticalAlignAuto = 0x00000000, 
		VerticalAlignBaseline = 0x00000100, 
		VerticalAlignBottom = 0x00000200, 
		VerticalAlignMiddle = 0x00000400, 
		VerticalAlignSub = 0x00000800, 
		VerticalAlignSuper = 0x00001000, 
		VerticalAlignTextBottom = 0x00002000, 
		VerticalAlignTextTop = 0x00004000, 
		VerticalAlignTop = 0x00008000
	};

	//____________________________________________ TextDecoration
	enum TextDecoration //MB1: 0000 00XX
	{
		TextDecorationAuto = 0x00000000, 
		TextDecorationBlink = 0x00000001, 
		TextDecorationLineThrough = 0x00000002, 
		TextDecorationNone = 0x00000004,
		TextDecorationOverline = 0x00000008, 
		TextDecorationUnderline = 0x00000010
	};

	//____________________________________________ Visibility
	enum Visibility//MB2: X000 0000
	{
		VisibilityAuto = 0x00000000, 
		VisibilityHidden = 0x10000000, 
		VisibilityVisible = 0x20000000
	};

	//____________________________________________ BorderStyle
	enum BorderStyle//MB2: 0XX0 0000
	{
		BorderStyleAuto = 0x00000000, 
		BorderStyleDotted = 0x00100000, 
		BorderStyleGroove = 0x00200000, 
		BorderStyleInset = 0x00400000,
		BorderStyleNone = 0x00800000, 
		BorderStyleOutset = 0x01000000, 
		BorderStyleRidge = 0x02000000,
		BorderStyleSolid = 0x04000000
	};

	//____________________________________________ Display
	enum Display //MB2: 000X 0000
	{
		DisplayAuto = 0x00000000, 
		DisplayBlock = 0x00010000, 
		DisplayInline = 0x00020000, 
		DisplayListItem = 0x00040000,
		DisplayNone = 0x00080000
	};

	//____________________________________________ Cursor
	enum Cursor//MB2: 0000 XXXX
	{
		CursorAuto = 0x00000000, 
		CursorCrosshair = 0x00000001, 
		CursorDefault = 0x00000002, 
		CursorEResize = 0x00000004, 
		CursorHelp = 0x00000008, 
		CursorMove = 0x00000010, 
		CursorNeResize = 0x00000020, 
		CursorNResize = 0x00000040, 
		CursorNwResize = 0x00000080, 
		CursorPointer = 0x00000100, 
		CursorSeResize = 0x00000200, 
		CursorSResize = 0x00000400, 
		CursorSwResize = 0x00000800, 
		CursorText = 0x00001000, 
		CursorWait = 0x00002000,  
		CursorWResize = 0x00004000 	
	};

	//____________________________________________ OverflowX
	enum OverflowX//MB3: XX00 0000
	{
		OverflowXNone = 0x00000000, 
		OverflowXVisible = 0x01000000, 
		OverflowXHidden = 0x02000000, 
		OverflowXScroll = 0x04000000, 
		OverflowXAuto = 0x08000000, 
		OverflowXInherit = 0x10000000, 
	};

	//____________________________________________ OverflowY
	enum OverflowY//MB3: 00XX 0000
	{
		OverflowYNone = 0x00000000, 
		OverflowYVisible = 0x00010000, 
		OverflowYHidden = 0x00020000, 
		OverflowYScroll = 0x00040000, 
		OverflowYAuto = 0x00080000, 
		OverflowYInherit = 0x00100000, 
	};
	private:
	CssType();
};

//__________________________________________________ Helper
class Helper
{
public:
	~Helper();
	static wchar_t* GetControlClass(int type_id);
	static wchar_t * GetControlCaption(int type_id);
	static wchar_t* GetControlDescr(int type_id);
	//
	static wchar_t* GetTagDesc(int type);
	static wchar_t* GetTag(int type);
	static wchar_t* GetTagName(int type);
	static wchar_t* GetNodeTypeText(int type); //For:  Label and ParentNode
	static bool RequiresClosingTag(int type);
	//
	static wchar_t* GetEventDesc(int type);
	static wchar_t* GetEventName(int type);
	static wchar_t* GetEventShortName(int type);
	static wchar_t* GetEventID(int type);
	static wchar_t* GetEventProperty(int type);
	//_________________________________________________ CSS
	//_______________________________________________ Look up functions
	static wchar_t* GetPositionDescr(Web::CssType::Position position);
	static wchar_t* GetFontFamilyDescr(Web::CssType::FontFamily font_family);
	static wchar_t* GetTextAlignDescr(Web::CssType::TextAlign text_align);
	static wchar_t* GetVerticalAlignDescr(Web::CssType::VerticalAlign vertical_align);
	static wchar_t* GetTextDecorationDescr(Web::CssType::TextDecoration text_decoration);
	static wchar_t* GetVisibilityDescr(Web::CssType::Visibility visibility);
	static wchar_t* GetBorderStyleDescr(Web::CssType::BorderStyle border_style);
	static wchar_t* GetDisplayDescr(Web::CssType::Display display);
	static wchar_t* GetCursorDescr(Web::CssType::Cursor cursor);
	//_______________________________________________ Look up Values
	static wchar_t* GetPositionValue(Web::CssType::Position position);
	static wchar_t* GetFontFamilyValue(Web::CssType::FontFamily font_family);
	static wchar_t* GetTextAlignValue(Web::CssType::TextAlign text_align);
	static wchar_t* GetVerticalAlignValue(Web::CssType::VerticalAlign vertical_align);
	static wchar_t* GetTextDecorationValue(Web::CssType::TextDecoration text_decoration);
	static wchar_t* GetVisibilityValue(Web::CssType::Visibility visibility);
	static wchar_t* GetBorderStyleValue(Web::CssType::BorderStyle border_style);
	static wchar_t* GetDisplayValue(Web::CssType::Display display);
	static wchar_t* GetCursorValue(Web::CssType::Cursor cursor);
	static wchar_t* GetOverflowXValue(Web::CssType::OverflowX overflowX);
	static wchar_t* GetOverflowYValue(Web::CssType::OverflowY overflowY);
	//_______________________________________________ Look up Enums
	static wchar_t* GetPositionEnum(Web::CssType::Position position);
	static wchar_t* GetFontFamilyEnum(Web::CssType::FontFamily font_family);
	static wchar_t* GetTextAlignEnum(Web::CssType::TextAlign text_align);
	static wchar_t* GetVerticalAlignEnum(Web::CssType::VerticalAlign vertical_align);
	static wchar_t* GetTextDecorationEnum(Web::CssType::TextDecoration text_decoration);
	static wchar_t* GetVisibilityEnum(Web::CssType::Visibility visibility);
	static wchar_t* GetBorderStyleEnum(Web::CssType::BorderStyle border_style);
	static wchar_t* GetDisplayEnum(Web::CssType::Display display);
	static wchar_t* GetCursorEnum(Web::CssType::Cursor cursor);
	static wchar_t* GetOverflowXEnum(Web::CssType::OverflowX overflowX);
	static wchar_t* GetOverflowYEnum(Web::CssType::OverflowY overflowY);
	//_______________________________________________ Reverse Look up functions
	static Web::CssType::Position GetPositionType(const wchar_t* text);
	static Web::CssType::FontFamily GetFontFamilyType(const wchar_t* text);
	static Web::CssType::TextAlign GetTextAlignType(const wchar_t* text);
	static Web::CssType::VerticalAlign GetVerticalAlignType(const wchar_t* text);
	static Web::CssType::TextDecoration GetTextDecorationType(const wchar_t* text);
	static Web::CssType::Visibility GetVisibilityType(const wchar_t* text);
	static Web::CssType::BorderStyle GetBorderStyleType(const wchar_t* text);
	static Web::CssType::Display GetDisplayType(const wchar_t* text);
	static Web::CssType::Cursor GetCursorType(const wchar_t* text);
	static Web::CssType::OverflowX GetOverflowXType(const wchar_t* text);
	static Web::CssType::OverflowY GetOverflowYType(const wchar_t* text);
private:
	Helper();
};

//__________________________________________________ HttpConnector
class HttpConnector : public Sys::ITextWriterW
{
public:
	HttpConnector(EXTENSION_CONTROL_BLOCK* pECB);
	~HttpConnector();
	bool WriteText(const wstring& source);
	wchar_t* GetWindowID();
	bool CheckEvent(const wstring& ID, int notification);
	DWORD SendResponse(EXTENSION_CONTROL_BLOCK* pECB);
	bool IsIndent();
	wstring url;
	bool HasRequestBeenHandled();
	void SetRequestEvent();
	void NavigateTo(const wchar_t* windowID);
	bool GetServerVariable(char* variableName, char* buffer, DWORD bufferLen);
	bool GetServerVariable(char* variableName, string& out_value);
	bool GetServerVariable(char* variableName, wstring& out_value);
	multimap<wstring, wstring> value; // the list of variables and their values
	char* postData;
	string responseData; // Use by: BarChart, PieChart, PolarChart and XyChart
	int GetExplorerID(); // returns: HTML_BROWSER_UNKNOWN, HTML_BROWSER_IE, ...
	int ContentType; //HTML_CONTENT_TYPE_TEXT_HTML, HTML_CONTENT_TYPE_TEXT_XML, ...
	int httpCode; //100, 101, 200, 201, 202, ...
	//
	bool IsFirstTime();
	__declspec( property ( get=IsFirstTime) ) bool FirstTime;
	//
	void AddVariable(const wchar_t* variableName, const wchar_t* variableValue);
	bool SetVariable(const wchar_t* variableName, const wchar_t* variableValue);
	bool GetVariable(const wchar_t* variableName, wstring& out_variableValue);
	//
	static void GetTimeHeader(char* buffer, int bufferSize);
	static void GetHttpDateHeader(char* buffer, int bufferSize);
	static char* GetHttpCodeDescr(int code);
	static char* GetMimeContentType(const char* fileExtension);
protected:
	void ReadQueryString();
	bool ReadPostData();
	void ReadVariables(const char* data, DWORD len);
	bool _hasRequestBeenHandled;
	wstring html;
	wchar_t windowID[64];
	EXTENSION_CONTROL_BLOCK* pECB;
	void UpdateUrl(); 
};

#ifdef WIN_SOCKETS_SUPPORT

//__________________________________________________ ConnectionHandle
class ConnectionHandle : public Mt::IThread
{
public:
	ConnectionHandle();
	~ConnectionHandle();
	Sys::Socket socket;
	//bool ExtractUri(string& text2);
	//_________________________ Mt::IThread
	DWORD ThreadFunc(Mt::BoolTs& running, Mt::DoubleTs& progress, Mt::BoolTs& resetTime); 
protected:
	static wchar_t * GetMethodDescW(int method);
	static char  * GetMethodDesc(int method);
	void Clear();
	int requestMethod;
	int httpMajorVersion;
	int httpMinorVersion;
	string url;
	string unencodedUrl;
	string uriPath;
	string uriFileName;
	string uriFileExt;
	string query_string;
	string authorization;
	string accept;
	string accept_language;
	string accept_encoding;
	string user_agent;
	string host;
	string connection;
	string username;
	string password;
	string contentType;
	unsigned int contentLength;
	static int GetMethod(string& text1);
	bool ExtractVersion(string& text3);
	bool ExtractUri(string& text2);
	static int SeparateBySpace(string& line, string& out1, string& out2, string& out3);
	bool SendErrorCode(int code, bool readRemaining, wchar_t* details);
	bool GetFileName(wchar_t* buffer, int bufferLength); 
	bool GetDllFileName(wchar_t* buffer, int bufferLength); 
	bool SendFile();
	bool ExecuteDll();
	bool GetServerName(char* buffer, int bufferLength);
	int GetPort();
	char *postData;
	bool SendHttpResponse(int code, int length, const char* fileExt, bool closeConnection, bool gzip);
	//
	static BOOL WINAPI ServerSupportFunction_(HCONN hConn, 
								   DWORD dwHSERequest, LPVOID lpvBuffer, LPDWORD lpdwSize, LPDWORD lpdwDataType);
	static BOOL WINAPI WriteClient_(HCONN hConn, LPVOID Buffer, LPDWORD lpdwBytes, DWORD dwReserved);
	static BOOL WINAPI GetServerVariable_ ( HCONN hConn, LPSTR lpszVariableName, LPVOID lpvBuffer, LPDWORD lpdwSize);
};

//__________________________________________________ Server

class Server
{
public:
	Server();
	~Server();
	wchar_t* Start(unsigned int port, const int numClients); // Call this first to start the server
	wchar_t* Run(unsigned int port, const int numClients); // Call this second to run the server
protected:
	Sys::Socket socketListen;
};
#endif

//________________________________________________________ Css
class Css
{
public:
	Css(void);
	virtual ~Css(void);
	//____________________________________________ Position MB1: X000 0000
	void SetPosition(Web::CssType::Position position);
	Web::CssType::Position GetPosition();
	__declspec( property( get=GetPosition, put=SetPosition) ) Web::CssType::Position position;
	//____________________________________________ FontFamily MB1: 0XX0 0000
	void SetFontFamily(Web::CssType::FontFamily font);
	Web::CssType::FontFamily GetFontFamily();
	__declspec( property( get=GetFontFamily, put=SetFontFamily) ) Web::CssType::FontFamily font_family;
	//____________________________________________ TextAlign MB1: 000X 0000
	void SetTextAlign(Web::CssType::TextAlign text_align);
	Web::CssType::TextAlign GetTextAlign();
	__declspec( property( get=GetTextAlign, put=SetTextAlign) ) Web::CssType::TextAlign text_align;
	//____________________________________________ VerticalAlign MB1: 0000 XX00
	void SetVerticalAlign(Web::CssType::VerticalAlign vertical_align);
	Web::CssType::VerticalAlign GetVerticalAlign();
	__declspec( property( get=GetVerticalAlign, put=SetVerticalAlign) ) Web::CssType::VerticalAlign vertical_align;
	//____________________________________________ TextDecoration MB1: 0000 00XX
	void SetTextDecoration(Web::CssType::TextDecoration text_decoration);
	Web::CssType::TextDecoration GetTextDecoration();
	__declspec( property( get=GetTextDecoration, put=SetTextDecoration) ) Web::CssType::TextDecoration text_decoration;
	//____ First memory block
	//____________________________________________ Visibility MB2: X000 0000
	void SetVisibility(Web::CssType::Visibility visibility);
	Web::CssType::Visibility GetVisibility();
	__declspec( property( get=GetVisibility, put=SetVisibility) ) Web::CssType::Visibility visibility;
	//____________________________________________ BorderStyle MB2: 0XX0 0000
	void SetBorderStyle(Web::CssType::BorderStyle border_style);
	Web::CssType::BorderStyle GetBorderStyle();
	__declspec( property( get=GetBorderStyle, put=SetBorderStyle) ) Web::CssType::BorderStyle border_style;
	//____________________________________________ Display MB2: 000X 0000
	void SetDisplay(Web::CssType::Display display);
	Web::CssType::Display GetDisplay();
	__declspec( property( get=GetDisplay, put=Display) ) Web::CssType::Display display;
	//____________________________________________ Cursor MB2: 0000 XXXX
	void SetCursor(Web::CssType::Cursor cursor);
	Web::CssType::Cursor GetCursor();
	__declspec( property( get=GetCursor, put=SetCursor) ) Web::CssType::Cursor cursor;
	//____________________________________________ OverflowX MB3: XX00 0000
	void SetOverflowX(Web::CssType::OverflowX overflowX);
	Web::CssType::OverflowX GetOverflowX();
	__declspec( property( get=GetOverflowX, put=SetOverflowX) ) Web::CssType::OverflowX overflow_x;
	//____________________________________________ OverflowY MB3: 00XX 0000
	void SetOverflowY(Web::CssType::OverflowY overflowY);
	Web::CssType::OverflowY GetOverflowY();
	__declspec( property( get=GetOverflowY, put=SetOverflowY) ) Web::CssType::OverflowY overflow_y;
	//
	COLORREF background;
	COLORREF border_color;
	COLORREF color; 
	wstring additionalStyles;
	int font_size;
	int width;  // Positive is in pixels, Negative is in percent, or HTML_SIZE_AUTO
	int height;  // Positive is in pixels, Negative is in percent, or HTML_SIZE_AUTO
	int border_width; // Positive is in pixels, Negative is in percent, or HTML_SIZE_AUTO
	int padding_left;// Positive is in pixels, Negative is in percent, or HTML_SIZE_AUTO
	int padding_right;// Positive is in pixels, Negative is in percent, or HTML_SIZE_AUTO
	int padding_top;// Positive is in pixels, Negative is in percent, or HTML_SIZE_AUTO
	int padding_bottom;// Positive is in pixels, Negative is in percent, or HTML_SIZE_AUTO
	int margin;// Positive is in pixels, Negative is in percent, or HTML_SIZE_AUTO
	void GetHtml(Sys::ITextWriterW& out_html);
private:
	bool HasStyle();
	bool RenderColor(bool semicolon, const wchar_t* name, COLORREF color, Sys::ITextWriterW& out_html);
	bool RenderInteger(bool semicolon, const wchar_t* name, int value, Sys::ITextWriterW& out_html);
	unsigned int memoryBlock1;
	unsigned int memoryBlock2;
	unsigned int memoryBlock3;
};

//________________________________________________________ Object
class Object
{
public:
	Object(void);
	virtual ~Object(void);
	wstring BeginHtml;
	wstring EndHtml;
	wstring ID;
	virtual void GetHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector) = 0;
	virtual void GetXml(Web::HttpConnector& httpConnector) = 0;
	virtual void LoadState(Web::HttpConnector& httpConnector) = 0;	
	virtual void OnNavigateAway(Web::HttpConnector& httpConnector) = 0;	
	virtual bool IsEvent(Web::HttpConnector& httpConnector, int notification);
	static void Indent(int indentCount, Sys::ITextWriterW& out_html);
protected:
	virtual wchar_t* GetTag() = 0;
	void EndIndent(int& indentCount, bool newLine, Sys::ITextWriterW& out_html);
	//
	wchar_t* RenderTagAndId(bool increaseIndent, int& indentCount, Sys::ITextWriterW& out_html);
	void RenderHiddenValue(bool increaseIndent, int& indentCount, const wchar_t* value, Sys::ITextWriterW& out_html);
	void RenderPair(const wchar_t* name, wstring& value, Sys::ITextWriterW& out_html);
	void RenderPair(const wchar_t* name, const wchar_t* value, Sys::ITextWriterW& out_html);
	void RenderPair(const wchar_t* name, int value, Sys::ITextWriterW& out_html);
	void RenderFunction(int eventID, Sys::ITextWriterW& out_html, const wchar_t* url);
};

//________________________________________________________ VisibleObject
class VisibleObject : public Web::Object
{
public:
	VisibleObject(void);
	virtual ~VisibleObject(void);
	wstring cssClass;
	Web::Css css;
	//_______________________________________________________________ Visible
	void SetVisible(bool visible); 
	bool GetVisible();
	__declspec( property( get=GetVisible, put=SetVisible) ) bool Visible;
	//_______________________________________________________________ Enabled
	void SetEnabled(bool enabled); 
	bool GetEnabled();
	__declspec( property( get=GetEnabled, put=SetEnabled) ) bool Enabled;
	//_______________________________________________________________ Click
	void SetOnClick(bool fireEvent); 
	bool GetOnClick();
	__declspec( property( get=GetOnClick, put=SetOnClick) ) bool OnClick;
	//
	void SetOnJsClick(bool fireEvent); 
	bool GetOnJsClick();
	__declspec( property( get=GetOnJsClick, put=SetOnJsClick) ) bool OnJsClick;
	//_______________________________________________________________ DblClick
	void SetOnDblClick(bool fireEvent);
	bool GetOnDblClick();
	__declspec( property( get=GetOnDblClick, put=SetOnDblClick) ) bool OnDblClick;
	//
	void SetOnJsDblClick(bool fireEvent);
	bool GetOnJsDblClick();
	__declspec( property( get=GetOnJsDblClick, put=SetOnJsDblClick) ) bool OnJsDblClick;
	//_______________________________________________________________ MouseDown
	void SetOnMouseDown(bool fireEvent);
	bool GetOnMouseDown();
	__declspec( property( get=GetOnMouseDown, put=SetOnMouseDown) ) bool OnMouseDown;
	//
	void SetOnJsMouseDown(bool fireEvent);
	bool GetOnJsMouseDown();
	__declspec( property( get=GetOnJsMouseDown, put=SetOnJsMouseDown) ) bool OnJsMouseDown;
	//_______________________________________________________________ MouseUp
	void SetOnMouseUp(bool fireEvent);
	bool GetOnMouseUp();
	__declspec( property( get=GetOnMouseUp, put=SetOnMouseUp) ) bool OnMouseUp;
	//
	void SetOnJsMouseUp(bool fireEvent);
	bool GetOnJsMouseUp();
	__declspec( property( get=GetOnJsMouseUp, put=SetOnJsMouseUp) ) bool OnJsMouseUp;
	//_______________________________________________________________ MouseMove
	void SetOnMouseMove(bool fireEvent);
	bool GetOnMouseMove();
	__declspec( property( get=GetOnMouseMove, put=SetOnMouseMove) ) bool OnMouseMove;
	//
	void SetOnJsMouseMove(bool fireEvent);
	bool GetOnJsMouseMove();
	__declspec( property( get=GetOnJsMouseMove, put=SetOnJsMouseMove) ) bool OnJsMouseMove;
	//_______________________________________________________________ MouseOut
	void SetOnMouseOut(bool fireEvent);
	bool GetOnMouseOut();
	__declspec( property( get=GetOnMouseOut, put=SetOnMouseOut) ) bool OnMouseOut;
	//
	void SetOnJsMouseOut(bool fireEvent);
	bool GetOnJsMouseOut();
	__declspec( property( get=GetOnJsMouseOut, put=SetOnJsMouseOut) ) bool OnJsMouseOut;
	//_______________________________________________________________ Focus
	void SetOnFocus(bool fireEvent);
	bool GetOnFocus();
	__declspec( property( get=GetOnFocus, put=SetOnFocus) ) bool OnFocus;
	//
	void SetOnJsFocus(bool fireEvent);
	bool GetOnJsFocus();
	__declspec( property( get=GetOnJsFocus, put=SetOnJsFocus) ) bool OnJsFocus;
	//_______________________________________________________________ Blur
	void SetOnBlur(bool fireEvent);
	bool GetOnBlur();
	__declspec( property( get=GetOnBlur, put=SetOnBlur) ) bool OnBlur;
	//
	void SetOnJsBlur(bool fireEvent);
	bool GetOnJsBlur();
	__declspec( property( get=GetOnJsBlur, put=SetOnJsBlur) ) bool OnJsBlur;
	//_______________________________________________________________ KeyPress
	void SetOnKeyPress(bool fireEvent);
	bool GetOnKeyPress();
	__declspec( property( get=GetOnKeyPress, put=SetOnKeyPress) ) bool OnKeyPress;
	//
	void SetOnJsKeyPress(bool fireEvent);
	bool GetOnJsKeyPress();
	__declspec( property( get=GetOnJsKeyPress, put=SetOnJsKeyPress) ) bool OnJsKeyPress;
	//_______________________________________________________________ KeyDown
	void SetOnKeyDown(bool fireEvent);
	bool GetOnKeyDown();
	__declspec( property( get=GetOnKeyDown, put=SetOnKeyDown) ) bool OnKeyDown;
	//
	void SetOnJsKeyDown(bool fireEvent);
	bool GetOnJsKeyDown();
	__declspec( property( get=GetOnJsKeyDown, put=SetOnJsKeyDown) ) bool OnJsKeyDown;
	//_______________________________________________________________ KeyUp
	void SetOnKeyUp(bool fireEvent);
	bool GetOnKeyUp();
	__declspec( property( get=GetOnKeyUp, put=SetOnKeyUp) ) bool OnKeyUp;
	//
	void SetOnJsKeyUp(bool fireEvent);
	bool GetOnJsKeyUp();
	__declspec( property( get=GetOnJsKeyUp, put=SetOnJsKeyUp) ) bool OnJsKeyUp;
	//_______________________________________________________________ Select
	void SetOnSelect(bool fireEvent);
	bool GetOnSelect();
	__declspec( property( get=GetOnSelect, put=SetOnSelect) ) bool OnSelect;
	//
	void SetOnJsSelect(bool fireEvent);
	bool GetOnJsSelect();
	__declspec( property( get=GetOnJsSelect, put=SetOnJsSelect) ) bool OnJsSelect;
	//_______________________________________________________________ Change
	void SetOnChange(bool fireEvent);
	bool GetOnChange();
	__declspec( property( get=GetOnChange, put=SetOnChange) ) bool OnChange;
	//
	void SetOnJsChange(bool fireEvent);
	bool GetOnJsChange();
	__declspec( property( get=GetOnJsChange, put=SetOnJsChange) ) bool OnJsChange;
	//_______________________________________________________________
	//
protected:
	void RenderClassAndStyle(Sys::ITextWriterW& out_html);
	void RenderJavascriptEvents(Sys::ITextWriterW& out_html, const wchar_t* url);
	void RenderName(Sys::ITextWriterW& out_html);
	unsigned int memoryBlock1;
	unsigned int memoryBlock2;
	// Visible:                                                            memoryBlock2: 0000 0000 0000 0000 00000 1000 0000 0000
	// Enabled:                                                           memoryBlock2: 0000 0000 0000 0000 00000 0100 0000 0000
	// ListBox, ComboBox, ListView, CheckBoxList:AjaxUpdate:    memoryBlock2: 0000 0000 0000 0000 00000 0010 0000 0000
	// Button:Submit:                                                  memoryBlock2:0000 0000 0000 0000 00000 0000 0100 0000
	// TextBox:Password:                                          memoryBlock2:0000 0000 0000 0000 00000 0000 0010 0000
	// TextBox:ReadOnly:                                          memoryBlock2:0000 0000 0000 0000 00000 0000 0001 0000
};

//________________________________________________________ Button
class Button : public Web::VisibleObject
{
public:
	Button();
	~Button();
	wstring Text;
	//
	void SetSubmit(bool isSubmit);
	bool IsSubmit();
	__declspec( property ( get=IsSubmit, put=SetSubmit ) ) bool Submit;
	//
	void GetPreview(int& indentCount, Sys::ITextWriterW& out_html);
	//
	void GetHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	void GetXml(Web::HttpConnector& httpConnector);
	void LoadState(Web::HttpConnector& httpConnector);
	void OnNavigateAway(Web::HttpConnector& httpConnector);
protected:
	wchar_t* GetTag();
};

//________________________________________________________ Textbox
class Textbox : public Web::VisibleObject, public Sql::ISelectString
{
public:
	Textbox();
	~Textbox();
	wstring Text;
	int MaxLength;
	int ColCount;
	int RowCount;
	void ShowBalloonTip(const wchar_t* caption, const wchar_t* text, int icon); //icon: TTI_INFO, TTI_WARNING, TTI_ERROR
	void ShowBalloonTip(const wstring& caption, const wstring& text, int icon); //icon: TTI_INFO, TTI_WARNING, TTI_ERROR
	//
	void SetPassword(bool isPassword);
	bool GetPassword();
	__declspec( property ( get=GetPassword, put=SetPassword ) ) bool Password;
	//
	void SetReadOnly(bool readOnly);
	bool GetReadOnly();
	__declspec( property ( get=GetReadOnly, put=SetReadOnly ) ) bool ReadOnly;
	//
	int GetInt(void);
	void SetInt(int value);
	__declspec( property( get=GetInt, put=SetInt) ) int IntValue;
	//
	void SetDouble(double value, const wchar_t* format);
	void SetDouble(double value);
	double GetDouble();
	__declspec( property( get=GetDouble, put=SetDouble) ) double DoubleValue;
	//
	void GetPreview(int& indentCount, Sys::ITextWriterW& out_html, bool isBrowserView);
	void GetHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	void GetXml(Web::HttpConnector& httpConnector);
	void LoadState(Web::HttpConnector& httpConnector);
	void OnNavigateAway(Web::HttpConnector& httpConnector);
	//_____________________________________________________________________ ISelectString
	wstring& SqlGetString();
	void SqlUpdate(bool toGui);
	//
	//operator wstring&();
protected:
	wchar_t* GetTag();
	wstring _balloonCaption;
	wstring _balloonText;
	int _balloonIcon;
	void RenderBalloon(int& indentCount, Sys::ITextWriterW& out_html);
};

class DropDownList;
class ListBox;
//_____________________________________________________________________ ListItem
class ListItem
{
public:
	ListItem();
	~ListItem();
	wstring Text;
	wstring Data;
	bool Selected;	
	bool operator==(const ListItem& init) const;
	bool operator!=(const ListItem& init) const;
};

//_____________________________________________________________________ ListItemCollection
class ListItemCollection
{
public:
	ListItemCollection(void);
	virtual ~ListItemCollection(void);
	//
	void Add(const wchar_t* text, const wchar_t* data);
	void Add(const wstring& text, const wstring& data);
	void Add(const wchar_t* text, const wchar_t* data, bool selected);
	void Add(const wstring& text, const wstring& data, bool selected);
	//
	bool Delete(int index);
	void DeleteAll();
	//
	int GetCount();
	__declspec( property( get=GetCount ) ) int Count;	
	//
	int GetIndex(const wchar_t* text);
	Web::ListItem& operator[](long index);
	//
	vector<ListItem> storage;
	bool operator==(const ListItemCollection& init) const;
private:
	friend class Web::DropDownList;
	friend class Web::ListBox;
	int _selectedIndex;
	int GetLoadItemIndex(const wchar_t* data);
};

class Page;

//________________________________________________________ DropDownList
class DropDownList : public Web::VisibleObject, public Sql::ISqlNumerator, public Sql::ISelectString
{
public:
	DropDownList();
	~DropDownList();
	//
	bool SetSelected(int index);
	int GetSelectedIndex();
	__declspec( property( get=GetSelectedIndex, put=SetSelected ) ) int SelectedIndex;
	//
	//_______________________________________________________________ AjaxUpdate
	void SetAjaxUpdate(bool update); 
	bool GetAjaxUpdate();
	__declspec( property( get=GetAjaxUpdate, put=SetAjaxUpdate) ) bool AjaxUpdate;
	//
	bool SetSelected(const wchar_t* text);
	//
	bool SetSelectedByData(const wstring& data);
	wstring GetSelectedData();
	__declspec( property ( get=GetSelectedData, put=SetSelectedByData ) ) wstring SelectedData;
	//
	ListItemCollection Items;
	//
	void GetHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	void GetXml(Web::HttpConnector& httpConnector);
	void LoadState(Web::HttpConnector& httpConnector);
	void OnNavigateAway(Web::HttpConnector& httpConnector);
	//_____________________________________________________________________ ISqlNumerator
	void Enumerate(wchar_t** data, int colCount, int rowIndex);
	//_____________________________________________________________________ ISelectGetString
	wstring& SqlGetString();
	void SqlUpdate(bool toGui);
protected:
	virtual void RenderInvisible(int& indentCount, Sys::ITextWriterW& out_html);
	wchar_t* GetTag();
	int _rowCount;
	wstring _sqlData;
	//wstring _selectedData;
	//
	//ListItemCollection _prevItems;
	virtual void RenderMultipleSelection(Sys::ITextWriterW& out_html);
	friend class Web::Page;
};

//________________________________________________________ ListBox
class ListBox : public Web::DropDownList
{
public:
	ListBox();
	~ListBox();
	//
	bool MultipleSelection;
	//
	void SetHeight(int height);
	int GetHeight();
	__declspec( property ( get=GetHeight, put=SetHeight ) ) int Height;
	//
	bool SetSelected(int itemIndex, bool selected);// Use itemIndex=-1 to affect all rows
	//
	//void LoadState(Web::HttpConnector& httpConnector);
protected:
	void RenderInvisible(int& indentCount, Sys::ITextWriterW& out_html);
	void RenderMultipleSelection(Sys::ITextWriterW& out_html);
};

class ListView;
class CheckBoxList;

//_____________________________________________________________________ ListViewItem
class ListViewItem
{
public:
	ListViewItem();
	~ListViewItem();
	bool Selected;
	wstring Data;
	vector<wstring> Text;
	bool operator==(const 	ListViewItem& init) const;
	bool operator!=(const 	ListViewItem& init) const;
};

//_____________________________________________________________________ CheckBoxItem
class CheckBoxItem
{
public:
	CheckBoxItem();
	~CheckBoxItem();
	bool Checked;
	wstring Data;
	vector<wstring> Text;
	bool operator==(const 	CheckBoxItem& init) const;
	bool operator!=(const 	CheckBoxItem& init) const;
};

//_____________________________________________________________________ ListViewColumn
struct ListViewColumn
{
	int format;//LVCFMT_LEFT, LVCFMT_CENTER, LVCFMT_RIGHT
	int width;
	wstring Text;
};

//_____________________________________________________________________ CheckBoxColumnn
struct CheckBoxColumn
{
	int format;//LVCFMT_LEFT, LVCFMT_CENTER, LVCFMT_RIGHT
	wstring Text;
};

//_____________________________________________________________________ ListViewItemCollection
class ListViewItemCollection
{
public:
	ListViewItemCollection(void);
	virtual ~ListViewItemCollection(void);
	//
	void Add(const wchar_t* text, const wchar_t* data);
	void Add(const wstring& text, const wstring& data);
	void Add(const wchar_t* text, const wchar_t* data, bool selected);
	void Add(const wstring& text, const wstring& data, bool selected);
	//
	bool Delete(int index);
	void DeleteAll();
	//
	__declspec( property( get=GetCount ) ) int Count;
	int GetCount();
	//
	int GetIndex(const wchar_t* text);
	Web::ListViewItem& operator[](long index);
	//
	vector<ListViewItem> storage;
	bool operator==(const ListViewItemCollection& init) const;
private:
	friend class Web::ListView;
	vector<Web::ListViewColumn>* colsCollection;
	int _selectedIndex;
	int GetLoadItemIndex(const wchar_t* data);
};

//_____________________________________________________________________ CheckBoxItemCollection
class CheckBoxItemCollection
{
public:
	CheckBoxItemCollection(void);
	virtual ~CheckBoxItemCollection(void);
	//
	void Add(const wchar_t* text, const wchar_t* data);
	void Add(const wstring& text, const wstring& data);
	void Add(const wchar_t* text, const wchar_t* data, bool checked);
	void Add(const wstring& text, const wstring& data, bool checked);
	//
	bool Delete(int index);
	void DeleteAll();
	//
	__declspec( property( get=GetCount ) ) int Count;
	int GetCount();
	//
	int GetIndex(const wchar_t* text);
	Web::CheckBoxItem& operator[](long index);
	//
	vector<CheckBoxItem> storage;
	bool operator==(const CheckBoxItemCollection& init) const;
private:
	friend class Web::CheckBoxList;
	vector<Web::CheckBoxColumn>* colsCollection;
	int GetLoadItemIndex(const wchar_t* data);
};

//_____________________________________________________________________ ListViewColCollection
class ListViewColCollection
{
public:
	ListViewColCollection(void);
	virtual ~ListViewColCollection(void);
	bool Add(int format, int width, const wchar_t* text); // format: LVCFMT_LEFT, LVCFMT_CENTER, LVCFMT_RIGHT
	bool Add(int format, int width, wstring& text);
	//
	bool Delete(int index);
	void DeleteAll(void);
	//
	__declspec( property( get=GetCount ) ) int Count;
	int GetCount();
	//
	Web::ListViewColumn& operator[](long index);
	vector<Web::ListViewColumn> storage;
};

//_____________________________________________________________________ CheckBoxColCollection
class CheckBoxColCollection
{
public:
	CheckBoxColCollection(void);
	virtual ~CheckBoxColCollection(void);
	bool Add(int format, const wchar_t* text); // format: LVCFMT_LEFT, LVCFMT_CENTER, LVCFMT_RIGHT
	bool Add(int format, wstring& text);
	//
	bool Delete(int index);
	void DeleteAll(void);
	//
	__declspec( property( get=GetCount ) ) int Count;
	int GetCount();
	//
	Web::CheckBoxColumn& operator[](long index);
	vector<Web::CheckBoxColumn> storage;
};

//________________________________________________________ ListView
class ListView : public Web::VisibleObject, public Sql::ISqlNumerator
{
public:
	ListView();
	~ListView();
	wstring Text;
	int Height;
	int FontSize;
	bool MultipleSelection;
	//
	Web::ListViewColCollection Cols;
	Web::ListViewItemCollection Items;
	//_____________________________________________________ ISqlNumerator
	void Enumerate(wchar_t** data, int colCount, int rowIndex);
	//
	//_______________________________________________________________ AjaxUpdate
	void SetAjaxUpdate(bool update); 
	bool GetAjaxUpdate();
	__declspec( property( get=GetAjaxUpdate, put=SetAjaxUpdate) ) bool AjaxUpdate;
	//
	bool SetSelected(int itemIndex, bool selected);// Use itemIndex=-1 to affect all rows
	bool SetSelected(int index);// Use this for single item selection
	int GetSelectedIndex();
	__declspec( property( get=GetSelectedIndex, put=SetSelected ) ) int SelectedIndex;
	//
	bool SetSelected(const wchar_t* text);
	//
	bool SetSelectedByData(const wstring& data);
	wstring& GetSelectedData();
	__declspec( property ( get=GetSelectedData, put=SetSelectedByData ) ) wstring SelectedData;
	//
	void GetPreview(int& indentCount, Sys::ITextWriterW& out_html, bool isBrowserView);
	//
	void GetHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	void GetXml(Web::HttpConnector& httpConnector);
	void LoadState(Web::HttpConnector& httpConnector);
	void OnNavigateAway(Web::HttpConnector& httpConnector);
protected:
	void RenderHeader(int& indentCount, Sys::ITextWriterW& out_html);
	void RenderItem(Web::ListViewItem& item, const wchar_t * space, Sys::ITextWriterW& out_html);
	void RenderColumn(const wstring& text, vector<Web::ListViewColumn>::iterator& col, const wchar_t * space, wstring& truncate, Sys::ITextWriterW& out_html);
	wchar_t* GetTag();
	int GetTotalWidth();
	//
	friend class Web::Page;
};

//________________________________________________________ RadioButton
class RadioButton : public Web::VisibleObject, public Sql::ISelectBool
{
public:
	RadioButton();
	~RadioButton();
	wstring Text;
	wstring Data;
	bool Checked;
	//
	wstring Name; //Assign the same Name to all the radio buttons in a group
	wstring AccessKey;
	void GetHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	void GetXml(Web::HttpConnector& httpConnector);
	void LoadState(Web::HttpConnector& httpConnector);
	void OnNavigateAway(Web::HttpConnector& httpConnector);
	//_____________________________________________________________________ ISelectBool
	bool& SqlGetBool();
	void SqlUpdate(bool toGui);
protected:
	wchar_t* GetTag();
};

//________________________________________________________ CheckBox
class CheckBox : public Web::VisibleObject, public Sql::ISelectBool
{
public:
	CheckBox();
	~CheckBox();
	wstring Text;
	bool Checked;
	//
	void GetHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	void GetXml(Web::HttpConnector& httpConnector);
	void LoadState(Web::HttpConnector& httpConnector);
	void OnNavigateAway(Web::HttpConnector& httpConnector);
	//_____________________________________________________________________ ISelectBool
	bool& SqlGetBool();
	void SqlUpdate(bool toGui);
protected:
	wchar_t* GetTag();
};

//________________________________________________________ HiddenValue
class HiddenValue : public Web::Object
{
public:
	HiddenValue();
	~HiddenValue();
	wstring Data;
	void GetHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	void GetXml(Web::HttpConnector& httpConnector);
	void LoadState(Web::HttpConnector& httpConnector);
	void OnNavigateAway(Web::HttpConnector& httpConnector);
protected:
	wchar_t* GetTag();
};

//________________________________________________________ Image
class Image : public Web::VisibleObject
{
public:
	Image();
	~Image();
	wstring Text; //alt;
	wstring src;
	void GetHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	void GetXml(Web::HttpConnector& httpConnector);
	void LoadState(Web::HttpConnector& httpConnector);
	void OnNavigateAway(Web::HttpConnector& httpConnector);
protected:
	wchar_t* GetTag();
};

//________________________________________________________ ImageLink
class ImageLink : public Web::VisibleObject
{
public:
	ImageLink();
	~ImageLink();
	wstring Text; //alt
	wstring src; 
	wstring href; //http://www.yahoo.com, mailto:system@hotmail.com, ftp://ugto.mx, ftp://username:password@ugto.mx, windowID
	wstring targetWindowName;
	wstring AccessKey;
	wstring tabIndex;
	//Web::Css imageCss;
	wstring imageCssClass;
	void GetHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	void GetXml(Web::HttpConnector& httpConnector);
	void LoadState(Web::HttpConnector& httpConnector);
	void OnNavigateAway(Web::HttpConnector& httpConnector);
protected:
	bool HrefNavigateTo(Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	wchar_t* GetTag();
};

//________________________________________________________ TextLink
class TextLink : public Web::VisibleObject
{
public:
	TextLink();
	~TextLink();
	wstring Text; //alt
	wstring href; //http://www.yahoo.com, mailto:system@hotmail.com, ftp://ugto.mx, ftp://username:password@ugto.mx, windowID
	wstring targetWindowName;
	wstring AccessKey;
	wstring tabIndex;
	void GetHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	void GetXml(Web::HttpConnector& httpConnector);
	void LoadState(Web::HttpConnector& httpConnector);
	void OnNavigateAway(Web::HttpConnector& httpConnector);
protected:
	wchar_t* GetTag();
	bool HrefNavigateTo(Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
};

#ifdef WIN_GDI_PLUS_ON
//________________________________________________________ DynamicImage
class DynamicImage : public Web::VisibleObject
{
public:
	DynamicImage();
	~DynamicImage();
	COLORREF LineColor;
	wstring Text;
	bool WhiteAndBlack;
	//
	void GetHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	void GetXml(Web::HttpConnector& httpConnector);
	void LoadState(Web::HttpConnector& httpConnector);	
	void OnNavigateAway(Web::HttpConnector& httpConnector);
	//
	void RenderImage(string& data);
	virtual void BuildBitmap(Gdiplus::Graphics& graphics, Gdiplus::Font& font, Gdiplus::SolidBrush& brushFont, Gdiplus::Pen& penLine, Gdiplus::Pen& penText) = 0; 
	virtual void Sync(Web::HttpConnector& h) = 0;
	void BasicSync(Web::HttpConnector& h);
protected:
	bool ColorSync(Web::HttpConnector& h, const wchar_t* red, const wchar_t* green, const wchar_t* blue, COLORREF& color);
	void RenderProperties(Web::DynamicImage& di, wstring& text);
	virtual void GetSource(wstring& source, const wchar_t* url) = 0;
	wchar_t* GetTag();
	void RenderValue(const wchar_t* name, wstring& value, wstring& output);
	void RenderValue(const wchar_t* name, double value, wstring& output);
	void RenderValue(const wchar_t* name, int value, wstring& output);
	void RenderValue(const wchar_t* name, bool value, wstring& output);
	wstring encodedText;
};
#endif

//________________________________________________________ Bar
class Bar
{
public:
	Bar();
	~Bar();
	wstring Text;
	COLORREF Color;
	double Value;
	bool operator<(const Web::Bar& bar) const;
};

//_________________________________________________________ BarCollection
class BarCollection
{
public:
	BarCollection();
	~BarCollection();
	void Add(const wstring& text, COLORREF color, double value);
	void DeleteAll();
	//
	Web::Bar& operator[](long index);
	//
	int GetCount();
	__declspec( property( get=GetCount) ) int Count; 
	//
	vector<Web::Bar> storage;
};

#ifdef WIN_GDI_PLUS_ON
//________________________________________________________ BarChart
class BarChart : public Web::DynamicImage
{
public:
	BarChart();
	~BarChart();
	//
	Web::BarCollection Bars;
	int DivYCount;
	double MaxY; // To set the maximum value of Y you must set Autoscale to false
	bool AutoScale;
	//
	void BuildBitmap(Gdiplus::Graphics& graphics, Gdiplus::Font& font, Gdiplus::SolidBrush& brushFont, Gdiplus::Pen& penLine, Gdiplus::Pen& penText);
	void Sync(Web::HttpConnector& h);
protected:
	void GetSource(wstring& source, const wchar_t* url);
	double GetMaxY();
	void ComputeBox(Gdiplus::RectF& box);
};
#endif

//________________________________________________________ CheckBoxList
class CheckBoxList  : public Web::VisibleObject, public Sql::ISqlNumerator
{
public:
	CheckBoxList();
	~CheckBoxList();
	wstring Text;
	//
	Web::CheckBoxColCollection Cols;
	Web::CheckBoxItemCollection Items;
	//_____________________________________________________ ISqlNumerator
	void Enumerate(wchar_t** data, int colCount, int rowIndex);
	//
	//_______________________________________________________________ AjaxUpdate
	void SetAjaxUpdate(bool update); 
	bool GetAjaxUpdate();
	__declspec( property( get=GetAjaxUpdate, put=SetAjaxUpdate) ) bool AjaxUpdate;
	//
	void GetPreview(int& indentCount, Sys::ITextWriterW& out_html, bool isBrowserView);
	//
	void GetHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	void GetXml(Web::HttpConnector& httpConnector);
	void LoadState(Web::HttpConnector& httpConnector);
	void OnNavigateAway(Web::HttpConnector& httpConnector);
	//
protected:
	wchar_t* GetTag();
	void RenderState(int& indentCount, Sys::ITextWriterW& out_html);
	void RenderData(int& indentCount, Sys::ITextWriterW& out_html);
	//
	friend class Web::Page;
};

//________________________________________________________ DateTimeBox
class DateTimeBox : public Web::VisibleObject, public Sql::ISelectTime
{
public:
	DateTimeBox();
	~DateTimeBox();
	//
	wstring CssFile;
	//
	//void GetCurrentSelection(Sys::Time& systime);
	////
	//Sys::Time GetCurrentSelection();
	//void SetCurrentSelection(Sys::Time& systime);
	//__declspec( property( get=GetCurrentSelection, put=SetCurrentSelection) ) 
	Sys::Time SelectedDate;
	//
	void GetCurrentSelection(int& month, int& day, int& year);
	void SetCurrentSelection(int month, int day, int year);
	//
	virtual void GetPreview(int& indentCount, Sys::ITextWriterW& out_html, bool isBrowserView);
	//
	virtual void GetHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	void GetXml(Web::HttpConnector& httpConnector);
	void LoadState(Web::HttpConnector& httpConnector);
	void OnNavigateAway(Web::HttpConnector& httpConnector);
	//
	int Language; // WIN_LANGUAGE_ENGLISH, WIN_LANGUAGE_SPANISH
	//_______________________________________ ISelectTime
	Sys::SqlTime& SqlGetTime();
	Sys::Time& SqlGetSysTime();
	void SqlUpdate(bool toGui);
protected:
	void GetText(wchar_t* buffer, int bufferLength);
	wchar_t* GetTag();
	//Sys::Time _systemtime;	
	Sys::SqlTime _sqltime;
};

//________________________________________________________ DateView
class DateView : public Web::DateTimeBox
{
public:
	DateView();
	~DateView();
	//
	void GetPreview(int& indentCount, Sys::ITextWriterW& out_html, bool isBrowserView);
	void GetHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
};

//________________________________________________________ PlugIn: FlashPlayer, ...
struct ObjectParam
{
	wstring name;
	wstring value;
};

class PlugIn : public Web::VisibleObject
{
public:
	PlugIn();
	~PlugIn();
	wstring Type;
	wstring Data;
	vector<Web::ObjectParam> param;
	void AddParam(const wchar_t* name, const wchar_t* value);
	void AddParam(const wstring& name, const wstring& value);
	void GetPreview(int& indentCount, Sys::ITextWriterW& out_html, bool isBrowserView);
	//
	void GetHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	void GetXml(Web::HttpConnector& httpConnector);
	void LoadState(Web::HttpConnector& httpConnector);
	void OnNavigateAway(Web::HttpConnector& httpConnector);
protected:
	wchar_t* GetTag();
};

//<object type="application/x-shockwave-flash" width="400" height="220" 
//	wmode="transparent" data="flvplayer.swf?file=movies/holiday.flv">
//	<param name="movie" value="flvplayer.swf?file=movies/holiday.flv" />
//	<param name="wmode" value="transparent" />
//</object>

//________________________________________________________ Pie
class Pie
{
public:
	Pie();
	~Pie();
	wstring Text;
	COLORREF Color;
	double Value;
	bool operator<(const Web::Pie& pie) const;
};

//_________________________________________________________ PieCollection
class PieCollection
{
public:
	PieCollection();
	~PieCollection();
	void Add(const wstring& text, COLORREF color, double value);
	void DeleteAll();
	//
	Web::Pie& operator[](long index);
	//
	int GetCount();
	__declspec( property( get=GetCount) ) int Count; 
	//
	vector<Web::Pie> storage;
};


#ifdef WIN_GDI_PLUS_ON

//_____________________________________________________________________Graph
class Graph
{
public:
	enum Type {TypeDot = 0, TypeLine, TypeCross, TypeCircle, TypeSquare, TypeHistogram};
	Graph();
	virtual ~Graph();
	COLORREF color;
	int penWidth;
	wstring caption;
	Graph::Type type;
	vector<Sys::PointF> point;
	//
	double GetMaxX();
	double GetMaxY();
};

//_____________________________________________________________________ GraphCollection
class GraphCollection
{
public:
	GraphCollection();
	~GraphCollection();
	int Add(int graphPointCount);
	int Add();
	void Delete(long index);
	void DeleteAll();
	Web::Graph& operator[](long index);
	int GetCount();
	__declspec( property( get=GetCount) ) int Count;
	vector<Web::Graph> storage;
};

//________________________________________________________ PieChart
class PieChart : public Web::DynamicImage
{
public:
	PieChart();
	~PieChart();
	Web::PieCollection Pies;
	void BuildBitmap(Gdiplus::Graphics& graphics, Gdiplus::Font& font, Gdiplus::SolidBrush& brushFont, Gdiplus::Pen& penLine, Gdiplus::Pen& penText);
	void Sync(Web::HttpConnector& h);
protected:
	void GetSource(wstring& source, const wchar_t* url);
};

//________________________________________________________ PolarChart
class PolarChart : public Web::DynamicImage
{
public:
	PolarChart();
	~PolarChart();
	Web::GraphCollection Graphs;
	double MinRadius;
	double MaxRadius;
	bool AutoScale;
	bool ShowSubgrid;
	COLORREF SubgridColor;
	//
	void BuildBitmap(Gdiplus::Graphics& graphics, Gdiplus::Font& font, Gdiplus::SolidBrush& brushFont, Gdiplus::Pen& penLine, Gdiplus::Pen& penText);
	void Sync(Web::HttpConnector& h);
protected:
	void GetSource(wstring& source, const wchar_t* url);
	virtual void OnPaintScaleR(Gdiplus::Graphics& graphics, Gdiplus::Font& font, Gdiplus::SolidBrush& brushFont, Gdiplus::PointF& center, double value); //Overwrite this functions to chante the scale
	void PaintGraphs(Gdiplus::Graphics& graphics);
	virtual void DrawGraph(Gdiplus::Graphics& graphics, Gdiplus::Pen& pen, int graphIndex);
	void Line(Gdiplus::Graphics& graphics, Gdiplus::Pen& pen, double angle, double radius);
	void ShortLine(Gdiplus::Graphics& graphics, Gdiplus::Pen& pen, double angle, double radius);
private:
	int TransformToScreenCoordinatesX(double tetha, double r) 
	{
		r -= MinRadius;
		if (r>0)
			return (int)(r * _scale*cos(tetha) + _centerX+0.5);
		else
			return (int)(r * _scale*cos(tetha+M_PI)+ _centerX+0.5);
	}	
	int TransformToScreenCoordinatesY(double tetha, double r) 
	{
		r -= MinRadius;
		if (r>0)
			return (int)(-r* _scale*sin(tetha)+ _centerY+0.5);
		else
			return (int)(-r* _scale*sin(tetha+M_PI)+ _centerY+0.5);
	}
	double _scale;
	double _centerX;
	double _centerY;
};

//________________________________________________________ XyChart
class XyChart : public Web::DynamicImage
{
public:
	XyChart();
	~XyChart();
	//
	Web::GraphCollection Graphs;
	double MinX;
	double MaxX;
	double MinY;
	double MaxY;
	int DivisionCountX;
	int DivisionCountY;
	int SubDivisionCountX;
	int SubDivisionCountY;
	wstring CaptionX;
	wstring CaptionY;
	bool LogScaleX;
	bool LogScaleY;
	COLORREF SubgridColor;
	bool AutoScaleX;
	bool AutoScaleY;
	//
	void BuildBitmap(Gdiplus::Graphics& graphics, Gdiplus::Font& font, Gdiplus::SolidBrush& brushFont, Gdiplus::Pen& penLine, Gdiplus::Pen& penText);
	void Sync(Web::HttpConnector& h);
protected:
	double _minX;
	double _maxX;
	double _minY;
	double _maxY;
	double _originX;
	double _originY;
	double _scaleX;
	double _scaleY;
	void GetSource(wstring& source, const wchar_t* url);
	double TransformFromScreenCoordinatesX(int x);
	double TransformFromScreenCoordinatesY(int y); 
	void PaintCaptionX(Gdiplus::Graphics& graphics, Gdiplus::Font& font, Gdiplus::Brush& brush);
	void PaintCaptionY(Gdiplus::Graphics& graphics, Gdiplus::Font& font, Gdiplus::Brush& brush);
	void PaintScaleX(Gdiplus::Graphics& graphics, Gdiplus::Font& font, Gdiplus::Brush& brush, double deltaX);
	void PaintScaleY(Gdiplus::Graphics& graphics, Gdiplus::Font& font, Gdiplus::Brush& brush, double deltaY);
	void PaintDivX(Gdiplus::Graphics& graphics, Gdiplus::Pen& pen);
	void PaintDivY(Gdiplus::Graphics& graphics, Gdiplus::Pen& pen);
	void PaintSubDivX(Gdiplus::Graphics& graphics, Gdiplus::Pen& pen);
	void PaintSubDivY(Gdiplus::Graphics& graphics, Gdiplus::Pen& pen);
	void PaintGraphs(Gdiplus::Graphics& graphics, Gdiplus::Font& font);
	virtual void OnPaintScaleX(Gdiplus::Graphics& graphics, Gdiplus::Font& font, Gdiplus::Brush& brush, int index, double delta, double value);
	virtual void OnPaintScaleY(Gdiplus::Graphics& graphics, Gdiplus::Font& font, Gdiplus::Brush& brush, int index, double delta, double value);
	virtual void DrawGraph(Gdiplus::Graphics& graphics, int graphIndex);

	Gdiplus::REAL TransformToScreenCoordinatesX(double x) 
	{
		return (Gdiplus::REAL)((x - _minX)* _scaleX + _originX);
	}
	Gdiplus::REAL TransformToScreenCoordinatesY(double y) 
	{
		return (Gdiplus::REAL)(( y - _minY)* _scaleY +  _originY);
	}
	void _AutoScaleX();
	void _AutoScaleY();
	double _boxCaptionHeight;
	void OnSizePrivate();
	RECT _rcMain;
};

//________________________________________________________ Histogram
class Histogram : public Web::XyChart
{
public:
	Histogram();
	~Histogram();
	void SetData(valarray<double>& data, int resolution, bool percentDisplay);
};

#endif

//________________________________________________________ ProgressBar
class ProgressBar
{
public:
	ProgressBar();
	~ProgressBar();
	void RenderImage(string& data);
};

//________________________________________________________ Label
class Label : public Web::VisibleObject
{
public:
	Label();
	~Label();
	wstring Text;
	int Type; // HTML_TND_SPAN, HTML_TND_P, HTML_TND_SMALL, HTML_TND_PRE,...
	void GetHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	void GetXml(Web::HttpConnector& httpConnector);
	void LoadState(Web::HttpConnector& httpConnector);
	void OnNavigateAway(Web::HttpConnector& httpConnector);
protected:
	wchar_t* GetTag();
};

//________________________________________________________ ParentNode
class ParentNode : public Web::VisibleObject
{
public:
	ParentNode();
	~ParentNode();
	int Type; //  HTML_PND_TABLE, HTML_PND_UL, HTML_PND_OL, HTML_PND_DL,...
	void AddChild(Web::Object& object);
	void GetHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	void GetXml(Web::HttpConnector& httpConnector);
	void LoadState(Web::HttpConnector& httpConnector);
	void OnNavigateAway(Web::HttpConnector& httpConnector);
	//______________________________________ This are implemented only for design time
	void GetPreHtml(int& indentCount, Sys::ITextWriterW& out_html);
	void GetPostHtml(int& indentCount, Sys::ITextWriterW& out_html);
	void GetPreChildHtml(int childIndex, int childCount, int& indentCount, Sys::ITextWriterW& out_html);
	void GetPostChildHtml(int childIndex, int childCount, int& indentCount, Sys::ITextWriterW& out_html);
protected:
	list<Web::Object*> child;
	wchar_t* GetTag();
};

//________________________________________________________ MessageBoxInfo
struct MessageBoxInfo
{
	wstring text;
	wstring caption;
	int iconType;
};

//________________________________________________________ Page
class Page
{
public:
	Page(void);
	virtual ~Page(void);
	//
	wstring Title;
	wstring CssFile;
	wstring JavascriptFile;
	wstring Author;
	wstring Keywords;
	wstring Refresh;
	wstring Description;
	wstring ID;
	//
	void MessageBox(const wchar_t * text, const wchar_t * caption, UINT iconType); //MB_ICONWARNING  MB_ICONERROR, MB_ICONINFORMATION
	void MessageBox(const wstring& text, const wstring& caption, UINT iconType); //MB_ICONWARNING  MB_ICONERROR, MB_ICONINFORMATION
	//
	void AddChild(Web::Object& object);
	void Run(Web::HttpConnector& httpConnector);
	virtual void EventHandler(Web::HttpConnector& h);
	virtual void InitializeGui();
	virtual void Window_Open(Web::HttpConnector& h);
	//__________________________________ 
	void GetHtml(bool indent, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	void GetXml(Web::HttpConnector& httpConnector);
	void LoadState(Web::HttpConnector& httpConnector);
	void OnNavigateAway(Web::HttpConnector& httpConnector);
	//
	void HeadItem(int indentCount, wstring& variable, const wchar_t* tagini, const wchar_t* tagend, Sys::ITextWriterW& out_html);
	//
	//_______________________________________________________________ Submit
	void SetOnSubmit(bool fireEvent); 
	bool GetOnSubmit();
	__declspec( property( get=GetOnSubmit, put=SetOnSubmit) ) bool OnSubmit;
	//_______________________________________________________________ Reset
	void SetOnReset(bool fireEvent); 
	bool GetOnReset();
	__declspec( property( get=GetOnReset, put=SetOnReset) ) bool OnReset;
	//_______________________________________________________________ Load
	void SetOnLoad(bool fireEvent); 
	bool GetOnLoad();
	__declspec( property( get=GetOnLoad, put=SetOnLoad) ) bool OnLoad;
	//_______________________________________________________________ Unload
	void SetOnUnload(bool fireEvent); 
	bool GetOnUnload();
	__declspec( property( get=GetOnUnload, put=SetOnUnload) ) bool OnUnload;
	//
	void GetPreHtml(int& indentCount, Sys::ITextWriterW& out_html);
	void GetPostHtml(int& indentCount, Sys::ITextWriterW& out_html, Web::HttpConnector& httpConnector);
	//
	bool isPreview;
private:
	list<Web::Object*> child;
	wstring script_name;
	vector<MessageBoxInfo> _msgbox;
	void RenderMessages(int& indentCount, Sys::ITextWriterW& out_html);
	void RenderXmlMessages(Web::HttpConnector& httpConnector);
	//_______________________________________________________________ GZipEncoding
	void SetGZipEncoding(bool gzipEncoding); 
	bool GetGZipEncoding();
	__declspec( property( get=GetGZipEncoding, put=SetGZipEncoding) ) bool GZipEncoding;
	//
	unsigned int memoryBlock;
};


} //____________________________________________________ namespace Web::End


