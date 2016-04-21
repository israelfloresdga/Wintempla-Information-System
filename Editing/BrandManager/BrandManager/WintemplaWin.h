#pragma once

/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.  I ACCEPT NO LIABILITY FOR ANY DAMAGE OR LOSS
   OF BUSINESS THAT THIS SOFTWARE MAY CAUSE.

   WintemplaWin.h
 
   © Copyright 2004 - 2014 Sergio Ledesma.  All Rights Reserved.

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

#include "Wintempla.h"
//_____________________________________________________________________Definitions
#define WINTEMPLA_WIN 1
#define WIN_MAX_FILTER 255 //For FileDlg
#define WIN_FILEDLG_MAXPATH 1024
#define MAX_FIND_LEN 1024 //For FindReplaceDlg
#define WIN_COLORDISPLAY_FONTFAMILYLENGTH 32
//#define DPD_MAX_NAME 255 //For PrintDoc and PageDlg
#define WPPD_PRINT 1000  //For PrintPreviewDlg
#define WPPD_PAGESETUP 1001  //For PrintPreviewDlg
#define WPPD_CLOSE 1002  //For PrintPreviewDlg
#define WPPD_UPDOWN 1003  //For PrintPreviewDlg
#define WPPD_PRINTPREVIEW 1004  //For PrintPreviewDlg
#define WPPD_PREV 1005  //For PrintPreviewDlg
#define WPPD_NEXT 1006  //For PrintPreviewDlg
#define WPPD_MSWORD 1007  //For PrintPreviewDlg
#define WPPD_MSEXCEL 1008  //For PrintPreviewDlg
#define WPPD_LETTER_PAGEWIDTH_CM (8.50*2.536)  //For PrintPreviewDlg
#define WPPD_LETTER_PAGEHEIGHT_CM (11.0*2.536)  //For PrintPreviewDlg
#define WPPD_LETTER_PAGEWIDTH_LU  21590 //For PrintPreviewDlg
#define WPPD_LETTER_PAGEHEIGHT_LU 27940 //For PrintPreviewDlg
#define WIN_VIEWER3D_MAX_DIV 20
#define WINXYCHART_PRINTERPEN 20
#define WINXYCHART_PRINTERPENGRAPH 40
#define WINFONT_MAXRES 4000
#define WIN_PIECHART_SZ 64
#define WIN_MONITOR_CONTROL_MAX 256
#define WIN_LEVELCONTROL_MAX 512
#define MM_DAC_NUM_BUFFER 8
#define MM_ADC_NUM_BUFFER 8
#define WINCOM_MAX_ADVISETOKEN 128
#define WIN_PRINTDOC_NAMEMAX 64
#define WIN_PRINTDOC_ELEMENTMAX 128
#define WIN_LEVEL_STATE_WIDTH 0.33
#define WIN_LEVEL_STATE_STATES 32
#define WIN_LEVEL_STATE_LEVELWIDTH 4
#define WIN_CLICK 1
#define WIN_RCLICK 2
#define WIN_DBLCLICK 3
#define WIN_PAINT 4
#define WIN_STARTED 5
#define WIN_STOPPED 6
#define WIN_DATADONE 7
#define WIN_DAC_DATA 8
#define WIN_ADC_DATA 9
#define WIN_HSCROLL 10
#define WIN_VSCROLL 11
#define WIN_REQUESTINFO 20
#define WNT_PAINTCELLSBEGIN 21
#define WNT_PAINTCELL 22
#define WNT_PAINTCELLSEND 23
#define WIN_ALL_EVENTS 24
//#define WIN_COMMAND_ALL 25
//#define WNT_PAINTHDREND 26
#define WIN_GETFILENAME 27
#define WIN_MODIFYSAMPLES 28
#define WIN_RX 50
#define WIN_TX 51
#define WIN_BREAKDETECT 52
#define WIN_FRAMINGERROR 53
#define WIN_HARDWAREOVERRUN 54
#define WIN_PARITYERROR 55
#define WIN_SOFTWAREOVERRUN 56
#define WIN_CTS 57
#define WIN_DSR 58
#define WIN_CD 59
#define WIN_RI 60
#define WIN_ALIGNMENT_LEFT 0
#define WIN_ALIGNMENT_RIGHT 1
#define WIN_ALIGNMENT_CENTER 2
#define WIN_ALIGNMENT_JUSTIFIED 3
//#define WIN_LISTTYPE_NONE 0
//#define WIN_LISTTYPE_NUMBER 1
//#define WIN_LISTTYPE_UNNUMBER 2
//#define WIN_FILEDAC_BUFFER_SIZE 32768
//#define WIN_FILEDAC_OVERLAP_SIZE 32768
#define WIN_FILEDAC_CHA 0
#define WIN_FILEDAC_CHB 1
#define WIN_FILEDAC_FROM_A_TO_B 2
#define WIN_FILEDAC_FROM_B_TO_A 3
#define WIN_FILEDAC_OVERLAP_GAIN -50.0
//#define WIN_FILEDAC_OVERLAP_GAIN (4.0/PLAYER_OVERLAP_SIZE)

//__________________________ CONTROLS APPEARANCE
#define WIN_LINE_COLOR RGB(90, 90, 90)
#define WIN_SUBLINE_COLOR RGB(30, 30, 30)
#define WIN_BACK_COLOR RGB(0, 0, 0)
#define WIN_TEXT_COLOR RGB(0, 200, 180)
#define WIN_BACK_DISABLED ::GetSysColor(COLOR_BTNFACE)
#define WIN_TEXT_DISABLED RGB(200, 200, 200)


#ifndef RB_GETBARHEIGHT
#define RB_GETBARHEIGHT (WM_USER + 27)
#endif

//________ Com
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")


#include <commctrl.h>
#include <commdlg.h>
#pragma comment(lib, "comctl32.lib")

namespace Win {
	typedef struct DLGTEMPLATEEX
	{
		WORD dlgVer;
		WORD signature;
		DWORD helpID;
		DWORD exStyle;
		DWORD style;
		WORD cDlgItems;
		short x;
		short y;
		short cx;
		short cy;
	} DLGTEMPLATEEX, *LPDLGTEMPLATEEX;
}

struct DLGWINTEMPLATE
{
	DLGTEMPLATE dlgTemplate;
	DWORD menu;
	DWORD dlgclass;
	DWORD title;
};

#include <poppack.h>

//_________________________ We define WIN_DAC_ADC_SUPPORT to include: <mmsystem.h>
#ifdef WIN_DIRECTX
	#define WIN_DAC_ADC_SUPPORT
	#include <d3d9.h>
	#include <d3dx9.h>

	_COM_SMARTPTR_TYPEDEF(IDirect3D9, __uuidof(IDirect3D9));
	_COM_SMARTPTR_TYPEDEF(IDirect3DVertexBuffer9, __uuidof(IDirect3DVertexBuffer9));
	_COM_SMARTPTR_TYPEDEF(IDirect3DDevice9, __uuidof(IDirect3DDevice9));

	#pragma comment(lib, "d3d9.lib")
	#pragma comment(lib, "DxErr.lib")
	#pragma comment(lib, "dxguid.lib")
#ifdef _DEBUG
	#pragma comment(lib, "d3dx10d.lib")
	#pragma comment(lib, "d3dx9d.lib")
#else
	#pragma comment(lib, "d3dx10.lib")
	#pragma comment(lib, "d3dx9.lib")
#endif
#endif

//_________________________ We define WIN_DAC_ADC_SUPPORT to include: <mmsystem.h>
#ifdef WIN_OPENGL_SUPPORT
	#define WIN_DAC_ADC_SUPPORT
	#include <gl\Gl.h>			// Header File For The OpenGL32 Library
	#include <gl\Glu.h>			// Header File For The GLu32 Library
	//#include <gl\glaux.h>		// Header File For The Glaux Library
	#pragma comment(lib, "opengl32.lib")
	#pragma comment(lib, "glu32.lib")
#endif

//#pragma comment(lib, "ole32.lib") // For Moniker in Com::Container

#ifdef WIN_RICHEDIT_SUPPORT
	#include <richedit.h>
#endif

//#include <shlobj.h>
//#include <shlwapi.h>
//#pragma comment(lib, "shlwapi.lib")
//#include "shellapi.h" // for the tray
#ifdef WIN_DAC_ADC_SUPPORT
	#define WIN_MIX_CONTROLS 2
	#include <mmsystem.h>
	#pragma comment(lib, "Winmm.lib")
	#define MM_MIDI_ACOUSTIC_GRAND_PIANO 0
	#define MM_MIDI_BRIGHT_ACOUSTIC_PIANO 1
	#define MM_MIDI_ELECTRIC_GRAND_PIANO 2
	#define MM_MIDI_HONKY_TONK_PIANO 3
	#define MM_MIDI_RHODES_PIANO 4
	#define MM_MIDI_CHORUSED_PIANO 5
	#define MM_MIDI_HARPSICHORD 6
	#define MM_MIDI_CLAVINET 7
	#define MM_MIDI_CELESTA 8
	#define MM_MIDI_GLOCKENSPIEL 9
	#define MM_MIDI_MUSIC BOX 10
	#define MM_MIDI_VIBRAPHONE 11
	#define MM_MIDI_MARIMBA  12
	#define MM_MIDI_XYLOPHONE 13
	#define MM_MIDI_TUBULAR BELLS 14
	#define MM_MIDI_DULCIMER 15
	#define MM_MIDI_HAMMOND _ORGAN 16
	#define MM_MIDI_PERCUSSIVE_ORGAN 17
	#define MM_MIDI_ROCK_ORGAN 18
	#define MM_MIDI_CHURCH_ORGAN 19
	#define MM_MIDI_REED_ORGAN 20
	#define MM_MIDI_ACCORDIAN 21
	#define MM_MIDI_HARMONICA 22
	#define MM_MIDI_TANGO_ACCORDIAN 23
	#define MM_MIDI_ACOUSTIC_GUITAR_NYLON 24
	#define MM_MIDI_ACOUSTIC_GUITAR_STEEL  25
	#define MM_MIDI_ELECTRIC_GUITAR_JAZZ  26
	#define MM_MIDI_ELECTRIC_GUITAR_CLEAN 27
	#define MM_MIDI_ELECTRIC_GUITAR_MUTED 28
	#define MM_MIDI_OVERDRIVEN_GUITAR 29
	#define MM_MIDI_DISTORTION_GUITAR 30
	#define MM_MIDI_GUITAR_HARMONICS 31
	#define MM_MIDI_ACOUSTIC_BASS 32
	#define MM_MIDI_ELECTRIC_BASS_FINGER 33
	#define MM_MIDI_ELECTRIC_BASS_PICK 34
	#define MM_MIDI_FRETLESS_BASS 35
	#define MM_MIDI_SLAP_BASS_1 36
	#define MM_MIDI_SLAP_BASS_2 37
	#define MM_MIDI_SYNTH_BASS_1 38
	#define MM_MIDI_SYNTH_BASS_2 39
	#define MM_MIDI_VIOLIN 40
	#define MM_MIDI_VIOLA 41
	#define MM_MIDI_CELLO 42
	#define MM_MIDI_CONTRABASS 43
	#define MM_MIDI_TREMOLO_STRINGS 44
	#define MM_MIDI_PIZZICATO_STRINGS 45
	#define MM_MIDI_ORCHESTRAL_HARP 46
	#define MM_MIDI_TIMPANI 47
	#define MM_MIDI_STRING_ENSEMBLE_1 48
	#define MM_MIDI_STRING_ENSEMBLE_2 49
	#define MM_MIDI_SYNTH_STRINGS_1 50
	#define MM_MIDI_SYNTH STRINGS_2 51
	#define MM_MIDI_CHOIR_AAHS 52
	#define MM_MIDI_VOICE_OOHS 53
	#define MM_MIDI_SYNTH_VOICE 54
	#define MM_MIDI_ORCHESTRA_HIT 55
	#define MM_MIDI_TRUMPET 56
	#define MM_MIDI_TROMBONE 57
	#define MM_MIDI_TUBA 58
	#define MM_MIDI_MUTED_TRUMPET 59
	#define MM_MIDI_FRENCH_HORN 60
	#define MM_MIDI_BRASS_SECTION 61
	#define MM_MIDI_SYNTH_BRASS_1 62
	#define MM_MIDI_SYNTH_BRASS_2 63
	#define MM_MIDI_SOPRANO_SAX 64
	#define MM_MIDI_ALTO_SAX  65
	#define MM_MIDI_TENOR SAX 66
	#define MM_MIDI_BARITONE_SAX 67
	#define MM_MIDI_OBOE 68
	#define MM_MIDI_ENGLISH_HORN 69
	#define MM_MIDI_BASSOON 70
	#define MM_MIDI_CLARINET 71
	#define MM_MIDI_PICCOLO 72
	#define MM_MIDI_FLUTE 73
	#define MM_MIDI_RECORDER 74
	#define MM_MIDI_PAN_FLUTE 75
	#define MM_MIDI_BOTTLE_BLOW 76
	#define MM_MIDI_SHAKUHACHI 77
	#define MM_MIDI_WHISTLE 78
	#define MM_MIDI_OCARINA 79
	#define MM_MIDI_LEAD_1_SQUARE 80
	#define MM_MIDI_LEAD_2_SAWTOOTH 81
	#define MM_MIDI_LEAD_3_CALIOPE_LEAD  82
	#define MM_MIDI_LEAD_4_CHIFF_LEAD 83
	#define MM_MIDI_LEAD_5_CHARANG 84
	#define MM_MIDI_LEAD_6_VOICE  85
	#define MM_MIDI_LEAD_7_FIFTHS 86
	#define MM_MIDI_LEAD_8_BRASS_LEAD 87
	#define MM_MIDI_PAD_1_NEW_AGE 88
	#define MM_MIDI_PAD_2_WARM 89
	#define MM_MIDI_PAD_3_POLYSYNTH 90
	#define MM_MIDI_PAD_4_CHOIR 91
	#define MM_MIDI_PAD_5_BOWED 92
	#define MM_MIDI_PAD_6_METALLIC 93
	#define MM_MIDI_PAD_7_HALO 94
	#define MM_MIDI_PAD_8_SWEEP 95
	#define MM_MIDI_FX_1_RAIN 96
	#define MM_MIDI_FX_2_SOUNDTRACK 97
	#define MM_MIDI_FX_3_CRYSTAL 98
	#define MM_MIDI_FX_4_ATMOSPHERE 99
	#define MM_MIDI_FX_5_BRIGHTNESS 100
	#define MM_MIDI_FX_6_GOBLINS 101
	#define MM_MIDI_FX_7_ECHOES 102
	#define MM_MIDI_FX_8_SCI_FI 103
	#define MM_MIDI_SITAR 104
	#define MM_MIDI_BANJO 105
	#define MM_MIDI_SHAMISEN 106
	#define MM_MIDI_KOTO 107
	#define MM_MIDI_KALIMBA 108
	#define MM_MIDI_BAGPIPE 109
	#define MM_MIDI_FIDDLE 110
	#define MM_MIDI_SHANAI 111
	#define MM_MIDI_TINKLE_BELL 112
	#define MM_MIDI_AGOGO 113
	#define MM_MIDI_STEEL_DRUMS 114
	#define MM_MIDI_WOODBLOCK 115
	#define MM_MIDI_TAIKO DRUM 116
	#define MM_MIDI_MELODIC TOM 117
	#define MM_MIDI_SYNTH_DRUM 118
	#define MM_MIDI_REVERSE_CYMBAL 119
	#define MM_MIDI_GUITAR_FRET_NOISE 120
	#define MM_MIDI_BREATH_NOISE 121
	#define MM_MIDI_SEASHORE  122
	#define MM_MIDI_BIRD_TWEET 123
	#define MM_MIDI_TELEPHONE_RING 124
	#define MM_MIDI_HELICOPTER 125
	#define MM_MIDI_APPLAUSE  126
	#define MM_MIDI_GUNSHOT 127
	#define MIDI_ON 127
	#define MIDI_OFF 0
	#define C_MIDI 0
	#define CS_MIDI 1
	#define D_MIDI 2
	#define DS_MIDI 3
	#define E_MIDI 4
	#define F_MIDI 5
	#define FS_MIDI 6
	#define G_MIDI 7
	#define GS_MIDI 8
	#define A_MIDI 9
	#define AS_MIDI 10
	#define B_MIDI 11
	#define NONE_MIDI 12

	#define WHOLE_NOTE 64
	#define HALF_NOTE 32
	#define QUARTER_NOTE 16
	#define EIGHTH_NOTE 8
	#define SIXTEENTH_NOTE 4
	#define FUSA_NOTE 2
	#define SEMIFUSA_NOTE 1
#endif

#define NEURALNET_SIZE 32
#define WIN_SIGNALVIEWER_MAX 1024
#define WIN_TIEMPO_MAX 32
#define WIN_VIEWER3D_ANGLESTEPS 360
#define WIN_VIEWER3D_ZOOMRES 1000
#define DOCK_NONE 0
#define DOCK_BORDER 1
#define DOCK_CENTER 2

namespace Win //________________________________________ namespace Win::Ini
{

//_____________________________________________________________________ IParent
class IParent
{
public:
	virtual HWND GetHWND()=0;
	virtual void UpdateValue()=0;
	virtual void DoDock(int initialWidth, int initialHeight, int newWidth, int newHeight)=0;
	virtual void GetInitialRect(RECT& initialRect) = 0;
};

struct Event
{
	HWND hWnd;
	UINT uMsg;
	WPARAM wParam;
	LPARAM lParam;
	LRESULT returnValue;
};

#ifdef WIN_GDI_PLUS_ON
//_____________________________________________________________________GdiPlusOn
class GdiPlusOn
{
public:
	GdiPlusOn(void);
	virtual ~GdiPlusOn(void);
	static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
private:
	Gdiplus::GdiplusStartupInput m_si;
	ULONG_PTR m_token;
};
#endif

//____________________________________________________________________ TextExtent
class TextExtent
{
public:
	TextExtent(HDC hdc);
	virtual ~TextExtent(void);
	double GetWidth(const wchar_t* text, int length);
	double GetWidth(const wchar_t* text);
	static LONG GetHeight(int font);
private:
	double widths[256];
	double height;
};

class DDBitmap;
class DIBitmap;
class DIBitmapP;
class Metafile;

//_____________________________________________________________________Gdi
class Gdi
{
public:
	class Font
	{
	public:
		Font(void);
		virtual ~Font(void);
		Font(const wstring& name, int size);
		Font(const wstring& name, const wstring& text, int width, int height);
		Font(const wstring& name, const wstring& text, RECT& rect);
		HFONT Create(LOGFONT& logFont);
		HFONT Create(const wstring& name, int size, bool bold, bool italic, bool underline, bool strikeout);
		HFONT Create(int charCount, const wstring& name, int width, int height);
		HFONT Create(const wstring& name, const wstring& text, int width, int height);
		HFONT Create(const wstring& name, int size, bool bold, bool italic, int angle);
		HFONT Create(HDC hdc, const wstring& name, double heightPoints, bool bold, bool italic, bool deviceIndependent);
		HFONT CreateFromDialog(HWND hDlg, const wstring& name, int points, bool bold, bool italic);
		//
		Font(const wchar_t* name, int size);
		Font(const wchar_t* name, const wchar_t* text, int width, int height);
		Font(const wchar_t* name, wchar_t* text, RECT& rect);
		HFONT Create(const wchar_t* name, int size, bool bold, bool italic, bool underline, bool strikeout);
		HFONT Create(int charCount, const wchar_t* name, int width, int height);
		HFONT Create(const wchar_t* name, const wchar_t* text, int width, int height);
		HFONT Create(const wchar_t* name, int size, bool bold, bool italic, int angle);
		HFONT Create(HDC hdc, const wchar_t* name, double heightPoints, bool bold, bool italic, bool deviceIndependent);
		HFONT CreateFromDialog(HWND hDlg, const wchar_t* name, int points, bool bold, bool italic);
		// 
		int GetSize();
		wchar_t* GetName();
		void Delete();
		HFONT GetHFONT();
		LOGFONT& GetLogFont();
		static int GetIdealFontSize(const wstring& text, double width, double height);
		static void InitializeLogfont(LOGFONT& logfont);
		//
		Font(const Win::Gdi::Font& init); // Copy constructor
		Win::Gdi::Font& operator =(const Win::Gdi::Font& init);
	private:
		void Copy(const Font& init);
		HFONT Create();
		void Constructor();
		LOGFONT logfont;
		HFONT hFont;
		Win::Gdi* m_pGdi;
		void Update(Win::Gdi* pGdi){m_pGdi = pGdi;}
		friend class Win::Gdi;
	};
	class Pen
	{
	public:
		Pen();
		virtual ~Pen(void);
		Pen(int nPenStyle, int nWidth, COLORREF color);
		HPEN Create(int nPenStyle, int nWidth, COLORREF color);
		void Delete();  // You don't need to call this explictly
		HPEN GetHPEN()
			{return m_hPen;};
	private:
		void Update(Win::Gdi* pGdi){m_pGdi = pGdi;}
		HPEN m_hPen;
		Win::Gdi* m_pGdi; 
		friend class Win::Gdi;
	};
	class Brush
	{
	public:
		Brush();
		virtual ~Brush(void);
		Brush(COLORREF color);
		HBRUSH CreateHatch(int nHatchStyle, COLORREF color);
		HBRUSH CreateSolid(COLORREF color);
		HBRUSH CreatePattern(HINSTANCE hInstance, const wchar_t * pszBitmap);
		HBRUSH GetHBRUSH()
			{return m_hBrush;};
		void Delete(); // You don't need to call this explictly
	private:
		void Update(Win::Gdi* pGdi){m_pGdi = pGdi;}
		HBRUSH m_hBrush;
		Win::Gdi* m_pGdi; 
		friend class Win::Gdi;
	};
	class Color3D
	{
	public:
		Color3D();
		virtual ~Color3D(void);
		Color3D(COLORREF color);
		COLORREF GetColor();

		Win::Gdi::Pen& GetHighLight();
		Win::Gdi::Pen& GetLight();
		Win::Gdi::Pen& GetShadow();
		Win::Gdi::Pen& GetDarkShadow();
		Win::Gdi::Brush& GetFilling();

		static bool IsCloseToBlack(const COLORREF color);
		static COLORREF AddLight(const COLORREF color, int delta);
		void SetColor(COLORREF color);
		void SetFromSystemColor();
		static COLORREF GetHighLightColor(COLORREF color);
		static COLORREF GetLightColor(COLORREF color);
		static COLORREF GetShadowColor(COLORREF color);
		static COLORREF GetDarkShadowColor(COLORREF color);
		static COLORREF GetConstrastColor(COLORREF color);
		static COLORREF AddColors(COLORREF color1, COLORREF color2);
	private:
		COLORREF m_color;
		Brush m_brushFilling;
		Pen m_penHighLight;
		Pen m_penLight;
		Pen m_penShadow;
		Pen m_penDarkShadow;
	};
	class PointF
	{
	public:
		PointF(void)
		{
			x=0;
			y=0;
		}
		virtual ~PointF(void)
		{
		};
		double x;
		double y;
		void SetFromPoint(POINT& pt)
		{
			x = (double)(pt.x+0.5);
			y = (double)(pt.y+0.5);
		}
	};
/* class GDI
{   */
	void Delete();
	void DrawDoubleBuffer(Win::DDBitmap& ddbitmap);
	void DrawCompatibleBitmap(Win::DDBitmap& ddbitmap, int x, int y);
	void DrawCompatibleBitmap(Win::DDBitmap& ddbitmap, int x, int y, int targetWidth, int targetHeight);
	void DrawBitmap(Win::DDBitmap& ddbitmap, int x, int y);
	void DrawBitmap(Win::DDBitmap& ddbitmap, int x, int y, int width, int height, bool isColor);
	void DrawBitmap(Win::DIBitmap& dibitmap, int x, int y);
	void DrawBitmap(Win::DIBitmap& dibitmap, int x, int y, int width, int height, bool isColor);
	void DrawBitmap(Win::DIBitmapP&, int x, int y);
	void DrawMetafile(Win::Metafile& metafile, const RECT& rect);
	void DrawMetafile(Win::Metafile& metafile, int x, int y);
	void DrawMetafile(Win::Metafile& metafile, int x, int y, int width, int height, bool center);
	void DrawGraphics(Sys::Graphics& graphics, int x, int y);
	void DrawGraphics(Sys::Graphics& graphics, int x, int y, int width, int height);
	//
	int DrawGraphScaleX(int posX, int posY, int width, double minX, double maxX, int numTicks, int tickSize, const wchar_t* caption); 
	int DrawGraphScaleY(int posX, int posY, int height, double minY, double maxY, int numTicks, int tickSize, const wchar_t* caption); 
	int DrawGraphScaleYLeft(int posX, int posY, int height, double minY, double maxY, int numTicks, int tickSize, const wchar_t* caption); 
	int DrawGraphGradientScale(int posX, int posY, int height, double minimum, double maximum, int numTicks, int tickSize, int numColors, bool invertColors); // numColors = 0 for Black and White
	//
	void DrawArrow(RECT& rect, Win::Gdi::Brush& brush, int direction); // WIN_DRAWARROW_NORTH, ...
	void FillPolyBezier(const POINT* arrayPoints, DWORD count, Win::Gdi::Brush& brush);

	// To remove a device-context's clipping region, specify a NULL region handle
	int SelectClipRgn(HRGN hRgn)
		{return ::SelectClipRgn(m_hdc, hRgn);}
	BOOL GetTextExtentPoint32(const wchar_t * psz, SIZE& size)
		{return ::GetTextExtentPoint32(m_hdc, psz, lstrlen(psz), &size);}
	int GetTextWidth(const wchar_t* text)
	{
		SIZE size;
		::GetTextExtentPoint32W(m_hdc, text, lstrlen(text), &size);
		return size.cx;
	}
	BOOL GetTextMetrics(LPTEXTMETRIC pTM)
		{return ::GetTextMetrics(m_hdc, pTM);}
	UINT SetTextAlign(UINT nType)
		{return ::SetTextAlign(m_hdc, nType);}// TA_CENTER, TA_LEFT, TA_RIGHT, TA_BASELINE, TA_BOTTOM, TA_TOP
	BOOL DrawIcon(int x, int y, HICON hIcon)
		{return ::DrawIcon(m_hdc, x, y, hIcon);}
	BOOL DrawIcon(int x, int y, Sys::Icon& icon);
	BOOL DrawIcon(int x, int y, Sys::Icon& icon, Win::Gdi::Brush& brushBackground);
	COLORREF SetTextColor(COLORREF color)
		{return ::SetTextColor(m_hdc, color);}
	HGDIOBJ SelectObject(HGDIOBJ hgdiobj)
		{return ::SelectObject(m_hdc, hgdiobj);}
	BOOL TextOut(int x, int y, const wchar_t * psz)
		{const int len = wcslen(psz); if (len== 0) return true; return ::TextOut(m_hdc, x, y, (wchar_t*)psz, len);}
	void TextOut(int x, int y, const wstring& text)
	{const int len = text.length(); if (len == 0) return; ::TextOut(m_hdc, x, y, text.c_str(), len);}
	void TextOut(int x, int y, const wchar_t* text, const RECT& rect, unsigned int options); // ETO_CLIPPED, ETO_OPAQUE, 
	int SetMapMode(int nMode)
		{return ::SetMapMode(m_hdc, nMode);}// MM_TEXT, MM_LOMETRIC, MM_HIMETRIC, MM_LOENGLISH, MM_HIENGLISH, MM_TWIPS, MM_ISOTROPIC, MM_ANISOTROPIC
	int GetMapMode(void)
		{return ::GetMapMode(m_hdc);}
	BOOL DPtoLP(POINT* pPoints, int nCount)
		{return ::DPtoLP(m_hdc, pPoints, nCount);}
	BOOL LPtoDP(POINT* pPoints, int nCount)
		{return ::LPtoDP(m_hdc, pPoints, nCount);}
	BOOL DPtoLP(RECT& rect)
		{return ::DPtoLP(m_hdc, (PPOINT)&rect, 2);}
	BOOL LPtoDP(RECT& rect)
		{return ::LPtoDP(m_hdc, (PPOINT)&rect, 2);}
	BOOL SetViewportExtEx(int width, int height)
		{return ::SetViewportExtEx(m_hdc, width, height, NULL);}
	BOOL SetWindowExtEx(int width, int height)
		{return ::SetWindowExtEx(m_hdc, width, height, NULL);}
	BOOL SetViewportOrgEx(int pixelsX, int pixelsY)
		{return ::SetViewportOrgEx(m_hdc, pixelsX, pixelsY, NULL);}
	BOOL GetViewportExtEx(LPSIZE size) 
		{return ::GetViewportExtEx(m_hdc, size);}
	BOOL GetWindowExtEx(LPSIZE size) 
		{return ::GetWindowExtEx(m_hdc, size);}
	BOOL SetWindowOrgEx(int luX, int luY)
		{return ::SetWindowOrgEx(m_hdc, luX, luY, NULL);}
	BOOL GetViewportOrgEx(POINT& pt) 
		{return ::GetViewportOrgEx(m_hdc, &pt);} //  pixels
	BOOL GetWindowOrgEx(POINT& pt)
		{return ::GetWindowOrgEx(m_hdc, &pt);} //Logical units
	int FillRect(const RECT& rect, HBRUSH hBrush)
		{return ::FillRect(m_hdc, &rect, hBrush);}
	int FillRect(const RECT& rect, Brush& brush)
		{return ::FillRect(m_hdc, &rect, brush.GetHBRUSH());}
	int FrameRect(const RECT* rect, HBRUSH hBrush)
		{return ::FrameRect(m_hdc, rect, hBrush);}
	int FrameRect(const RECT* rect, Brush& brush)
		{return ::FrameRect(m_hdc, rect, brush.GetHBRUSH());}
	BOOL InvertRect(const RECT* rect)
		{return ::InvertRect(m_hdc, rect);}
	BOOL FillRgn(HRGN hRgn, HBRUSH hBrush)
		{return ::FillRgn(m_hdc, hRgn, hBrush);}
	BOOL FillRgn(HRGN hRgn, Brush& brush)
		{return ::FillRgn(m_hdc, hRgn, brush.GetHBRUSH());}
	BOOL FrameRgn(HRGN hRgn, HBRUSH hBrush, int xFrame, int yFrame)
		{return ::FrameRgn(m_hdc, hRgn, hBrush, xFrame, yFrame);}
	BOOL FrameRgn(HRGN hRgn, Brush& brush, int xFrame, int yFrame)
		{return ::FrameRgn(m_hdc, hRgn, brush.GetHBRUSH(), xFrame, yFrame);}
	BOOL InvertRgn(HRGN hRgn)
		{return ::InvertRgn(m_hdc, hRgn);}
	BOOL PaintRgn(HRGN hRgn)
		{return ::PaintRgn(m_hdc, hRgn);}
	int SetPolyFillMode(bool bWinding) 
		{return ::SetPolyFillMode(m_hdc, bWinding ? WINDING : ALTERNATE);}
	int GetHorizontalSize()
		{return ::GetDeviceCaps(m_hdc, HORZSIZE);} // milimeter
	int GetVerticalSize()
		{return ::GetDeviceCaps(m_hdc, VERTSIZE);}// milimeters
	int GetHorizontalDPI()
		{return ::GetDeviceCaps(m_hdc, LOGPIXELSX);}
	int GetVerticalDPI()
		{return ::GetDeviceCaps(m_hdc, LOGPIXELSY);}
	BOOL BeginPath()
		{return ::BeginPath(m_hdc);}
	BOOL EndPath()
		{return ::EndPath(m_hdc);}
	BOOL FlattenPath()
		{return ::FlattenPath(m_hdc);}
	BOOL FillPath()
		{return ::FillPath(m_hdc);}
	BOOL StrokePath()
		{return ::StrokePath(m_hdc);}
	BOOL StrokeAndFillPath()
		{return ::StrokeAndFillPath(m_hdc);}
	int SaveDC()
		{return ::SaveDC(m_hdc);}
	BOOL Rectangle(int xLeft, int yTop, int xRight, int yBottom)
		{return ::Rectangle(m_hdc, xLeft, yTop, xRight, yBottom);}
	BOOL Rectangle(const RECT& rect)
		{return ::Rectangle(m_hdc, rect.left, rect.top, rect.right, rect.bottom);}
	int SetBkMode(bool bTransparent)
		{return ::SetBkMode(m_hdc, bTransparent ? TRANSPARENT : OPAQUE);}
	COLORREF SetBkColor(COLORREF color)
		{return ::SetBkColor(m_hdc, color);}
	int SetROP2(int nMode)
		{return ::SetROP2(m_hdc, nMode);}// R2_COPYPEN is the default, R2_NOTCOPYPEN to invert, R2_WHITE, R2_BLACK, R2_XORPEN for temporary displaying
	int GetROP2()
		{return ::GetROP2(m_hdc);}
	int SetTextCharacterExtra_(int nExtra)
		{return ::SetTextCharacterExtra(m_hdc, nExtra);}
	BOOL Polyline(const POINT* arrayPoints, int nCount)
		{return ::Polyline(m_hdc, arrayPoints, nCount);}
	BOOL PolylineTo(const POINT* arrayPoints, DWORD nCount)
		{return ::PolylineTo(m_hdc, arrayPoints, nCount);}
	BOOL PolyBezier(const POINT* arrayPoints, DWORD nCount)
		{return ::PolyBezier(m_hdc, arrayPoints, nCount);}// Start, Control1, Control2, End
	BOOL PolyBezierTo_(const POINT* arrayPoints, DWORD nCount)
		{return PolyBezierTo(m_hdc, arrayPoints, nCount);}	// Start, Control1, Control2, End
	void RestoreDC(int n)
		{::RestoreDC(m_hdc, n);}// -1 to restore to last saved one
	COLORREF SetPixel(int x, int y, COLORREF color)
		{return ::SetPixel(m_hdc, x, y, color);}
	COLORREF GetPixel_(int x, int y)
		{return ::GetPixel(m_hdc, x, y);}
	HDC GetHDC(){return m_hdc;}
	BOOL MoveToEx(int nPosX, int nPosY)
		{return ::MoveToEx(m_hdc, nPosX, nPosY, NULL);}
	BOOL LineTo(int nPosX, int nPosY)
		{return ::LineTo(m_hdc, nPosX, nPosY);}
	BOOL Ellipse(int xLeft, int yTop, int xRight, int yBottom)
		{return ::Ellipse(m_hdc, xLeft, yTop, xRight, yBottom);}
	BOOL Circle(int x, int y, int radius)
		{return ::Ellipse(m_hdc, x-radius, y-radius, x+radius+1, y+radius+1);}
	BOOL GetTextFace(int nCount, wchar_t* pszFontName)
		{return ::GetTextFace(m_hdc, nCount, pszFontName);}
	double GetPixelsPerMilimeterX()
		{return GetDeviceCaps(m_hdc, HORZRES)/GetDeviceCaps(m_hdc, HORZSIZE);}
	double GetPixelsPerMilimeterY()
		{return GetDeviceCaps(m_hdc, VERTRES)/GetDeviceCaps(m_hdc, VERTSIZE);}
	static double GetMaxScale(const Win::Gdi::PointF * pfInterior, const Win::Gdi::PointF * sizeExterior);
	TEXTMETRIC tm;
	void SetWorldRotation(double angle, double eDx, double eDy) //It doesn't work on Windows 98 or me, eDx is width/2 and eDy is height/2
	{
		XFORM tf;
		tf.eM11 = (FLOAT) cos(angle*M_PI/180);
		tf.eM12 = (FLOAT) sin(angle*M_PI/180);
		tf.eM21 = (FLOAT) -sin(angle*M_PI/180);
		tf.eM22 = (FLOAT) cos(angle*M_PI/180);
		tf.eDx = (FLOAT) eDx;
		tf.eDy = (FLOAT) eDy;
		::SetGraphicsMode(this->m_hdc, GM_ADVANCED);
		::SetWorldTransform(this->m_hdc, &tf);
	}

	void SetAdvancedMode(bool advanced)
	{
		if (advanced == true)
		{
			::SetGraphicsMode(this->m_hdc, GM_ADVANCED);
		}
		else
		{
			::SetGraphicsMode(this->m_hdc, GM_COMPATIBLE);
		}	
	}

	BOOL Line(int x1, int y1, int x2, int y2)
	{
		if (::MoveToEx(this->m_hdc, x1, y1, NULL))
		{
			return ::LineTo(this->m_hdc, x2, y2);
		}
		return FALSE;
	}

	BOOL RoundRect(int xLeft, int yTop, int xRight, int yBottom, int xCornerEllipse, int yCornerEllipse)
	{
		return ::RoundRect(m_hdc, xLeft, yTop, xRight, yBottom, xCornerEllipse, yCornerEllipse);
	}

	BOOL RoundRect(RECT& rect, int xCornerEllipse, int yCornerEllipse)
	{
		return ::RoundRect(m_hdc, rect.left, rect.top, rect.right, rect.bottom, xCornerEllipse, yCornerEllipse);
	}

	BOOL Arc(int xLeft, int yTop, int xRight, int yBottom, int xStart, int yStart, int xEnd, int yEnd)
	{
		return ::Arc(m_hdc, xLeft, yTop, xRight, yBottom, xStart, yStart, xEnd, yEnd);
	}

	BOOL Chord(int xLeft, int yTop, int xRight, int yBottom, int xStart, int yStart, int xEnd, int yEnd)
	{
		return ::Chord(m_hdc, xLeft, yTop, xRight, yBottom, xStart, yStart, xEnd, yEnd);
	}

	BOOL Pie(int xLeft, int yTop, int xRight, int yBottom, int xStart, int yStart, int xEnd, int yEnd)
	{
		return ::Pie(m_hdc, xLeft, yTop, xRight, yBottom, xStart, yStart, xEnd, yEnd);
	}

	BOOL PolyPolyline(const POINT* arrayPoints, const DWORD* pointsPerPolygon, DWORD nCount)
	{
		//pointsPerPolygon is an array with the number of points in each polygon
		return ::PolyPolyline(m_hdc, arrayPoints, pointsPerPolygon, nCount);
	}

	BOOL Polygon(const POINT* arrayPoints, int nCount)
	{
		return ::Polygon(m_hdc, arrayPoints, nCount);
	}

	BOOL PolyPolygon(const POINT* arrayPoints, const int * pointsPerPolygon, int nCount)
	{
		//pointsPerPolygon is an array with the number of points in each polygon
		return ::PolyPolygon(m_hdc, arrayPoints, pointsPerPolygon, nCount);
	}

	BOOL TabbedTextOut(int x, int y, const wchar_t * pszString, int nCount, int nTabPositions, int* pcInt, int nTabOrigin)
	{
		return ::TabbedTextOut(m_hdc, x, y, pszString, nCount, nTabPositions, pcInt, nTabOrigin);
	}

	BOOL ExtTextOut(int x, int y, UINT uOptions, RECT& rect, const wchar_t * pszText, int nCount, const int* pxDistance)
	{
		//uOptions:  ETO_CLIPPLED or ETO_OPAQUE
		return ::ExtTextOut(m_hdc, x, y, uOptions, &rect, pszText, nCount, pxDistance);
	}

	int DrawParagraph(const wchar_t* text, int text_width, int x, int y, int alignment, int rowIndex);//alignment: WIN_ALIGNMENT_LEFT, WIN_ALIGNMENT_RIGHT, WIN_ALIGNMENT_CENTER, WIN_ALIGNMENT_JUSTIFIED

	BOOL DrawText(wchar_t* psz, RECT &rect, UINT uTextAlign)
	{
		// uTextAlign
		// DT_CENTER | DT_VCENTER | DT_SINGLELINE, you can use SetTextAlign() also
		// uTextAling = 0 ->  '\r' and '\n' are new lines
		// DT_TOP or DT_BOTTOM
		// DT_WORDBREAK, DT_NOCLIP, DT_EXTERNALLEADING, DT_EXPANDTABS
		return ::DrawText(m_hdc, psz, lstrlen(psz), &rect, uTextAlign);
	}

	BOOL DrawEdge(LPRECT pRect, UINT edge, UINT grfFlags)
	{
		//edge: BDR_RAISEDOUTER BDR_SUNKENOUTER BDR_RAISEDINNER BDR_SUNKENINNER
		//BDR_OUTER BDR_INNER BDR_RAISED BDR_SUNKEN, 
		//grfFlags: BF_RECT BF_FLAT BF_LEFT BF_MONO BF_RIGHT BF_SOFT
		//BF_TOP BF_TOPLEFT BF_TOPRIGHT BF_BOTTOMRIGHT BF_ADJUST
		return ::DrawEdge(m_hdc, pRect, edge, grfFlags);
	}

	BOOL DrawFocusRect(LPRECT pRect)
	{
		return ::DrawFocusRect(m_hdc, pRect);
	}

	BOOL DrawTextEx(LPTSTR pszText, RECT& rect, 
		UINT uFormat, LPDRAWTEXTPARAMS pDrawTextParams)
	{
		//The text alignment mode for the device context must include the TA_LEFT, TA_TOP, and TA_NOUPDATECP flags
		//DT_BOTTOM, DT_CALCRECT,DT_CENTER,DT_EDITCONTROL, DT_END_ELLIPSIS, DT_EXPANDTABS, DT_EXTERNALLEADING 
		//DT_HIDEPREFIX, DT_INTERNAL, DT_LEFT, DT_MODIFYSTRING, DT_NOCLIP, DT_NOFULLWIDTHCHARBREAK,
		//DT_NOPREFIX, DT_PATH_ELLIPSIS, DT_PREFIXONLY, DT_RIGHT, DT_SINGLELINE, DT_TABSTOP 
		//DT_TOP, DT_VCENTER, DT_WORDBREAK, DT_WORD_ELLIPSIS
		::SetTextAlign(m_hdc, TA_LEFT | TA_TOP | TA_NOUPDATECP);
		return ::DrawTextEx(m_hdc, pszText, -1, &rect, uFormat, pDrawTextParams);
	}

	void GetPhysicalSize(SIZE& size)
	{
		size.cx = ::GetDeviceCaps(m_hdc, PHYSICALWIDTH);
		size.cy = ::GetDeviceCaps(m_hdc, PHYSICALHEIGHT);
	}
	
	// Returns the offset from the pritable area and the page
	void GetPhysicalOffset(POINT& point)
	{
		point.x = ::GetDeviceCaps(m_hdc, PHYSICALOFFSETX);
		point.y = ::GetDeviceCaps(m_hdc, PHYSICALOFFSETY);
	}

	static bool DoRectOverlap(RECT& rectA, RECT rectB)
	{
		RECT rect;
		::IntersectRect(&rect, &rectA, &rectB);
		return (::IsRectEmpty(&rect)==FALSE);
	}

	bool DoRcPaintOverlap(RECT& rect)
	{
		RECT rectIntersect; //Returns true if rect overlaps with rcPaint
		::IntersectRect(&rectIntersect, &rect, &m_ps.rcPaint);
		return (::IsRectEmpty(&rect)==FALSE);
	}

	//// Returns true if the rectangles overlap
	//static bool DoTheyOverlap2(RECT& rcA, RECT& rcB)
	//{
	//	bool bOverlap=true;

	//	if (rcA.left<=rcB.left)
	//	{
	//		if (rcA.right<rcB.left) bOverlap=false;
	//	}
	//	else
	//	{
	//		if (rcB.right<rcA.left) bOverlap=false;
	//	}
	//	if (bOverlap)
	//	{
	//		if (rcA.top<=rcB.top)
	//		{
	//			if (rcA.bottom<rcB.top) bOverlap=false;
	//		}
	//		else
	//		{
	//			if (rcB.bottom<rcA.top) bOverlap=false;
	//		}
	//	}
	//	return bOverlap;
	//}

	static bool Inflate(RECT& rectResult, RECT& rectOriginal, int nAmount)
	{
		rectResult.bottom = rectOriginal.bottom - nAmount;
		rectResult.left = rectOriginal.left + nAmount;
		rectResult.right = rectOriginal.right - nAmount;
		rectResult.top = rectOriginal.top + nAmount;
		return true;
	}

	BOOL PieCircle(int xCenter, int yCenter, int nRadius, double angleStart, double angleDelta);
	//
	void TextOutCenter(RECT& rect, const wchar_t * text, bool centerX, bool centerY);
	BOOL TextOutVCenterRight(RECT& rect, const wchar_t * text);
	BOOL TextOutVCenterLeft(RECT& rect, const wchar_t * text);
	BOOL TextOutCenter(int x, int y, const wchar_t * text, bool centerX, bool centerY);
	bool TextOutTruncate(int x, int y, const wchar_t* text, int width, bool ellipses, bool centerX);
	//
	void TextOutCenter(RECT& rect, const wstring& text, bool centerX, bool centerY);
	BOOL TextOutVCenterRight(RECT& rect, const wstring& text);
	BOOL TextOutVCenterLeft(RECT& rect, const wstring& text);
	BOOL TextOutCenter(int x, int y, const wstring& text, bool centerX, bool centerY);
	BOOL TextOutTruncate(int x, int y, const wstring& text, int width, bool ellipses, bool centerX);
	//
	void SetScaleMode(int logUnitsWidth, int logUnitsHeight, int pxWidth, int pxHeight, bool bCartesian);
	void SetMili100Mode();
	void Cilinder(int x, int y, double radius, double height, bool topEllipse, bool bottomEllipse); 
	void SolidCilinder(int x, int y, double radius, double height, COLORREF color); 
	bool OnPaintLoopX_(RECT& rcTotalLoopArea, int* array, int arrayLength, int& index1, int& index2, int& nTop, int& nBottom);
	bool OnPaintLoopY_(RECT& rcTotalLoopArea, int* array, int arrayLength,  int& index1, int& index2, int& nLeft, int& nRight);
	bool OnPaintLoopX(int deltaX, RECT& rcTotalLoopArea, RECT& rcRequiredLoopArea);
	bool OnPaintLoopY(int deltaY, RECT& rcTotalLoopArea, RECT& rcRequiredLoopArea);
	bool OnPaintLoopX(double inDeltaX, RECT& inRectBox, int& outTop, int& outBottom, int& outIndex1, int& outIndex2);
	bool OnPaintLoopY(double inDeltaY, RECT& inRectBox, int& outLeft, int& outRight, int& outIndex1, int& outIndex2);
	Gdi(PAINTSTRUCT& ps, bool createGdiplusObject);
	Gdi(Win::DDBitmap& ddbitmap, RECT& rcPaint, bool createGdiplusObject);
	Gdi(Sys::Graphics& graphics, bool createGdiplusObject);
	Gdi(Win::Metafile& metafile, bool createGdiplusObject);
	Gdi(HWND hWnd, bool bOnPaint, bool createGdiplusObject);
	virtual ~Gdi(void);
	operator HDC() 
		{return m_hdc;}
	operator HDC &() 
		{return m_hdc;}
	operator RECT()
		{return m_ps.rcPaint;}
	PAINTSTRUCT GetPaintStruct()
		{return m_ps;}
	RECT& GetRcPaint()
		{return m_ps.rcPaint;}
	HFONT SelectFont_(Win::Gdi::Font& font)
		{return this->UpdateFont(&font, font.GetHFONT());}
	HFONT SelectFont__(HFONT hFont)
		{return this->UpdateFont(NULL, hFont);}
	HPEN SelectPen_(Win::Gdi::Pen& pen)
		{return this->UpdatePen(&pen, pen.GetHPEN());}
	HPEN SelectPen__(HPEN hPen)
		{return this->UpdatePen(NULL, hPen);}
	HBRUSH SelectBrush_(Win::Gdi::Brush& brush)
		{return this->UpdateBrush(&brush, brush.GetHBRUSH());}
	HBRUSH SelectBrush__(HBRUSH hBrush)
		{return this->UpdateBrush(NULL, hBrush);}
#ifdef WIN_GDI_PLUS_ON 
	Gdiplus::Graphics& GetGdiPlus();
	__declspec( property( get=GetGdiPlus ) ) Gdiplus::Graphics& Plus;
#endif
private:
#ifdef WIN_GDI_PLUS_ON 
	Gdiplus::Graphics* pGdiPlus;
#endif
	Win::Gdi::Brush * m_pBrush;
	Win::Gdi::Pen* m_pPen;
	Win::Gdi::Font* m_pFont;
	HFONT UpdateFont(Font* pFont, HFONT hFont);
	HPEN UpdatePen(Pen* pPen, HPEN hPen);
	HBRUSH UpdateBrush(Brush* pBrush, HBRUSH hBrush);
	void UpdateFontExt(Font* pFont);
	void UpdatePenExt(Pen* pPen);
	void UpdateBrushExt(Brush* pBrush);
	void Constructor();
	HBRUSH m_hBrushOriginal; 
	HPEN m_hPenOriginal; 
	HFONT m_hFontOriginal; 
	enum Type{FromPainstruct, CaptureReleaseDc, BeginEndPaint};
	HDC m_hdc;
	PAINTSTRUCT m_ps;
	HWND m_hWnd;
	Win::Gdi::Type m_type;
	friend class Win::Gdi::Font;
	friend class Win::Gdi::Pen;
	friend class Win::Gdi::Brush;
};

//_____________________________________________________________________IExportable and Exporter
class IExportable // A control that implements IExportable is capable of storing as EMF
{
public:
	virtual HWND GetControlInfo(int& width, int& height)=0;
	virtual void SetControlSize(int width, int height) = 0;
	virtual void OnPaintControl(Win::Gdi& gdi) = 0;
};

class Exporter
{
public:
	~Exporter(void);
	static bool SaveToFile(const wchar_t* filename, Win::IExportable& ixp);
	static bool SaveToFile(const wchar_t* filename, double aspectRatio, Win::IExportable& ixp);
	static bool CopyToClipboard(Win::IExportable& ixp);
	static bool CopyToBitmap(Win::IExportable& ixp, int width, int height, bool clientEdge, Win::DDBitmap& result);
private:
	Exporter(void);
};

//_____________________________________________________________________ PrintInfo
struct PrintInfo
{
	int width;
	int height;
	int pageWidth;
	int pageHeight;
	int page;
	int index;
	POINT position;
	bool isFirst;
	bool isLast;
	bool isFirstOnPage;
	bool isLastOnPage;
};

//_____________________________________________________________________ IPrint
class IPrint
{
public:
	virtual void Print(Win::Gdi& gdi, Win::PrintInfo pi) = 0;
	//virtual bool CopyToClipboard(HWND hWnd) = 0; // Implement this to export to MS Word and MS Excel
};

//_____________________________________________________________________ IPrintDoc
class IPrintDoc
{
public:
	virtual void SetMargin(RECT& rect) = 0;
	virtual RECT GetMargin(void) = 0;
	virtual void SetOrientation(bool isPortrait) = 0;
	virtual bool IsPortraitOrientation(void) = 0;
	virtual void SetPaperSize(const POINT paperSize) = 0;
	virtual POINT GetPaperSize(void) = 0;
	virtual void ResetCurrentPosition(void) = 0;
	virtual void SetDocumentName(const wchar_t* name) = 0;
	virtual const wchar_t* GetDocumentName() = 0;
	virtual BOOL OnPrintPage(Win::Gdi& gdi, int page, int width, int height) = 0;
	virtual int GetPageCount() = 0;
};

class Module;

//_____________________________________________________________________________Timer
class Timer
{
public:
	Timer();
	~Timer();
	/* The event WM_TIMER will call Window_Timer */
	void Set(UINT_PTR timer_id, UINT duration);
	void Kill(UINT_PTR timer_id);
private:
	void SetParent(Win::IParent* iparent);
	Win::IParent* iparent;
	friend class Win::Module;
};


//_____________________________________________________________________Module
class Module : public Win::IParent // Not to be used to build an object
{
public:
	virtual ~Module(void);
	virtual HWND Create(DWORD dwExStyle, const wchar_t* pszWindowName, DWORD dwStyle, int x, int y, int width, int height, HWND hParent, int id);
	virtual bool IsEvent(Win::Event& e, int notification);
	HWND SetFocus();
	int GetID();
	virtual void UpdateValue();
	operator HWND();
	int MessageBox(const wchar_t * text, const wchar_t * caption, UINT type);
	int MessageBox(const wstring& text, const wstring& caption, UINT type);
	static HINSTANCE GetInstance();
	DWORD SetCursorPos(int x, int y);
	HWND GetDialogItem(HWND parent, int id);
	virtual void SetVisible(bool visible);
	virtual bool IsVisible();
	__declspec( property( get=IsVisible, put=SetVisible) ) bool Visible;
	void SetEnable(bool enabled);
	bool GetEnable();
	__declspec( property( get=GetEnable, put=SetEnable) ) bool Enabled;
	//
	void SetPositionX(int x);
	int GetPositionX();
	void SetPositionY(int y);
	int GetPositionY();
	void GetRect(RECT& rc);
	void SetRect(RECT& rc);
	__declspec( property( get=GetPositionX, put=SetPositionX ) ) int PositionX;
	__declspec( property( get=GetPositionY, put=SetPositionY ) ) int PositionY;
	//
	void SetWidth(int width);
	int GetWidth();
	void SetHeight(int height);
	int GetHeight();
	__declspec( property( get=GetWidth, put=SetWidth ) ) int Width;
	__declspec( property( get=GetHeight, put=SetHeight ) ) int Height;
	//
	void SetWindowPosition(int x, int y, int width, int height, HWND insertAfter, unsigned int flags); //insertAfter: HWND_BOTTOM, HWND_NOTOPMOST, HWND_TOP, HWND_TOPMOST
	//
	LRESULT SendMessage(UINT message, WPARAM wParam, LPARAM lParam);
	WNDPROC SetProc(WNDPROC wndProc);
	LRESULT SetRedraw(bool redraw);
	BOOL Move(int x, int y, int nWidth, int nHeight, bool repaint);
	BOOL Move(RECT& rect, bool repaint);
	BOOL MoveToFill(Win::Event& e);
	int Scroll(int deltaX, int deltaY);
	int Scroll(int deltaX, int deltaY, LPRECT prcUpdate);
	int SetScrollInfoV(SCROLLINFO& si);
	int SetScrollInfoV(int minimum, int maximum, int position);
	int SetScrollInfoV(int minimum, int maximum, int position, int page);
	int SetScrollInfoH(SCROLLINFO& si);
	int SetScrollInfoH(int minimum, int maximum, int position);
	//
	int GetScrollPositionH(SCROLLINFO& si, Win::Event& e); // Returns the scroll_delta
	int GetScrollPositionV(SCROLLINFO& si, Win::Event& e); // Returns the scroll_delta
	BOOL Redraw(const RECT * lprcUpdate, HRGN hrgnUpdate, UINT flags);
	void LockUpdate(bool locked);

	//SW_HIDE SW_SHOWNORMAL SW_NORMAL SW_SHOWMINIMIZED SW_SHOWMAXIMIZED
	//SW_MAXIMIZE SW_SHOWNOACTIVATE SW_SHOW SW_MINIMIZE SW_SHOWMINNOACTIVE
	//SW_SHOWNA SW_RESTORE SW_SHOWDEFAULT SW_FORCEMINIMIZE SW_MAX
	void Show(int cmdShow);
	void Minimize();
	void Maximize();
	void Destroy();
	void Update();
	void Close();
	void RefreshMenu();	
	BOOL SetMenu(HMENU hMenu);
	HMENU GetMenu();
	void ScreenToClient(POINT& pt);
	void ClientToScreen(POINT& pt);
	//void GetRect(RECT& rc);
	void GetRelativeRect(HWND parent, RECT& rc);
	void GetClientRect(RECT& rc);

	virtual int GetTextLength();
	void Repaint(RECT* rc, bool erase);
	//int GetID();
	BOOL SetForeground();
	HWND GetParent();
	LONG_PTR GetLongPtr(int flags);

	void AlwaysOnTop(bool onTop);
	void SetClassCursor(HCURSOR hcursor);
	void SetClassIcon(HICON hicon);
	void SetClassBackground(HBRUSH hbrush);
	HICON GetClassIcon(bool smallIcon);

	HDC GetWindowDC();
	HDC GetDC();
	void ReleaseDC(HDC hdc);
	void EnableCloseButton(bool enabled);
	void EnableMoveButton(bool enabled);
	void EnableSizeButton(bool enabled);
	//
	Win::Timer timer;
	virtual void SetFont(Win::Gdi::Font& font);
	//Win::Gdi::Font& GetFont();
	__declspec( property( put=SetFont) ) Win::Gdi::Font& Font;
	virtual void SetWindowText(const wchar_t* text);
	virtual int GetWindowText(wchar_t* text, int size);
	virtual wstring GetText();
	virtual void SetText(const wstring text);
	__declspec( property( get=GetText, put=SetText) ) wstring Text;
	//
	void SetDock(int left, int top, int right, int bottom);
	void GetDock(int& left, int& top, int& right, int& bottom);
	//____________________________________________ IParent
	HWND GetHWND();
	void DoDock(int initialWidth, int initialHeight, int newWidth, int newHeight);
	void GetInitialRect(RECT& initialRect);
	//
#ifdef WIN_DAC_ADC_SUPPORT
	bool PlayWaveSound(const wchar_t* filename);
	bool PlayWaveSound(HINSTANCE hInstance, const wchar_t* resource_id);
#endif
protected:
	//_________________________ Gdi Plus Activation
#ifdef WIN_GDI_PLUS_ON
	static Gdiplus::GdiplusStartupInput _gdiPlusStartupInput;
	static ULONG_PTR _gdiPlusToken;
	static bool _isGdiPlusOn;
#endif
	Module();
	int width;
	int height;
	RECT _dock;
	RECT _initialRect;
	LONG_PTR id;
	HWND hWnd;
	//HFONT _hfont;
	virtual const wchar_t * GetClassName(void) = 0;
	static HINSTANCE hInstance;
	virtual void InitialUpdate(HWND hWndParent);
private:	
};

//_____________________________________________________________________Window
class Window : public Module
{
public:
	int GetClientWidth();
	int GetClientHeight();
	virtual ~Window(void);
	bool RegisterClassEx(UINT nClassStyle, bool bModelessDialog, HINSTANCE hInst, USHORT nIconId, USHORT nSmallIconId, USHORT nMenu, HCURSOR hCursor, HBRUSH hBackground);
	bool RegisterClassEx(HCURSOR hCursor, HBRUSH hbrBackground);
	static bool UserControlRegisterClass();
	bool RegisterGlobalClassEx(HCURSOR hCursor, HBRUSH hbrBackground);
	virtual HWND Create(DWORD dwExStyle, const wchar_t * text, DWORD dwStyle, int x, int y, int width, int height, HWND hParent, int id);
	HWND CreateMainWindow(const wchar_t * text, int cmdShow, USHORT iconID, USHORT menuID, HBRUSH bkgnd, HINSTANCE hInstance);
	HWND CreateMainWindow(DWORD dwExStyle, DWORD dwStyle, int x, int y, int width, int height, const wchar_t * text, int cmdShow, USHORT iconID, USHORT menuID, HBRUSH bkgnd, HINSTANCE hInstance);
	HWND GetDialogItem(HWND hDlg, int id);
	virtual int MessageLoop(WORD aceleratorsID);
	virtual void GetWindowInformation(CREATESTRUCT& createStruct);
	bool GetCommandFileName(const wchar_t* in_cmdLine, wstring& out_filename);
protected:
	virtual void GetRegisterClass(WNDCLASSEX& wcex);
	vector<Win::IParent*> children;
	bool _isMainWindow;
	int initialWidth;
	int initialHeight;
	Window();
	inline virtual bool Window_WndProc(Win::Event& e);
	inline virtual void InitializeGui();
	inline virtual bool EventHandler(Win::Event& e);
	inline virtual void Window_WinAddChild(Win::Event& e);
	inline virtual void Window_Activate(Win::Event& e);
	inline virtual void Window_Cancel(Win::Event& e);
	inline virtual void Window_Char(Win::Event& e);
	inline virtual void Window_Close(Win::Event& e);
	inline virtual void Window_Open(Win::Event& e);
	inline virtual void Window_Destroy(Win::Event& e);
	inline virtual void Window_DrawItem(Win::Event& e);
	inline virtual void Window_DropFiles(Win::Event& e);
	inline virtual void Window_EraseBkgnd(Win::Event& e);
	inline virtual void Window_GetDlgCode(Win::Event& e);
	inline virtual void Window_GetFont(Win::Event& e);
	inline virtual void Window_GetMinMaxInfo(Win::Event& e);
	inline virtual void Window_GetText(Win::Event& e);
	inline virtual void Window_GetTextLength(Win::Event& e);
	inline virtual void Window_Help(Win::Event& e);
	inline virtual void Window_KeyDown(Win::Event& e);
	inline virtual void Window_KeyUp(Win::Event& e);
	inline virtual void Window_KillFocus(Win::Event& e);
	inline virtual void Window_LButtonDblclk(Win::Event& e);
	inline virtual void Window_LButtonDown(Win::Event& e);
	inline virtual void Window_LButtonUp(Win::Event& e);
	inline virtual void Window_RButtonDblclk(Win::Event& e);
	inline virtual void Window_RButtonDown(Win::Event& e);
	inline virtual void Window_RButtonUp(Win::Event& e);
	inline virtual void Window_MeasureItem(Win::Event& e);
	inline virtual void Window_MouseMove(Win::Event& e);
	inline virtual void Window_MouseWheel(Win::Event& e);
	inline virtual void Window_Paint(Win::Event& e);
	inline virtual void Window_SetFocus(Win::Event& e);
	inline virtual void Window_SetFont(Win::Event& e);
	inline virtual void Window_SetText(Win::Event& e);
	inline virtual void Window_Size(Win::Event& e);
	inline virtual void Window_SysCommand(Win::Event& e);
	inline virtual void Window_Timer(Win::Event& e);
	inline virtual void Window_User(Win::Event& e);
	inline virtual void Window_VScroll(Win::Event& e);
	inline virtual void Window_HScroll(Win::Event& e);
	inline virtual void Window_SocketNotify(Win::Event& e);
	inline virtual void Window_SocketHostname(Win::Event& e);
#ifdef WIN_DAC_ADC_SUPPORT
	inline virtual void Window_WomOpen(Win::Event& e);
	inline virtual void Window_WomClose(Win::Event& e);
	inline virtual void Window_WomDone(Win::Event& e);
	inline virtual void Window_WimOpen(Win::Event& e);
	inline virtual void Window_WimClose(Win::Event& e);
	inline virtual void Window_WimData(Win::Event& e);
#endif
	//inline virtual void GameLoop();
private:
	static LRESULT CALLBACK InternalWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

//_____________________________________________________________________ Control
class Control : public Win::Window, public Win::IExportable, public Win::IPrint
{
public:
	Control(void);
	virtual ~Control(void);
	//
	HWND Create(DWORD dwExStyle, const wchar_t * text, DWORD dwStyle, int x, int y, int width, int height, HWND hParent, int id);
	bool IsEvent(Win::Event& e, int notification);
	//
	COLORREF GetBackColor();
	virtual void SetBackColor(COLORREF color);
	__declspec( property( get=GetBackColor, put=SetBackColor ) ) COLORREF BackColor;
	//
	COLORREF GetTextColor();
	virtual void SetTextColor(COLORREF color);
	__declspec( property( get=GetTextColor, put=SetTextColor ) ) COLORREF TextColor;
	//
	COLORREF GetLineColor();
	virtual void SetLineColor(COLORREF color);
	__declspec( property( get=GetLineColor, put=SetLineColor ) ) COLORREF LineColor;
	//
	void SetPrinterFormat(bool printerFormat);
	virtual void SetWindowText(const wchar_t* text);
	virtual int GetWindowText(wchar_t* text, int size);
	virtual int GetTextLength();
	//
	void SetColorMode(bool isBlackAndWhite);
	//
	virtual wstring GetText();
	virtual void SetText(const wstring text);
	__declspec( property( get=GetText, put=SetText) ) wstring Text;
	//
	virtual void SetFont(Win::Gdi::Font& font);
	__declspec( property( put=SetFont) ) Win::Gdi::Font& Font;
	//____________________________________________________ IExportable
	virtual void OnPaintControl(Win::Gdi& gdi);
	HWND GetControlInfo(int& width, int&height);
	void SetControlSize(int width, int height);
	//____________________________________________________ IPrint
	void Print(Win::Gdi& gdi, Win::PrintInfo pi);
	//
	bool CopyToClipboard();
	//
	bool CopyToBitmap(int width, int height, bool clientEdge, Win::DDBitmap& result);
	bool SaveEmfImage(const wchar_t* fileName);
	bool SaveEmfImage(const wchar_t* fileName, double aspectRatio);

protected:
	Win::PrintInfo printInfo;
	wstring _text;
	bool _printerFormat;
	HFONT _hfont;
	COLORREF _textColor;
	COLORREF _backColor;
	COLORREF _lineColor;
	//
	COLORREF _colorModeBackColor;
	COLORREF _colorModeTextColor;
	COLORREF _colorModeLineColor;
	//
	int _fontHeight;
	void GetLogfont(LOGFONT& logfont);
	virtual void OnSizePrivate();
	void Window_Paint(Win::Event& e);
	void Window_Size(Win::Event& e);
	void Window_LButtonDown(Win::Event& e);
	void Window_RButtonDown(Win::Event& e);
	void Window_LButtonDblclk(Win::Event& e);
	const wchar_t * GetClassName(void){return L"WINTEMPLA_CONTROL";}
private:
	static bool bRegistered;
};

#ifdef WIN_GDI_PLUS_ON
//_____________________________________________________________________ Image
class Image : public Win::Window
{
public:
	Image(void);
	virtual ~Image(void);
	bool IsEvent(Win::Event& e, int notification);
	//
	const wstring& GetFileName();
	void SetFileName(const wstring& filename);
	__declspec( property( get=GetFileName, put=SetFileName ) ) wstring& FileName;
protected:
	wstring filename;
	void Window_Paint(Win::Event& e);
	void Window_LButtonDown(Win::Event& e);
	void Window_RButtonDown(Win::Event& e);
	const wchar_t * GetClassName(void){return L"WINTEMPLA_IMAGE";}
private:
	static bool bRegistered;
};
#endif
//_____________________________________________________________________Button
class Button : public Module, public Sql::ISelectBool
{
public:
	Button(void);
	virtual ~Button(void);
	//
	COLORREF GetBackColor();
	virtual void SetBackColor(COLORREF color);
	__declspec( property( get=GetBackColor, put=SetBackColor ) ) COLORREF BackColor;
	//
	COLORREF GetTextColor();
	virtual void SetTextColor(COLORREF color);
	__declspec( property( get=GetTextColor, put=SetTextColor ) ) COLORREF TextColor;
	//
	// To display an Icon and Text set the icon and do not use BS_ICON
	LRESULT SetImage(HICON hicon);
	LRESULT SetImage(Sys::Icon& icon);
	LRESULT SetImage(Sys::Bitmap& bitmap);
	LRESULT SetImage(Win::DDBitmap& bitmap);
	void SetChecked(bool bChecked);
	bool IsChecked();
	__declspec( property( get=IsChecked, put=SetChecked) ) bool Checked;
	__declspec( property( put=SetImage) ) Sys::Bitmap& Bitmap;
	__declspec( property( put=SetImage) ) Sys::Icon& Icon;
	bool IsEvent(Win::Event& e, int notification);
	void UpdateValue();
	static void DrawButton(Win::Gdi& gdi, RECT& rect, bool isUp, bool defaultButton, Gdi::Color3D& color3D);
	//static void DrawDefaultButton(Win::Gdi& gdi, RECT& rect, bool isUp, Gdi::Color3D& color3D);
	void DrawButton(DRAWITEMSTRUCT* pDrawItem);
	static void DrawButton(DRAWITEMSTRUCT* pDrawItem, COLORREF colorText, COLORREF backColor);
	static void DrawButtonText(Win::Gdi& gdi, DWORD buttonStyle, RECT rect, const wchar_t* text, COLORREF colorText);
	//_____________________________________________________________________ ISelectBool
	bool& SqlGetBool();
	void SqlUpdate(bool toGui);
protected:
	COLORREF _textColor;
	COLORREF _backColor;
	bool used_checked;
	bool _checked;
	const wchar_t * GetClassName(void){return WC_BUTTON;}
	void InitialUpdate(HWND hParent);
};
	
//_____________________________________________________________________Dialog
class Dialog : public Module
{
public:
	Dialog(void);
	virtual ~Dialog(void);
	int DialogBox_(HWND hWndParent); //Modal Dialog
	int CreateDialog_(HWND hWndParent); //Modeless
	int CreateDialog__(HWND hWndParent, LPDLGTEMPLATE pTemplate);// Modeless
	int BeginDialog(USHORT iconID, HINSTANCE hInstance); //Modal Dialog Application
	int BeginDialog(HWND hWndParent); //Modal Dialog
	//
	void EndDialog(int result);
	HWND GetNextTabItem(HWND hWndCurrentControl);
	HWND GetPrevTabItem(HWND hWndCurrentControl);
	HWND GetNextGroupItem(HWND hWndCurrentControl);
	HWND GetPrevGroupItem(HWND hWndCurrentControl);
	BOOL MapDialogRect(RECT* pRect);// Convert pRect to pixels coordinates
	static void SetInstance(HINSTANCE hInstance);
	void SetDefaultButton(Win::Button& button);
	LONG SetReturnValue(LONG value);
protected:
	void DoChildDock(Win::IParent& child);
	bool _isDialogApplication;
	int initialWidth;
	int initialHeight;
	virtual void GetDialogTemplate(DLGTEMPLATE& dlgTemplate);
	virtual int GetIDD(void);
	const wchar_t * GetClassName(void) {return L"WINDIALOG";}
	inline virtual void InitializeGui();
	virtual bool Window_WndProc(Win::Event& e);
	inline virtual bool EventHandler(Win::Event& e);
	inline virtual void Window_WinAddChild(Win::Event& e);
	inline virtual void Window_Activate(Win::Event& e);
	inline virtual void Window_Cancel(Win::Event& e);
	inline virtual void Window_Char(Win::Event& e);
	inline virtual void Window_Close(Win::Event& e);
	inline virtual void Window_Open(Win::Event& e);
	inline virtual void Window_Destroy(Win::Event& e);
	inline virtual void Window_DrawItem(Win::Event& e);
	inline virtual void Window_DropFiles(Win::Event& e);
	inline virtual void Window_EraseBkgnd(Win::Event& e);
	inline virtual void Window_GetFont(Win::Event& e);
	inline virtual void Window_GetMinMaxInfo(Win::Event& e);
	inline virtual void Window_GetText(Win::Event& e);
	inline virtual void Window_GetTextLength(Win::Event& e);
	inline virtual void Window_Help(Win::Event& e);
	inline virtual void Window_KeyDown(Win::Event& e);
	inline virtual void Window_KeyUp(Win::Event& e);
	inline virtual void Window_KillFocus(Win::Event& e);
	inline virtual void Window_LButtonDblclk(Win::Event& e);
	inline virtual void Window_LButtonDown(Win::Event& e);
	inline virtual void Window_LButtonUp(Win::Event& e);
	inline virtual void Window_RButtonDblclk(Win::Event& e);
	inline virtual void Window_RButtonDown(Win::Event& e);
	inline virtual void Window_RButtonUp(Win::Event& e);
	inline virtual void Window_MeasureItem(Win::Event& e);
	inline virtual void Window_MouseMove(Win::Event& e);
	inline virtual void Window_MouseWheel(Win::Event& e);
	inline virtual void Window_Paint(Win::Event& e);
	inline virtual void Window_SetFocus(Win::Event& e);
	inline virtual void Window_SetFont(Win::Event& e);
	inline virtual void Window_SetText(Win::Event& e);
	inline virtual void Window_Size(Win::Event& e);
	inline virtual void Window_SysCommand(Win::Event& e);
	inline virtual void Window_Timer(Win::Event& e);
	inline virtual void Window_User(Win::Event& e);
	inline virtual void Window_VScroll(Win::Event& e);
	inline virtual void Window_HScroll(Win::Event& e);
	inline virtual void Window_SocketNotify(Win::Event& e);
	inline virtual void Window_SocketHostname(Win::Event& e);
#ifdef WIN_DAC_ADC_SUPPORT
	inline virtual void Window_WomOpen(Win::Event& e);
	inline virtual void Window_WomClose(Win::Event& e);
	inline virtual void Window_WomDone(Win::Event& e);
	inline virtual void Window_WimOpen(Win::Event& e);
	inline virtual void Window_WimClose(Win::Event& e);
	inline virtual void Window_WimData(Win::Event& e);
#endif
	static LRESULT CALLBACK ModalDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK ModelessDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	USHORT iconID;
private:
	vector<Win::IParent*> children;
	bool bModal;
};

class DropDownList;
class ListBox;
class ListItemCollection;
//_____________________________________________________________________ ListItem
class ListItem
{
public:
	ListItem(void);
	virtual ~ListItem(void);
	__declspec( property( get=GetData, put=SetData ) ) LPARAM Data;
	LPARAM GetData();
	void SetData(LPARAM data);
	__declspec( property( get=GetText ) ) wstring Text;
	wstring GetText();
	void GetText(wchar_t* text);
	__declspec( property( get=GetTextLength ) ) int TextLength;
	int GetTextLength();
private:
	bool isListBox;
	int index;
	HWND listControl;
	friend class Win::ListItemCollection;
};

//_____________________________________________________________________ ListItemCollection
class ListItemCollection
{
public:
	ListItemCollection(void);
	virtual ~ListItemCollection(void);
	LRESULT Delete(int index);
	LRESULT DeleteAll();
	LRESULT Add(const wchar_t* text);
	LRESULT Add(const wstring& text);
	LRESULT Add(const wchar_t* text, LPARAM data);
	LRESULT Add(const wstring& text, LPARAM data);
	LRESULT Add(const wchar_t* text, int index, LPARAM data);
	LRESULT Add(const wstring& text, int index, LPARAM data);
	__declspec( property( get=GetCount ) ) int Count;
	int GetCount();
	//
	int GetIndex(const wchar_t* text);
	int GetIndex(const wstring& text);
	//
	Win::ListItem& operator[](long index);
private:
	bool used_data;
	LPARAM _data;
	Win::ListItem _item;
	void SetParent(Win::IParent* iparent, bool isListBox);
	Win::IParent* iparent;
	bool isListBox;
	friend class Win::DropDownList;
	friend class Win::ListBox;
};

//_____________________________________________________________________ DropDownList
class DropDownList : public Module, public Sql::ISqlNumerator, public Sql::ISelectInt
{
public:
	DropDownList(void);
	virtual ~DropDownList(void);
	//_____________________________________________________________________ ISqlNumerator
	void Enumerate(wchar_t** data, int colCount, int rowIndex);
	//
	LRESULT SetSelected(int index);
	int GetSelectedIndex();
	__declspec( property( get=GetSelectedIndex, put=SetSelected ) ) int SelectedIndex;
	//
	LRESULT SetSelected(const wchar_t* searchString);
	LRESULT SetSelected(const wstring& searchString);
	//
	void SetSelectedByData(LPARAM data);
	LPARAM GetSelectedData();
	__declspec( property ( get=GetSelectedData, put=SetSelectedByData ) ) LPARAM SelectedData;
	//
	ListItemCollection& GetItems();
	__declspec( property ( get=GetItems) ) ListItemCollection& Items;
	//
	LRESULT ShowDropDown(bool show);
	bool IsEvent(Win::Event& e, int notification);
	LRESULT FillWithDirectoryInfo(int nAttributes, const wchar_t* pszFilter);
	int GetMinWidth();
	void UpdateValue();
	//
	void CopyToClipboard();
	void PasteFromClipboard();
	void ClearSelection();
	void CutSelection();
	//_____________________________________________________________________ ISelectInt
	LPARAM& SqlGetInt();
	void SqlUpdate(bool toGui);
protected:
	Win::ListItemCollection _items;
	LPARAM _data;
	bool used_data;
	const wchar_t * GetClassName(void){return WC_COMBOBOX;}
	bool m_bListBox; // If false, then it is a DropDownList
	void InitialUpdate(HWND hParent);
};

//_____________________________________________________________________HourGlassCursor
class HourGlassCursor
{
public:
	HourGlassCursor(void);
	HourGlassCursor(bool busy);
	virtual ~HourGlassCursor(void);
	HCURSOR SetBusy();
	void SetNormal();
private:
	HCURSOR hCursor;
};

//_____________________________________________________________________ListBox
class ListBox : public DropDownList
{
public:
	ListBox(void);
	virtual ~ListBox(void);
	int MultipleSetSelected(int nIndex, bool bSelect);
	bool MultipleGetSelected(int nIndex);
	void SetColumnWidth(int columnWidth);
protected:
	const wchar_t * GetClassName(void){return WC_LISTBOX;}
};

//_____________________________________________________________________Menu
class Menu
{
public:
	Menu(void);
	virtual ~Menu(void);
	void Attach(HMENU hMenu, bool bPopUp);

	// Use this to attach a main menu with bPopUp set to false
	void Attach(HWND hWnd, bool bPopUp);
	bool Create(bool bPopUp);
	void AddItem(UINT nID, wchar_t* pszCaption, bool bChecked, bool bEnabled);
	void AddItem(UINT nID, HBITMAP hBitmap, bool bEnabled);
	void SetItemEnableByPosition(int nPosition, bool bEnabled);
	void SetItemEnableByID(UINT nID, bool bEnabled);
	void SetItemCheckByPosition(int nPosition, bool bChecked);
	void SetItemCheckByID(UINT nID, bool bChecked);
	bool Create(HINSTANCE hInstance, const wchar_t * pszID);
	HMENU GetHMENU();
	HMENU GetSubHMENU_(int nPosition);
	int GetStringByID(UINT nID, wchar_t* pszCaption, int nMaxCount);
	int GetStringByPosition(UINT nID, wchar_t* pszCaption, int nMaxCount);
	BOOL AddItem(MENUITEMINFO& menuInfo);
	bool IsItemEnabled(int nID);
	bool IsItemChecked(int nID);
	BOOL AppendMenu_(HMENU hMenu, wchar_t* pszCaption);
	BOOL AppendMenu_(Menu& menu, wchar_t* pszCaption);
	bool IsPopUp(void);
	BOOL DeleteItemByPosition(int nPosition);
	BOOL DeleteItemByID(int nID);
	UINT GetItemID(int nPosition);
	int GetItemCount(void);
	Menu GetSubMenu_(int nPosition);
	void AddSeparator(void);
	operator HMENU();
protected:
	HMENU hMenu;
	bool bCreated;
private:
	bool bPopUp;
	void Destructor();
	int nPosition;
};

//_____________________________________________________________________ Label
class Label : public Module
{
public:
	Label(void);
	virtual ~Label(void);
	LRESULT SetImage(HICON hicon);	
	LRESULT SetImage(HBITMAP hbitmap);
	LRESULT SetImage(Win::DDBitmap& bitmap);
	LRESULT SetImage(Sys::Bitmap& bitmap);
	LRESULT SetImage(Sys::Icon& icon);	
	LRESULT SetImage(HENHMETAFILE henhmetafile);
	LRESULT SetImage(Win::Metafile& metafile);
	bool IsEvent(Win::Event& e, int notification);
	//
	COLORREF GetBackColor();
	void SetBackColor(COLORREF color);
	__declspec( property( get=GetBackColor, put=SetBackColor) ) COLORREF BackColor;
	//
	COLORREF GetTextColor();
	void SetTextColor(COLORREF color);
	__declspec( property( get=GetTextColor, put=SetTextColor) ) COLORREF TextColor;
	//
	void SetTransparent(bool transparent);
	bool GetTransparent();
	__declspec( property( get=GetTransparent, put=SetTransparent) ) bool Transparent;
protected:
	const wchar_t * GetClassName(void){return WC_STATIC;}
	Win::Gdi::Brush _brush;
	COLORREF _backColor;
	COLORREF _textColor;
	bool _transparent;
};

//_____________________________________________________________________ VideoAvi
class VideoAvi : public Win::Module
{
public:
	VideoAvi(void);
	virtual ~VideoAvi(void);
	virtual HWND Create(DWORD dwExStyle, const wchar_t* pszWindowName, DWORD dwStyle, int x, int y, int width, int height, HWND hParent, int id);
	bool Open(int resourceID);
	bool Open(LPTSTR name);
	BOOL CloseAnimation();
	BOOL Play(UINT from, UINT to, UINT repeat);
	BOOL PlayContinuously();
	BOOL Play(int repeatCount);
	BOOL Stop();
	virtual bool IsEvent(Win::Event& e, int notification);
	//
	COLORREF GetBackColor();
	void SetBackColor(COLORREF color);
	__declspec( property( get=GetBackColor, put=SetBackColor) ) COLORREF BackColor;
protected:
	Win::Gdi::Brush _brush;
	const wchar_t * GetClassName(void){return ANIMATE_CLASS;} //Not used
	static int bRegistered;
	COLORREF _backColor;
};

//_____________________________________________________________________PropertySheet and Wizard
class PropertySheet_ : public Dialog
{
public:
	PropertySheet_(void);
	virtual ~PropertySheet_(void);
	HPROPSHEETPAGE CreatePropertySheetPage_(HWND hParent, const wchar_t * pszTemplateId, const wchar_t * pszIcon);
	HPROPSHEETPAGE CreateWizardMainPage(HWND hParent, const wchar_t * pszTemplateId);
	HPROPSHEETPAGE CreateWizardPage(HWND hParent, const wchar_t * pszTemplateId, const wchar_t * pszTitle, const wchar_t * pszSubTitle);
	static int CALLBACK RemoveContextHelpProc(HWND hwnd, UINT message, LPARAM lParam);
	void SetEnableApplyButton(bool bEnabled);  
	void SetWizardButtons(DWORD dwFlags);
protected:
	static LRESULT CALLBACK PropertySheetProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	bool m_bModal;
};

//_____________________________________________________________________ColorDlg
class ColorDlg
{
public:
	ColorDlg(void);
	virtual ~ColorDlg(void);
	bool BeginDialog(HWND hWndParent);
	//
	__declspec( property( get=GetSelectedColor, put=SetSelectedColor) ) COLORREF SelectedColor;
	COLORREF GetSelectedColor();
	 void SetSelectedColor(COLORREF color);
	 //
	 bool SaveCustomColors(const wchar_t* filename);
	 bool LoadCustomColors(const wchar_t* filename);
	//
	void ResetCustomColors();
private:
	CHOOSECOLOR m_cc;
	static COLORREF m_rgbColor[16];
};

//_____________________________________________________________________ DateView
class DateView : public Win::Module, public Sql::ISelectTime
{
public:
	DateView(void);
	virtual ~DateView(void);
	bool GetCurrentSelection(Sys::Time& systime);
	Sys::Time GetCurrentSelection();
	bool SetCurrentSelection(Sys::Time& systime);
	__declspec( property( get=GetCurrentSelection, put=SetCurrentSelection) ) Sys::Time SelectedDate;
	//
	bool SetRange(Sys::Time& minimum, Sys::Time& maximum);
	bool GetCurrentSelection(int& month, int& day, int& year);
	bool SetCurrentSelection(int month, int day, int year);
	bool IsEvent(Win::Event& e, int notification);
	void AdjustSize(int x, int y);
	//
	void SetBackColor(COLORREF color);
	COLORREF GetBackColor();
	__declspec( property( get=GetBackColor, put=SetBackColor) ) COLORREF BackColor;
	//
	void SetTextColor(COLORREF color);
	COLORREF GetTextColor();
	__declspec( property( get=GetTextColor, put=SetTextColor) ) COLORREF TextColor;
	//
	void SetMonthBkColor(COLORREF color);
	COLORREF GetMonthBkColor();
	__declspec( property( get=GetMonthBkColor, put=SetMonthBkColor) ) COLORREF MonthBkColor;
	//
	void SetTitleBkColor(COLORREF color);
	COLORREF GetTitleBkColor();
	__declspec( property( get=GetTitleBkColor, put=SetTitleBkColor) ) COLORREF TitleBkColor;
	//
	void SetTitleTextColor(COLORREF color);
	COLORREF GetTitleTextColor();
	__declspec( property( get=GetTitleTextColor, put=SetTitleTextColor) ) COLORREF TitleTextColor;
	//
	void SetTrailingTextColor(COLORREF color);
	COLORREF GetTrailingTextColor();
	__declspec( property( get=GetTrailingTextColor, put=SetTrailingTextColor) ) COLORREF TrailingTextColor;
	//
	void Window_Size(Win::Event& e); // Call onsize of the parent to display as much months as possible
	//_______________________________________ ISelectTime
	Sys::SqlTime& SqlGetTime();
	Sys::Time& SqlGetSysTime();
	void SqlUpdate(bool toGui);
protected:
	const wchar_t * GetClassName(void){return MONTHCAL_CLASS;}
	Sys::Time _systemtime;	
	bool used_systemtime;
	void InitialUpdate(HWND hParent);
	Sys::SqlTime _sqltime;
private:
	static bool bInit;
};

//_____________________________________________________________________ HotKey
class HotKey : public Win::Module
{
public:
	HotKey(void);
	virtual ~HotKey(void);
	void SetRules(WPARAM invalidKeyCombinations, LPARAM invalidEntries);
	void SetHotKey(WPARAM defaultKey);
protected:
	const wchar_t * GetClassName(void){return HOTKEY_CLASS;}
};

//_____________________________________________________________________ DateTimeBox
class DateTimeBox : public Win::Module, public Sql::ISelectTime
{
public:
	DateTimeBox(void);
	virtual ~DateTimeBox(void);
	bool GetCurrentSelection(Sys::Time& systime);
	//
	Sys::Time GetCurrentSelection();
	bool SetCurrentSelection(Sys::Time& systime);
	__declspec( property( get=GetCurrentSelection, put=SetCurrentSelection) ) Sys::Time SelectedDate;
	//
	bool GetCurrentSelection(int& month, int& day, int& year);
	bool SetCurrentSelection(int month, int day, int year);
	//
	bool SetRange(Sys::Time& minimum, Sys::Time& maximum);
	//void SetMonthBkColor(COLORREF color);
	//void SetTitleBkColor(COLORREF color);
	//void SetTitleTextColor(COLORREF color);
	//void SetTrailingTextColor(COLORREF color);
	bool IsEvent(Win::Event& e, int notification);

	//format> L"hh:mm:ss dddd MMM dd, yyyy"
	bool SetFormat(const wchar_t * format);
	void UpdateValue();
	//_______________________________________ ISelectTime
	Sys::SqlTime& SqlGetTime();
	Sys::Time& SqlGetSysTime();
	void SqlUpdate(bool toGui);
protected:
	Sys::Time _systemtime;	
	bool used_systemtime;
	const wchar_t * GetClassName(void){return DATETIMEPICK_CLASS;}
	void InitialUpdate(HWND hParent);
	Sys::SqlTime _sqltime;
private:
	static bool bInit;
};

//_____________________________________________________________________ IpAddress
class IpAddress : public Win::Module
{
public:
	IpAddress(void);
	virtual ~IpAddress(void);
	void SetFieldRange(int index, int minimum, int maximum);
	void SetAddress(int b1, int b2, int b3, int b4);
	void GetAddress(int& b1, int& b2, int& b3, int& b4);
	void Clear();
	bool IsBlank();
protected:
	const wchar_t * GetClassName(void){return WC_IPADDRESS;}
private:
	static bool bInit;
};

//_____________________________________________________________________ SysLink
class SysLink : public Win::Module
{
public:
	SysLink(void);
	virtual ~SysLink(void);
	void SetItem(LITEM& litem);
	void GetItem(LITEM& litem);
protected:
	const wchar_t * GetClassName(void){return WC_LINK;}
private:
	static bool bInit;
};

	//LITEM litem;
	//litem.state = LIS_ENABLED;
	//litem.mask = LIF_ITEMINDEX | LIF_STATE | LIF_URL;
	//litem.iLink = 0;
	//_snwprintf_s(litem.szUrl, L_MAX_URL_LENGTH, _TRUNCATE, L"%s", L"http://www.yahoo.com");
	//this->link1.SetItem(litem);

//#pragma once
//#include "Module.h"
//#include "Error.h"
//
//// This control works only with Unicode
////#define _WIN32_WINNT 0x0501   // for Mouse Wheel support & SysLink
//namespace win{
//
//class SysLink : public win::Module
//{
//public:
//	SysLink(void);
//	virtual ~SysLink(void);
//	HWND Create(DWORD dwExStyle, DWORD dwStyle, int x, int y, int width, int height,
//					 const TCHAR* pszHtml, HWND hParent, HMENU id);
//	bool SetItem(PLITEM pLitem)
//	{
//		return (TRUE==SendMessage(this->m_hWnd, (UINT) LM_SETITEM, (WPARAM)NULL,
//			(LPARAM)pLitem));
//	}
//	bool GetItem(PLITEM pLitem)
//	{
//		return (TRUE==SendMessage(this->m_hWnd, (UINT) LM_GETITEM, (WPARAM)NULL,
//			(LPARAM)pLitem));
//	}
//private:
//	static int m_nCount;
//};
//
//}

 //#include <commctrl.h> //Requires a manifest 
//#define _WIN32_WINNT >= 0x501
// Class View -> right click -> Properties -> Linker -> Command Line -> comctl32.lib

// Following are examples of resource strings that
// contain an anchor tag(<A>) with an ID or
// HREF attribute.

// Or inside a Resource file
//CONTROL "For more information, see the 
//<A ID=""idLaunchHelp"">HelpCenter</A>, 
//<A ID=""idHelpMenu"">Help Menu</A>,
//<A HREF=""http://www.help.com"">Website</A>,
//IDD_MYLINK, WS_TABSTOP, 8, 8, 200, 24

/*
LRESULT InstDigital::OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//TCHAR * psz = _T("Click here to connect to <A HREF=\"http://www.yahoo.com\">Yahoo!</A>");
	TCHAR * psz = _T("Click here to connect to <A HREF=\"ftp://www.ugto.mx\">Ugto Ftp!</A>");
	this->m_sl.Create(0, 0, 0, 0, 200, 300, psz, hWnd, (HMENU)IDC_LINK);
	LITEM litem;
	litem.mask = LIF_ITEMINDEX | LIF_URL;
	litem.iLink = 0;
	this->m_sl.GetItem(&litem);
	this->MessageBox_(litem.szUrl);
	return 0;
}

LRESULT InstDigital::OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LPNMHDR pHdr = (LPNMHDR)lParam;
	PNMLINK pNMLink = NULL;
	switch (pHdr->code)
	{
		case NM_RETURN:
		case NM_CLICK:
			 pNMLink= (PNMLINK) lParam;
			 switch(pNMLink->item.iLink)
			 {
			 case 0:
				 this->MessageBox_(pNMLink->item.szUrl, _T("Open this link"));
				 break;
			 }
			
			//if (!StrCmpW (pNMLink->item.szID,
			//				L"idLaunchHelp"))
			//{
			//	// TODO: Launch Help Center...
			//}
			//else if (!StrCmpW (pNMLink->item.szID,
			//	L"idHelpMenu"))
			//{
			//	// TODO: Launch Help Menu...
			//}
	break;
	}
	return TRUE;
}
*/

//#include "StdAfx.h"
//#include ".\SysLink.h"
//
//namespace win{
//
//int SysLink::m_nCount = 0;
//
//SysLink::SysLink(void)
//{
//	if (m_nCount==0)
//	{
//		CoInitialize(NULL);
//		INITCOMMONCONTROLSEX cc;
//		cc.dwSize=sizeof(INITCOMMONCONTROLSEX);
//		cc.dwICC=ICC_LINK_CLASS;
//		InitCommonControlsEx(&cc);
//	}
//	m_nCount++;
//}
//
//SysLink::~SysLink(void)
//{
//	m_nCount--;
//	if (m_nCount==0) CoUninitialize();
//}
//
//HWND SysLink::Create(DWORD dwExStyle, DWORD dwStyle, int x, int y, int width, int height,
//					 const TCHAR* pszHtml, HWND hParent, HMENU id)
//{
//	if (dwStyle==0) dwStyle = WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP; 
//	 Module::Create(dwExStyle, (LPCTSTR)WC_LINK, pszHtml, dwStyle, 
//		x, y, width, height, hParent, id, NULL);
//	 win::Error::DisplayLastError(NULL);
//	 return 0;
//}
//}
/*
LIF_ITEMINDEX
Retrieve the numeric item index. Items are always accessed by index, therefore you must always set this flag and assign a value to iLink. To obtain the item ID you must set both LIF_ITEMINDEX and LIF_ITEMID.
LIF_STATE
Use stateMask to get or set the state of the link.
LIF_ITEMID
Specify the item by the ID value given in szID.
LIF_URL
Set or get the URL for this item.
iLink
Value of type int that contains the item index. This numeric index is used to access a SysLink control link.
state
Combination of one or more of the following flags, describing the state of the item.
LIS_ENABLED
The link can respond to user input. This is the default unless the entire control was created with WS_DISABLED. In this case, all links are disabled.
LIS_FOCUSED
The link has the keyboard focus. Pressing ENTER sends a NM_CLICK notification.
LIS_VISITED
The link has been visited by the user. Changing the URL to one that has not been visited causes this flag to be cleared.
stateMask
Combination of flags describing which state item to get or set. Allowable items are identical to those allowed in state.
szID
WCHAR string that contains the ID name. The maximum number of characters in the array is MAX_LINKID_TEXT. The ID name cannot be used to access a SysLink control link. You use the item index to access the item.
szUrl
WCHAR string that contains the URL represented by the link. The maximum number of characters in the array is L_MAX_URL_LENGTH.
*/

//#ifdef WIN_FOLDER_DLG
//_____________________________________________________________________FolderDlg
class FolderDlg : public Win::Module
{
public:
	FolderDlg(void);
	~FolderDlg(void);
	wchar_t* BeginDialog(HWND hParent, const wchar_t * caption);
	wchar_t* GetFolderName(); //Call this after a successfull call to BeginDialog
private:
	wchar_t* GetPathName_(LPCITEMIDLIST pidl);
	wchar_t* GetDisplayNameOf(IShellFolder* psf, LPCITEMIDLIST pidl, DWORD uFlags);
	static void FreePIDL(LPCITEMIDLIST pidl);
	wchar_t pathName[WIN_FILEDLG_MAXPATH];
	wchar_t displayName[WIN_FILEDLG_MAXPATH];
	wchar_t tmpName[WIN_FILEDLG_MAXPATH];// allows selecting previous folder selected
	IShellFolder *shellFolderRoot;
protected:
	BROWSEINFO browseInfo;
	static int CALLBACK CallbackProc(HWND hwnd, UINT msg, LPARAM lp, LPARAM lpData);
	virtual void OnInitialized();
	//virtual void OnIUnknown(IUnknown* punk);
	virtual void OnSelChanged(LPCITEMIDLIST pidl);
	virtual BOOL OnValidateFailed(const wchar_t * lpsz);
	void EnableOK(BOOL bEnable) {this->SendMessage(BFFM_ENABLEOK,0,bEnable);}// Enable or disable the OK button
	void SetOKText(LPCWSTR lpText) {this->SendMessage(BFFM_SETOKTEXT,0,(LPARAM)lpText);}
	//void SetSelection(const wchar_t * lpText) {this->SendMessage(BFFM_SETSELECTION,TRUE,(LPARAM)lpText);}
	void SetSelection(const wchar_t * lpText) {this->SendMessage(BFFM_SETSELECTION, (LPARAM)lpText, TRUE);}
	void SetSelection(LPCITEMIDLIST pidl) {SendMessage(BFFM_SETSELECTION,FALSE,(LPARAM)pidl);}
	void SetExpanded(LPCWSTR lpText) {this->SendMessage(BFFM_SETEXPANDED,TRUE,(LPARAM)lpText);}
	void SetExpanded(LPCITEMIDLIST pidl) {this->SendMessage(BFFM_SETEXPANDED,FALSE,(LPARAM)pidl);}
	void SetStatusText(const wchar_t * pText) {this->SendMessage(BFFM_SETSTATUSTEXT,0,(LPARAM)pText);}
	const wchar_t * GetClassName(void){return L"WINFOLDERDLG";}
};
//#endif

//_____________________________________________________________________FileDlg
class FileDlg
{
public:
	FileDlg(void);
	virtual ~FileDlg(void);
	bool BeginDialog(HWND hWndParent, const wchar_t* caption, bool save);
	//
	void SetFilter(wchar_t* pszFilter, int nFilterIndex, wchar_t* pszDefaultExtenstion);
	const wchar_t* GetFileName();
	bool SetFileName(const wchar_t* fileName);
	const wchar_t* GetFileNameFullPath();
	const wchar_t* GetFilePath();
	const wchar_t* GetExt();
	const wchar_t* GetFileNameWithoutExt();
	void Clear();
	void ClearFileName();
	//
	wstring& GetWorkingFolder();
	void SetWorkingFolder(const wstring& folderName);
	__declspec( property( get=GetWorkingFolder, put=SetWorkingFolder) ) wstring WorkingFolder;
	//
	wstring GetSelectedFileName();
	void SetSelectedFileName(const wstring fileName);
	__declspec( property( get=GetSelectedFileName, put=SetSelectedFileName) ) wstring SelectedFileName;
	//
	OPENFILENAME openFileName;
private:
	wchar_t m_szFileName[WIN_FILEDLG_MAXPATH];
	wchar_t m_szFileNameWithoutExt[WIN_FILEDLG_MAXPATH];
	wchar_t m_szPath[WIN_FILEDLG_MAXPATH];
	wchar_t m_szFilePath[WIN_FILEDLG_MAXPATH];
	wchar_t m_szDefaultExt[32];
	wchar_t m_szFilter[WIN_MAX_FILTER];
	wchar_t m_szExt[32];
	static wchar_t m_szCustomFilter[WIN_MAX_FILTER];
	wstring _workingFolder;
};

//_____________________________________________________________________FindReplaceDlg
class FindReplaceDlg
{
public:
	FindReplaceDlg(void);
	virtual ~FindReplaceDlg(void);
	static void OnParentCreate()
		{m_FindMessage=RegisterWindowMessage(FINDMSGSTRING);}//Call from Parent.Create
	HWND OpenFindDlg(HWND hWndParent, const wchar_t* pszFindWhat);
	HWND OpenReplaceDlg(HWND hWndParent, const wchar_t* pszFindWhat, const wchar_t* pszReplaceWith);
	static LRESULT CheckFindMessage(Win::Event& e);
private:
	static FINDREPLACE m_fr;
	static wchar_t m_szFindText[MAX_FIND_LEN];
	static wchar_t m_szReplaceText[MAX_FIND_LEN];
	static HWND m_hWndFindReplace;
	static void UpdateHWND(HWND hWndFindReplaceDlg);
	static UINT m_FindMessage;
};

//_____________________________________________________________________FontDlg
class FontDlg
{
public:
	FontDlg(void);
	virtual ~FontDlg(void);
	bool BeginDialog(HWND hWndParent);
	//
	void SetSelectedFontName(const wstring& fontname);
	wstring GetSelectedFontName();
	__declspec( property( get=GetSelectedFontName, put=SetSelectedFontName) ) wstring SelectedFontName;
	//
	void SetSelectedPointSize(const double pointSize);
	double GetSelectedPointSize();
	__declspec( property( get=GetSelectedPointSize, put=SetSelectedPointSize) ) double SelectedPointSize;
	//
	void SetSelectedFont(Win::Gdi::Font& font);
	//
	void SetSelectedLogFont(LOGFONT& logFont);
	LOGFONT& GetSelectedLogFont();
	__declspec( property( get=GetSelectedLogFont, put=SetSelectedLogFont) ) LOGFONT SelectedLogFont;
	//
	void SetSelectedFontColor(COLORREF color);
	COLORREF GetSelectedFontColor();
private:
	CHOOSEFONT m_cf;
	LOGFONT m_logFont;
};

class PrintDoc;

//_____________________________________________________________________Edit
class Textbox : public Module, public Win::IPrint, public Sql::ISelectString
{
public:
	Textbox(void);
	virtual ~Textbox(void);
	//
	COLORREF GetBackColor();
	virtual void SetBackColor(COLORREF color);
	__declspec( property( get=GetBackColor, put=SetBackColor ) ) COLORREF BackColor;
	//
	COLORREF GetTextColor();
	virtual void SetTextColor(COLORREF color);
	__declspec( property( get=GetTextColor, put=SetTextColor ) ) COLORREF TextColor;
	//
	void SetLeft(bool isLeft);
	bool GetLeft();
	__declspec( property ( get=GetLeft, put=SetLeft ) ) bool Left;
	//
	void SetCenter(bool isCenter);
	bool GetCenter();
	__declspec( property ( get=GetCenter, put=SetCenter ) ) bool Center;
	//
	void SetRight(bool isRight);
	bool GetRight();
	__declspec( property ( get=GetRight, put=SetRight ) ) bool Right;
	//
	void SetMultiline(bool isMultiline);
	bool GetMultiline();
	__declspec( property ( get=GetMultiline, put=SetMultiline ) ) bool Multiline;
	//
	void SetUppercase(bool isUppercase);
	bool GetUppercase();
	__declspec( property ( get=GetUppercase, put=SetUppercase ) ) bool Uppercase;
	//
	void SetLowercase(bool isLowercase);
	bool GetLowercase();
	__declspec( property ( get=GetLowercase, put=SetLowercase) ) bool Lowercase;
	//
	void SetPassword(bool isPassword);
	bool GetPassword();
	__declspec( property ( get=GetPassword, put=SetPassword ) ) bool Password;
	//
	void SetNumber(bool isNumber);
	bool GetNumber();
	__declspec( property ( get=GetNumber, put=SetNumber ) ) bool Number;
	//
	bool GetInt(int &outValue);
	int GetInt(void);
	void SetInt(int value);
	__declspec( property( get=GetInt, put=SetInt) ) int IntValue;
	//
	// icon values: TTI_ERROR,TTI_INFO,TTI_NONE,TTI_WARNING
	LRESULT ShowBalloonTip(LPCWSTR caption, LPCWSTR text, INT icon); 
	LRESULT ShowBalloonTip(const wstring& caption, const wstring& text, INT icon); 
	void HideBalloonTip();
	bool CanUndo();
	bool Undo();
	//
	void SetDouble(double value, const wchar_t* format);
	void SetDouble(double value);
	double GetDouble();
	__declspec( property( get=GetDouble, put=SetDouble) ) double DoubleValue;
	//
	void SetMaxText(int maxCharacter);// Check for notification EN_MAXTEXT
	int GetMaxText();
	__declspec( property( get=GetMaxText, put=SetMaxText) ) int MaxText;
	//
	int GetLineCount();
	int GetPrintLineCount(Win::PrintDoc& doc, int lineHeight);
	void SetPrintAlignment(int alignment); //WIN_ALIGNMENT_LEFT, WIN_ALIGNMENT_RIGHT, WIN_ALIGNMENT_CENTER, WIN_ALIGNMENT_JUSTIFIED
	//void SetPrintList(int type); //WIN_LISTTYPE_NONE, WIN_LISTTYPE_NUMBER, WIN_LISTTYPE_UNNUMBER

	void SetReadOnly(bool readOnly);
	bool GetReadOnly();
	__declspec( property( get=GetReadOnly, put=SetReadOnly) ) bool ReadOnly;

	int GetOffset(int line);
	bool GetLine(wchar_t* result, int lineIndex, int bufferSize);
	wstring GetLine(int lineIndex);
	int GetLineLength(int lineIndex);
	int ScrollCaret();
	LRESULT Scroll(WPARAM how);
	bool AppendText(wchar_t* buffer);
	
	LRESULT SetCueBanner(wchar_t* cue);
	//
	bool IsEvent(Win::Event& e, int notification);
	//_______________________________________________________________ Win::IPrint
	void Print(Win::Gdi& gdi, Win::PrintInfo pi);
	//
	void CopyToClipboard();
	void PasteFromClipboard();
	void ClearSelection();
	void CutSelection();
	void SelectAll();
	LRESULT GetSelection(int& start, int& end);
	LRESULT SetSelection(int start, int end);
	void ReplaceSelection(wchar_t* replaceWithThis, bool canBeUndone);
	//
	wstring GetText();
	void SetText(const wstring text);
	__declspec( property( get=GetText, put=SetText) ) wstring Text;
	//
	void UpdateValue();
	bool GetParagraphText(vector<wstring>& output);
	//_____________________________________________________________________ ISelectString
	wstring& SqlGetString();
	void SqlUpdate(bool toGui);
protected:
	void InitialUpdate(HWND hParent);
	const wchar_t * GetClassName(void){return WC_EDIT;}
	int maxTextLength;
	wstring _text;
	bool used_text;
	Win::Gdi::Brush brush;
	COLORREF _backColor;
	COLORREF _textColor;
	int _printAlignment;
	//int _printRowCount;
	void CreatePrintFont(Win::Gdi::Font& output, int rowHeight);
	//int _printListType;
};

//_____________________________________________________________________PrintDoc
class PrintDoc : public Win::IPrintDoc
{
public:
	PrintDoc(void);
	virtual ~PrintDoc(void);
	void Create(const wchar_t* documentName);
	bool Add(int height, int repeatCount, Win::IPrint& iprint);
	void SetFooter(int height, Win::IPrint& iprint);
	//_______________________IPrintDoc
	void SetMargin(RECT& rect);
	RECT GetMargin(void);
	void SetOrientation(bool isPortrait);
	bool IsPortraitOrientation(void);
	void SetPaperSize(const POINT paperSize);
	POINT GetPaperSize(void);
	void ResetCurrentPosition(void);
	void SetDocumentName(const wchar_t* name);
	const wchar_t* GetDocumentName();
	BOOL OnPrintPage(Win::Gdi& gdi, int page, int width, int height); 
	int GetPageCount();
	//_______________________
	POINT GetPrintingAreaSize(void);
	static POINT GetLetterPrintArea(bool isPortrait);  //Manager function, it returns the size of the print area in a page of size letter
	static int GetRowCountPerLetterPage(bool isPortrait, int fontSize); 
protected:
	POINT currentPosition;
	wchar_t documentName[WIN_PRINTDOC_NAMEMAX];
	void Reset(void);
private:
	RECT margin;
	POINT paperSize;
	Win::IPrint *element[WIN_PRINTDOC_ELEMENTMAX];
	int elementHeight[WIN_PRINTDOC_ELEMENTMAX];
	int elementRepeat[WIN_PRINTDOC_ELEMENTMAX];
	int elementCount;
	Win::IPrint* footer;
	int footerHeight;
	int GetNextElementHeight(int in_element, int in_repeat, int height);
};

//___________________________________________ PrintSeparator
class PrintSeparator: public Win::IPrint
{
public:
	PrintSeparator();
	~PrintSeparator();
	void Print(Win::Gdi& gdi, Win::PrintInfo pi);
	//bool CopyToClipboard(HWND hWnd);
};

//_____________________________________________________________________PageDlg
class PageDlg
{
public:
	PageDlg(void);
	virtual ~PageDlg(void);
	BOOL OpenPageSetupDlg(HWND hWndParent, Win::IPrintDoc* pIPrintDoc);
	BOOL OpenPageSetupDlg(HWND hWndParent);
	RECT GetMargin();
	void SetMargin(RECT& rect);
	void SetMinMargin(RECT& rect);
	POINT GetPaperSize();
	void SetPaperSize(POINT& pt);
private:
	PAGESETUPDLG m_psd;
	static BOOL CALLBACK PaintHook(HWND hwndDlg, UINT uMsg, WPARAM wParam,
    LPARAM lParam);
	void Destructor();
};

//_____________________________________________________________________PrintDlg
// It includes:  Print Dialog, Print Setup Dialog
// You must derive from this Class and implement PrintPage();
class PrintDlg_ : public Win::Module
{
public:
	PrintDlg_(void);
	virtual ~PrintDlg_(void);
	BOOL BeginDialog(HWND hWndParent, Win::IPrintDoc* pIPrintDoc);
	BOOL OpenPrintSetupDlg(HWND hWndParent);
//	If the PD_RETURNDEFAULT flag is set and both hDevMode and 
//	hDevNames are NULL, PrintDlg uses the hDevNames and hDevMode members to 
//	return information about the current default printer without displaying the dialog box.
protected:
	const wchar_t * GetClassName(void){return L"PRINTDLG";} //Not used
private:
	static PRINTDLG m_pd;
	void Destructor();
	static bool m_bUserAbort;
	static HWND m_hDlgCancel;
	static BOOL CALLBACK PrintDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
	static BOOL CALLBACK AbortProc(HDC hPrinterDC, int iCode);
	static HWND m_hInfo;
	void UpdateDevInfo();
	void UpdateCancelWindowInfo(int page);
	BOOL OnPrintDocument();
	BOOL OnPrintPage(HDC hdc, int page);
	int m_nHorzRes;
	int m_nVertRes;
	int m_nHorzSize;
	int m_nVertSize;
	Win::IPrintDoc* m_pIPrintDocument;
	//PRINTER_INFO_4 pinfo4;
	//PRINTER_INFO_5 pinfo5;
};

//_____________________________________________________________________PrintPreview
class PrintPreview : public Window
{
public:
	PrintPreview(void);
	virtual ~PrintPreview(void);
	void SetDoc(Win::IPrintDoc* pIPrintDoc);
	void SetCurrentPage(int pageNumber);
	int GetCurrentPage(void);
protected:
	const wchar_t * GetClassName(void){return L"WINPRINTPREVIEW";}
	//void WndProc(Win::Event& e);
private:
	void Window_Paint(Win::Event& e);
	Win::IPrintDoc* pIPrintDoc;
	int page;
	RECT rect;
	static bool registered;
};

//_____________________________________________________________________PrintPreviewDlg
class PrintPreviewDlg : public Dialog
{
public:
	wstring PrintButtonText;
	wstring CloseButtonText;
	wstring PreviousButtonText;
	wstring NextButtonText;
	wstring PageSetupButtonText;
	wstring WindowText;
	Win::Gdi::Font font;
	//Win::Gdi::Font fontBold;
	virtual ~PrintPreviewDlg(void);
	PrintPreviewDlg(void);
	BOOL BeginDialog_(HWND hWndParent, Win::IPrintDoc* pIPrintDoc);
	static double GetMaxScale(const Win::Gdi::PointF& pfInterior, const Win::Gdi::PointF& pfExterior);
private:
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate);
	void Window_Open(Win::Event& e);
	void Window_Paint(Win::Event& e);
	void Window_Size(Win::Event& e);
	void btPrint_Click(Win::Event& e);
	void btPageSetup_Click(Win::Event& e);
	void btClose_Click(Win::Event& e);
	void btPrev_Click(Win::Event& e);
	void btNext_Click(Win::Event& e);
	//void btMsWord_Click(Win::Event& e);
	//void btMsExcel_Click(Win::Event& e);
	int m_nPage;
	int m_nMaxPage;
	RECT m_rect;
	PAINTSTRUCT m_ps;
	Win::Button btPrint;
	Win::Button btPageSetup;
	Win::Button btClose;
	Win::Button btPrev;
	Win::Button btNext;
	//Win::Button btMsWord;
	//Win::Button btMsExcel;
	Win::PrintPreview m_printPreview;
	bool EventHandler(Win::Event& e);
	Win::IPrintDoc* m_pIPrintDocument;
	Win::PageDlg m_pageDlg;
	Win::PrintDlg_ m_printDlg;
	RECT m_rectButton;
	void Resize();
	void UpdateButtons();
};

//_____________________________________________________________________ Scintilla
// Be sure to include Scintilla.h before WintemplaWin.h
// Be sure to place in the working folder SciLexer.dll
// Be sure to include SciLexer.h before Scintilla.h
#ifdef SCINTILLA_H
class Scintilla: public Win::Window, public Win::IPrint
{
public:
	Scintilla();
	~Scintilla();
	void Undo();
	bool CanUndo();
	void Redo();
	bool CanRedo();
	void Replace(const wchar_t* originalText, const wchar_t* newText);
	void Cut();
	void Copy();
	void Paste();
	void Clear();
	bool CanPaste();
	void BeginUndoAction();
	void EndUndoAction();
	void EmptyUndoBuffer();
	//
	void SelectAll();
	void SetSelectionStart(int position);
	void SetSelectionEnd(int position);
	void SelectLine(int line);
	int GetSelectionStart();
	int GetSelectionEnd();
	bool IsSelectionEmpty();
	int GetSelectionStartLine();
	int GetSelectionEndLine();
	void GetSelectedText(wstring& text);
	int LineFromPosition(int position);
	int PositionFromLine(int line);
	int GetLineEndPosition(int line);
	int LineLength(int line);
	void GetCurrentLine(wstring& text);
	int GetCurrentLine(char * text);
	int GetCurrentLineNumber();
	//
	void New();
	void ClearAll();
	void SetSavePoint(); // Call this every time you save the file
	bool IsModified();
	void Cancel();
	void SetUndoCollection(bool collectInformation);
	void AddText(int length, const wchar_t* text);
	int GetLineCount();
	//
	void CommentOut();
	void Uncomment();
	//
	void GoToPosition(int position);
	void GoToLine(int line);
	void SetCurrentPostion(int position);
	int GetCurrentPosition();
	//
	int GetTextLength();
	void GetText(int length, char *text);
	void GetText(wstring& text);
	void GetTextRange(int posStart, int posEnd, wstring& text);
	void SetText(const wchar_t* text);
	void GetLine(int line, wstring& text);
	void GetLine(int line, string& text);
	void GetLine(int line, char * text);
	void ReplaceSelection(const char* text);
	int TextWidth(int styleNumber, const char *text);
	//
	void SetLexer(int sclex);
	void SetKeyWords(int keyWordSet, const char *keyWordList);
	//
	void SetStyleFore(int styleNumber, COLORREF color);
	void SetStyleBack(int styleNumber, COLORREF color);
	void SetStyleSize(int styleNumber, int sizeInPoints);
	int GetStyleSize(int styleNumber);
	void SetStyleFont(int styleNumber, const char* fontName);
	void GetStyleFont(int styleNumber, char * buffer);
	void SetStyle(int styleNumber, COLORREF fore, COLORREF back, int sizeInPoints, const char* fontName);
	void StyleClearAll();
	//
	void TipShow(int position, const char* tip);
	bool IsTipActive();
	void TipCancel();
	void SetTipHighlight(int highlightStart, int highlightEnd);
	void SetTipBackColor(COLORREF color);
	void SetTipTextColor(COLORREF color);
	void SetTipForeHltColor(COLORREF color);
	void SetTipUseStyle(int tabsize);
	void SetTipPosition(bool above);
	//
	void AutoCompletionShow(int lenEntered, const char *list);
	void AutoCompletionCancel();
	bool IsAutoCompletionActive();
	int AutoCompletionPositionStart();
	void AutoCompletionComplete();
	void AutoCompletionStop(const char *chars);
	void AutoCompletionSelect(const char* chars);
	int AutoCompletionGetCurrent();
	bool GetAutoCompletionIgnoreCase();
	void SetAutoCompletionIgnoreCase(bool ignoreCase);
	int GetAutoCompletionMaxWidth();
	void SetAutoCompletionMaxWidth(int width);
	int GetAutoCompletionMaxHeight();
	void SetAutoCompletionMaxHeight(int height);
	//
	void SetMarginType(int marginIndex, int type);
	int GetMarginType(int marginIndex);
	void SetMarginWidth(int marginIndex, int widthPixels);
	int GetMarginWidth(int marginIndex);
	//
	void SetReadOnly(bool readOnly);
	bool GetReadOnly();
	__declspec( property( get=GetReadOnly, put=SetReadOnly) ) bool ReadOnly;
	//
	bool IsEvent(Win::Event& e, int notification);
	//_______________________________________________________________ Win::IPrint
	void Print(Win::Gdi& gdi, Win::PrintInfo pi);
private:
	const wchar_t * GetClassName(void){return L"SCINTILLA";}
	Sys::DLLibray dll;
protected:
};
#endif

#ifdef WIN_RICHEDIT_SUPPORT

//_____________________________________________________________________ RichEdit
class RichEdit : public Module //, public Win::IPrintDoc
{
public:
	RichEdit(void);
	virtual ~RichEdit(void);
		//SCF_ALL, SCF_SELECTION, SCF_WORD
	LRESULT SelectLine(int lineIndex);
	LRESULT SetCharFormat(CHARFORMAT2& cf, WPARAM scf);
	LRESULT GetCharFormat(CHARFORMAT2& cf, WPARAM scf);
	LRESULT SetParaFormat(PARAFORMAT2& pf);
	LRESULT GetParaFormat(PARAFORMAT2& pf);
	LRESULT SetBold(bool bBold, WPARAM scf);
	LRESULT SetItalic(bool bItalic, WPARAM scf);
	LRESULT SetUnderline(bool bUnderline, WPARAM scf);
	LRESULT SetFontSize(int fontSize, WPARAM scf);
	LRESULT SetTextColor(COLORREF rgb, WPARAM scf);
	LRESULT SetFontFamily(const wchar_t* fontFamily, WPARAM scf);
	LRESULT SetFont(const wchar_t* fontFamily, int fontSize, WPARAM scf);
	LRESULT SetParaFormat(PARAFORMAT& pf);
	LRESULT SetParaAligment(WORD aligment);
	LRESULT SetNumbering(bool bullets);
	void SetScrollPosition(const POINT* point);
	bool SetZoom(int numerator, int denominator);
	LRESULT SetEventMask(LPARAM eventMask);
	LRESULT GetEventMask();
	LRESULT SetBkGndColor(COLORREF color);
	void GetSelection(CHARRANGE& crSelection);
	void GetSelection(int& charStart, int& charEnd);
	LRESULT SetSelection(CHARRANGE& crSelection);
	LRESULT SetSelection(int charStart, int charEnd);
	LRESULT GetSelectionType();
	void ShowSelection(bool show);
	int GetSelectedText(wchar_t * buffer);
	int GetSelectedText(wstring& selectedText);
	int GetText(int charStart, int cpMax, wchar_t * buffer);
	int GetText(CHARRANGE& cr, wchar_t * buffer);
	int GetTextLength();
	CHARRANGE FindText(int charStart, int charEnd, wchar_t * stringToFind, bool matchCase, bool wholeWords, bool backwards);
	int GetLineFromChar(int charIndex);
	int GetCharIndex(int lineIndex);
	int GetLineLength(int lineIndex);
	int GetLineLengthFromChar(int charIndex);
	int GetLineCount();
	bool GetLineText(int lineIndex, wchar_t * buffer);
	bool GetLineText(int lineIndex, wchar_t * buffer, int bufferLength);
	bool AppendText(const wchar_t* text);
	bool AppendText(const wchar_t* text, CHARFORMAT2& cf);
	bool AppendText(const wchar_t* text, COLORREF color);
	bool AppendText(const wchar_t* text, const wchar_t* fontFamily, int fontSize);
	bool AppendText(const wchar_t* text, const wchar_t* fontFamily, int fontSize, COLORREF color);
	bool AppendText(const wstring& text);
	bool AppendText(const wstring& text, CHARFORMAT2& cf);
	bool AppendText(const wstring& text, COLORREF color);
	bool AppendText(const wstring& text, const wchar_t* fontFamily, int fontSize);
	bool AppendText(const wstring& text, const wchar_t* fontFamily, int fontSize, COLORREF color);
	void Delete();
	void ReplaceSelection(const wchar_t* replaceWithThis, bool canBeUndone);
	void SetFormatRange(int charStart, int charEnd, bool isBold, COLORREF color);
	void SetFormatRange(int charStart, int charEnd, bool isBold, COLORREF color, const wchar_t* fontFamily, int fontSize);
	void SetProtectedFormatRange(int charStart, int charEnd, bool isBold, COLORREF color, const wchar_t* fontFamily, int fontSize);
	bool IsEvent(Win::Event& e, int notification);
	BOOL Print(HWND hWndParent, const wchar_t* documentName);
	virtual bool Undo();
	virtual bool Redo();
	virtual void CopyToClipboard();
	virtual void PasteFromClipboard();
	virtual void ClearSelection();
	virtual void CutSelection();
	bool SetAutoUrlDetect(bool autoDetect);
	bool CanPaste();
	bool CanRedo();
	bool CanUndo();
	//
	__declspec( property( get=GetReadOnly, put=SetReadOnly) ) bool ReadOnly;
	void SetReadOnly(bool readOnly);
	bool GetReadOnly();
	void GetData(string& output);
	bool SaveToRtf(const wchar_t* filename);
protected:
	const wchar_t * GetClassName(void){return RICHEDIT_CLASS;}
private:
	HMODULE m_hModule;
	static DWORD CALLBACK StreamCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
};

//_____________________________________________________________________ CodeEditor
class CodeEditor : public Win::RichEdit
{
public:
	CodeEditor(void);
	~CodeEditor(void);
	void CommentOut();
	void Uncomment();
	void Setup(const wchar_t* fontFamily, int fontSize);
	void FormatTextRange(int charStart, int charEnd);
	void FormatTextLines(int lineStart, int lineEnd);
	void FormatAll();
	COLORREF keywordColor;
	COLORREF functionColor;
	COLORREF commentColor;
	COLORREF numberColor;
	COLORREF stringColor;
	set<wstring> keywords;
	set<wstring> functions;
	virtual void OnChange(Win::Event& e);
	virtual void OnProtected(Win::Event& e);
	virtual void OnMsgFilter(Win::Event& e);
	virtual bool Undo();
	virtual bool Redo();
	void PasteFromClipboard();
	virtual wstring GetText();
	virtual void SetText(const wstring text);
	__declspec( property( get=GetText, put=SetText) ) wstring Text;
private:
	enum FormatType 
	{
		FORMAT_CURRENT_SELECTION = 0, 
		FORMAT_ALL, 
		FORMAT_REPLACESEL, 
		FORMAT_CUT, 
		FORMAT_PASTE, 
		FORMAT_MOVE
	};
	struct SymbolColor 
	{
		COLORREF color;
		bool isBold;
	};
	bool isBlocking;
	FormatType formatType;
	CHARRANGE previousSelection;
	wchar_t _fontFamily[LF_FACESIZE];
	int _fontSize;
};
#endif

//_____________________________________________________________________ImageList
class ImageList // Indexes start at 0
{
public:
	ImageList(void);
	virtual ~ImageList(void);
	HIMAGELIST Create(int width, int height, UINT flags, int initialNumImages, int grow);
	HIMAGELIST Create(int width, int height, int initialNumImages);
	HIMAGELIST CreateFromBitmap(HINSTANCE hi, const wchar_t * bimap_id, int width, int grow, COLORREF mask, UINT uFlags);
	HIMAGELIST GetHImageList();
	int AddIcon(HICON hIcon);
	int AddIcon(HINSTANCE hInst, const wchar_t * idIcon);
	int AddIcon(HINSTANCE hInst, int idIcon);
	int AddSystemIcon(LPTSTR idIcon);
	int ReplaceIcon(int index, HICON hicon);
	int ReplaceIcon(int index, HINSTANCE hInst, const wchar_t * icon_id);
	int ReplaceIcon(int index, HINSTANCE hInst, int icon_id);
	BOOL Draw(int index, HDC hdc, int x, int y, int dx, int dy, UINT fStyle);
	int GetImageCount();
	BOOL RemoveAll();
	BOOL Remove(int index);
	operator HIMAGELIST();
	BOOL Destroy();
private:
	HIMAGELIST m_hIL;
	static bool bInit;
};

//_____________________________________________________________________ Spin
class Spin : public Win::Module
{
public:
	Spin(void);
	virtual ~Spin(void);
	LRESULT SetRange(int minimum, int maximum);
	LRESULT SetPosition(int position);
	int GetPosition();
	__declspec( property( get=GetPosition, put=SetPosition) ) int Position;
	LRESULT SetBuddy(HWND hEditBox);
	LRESULT SetBuddy(Win::Textbox& txbox);
	bool IsEvent(Win::Event& e, int notification);
protected:
	const wchar_t * GetClassName(void){return UPDOWN_CLASS;}
private:
	static bool bInit;
};

//_____________________________________________________________________ TreeView
class TreeView : public Win::Module
{
public:
	TreeView(void);
	virtual ~TreeView(void);
	BOOL SetItem(const TVITEMEX& tvitem);
	BOOL SetItemText(HTREEITEM hItem, const wchar_t* text);
	BOOL SetItemImage(HTREEITEM hItem, int imageIndex);
	BOOL SetItemData(HTREEITEM hItem, LPARAM data);
	HTREEITEM InsertItem(TVINSERTSTRUCT& tvinsert);
	HTREEITEM InserItem(HTREEITEM hParent, HTREEITEM hInsertAfter, const wchar_t *text);
	HTREEITEM InserItem(HTREEITEM hParent, HTREEITEM hInsertAfter, const wchar_t *text, int imageIndex);
	HTREEITEM InserItem(HTREEITEM hParent, HTREEITEM hInsertAfter, const wchar_t *text, int imageIndex, LPARAM data);
	BOOL GetItem(TVITEMEX& tvitem);
	BOOL GetItemText(HTREEITEM hItem, wchar_t* buffer, int bufferSize);
	BOOL GetItemImage(HTREEITEM hItem, int& imageIndex);
	BOOL GetItemData(HTREEITEM hItem, LPARAM& lParam);
	HTREEITEM GetNextItem(UINT flag, HTREEITEM hItem);
	BOOL SelectItem(DWORD flag, HTREEITEM hItem);
	HTREEITEM GetSelectedItem(HTREEITEM hItem);
	BOOL DeleteItem(HTREEITEM hItem);
	BOOL GetItemRect(RECT& rc, HTREEITEM hItem, bool onlyTextBox);
	int GetCount(void);
	int GetVisibleCount(void);
	HIMAGELIST SetImageList(Win::ImageList& imageList);
	bool IsEvent(Win::Event& e, int notification);
protected:
	const wchar_t * GetClassName(void){return WC_TREEVIEW;}
private:
	static bool bInit;
};

class ListView;
class ListViewItemCollection;
class ListViewItem;

//_____________________________________________________________________ ListViewSubItem
class ListViewSubItem
{
public:
	ListViewSubItem(void);
	virtual ~ListViewSubItem(void);
	int GetItemText(wchar_t* buffer, int buffer_length);
	wstring GetText();
	void SetText(const wstring& text);
	__declspec( property( get=GetText, put=SetText) ) wstring Text;
private:
	int index;
	int sub_index;
	HWND listControl;
	friend class Win::ListViewItem;
};

//_____________________________________________________________________ ListViewItem
class ListViewItem
{
public:
	ListViewItem(void);
	virtual ~ListViewItem(void);
	BOOL GetText(int subItemIndex, wchar_t* buffer, int bufferSize);
	LRESULT SetText(int subItemIndex, const wchar_t* text);
	wstring GetText(int subItemIndex);
	void SetText(int subItemIndex, const wstring& text);
	//
	wstring GetText();
	void SetText(const wstring& text);
	__declspec( property( get=GetText, put=SetText) ) wstring Text;
	//
	UINT GetState(UINT mask);
	LRESULT SetState(UINT state, UINT stateMask);
	//
	bool GetChecked();
	void SetChecked(bool isChecked);
	__declspec( property( get=GetChecked, put=SetChecked ) ) bool Checked;
	//
	LPARAM GetData();
	void SetData(LPARAM data);
	__declspec( property( get=GetData, put=SetData ) ) LPARAM Data;
	//
	int GetImageIndex();
	void SetImageIndex(int imageIndex);
	__declspec( property( get=GetImageIndex, put=SetImageIndex ) ) int ImageIndex;
	//
	void SetDropHiLited(bool on);
	__declspec( property( put=SetDropHiLited ) ) bool DropHiLited;
	//
	bool Delete();
	Win::ListViewSubItem& operator[](long index);
	//
	bool GetSelected();
	void SetSelected(bool selected);
	__declspec( property( get=GetSelected, put=SetSelected) ) bool Selected;
	//
	bool GetBoundsRect(long index, RECT& output);
	bool GetIconRect(long index, RECT& output);
	bool GetLabelRect(long index, RECT& output);
	bool GetSelectBoundsRect(long index, RECT& output);
private:
	Win::ListViewSubItem _subItem;
	int index;
	HWND listControl;
	friend class Win::ListViewItemCollection;
};

//_____________________________________________________________________ ListViewItemCollection
class ListViewItemCollection
{
public:
	ListViewItemCollection(void);
	virtual ~ListViewItemCollection(void);
	LRESULT DeleteAll();
	LRESULT DeleteItem(int index);
	int GetCount();
	__declspec( property( get=GetCount ) ) int Count;
	int GetIndex(const wchar_t* text) ;// Returns the index of the item or -1 if not found
	//
	LRESULT Add(LVITEM& lvi);// Use module::SetRedraw(false) before inserting a lot of items
	LRESULT Add(int index, int imageIndex, const wchar_t* text);
	LRESULT Add(int index, const wchar_t* text, int imageIndex, LPARAM data);
	LRESULT Add(int index, const wchar_t* text);
	LRESULT Add(int index, const wchar_t* text, LPARAM data);
	//
	LRESULT Add(int index, int imageIndex, const wstring& text);
	LRESULT Add(int index, const wstring& text, int imageIndex, LPARAM data);
	LRESULT Add(int index, const wstring& text);
	LRESULT Add(int index, const wstring& text, LPARAM data);
	//
	LRESULT Add(int index, const wchar_t* text, int imageIndex, LPARAM data, int group_id);
	LRESULT Add(int index, const wstring& text, int imageIndex, LPARAM data, int group_id);
	//
	BOOL Set(LVITEM& lvitem);
	BOOL Get(LVITEM& lvitem);
	//
	Win::ListViewItem& operator[](long index);
private:
	Win::ListViewItem _item;
	void SetParent(Win::IParent* iparent);
	Win::IParent* iparent;
	friend class Win::ListView;
};

//_____________________________________________________________________ ListViewColumn
class ListViewColumn
{
public:
	ListViewColumn(void);
	virtual ~ListViewColumn(void);

	//LVCFMT_LEFT, LVCFMT_CENTER, LVCFMT_RIGHT
	LRESULT Add(LVCOLUMN& lvcolumn, int index);
	LRESULT Add(int index, int format, int width, const wchar_t* text);
	LRESULT Add(int index, int format, int width, const wstring& text);
	bool DeleteAll(void);
	LRESULT Set(int index, LPLVCOLUMN pLvc);// Indexes start at 0
	LRESULT GetText(int index, wchar_t* buffer, int buffer_size);
	LRESULT SetWidth(int index, int width);
	int GetWidth(int index);
	int GetFormat(int index);
	int GetCount();
	LRESULT Delete(int index);
	LRESULT SetText(int index, const wchar_t* text);// Indexes start at 0
private:
	void SetParent(Win::IParent* iparent);
	Win::IParent* iparent;
	friend class Win::ListView;
};

//_____________________________________________________________________ LVDropInfo
struct LVDropInfo
{
	int sourceItemIndex;
	int targetItemIndex;
};

//_____________________________________________________________________ListView
class ListView : public Win::Module, public Sql::ISqlNumerator, public Win::IPrint, public Sys::IError
{
public:
	ListView(void);
	virtual ~ListView(void);
	LRESULT SetExtStyle(DWORD dwExMask, DWORD dwExStyle);
	LRESULT GetExtStyle();
	void SetView(int view);
	int GetView();
	int GetSelectedCount();
	int GetNextIndex(int index, DWORD flags); // Use this for multiple item selection
	int GetNextSelectedIndex(int index); // Use this for multiple item selection:  index should be -1 the first time, next calls index must be the previous return value
	int GetSelectedIndex(); // Use this for single item selection
	bool IsEvent(Win::Event& e, int notification);
	bool CopyLatexToCliboard(bool isNumber);
	bool EnableGroupView(bool groupView);
	LRESULT InsertGroup(int index, int groupId, LPWSTR text, UINT align);
	LRESULT InsertItemIntoGroup(int index, wchar_t* text, int imageIndex, int groupId);
	LRESULT InsertItemIntoGroup(int index, wchar_t* text, int imageIndex, LPARAM userData, int groupId);
	LRESULT InsertItemIntoGroup(int index, wchar_t* text, int groupId);
	LRESULT InsertItemIntoGroup(int index, wchar_t* text, LPARAM userData, int groupId);
	void Enumerate(wchar_t** data, int colCount, int rowIndex);
	LRESULT SetSelected(int nItemIndex, bool selected);// Indexes start at 0. Use nItemIndex=-1 to affect all rows
	BOOL Scroll(int deltaX, int deltaY);
	BOOL Scroll();
	BOOL RedrawItems(int indexIni, int indexEnd);
	HWND GetHeaderControl();
	BOOL GetHeaderText(int index, wchar_t* pszBuffer, int nBufferSize);
	LRESULT SetBkColor_(COLORREF rgb);
	LRESULT SetImageList(HIMAGELIST hil, bool bSmall);
	bool SaveToFile(const wchar_t* filename, const wchar_t* colIni, const wchar_t* colEnd, const wchar_t* rowIni, const wchar_t* rowEnd, const wchar_t* docIni, const wchar_t* docEnd);
	bool SaveToFile(HANDLE hFile, const wchar_t* colIni, const wchar_t* colEnd, const wchar_t* rowIni, const wchar_t* rowEnd, const wchar_t* headIni, const wchar_t* headEnd, bool includeHeader);
	bool SaveToFile(const wchar_t* filename);
	bool SaveToFile(const wchar_t* filename, const char* colIni, const char* colEnd, const char* rowIni, const char* rowEnd, const char* docIni, const char* docEnd);
	bool SaveToFile(HANDLE hFile, const char* colIni, const char* colEnd, const char* rowIni, const char* rowEnd, const char* headIni, const char* headEnd, bool includeHeader);
	bool SaveToFileA(const wchar_t* filename);
	bool SaveWebFile(const wchar_t* filename);
	bool SaveLatexToFile(const wchar_t* filename);
	bool ExportToMsExcel(const wchar_t* filename);
	//____________________________________________________ Win::IPrint
	void Print(Win::Gdi& gdi, Win::PrintInfo pi);
	//
	bool CopyToClipboard();
	//
	Win::ListViewColumn& GetColumns();
	__declspec( property( get=GetColumns) ) Win::ListViewColumn& Cols;
	//
	/*__declspec(property(*/ Win::ListViewItemCollection Items;
	//
	int GetHitTestItemIndex(LVHITTESTINFO& hitTestInfo); // returns the item index or -1
	void BeginDrag(Win::Event& e); // Call this on listView_beginDrag
	void Drag(Win::Event& e, Win::ListView& listViewTarget); // Call this on Window_MouseMove using the input list view
	LVDropInfo Drop(Win::Event& e, Win::ListView& listViewTarget);  // Call this on Window_LButtonUp using the input list view, use return LVDropInfo
	//
	bool GetSubItemRect(int itemIndex, int subItemIndex, RECT& output);
	bool GetSubItemRect(int itemIndex, int subItemIndex, int flags, RECT& output); // flags: LVIR_BOUNDS, LVIR_ICON, LVIR_LABEL 
	//_____________________________________________________ Sys::IError
	void ReportError(bool error, wchar_t* description);
protected:
	Win::ListViewColumn _cols;
	
	const wchar_t * GetClassName(void){return WC_LISTVIEW;}
private:
	static bool bInit;
	bool isDragging;
	//HIMAGELIST imageList;
	int dragItemIndex;
	Sys::Cursor cursor;
};

//_____________________________________________________________________ Slider
class Slider : public Win::Module
{
public:
	Slider(void);
	virtual ~Slider(void);
	bool IsEvent(Win::Event& e, int notification);
	void SetRange(int minimum, int maximum);
	//
	void SetPosition(int position);
	int GetPosition();
	__declspec( property( get=GetPosition, put=SetPosition) ) int Position;
	//
	void SetMinimumPosition(int position);
	int GetMinimumPosition();
	__declspec( property( get=GetMinimumPosition, put=SetMinimumPosition) ) int MinimumPosition;
	//
	void SetMaximumPosition(int position);
	int GetMaximumPosition();
	__declspec( property( get=GetMaximumPosition, put=SetMaximumPosition) ) int MaximumPosition;
	//
	int HasPositionChanged(); // If the position has NOT changed, it returns -1.  If the position has changed, the function returns the new position
protected:
	const wchar_t * GetClassName(void){return TRACKBAR_CLASS;}
private:
	int _position;
	static bool bInit;
};

//_____________________________________________________________________Toolbar
class Toolbar : public Win::Module
{
public:
	Toolbar(void);
	virtual ~Toolbar(void);
	LRESULT SetImageList(Win::ImageList& imageList);
	LRESULT SetDisabledImageList(Win::ImageList& imageList);
	LRESULT SetBitmapSize(UINT width, UINT height);
	LRESULT SetButtonSize(UINT width, UINT height);
	LRESULT AddBitmap(HINSTANCE hInst, UINT idBitmap, UINT_PTR nImages);
	LRESULT AddStdBitmap(bool bLarge);
	LRESULT AddViewBitmap(bool bLarge);
	LRESULT LoadStdImages(bool bLarge);
	LRESULT LoadViewImages(bool bLarge);
	LRESULT LoadHistoryImages(bool bLarge);
	LRESULT AddButtons(LPCTBBUTTON lpButtons, UINT nButtons);
	LRESULT AddString(const wchar_t * szText);
	void AutoSize();
	UINT GetButtonCount();
	UINT GetButtonState(int button_id);
	BOOL Customize(); // Requires OnNotify(...) 
	bool CheckButton(int button_id, bool checked);
	bool PressButton(int button_id, bool pressed);
	bool EnableButton(int button_id, bool enabled);
	bool HideButton(int button_id, bool hidden);
	BOOL DeleteButton(int index);
	BOOL GetButton(int index, LPTBBUTTON pButton);
	LRESULT GetButtonSize();
	BOOL GetItemRect(int index, LPRECT pRect);
	BOOL GetMaxSize(LPSIZE pSize);
	BOOL InsertButton(int index, LPTBBUTTON pButton);
	bool IsButtonChecked(int button_id);
	bool IsButtonPressed(int button_id);
	bool IsButtonEnabled(int button_id);
	bool IsButtonHidden(int button_id);
	void SetMaxTextRows(int count);
	void SetButtonWidth(int mimimum, int maximum);
	bool IsEvent(Win::Event& e, int notification);
	Win::ImageList imageList;
private:
	static bool bInit;
protected:
	const wchar_t * GetClassName(void){return TOOLBARCLASSNAME;}
};

//_____________________________________________________________________ Tooltip
class Tooltip : public Win::Module
{
public:
	Tooltip(void);
	virtual ~Tooltip(void);
	HWND Create(HWND parent);
	HWND Create(DWORD dwExStyle, const wchar_t* pszWindowName, DWORD dwStyle, int x, int y, int width, int height, HWND hParent, int id);
	LRESULT AddTool(Win::Module& tool, wchar_t* tip);
	LRESULT AddTool(HWND hWndTool, UINT tool_id, wchar_t* tip);
	LRESULT DelTool(Win::Module& control);
	LRESULT DelTool(HWND hWndTool, UINT tool_id);
protected:
	const wchar_t * GetClassName(void){return TOOLTIPS_CLASS;}
private:
};

class TabItemCollection;
class Tab;

//_____________________________________________________________________ TabItem
class TabItem
{
public:
	TabItem(void);
	virtual ~TabItem(void);
	//
	wstring GetText();
	void SetText(const wstring& text);
	__declspec( property( get=GetText, put=SetText) ) wstring Text;
	//
	LPARAM GetData();
	void SetData(LPARAM data);
	__declspec( property( get=GetData, put=SetData ) ) LPARAM Data;
	//
	int GetImageIndex();
	void SetImageIndex(int imageIndex);
	__declspec( property( get=GetImageIndex, put=SetImageIndex ) ) int ImageIndex;
	//
	BOOL Delete();
	bool GetItemRect(int index, RECT& rect);
private:
	int index;
	HWND tabControl;
	friend class Win::TabItemCollection;
};

//_____________________________________________________________________ TabItemCollection
class TabItemCollection
{
public:
	TabItemCollection(void);
	virtual ~TabItemCollection(void);
	LRESULT DeleteAll();
	int GetCount();
	__declspec( property( get=GetCount ) ) int Count;
	int GetIndex(const wchar_t* text) ;// Returns the index of the item or -1 if not found
	//
	int Add(int index, TCITEM& item);// Use module::SetRedraw(false) before inserting a lot of items
	int Add(int index, int imageIndex, const wchar_t* text);
	int Add(int index, const wchar_t* text, int imageIndex, LPARAM data);
	int Add(int index, const wchar_t* text);
	int Add(int index, const wchar_t* text, LPARAM data);
	//
	int Add(int index, int imageIndex, const wstring& text);
	int Add(int index, const wstring& text, int imageIndex, LPARAM data);
	int Add(int index, const wstring& text);
	int Add(int index, const wstring& text, LPARAM data);
	//
	bool Set(TCITEM& item);
	bool Get(TCITEM& item);
	//
	Win::TabItem& operator[](long index);
private:
	Win::TabItem _item;
	void SetParent(Win::IParent* iparent);
	Win::IParent* iparent;
	friend class Win::Tab;
};

//_____________________________________________________________________ Tab
class Tab : public Win::Module
{
public:
	Tab(void);
	virtual ~Tab(void);
	int SetSelected(int index);
	int GetSelectedIndex();
	__declspec( property( get=GetSelectedIndex, put=SetSelected ) ) int SelectedIndex;
	//
	void SetSelectedByData(LPARAM data);
	LPARAM GetSelectedData();
	__declspec( property ( get=GetSelectedData, put=SetSelectedByData ) ) LPARAM SelectedData;
	//
	LRESULT HighLightItem(int index, bool bIsHighLight);
	HIMAGELIST SetImageList(Win::ImageList& imageList);
	bool IsEvent(Win::Event& e, int notification);
	Win::TabItemCollection Items;
protected:
	const wchar_t * GetClassName(void){return WC_TABCONTROL;}
private:
	static bool bInit;
};

//_____________________________________________________________________ProgressBar
class ProgressBar : public Win::Module
{
public:
	ProgressBar(void);
	virtual ~ProgressBar(void);

	int SetStep(int stepSize);
	int SetRange(int minimum, int maximum);
	int StepIt();
	COLORREF SetBarcolor(COLORREF rgb);
	COLORREF SetBkcolor(COLORREF rgb);
	//
	void SetMarquee(bool on, int milliseconds);
	//
	void SetPosition(int position);
	int GetPosition();
	__declspec( property( get=GetPosition, put=SetPosition ) ) int Position;
protected:
	const wchar_t * GetClassName(void){return PROGRESS_CLASS;}
private:
	static bool bInit;
};

//_____________________________________________________________________ StatusBar
class StatusBar : public Win::Module
{
public:
	StatusBar(void);
	virtual ~StatusBar(void);
	LRESULT SetPartCount(int nCount, int* nPartWidth);
	LRESULT SetPartText(int index, const wchar_t * szText) 
		{return ::SendMessage(hWnd, SB_SETTEXT, (WPARAM)index, (LPARAM)szText);}
	BOOL SetPartIcon(INT index, HICON hIcon);
	BOOL SetPartIcon(INT index, UINT resourceID, HINSTANCE hInst);
	COLORREF SetBackcolor(COLORREF rgb);
	int GetPartTextLength(int index);
	LRESULT GetPartText(int index, wchar_t* buffer);
	void SetMinHeight(int height);
protected:
	const wchar_t * GetClassName(void){return STATUSCLASSNAME;}
private:
	static bool bInit;
};

//_____________________________________________________________________ Rebar
class Rebar : public Win::Module
{
public:
	Rebar(void);
	virtual ~Rebar(void);
	UINT GetBarHeight();
	UINT GetBandCount();
	BOOL InsertBand(LPREBARBANDINFO rbBand);
	BOOL InsertBand(int index, LPREBARBANDINFO rbBand);
	BOOL GetBandInfo(UINT index, LPREBARBANDINFO p);
	BOOL SetBandInfo(UINT index, LPREBARBANDINFO p);
	BOOL SetBarInfo(HIMAGELIST hImageList);
protected:
	const wchar_t * GetClassName(void){return REBARCLASSNAME;}
private:
	static bool bInit;
};

class DropDownImageList;
class ListImageCollection;
//_____________________________________________________________________ ListImage
class ListImage
{
public:
	ListImage(void);
	virtual ~ListImage(void);
	//
	DWORD GetData();
	void SetData(DWORD data);
	__declspec( property( get=GetData, put=SetData ) ) DWORD Data;
	//
	wstring GetText();
	void GetText(wchar_t* text);
	__declspec( property( get=GetText ) ) wstring Text;
	//
	int GetTextLength();
	__declspec( property( get=GetTextLength ) ) int TextLength;
	//
	int Delete();
private:
	bool isListBox;
	int index;
	HWND listControl;
	friend class Win::ListImageCollection;
};

//_____________________________________________________________________ ListImageCollection
class ListImageCollection
{
public:
	ListImageCollection(void);
	virtual ~ListImageCollection(void);
	void DeleteAll();
	bool Add(COMBOBOXEXITEM cbei);
	bool Add(int index, int indent, int image, int imageSelected, const wchar_t* text);
	bool Add(int index, int indent, int image, int imageSelected, const wchar_t* text, LPARAM data);
	bool Add(int index, int indent, int image, int imageSelected, const wstring& text);
	bool Add(int index, int indent, int image, int imageSelected, const wstring& text, LPARAM data);
	__declspec( property( get=GetCount ) ) int Count;
	int GetCount();
	int GetIndex(wchar_t* text);
	Win::ListImage& operator[](long index);
private:
	bool used_data;
	LPARAM _data;
	Win::ListImage _item;
	void SetParent(Win::IParent* iparent);
	Win::IParent* iparent;
	friend class Win::DropDownImageList;
};

//_____________________________________________________________________ DropDownImageList
class DropDownImageList : public Win::Module
{
public:
	DropDownImageList(void);
	virtual ~DropDownImageList(void);
	//
	LRESULT SetSelected(int index);
	int GetSelectedIndex();
	__declspec( property( get=GetSelectedIndex, put=SetSelected ) ) int SelectedIndex;
	//
	void SetSelectedByData(DWORD data);
	DWORD GetSelectedData();
	__declspec( property ( get=GetSelectedData, put=SetSelectedByData ) ) DWORD SelectedData;
	//
	int FindString(LPCSTR pszString);
	//
	void SetSelectedByData(const wchar_t* data);
	//
	void SetImageList(Win::ImageList& imageList, HWND parent);
	bool IsEvent(Win::Event& e, int notification);
	LRESULT SearchSelect(const wchar_t* searchString);
	//
	ListImageCollection& GetItems();
	__declspec( property ( get=GetItems) ) ListImageCollection& Items;
	//
	LRESULT ShowDropDown(bool show);
protected:
	Win::ListImageCollection _items;
	const wchar_t * GetClassName(void){return WC_COMBOBOXEX;}
private:
	static bool bInit;
};

//_____________________________________________________________________ Tray
class Tray
{
public:
	Tray(void);
	virtual ~Tray(void);
	void Create(HINSTANCE hInst, HWND hWndParent, UINT id);
	BOOL Add(UINT idIcon, const wchar_t* szTip);
	BOOL ModifyTip(const wchar_t* szTip);
	BOOL ModifyIcon(UINT idIcon);
	BOOL Delete();
	UINT GetId()
		{return m_id;}
	bool IsTrayMessage(UINT uMsg, WPARAM wParam)
	{
		return (uMsg == m_WinMessage && wParam==m_id);
	}
private:
	HWND m_hWndParent;
	UINT m_id;
	HINSTANCE m_hInst;
	bool m_bAdd;
	UINT m_WinMessage;
};

//____________________________________________________________________ ScrollBar
class ScrollBar : public Module
{
public:
	ScrollBar();
	~ScrollBar();
	int SetScrollInfo(LPCSCROLLINFO lpsi,BOOL fRedraw);
	int GetScrollInfo(LPSCROLLINFO lpsi);
	int SetRange(int nMin, int nMax);
	int GetRange(int& nMin, int& nMax);
	int SetPosition(int nPos);
	int GetPosition(int& nPos);
	int SetPage(int page);
	int GetPage(int& page);
	int GetTrackPosition(int& nPos);
	int GetNewPosition(Win::Event& e); // Call this from Window_HScroll or Window_VScroll
	bool IsEvent(Win::Event& e, int notification);
protected:
	const wchar_t * GetClassName(void){return WC_SCROLLBAR;}
	SCROLLINFO si;
};

//_____________________________________________________________________ ITable
class ITable
{
public:
	struct TableInfo
	{
		HWND hWnd;
		LPARAM lParam;
		int row;
		int col;
		RECT cell;
	};
	struct Info
	{
		int rowCount;
		int columnCount;
	};
	struct PaintEvent
	{
		Win::Gdi * gdi;
		RECT cell;
		int row;
		int col;
		bool isSelected;
	};
	virtual void OnTablePaint(int paintEvent, Win::Gdi& gdi, RECT& cell, int row, int col, bool isSelected)=0; //It is called on painting the table
	virtual void OnTableRequestInfo(Win::ITable::Info& info)=0; //It returns the requested information
};

//_____________________________________________________________________ Metafile
class Metafile
{
public:
	Metafile(void);
	virtual ~Metafile(void);
	HDC Create();
	bool Create(HENHMETAFILE hEMF);
	HDC CreateToFile(HDC hdcRef, RECT* rect, const wchar_t* filename, const wchar_t* description);
	HDC CreateToFile(HWND hWnd, const wchar_t* filename, int width, int height);
	bool CreateFromFile(const wchar_t* filename);
	SIZE GetSizeInDeviceUnits(void);
	SIZE GetSizeIn0_01mm(void);
	HENHMETAFILE Close();
	void Delete();
	UINT GetHeader(ENHMETAHEADER& header);
	BOOL Enumerate(HDC hdc, const RECT* pRect);
	static int CALLBACK EmfProc(HDC hdc, HANDLETABLE* phTable, const ENHMETARECORD* pEmfRecord, int nHandles, LPARAM lData);
	HENHMETAFILE GetHandle();
	HDC GetHDC();
private:
	HENHMETAFILE m_hEMF;
	HMETAFILE m_hMF;
	HDC m_hdcEMF;
};

//_____________________________________________________________________ Box
//class Box
//{
//public:
//	virtual ~Box(void)
//	{
//	}
//	Box(void)
//	{
//		ZeroMemory(&m_rect, sizeof(RECT));
//		m_bClipping = true;
//		m_bVisible = true;
//	};
//	void SetClipping(bool bClipping)
//	{
//		m_bClipping = bClipping;
//	}
//	void SetSize(RECT& rect)
//	{
//		m_rect = rect;
//	}
//	void SetVisible(bool bVisible)
//	{
//		m_bVisible = bVisible;
//	}
//	void SetSize(int width, int height)
//	{
//		m_rect.top = 0;
//		m_rect.left = 0;
//		m_rect.right = width;
//		m_rect.bottom = height;
//	}
//	void SetSize_(int top, int left, int right, int bottom)
//	{
//		m_rect.top = top;
//		m_rect.left = left;
//		m_rect.right = right;
//		m_rect.bottom = bottom;
//	}
//	void SetSize(int left, int top, int width, int height)
//	{
//		m_rect.top = top;
//		m_rect.left = left;
//		m_rect.right = left+width;
//		m_rect.bottom = top+height;
//	}
//	void Window_Paint(Win::Gdi& gdi)
//	{
//		return OnPaint(gdi, gdi.GetPaintStruct());
//	}
//	void Window_Paint(HDC& hdc, PAINTSTRUCT& ps)
//	{
//		if (m_bVisible == false) return TRUE;
//		RECT rect;
//
//		::IntersectRect(&rect, &ps.rcPaint, &this->m_rect);
//		if (!::IsRectEmpty(&rect))
//		{
//			RECT rectClip;
//			if (this->m_bClipping)
//			{
//				GetClipBox(hdc, &rectClip);
//				SelectClipRgn(hdc, CreateRectRgnIndirect(&m_rect));
//			}
//			this->Paint(hdc, ps);
//			if (this->m_bClipping)
//			{
//				SelectClipRgn(hdc, CreateRectRgnIndirect(&rectClip));
//			}
//		}
//		return TRUE;
//	}
//
//protected:
//	virtual void Paint(HDC& hdc, PAINTSTRUCT& ps) = 0;
//	RECT m_rect;
//
//private:
//	bool m_bClipping;
//	bool m_bVisible;
//};
//
////_____________________________________________________________________ BoxText
//class BoxText : public Win::Box
//{
//public:
//	virtual ~BoxText(void)
//	{
//		if (m_psz) delete [] m_psz;
//	}
//	BoxText(void)
//	{
//		m_psz = NULL;
//		m_n = 0;
//	}
//	void SetText(wchar_t* psz)
//	{
//		if (m_psz) delete [] m_psz;
//		m_psz = NULL;
//		if (psz)
//		{
//			m_n = lstrlen(psz);
//			m_psz = new wchar_t[m_n+1];
//			lstrcpy(m_psz, psz);
//		}
//	}
//
//protected:
//	void Paint(HDC& hdc, PAINTSTRUCT& ps)
//	{
//		TextOut(hdc, m_rect.left, m_rect.top, m_psz, m_n);
//	}
//	wchar_t* m_psz;
//	int m_n;
//};

//_____________________________________________________________________ DIBitmapP
// Packed Device Independent Bitmap
class DIBitmapP
{
public:
	DIBitmapP(void);
	virtual ~DIBitmapP(void);
	bool CreateFromFile(const wchar_t* pszFileName);
	bool Create(int width, int height, int nBitsPerPixel, int nColors);
	bool CreateFlip(Win::DIBitmapP& dib, bool bHorizontal);
	bool CreateRotate(Win::DIBitmapP& dib);
	bool SaveToFile(const wchar_t* szFileName);
	bool ExtractPixels(vector<valarray<COLORREF> >& output);
	bool ExtractGrayPixels(MATRIX& output);
	bool ExtractColorPixels(MATRIX& outRed, MATRIX& outGreen, MATRIX& outBlue);
	bool IsValid();
	HBITMAP GetHBITMAP() {return m_hDIB;}
	int GetWidth();
	int GetHeight();
	int GetNumBitsPerPixel();
	int GetColorTableCount();
	int GetRowLength();
	DWORD GetMask(int n);
	DWORD GetRShift(int n);
	DWORD GetLShift(int n);
	int GetCompression();
	inline bool IsCompressed();
	DWORD GetTotalSize();
	BOOL GetTableColor(int nIndex, RGBQUAD* pRGB);
	BOOL SetTableColor(int nIndex, const RGBQUAD* pRGB);
	const BITMAPINFOHEADER* GetInfoHeader();
	void* GetBits();
	BOOL GetPixelColor(int x, int y, RGBQUAD* pRgb);
	BOOL SetPixelColor (int x, int y, RGBQUAD* pRgb);
	PBYTE GetPixelPtr1(int x, int y)
	{
		return (this->m_ppRow[y]) + (x >> 3);
	}
		
	PBYTE GetPixelPtr4(int x, int y)
	{
		return (this->m_ppRow[y]) + (x >> 1);
	}

	PBYTE GetPixelPtr8(int x, int y)
	{
		return this->m_ppRow[y]+ (x);
	}

	WORD* GetPixelPtr16(int x, int y)
	{
		return (WORD *) (this->m_ppRow[y] +  2*x );
	}

	RGBTRIPLE* GetPixelPtr24(int x, int y)
	{
		return (RGBTRIPLE *) (this->m_ppRow[y] +  3*x  );
	}

	DWORD* GetPixelPtr32(int x, int y) 
	{
		return (DWORD *) (this->m_ppRow[y] +  4*x  );
	}

	inline BYTE GetPixel1(int x, int y);
	inline BYTE GetPixel4(int x, int y);
	inline BYTE GetPixel8(int x, int y);
	inline WORD GetPixel16(int x, int y);
	inline RGBTRIPLE GetPixel24(int x, int y);
	COLORREF GetPixelRgb24(int x, int y);
	inline DWORD GetPixel32(int x, int y);
	void SetPixel1(int x, int y, BYTE p);
	void SetPixel4(int x, int y, BYTE p);
	void SetPixel8(int x, int y, BYTE p);
	void SetPixel16(int x, int y, WORD p);
	void SetPixel24(int x, int y, RGBTRIPLE p);
	void SetPixel32(int x, int y, DWORD p);
	//
	PBYTE CopyToPackedDib(bool bUseGlobalMemory);
	BOOL CopyFromPackedDib(BITMAPINFO * pPackedDib); // This is a constructor (create)
	PBYTE CreateBitmapInfo(); // To be used only by gdi::DDitmap
private:
	bool m_bIsValid;
	 PBYTE * m_ppRow;
	 size_t m_nRow;
     int m_nSignature;
     HBITMAP m_hDDB;
	 HBITMAP m_hDIB;
     BYTE* m_pBits;
	 PBYTE m_pBmInfo;
     DIBSECTION m_ds;
     int m_nRShift[3];
     int m_nLShift[3];
	 //
	 void Constructor();
	 void Destructor();
	 //
	 DWORD GetMaskSize();
	 DWORD GetColorSize();
	 DWORD GetInfoHeaderSize();
	 DWORD GetInfoSize();
	 DWORD GetBitsSize();
	 //
	 BYTE* GetPixelPtr(int x, int y);
	inline DWORD GetPixel (int x, int y);
	BOOL SetPixel(int x, int y, DWORD dw);
	//
	static int MaskToRShift (DWORD dwMask);
	static int MaskToLShift (DWORD dwMask);
	//
	bool CreateFromInfo(BITMAPINFO* pBmInfo);
	bool CopyRotate(Win::DIBitmapP& dib, bool bRotate);
	friend class Gdi;
};

//_____________________________________________________________________ DIBitmap
class DIBitmap
{
public:
	DIBitmap(void);
	virtual ~DIBitmap(void);
	BOOL DIBitmap::CreateFromFile(const wchar_t* filename);
	int GetWidth();
	int GetHeight();
	BOOL SaveToFile(const wchar_t* filename);
	const BITMAPFILEHEADER* GetFileHeader(){return pBmFH;}
	const BITMAPINFO* GetFileInfo()
		{return pBmInfo;}
	const BYTE* GetBits()
		{return pBits;}
private:
	BYTE* pData;
	void Destructor();
	BITMAPFILEHEADER* pBmFH;
	BITMAPINFO* pBmInfo;
	BYTE* pBits;
	int nWidth;
	int nHeight;
	friend class Gdi;
};

//_____________________________________________________________________ DDBitmap
class DDBitmap
{
public:
	DDBitmap(void);
	virtual ~DDBitmap(void);
	HBITMAP CreateFromResource(HINSTANCE hInst, int bitmap_id);
	HBITMAP CreateFromFile(HINSTANCE hInst, const wchar_t * szFileName);
	HBITMAP CreateWinPredefined(UINT idOBM);
	HBITMAP CreateFromBits(int width, int height, int nPlanes, int nBitCount, DWORD* bits);
	HBITMAP CreateFromDesktop();
	HBITMAP CreateFromWindow(HWND hWnd, bool clientEdge);
	HBITMAP CreateFromDIB(HDC hdc, Win::DIBitmap& dib);
	HBITMAP CreateFromDIB(HWND hWnd, Win::DIBitmap& dib);
	HBITMAP CreateFromDIB(HDC hdc, Win::DIBitmapP& dib);
	HBITMAP CreateFromDIB(HWND hWnd, Win::DIBitmapP& dib);
	void Create(HBITMAP hBitmap);
	HDC CreateCompatible(HDC hdc, int width, int height);
	HDC CreateCompatible(HWND hWnd, int width, int height);
	HDC CreateCompatibleFromBits(HDC hdc, int width, int height, DWORD* bits);
	HDC CreateCompatibleFromBits(HWND hWnd, int width, int height, DWORD* bits);
	int GetWidth();
	int GetHeight();
	HBITMAP GetHBITMAP(){return hBitmap;}
	HBITMAP Strech(int scaleX, int scaleY);
	DDBitmap(const DDBitmap& init); // Copy constructor
	DDBitmap& operator =(const DDBitmap&init);
	HDC GetBitmapDC();
	void DeleteMemDC();
private:
	HBITMAP hBitmap;
	void Destructor();
	BITMAP bitmap;
	HDC hdcMem;
	void Copy(const DDBitmap& init);
	friend class Gdi;
};

//_____________________________________________________________________ ScrollControl
class ScrollControl : public Win::Window, Win::ITable
{
public:
	ScrollControl(void);
	virtual ~ScrollControl(void);
	//
	COLORREF GetBackColor();
	virtual void SetBackColor(COLORREF color);
	__declspec( property( get=GetBackColor, put=SetBackColor ) ) COLORREF BackColor;
	//
	COLORREF GetHdrBackColor();
	virtual void SetHdrBackColor(COLORREF color);
	__declspec( property( get=GetHdrBackColor, put=SetHdrBackColor ) ) COLORREF HdrBackColor;
	//
	COLORREF GetTextColor();
	virtual void SetTextColor(COLORREF color);
	__declspec( property( get=GetTextColor, put=SetTextColor ) ) COLORREF TextColor;
	//
	COLORREF GetLineColor();
	virtual void SetLineColor(COLORREF color);
	__declspec( property( get=GetLineColor, put=SetLineColor ) ) COLORREF LineColor;
	//
	int GetRowHeight();
	void SetRowHeight(int rowHeight);
	__declspec( property( get=GetRowHeight, put=SetRowHeight ) ) int RowHeight;
	//
	int GetColumnWidth();
	void SetColumnWidth(int columnWidth);
	__declspec( property( get=GetColumnWidth, put=SetColumnWidth ) ) int ColumnWidth;
	//
	virtual void SetFont(Win::Gdi::Font& font);
	__declspec( property( put=SetFont) ) Win::Gdi::Font& Font;
	//
	void RefreshCell(int row, int col);
	void SetSelectedCell(int row, int col);
	//
	bool SetSelectedCol(int col);
	int GetSelectedCol(); // if the value is negative, the full row is selected and the column index begins at -1
	__declspec( property( get=GetSelectedCol, put= SetSelectedCol ) ) int SelectedCol;
	//
	bool SetSelectedRow(int row);
	int GetSelectedRow();
	__declspec( property( get=GetSelectedRow, put=SetSelectedRow ) ) int SelectedRow;
	//
	void SetSelectFullRow(bool selectFullRow);
	bool GetSelectFullRow();
	__declspec( property( get=GetSelectFullRow, put=SetSelectFullRow ) ) bool SelectFullRow;
	//
	void SetShowVerticalGrid(bool showGrid);
	bool GetShowVerticalGrid();
	__declspec( property( get=GetShowVerticalGrid, put=SetShowVerticalGrid ) ) bool ShowVerticalGrid;
	//
	void SetShowHorizontalGrid(bool showGrid);
	bool GetShowHorizontalGrid();
	__declspec( property( get=GetShowHorizontalGrid, put=SetShowHorizontalGrid ) ) bool ShowHorizontalGrid;
	//
	void RemoveSelection();
	void GetPaintInfo(const PAINTSTRUCT& ps, int& posX, int& posY, int& row1, int& row2, int& col1, int&col2);
	void GetPageInfoH(int& nIniColIndex, int& nEndColIndex);
	void GetPageInfoV(int& nIniRowIndex, int& nEndRowIndex);
	void GetClickInfo(LPARAM lParam, int&row, int& col, RECT& cell); 
	void GetAbsoluteClickInfo(LPARAM lParam, int&row, int& col, RECT& cell); 
	void UpdateScrollInfo(); //Call this after inserting or removing columns or rows
	bool IsEvent(Win::Event& e, int notification);
	void RefreshAll();
	void HeaderSetup(bool hasHeader);
	void CopyToClipboard();
	bool SaveEmfImage(const wchar_t* filename);
	//__________________________________________ Win::ITable
	virtual void OnTablePaint(int paintEvent, Win::Gdi& gdi, RECT& cell, int row, int col, bool isSelected);
	virtual void OnTableRequestInfo(Win::ITable::Info& info);
protected:
	//__________________________ For double buffer
	Win::DDBitmap _bitmap;
	void OnPaintControl(Win::Gdi& gdi, bool isMetafile);
	//
	const wchar_t * GetClassName(void){return L"WINSCROLLCONTROL";}
	virtual void Window_GetDlgCode(Win::Event& e);
	virtual void Window_Size(Win::Event& e);
	virtual void Window_VScroll(Win::Event& e);
	virtual void Window_HScroll(Win::Event& e);
	virtual void Window_KeyDown(Win::Event& e);
	virtual void Window_MouseWheel(Win::Event& e);
	virtual void Window_LButtonDown(Win::Event& e);
	virtual void Window_RButtonDown(Win::Event& e);
	virtual void Window_LButtonDblclk(Win::Event& e);
	virtual void Window_Paint(Win::Event& e);
	virtual void Window_Open(Win::Event& e);
	virtual void Window_SetFocus(Win::Event& e);
	virtual void Window_KillFocus(Win::Event& e);
	virtual bool ProcessMouse(HWND hWnd, Win::ITable::TableInfo& ti, LPARAM lParam);
	int _deltaWheelPerLine; 
	bool _selectFullRow;
	int _selectedRow; // Full row selected: _selectedRow >= 0 && _selectedCol < 0 
	int _selectedCol; // Full col selected: _selectedRow < 0 && _selectedCol >= 0
						       // Empty selection: _selectedRow < 0 && _selectedCol < 0 
							// Once cell selected: _selectedRow >= 0 && _selectedCol >= 0 
	bool _hasFocus;
	//Win::ITable *_itable;
	HWND _hWndParent;
	bool _showVerticalGrid;
	bool _showHorizontalGrid;
	COLORREF _backColor;
	COLORREF _hdrBackColor;
	COLORREF _textColor;
	COLORREF _lineColor;
	int _columnWidth;
	int _rowHeight;
	bool _hasHeader;
	void GetSelectionRect(RECT& rect);
	HFONT _hfont;
	int _emfWidth;
	int _emfHeight;
private:
	static int _isRegistered;
};

//_____________________________________________________________________ ScrollText
struct Sysmetrics
{
     int     iIndex ;
     wchar_t * szLabel ;
     wchar_t * szDesc ;
};

class ScrollText : public Win::ScrollControl
{
public:
	ScrollText(void);
	virtual ~ScrollText(void);
protected:
	virtual void Window_Paint(Win::Event& e);
	virtual void Window_Open(Win::Event& e);
	//______________________________________________ Win::ITable
	void OnTablePaint(int paint, Win::Gdi& gdi, RECT& cell, int row, int col, bool isSelected);
	void OnTableRequestInfo(Win::ITable::Info& info);
	//
	int GetColCount(void);
	int GetRowCount(void);
	int GetCellWidth(void);
	int GetCellHeight(void);
};

//_____________________________________________________________________ Clipboard
class Clipboard
{
public:
	virtual ~Clipboard(void);
	static bool HasDDBitmap(HWND hWnd);
	static bool HasDIBitmap(HWND hWnd);
	static bool HasText(HWND hWnd);
	static bool HasMetafile(HWND hWnd);
	static bool CopyDDBFromClipboard(HWND hWnd, Win::DDBitmap& ddbitmap);
	static bool CopyDDBToClipboard(HWND hWnd, HBITMAP hBitmap);
	static bool CopyDDBToClipboard(HWND hWnd, Win::DDBitmap& ddbitmap);
	static BOOL CopyDIBFromClipboard(HWND hWnd, Win::DIBitmapP& dib);
	static bool CopyDIBToClipboard(HWND hWnd, Win::DIBitmapP& dib);
	static wchar_t* CopyTextToClipboard(HWND hWnd, const wchar_t* text);
	static wchar_t* CopyTextToClipboard(HWND hWnd, const wstring& text);
	static wchar_t* CopyTextToClipboard(HWND hWnd, const char* text);
	static wchar_t* CopyTextToClipboard(HWND hWnd, const string& text);
	static wchar_t* CopyTextFromClipboard(HWND hWnd, wchar_t** text);	
	static void CopyTextFromClipboard(HWND hWnd, wstring& out_text);
	static void CopyTextFromClipboard(HWND hWnd, string& out_text);
	//static bool CopyHtmlToClipboard(HWND hWnd, const wchar_t* html);
	//static bool CopyHtmlToClipboard(HWND hWnd, const wstring& html);
	static bool CopyMetaFileToClipboard(HWND hWnd, Win::Metafile& mf);
	static bool CopyMetaFileFromClipboard(HWND hWnd, Win::Metafile& mf);
private:
	Clipboard(void);
};

//_____________________________________________________________________Splitter
//splitter.CreateVertical(hWnd, child1, child2, 0.5);
//splitter.OnParentSize(MAKELPARAM(width, height), NULL); // Call this from OnInitDialog to set the initial size
class Splitter :
	public Win::Window
{
public:
	Splitter(void);
	virtual ~Splitter(void);
	HWND CreateHorizontal(HWND parent, HWND child1, HWND child2, double sizeRatio);
	HWND CreateVertical(HWND parent, HWND child1, HWND child2, double sizeRatio);
	void OnParentSize(Win::Event& e, HWND rebar);  // Call this on Parent::Window_Size
protected:
	const wchar_t * GetClassName(void);
private:
	//LRESULT WndProc(Win::Event& e);
	void Window_LButtonUp(Win::Event& e);
	void Window_LButtonDown(Win::Event& e);
	void Window_MouseMove(Win::Event& e);
	void Adjust(int nSplitterPosition);
	int m_nSplitterWidth;
	double m_dSizeRatio;
	HWND m_hWndChild1;
	HWND m_hWndChild2;
	static int m_nObjectCountVe;
	static int m_nObjectCountHo;
	Sys::Cursor cursor;
	bool m_bHorizontal;
	int m_nParentWidth;
	int m_nParentHeight;
	enum position{child1, splitter, child2};
	void DrawBoxOutline(HWND hWnd, int nPosition);
	int m_nPosition;
	bool m_bBlocking;
	Win::Splitter::position m_position;
	int m_nChild1Size;
	int m_nChild2Size;
	int rebarHeight;
};

//_____________________________________________________________________ Digit
class Digit : public Win::Window
{
public:
	Digit(void);
	virtual ~Digit(void);
	void SetValue(int n);
	int GetValue();
	void SetColor(COLORREF color);
	COLORREF GetColor(void);
	void SetBackColor(COLORREF color);
	COLORREF GetBackColor(void);
	bool IsEvent(Win::Event& e, int notification);
protected:
	COLORREF color;
	COLORREF colorBackground;
	int m_nValue;
	void Window_Paint(Win::Event& e);
	void Window_LButtonDown(Win::Event& e);
	void Window_RButtonDown(Win::Event& e);
	//LRESULT WndProc(Win::Event& e);
	const wchar_t * GetClassName(void){return L"WINDIGIT";}
	static bool m_bRegistered;
};

//_____________________________________________________________________ FlowDisplay
class FlowDisplay : public Win::Window
{
public:
	FlowDisplay(void);
	virtual ~FlowDisplay(void);
	enum Flow{Left, None, Right};
	void SetFlow(Win::FlowDisplay::Flow flow);
	void SetColor(COLORREF color);
	COLORREF GetColor(void);
	bool IsEvent(Win::Event& e, int notification);
protected:
	COLORREF color;
	Win::FlowDisplay::Flow m_flow;
	bool m_bFlowing;
	bool m_bDisplayed;
	void Window_Paint(Win::Event& e);
	void Window_Timer(Win::Event& e);
	void Window_LButtonDown(Win::Event& e);
	void Window_RButtonDown(Win::Event& e);
	//LRESULT WndProc(Win::Event& e);
	COLORREF ReduceLuminance(COLORREF color);
	const wchar_t * GetClassName(void){return L"WINFLOWDISPLAY";}
	static bool m_bRegistered;
};

//_____________________________________________________________________ SimulationView
class SimulationView : public Win::Window
{
public:
	SimulationView(void);
	virtual ~SimulationView(void);
	COLORREF GetBackColor();
	virtual void SetBackColor(COLORREF color);
	__declspec( property( get=GetBackColor, put=SetBackColor ) ) COLORREF BackColor;
	//
	COLORREF GetTextColor();
	virtual void SetTextColor(COLORREF color);
	__declspec( property( get=GetTextColor, put=SetTextColor ) ) COLORREF TextColor;
	//
	virtual void SetFont(Win::Gdi::Font& font);
	__declspec( property( put=SetFont) ) Win::Gdi::Font& Font;
	//
	bool IsEvent(Win::Event& e, int notification);
	void Start(int refreshTime);
	void Stop();
	Sys::Stopwatch time;
	Win::DDBitmap bitmap;
protected:
	COLORREF _backColor;
	COLORREF _textColor;
	HFONT _hfont;
	void Window_Open(Win::Event& e);
	void Window_Size(Win::Event& e);
	void Window_Paint(Win::Event& e);
	void Window_Timer(Win::Event& e);
	void Window_LButtonDown(Win::Event& e);
	void Window_RButtonDown(Win::Event& e);
	//LRESULT WndProc(Win::Event& e);
	const wchar_t * GetClassName(void){return L"VISUALSIMULATION";}
	static bool m_bRegistered;
};

//_____________________________________________________________________ Tank
class Tank : public Win::Control
{
public:
	Tank(void);
	virtual ~Tank(void);
	void SetRange(double minimum, double maximum);
	//
	void SetLevel(double level);
	double GetLevel();
	__declspec( property( get=GetLevel, put=SetLevel ) ) double Level;
	//
	void SetTankColor(COLORREF color);
	COLORREF GetTankColor(void);
	__declspec( property( get=GetTankColor, put=SetTankColor ) ) COLORREF TankColor;
protected:
	COLORREF _tankColor;
	double _level;
	double _levelOld;
	double _minLevel;
	double _maxLevel;
	RECT _rcScale;
	RECT _rcMarks;
	RECT _rcCilinder;
	RECT _rcCaption;
	double _markDelta;
	virtual void OnPaintControl(Win::Gdi& gdi);
	virtual void OnSizePrivate();
	virtual void Window_Open(Win::Event& e);
	virtual void Window_Paint(Win::Event& e);
	virtual void Window_Size(Win::Event& e);
	Win::DDBitmap bitmap;
};

//_____________________________________________________________________ ValueDisplay
class ValueDisplay : public Win::Control
{
public:
	ValueDisplay(void);
	virtual ~ValueDisplay(void);
	void SetValue(const wstring& psz);
	wstring& GetValue();
	__declspec( property( get=GetValue, put=SetValue ) ) wstring& Value;
	//
	void SetDouble(double value);
	double GetDouble();
__declspec( property( get=GetDouble, put=SetDouble) ) double DoubleValue;
protected:
	Win::DDBitmap bitmap;
	virtual void Window_Open(Win::Event& e);
	virtual void Window_Size(Win::Event& e);
	virtual void Window_Paint(Win::Event& e);
	//
	wstring _value;
	RECT _rectName;
	RECT _rectValue;
	void OnPaintControl(Win::Gdi& gdi);
	void OnSizePrivate();
};

//_____________________________________________________________________ ColorDisplay
class ColorDisplay : public Win::Control
{
public:
	ColorDisplay(void);
	virtual ~ColorDisplay(void);
	bool IsEvent(Win::Event& e, int notification);
	void SetAlignment(int alignment); //TA_LEFT, TA_CENTER, TA_RIGHT
	int GetAlignment(); //TA_LEFT, TA_CENTER, TA_RIGHT
	__declspec( property( get=GetAlignment, put=SetAlignment ) ) int Alignment;
	//
	void SetBlink(bool blink);
	bool GetBlink();
	__declspec( property( get=GetBlink, put=SetBlink ) ) bool Blink;
protected:
	Win::DDBitmap bitmap;
	virtual void Window_Open(Win::Event& e);
	virtual void Window_Size(Win::Event& e);
	virtual void Window_Paint(Win::Event& e);
	bool _blink;
	bool _on;
	void Window_Timer(Win::Event& e);
	int alignment;
	void OnPaintControl(Win::Gdi& gdi);
};

#ifdef WIN_DAC_ADC_SUPPORT
//_____________________________________________________________________ SignalView
class SignalView : public Win::Control
{
public:
	SignalView(void);
	virtual ~SignalView(void);
	void SetToZero(void);
	bool IsEvent(Win::Event& e, int notification);
	void OnData(LPARAM lParam); // Call internally by IsEvent()
protected:
	void OnPaintControl(Win::Gdi& gdi);
	POINT _ptLeft[WIN_SIGNALVIEWER_MAX];
	POINT _ptRight[WIN_SIGNALVIEWER_MAX];
	int _minimum, _maximum;
};
#endif

//_____________________________________________________________________Graph
class Graph
{
public:
	enum Type {dot, line, cross, circle, square, histogram, impulse, number};
	Graph(void);
	virtual ~Graph(void);
	COLORREF color;
	int penWidth;
	void SetCaption(const wchar_t* caption);
	const wchar_t* GetCaption();
	wchar_t* SaveAsAnsiTextFile(const wchar_t* pszFileName, const char* pszFormat);
	void QuickDisplay(HWND hWnd, const wchar_t* pszFormat);
	void SetType(Win::Graph::Type type);
	Win::Graph::Type GetType();
	virtual bool SetPointCount(int nPointCount);
	int GetPointCount();
	void Delete();
	POINT* GetScreenPoints();
	Win::Gdi::PointF* GetDataPoints();
	Graph(const Graph& init);
	Graph& operator =(const Graph& init);
	Win::Gdi::PointF& operator[](long index) // Subscript operator
	{
		if (index<0 || index>=(long) m_nPointCount) throw out_of_range("Invalid index");
		return m_pDataPoints[index];
	}
	const Win::Gdi::PointF& operator[](long index) const// Subscript operator
	{
		if (index<0 || index>=(long) m_nPointCount) throw out_of_range("Invalid index");
		return m_pDataPoints[index];
	}
	Win::Gdi::PointF& Get(long index);
	void Set(long index, double x, double y);
	void SetData(double* x, double* y, int length);
	void SetData(double* y, int length);
	double GetMaxX(void);
	double GetMaxY(void);
	bool DownSample(int newLength);
protected:
	void Contruction(void);
	void Copy(const Graph& init);
	POINT *m_pScreenPoints;
	Win::Gdi::PointF *m_pDataPoints;
	wchar_t *m_pszCaption;
	int m_nPointCount;
	Win::Graph::Type m_type;
	wchar_t errorInformation[256];
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
	Win::Graph& operator[](long index);
	int GetCount();
	__declspec( property( get=GetCount) ) int Count;
protected:
	vector<Win::Graph> _data;
};

//_____________________________________________________________________ XyChart
// You can override OnPaintScaleX and OnPaintScaleY
class XyChart : public Win::Control
{
public:
	XyChart(void);
	virtual ~XyChart(void);
	//
	Win::GraphCollection Graphs;
	//
	void SetShowGrid(bool showGrid);
	bool GetShowGrid();
	__declspec( property( get=GetShowGrid, put=SetShowGrid ) ) bool ShowGrid;
	//
	void SetMinX(double minimum);
	double GetMinX();
	__declspec( property( get=GetMinX, put=SetMinX ) ) double MinX;
	//
	void SetMaxX(double maximum);
	double GetMaxX();
	__declspec( property( get=GetMaxX, put=SetMaxX ) ) double MaxX;
	//
	void SetMinY(double minimum);
	double GetMinY();
	__declspec( property( get=GetMinY, put=SetMinY ) ) double MinY;
	//
	void SetMaxY(double maximum);
	double GetMaxY();
	__declspec( property( get=GetMaxY, put=SetMaxY ) ) double MaxY;
	//
	void SetDivisionCountX(int count);
	int GetDivisionCountX();
	__declspec( property( get=GetDivisionCountX, put=SetDivisionCountX ) ) int DivisionCountX;
	//
	void SetDivisionCountY(int count);
	int GetDivisionCountY();
	__declspec( property( get=GetDivisionCountY, put=SetDivisionCountY ) ) int DivisionCountY;
	//
	void SetSubDivisionCountX(int count);
	int GetSubDivisionCountX();
	__declspec( property( get=GetSubDivisionCountX, put=SetSubDivisionCountX ) ) int SubDivisionCountX;
	//
	void SetSubDivisionCountY(int count);
	int GetSubDivisionCountY();
	__declspec( property( get=GetSubDivisionCountY, put=SetSubDivisionCountY ) ) int SubDivisionCountY;
	//
	void SetCaptionX(const wstring& caption);
	wstring& GetCaptionX();
	__declspec( property( get=GetCaptionX, put=SetCaptionX ) ) wstring& CaptionX;
	//
	void SetCaptionY(const wstring& caption);
	wstring& GetCaptionY();
	__declspec( property( get=GetCaptionY, put=SetCaptionY ) ) wstring& CaptionY;
	//
	void SetLogScaleX(bool logScale);
	bool GetLogScaleX();
	__declspec( property( get=GetLogScaleX, put=SetLogScaleX ) ) bool LogScaleX;
	//
	void SetLogScaleY(bool logScale);
	bool GetLogScaleY();
	__declspec( property( get=GetLogScaleY, put=SetLogScaleY ) ) bool LogScaleY;
	//
	void SetSubgridColor(COLORREF color);
	COLORREF GetSubgridColor();
	__declspec( property( get=GetSubgridColor, put=SetSubgridColor ) ) COLORREF SubgridColor;
	//
	void SetSymbolCaption(bool captionX, bool captionY);
	//
	void AutoScaleX();
	void AutoScaleY();
	//
	void SetFormat(const wchar_t* formatX, const wchar_t* formatY);
	void SetCommaSeparatedFormat(bool useCommaX, bool useCommaY);
	void RefreshGraphArea();
	void RefreshAll();
	void RefreshGraphCaption();
	double TransformFromScreenCoordinatesX(int x);
	double TransformFromScreenCoordinatesY(int y); 
	//
	wstring fontFamilyCaptionY;
	//____________________________________________________ IExportable
	void OnPaintControl(Win::Gdi& gdi);
	bool IsEvent(Win::Event& e, int notification);
protected:
	Win::DDBitmap bitmap;
	virtual void Window_Open(Win::Event& e);
	virtual void Window_Size(Win::Event& e);
	virtual void Window_Paint(Win::Event& e);
	//
	void OnSizePrivate(void);
	virtual void OnPaintScaleX(Win::Gdi& gdi, int index, double delta, double value);
	virtual void OnPaintScaleY(Win::Gdi& gdi, int index, double delta, double value);
	virtual void DrawGraph(Win::Gdi& gdi, int graphIndex);
	double _originX;
	double _originY;
private:
	bool _useCommaX;
	bool _useCommaY;
	RECT _rcMain;
	double _minX;
	double _maxX;
	double _minY;
	double _maxY;
	double _minXUser;
	double _maxXUser;
	double _minYUser;
	double _maxYUser;
	double _scaleX;
	double _scaleY;
	double _boxCaptionHeight;
	wstring _captionX;
	wstring _captionY;
	wchar_t _formatX[8];
	wchar_t _formatY[8];
	int _divCountX;
	int _divCountY;
	int _subDivCountX;
	int _subDivCountY;
	bool _isLogX;
	bool _isLogY;
	bool _showGrid;
	bool _symbolCaptionX;
	bool _symbolCaptionY;
	COLORREF _subgridColor;
	void PaintCaptionX(Win::Gdi& gdi);
	void PaintCaptionY(Win::Gdi& gdi);
	void PaintScaleX(Win::Gdi& gdi, double deltaX);
	void PaintScaleY(Win::Gdi& gdi, double deltaY);
	void PaintDivX(Win::Gdi& gdi);
	void PaintDivY(Win::Gdi& gdi);
	void PaintSubDivX(Win::Gdi& gdi);
	void PaintSubDivY(Win::Gdi& gdi);
	void PaintGraphs(Win::Gdi& gdi);

	int TransformToScreenCoordinatesX(double x) 
	{
		return (int)((x - _minX)* _scaleX + _originX+0.5);
	}
	int TransformToScreenCoordinatesY(double y) 
	{
		return (int)(( y - _minY)* _scaleY +  _originY+0.5);
	}
};

//_____________________________________________________________________ PolarChart
// Use a graph object to plot over a plotter x is the tetha (radians) and y is the radius
class PolarChart : public Win::Control
{
public:
	PolarChart(void);
	virtual ~PolarChart(void);
	//
	Win::GraphCollection Graphs;
	//
	virtual void OnPaintScaleR(Win::Gdi& gdi, POINT center, double value);//You may overwrite this function
	void OnPaintControl(Win::Gdi& gdi);
	void SetRadius(double minimum, double maximum);
	void AutoScaleRadius();
	//
	void SetSubgridColor(COLORREF color);
	COLORREF GetSubgridColor();
	__declspec( property( get=GetSubgridColor, put=SetSubgridColor ) ) COLORREF SubgridColor;
	//
	void Refresh();
	void ShowSubgrid(bool subgrid);
protected:
	virtual void Window_Open(Win::Event& e);
	virtual void Window_Size(Win::Event& e);
	virtual void Window_Paint(Win::Event& e);
	void OnSizePrivate(void);
	void PaintGraphs(Win::Gdi& gdi);
	virtual void DrawGraph(Win::Gdi& gdi, int graphIndex);
	int Line(Win::Gdi& gdi, double angle, int index, POINT* points);
	int ShortLine(Win::Gdi& gdi, double angle, int index, POINT* points);
	COLORREF _subgridColor;
	bool _subgrid;
	Win::DDBitmap bitmap;
private:
	int TransformToScreenCoordinatesX(double tetha, double r) 
	{
		r -= _minRadius;
		if (r>0)
			return (int)(r * _scale*cos(tetha) + _centerX+0.5);
		else
			return (int)(r * _scale*cos(tetha+M_PI)+ _centerX+0.5);
	}	
	int TransformToScreenCoordinatesY(double tetha, double r) 
	{
		r -= _minRadius;
		if (r>0)
			return (int)(-r* _scale*sin(tetha)+ _centerY+0.5);
		else
			return (int)(-r* _scale*sin(tetha+M_PI)+ _centerY+0.5);
	}
	double _scale, _centerX, _centerY, _maxRadius, _minRadius;
};

//_____________________________________________________________________ View3D
class View3D : public Win::Window, public Win::IExportable, public Win::IPrint
{
public:
	View3D(void);
	virtual ~View3D(void);
	//
	void SetCenter(double centerX, double centerY);
	void GetCenter(double& centerX, double& centerY);
	//
	COLORREF GetBackColor();
	virtual void SetBackColor(COLORREF color);
	__declspec( property( get=GetBackColor, put=SetBackColor ) ) COLORREF BackColor;
	//
	COLORREF GetLineColor();
	virtual void SetLineColor(COLORREF color);
	__declspec( property( get=GetLineColor, put=SetLineColor ) ) COLORREF LineColor;
	//
	COLORREF GetTextColor();
	virtual void SetTextColor(COLORREF color);
	__declspec( property( get=GetTextColor, put=SetTextColor ) ) COLORREF TextColor;
	//
	virtual void SetFont(Win::Gdi::Font& font);
	__declspec( property( put=SetFont) ) Win::Gdi::Font& Font;
	//
	void SetZoom(double zoom);
	double GetZoom(void);
	__declspec( property( get=GetZoom, put=SetZoom ) ) double Zoom;
	//
	void SetAngle(double angleDegrees);
	double GetAngle(void);
	__declspec( property( get=GetAngle, put=SetAngle ) ) double Angle;
	//
	void SetShowBox(bool showBox);
	bool GetShowBox(void);
	__declspec( property( get=GetShowBox, put=SetShowBox ) ) bool ShowBox;
	//
	void SetPerspective(double angleDegrees);
	double GetPerspective(void);
	__declspec( property( get=GetPerspective, put=SetPerspective ) ) double Perspective;
	//
	void SetMinX(double minimum);
	double GetMinX();
	__declspec( property( get=GetMinX, put=SetMinX ) ) double MinX;
	//
	void SetMaxX(double maximum);
	double GetMaxX();
	__declspec( property( get=GetMaxX, put=SetMaxX ) ) double MaxX;
	//
	void SetMinY(double minimum);
	double GetMinY();
	__declspec( property( get=GetMinY, put=SetMinY ) ) double MinY;
	//
	void SetMaxY(double maximum);
	double GetMaxY();
	__declspec( property( get=GetMaxY, put=SetMaxY ) ) double MaxY;
	//
	void SetMinZ(double minimum);
	double GetMinZ();
	__declspec( property( get=GetMinZ, put=SetMinZ ) ) double MinZ;
	//
	void SetMaxZ(double maximum);
	double GetMaxZ();
	__declspec( property( get=GetMaxZ, put=SetMaxZ ) ) double MaxZ;
	//
	void SetDivisionCountX(int count);
	int GetDivisionCountX();
	__declspec( property( get=GetDivisionCountX, put=SetDivisionCountX ) ) int DivisionCountX;
	//
	void SetDivisionCountY(int count);
	int GetDivisionCountY();
	__declspec( property( get=GetDivisionCountY, put=SetDivisionCountY ) ) int DivisionCountY;
	//
	void SetDivisionCountZ(int count);
	int GetDivisionCountZ();
	__declspec( property( get=GetDivisionCountZ, put=SetDivisionCountZ ) ) int DivisionCountZ;
	//
	void SetAxisLength(float length);
	void ResetView(bool resetZoom);
	virtual void OnPaint3D(Win::Gdi& gdi); //Override this function
	//
	void Transform(const vector<Sys::Line3D>& input, vector<Sys::Line16X>& output);
	void Transform(Sys::Point3D* input, POINT* output, const int count);
	void Transform(Sys::Point3D* input, Sys::Point* output, const int count);
	void Transform(Sys::Point3D* input, Sys::Point16* output, const int count);
	//
	void DrawCenter(COLORREF color);
	//
	static void ConvertFromSphericalToCartesian(Sys::SphericalPoint* input, Sys::Point3D* output, const int count);
	bool IsEvent(Win::Event& e, int notification);
	//____________________________________________________ IExportable
	void OnPaintControl(Win::Gdi& gdi);
	HWND GetControlInfo(int& width, int&height);
	void SetControlSize(int width, int height);
	//____________________________________________________ IPrint
	void Print(Win::Gdi& gdi, Win::PrintInfo pi);
	//
	bool CopyToClipboard();
	Sys::Graphics graphics;
protected:
	//Win::DDBitmap bitmap;
	void Window_Paint(Win::Event& e);
	void Window_Size(Win::Event& e);
	void Window_Open(Win::Event& e);
	void Window_KeyDown(Win::Event& e);
	void Window_HScroll(Win::Event& e);
	void Window_VScroll(Win::Event& e);
	void Window_LButtonDown(Win::Event& e);
	void Window_RButtonDown(Win::Event& e);
	void Window_LButtonUp(Win::Event& e);
	void Window_MouseMove(Win::Event& e);
	void Window_MouseWheel(Win::Event& e);
	void Window_GetDlgCode(Win::Event& e);
	virtual void Window_SetFocus(Win::Event& e);
	virtual void Window_KillFocus(Win::Event& e);
	const wchar_t * GetClassName(void){return L"VIEW3D";}
	void OnSizePrivate(void);
	//
	COLORREF _backColor;
	COLORREF _backColorx;
	COLORREF _lineColor;
	COLORREF _textColor;
	HFONT _hfont;
	float _axisLength;
	float _angle;
	float _sinAngle;
	float _cosAngle;
	float _zoom;
	float _centerX;
	double _centerY;
	float _perspective;
	float _cosPerspective;
	float _sinPerspective;
	double _minX;
	double _maxX;
	double _minY;
	double _maxY;
	double _minZ;
	double _maxZ;
	int _divCountX;
	int _divCountY;
	int _divCountZ;
	int _deltaWheelPerLine, _accumWheelDelta;
	bool _hasFocus;
	bool _showBox;
	bool _lbuttonDown;
	POINT _mousePosition;
	HCURSOR _hCursor;
	HWND _hWndParent;
private:
	static bool _bRegistered;
};

class BarChart;
class BarCollection;

//_____________________________________________________________________ Bar
class Bar
{
public:
	Bar();
	~Bar();
	//
	COLORREF GetColor();
	virtual void SetColor(COLORREF color);
	__declspec( property( get=GetColor, put=SetColor ) ) COLORREF Color;
	//
	double GetValue();
	virtual void SetValue(double value);
	__declspec( property( get=GetValue, put=SetValue ) ) double Value;
	//
	wstring GetText();
	virtual void SetText(wstring text);
	__declspec( property( get=GetText, put=SetText ) ) wstring Text;
	//
	bool operator<(const Win::Bar& bar) const;
private:
	double _value;
	wstring _text;
	COLORREF _color;
	int _index;
	//
	HWND barchart;
	Win::BarChart * barChart;
	friend class BarChart;
	friend class BarCollection;
};

//_____________________________________________________________________ BarCollection
class BarCollection
{
public:
	BarCollection();
	~BarCollection();
	void Add(const wstring& text, COLORREF color, double value);
	void DeleteAll();
	//
	Win::Bar& operator[](long index);
	//
	int GetCount();
	__declspec( property( get=GetCount) ) int Count; 
private:
	vector<Bar> _bars;
	Win::BarChart * barChart;
	friend class BarChart;
};

//_____________________________________________________________________ BarChart
class BarChart : public Win::Control
{
public:
	BarChart(void);
	virtual ~BarChart(void);
	//
	void SetDivYCount(int count);
	int GetDivYCount();
	__declspec( property( get=GetDivYCount, put=SetDivYCount ) ) int DivYCount;
	//
	void SetMaxY(double value);
	double GetMaxY();
	__declspec( property( get=GetMaxY, put=SetMaxY ) ) double MaxY;
	//
	void SetMinY(double value);
	double GetMinY();
	__declspec( property( get=GetMinY, put=SetMinY ) ) double MinY;
	//
	void SetAutoscale(bool autoscale);
	bool GetAutoscale();
	__declspec( property( get=GetAutoscale, put=SetAutoscale ) ) bool Autoscale;
	//
	//void SetCaptionYFormat(const wchar_t* format);
	//
	bool IsEvent(Win::Event& e, int notification);
	void Refresh();
	//
	Win::BarCollection& GetBars();
	__declspec( property( get=GetBars) ) Win::BarCollection& Bars;
	//
	void UpdateBar(int index);
	void UpdateBarText(int index);
	void UpdateBarValues();
	//
	void OnPaintControl(Win::Gdi& gdi);
private:
	Win::BarCollection _bars;
	//
	RECT _box;
	int * pGridY;
	int _divCount;
	RECT _rectCaptionX;
	RECT _rectCaptionY;
	double _deltaX;
	double _deltaY;
	double _scaleY;
	double _barWidth;
	
	double _maxValue;
	double _minValue;
protected:
	Win::DDBitmap bitmap;
	virtual void Window_Open(Win::Event& e);
	virtual void Window_Size(Win::Event& e);
	virtual void Window_Paint(Win::Event& e);
	//static bool m_bRegistered;	
	//const wchar_t * GetClassName(void){return L"WINBARCHART";}
	bool m_bTickX;
	bool _autoscale;
	void OnSizePrivate(void);
};

class PieChart;
class PieCollection;

//_____________________________________________________________________ Pie
class Pie
{
public:
	Pie();
	~Pie();
	//
	COLORREF GetColor();
	virtual void SetColor(COLORREF color);
	__declspec( property( get=GetColor, put=SetColor ) ) COLORREF Color;
	//
	double GetValue();
	virtual void SetValue(double value);
	__declspec( property( get=GetValue, put=SetValue ) ) double Value;
	//
	wstring GetText();
	virtual void SetText(wstring text);
	__declspec( property( get=GetText, put=SetText ) ) wstring Text;
	//
	bool operator<(const Win::Pie& pie) const;
private:
	double _value;
	wstring _text;
	COLORREF _color;
	int _index;
	//
	HWND piechart;
	Win::PieChart * pieChart;
	friend class PieChart;
	friend class PieCollection;
};

//_____________________________________________________________________ PieCollection
class PieCollection
{
public:
	PieCollection();
	~PieCollection();
	void Add(const wstring& text, COLORREF color, double value);
	void DeleteAll();
	//
	Win::Pie& operator[](long index);
	//
	int GetCount();
	__declspec( property( get=GetCount) ) int Count; 
private:
	vector<Pie> _pies;
	Win::PieChart * pieChart;
	friend class PieChart;
};


//_____________________________________________________________________ PieChart
class PieChart : public Win::Control
{
public:
	PieChart(void);
	virtual ~PieChart(void);
	//
	Win::PieCollection& GetPies();
	__declspec( property( get=GetPies) ) Win::PieCollection& Pies;
	//
	void SetPieValue(int index, double value);
	void SetPieColor(int index, COLORREF color);
	void SetPieText(int index, const wchar_t* text);
	void SetPieText(int index, const wstring& text);
	void SetCaptionFormat(const wchar_t* format);
	//
	void OnPaintControl(Win::Gdi& gdi);
	void Refresh();
private:
	Win::PieCollection _pies;
	void Pie_(Win::Gdi& gdi, const wchar_t* text, double percentaje, COLORREF color, int spacingY);
	int _x;
	int _y; 
	int _radius;
	int _xCenter; 
	int _yCenter;
	int _xCaption;
	int _yCaption;
	double _dimension;
	double _angleIni;
	double _total;
protected:
	Win::DDBitmap bitmap;
	virtual void Window_Paint(Win::Event& e);
	virtual void Window_Open(Win::Event& e);
	virtual void Window_Size(Win::Event& e);
	void OnSizePrivate(void);
	void UpdateBarValues();
	wchar_t captionFormat[WIN_PIECHART_SZ];
};

//_____________________________________________________________________Histogram
class Histogram : public Win::XyChart
{
public:
	Histogram(void);
	virtual ~Histogram(void);
	void SetData(valarray<double>& data, int resolution, bool percentDisplay);
};

//_____________________________________________________________________LevelControl
class LevelControl : public Win::Control
{
public:
	LevelControl(void);
	virtual ~LevelControl(void);
	void SetRange(double minValue, double maxValue);
	//
	void SetLevel(double level);
	double GetLevel();
	__declspec( property( get=GetLevel, put=SetLevel ) ) double Level;
	//
	COLORREF GetWarningColor();
	virtual void SetWarningColor(COLORREF color);
	__declspec( property( get=GetWarningColor, put=SetWarningColor ) ) COLORREF WarningColor;
	//
	COLORREF GetErrorColor();
	virtual void SetErrorColor(COLORREF color);
	__declspec( property( get=GetErrorColor, put=SetErrorColor ) ) COLORREF ErrorColor;
	//
	void Setup(double normalLevel, double warningLevel);
protected:
	double Normalize(double x);
	struct LevelInfo
	{
		RECT rc;
		int brushOnIndex;
		int brushOffIndex;
		double level; //From 0.0 to 0.99
	};
	void OnPaintControl(Win::Gdi& gdi);
	void OnSizePrivate();
	static COLORREF GetOffColor(COLORREF color);
private:
	COLORREF _warningColor;
	COLORREF _errorColor;
	double _normalLevel;
	double _warningLevel;
	int _blockCount;
	int _blockHeight;
	const int _blockWidth;
	const int _blockPadding;
	int _padding;
	double _minLevel;
	double _maxLevel;
	double _level;
	LevelInfo levels[WIN_LEVELCONTROL_MAX];
};

//_____________________________________________________________________LevelState
class LevelState : public Win::Control
{
public:
	LevelState(void);
	virtual ~LevelState(void);
	void SetStateCount(int count);
	int GetStateCount();
	__declspec( property( get=GetStateCount, put=SetStateCount ) ) int StateCount;
	//
	void SetState(int index, double minValue, double maxValue, COLORREF color, wchar_t* caption);
	//
	void SetLevel(double level);
	double GetLevel();
	__declspec( property( get=GetLevel, put=SetLevel ) ) double Level;
	//
	void SetLogScale(bool logScale);
	bool GetLogScale();
	__declspec( property( get=GetLogScale, put=SetLogScale ) ) bool LogScale;
	//
	void SetDisplayLevelValue(bool displayLevelValue);
	bool GetDisplayLevelValue();
	__declspec( property( get=GetDisplayLevelValue, put=SetDisplayLevelValue ) ) bool DisplayLevelValue;
protected:
	Win::DDBitmap bitmap;
	virtual void Window_Open(Win::Event& e);
	virtual void Window_Size(Win::Event& e);
	virtual void Window_Paint(Win::Event& e);
	//
	void OnPaintControl(Win::Gdi& gdi);
	int _numDivisions;
	double _minValue;
	double _maxValue;
	int MapToScreen(double value, int fontHeight);
	double _level;
	int _stateCount;
private:
	struct StateInfo
	{
		double minValue;
		double maxValue;
		COLORREF color;
		wchar_t text[64];
	};
	LevelState::StateInfo _si[WIN_LEVEL_STATE_STATES];
	bool _logScale;
	bool _displayLevelValue;
	double _minimum;
	double _scale;
	void InvalidateMiddle();
};

//m_lc.Create(0, NULL, WS_VISIBLE | WS_CHILD | WS_TABSTOP, 
//	0, 0, 0, 0, hWnd, (HMENU)IDC_STATIC);
//m_lc.SetRange(1.90, 4.5155);
//m_lc.SetLevel(0);
//_____________________________________________________________________Monitor
class Monitor : public Win::Control
{
public:
	Monitor(void);
	virtual ~Monitor(void);
	void AddValue(double value);
	void SetSquareSize(int size);
	void SetResolution(int resolution);
	void SetRange(double minimum, double maximum);
	void Clear();
	void SetAll(double value);
	//
	COLORREF GetLineColor1();
	virtual void SetLineColor1(COLORREF color);
	__declspec( property( get=GetLineColor1, put=SetLineColor1 ) ) COLORREF LineColor1;
protected:
	Win::DDBitmap bitmap;
	virtual void Window_Open(Win::Event& e);
	virtual void Window_Size(Win::Event& e);
	virtual void Window_Paint(Win::Event& e);
	//
	virtual void OnPaintControl(Win::Gdi& gdi);
	virtual void OnSizePrivate();
	double _min;
	double _max;
private:
	double *_data;
	int _dataSize;
	int _dataScreenCount;
	int _lineOffset;
	int _resolutionX;
	int _squareSize;
	double _scale;
	int _offsetData;
	COLORREF _lineColor1;
};

//_____________________________________________________________________ Monitor3
class Monitor3 : public Win::Control
{
public:
	Monitor3(void);
	virtual ~Monitor3(void);
	void AddValue(double value1, double value2, double value3);
	void SetSquareSize(int size);
	void SetResolution(int resolution);
	void SetRange(double minimum, double maximum);
	void Clear();
	void SetAll(double value1, double value2, double value3);
	//
	COLORREF GetLineColor1();
	virtual void SetLineColor1(COLORREF color);
	__declspec( property( get=GetLineColor1, put=SetLineColor1 ) ) COLORREF LineColor1;
	//
	COLORREF GetLineColor2();
	virtual void SetLineColor2(COLORREF color);
	__declspec( property( get=GetLineColor2, put=SetLineColor2 ) ) COLORREF LineColor2;
	//
	COLORREF GetLineColor3();
	virtual void SetLineColor3(COLORREF color);
	__declspec( property( get=GetLineColor3, put=SetLineColor3 ) ) COLORREF LineColor3;
protected:
	Win::DDBitmap bitmap;
	virtual void Window_Open(Win::Event& e);
	virtual void Window_Size(Win::Event& e);
	virtual void Window_Paint(Win::Event& e);
	virtual void OnPaintControl(Win::Gdi& gdi);
	virtual void OnSizePrivate();
	double _min;
	double _max;
	void PaintData(Win::Gdi& gdi, int index1, int index2, double* data);
private:
	double *_data1;
	double *_data2;
	double *_data3;
	int _dataSize;
	int _dataScreenCount;
	int _lineOffset;
	int _resolutionX;
	int _squareSize;
	double _scale;
	int _offsetData;
	COLORREF _lineColor1, _lineColor2, _lineColor3;
};

//____________________________________________________________SerialPort
class SerialPort : public Win::Control
{
public:
	enum Status{Success=0, Error, Timeout};
	SerialPort(void);
	~SerialPort(void);
	bool Open(wchar_t* portName, DCB& dcb); 
	void Close();
	void InitializeDcbDefaults(DCB& dcb);
	BOOL InitializeDcbDlg(const wchar_t * lpszName, HWND hWnd, DCB& dcb);
	Win::SerialPort::Status writeByte(BYTE byte);
	Win::SerialPort::Status writeBuffer(char* buffer, unsigned int count);
	Win::SerialPort::Status readByte(BYTE& byte);
	Win::SerialPort::Status readBuffer(char* buffer, unsigned int count);
	void Break(long milliseconds);
	Win::SerialPort::Status Peek(void* buffer, unsigned int count);
	bool IsEvent(Win::Event& e, int notification);
protected:
	Mt::Deque rxQueue;
	Mt::Deque txQueue;
	virtual void RxNotify(int byteCount); // It's called when there is data ready to read
	virtual void TxNotify(); //Its' called when data is successfully trasmitted
	virtual void BreakDetectNotify();
	virtual void FramingErrorNotify();
	virtual void HardwareOverrunErrorNotify();
	virtual void ParityErrorNotify();
	virtual void SoftwareOverrunErrorNotify();
	virtual void CtsNotify(bool status);
	virtual void DsrNotify(bool status);
	virtual void CdNotify(bool status);
	virtual void RiNotify(bool status);
	//
	int rxCount;
	int txCount;
	bool isCts;
	bool isDsr;
	bool isCd;
	bool isRi;
	wchar_t * errorCaption;
	//
	void UpdateRow(int index);
	//
	wchar_t  portName[32];
	void Window_Open(Win::Event& e);
	void OnPaintControl(Win::Gdi& gdi);
private:
	HWND hWndParent;
	HANDLE port;
	HANDLE hInputThread;
	HANDLE hOutputThread;
	int breakDuration;
	DWORD dwErrors;
	DWORD dwModemStatus;
	Win::SerialPort::Status error_status;
	Mt::EventI eventKillInputThread;
	Mt::EventI eventKillOutputThread;
	Mt::EventI eventWriteRequest;
	Mt::EventI eventReadRequest;
	Mt::EventI eventBreakRequest;
	static unsigned WINAPI InputThreadFunc(LPVOID param);
	static unsigned WINAPI OutputThreadFunc(LPVOID param);
	void clear_error(void);
	void check_modem_status(bool first_time, DWORD event_mask);
	bool output_worker();
	bool bInputThreadReading;
	int iBreakDuration;
	unsigned int byteCount;
	void DrawDataRow(Win::Gdi& gdi, int index, COLORREF nameColor, const wchar_t* text, bool active);
};

//__________________________________________________________________________ ListDlg
// This class allows displaying a vector of strings in a dialog, the first row in the vector is displayed in the Window Title
class ListDlg :    
	public Dialog
{
public:
	ListDlg()
	{
	}
	~ListDlg()
	{
	}
	list<wstring> data; // The first row is displayed in the Window Title
private:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Button btDummy;
	Win::Textbox tbxData;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(687);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(602);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"List Dialog";
		btDummy.Create(NULL, L"Get Focus", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 308, 65, 4, 7, hWnd, 1000);
		tbxData.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_HSCROLL | WS_VISIBLE | WS_VSCROLL | ES_AUTOHSCROLL | ES_MULTILINE | ES_READONLY | ES_WANTRETURN | ES_LEFT | ES_WINNORMALCASE, 0, 0, 685, 600, hWnd, 1001);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		btDummy.Font = fontArial014A;
		tbxData.Font = fontArial014A;
		tbxData.SetDock(DOCK_BORDER, DOCK_BORDER, DOCK_BORDER, DOCK_BORDER);
	}
	//_________________________________________________
	void btDummy_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (btDummy.IsEvent(e, BN_CLICKED)) {btDummy_Click(e); return true;}
		return false;
	}
};

} //____________________________________________________ namespace Win::End

//______________________________________________________ namespace Mm::Ini
#ifdef WIN_DAC_ADC_SUPPORT
namespace Mm{

//_____________________________________________________________________ SoundResource
class SoundResource
{
public:
	SoundResource(void);
	virtual ~SoundResource(void);
	bool Play(const wchar_t* name, HINSTANCE hInstance);
	void Stop();
	void Delete();
private:
	HANDLE hRes; 
};

//_____________________________________________________________________ WaveFile
class WaveFile
{
public:
	WaveFile(void);
	virtual ~WaveFile(void);
	wchar_t* OpenForReading(const wchar_t* fileName);
	wchar_t* OpenForWritting(unsigned int samplesPerSec, bool bStereo, unsigned int bitsPerSample, const wchar_t* fileName);
	void GetInfo(unsigned int& bitsPerSample, DWORD& samplesPerSec, unsigned short&numChannels);
	wchar_t* Close(void);
	long ReadData(LPSTR buffer, unsigned int bufferSize); //returns bytes written
	long WriteData(LPSTR buffer, unsigned int bufferSize); //returns bytes read
	double GetRemainingSeconds();
	unsigned int GetRemainingByteCount(void);
	wchar_t* GetFileDuration(const wchar_t* fileName, double& durationSeconds);
	int GetNumChannels();
	int GetBitsPerSample();
	int GetSamplesPerSecond();
protected:
	HMMIO hmmio;
	unsigned short bitsPerSample;
	DWORD samplesPerSec;
	unsigned short numChannels;
	unsigned int dataSize;
	bool isWritting;
	MMCKINFO mmckinfoData;
	MMCKINFO mmckinfoWave;
	//void Destructor(void);
};

//_____________________________________________________________________ WaveBuffer
class WaveBuffer
{
public:
	WaveBuffer(void);
	virtual ~WaveBuffer(void);
	bool Create(unsigned int nBufferSize);
	void Destroy();
	LPWAVEHDR m_pWaveHdr;
	char* GetBuffer()
		{return m_pBuffer;}
	unsigned int GetBufferSize();
	bool CreateUsingExternalBuffer(char* pData, unsigned int nBufferSize);
	void SetValue(unsigned int index, char value)
		{m_pBuffer[index] = value;}
	unsigned int GetString(wchar_t* pszBuffer, int nBufferSize);
	operator char*() 
		{return m_pBuffer;}
	operator WAVEHDR*() 
		{return m_pWaveHdr;}
private:
	char* m_pBuffer;
	bool m_bExternalBuffer;
	//unsigned int m_nBufferSize;
};

//_____________________________________________________________________ WaveIn
class WaveIn
{
public:
	WaveIn(void);
	virtual ~WaveIn(void);
	MMRESULT Open(UINT uDeviceID, LPCWAVEFORMATEX pwfx, DWORD_PTR dwCallback, DWORD_PTR dwInstance, DWORD fdwOpen)
	{
		return ::waveInOpen(&m_hWaveIn, uDeviceID, pwfx, dwCallback, dwInstance, fdwOpen);
	}
	 //This generates a message MM_WOM_OPEN
	MMRESULT OpenPCM8(HWND hWndParent, DWORD nSamplesPerSec, bool bStereo);
	MMRESULT OpenPCM8(DWORD nSamplesPerSec, bool bStereo, DWORD_PTR waveOutProc, DWORD_PTR dwCustomData);
	MMRESULT OpenPCM16(HWND hWndParent, DWORD nSamplesPerSec, bool bStereo);

	MMRESULT PrepareHeader(LPWAVEHDR pwh)
	{
		return ::waveInPrepareHeader(m_hWaveIn, pwh, sizeof(WAVEHDR));
	}

	MMRESULT PrepareHeader(Mm::WaveBuffer& waveBuffer)
	{
		return ::waveInPrepareHeader(m_hWaveIn, waveBuffer.m_pWaveHdr, sizeof(WAVEHDR));
	}

	MMRESULT UnprepareHeader(LPWAVEHDR pwh)
	{
		return ::waveInUnprepareHeader(m_hWaveIn, pwh, sizeof(WAVEHDR));
	}

	//MMRESULT UnprepareHeader(Mm::WaveBuffer& waveBuffer)
	//{
	//	return ::waveInUnprepareHeader(m_hWaveIn, waveBuffer.m_pWaveHdr, sizeof(WAVEHDR)) ;
	//}

	MMRESULT AddBuffer(LPWAVEHDR pwh)
	{
		return ::waveInAddBuffer(m_hWaveIn, pwh, sizeof(WAVEHDR));
	}

	MMRESULT AddBuffer(Mm::WaveBuffer& waveBuffer)
	{
		return ::waveInAddBuffer(m_hWaveIn, waveBuffer.m_pWaveHdr, sizeof(WAVEHDR));
	}

	MMRESULT Reset()
	{
		return ::waveInReset(m_hWaveIn);
	}
	MMRESULT Close() //This generates a message MM_WIM_CLOSE
	{
		return ::waveInClose(m_hWaveIn);
	}

	bool IsOpen()
	{
		return (m_hWaveIn != NULL);
	}

	void ClearHandle()
	{
		this->m_hWaveIn = NULL;
	}

	MMRESULT Start() // This will produce a MM_WIM_DATA
	{
		return waveInStart(m_hWaveIn);
	}

	wchar_t* GetErrorDescr(MMRESULT mmresult);
	HWAVEIN GetHandle()
		{ return m_hWaveIn;}
	void ListLineControls(void);
private:
	HWAVEIN  m_hWaveIn;
	WAVEFORMATEX m_wf;
	wchar_t m_pErrorDescr[MAXERRORLENGTH];
};

//_____________________________________________________________________ WaveOut
class WaveOut
{
public:
	WaveOut(void);
	virtual ~WaveOut(void);
	MMRESULT Open(UINT uDeviceID, LPCWAVEFORMATEX pwfx, DWORD_PTR dwCallback, DWORD_PTR dwInstance, DWORD fdwOpen)
	{
		return ::waveOutOpen(&m_hWaveOut, uDeviceID, pwfx, dwCallback, dwInstance, fdwOpen);
	}
	 //This generates a message MM_WOM_OPEN
	MMRESULT OpenPCM8(HWND hWndParent, DWORD nSamplesPerSec, bool bStereo);
	MMRESULT OpenPCM8(DWORD nSamplesPerSec, bool bStereo, DWORD_PTR waveOutProc, DWORD_PTR dwCustomData);
	MMRESULT OpenPCM16(HWND hWndParent, DWORD nSamplesPerSec, bool bStereo);
	MMRESULT PrepareHeader(Mm::WaveBuffer& waveBuffer);
	MMRESULT PrepareHeader(LPWAVEHDR pwh)
	{
		return ::waveOutPrepareHeader(m_hWaveOut, pwh, sizeof(WAVEHDR));
	}
	//MMRESULT UnprepareHeader(Mm::WaveBuffer& waveBuffer);
	MMRESULT UnprepareHeader(LPWAVEHDR pwh)
	{
		return ::waveOutUnprepareHeader(m_hWaveOut, pwh, sizeof(WAVEHDR));
	}
	MMRESULT Reset()
	{
		return ::waveOutReset(m_hWaveOut);
	}
	MMRESULT Close() //This generates a message MM_WOM_CLOSE
	{
		return ::waveOutClose(m_hWaveOut);
	}
	MMRESULT GetVolume(LPDWORD pdwVolume)
	{
		return ::waveOutGetVolume(m_hWaveOut, pdwVolume);
	}
	MMRESULT SetVolume(DWORD dwVolume)
	{
		return ::waveOutSetVolume(m_hWaveOut, dwVolume);
	}
	bool IsOpen()
	{
		return (m_hWaveOut != NULL);
	}
	MMRESULT Write(LPWAVEHDR pwh)
	{
		return ::waveOutWrite(m_hWaveOut, pwh, sizeof(WAVEHDR));
	}
	MMRESULT Write(Mm::WaveBuffer& wb)
	{
		MMRESULT r;
		r = waveOutWrite(m_hWaveOut, wb.m_pWaveHdr, sizeof(WAVEHDR));
		return r;
	}
	void ClearHandle()
	{
		this->m_hWaveOut = NULL;
	}
	wchar_t* GetErrorDescr(MMRESULT mmresult);
private:
	HWAVEOUT  m_hWaveOut;
	WAVEFORMATEX m_wf;
	wchar_t m_pErrorDescr[MAXERRORLENGTH];
};

//_____________________________________________________________________ IDataTransfer
// The buffer is used to moved the data
// return the number of bytes filled or return 0 to stop
class IDataTransfer
{
public:
	virtual void OnDataStarted() = 0;
	virtual void OnData(LPARAM lParam) = 0;
	virtual void OnDataStopped() = 0;
};

//_____________________________________________________________________ Dac
//Sends data to the DAC
class Dac : public Win::Control
{
public:
	Dac(void);
	virtual ~Dac(void);
	wchar_t* Start(unsigned int samplesRate, int channels,  int bitsPerSample, unsigned int bufferSize);
	bool Stop();
	bool IsPlaying();
	static void GetMaxLevel(LPSTR buffer, int bufferSize, bool bStereo, bool b16Bits, int& channel_1, int& channel_2);
	void DeleteBuffers(void);
	void SetIDataTransfer(Mm::IDataTransfer* idataTransfer);
	bool IsEvent(Win::Event& e, int notification);
private:
	Mm::WaveOut waveOut;
	bool bPlaying;
	bool bEnding;
	HWND hWndParent;
	int preparedBufferCount; 
	Mm::WaveBuffer wb[MM_DAC_NUM_BUFFER];
protected:
	bool showData;
	virtual void OnPaintControl(Win::Gdi& gdi);
	virtual bool EventHandler(Win::Event& e);
	void Window_WomOpen(Win::Event& e);
	void Window_WomClose(Win::Event& e);
	void Window_WomDone(Win::Event& e);
	unsigned int sampleRate;
	unsigned int bufferSize;
	bool b16Bits;
	unsigned int numChannels;
	int bytesPerSample;
	wchar_t * info;
	Mm::IDataTransfer * idataTransfer;
	void DrawDataRow(Win::Gdi& gdi, int row, const wchar_t* name, const wchar_t* value);
	int colWidth;
	virtual void RefreshProgressInfo();
	void RepaintRect(const int row, const int col);
};

//____________________________________________________________________ Adc
//Don't close the program while recording
//Captures data from the ADC
class Adc : public Win::Control
{
public:
	Adc(void);
	virtual ~Adc(void);
	//
	bool paused;
	bool Stop();
	wchar_t* Start(unsigned int sampleRate, int channels, int bitsPerSample, unsigned int bufferSize);
	bool IsRecording();
	void SetIDataTransfer(Mm::IDataTransfer* idataTransfer);
	bool IsEvent(Win::Event& e, int notification);
	double GetBufferDuration(); //in seconds
	static void GetMaxLevel(LPSTR buffer, unsigned int bufferSize, int channels, int bitsPerSample, int& out_channel_1, int& out_channel_2);
	static void GetRmsLevel(LPSTR buffer, unsigned int bufferSize, int channels, int bitsPerSample, double& out_channel_1, double& out_channel_2);
	static void GetZeroCrossings(LPSTR buffer, unsigned int bufferSize, int channels, int bitsPerSample, int& out_channel_1, int& out_channel_2);
	static void GetFrequency(LPSTR buffer, unsigned int bufferSize, int channels, int bitsPerSample, double& out_channel_1, double& out_channel_2);
	static void GetPhaseDifference(LPSTR buffer, unsigned int bufferSize, int channels, int& out_differenceCount); //Requires an sterero signal
	//
	static void GetMaxLevel(LPARAM lParam, int channels, int bitsPerSample, int& out_channel_1, int& out_channel_2);
	static void GetRmsLevel(LPARAM lParam, int channels, int bitsPerSample, double& out_channel_1, double& out_channel_2);
	static void GetZeroCrossings(LPARAM lParam, int channels, int bitsPerSample, int& out_channel_1, int& out_channel_2);
	static void GetFrequency(LPARAM lParam, int channels, int bitsPerSample, double& out_channel_1, double& out_channel_2);
	static void GetPhaseDifference(LPARAM lParam, int channels, int& out_differenceCount); //Requires an sterero signal
	void DeleteBuffers(void);
	static bool isSignDifferent(int x, int y);
	void OnPaintControl(Win::Gdi& gdi);
protected:
	void DrawDataRow(Win::Gdi& gdi, int index, const wchar_t* name, const wchar_t* value);
	bool showData;
	virtual void Window_WimOpen(Win::Event& e);
	virtual void Window_WimClose(Win::Event& e);
	virtual void Window_WimData(Win::Event& e);
	virtual bool EventHandler(Win::Event& e);
	Mm::IDataTransfer * idataTransfer;
	unsigned int samplesPerSec;
	wchar_t * info;
	bool b16Bits;
	bool bStereo;
	wchar_t fileName[1024];
private:
	Mm::WaveIn waveIn;
	bool bStopping;
	HWND hWndParent;
	
	void Destructor();
	Mm::WaveBuffer wb[MM_ADC_NUM_BUFFER];
	unsigned int bufferSize;
	int preparedBufferCount; 
};

//_____________________________________________________________________ Note
struct Note
{
	int note; //C_MIDI, D_MIDI, DS_MIDI, E_MIDI, ...
	int octave;
	int duration; //WHOLE_NOTE, HALF_NOTE, QUARTER_NOTE,...
};

//_____________________________________________________________________ MidiOut
class MidiOut : public Win::Control
{
public:
	MidiOut(void);
	~MidiOut(void);
	MMRESULT Open(UINT uDeviceID);
	MMRESULT Close(void);
	MMRESULT Reset(void);
	MMRESULT ShortMessage(int status, int channel, int data1, int data2);
	void PlayNote(int channel, int note, int octave);
	void StopNote(int channel, int note, int octave);
	void Play(int tempo);
	void StopSong();
	vector<Mm::Note> ch0;
	vector<Mm::Note> ch1;
private:
	void OnPaintControl(Win::Gdi& gdi);
	void Window_Timer(Win::Event& e);
	HMIDIOUT hMidiOut;
	int index_ch0;
	int index_ch1;
	int duration_ch0;
	int duration_ch1;
	bool active_ch0;
	bool active_ch1;
};

//____________________________________________________________________ Mixer
class Mixer
{
public:
	Mixer();
	~Mixer();
	wchar_t * Open(void);
	void Close(void);
	wchar_t* Set_Src_Waveout(DWORD level); // level: 0 to 65535
	wchar_t* Get_Src_Waveout(DWORD& level);
	wchar_t* Set_Src_Mic(DWORD level); // level: 0 to 65535
	wchar_t* Get_Src_Mic(DWORD& level);
	wchar_t* Set_Src_Line(DWORD level); // level: 0 to 65535
	wchar_t* Get_Src_Line(DWORD& level);
	wchar_t* Set_Main_Volume(DWORD level);
	wchar_t* Get_Main_Volume(DWORD& level);
private:
	HMIXER hMixer;
	DWORD src_waveout_control_id;
	DWORD main_volume_control_id;
	DWORD src_mic_control_id;
	DWORD src_line_control_id;
	wchar_t* Open_Src_Waveout(void);
	wchar_t * Open_Src_Mic(void);
	wchar_t * Open_Src_Line(void);
	wchar_t* Open_Main_Volume(void);
	wchar_t* GetLevel(DWORD& level, DWORD controlID);
	wchar_t* SetLevel(DWORD level, DWORD controlID);
	wchar_t* GetControlID(DWORD dwComponentType, DWORD& dwControlID);
};

//Mm::Mixer mixer;
//
//wchar_t* error = mixer.Open();
//
//if (error) this->MessageBox(error, L"mixer.Open");
//
//DWORD level;
//error = mixer.Get_Main_Volume(level);//mixer.Get_Src_Waveout(level);
//if (error) this->MessageBox(error, L"mixer.Get_Src_Waveout");
//wchar_t texto[256];
//_snwprintf(texto, 256, L"%d", level);
//this->MessageBox(texto);

//____________________________________________________________________ FileAdc
//Don't close the program while recording
//Captures data from the ADC to a FILE
class FileAdc : public Mm::Adc, public Mm::IDataTransfer
{
public:
	FileAdc(void);
	virtual ~FileAdc(void);
	wchar_t* Record(int samplesPerSec, int channels, int bitsPerSample, int bufferSize, const wchar_t* fileName);
	void Break(const wchar_t* fileName);//Starts storing data to a new file 
	//_______________________________________________________ Mm::IDataTransfer
	void OnDataStarted();
	virtual void OnData(LPARAM lParam);
	void OnDataStopped();
protected:
	Mm::WaveFile waveFile;
	bool isBreaking;
};


//____________________________________________________________________ FileDac
//Sends a file to the DAC
// The controls fires the events
// WIN_GETFILENAME to retrieve the name of the file to be played
// WIN_MODIFYSAMPLES to allow the user to modify the samples
class FileDac : public Mm::Dac, Mm::IDataTransfer
{
public:
	struct SongInfo
	{
		wchar_t songName[32];
		wchar_t album[32];
		wchar_t artist[32];
		wchar_t details[32];
	};
	struct DataInfo
	{
		CHAR * samples;
		int numSamples;
		int bitsPerSample;
		int numChannels;
		int sampleRate;
	};
	SongInfo si;
	FileDac(void);
	virtual ~FileDac(void);
	wchar_t* Play(unsigned int bufferSize, bool smoothFileTransition);
	void Reset();
	double GetRemainingSeconds(void);
	static void SeparateSongInfo(const wchar_t* filename, wchar_t separator, Mm::FileDac::SongInfo& si);
	static void CleanString(wstring& input, wchar_t* output);
	virtual void ModifySamples(CHAR* buffer, int numSamples, int bitsPerSample, int numChannels, int sampleRate); // Override to modify the data
	virtual bool GetFilename(wchar_t * filename, int filename_length); // Override this function and copy the name of the file in the filename variable
	//_______________________________________________________ Mm::IDataTransfer
	virtual void OnDataStarted();
	virtual void OnData(LPARAM lParam);
	virtual void OnDataStopped();
	//
	virtual void OnDataSimple(LPARAM lParam);
	virtual void OnDataSmooth(LPARAM lParam);
	//
	virtual void OnPaintControl(Win::Gdi& gdi);
protected:
	static void ClearSongInfo(Mm::FileDac::SongInfo& si);
	bool smoothFileTransition;
	Mm::WaveFile waveFileA;
	Mm::WaveFile waveFileB;
	int state;
	//int overlapIndex;
	double overlapGain;
	double overlapFactor;
	wchar_t filename[1024];
	CHAR *bufferA;
	CHAR *bufferB;
	virtual void RefreshProgressInfo();
	//Sys::File file;
};

//LRESULT MyProyect::OnCommand(Win::Event& e)
//{
//	int nID = LOWORD(e.wParam);
//	int notification = HIWORD(e.wParam);
// double level;
//	switch(nID)
//	{
//	case IDC_WaveFileCapturer: // This is only required to receive WIM notifications
//		{
//			switch(notification)
//			{
			//case MM_WIM_OPEN:
			//	this->SetWindowText(L"Open");
			//	return TRUE; // You must return TRUE notify the FileAdc To process the message
			//case MM_WIM_DATA:
//				level = 20.0*log10(lParam/32767.0);
			//	this->SetWindowText(L"Data");
			//	return TRUE;
			//case MM_WIM_CLOSE:
			//		this->SetWindowText(L"Close");
			//		return TRUE;
//			default:
//				return FALSE;
//			}
//		}
//		break;
//	case ID_RUN:


//LRESULT AudioGen::OnCommand(Win::Event& e)
//{
//	int nID = LOWORD(e.wParam);
//	int notification = HIWORD(e.wParam);
//	switch(nID)
//	{
//	case IDM_RECORD:
//		this->m_mfr.Record(hWnd, false, 44100, true, 16, L"C:\\hwy.wav");
//		break;
//	case IDM_STOP_RECORDING:
//		this->m_mfr.Stop();
//		break;
//	case IDM_EXIT:
//		DestroyWindow(hWnd);
//		break;
//	default:
//		return DefWindowProc(hWnd, WM_COMMAND, wParam, lParam);
//	}	
//	return 0;
//}


// Don't close the application while recording
// Disable the Close button while recording
//LRESULT MyApplication::OnSysCommand(Win::Event& e)
//{
//	switch(wParam)
//	{
//	case SC_CLOSE:
//		m_waveGenerator.OnSysCommandClose(e);
//		m_WaveFileCapturer.OnSysComandClose(e);
//		return TRUE;
//	}
//	return ::DefWindowProc(hWnd, WM_SYSCOMMAND, wParam, lParam);
//}

//____________________________________________________________________ FmDemodulator
class FmDemodulator
{
public:
	FmDemodulator(void);
	virtual ~FmDemodulator(void);
	bool Create(unsigned int bufferSize, bool isStereo, bool is16Bits);
	int Demodulate(LPSTR buffer, unsigned int bytesRecorded);
	int Demodulate(LPARAM lParam);
	int* GetLeft(void);
	int* GetRight(void);
private:
	int* dataLeft;
	int* dataRight;
	unsigned int bufferSize;
	unsigned int data_size;
	bool isStereo;
	bool is16Bits;
	void Delete(void);
};

} // End of namespace Mm

#endif
//______________________________________________________ namespace Mm::End

namespace Game //________________________________________ namespace Game::Ini
{

//_____________________________________________________________________ VextexRhw
struct VertexRhw
{
	float x, y, z, rhw; 
	DWORD color; 
};

//_____________________________________________________________________ Vextex
struct Vertex
{
	float x, y, z; 
	DWORD color;
};

//_____________________________________________________________________ Object2D
class Object2D
{
public:
	Object2D();
	virtual ~Object2D();
	//
	void SetPositionX(float x);
	float GetPositionX();
	__declspec( property( get=GetPositionX, put=SetPositionX) ) float PositionX;
	//
	void SetPositionY(float y);
	float GetPositionY();
	__declspec( property( get=GetPositionY, put=SetPositionY) ) float PositionY;
	//
	void SetRotationAngle(float radians);
	float GetRotationAngle();
	__declspec( property( get=GetRotationAngle, put=SetRotationAngle) ) float RotationAngle;
	//
	void SetMinX(float minX);
	float GetMinX();
	__declspec( property( get=GetMinX, put=SetMinX) ) float MinX;
	//
	void SetMaxX(float maxX);
	float GetMaxX();
	__declspec( property( get=GetMaxX, put=SetMaxX) ) float MaxX;
	//
	void SetMinY(float minY);
	float GetMinY();
	__declspec( property( get=GetMinY, put=SetMinY) ) float MinY;
	//
	void SetMaxY(float maxY);
	float GetMaxY();
	__declspec( property( get=GetMaxY, put=SetMaxY) ) float MaxY;
	//
	void SetType(int type);
	int GetType();
	__declspec( property( get=GetType, put=SetType) ) int Type;
	//
	void SetVisible(bool visible);
	bool IsVisible();
	__declspec( property( get=IsVisible, put=SetVisible) ) bool Visible;
	//
	bool IsCollision(Game::Object2D& object);
	virtual void UpdateBounds(float deltaTimeSec);
	vector<Sys::Bound2D>& GetBounds();
	//
#ifdef WIN_DIRECTX
	virtual void Render(IDirect3DDevice9Ptr d3dDevice, float deltaTimeSec);
#else
	virtual void Render(Win::Gdi& gdi, float deltaTimeSec);
#endif
protected:
#ifdef WIN_DIRECTX
	virtual void InternalRender(IDirect3DDevice9Ptr d3dDevice, float deltaTimeSec);
#else
	virtual void InternalRender(Win::Gdi& gdi, float deltaTimeSec);
#endif
	virtual void ComputeState(float deltaTimeSec, float& out_nextPositionX, float& out_nextPositionY, float& out_nextAngle, float& out_nextSpeed);
	void UpdateBounds(float positionX, float positionY, float rotationAngle);
	float _x;
	float _y;
	int _type;
	bool _visible;
	float _rotationAngle;
	float _minX;
	float _maxX;
	float _minY;
	float _maxY;
	float _speed;
	vector<Sys::Point2D> shape;
	vector<Sys::Bound2D> _bounds;
};

//_____________________________________________________________________ Mobile2D
class Mobile2D : public Object2D
{
public:
	Mobile2D();
	virtual ~Mobile2D();
	//
	void SetSpeed(float speed);
	float GetSpeed();
	__declspec( property( get=GetSpeed, put=SetSpeed) ) float Speed;
	//
	void SetMaxSpeed(float maxSpeed);
	float GetMaxSpeed();
	__declspec( property( get=GetMaxSpeed, put=SetMaxSpeed) ) float MaxSpeed;
	//
	void SetAcceleration(float acceleration);
	float GetAcceleration();
	__declspec( property( get=GetAcceleration, put=SetAcceleration) ) float Acceleration;
	//
	void SetMaxAcceleration(float maxAcceleration);
	float GetMaxAcceleration();
	__declspec( property( get=GetMaxAcceleration, put=SetMaxAcceleration) ) float MaxAcceleration;
	//
	void SetRotationSpeed(float rotationSpeed);
	float GetRotationSpeed();
	__declspec( property( get=GetRotationSpeed, put=SetRotationSpeed) ) float RotationSpeed;
	//
	void SetMaxRotationSpeed(float maxRotationSpeed);
	float GetMaxRotationSpeed();
	__declspec( property( get=GetMaxRotationSpeed, put=SetMaxRotationSpeed) ) float MaxRotationSpeed;
	//
	virtual void UpdateBounds(float deltaTimeSec);
protected:
	void ComputeState(float deltaTimeSec, float& out_nextPositionX, float& out_nextPositionY, float& out_nextAngle, float& out_nextSpeed);
	float _maxSpeed;
	float _acceleration;
	float _maxAcceleration;
	float _rotationSpeed;
	float _maxRotationSpeed;
};

//_____________________________________________________________________ Game::Window
class Window : public Win::Window
{
public:
	Window(void);
	~Window(void);
	virtual bool RenderScene(Win::Gdi& gdi)=0;
	virtual int MessageLoop(WORD aceleratorsID);
protected:
	DWORD currentTime;
	float currentTimeSec;
	float deltaTimeSec;
	bool isGameMode;
	virtual void GetRegisterClass(WNDCLASSEX& wcex);
	virtual void Window_Paint(Win::Event& e);
	virtual void Window_Size(Win::Event& e);
	virtual void Window_Destroy(Win::Event& e);
	virtual void Window_Activate(Win::Event& e);
	virtual void Window_KeyDown(Win::Event& e);
	virtual void Window_KeyUp(Win::Event& e);
	virtual void Window_SysCommand(Win::Event& e);
	bool	keyboard[256];
	bool isActive;
	Win::DDBitmap bitmap;
};

//_____________________________________________________________________ DxWindow
class DxWindow : public Win::Window
{
public:
	DxWindow(void);
	~DxWindow(void);
#ifdef WIN_DIRECTX
	IDirect3D9Ptr d3d;
	IDirect3DDevice9Ptr d3dDevice;
#endif
	virtual bool RenderScene()=0;
	virtual int MessageLoop(WORD aceleratorsID);
protected:
	DWORD currentTime;
	float currentTimeSec;
	float deltaTimeSec;
	bool isGameMode;
	virtual void GetRegisterClass(WNDCLASSEX& wcex);
	virtual void Window_Destroy(Win::Event& e);
};

} //____________________________________________________ namespace Game::End

//______________________________________________________ namespace Ogl::Ini
#ifdef WIN_OPENGL_SUPPORT
namespace Ogl{
//_____________________________________________________________________ ViewManager
class ViewManager
{
public:
	ViewManager(void);
	~ViewManager(void);
	void incrementX(void);
	void decrementX(void);
	void incrementY(void);
	void decrementY(void);
	void incrementZ(void);
	void decrementZ(void);
	void incrementAngleXZ(void);
	void decrementAngleXZ(void);
	//
	void AdjustView(); //Call this inside RenderScene
protected:
	double angleXZ;
	double deltaAngleXZ;
	double x;
	double y;
	double z;
	double deltaX;
	double deltaY;
	double deltaZ;
};

//_____________________________________________________________________ Object
class Object
{
public:
	Object(void);
	~Object(void);
	GLuint GetID();
	operator GLuint() 
		{return this->id;}
protected:
	GLuint id;
};

//_____________________________________________________________________ Lists
class Lists : public Ogl::Object
{
public:
	Lists(void);
	~Lists(void);
	GLuint Generate(GLsizei size);
	void Delete(void);
protected:
	GLsizei size;
};

//_____________________________________________________________________ Texture
class Texture : public Ogl::Object
{
public:
	Texture(void);
	~Texture(void);
	void Delete(void);
	wchar_t* CreateFromBitmap(const wchar_t* filename);
	wchar_t* CreateFromBitmap(const wchar_t* filename, GLfloat minFilter, GLfloat magFilter, GLint components);
	GLuint GetWidth();
	GLuint GetHeight();
private:
	GLuint width;
	GLuint height;
};

//_____________________________________________________________________ Font
class Font : public Ogl::Lists
{
public:
	Font(void);
	~Font(void);
	wchar_t* CreateFromBitmap(const wchar_t* filename);
private:
	Ogl::Texture texture;
	const GLuint ROWS;
	const GLuint COLS;
};

//_____________________________________________________________________ GLWindow
class GLWindow : public Win::Window
{
public:
	GLWindow(void);
	~GLWindow(void);
	bool ActivateFullScreen();
	wchar_t* SetupGL(PIXELFORMATDESCRIPTOR& pfd);
	void DestroyGL();
	DWORD bitsPerPixel;
	void SetGLSize();
	bool	keyboard[256];
	bool isActive;
	Ogl::ViewManager viewManager;
	void DrawCube(void);
	void Print(Ogl::Font& font, const wchar_t * text);
	void Print(GLdouble x, GLdouble y, Ogl::Font& font, const wchar_t * text); //To be called inside RenderScene
	//
	void DrawFramesPerSecond(GLdouble x, GLdouble y, Ogl::Font& font);
	virtual bool RenderScene()=0;
	virtual int MessageLoop(WORD aceleratorsID);
protected:
	virtual void Window_Size(Win::Event& e);
	virtual void Window_Destroy(Win::Event& e);
	virtual void Window_Activate(Win::Event& e);
	virtual void Window_KeyDown(Win::Event& e);
	virtual void Window_KeyUp(Win::Event& e);
	virtual void Window_SysCommand(Win::Event& e);
private:
	bool isFullScreen;
	HDC hDC; // Permanent Device Context
	HGLRC hGLRC;// Permanent Rendering Context
	//
	int frames;
	bool displayedFramesPerSecond;
};

//struct TgaHeader
//{
//	__int8  identsize;          // size of ID field that follows 18 byte header (0 usually)
//	__int8  colourmaptype;      // type of colour map 0=none, 1=has palette
//	__int8  imagetype;          // type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed
//	__int16 colourmapstart;     // first colour map entry in palette
//	__int16 colourmaplength;    // number of colours in palette
//	__int8  colourmapbits;      // number of bits per palette entry 15,16,24,32
//	__int16 xstart;             // image x origin
//	__int16 ystart;             // image y origin
//	__int16 width;              // image width in pixels
//	__int16 height;             // image height in pixels
//	__int8  bitsPerPixel;               // image bits per pixel 8,16,24,32
//	__int8  descriptor;         // image descriptor bits (vh flip bits)
//	// pixel data follows header
//};

} // End of namespace Ogl
#endif
//______________________________________________________ namespace Ogl::End


//______________________________________________________ namespace Com::Ini
namespace Com
{

//___________________________________________________________________ Container
// Example of how to find help about a function of IOleClientSite:
//    1. Type anywhere in the program IOleClientSite::Function
//    2. Press F1.
class Container : 
	public Win::Window, 
	public IDispatch,
	public IOleClientSite, 
	public IOleControlSite,
	public IAdviseSink,
	public IServiceProvider,
	public IOleInPlaceSiteWindowless, // >IOleInPlaceSiteEx>IOleInPlaceSite>IOleWindow
	public IOleInPlaceFrame, // >IOleInPlaceUIWindow>IOleWindow
	public IOleContainer, // >IParseDisplayName
	public IBindHost
{
public:
	Container();
	~Container();
	Com::Object comobj;
	IUnknownPtr unknown;
	COLORREF GetBackColor();
	virtual void SetBackColor(COLORREF color);
	__declspec( property( get=GetBackColor, put=SetBackColor ) ) COLORREF BackColor;
	//
	COLORREF GetTextColor();
	virtual void SetTextColor(COLORREF color);
	__declspec( property( get=GetTextColor, put=SetTextColor ) ) COLORREF TextColor;
	//
	bool GetUserMode();
	virtual void SetUserMode(bool userMode);
	__declspec( property( get=GetUserMode, put=SetUserMode ) ) bool UserMode;
	//
	HRESULT DoVerb(long verb);
	//
	HRESULT Activate();
	HRESULT Activate(vector<Property>& properties);
	HRESULT OleObjectQueryInterface(REFIID riid, void** pvvObject);
	void Delete(void);
	//
	void SetVisible(bool visible);
	bool IsVisible();
	__declspec( property( get=IsVisible, put=SetVisible ) ) bool Visible;
	//
    void SetAllowResize(bool resizable);
	bool GetAllowResize();
	__declspec( property( get=GetAllowResize, put=SetAllowResize) ) bool AllowResize;
	//
	wstring hostUrl;

	static void DisplayInterfaceFunctions(HWND hWnd, Com::Object& object);
	//
	// text may be a ProgID or a ClassID in the format {...}
	static bool GetFuncInfo(HWND hWnd, const wchar_t* text, list<Com::FuncInfo>& result);
	//
	static int GetActivexInfo(vector<Com::ActiveXInfo>& info);
protected:
	OLE_COLOR _backColor;
	OLE_COLOR _textColor;
	bool _userMode;
	LCID _localeId;
	struct ControlInfo
	{
		IOleObjectPtr oleObject;
		IViewObjectPtr viewObject;
		IViewObject2Ptr viewObject2;
		IViewObjectExPtr viewObjectEx;
		IDataObjectPtr dataObject;
		IUnknownPtr unknown;
		IOleInPlaceObjectPtr oleInPlaceObject;
		IOleInPlaceObjectWindowlessPtr oleInPlaceObjectWindowless;
	};
	static bool m_bRegistered;
	ControlInfo activex;
	const wchar_t * GetClassName(void){return L"WINCOM_CONTAINER";}
	void Window_Open(Win::Event& e);
	void Window_Destroy(Win::Event& e);
	void Window_Paint(Win::Event& e);
	void Window_Size(Win::Event& e);
	void Window_LButtonDown(Win::Event& e);
	void Window_RButtonDown(Win::Event& e);
	//___________________________________________________
	int refCount;
	//___________________________________________________
	bool visible;
	bool allowResize;
	DWORD miscStatus;
	RECT rectPosition;
	bool inplaceActive;
	bool isInPlace;
	//
	//HRESULT Activate();
	HRESULT InplaceActivate();
	HRESULT SetActivexRect(const RECT& rc);
	HRESULT SetExtent();
	void SetActivate(bool activate);
	//______________________________________________ IUnknown
	STDMETHOD (QueryInterface) (REFIID iid, void**ppvObject);
	STDMETHOD_(ULONG, AddRef) ();
	STDMETHOD_(ULONG, Release) ();
	//_______________________________________________________ IDispatch
	STDMETHOD (GetTypeInfoCount) (UINT *pctinfo);
	STDMETHOD (GetTypeInfo) (UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo);
	STDMETHOD (GetIDsOfNames) (REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId);
	STDMETHOD (Invoke) (DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);
	//_______________________________________________________ IOleClientSite
	STDMETHOD (SaveObject) ();
	STDMETHOD (GetMoniker) (DWORD dwA, DWORD dwW, IMoniker** pMoniker);
	STDMETHOD (GetContainer) (IOleContainer** pOleContainer);
	STDMETHOD (ShowObject) ();
	STDMETHOD (OnShowWindow) (BOOL fShow);
	STDMETHOD (RequestNewObjectLayout) ();
	void ProcessPaint(HDC hdc, LPCRECT lpClipRect);
	bool InsideClippingRegion(const RECT& rcClip) const;
	//_______________________________________________________ IOleControlSite
	STDMETHOD (OnControlInfoChanged) (void);
	STDMETHOD (LockInPlaceActive) (BOOL fLock);
	STDMETHOD (GetExtendedControl) (IDispatch **ppDisp);
	STDMETHOD (TransformCoords) (POINTL *pPtlHimetric, POINTF *pPtfContainer, DWORD dwFlags);
	STDMETHOD (TranslateAccelerator) (MSG *pMsg, DWORD grfModifiers);
	STDMETHOD (OnFocus) (BOOL fGotFocus);
	STDMETHOD (ShowPropertyFrame) (void);
	//_______________________________________________________ IAdviseSink
	STDMETHOD_ (void, OnDataChange) (FORMATETC *pFormatEtc, STGMEDIUM *pStgMedium);
	STDMETHOD_ (void, OnViewChange) (DWORD dwAspect, LONG lIndex);
	STDMETHOD_ (void, OnRename) (IMoniker * pMoniker);
	STDMETHOD_ (void, OnSave) ();
	STDMETHOD_ (void, OnClose) ();
	//_______________________________________________________ IServiceProvider
	STDMETHOD (QueryService) (REFGUID guidService, REFIID riid, void **ppvObject);
	//_______________________________________________________ IOleInPlaceSiteWindowless
	STDMETHOD (CanWindowlessActivate) ();
	STDMETHOD (GetCapture) ();
	STDMETHOD (SetCapture) (BOOL fCapture);
	STDMETHOD (GetFocus) ();
	STDMETHOD (SetFocus) (BOOL fFocus);
	STDMETHOD (GetDC) (LPCRECT pRect, DWORD grfFlags, HDC *phDC);
	STDMETHOD (ReleaseDC) (HDC hDC);
	STDMETHOD (InvalidateRect) (LPCRECT pRect, BOOL fErase);
	STDMETHOD (InvalidateRgn) (HRGN hRGN, BOOL fErase);
	STDMETHOD (ScrollRect) (INT dx, INT dy, LPCRECT pRectScroll, LPCRECT pRectClip);
	STDMETHOD (AdjustRect) (LPRECT prc);
	STDMETHOD (OnDefWindowMessage) (UINT msg, WPARAM wParam, LPARAM lParam, LRESULT *plResult);
	//_______________________________________________________ IOleInPlaceSiteEx
	STDMETHOD (OnInPlaceActivateEx) (BOOL *pfNoRedraw, DWORD dwFlags);
	STDMETHOD (OnInPlaceDeactivateEx) (BOOL fNoRedraw);      
	STDMETHOD (RequestUIActivate) (void);
	//_______________________________________________________ IOleInPlaceSite
	STDMETHOD (CanInPlaceActivate) ();
	STDMETHOD (OnInPlaceActivate) ();
	STDMETHOD (OnUIActivate) ();
	STDMETHOD (GetWindowContext) (IOleInPlaceFrame** ppFrame, IOleInPlaceUIWindow **ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo);
	STDMETHOD (Scroll) (SIZE scrollExtant);
	STDMETHOD (OnUIDeactivate) (BOOL fUndoable);
	STDMETHOD (OnInPlaceDeactivate) ();
	STDMETHOD (DiscardUndoState) ();
	STDMETHOD (DeactivateAndUndo) ();
	STDMETHOD (OnPosRectChange) (LPCRECT rc);
	//_______________________________________________________ IOleWindow
	STDMETHOD (GetWindow) (HWND *phWnd);
	STDMETHOD (ContextSensitiveHelp) (BOOL f);
	//_______________________________________________________ IOleInPlaceFrame
	STDMETHOD (InsertMenus) (HMENU hmenuShared, LPOLEMENUGROUPWIDTHS lpMenuWidths);
	STDMETHOD (SetMenu) (HMENU hmenuShared, HOLEMENU holemenu, HWND hwndActiveObject);
	STDMETHOD (RemoveMenus) (HMENU hmenuShared);
	STDMETHOD (SetStatusText) (LPCOLESTR pszStatusText);
	STDMETHOD (EnableModeless) (BOOL fEnable);
	STDMETHOD (TranslateAccelerator) (LPMSG lpmsg, WORD wID);
	//_______________________________________________________ IOleInPlaceUIWindow
	STDMETHOD (GetBorder) (LPRECT lprectBorder);    
	STDMETHOD (RequestBorderSpace) (LPCBORDERWIDTHS pborderwidths);
	STDMETHOD (SetBorderSpace) (LPCBORDERWIDTHS pborderwidths);   
	STDMETHOD (SetActiveObject) (IOleInPlaceActiveObject *pActiveObject, LPCOLESTR pszObjName);
	//______________________________________________________ IOleContainer
	STDMETHOD (EnumObjects) (DWORD grfFlags, IEnumUnknown **ppenum);     
	STDMETHOD (LockContainer) (BOOL fLock);
	//______________________________________________________ IParseDisplayName
	STDMETHOD (ParseDisplayName) (IBindCtx *pbc, LPOLESTR pszDisplayName, ULONG *pchEaten, IMoniker **ppmkOut);
	//_______________________________________________________ IBindHost
	STDMETHOD (CreateMoniker) (LPOLESTR szName, IBindCtx *pBC, IMoniker **ppmk, DWORD dwReserved);
	STDMETHOD (MonikerBindToStorage) (IMoniker *pMk, IBindCtx *pBC, IBindStatusCallback *pBSC, REFIID riid, void **ppvObj);    
	STDMETHOD (MonikerBindToObject) (IMoniker *pMk, IBindCtx *pBC, IBindStatusCallback *pBSC, REFIID riid, void **ppvObj);
};

}//______________________________________________________ namespace Com::End