#include "StdAfx.h"
#include "WintemplaWin.h"
/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.  I ACCEPT NO LIABILITY FOR ANY DAMAGE OR LOSS
   OF BUSINESS THAT THIS SOFTWARE MAY CAUSE.

   WintemplaWin.cpp
 
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

namespace Win //________________________________________ namespace Win::Ini
{

//_____________________________________________________________________ IParent


#ifdef WIN_GDI_PLUS_ON
//_____________________________________________________________________GdiPlusOn
GdiPlusOn::GdiPlusOn(void)
{
	Gdiplus::GdiplusStartup(&m_token, &m_si, NULL);
}

GdiPlusOn::~GdiPlusOn(void)
{
	Gdiplus::GdiplusShutdown(m_token);
}

//BMP 
//GIF 
//JPEG 
//PNG 
//TIFF 
//GDI+ also has built-in decoders that support the following file types: 
//WMF 
//EMF 
//ICON 
int GdiPlusOn::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if(size == 0) return -1;  // Failure

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL) return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);
	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}    
	}
	free(pImageCodecInfo);
	return -1;  // Failure
}
#endif

//_____________________________________________________________________Gdi
void Gdi::Constructor()
{
	m_pBrush = NULL;
	m_pPen = NULL;
	m_pFont = NULL;
	//
	m_hBrushOriginal = NULL;
	m_hPenOriginal = NULL;
	m_hFontOriginal = NULL;
}

Gdi::Gdi(PAINTSTRUCT& ps, bool createGdiplusObject)
{
	this->Constructor();
	m_type = Win::Gdi::FromPainstruct;
	m_ps = ps;
	m_hdc = ps.hdc;
	m_hWnd = NULL;
	::GetTextMetrics(m_hdc, &tm);
	//
#ifdef WIN_GDI_PLUS_ON 
	pGdiPlus = NULL;
	if (createGdiplusObject)
	{
		pGdiPlus = new Gdiplus::Graphics(m_hdc);
	}
#endif
}

Gdi::Gdi(Win::DDBitmap& ddbitmap, RECT& rcPaint, bool createGdiplusObject)
{
	this->Constructor();
	m_type = Win::Gdi::FromPainstruct;
	//
	m_ps.rcPaint = rcPaint;
	//SIZE size = ddbitmap.GetSize();
 //   m_ps.rcPaint.left = rcPaint;
	//m_ps.rcPaint.top = 0;
	//m_ps.rcPaint.right = size.cx;
	//m_ps.rcPaint.bottom = size.cy;
	//
	m_ps.hdc = ddbitmap.GetBitmapDC();
	m_hdc = ddbitmap.GetBitmapDC();
	m_hWnd = NULL;
	::GetTextMetrics(m_hdc, &tm);
	//
#ifdef WIN_GDI_PLUS_ON 
	pGdiPlus = NULL;
	if (createGdiplusObject)
	{
		pGdiPlus = new Gdiplus::Graphics(m_hdc);
	}
#endif
}

Gdi::Gdi(Sys::Graphics& graphics, bool createGdiplusObject)
{
	this->Constructor();
	graphics.CreateBitmap();
	m_type = Win::Gdi::FromPainstruct;
	//
	m_ps.rcPaint.left = 0;
	m_ps.rcPaint.top = 0;
	m_ps.rcPaint.right = graphics.GetWidth();
	m_ps.rcPaint.bottom = graphics.GetHeight();
	//
	m_ps.hdc = graphics.hdc;
	m_hdc = graphics.hdc;
	m_hWnd = NULL;
	::GetTextMetrics(m_hdc, &tm);
	//
#ifdef WIN_GDI_PLUS_ON 
	pGdiPlus = NULL;
	if (createGdiplusObject)
	{
		pGdiPlus = new Gdiplus::Graphics(m_hdc);
	}
#endif
}


Gdi::Gdi(Win::Metafile& metafile, bool createGdiplusObject)
{
	this->Constructor();
	m_type = Win::Gdi::FromPainstruct;
	//
	ENHMETAHEADER head;
	metafile.GetHeader(head);
	m_ps.rcPaint.left = head.rclBounds.left;
	m_ps.rcPaint.top = head.rclBounds.top;
	m_ps.rcPaint.right = head.rclBounds.right;
	m_ps.rcPaint.bottom = head.rclBounds.bottom;
	//
	m_ps.hdc = metafile.GetHDC();
	m_hdc = metafile.GetHDC();
	m_hWnd = NULL;
	::GetTextMetrics(m_hdc, &tm);
	//
#ifdef WIN_GDI_PLUS_ON 
	pGdiPlus = NULL;
	if (createGdiplusObject)
	{
		pGdiPlus = new Gdiplus::Graphics(m_hdc);
	}
#endif
}


Gdi::Gdi(HWND hWnd, bool bOnPaint, bool createGdiplusObject)
{
	this->Constructor();
	if (bOnPaint)
	{
		m_type = Win::Gdi::BeginEndPaint;
		m_hdc = ::BeginPaint(hWnd, &m_ps);
		m_hWnd = hWnd;
	}
	else
	{
		m_type = Win::Gdi::CaptureReleaseDc;
		m_hdc = ::GetDC(hWnd);
		::ZeroMemory(&m_ps, sizeof(PAINTSTRUCT));
		RECT rect;
		::GetWindowRect(hWnd, &rect);
		m_ps.rcPaint.left = 0;
		m_ps.rcPaint.top = 0;
		m_ps.rcPaint.right = rect.right - rect.left;
		m_ps.rcPaint.bottom = rect.bottom-rect.top;
		m_ps.hdc = m_hdc;
		m_hWnd = hWnd;
	}
	::GetTextMetrics(m_hdc, &tm);
	//
#ifdef WIN_GDI_PLUS_ON 
	pGdiPlus = NULL;
	if (createGdiplusObject)
	{
		pGdiPlus = new Gdiplus::Graphics(m_hdc);
		//if (pGdiPlus == NULL)
		//{
		//	Sys::DisplayLastError(hWnd, L"Gdiplus Error");
		//}
	}
#endif

}

#ifdef WIN_GDI_PLUS_ON 
	Gdiplus::Graphics& Gdi::GetGdiPlus()
	{
		return *pGdiPlus;
	}
#endif

//____________________________________________________________________ TextExtent
TextExtent::TextExtent(HDC hdc)
{
	height = 0;
	//
	double  dScale = 0;
	HFONT hFont, hFontDesign;
	int i = 0;
	LOGFONT lf;
	OUTLINETEXTMETRIC otm;
	double dHeight = 0;
	int nWidths[256];

	hFont = (HFONT)::GetCurrentObject (hdc, OBJ_FONT);
	::GetObject (hFont, sizeof (LOGFONT), &lf);
	dHeight = (double)(-lf.lfHeight);

	otm.otmSize = sizeof (OUTLINETEXTMETRIC);
	GetOutlineTextMetrics (hdc, sizeof (OUTLINETEXTMETRIC), &otm);

	//__________________________________Create a new font based on the design size
	lf.lfHeight = - (int) otm.otmEMSquare;
	lf.lfWidth  = 0;
	hFontDesign = ::CreateFontIndirect (&lf);

	//__________________________________Select the font into the DC and get the character widths
	::SaveDC (hdc);
	::SetMapMode (hdc, MM_TEXT);
	::SelectObject (hdc, hFontDesign);

	::GetCharWidth (hdc, 0, 255, nWidths);
	::SelectObject (hdc, hFont);
	::RestoreDC (hdc, -1);

	//_________________________________Scale the widths and store as floating point values
	dScale = dHeight /(double) otm.otmEMSquare;

	for (i = 0; i <= 255; i++)
		widths[i] = dScale * nWidths[i];

	height = dHeight * 1.15;

	// Clean up
	::DeleteObject (hFontDesign);

	//::GetCharWidthFloat(hdc, 0, 255, widths);
}

TextExtent::~TextExtent(void)
{
}

//DEVICE_DEFAULT_FONT
//DEFAULT_GUI_FONT
//SYSTEM_FONT
LONG TextExtent::GetHeight(int font)
{
	LOGFONT lf;
	HFONT h = (HFONT)::GetStockObject(font);
	::GetObject(h, sizeof (LOGFONT), &lf);
	return -lf.lfHeight;
}

double TextExtent::GetWidth(const wchar_t * text)
{
	return this->GetWidth(text, lstrlen(text));
}

double TextExtent::GetWidth(const wchar_t * text, int length)
{
	double width = 0;
	for (int i = 0; i<length; i++) width += widths[text[i]%256];
	return width;
}

//_______________________________________________________________ Gdi

Gdi::~Gdi(void)
{
	Delete();
}

void Gdi::Delete()
{
	#ifdef WIN_GDI_PLUS_ON 
	if (pGdiPlus) delete pGdiPlus;
#endif
	//*************************************************** Restore Brush
	if (m_pBrush) m_pBrush->Update(NULL);
	if (m_hBrushOriginal) ::SelectObject(m_hdc, m_hBrushOriginal);

	//*************************************************** Restore Pen
	if (m_pPen) m_pPen->Update(NULL);
	if (m_hPenOriginal) ::SelectObject(m_hdc, m_hPenOriginal);

	//*************************************************** Restore Font
	if (m_pFont) m_pFont->Update(NULL);
	if (m_hFontOriginal) ::SelectObject(m_hdc, m_hFontOriginal);

	switch(m_type)
	{
	case Win::Gdi::BeginEndPaint:
		::EndPaint(m_hWnd, &m_ps);
		break;
	case Win::Gdi::CaptureReleaseDc:
		::ReleaseDC(m_hWnd, m_hdc);
		break;
	case Win::Gdi::FromPainstruct:
		break;
	}
}

void Gdi::TextOut(int x, int y, const wchar_t* text, const RECT& rect, unsigned int options) // ETO_CLIPPED, ETO_OPAQUE, 
{
	::ExtTextOut(m_hdc, x, y, options, &rect, text, wcslen(text), NULL);

}

void Gdi::DrawCompatibleBitmap(Win::DDBitmap& ddbitmap, int x, int y)
{
	::BitBlt(m_hdc, x, y, ddbitmap.GetWidth(), ddbitmap.GetHeight(), 
		ddbitmap.GetBitmapDC(), 0, 0, SRCCOPY);
}

void Gdi::DrawCompatibleBitmap(Win::DDBitmap& ddbitmap, int x, int y, int targetWidth, int targetHeight)
{
	int strechMode = ::SetStretchBltMode(m_hdc, COLORONCOLOR);

	//::BitBlt(m_hdc, x, y, ddbitmap.GetWidth(), ddbitmap.GetHeight(), 
	//	ddbitmap.GetBitmapDC(), x, y, SRCCOPY);

	::StretchBlt(m_hdc, x, y, targetWidth, targetHeight, ddbitmap.GetBitmapDC(), x, y, 
		ddbitmap.GetWidth(), ddbitmap.GetHeight(), SRCCOPY);

	::SetStretchBltMode(m_hdc, strechMode);
}

void Gdi::DrawGraphics(Sys::Graphics& graphics, int x, int y)
{
	int width, height;
	HDC hdcBitmap;
	graphics.GetInfo(width, height, hdcBitmap);
	::BitBlt(m_hdc, x, y, width, height, hdcBitmap, 0, 0, SRCCOPY);
}

void Gdi::DrawGraphics(Sys::Graphics& graphics, int x, int y, int width, int height)
{
	int widthBitmap, heightBitmap;
	HDC hdcBitmap;
	graphics.GetInfo(widthBitmap, heightBitmap, hdcBitmap);
	int strechMode = ::SetStretchBltMode(m_hdc, COLORONCOLOR);
	::StretchBlt(m_hdc, x, y, width, height, hdcBitmap, x, y, widthBitmap, heightBitmap, SRCCOPY);
	::SetStretchBltMode(m_hdc, strechMode);
}

void Gdi::DrawDoubleBuffer(Win::DDBitmap& ddbitmap)
{
	const int width = m_ps.rcPaint.right - m_ps.rcPaint.left;
	const int height = m_ps.rcPaint.bottom - m_ps.rcPaint.top;

	::BitBlt(m_hdc, m_ps.rcPaint.left, m_ps.rcPaint.top, width, height, ddbitmap.GetBitmapDC(), 
		m_ps.rcPaint.left, m_ps.rcPaint.top, SRCCOPY);
}

void Gdi::DrawBitmap(Win::DDBitmap& ddbitmap, int x, int y)
{
	if (ddbitmap.GetHBITMAP() == NULL) return;
	HDC hdcMem = CreateCompatibleDC(m_hdc);
	::SelectObject(hdcMem, ddbitmap.hBitmap);
	::BitBlt(m_hdc, x, y, ddbitmap.bitmap.bmWidth, ddbitmap.bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
	::DeleteDC(hdcMem);
	hdcMem = NULL;
}

void Gdi::DrawBitmap(Win::DDBitmap& ddbitmap, int x, int y, int width, int height, bool isColor)
{
	int widthDevice = 0, heightDevice =0;

	if (isColor) 
	{
		::SetStretchBltMode(m_hdc, COLORONCOLOR);
	}
	else 
	{
		::SetStretchBltMode(m_hdc, WHITEONBLACK);
	}

	HDC hdcMem = ::CreateCompatibleDC(m_hdc);
	::SelectObject(hdcMem, ddbitmap.hBitmap);
	//if (preventDistortion)
	//{
	//	const double scaleWidth = width/(double)bitmap.bmWidth;
	//	const double scaleHeight = height/(double)bitmap.bmHeight;
	//	const double scale = MINIMUM(scaleWidth, scaleHeight);
	//	if (scaleWidth>scaleHeight)
	//	{
	//		widthDevice = width;
	//		heightDevice = (int)(width*scale+0.5);
	//	}
	//	else
	//	{
	//		widthDevice = (int)(height*scale+0.5);
	//		heightDevice = height;
	//	}
	//}
	//else
	//{
	//	widthDevice = width;
	//	heightDevice = height;
	//}
	::StretchBlt(m_hdc, x, y, width, height, hdcMem, 0, 0, ddbitmap.bitmap.bmWidth, ddbitmap.bitmap.bmHeight, SRCCOPY);
	::DeleteDC(hdcMem);
}

void Gdi::DrawBitmap(Win::DIBitmap& dibitmap, int x, int y)
{
	if (dibitmap.pBmFH)
	{
		::SetDIBitsToDevice (m_hdc, x, y, dibitmap.nWidth, dibitmap.nHeight, 
			0, 0, 0, dibitmap.nHeight, 
			dibitmap.pBits, dibitmap.pBmInfo, DIB_RGB_COLORS);
	}
}

void Gdi::DrawBitmap(Win::DIBitmap& dibitmap, int x, int y, int width, int height, bool isColor)
{
	if (isColor) 
	{
		::SetStretchBltMode(m_hdc, COLORONCOLOR);
	}
	else 
	{
		::SetStretchBltMode(m_hdc, WHITEONBLACK);
	}
	if (dibitmap.pBmFH)
	{
		::StretchDIBits(m_hdc, x, y, width, height, 
											0, 0, dibitmap.nWidth, dibitmap.nHeight, 
											dibitmap.pBits, dibitmap.pBmInfo, DIB_RGB_COLORS, SRCCOPY);
	}
}

void Gdi::DrawBitmap(Win::DIBitmapP& dibitmap, int x, int y)
{
	if (dibitmap.m_bIsValid == false) return;

	if (dibitmap.m_hDDB == NULL)
	{
		PBYTE pBmInfo = dibitmap.CreateBitmapInfo();
		const BITMAPINFOHEADER* p = dibitmap.GetInfoHeader();
		dibitmap.m_hDDB = CreateDIBitmap
		(
			m_hdc, 
			p, 
			CBM_INIT, 
			dibitmap.m_pBits,
			(BITMAPINFO*)pBmInfo, 
			DIB_RGB_COLORS
		);
		if (pBmInfo) delete [] pBmInfo;
	}

	if (dibitmap.m_hDDB)
	{
		BITMAP bitmap;
		HDC hdcMem = ::CreateCompatibleDC(m_hdc);
		::SelectObject(hdcMem, dibitmap.m_hDDB);
		::GetObject(dibitmap.m_hDDB, sizeof(BITMAP), &bitmap);
		::BitBlt(m_hdc, x, y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
		::DeleteDC(hdcMem);
	}
}

BOOL Gdi::DrawIcon(int x, int y, Sys::Icon& icon)
{
	return ::DrawIconEx(m_hdc, x, y, icon.GetHIcon(), 0, 0, 0, NULL, DI_NORMAL);  
}

BOOL Gdi::DrawIcon(int x, int y, Sys::Icon& icon, Win::Gdi::Brush& brushBackground)
{
	return ::DrawIconEx(m_hdc, x, y, icon.GetHIcon(), 0, 0, 0, brushBackground.GetHBRUSH(), DI_NORMAL); 
}

// returns the height of the painted area
int Gdi::DrawGraphScaleX(int posX, int posY, int width, double minX, double maxX, int numTicks, int tickSize, const wchar_t* caption)
{
	width--;
	const double deltaX = (maxX - minX)/(numTicks-1.0);
	const double delta = width/(numTicks-1.0);

	double value;
	int pos;
	SIZE size;
	int textAlign = ::SetTextAlign(m_hdc, TA_LEFT | TA_TOP);
	wchar_t text[32];
	//_____________________________________ Draw Ticks and values
	int paintedAreaHeight = tickSize;
	for(int i = 0; i < numTicks; i++)
	{
		pos = (int)(posX + i*delta);
		::MoveToEx(this->m_hdc, pos, posY, NULL);
		::LineTo(this->m_hdc, pos, posY+tickSize);
		//
		value = minX + i*deltaX;
		Sys::Convert::ToString(value, text, 32, true);
		::GetTextExtentPoint32(m_hdc, text, wcslen(text), &size);
		::TextOut(m_hdc, pos-size.cx/2, posY+paintedAreaHeight, text, wcslen(text));
	}
	paintedAreaHeight += size.cy;
	//____________________________________ Draw Caption
	if (caption != NULL)
	{
		const int y = posY + tickSize+ size.cy;
		::GetTextExtentPoint32(m_hdc, caption, wcslen(caption), &size);
		const int x = posX + width/2 - size.cx/2;
		::TextOut(m_hdc, x, y, caption, wcslen(caption));
		paintedAreaHeight += size.cy;
	}
	::SetTextAlign(m_hdc, textAlign);
	return paintedAreaHeight;
}

// returns the width of the painted area
int Gdi::DrawGraphScaleY(int posX, int posY, int height, double minY, double maxY, int numTicks, int tickSize, const wchar_t* caption)
{
	height--;
	const double deltaY = (maxY - minY)/(numTicks-1.0);
	const double delta = height/(numTicks-1.0);

	double value;
	int pos;
	SIZE size;
	const int textAlign = ::SetTextAlign(m_hdc, TA_LEFT | TA_TOP);
	wchar_t text[32];
	const int offsetX = (int)(1.5*tickSize+0.5);
	int maxWidth = 0;
	//_____________________________________ Draw Ticks and values
	for(int i = 0; i < numTicks; i++)
	{
		pos = (int)(posY+ i*delta);
		::MoveToEx(this->m_hdc, posX, pos, NULL);
		::LineTo(this->m_hdc, posX+tickSize, pos);
		//
		value = maxY - i*deltaY;
		Sys::Convert::ToString(value, text, 32, true);
		::GetTextExtentPoint32(m_hdc, text, wcslen(text), &size);
		::TextOut(m_hdc, posX+offsetX, pos-size.cy/2, text, wcslen(text));
		if (maxWidth < size.cx) maxWidth = size.cx; 
	}
	int paintedAreaWidth = offsetX + maxWidth;
	//____________________________________ Draw Caption
	if (caption != NULL)
	{
		const int x = posX + maxWidth+tickSize;
		::GetTextExtentPoint32(m_hdc, caption, wcslen(caption), &size);
		const int y = posY + height/2 - size.cy/2;
		::TextOut(m_hdc, x, y, caption, wcslen(caption));
		paintedAreaWidth += size.cx;
	}
	::SetTextAlign(m_hdc, textAlign);
	return paintedAreaWidth;
}

// returns the width of the painted area
int Gdi::DrawGraphScaleYLeft(int posX, int posY, int height, double minY, double maxY, int numTicks, int tickSize, const wchar_t* caption)
{
	height--;
	const double deltaY = (maxY - minY)/(numTicks-1.0);
	const double delta = height/(numTicks-1.0);

	double value;
	int pos;
	SIZE size;
	const int textAlign = ::SetTextAlign(m_hdc, TA_RIGHT | TA_TOP);
	wchar_t text[32];
	const int offsetX = (int)(1.5*tickSize+0.5);
	int maxWidth = 0;
	//_____________________________________ Draw Ticks and values
	for(int i = 0; i < numTicks; i++)
	{
		pos = (int)(posY+ i*delta);
		::MoveToEx(this->m_hdc, posX, pos, NULL);
		::LineTo(this->m_hdc, posX-tickSize, pos);
		//
		value = maxY - i*deltaY;
		Sys::Convert::ToString(value, text, 32, true);
		::GetTextExtentPoint32(m_hdc, text, wcslen(text), &size);
		::TextOut(m_hdc, posX-offsetX, pos-size.cy/2, text, wcslen(text));
		if (maxWidth < size.cx) maxWidth = size.cx; 
	}
	int paintedAreaWidth = offsetX + maxWidth;
	//____________________________________ Draw Caption
	if (caption != NULL)
	{
		const int x = (int)(posX - maxWidth - 3.0*tickSize+0.5);
		::GetTextExtentPoint32(m_hdc, caption, wcslen(caption), &size);
		const int y = posY + height/2 - size.cy/2;
		::TextOut(m_hdc, x, y, caption, wcslen(caption));
		paintedAreaWidth += size.cx;
	}
	::SetTextAlign(m_hdc, textAlign);
	return paintedAreaWidth;
}

// numColors = 0 for Black and White a maximum of six colors can be used
int Gdi::DrawGraphGradientScale(int posX, int posY, int height, double minimum, double maximum, int numTicks, int tickSize, int numColors, bool invertColors)
{
	height--;
	const bool isColor = (numColors != 0);
	//__________________________________________ Compute the caption column width
	SIZE size;
	::GetTextExtentPoint32(m_hdc, L"99.99", 5, &size);
	int i;

	//____________________________________________________ Color Scale Line
	const int pixelHeight = height-size.cy/2;
	double amplitude;
	int iamplitude;
	int value;
	COLORREF color;

	for(i = size.cy/2, value = pixelHeight; i < pixelHeight; i++, value--)
	{	
		if (invertColors == true)
		{
			amplitude = 1.0-(value/(double)pixelHeight);
		}
		else
		{
			amplitude = value/(double)pixelHeight;
		}
		if (isColor == true)
		{
			color = Sys::Convert::DoubleToColorRef(amplitude, true, numColors); // for a bitmap you should use false for the standard format
		}
		else
		{
			iamplitude = (int)(255.0*amplitude);
			color = RGB(iamplitude, iamplitude, iamplitude);
		}
		::SetPixel(m_hdc, posX, posY+i, color);
	}
	::BitBlt(m_hdc, posX+1, posY+size.cy/2, 1, pixelHeight, m_hdc, posX, posY+size.cy/2, SRCCOPY); // resulting width = 2
	::BitBlt(m_hdc, posX+2, posY+size.cy/2, 2, pixelHeight, m_hdc, posX, posY+size.cy/2, SRCCOPY); // resulting width = 4
	::BitBlt(m_hdc, posX+4, posY+size.cy/2, 4, pixelHeight, m_hdc, posX, posY+size.cy/2, SRCCOPY);// resulting width = 8
	::BitBlt(m_hdc, posX+8, posY+size.cy/2, 8, pixelHeight, m_hdc, posX, posY+size.cy/2, SRCCOPY);// resulting width = 16

	//____________________________________________________ Caption
	const double deltaY = (height-size.cy+1)/(double)(numTicks);
	const double delta =(maximum - minimum)/(double)(numTicks);
	wchar_t text[32];
	int iy;
	int len = 0;
	double y;
	const int colorBandWidth = 16;
	int maxWidth = 0;
	const int sigma = (int)(2.0*tickSize+0.5);
	for(i = 0; i <= numTicks; i++)
	{
		iy = (int)(i *deltaY-0.5);// + size.cy/2;
		y = maximum - i * delta;
		len = Sys::Convert::ToString(y, text, 32, true);
		//____________________________________________ Compute max width
		::GetTextExtentPoint32(m_hdc, text, len, &size);
		if (maxWidth < size.cx) maxWidth = size.cx;
		//____________________________________________  Numbers
		::TextOut(m_hdc, posX+sigma+colorBandWidth, posY+iy, text, len);
		//____________________________________________ Tics
		::MoveToEx(m_hdc, posX, posY+iy +size.cy/2, NULL);
		::LineTo(m_hdc, posX+tickSize+colorBandWidth, posY+iy +size.cy/2);
	}

	return sigma + maxWidth;
}

void Gdi::DrawArrow(RECT& rect, Win::Gdi::Brush& brush, int direction) // WIN_DRAWARROW_NORTH, ...
{
	POINT point[8];
	const int width = rect.right - rect.left;
	const int height = rect.bottom - rect.top;
	const int minimum = (width < height ) ? width : height;
	const int a = (int)(0.25*minimum+0.5);
	const int b = (int)(0.125*minimum+0.5);
	const int med_width = (int)((rect.right + rect.left)/2.0+0.5);
	const int med_height = (int)((rect.bottom + rect.top)/2.0+0.5);
	bool ok = false;

	if (direction == WIN_DRAWARROW_NORTH)
	{
		point[0].x = med_width;
		point[0].y = rect.top;
		//
		point[1].x = med_width + a;
		point[1].y = rect.top + a;
		//
		point[2].x = med_width + b;
		point[2].y = rect.top + a;
		//
		point[3].x = med_width + b;
		point[3].y = rect.bottom-1;
		//
		point[4].x = med_width - b;
		point[4].y = rect.bottom-1;
		//
		point[5].x = med_width - b;
		point[5].y = rect.top + a;
		//
		point[6].x = med_width - a;
		point[6].y = rect.top + a;
		//
		point[7] = point[0];
		ok = true;
	}
	else if (direction == WIN_DRAWARROW_EAST)
	{
		point[0].y = med_height;
		point[0].x = rect.left;
		//
		point[1].y = med_height + a;
		point[1].x = rect.left + a;
		//
		point[2].y = med_height + b;
		point[2].x = rect.left + a; 
		//
		point[3].y = med_height + b;
		point[3].x = rect.right - 1;
		//
		point[4].y = med_height - b;
		point[4].x = rect.right -1;
		//
		point[5].y = med_height - b;
		point[5].x = rect.left + a;
		//
		point[6].y = med_height - a;
		point[6].x = rect.left + a;
		//
		point[7] = point[0];
		ok = true;
	}
	else if (direction == WIN_DRAWARROW_SOUTH)
	{
		point[0].x = med_width;
		point[0].y = rect.bottom-1;
		//
		point[1].x = med_width + a;
		point[1].y = rect.bottom - a - 1;
		//
		point[2].x = med_width + b;
		point[2].y = rect.bottom - a - 1;
		//
		point[3].x = med_width + b;
		point[3].y = rect.top;
		//
		point[4].x = med_width - b;
		point[4].y = rect.top;
		//
		point[5].x = med_width - b;
		point[5].y = rect.bottom - a - 1;
		//
		point[6].x = med_width - a;
		point[6].y = rect.bottom - a - 1;
		//
		point[7] = point[0];
		ok = true;
	}
	else if (direction == WIN_DRAWARROW_WEST)
	{
		point[0].y = med_height;
		point[0].x = rect.right - 1;
		//
		point[1].y = med_height + a;
		point[1].x = rect.right - a -1;
		//
		point[2].y = med_height + b;
		point[2].x = rect.right - a -1;
		//
		point[3].y = med_height + b;
		point[3].x = rect.left;
		//
		point[4].y = med_height - b;
		point[4].x = rect.left;
		//
		point[5].y = med_height - b;
		point[5].x = rect.right - a - 1;
		//
		point[6].y = med_height - a;
		point[6].x = rect.right - a - 1;
		//
		point[7] = point[0];
		ok = true;
	}
	if (ok == false) return;
	//______________________________________________ Border
	::MoveToEx(m_hdc, point[0].x, point[0].y, NULL);
	::PolylineTo(m_hdc, point, 8);
	//______________________________________________ Filling
	HRGN region = ::CreatePolygonRgn(point, 8, WINDING);
	if (region == NULL) return;
	::FillRgn(m_hdc, region, brush.GetHBRUSH());

	::DeleteObject(region);
}

void Gdi::FillPolyBezier(const POINT* arrayPoints, DWORD count, Win::Gdi::Brush& brush)
{
	::BeginPath(m_hdc);
	::PolyBezier(m_hdc, arrayPoints, count);
	::EndPath(m_hdc);
	::SelectObject(m_hdc, (HGDIOBJ)brush.GetHBRUSH());
	::FillPath(m_hdc);
}

//alignment: WIN_ALIGNMENT_LEFT, WIN_ALIGNMENT_RIGHT, WIN_ALIGNMENT_CENTER, WIN_ALIGNMENT_JUSTIFIED
// returns the number of lines requiered to display the text in the specified width
// To print all the rows set rowIndex to -1
// To compute the number of rows without printing set rowIndex to -2
int Gdi::DrawParagraph(const wchar_t* text, int text_width, int x, int y, int alignment, int rowIndex) 
{
	int line_count = 0;
	wchar_t* pText = (wchar_t*)text;
	double width;
	int spaceChars = 0;
	int pos_x;
	wchar_t*  begin;
	wchar_t* end;
	SIZE   size;
	TextExtent txEx(m_hdc);

	int pos_y = y;
	do
	{
		spaceChars = 0;
		while (*pText == ' ') pText++;    // skip spaces
		begin = pText;
		do
		{
			end = pText;
			while (*pText != '\0' && *pText++ != ' ');	// skip to next space 
			if (*pText == '\0')	break;

			spaceChars++;
			width = txEx.GetWidth(begin, (int)(pText - begin - 1));
		}
		//while (width < (double) (rect.right - rect.left));
		while (width < (double)text_width);

		spaceChars--;               // discount last space at end of line
		while (*(end - 1) == ' ')    // eliminate trailing spaces
		{
			end--;
			spaceChars--;
		}

		if (*pText == '\0' || spaceChars <= 0) end = pText;
		::GetTextExtentPoint32(m_hdc, begin, (int)(end - begin), &size);

		switch (alignment)
		{
		case WIN_ALIGNMENT_LEFT:
			//x = rect.left;
			pos_x = x;
			break;
		case WIN_ALIGNMENT_RIGHT:
			//x = rect.right - size.cx;
			pos_x = x + text_width - size.cx;
			break;
		case WIN_ALIGNMENT_CENTER:
			//x = (rect.right + rect.left - size.cx) / 2;
			pos_x = (x+ text_width + x - size.cx) / 2;
			break;
		case WIN_ALIGNMENT_JUSTIFIED:
			if (*pText != '\0' && spaceChars > 0)
			{
				//SetTextJustification (m_hdc,rect.right - rect.left - size.cx, spaceChars);
				SetTextJustification (m_hdc, text_width - size.cx, spaceChars);
			}
			//x = rect.left;
			pos_x = x;
			break;
		}
		if (rowIndex == -1)
		{
			if (rowIndex != -2)
			{
				::TextOut (m_hdc, pos_x, (int)(pos_y+0.5), begin, (int)(end - begin));
			}
		}
		else
		{
			if (rowIndex == line_count)
			{
				if (rowIndex != -2)
				{
					::TextOut (m_hdc, pos_x, y, begin, (int)(end - begin));
				}
			}
		}
	//	// prepare for next line
		::SetTextJustification (m_hdc, 0, 0);
		pos_y += size.cy;
		line_count++;
		pText = end;
	}
	while (*pText);

	return line_count;
}

void Gdi::DrawMetafile(Win::Metafile& metafile, const RECT& rect)
{
	PlayEnhMetaFile(m_hdc, metafile.GetHandle(), &rect);
}

void Gdi::DrawMetafile(Win::Metafile& metafile, int x, int y, int width, int height, bool center)
{
	HENHMETAFILE hEMF = metafile.GetHandle();
	if (hEMF == NULL) return;

	RECT rect;
	int cx, cy, cxMms, cyMms, cxPix, cyPix;
	ENHMETAHEADER emh;
	float fScaleX, fScaleY, fScale;

	cxMms = GetDeviceCaps(m_hdc, HORZSIZE);
	cyMms = GetDeviceCaps(m_hdc, VERTSIZE);
	cxPix = GetDeviceCaps(m_hdc, HORZRES);
	cyPix = GetDeviceCaps(m_hdc, VERTRES);

	GetEnhMetaFileHeader(hEMF, sizeof(ENHMETAHEADER), &emh);
	cx = (emh.rclFrame.right - emh.rclFrame.left)*cxPix/cxMms/100;
	cy = (emh.rclFrame.bottom - emh.rclFrame.top)*cyPix/cyMms/100;

	//****************************** Scale metafile
	fScaleX = (float)width/cx;
	fScaleY = (float)height/cy;
	 
	if (center)
	{
		if (fScaleX<fScaleY) 
		{
			cx = (int) (fScaleX*cx);
			cy = (int) (fScaleX*cy);

			rect.left = x;
			rect.top = y +((height-cy)/2);
			rect.right = x + cx;
			rect.bottom = rect.top + cy;
		}
		else
		{	
			cx = (int) (fScaleY*cx);
			cy = (int) (fScaleY*cy);

			rect.left = x + ((width-cx)/2);
			rect.top = y;
			rect.right = rect.left + cx;
			rect.bottom = y + cy;
		}
	}
	else
	{
		fScale = MINIMUM(fScaleX, fScaleY);
		cx = (int) (fScale*cx);
		cy = (int) (fScale*cy);

		rect.left = x;
		rect.top = y;
		rect.right = x + cx;
		rect.bottom = y + cy;
	}
	PlayEnhMetaFile(m_hdc, hEMF, &rect);
}

void Gdi::DrawMetafile(Win::Metafile& metafile, int x, int y)
{
	HENHMETAFILE hEMF = metafile.GetHandle();
	if (hEMF == NULL) return;
	RECT rect;
	int cx, cy, cxMms, cyMms, cxPix, cyPix;
	ENHMETAHEADER emh;

	cxMms = GetDeviceCaps(m_hdc, HORZSIZE);
	cyMms = GetDeviceCaps(m_hdc, VERTSIZE);
	cxPix = GetDeviceCaps(m_hdc, HORZRES);
	cyPix = GetDeviceCaps(m_hdc, VERTRES);

	GetEnhMetaFileHeader(hEMF, sizeof(ENHMETAHEADER), &emh);
	cx = (emh.rclFrame.right - emh.rclFrame.left)*cxPix/cxMms/100;
	cy = (emh.rclFrame.bottom - emh.rclFrame.top)*cyPix/cyMms/100;
	rect.left = x;
	rect.top = y;
	rect.right = x + cx;
	rect.bottom = y + cy;
	PlayEnhMetaFile(m_hdc, hEMF, &rect);
}

//SIZE DIBitmap::GetSize()
//{
//	SIZE sz;
//	sz.cx = this->nWidth;
//	sz.cy = this->nHeight;
//	return sz;
//}

void Gdi::TextOutCenter(RECT& rect, const wchar_t * text, bool bCenterX, bool bCenterY)
{
	if (text==NULL) return;
	const int n= lstrlen(text);
	SIZE size;
	::GetTextExtentPoint32(this->m_hdc, text, n, &size);
	int positionX = rect.left;
	int positionY = rect.top;
	if (bCenterX) positionX = (int)(rect.left+(rect.right-rect.left-size.cx)/2.0+0.5);
	if (bCenterY) positionY = (int)(rect.top+(rect.bottom-rect.top-size.cy)/2.0+0.5);
	this->SetTextAlign(TA_LEFT | TA_TOP);
	::TextOut(this->m_hdc, positionX, positionY, text, n);
}

BOOL Gdi::TextOutVCenterRight(RECT& rect, const wchar_t * text)
{
	if (text==NULL) return FALSE;
	const int n= lstrlen(text);
	SIZE size;
	::GetTextExtentPoint32(this->m_hdc, text, n, &size);
	const int positionX = (int)(rect.right-size.cx+0.5);
	const int positionY = (int)(rect.top+(rect.bottom-rect.top-size.cy)/2.0+0.5);
	this->SetTextAlign(TA_LEFT | TA_TOP);
	return ::TextOut(this->m_hdc, positionX, positionY, text, n);
}

BOOL Gdi::TextOutVCenterLeft(RECT& rect, const wchar_t * text)
{
	if (text==NULL) return FALSE;
	const int n= lstrlen(text);
	SIZE size;
	::GetTextExtentPoint32(this->m_hdc, text, n, &size);
	const int positionY = (int)(rect.top + (rect.bottom - rect.top - size.cy)/2.0+0.5);
	this->SetTextAlign(TA_LEFT | TA_TOP);
	return ::TextOut(this->m_hdc, rect.left, positionY, text, n);
}

BOOL Gdi::TextOutCenter(int x, int y, const wchar_t * text, bool bCenterX, bool bCenterY)
{
	if (text==NULL) return FALSE;
	const int n= lstrlen(text);
	SIZE size;
	int positionX = x;
	int positionY = y;
	::GetTextExtentPoint32(this->m_hdc, text, n, &size);
	if (bCenterX) positionX = (int)(x-size.cx/2.0+0.5);
	if (bCenterY) positionY = (int)(y-size.cy/2.0+0.5);
	this->SetTextAlign(TA_LEFT | TA_TOP);
	return ::TextOut(this->m_hdc, positionX, positionY, text, n);
}

void Gdi::TextOutCenter(RECT& rect, const wstring& text, bool centerX, bool centerY)
{
	TextOutCenter(rect, text.c_str(), centerX, centerY);
}

BOOL Gdi::TextOutVCenterRight(RECT& rect, const wstring& text)
{
	return TextOutVCenterRight(rect, text.c_str());
}

BOOL Gdi::TextOutVCenterLeft(RECT& rect, const wstring& text)
{
	return TextOutVCenterLeft(rect, text.c_str());
}

BOOL Gdi::TextOutCenter(int x, int y, const wstring& text, bool centerX, bool centerY)
{
	return TextOutCenter(x, y, text.c_str(), centerX, centerY);
}

BOOL Gdi::TextOutTruncate(int x, int y, const wstring& text, int width, bool ellipses, bool centerX)
{
	return TextOutTruncate(x, y, text.c_str(), width, ellipses, centerX);
}

BOOL Gdi::PieCircle(int xCenter, int yCenter, int nRadius, double angleStart, double angleDelta)
{
	const double pi = 3.14159265359;
	double angleStartDegree = angleStart*pi/180;
	double angleEndDegree = (angleStart + angleDelta)*pi/180;
	return ::Pie
		(
			m_hdc, xCenter-nRadius, 
			yCenter-nRadius, 
			xCenter+nRadius, 
			yCenter+nRadius,
			(int)(xCenter+nRadius*cos(angleStartDegree)+0.5), 
			(int)(yCenter-nRadius*sin(angleStartDegree)+0.5), 
			(int)(xCenter+nRadius*cos(angleEndDegree)+0.5), 
			(int)(yCenter-nRadius*sin(angleEndDegree)+0.5)
		);
}

bool Gdi::TextOutTruncate(int x, int y, const wchar_t* pszText, int width, bool bEllipses, bool centerX)
{
	if (pszText == NULL) return true; // Nothing to do
	const int textLen = wcslen(pszText);
	if (textLen <= 0) return true; // Nothing to do
	//
	static SIZE size;
	static TEXTMETRIC tm;
	const int len = textLen+6;//Null terminator plus ellipses
	wchar_t* sz = new wchar_t[len]; 
	if (sz == NULL) return false;

	_snwprintf_s(sz, len, _TRUNCATE, L"%s", pszText);
	//wcscpy_s(sz, len, pszText);

	::GetTextMetrics(m_hdc, &tm);
	if (width < tm.tmAveCharWidth*2) width = tm.tmAveCharWidth*2;
	::GetTextExtentPoint32(m_hdc, sz, wcslen(sz), &size);

	const int i =width/tm.tmAveCharWidth;
	int k = MINIMUM(width/tm.tmAveCharWidth - 2, textLen);
	const int minWidth = width - tm.tmAveCharWidth - tm.tmAveCharWidth/2;

	while(minWidth < size.cx && 0 < k)
	{
		if (bEllipses == true)
		{
			sz[k] = '.';
			sz[k+1] = '.';
			sz[k+2] = '.';
			sz[k+3] = '\0';
			//lstrcpy(&sz[i-j], L"...");
		}
		else
		{
			sz[k] = '\0';
			//lstrcpy(&sz[i-j], L"");
		}
		::GetTextExtentPoint32(m_hdc, sz, wcslen(sz), &size);
		k--;
	}

	if (centerX == true)
	{
		::TextOut(m_hdc, x+(width-size.cx)/2, y, sz, wcslen(sz));
	}
	else
	{	
		::TextOut(m_hdc, x, y, sz, wcslen(sz));
	}
	if (sz != NULL) delete [] sz;
	return true;
}

// 1 milimeter containts 100 logical units
void Gdi::SetMili100Mode()
{
	::SetMapMode(m_hdc, MM_ANISOTROPIC);
	::SetWindowExtEx(m_hdc, 100, 100, NULL);
	::SetViewportExtEx
		(
			m_hdc, 
			(int)(this->GetPixelsPerMilimeterX()+0.5),
			(int)(this->GetPixelsPerMilimeterY()+0.5),
			NULL
		);
}

// For cartesian mode:  SetScaleMode(1000, 1000, width/2, height/2, true);
void Gdi::SetScaleMode(int logUnitsWidth, int logUnitsHeight, int pxWidth, int pxHeight, bool bCartesian)
{
	::SetMapMode(m_hdc, MM_ISOTROPIC);
	::SetWindowExtEx(m_hdc, logUnitsWidth, logUnitsHeight, NULL);
	::SetViewportExtEx(m_hdc, pxWidth, bCartesian ? -pxHeight : pxHeight, NULL);
	if (bCartesian) ::SetViewportOrgEx(m_hdc, pxWidth, pxHeight, NULL);
}


HFONT Gdi::UpdateFont(Font* pFont, HFONT hFont)
{
	HFONT hf = NULL;

	if (m_pFont) m_pFont ->Update(NULL);
	this->m_pFont = pFont;
	if (pFont) m_pFont ->Update(this);
	hf = (HFONT)::SelectObject(m_hdc, hFont);
	if (m_hFontOriginal == NULL) m_hFontOriginal = hf;
	::GetTextMetrics(m_hdc, &tm);
	return hf;
}

HPEN Gdi::UpdatePen(Pen* pPen, HPEN hPen)
{
	HPEN hp = NULL;

	if (m_pPen) m_pPen ->Update(NULL);
	this->m_pPen = pPen;
	if (pPen) m_pPen ->Update(this);
	hp = (HPEN)::SelectObject(m_hdc, hPen);
	if (m_hPenOriginal == NULL) m_hPenOriginal = hp;
	return hp;
}

HBRUSH Gdi::UpdateBrush(Brush* pBrush, HBRUSH hBrush)
{
	HBRUSH hb = NULL;

	if (m_pBrush) m_pBrush ->Update(NULL);
	this->m_pBrush = pBrush;
	if (pBrush) m_pBrush ->Update(this);
	hb = (HBRUSH) ::SelectObject(m_hdc, hBrush);
	if (m_hBrushOriginal == NULL) m_hBrushOriginal = hb;
	return hb;
}

void Gdi::UpdateFontExt(Font* pFont)
{
	if (pFont)
	{
		this->UpdateFont(pFont, pFont->GetHFONT());
	}
	else
	{
		::SelectObject(m_hdc, m_hFontOriginal);
		m_hFontOriginal = NULL;
	}
	m_pFont = pFont;
}

void Gdi::UpdatePenExt(Pen* pPen)
{
	if (pPen)
	{
		this->UpdatePen(pPen, pPen->GetHPEN());
	}
	else
	{
		::SelectObject(m_hdc, m_hPenOriginal);
		m_hPenOriginal = NULL;
	}
	m_pPen = pPen;
}

void Gdi::UpdateBrushExt(Brush* pBrush)
{
	if (pBrush)
	{
		this->UpdateBrush(pBrush, pBrush->GetHBRUSH());
	}
	else
	{
		::SelectObject(m_hdc, m_hBrushOriginal);
		m_hBrushOriginal = NULL;
	}
	m_pBrush = pBrush;
}

// You can select any brush or pen before calling 
void Gdi::Cilinder(int x, int y, double radius, double height, bool topEllipse, bool bottomEllipse)
{
	int right = (int)(x + 2*radius+0.5);
	int bottom = (int)(y+height+0.5);
	const double perspective = 0.2*radius;
	this->MoveToEx(x, y); //**** Left line
	this->LineTo(x, bottom);
	this->MoveToEx(right-1, y); //**** Right line
	this->LineTo(right-1, bottom);
	//
	if (topEllipse) this->Ellipse(x, (int)(y-perspective+0.5), right, (int)(y+perspective+0.5));// top ellipse
	if (bottomEllipse)this->Ellipse(x, (int)(bottom-perspective + 0.5), right, (int)(bottom+perspective+0.5));//bottom ellipse
}

// You may want to select the NULL pen before calling SolidCilinder
void Gdi::SolidCilinder(int x, int y, double radius, double height, COLORREF color)
{
	Win::Gdi::Brush brushDark(Win::Gdi::Color3D::GetShadowColor(color));
	Win::Gdi::Brush brushHighLight(Win::Gdi::Color3D::GetHighLightColor(color));
	Win::Gdi::Pen penLight(PS_SOLID, 1, Win::Gdi::Color3D::GetLightColor(color));
	Win::Gdi::Pen penShadow(PS_SOLID, 1, Win::Gdi::Color3D::GetShadowColor(color));
	Win::Gdi::Brush brushNormal(color);
	int right = (int)(x + 2*radius+0.5);
	int bottom = (int)(y+height+0.5);
	const double perspective = 0.2*radius;

	this->SelectBrush_(brushNormal);
	this->Rectangle(x, y, right, bottom);
	//
	this->SelectPen_(penShadow);
	this->SelectBrush_(brushDark);
	this->Ellipse(x, (int)(bottom-perspective - 0.5), right-1, (int)(bottom+perspective+0.5));//**** top ellipse
	//
	this->SelectPen_(penLight);
	this->SelectBrush_(brushHighLight);
	this->Ellipse(x, (int)(y-perspective+0.5), right-1, (int)(y+perspective-0.5));//**** top ellipse
}

// Returns the maximum scale so that the rectangle described by sizeInterior fits inside sizeExterior
double Gdi::GetMaxScale(const Win::Gdi::PointF* pfInterior, const Win::Gdi::PointF* pfExterior)
{
	double scale = 0;

	scale = pfExterior->x / pfInterior->x;
	if (scale*pfInterior->y < pfExterior->y) return scale;
	return pfExterior->y / pfInterior->y;
}

//This is useful for a painting loop that goes from left to right drawing lines
// the Data::Array contains the coordinates of the lines, you should fill this array during OnSize
bool Gdi::OnPaintLoopX_(RECT& rcTotalLoopArea, int* array, int arrayLength, 
		int& index1, int& index2, int& nTop, int& nBottom)
{
	bool bOverlapped = false;
	RECT rect;
	int i, value;

	index1=0;
	index2=0;
	nTop = 0;
	nBottom = 0;

	::IntersectRect(&rect, &this->m_ps.rcPaint, &rcTotalLoopArea);
	bOverlapped =(::IsRectEmpty(&rect)==FALSE);

	if (bOverlapped)
	{
		nTop = rect.top;
		nBottom = rect.bottom;
		//******************** index1;
		for(i=0; i<arrayLength; i++)
		{
			value = array[i];
			if (rect.left<= value && value<rect.right)
			{
				index1 = i;
				break;
			}
		}
		//******************** index2;
		for(i=arrayLength-1; i>=index1; i--)
		{
			value = array[i];
			if (rect.left<= value && value<rect.right)
			{
				index2 = i;
				break;
			}
		}
	}
	return bOverlapped;
}

//This is useful for a painting loop that goes from left to right drawing lines
// the Data::Array contains the coordinates of the lines, you should fill this array during OnSize
bool Gdi::OnPaintLoopY_(RECT& rcTotalLoopArea, int* array, int arrayLength,  
		int& index1, int& index2, int& nLeft, int& nRight)
{
	bool bOverlapped = false;
	RECT rect;
	int i, value;

	index1=0;
	index2=0;
	nLeft = 0;
	nRight = 0;

	::IntersectRect(&rect, &this->m_ps.rcPaint, &rcTotalLoopArea);
	bOverlapped =(::IsRectEmpty(&rect)==FALSE);

	if (bOverlapped)
	{
		nLeft = rect.left;
		nRight = rect.right;
		//******************** index1;
		for(i=0; i<arrayLength; i++)
		{
			value = array[i];
			if (rect.top<= value && value<rect.bottom)
			{
				index1 = i;
				break;
			}
		}
		//******************** index2;
		for(i=arrayLength-1; i>=index1; i--)
		{
			value = array[i];
			if (rect.top<= value && value<rect.bottom)
			{
				index2 = i;
				break;
			}
		}
	}
	return bOverlapped;
}

// Returns the initial and final values for a loop inside a paint function
// rcTotalLoopArea is the total area draw by the loop
//
// rcRequiredLoopArea.left is the initial value of X in the loop
// rcRequiredLoopArea.right is the final value of X in the loop
// rcRequiredLoopArea.top is the minimum value of Y to paint
// rcRequiredLoopArea.bottom is the maximum value of Y to paint
// This is useful for a painting loop that goes from left to right drawing boxes
bool Gdi::OnPaintLoopX(int deltaX, RECT& rcTotalLoopArea, RECT& rcRequiredLoopArea)
{
	bool bOverlapped = false;
	RECT rect;
	int a = 0;

	ZeroMemory(&rcRequiredLoopArea, sizeof(RECT));
	::IntersectRect(&rect, &this->m_ps.rcPaint, &rcTotalLoopArea);
	bOverlapped =(::IsRectEmpty(&rect)==FALSE);

	if (bOverlapped)
	{
		rcRequiredLoopArea.top = rect.top;
		rcRequiredLoopArea.bottom = rect.bottom;
		//
		a = (rect.left - rcTotalLoopArea.left)/deltaX;
		rcRequiredLoopArea.left = rcTotalLoopArea.left + a * deltaX;
		//
		a = (rect.right- rcTotalLoopArea.left)/deltaX;
		rcRequiredLoopArea.right = 1+ rcTotalLoopArea.left + a * deltaX;
	}

	return bOverlapped;
}

// Returns the initial and final loop indexes for a painting function of area rectBox
// This is useful for a painting loop that goes from left to right drawing boxes
// Check return value of this function before starting the loop
bool Gdi::OnPaintLoopX(double inDeltaX, RECT& inRectBox, 
	int& outTop, int& outBottom, int& outIndex1, int& outIndex2)
{
	bool bOverlapped = false;
	RECT rect;

	//****************************************** Initialize out variables
	outIndex1=0;
	outIndex2=0;
	outTop = inRectBox.top;
	outBottom = inRectBox.bottom;

	::IntersectRect(&rect, &m_ps.rcPaint, &inRectBox);
	bOverlapped =(::IsRectEmpty(&rect)==FALSE);

	if (bOverlapped)
	{
		outTop = rect.top;
		outBottom = rect.bottom;
		//
		outIndex1 = (int)((rect.left - inRectBox.left-1)/inDeltaX);
		outIndex2 = (int)((rect.right- inRectBox.left-1)/inDeltaX);
	}

	return bOverlapped;
}

// Returns the initial and final values for a loop inside a paint function
// rcTotalLoopArea is the total area draw by the loop
//
// rcRequiredLoopArea.left is the minimum value of Y to paint
// rcRequiredLoopArea.right is the maximum value of Y to paint
// rcRequiredLoopArea.top is the initial value of Y in the loop
// rcRequiredLoopArea.bottom is the last value of Y in the loop
//This is useful for a painting loop that goes from top to bottom inside drawing boxes
bool Gdi::OnPaintLoopY(int deltaY, RECT& rcTotalLoopArea, RECT& rcRequiredLoopArea)
{
	bool bOverlapped = false;
	RECT rect;
	int a = 0;

	ZeroMemory(&rcRequiredLoopArea, sizeof(RECT));
	::IntersectRect(&rect, &this->m_ps.rcPaint, &rcTotalLoopArea);
	bOverlapped =(::IsRectEmpty(&rect)==FALSE);

	if (bOverlapped)
	{
		rcRequiredLoopArea.left = rect.left;
		rcRequiredLoopArea.right = rect.right;
		//
		a = (rect.top - rcTotalLoopArea.top)/deltaY;
		rcRequiredLoopArea.top = rcTotalLoopArea.top + a * deltaY;
		//
		a = (rect.bottom- rcTotalLoopArea.top)/deltaY;
		rcRequiredLoopArea.bottom = 1+ rcTotalLoopArea.top + a * deltaY;
	}

	return bOverlapped;
}

// Returns the initial and final loop indexes for a painting function of area rectBox
// This is useful for a painting loop that goes from top to bottom drawing boxes
// Check return value of this function before starting the loop
bool Gdi::OnPaintLoopY(double inDeltaY, RECT& inRectBox, int& outLeft, int& outRight, int& outIndex1, int& outIndex2)
{
	bool bOverlapped = false;
	RECT rect;

	//****************************************** Initialize out variables
	outIndex1=0;
	outIndex2=0;
	outLeft = inRectBox.left;
	outRight = inRectBox.right;

	::IntersectRect(&rect, &m_ps.rcPaint, &inRectBox);
	bOverlapped =(::IsRectEmpty(&rect)==FALSE);

	if (bOverlapped)
	{
		outLeft = rect.left;
		outRight = rect.right;
		//
		outIndex1 = (int)((rect.top - inRectBox.top-1)/inDeltaY);
		outIndex2 = (int)((rect.bottom- inRectBox.top-1)/inDeltaY);
	}

	return bOverlapped;
}

//_____________________________________________________________________ Gdi::Font
Gdi::Font::Font(void)
{
	Constructor();
}

void Gdi::Font::Constructor()
{
	m_pGdi = NULL;
	hFont = NULL;
	//
	logfont.lfHeight = 0;
	logfont.lfWidth = 0;
	logfont.lfEscapement = 0;
	logfont.lfOrientation = 0;
	logfont.lfWeight = FW_NORMAL;
	logfont.lfItalic = FALSE;
	logfont.lfUnderline = FALSE;
	logfont.lfStrikeOut = FALSE;
	logfont.lfCharSet = DEFAULT_CHARSET;
	logfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logfont.lfQuality = DEFAULT_QUALITY;
	logfont.lfPitchAndFamily = VARIABLE_PITCH | FF_DONTCARE;
	logfont.lfFaceName[0] = '\0';
}

HFONT Gdi::Font::GetHFONT()
{
	return hFont;
}

int Gdi::Font::GetSize()
{
	return abs(logfont.lfHeight);
}

wchar_t* Gdi::Font::GetName()
{
	return logfont.lfFaceName;
}

//________________________________________________________
Gdi::Font::Font(const wchar_t* name, int size)
{
	this->Constructor();
	this->Create(name, size, false, false, false, false);
}

Gdi::Font::Font(const wstring& name, int size)
{
	this->Constructor();
	this->Create(name, size, false, false, false, false);
}

//________________________________________________________
Gdi::Font::Font(const wchar_t* name, wchar_t* text, RECT& rect)
{
	this->Constructor();
	this->Create(name, text, rect.right-rect.left, rect.bottom-rect.top);
}

Gdi::Font::Font(const wstring& name, const wstring& text, RECT& rect)
{
	this->Constructor();
	this->Create(name, text, rect.right-rect.left, rect.bottom-rect.top);
}

//________________________________________________________
Gdi::Font::Font(const wchar_t* name, const wchar_t* text, int width, int height)
{
	this->Constructor();
	this->Create(name, text, width, height);
}

// This constructor will create the right font to fit the text inside a box of size width time height
Gdi::Font::Font(const wstring& name, const wstring& text, int width, int height)
{
	this->Constructor();
	this->Create(name, text, width, height);
}

//________________________________________________________
HFONT Gdi::Font::Create(const wchar_t* name, int size, bool bold, bool italic, bool underline, bool strikeout)
{
	Delete();
	logfont.lfStrikeOut = strikeout ? 1 : 0;
	logfont.lfUnderline = underline ? 1 : 0;
	logfont.lfHeight = - size;
	logfont.lfWeight = bold ? 700 : 0;
	logfont.lfItalic = italic ? 1 : 0;
	lstrcpy (logfont.lfFaceName, name);
	return this->Create();
}

HFONT Gdi::Font::Create(const wstring& name, int size, bool bold, bool italic, bool underline, bool strikeout)
{	
	return Create(name.c_str(), size, bold, italic, underline, strikeout);
}

//________________________________________________________
HFONT Gdi::Font::Create(int charCount, const wchar_t* name, int width, int height)
{
	Delete();
	int nSize = (int)(0.9*MINIMUM(2*width/charCount, height)+0.5);
	logfont.lfHeight = -nSize;
	lstrcpy (logfont.lfFaceName, name);
	return this->Create();
}

HFONT Gdi::Font::Create( int charCount, const wstring& name, int width, int height)
{
	return Create(charCount, name.c_str(), width, height);
}

//________________________________________________________
// Creates a font to fit the text in a box of size width x height
HFONT Gdi::Font::Create(const wchar_t* name, const wchar_t* text, int width, int height)
{
	Delete();
	int nSize = Win::Gdi::Font::GetIdealFontSize(text, width, height);
	logfont.lfHeight = -nSize;
	lstrcpy (logfont.lfFaceName, name);
	return this->Create();
}

HFONT Gdi::Font::Create(const wstring& name, const wstring& text, int width, int height)
{	
	return Create(name.c_str(), text.c_str(), width, height);
}

//________________________________________________________
HFONT Gdi::Font::Create(const wchar_t* name, int size, bool bold, bool italic, int angle)
{
	Delete();
	logfont.lfHeight = - size;
	logfont.lfEscapement = angle;
	logfont.lfOrientation = angle;
	logfont.lfWeight = bold ? 700 : 0;
	logfont.lfItalic = italic ? 1 : 0;
	lstrcpy (logfont.lfFaceName, name);
	return this->Create();
}

//45 degrees -> angle = 450
HFONT Gdi::Font::Create(const wstring& name, int size, bool bold, bool italic, int angle)
{	
	return Create(name.c_str(), size, bold, italic, angle);
}

//________________________________________________________
HFONT Gdi::Font::Create(HDC hdc, const wchar_t* name, double heightPoints, bool bold, bool italic, bool deviceIndependent)
{
	const int decipointHeight = (int)(10.0*heightPoints+0.5);
	::SaveDC(hdc);
	::SetGraphicsMode(hdc, GM_ADVANCED);
	::ModifyWorldTransform(hdc, NULL, MWT_IDENTITY);
	::SetViewportOrgEx(hdc, 0, 0, NULL);
	::SetWindowOrgEx(hdc, 0, 0, NULL);
	double cxDpi, cyDpi;

	if (deviceIndependent)
	{
		cxDpi = 25.4 * (double)::GetDeviceCaps (hdc, HORZRES) / (double)::GetDeviceCaps (hdc, HORZSIZE);
		cyDpi = 25.4 * (double)::GetDeviceCaps (hdc, VERTRES) / (double)::GetDeviceCaps (hdc, VERTSIZE);
	}
	else
	{
		cxDpi = (double)::GetDeviceCaps(hdc, LOGPIXELSX);
		cyDpi = (double)::GetDeviceCaps(hdc, LOGPIXELSY);
	}
	
	const int decipointWidth = 100; // it does not matter
	POINT pt;
	pt.x = (int) (decipointWidth  * cxDpi / 72.0 + 0.5) ;
	pt.y = (int) (decipointHeight * cyDpi / 72.0 + 0.5);

	::DPtoLP (hdc, &pt, 1);
	Delete();
	logfont.lfHeight = - (int) (fabs ((double)pt.y) / 10.0 + 0.5);
	logfont.lfWeight = bold ? 700 : 0;
	logfont.lfItalic = italic ? 1 : 0;
	lstrcpy (logfont.lfFaceName, name);
	::RestoreDC (hdc, -1) ;
	return this->Create();
}

// Height is in points,  There are 72 points in a inch.  There are 2.8346 points in a milimeter
// if isDeviceIndependent is true, the font will the same size no matter the type of device
HFONT Gdi::Font::Create(HDC hdc, const wstring& name, double heightPoints, bool bold, bool italic, bool deviceIndependent)
{
	return Create(hdc, name.c_str(), heightPoints, bold, italic, deviceIndependent);
}

//________________________________________________________
HFONT Gdi::Font::CreateFromDialog(HWND hDlg, const wchar_t* name, int points, bool bold, bool italic)
{
	Delete();
	RECT rect;
	rect.bottom =  (int)(0.81*points+0.5);
	::MapDialogRect(hDlg, &rect);
	logfont.lfHeight = - abs(rect.bottom);
	logfont.lfWeight = bold ? 700 : 0;
	logfont.lfItalic = italic ? 1 : 0;
	lstrcpy (logfont.lfFaceName, name);
	return this->Create();
}

HFONT Gdi::Font::CreateFromDialog(HWND hDlg, const wstring& name, int points, bool bold, bool italic)
{
	return CreateFromDialog(hDlg, name.c_str(), points, bold, italic);
}

//________________________________________________________
Gdi::Font::~Font(void)
{
	Delete();
}

Gdi::Font::Font(const Win::Gdi::Font& init) // Copy constructor
{
	this->Constructor();
	Copy(init);
}
		
Win::Gdi::Font& Gdi::Font::operator =(const Win::Gdi::Font& init)
{
	Copy(init);
	return *this;
}

void Gdi::Font::Copy(const Win::Gdi::Font& init)
{
	this->Delete();
	if (init.hFont==NULL) return;
	::GetObject(init.hFont, sizeof(LOGFONT), &this->logfont);
	this->Create();
}

LOGFONT& Gdi::Font::GetLogFont()
{
	return logfont;
}

void Gdi::Font::Delete()
{
	if (m_pGdi) m_pGdi->UpdateFontExt(NULL);
	if (hFont) ::DeleteObject(hFont);
	hFont = NULL;
	//
	logfont.lfHeight = 0;
	logfont.lfWidth = 0;
	logfont.lfEscapement = 0;
	logfont.lfOrientation = 0;
	logfont.lfWeight = FW_NORMAL;
	logfont.lfItalic = FALSE;
	logfont.lfUnderline = FALSE;
	logfont.lfStrikeOut = FALSE;
	logfont.lfCharSet = DEFAULT_CHARSET;
	logfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logfont.lfQuality = CLEARTYPE_NATURAL_QUALITY;
	logfont.lfPitchAndFamily = VARIABLE_PITCH | FF_DONTCARE;
	logfont.lfFaceName[0] = '\0';
	//
	m_pGdi = NULL;
}

//HFONT Gdi::Font::CreateForDragAndDrop(const wchar_t* faceName, int height)
//{
//	LOGFONT logfont;
//	logfont.lfHeight = -height;
//	logfont.lfWidth = 0;
//	logfont.lfEscapement = 0;
//	logfont.lfOrientation = 0;
//	logfont.lfWeight = FW_NORMAL;
//	logfont.lfItalic = FALSE;
//	logfont.lfUnderline = FALSE;
//	logfont.lfStrikeOut = FALSE;
//	logfont.lfCharSet = DEFAULT_CHARSET;
//	logfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
//	logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
//	logfont.lfQuality = NONANTIALIASED_QUALITY; // this is the one
//	logfont.lfPitchAndFamily = VARIABLE_PITCH | FF_DONTCARE;
//	lstrcpy(logfont.lfFaceName, faceName);
//	return Create(logfont);
//}


HFONT Gdi::Font::Create()
{
	if (hFont) ::DeleteObject(hFont);
	hFont = NULL;
	//
	hFont = ::CreateFontIndirect(&logfont);
	if (m_pGdi) m_pGdi->UpdateFontExt(this);
	return hFont;
}

HFONT Gdi::Font::Create(LOGFONT& logFont)
{
	if (hFont) ::DeleteObject(hFont);
	hFont = NULL;
	this->logfont = logFont;
	hFont = ::CreateFontIndirect(&logFont);
	if (m_pGdi) m_pGdi->UpdateFontExt(this);
	return hFont;
}

void Gdi::Font::InitializeLogfont(LOGFONT& logfont)
{
	logfont.lfHeight = 0;
	logfont.lfWidth = 0;
	logfont.lfEscapement = 0;
	logfont.lfOrientation = 0;
	logfont.lfWeight = FW_NORMAL;
	logfont.lfItalic = FALSE;
	logfont.lfUnderline = FALSE;
	logfont.lfStrikeOut = FALSE;
	logfont.lfCharSet = DEFAULT_CHARSET;
	logfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logfont.lfQuality = DEFAULT_QUALITY;
	logfont.lfPitchAndFamily = VARIABLE_PITCH | FF_DONTCARE;
	logfont.lfFaceName[0] = '\0';
}

int Gdi::Font::GetIdealFontSize(const wstring& text, double width, double height)
{
	if (text.empty()) return 120;
	const int length = text.length();
	double charCount=2;
	for(int i=0; i<length; i++)
	{
		if (text[i]==',' || text[i]=='.' || text[i]==':' || text[i]==';' || text[i]==' ')
			charCount+=0.72;
		else if (text[i]=='I' || text[i]=='1' || text[i]=='i' || text[i]=='l' || text[i]=='!')
			charCount+=0.8;
		else if (text[i]=='(' || text[i]==')' || text[i]=='t' || text[i]=='f')
			charCount+=0.85;
		else if (text[i]=='m' || text[i]=='w')
			charCount+=1.8;
		else if (text[i]=='M' || text[i]=='W' || text[i]=='Q' || text[i]=='O'  || text[i]=='%'  || text[i]=='@')
			charCount+=2.12;
		else if (::isupper(text[i])) 
			charCount+=1.45;
		else
			charCount+=1.0;
	}
	int nWidth = (int)(width*2.0/charCount+0.5);
	int nHeight = (int)(height*1.1+0.5);
	return MINIMUM(nWidth, nHeight)*10;
}



//_____________________________________________________________________Gdi::Pen
Gdi::Pen::Pen(void)
{
	m_hPen = NULL;
	m_pGdi = NULL;
}

Gdi::Pen::~Pen(void)
{
	Delete();
}

void Gdi::Pen::Delete()
{
	if (m_pGdi) m_pGdi->UpdatePenExt(NULL);
	if (m_hPen != NULL) ::DeleteObject(m_hPen);
	m_hPen = NULL;
	m_pGdi = NULL;
}

Gdi::Pen::Pen(int nPenStyle, int nWidth, COLORREF color)
{
	m_hPen = NULL;
	m_pGdi = NULL;
	this->Create(nPenStyle, nWidth, color);
}

// PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT
// PS_DASHDOTDOT, PS_NULL, PS_INSIDEFRAME
// Call SetBkMode_(true) to avoid filling the gaps
// Use the RGB macro to create COLORREF
HPEN Gdi::Pen::Create(int nPenStyle, int nWidth, COLORREF color)
{
	if (m_hPen) ::DeleteObject(m_hPen);
	m_hPen = CreatePen(nPenStyle, nWidth, color);
	if (m_pGdi) m_pGdi->UpdatePenExt(this);
	return m_hPen;
}

//_____________________________________________________________________Gdi::Brush
Gdi::Brush::Brush(void)
{
	m_hBrush = NULL;
	m_pGdi = NULL;
}

void Gdi::Brush::Delete()
{
	if (m_pGdi) m_pGdi->UpdateBrushExt(NULL);
	if (m_hBrush) ::DeleteObject(m_hBrush);
	m_hBrush = NULL;
	m_pGdi = NULL;
}

Gdi::Brush::~Brush(void)
{
	if (m_pGdi) m_pGdi->UpdateBrushExt(NULL);
	if (m_hBrush) ::DeleteObject(m_hBrush);
}

Gdi::Brush::Brush(COLORREF color)
{
	m_hBrush = NULL;
	m_pGdi = NULL;
	this->CreateSolid(color);
}

HBRUSH Gdi::Brush::CreatePattern(HINSTANCE hInstance, const wchar_t * pszBitmap)
{
	HBITMAP h = LoadBitmap(hInstance, pszBitmap);
	if (m_hBrush) ::DeleteObject(m_hBrush);
	m_hBrush = ::CreatePatternBrush(h);
	::DeleteObject(h);
	if (m_pGdi) m_pGdi->UpdateBrushExt(this);
	return m_hBrush;
}

HBRUSH Gdi::Brush::CreateSolid(COLORREF color)
{
	if (m_hBrush) ::DeleteObject(m_hBrush);
	m_hBrush = ::CreateSolidBrush(color);
	if (m_pGdi) m_pGdi->UpdateBrushExt(this);
	return m_hBrush;
}

//HS_BDIAGONAL   Downward hatch (left to right) at 45 degrees 
//HS_CROSS   Horizontal and vertical crosshatch 
//HS_DIAGCROSS   Crosshatch at 45 degrees 
//HS_FDIAGONAL   Upward hatch (left to right) at 45 degrees 
//HS_HORIZONTAL   Horizontal hatch 
//HS_VERTICAL   Vertical hatch
HBRUSH Gdi::Brush::CreateHatch(int nHatchStyle, COLORREF color)
{
	if (m_hBrush) ::DeleteObject(m_hBrush);
	m_hBrush = ::CreateHatchBrush(nHatchStyle, color);
	if (m_pGdi) m_pGdi->UpdateBrushExt(this);
	return m_hBrush;
}

//_____________________________________________________________________Gdi::Color3D
Gdi::Color3D::Color3D(void)
{
	m_color = 0;
}

Gdi::Color3D::~Color3D(void)
{
}

Gdi::Color3D::Color3D(COLORREF color)
{
	m_color = 0;
	this->SetColor(color);
}

COLORREF Gdi::Color3D::GetColor()
{
	return m_color;
}

Win::Gdi::Pen& Gdi::Color3D::GetHighLight()
{
	return m_penHighLight;
}

Win::Gdi::Pen& Gdi::Color3D::GetLight()
{
	return m_penLight;
}

Win::Gdi::Pen& Gdi::Color3D::GetShadow()
{
	return m_penShadow;
}

Win::Gdi::Pen& Gdi::Color3D::GetDarkShadow()
{
	return m_penDarkShadow;
}

Win::Gdi::Brush& Gdi::Color3D::GetFilling()
{
	return m_brushFilling;
}

bool Gdi::Color3D::IsCloseToBlack(const COLORREF color)
{
	int nBritness = (int)(0.9*GetRValue(color) + 2.0* GetGValue(color) + 0.7*GetBValue(color)+0.5);
	return (nBritness<255);
}

COLORREF Gdi::Color3D::AddLight(const COLORREF color, int delta)
{
	if (delta == 0) return color;
	if (delta > 0)
	{
		int nRed = MINIMUM(255, (GetRValue(color)+delta));
		int nGreen = MINIMUM(255, (GetGValue(color)+delta));
		int nBlue = MINIMUM(255, (GetBValue(color)+delta));
		return RGB(nRed, nGreen, nBlue);
	}
	int nRed = MAXIMUM(0, (GetRValue(color)+delta));
	int nGreen = MAXIMUM(0, (GetGValue(color)+delta));
	int nBlue = MAXIMUM(0, (GetBValue(color)+delta));
	return RGB(nRed, nGreen, nBlue);
}

COLORREF Gdi::Color3D::GetHighLightColor(COLORREF color)
{
	return AddLight(color, 50);
}

COLORREF Gdi::Color3D::GetLightColor(COLORREF color)
{
	return AddLight(color, 25);
}

COLORREF Gdi::Color3D::GetShadowColor(COLORREF color)
{
	return AddLight(color, -30);
}

COLORREF Gdi::Color3D::GetDarkShadowColor(COLORREF color)
{
	return AddLight(color, -60);
}

void Gdi::Color3D::SetFromSystemColor()
{
	m_color = GetSysColor(COLOR_BTNFACE);
	m_brushFilling.CreateSolid(m_color);
	m_penHighLight.Create(PS_SOLID, 1, GetSysColor(COLOR_BTNHIGHLIGHT));
	m_penLight.Create(PS_SOLID, 1, GetSysColor(COLOR_3DLIGHT));
	m_penShadow.Create(PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW));
	m_penDarkShadow.Create(PS_SOLID, 1, GetSysColor(COLOR_3DDKSHADOW));
}

void Gdi::Color3D::SetColor(COLORREF color)
{
	m_color = color;
	m_brushFilling.CreateSolid(m_color);
	m_penHighLight.Create(PS_SOLID, 1, GetHighLightColor(color));
	m_penLight.Create(PS_SOLID, 1, GetLightColor(color));
	m_penShadow.Create(PS_SOLID, 1, GetShadowColor(color));
	m_penDarkShadow.Create(PS_SOLID, 1, GetDarkShadowColor(color));
}

// Computes the perfect color to make the color to notice
COLORREF Gdi::Color3D::GetConstrastColor(COLORREF color)
{
	int nRed = (GetRValue(color)<128) ? (128+GetRValue(color)) : (255-GetRValue(color));
	int nGreen = (GetGValue(color)<128) ? (128+GetGValue(color)) : (255-GetGValue(color));
	int nBlue = (GetBValue(color)<128) ? (128+GetBValue(color)) : (255-GetBValue(color));

	return RGB(nRed, nGreen, nBlue);
	//if (Win::Gdi::Color3D::IsCloseToBlack(color)) return Win::Gdi::Color3D::GetHighLightColor(color);
	//return Win::Gdi::Color3D::GetShadowColor(color);
}

COLORREF Gdi::Color3D::AddColors(COLORREF color1, COLORREF color2)
{
	int nRed = GetRValue(color1)+GetRValue(color2);
	int nGreen =GetGValue(color1)+GetGValue(color2);
	int nBlue = GetBValue(color1)+GetBValue(color2);
	//int nMax = MAXIMUM(nRed, MAXIMUM(nGreen, nBlue));
	//if (nMax>255)
	//{

	//}
	return RGB(nRed/2, nGreen/2, nBlue/2);
}

//_____________________________________________________________________IExportable and Exporter
Exporter::Exporter(void)
{
}

Exporter::~Exporter(void)
{
}

bool Exporter::CopyToBitmap(Win::IExportable& ixp, int width, int height, bool clientEdge, Win::DDBitmap& result)
{
	int initial_width = 0;
	int initial_height = 0;
	HWND hWnd = ixp.GetControlInfo(initial_width, initial_height);
	if (hWnd==NULL)
	{
		hWnd = ::GetDesktopWindow();
	}
	HDC hdc = result.CreateCompatible(hWnd, width, height);
	ixp.SetControlSize(width, height);
	RECT rcPaint = {0, 0, width, height};
	Win::Gdi gdi(result, rcPaint, false);
	ixp.OnPaintControl(gdi);
	if (clientEdge)
	{
		RECT rcBorder = {0, 0, width, height};
		gdi.DrawEdge(&rcBorder, EDGE_SUNKEN, BF_RECT);
	}
	result.DeleteMemDC();
	ixp.SetControlSize(initial_width, initial_height);
	return true;
}

// File type is *.emf
bool Exporter::SaveToFile(const wchar_t* filename, Win::IExportable& ixp)
{
	return Win::Exporter::SaveToFile(filename, 0.75, ixp);
}

bool Exporter::CopyToClipboard(Win::IExportable& ixp)
{
	//const double aspectRatio = 0.75;
	//int tmpWidth = 0;
	//int tmpHeight = 0;
	int width, height;
	//HWND hWnd = ixp.GetControlInfo(tmpWidth, tmpHeight);
	HWND hWnd = ixp.GetControlInfo(width, height);
	Win::Metafile emf;
	HDC hdcEmf = NULL;
	HDC hdcRef = ::GetDC(hWnd);
	RECT rect;
	//int width = tmpWidth;//32767;
	//int height = tmpHeight;//(int)(aspectRatio*32767+0.5);
	PAINTSTRUCT ps;
	RECT rcPaint = {0, 0, width, height};

	// Determine the picture frame dimensions. 
	const int displayWidthMilimeter = GetDeviceCaps(hdcRef, HORZSIZE); 
	const int displayHeightMilimeter = GetDeviceCaps(hdcRef, VERTSIZE); 
	const int displayWidthPixel = GetDeviceCaps(hdcRef, HORZRES);
	const int displayHeightPixel = GetDeviceCaps(hdcRef, VERTRES);
	 
	// Convert client coordinates to .01-mm units. 
	rect.left = 0;
	rect.top = 0;
	rect.right = (width * displayWidthMilimeter * 100)/displayWidthPixel; 
	rect.bottom = (height * displayHeightMilimeter * 100)/displayHeightPixel;
	//ixp.SetControlSize(width, height);

	hdcEmf = emf.Create();
	ps.hdc = hdcEmf;
	ps.rcPaint = rcPaint;
	
	Win::Gdi gdi(ps, false);
	ixp.OnPaintControl(gdi);
	emf.Close();
	Win::Clipboard::CopyMetaFileToClipboard(hWnd, emf);
	::ReleaseDC(hWnd, hdcRef);
	//ixp.SetControlSize(tmpWidth, tmpHeight);

	return true;
}

// File type is *.emf
bool Exporter::SaveToFile(const wchar_t* filename, double aspectRatio, Win::IExportable& ixp)
{
	int tmpWidth = 0;
	int tmpHeight = 0;
	HWND hWnd = ixp.GetControlInfo(tmpWidth, tmpHeight);
	Win::Metafile emf;
	HDC hdcEmf = NULL;
	HDC hdcRef = ::GetDC(hWnd);
	RECT rect;
	int width = 8000; //32767;
	int height = (int)(aspectRatio*width+0.5);
	PAINTSTRUCT ps;
	RECT rcPaint = {0, 0, width, height};

	// Determine the picture frame dimensions. 
	const int displayWidthMilimeter = GetDeviceCaps(hdcRef, HORZSIZE); 
	const int displayHeightMilimeter = GetDeviceCaps(hdcRef, VERTSIZE); 
	const int displayWidthPixel = GetDeviceCaps(hdcRef, HORZRES);
	const int displayHeightPixel = GetDeviceCaps(hdcRef, VERTRES);
	 
	// Convert client coordinates to .01-mm units. 
	rect.left = 0;
	rect.top = 0;
	rect.right = (width * displayWidthMilimeter * 100)/displayWidthPixel; 
	rect.bottom = (height * displayHeightMilimeter * 100)/displayHeightPixel;
	ixp.SetControlSize(width, height);

	hdcEmf = emf.CreateToFile(hdcRef, &rect, filename, L"xy chart\0graph\0");
	ps.hdc = hdcEmf;
	ps.rcPaint = rcPaint;
	
	Win::Gdi gdi(ps, false);
	ixp.OnPaintControl(gdi);
	emf.Close();
	gdi.Delete();
	
	//emf.Delete();
	::ReleaseDC(hWnd, hdcRef);
	ixp.SetControlSize(tmpWidth, tmpHeight);

	return true;
}

//_____________________________________________________________________ PrintInfo

//_____________________________________________________________________ IPrint

//_____________________________________________________________________ IPrintDoc

//_________________________________________________________________________Timer
Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::Set(UINT_PTR timer_id, UINT duration)
{
	::SetTimer(iparent->GetHWND(), timer_id, duration, NULL);
}
		

void Timer::Kill(UINT_PTR timer_id)
{
	::KillTimer(iparent->GetHWND(), timer_id);
}


void Timer::SetParent(Win::IParent* iparent)
{
	this->iparent = iparent;
}

//_____________________________________________________________________Module

HINSTANCE Module::hInstance = NULL;
#ifdef WIN_GDI_PLUS_ON
	Gdiplus::GdiplusStartupInput Module::_gdiPlusStartupInput;
	ULONG_PTR Module::_gdiPlusToken;
	bool Module::_isGdiPlusOn = false;
#endif

Module::Module(void)
{
	this->hWnd = NULL;
	this->width = 0;
	this->height = 0;
	this->id = -1;
	//
	this->_dock.left = DOCK_BORDER;
	this->_dock.top = DOCK_BORDER;
	this->_dock.right = DOCK_NONE;
	this->_dock.bottom = DOCK_NONE;
	//
	_initialRect.left = 0;
	_initialRect.top = 0;
	_initialRect.right = 0;
	_initialRect.bottom = 0;
	//
	//_hfont = NULL;
	//
	timer.SetParent(this);
}

Module::~Module(void)
{
}

 //insertAfter: HWND_BOTTOM, HWND_NOTOPMOST, HWND_TOP, HWND_TOPMOST
// flags: SWP_ASYNCWINDOWPOS, SWP_DEFERERASE, SWP_DEFERERASE, SWP_FRAMECHANGED, SWP_HIDEWINDOW, SWP_NOACTIVATE, 
//SWP_NOCOPYBITS, SWP_NOMOVE, SWP_NOOWNERZORDER, SWP_NOREDRAW, SWP_NOREPOSITION, SWP_NOSENDCHANGING
//SWP_NOSIZE, SWP_NOZORDER, SWP_SHOWWINDOW
void Module::SetWindowPosition(int x, int y, int width, int height, HWND insertAfter, unsigned int flags)
{
	::SetWindowPos(hWnd, insertAfter, x, y, width, height, flags);
}

#ifdef WIN_DAC_ADC_SUPPORT
bool Module::PlayWaveSound(const wchar_t* filename)
{
	return (::PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT) != FALSE);
}

bool Module::PlayWaveSound(HINSTANCE hInstance, const wchar_t* resource_id)
{
	HRSRC hrsrc = ::FindResource(hInstance, MAKEINTRESOURCE(resource_id), L"WAVE");
	if (hrsrc==NULL) return false;

	HANDLE hResource = ::LoadResource (hInstance, hrsrc); 
	if (hResource == NULL) return false;

	LPTSTR lpRes = (LPTSTR)::LockResource (hResource);
  
	bool ok = false;
	if (lpRes != NULL) 
	{ 
		if (::PlaySound(lpRes, hInstance, SND_MEMORY | SND_SYNC | SND_NODEFAULT) != FALSE)
		{
			::FreeResource(hResource);
			return true;
		}
	} 
	else
	{
		::FreeResource(hResource);
	}
  return false; 
}
#endif

void Module::SetDock(int left, int top, int right, int bottom)
{
	if (left != DOCK_BORDER && left != DOCK_CENTER) left = DOCK_NONE;
	if (right != DOCK_BORDER &&  right != DOCK_CENTER) right = DOCK_NONE;
	if (top != DOCK_BORDER && top != DOCK_CENTER) top = DOCK_NONE;
	if (bottom != DOCK_BORDER && bottom != DOCK_CENTER) bottom = DOCK_NONE;
	this->_dock.left = left;
	this->_dock.right = right;
	this->_dock.top = top;
	this->_dock.bottom = bottom;
}

void Module::GetDock(int& left, int& top, int& right, int& bottom)
{
	left = _dock.left;
	top = _dock.top;
	right = _dock.right;
	bottom = _dock.bottom;
}

void Module::DoDock(int initialWidth, int initialHeight, int newWidth, int newHeight)
{
	RECT rc = _initialRect;
	bool modified = false;
	//_________________________________________________________ Left + Right
	if (_dock.left == DOCK_BORDER && _dock.right == DOCK_BORDER)
	{
		modified = true;
		rc.right = newWidth - (initialWidth-_initialRect.right);
	}
	else if (_dock.left == DOCK_BORDER && _dock.right == DOCK_CENTER)
	{
		modified = true;
		rc.right = newWidth/2 - (initialWidth/2-_initialRect.right);
	}
	else if (_dock.left== DOCK_BORDER && _dock.right == DOCK_NONE)
	{
	}
	else if (_dock.left== DOCK_CENTER && _dock.right ==DOCK_BORDER)
	{
		modified = true;
		rc.left = newWidth/2 - (initialWidth/2-_initialRect.left);
		rc.right = newWidth - (initialWidth-_initialRect.right);
	}
	else if (_dock.left== DOCK_CENTER && _dock.right ==DOCK_CENTER)
	{
		modified = true;
		rc.left = newWidth/2 - (initialWidth/2-_initialRect.left);
		rc.right = newWidth/2 - (initialWidth/2-_initialRect.right);
	}
	else if (_dock.left == DOCK_CENTER && _dock.right == DOCK_NONE)
	{
		modified = true;
		rc.left = newWidth/2 - (initialWidth/2-_initialRect.left);
		rc.right = rc.left + (_initialRect.right - _initialRect.left);
	}
	else if (_dock.left== DOCK_NONE && _dock.right ==DOCK_BORDER)
	{
		modified = true;
		rc.right = newWidth - (initialWidth-_initialRect.right);
		rc.left = rc.right - (_initialRect.right - _initialRect.left);
	}
	else if (_dock.left== DOCK_NONE && _dock.right ==DOCK_CENTER)
	{
		modified = true;
		rc.right = newWidth/2 - (initialWidth/2-_initialRect.right);
		rc.left = rc.right - (_initialRect.right - _initialRect.left);
	}
	else if (_dock.left== DOCK_NONE && _dock.right ==DOCK_NONE)
	{
	}
	//_________________________________________________________ Top + Bottom
	if (_dock.top == DOCK_BORDER && _dock.bottom == DOCK_BORDER)
	{
		modified = true;
		rc.bottom = newHeight - (initialHeight -_initialRect.bottom);
	}
	else if (_dock.top == DOCK_BORDER && _dock.bottom == DOCK_CENTER)
	{
		modified = true;
		rc.bottom = newHeight /2 - (initialHeight /2-_initialRect.bottom);
	}
	else if (_dock.top== DOCK_BORDER && _dock.bottom == DOCK_NONE)
	{
	}
	else if (_dock.top== DOCK_CENTER && _dock.bottom ==DOCK_BORDER)
	{
		modified = true;
		rc.top = newHeight /2 - (initialHeight /2-_initialRect.top);
		rc.bottom = newHeight  - (initialHeight -_initialRect.bottom);
	}
	else if (_dock.top== DOCK_CENTER && _dock.bottom ==DOCK_CENTER)
	{
		modified = true;
		rc.top = newHeight /2 - (initialHeight /2-_initialRect.top);
		rc.bottom = newHeight /2 - (initialHeight /2-_initialRect.bottom);
	}
	else if (_dock.top == DOCK_CENTER && _dock.bottom == DOCK_NONE)
	{
		modified = true;
		rc.top = newHeight /2 - (initialHeight /2-_initialRect.top);
		rc.bottom = rc.top + (_initialRect.bottom - _initialRect.top);
	}
	else if (_dock.top== DOCK_NONE && _dock.bottom ==DOCK_BORDER)
	{
		modified = true;
		rc.bottom = newHeight  - (initialHeight -_initialRect.bottom);
		rc.top = rc.bottom - (_initialRect.bottom - _initialRect.top);
	}
	else if (_dock.top== DOCK_NONE && _dock.bottom ==DOCK_CENTER)
	{
		modified = true;
		rc.bottom = newHeight /2 - (initialHeight /2-_initialRect.bottom);
		rc.top = rc.bottom - (_initialRect.bottom - _initialRect.top);
	}
	else if (_dock.top== DOCK_NONE && _dock.bottom ==DOCK_NONE)
	{
	}
	if (modified)
	{
		::MoveWindow(hWnd, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, TRUE);
		::InvalidateRect(hWnd, NULL, TRUE);
	}
}

void Module::GetInitialRect(RECT& initialRect)
{
	initialRect = this->_initialRect;
}

void Module::GetRect(RECT& rc)
{
	::GetWindowRect(hWnd, &rc);
	::MapWindowPoints(HWND_DESKTOP, ::GetParent(hWnd), (LPPOINT)&rc, 2);
}

void Module::SetRect(RECT& rc)
{
	RECT currentRc;
	this->GetRect(currentRc);
	const int actualWidth = currentRc.right-currentRc.left;
	const int actualHeight = currentRc.bottom-currentRc.top;
	//
	const int newWidth = rc.right-rc.left;
	const int newHeight = rc.bottom-rc.top;
	//
	//const bool repaint = (actualWidth!=newWidth) || (actualHeight!=newHeight);

	::MoveWindow(hWnd, rc.right, rc.top, newWidth, newHeight, true);
}

void Module::SetPositionX(int x)
{
	RECT rc;
	this->GetRect(rc);
	const int width = rc.right-rc.left;
	const int height = rc.bottom-rc.top;
	::MoveWindow(hWnd, x, rc.top, width, height, true);
}

int Module::GetPositionX()
{
	RECT rc;
	this->GetRect(rc);
	return rc.left;
}

void Module::SetPositionY(int y)
{
	RECT rc;
	this->GetRect(rc);
	const int width = rc.right-rc.left;
	const int height = rc.bottom-rc.top;
	::MoveWindow(hWnd, rc.left, y, width, height, true);
}

int Module::GetPositionY()
{
	RECT rc;
	this->GetRect(rc);
	return rc.top;
}

void Module::SetWidth(int width)
{
	RECT rc;
	::GetWindowRect(hWnd, &rc); // screen coordinates
	const int height = rc.bottom-rc.top;
	::MapWindowPoints(HWND_DESKTOP, ::GetParent(hWnd), (LPPOINT)&rc, 2); // From screen coordinates to Client Coordinates
	::MoveWindow(hWnd, rc.left, rc.top, width, height, true);
	this->width = width;
}

int Module::GetWidth()
{
	RECT rc;
	::GetWindowRect(hWnd, &rc);
	return (rc.right-rc.left);
}

void Module::SetHeight(int height)
{
	RECT rc;
	::GetWindowRect(hWnd, &rc);
	::MapWindowPoints(HWND_DESKTOP, ::GetParent(hWnd), (LPPOINT)&rc, 2);
	const int width = rc.right-rc.left;
	::MoveWindow(hWnd, rc.left, rc.top, width, height, true);
	this->height = height;
}

int Module::GetHeight()
{
	RECT rc;
	::GetWindowRect(hWnd, &rc);
	return (rc.bottom-rc.top);
}

LRESULT Module::SendMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	return ::SendMessage(hWnd, message, wParam, lParam);
}

WNDPROC Module::SetProc(WNDPROC wndProc)
{
	return (WNDPROC)(LONG_PTR) ::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG)(LONG_PTR)wndProc);
}

LRESULT Module::SetRedraw(bool redraw)
{
	BOOL tmp = redraw ? TRUE : FALSE;
	return ::SendMessage(hWnd, WM_SETREDRAW, (WPARAM)tmp, 0);
}

BOOL Module::Move(int x, int y, int nWidth, int nHeight, bool repaint)
{
	BOOL tmp = repaint ? TRUE : FALSE;
	return ::MoveWindow(hWnd, x, y, nWidth, nHeight, tmp);
}

BOOL Module::Move(RECT& rect, bool repaint)
{
	BOOL tmp = repaint ? TRUE : FALSE;
	return ::MoveWindow(hWnd, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, tmp);
}

BOOL Module::MoveToFill(Win::Event& e)
{
	return ::MoveWindow(hWnd, 0, 0, LOWORD(e.lParam), HIWORD(e.lParam), TRUE);
}

int Module::Scroll(int deltaX, int deltaY)
{
	return ::ScrollWindowEx(hWnd, deltaX, deltaY, (CONST RECT *) NULL, 
        (CONST RECT *) NULL, (HRGN) NULL, (LPRECT) NULL, 
        SW_ERASE | SW_INVALIDATE); 
}

// prcUpdate returns the invalidated rectangle
int Module::Scroll(int deltaX, int deltaY, LPRECT prcUpdate)
{
	return ::ScrollWindowEx(hWnd, deltaX, deltaY, (CONST RECT *) NULL, 
        (CONST RECT *) NULL, (HRGN) NULL, (LPRECT) prcUpdate, 
        SW_ERASE | SW_INVALIDATE); 
}

int Module::SetScrollInfoV(SCROLLINFO& si)
{
	si.cbSize = sizeof(SCROLLINFO);
	return ::SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
}

int Module::SetScrollInfoV(int minimum, int maximum, int position)
{
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_POS | SIF_RANGE;
	si.nMin = minimum;
	si.nMax = maximum;
	si.nPos = position;
	return ::SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
}

int Module::SetScrollInfoV(int minimum, int maximum, int position, int page)
{
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_POS | SIF_RANGE | SIF_PAGE;
	si.nMin = minimum;
	si.nMax = maximum;
	si.nPos = position;
	si.nPage = page;
	return ::SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
}

int Module::SetScrollInfoH(SCROLLINFO& si)
{
	si.cbSize = sizeof(SCROLLINFO);
	return ::SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
}

int Module::SetScrollInfoH(int minimum, int maximum, int position)
{
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_POS | SIF_RANGE;
	si.nMin = minimum;
	si.nMax = maximum;
	si.nPos = position;
	return ::SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
}

void Module::LockUpdate(bool locked)
{
	if (locked)
		::LockWindowUpdate(hWnd);
	else
		::LockWindowUpdate(NULL);
}

BOOL Module::Redraw(const RECT * lprcUpdate, HRGN hrgnUpdate, UINT flags)
{
	return ::RedrawWindow(hWnd, lprcUpdate, hrgnUpdate, flags);
}

int Module::GetScrollPositionV(SCROLLINFO& si, Win::Event& e)
{
	si.cbSize = sizeof (SCROLLINFO);
	si.fMask  = SIF_ALL;
	::GetScrollInfo (hWnd, SB_VERT, &si);

	// Save the position for comparison later on
	int nVertPos = si.nPos;

	switch (LOWORD (e.wParam))
	{
	case SB_TOP:
		si.nPos = si.nMin;
		break;	    
	case SB_BOTTOM:
		si.nPos = si.nMax;
		break;    
	case SB_LINEUP:
		si.nPos -= 1;
		break;	    
	case SB_LINEDOWN:
		si.nPos += 1;
		break;	    
	case SB_PAGEUP:
		si.nPos -= si.nPage;
		break;	    
	case SB_PAGEDOWN:
		si.nPos += si.nPage;
		break;	    
	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos;
		break;    
	case SB_THUMBPOSITION:
		si.nPos = si.nTrackPos;
        break;
	default:
		break;         
	}
	// Set the position and then retrieve it.  Due to adjustments
	//   by Windows it may not be the same as the value set.
	si.fMask = SIF_POS;
	::SetScrollInfo (hWnd, SB_VERT, &si, TRUE);
	::GetScrollInfo (hWnd, SB_VERT, &si);

	// If the position has changed, scroll the window and update it
	return (nVertPos - si.nPos); 
	//if (si.nPos != nVertPos)
	//{      
	//	return true;
	//}
	//return false;
}

int Module::GetScrollPositionH(SCROLLINFO& si, Win::Event& e)
{
	si.cbSize = sizeof (SCROLLINFO);
	si.fMask  = SIF_ALL;
	::GetScrollInfo (hWnd, SB_HORZ, &si);

	// Save the position for comparison later on
	int position = si.nPos;

	switch (LOWORD (e.wParam))
	{
	case SB_LINELEFT:
		si.nPos -= 1;
		break;
	case SB_LINERIGHT:
		si.nPos += 1 ;
		break;
	case SB_PAGELEFT:
		si.nPos -= si.nPage;
		break;
	case SB_PAGERIGHT:
		si.nPos += si.nPage;
		break;
	case SB_THUMBPOSITION:
		si.nPos = si.nTrackPos;
        break;
	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos;
		break; 
	//default:
	//break;
	}
	// Set the position and then retrieve it.  Due to adjustments
	//   by Windows it may not be the same as the value set.
	si.fMask = SIF_POS;
	::SetScrollInfo (hWnd, SB_HORZ, &si, TRUE);
	::GetScrollInfo (hWnd, SB_HORZ, &si);

	// If the position has changed, scroll the window and update it
	return (position- si.nPos);
	//if (si.nPos != position)
	//{      
	//	return true;
	//}
	//return false;
}

void Module::Close()
{
	::SendMessage(hWnd, WM_CLOSE, 0, 0);
}

void Module::RefreshMenu()
{
	::DrawMenuBar(hWnd);	
}		

BOOL Module::SetMenu(HMENU hMenu)
{
	return ::SetMenu(hWnd, hMenu);
}

HMENU Module::GetMenu()
{
	return ::GetMenu(hWnd);
}

void Module::ScreenToClient(POINT& pt)
{
	::ScreenToClient(hWnd, &pt);
}

void Module::ClientToScreen(POINT& pt)
{
	::ClientToScreen(hWnd, &pt);
}

//void Module::GetRect(RECT& rc)
//{
//	::GetWindowRect(hWnd, &rc);
//}

void Module::GetClientRect(RECT& rc)
{
	::GetClientRect(hWnd, &rc);
}

void Module::GetRelativeRect(HWND parent, RECT& rc)
{  
	::GetWindowRect(hWnd, &rc);
	::MapWindowPoints(NULL, parent, (LPPOINT)&rc, 2);
}

int Module::GetTextLength()
{
	return ::GetWindowTextLength(hWnd);
}

void Module::Repaint(RECT* rc, bool erase)
{
	::InvalidateRect(hWnd, rc, (erase!=0));
}

int Module::GetID()
{
	return ::GetWindowLong(hWnd, GWL_ID);
}

BOOL Module::SetForeground()
{
	return ::SetForegroundWindow(hWnd);
}

HWND Module::GetParent()
{
	return ::GetParent(hWnd);
}

LONG_PTR Module::GetLongPtr(int flags)
{ 
	return ::GetWindowLongPtr(hWnd, flags);
}

void Module::AlwaysOnTop(bool onTop)
{
	::SetWindowPos(hWnd, onTop ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, 
		SWP_NOMOVE | SWP_NOSIZE);
}

void Module::SetClassCursor(HCURSOR hcursor)
{
	::SetClassLongPtr(hWnd, GCLP_HCURSOR, (LONG)(LONG_PTR)hcursor);
}

void Module::SetClassIcon(HICON hicon)
{
	::SetClassLongPtr(hWnd, GCLP_HICONSM, (LONG)(LONG_PTR)hicon);
	::SetClassLongPtr(hWnd, GCLP_HICON, (LONG)(LONG_PTR)hicon);
}


//	this->SetClassBackground(brush);
// ::InvalidateRect(hWnd, NULL, true);
void Module::SetClassBackground(HBRUSH hbrush)
{
	::SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)(LONG_PTR)hbrush);
}

HICON Module::GetClassIcon(bool smallIcon)
{
	return (HICON) (LONG_PTR)::GetClassLongPtr(hWnd, smallIcon ? GCLP_HICONSM : GCLP_HICON);
}

//void AlwaysOnTop(bool onTop);
//void SetClassCursor(HCURSOR hcursor);
//void SetClassIcon(HICON hicon, bool smallIcon);
//void SetClassBackground(HBRUSH hbrush);
//HICON GetClassIcon(bool smallIcon);
//HWND GetDialogItem(HWND parent, int item_id);

void Module::Show(int cmdShow)
{
	::ShowWindow(hWnd, cmdShow);
}

void Module::Maximize()
{
	::ShowWindow(hWnd, SW_MAXIMIZE);
}

void Module::Minimize()
{
	::ShowWindow(hWnd, SW_MINIMIZE);
}

void Module::Destroy()
{
	::DestroyWindow(hWnd);
}

void Module::Update()
{
	::UpdateWindow(hWnd);
}

HDC Module::GetWindowDC()
{
	return ::GetDC(hWnd);
}

HDC Module::GetDC()
{
	return ::GetWindowDC(hWnd);
}

void Module::ReleaseDC(HDC hdc)
{
	::ReleaseDC(hWnd, hdc);
}

void Module::EnableCloseButton(bool enabled)
{
	::EnableMenuItem (::GetSystemMenu (hWnd, FALSE), SC_CLOSE, enabled ? MF_ENABLED :MF_GRAYED);
}

void Module::EnableMoveButton(bool enabled)
{
	::EnableMenuItem (::GetSystemMenu (hWnd, FALSE), SC_MOVE, enabled ? MF_ENABLED :MF_GRAYED);
}

void Module::EnableSizeButton(bool enabled)
{
	::EnableMenuItem (::GetSystemMenu (hWnd, FALSE), SC_SIZE, enabled ? MF_ENABLED :MF_GRAYED);
}


void Module::InitialUpdate(HWND hWndParent)
{
	::SendMessage(hWndParent, WM_WINADDCHILD, (WPARAM)this, (LPARAM)0);
}

void Module::UpdateValue()
{
}

HWND Module::GetDialogItem(HWND parent, int id)
{
	this->hWnd = ::GetDlgItem(parent, id);
	this->id = id;
	InitialUpdate(parent);
	return this->hWnd;
}

void Module::SetFont(Win::Gdi::Font& font)
{
	if (::IsWindow(hWnd))
	{
		::SendMessage(this->hWnd, WM_SETFONT, (WPARAM)font.GetHFONT(), MAKELPARAM(TRUE, TRUE));
	}
	//else
	//{
	//	_hfont = font.GetHFONT();
	//}
}

//Win::Gdi::Font& Module::GetFont()
//{
//	Win::Gdi::Font font;
//	return font;
//}

bool Module::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_COMMAND) return false;
	if (LOWORD(e.wParam)!= notification) return false;
	return true;
}

HINSTANCE Module::GetInstance()
{
	return hInstance;
}

// Returns the Window Text
wstring Module::GetText()
{
	wstring tmp;
	const int length = ::GetWindowTextLength(hWnd);
	tmp.resize(length);
	::GetWindowText(hWnd, (wchar_t*)tmp.data(), length+1);
	return tmp;
}

void Module::SetText(const wstring text)
{
	::SetWindowText(hWnd, text.c_str());
}

HWND Module::Create(DWORD dwExStyle, const wchar_t* pszWindowName, 
					DWORD dwStyle, int x, int y, int width, int height, HWND hParent, int id)
{
	if (!::IsWindow(this->hWnd)) this->hWnd=NULL;
	if (this->hWnd!=NULL) return NULL;
	//
	this->_initialRect.left = x;
	this->_initialRect.right = x + width;
	this->_initialRect.top = y;
	this->_initialRect.bottom = y + height;
	//
	this->hWnd = ::CreateWindowEx(dwExStyle, this->GetClassName(), pszWindowName, dwStyle, 
		x, y, width, height, hParent, (HMENU)id, this->hInstance, 0);

	if (this->hWnd==NULL)
	{
		Sys::DisplayLastError(NULL, this->GetClassName());
		_initialRect.left = 0;
		_initialRect.top = 0;
		_initialRect.right = 0;
		_initialRect.bottom = 0;
		return NULL;
	}
	//________________________________________________ store 'this' if subclassing is used
	::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)(LONG_PTR)this);
	this->id = (LONG_PTR)id;
	this->width = width;
	this->height = height;
	InitialUpdate(hParent);
	return this->hWnd;
}

HWND Module::SetFocus()
{
	return ::SetFocus(this->hWnd);
}

void Module::SetVisible(bool visible)
{
	::ShowWindow(this->hWnd, visible ? SW_SHOWNORMAL:SW_HIDE);
}

bool Module::IsVisible()
{
	return (::IsWindowVisible(this->hWnd)==TRUE);
}

void Module::SetEnable(bool enabled)
{
	::EnableWindow(this->hWnd, enabled ? TRUE : FALSE);
}

bool Module::GetEnable() 
{
	if (::IsWindow(hWnd))
	{
		return (::IsWindowEnabled(this->hWnd)==TRUE);
	}
	return true;
}

void Module::SetWindowText(const wchar_t* text)
{
	::SetWindowText(this->hWnd, text);
}

int Module::GetWindowText(wchar_t* text, int size)
{	
	return ::GetWindowText(this->hWnd, text, size); 
}

HWND Module::GetHWND()
{
	return this->hWnd;
}

//int Module::GetID()
//{
//	return id;
//}

Module::operator HWND() 
{
	return this->hWnd;
}

int Module::MessageBox(const wchar_t * text, const wchar_t * caption, UINT type)
{
	return ::MessageBox(this->hWnd, text, caption, type);
}

int Module::MessageBox(const wstring& text, const wstring& caption, UINT type)
{
	return ::MessageBox(this->hWnd, text.c_str(), caption.c_str(), type);
}

DWORD Module::SetCursorPos(int x, int y)
{
	return ::SetCursorPos(x, y);
}

//
//void Module::RemoveModelessDlgHWND(HWND hDlg)
//{
//	vector<HWND>::iterator p = NULL;
//
//	for(p = m_vModeless.begin(); p!=m_vModeless.end(); p++)
//	{
//		if (*p == hDlg)
//		{
//			m_vModeless.erase(p);
//			break;
//		}
//	}
//}
//
//
//void Module::AddModelessDlgHWND(HWND hDlg)
//{
//	m_vModeless.push_back(hDlg);
//}

//_____________________________________________________________________Window
Window::Window(void)
{
	initialWidth = 0;
	initialHeight = 0;
	_isMainWindow = false;
}

Window::~Window(void)
{
#ifdef WIN_GDI_PLUS_ON
	if (_isMainWindow && _isGdiPlusOn)
	{
		Gdiplus::GdiplusShutdown(_gdiPlusToken);
	}
#endif
}

void Window::GetWindowInformation(CREATESTRUCT& createStruct)
{
	memset(&createStruct, 0, sizeof(CREATESTRUCT));
	createStruct.dwExStyle = 0;
	createStruct.style = WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW;
	createStruct.x = CW_USEDEFAULT;
	createStruct.y = CW_USEDEFAULT;
	createStruct.cx = CW_USEDEFAULT;
	createStruct.cy = CW_USEDEFAULT;
}

// The function must return false, when the message is not being processed
bool Window::Window_WndProc(Win::Event& e)
{
	e.returnValue = FALSE;
	return false;
}

int Window::GetClientWidth()
{
	return this->width;
}

int Window::GetClientHeight()
{
	return this->height;
}

// Class styles:
// CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
// Cursor:
//IDC_APPSTARTING
//IDC_ARROW
//IDC_CROSS
//IDC_HAND
//IDC_HELP
//IDC_IBEAM
//IDC_NO
//IDC_SIZEALL
//IDC_SIZENESW
//IDC_SIZENS
//IDC_SIZENWSE
//IDC_SIZEWE
//IDC_UPARROW
//IDC_WAIT
// nIconID = 0 for no application icon
// nSmallIconID = 0 for no small icon applications
// nMenu = 0 for no menu applications 
// hInstance is required for the first class registered
bool Window::RegisterClassEx
				(
					UINT nClassStyle,
					bool bModelessDialog,
					HINSTANCE hInst,
					USHORT nIconId, USHORT nSmallIconId, 
					USHORT nMenu, HCURSOR hCursor,
					HBRUSH hBackground
				)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style = nClassStyle;
	wcex.lpfnWndProc	= (WNDPROC)this->InternalWndProc;
	wcex.cbClsExtra	= 0;
	wcex.cbWndExtra = bModelessDialog ? DLGWINDOWEXTRA : 0;
	if (this->hInstance==NULL) this->hInstance = hInst;
	wcex.hInstance = this->hInstance;
	wcex.hIcon	= (nIconId == 0) ? NULL : LoadIcon(this->hInstance, (const wchar_t *)nIconId);
	wcex.hCursor = hCursor;
	wcex.hbrBackground = hBackground; //(HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = (const wchar_t *)nMenu;
	wcex.lpszClassName	= this->GetClassName();
	wcex.hIconSm	= (nSmallIconId==0) ? 0 : LoadIcon(this->hInstance, (wchar_t*)nSmallIconId);

	return (::RegisterClassEx(&wcex)!=0);
}

bool Window::UserControlRegisterClass()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc	= (WNDPROC)InternalWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = Win::Window::hInstance;
	wcex.hIcon	= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(NULL_BRUSH);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= L"WINTEMPLA_USERCONTROL";
	wcex.hIconSm = NULL;
	return (::RegisterClassEx(&wcex)!=0);
}

// It register a window class for a custom control
bool Window::RegisterClassEx(HCURSOR hCursor, HBRUSH hbrBackground)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc	= (WNDPROC)InternalWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = this->hInstance;
	wcex.hIcon	= NULL;
	wcex.hCursor		= hCursor;
	wcex.hbrBackground	= hbrBackground;//HBRUSH(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= this->GetClassName();
	wcex.hIconSm = NULL;
	return (::RegisterClassEx(&wcex)!=0);
}

// It register a window class for a custom control
bool Window::RegisterGlobalClassEx(HCURSOR hCursor, HBRUSH hbrBackground)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style = CS_GLOBALCLASS | CS_DBLCLKS;
	wcex.lpfnWndProc	= (WNDPROC)InternalWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = this->hInstance;
	wcex.hIcon	= NULL;
	wcex.hCursor		= hCursor;
	wcex.hbrBackground	= hbrBackground;//HBRUSH(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= this->GetClassName();
	wcex.hIconSm = NULL;
	return (::RegisterClassEx(&wcex)!=0);
}

LRESULT CALLBACK Window::InternalWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* p = NULL;
	if ( uMsg == WM_NCCREATE )
	{
		if (IsBadReadPtr((void *) lParam, sizeof(CREATESTRUCT))==false)
		{
			LPCREATESTRUCT lpCS = (LPCREATESTRUCT) lParam;
			CREATESTRUCT* pCS = (CREATESTRUCT*)lpCS->lpCreateParams;
			p = (Window*) pCS->lpCreateParams;
			if (IsBadReadPtr(p, sizeof(Window))==false)
			{
				p->hWnd = hWnd;
				::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)(LONG_PTR)p);
			}
			else
			{
				::MessageBox(hWnd, L"Invalid pointer during WM_NCCREATE", 
					L"Win::Window::InternalWndProc", MB_ICONERROR);
			}
		}
		else
		{
			::MessageBox(hWnd, L"Invalid CREATESTRUCT pointer during WM_NCCREATE", 
				L"Win::Window::InternalWndProc", MB_ICONERROR);
		}
	}
	else
	{
		p = (Window*)(LONG_PTR)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}

	if (p==NULL) return DefWindowProc(hWnd, uMsg, wParam, lParam);

	Win::Event e;
	e.hWnd = hWnd;
	e.uMsg = uMsg;
	e.wParam = wParam;
	e.lParam = lParam;
	e.returnValue = 0; // If the message is processed return 0, otherwise return the value returned by DefWndProc

	switch(uMsg)
	{
	case WM_WINADDCHILD: 
		p->Window_WinAddChild(e); 
		return e.returnValue;
	case WM_ACTIVATE: 
		p->Window_Activate(e); 
		return e.returnValue;
	case WM_CHAR: p->Window_Char(e); 
		return e.returnValue;
	case WM_CLOSE: p->Window_Close(e); 
		return e.returnValue;
	case WM_CREATE: 
		p->InitializeGui();
		p->Window_Open(e); 
		return e.returnValue;
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORSTATIC:
			if (p->EventHandler(e)) return e.returnValue;
			return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_DESTROY: 
		p->Window_Destroy(e); 
		return e.returnValue;
	case WM_DRAWITEM:
		if ( ((DRAWITEMSTRUCT*)e.lParam)->CtlType == ODT_LISTBOX ||
			 ((DRAWITEMSTRUCT*)e.lParam)->CtlType == ODT_COMBOBOX ||
			  ((DRAWITEMSTRUCT*)e.lParam)->CtlType == ODT_BUTTON)
			   //((DRAWITEMSTRUCT*)e.lParam)->CtlType == ODT_STATIC ||
			   // ((DRAWITEMSTRUCT*)e.lParam)->CtlType == ODT_MENU)
		{
			if (p->EventHandler(e)) return e.returnValue;
		}
		p->Window_DrawItem(e); 
		return e.returnValue;
	case WM_DROPFILES: 
		p->Window_DropFiles(e); 
		return e.returnValue;
	case WM_ERASEBKGND: 
		p->Window_EraseBkgnd(e); 
		return e.returnValue;
	case WM_GETDLGCODE:
		p->Window_GetDlgCode(e);
		return e.returnValue;
	case WM_GETFONT: 
		p->Window_GetFont(e); 
		return e.returnValue;
	case WM_GETMINMAXINFO: 
		p->Window_GetMinMaxInfo(e); 
		return e.returnValue;
	case WM_GETTEXT: 
		p->Window_GetText(e); 
		return e.returnValue;
	case WM_GETTEXTLENGTH: 
		p->Window_GetTextLength(e); 
		return e.returnValue;
	case WM_HELP: 
		p->Window_Help(e); 
		return e.returnValue;
	case WM_KEYDOWN: 
		p->Window_KeyDown(e); 
		return e.returnValue;
	case WM_KEYUP: 
		p->Window_KeyUp(e); 
		return e.returnValue;
	case WM_KILLFOCUS: 
		p->Window_KillFocus(e); 
		return e.returnValue;
	case WM_LBUTTONDBLCLK: 
		p->Window_LButtonDblclk(e); 
		return e.returnValue;
	case WM_LBUTTONDOWN: 
		p->Window_LButtonDown(e); 
		return e.returnValue;
	case WM_LBUTTONUP: 
		p->Window_LButtonUp(e); 
		return e.returnValue;
	case WM_RBUTTONDBLCLK: 
		p->Window_RButtonDblclk(e); 
		return e.returnValue;
	case WM_RBUTTONDOWN: 
		p->Window_RButtonDown(e); 
		return e.returnValue;
	case WM_RBUTTONUP: 
		p->Window_RButtonUp(e); 
		return e.returnValue;
	case WM_MEASUREITEM:
		p->Window_MeasureItem(e); 
		return e.returnValue;
	case WM_MOUSEMOVE: 
		p->Window_MouseMove(e); 
		return e.returnValue;
	case WM_MOUSEWHEEL: 
		p->Window_MouseWheel(e); 
		return e.returnValue;
	case WM_PAINT:
		p->Window_Paint(e); 
		return e.returnValue;
	case WM_SETFOCUS: 
		p->Window_SetFocus(e); 
		return e.returnValue;
	case WM_SETFONT: 
		p->Window_SetFont(e); 
		return e.returnValue;
	case WM_SETTEXT: 
		p->Window_SetText(e); 
		return e.returnValue;
	case WM_SIZE: 
		p->width = LOWORD(lParam);
		p->height = HIWORD(lParam);
		if (p->initialWidth==0 && p->initialHeight==0)
		{
			p->initialWidth = p->width;
			p->initialHeight = p->height;
		}
		p->Window_Size(e); 
		return e.returnValue;
	case WM_SYSCOMMAND: 
		p->Window_SysCommand(e); 
		return e.returnValue;
	case WM_TIMER: 
		p->Window_Timer(e); 
		return e.returnValue;
	case WM_USER: 
		p->Window_User(e); 
		return e.returnValue;
	case WM_VSCROLL:
		if (e.lParam==NULL) 
		{
			p->Window_VScroll(e); 
			return e.returnValue;
		}
		if (p->EventHandler(e)) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_HSCROLL: 
		if (e.lParam==NULL) 
		{
			p->Window_HScroll(e); 
			return e.returnValue;
		}
		if (p->EventHandler(e)) return e.returnValue;
	case WM_COMMAND:
		if (p->EventHandler(e)) return e.returnValue;
		if (LOWORD(e.wParam)==IDCANCEL) 
		{
			p->Window_Cancel(e);
			return e.returnValue;
		}
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_NOTIFY:
		if (p->EventHandler(e)) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_SOCKETNOTIFY: 
		p->Window_SocketNotify(e); 
		return e.returnValue;
	case WM_SOCKETHOSTNAME: 
		p->Window_SocketHostname(e); 
		return e.returnValue;
#ifdef WIN_DAC_ADC_SUPPORT
	case MM_WOM_OPEN: 
		p->Window_WomOpen(e); 
		return e.returnValue;
	case MM_WOM_CLOSE: 
		p->Window_WomClose(e); 
		return e.returnValue;
	case MM_WOM_DONE: 
		p->Window_WomDone(e); 
		return e.returnValue;
	case MM_WIM_OPEN: 
		p->Window_WimOpen(e); 
		return e.returnValue;
	case MM_WIM_CLOSE: 
		p->Window_WimClose(e); 
		return e.returnValue;
	case MM_WIM_DATA: 
		p->Window_WimData(e); 
		return e.returnValue;
#endif
	default:
		if (p->Window_WndProc(e)) return e.returnValue;
	}
	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Window::InitializeGui()
{
}

// The function must return false, when the message is not being processed
bool Window::EventHandler(Win::Event& e)
{
	return false;
}

void Window::Window_WinAddChild(Win::Event& e)
{
	if (_isMainWindow)
	{
		children.push_back((Win::IParent*)e.wParam);
		e.returnValue = TRUE;
	}
	else
	{
		e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
	}
}

void Window::Window_Activate(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_Cancel(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_Char(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_Close(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_Open(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_Destroy(Win::Event& e)
{
	if (_isMainWindow)
	{
		::PostQuitMessage(0);
		e.returnValue = 0;
	}
	else
	{
		e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
	}
}

void Window::Window_DrawItem(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_DropFiles(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_EraseBkgnd(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_GetDlgCode(Win::Event& e)
{
//	The return value is one or more of the following values, indicating which type of input the application processes. 
//DLGC_BUTTON Button. 
//DLGC_DEFPUSHBUTTON Default push button. 
//DLGC_HASSETSEL EM_SETSEL messages. 
//DLGC_RADIOBUTTON Radio button. 
//DLGC_STATIC Static control. 
//DLGC_UNDEFPUSHBUTTON Non-default push button. 
//DLGC_WANTALLKEYS All keyboard input. 
//DLGC_WANTARROWS Direction keys. 
//DLGC_WANTCHARS WM_CHAR messages. 
//DLGC_WANTMESSAGE All keyboard input (the application passes this message in the MSG structure to the control). 
//DLGC_WANTTAB TAB key. 
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_GetFont(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_GetMinMaxInfo(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_GetText(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_GetTextLength(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_Help(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_KeyDown(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_KeyUp(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_KillFocus(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_LButtonDblclk(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_LButtonDown(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_LButtonUp(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_RButtonDblclk(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_RButtonDown(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_RButtonUp(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_MeasureItem(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_MouseMove(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_MouseWheel(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_Paint(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_SetFocus(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_SetFont(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_SetText(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_Size(Win::Event& e)
{
	if (_isMainWindow)
	{
		if (initialWidth == CW_DEFAULT || initialHeight == CW_DEFAULT)
		{
			e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
			return;
		}
		if (children.empty() == false && initialWidth>0 && initialHeight>0 && width>0 && height>0)
		{
			const int len = children.size();
			for(int i = 0; i<len; i++)
			{
				children[i]->DoDock(initialWidth, initialHeight, width, height);
			}
		}
		e.returnValue = TRUE;
	}
	else
	{
		e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
	}
}

void Window::Window_SysCommand(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_Timer(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_User(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_VScroll(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_HScroll(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_SocketNotify(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_SocketHostname(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

#ifdef WIN_DAC_ADC_SUPPORT
void Window::Window_WomOpen(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_WomClose(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_WomDone(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_WimOpen(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_WimClose(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}

void Window::Window_WimData(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(hWnd, e.uMsg, e.wParam, e.lParam);
}
#endif

//void Window::GameLoop()
//{
//}

void Window::GetRegisterClass(WNDCLASSEX& wcex)
{
}

HWND Window::CreateMainWindow(DWORD dwExStyle, DWORD dwStyle, int x, int y, int width, int height, const wchar_t * text, int cmdShow, USHORT iconID, USHORT menuID, HBRUSH bkgnd, HINSTANCE hInstance)
{
	INITCOMMONCONTROLSEX init;
	init.dwSize = sizeof(INITCOMMONCONTROLSEX);
	init.dwICC = ICC_WIN95_CLASSES;
	::InitCommonControlsEx(&init);

//#ifdef WIN_GDI_PLUS_ON
//	Win::GdiPlusOn gpo;
//#endif
#ifdef WIN_GDI_PLUS_ON
	if (_isGdiPlusOn == false)
	{
		Gdiplus::GdiplusStartup(&Win::Window::_gdiPlusToken, &Win::Window::_gdiPlusStartupInput, NULL);
		_isGdiPlusOn = true;
	}
#endif

	Win::Module::hInstance=hInstance;

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc	= (WNDPROC)this->InternalWndProc;
	wcex.cbClsExtra	= 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = this->hInstance;
	wcex.hIcon	= ::LoadIcon(this->hInstance, MAKEINTRESOURCE(iconID));
	wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = bkgnd; //(HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = MAKEINTRESOURCE(menuID);
	wcex.lpszClassName	= this->GetClassName();
	wcex.hIconSm	= ::LoadIcon(this->hInstance, MAKEINTRESOURCE(iconID));

	GetRegisterClass(wcex); // Give the user the oportunity to modify WNDCLASSEX

	if (::RegisterClassEx(&wcex)==0) return NULL;

	Win::Window::UserControlRegisterClass();
	_isMainWindow = true;
	Create(dwExStyle, text, dwStyle, x, y, width, height, NULL, 0);
	_isMainWindow = true;
	::ShowWindow(this->hWnd, cmdShow);
	::UpdateWindow(this->hWnd);

	return this->hWnd;
}

HWND Window::CreateMainWindow(const wchar_t * text, int cmdShow, USHORT iconID, USHORT menuID, HBRUSH bkgnd, HINSTANCE hInstance)
{
	CREATESTRUCT createStruct;
	createStruct.dwExStyle = 0;
	createStruct.style = WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW;
	createStruct.x = CW_USEDEFAULT;
	createStruct.y = CW_USEDEFAULT;
	createStruct.cx = CW_USEDEFAULT;
	createStruct.cy = CW_USEDEFAULT;
	//
	this->GetWindowInformation(createStruct);
	if (createStruct.x > 100000) createStruct.x =  CW_USEDEFAULT;
	if (createStruct.y > 100000) createStruct.y =  CW_USEDEFAULT;
	if (createStruct.cx > 100000) createStruct.cx =  CW_USEDEFAULT;
	if (createStruct.cy > 100000) createStruct.cy =  CW_USEDEFAULT;

	//
	return CreateMainWindow(createStruct.dwExStyle, createStruct.style, 
		createStruct.x, createStruct.y, createStruct.cx, createStruct.cy, 
		text, cmdShow, iconID, menuID, bkgnd, hInstance);
}

HWND Window::Create(DWORD dwExStyle, const wchar_t * text, 
					DWORD dwStyle, int x, int y, int width, int height, HWND hParent, int id)
{
	_isMainWindow = false;
	if (!::IsWindow(this->hWnd)) this->hWnd=NULL;
	if (this->hWnd==NULL)
	{
		this->_initialRect.left = x;
		this->_initialRect.right = x + width;
		this->_initialRect.top = y;
		this->_initialRect.bottom = y + height;
		//
		_isMainWindow = (::IsWindow(hParent) == 0);
		bool isDefaultWidth = (width == CW_USEDEFAULT);
		bool isDefaultHeight = (height == CW_USEDEFAULT);
		//
		initialWidth = width;
		initialHeight = height;
		this->width = width;
		this->height = height;
		this->id = (LONG_PTR)id;
		//
		CREATESTRUCT cs;			
		memset(&cs, 0, sizeof(cs));
		cs.lpCreateParams = (LPVOID) this;
		this->hWnd = ::CreateWindowEx(dwExStyle, this->GetClassName(), text, dwStyle, 
		x, y, width, height, hParent, (HMENU)id, this->hInstance, &cs);

		if (this->hWnd==NULL)
		{
			Sys::DisplayLastError(NULL, this->GetClassName());
			_initialRect.left = 0;
			_initialRect.top = 0;
			_initialRect.right = 0;
			_initialRect.bottom = 0;
			//
			initialWidth = 0;
			initialHeight = 0;
			this->width = 0;
			this->height = 0;
			this->id = (LONG_PTR)0;
			return NULL;
		}
		if (_isMainWindow)
		{
			RECT rect;
			::GetClientRect(hWnd, &rect);
			this->width = rect.right - rect.left;
			this->height = rect.bottom-rect.top;
			// ________________________ Compute the window size using the children
			int childrenWidth = 0;
			int childrenHeight = 0;
			RECT rcChild;

			if (isDefaultWidth || isDefaultHeight)
			{
				const int count = children.size();
				for(int i = 0; i<count; i++)
				{
					children[i]->GetInitialRect(rcChild);
					if (rcChild.right > childrenWidth) childrenWidth = rcChild.right;
					if (rcChild.bottom > childrenHeight) childrenHeight = rcChild.bottom;
				}
			}

			initialWidth = isDefaultWidth ? (childrenWidth+1) : this->width;
			initialHeight = isDefaultHeight ? (childrenHeight+1) : this->height;
			_initialRect.left = 0;
			_initialRect.top = 0;
			_initialRect.right = initialWidth;
			_initialRect.bottom = initialHeight;
		}
		InitialUpdate(hParent);
	}
	return this->hWnd;
}

//Call this function between:  CreateMainWindow and return MessageLoop
bool Window::GetCommandFileName(const wchar_t* in_cmdLine, wstring& out_filename)
{
	if (in_cmdLine == NULL) return false;
	const int len = wcslen(in_cmdLine)+1;
	
	for(int i = 0; i<len; i++)
	{
		if (in_cmdLine[i] != '\"')
		{
			out_filename += in_cmdLine[i];
		}
	}
	return (out_filename.size() > 2);
}

// This functions is used to create items from a dialog
// On the editor, you create a button control, the button control will be replaced by the custom window
HWND Window::GetDialogItem(HWND hDlg, int id)
{
	if (!::IsWindow(this->hWnd)) this->hWnd=NULL;
	if (this->hWnd==NULL)
	{
		RECT rect;
		CREATESTRUCT cs;
		HWND hStatic = ::GetDlgItem(hDlg, id);
		DWORD dwStyle = ::GetWindowLongPtr(hStatic, GWL_STYLE);
		DWORD dwExStyle = ::GetWindowLongPtr(hStatic, GWL_EXSTYLE);
		int length = ::GetWindowTextLength(hStatic);
		wchar_t *psz = new wchar_t[length+1];
		::GetWindowText(hStatic, psz, length+1);
		memset(&cs, 0, sizeof(cs));
		::GetWindowRect(hStatic, &rect);
		::MapWindowPoints(NULL, hDlg, (LPPOINT)&rect, 2);
		::DestroyWindow(hStatic);

		cs.lpCreateParams = (LPVOID) this;

		//this->hWnd=Win::Module::Create(dwExStyle, psz, dwStyle, rect.left, 
		//	rect.top, rect.right-rect.left, rect.bottom-rect.top, hDlg, (HMENU)id, &cs);
		this->hWnd = ::CreateWindowEx(dwExStyle, this->GetClassName(), psz, dwStyle, 
		rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, hDlg, (HMENU)id, this->hInstance, &cs);

		this->id = (LONG_PTR)id;
		this->width = rect.right-rect.left;
		this->height = rect.bottom-rect.top;

		if (this->hWnd==NULL)
		{
			Sys::DisplayLastError(NULL, this->GetClassName());
				//L"Win::Module::CreateWindow unable to create window of class",
				
			return NULL;
		}
		InitialUpdate(hDlg);
		
		if (psz) delete [] psz;
		//this->GetWindowRect(rect);
		//width = rect.right-rect.left;
		//height = rect.bottom-rect.top;
	}
	return this->hWnd;
}

int Window::MessageLoop(WORD aceleratorsID)
{
	MSG msg;		
	::ZeroMemory(&msg, sizeof(MSG));
	HACCEL hAccelTable= LoadAccelerators(hInstance, MAKEINTRESOURCE(aceleratorsID));

	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		//if (!::IsWindow(app.dlgModeless.GetHWND()) || !::IsDialogMessage(app.dlgModeless.GetHWND(), &msg))//Modeless
		//{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		//}
	}
	return (int) msg.wParam;
}

// For this to work you need:
// 1. Register using the bModelessDialog set to true
// 2. The class name of the template must be the same as the class name registered during Register()
// 3. You need to use the GenericDlgProc during Register()
// 4. There is still a problem for this to work.  You don-t know what the DlgProc receives as LPARAM
//      during Creation
//HWND Window::Create(USHORT nTemplateId)
//{
//	if (m_hWnd == NULL)
//	{
//		//m_hWnd = CreateDialog(m_hInstance, (wchar_t*)nTemplateId, NULL, 0);
//		//CREATESTRUCT cs;			
//		//memset(&cs, 0, sizeof(cs));
//		//cs.lpCreateParams = (LPVOID) this;
//		m_hWnd = CreateDialogParam(m_hInstance, (wchar_t*)nTemplateId, NULL, 0, (LPARAM)this);
//	}
//	else
//	{
//		::MessageBox
//			(
//				NULL,
//				L"There is another instance of application already running", 
//				L"Win::Application.Run", MB_ICONERROR
//			);
//	}
//	return m_hWnd;
//}



//_____________________________________________________________________ Control
bool Control::bRegistered= false;

Control::Control(void)
{
	if (!bRegistered)
	{
		RegisterClassEx(LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(NULL_BRUSH));
		bRegistered = true;
	}
	_printerFormat = false;
	_hfont = NULL;
	_backColor = RGB(250, 250, 250);
	_textColor = RGB(0, 0, 200);
	_lineColor = RGB(235, 235, 255);
	//
	//______________ These variables are used to temporarily store the control colors
	_colorModeBackColor = _backColor;
	_colorModeTextColor = _textColor;
	_colorModeLineColor = _lineColor;
	//
	_fontHeight = 12;
	//
	printInfo.width = 0;
	printInfo.height = 0;
	printInfo.pageWidth = 0;
	printInfo.pageHeight = 0;
	printInfo.page = 0;
	printInfo.index = 0;
	printInfo.position.x = 0;
	printInfo.position.y = 0;
	printInfo.isFirst = false;
	printInfo.isLast = false;
	printInfo.isFirstOnPage = false;
	printInfo.isLastOnPage = false;
}

Control::~Control(void)
{
}

void Control::SetColorMode(bool isBlackAndWhite)
{
	if (isBlackAndWhite)
	{
		//_colorModeBackColor = _backColor;
		//_colorModeTextColor = _textColor;
		//_colorModeLineColor = _lineColor;
		//
		_backColor = RGB(255, 255, 255);
		_textColor = RGB(0, 0, 0);
		_lineColor = RGB(180, 180, 180);
	}
	else
	{
		_backColor = _colorModeBackColor;
		_textColor = _colorModeTextColor;
		_lineColor = _colorModeLineColor;
	}
	if (hWnd) ::InvalidateRect(this->hWnd, NULL, FALSE);
}

bool Control::SaveEmfImage(const wchar_t* fileName)
{
	return Win::Exporter::SaveToFile(fileName, *this);
}
	
bool Control::SaveEmfImage(const wchar_t* fileName, double aspectRatio)
{
	return Win::Exporter::SaveToFile(fileName, aspectRatio, *this);
}

bool Control::CopyToClipboard()
{
	return Win::Exporter::CopyToClipboard(*this);
}

bool Control::CopyToBitmap(int width, int height, bool clientEdge, Win::DDBitmap& result)
{
	return Win::Exporter::CopyToBitmap(*this, width, height, clientEdge, result);
	//int initial_width = 0;
	//int initial_height = 0;
	//HWND hWnd = this->GetControlInfo(initial_width, initial_height);
	//if (hWnd==NULL)
	//{
	//	hWnd = ::GetDesktopWindow();
	//}
	//HDC hdc = result.CreateCompatible(hWnd, width, height);
	//this->SetControlSize(width, height);
	//RECT rcPaint = {0, 0, width, height};
	//Win::Gdi gdi(result, rcPaint, false);
	////if (_hfont) gdi.SelectFont__(_hfont);
	//this->OnPaintControl(gdi);
	//if (clientEdge)
	//{
	//	RECT rcBorder = {0, 0, width, height};
	//	gdi.DrawEdge(&rcBorder, EDGE_SUNKEN, BF_RECT);
	//}
	//result.DeleteMemDC();
	//this->SetControlSize(initial_width, initial_height);
	//return true;
}

void Control::GetLogfont(LOGFONT& logfont)
{
	Win::Gdi::Font::InitializeLogfont(logfont); 

	if (_hfont == NULL)
	{
		_snwprintf_s(logfont.lfFaceName, 32, _TRUNCATE, L"%s", L"Arial");
		logfont.lfHeight = -12;
		return;
	}
	
	if (_hfont != NULL)
	{
		if (::GetObject(_hfont, sizeof(LOGFONT), &logfont)!=0) return;
	}	
}

void Control::SetWindowText(const wchar_t* text)
{
	if (text)
	{
		_text = text;
	}
	else
	{
		_text.clear();
	}
	if (hWnd == NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

int Control::GetWindowText(wchar_t* text, int size)
{
	int i = 0;
	const int len = _text.length()+1;
	if (len == 0) return 0;
	const int len_copy = MINIMUM(size, len);
	for(i = 0; i<len_copy; i++) text[i] = _text[i];
	text[i] = '\0';
	//_snwprintf_s(text, len_copy, _TRUNCATE, L"%s", _text.c_str());
	return len_copy;
}

int Control::GetTextLength()
{
	return _text.length();
}

wstring Control::GetText()
{
	return _text;
}

void Control::SetText(const wstring text)
{
	if (_text==text) return;
	_text = text;
	if (hWnd == NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

void Control::SetFont(Win::Gdi::Font& font)
{
	_hfont = font.GetHFONT();
	LOGFONT logfont;
	this->GetLogfont(logfont);
	_fontHeight = abs(logfont.lfHeight);
	this->OnSizePrivate();
	if (hWnd == NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

HWND Control::Create(DWORD dwExStyle, const wchar_t * text, 
					DWORD dwStyle, int x, int y, int width, int height, HWND hParent, int id)
{
	if (!::IsWindow(this->hWnd)) this->hWnd=NULL;
	if (this->hWnd==NULL)
	{
		this->_initialRect.left = x;
		this->_initialRect.right = x + width;
		this->_initialRect.top = y;
		this->_initialRect.bottom = y + height;
		//
		if (text!=NULL)
		{
			_text = text;
		}
		else
		{
			_text.clear();
		}
		//
		initialWidth = width;
		initialHeight = height;
		this->width = width;
		this->height = height;
		this->id = (LONG_PTR)id;
		//
		CREATESTRUCT cs;			
		memset(&cs, 0, sizeof(cs));
		cs.lpCreateParams = (LPVOID) this;
		this->hWnd = ::CreateWindowEx(dwExStyle, this->GetClassName(), NULL, dwStyle, 
		x, y, width, height, hParent, (HMENU)id, this->hInstance, &cs);

		if (this->hWnd==NULL)
		{
			Sys::DisplayLastError(NULL, this->GetClassName());
			_initialRect.left = 0;
			_initialRect.top = 0;
			_initialRect.right = 0;
			_initialRect.bottom = 0;
			//
			_text.clear();
			//
			initialWidth = 0;
			initialHeight = 0;
			this->width = 0;
			this->height = 0;
			this->id = (LONG_PTR)0;
			return NULL;
		}
		InitialUpdate(hParent);
	}
	return this->hWnd;
}

COLORREF Control::GetBackColor()
{
	return _backColor;
}

void Control::SetBackColor(COLORREF color)
{
	_colorModeBackColor = color;
	if (_backColor == color) return;
	_backColor = color;
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

COLORREF Control::GetTextColor()
{
	return _textColor;
}

void Control::SetTextColor(COLORREF color)
{
	_colorModeTextColor = color;
	if (_textColor == color) return;
	_textColor = color;
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

COLORREF Control::GetLineColor()
{
	return _lineColor;
}

void Control::SetLineColor(COLORREF color)
{
	_colorModeLineColor = color;
	if (_lineColor == color) return;
	_lineColor = color;
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

bool Control::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_COMMAND) return false;
	const int id = LOWORD(e.wParam);
	const int notificationd = HIWORD(e.wParam);
	if (id != this->id) return false;
	if (notificationd!=notification) return false;
	return true;
}

void Control::Window_LButtonDown(Win::Event& e)
{
	if (Enabled==false) return;
	HWND hWndParent = ::GetParent(hWnd);
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_CLICK), e.lParam);
	::SetFocus(hWnd);
}

void Control::Window_RButtonDown(Win::Event& e)
{
	if (Enabled==false) return;
	HWND hWndParent = ::GetParent(hWnd);
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_RCLICK), e.lParam);
	::SetFocus(hWnd);
}

void Control::Window_LButtonDblclk(Win::Event& e)
{
	if (Enabled==false) return;
	HWND hWndParent = ::GetParent(hWnd);
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_DBLCLICK), e.lParam);
	::SetFocus(hWnd);
}

void Control::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, false);
	if (_hfont) gdi.SelectFont__(_hfont);
	OnPaintControl(gdi);
}

void Control::Window_Size(Win::Event& e)
{
	OnSizePrivate();
}

void Control::SetPrinterFormat(bool printerFormat)
{
	this->_printerFormat = printerFormat;
}

//________________________________________________ IExportable
void Control::SetControlSize(int width, int height)
{
	this->width = width;
	this->height = height;
	OnSizePrivate();
}

HWND Control::GetControlInfo(int& width, int&height)
{
	width = this->width;
	height = this->height;
	return this->hWnd;
}

void Control::OnPaintControl(Win::Gdi& gdi)
{
}

//_______________________________________________ IPrint
void Control::Print(Win::Gdi& gdi, Win::PrintInfo pi)
{
	printInfo = pi;
	int widthScreen; 
	int heightScreen; 

	//RECT rect = {0, 0, width, height}; 
	//gdi.Rectangle(&rect);

	gdi.SetTextColor(RGB(0, 0, 0));
	this->GetControlInfo(widthScreen, heightScreen); 
	this->SetPrinterFormat(true); 
	this->SetControlSize(pi.width, pi.height); 
	this->OnPaintControl(gdi); 
	this->SetPrinterFormat(false); 
	this->SetControlSize(widthScreen, heightScreen); 
	//this->RefreshAll(); 
}

void Control::OnSizePrivate()
{
}

#ifdef WIN_GDI_PLUS_ON
//_____________________________________________________________________ Image
bool Image::bRegistered= false;

Image::Image(void)
{
	if (!bRegistered)
	{
		RegisterClassEx(LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(WHITE_BRUSH));
		bRegistered = true;
	}
}

Image::~Image(void)
{
}

bool Image::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_COMMAND) return false;
	const int id = LOWORD(e.wParam);
	const int notificationd = HIWORD(e.wParam);
	if (id != this->id) return false;
	if (notificationd!=notification) return false;
	return true;
}

void Image::Window_LButtonDown(Win::Event& e)
{
	if (Enabled==false) return;
	HWND hWndParent = ::GetParent(hWnd);
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_CLICK), e.lParam);
}

void Image::Window_RButtonDown(Win::Event& e)
{
	if (Enabled==false) return;
	HWND hWndParent = ::GetParent(hWnd);
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_RCLICK), e.lParam);
}

const wstring& Image::GetFileName()
{
	return filename;
}

void Image::SetFileName(const wstring& filename)
{
	this->filename = filename;
	if (hWnd == NULL) return;
	::InvalidateRect(hWnd, NULL, TRUE);
}

void Image::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, true);
	if (filename.length()<=4) return;
	Gdiplus::Image image(filename.c_str());
	gdi.Plus.DrawImage(&image, 0, 0, image.GetWidth(), image.GetHeight());
}

#endif
//_____________________________________________________________________Button
Button::Button(void)
{
	used_checked = false;
	_checked = false;
	//
	_textColor = RGB(0, 0, 0);
	_backColor = RGB(245, 245, 245);
}

Button::~Button(void)
{
}

//_____________________________________________________________________ ISelectBool
bool& Button::SqlGetBool()
{
	return _checked;
}

void Button::SqlUpdate(bool toGui)
{
	if (toGui == true)
	{
		if (::IsWindow(hWnd))
		{
			::SendMessage(this->hWnd, BM_SETCHECK, _checked ? BST_CHECKED : BST_UNCHECKED, 0);
		}
	}
	else
	{
		_checked = (::SendMessage(this->hWnd, BM_GETCHECK, 0, 0)==BST_CHECKED);
	}
}

COLORREF Button::GetBackColor()
{
	return _backColor;
}

void Button::SetBackColor(COLORREF color)
{
	_backColor = color;
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

COLORREF Button::GetTextColor()
{
	return _textColor;
}

void Button::SetTextColor(COLORREF color)
{
	_textColor = color;
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

void Button::InitialUpdate(HWND hParent)
{
	if (used_checked)
	{
		SetChecked(_checked);
	}
	::SendMessage(hParent, WM_WINADDCHILD, (WPARAM)this, (LPARAM)0);
}

bool Button::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg == WM_COMMAND)// && notification != WM_DRAWITEM)
	{
		if (LOWORD(e.wParam) != this->id) return false;
		if (HIWORD(e.wParam) != notification) return false;
		return true;
	}
	else if (e.uMsg == WM_DRAWITEM && notification == WM_DRAWITEM)
	{
		if (e.wParam != this->id) return false;
		return true;
	}
	return false;
}

bool Button::IsChecked()
{
	if (IsWindow(hWnd)) return (::SendMessage(this->hWnd, BM_GETCHECK, 0, 0)==BST_CHECKED);
	if (used_checked) return _checked; 
	return false;
}

void Button::UpdateValue()
{
	this->used_checked = true;
	_checked = (::SendMessage(this->hWnd, BM_GETCHECK, 0, 0)==BST_CHECKED);
}

void Button::SetChecked(bool checked)
{
	if (IsWindow(hWnd))
	{
		::SendMessage(this->hWnd, BM_SETCHECK, checked ? BST_CHECKED : BST_UNCHECKED, 0);
		return;
	}
	used_checked = true;
	_checked = checked;
}

//LoadImage(hinstance, // small class icon 
//        MAKEINTRESOURCE(5),
//        IMAGE_ICON, 
//        GetSystemMetrics(SM_CXSMICON), 
//        GetSystemMetrics(SM_CYSMICON), 
//        LR_DEFAULTCOLOR); 

// Requires the style BS_ICON
//LoadIcon only works with icons of size SM_CXICON, SM_CYICON
//to load icons of other sizes use LoadImage
LRESULT Button::SetImage(HICON hicon)
{
	return ::SendMessage(this->hWnd, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hicon);
}

// Requires the style BS_ICON
//LoadIcon only works with icons of size SM_CXICON, SM_CYICON
//to load icons of other sizes use LoadImage
LRESULT Button::SetImage(Sys::Icon& icon)
{
	return ::SendMessage(this->hWnd, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)icon.GetHIcon());
}

// Requires the style BS_BITMAP
LRESULT Button::SetImage(Sys::Bitmap& bitmap)
{
	return ::SendMessage(this->hWnd, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)bitmap.GetHBitmap());
}

// Requires the style BS_BITMAP
LRESULT Button::SetImage(Win::DDBitmap& bitmap)
{
	return ::SendMessage(this->hWnd, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)bitmap.GetHBITMAP());
}

void Button::DrawButton(Win::Gdi& gdi, RECT& rect, bool isUp, bool defaultButton, Gdi::Color3D& color3D)
{
	Win::Gdi::Pen penExteriorBorder(PS_SOLID, 1, RGB(225, 220, 201));
	HBRUSH brushNull = (HBRUSH)::GetStockObject(NULL_BRUSH);
	Win::Gdi::Pen penDefaultButton;
	if (defaultButton) penDefaultButton.Create(PS_SOLID, 1, RGB(173, 199, 240));

	RECT rcButton = rect;
	//________________________________________________ Exterior Border
	gdi.SelectBrush__(brushNull);
	gdi.SelectPen_(penExteriorBorder);
	gdi.Rectangle(rcButton);
	::InflateRect(&rcButton, -1, -1);
	gdi.Rectangle(rcButton);

	::InflateRect(&rcButton, -1, -1);
	//________________________________________  Filling
	gdi.FillRect(rcButton, color3D.GetFilling()); 
	//______________________________________High Light
	if (defaultButton)
	{
		gdi.SelectPen_(penDefaultButton);
	}
	else
	{
		gdi.SelectPen_(isUp ? color3D.GetHighLight() : color3D.GetDarkShadow());
	}
	gdi.MoveToEx(rcButton.left, rcButton.bottom-1);
	gdi.LineTo(rcButton.left, rcButton.top);
	gdi.LineTo(rcButton.right-1, rcButton.top);
	//______________________________________ Light
	if (defaultButton)
	{
		gdi.SelectPen_(penDefaultButton);
	}
	else
	{
		gdi.SelectPen_(isUp ? color3D.GetLight() : color3D.GetShadow());
	}
	gdi.MoveToEx(rcButton.left+1, rcButton.bottom-2);
	gdi.LineTo(rcButton.left+1, rcButton.top+1);
	gdi.LineTo(rcButton.right-2, rcButton.top+1);
	//______________________________________ Shadow
	if (defaultButton)
	{
		gdi.SelectPen_(penDefaultButton);
	}
	else
	{
		gdi.SelectPen_(isUp ? color3D.GetShadow() : color3D.GetLight());
	}
	gdi.MoveToEx(rcButton.right-2, rcButton.top+1);
	gdi.LineTo(rcButton.right-2, rcButton.bottom-2);
	gdi.LineTo(rcButton.left, rcButton.bottom-2);
	//______________________________________ DarkShadow
	if (defaultButton)
	{
		gdi.SelectPen_(penDefaultButton);
	}
	else
	{
		gdi.SelectPen_(isUp ? color3D.GetDarkShadow() : color3D.GetHighLight());
	}
	gdi.MoveToEx(rcButton.right-1, rcButton.top);
	gdi.LineTo(rcButton.right-1, rcButton.bottom-1);
	gdi.LineTo(rcButton.left-1, rcButton.bottom-1);
	//_____________________________________ Button Border
	Win::Gdi::Pen penButtonBorder(PS_SOLID, 1, RGB(0, 60, 116));
	gdi.SelectBrush__(brushNull);
	gdi.SelectPen_(penButtonBorder);
	::InflateRect(&rcButton, 1, 1);
	gdi.RoundRect(rcButton, 4, 4);
}

//void Button::DrawDefaultButton(Win::Gdi& gdi, RECT& rect, bool isUp, Gdi::Color3D& color3D)
//{
//	const bool bBlack = Gdi::Color3D::IsCloseToBlack(color3D.GetColor());
//	gdi.SelectBrush__((HBRUSH)GetStockObject(NULL_BRUSH));
//	if (bBlack)
//	{
//		gdi.SelectPen__((HPEN)GetStockObject(WHITE_PEN));
//		gdi.Rectangle(rect.left, rect.top, rect.right, rect.bottom);
//	}
//	else
//	{
//		gdi.SelectPen__((HPEN)GetStockObject(BLACK_PEN));
//		gdi.Rectangle(rect.left, rect.top, rect.right, rect.bottom);
//	}
//	RECT rectButton;
//
//	rectButton.bottom = rect.bottom - 1;
//	rectButton.left = rect.left + 1;
//	rectButton.right = rect.right - 1;
//	rectButton.top = rect.top + 1;
//	Win::Button::DrawButton(gdi, rectButton, isUp, color3D);
//}

void Button::DrawButtonText(Win::Gdi& gdi, DWORD buttonStyle, RECT rect, const wchar_t* text, COLORREF colorText)
{
	if (text==NULL) return;
	//________________________________________  Text
	UINT format = 0L;

	if (buttonStyle== 0) 
	{
		format = DT_VCENTER | DT_CENTER | DT_SINGLELINE;
	}
	else
	{
		 if ((buttonStyle & BS_MULTILINE) == 0L) 
			 format |= DT_SINGLELINE;
		 if ((buttonStyle & BS_BOTTOM) != 0L && (buttonStyle & BS_TOP) == 0L) 
			 format |= DT_BOTTOM;
		 if ( (buttonStyle & BS_TOP) != 0L && (buttonStyle & BS_BOTTOM) == 0L)
			 format |= DT_TOP;
		 if ((buttonStyle & BS_BOTTOM) != 0L && (buttonStyle & BS_TOP) != 0L) 
			 format |= DT_VCENTER;
		 if ((buttonStyle & BS_LEFT) != 0L && (buttonStyle & BS_RIGHT) == 0L) 
			 format |= DT_LEFT;
		 if ((buttonStyle & BS_RIGHT) != 0L && (buttonStyle & BS_LEFT) != 0L) 
			 format |= DT_CENTER;
		 if ((buttonStyle & BS_RIGHT) != 0L && (buttonStyle & BS_LEFT) == 0L) 
			 format |= DT_RIGHT;
	}
	gdi.SetTextColor(colorText);	
	::InflateRect(&rect, -6, -6);
	gdi.DrawTextEx((wchar_t*)text,  rect, format, NULL);
}

void Button::DrawButton(DRAWITEMSTRUCT* pDrawItem)
{
	if ( (pDrawItem->itemState & ODS_DISABLED) == 0) //this->Enabled)
	{
		DrawButton(pDrawItem, _textColor, _backColor);
	}
	else
	{
		DrawButton(pDrawItem, WIN_TEXT_DISABLED, WIN_BACK_DISABLED);
	}
}

void Button::DrawButton(DRAWITEMSTRUCT* pDrawItem, COLORREF colorText, COLORREF backColor)
{
	if (pDrawItem->CtlType != ODT_BUTTON) return;
	PAINTSTRUCT ps;
	RECT rect = pDrawItem->rcItem;
	bool isUp = ((pDrawItem->itemState & ODS_SELECTED) == 0);
	bool hasFocus = !((pDrawItem->itemState & ODS_FOCUS) == 0);
	ps.hdc = pDrawItem->hDC;
	Win::Gdi gdi(ps, false);
	::InflateRect(&rect, 4, 4);
	Win::Gdi::Color3D color3D(backColor);

	//if (pDrawItem->itemAction == ODA_DRAWENTIRE) //The entire control needs to be drawn. 
	//{
	//}
	//else if (pDrawItem->itemAction == ODA_FOCUS) //The control has lost or gained the keyboard focus. You should check the itemState member to determine whether the control has the focus.  
	//{
	//}
	//else if (pDrawItem->itemAction == ODA_SELECT) //The selection status has changed. You should check the itemState member to determine the new selection state.
	//{
	//}

	DWORD buttonStyle = ::GetWindowLongPtr(pDrawItem->hwndItem, GWL_STYLE);
	//DWORD dwExStyle = ::GetWindowLongPtr(pDrawItem->hwndItem, GWL_EXSTYLE);

	bool defaultButton = ( (buttonStyle & BS_FLAT) != 0 && (buttonStyle & BS_OWNERDRAW) != 0); 
	//defaultButton = defaultButton || ((dwStyle & BS_DEFSPLITBUTTON) != 0);
	//defaultButton = defaultButton || ((dwStyle & BS_DEFCOMMANDLINK) != 0);

	if (defaultButton == true)
	{
		if (hasFocus == true)
		{
			if (isUp == true)
			{
				Win::Button::DrawButton(gdi, pDrawItem->rcItem, isUp, true, color3D);
			}
			else
			{
				Win::Button::DrawButton(gdi, pDrawItem->rcItem, isUp, false, color3D);
			}
		}
		else
		{
			Win::Button::DrawButton(gdi, pDrawItem->rcItem, isUp, false, color3D);
		}
	}
	else
	{
		Win::Button::DrawButton(gdi, pDrawItem->rcItem, isUp, false, color3D);
	}

	//________________________________________  Text
	gdi.SetBkColor(color3D.GetColor());

	if (::GetWindowTextLength(pDrawItem->hwndItem)<=0) return;
	wchar_t sz[255];
	::GetWindowText(pDrawItem->hwndItem, sz, 255);
	sz[255-1] = '\0';
	Win::Button::DrawButtonText(gdi, buttonStyle, pDrawItem->rcItem, sz, colorText);
	//________________________________________ Focus
	rect = pDrawItem->rcItem;
	::InflateRect(&rect, -6, -6);
	if (hasFocus) gdi.DrawFocusRect(&rect);
}



//_____________________________________________________________________Dialog
Dialog::Dialog(void)
{
	this->bModal = true;
	this->iconID = -1;
	this->initialWidth = 0;
	this->initialHeight = 0;
	this->_isDialogApplication = false;
}

Dialog::~Dialog(void)
{
#ifdef WIN_GDI_PLUS_ON
	if (_isDialogApplication && _isGdiPlusOn)
	{
		Gdiplus::GdiplusShutdown(_gdiPlusToken);
	}
#endif
}

void Dialog::GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
{
	dlgTemplate.dwExtendedStyle = 0;
	dlgTemplate.style = DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | DS_CENTER;
	dlgTemplate.x = 0;
	dlgTemplate.y = 0;
	dlgTemplate.cx = 100;
	dlgTemplate.cy = 80;
	dlgTemplate.cdit = 0;
}

void Dialog::SetDefaultButton(Win::Button& button)
{
	::SendMessage(hWnd, DM_SETDEFID, (WPARAM)button.GetID(), (LPARAM)0);
}

LONG Dialog::SetReturnValue(LONG value)
{
	return ::SetWindowLong(hWnd, DWL_MSGRESULT, value);
}

int Dialog::BeginDialog(USHORT iconID, HINSTANCE hInstance)
{
	_isDialogApplication = true;

	INITCOMMONCONTROLSEX init;
	init.dwSize = sizeof(INITCOMMONCONTROLSEX);
	init.dwICC = ICC_WIN95_CLASSES;
	::InitCommonControlsEx(&init);

//#ifdef WIN_GDI_PLUS_ON
//	Win::GdiPlusOn gpo;
//#endif
#ifdef WIN_GDI_PLUS_ON
	if (_isGdiPlusOn == false)
	{
		Gdiplus::GdiplusStartup(&Win::Window::_gdiPlusToken, &Win::Window::_gdiPlusStartupInput, NULL);
		_isGdiPlusOn = true;
	}
#endif

	Win::Module::hInstance=hInstance;
	this->iconID = iconID;
	Win::Window::UserControlRegisterClass();
	//
	return BeginDialog(NULL);
}

int Dialog::BeginDialog(HWND hWndParent) //Modal Dialog
{
	this->bModal = true;

	HGLOBAL hGlobal = ::GlobalAlloc(GHND | GMEM_MOVEABLE, sizeof(DLGWINTEMPLATE));
	DLGWINTEMPLATE *pTemplate = (DLGWINTEMPLATE *)::GlobalLock(hGlobal);

	pTemplate->dlgTemplate.dwExtendedStyle = 0;
	pTemplate->dlgTemplate.style = DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | DS_CENTER;
	pTemplate->dlgTemplate.x = 0;
	pTemplate->dlgTemplate.y = 0;
	pTemplate->dlgTemplate.cx = 100;
	pTemplate->dlgTemplate.cy = 80;
	pTemplate->dlgTemplate.cdit = 0;
	pTemplate->menu = 0x0000;
	pTemplate->dlgclass = 0x0000;
	pTemplate->title = 0x0000;
	this->GetDialogTemplate(pTemplate->dlgTemplate);
	this->initialWidth = Sys::Convert::DlgUnitToPixelX(pTemplate->dlgTemplate.cx);
	this->initialHeight = Sys::Convert::DlgUnitToPixelY(pTemplate->dlgTemplate.cy);

	::GlobalUnlock(hGlobal);
	int result = ::DialogBoxIndirectParam(this->hInstance, &pTemplate->dlgTemplate, hWndParent,  (DLGPROC)ModalDlgProc, (LPARAM)this);
	if (hGlobal) ::GlobalFree(hGlobal);
	return result;

	//DLGTEMPLATE dlgTemplate;
	//dlgTemplate.dwExtendedStyle = 0;
	//dlgTemplate.style = DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | DS_CENTER;
	//dlgTemplate.x = 0;
	//dlgTemplate.y = 0;
	//dlgTemplate.cx = 100;
	//dlgTemplate.cy = 80;
	//dlgTemplate.cdit = 0;
	//this->GetDialogTemplate(dlgTemplate);
	//this->initialWidth = Sys::Convert::DlgUnitToPixelX(dlgTemplate.cx);
	//this->initialHeight = Sys::Convert::DlgUnitToPixelY(dlgTemplate.cy);

	//HGLOBAL hGlobal = ::GlobalAlloc
	//	(
	//		GHND | GMEM_SHARE, 
	//		sizeof(DLGTEMPLATE)+3*sizeof(WORD) // DLGTEMPLATE + MENU + CLASS + TITLE
	//	);
	//DLGTEMPLATE *pTemplate = (DLGTEMPLATE *)::GlobalLock(hGlobal);
	//char* p = (char*)pTemplate;
	//p+=sizeof(DLGTEMPLATE);
	//::memcpy((LPVOID)pTemplate, (const void*)&dlgTemplate, sizeof(DLGTEMPLATE));
	////::memset(pTemplate+sizeof(DLGTEMPLATE), 0, 3*sizeof(WORD));
	//::memset(p, 0, 3*sizeof(WORD));
	//::GlobalUnlock(hGlobal);
	//int result = ::DialogBoxIndirectParam(this->hInstance, pTemplate, hWndParent,  (DLGPROC)ModalDlgProc, (LPARAM)this);
	//if (hGlobal) ::GlobalFree(hGlobal);
	//return result;
}

int Dialog::DialogBox_(HWND hWndParent) //Modal Dialog
{
	this->bModal = true;
	return ::DialogBoxParam(this->hInstance, MAKEINTRESOURCE(GetIDD()), hWndParent, 
		(DLGPROC)ModalDlgProc, (LPARAM)this);
}

// Register a Window Class to get well formatted icons, creates a windows and begins a dialog
//int Dialog::DialogBox_(USHORT iconID, HINSTANCE hInstance) //Modal Dialog Application
//{
//	INITCOMMONCONTROLSEX init;
//	init.dwSize = sizeof(INITCOMMONCONTROLSEX);
//	init.dwICC = ICC_WIN95_CLASSES;
//	::InitCommonControlsEx(&init);
//
//#ifdef WIN_GDI_PLUS_ON
//	Win::GdiPlusOn gpo;
//#endif
//	Win::Module::hInstance=hInstance;
//	this->iconID = iconID;
//	Win::Window::UserControlRegisterClass();
//	return this->DialogBox_(NULL);
//}

//int Dialog::DialogBox__(HWND hWndParent, LPDLGTEMPLATE pTemplate) //Modal Dialog
//{
//	this->bModal = true;
//	return ::DialogBoxIndirectParam(this->hInstance, pTemplate, hWndParent, 
//		(DLGPROC)ModalDlgProc, (LPARAM)this);
//}

INT_PTR Dialog::CreateDialog_(HWND hWndParent) //Modeless
{
	this->bModal = false;
	if (this->hWnd==NULL)
	{	
		::CreateDialogParam(this->hInstance, MAKEINTRESOURCE(GetIDD()), hWndParent, (DLGPROC)ModelessDlgProc, (LPARAM)this);
	}
	else
	{
		::MessageBox
		(
			hWndParent, 
			L"There is an instance on ModelessDlg.  You need to destroy the previous instance before creating a new one", 
			L"Win::Dialog::CreateDialog_", MB_ICONERROR
		);
		return FALSE;
	}

	if (this->hWnd==NULL)
	{
		::MessageBox
		(
			hWndParent, 
			L"Unable to create modeless dialog", 
			L"Win::Dialog::CreateDialog_", MB_ICONERROR
		);
		return FALSE;
	}

	::ShowWindow(this->hWnd, SW_SHOW);
	return TRUE;
}

INT_PTR Dialog::CreateDialog__(HWND hWndParent, LPDLGTEMPLATE pTemplate) // Modeless
{
	this->bModal = false;
	if (this->hWnd==NULL)
	{	
		::CreateDialogIndirectParam(this->hInstance, pTemplate, hWndParent, (DLGPROC)ModelessDlgProc, (LPARAM)this);
	}
	else
	{
		::MessageBox
		(
			hWndParent, 
			L"There is an instance on ModelessDlg.  You need to destroy the previous instance before creating a new one", 
			L"Win::Dialog::CreateDialog__", MB_ICONERROR
		);
		return FALSE;
	}

	if (this->hWnd==NULL)
	{
		::MessageBox
		(
			hWndParent, 
			L"Unable to create modeless dialog", 
			L"Win::Dialog::CreateDialog__", MB_ICONERROR
		);
		return FALSE;
	}

	::ShowWindow(this->hWnd, SW_SHOW);
	return TRUE;
}

void Dialog::SetInstance(HINSTANCE hInstance)
{
	Win::Dialog::hInstance = hInstance;
	//hInstance = hInst;
}

int Dialog::GetIDD(void)
{
	return 103;
}

// The function must return false, when the message is not being processed
bool Dialog::EventHandler(Win::Event& e)
{
	if (e.uMsg!=WM_COMMAND) return false;
	if (LOWORD(e.wParam)==IDOK) 
	{
		this->EndDialog(TRUE);
		return true;
	}
	if (LOWORD(e.wParam)==IDCANCEL)
	{
		this->EndDialog(FALSE);
		return true;
	}
	return false;
}

void Dialog::EndDialog(int result) 
{
	if (this->bModal)
	{
		if (result != FALSE)
		{
			const int count = children.size();
			for(int i=0; i<count; i++)
			{
				children[i]->UpdateValue();
			}
			children.clear();
		}
		::EndDialog(this->hWnd, (INT_PTR)result);
	}
	else	
	{
		::DestroyWindow(this->hWnd);
		this->hWnd = NULL;
	}
}

HWND Dialog::GetNextTabItem(HWND hWndCurrentControl)
{
	return ::GetNextDlgTabItem(this->hWnd, hWndCurrentControl, FALSE);
}

HWND Dialog::GetPrevTabItem(HWND hWndCurrentControl)
{
	return ::GetNextDlgTabItem(this->hWnd, hWndCurrentControl, TRUE);
}

HWND Dialog::GetNextGroupItem(HWND hWndCurrentControl)
{
	return ::GetNextDlgGroupItem(this->hWnd, hWndCurrentControl, FALSE);
}

HWND Dialog::GetPrevGroupItem(HWND hWndCurrentControl)
{
	return ::GetNextDlgGroupItem(this->hWnd, hWndCurrentControl, TRUE);
}

// Convert pRect to pixels coordinates
BOOL Dialog::MapDialogRect(RECT* pRect)
{
	return ::MapDialogRect(this->hWnd, pRect);
}

LRESULT CALLBACK Dialog::ModalDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Dialog* p = NULL;
	if (uMsg == WM_INITDIALOG)
	{
		if (IsBadReadPtr((void *) lParam, sizeof(Dialog))==false)
		{
			p = (Dialog*)(LONG_PTR)lParam;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)(LONG_PTR)p);
			p->hWnd = hWnd;
		}
		else
		{
			::MessageBox
				(
					hWnd, L"Invalid ModalDltG pointer during WM_INITDIALOG", 
					L"Win::Dialog::ModalDlgProc", MB_ICONERROR
				);
		}
	}
	else
	{
		p = (Dialog*)(LONG_PTR)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}
	if (p==NULL) return FALSE;

	Win::Event e;
	e.hWnd = hWnd;
	e.uMsg = uMsg;
	e.wParam = wParam;
	e.lParam = lParam;
	e.returnValue = TRUE;  // Return true when the message is being processed, otherwise return FALSE
	switch(uMsg)
	{
	case WM_WINADDCHILD: 
		p->Window_WinAddChild(e); 
		return e.returnValue;
	case WM_ACTIVATE: 
		p->Window_Activate(e); 
		return e.returnValue;
	case WM_CHAR: 
		p->Window_Char(e); 
		return e.returnValue;
	case WM_CLOSE: 
		p->Window_Close(e); 
		return e.returnValue;
	case WM_INITDIALOG:
		p->SetClassIcon(::LoadIcon(hInstance, MAKEINTRESOURCE(p->iconID)));
		{
			RECT rect;
			::GetClientRect(hWnd, &rect);
			//::SendMessage(hWnd, WM_SIZE, (WPARAM)SIZE_MAXIMIZED, MAKELPARAM(rect.right, rect.bottom));
			p->width = rect.right;
			p->height = rect.bottom;
			p->InitializeGui();
			::SendMessage(hWnd, WM_SIZE, (WPARAM)SIZE_MAXIMIZED, MAKELPARAM(rect.right, rect.bottom));
		}	
		p->Window_Open(e); 
		return e.returnValue;
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORSTATIC:
		if (p->EventHandler(e)) return e.returnValue;
		return FALSE;
	case WM_DESTROY: 
		p->Window_Destroy(e); 
		return e.returnValue;
	case WM_DRAWITEM:
		if ( ((DRAWITEMSTRUCT*)e.lParam)->CtlType == ODT_LISTBOX ||
			 ((DRAWITEMSTRUCT*)e.lParam)->CtlType == ODT_COMBOBOX ||
			  ((DRAWITEMSTRUCT*)e.lParam)->CtlType == ODT_BUTTON)
			   //((DRAWITEMSTRUCT*)e.lParam)->CtlType == ODT_STATIC ||
			   // ((DRAWITEMSTRUCT*)e.lParam)->CtlType == ODT_MENU)
		{
			if (p->EventHandler(e)) return e.returnValue;
		}
		p->Window_DrawItem(e);
		return e.returnValue;
	case WM_DROPFILES: 
		p->Window_DropFiles(e); 
		return e.returnValue;
	case WM_ERASEBKGND: 
		p->Window_EraseBkgnd(e); 
		return e.returnValue;
	case WM_GETFONT: 
		p->Window_GetFont(e); 
		return e.returnValue;
	case WM_GETMINMAXINFO: 
		p->Window_GetMinMaxInfo(e); 
		return e.returnValue;
	case WM_GETTEXT: 
		p->Window_GetText(e); 
		return e.returnValue;
	case WM_GETTEXTLENGTH: 
		p->Window_GetTextLength(e); 
		return e.returnValue;
	case WM_HELP:
		p->Window_Help(e); 
		return e.returnValue;
	case WM_KEYDOWN: 
		p->Window_KeyDown(e); 
		return e.returnValue;
	case WM_KEYUP: 
		p->Window_KeyUp(e); 
		return e.returnValue;
	case WM_KILLFOCUS: 
		p->Window_KillFocus(e); 
		return e.returnValue;
	case WM_LBUTTONDBLCLK: 
		p->Window_LButtonDblclk(e); 
		return e.returnValue;
	case WM_LBUTTONDOWN: 
		p->Window_LButtonDown(e); 
		return e.returnValue;
	case WM_LBUTTONUP: 
		p->Window_LButtonUp(e); 
		return e.returnValue;
	case WM_RBUTTONDBLCLK: 
		p->Window_RButtonDblclk(e); 
		return e.returnValue;
	case WM_RBUTTONDOWN: 
		p->Window_RButtonDown(e); 
		return e.returnValue;
	case WM_RBUTTONUP: 
		p->Window_RButtonUp(e); 
		return e.returnValue;
	case WM_MEASUREITEM: 
		p->Window_MeasureItem(e); 
		return e.returnValue;
	case WM_MOUSEMOVE: 
		p->Window_MouseMove(e); 
		return e.returnValue;
	case WM_MOUSEWHEEL: 
		p->Window_MouseWheel(e); 
		return e.returnValue;
	case WM_PAINT: 
		p->Window_Paint(e); return e.returnValue;
	case WM_SETFOCUS: 
		p->Window_SetFocus(e); 
		return e.returnValue;
	case WM_SETFONT: 
		p->Window_SetFont(e); 
		return e.returnValue;
	case WM_SETTEXT: 
		p->Window_SetText(e); 
		return e.returnValue;
	case WM_SIZE: 
		p->width = LOWORD(lParam);
		p->height = HIWORD(lParam);
		if (p->initialWidth==0 && p->initialHeight==0)
		{
			p->initialWidth = p->width;
			p->initialHeight = p->height;
		}
		//if (p->children.empty() == false && p->initialWidth>0 && p->initialHeight>0 && p->width>0 && p->height>0)
		//{
		//	const int len = p->children.size();
		//	for(int i = 0; i<len; i++)
		//	{
		//		p->children[i]->DoDock(p->initialWidth, p->initialHeight, p->width, p->height);
		//	}
		//}
		p->Window_Size(e); 
		return e.returnValue;
	case WM_SYSCOMMAND: 
		p->Window_SysCommand(e); 
		return e.returnValue;
	case WM_TIMER: 
		p->Window_Timer(e); 
		return e.returnValue;
	case WM_USER: 
		p->Window_User(e); 
		return e.returnValue;
	case WM_VSCROLL:
		if (e.lParam==NULL)
		{
			p->Window_VScroll(e); 
			return e.returnValue;
		}
		if (p->EventHandler(e)) return e.returnValue;
		return FALSE;
	case WM_HSCROLL: 
		if (e.lParam==NULL) 
		{
			p->Window_HScroll(e); 
			return e.returnValue;
		}
		if (p->EventHandler(e)) return e.returnValue;
		return FALSE;
	case WM_COMMAND:
		if (p->EventHandler(e)) return e.returnValue;
		if (LOWORD(e.wParam)==IDCANCEL) 
		{
			p->Window_Cancel(e);
			return TRUE;
		}
		return FALSE;
	case WM_NOTIFY:
		if (p->EventHandler(e)) return e.returnValue;
		return FALSE;
	case WM_SOCKETNOTIFY: 
		p->Window_SocketNotify(e); 
		return e.returnValue;
	case WM_SOCKETHOSTNAME: 
		p->Window_SocketHostname(e); 
		return e.returnValue;
#ifdef WIN_DAC_ADC_SUPPORT
	case MM_WOM_OPEN: 
		p->Window_WomOpen(e); 
		return e.returnValue;
	case MM_WOM_CLOSE: 
		p->Window_WomClose(e); 
		return e.returnValue;
	case MM_WOM_DONE: 
		p->Window_WomDone(e); 
		return e.returnValue;
	case MM_WIM_OPEN: 
		p->Window_WimOpen(e); 
		return e.returnValue;
	case MM_WIM_CLOSE: 
		p->Window_WimClose(e); 
		return e.returnValue;
	case MM_WIM_DATA: 
		p->Window_WimData(e); 
		return e.returnValue;
#endif
	default:
		if (p->Window_WndProc(e)) return e.returnValue;
	}
	return FALSE;
}

void Dialog::InitializeGui()
{
}

// The function must return false, when the message is not being processed
bool Dialog::Window_WndProc(Win::Event& e)
{
	e.returnValue = FALSE;
	return false;
}

void Dialog::Window_WinAddChild(Win::Event& e)
{
	children.push_back((Win::IParent*)e.wParam);
	e.returnValue = TRUE;
}

void Dialog::Window_Activate(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_Cancel(Win::Event& e)
{
	this->EndDialog(FALSE);
	e.returnValue = TRUE;
}

void Dialog::Window_Char(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_Close(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_Open(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_Destroy(Win::Event& e)
{
	if (bModal) 
	{
		e.returnValue = FALSE;
		return;
	}
	e.returnValue = TRUE;
	::DestroyWindow(hWnd);
	//	RemoveModelessDlgHWND(hWnd);
	this->hWnd = NULL;
}

void Dialog::Window_DrawItem(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_DropFiles(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_EraseBkgnd(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_GetFont(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_GetMinMaxInfo(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_GetText(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_GetTextLength(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_Help(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_KeyDown(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_KeyUp(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_KillFocus(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_LButtonDblclk(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_LButtonDown(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_LButtonUp(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_RButtonDblclk(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_RButtonDown(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_RButtonUp(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_MeasureItem(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_MouseMove(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_MouseWheel(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_Paint(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_SetFocus(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_SetFont(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_SetText(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_Size(Win::Event& e)
{
	if (children.empty() == false && initialWidth>0 && initialHeight>0 && width>0 && height>0)
	{
		const int len = children.size();
		for(int i = 0; i<len; i++)
		{
			children[i]->DoDock(initialWidth, initialHeight, width, height);
		}
	}
	e.returnValue = FALSE;
}

void Dialog::DoChildDock(Win::IParent& child)
{
	child.DoDock(initialWidth, initialHeight, width, height);
}

// e.wParam
//SC_CLOSE, SC_CONTEXTHELP, SC_DEFAULT, SC_HOTKEY, SC_HSCROLL, SCF_ISSECURE,SC_KEYMENU, SC_MAXIMIZE,SC_MINIMIZE
//SC_MONITORPOWER, SC_MOUSEMENU, SC_MOVE, SC_NEXTWINDOW,SC_PREVWINDOW, SC_RESTORE, SC_SCREENSAVE, SC_SIZE
//SC_TASKLIST,SC_VSCROLL
void Dialog::Window_SysCommand(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_Timer(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_User(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_VScroll(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_HScroll(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_SocketNotify(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_SocketHostname(Win::Event& e)
{
	e.returnValue = FALSE;
}

#ifdef WIN_DAC_ADC_SUPPORT
void Dialog::Window_WomOpen(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_WomClose(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_WomDone(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_WimOpen(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_WimClose(Win::Event& e)
{
	e.returnValue = FALSE;
}

void Dialog::Window_WimData(Win::Event& e)
{
	e.returnValue = FALSE;
}

#endif

LRESULT CALLBACK Dialog::ModelessDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Dialog* p = NULL;
	if (uMsg == WM_INITDIALOG)
	{
		if (IsBadReadPtr((void *) lParam, sizeof(Dialog))==false)
		{
			p = (Dialog*)lParam;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)(LONG_PTR)p);
			p->hWnd = hWnd;
		}
		else
		{
			::MessageBox
				(
					hWnd, L"Invalid ModelessDlg pointer during WM_INITDIALOG", 
					L"Win::Dialog::ModelessDlgProc", MB_ICONERROR
				);
		}
	}
	else
	{
		p = (Dialog*)(LONG_PTR)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}
	if (p==NULL) return FALSE;

	Win::Event e;
	e.hWnd = hWnd;
	e.uMsg = uMsg;
	e.wParam = wParam;
	e.lParam = lParam;
	e.returnValue = FALSE;
	switch(uMsg)
	{
	case WM_WINADDCHILD: 
		p->Window_WinAddChild(e); 
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_ACTIVATE: 
		p->Window_Activate(e); 
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_CHAR: 
		p->Window_Char(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_CLOSE: 
		p->Window_Close(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_INITDIALOG:
		p->InitializeGui();
		p->Window_Open(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORSTATIC:
		if (p->EventHandler(e)) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_DESTROY: 
		p->Window_Destroy(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_DRAWITEM: 
		if ( ((DRAWITEMSTRUCT*)e.lParam)->CtlType == ODT_LISTBOX ||
			 ((DRAWITEMSTRUCT*)e.lParam)->CtlType == ODT_COMBOBOX ||
			  ((DRAWITEMSTRUCT*)e.lParam)->CtlType == ODT_BUTTON)
			   //((DRAWITEMSTRUCT*)e.lParam)->CtlType == ODT_STATIC ||
			   // ((DRAWITEMSTRUCT*)e.lParam)->CtlType == ODT_MENU)
		{
			if (p->EventHandler(e)) return e.returnValue;
		}
		p->Window_DrawItem(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_DROPFILES: 
		p->Window_DropFiles(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_ERASEBKGND: 
		p->Window_EraseBkgnd(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_GETFONT: 
		p->Window_GetFont(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_GETMINMAXINFO: 
		p->Window_GetMinMaxInfo(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_GETTEXT: 
		p->Window_GetText(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_GETTEXTLENGTH: 
		p->Window_GetTextLength(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_HELP: 
		p->Window_Help(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_KEYDOWN: 
		p->Window_KeyDown(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_KEYUP: 
		p->Window_KeyUp(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);;
	case WM_KILLFOCUS: 
		p->Window_KillFocus(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_LBUTTONDBLCLK: 
		p->Window_LButtonDblclk(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_LBUTTONDOWN: 
		p->Window_LButtonDown(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_LBUTTONUP: 
		p->Window_LButtonUp(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_RBUTTONDBLCLK: 
		p->Window_RButtonDblclk(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_RBUTTONDOWN: 
		p->Window_RButtonDown(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_RBUTTONUP: 
		p->Window_RButtonUp(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_MEASUREITEM: 
		p->Window_MeasureItem(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_MOUSEMOVE: 
		p->Window_MouseMove(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_MOUSEWHEEL: 
		p->Window_MouseWheel(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_PAINT: 
		p->Window_Paint(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_SETFOCUS: 
		p->Window_SetFocus(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_SETFONT: 
		p->Window_SetFont(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_SETTEXT: 
		p->Window_SetText(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_SIZE: 
		p->width = LOWORD(lParam);
		p->height = HIWORD(lParam);
		if (p->initialWidth==0 && p->initialHeight==0)
		{
			p->initialWidth = p->width;
			p->initialHeight = p->height;
		}
		//if (p->children.empty() == false && p->initialWidth>0 && p->initialHeight>0 && p->width>0 && p->height>0)
		//{
		//	const int len = p->children.size();
		//	for(int i = 0; i<len; i++)
		//	{
		//		p->children[i]->DoDock(p->initialWidth, p->initialHeight, p->width, p->height);
		//	}
		//}
		p->Window_Size(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_SYSCOMMAND: 
		p->Window_SysCommand(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_TIMER: 
		p->Window_Timer(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_USER: 
		p->Window_User(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_VSCROLL:
		if (e.lParam==NULL)
		{
			p->Window_VScroll(e); 
			return e.returnValue;
		}
		if (p->EventHandler(e)) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_HSCROLL: 
		if (e.lParam==NULL) 
		{
			p->Window_HScroll(e);
			return e.returnValue;
		}
		if (p->EventHandler(e)) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_COMMAND: 
		if (LOWORD(e.wParam)==IDCANCEL) 
		{
			p->Window_Cancel(e);
			return TRUE;
		}
		if (p->EventHandler(e)) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_NOTIFY:
		if (p->EventHandler(e)) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_SOCKETNOTIFY: 
		p->Window_SocketNotify(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_SOCKETHOSTNAME: 
		p->Window_SocketHostname(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
#ifdef WIN_DAC_ADC_SUPPORT
	case MM_WOM_OPEN: 
		p->Window_WomOpen(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case MM_WOM_CLOSE: 
		p->Window_WomClose(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case MM_WOM_DONE: 
		p->Window_WomDone(e); 
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case MM_WIM_OPEN: 
		p->Window_WimOpen(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case MM_WIM_CLOSE: 
		p->Window_WimClose(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	case MM_WIM_DATA: 
		p->Window_WimData(e);
		if (e.returnValue!=FALSE) return e.returnValue;
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
#endif
	default:
		if (p->Window_WndProc(e)) return e.returnValue;
	}
	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//_____________________________________________________________________ ListItem
ListItem::ListItem(void)
{
	isListBox = false;
	index = -1;
	listControl= NULL;
}

ListItem::~ListItem(void)
{
}

int ListItem::GetTextLength()
{
	if (isListBox)
	{
		return (int)::SendMessage(listControl, LB_GETTEXTLEN, index, 0);
	}
	else
	{
		return (int)::SendMessage(listControl, CB_GETLBTEXTLEN, index, 0);
	}
}

void ListItem::SetData(LPARAM data)
{
	if (isListBox)
	{
		::SendMessage(listControl, LB_SETITEMDATA, (WPARAM)index, (LPARAM)data);
	}
	else
	{
		::SendMessage(listControl, CB_SETITEMDATA, (WPARAM)index, (LPARAM)data);
	}
}

LPARAM ListItem::GetData()
{
	if (isListBox)
	{
		return (LPARAM)::SendMessage(listControl, LB_GETITEMDATA, (WPARAM)index, (LPARAM)0);
	}
	else
	{
		return (LPARAM)::SendMessage(listControl, CB_GETITEMDATA, (WPARAM)index, (LPARAM)0);
	}
}

void ListItem::GetText(wchar_t* text)
{
	::SendMessage(listControl, isListBox ? LB_GETTEXT : CB_GETLBTEXT, index, (LPARAM)text); 
}

wstring ListItem::GetText()
{
	const int length = GetTextLength();
	wstring tmp;
	tmp.resize(length+1);
	::SendMessage(listControl, isListBox ? LB_GETTEXT :CB_GETLBTEXT, index, (LPARAM)tmp.data()); 
	tmp.resize(length);
	return tmp;
}

//_____________________________________________________________________ ListItemCollection
ListItemCollection::ListItemCollection(void)
{
	iparent = NULL;
	isListBox = false;
	used_data = false;
	_data = 0;
}

ListItemCollection::~ListItemCollection(void)
{
}

Win::ListItem& ListItemCollection::operator[](long index)
{
	_item.isListBox = this->isListBox;
	_item.index = index;
	_item.listControl = this->iparent->GetHWND();
	return _item;
}

LRESULT ListItemCollection::Delete(int index)
{
	if (isListBox)
		return ::SendMessage(iparent->GetHWND(), LB_DELETESTRING, index, 0);
	else
		return ::SendMessage(iparent->GetHWND(), CB_DELETESTRING, index, 0);
}

LRESULT ListItemCollection::Add(const wstring& text)
{
	return Add(text.c_str());
}

LRESULT ListItemCollection::Add(const wstring& text, LPARAM data)
{
	return Add(text.c_str(), data);
}

LRESULT ListItemCollection::Add(const wstring& text, int index, LPARAM data)
{
	return Add(text.c_str(), index, data);
}

int ListItemCollection::GetIndex(const wstring& text)
{
	return GetIndex(text.c_str());
}

LRESULT ListItemCollection::Add(const wchar_t* text, LPARAM data)
{
	LRESULT result = 0;
	int index = 0;
	if (isListBox)
	{
		index = (int)::SendMessage(iparent->GetHWND(), LB_ADDSTRING, 0, (LPARAM)text);
		if (index !=LB_ERR)
		{
			return ::SendMessage(iparent->GetHWND(), LB_SETITEMDATA, index, (LPARAM)data); 
		}
	}
	else
	{
		index = (int)::SendMessage(iparent->GetHWND(), CB_ADDSTRING, 0, (LPARAM)text);
		if (index !=CB_ERR)
		{
			return ::SendMessage(iparent->GetHWND(), CB_SETITEMDATA, index, (LPARAM)data); 
		}
	}
	//___________________________________ Set seleccion if exists
	if (used_data==false) return 0;
	if (_data != data) return 0;
	if (isListBox)
	{
		if (index == LB_ERR) return 0;
		return ::SendMessage(iparent->GetHWND(), LB_SETCURSEL, index, 0);
	}
	else
	{
		if (index == CB_ERR) return 0;
		return ::SendMessage(iparent->GetHWND(), CB_SETCURSEL, index, 0);
	}
	return 0;
}

int ListItemCollection::GetCount()
{
	if (isListBox)
		return (int)::SendMessage(iparent->GetHWND(), LB_GETCOUNT, 0, 0);
	else
		return (int)::SendMessage(iparent->GetHWND(), CB_GETCOUNT, 0, 0);
}

void ListItemCollection::SetParent(Win::IParent* iparent, bool isListBox)
{
	this->iparent = iparent;
	this->isListBox = isListBox;
}

// Index = -1 to add at the bottom of the list
LRESULT ListItemCollection::Add(const wchar_t* text, int index, LPARAM data)
{
	int new_index;
	if (isListBox)
	{
		new_index = (int)::SendMessage(iparent->GetHWND(), LB_INSERTSTRING, index, (LPARAM)text);
		if (new_index !=LB_ERR)
		{
			::SendMessage(iparent->GetHWND(), LB_SETITEMDATA, new_index, (LPARAM)data); 
		}
	}
	else
	{
		new_index = (int)::SendMessage(iparent->GetHWND(), CB_INSERTSTRING, index, (LPARAM)text);
		if (new_index !=CB_ERR)
		{
			::SendMessage(iparent->GetHWND(), CB_SETITEMDATA, new_index, (LPARAM)data); 
		}
	}
	
	//___________________________________ Set seleccion if exists
	if (used_data==false) return 0;
	if (_data != data) return 0;
	if (isListBox)
	{
		if (new_index == LB_ERR) return 0;
		return ::SendMessage(iparent->GetHWND(), LB_SETCURSEL, new_index, 0);
	}
	else
	{
		if (new_index == CB_ERR) return 0;
		return ::SendMessage(iparent->GetHWND(), CB_SETCURSEL, new_index, 0);
	}
	return 0;
}

LRESULT ListItemCollection::Add(const wchar_t* text)
{
	if (isListBox)
	{
		return ::SendMessage(iparent->GetHWND(), LB_ADDSTRING, 0, (LPARAM)text);
	}
	else
	{
		return  ::SendMessage(iparent->GetHWND(), CB_ADDSTRING, 0, (LPARAM)text);
	}
	return 0;
}

//The return value is the zero-based index of the matching item. If the search is unsuccessful, it is CB_ERR
int ListItemCollection::GetIndex(const wchar_t* text)
{
	return (int)::SendMessage(iparent->GetHWND(), isListBox ? LB_FINDSTRING : CB_FINDSTRING,
		(WPARAM)-1, (LPARAM)text);
}

LRESULT ListItemCollection::DeleteAll()
{
	if (isListBox)
		return ::SendMessage(iparent->GetHWND(), LB_RESETCONTENT, 0, 0);
	else
		return ::SendMessage(iparent->GetHWND(), CB_RESETCONTENT, 0, 0);
}


//_____________________________________________________________________ DropDownList
DropDownList::DropDownList(void)
{
	m_bListBox = false;
	used_data = false;
	_data = 0;
	Items._data = _data;
	Items.used_data = used_data;
	Items.SetParent(this, false);
}

DropDownList::~DropDownList(void)
{
}

void DropDownList::CopyToClipboard()
{
	::SendMessage(this->hWnd, WM_COPY, 0, 0);
}

void DropDownList::PasteFromClipboard()
{
	::SendMessage(hWnd, WM_PASTE, 0, 0);
}

void DropDownList::ClearSelection()
{
	::SendMessage(hWnd, WM_CLEAR, 0, 0);
}

void DropDownList::CutSelection()
{
	::SendMessage(hWnd, WM_CUT, 0, 0);
}

//_____________________________________________________________________ ISelectInt
LPARAM& DropDownList::SqlGetInt()
{
	return _data;
}

void DropDownList::SqlUpdate(bool toGui)
{
	if (toGui == true)
	{
		if (::IsWindow(hWnd) == false) return;

		const int count = this->Items.GetCount();
		for(int i=0; i<count; i++)
		{
			if (this->Items[i].GetData()==_data)
			{
				this->SetSelected(i);
				break;
			}
		}
	}
	else
	{
		const int selectedIndex = (int)::SendMessage(hWnd, CB_GETCURSEL, 0, 0);
		_data = (LPARAM)::SendMessage(hWnd, CB_GETITEMDATA, (WPARAM)selectedIndex, (LPARAM)0);
	}
}

ListItemCollection& DropDownList::GetItems()
{
	return _items;
}

void DropDownList::InitialUpdate(HWND hParent)
{
	Items._data = _data;
	Items.used_data = used_data;
	::SendMessage(hParent, WM_WINADDCHILD, (WPARAM)this, (LPARAM)0);
}

void DropDownList::UpdateValue()
{
	this->used_data = true;
	const int selectedIndex = this->GetSelectedIndex();
	if (this->m_bListBox)
	{
		_data =  (LPARAM)::SendMessage(this->hWnd, LB_GETITEMDATA, (WPARAM)selectedIndex, (LPARAM)0);
	}
	else
	{
		_data =  (LPARAM)::SendMessage(this->hWnd, CB_GETITEMDATA, (WPARAM)selectedIndex, (LPARAM)0);
	}
}

bool DropDownList::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg == WM_COMMAND)
	{
		if (LOWORD(e.wParam) != this->id) return false;
		if (HIWORD(e.wParam) != notification) return false;
		return true;
	}
	else if (e.uMsg == WM_DRAWITEM && notification == WM_DRAWITEM)
	{
		if (e.wParam != this->id) return false;
		return true;
	}
	return false;
}

LRESULT DropDownList::ShowDropDown(bool show)
{
	BOOL f = show ? TRUE : FALSE;
	return ::SendMessage(this->hWnd, CB_SHOWDROPDOWN, (WPARAM)f, (LPARAM)0);
}

LPARAM DropDownList::GetSelectedData()
{
	if (IsWindow(hWnd))
	{
		const int selectedIndex = this->GetSelectedIndex();
		if (this->m_bListBox)
		{
			return (LPARAM)::SendMessage(this->hWnd, LB_GETITEMDATA, (WPARAM)selectedIndex, (LPARAM)0);
		}
		else
		{
			return (LPARAM)::SendMessage(this->hWnd, CB_GETITEMDATA, (WPARAM)selectedIndex, (LPARAM)0);
		}
	}
	if (used_data) return _data; 
	return -1;
}

// data[0] must be an integer primary key, data[1] must be the caption shown to the user
void DropDownList::Enumerate(wchar_t** data, int colCount, int rowIndex)
{
	if (colCount>=2)
	{
		this->Items.Add(data[1], (LPARAM)_wtoi(data[0]));
		//this->InsertItem(data[1], (DWORD)_wtoi(data[0]), rowIndex);
	}
	else if (colCount==1)
	{
		this->Items.Add(data[0]);
		//this->InsertString(data[0], rowIndex);
	}
}

int DropDownList::GetMinWidth()
{
	int nScrollBarWidth = ::GetSystemMetrics(SM_CXVSCROLL);
	int nCount = this->Items.GetCount();
	int i = 0;
	int nWidth = 0;
	SIZE size;
	wchar_t text[256];
	HDC hdc = ::GetDC(this->hWnd);

	for(i=0; i<nCount; i++)
	{
		this->Items[i].GetText(text);
		::GetTextExtentPoint32(hdc, text, lstrlen(text), &size);
		if (nWidth<size.cx) nWidth = size.cx;
	}
	::ReleaseDC(this->hWnd, hdc);
	return nWidth + 8 * ::GetSystemMetrics(SM_CXBORDER);
}

LRESULT DropDownList::SetSelected(int index)
{
	if (m_bListBox)
		return ::SendMessage(this->hWnd, LB_SETCURSEL, index, 0);
	else
		return ::SendMessage(this->hWnd, CB_SETCURSEL, index, 0);
}

int DropDownList::GetSelectedIndex()
{
	if (m_bListBox)
		return (int)::SendMessage(this->hWnd, LB_GETCURSEL, 0, 0);
	else
		return (int)::SendMessage(this->hWnd, CB_GETCURSEL, 0, 0);
}

// searchString may be only the first few letters of the string
LRESULT DropDownList::SetSelected(const wchar_t* searchString)
{
	if (m_bListBox)
		return ::SendMessage(this->hWnd, LB_SELECTSTRING, -1, (LPARAM)searchString);
	else
		return ::SendMessage(this->hWnd, CB_SELECTSTRING, -1, (LPARAM)searchString);
}

// searchString may be only the first few letters of the string
LRESULT DropDownList::SetSelected(const wstring& searchString)
{
	return SetSelected(searchString.c_str());
}

void DropDownList::SetSelectedByData(LPARAM data)
{
	if (IsWindow(hWnd))
	{
		const int count = this->Items.GetCount();
		for(int i=0; i<count; i++)
		{
			if (this->Items[i].GetData()==data)
			{
				this->SetSelected(i);
				break;
			}
		}
		return;
	}
	used_data = true;
	_data = data;
}

// It populates the list control with the directory files
// nAttribues: DDL_READWRITE, DDL_READONLY, DDL_HIDDEN, DDL_SYSTEM
// DDL_DIRECTORY, DDL_ARCHIVE, DDL_DRIVES, DDL_EXCLUSIVE (For searching)
// pszFilter: "*.*"
LRESULT DropDownList::FillWithDirectoryInfo(int nAttributes, const wchar_t* pszFilter)
{
	if (m_bListBox)
		return ::SendMessage(this->hWnd, LB_DIR, (WPARAM)nAttributes, (LPARAM)pszFilter);
	else
		return ::SendMessage(this->hWnd, CB_DIR, (WPARAM)nAttributes, (LPARAM)pszFilter);
}


//_____________________________________________________________________HourGlassCursor
HourGlassCursor::HourGlassCursor(void)
{
	hCursor = NULL;
}

HourGlassCursor::HourGlassCursor(bool busy)
{
	hCursor = NULL;
	if (busy) SetBusy();
}

HourGlassCursor::~HourGlassCursor(void)
{
	if (hCursor) ::SetCursor(hCursor);
}

HCURSOR HourGlassCursor::SetBusy()
{
	if (hCursor == NULL)
	{
		hCursor = ::SetCursor(::LoadCursor(NULL, IDC_WAIT));
		::ShowCursor(TRUE);
	}
	return hCursor;
}

void HourGlassCursor::SetNormal()
{
	if (hCursor) SetCursor(hCursor);
}

//_____________________________________________________________________ListBox
ListBox::ListBox(void)
{
	this->m_bListBox = true;
	this->Items.SetParent(this, true);
}

ListBox::~ListBox(void)
{
}

void ListBox::SetColumnWidth(int columnWidth)
{
	::SendMessage(this->hWnd, LB_SETCOLUMNWIDTH, (WPARAM)columnWidth, (LPARAM)0);
}

int ListBox::MultipleSetSelected(int nIndex, bool bSelect)
{
	return (int)::SendMessage(this->hWnd, LB_SETSEL, bSelect, nIndex);
}

bool ListBox::MultipleGetSelected(int nIndex)
{
	return (::SendMessage(this->hWnd, LB_GETSEL, nIndex, 0)!=0);
}

//_____________________________________________________________________Menu
Menu::Menu(void)
{
	this->hMenu = NULL;
	this->bPopUp = false;
	this->bCreated = false;
}

Menu::~Menu(void)
{
	Destructor();
}

void Menu::Attach(HMENU hMenu, bool bPopUp)
{
	Destructor();
	this->bPopUp = bPopUp;
	this->hMenu = hMenu;
	this->bCreated = false;
	this->nPosition = 0;
}

// Use this to attach a main menu with bPopUp set to false
void Menu::Attach(HWND hWnd, bool bPopUp)
{
	Destructor();
	this->bPopUp = bPopUp;
	this->hMenu = ::GetMenu(hWnd);
	this->bCreated = false;
	this->nPosition = 0;
}

bool Menu::Create(bool bPopUp)
{
	Destructor();
	this->bPopUp = bPopUp;
	if (this->bPopUp)
	{
		this->hMenu = ::CreateMenu();
	}
	else
	{
		this->hMenu = ::CreatePopupMenu();
	}
	this->bCreated = (this->hMenu!=NULL);
	return this->bCreated;
}

// You may need to call RefreshMenu() from the parent
void Menu::AddItem(UINT nID, wchar_t* pszCaption, bool bChecked, bool bEnabled)
{
	UINT flags = MF_STRING;
	if (bChecked) flags = flags | MF_CHECKED;
	if (bEnabled == false) flags = flags | MF_GRAYED;
	AppendMenu(this->hMenu, flags, nID, pszCaption);
	this->nPosition++;
}

// You may need to call RefreshMenu() from the parent
// you can use DDBitmaps objects through the method GetHBITMAP
void Menu::AddItem(UINT nID, HBITMAP hBitmap, bool bEnabled)
{
	UINT flags = MF_BITMAP;
	if (bEnabled == false) flags = flags | MF_GRAYED;
	AppendMenu(this->hMenu, flags, nID, (const wchar_t *)hBitmap);
	this->nPosition++;
}

void Menu::SetItemEnableByPosition(int nPosition, bool bEnabled)
{
	::EnableMenuItem
		(
		this->hMenu, nPosition, 
		bEnabled ? MF_ENABLED | MF_BYPOSITION : MF_GRAYED | MF_BYPOSITION
		);
}

void Menu::SetItemEnableByID(UINT nID, bool bEnabled)
{
	::EnableMenuItem(this->hMenu, nID, bEnabled ? MF_ENABLED : MF_GRAYED);
}

void Menu::SetItemCheckByPosition(int nPosition, bool bChecked)
{
	CheckMenuItem
		(
		this->hMenu, nPosition, 
		bChecked ? MF_CHECKED | MF_BYPOSITION : MF_UNCHECKED | MF_BYPOSITION
		);
}

void Menu::SetItemCheckByID(UINT nID, bool bChecked)
{
	::CheckMenuItem(this->hMenu, nID, bChecked ? MF_CHECKED : MF_UNCHECKED);
}

bool Menu::Create(HINSTANCE hInstance, const wchar_t * pszID)
{
	Destructor();
	this->bPopUp = false;
	this->hMenu = ::LoadMenu(hInstance, pszID);
	this->bCreated = (this->hMenu!=NULL);
	this->nPosition = 0;
	return this->bCreated;
}

HMENU Menu::GetHMENU()
{
	return this->hMenu;
}

HMENU Menu::GetSubHMENU_(int nPosition)
{
	return GetSubMenu(this->hMenu, nPosition);
}

// Returns result in pszCaption
int Menu::GetStringByID(UINT nID, wchar_t* pszCaption, int nMaxCount)
{
	return ::GetMenuString(this->hMenu, nID, pszCaption, nMaxCount, MF_BYCOMMAND);
}

// Returns result in pszCaption
int Menu::GetStringByPosition(UINT nID, wchar_t* pszCaption, int nMaxCount)
{
	return ::GetMenuString(this->hMenu, nID, pszCaption, nMaxCount, MF_BYPOSITION);
}

BOOL Menu::AddItem(MENUITEMINFO& menuInfo)
{
	return ::InsertMenuItem(this->hMenu, this->nPosition++, 1, &menuInfo);
}

bool Menu::IsItemEnabled(int nID)
{
	return ((::GetMenuState(this->hMenu, nID, MF_BYCOMMAND) & MF_GRAYED) == 0);
}

bool Menu::IsItemChecked(int nID)
{
	return ((::GetMenuState(this->hMenu, nID, MF_BYCOMMAND) & MF_CHECKED) != 0);
}

BOOL Menu::AppendMenu_(HMENU hMenu, wchar_t* pszCaption)
{
	return ::AppendMenu(this->hMenu, MF_POPUP | MF_ENABLED, (UINT_PTR)hMenu, pszCaption);
}

BOOL Menu::AppendMenu_(Menu& menu, wchar_t* pszCaption)
{
	return ::AppendMenu(this->hMenu, MF_POPUP | MF_ENABLED, (UINT_PTR)menu.GetHMENU(), pszCaption);
}

bool Menu::IsPopUp()
{
	return this->bPopUp;
}

BOOL Menu::DeleteItemByPosition(int nPosition)
{
	return ::DeleteMenu(this->hMenu, nPosition, MF_BYPOSITION);
}

BOOL Menu::DeleteItemByID(int nID)
{
	return ::DeleteMenu(this->hMenu, nID, MF_BYCOMMAND);
}

UINT Menu::GetItemID(int nPosition)
{
	return ::GetMenuItemID(this->hMenu, nPosition);
}

int Menu::GetItemCount()
{
	return ::GetMenuItemCount(this->hMenu);
}

Win::Menu Menu::GetSubMenu_(int nPosition)
{
	Menu m;
	m.Attach(GetSubMenu(this->hMenu, nPosition), this->bPopUp);
	return m;
}

// You may need to call RefreshMenu() from the parent
void Menu::AddSeparator()
{
	AppendMenu(this->hMenu, MF_SEPARATOR, 0, NULL);
}

Menu::operator HMENU()
{
	return this->hMenu;
}

void Menu::Destructor()
{
	if (this->bCreated)
	{
		::DestroyMenu(this->hMenu);
	}
	this->hMenu = NULL;
	this->bPopUp = false;
	this->bCreated = false;		
}
//_____________________________________________________________________ Label
Label::Label(void)
{
	//brush.CreateSolid(GetSysColor(COLOR_BTNFACE));
	_backColor = COLOR_BTNFACE;
	_textColor = RGB(0, 0, 0);
	_transparent = false;
}

Label::~Label(void)
{
}

void Label::SetTransparent(bool transparent)
{
	_transparent = transparent;
	::InvalidateRect(hWnd, NULL, TRUE);
}

bool Label::GetTransparent()
{
	return _transparent;
}

void Label::SetBackColor(COLORREF color)
{
	_backColor = color;
	_brush.CreateSolid(color);
	::InvalidateRect(hWnd, NULL, TRUE);
}

COLORREF Label::GetBackColor()
{
	return _backColor;
}

void Label::SetTextColor(COLORREF color)
{
	_textColor = color;
	_brush.CreateSolid(_backColor);
	::InvalidateRect(hWnd, NULL, TRUE);
}

COLORREF Label::GetTextColor()
{
	return _textColor;
}

// Requires the style SS_ICON
//m_static.Create(0, WS_VISIBLE | SS_CENTER | WS_CHILD | SS_ICON, L"HEY", 
//	0, 0, 100, 24, hWnd, (HMENU)IDC_HOLA);
//	m_hIcon = LoadIcon(this->hInstance, MAKEINTRESOURCE(IDI_SMALL));
//  m_static.SetImage(m_hIcon);
LRESULT Label::SetImage(HICON hicon)
{
	return ::SendMessage(this->hWnd, STM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hicon);
}

// Requires the style SS_BITMAP, you can add this style editing the resource file manually
// Win::DDBitmap m_bitmap;
//m_static.Create(0, WS_VISIBLE | WS_CHILD | SS_BITMAP, L"HEY", 
//	0, 0, 500, 500, hWnd, (HMENU)IDC_STATIC);
//	m_static.SetImage
//	(
//		m_bitmap.CreateFromResource(this->hInstance, MAKEINTRESOURCE(IDB_BITMAP3))
//	);
LRESULT Label::SetImage(HBITMAP hbitmap)
{
	return ::SendMessage(this->hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbitmap);
}

LRESULT Label::SetImage(Win::DDBitmap& bitmap)
{
	return ::SendMessage(this->hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)bitmap.GetHBITMAP());
}

// Requires the style SS_ENHMETAFILE
LRESULT Label::SetImage(HENHMETAFILE henhmetafile)
{
	return ::SendMessage(this->hWnd, STM_SETIMAGE, (WPARAM)IMAGE_ENHMETAFILE, (LPARAM)henhmetafile);
}

LRESULT Label::SetImage(Win::Metafile& metafile)
{
	return ::SendMessage(this->hWnd, STM_SETIMAGE, (WPARAM)IMAGE_ENHMETAFILE, (LPARAM)metafile.GetHandle());
}

LRESULT Label::SetImage(Sys::Bitmap& bitmap)
{
	return ::SendMessage(this->hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)bitmap.GetHBitmap());
}

LRESULT Label::SetImage(Sys::Icon& icon)
{
	return ::SendMessage(this->hWnd, STM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)icon.GetHIcon());
}

bool Label::IsEvent(Win::Event& e, int notification)
{
	if (notification != WM_CTLCOLORSTATIC) return false;
	if (e.uMsg != WM_CTLCOLORSTATIC) return false;
	//HWND hWndControl = (HWND)e.lParam;
	if ((HWND)e.lParam != this->hWnd) return false;
	HDC hdc = (HDC)e.wParam;
	if (_transparent)
	{
		::SetBkMode(hdc, TRANSPARENT);
		e.returnValue = (LRESULT)::GetStockObject(NULL_BRUSH);
	}
	else
	{
		::SetTextColor(hdc, _textColor);
		::SetBkColor(hdc, _backColor);
		::SetBkMode(hdc, TRANSPARENT);
		e.returnValue = (LRESULT)_brush.GetHBRUSH();
	}
	return true;
}

//_____________________________________________________________________PropertySheet and Wizard
PropertySheet_::PropertySheet_(void)
{
}

PropertySheet_::~PropertySheet_(void)
{
}

LRESULT CALLBACK PropertySheet_::PropertySheetProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PropertySheet_* p = NULL;
	if (uMsg == WM_INITDIALOG)
	{
		if (IsBadReadPtr((void *) lParam, sizeof(PropertySheet_))==false)
		{
			LPPROPSHEETPAGE pPSH = (LPPROPSHEETPAGE)lParam;
			p = (PropertySheet_*)(LONG_PTR)pPSH->lParam;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)(LONG_PTR)p);// ==0) //(LONG)(LONG_PTR)p) ==0)
			p->hWnd = hWnd;
		}
		else
		{
			::MessageBox
				(
					hWnd, L"Invalid PropertyPage pointer during WM_INITDIALOG", 
					L"Win::PropertySheet_.PropertySheetProc", MB_ICONERROR
				);
		}
	}
	else
	{
		p = (PropertySheet_*)(LONG_PTR)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}
	if (p==NULL) return FALSE;
	
	if (uMsg == WM_SIZE)
	{
		p->width = LOWORD(lParam);
		p->height = HIWORD(lParam);
	}
	Win::Event e;
	e.hWnd = hWnd;
	e.uMsg = uMsg;
	e.wParam = wParam;
	e.lParam = lParam;
	 p->Window_WndProc(e);
	 return e.returnValue;
}

void PropertySheet_::SetEnableApplyButton(bool bEnabled)
{
	UINT msg = bEnabled ? PSM_CHANGED : PSM_UNCHANGED;

	::SendMessage(::GetParent(this->hWnd),  msg, (WPARAM)(HWND)this->hWnd, (LPARAM)0);  
}

//PSWIZB_BACK   Enables the Back button. If this flag is not set, the Back button is displayed as disabled.
//PSWIZB_DISABLEDFINISH   Displays a disabled Finish button.
//PSWIZB_FINISH   Displays an enabled Finish button.
//PSWIZB_NEXT  Enables the Next button. If this flag is not set, the Next button is displayed as disabled.
void PropertySheet_::SetWizardButtons(DWORD dwFlags)
{
	::SendMessage(::GetParent(this->hWnd), (UINT)PSM_SETWIZBUTTONS, (WPARAM)0, (LPARAM)dwFlags);
}


// This callback function can be passed to the Property Sheet Header to hide the context help icon
int CALLBACK PropertySheet_::RemoveContextHelpProc(HWND hwnd, UINT message, LPARAM lParam)
{
    switch (message) 
	{
    case PSCB_PRECREATE:
        // Remove the DS_CONTEXTHELP style from the dialog box template
        if (((LPDLGTEMPLATEEX)lParam)->signature == 0xFFFF)
		{
            ((LPDLGTEMPLATEEX)lParam)->style &= ~DS_CONTEXTHELP;
        }
        else 
		{
            ((LPDLGTEMPLATE)lParam)->style &= ~DS_CONTEXTHELP;
        }
        return TRUE;
    }
    return TRUE;
}

//pp.Create(hWnd, MAKEINTRESOURCE(IDD_ABOUTBOX), NULL);
HPROPSHEETPAGE PropertySheet_::CreatePropertySheetPage_(HWND hWndParent, const wchar_t * pszTemplateId, const wchar_t * pszIcon)
{
	PROPSHEETPAGE psh;
	HPROPSHEETPAGE hpsp = NULL;

	psh.dwSize = sizeof(PROPSHEETPAGE);
	psh.dwFlags = (pszIcon==NULL) ? PSP_DEFAULT : PSP_DEFAULT | PSP_USEICONID;
	psh.hInstance = this->hInstance;
	psh.pszTemplate = pszTemplateId;
	psh.pszIcon = pszIcon;
	psh.pfnDlgProc = (DLGPROC)PropertySheetProc;
	psh.pszTitle = L"";
	psh.pfnCallback = NULL;
	//
	this->hWnd = NULL;
	psh.lParam= (LPARAM)(LONG_PTR)this;
	hpsp = ::CreatePropertySheetPage(&psh);
	return hpsp;
}

// The size of the dialog must be 317 X 193
HPROPSHEETPAGE PropertySheet_::CreateWizardMainPage(HWND hWndParent, const wchar_t * pszTemplateId)
{
	PROPSHEETPAGE psh;
	HPROPSHEETPAGE hpsp = NULL;

	psh.dwSize = sizeof(PROPSHEETPAGE);
	psh.dwFlags = PSP_DEFAULT | PSP_HIDEHEADER;
	psh.hInstance = this->hInstance;
	psh.pszTemplate = pszTemplateId;
	psh.pszIcon = NULL;
	psh.pfnDlgProc = (DLGPROC)PropertySheetProc;
	psh.pszTitle = L"";
	psh.pfnCallback = NULL;
	//
	this->hWnd = NULL;
	psh.lParam= (LPARAM)(LONG_PTR)this;
	hpsp = ::CreatePropertySheetPage(&psh);
	return hpsp;
}

// The size of the dialog must be 317 X 143
HPROPSHEETPAGE PropertySheet_::CreateWizardPage(HWND hWndParent, const wchar_t * pszTemplateId, const wchar_t * pszTitle, const wchar_t * pszSubTitle)
{
	PROPSHEETPAGE psh;
	HPROPSHEETPAGE hpsp = NULL;

	psh.dwSize = sizeof(PROPSHEETPAGE);
	psh.dwFlags = PSP_DEFAULT | PSP_USEHEADERTITLE | PSP_USEHEADERSUBTITLE;
	psh.hInstance = this->hInstance;
	psh.pszTemplate = pszTemplateId;
	psh.pszIcon = NULL;
	psh.pfnDlgProc = (DLGPROC)PropertySheetProc;
	psh.pszTitle = NULL;
	psh.pszHeaderTitle = pszTitle;
	psh.pszHeaderSubTitle = pszSubTitle;
	psh.pfnCallback = NULL;
	//
	this->hWnd = NULL;
	psh.lParam= (LPARAM)(LONG_PTR)this;
	hpsp = ::CreatePropertySheetPage(&psh);
	return hpsp;
}

//_____________________________________________________________________ColorDlg
COLORREF ColorDlg::m_rgbColor[16];
//COLORREF ColorDlg::m_rgbCurrent = 0;

ColorDlg::ColorDlg(void)
{
	ZeroMemory(&m_cc, sizeof(CHOOSECOLOR));
	m_cc.lStructSize=sizeof(CHOOSECOLOR);
	m_cc.lpCustColors = (LPDWORD) m_rgbColor;
	ResetCustomColors();
}

ColorDlg::~ColorDlg(void)
{
}

void ColorDlg::ResetCustomColors()
{
	m_rgbColor[0] = RGB(255, 200, 200);
	m_rgbColor[8] = RGB(255, 230, 230);

	m_rgbColor[1] = RGB(255, 255, 200);
	m_rgbColor[9] = RGB(255, 255, 230);

	m_rgbColor[2] = RGB(255, 200, 128);
	m_rgbColor[10] = RGB(255, 240, 230);

	m_rgbColor[3] = RGB(180, 255, 180);
	m_rgbColor[11] = RGB(220, 255, 220);

	m_rgbColor[4] = RGB(200, 255, 255);
	m_rgbColor[12] = RGB(230, 255, 255);

	m_rgbColor[5] = RGB(255, 168, 222);
	m_rgbColor[13] = RGB(255, 217, 241);

	m_rgbColor[6] = RGB(210, 210, 255);
	m_rgbColor[14] = RGB(230, 230, 255);

	m_rgbColor[7] = RGB(222, 222, 222);
	m_rgbColor[15] = RGB(240, 240, 240);
}

void ColorDlg::SetSelectedColor(COLORREF color)
{
	m_cc.rgbResult = color;
}

COLORREF ColorDlg::GetSelectedColor()
{
	return m_cc.rgbResult;
}

bool ColorDlg::BeginDialog(HWND hWndParent)
{
	m_cc.hwndOwner=hWndParent;		
	//if (customColors)
	//{
		m_cc.Flags = CC_RGBINIT | CC_FULLOPEN | CC_ANYCOLOR | CC_SOLIDCOLOR;
	//}
	//else
	//{
	//	m_cc.Flags = CC_RGBINIT | CC_PREVENTFULLOPEN | CC_ANYCOLOR;
	//}
	return (ChooseColor(&m_cc)==TRUE);
}

bool ColorDlg::SaveCustomColors(const wchar_t* filename)
{
	Sys::File file;
	if (file.CreateForWritting(filename) == false) return false;
	const int bytesToWrite = 16*sizeof(COLORREF);
	if (bytesToWrite != file.Write(m_rgbColor, bytesToWrite)) return false;
	return true;
}

bool ColorDlg::LoadCustomColors(const wchar_t* filename)
{
	Sys::File file;
	if (file.CreateForReading(filename) == false) return false;
	const int fileSize = file.GetSizeInBytes();

	const int bytesToRead = 16*sizeof(COLORREF);
	if (file.GetSizeInBytes() != bytesToRead) return false;
	if (bytesToRead != file.Read(m_rgbColor, bytesToRead)) return false;
	return true;
}

//_____________________________________________________________________ VideoAvi
int VideoAvi::bRegistered = false;

VideoAvi::VideoAvi(void)
{
	_brush.CreateSolid(::GetSysColor(COLOR_BTNFACE));
	if (bRegistered==false)
	{
		INITCOMMONCONTROLSEX cc;
		cc.dwSize=sizeof(INITCOMMONCONTROLSEX);
		cc.dwICC=ICC_ANIMATE_CLASS;
		::InitCommonControlsEx(&cc);
		bRegistered=true;
	}
	_backColor = RGB(255, 255, 255);
}

VideoAvi::~VideoAvi(void)
{

}

//Allows you to match an animation's background color to that of the underlying window, creating a "transparent" background. 
//The parent of the animation control must not have the WS_CLIPCHILDREN style (see Window Styles). 
//The control sends a WM_CTLCOLORSTATIC message to its parent. Use SetBkColor to set the background 
//color for the device context to an appropriate value. The control interprets the upper-left pixel of the first 
//frame as the animation's default background color. It will remap all pixels with that color 
//to the value you supplied in response to WM_CTLCOLORSTATIC. 
bool VideoAvi::IsEvent(Win::Event& e, int notification)
{
	e.returnValue = FALSE;
	if (notification == WM_CTLCOLORSTATIC && e.uMsg==WM_CTLCOLORSTATIC)
	{
		HWND hWndControl = (HWND)e.lParam;
		if (hWndControl != this->hWnd) return false;
		HDC hdc = (HDC)e.wParam;

		//LONG_PTR style = ::GetWindowLongPtr(hWnd, GWL_EXSTYLE);  
		//bool transparent = (style & WS_EX_TRANSPARENT) != 0;
		LONG_PTR style = ::GetWindowLongPtr(hWnd, GWL_STYLE);

		if ((style & ACS_TRANSPARENT) != 0)
		{
			//SetTextColor(...);
			::SetBkColor(hdc, _backColor);
			e.returnValue = (LRESULT) _brush.GetHBRUSH();
			return true;
		}
	}
	if (e.uMsg != WM_COMMAND) return false;
	if (LOWORD(e.wParam)!=this->id) return false;
	if (HIWORD(e.wParam)==notification)
	{
		e.returnValue = TRUE;
		return true;
	}
	return false;
}

void VideoAvi::SetBackColor(COLORREF color)
{
	_backColor = color;
	_brush.CreateSolid(_backColor);
	::InvalidateRect(hWnd, NULL, TRUE);
}

COLORREF VideoAvi::GetBackColor()
{
	return _backColor;
}


HWND VideoAvi::Create(DWORD dwExStyle, const wchar_t* pszWindowName, DWORD dwStyle, int x, int y, int width, int height, HWND hParent, int id)
{
	this->id = 0;
	this->_initialRect.left =0;
	this->_initialRect.top = 0;
	this->_initialRect.bottom = 0;
	this->_initialRect.right = 0;
	//
	this->hWnd = Animate_Create(hParent, (HMENU)id, dwStyle, this->hInstance);
	::SetWindowPos(this->hWnd, 0, x, y, width, height, SWP_NOZORDER | SWP_DRAWFRAME); 
//    Animate_Open(m_hWnd, "SEARCH.AVI"; 
	::ShowWindow(hWnd, SW_SHOW);
	if (this->hWnd == NULL) return NULL;
	this->id = id;
	this->_initialRect.left = x;
	this->_initialRect.top = y;
	this->_initialRect.bottom = y + height;
	this->_initialRect.right = x + width;
	return this->hWnd;
}

/////////////////////////////////////////////////////////////////////////////
//
// AVI
//
//IDA_UPDATE               AVI                     "update.avi"
//
//If resource_id is NULL, the system closes the AVI file that was previously opened for the specified animation control, if any. 
bool VideoAvi::Open(int resource_id)
{
	Animate_Close(this->hWnd);
	//
	HINSTANCE hInstance = NULL;
	bool ok = (::SendMessage(hWnd, ACM_OPEN, (WPARAM)hInstance, (LPARAM)MAKEINTRESOURCE(resource_id)) != 0);
	::ShowWindow(hWnd, SW_SHOW);
	return ok;
}

bool VideoAvi::Open(LPTSTR name) 
{
	Animate_Close(this->hWnd);
	//
	bool ok = (::SendMessage(hWnd, ACM_OPEN, (WPARAM)0, (LPARAM)name) != 0);
	::ShowWindow(hWnd, SW_SHOW);
	return ok;
}

BOOL VideoAvi::CloseAnimation()
{
	return Animate_Close(this->hWnd);
}

BOOL VideoAvi::Play(UINT from, UINT to, UINT repeat) 
{
	BOOL f = Animate_Play(this->hWnd, from, to, repeat);
	::ShowWindow(this->hWnd, SW_SHOW);
	return f;
}

BOOL VideoAvi::Play(int repeatCount)
{
	BOOL f = Animate_Play(this->hWnd, 0, -1, repeatCount);
	::ShowWindow(this->hWnd, SW_SHOW);
	return f;
}

BOOL VideoAvi::PlayContinuously()
{
	BOOL f = Animate_Play(this->hWnd, 0, -1, -1);
	::ShowWindow(this->hWnd, SW_SHOW);
	return f;
}

BOOL VideoAvi::Stop()
{
	return Animate_Stop(this->hWnd);
}

//_____________________________________________________________________ DateView
bool DateView::bInit = 0;

DateView::DateView(void)
{
	if (bInit==false)
	{
		INITCOMMONCONTROLSEX cc;
		cc.dwSize=sizeof(INITCOMMONCONTROLSEX);
		cc.dwICC=ICC_DATE_CLASSES;
		InitCommonControlsEx(&cc);
		bInit= true;
	}	
	used_systemtime = false;
}

DateView::~DateView(void)
{
}

//_______________________________________ ISelectTime
Sys::SqlTime& DateView::SqlGetTime()
{
	return _sqltime;
}

Sys::Time& DateView::SqlGetSysTime()
{
	return _systemtime;
}

void DateView::SqlUpdate(bool toGui)
{
	if (toGui == true)
	{
		Sys::Convert::SqlTimeToSysTime(_sqltime, _systemtime);
		::SendMessage(this->hWnd, MCM_SETCURSEL, 0, (WPARAM)&_systemtime);
	}
	else
	{
		::SendMessage(this->hWnd, (UINT) MCM_GETCURSEL, (WPARAM)0, (LPARAM)&_systemtime);
		Sys::Convert::SysTimeToSqlTime(_systemtime, _sqltime);
	}
}

void DateView::SetMonthBkColor(COLORREF color)
{
	::SendMessage(this->hWnd, (UINT)MCM_SETCOLOR, (WPARAM)MCSC_MONTHBK, (LPARAM)color);
}

COLORREF DateView::GetMonthBkColor()
{
	return (COLORREF)::SendMessage(this->hWnd, (UINT)MCM_GETCOLOR, 
			(WPARAM)MCSC_MONTHBK, (LPARAM)0);
}

void DateView::SetTitleBkColor(COLORREF color)
{
	::SendMessage(this->hWnd, (UINT)MCM_SETCOLOR, (WPARAM)MCSC_TITLEBK, (LPARAM)color);
}

COLORREF DateView::GetTitleBkColor()
{
	return (COLORREF)::SendMessage(this->hWnd, (UINT)MCM_GETCOLOR, 
			(WPARAM)MCSC_TITLEBK, (LPARAM)0);
}

void DateView::SetTitleTextColor(COLORREF color)
{
	::SendMessage(this->hWnd, (UINT)MCM_SETCOLOR, (WPARAM)MCSC_TITLETEXT, (LPARAM)color);
}

COLORREF DateView::GetTitleTextColor()
{
	return (COLORREF)::SendMessage(this->hWnd, (UINT)MCM_GETCOLOR, 
			(WPARAM)MCSC_TITLETEXT, (LPARAM)0);
}

void DateView::SetTrailingTextColor(COLORREF color)
{
	::SendMessage(this->hWnd, (UINT)MCM_SETCOLOR, (WPARAM)MCSC_TRAILINGTEXT, (LPARAM)color);
}

COLORREF DateView::GetTrailingTextColor()
{
	return (COLORREF)::SendMessage(this->hWnd, (UINT)MCM_GETCOLOR, 
			(WPARAM)MCSC_TRAILINGTEXT, (LPARAM)0);
}

void DateView::SetBackColor(COLORREF color)
{
	::SendMessage(this->hWnd, (UINT)MCM_SETCOLOR, 
			(WPARAM)MCSC_BACKGROUND, (LPARAM)color);
}

COLORREF DateView::GetBackColor()
{
	return (COLORREF)::SendMessage(this->hWnd, (UINT)MCM_GETCOLOR, 
			(WPARAM)MCSC_BACKGROUND, (LPARAM)0);
}

void DateView::SetTextColor(COLORREF color)
{
	::SendMessage(this->hWnd, (UINT)MCM_SETCOLOR, 
			(WPARAM)MCSC_TEXT, (LPARAM)color);
}

COLORREF DateView::GetTextColor()
{
	return (COLORREF)::SendMessage(this->hWnd, (UINT)MCM_GETCOLOR, 
			(WPARAM)MCSC_TEXT, (LPARAM)0);
}

bool DateView::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_NOTIFY) return false;
	NMHDR* pNMHDR= (LPNMHDR)e.lParam; 
     if (pNMHDR->hwndFrom!=this->GetHWND()) return false;
     if (pNMHDR->code!=notification) return false; 
	return true;
}

void DateView::InitialUpdate(HWND hParent)
{
	if (used_systemtime)
	{
		::SendMessage(this->hWnd, MCM_SETCURSEL, 0, (WPARAM)&_systemtime);
	}
	::SendMessage(hParent, WM_WINADDCHILD, (WPARAM)this, (LPARAM)0);
}

bool DateView::SetCurrentSelection(Sys::Time& systime)
{
	_systemtime = systime;
	used_systemtime = true;
	if (hWnd==NULL) return true;
	return (::SendMessage(this->hWnd, MCM_SETCURSEL, 0, (WPARAM)&systime)!=0);
}

bool DateView::GetCurrentSelection(Sys::Time& systime)
{
	systime.wHour = 0;
	systime.wMinute = 0;
	systime.wSecond = 0;
	systime.wMilliseconds = 0;
	if (::IsWindow(hWnd))
	{
		if (::SendMessage(this->hWnd, MCM_GETCURSEL, 0, (WPARAM)&systime)!=0)
		{
			systime.wHour = 0;
			systime.wMinute = 0;
			systime.wSecond = 0;
			systime.wMilliseconds = 0;
			return true;
		}
	}
	systime = _systemtime;
	systime.wHour = 0;
	systime.wMinute = 0;
	systime.wSecond = 0;
	systime.wMilliseconds = 0;
	return true;
}

Sys::Time DateView::GetCurrentSelection()
{
	Sys::Time st;
	GetCurrentSelection(st);
	return st;
}

bool DateView::GetCurrentSelection(int& month, int& day, int& year)
{
	Sys::Time st;
	bool result =GetCurrentSelection(st);
	month = st.wMonth;
	day = st.wDay;
	year = st.wYear;
	return result;
}
	
bool DateView::SetCurrentSelection(int month, int day, int year)
{
	Sys::Time st;
	st.wMonth = month;
	st.wYear = year;
	st.wDay = day;
	return SetCurrentSelection(st);
}

void DateView::AdjustSize(int x, int y)
{
	RECT rect;
	int nTodayWidth;

	MonthCal_GetMinReqRect(this->hWnd, &rect);
	nTodayWidth=MonthCal_GetMaxTodayWidth(this->hWnd);
	if (nTodayWidth>rect.right) rect.right=nTodayWidth;
	::MoveWindow(this->hWnd, x, y, rect.right, rect.bottom,1);
}

void DateView::Window_Size(Win::Event& e)
{
	::MoveWindow(this->hWnd, 0, 0, LOWORD(e.lParam), HIWORD(e.lParam), TRUE);
	e.returnValue = TRUE;
}

bool DateView::SetRange(Sys::Time& minimum, Sys::Time& maximum)
{
	LRESULT lr;
	SYSTEMTIME st[2];

	st[0] = minimum;
	st[1] = maximum;
	lr = ::SendMessage(
				this->hWnd, 
				(UINT)MCM_SETRANGE, 
				(WPARAM)(SHORT)GDTR_MAX | GDTR_MIN,
				(LPARAM)(LPSYSTEMTIME)st
			);
	return (lr != 0);
}

//_____________________________________________________________________ HotKey
HotKey::HotKey(void)
{
}

HotKey::~HotKey(void)
{
}

// Set rules for invalid key combinations. If the user does not supply a
// modifier key, use ALT as a modifier. If the user supplies SHIFT as a 
// modifier key, use SHIFT + ALT instead.
//
// SetRules(HKCOMB_NONE | HKCOMB_S,   // invalid key combinations 
//                MAKELPARAM(HOTKEYF_ALT, 0));       // add ALT to invalid entries 
void HotKey::SetRules(WPARAM invalidKeyCombinations, LPARAM invalidEntries)
{
	::SendMessage(hWnd, HKM_SETRULES, invalidKeyCombinations, invalidEntries);
}

// Set CTRL + ALT + A as the default hot key for this window. 
// 0x41 is the virtual key code for 'A'. 
//
// SetHotKey(MAKEWORD(0x41, HOTKEYF_CONTROL | HOTKEYF_ALT));
void HotKey::SetHotKey(WPARAM defaultKey)
{
	::SendMessage(hWnd, HKM_SETHOTKEY, defaultKey, (LPARAM)0);
}

//_____________________________________________________________________ DateTimeBox
bool DateTimeBox::bInit = false;

DateTimeBox::DateTimeBox(void)
{
	if (bInit==false)
	{
		INITCOMMONCONTROLSEX cc;
		cc.dwSize=sizeof(INITCOMMONCONTROLSEX);
		cc.dwICC=ICC_DATE_CLASSES;
		::InitCommonControlsEx(&cc);
		bInit=true;
	}
	used_systemtime = false;
}

DateTimeBox::~DateTimeBox(void)
{
}

//_______________________________________ ISelectTime
Sys::SqlTime& DateTimeBox::SqlGetTime()
{
	return _sqltime;
}

Sys::Time& DateTimeBox::SqlGetSysTime()
{
	return _systemtime;
}

void DateTimeBox::SqlUpdate(bool toGui)
{
	if (toGui == true)
	{
		Sys::Convert::SqlTimeToSysTime(_sqltime, _systemtime);
		::SendMessage(this->hWnd, (UINT) DTM_SETSYSTEMTIME, (WPARAM)(DWORD)GDT_VALID, (LPARAM)&_systemtime);
	}
	else
	{
		::SendMessage(this->hWnd, (UINT) DTM_GETSYSTEMTIME, (WPARAM)0, (LPARAM)&_systemtime);
		Sys::Convert::SysTimeToSqlTime(_systemtime, _sqltime);
	}
}

//void DateTimeBox::SetMonthBkColor(COLORREF color)
//{
//	::SendMessage((HWND)::SendMessage(hWnd, DTM_GETMONTHCAL, 0, 0),
//		(UINT)MCM_SETCOLOR, (WPARAM)MCSC_MONTHBK, (LPARAM)color);
//}
//
//void DateTimeBox::SetTitleBkColor(COLORREF color)
//{
//	::SendMessage((HWND)::SendMessage(hWnd, DTM_GETMONTHCAL, 0, 0),
//		(UINT)MCM_SETCOLOR, (WPARAM)MCSC_TITLEBK, (LPARAM)color);
//}
//
//void DateTimeBox::SetTitleTextColor(COLORREF color)
//{
//	::SendMessage((HWND)::SendMessage(hWnd, DTM_GETMONTHCAL, 0, 0),
//		(UINT)MCM_SETCOLOR, (WPARAM)MCSC_TITLETEXT, (LPARAM)color);
//}
//
//void DateTimeBox::SetTrailingTextColor(COLORREF color)
//{
//	::SendMessage((HWND)::SendMessage(hWnd, DTM_GETMONTHCAL, 0, 0),
//		(UINT)MCM_SETCOLOR, (WPARAM)MCSC_TRAILINGTEXT, (LPARAM)color);
//}

void DateTimeBox::UpdateValue()
{
	this->used_systemtime = true;
	if (GDT_ERROR != ::SendMessage(this->hWnd, (UINT) DTM_GETSYSTEMTIME,
		(WPARAM)0, (LPARAM)&_systemtime)) return;
}

bool DateTimeBox::GetCurrentSelection(int& month, int& day, int& year)
{
	Sys::Time st;
	bool result =GetCurrentSelection(st);
	month = st.wMonth;
	day = st.wDay;
	year = st.wYear;
	return result;
}
	
bool DateTimeBox::SetCurrentSelection(int month, int day, int year)
{
	Sys::Time st;
	st.wMonth = month;
	st.wYear = year;
	st.wDay = day;
	return SetCurrentSelection(st);
}

bool DateTimeBox::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_NOTIFY) return false;
	NMHDR* pNMHDR= (LPNMHDR)e.lParam; 
     if (pNMHDR->hwndFrom!=this->GetHWND()) return false;
     if (pNMHDR->code!=notification) return false; 
	return true;
}

void DateTimeBox::InitialUpdate(HWND hParent)
{
	if (used_systemtime)
	{
		::SendMessage(this->hWnd, (UINT) DTM_SETSYSTEMTIME,
			(WPARAM)(DWORD)GDT_VALID, (LPARAM)&_systemtime);
	}
	::SendMessage(hParent, WM_WINADDCHILD, (WPARAM)this, (LPARAM)0);
}

bool DateTimeBox::GetCurrentSelection(Sys::Time& systime)
{
	if (::IsWindow(hWnd))
	{
		if (GDT_ERROR != ::SendMessage(this->hWnd, (UINT) DTM_GETSYSTEMTIME,
			(WPARAM)0, (LPARAM)&systime)) return true;
	}
	systime = _systemtime;
	return true;
}

bool DateTimeBox::SetCurrentSelection(Sys::Time& systime)
{
	_systemtime = systime;
	used_systemtime = true;
	if (hWnd==NULL) return true;
	if (0 != ::SendMessage(this->hWnd, (UINT) DTM_SETSYSTEMTIME,
			(WPARAM)(DWORD)GDT_VALID, (LPARAM)&systime))
	{
		//value = *pst;
		return true;
	}
	return false;
}

Sys::Time DateTimeBox::GetCurrentSelection()
{
	Sys::Time systime;
	this->GetCurrentSelection(systime);
	return systime;
}

bool DateTimeBox::SetRange(Sys::Time& minimum, Sys::Time& maximum)
{
	LRESULT lr;
	SYSTEMTIME st[2];

	st[0] = minimum;
	st[1] = maximum;
	lr = ::SendMessage(
				this->hWnd, 
				(UINT)DTM_SETRANGE, 
				(WPARAM)(SHORT)GDTR_MAX | GDTR_MIN,
				(LPARAM)(LPSYSTEMTIME)st
			);
	return (lr != 0);
}

bool DateTimeBox::SetFormat(const wchar_t * format)
{
	LRESULT lr;
	lr = ::SendMessage(hWnd, (UINT) DTM_SETFORMAT, (WPARAM)0, (LPARAM) (const wchar_t *)format);
	return (lr != 0);
}

//_____________________________________________________________________ IpAddress
bool IpAddress::bInit = false;

IpAddress::IpAddress(void)
{
	if (bInit==false)
	{
		INITCOMMONCONTROLSEX cc;
		cc.dwSize=sizeof(INITCOMMONCONTROLSEX);
		cc.dwICC=ICC_INTERNET_CLASSES;
		::InitCommonControlsEx(&cc);
		bInit=true;
	}
}

IpAddress::~IpAddress(void)
{
}

void IpAddress::SetFieldRange(int index, int minimum, int maximum)
{
	::SendMessage(hWnd, IPM_SETRANGE, (WPARAM)index, (LPARAM)MAKEIPRANGE(minimum, maximum));
}

void IpAddress::SetAddress(int b1, int b2, int b3, int b4) 
{
	::SendMessage(hWnd, IPM_SETADDRESS, (WPARAM)0, (LPARAM)MAKEIPADDRESS(b1, b2, b3, b4));
}

void IpAddress::GetAddress(int& b1, int& b2, int& b3, int& b4)
{
	b1 = 0;
	b2 = 0;
	b3 = 0;
	b4 = 0;
	DWORD address;
	::SendMessage(hWnd, IPM_GETADDRESS, (WPARAM)0, (LPARAM)&address);
	b1 = FIRST_IPADDRESS(address);
	b2 = SECOND_IPADDRESS(address);
	b3 = THIRD_IPADDRESS(address);
	b4 = FOURTH_IPADDRESS(address);
}

void IpAddress::Clear()
{
	::SendMessage(hWnd, IPM_CLEARADDRESS, (WPARAM)0, (LPARAM)0);
}

bool IpAddress::IsBlank()
{
	return (::SendMessage(hWnd, IPM_ISBLANK, (WPARAM)0, (LPARAM)0) != 0);
}

//_____________________________________________________________________ SysLink
bool SysLink::bInit = false;

SysLink::SysLink(void)
{
	//::CoInitialize(NULL);
	if (bInit==false)
	{
		INITCOMMONCONTROLSEX cc;
		cc.dwSize=sizeof(INITCOMMONCONTROLSEX);
		cc.dwICC=ICC_LINK_CLASS;
		::InitCommonControlsEx(&cc);
		bInit=true;
	}
}

SysLink::~SysLink(void)
{
	//::CoUninitialize();
}

//LITEM litem;
//litem.mask = LIF_ITEMINDEX | LIF_STATE | LIF_ITEMID | LIF_URL;
//litem.iLink = 0;
//litem.state = LIS_ENABLED; //LIS_FOCUSED, LIS_VISITED;
//litem.stateMask = LIS_ENABLE; 
//_snwprintf_s(litem.szID, MAX_LINKID_TEXT, _TRUNCATE, L"%s", L"Yahoo!");
//_snwprintf_s(litem.szUrl, L_MAX_URL_LENGTH, _TRUNCATE, L"%s", L"http://www.yahoo.com");
void SysLink::SetItem(LITEM& litem)
{
	::SendMessage(hWnd, LM_SETITEM, (WPARAM)NULL, (LPARAM)&litem);
}

void SysLink::GetItem(LITEM& litem)
{
	::SendMessage(hWnd, LM_GETITEM, (WPARAM)NULL, (LPARAM)&litem);
}

//SysLink_Return(Win::Event& e)
//SysLink_Click(Win::Event& e)
//{
//	PNMLINK pNMLink = (PNMLINK) lparam;
//
//	if (!StrCmpW(pNMLink->item.szID, L"idLaunchHelp"))
//	{
//		// Insert code here to launch Help Center.
//	}
//	else if (!StrCmpW(pNMLink->item.szID, L"idHelpMenu"))
//	{
//		// Insert code here to launch Help Menu.
//	}
//}



//#ifdef WIN_FOLDER_DLG
//_____________________________________________________________________FolderDlg
FolderDlg::FolderDlg(void)
{
	DWORD dwCoInit = COINIT_APARTMENTTHREADED;
	::CoInitializeEx(NULL, dwCoInit);
	pathName[0]='\0';
	displayName[0]='\0';
	tmpName[0]='\0';
	memset(&browseInfo, 0, sizeof(BROWSEINFO));
	SHGetDesktopFolder(&shellFolderRoot);		 // get root IShellFolder
}

FolderDlg::~FolderDlg(void)
{
	//if (pidl) FolderDlg::FreePIDL(pidl);
	shellFolderRoot->Release();
	::CoUninitialize();
}

wchar_t* FolderDlg::GetFolderName()
{
	return displayName;
}

// Returns NULL if cancelled
wchar_t* FolderDlg::BeginDialog(HWND hParent, const wchar_t * caption)
{
	const bool bNewDlgStyle = true;
	browseInfo.hwndOwner = hParent;
	browseInfo.pidlRoot = NULL;
	browseInfo.pszDisplayName = displayName;
	browseInfo.lpszTitle = caption;
	browseInfo.ulFlags = bNewDlgStyle? BIF_USENEWUI | BIF_VALIDATE : BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	browseInfo.lpfn = CallbackProc;
	browseInfo.lParam = (LPARAM)this;
	
	LPCITEMIDLIST pidl = SHBrowseForFolder(&browseInfo); // do it
	if (pidl==NULL) return NULL;
	this->GetPathName_(pidl);
	CopyMemory(tmpName, pathName, WIN_FILEDLG_MAXPATH*sizeof(wchar_t));
	this->FreePIDL(pidl);
	return pathName;
}

// Handy function to get the string pathname from pidl.
wchar_t* FolderDlg::GetPathName_(LPCITEMIDLIST pidl)
{
	SHGetPathFromIDList(pidl, pathName);
	return pathName;
}

// Handy function to get the display name from pidl.
wchar_t* FolderDlg::GetDisplayNameOf(IShellFolder* psf, LPCITEMIDLIST pidl, DWORD uFlags)
{
	STRRET strret;								 // special struct for GetDisplayNameOf
	strret.uType = STRRET_CSTR;			 // get as CSTR
	if (SUCCEEDED(psf->GetDisplayNameOf(pidl, uFlags, &strret))) {
		StrRetToBuf(&strret, pidl, displayName, WIN_FILEDLG_MAXPATH);
	}
	return displayName;
}

// Free PIDL using shell's IMalloc
void FolderDlg::FreePIDL(LPCITEMIDLIST pidl)
{
	IMalloc* iMalloc=NULL;	// shell's IMalloc
	HRESULT hr = SHGetMalloc(&iMalloc);
	if(SUCCEEDED(hr)) iMalloc->Free((void*)pidl);
	if (iMalloc) iMalloc->Release();
}

int CALLBACK FolderDlg::CallbackProc(HWND hwnd, UINT msg, LPARAM lp, LPARAM lpData)
{
	FolderDlg* pDlg = (FolderDlg*)lpData;
	if (pDlg)
	{
		switch (msg) 
		{
		case BFFM_INITIALIZED:
			pDlg->OnInitialized();
			return 0;
		case BFFM_IUNKNOWN:
			//pDlg->OnIUnknown((IUnknown*)lp);
			return 0;
		case BFFM_SELCHANGED:
			pDlg->OnSelChanged((LPCITEMIDLIST)lp);
			return 0;
		case BFFM_VALIDATEFAILED:
			return pDlg->OnValidateFailed((const wchar_t *)lp);
		//default:
			//::MessageBox
		}
	}
	return 0;
}

void FolderDlg::OnInitialized()
{
	if (lstrlen(tmpName)>0)  
	{
	//	//this->SetExpanded(tmpName);
		this->SetSelection(tmpName);
	}
//	if (pidl) this->SetSelection(pidl);
	//if (!(browseInfo.ulFlags & BIF_NEWDIALOGSTYLE)) SetStatusText(L"Old style title");
	//SetOKText(L"Choose Me!";
}

//// Browser is notifying me with its IUnknown: use it to set filter if
//// requested. Note this can be called with punk=NULL when shutting down!
//void FolderDlg::OnIUnknown(IUnknown* punk)
//{
//	BFTRACE(L"CFolderDialog::OnIUnknown: %p\n", punk);
//	if (punk && m_bFilter) {
//		CComQIPtr<IFolderFilterSite> iffs;
//		VERIFY(SUCCEEDED(punk->QueryInterface(IID_IFolderFilterSite, (void**)&iffs)));
//		iffs->SetFilter((IFolderFilter*)&m_xFolderFilter);
//		// smart pointer automatically Releases iffs,
//		// no longer needed once you call SetFilter
//	}
//}

// User selected a different folder.
void FolderDlg::OnSelChanged(LPCITEMIDLIST pidl)
{
	GetDisplayNameOf(shellFolderRoot, pidl, SHGDN_FORPARSING);
	if (browseInfo.ulFlags & BIF_NEWDIALOGSTYLE) 
	{
		GetPathName_(pidl);
		EnableOK(lstrlen(pathName)>0);
	}
}

// User attempted to enter a name in the edit box that isn't a folder.
BOOL FolderDlg::OnValidateFailed(const wchar_t * lpsz)
{
	wchar_t lenguaje[64];
	::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_ILANGUAGE, lenguaje, 64);
	if (lstrcmp(L"0409", lenguaje)==0)
		this->MessageBox(L"The specified folder does not exist", L"Browse Folder", MB_OK | MB_ICONERROR);
	else
		this->MessageBox(L"La carpeta no existe", L"Explorar carpeta", MB_OK | MB_ICONERROR);
	return TRUE; // don't close dialog.
}

//#endif

//_____________________________________________________________________FileDlg
wchar_t FileDlg::m_szCustomFilter[255];

FileDlg::FileDlg(void)
{
	SetFilter(L"Text Documents (*.txt)\0*.txt\0All Files (*.*)\0*.*\0\0", 0, L"txt");
	m_szFileName[0] ='\0';
	m_szPath[0] ='\0';
	m_szExt[0] ='\0';
	m_szFilePath[0] = '\0';
	//
	memset(&openFileName, 0, sizeof(OPENFILENAME));
	openFileName.lStructSize=sizeof(OPENFILENAME);
	openFileName.hwndOwner=NULL;
	//
	openFileName.lpstrFilter= m_szFilter;
	//
	openFileName.lpstrCustomFilter = m_szCustomFilter;
	openFileName.nMaxCustFilter = WIN_MAX_FILTER-1;
	//
	openFileName.lpstrFile=m_szPath;
	openFileName.nMaxFile=WIN_FILEDLG_MAXPATH;
	//
	openFileName.lpstrFileTitle=m_szFileName;
	openFileName.nMaxFileTitle=WIN_FILEDLG_MAXPATH;
	//
	openFileName.lpstrDefExt = m_szDefaultExt; //Default extension
	//
	openFileName.lpstrInitialDir = NULL;
	openFileName.Flags = OFN_OVERWRITEPROMPT | OFN_EXPLORER;
}

FileDlg::~FileDlg(void)
{
}

void FileDlg::Clear()
{
	m_szFileName[0] ='\0';
	m_szPath[0] ='\0';
	//m_szExt[0] ='\0';
	m_szFilePath[0] = '\0';
}

void FileDlg::ClearFileName()
{
	m_szFileName[0] ='\0';
}

// returns only the file name
const wchar_t* FileDlg::GetFileName()
{
	return m_szFileName;
}

bool FileDlg::SetFileName(const wchar_t* fileName)
{
	if (fileName==NULL) return false;
	const int length = lstrlen(fileName);
	lstrcpyn(m_szPath, fileName, WIN_FILEDLG_MAXPATH);
	m_szFileName[WIN_FILEDLG_MAXPATH-1]='\0';
	return true;
}

// return the file name with the full path
const wchar_t* FileDlg::GetFileNameFullPath()
{
	return m_szPath;
}

wstring FileDlg::GetSelectedFileName()
{
	return m_szPath;
}

void FileDlg::SetSelectedFileName(const wstring fileName)
{
	const int len = fileName.length();
	if (len > 0)
	{
		SetFileName(fileName.c_str());
	}
	else
	{
		m_szPath[0] = '\0';
	}
}

wstring& FileDlg::GetWorkingFolder()
{
	_workingFolder = GetFilePath();
	return _workingFolder;
}

void FileDlg::SetWorkingFolder(const wstring& folderName)
{
	_workingFolder = folderName;
	this->openFileName.lpstrInitialDir = _workingFolder.c_str();
}

// returns the path where the file is located
const wchar_t* FileDlg::GetFilePath()
{
	const int n= wcslen(m_szPath) - wcslen(m_szFileName);
	lstrcpyn(m_szFilePath, m_szPath, n);
	return m_szFilePath;
}

// Default extension is appended if the user does not provide one
// SetFilter(L"Text Documents (*.txt)\0*.txt\0All Files (*.*)\0*.*\0\0", 0, L"txt");
void FileDlg::SetFilter(wchar_t* pszFilter, int nFilterIndex, wchar_t* pszDefaultExt)
{
	wchar_t* p = NULL;
	int i = 0;
	
	for(p = pszFilter, i = 0; (*p != '\0' || *(p+1) != '\0') && i<WIN_MAX_FILTER-2; p++, i++)
	{
		m_szFilter[i] = *p;
	}
	m_szFilter[i++]='\0';
	m_szFilter[i]='\0';
	
	openFileName.nFilterIndex = nFilterIndex;
	lstrcpyn(m_szDefaultExt, pszDefaultExt, 32);
	m_szDefaultExt[32-1] = '\0';
}

const wchar_t* FileDlg::GetFileNameWithoutExt()
{
	Sys::TextAssistant::ExtractFileName(m_szFilePath, false, m_szFileNameWithoutExt, WIN_FILEDLG_MAXPATH);
	//const int n = wcslen(m_szFileName);
	//if (n<=0) return NULL;
	//lstrcpyn(m_szFileNameWithoutExt, m_szFileName, WIN_FILEDLG_MAXPATH);
	//const int extLength = wcslen(this->GetExt());
	//m_szFileNameWithoutExt[n-extLength-1]='\0';
	return m_szFileNameWithoutExt;
}

bool FileDlg::BeginDialog(HWND hWndParent, const wchar_t* caption, bool save)
{
	openFileName.lpstrTitle = caption;
	openFileName.hwndOwner = hWndParent;
	if (save == true)
	{

		openFileName.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_EXPLORER;
		return (::GetSaveFileName(&openFileName) ==TRUE);
	}
	openFileName.Flags=OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER;
	return (::GetOpenFileName(&openFileName) ==TRUE);
}

const wchar_t* FileDlg::GetExt()
{
	m_szExt[0] ='\0';
	Sys::TextAssistant::ExtractFileExt(m_szFileName, m_szExt, 32);
	return m_szExt;
}


//_____________________________________________________________________FindReplaceDlg
HWND FindReplaceDlg::m_hWndFindReplace = NULL;
FINDREPLACE FindReplaceDlg::m_fr;
wchar_t FindReplaceDlg::m_szFindText[MAX_FIND_LEN];
wchar_t FindReplaceDlg::m_szReplaceText[MAX_FIND_LEN];
UINT FindReplaceDlg::m_FindMessage = 0;

FindReplaceDlg::FindReplaceDlg(void)
{
	
	//m_fr.Flags = FR_HIDEUPDOWN | FR_HIDEMATCHCASE | FR_HIDEWHOLEWORD;
}

FindReplaceDlg::~FindReplaceDlg(void)
{
}

// Execute last on WndProc
LRESULT FindReplaceDlg::CheckFindMessage(Win::Event& e)
{
	if (e.uMsg == m_FindMessage)
	{
		LPFINDREPLACE pfr = (LPFINDREPLACE)e.lParam;

		if (pfr->Flags & FR_DIALOGTERM)
		{
			//Win::Module::RemoveModelessDlgHWND(m_hWndFindReplace);
			m_hWndFindReplace = NULL;
		}

		if (pfr->Flags & FR_FINDNEXT)
		{
			::MessageBox(e.hWnd, pfr->lpstrFindWhat, L"Finding", MB_OK);
		}

		if (pfr->Flags & FR_REPLACE)
		{
			::MessageBox(e.hWnd, pfr->lpstrReplaceWith, pfr->lpstrFindWhat, MB_OK);
		}

		if (pfr->Flags & FR_REPLACEALL)
		{
			::MessageBox(e.hWnd, pfr->lpstrReplaceWith, pfr->lpstrFindWhat, MB_OK);
		}
	}
	return 0;
}

void FindReplaceDlg::UpdateHWND(HWND hWndFindReplaceDlg)
{
	if (hWndFindReplaceDlg != NULL)
	{
		if (m_hWndFindReplace!=NULL)
		{
			//Win::Module::RemoveModelessDlgHWND(m_hWndFindReplace);
		}
		//Win::Module::AddModelessDlgHWND(hWndFindReplaceDlg);
		m_hWndFindReplace = hWndFindReplaceDlg;
	}
}

HWND FindReplaceDlg::OpenFindDlg(HWND hWndParent, const wchar_t* pszFindWhat)
{
	HWND hWnd = NULL;

	ZeroMemory(&m_fr, sizeof(FINDREPLACE));
	m_fr.lStructSize = sizeof (FINDREPLACE);
	m_fr.hwndOwner = hWndParent;
	m_fr.lpstrFindWhat = m_szFindText;
	m_fr.wFindWhatLen = MAX_FIND_LEN;
	m_fr.lpstrReplaceWith = NULL;
	m_fr.wReplaceWithLen = 0;

	hWnd = FindText(&m_fr);
	UpdateHWND(hWnd);
	return hWnd;
}

HWND FindReplaceDlg::OpenReplaceDlg
(
	HWND hWndParent, const wchar_t* pszFindWhat, const wchar_t* pszReplaceWith
)
{
	HWND hWnd = NULL;

	ZeroMemory(&m_fr, sizeof(FINDREPLACE));
	m_fr.lStructSize = sizeof (FINDREPLACE);
	m_fr.hwndOwner = hWndParent;
	m_fr.lpstrFindWhat = m_szFindText;
	m_fr.wFindWhatLen = MAX_FIND_LEN;
	m_fr.lpstrReplaceWith = m_szReplaceText;
	m_fr.wReplaceWithLen = MAX_FIND_LEN;
	
	hWnd = ReplaceText(&m_fr);
	UpdateHWND(hWnd);
	return hWnd;
}

//_____________________________________________________________________FontDlg
FontDlg::FontDlg(void)
{
	ZeroMemory(&m_cf, sizeof(CHOOSEFONT));
	m_cf.lStructSize=sizeof(CHOOSEFONT);
	//m_cf.Flags=CF_BOTH | CF_USESTYLE | CF_EFFECTS;
	m_cf.Flags=CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;//CF_TTONLY True Type only
	::ZeroMemory(&m_logFont, sizeof(LOGFONT));
	m_logFont.lfHeight = -24;
	m_logFont.lfWidth = 0;
	m_logFont.lfEscapement = 0;
	m_logFont.lfOrientation = 0;
	m_logFont.lfWeight = FW_NORMAL;
	m_logFont.lfItalic = FALSE;
	m_logFont.lfUnderline = FALSE;
	m_logFont.lfStrikeOut = FALSE;
	m_logFont.lfCharSet = DEFAULT_CHARSET;
	m_logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	m_logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	m_logFont.lfQuality = CLEARTYPE_NATURAL_QUALITY;
	m_logFont.lfPitchAndFamily = VARIABLE_PITCH | FF_DONTCARE;
	_snwprintf_s(m_logFont.lfFaceName, 32, _TRUNCATE, L"%s", L"Arial");
	m_cf.lpLogFont = &m_logFont;

	//m_cf.hDC = hdc; You can pass the HDC of a printer to display the printer fonts, use CF_PRINTERFONTS
	//m_cf.iPointSize = 0;
	//m_cf.rgbColors = 0;
	//m_cf.lCustData = 0;
	//m_cf.lpfnHook = NULL;
	//m_cf.lpTemplateName = NULL;
	//m_cf.hInstance = NULL;
	//m_cf.lpszStyle = NULL;
	//m_cf.nFontType = 0;
	//m_cf.nSizeMin = 0;
	//m_cf.nSizeMax = 0;
}

FontDlg::~FontDlg(void)
{
}

void FontDlg::SetSelectedFontName(const wstring& fontname)
{
	_snwprintf_s(m_logFont.lfFaceName, 32, _TRUNCATE, L"%s", fontname.c_str());
}

wstring FontDlg::GetSelectedFontName()
{
	return m_logFont.lfFaceName;
}

void FontDlg::SetSelectedPointSize(const double pointSize)
{
	m_cf.iPointSize = (int)(10*pointSize);
	m_logFont.lfHeight = - Sys::Convert::FontPointToLogicUnits(pointSize);
}

double FontDlg::GetSelectedPointSize()
{
	return m_cf.iPointSize/10.0;
}

bool FontDlg::BeginDialog(HWND hWndParent)
{
	m_cf.hwndOwner = hWndParent;
	return (ChooseFont(&m_cf)==TRUE);
}

void FontDlg::SetSelectedLogFont(LOGFONT& logFont)
{
	m_logFont = logFont;
}

LOGFONT& FontDlg::GetSelectedLogFont()
{
	return m_logFont;
}


void FontDlg::SetSelectedFontColor(COLORREF color)
{
	m_cf.rgbColors = color;
}

COLORREF FontDlg::GetSelectedFontColor()
{
	return m_cf.rgbColors;
}

void FontDlg::SetSelectedFont(Win::Gdi::Font& font)
{
	::GetObject(font.GetHFONT(), sizeof(LOGFONT), (PTSTR)&m_logFont);
}

//_____________________________________________________________________Edit
//By default, the dialog box window procedure uses the tab key to navigate
//between controls. It intercepts the tab key before the edit control gets it.
//Overriding this normal behaviour may confuse your users. If you want to do
//it anyway, then you need to subclass the edit control and process the
//WM_GETDLGCODE message by returning DLGC_WANTTAB.

Textbox::Textbox(void)
{
	maxTextLength=0;
	//brush.CreateSolid(GetSysColor(COLOR_WINDOW));
	used_text = false;
	_textColor = RGB(0, 0, 0);
	_backColor = RGB(255, 255, 255);
	_printAlignment = WIN_ALIGNMENT_JUSTIFIED;
	//_printRowCount = 0;
	//_printListType = WIN_LISTTYPE_NONE;
}

Textbox::~Textbox(void)
{
	//if (m_brush) DeleteObject(m_brush);
}

void Textbox::SetLeft(bool isLeft)
{
	LONG_PTR style = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	if (isLeft == true)
	{
		style = style | ES_LEFT;
	}
	else
	{
		style = style & (~ES_LEFT);
	}
	::SetWindowLongPtr(hWnd, GWL_STYLE, style);
}

bool Textbox::GetLeft()
{
	LONG_PTR result = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	return ((result & ES_LEFT) != 0);
}

void Textbox::SetCenter(bool isCenter)
{
	LONG_PTR style = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	if (isCenter == true)
	{
		style = style | ES_CENTER;
	}
	else
	{
		style = style & (~ES_CENTER);
	}
	::SetWindowLongPtr(hWnd, GWL_STYLE, style);
}

bool Textbox::GetCenter()
{
	LONG_PTR result = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	return ((result & ES_CENTER) != 0);
}

void Textbox::SetRight(bool isRight)
{
	LONG_PTR style = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	if (isRight == true)
	{
		style = style | ES_RIGHT;
	}
	else
	{
		style = style & (~ES_RIGHT);
	}
	::SetWindowLongPtr(hWnd, GWL_STYLE, style);
}

bool Textbox::GetRight()
{
	LONG_PTR result = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	return ((result & ES_RIGHT) != 0);
}

void Textbox::SetMultiline(bool isMultiline)
{
	LONG_PTR style = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	if (isMultiline == true)
	{
		style = style | ES_MULTILINE;
	}
	else
	{
		style = style & (~ES_MULTILINE);
	}
	::SetWindowLongPtr(hWnd, GWL_STYLE, style);
}

bool Textbox::GetMultiline()
{
	LONG_PTR result = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	return ((result & ES_MULTILINE) != 0);
}

void Textbox::SetUppercase(bool isUppercase)
{
	LONG_PTR style = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	if (isUppercase == true)
	{
		style = style | ES_UPPERCASE;
	}
	else
	{
		style = style & (~ES_UPPERCASE);
	}
	::SetWindowLongPtr(hWnd, GWL_STYLE, style);
}

bool Textbox::GetUppercase()
{
	LONG_PTR result = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	return ((result & ES_UPPERCASE) != 0);
}

void Textbox::SetLowercase(bool isLowercase)
{
	LONG_PTR style = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	if (isLowercase == true)
	{
		style = style | ES_LOWERCASE;
	}
	else
	{
		style = style & (~ES_LOWERCASE);
	}
	::SetWindowLongPtr(hWnd, GWL_STYLE, style);
}

bool Textbox::GetLowercase()
{
	LONG_PTR result = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	return ((result & ES_LOWERCASE) != 0);
}

void Textbox::SetPassword(bool isPassword)
{
	LONG_PTR style = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	if (isPassword == true)
	{
		style = style | ES_PASSWORD;
	}
	else
	{
		style = style & (~ES_PASSWORD);
	}
	::SetWindowLongPtr(hWnd, GWL_STYLE, style);
}

bool Textbox::GetPassword()
{
	LONG_PTR result = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	return ((result & ES_PASSWORD) != 0);
}

void Textbox::SetNumber(bool isNumber)
{
	LONG_PTR style = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	if (isNumber == true)
	{
		style = style | ES_NUMBER;
	}
	else
	{
		style = style & (~ES_NUMBER);
	}
	::SetWindowLongPtr(hWnd, GWL_STYLE, style);
}

bool Textbox::GetNumber()
{
	LONG_PTR result = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	return ((result & ES_NUMBER) != 0);
}

void Textbox::CopyToClipboard()
{
	::SendMessage(this->hWnd, WM_COPY, 0, 0);
}

void Textbox::PasteFromClipboard()
{
	::SendMessage(hWnd, WM_PASTE, 0, 0);
}

void Textbox::ClearSelection()
{
	::SendMessage(hWnd, WM_CLEAR, 0, 0);
}

void Textbox::CutSelection()
{
	::SendMessage(hWnd, WM_CUT, 0, 0);
}

//_____________________________________________________________________ ISelectString
wstring& Textbox::SqlGetString()
{
	return _text;
}

void Textbox::SqlUpdate(bool toGui)
{
	if (toGui == true)
	{
		const int len = wcslen(_text.c_str());
		_text.resize(len);
		::SetWindowText(hWnd, _text.c_str());
	}
	else
	{
		const int len = ::GetWindowTextLength(hWnd)+1;
		_text.resize(len);
		::GetWindowText(hWnd, (wchar_t*)_text.c_str(), len);
		_text.resize(len-1);
	}
}

void Textbox::InitialUpdate(HWND hParent)
{
	if (used_text)
	{
		::SetWindowText(hWnd, _text.c_str());
	}
	::SendMessage(hParent, WM_WINADDCHILD, (WPARAM)this, (LPARAM)0);
}

void Textbox::UpdateValue()
{
	this->used_text = true;
	const int length = ::GetWindowTextLength(hWnd);
	_text.resize(length);
	::GetWindowText(hWnd, (wchar_t*)_text.data(), length+1);
}

void Textbox::SetBackColor(COLORREF color)
{
	_backColor = color;
	brush.CreateSolid(_backColor);
	if (hWnd) ::InvalidateRect(hWnd, NULL, TRUE);
}

COLORREF Textbox::GetBackColor()
{
	return _backColor;
}

COLORREF Textbox::GetTextColor()
{
	return _textColor;
}

void Textbox::SetTextColor(COLORREF color)
{
	_textColor = color;
	brush.CreateSolid(_backColor);
	if (hWnd) ::InvalidateRect(hWnd, NULL, TRUE);
}

wstring Textbox::GetText()
{
	if (::IsWindow(hWnd))
	{
		const int length = ::GetWindowTextLength(hWnd);
		_text.resize(length);
		::GetWindowText(hWnd, (wchar_t*)_text.data(), length+1);
		return _text;
	}
	return _text;
}

void Textbox::SetText(const wstring text)
{
	_text = text;
	used_text = true;
	if (hWnd==NULL) return;
	::SetWindowText(hWnd, text.c_str());
}

bool Textbox::IsEvent(Win::Event& e, int notification)
{
	if (notification == WM_CTLCOLOREDIT && e.uMsg==WM_CTLCOLOREDIT)
	{
		if ((HWND)e.lParam != this->hWnd) return false;
		HDC hdc = (HDC)e.wParam;
		::SetTextColor(hdc, _textColor);
		::SetBkColor(hdc, _backColor);
		::SetBkMode(hdc, TRANSPARENT);
		e.returnValue = (LRESULT)brush.GetHBRUSH();
		return true;
	}
	if (e.uMsg!=WM_COMMAND) return false;
	if (LOWORD(e.wParam)!=this->id) return false;
	if (HIWORD(e.wParam)==notification) return true;
	return false;
}

bool Textbox::GetInt(int &outValue)
{
	BOOL b;
	outValue = ::GetDlgItemInt(this->GetParent(), id, &b, TRUE);
	return (b==TRUE);
}

int Textbox::GetInt(void)
{
	return Sys::Convert::ToInt(Text);
}

void Textbox::SetInt(int value)
{
	this->Text = Sys::Convert::ToString(value);
}

//TTI_ERROR,TTI_INFO,TTI_NONE,TTI_WARNING
LRESULT Textbox::ShowBalloonTip(LPCWSTR caption, LPCWSTR text, INT icon) 
{
	EDITBALLOONTIP tip; //.ShowBalloonTip(L"Kohonen net", ...
	tip.cbStruct = sizeof(EDITBALLOONTIP);
	tip.pszText = text;
	tip.pszTitle = caption;
	tip.ttiIcon = icon;
	return ::SendMessage(this->hWnd, EM_SHOWBALLOONTIP, 0, (LPARAM) (PEDITBALLOONTIP)&tip);
}

//TTI_ERROR,TTI_INFO,TTI_NONE,TTI_WARNING
LRESULT Textbox::ShowBalloonTip(const wstring& caption, const wstring& text, INT icon)
{
	EDITBALLOONTIP tip; //.ShowBalloonTip(L"Kohonen net", ...
	tip.cbStruct = sizeof(EDITBALLOONTIP);
	tip.pszText = text.c_str();
	tip.pszTitle = caption.c_str();
	tip.ttiIcon = icon;
	return ::SendMessage(this->hWnd, EM_SHOWBALLOONTIP, 0, (LPARAM) (PEDITBALLOONTIP)&tip);
}

void Textbox::HideBalloonTip()
{
	::SendMessage(this->hWnd, EM_HIDEBALLOONTIP, 0, (LPARAM)0L);
}

int Textbox::GetPrintLineCount(Win::PrintDoc& doc, int lineHeight)
{
	vector<wstring> paragraph;
	if (GetParagraphText(paragraph)==false) return 0;
	//Win::PrintDoc printDoc;
	//POINT size = Win::PrintDoc::GetLetterPrintArea(true);
	//______________________________________ Create a gdi from a bitmap
	RECT rect = {0, 0, 512, 512};
	Win::DDBitmap bitmap;
	bitmap.CreateCompatible(hWnd, 512, 512);
	Win::Gdi gdi(bitmap, rect, false);
	gdi.SetMapMode(MM_ISOTROPIC);
	gdi.SetWindowExtEx(doc.GetPaperSize().x, doc.GetPaperSize().y);
	gdi.SetViewportExtEx(512, 512);
	gdi.SetWindowOrgEx(doc.GetMargin().left, -doc.GetMargin().top);
	gdi.SetViewportOrgEx(0, 0);
	Win::Gdi::Font font;
	this->CreatePrintFont(font, lineHeight);
	gdi.SelectFont_(font);
	int count = 0;
	POINT size = doc.GetPrintingAreaSize();
	for(int i = 0; i<(int)paragraph.size(); i++)
	{
		count += gdi.DrawParagraph(paragraph[i].c_str(), size.x, 0, 0, _printAlignment, 0); // Draw only the first raw
	}
	if (paragraph.size()>1)
	{
		count += (paragraph.size()-1);
	}
	//Win::Clipboard::CopyDDBToClipboard(hWnd, bitmap);
	return count;
}

void Textbox::SetPrintAlignment(int alignment) //WIN_ALIGNMENT_LEFT, WIN_ALIGNMENT_RIGHT, WIN_ALIGNMENT_CENTER, WIN_ALIGNMENT_JUSTIFIED
{
	_printAlignment = alignment;
}

//void Textbox::SetPrintList(int type) //WIN_LISTTYPE_NONE, WIN_LISTTYPE_NUMBER, WIN_LISTTYPE_UNNUMBER
//{
//	_printListType = type;
//}

void Textbox::CreatePrintFont(Win::Gdi::Font& output, int rowHeight)
{
	const int fontSize = (int)(rowHeight*0.8+0.5);
	LOGFONT logfont;
	Win::Gdi::Font::InitializeLogfont(logfont); 
	HFONT hfont = (HFONT)::SendMessage(hWnd, WM_GETFONT, 0, 0);
	if (hfont == NULL)
	{
		output.Create(L"Arial", fontSize, false, false, false, false);
	}
	else
	{
		if (::GetObject(hfont, sizeof(LOGFONT), &logfont)!=0 )
		{
			logfont.lfHeight = - fontSize;
			output.Create(logfont);
		}
		else
		{
			output.Create(L"Arial", fontSize, false, false, false, false);
		}
	}
}

void Textbox::Print(Win::Gdi& gdi, Win::PrintInfo pi)
{
	const int offsetX = (int)(pi.height*0.3+0.5);
	const int offsetY = (int)(pi.height*0.1+0.5);

	Win::Gdi::Pen pen;
	//___________________________________________________________________ Font
	Win::Gdi::Font font;
	CreatePrintFont(font, pi.height);
	gdi.SelectFont_(font);
	gdi.SetTextColor(RGB(0, 0, 0));
	pi.position.x = 0;

	//wstring text = this->Text;
	vector<wstring> paragraph;
	if (GetParagraphText(paragraph)==false) return;
	const int paragraphCount = paragraph.size();
	gdi.SetTextAlign(TA_LEFT | TA_TOP);
	int count = 0;
	int i = 0;
	int rows = 0;
	int paragraphIndex;
	int rowIndex;

	//__________________________________________ Find which row to print
	for(i = 0; i<paragraphCount; i++)
	{
		rows = gdi.DrawParagraph(paragraph[i].c_str(), pi.width, pi.position.x, pi.position.y, _printAlignment, -2);
		count += rows;
		count += 1; // a blank line after the paragraph
		if (count>pi.index)
		{
			paragraphIndex = i;
			break;
		}
	}

	for(i= 0; i<rows; i++)
	{
		rowIndex = count - (rows+1) + i;
		//if (paragraphIndex == 0)
		//{
		//	rowIndex = count - (rows+1) + i;
		//}
		//else
		//{
		//	rowIndex = count - rows + i;
		//}
		if (pi.index == rowIndex)
		{
			gdi.DrawParagraph(paragraph[paragraphIndex].c_str(), pi.width, pi.position.x, pi.position.y, _printAlignment, i);
			break;
		}
	}
}

// Returns the text of each paragraph
bool Textbox::GetParagraphText(vector<wstring>& output)
{
	//________________________________________________ Get Window Text
	const int len = ::GetWindowTextLength(hWnd);
	if (len <=0 ) return true;
	wchar_t *text = new wchar_t[len+1];
	if (text == NULL) return false;
	wchar_t *buffer = new wchar_t[len+1];
	if (buffer == NULL)
	{
		if (text) delete [] text;
		return false;
	}
	::GetWindowText(hWnd, text, len+1);
	//_______________________________________________  Separate Text
	int i, j = 0;
	int count = 0;
	for(i=0; i<len+1; i++)
	{
		if (text[i] == '\r') continue;
		if (i==len)
		{
			buffer[j] = '\0';
			output.push_back(buffer);
			break;
		}
		if (text[i] == '\n') 
		{
			count ++;
			if (count == 1) continue;
			count = 0;
			buffer[j] = '\0';
			j = 0;
			output.push_back(buffer);
		}
		else
		{
			buffer[j++] = text[i];
		}
	}

	//_______________________________________________ Clean Up
	if (text) delete [] text;
	if (buffer) delete [] buffer;
	return true;
}

bool Textbox::CanUndo()
{
	return (::SendMessage(this->hWnd, EM_CANUNDO, 0, 0) != 0);
}

bool Textbox::Undo()
{
	return (::SendMessage(this->hWnd, EM_UNDO, 0, 0) != 0);
}

double Textbox::GetDouble()
{
	//if (::GetWindowTextLength(this->hWnd)<=0) return 0.0;
	//wchar_t sz[32];
	//::GetWindowText(this->hWnd, sz, 32);
	//sz[31]='\0';
	//return Sys::Convert::ToDouble(sz);
	return Sys::Convert::ToDouble(Text);
}

void Textbox::SetDouble(double value, const wchar_t* format)
{
	if (format==NULL) format = L"%g";
	Text = Sys::Convert::ToString(value, format);
}

void Textbox::SetDouble(double value)
{
	this->SetDouble(value, L"%g");
}

// Check for notification EN_MAXTEXT
void Textbox::SetMaxText(int nMaxCharacter)
{
	::SendMessage(this->hWnd, EM_SETLIMITTEXT, nMaxCharacter,  0L);
}

LRESULT Textbox::GetSelection(int& nStart, int& nEnd)
{
	return ::SendMessage(this->hWnd, EM_GETSEL, (WPARAM)&nStart, (LPARAM)&nEnd);
}

void Textbox::SelectAll()
{
	::SendMessage(this->hWnd, EM_SETSEL, (WPARAM)0, (LPARAM)-1);
}

// To select all SetSelection(0, -1)
// If the start is –1, any current selection is deselected.
LRESULT Textbox::SetSelection(int nStart, int nEnd)
{
	return ::SendMessage(this->hWnd, EM_SETSEL, (WPARAM)nStart, (LPARAM)nEnd);
}

void Textbox::ReplaceSelection(wchar_t* replaceWithThis, bool canBeUndone)
{
	BOOL undone = canBeUndone ? TRUE : FALSE;
	::SendMessage (this->hWnd, EM_REPLACESEL, undone, (LPARAM) replaceWithThis);
}

int Textbox::GetLineCount()
{
	return (int)::SendMessage(this->hWnd, EM_GETLINECOUNT, 0, 0);
}

void Textbox::SetReadOnly(bool readOnly)
{
	WPARAM p = readOnly ? TRUE : FALSE;
	::SendMessage(this->hWnd, EM_SETREADONLY, p, (LPARAM)0);
}

bool Textbox::GetReadOnly()
{
	if (::GetWindowLong(hWnd, GWL_STYLE) & ES_READONLY) return true;
	return false;
}

int Textbox::GetOffset(int nLine)
{
	return (int)::SendMessage(this->hWnd, EM_LINELENGTH, nLine, 0);
}

int Textbox::GetLineLength(int nLineIndex)
{
	int index = (int)::SendMessage(this->hWnd, EM_LINEINDEX, (WPARAM)nLineIndex, (LPARAM)0);
	return (int)::SendMessage(this->hWnd, EM_LINELENGTH, (WPARAM)index, (LPARAM)0);
}

int Textbox::ScrollCaret()
{
	return (int)::SendMessage(this->hWnd, EM_SCROLLCARET, 0, 0);
}

LRESULT Textbox::Scroll(WPARAM how) //SB_LINEDOWN, SB_LINEUP, SB_PAGEDOWN, SB_PAGEUP
{
	return ::SendMessage(this->hWnd, EM_SCROLL, how, (LPARAM)0);
}

bool Textbox::AppendText(wchar_t* pBuffer)
{
	if (maxTextLength==0)
	{
		maxTextLength = (int)::SendMessage(this->hWnd, EM_GETLIMITTEXT, (WPARAM)0, (LPARAM)0);
	}
	if (pBuffer==NULL) return false;
	int n = ::GetWindowTextLength(this->hWnd)+lstrlen(pBuffer)+1;
	if (n>=maxTextLength)
	{
		::SendMessage(this->hWnd, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
	}
	::SendMessage (this->hWnd, EM_SETSEL, (WPARAM) -1, (LPARAM) -1);
	//::SendMessage (this->hWnd, EM_SCROLLCARET, 0, 0);
	::SendMessage (this->hWnd, EM_REPLACESEL, FALSE, (LPARAM) pBuffer);
	::SendMessage (this->hWnd, EM_SCROLLCARET, 0, 0);
	return true;
}

int Textbox::GetMaxText() // Returns the MAXIMUM number of characters
{
	return (int)::SendMessage(this->hWnd, EM_GETLIMITTEXT, (WPARAM)0, (LPARAM)0);
}

LRESULT Textbox::SetCueBanner(wchar_t* cue) // Displays an initial hint, Requires Manifest and Unicode
{
	return ::SendMessage(this->hWnd, EM_SETCUEBANNER, (WPARAM)0, (LPARAM) cue);
}

// First line is index 0
bool Textbox::GetLine(wchar_t* pszResult, int lineIndex, int bufferSize)
{	
	if (lineIndex<0 || GetLineCount()<=lineIndex) return false;
	WORD &length = (WORD&)pszResult[0];
	length = bufferSize;
	const int result = (int)::SendMessage(this->hWnd, EM_GETLINE, lineIndex, (LPARAM)(const wchar_t *)pszResult);
	pszResult[result]='\0';
	return true;
}

wstring Textbox::GetLine(int lineIndex)
{	
	const int len = this->GetLineLength(lineIndex);
	wstring tmp;
	tmp.resize(len+1);
	if (this->GetLine((wchar_t*)tmp.data(), lineIndex, len+1)) return tmp;
	return L"Incorrect Line";
}


//_____________________________________________________________________PrintDoc
PrintDoc::PrintDoc(void)
{
	margin.top = 2000;
	margin.left = 1250;
	margin.right = 1250;
	margin.bottom = 1500;
	//
	paperSize.x = WPPD_LETTER_PAGEWIDTH_LU;
	paperSize.y = WPPD_LETTER_PAGEHEIGHT_LU;
	//
	Reset();
}

PrintDoc::~PrintDoc(void)
{
}

void PrintDoc::Reset(void)
{
	lstrcpy(documentName, L"Untitled");
	this->elementCount = 0;
	this->footer = NULL;
	this->footerHeight = 0;
	//
	for(int i=0; i<WIN_PRINTDOC_ELEMENTMAX; i++)
	{
		element[i]=NULL;
		elementHeight[i]=0;
		elementRepeat[i]=0;
	}
}

void PrintDoc::Create(const wchar_t* documentName)
{
	Reset();
	this->SetDocumentName(documentName);
}

bool PrintDoc::Add(int height, int repeatCount, Win::IPrint& iprint)
{
	if (elementCount==WIN_PRINTDOC_ELEMENTMAX) return false;
	element[elementCount] = &iprint;
	this->elementHeight[elementCount]=height;
	this->elementRepeat[elementCount]=repeatCount;
	elementCount++;
	return true;
}

void PrintDoc::SetFooter(int milimeterHeight, Win::IPrint& iprint)
{
	this->footerHeight = milimeterHeight;
	this->footer = &iprint;
}

//double PrintDoc::TransformToLogicUnits(double centimeters)
//{
//	return centimeters*WPPD_LETTER_PAGEWIDTH_LU/WPPD_LETTER_PAGEWIDTH_CM;
//}
//
//double PrintDoc::TransformToCentimeters(double logicUnits)
//{
//	return logicUnits*WPPD_LETTER_PAGEWIDTH_CM/WPPD_LETTER_PAGEWIDTH_LU;
//}

POINT PrintDoc::GetLetterPrintArea(bool isPortrait)
{
	POINT pt;
	if (isPortrait)
	{
		pt.x = 21590-1250-1250;
		pt.y = 27940-2000-1500;
	}
	else
	{
		pt.y = 21590-1250-1250;
		pt.x = 27940-2000-1500;
	}
	return pt;
}

int PrintDoc::GetRowCountPerLetterPage(bool isPortrait, int fontSize)
{
	POINT ptPrintArea = Win::PrintDoc::GetLetterPrintArea(isPortrait);
	int rowCount = (int)(ptPrintArea.y/(1.5*fontSize));
	return rowCount;
}

int PrintDoc::GetNextElementHeight(int in_element, int in_repeat, int height)
{
	if (elementCount==0) return 100000;
	int pageCount=0;
	int ielement, irepeat;
	int repeatCount=0;
	int currentHeight = 0;
	bool found = false;

	for(ielement=0; ielement<elementCount; ielement++)
	{
		repeatCount = this->elementRepeat[ielement];
		for(irepeat=0; irepeat<repeatCount; irepeat++)
		{
			if (found)
			{
				return elementHeight[ielement];
			}
			if (ielement==in_element && irepeat==in_repeat) found = true;
			if (currentHeight == 0) //_____________________________ the first one
			{
				currentHeight += this->elementHeight[ielement];
				if (elementHeight[ielement]>= height - footerHeight)
				{
					pageCount++;
					currentHeight = 0;
				}
			}
			else if (currentHeight+elementHeight[ielement]<height - footerHeight)
			{
				currentHeight += this->elementHeight[ielement];
			}
			else //__________________________________________ the last one
			{			
				pageCount++;
				currentHeight = 0;
				//
				currentHeight += this->elementHeight[ielement];
				if (elementHeight[ielement]>= height - footerHeight)
				{
					pageCount++;
					currentHeight = 0;
				}
			}

		}
	}		
	return 100000;
}

// Where width and height are specified on cmm (100 cmm = 1 mm)
BOOL PrintDoc::OnPrintPage(Win::Gdi& gdi, int page, int width, int height)
{
	if (elementCount==0) return TRUE;
	PrintInfo pi;
	int pageCount=0;
	int ielement, irepeat;
	int repeatCount=0;
	int currentHeight = 0;

	for(ielement=0; ielement<elementCount; ielement++)
	{
		repeatCount = this->elementRepeat[ielement];
		for(irepeat=0; irepeat<repeatCount; irepeat++)
		{
			pi.page = page-1;
			pi.index = irepeat;
			pi.width = width;
			pi.height = elementHeight[ielement];
			pi.position.x = 0;
			pi.pageWidth = width;
			pi.pageHeight = height;
			pi.isFirst = (irepeat==0);
			//pi.isLast = (irepeat==elementRepeat[ielement]-1); XXXPRINT
			pi.isLast = (irepeat==repeatCount-1);
			if (currentHeight == 0) //_____________________________ the first one
			{
				pi.position.y = 0;
				pi.isFirstOnPage = true;
				pi.isLastOnPage = (elementHeight[ielement]>= height - footerHeight);
				if (page-1 == pageCount) element[ielement]->Print(gdi, pi);
				currentHeight += this->elementHeight[ielement];
				if (pi.isLastOnPage)
				{
					pageCount++;
					currentHeight = 0;
				}
			}
			else if (currentHeight+elementHeight[ielement]<height - footerHeight)
			{
				pi.isFirstOnPage = false;
				pi.position.y = currentHeight;
				if (currentHeight+elementHeight[ielement]+GetNextElementHeight(ielement, irepeat, height)<height - footerHeight)
				{
					pi.isLastOnPage = false;
					if (page-1 == pageCount ) element[ielement]->Print(gdi, pi);
					currentHeight += this->elementHeight[ielement];
				}
				else
				{
					pi.isLastOnPage = true;
					if (page-1 == pageCount ) element[ielement]->Print(gdi, pi);	
					currentHeight += this->elementHeight[ielement];
					if (footer)
					{
						pi.index = 0;
						pi.isFirst = true;
						pi.isFirstOnPage = false;
						pi.isLast = true;
						pi.isLastOnPage = true;
						pi.position.y = height-footerHeight;
						pi.height = footerHeight;
						footer->Print(gdi, pi);
					}
				}
			}
			else //__________________________________________ the last one
			{			
				pageCount++;
				currentHeight = 0;
				//
				pi.position.y = 0;
				pi.isFirstOnPage = true;
				pi.isLastOnPage = (elementHeight[ielement]>= height - footerHeight);
				if (page-1 == pageCount) element[ielement]->Print(gdi, pi);
				currentHeight += this->elementHeight[ielement];
				if (pi.isLastOnPage)
				{
					pageCount++;
					currentHeight = 0;
				}
			}

		}
	}		
	return TRUE;
}

POINT PrintDoc::GetPaperSize(void)
{
	return paperSize;
}

void PrintDoc::SetPaperSize(const POINT paperSize)
{
	this->paperSize.x = paperSize.x;
	this->paperSize.y = paperSize.y;
}

POINT PrintDoc::GetPrintingAreaSize(void)
{
	POINT pt;
	pt.x = paperSize.x - margin.left - margin.right;
	pt.y = paperSize.y - margin.top - margin.bottom;
	return pt;
}

bool PrintDoc::IsPortraitOrientation(void) 
{
	return (paperSize.x<paperSize.y);
}

void PrintDoc::ResetCurrentPosition(void)
{
	this->currentPosition.x = 0;
	this->currentPosition.y = 0;
}

const wchar_t* PrintDoc::GetDocumentName()  //Override this function
{
	return this->documentName;
}

void PrintDoc::SetDocumentName(const wchar_t* name)
{
	lstrcpyn(this->documentName, documentName,WIN_PRINTDOC_NAMEMAX);
	this->documentName[WIN_PRINTDOC_NAMEMAX-1]='\0';
}

int PrintDoc::GetPageCount() //Override this function
{ 
	const POINT printingArea = this->GetPrintingAreaSize();
	const int height = printingArea.y;
	if (elementCount==0) return 1;
	int pageCount=1;
	int ielement, irepeat;
	int repeatCount=0;
	int currentHeight = 0;

	for(ielement=0; ielement<elementCount; ielement++)
	{
		repeatCount = this->elementRepeat[ielement];
		for(irepeat=0; irepeat<repeatCount; irepeat++)
		{
			if (currentHeight == 0) //_____________________________ the first one
			{
				currentHeight += this->elementHeight[ielement];
				if ((elementHeight[ielement]>= height - footerHeight))
				{
					pageCount++;
					currentHeight = 0;
				}
			}
			else if (currentHeight+elementHeight[ielement]<height - footerHeight)
			{
				currentHeight += this->elementHeight[ielement];
			}
			else
			{			
				pageCount++;
				currentHeight = 0;
				//
				currentHeight += this->elementHeight[ielement];
				if (elementHeight[ielement]>= height - footerHeight)
				{
					pageCount++;
					currentHeight = 0;
				}
			}
		}
	}	
	return pageCount;
}

void PrintDoc::SetOrientation(bool isPortrait)
{
	if (isPortrait)
	{
		paperSize.x = 21590;
		paperSize.y = 27940;
		//
		//m_rectMargin.top = 2000;
		//m_rectMargin.left = 1250;
		//m_rectMargin.right = 1250;
		//m_rectMargin.bottom = 1500;
	}
	else
	{
		paperSize.y = 21590;
		paperSize.x = 27940;
		//
		//m_rectMargin.left = 2000;
		//m_rectMargin.top = 1250;
		//m_rectMargin.bottom = 1250;
		//m_rectMargin.right = 1500;
	}
}

RECT PrintDoc::GetMargin(void)
{
	return margin;
}

void PrintDoc::SetMargin(RECT& margin)
{
	this->margin = margin;
}

//___________________________________________ PrintSeparator
PrintSeparator::PrintSeparator()
{
}

PrintSeparator::~PrintSeparator()
{
}

void PrintSeparator::Print(Win::Gdi& gdi, Win::PrintInfo pi)
{
}

//bool PrintSeparator::CopyToClipboard(HWND hWnd)
//{
//	return true;
//}

//_____________________________________________________________________PageDlg
PageDlg::PageDlg(void)
{
	ZeroMemory(&m_psd, sizeof(PAGESETUPDLG));
	m_psd.lStructSize = sizeof(PAGESETUPDLG);
	m_psd.hwndOwner   = NULL;
	m_psd.hDevMode    = NULL; // Don't forget to free or store hDevMode
	m_psd.hDevNames   = NULL; // Don't forget to free or store hDevNames
	//m_psd.Flags       = PSD_INTHOUSANDTHSOFINCHES | PSD_MARGINS | ;// 
					//PSD_ENABLEPAGEPAINTHOOK | PSD_DEFAULTMINMARGINS; 
	m_psd.Flags = PSD_MARGINS | PSD_INHUNDREDTHSOFMILLIMETERS | PSD_MINMARGINS;
	m_psd.rtMargin.top = 2000;
	m_psd.rtMargin.left = 1250;
	m_psd.rtMargin.right = 1250;
	m_psd.rtMargin.bottom = 1500;
	m_psd.rtMinMargin.top = 500;
	m_psd.rtMinMargin.left = 500;
	m_psd.rtMinMargin.bottom = 500;
	m_psd.rtMinMargin.right = 500;
	m_psd.lpfnPagePaintHook = NULL;//(LPPAGEPAINTHOOK)PaintHook;

	m_psd.ptPaperSize.x = 21590;
	m_psd.ptPaperSize.y = 27940;
}

POINT PageDlg::GetPaperSize()
{
	return m_psd.ptPaperSize;
}
	
void PageDlg::SetPaperSize(POINT& pt)
{
	m_psd.ptPaperSize = pt;
}

RECT PageDlg::GetMargin()
{
	return m_psd.rtMargin;
}

void PageDlg::SetMargin(RECT& rect)
{
	m_psd.rtMargin = rect;
}

void PageDlg::SetMinMargin(RECT& rect)
{
	m_psd.rtMinMargin = rect;
}

BOOL PageDlg::OpenPageSetupDlg(HWND hWndParent, Win::IPrintDoc* pIPrintDoc)
{
	//DEVMODE dm;

	Destructor();
	m_psd.hwndOwner = hWndParent;
	m_psd.ptPaperSize = pIPrintDoc->GetPaperSize();
	m_psd.rtMargin = pIPrintDoc->GetMargin();
	BOOL b  = PageSetupDlg(&m_psd);
	pIPrintDoc->SetMargin(m_psd.rtMargin);
	pIPrintDoc->SetPaperSize(m_psd.ptPaperSize);
	return b;
}

BOOL PageDlg::OpenPageSetupDlg(HWND hWndParent)
{
	Destructor();
	m_psd.hwndOwner = hWndParent;
	return PageSetupDlg(&m_psd);
}

void PageDlg::Destructor()
{
	if (m_psd.hDevMode != NULL) 
	{
		GlobalFree(m_psd.hDevMode); 
		m_psd.hDevMode = NULL;
	}

	if (m_psd.hDevNames != NULL) 
	{
		GlobalFree(m_psd.hDevNames);
		m_psd.hDevNames =NULL;
	}
}

PageDlg::~PageDlg(void)
{
	Destructor();
}

BOOL CALLBACK PageDlg::PaintHook(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{ 
    LPRECT lprc; 
    COLORREF crMargRect; 
    HDC hdc, hdcOld; 
 
    switch (uMsg) { 
 
        // Drawing the margin rectangle. 
        case WM_PSD_MARGINRECT: 
            hdc = (HDC) wParam; 
            lprc = (LPRECT) lParam; 
 
            // Get the system highlight color. 
            crMargRect = GetSysColor(COLOR_HIGHLIGHT); 
 
            // Create a dash-dot pen of the system highlight color and 
            // select it into the DC of the sample page. 
            hdcOld = (HDC)SelectObject(hdc, CreatePen(PS_DASHDOT, (int).5, crMargRect)); 
 
            // Draw the margin rectangle. 
            Rectangle(hdc, lprc->left, lprc->top, lprc->right, 
                lprc->bottom); 
 
            // Restore the previous pen to the DC. 
            SelectObject(hdc, hdcOld); 
            return TRUE; 
 
        default: 
            return FALSE; 
    } 
    return TRUE; 
} 

//_____________________________________________________________________PrintDlg
bool PrintDlg_::m_bUserAbort = false;
HWND PrintDlg_::m_hDlgCancel = NULL;
HWND PrintDlg_::m_hInfo = NULL;
PRINTDLG PrintDlg_::m_pd;

PrintDlg_::PrintDlg_(void)
{
	m_bUserAbort = false;
	m_hDlgCancel = NULL;
	m_pIPrintDocument = NULL;

	ZeroMemory((void*)&m_pd, sizeof(PRINTDLG));
	m_pd.lStructSize = sizeof (PRINTDLG);
	//m_pd.hwndOwner = NULL;
	//m_pd.hDevMode = NULL ;
	//m_pd.hDevNames = NULL ;
	//m_pd.hDC = NULL ;
	m_pd.Flags = PD_ALLPAGES | PD_COLLATE | PD_RETURNDC | PD_NOSELECTION;
	//m_pd.Flags = PD_ALLPAGES | PD_COLLATE | PD_RETURNDC;
	//m_pd.Flags = PD_ALLPAGES | PD_RETURNDC;
	//m_pd.Flags = PD_ALLPAGES | PD_USEDEVMODECOPIES;
	//m_pd.Flags = PD_PRINTSETUP;
	//m_pd.nFromPage = 1;
	//m_pd.nToPage = 1;
	//m_pd.nMinPage = 1;
	//m_pd.nMaxPage = 1;
	//m_pd.nCopies = 1;
	//m_pd.hInstance = NULL;
	//m_pd.lCustData = 0L;
	//m_pd.lpfnPrintHook = NULL;
	//m_pd.lpfnSetupHook = NULL;
	//m_pd.lpPrintTemplateName = NULL;
	//m_pd.lpSetupTemplateName = NULL;
	//m_pd.hPrintTemplate = NULL;
	//m_pd.hSetupTemplate  = NULL;

	m_nHorzRes = 0;
	m_nVertRes = 0;
	m_nHorzSize = 0;
	m_nVertSize = 0;
}

BOOL PrintDlg_::BeginDialog(HWND hWndParent, Win::IPrintDoc* pIPrintDoc)
{
	BOOL bOk = FALSE;
	m_pIPrintDocument = pIPrintDoc;

	m_bUserAbort = false;
	m_hDlgCancel = NULL;
	m_pd.nMinPage = 1;
	m_pd.nCopies = 1;
	m_pd.nFromPage = 1;
	m_pd.nMaxPage = m_pIPrintDocument->GetPageCount();
	m_pd.nToPage = m_pIPrintDocument->GetPageCount();
	m_pd.hwndOwner = hWndParent;
	m_pd.Flags = PD_ALLPAGES | PD_COLLATE | PD_RETURNDC | PD_NOSELECTION;
	bOk = PrintDlg(&m_pd);
	if (bOk)
	{	
		DLGTEMPLATE dlgTemplate;
		dlgTemplate.style = DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | DS_CENTER;
		dlgTemplate.x = 0;
		dlgTemplate.y = 0;
		dlgTemplate.cx = 150;
		dlgTemplate.cy = 80;
		dlgTemplate.dwExtendedStyle = 0;
		dlgTemplate.cdit = 0;

		HGLOBAL hGlobal = ::GlobalAlloc
		(
			GHND | GMEM_SHARE, 
			sizeof(DLGTEMPLATE)+3*sizeof(WORD) // DLGTEMPLATE + MENU + CLASS + TITLE
		);
		DLGTEMPLATE *pTemplate = (DLGTEMPLATE *)::GlobalLock(hGlobal);
		::memcpy((LPVOID)pTemplate, (const void*)&dlgTemplate, sizeof(DLGTEMPLATE));
		::GlobalUnlock(hGlobal);
		//
		UpdateDevInfo();
		::EnableWindow(hWndParent, FALSE);// Disable parent
		m_bUserAbort = false;
		m_hDlgCancel = CreateDialogIndirect(hInstance, pTemplate, hWndParent, PrintDlgProc);
		::SetWindowText(m_hDlgCancel, m_pIPrintDocument->GetDocumentName());
		SetAbortProc(m_pd.hDC, AbortProc);
		bOk = OnPrintDocument();
		if (hGlobal) ::GlobalFree(hGlobal);
	}
	::EnableWindow (hWndParent, TRUE) ;
	::DestroyWindow (m_hDlgCancel);
	m_hDlgCancel = NULL;
	Destructor();
	return bOk;
}

BOOL PrintDlg_::OnPrintDocument()
{
	static DOCINFO docInfo;
	int i = 0, iPage = 0, iTotalPages = 0, j = 0;
	bool bCollate = ((m_pd.Flags & PD_COLLATE)!=0);
	static RECT rect;

	rect.top = 0;
	rect.left = 0;
	rect.right = GetDeviceCaps(m_pd.hDC, PHYSICALWIDTH);
	rect.bottom = GetDeviceCaps(m_pd.hDC, PHYSICALHEIGHT);

	if (this->m_pIPrintDocument == NULL) return FALSE;

	//******************************************************** Start printing
	ZeroMemory((void*)&docInfo, sizeof(DOCINFO));
	docInfo.cbSize = sizeof(DOCINFO);
	docInfo.lpszDocName = m_pIPrintDocument->GetDocumentName();

	if (StartDoc (m_pd.hDC, &docInfo) <= 0) return FALSE;
//	if (StartDocPrinter(m_pd, 0, 
	const int pageCount = m_pIPrintDocument->GetPageCount(); // Forze to update document dimensions - do not delete

	for (i = 0; i < (bCollate ? m_pd.nCopies : 1); i++)
	{
		for (iPage = m_pd.nFromPage ; iPage <=m_pd.nToPage; iPage++)
		{
			for (j = 0 ; j < (bCollate ? 1: m_pd.nCopies ); j++)
			{
				this->UpdateCancelWindowInfo(iPage);
				if (StartPage (m_pd.hDC) < 0) return FALSE;
				m_pIPrintDocument->ResetCurrentPosition();
				//::GetTextMetrics(m_pd.hDC, &m_pPrintDocument->tm);
				if (OnPrintPage(m_pd.hDC, iPage) == FALSE) return FALSE;
				if (EndPage (m_pd.hDC) < 0) return FALSE;
				if (m_bUserAbort) return FALSE;
			}
		}
	}
	return (EndDoc (m_pd.hDC)>=0);
}

BOOL PrintDlg_::OnPrintPage(HDC hdc, int page)
{
	if (m_pIPrintDocument==NULL) FALSE;
	PAINTSTRUCT ps;
	ZeroMemory(&ps, sizeof(PAINTSTRUCT));
	ps.hdc = hdc;
	Win::Gdi gdi(ps, false);
	SIZE sizeWin, sizeView;

	gdi.SetMapMode(MM_ANISOTROPIC);
	gdi.SetWindowExtEx(m_pIPrintDocument->GetPaperSize().x, m_pIPrintDocument->GetPaperSize().y);
	if (m_pIPrintDocument->IsPortraitOrientation())
	{
		gdi.SetViewportExtEx
			(
				GetDeviceCaps(hdc, PHYSICALWIDTH),
				GetDeviceCaps(hdc, PHYSICALHEIGHT)
			);
	}
	else
	{
		gdi.SetViewportExtEx
			(
				GetDeviceCaps(hdc, PHYSICALHEIGHT),
				GetDeviceCaps(hdc, PHYSICALWIDTH)
			);
	}
	gdi.GetWindowExtEx(&sizeWin);
	gdi.GetViewportExtEx(&sizeView);

	gdi.SetWindowOrgEx
		(
			-m_pIPrintDocument->GetMargin().left + sizeWin.cx*GetDeviceCaps(hdc, PHYSICALOFFSETX)/sizeView.cx, 
			-m_pIPrintDocument->GetMargin().top + sizeWin.cy*GetDeviceCaps(hdc, PHYSICALOFFSETY)/sizeView.cy
		);

	gdi.SetViewportOrgEx(0, 0);
	int documentWidth = m_pIPrintDocument->GetPaperSize().x - m_pIPrintDocument->GetMargin().left - m_pIPrintDocument->GetMargin().right;
	int documentHeight = m_pIPrintDocument->GetPaperSize().y - m_pIPrintDocument->GetMargin().top - m_pIPrintDocument->GetMargin().bottom;

	
	if (m_pIPrintDocument->IsPortraitOrientation()==false)
	{
		gdi.SetWorldRotation(90.0, documentHeight, 0);
	}
	m_pIPrintDocument->ResetCurrentPosition();
	//::GetTextMetrics(gdi.GetHDC(), &m_pPrintDocument->tm);
	return m_pIPrintDocument->OnPrintPage(gdi, page, documentWidth, documentHeight);
}

void PrintDlg_::UpdateCancelWindowInfo(int nPage)
{
	wchar_t sz[255];
	wsprintf(sz, L"Printing page: %d", nPage);
	::SetWindowText(this->m_hInfo, sz);
}

BOOL CALLBACK PrintDlg_::PrintDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	RECT rect;

     switch (msg)
     {
     case WM_INITDIALOG :
		EnableMenuItem (GetSystemMenu (hDlg, FALSE), SC_CLOSE, MF_GRAYED);

		//******************************************************************** Cancel button
		rect.top = 50;
		rect.bottom = 65;
		rect.left = 50;
		rect.right = 100;
		MapDialogRect(hDlg, &rect);
		CreateWindowEx
			(
			0, L"BUTTON", L"Cancel", 
			WS_CHILD | WS_VISIBLE, 
			rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, hDlg, 
			(HMENU)100, hInstance, 0
			);
		//******************************************************************** Static
		rect.top = 20;
		rect.bottom = 40;
		rect.left = 10;
		rect.right = 140;
		MapDialogRect(hDlg, &rect);
		m_hInfo = CreateWindowEx
			(
			0, L"STATIC", L"Printing page 1 out of 1", 
			WS_CHILD | WS_VISIBLE | SS_CENTER, 
			rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, hDlg, 
			(HMENU)101, hInstance, 0
			);
		return TRUE ;
          
     case WM_COMMAND :
          m_bUserAbort = TRUE ;
		  ::EnableWindow (::GetParent (hDlg), TRUE) ;
		  ::DestroyWindow (hDlg) ;
		  m_hDlgCancel = NULL;
          return TRUE ;
     }
     return FALSE ;
}          

BOOL CALLBACK PrintDlg_::AbortProc(HDC hPrinterDC, int iCode)
{
     MSG msg ;
     
     while (!m_bUserAbort && PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
     {
          if (!m_hDlgCancel || !IsDialogMessage (m_hDlgCancel, &msg))
          {
               TranslateMessage (&msg) ;
               DispatchMessage (&msg) ;
          }
     }
     return !m_bUserAbort ;
}

void PrintDlg_::UpdateDevInfo()
{
	this->m_nHorzRes = GetDeviceCaps(m_pd.hDC, HORZRES);
	this->m_nVertRes = GetDeviceCaps(m_pd.hDC, VERTRES);
	this->m_nHorzSize = GetDeviceCaps(m_pd.hDC, HORZSIZE);
	this->m_nVertSize = GetDeviceCaps(m_pd.hDC, VERTSIZE);
}

BOOL PrintDlg_::OpenPrintSetupDlg(HWND hWndParent)
{
	m_pd.hwndOwner = hWndParent;
	m_pd.Flags = PD_PRINTSETUP;
	
	BOOL b = PrintDlg(&m_pd);
	UpdateDevInfo();
	Destructor();
	return b;
}

PrintDlg_::~PrintDlg_(void)
{
	Destructor();
}

void PrintDlg_::Destructor()
{
	if (m_pd.hDC)
	{
		DeleteDC(m_pd.hDC);
		m_pd.hDC = NULL;
		m_pd.hwndOwner = NULL;
	}

	if (m_pd.hDevMode != NULL) 
	{
		GlobalFree(m_pd.hDevMode); 
		m_pd.hDevMode = NULL;
	}

	if (m_pd.hDevNames != NULL) 
	{
		GlobalFree(m_pd.hDevNames);
		m_pd.hDevNames = NULL;
	}
}

//_____________________________________________________________________PrintPreview
bool PrintPreview::registered = false;

PrintPreview::PrintPreview(void)
{
	if (!registered)
	{
		this->RegisterClassEx(LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(WHITE_BRUSH));
		registered = true;
	}
	this->pIPrintDoc = NULL;
	page = 1;
}

PrintPreview::~PrintPreview(void)
{
}

int PrintPreview::GetCurrentPage(void) 
{
	return page;
}

void PrintPreview::SetCurrentPage(int page)
{
	if (1<=page && page<1000) 
	{
		this->page = page; 
		::InvalidateRect(hWnd, NULL, TRUE);
	}
}

void PrintPreview::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, false);
	e.returnValue = TRUE;

	if (pIPrintDoc==NULL) return;
	gdi.SetMapMode(MM_ISOTROPIC);
	gdi.SetWindowExtEx(pIPrintDoc->GetPaperSize().x, pIPrintDoc->GetPaperSize().y);
	gdi.SetViewportExtEx(width, height);
	gdi.SetWindowOrgEx(-pIPrintDoc->GetMargin().left, -pIPrintDoc->GetMargin().top);
	gdi.SetViewportOrgEx(0, 0);
	pIPrintDoc->ResetCurrentPosition();
	//::GetTextMetrics(gdi.GetHDC(), &pPrintDoc->tm);
	if (page > this->pIPrintDoc->GetPageCount()) page =1;
	pIPrintDoc->OnPrintPage
		(
			gdi, 
			page, 
			pIPrintDoc->GetPaperSize().x - pIPrintDoc->GetMargin().left - pIPrintDoc->GetMargin().right, 
			pIPrintDoc->GetPaperSize().y - pIPrintDoc->GetMargin().top - pIPrintDoc->GetMargin().bottom
		);
}

void PrintPreview::SetDoc(Win::IPrintDoc* pIPrintDoc)
{
	this->pIPrintDoc = pIPrintDoc;
	::InvalidateRect(hWnd, NULL, TRUE);
}

//_____________________________________________________________________PrintPreviewDlg
PrintPreviewDlg::PrintPreviewDlg(void)
{
	m_nPage = 1;
	m_nMaxPage = 1;
	m_rect.top = 0;
	m_rect.left = 0;
	m_rect.right = 200;
	m_rect.bottom = 200;
	m_pIPrintDocument = NULL;
	m_rectButton.bottom = 12;
	m_rectButton.left = 0;
	m_rectButton.right = 44;
	m_rectButton.top = 0;
	//
	PrintButtonText = L"Print";
	CloseButtonText = L"Close";
	PreviousButtonText = L"<< Previous";
	NextButtonText = L"Next >>";
	PageSetupButtonText = L"Page Setup";
	WindowText = L"Print Preview - Please set the paper size using the printer properties";
}

PrintPreviewDlg::~PrintPreviewDlg(void)
{
}

void PrintPreviewDlg::UpdateButtons()
{
	int page = this->m_printPreview.GetCurrentPage();
	int maxPage = m_pIPrintDocument->GetPageCount();
	if (maxPage==1)
	{
		btNext.Enabled = false;
		btPrev.Enabled = false;
		return;
	}
	btNext.Enabled = (page<maxPage);
	btPrev.Enabled = (1<page);
}

void PrintPreviewDlg::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, false);

	RECT rect;
	m_printPreview.GetRect(rect);
	Win::Gdi::Pen penLight(PS_SOLID, 1, RGB(210, 210, 210));
	Win::Gdi::Pen penShadow(PS_SOLID, 1, RGB(100, 100, 100));
	gdi.SelectPen_(penLight);
	gdi.Line(rect.left-1, rect.top-1, rect.right, rect.top-1);
	gdi.Line(rect.left-1, rect.top, rect.left-1, rect.bottom);
	gdi.SelectPen_(penShadow);
	gdi.Line(rect.left, rect.bottom, rect.right+1, rect.bottom);
	gdi.Line(rect.right, rect.top, rect.right, rect.bottom+1);
}

void PrintPreviewDlg::Window_Size(Win::Event& e)
{
	int nSpacing = (int)(m_rectButton.bottom*1.25); 
	int nPositionX = this->width - m_rectButton.right - (int)(m_rectButton.bottom*0.35) - ::GetSystemMetrics(SM_CXBORDER);
	int nPositionY = (int)(m_rectButton.bottom*0.25);

	//************************************************************************** Move buttons
	btPrint.Move(nPositionX, nPositionY, m_rectButton.right, m_rectButton.bottom, TRUE);
	nPositionY +=nSpacing;

	btPageSetup.Move(nPositionX, nPositionY, m_rectButton.right, m_rectButton.bottom, TRUE);
	nPositionY +=nSpacing;

	btClose.Move(nPositionX, nPositionY, m_rectButton.right, m_rectButton.bottom, TRUE);
	nPositionY +=nSpacing;

	btPrev.Move(nPositionX, nPositionY, m_rectButton.right, m_rectButton.bottom, TRUE);
	nPositionY +=nSpacing;

	btNext.Move(nPositionX, nPositionY, m_rectButton.right, m_rectButton.bottom, TRUE);
	nPositionY +=nSpacing;

	//nPositionY +=nSpacing;
	//btMsWord.Move(nPositionX, nPositionY, m_rectButton.right, m_rectButton.bottom, TRUE);
	//nPositionY +=nSpacing;

	//btMsExcel.Move(nPositionX, nPositionY, m_rectButton.right, m_rectButton.bottom, TRUE);
	//nPositionY +=nSpacing;

	Resize();
	this->SetReturnValue(TRUE);
	e.returnValue = TRUE;
}

BOOL PrintPreviewDlg::BeginDialog_(HWND hWndParent, Win::IPrintDoc* pIPrintDoc)
{
	m_pIPrintDocument = pIPrintDoc;

	Win::PrintPreviewDlg ppd;
	ppd.PrintButtonText = this->PrintButtonText;
	ppd.CloseButtonText= this->CloseButtonText;
	ppd.PreviousButtonText= this->PreviousButtonText;
	ppd.NextButtonText= this->NextButtonText;
	ppd.PageSetupButtonText= this->PageSetupButtonText;
	ppd.WindowText= this->WindowText;

	if (m_pIPrintDocument)
	{
		ppd.m_pageDlg.SetPaperSize(m_pIPrintDocument->GetPaperSize());
	}

	ppd.m_printPreview.SetDoc(pIPrintDoc);
	ppd.m_pIPrintDocument = pIPrintDoc;
	ppd.BeginDialog(hWndParent);
	return TRUE;
}

void PrintPreviewDlg::GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
{
	dlgTemplate.dwExtendedStyle = 0;
	dlgTemplate.style = DS_MODALFRAME | DS_CENTER | WS_MAXIMIZEBOX | WS_THICKFRAME |
		 WS_POPUP | WS_CAPTION | WS_SYSMENU | DS_FIXEDSYS | WS_CLIPCHILDREN;
	dlgTemplate.x = 0;
	dlgTemplate.y = 0;
	dlgTemplate.cx = 20;
	dlgTemplate.cy = 20;
	dlgTemplate.cdit = 0;
}

void PrintPreviewDlg::btPrint_Click(Win::Event& e)
{
	m_printDlg.BeginDialog(hWnd, this->m_pIPrintDocument);
}

void PrintPreviewDlg::btPageSetup_Click(Win::Event& e)
{
	m_pageDlg.OpenPageSetupDlg(hWnd, m_pIPrintDocument);
	Resize();
	::InvalidateRect(m_printPreview, NULL, TRUE);
	this->UpdateButtons();
}

void PrintPreviewDlg::btClose_Click(Win::Event& e)
{
	this->EndDialog(FALSE); // Returns FALSE
}

void PrintPreviewDlg::btPrev_Click(Win::Event& e)
{
	int page = this->m_printPreview.GetCurrentPage();
	page--;
	if (page<1) page = 1;
	this->m_printPreview.SetCurrentPage(page);
	UpdateButtons();
}

void PrintPreviewDlg::btNext_Click(Win::Event& e)
{
	int page = this->m_printPreview.GetCurrentPage();
	int maxPage = m_pIPrintDocument->GetPageCount();
	page++;
	if (page> maxPage) page = maxPage;
	this->m_printPreview.SetCurrentPage(page);
	UpdateButtons();
}

//void PrintPreviewDlg::btMsWord_Click(Win::Event& e)
//{
//	Win::FileDlg dlg;
//	dlg.Clear();
//	dlg.SetFilter(L"Word Document (*.docx)\0*.docx\0\0", 0, L"docx");
//	if (dlg.BeginDialog(hWnd, L"Export to MS Word", true) != TRUE ) return;
//
//	Win::HourGlassCursor hgc(true);
//	::CoInitialize(NULL);
//	try
//	{
//		IUnknownPtr application;
//		Com::CDispatchPtr disp;
//		
//		application.CreateInstance(L"Word.Application");
//		disp = application;
//		disp.Get(L"Documents").Invoke(L"Add");
//		int index = 0;
//		while(m_pIPrintDocument->CopyElementToClipboard(hWnd, index))
//		{
//			disp.Get(L"Selection").Invoke(L"Paste");
//			disp.Get(L"Selection").Invoke(L"TypeParagraph");
//			index++;
//		}
//		disp.Get(L"ActiveDocument").Invoke(L"SaveAs", dlg.GetFileNameFullPath());
//		disp.Invoke(L"Quit");
//	}
//	catch(_com_error e)
//	{
//		this->MessageBox(e.ErrorMessage(), L"MS Word", MB_OK | MB_ICONERROR);
//	}
//	::CoUninitialize();
//}

//void PrintPreviewDlg::btMsExcel_Click(Win::Event& e)
//{
//	Win::FileDlg dlg;
//	dlg.Clear();
//	dlg.SetFilter(L"Excel Document (*.xlsx)\0*.xlsx\0\0", 0, L"xlsx");
//	if (dlg.BeginDialog(hWnd, L"Export to MS Excel", true) != TRUE ) return;
//	Win::HourGlassCursor hgc(true);
//	::CoInitialize(NULL);
//	try
//	{
//		IUnknownPtr application;
//		Com::CDispatchPtr disp;
//		
//		application.CreateInstance(L"Excel.Application");
//		disp = application;
//		disp.Get(L"Workbooks").Invoke(L"Add");
//		int index = 0;
//		while(m_pIPrintDocument->CopyElementToClipboard(hWnd, index))
//		{
//			disp.Get(L"ActiveSheet").Invoke(L"Paste");
//			index++;
//		}
//		disp.Get(L"ActiveSheet").Invoke(L"SaveAs", dlg.GetFileNameFullPath());
//		disp.Invoke(L"Quit");
//	}
//	catch(_com_error e)
//	{
//		this->MessageBox(e.ErrorMessage(), L"MS Excel", MB_OK | MB_ICONERROR);
//	}
//	::CoUninitialize();
//}

bool PrintPreviewDlg::EventHandler(Win::Event& e)
{
	if (btPrint.IsEvent(e, BN_CLICKED)) {btPrint_Click(e); return true;}
	if (btPageSetup.IsEvent(e, BN_CLICKED)) {btPageSetup_Click(e); return true;}
	if (btClose.IsEvent(e, BN_CLICKED)) {btClose_Click(e); return true;}
	if (btPrev.IsEvent(e, BN_CLICKED)) {btPrev_Click(e); return true;}
	if (btNext.IsEvent(e, BN_CLICKED)) {btNext_Click(e); return true;}
	//if (btMsWord.IsEvent(e, BN_CLICKED)) {btMsWord_Click(e); return true;}
	//if (btMsExcel.IsEvent(e, BN_CLICKED)) {btMsExcel_Click(e); return true;}
	return false;
}

void PrintPreviewDlg::Resize()
{
	const int spacing = 6;
	Win::Gdi::PointF sizeInterior, sizeExterior;
	POINT point = m_pageDlg.GetPaperSize();
	const int buttonWidth = m_rectButton.right-m_rectButton.left;

	sizeInterior.x = (double)(point.x+spacing+0.5);
	sizeInterior.y = (double)(point.y+spacing+0.5);
	sizeExterior.x = (double)(width - buttonWidth - 4*spacing +0.5);
	sizeExterior.y = (double)(height-2*spacing+0.5);
	double scale = Win::PrintPreviewDlg::GetMaxScale(sizeInterior, sizeExterior);
	m_printPreview.Move
		(
			spacing, spacing, 
			(int)(m_pageDlg.GetPaperSize().x*scale), 
			(int)(m_pageDlg.GetPaperSize().y*scale), 
			TRUE
		);
}

// Returns the maximum scale so that the rectangle described by sizeInterior fits inside sizeExterior
double PrintPreviewDlg::GetMaxScale(const Win::Gdi::PointF& pfInterior, const Win::Gdi::PointF& pfExterior)
{
	double scale = pfExterior.x / pfInterior.x;
	if (scale*pfInterior.y < pfExterior.y) return scale;
	return pfExterior.y / pfInterior.y;
}

//INT_PTR PrintPreviewDlg::Create(LPDLGTEMPLATE pTemplate, HWND hWndParent)
//{
//	return Dialog::DialogBox__(hWndParent, pTemplate);
//}

void PrintPreviewDlg::Window_Open(Win::Event& e)
{
	this->MapDialogRect(&m_rectButton);

	font.Create(L"Arial", 14, false, false, false, false);
	//fontBold.Create(L"Arial", 15, true, false, false, false);

	//******************************************************************* Buttons
	btPrint.Create(0, PrintButtonText.c_str(), WS_CHILD | WS_TABSTOP | WS_VISIBLE, 
		0, 0, 0, 0, hWnd, WPPD_PRINT);
	btPageSetup.Create(0, PageSetupButtonText.c_str(), WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		0, 0, 0, 0, hWnd, WPPD_PAGESETUP);
	btClose.Create(0, CloseButtonText.c_str(), WS_CHILD | WS_TABSTOP | WS_VISIBLE, 
		0, 0, 0, 0, hWnd, WPPD_CLOSE);
	btPrev.Create(0, PreviousButtonText.c_str(), WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		0, 0, 0, 0, hWnd, WPPD_PREV);
	btNext.Create(0, NextButtonText.c_str(), WS_CHILD | WS_TABSTOP | WS_VISIBLE, 
		0, 0, 0, 0, hWnd, WPPD_NEXT);
	//btMsWord.Create(0, L"MS Word", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_OWNERDRAW | BS_CENTER | BS_VCENTER,
	//	0, 0, 0, 0, hWnd, WPPD_MSWORD);
	//btMsExcel.Create(0, L"MS Excel", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_OWNERDRAW | BS_CENTER | BS_VCENTER, 
	//	0, 0, 0, 0, hWnd, WPPD_MSEXCEL);
	m_printPreview.Create(0, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, WPPD_PRINTPREVIEW);
	//
	btPrint.Font = font;
	btPageSetup.Font = font;
	btClose.Font = font;
	btPrev.Font = font;
	btNext.Font = font;
	//btMsWord.Font = fontBold;
	//btMsExcel.Font = fontBold;
	////
	//btMsWord.BackColor = RGB(230, 230, 240);
	//btMsExcel.BackColor = RGB(230, 240, 230);
	////
	//btMsWord.TextColor = RGB(0, 0, 190);
	//btMsExcel.TextColor = RGB(0, 110, 0);
	//
	btPrint.SetFocus();

	//********************************************************************** Set initial dialog size
	int n = ::GetSystemMetrics(SM_CYCAPTION);
	this->SetText(WindowText.c_str());
	this->Move(n, n, ::GetSystemMetrics(SM_CXSCREEN)-2*n, ::GetSystemMetrics(SM_CYSCREEN)-3*n, TRUE);
	this->UpdateButtons();
	e.returnValue = TRUE; // We return false because we set focus manually
}

//_____________________________________________________________________ Scintilla
#ifdef SCINTILLA_H
Scintilla::Scintilla()
{	
	//if (!this->isRegistered)
	//{
	//	 
	//	this->RegisterClassEx(
	//		LoadCursor(NULL, IDC_ARROW), // Cursor: IDC_IBEAM, IDC_WAIT, IDC_CROSS, ...
	//		(HBRUSH)(COLOR_BTNFACE+1)); //Background:  (HBRUSH)(COLOR_WINDOW+1)), ::GetStockObject(BLACK_BRUSH)...
	//	this->isRegistered = true;
	//}
	if (dll.Load(L"SciLexer.DLL") == false)
	{
		::MessageBox(NULL, L"Unable to load SciLexer.dll", L"Scintilla", MB_OK | MB_ICONERROR);
	}
}

Scintilla::~Scintilla()
{
}

bool Scintilla::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg != WM_NOTIFY) return false;
	NMHDR* pNMHDR= (LPNMHDR)e.lParam; 
	if (pNMHDR->hwndFrom!=this->GetHWND()) return false;
	if (notification != WIN_ALL_EVENTS) return false;
	return true;
}

void Scintilla::Print(Win::Gdi& gdi, Win::PrintInfo pi)
{
	const int offsetX = (int)(pi.height*0.3+0.5);
	const int offsetY = (int)(pi.height*0.1+0.5);

	Win::Gdi::Pen pen;
	//___________________________________________________________________ Font
	Win::Gdi::Font font;
	const int fontSize = (int)(pi.height*0.8+0.5);
	font.Create(L"Arial", fontSize, false, false, false, false),
	//font.Create(gdi.GetHDC(), L"Arial", 8, false, false, false);
	gdi.SelectFont_(font);
	gdi.SetTextColor(RGB(0, 0, 0));
	pi.position.x = 0;

	const int lineCount = GetLineCount();
	gdi.SetTextAlign(TA_LEFT | TA_TOP);
	int i = 0;
	wstring lineText;
	
	for(i= 0; i<lineCount; i++)
	{
		if (pi.index == i)
		{
			GetLine(i, lineText);
			const int length = lineText.length();
			int spaces = 0;
			int letters = 0;
			for(int j = 0; j < length; j++)
			{
				if (lineText[j] == ' ')
				{
					spaces++;
					continue;
				}
				if (lineText[j] == '\t')
				{
					spaces+=3;
					continue;
				}
				letters++;
				break;
			}
			if (letters == 0) break;
			Sys::TextAssistant::RemoveTrailingSpaces(lineText);
			if (lineText.length() == 0) return;
			if (spaces == 0)
			{
				gdi.TextOut(pi.position.x, pi.position.y, lineText.c_str());
			}
			else
			{
				gdi.TextOut(pi.position.x+spaces*fontSize/2, pi.position.y, lineText.c_str());
			}
			break;
		}
	}
}

void Scintilla::SetReadOnly(bool readOnly)
{
	::SendMessage(hWnd, SCI_SETREADONLY, (WPARAM)readOnly, (LPARAM)0);
}

bool Scintilla::GetReadOnly()
{
	return (::SendMessage(hWnd, SCI_GETREADONLY, (WPARAM)0, (LPARAM)0) != 0);
}

bool Scintilla::IsModified()
{
	return (::SendMessage(hWnd, SCI_GETMODIFY, (WPARAM)0, (LPARAM)0) != 0);
}

//This message tells Scintilla that the current state of the document is unmodified. 
//This is usually done when the file is saved or loaded, hence the name "save point". 
//As Scintilla performs undo and redo operations, it notifies the container that it has entered 
//or left the save point with SCN_SAVEPOINTREACHED and SCN_SAVEPOINTLEFT notification messages, 
//allowing the container to know if the file should be considered dirty or not.
void Scintilla::SetSavePoint()
{
	::SendMessage(hWnd, SCI_SETSAVEPOINT, (WPARAM)0, (LPARAM)0);
}


//This message causes a list to be displayed. lenEntered is the number of characters of the word already 
//entered and list is the list of words separated by separator characters. The initial separator character is 
//a space but this can be set or got with SCI_AUTOCSETSEPARATOR and SCI_AUTOCGETSEPARATOR.
void Scintilla::AutoCompletionShow(int lenEntered, const char *list)
{
	::SendMessage(hWnd, SCI_AUTOCSHOW, (WPARAM)lenEntered, (LPARAM)list);
}


//This message cancels any displayed autocompletion list. When in autocompletion mode, 
//the list should disappear when the user types a character that can not be part of the autocompletion, 
//such as '.', '(' or '[' when typing an identifier. A set of characters that will cancel autocompletion 
//can be specified with SCI_AUTOCSTOPS.
void Scintilla::AutoCompletionCancel()
{
	::SendMessage(hWnd, SCI_AUTOCCANCEL, (WPARAM)0, (LPARAM)0);
}

bool Scintilla::IsAutoCompletionActive()
{
	return (::SendMessage(hWnd, SCI_AUTOCACTIVE, (WPARAM)0, (LPARAM)0) != 0);
}

//This returns the value of the current position when SCI_AUTOCSHOW started display of the list.
int Scintilla::AutoCompletionPositionStart()
{
	return ::SendMessage(hWnd, SCI_AUTOCPOSSTART, (WPARAM)0, (LPARAM)0);
}

//This message triggers autocompletion. This has the same effect as the tab key.
void Scintilla::AutoCompletionComplete()
{
	::SendMessage(hWnd, SCI_AUTOCCOMPLETE, (WPARAM)0, (LPARAM)0);
}

//The chars argument is a string containing a list of characters that will automatically cancel 
//the autocompletion list. When you start the editor, this list is empty.
void Scintilla::AutoCompletionStop(const char *chars)
{
	::SendMessage(hWnd, SCI_AUTOCSTOPS, (WPARAM)0, (LPARAM)chars);
}

//This message selects an item in the autocompletion list. It searches the list of words 
//for the first that matches select. By default, comparisons are case sensitive, but you can change 
//this with SCI_AUTOCSETIGNORECASE. The match is character by character for 
//the length of the select string. That is, if select is "Fred" it will match "Frederick" if this 
//is the first item in the list that begins with "Fred". If an item is found, it is selected. 
//If the item is not found, the autocompletion list closes if auto-hide is true (see SCI_AUTOCSETAUTOHIDE).
void Scintilla::AutoCompletionSelect(const char *chars)
{
	::SendMessage(hWnd, SCI_AUTOCSELECT, (WPARAM)0, (LPARAM)chars);
}

//It returns the current selection index
int Scintilla::AutoCompletionGetCurrent()
{
	return ::SendMessage(hWnd, SCI_AUTOCGETCURRENT, (WPARAM)0, (LPARAM)0);
}

bool Scintilla::GetAutoCompletionIgnoreCase()
{
	return (::SendMessage(hWnd, SCI_AUTOCGETIGNORECASE, (WPARAM)0, (LPARAM)0) != 0);
}

void Scintilla::SetAutoCompletionIgnoreCase(bool ignoreCase)
{
	if (ignoreCase == true)
	{
		::SendMessage(hWnd, SCI_AUTOCSETIGNORECASE, (WPARAM)1, (LPARAM)0);
	}
	else
	{
		::SendMessage(hWnd, SCI_AUTOCSETIGNORECASE, (WPARAM)0, (LPARAM)0);
	}
}

int Scintilla::GetAutoCompletionMaxWidth()
{
	return ::SendMessage(hWnd, SCI_AUTOCGETMAXWIDTH, (WPARAM)0, (LPARAM)0);
}

void Scintilla::SetAutoCompletionMaxWidth(int width)
{
	::SendMessage(hWnd, SCI_AUTOCSETMAXWIDTH, (WPARAM)width, (LPARAM)0);
}

int Scintilla::GetAutoCompletionMaxHeight()
{
	return ::SendMessage(hWnd, SCI_AUTOCGETMAXHEIGHT, (WPARAM)0, (LPARAM)0);
}

void Scintilla::SetAutoCompletionMaxHeight(int height)
{
	::SendMessage(hWnd, SCI_AUTOCSETMAXHEIGHT, (WPARAM)height, (LPARAM)0);
}

// margin: 0, 1, 2, 3 or 4
// type: SC_MARGIN_NUMBER, SC_MARGIN_SYMBOL, SC_MARGIN_TEXT, SC_MARGIN_RTEXT, ...
void Scintilla::SetMarginType(int marginIndex, int type)
{
	::SendMessage(hWnd, SCI_SETMARGINTYPEN, (WPARAM)marginIndex, (LPARAM)type);
}

int Scintilla::GetMarginType(int marginIndex)
{
	return ::SendMessage(hWnd, SCI_GETMARGINTYPEN, (WPARAM)marginIndex, (LPARAM)0);
}

void Scintilla::SetMarginWidth(int marginIndex, int widthPixels)
{
	::SendMessage(hWnd, SCI_SETMARGINWIDTHN, (WPARAM)marginIndex, (LPARAM)widthPixels);
}

int Scintilla::GetMarginWidth(int marginIndex)
{
	return ::SendMessage(hWnd, SCI_GETMARGINWIDTHN, (WPARAM)marginIndex, (LPARAM)0);
}

//This returns the pixel width of a string drawn in the given styleNumber which can be used, 
//for example, to decide how wide to make the line number margin in order to display a given number of numerals.
int Scintilla::TextWidth(int styleNumber, const char *text)
{
	return ::SendMessage(hWnd, SCI_TEXTWIDTH, (WPARAM)styleNumber, (LPARAM)text);
}

void Scintilla::New()
{
	this->ClearAll();
	this->EmptyUndoBuffer();
	this->SetSavePoint();
}

void Scintilla::ClearAll()
{
	::SendMessage(hWnd, SCI_CLEARALL, 0, 0);
}

//This command tells Scintilla to forget any saved undo or redo history. It also sets the save point to the 
//start of the undo buffer, so the document will appear to be unmodified. 
//This does not cause the SCN_SAVEPOINTREACHED notification to be sent to the container.
void Scintilla::EmptyUndoBuffer()
{
	::SendMessage(hWnd, EM_EMPTYUNDOBUFFER, 0, 0);
}

void Scintilla::Cancel()
{
	::SendMessage(hWnd, SCI_CANCEL, 0, 0);
}

void Scintilla::SetUndoCollection(bool collectInformation)
{
	::SendMessage(hWnd, SCI_SETUNDOCOLLECTION, (WPARAM)collectInformation, (LPARAM)0);
}

void Scintilla::AddText(int length, const wchar_t* text)
{
	::SendMessage(hWnd, SCI_SETUNDOCOLLECTION, (WPARAM)length, reinterpret_cast<LPARAM>(static_cast<const wchar_t *>(text)));
}

void Scintilla::GoToPosition(int position)
{
	::SendMessage(hWnd, SCI_GOTOPOS, (WPARAM)position, (LPARAM)0);
}

void Scintilla::SetCurrentPostion(int position)
{
	::SendMessage(hWnd, SCI_SETCURRENTPOS, (WPARAM)position, (LPARAM)0);
}

int Scintilla::GetCurrentPosition()
{
	return ::SendMessage(hWnd, SCI_GETCURRENTPOS, (WPARAM)0, (LPARAM)0);
}

void Scintilla::CommentOut()
{
	if (IsSelectionEmpty() == true) return;
	const int lineStart = GetSelectionStartLine();
	const int lineEnd = GetSelectionEndLine();
	if (lineStart < 0) return;
	if (lineEnd < 0) return;
	if (lineStart > lineEnd) return;
	int line;
	string text;
	string newText;
	for(line = lineStart; line <= lineEnd; line++)
	{
		GetLine(line, text);
		newText += "//";
		newText += text;
		if (line != lineEnd) newText += "\r\n";
	}
	ReplaceSelection(newText.c_str());
}

void Scintilla::Uncomment()
{
	if (IsSelectionEmpty() == true) return;
	const int lineStart = GetSelectionStartLine();
	const int lineEnd = GetSelectionEndLine();
	if (lineStart < 0) return;
	if (lineEnd < 0) return;
	if (lineStart > lineEnd) return;
	int line;
	string text;
	string newText;
	size_t npos;
	for(line = lineStart; line <= lineEnd; line++)
	{
		GetLine(line, text);
		npos = text.find_first_of("//");
		if (npos != std::string::npos) text.erase(npos, 2); 
		newText += text;
		if (line != lineEnd) newText += "\r\n";
	}
	ReplaceSelection(newText.c_str());
}

void Scintilla::Replace(const wchar_t* originalText, const wchar_t* newText)
{
	if (GetTextLength() <= 0) return;
	wstring code;
	GetText(code);
	Sys::TextAssistant::ReplaceWord(code, originalText, newText, true);
	SetText(code.c_str());
}

//This removes any selection and sets the caret at the start of line number line and scrolls the view (if needed) to make it visible. 
//The anchor position is set the same as the current position. If line is outside the lines in the document (first line is 0), 
//the line set is the first or last.
void Scintilla::GoToLine(int line)
{
	::SendMessage(hWnd, SCI_GOTOLINE, (WPARAM)line, (LPARAM)0);
}

int Scintilla::GetTextLength()
{
	return (int)::SendMessage(hWnd, SCI_GETLENGTH, (WPARAM)0, (LPARAM)0);
}

void Scintilla::GetText(int length, char*text)
{
	::SendMessage(hWnd, SCI_GETTEXT, length, (LPARAM)text);
}

void Scintilla::GetText(wstring& text)
{
	const int len =  (int)::SendMessage(hWnd, SCI_GETLENGTH, (WPARAM)0, (LPARAM)0);
	if (len == 0)
	{
		text.clear();
		return;
	}
	char * input = new char[len+1];
	if (input == NULL)
	{
		text.clear();
		return;
	}
	::SendMessage(hWnd, SCI_GETTEXT, len+1, (LPARAM)input);
	input[len] = '\0';
	Sys::Convert::StringToWstring(input, text);
	if (input != NULL) delete [] input;
}

void Scintilla::GetTextRange(int posStart, int posEnd, wstring& text)
{
	//_______________________________________ compute length
	const int len = (posEnd-posStart+1) + 1;
	if (len <= 0)
	{
		text.clear();
		return;
	}
	Sci_TextRange tr;
	tr.chrg.cpMin = posStart;
	tr.chrg.cpMax = posEnd;
	//_______________________________________ memory allocation
	tr.lpstrText  = new char[len];
	if (tr.lpstrText== NULL)
	{
		text.clear();
		return;
	}
	::SendMessage(hWnd, SCI_GETTEXTRANGE, (WPARAM)0, (LPARAM)&tr);
	Sys::Convert::StringToWstring(tr.lpstrText, text);
	//_______________________________________ release memory
	if (tr.lpstrText != NULL) delete [] tr.lpstrText;
}

void Scintilla::SetText(const wchar_t* text)
{
	string tmp;
	Sys::Convert::WstringToString(text, tmp);
	::SendMessage(hWnd, SCI_SETTEXT, (WPARAM)0, (LPARAM)tmp.c_str());
}

void Scintilla::Undo()
{
	::SendMessage(hWnd, SCI_UNDO, 0, 0);
}

bool Scintilla::CanUndo()
{
	return (::SendMessage(hWnd, SCI_CANUNDO, (WPARAM)0, (LPARAM)0)==1);
}

void Scintilla::Redo()
{
	::SendMessage(hWnd, SCI_REDO, 0, 0);
}

bool Scintilla::CanRedo()
{
	return (::SendMessage(hWnd, SCI_CANREDO, (WPARAM)0, (LPARAM)0)==1);
}

void Scintilla::Cut()
{
	::SendMessage(hWnd, SCI_CUT, 0, 0);
}

void Scintilla::Copy()
{
	::SendMessage(hWnd, SCI_COPY, 0, 0);
}

void Scintilla::Paste()
{
	::SendMessage(hWnd, SCI_PASTE, 0, 0);
}

void Scintilla::Clear()
{
	::SendMessage(hWnd, SCI_CLEAR, 0, 0);
}

//Send these two messages to Scintilla to mark the beginning and end of a set of operations that you want 
//to undo all as one operation but that you have to generate as several operations. Alternatively, 
//you can use these to mark a set of operations that you do not want to have combined 
//with the preceding or following operations if they are undone.
void Scintilla::BeginUndoAction()
{
	::SendMessage(hWnd, SCI_BEGINUNDOACTION, 0, 0);
}

//Send these two messages to Scintilla to mark the beginning and end of a set of operations that you want 
//to undo all as one operation but that you have to generate as several operations. Alternatively, 
//you can use these to mark a set of operations that you do not want to have combined 
//with the preceding or following operations if they are undone.
void Scintilla::EndUndoAction()
{
	::SendMessage(hWnd, SCI_ENDUNDOACTION, 0, 0);
}

bool Scintilla::CanPaste()
{
	return (::SendMessage(hWnd, SCI_CANPASTE, (WPARAM)0, (LPARAM)0)==1);
}

//This selects all the text in the document. The current position is not scrolled into view.
void Scintilla::SelectAll()
{
	::SendMessage(hWnd, SCI_SELECTALL, (WPARAM)0, (LPARAM)0);
}

//These set the selection based on the assumption that the anchor position is less than the current position. 
//They do not make the caret visible. The table shows the positions of the anchor and the current position after using these messages.
void Scintilla::SetSelectionStart(int position)
{
	::SendMessage(hWnd, SCI_SETSELECTIONSTART, (WPARAM)position, (LPARAM)0);
}

void Scintilla::SetSelectionEnd(int position)
{
	::SendMessage(hWnd, SCI_SETSELECTIONEND, (WPARAM)position, (LPARAM)0);
}

void Scintilla::SelectLine(int line)
{
	const int posStart = PositionFromLine(line);
	if (posStart < 0) return;
	const int posEnd = GetLineEndPosition(line);
	if (posStart>posEnd) return;
	SetSelectionStart(posStart);
	SetSelectionEnd(posEnd);
}

//It returns the start of the selection without regard to which end is the current position and which is the anchor. 
//It returns the smaller of the current position or the anchor position. 
int Scintilla::GetSelectionStart()
{
	return ::SendMessage(hWnd, SCI_GETSELECTIONSTART, (WPARAM)0, (LPARAM)0);
}

//It returns the end of the selection without regard to which end is the current position and which is the anchor. 
//It returns the larger of the current position or the anchor position. 
int Scintilla::GetSelectionEnd()
{
	return ::SendMessage(hWnd, SCI_GETSELECTIONEND, (WPARAM)0, (LPARAM)0);
}

bool Scintilla::IsSelectionEmpty()
{
	const int startPosition = ::SendMessage(hWnd, SCI_GETSELECTIONSTART, (WPARAM)0, (LPARAM)0);
	const int endPosition = ::SendMessage(hWnd, SCI_GETSELECTIONEND, (WPARAM)0, (LPARAM)0);
	if (startPosition < 0) return true;
	if (endPosition < 0) return true;
	if (startPosition == endPosition) return true;
	if (startPosition > endPosition) return true;
	return false;
}

void Scintilla::GetSelectedText(wstring& text)
{
	const int len = ::SendMessage(hWnd, SCI_GETSELTEXT, (WPARAM)0, (LPARAM)0);
	if (len <= 0)
	{
		text.clear();
		return;
	}
	char* buffer = new char[len+1];
	::SendMessage(hWnd, SCI_GETSELTEXT, (WPARAM)0, (LPARAM)buffer);
	Sys::Convert::StringToWstring(buffer, text);
	//const int startPos = ::SendMessage(hWnd, SCI_GETSELECTIONSTART, (WPARAM)0, (LPARAM)0);
	//const int endPos = ::SendMessage(hWnd, SCI_GETSELECTIONEND, (WPARAM)0, (LPARAM)0);
	//if (startPos < 0)
	//{
	//	text.clear();
	//	return;
	//}
	//if (endPos < 0)
	//{
	//	text.clear();
	//	return;
	//}
	//if (startPos > endPos)
	//{
	//	text.clear();
	//	return;
	//}
	//GetTextRange(startPos, endPos, text);
}

//The return value is 0 if pos <= 0. The return value is the last line if pos is beyond the end of the document.
int Scintilla::LineFromPosition(int position)
{
	return ::SendMessage(hWnd, SCI_LINEFROMPOSITION, (WPARAM)position, (LPARAM)0);
}

int Scintilla::GetSelectionStartLine()
{
	const int pos = GetSelectionStart();
	return LineFromPosition(pos);
}

int Scintilla::GetSelectionEndLine()
{
	const int pos = GetSelectionEnd();
	return LineFromPosition(pos);
}

//This returns the document position that corresponds with the start of the line. 
//If line is negative, the position of the line holding the start of the selection is returned. 
//If line is greater than the lines in the document, the return value is -1. 
//If line is equal to the number of lines in the document (i.e. 1 line past the last line), the return value is the end of the document.
int Scintilla::PositionFromLine(int line)
{
	return ::SendMessage(hWnd, SCI_POSITIONFROMLINE, (WPARAM)line, (LPARAM)0);
}

//This returns the position at the end of the line, before any line end characters. 
//If line is the last line in the document (which does not have any end of line characters), 
//the result is the size of the document. If line is negative or line >= SCI_GETLINECOUNT(), the result is undefined
int Scintilla::GetLineEndPosition(int line)
{
	return ::SendMessage(hWnd, SCI_GETLINEENDPOSITION, (WPARAM)line, (LPARAM)0);
}

int Scintilla::GetLineCount()
{
	return ::SendMessage(hWnd, SCI_GETLINECOUNT, (WPARAM)0, (LPARAM)0);
}

////Selects the specified line
//void Scintilla::SelectLine(int line)
//{
//	const int positionBegin = PositionFromLine(line);
//	if (positionBegin < 0) return;
//	if (positionBegin >= GetLineCount()) return;
//	const int positionEnd =GetLineEndPosition(line)
//}

int Scintilla::LineLength(int line)
{
	return ::SendMessage(hWnd, SCI_LINELENGTH, (WPARAM)line, (LPARAM)0);
}

void Scintilla::GetLine(int line, wstring& text)
{
	const int len = ::SendMessage(hWnd, SCI_LINELENGTH, (WPARAM)line, (LPARAM)0);
	//if (len == 2) // \r\n
	//{
	//	text.clear();
	//	return;
	//}
	char* tmp = new char[len+1];
	if (tmp == NULL) return;
	::SendMessage(hWnd, SCI_GETLINE, (WPARAM)line, (LPARAM)tmp);
	tmp[len] = '\0';
	Sys::Convert::StringToWstring(tmp, text);
	if (tmp != NULL) delete [] tmp;
	//_____________________________________________ Remove \r or \n
	int wlen = text.length();
	if (wlen>1)
	{
		if (text[wlen-1] == '\n' || text[wlen-1] == '\r') text.resize(wlen-1);
	}
	//
	wlen = text.length();
	if (wlen>1)
	{
		if (text[wlen-1] == '\n' || text[wlen-1] == '\r') text.resize(wlen-1);
	}
}

void Scintilla::GetLine(int line, string& text)
{
	const int len = ::SendMessage(hWnd, SCI_LINELENGTH, (WPARAM)line, (LPARAM)0);
	if (len == 2) // \r\n
	{
		text.clear();
		return;
	}
	text.resize(len+1);
	::SendMessage(hWnd, SCI_GETLINE, (WPARAM)line, (LPARAM)text.c_str());
	text.resize(len);
	//_____________________________________________ Remove \r or \n
	int wlen = text.length();
	if (wlen>1)
	{
		if (text[wlen-1] == '\n' || text[wlen-1] == '\r') text.resize(wlen-1);
	}
	//
	wlen = text.length();
	if (wlen>1)
	{
		if (text[wlen-1] == '\n' || text[wlen-1] == '\r') text.resize(wlen-1);
	}
}

//This fills the buffer defined by text with the contents of the nominated line (lines start at 0). 
//The buffer is NOT terminated by a \0 character
void Scintilla::GetLine(int line, char * text)
{
	::SendMessage(hWnd, SCI_GETLINE, (WPARAM)line, (LPARAM)text);
}

// Returns the text and the text length
int Scintilla::GetCurrentLine(char * text)
{
	const int len = ::SendMessage(hWnd, SCI_GETCURLINE, (WPARAM)0, (LPARAM)0)+1;
	::SendMessage(hWnd, SCI_GETCURLINE, (WPARAM)len, (LPARAM)text);
	return len;
}

void Scintilla::GetCurrentLine(wstring& text)
{
	const int len = ::SendMessage(hWnd, SCI_GETCURLINE, (WPARAM)0, (LPARAM)0)+1;
	char *tmp = new char[len];
	if (tmp == NULL) return;
	::SendMessage(hWnd, SCI_GETCURLINE, (WPARAM)len, (LPARAM)tmp);
	Sys::Convert::StringToWstring(tmp, text);
	if (tmp != NULL) delete [] tmp;
}

void Scintilla::ReplaceSelection(const char* text)
{
	::SendMessage(hWnd, SCI_REPLACESEL, (WPARAM)0, (LPARAM)text);
}

//sclex: SCLEX_CONTAINER, SCLEX_NULL, SCLEX_PYTHON, SCLEX_CPP, SCLEX_HTML,...
void Scintilla::SetLexer(int sclex)
{
	::SendMessage(hWnd, SCI_SETLEXER, (WPARAM)sclex, (LPARAM)0);
}

void Scintilla::SetKeyWords(int keyWordSet, const char *keyWordList)
{
	if (keyWordSet > KEYWORDSET_MAX) return;
	::SendMessage(hWnd, SCI_SETKEYWORDS, (WPARAM)keyWordSet, (LPARAM)keyWordList);
}

//styleNumber = SCE_C_DEFAULT
void Scintilla::SetStyleFore(int styleNumber, COLORREF color)
{
	::SendMessage(hWnd, SCI_STYLESETFORE, (WPARAM)styleNumber, (LPARAM)color);
}

//styleNumber = SCE_C_DEFAULT
void Scintilla::SetStyleBack(int styleNumber, COLORREF color)
{
	::SendMessage(hWnd, SCI_STYLESETBACK, (WPARAM)styleNumber, (LPARAM)color);
}

//styleNumber = SCE_C_DEFAULT
void Scintilla::SetStyleSize(int styleNumber, int sizeInPoints)
{
	::SendMessage(hWnd, SCI_STYLESETSIZE, (WPARAM)styleNumber, (LPARAM)sizeInPoints);
}

//styleNumber = SCE_C_DEFAULT
int Scintilla::GetStyleSize(int styleNumber)
{
	return ::SendMessage(hWnd, SCI_STYLESETSIZE, (WPARAM)styleNumber, (LPARAM)0);
}

//styleNumber = SCE_C_DEFAULT
void Scintilla::SetStyleFont(int styleNumber, const char* fontName)
{
	::SendMessage(hWnd, SCI_STYLESETFONT, (WPARAM)styleNumber, (LPARAM)fontName);
}

//styleNumber = SCE_C_DEFAULT
// buffer returns the font name
void Scintilla::GetStyleFont(int styleNumber, char* buffer)
{
	::SendMessage(hWnd, SCI_STYLEGETFONT, (WPARAM)styleNumber, (LPARAM)buffer);
}

//styleNumber = SCE_C_DEFAULT
void Scintilla::SetStyle(int styleNumber, COLORREF fore, COLORREF back, int sizeInPoints, const char* fontName)
{
	::SendMessage(hWnd, SCI_STYLESETFORE, (WPARAM)styleNumber, (LPARAM)fore);
	::SendMessage(hWnd, SCI_STYLESETBACK, (WPARAM)styleNumber, (LPARAM)back);
	if (sizeInPoints > 0) ::SendMessage(hWnd, SCI_STYLESETSIZE, (WPARAM)styleNumber, (LPARAM)sizeInPoints);
	if (fontName != NULL) ::SendMessage(hWnd, SCI_STYLESETFONT, (WPARAM)styleNumber, (LPARAM)fontName);
}

void Scintilla::StyleClearAll()
{
	::SendMessage(hWnd, SCI_STYLECLEARALL, (WPARAM)0, (LPARAM)0);
}

int  Scintilla::GetCurrentLineNumber()
{
	const int position = ::SendMessage(hWnd, SCI_GETCURRENTPOS, (WPARAM)0, (LPARAM)0);
	if (position < 0) return -1;
	return ::SendMessage(hWnd, SCI_LINEFROMPOSITION, (WPARAM)position, (LPARAM)0);
}

void Scintilla::TipShow(int position, const char* tip)
{
	::SendMessage(hWnd, SCI_CALLTIPSHOW, (WPARAM)position, (LPARAM)tip);
}

bool Scintilla:: IsTipActive()
{
	return (::SendMessage(hWnd, SCI_CALLTIPACTIVE, (WPARAM)0, (LPARAM)0) != 0);
}

void Scintilla::TipCancel()
{
	::SendMessage(hWnd, SCI_CALLTIPCANCEL, (WPARAM)0, (LPARAM)0);
}

void Scintilla::SetTipHighlight(int highlightStart, int highlightEnd)
{
	::SendMessage(hWnd, SCI_CALLTIPSETHLT, (WPARAM)highlightStart, (LPARAM)highlightEnd);
}

void Scintilla::SetTipBackColor(COLORREF color)
{
	::SendMessage(hWnd, SCI_CALLTIPSETBACK, (WPARAM)color, (LPARAM)0);
}

void Scintilla::SetTipTextColor(COLORREF color)
{
	::SendMessage(hWnd, SCI_CALLTIPSETFORE, (WPARAM)color, (LPARAM)0);
}

void Scintilla::SetTipForeHltColor(COLORREF color)
{
	::SendMessage(hWnd, SCI_CALLTIPSETFOREHLT, (WPARAM)color, (LPARAM)0);
}

void Scintilla::SetTipUseStyle(int tabsize)
{
	::SendMessage(hWnd, SCI_CALLTIPUSESTYLE, (WPARAM)tabsize, (LPARAM)0);
}

void Scintilla::SetTipPosition(bool above)
{
	if (above == true)
	{
		::SendMessage(hWnd, SCI_CALLTIPSETPOSITION, (WPARAM)0, (LPARAM)1);
	}
	else
	{
		::SendMessage(hWnd, SCI_CALLTIPSETPOSITION, (WPARAM)0, (LPARAM)0);
	}
}


#endif

//_____________________________________________________________________ RichEdit
#ifdef WIN_RICHEDIT_SUPPORT
RichEdit::RichEdit(void)
{
	m_hModule = ::LoadLibrary(L"Riched20.dll");
}

RichEdit::~RichEdit(void)
{
	::FreeLibrary(m_hModule);
}

bool RichEdit::SetAutoUrlDetect(bool autoDetect)
{
	return (::SendMessage(this->hWnd, EM_AUTOURLDETECT, autoDetect ? TRUE : FALSE, 0) == 0);
}

void RichEdit::CopyToClipboard()
{
	::SendMessage(this->hWnd, WM_COPY, 0, 0);
}

void RichEdit::PasteFromClipboard()
{
	::SendMessage(hWnd, WM_PASTE, 0, 0);
}

void RichEdit::ClearSelection()
{
	::SendMessage(hWnd, WM_CLEAR, 0, 0);
}

void RichEdit::CutSelection()
{
	::SendMessage(hWnd, WM_CUT, 0, 0);
}

bool RichEdit::CanPaste()
{
	return (::SendMessage(this->hWnd, EM_CANPASTE, 0, 0) != 0);
}

bool RichEdit::CanRedo()
{
	return (::SendMessage(this->hWnd, EM_CANREDO, 0, 0) != 0);
}

bool RichEdit::CanUndo()
{
	return (::SendMessage(this->hWnd, EM_CANUNDO, 0, 0) != 0);
}

//The zoom ratio anywhere between 1/64 and 64
bool RichEdit::SetZoom(int numerator, int denominator)
{
	return (::SendMessage(this->hWnd, EM_SETZOOM, (WPARAM)numerator, (LPARAM)denominator) == TRUE);
}

//The document will be scrolled until this point is located in the upper-left corner of the edit control window. 
//If you want to change the view such that the upper left corner of the view is two lines down and one character in from the left edge, 
//You would pass a point of (7, 22). 
void RichEdit::SetScrollPosition(const POINT* point)
{
	::SendMessage(hWnd, EM_SETSCROLLPOS, 0, (LPARAM)point);
}

int RichEdit::GetSelectedText(wstring& selectedText)
{
	//__________________ Compute selectiont length
	CHARRANGE cr;
	::SendMessage(hWnd, EM_EXGETSEL, 0, (LPARAM)&cr);
	const int length = cr.cpMax-cr.cpMin+1;

	selectedText.resize(length);
	TEXTRANGE tr;
	tr.chrg.cpMin = cr.cpMin;
	tr.chrg.cpMax = cr.cpMax;
	tr.lpstrText = (LPWSTR)selectedText.c_str();
	::SendMessage(hWnd, EM_GETTEXTRANGE, 0, (LPARAM)&tr);
	selectedText.resize(length-1);
	return length-1;
}

void RichEdit::Delete()
{
	this->SetSelection(0, -1);
	this->ReplaceSelection(L"", true);
}

// ENM_CHANGE, ENM_CORRECTTEXT, ENM_DRAGDROPDONE, ENM_DROPFILES 
// ENM_KEYEVENTS, ENM_LINK, ENM_MOUSEEVENTS, ENM_OBJECTPOSITIONS 
// ENM_PROTECTED, ENM_REQUESTRESIZE, ENM_SCROLL, ENM_SCROLLEVENTS 
// ENM_SELCHANGE 
LRESULT RichEdit::SetEventMask(LPARAM eventMask)
{
	return ::SendMessage(hWnd, EM_SETEVENTMASK, 0, eventMask);
}

LRESULT RichEdit::GetEventMask()
{
	return ::SendMessage(hWnd, EM_GETEVENTMASK, 0, 0);
}

LRESULT RichEdit::SetBkGndColor(COLORREF color)
{
	return ::SendMessage(hWnd, EM_SETBKGNDCOLOR, 0, (LPARAM)color);
}

// If the cpMin and cpMax members are equal, the range is empty. 
// The range includes everything if cpMin is 0 and cpMax is –1
void RichEdit::GetSelection(CHARRANGE& crSelection)
{
	::SendMessage(hWnd, EM_EXGETSEL, 0, (LPARAM)&crSelection);
}

int RichEdit::GetLineCount()
{
	return (int)::SendMessage(hWnd, EM_GETLINECOUNT, 0, 0);
}

int RichEdit::GetTextLength()
{
	GETTEXTLENGTHEX  gtl;

	gtl.flags = GTL_DEFAULT;
	gtl.codepage = 1200;
	return (int)::SendMessage(hWnd, EM_GETTEXTLENGTHEX, (WPARAM)&gtl, 0);
}

void RichEdit::GetSelection(int& charStart, int& charEnd)
{
	CHARRANGE cr;
	::SendMessage(hWnd, EM_EXGETSEL, 0, (LPARAM)&cr);
	charStart = cr.cpMin;
	charEnd = cr.cpMax;
}

//If the cpMin and cpMax members are equal, the range is empty. The range includes everything if cpMin is 0 and cpMax is –1.
LRESULT RichEdit::SetSelection(CHARRANGE& crSelection)
{
	return ::SendMessage(hWnd, EM_EXSETSEL, 0, (LPARAM)&crSelection);
}

LRESULT RichEdit::SelectLine(int lineIndex)
{
	this->ShowSelection(true);
	int charIndex = GetCharIndex(lineIndex);
	int length = GetLineLength(lineIndex);
	return this->SetSelection(charIndex, charIndex+length);
}

LRESULT RichEdit::SetSelection(int charStart, int charEnd)
{
	CHARRANGE cr;
	cr.cpMin = charStart;
	cr.cpMax = charEnd;
	return ::SendMessage(hWnd, EM_EXSETSEL, 0, (LPARAM)&cr);
}

// SEL_EMPTY | SEL_TEXT | SEL_OBJECT | SEL_MULTICHAR | SEL_MULTIOBJECT 
LRESULT RichEdit::GetSelectionType()
{
	return ::SendMessage(hWnd, EM_SELECTIONTYPE, 0, 0);
}

void RichEdit::ShowSelection(bool show)
{
	WPARAM wp = show ? 0 : 1;
	::SendMessage(hWnd, EM_HIDESELECTION, 0, wp);
}

int RichEdit::GetSelectedText(wchar_t * buffer)
{
	return (int)::SendMessage(hWnd, EM_GETSELTEXT, 0, (LPARAM)buffer);
}

int RichEdit::GetText(int charStart, int charEnd, wchar_t * buffer)
{
	TEXTRANGE tr;
	tr.chrg.cpMin = charStart;
	tr.chrg.cpMax = charEnd;
	tr.lpstrText = buffer;
	return (int)::SendMessage(hWnd, EM_GETTEXTRANGE, 0, (LPARAM)&tr);
}

int RichEdit::GetText(CHARRANGE& cr, wchar_t * buffer)
{
	TEXTRANGE tr;
	tr.chrg = cr;
	tr.lpstrText = buffer;
	return (int)::SendMessage(hWnd, EM_GETTEXTRANGE, 0, (LPARAM)&tr);
}

CHARRANGE RichEdit::FindText(int charStart, int charEnd, wchar_t * stringToFind, bool matchCase, bool wholeWords, bool backwards)
{
	WPARAM wp = 0;
	if (matchCase) wp = wp | FR_MATCHCASE;
	if (wholeWords) wp = wp | FR_WHOLEWORD;
	if (backwards==false) wp = wp | FR_DOWN;

	FINDTEXTEXW ft;
	ft.chrg.cpMin = charStart;
	ft.chrg.cpMax = charEnd;
	ft.lpstrText = stringToFind;
	::SendMessage(hWnd, EM_FINDTEXTEXW, wp, (LPARAM)&ft);
	return ft.chrgText;
}

int RichEdit::GetLineFromChar(int charIndex)
{
	return (int)::SendMessage(hWnd, EM_EXLINEFROMCHAR, 0, (LPARAM)charIndex);
}

// Gets the character index of the first character of a specified line
// A value of –1 specifies the current line number (the line that contains the caret). 
int RichEdit::GetCharIndex(int lineIndex)
{
	return (int)::SendMessage(hWnd, EM_LINEINDEX, (WPARAM)lineIndex, 0);
}

int RichEdit::GetLineLength(int lineIndex)
{
	const int charIndex = GetCharIndex(lineIndex);
	return (int)::SendMessage(hWnd, EM_LINELENGTH, (WPARAM)charIndex, 0);
}

int RichEdit::GetLineLengthFromChar(int charIndex)
{
	return (int)::SendMessage(hWnd, EM_LINELENGTH, (WPARAM)charIndex, 0);
}

bool RichEdit::GetLineText(int lineIndex, wchar_t * buffer, int bufferLength)
{
	buffer[0]='\0';
	const int charIndex = GetCharIndex(lineIndex);
	int lineLength = GetLineLengthFromChar(charIndex);
	if (lineLength<=0) return false;
	lineLength = MINIMUM(lineLength, bufferLength-1);
	this->GetText(charIndex, charIndex+lineLength, buffer);
	buffer[lineLength]='\0';
	return true;
}

bool RichEdit::GetLineText(int lineIndex, wchar_t * buffer)
{
	buffer[0]='\0';
	const int charIndex = GetCharIndex(lineIndex);
	const int lineLength = GetLineLengthFromChar(charIndex);
	if (lineLength<=0) return false;
	this->GetText(charIndex, charIndex+lineLength, buffer);
	return true;
}

bool RichEdit::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg==WM_COMMAND)
	{
		if (LOWORD(e.wParam)!=this->id) return false;
		if (HIWORD(e.wParam)!=notification) return false;
		return true;
	}
	else if (e.uMsg==WM_NOTIFY)
	{
		NMHDR* pNMHDR= (LPNMHDR)e.lParam; 
		 if (pNMHDR->hwndFrom!=this->GetHWND()) return false;
		 if (pNMHDR->code!=notification) return false; 
		return true;
	}
	return false;
}

//SCF_ALL, SCF_SELECTION, SCF_WORD, 0  for DEFAULT FORMAT
LRESULT RichEdit::SetCharFormat(CHARFORMAT2& cf, WPARAM scf)
{
	cf.cbSize = sizeof(CHARFORMAT2);
	return ::SendMessage(this->hWnd, EM_SETCHARFORMAT, (WPARAM)scf, (LPARAM)&cf);
}

//SCF_SELECTION, SCF_DEFAULT
LRESULT RichEdit::GetCharFormat(CHARFORMAT2& cf, WPARAM scf)
{
	cf.cbSize = sizeof(CHARFORMAT2);
	return ::SendMessage(this->hWnd, EM_GETCHARFORMAT, (WPARAM)scf, (LPARAM)&cf);
}

LRESULT RichEdit::SetParaFormat(PARAFORMAT2& pf)
{
	pf.cbSize = sizeof(PARAFORMAT2);
	return ::SendMessage(this->hWnd, EM_SETPARAFORMAT, (WPARAM)0, (LPARAM)&pf);
}

LRESULT RichEdit::GetParaFormat(PARAFORMAT2& pf)
{
	pf.cbSize = sizeof(PARAFORMAT2);
	return ::SendMessage(this->hWnd, EM_GETPARAFORMAT, (WPARAM)0, (LPARAM)&pf);
}

//SCF_ALL, SCF_SELECTION, SCF_WORD
LRESULT RichEdit::SetBold(bool bBold, WPARAM scf)
{
	CHARFORMAT cf;
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_BOLD;
	cf.dwEffects = bBold ? CFE_BOLD : 0;
	return ::SendMessage(this->hWnd, EM_SETCHARFORMAT, scf, (WPARAM)&cf);
}

//SCF_ALL, SCF_SELECTION, SCF_WORD
LRESULT RichEdit::SetItalic(bool bItalic, WPARAM scf)
{
	CHARFORMAT cf;
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_ITALIC;
	cf.dwEffects = bItalic ? CFE_ITALIC : 0;
	return ::SendMessage(this->hWnd, EM_SETCHARFORMAT, scf, (WPARAM)&cf);
}

//SCF_ALL, SCF_SELECTION, SCF_WORD
LRESULT RichEdit::SetUnderline(bool bUnderline, WPARAM scf)
{
	CHARFORMAT cf;
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_UNDERLINE;
	cf.dwEffects = bUnderline ? CFE_UNDERLINE : 0;
	return ::SendMessage(this->hWnd, EM_SETCHARFORMAT, scf, (WPARAM)&cf);
}

//SCF_ALL, SCF_SELECTION, SCF_WORD
//fontSize, in twips (1/1440 of an inch or 1/20 of a printer's point). 
LRESULT RichEdit::SetFontSize(int fontSize, WPARAM scf)
{
	CHARFORMAT cf;
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_SIZE;
	cf.yHeight = fontSize;
	return ::SendMessage(this->hWnd, EM_SETCHARFORMAT, scf, (WPARAM)&cf);
}

//SCF_ALL, SCF_SELECTION, SCF_WORD
LRESULT RichEdit::SetTextColor(COLORREF rgb, WPARAM scf)
{
	CHARFORMAT cf;
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR;
	cf.dwEffects = 0;
	cf.crTextColor = rgb;
	return ::SendMessage(this->hWnd, EM_SETCHARFORMAT, scf, (WPARAM)&cf);
}

//SCF_ALL, SCF_SELECTION, SCF_WORD
LRESULT RichEdit::SetFontFamily(const wchar_t* fontFamily, WPARAM scf)
{
	CHARFORMAT cf;
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_FACE;
	//lstrcpyn(cf.szFaceName, fontFamily, LF_FACESIZE);
	_snwprintf_s(cf.szFaceName, LF_FACESIZE, _TRUNCATE, L"%s", fontFamily);
	return ::SendMessage(this->hWnd, EM_SETCHARFORMAT, scf, (WPARAM)&cf);
}

//SCF_ALL, SCF_SELECTION, SCF_WORD
//fontSize, in twips (1/1440 of an inch or 1/20 of a printer's point). 
LRESULT RichEdit::SetFont(const wchar_t* fontFamily, int fontSize, WPARAM scf)
{
	CHARFORMAT cf;
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_SIZE | CFM_FACE;
	cf.yHeight = fontSize;
	//lstrcpyn(cf.szFaceName, fontFamily, LF_FACESIZE);
	_snwprintf_s(cf.szFaceName, LF_FACESIZE, _TRUNCATE, L"%s", fontFamily);
	return ::SendMessage(this->hWnd, EM_SETCHARFORMAT, scf, (WPARAM)&cf);
}

LRESULT RichEdit::SetParaFormat(PARAFORMAT& pf)
{
	return ::SendMessage(this->hWnd, EM_SETPARAFORMAT, 0, (WPARAM)&pf);
}

//PFA_CENTER, PFA_LEFT, PFA_RIGHT
LRESULT RichEdit::SetParaAligment(WORD aligment)
{
	PARAFORMAT pf;
	pf.cbSize = sizeof(PARAFORMAT);
	pf.dwMask = PFM_ALIGNMENT;
	pf.wAlignment = aligment;
	return ::SendMessage(this->hWnd, EM_SETPARAFORMAT, 0, (WPARAM)&pf);
}

LRESULT RichEdit::SetNumbering(bool bullets)
{
	PARAFORMAT pf;
	pf.cbSize = sizeof(PARAFORMAT);
	pf.dwMask = PFM_NUMBERING;
	pf.wNumbering = bullets ? PFN_BULLET : 0;
	return ::SendMessage(this->hWnd, EM_SETPARAFORMAT, 0, (WPARAM)&pf);
}

bool RichEdit::AppendText(const wstring& text)
{
	return AppendText(text.c_str());
}

bool RichEdit::AppendText(const wstring& text, CHARFORMAT2& cf)
{
	return AppendText(text.c_str(), cf);
}

bool RichEdit::AppendText(const wstring& text, COLORREF color)
{
	return AppendText(text.c_str(), color);
}

bool RichEdit::AppendText(const wstring& text, const wchar_t* fontFamily, int fontSize)
{
	return AppendText(text.c_str(), fontFamily, fontSize);
}

bool RichEdit::AppendText(const wstring& text, const wchar_t* fontFamily, int fontSize, COLORREF color)
{
	return AppendText(text.c_str(), fontFamily, fontSize, color);
}

bool RichEdit::AppendText(const wchar_t* text)
{
	::SendMessage (this->hWnd, EM_SETSEL, (WPARAM) -1, (LPARAM) -1);
	::SendMessage (this->hWnd, EM_REPLACESEL, FALSE, (LPARAM) text);
	::SendMessage (this->hWnd, EM_SCROLLCARET, 0, 0);
	return true;
}

bool RichEdit::AppendText(const wchar_t* text, CHARFORMAT2& cf)
{
	cf.cbSize = sizeof(CHARFORMAT2);
	::SendMessage (this->hWnd, EM_SETSEL, (WPARAM) -1, (LPARAM) -1);
	const int currentLength = this->GetTextLength();
	const int lengthNewText = wcslen(text);
	::SendMessage (this->hWnd, EM_REPLACESEL, FALSE, (LPARAM) text);
	this->SetSelection(currentLength, currentLength+lengthNewText);
	this->SetCharFormat(cf, SCF_SELECTION);
	::SendMessage (this->hWnd, EM_SCROLLCARET, 0, 0);
	this->SetSelection(-1, -1);
	return true;
}

bool RichEdit::AppendText(const wchar_t* text, COLORREF color)
{
	CHARFORMAT2 ch;
	::memset(&ch, 0, sizeof(CHARFORMAT2));
	ch.cbSize = sizeof(CHARFORMAT2);
	ch.dwMask = CFM_COLOR;
	ch.crTextColor = color;
	return AppendText(text, ch);
}

bool RichEdit::AppendText(const wchar_t* text, const wchar_t* fontFamily, int fontSize)
{
	CHARFORMAT2 ch;
	::memset(&ch, 0, sizeof(CHARFORMAT2));
	ch.cbSize = sizeof(CHARFORMAT2);
	ch.dwMask = CFM_FACE | CFM_SIZE;
	_snwprintf_s(ch.szFaceName, 32, _TRUNCATE, L"%s", fontFamily);
	ch.yHeight = 20*fontSize;
	return AppendText(text, ch);
}

bool RichEdit::AppendText(const wchar_t* text, const wchar_t* fontFamily, int fontSize, COLORREF color)
{
	CHARFORMAT2 ch;
	::memset(&ch, 0, sizeof(CHARFORMAT2));
	ch.cbSize = sizeof(CHARFORMAT2);
	ch.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;
	ch.crTextColor = color;
	_snwprintf_s(ch.szFaceName, 32, _TRUNCATE, L"%s", fontFamily);
	ch.yHeight = 20*fontSize;
	return AppendText(text, ch);
}

void RichEdit::ReplaceSelection(const wchar_t* replaceWithThis, bool canBeUndone)
{
	BOOL undone = canBeUndone ? TRUE : FALSE;
	::SendMessage (this->hWnd, EM_REPLACESEL, undone, (LPARAM) replaceWithThis);
}

void RichEdit::SetFormatRange(int charStart, int charEnd, bool isBold, COLORREF color, const wchar_t* fontFamily, int fontSize)
{
	if (charStart >= charEnd) return; //nothing to format
	this->SetSelection(charStart, charEnd);

	DWORD effects = isBold ? CFE_BOLD : 0;

	CHARFORMAT2 cf;
    this->GetCharFormat(cf, SCF_SELECTION);
	
	if ((cf.dwMask & CFM_COLOR)  && cf.crTextColor == color && 
		(cf.dwMask & CFM_SIZE) && (cf.yHeight == fontSize) &&
		(cf.dwMask & CFM_FACE) && (wcscmp(cf.szFaceName, fontFamily) == 0) &&
		(cf.dwMask & CFM_BOLD) && (cf.dwEffects & CFE_BOLD) == effects) return; //nothing to format

	cf.dwEffects = effects;
	cf.crTextColor = color;
	cf.yHeight = fontSize;
	_snwprintf_s(cf.szFaceName, LF_FACESIZE, _TRUNCATE, L"%s", fontFamily);
	cf.dwMask = CFM_BOLD | CFM_COLOR | CFM_FACE | CFM_SIZE;
	this->SetCharFormat(cf, SCF_SELECTION);
}

void RichEdit::SetProtectedFormatRange(int charStart, int charEnd, bool isBold, COLORREF color, const wchar_t* fontFamily, int fontSize)
{
	if (charStart >= charEnd) return; //nothing to format
	this->SetSelection(charStart, charEnd);

	DWORD effects = isBold ? CFE_BOLD & CFE_PROTECTED : CFE_PROTECTED;

	CHARFORMAT2 cf;
    this->GetCharFormat(cf, SCF_SELECTION);
	
	if ((cf.dwMask & CFM_COLOR)  && cf.crTextColor == color && 
		(cf.dwMask & CFM_SIZE) && (cf.yHeight == fontSize) &&
		(cf.dwMask & CFM_FACE) && (wcscmp(cf.szFaceName, fontFamily) == 0) &&
		(cf.dwMask & CFM_BOLD) && (cf.dwEffects & CFE_BOLD) == effects) return; //nothing to format

	//cf.dwEffects = CFE_PROTECTED; 
	cf.dwMask = cf.dwMask | CFM_PROTECTED; // Force protected

	cf.dwEffects = effects;
	cf.crTextColor = color;
	cf.yHeight = fontSize;
	_snwprintf_s(cf.szFaceName, LF_FACESIZE, _TRUNCATE, L"%s", fontFamily);
	cf.dwMask = CFM_BOLD | CFM_COLOR | CFM_FACE | CFM_SIZE;
	this->SetCharFormat(cf, SCF_SELECTION);
}

void RichEdit::SetFormatRange(int charStart, int charEnd, bool isBold, COLORREF color)
{
	if (charStart >= charEnd) return; //nothing to format
	this->SetSelection(charStart, charEnd);

	DWORD effects = isBold ? CFE_BOLD : 0;

	CHARFORMAT2 cf;
    this->GetCharFormat(cf, SCF_SELECTION);
	
	if ((cf.dwMask & CFM_COLOR)  && cf.crTextColor == color && 
		(cf.dwMask & CFM_BOLD) && (cf.dwEffects & CFE_BOLD) == effects) return; //nothing to format

	cf.dwEffects = effects;
	cf.crTextColor = color;
	cf.dwMask = CFM_BOLD | CFM_COLOR;
	this->SetCharFormat(cf, SCF_SELECTION);
}


bool RichEdit::SaveToRtf(const wchar_t* filename)
{
	Sys::File file;
	if (file.CreateForWritting(filename) == false) return false;
	string data;
	GetData(data);
	file.Write(data.c_str(), data.length());
	return true;
}


//SF_RTF
//SF_TEXT
//SFF_SELECTION
//SF_UNICODE
// Use this function to save data to a file or to a buffer
void RichEdit::GetData(string& output)
{
	EDITSTREAM editStrem;
	editStrem.dwCookie = (DWORD_PTR)&output;
	editStrem.pfnCallback = Win::RichEdit::StreamCallback;
	::SendMessage(this->hWnd, EM_STREAMOUT, (WPARAM)SF_RTF, (LPARAM)&editStrem);
}

DWORD CALLBACK RichEdit::StreamCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	string* buffer = (string*)dwCookie;
	buffer->append((const char*)pbBuff, cb);
	*pcb = cb;
	return 0;
}

BOOL RichEdit::Print(HWND hWndParent, const wchar_t* documentName)
{
	static PRINTDLG pd;
	ZeroMemory((void*)&pd, sizeof(PRINTDLG));
	pd.lStructSize = sizeof(PRINTDLG);
	pd.nMinPage = 1;
	pd.nCopies = 1;
	pd.nFromPage = 1;
	pd.nMaxPage = 2;
	pd.nToPage = 2;
	pd.hwndOwner = hWndParent;
	pd.Flags = PD_RETURNDC | PD_NOSELECTION | PD_NOPAGENUMS;
	if (PrintDlg(&pd)==0) return FALSE;

	const int cxPhysOffset = ::GetDeviceCaps(pd.hDC, PHYSICALOFFSETX);
	const int cyPhysOffset = ::GetDeviceCaps(pd.hDC, PHYSICALOFFSETY);
	const int cxPhys = ::GetDeviceCaps(pd.hDC, PHYSICALWIDTH);
	const int cyPhys = ::GetDeviceCaps(pd.hDC, PHYSICALHEIGHT);

	FORMATRANGE fr;
	fr.hdc = pd.hDC;
	fr.hdcTarget = pd.hDC;
	fr.rc.left = cxPhysOffset;
	fr.rc.right = cxPhysOffset + cxPhys;
	fr.rc.top = cyPhysOffset;
	fr.rc.bottom = cyPhysOffset + cyPhys;

	static DOCINFO docInfo;
	ZeroMemory((void*)&docInfo, sizeof(DOCINFO));
	docInfo.cbSize = sizeof(DOCINFO);
	docInfo.lpszDocName = documentName;

	if (StartDoc (pd.hDC, &docInfo) <= 0) return FALSE;
	//________________________________Select the entire contents.
	::SendMessage(hWnd, EM_SETSEL, 0, (LPARAM)-1);
	//________________________________Get the selection into a CHARRANGE.
	::SendMessage(hWnd, EM_EXGETSEL, 0, (LPARAM)&fr.chrg);

	BOOL fSuccess = TRUE;
	int cpMin = -1;

	//_________________________________Print successive pages.
	while (fr.chrg.cpMin < fr.chrg.cpMax && fSuccess) 
	{
		fSuccess = StartPage(pd.hDC) > 0;
		if (!fSuccess) break;
		cpMin = ::SendMessage(hWnd, EM_FORMATRANGE, TRUE, (LPARAM)&fr);
		if (cpMin <= fr.chrg.cpMin) 
		{
			fSuccess = FALSE;
			break;
		}
		fr.chrg.cpMin = cpMin;
		fSuccess = EndPage(pd.hDC) > 0;
	}
	::SendMessage(hWnd, EM_FORMATRANGE, FALSE, 0);
	 EndDoc (pd.hDC);
	return TRUE;
}

bool RichEdit::Undo()
{
	return (::SendMessage(this->hWnd, EM_UNDO, 0, 0) != 0);
}

bool RichEdit::Redo()
{
	return (::SendMessage(this->hWnd, EM_REDO, 0, 0) != 0);
}

void RichEdit::SetReadOnly(bool readOnly)
{
	WPARAM p = readOnly ? TRUE : FALSE;
	::SendMessage(this->hWnd, EM_SETREADONLY, p, (LPARAM)0);
}

bool RichEdit::GetReadOnly()
{
	if (::GetWindowLong(hWnd, GWL_STYLE) & ES_READONLY) return true;
	return false;
}

//_____________________________________________________________________ CodeEditor
CodeEditor::CodeEditor(void)
{
	this->isBlocking = false;
	this->formatType = FORMAT_CURRENT_SELECTION;
	this->previousSelection.cpMin = 0;
	this->previousSelection.cpMax = 0;
	//
	keywordColor = RGB(0, 0, 255);
	functionColor = RGB(155, 51, 255);
	commentColor = RGB(0, 128, 0);
	numberColor = RGB(200, 0, 0);
	stringColor = RGB(200, 0,180);
	//
	_snwprintf_s(_fontFamily, LF_FACESIZE, _TRUNCATE, L"Arial");
	_fontSize = 200;
}

CodeEditor::~CodeEditor(void)
{
}

void CodeEditor::PasteFromClipboard()
{
	::SendMessage(hWnd, EM_PASTESPECIAL, CF_UNICODETEXT, NULL);
	this->FormatAll();
}

// Returns the Window Text
wstring CodeEditor::GetText()
{
	wstring tmp;
	const int length = ::GetWindowTextLength(hWnd);
	tmp.resize(length);
	::GetWindowText(hWnd, (wchar_t*)tmp.data(), length+1);
	return tmp;
}

void CodeEditor::SetText(const wstring text)
{
	::SetWindowText(hWnd, text.c_str());
	this->FormatAll();
}

bool CodeEditor::Undo()
{
	bool result = (::SendMessage(this->hWnd, EM_UNDO, 0, 0) != 0);
	FormatAll();
	return result;
}

bool CodeEditor::Redo()
{
	bool result = (::SendMessage(this->hWnd, EM_REDO, 0, 0) != 0);
	FormatAll();
	return result;
}

void CodeEditor::CommentOut()
{
	int charStart, charEnd;
	this->GetSelection(charStart, charEnd);

	wstring selection;
	this->GetSelectedText(selection);
	Sys::TextAssistant::ReplaceWord(selection, L"\r\n", L"\n", false);
	Sys::TextAssistant::ReplaceWord(selection, L"\n\r", L"\n", false);
	Sys::TextAssistant::ReplaceWord(selection, L"\r", L"\n", false);
	Sys::TextAssistant::ReplaceWord(selection, L"\n", L"\n//", false);
	wstring strNew(L"//");
	//isBlocking = true;
	strNew += selection;
	::SendMessage (this->hWnd, EM_REPLACESEL, TRUE, (LPARAM)strNew.c_str());
	
	//isBlocking = false;
	//
	const int newLength = strNew.length();
	FormatTextRange(charStart, charStart+newLength-1);
	//
	//_____________________ Restore selection
	this->SetSelection(charStart, charStart+newLength);
}

void CodeEditor::Uncomment()
{
	int charStart, charEnd;
	this->GetSelection(charStart, charEnd);

	wstring selection;
	const int length = this->GetSelectedText(selection);

	if (length<3) return;
	if (length>2)
	{
		if (selection[0]=='/' && selection[1]=='/')
		{
			selection.erase(selection.begin(), selection.begin()+2);
		}
	}
	const int count =  Sys::TextAssistant::GetWordCount(selection, L"//", false);
	//if (count<=0) return;

	Sys::TextAssistant::ReplaceWord(selection, L"\r\n", L"\n", false);
	Sys::TextAssistant::ReplaceWord(selection, L"\n\r", L"\n", false);
	Sys::TextAssistant::ReplaceWord(selection, L"\r", L"\n", false);
	Sys::TextAssistant::ReplaceWord(selection, L"\n//", L"\n", false);
	//isBlocking = true;
	::SendMessage (this->hWnd, EM_REPLACESEL, TRUE, (LPARAM)selection.c_str());
	//_____________________ Restore selection
	//isBlocking = false;
	//
	FormatTextRange(charStart, charStart+selection.length()-1);
	this->SetSelection(charStart, charStart+selection.length());
}

void CodeEditor::Setup(const wchar_t* fontFamily, int fontSize)
{
	this->formatType = FORMAT_CURRENT_SELECTION;
	_snwprintf_s(this->_fontFamily, LF_FACESIZE, _TRUNCATE, L"%s", fontFamily);
	this->_fontSize = fontSize;
	//
	this->SetEventMask(ENM_PROTECTED | ENM_CHANGE | ENM_KEYEVENTS | EN_MSGFILTER);
	//
	PARAFORMAT pf;
	pf.cbSize = sizeof(PARAFORMAT);
	pf.dwMask = PFM_TABSTOPS ;
	pf.cTabCount = MAX_TAB_STOPS;
	for( int itab = 0 ; itab < pf.cTabCount  ; itab++ )
		pf.rgxTabs[itab] = (itab + 1) * 1440/5 ;

	this->SetParaFormat(pf);
	//
	CHARFORMAT2 cf;
	cf.cbSize = sizeof(CHARFORMAT2);
	cf.dwEffects = CFE_PROTECTED; 
	cf.dwMask = CFM_FACE | CFM_SIZE | CFM_CHARSET | CFM_PROTECTED;
	cf.yHeight = fontSize;
	cf.bCharSet = DEFAULT_CHARSET;
	_snwprintf_s(cf.szFaceName, LF_FACESIZE, _TRUNCATE, L"%s", fontFamily); 
	this->SetCharFormat(cf, 0); // 0 = Default
}

void CodeEditor::FormatTextRange(int charStart, int charEnd)
{
	if (charStart >= charEnd) return;
	this->isBlocking = true;

	CHARRANGE tmpSelection;
	this->GetSelection(tmpSelection);
	this->LockUpdate(true);
	this->ShowSelection(false);

	wchar_t *buffer = NULL;
	try 
	{
		this->SetSelection(charStart, charEnd);
		buffer = new wchar_t[charEnd - charStart + 1];
		int length = this->GetSelectedText(buffer);
		_ASSERT(length <= charEnd - charStart);

		buffer[length] = '\0';

		wchar_t *pStart, *pPtr;
		pStart = pPtr = buffer;

		wchar_t* pSymbolStart = NULL;
		SymbolColor ic;

		while (*pPtr != 0) 
		{
			wchar_t ch = *pPtr;

	//		//if (ch == m_chComment && (m_chComment2 == 0 || pPtr[1] == m_chComment2)) 
			if (ch == '/' &&  pPtr[1] == '/') 
			{
				pSymbolStart = pPtr;
				do 
				{
					ch = *(++pPtr);
				} 
				while (ch != '\0' && ch != '\r' && ch != '\n' && ch != 11);// || (ch != 0 && ch != '\n'));
				ic.color = commentColor;
				ic.isBold = false;
				//pPtr++;
			} 
			else if (ch=='"') 
			{ // Process strings
				pSymbolStart = pPtr;
				wchar_t ch1 = ch;
				do 
				{
					ch = *(++pPtr);
				} 
				while (ch != 0 && ch != ch1 && ch != '\r' && ch != '\n' && ch != 11);
				if (ch == ch1) pPtr++;
				ic.color = stringColor;
				ic.isBold = false;
			} 
			else if (iswdigit(ch)) 
			{ // Process numbers
				pSymbolStart = pPtr;
				wcstod(pSymbolStart, &pPtr);
				ic.color = numberColor;
				ic.isBold = false;
			} 
			else if (iswalpha(ch) || ch == '_') 
			{ // Process keywords
				pSymbolStart = pPtr;
				do 
				{
					ch = *(++pPtr);
				} 
				while (iswalnum(ch) || ch == '_');
				*pPtr = 0;
				if (keywords.find(pSymbolStart) != keywords.end()) 
				{
					ic.color = keywordColor;
					ic.isBold = true;
				} 
				else 
				{
					if (functions.find(pSymbolStart) != functions.end() )
					{
						ic.color = functionColor;
						ic.isBold = true;
					} 
					else 
					{
						pSymbolStart = NULL;
					}
				}
				*pPtr = ch;
			} 
			else 
			{
				pPtr++;
			}

			if (pSymbolStart != NULL) 
			{
				_ASSERT(pSymbolStart < pPtr);
				this->SetProtectedFormatRange(charStart + pStart - buffer, charStart + pSymbolStart - buffer, FALSE, RGB(0,0,0), _fontFamily, _fontSize);
				this->SetProtectedFormatRange(charStart + pSymbolStart - buffer, charStart + pPtr - buffer, ic.isBold, ic.color, _fontFamily, _fontSize);
				pStart = pPtr;
				pSymbolStart = 0;
			} 
			else if (*pPtr == '\0')
				this->SetProtectedFormatRange(charStart + pStart - buffer, charStart + pPtr - buffer, FALSE, RGB(0,0,0), _fontFamily, _fontSize);
		}

	} catch(...){}

	//_______________________________________ Correct paragraph line spacing
	PARAFORMAT2 pf;
	::memset(&pf, 0, sizeof(PARAFORMAT2));
	pf.dwMask = PFM_LINESPACING | PFM_SPACEAFTER | PFM_SPACEBEFORE;
	pf.bLineSpacingRule = 0;
	pf.dySpaceBefore = 0;
	pf.dySpaceAfter = 0;
	this->SetSelection(0, GetTextLength());
	this->SetParaFormat(pf);
	//
	if (buffer) delete [] buffer;
	this->SetSelection(tmpSelection);
	this->ShowSelection(true);
	this->LockUpdate(false);
	this->isBlocking = false;
}

void CodeEditor::FormatTextLines(int lineStart, int lineEnd)
{
	int start = this->GetCharIndex(this->GetLineFromChar(lineStart));
	int end = this->GetCharIndex(this->GetLineFromChar(lineEnd));
	end += this->GetLineLength(lineEnd);

	this->FormatTextRange(start, end);
}

void CodeEditor::FormatAll()
{
	this->FormatTextRange(0, this->GetTextLength());
}

//void CodeEditor::CodeEditor_SetText(CodeEditor& ce, WPARAM wParam, LPARAM lParam)
//{
//	ce.FormatAll();
//}

void CodeEditor::OnChange(Win::Event& e) 
{
	e.returnValue = FALSE;
	if (isBlocking) return;

	CHARRANGE currentSelection; 
	this->GetSelection(currentSelection);

	if (this->formatType == FORMAT_MOVE && currentSelection.cpMin == currentSelection.cpMax)
	{
		this->formatType = FORMAT_PASTE;
	}

	switch(this->formatType) 
	{
	case FORMAT_REPLACESEL:
		FormatTextLines(this->previousSelection.cpMin, currentSelection.cpMax);
		break;
	case FORMAT_PASTE: 
		FormatTextLines(this->previousSelection.cpMin, currentSelection.cpMax);
		break;
	case FORMAT_CURRENT_SELECTION:
		if (currentSelection.cpMin == currentSelection.cpMax)
		{
			//____________________ This is necesary when the control is empty and the user paste using ctrl+v
			if (this->GetTextLength() < 10)
			{
				FormatAll();
			}
			else
			{
				FormatTextLines(currentSelection.cpMin, currentSelection.cpMin+1);
			}
		}
		else
		{
			FormatTextLines(currentSelection.cpMin, currentSelection.cpMax);
		}
		break;
	case FORMAT_CUT:
		FormatTextLines(currentSelection.cpMin, currentSelection.cpMax);
		break;
	case FORMAT_MOVE: 
		FormatTextLines(currentSelection.cpMin, currentSelection.cpMax);
		if (currentSelection.cpMin > previousSelection.cpMin) // move after
		{
			FormatTextLines(previousSelection.cpMin, previousSelection.cpMin);
		}
		else // move before
		{
			FormatTextLines(previousSelection.cpMax, previousSelection.cpMax);
		}
		break;
	default:
		FormatAll();
		break;
	}
	this->formatType = FORMAT_CURRENT_SELECTION;
}

void CodeEditor::OnProtected(Win::Event& e)
{
	e.returnValue = FALSE; // Allow all operations

	ENPROTECTED& enProtected(*((ENPROTECTED *)e.lParam));

	switch (enProtected.msg) 
	{
	case WM_KEYDOWN:
		switch (enProtected.wParam) 
		{
		case VK_DELETE:
			this->formatType = FORMAT_CURRENT_SELECTION;
			break;
		case VK_BACK:
			this->formatType = FORMAT_CURRENT_SELECTION;
			break;
		default:
			this->formatType = FORMAT_ALL;
			break;
		}
		break;
	case EM_REPLACESEL:
	case WM_CHAR:
		this->formatType = FORMAT_REPLACESEL;
		break;
	case WM_PASTE:
		this->formatType = (this->formatType == FORMAT_CUT) ? FORMAT_MOVE : FORMAT_PASTE;
		break;
	case WM_CUT:
		this->formatType = FORMAT_CUT;
		break;
	default:
		this->formatType = FORMAT_ALL;
		//this->formatType = FORMAT_CURRENT_SELECTION;
		break;
	}

	if (enProtected.msg == EM_SETCHARFORMAT || this->formatType == FORMAT_MOVE)
	{
	}
	else
	{
		this->previousSelection = enProtected.chrg;
	}
}

void CodeEditor::OnMsgFilter(Win::Event& e)
{
	e.returnValue = 0; // Allow all operations
	MSGFILTER& msgFilter(*((MSGFILTER *)e.lParam));
	
	if (msgFilter.msg == WM_KEYDOWN)
	{
		//NMHDR nmhdr = msgFilter.nmhdr;
		//int x = nmhdr.code;
		//double y;
	}
	else if (msgFilter.msg == WM_PASTE)
	{
		//this->formatType = FORMAT_CURRENT_SELECTION;
		::SendMessage(hWnd, EM_PASTESPECIAL, CF_UNICODETEXT, NULL);
		e.returnValue = 1;
	}
	else if (msgFilter.msg == EM_PASTESPECIAL)
	{
		this->formatType = FORMAT_CURRENT_SELECTION;
	}
	else if (msgFilter.msg == EM_UNDO)
	{
	}
}

//UINT CodeEditor::OnGetDlgCode() 
//{
//	UINT uCode = CRichEditCtrl::OnGetDlgCode();
//	
//	uCode = DLGC_WANTALLKEYS | DLGC_WANTARROWS | DLGC_WANTCHARS | DLGC_WANTMESSAGE | DLGC_WANTTAB;
//
//	return uCode;
//}
//
//void CodeEditor::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
//{
//	if (nChar == '\t' && GetKeyState(VK_CONTROL) >= 0) {
//		ReplaceSel("\t");
//		this->SetFocus();
//		return;
//	}
//	
//	CRichEditCtrl::OnChar(nChar, nRepCnt, nFlags);
//}

#endif

//_____________________________________________________________________ ImageList
bool ImageList::bInit = 0;
ImageList::ImageList(void)
{
	m_hIL = NULL;
	if (bInit==false)
	{
		INITCOMMONCONTROLSEX cc;
		ZeroMemory(&cc, sizeof(INITCOMMONCONTROLSEX));
		cc.dwSize=sizeof(INITCOMMONCONTROLSEX);
		InitCommonControlsEx(&cc);
		bInit=true;
	}
}

ImageList::~ImageList(void)
{
	//if (this->m_hIL) ImageList_Destroy(m_hIL);
}

// flags: ILC_COLOR, ILC_COLOR4, ILC_COLOR8, ILC_COLOR16, ILC_COLOR24, ILC_COLOR32, ILC_COLORDDB
HIMAGELIST ImageList::Create(int width, int height, UINT flags, int initialNumImages, int cGrow)
{
	m_hIL = ImageList_Create(width, height, flags, initialNumImages, cGrow);
	return m_hIL;
}

//this->m_IL.Create(32, 32, 3);
//m_IL.AddIcon(NULL, IDI_ICON1);
//m_IL.AddIcon(NULL, IDI_ICON2);
//m_IL.AddIcon(NULL, IDI_ICON3);
HIMAGELIST ImageList::Create(int width, int height, int initialNumImages)
{
	m_hIL = ImageList_Create(width, height, ILC_COLOR32 | ILC_MASK, initialNumImages, 10);
	return m_hIL;
}

int ImageList::AddIcon(HINSTANCE hInst, const wchar_t * idIcon)
{
	HICON hIcon;
	hIcon = LoadIcon(hInst, idIcon);
	return ImageList_AddIcon(m_hIL, hIcon);
}

int ImageList::AddIcon(HINSTANCE hInst, int idIcon)
{
	HICON hIcon;
	hIcon = LoadIcon(hInst, MAKEINTRESOURCE(idIcon));
	return ImageList_AddIcon(m_hIL, hIcon);
}

// Creates an image list from the images in a bitmap
//cx: The width of each image.
//crMask: CLR_DEFAULT, CLR_NONE
//uFlags: LR_DEFAULTCOLOR, LR_LOADFROMFILE, LR_LOADTRANSPARENT, 
HIMAGELIST ImageList::CreateFromBitmap(HINSTANCE hi, const wchar_t * lpbmp, int cx, int cGrow, COLORREF crMask, UINT uFlags)
{
	UINT uType = IMAGE_BITMAP;
	return ImageList_LoadImage(hi, lpbmp, cx, cGrow, crMask, uType, uFlags);
}

HIMAGELIST ImageList::GetHImageList()
{
	return m_hIL;
}

int ImageList::AddIcon(HICON hIcon)
{
	return ImageList_AddIcon(m_hIL, hIcon);
}

int ImageList::ReplaceIcon(int index, HICON hIcon)
{
	return ImageList_ReplaceIcon(m_hIL, index, hIcon);
}

int ImageList::GetImageCount()
{
	return ImageList_GetImageCount(m_hIL);
}

BOOL ImageList::RemoveAll() 
{
	return ImageList_RemoveAll(m_hIL);
}

BOOL ImageList::Remove(int index) 
{
	return ImageList_Remove(m_hIL, index);
}

ImageList::operator HIMAGELIST() 
{
	return m_hIL;
}

BOOL ImageList::Destroy() //Call destroy only, if you don't set the image list to another control
{
	return ImageList_Destroy(m_hIL);
}


//IDI_APPLICATION
//IDI_ASTERISK
//IDI_EXCLAMATION
//IDI_HAND
//IDI_QUESTION
//IDI_WINLOGO
//IDI_WARNING
//IDI_ERROR
//IDI_INFORMATION
int ImageList::AddSystemIcon(LPTSTR idIcon)
{
	HICON hIcon = LoadIcon(NULL, idIcon);
	return ImageList_AddIcon(m_hIL, hIcon);
}

// if hInst is NULL, it uses the current instance
int ImageList::ReplaceIcon(int index, HINSTANCE hInst, const wchar_t * idIcon)
{
	HICON hIcon;
//	if (hInst == NULL) hInst = this->m_hInstance;
	hIcon = LoadIcon(hInst, idIcon);
	return ImageList_ReplaceIcon(m_hIL, index, hIcon);
}

// if hInst is NULL, it uses the current instance
int ImageList::ReplaceIcon(int index, HINSTANCE hInst, int idIcon)
{
	HICON hIcon;
//	if (hInst == NULL) hInst = this->m_hInstance;
	hIcon = LoadIcon(hInst, MAKEINTRESOURCE(idIcon));
	return ImageList_ReplaceIcon(m_hIL, index, hIcon);
}

// fStyle -> ILD_BLEND25, ILD_FOCUS, ILD_BLEND50, ILD_SELECTED, ILD_BLEND
//ILD_MASK, ILD_NORMAL, ILD_TRANSPARENT, ILD_IMAGE
// gdi::DevContext dc(hWnd, true);
//this->m_IL.Draw(0, dc.GetHDC(), 0, 0, this->m_nWidth, this->m_nHeight, ILD_NORMAL);
BOOL ImageList::Draw(int index, HDC hdc, int x, int y, int dx, int dy, UINT fStyle)
{
	return ImageList_DrawEx(m_hIL, index, hdc, x, y, dx, dy, CLR_NONE, CLR_NONE,  fStyle);
}

//_____________________________________________________________________ Spin
bool Spin::bInit = false;

Spin::Spin(void)
{
	if (bInit == false)
	{
		INITCOMMONCONTROLSEX cc;
		cc.dwSize=sizeof(INITCOMMONCONTROLSEX);
		cc.dwICC=ICC_UPDOWN_CLASS;
		::InitCommonControlsEx(&cc);
		bInit = true;
	}
}

Spin::~Spin(void)
{
}

bool Spin::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_NOTIFY) return false;
	NMHDR* pNMHDR= (LPNMHDR)e.lParam; 
     if (pNMHDR->hwndFrom!=this->GetHWND()) return false;
     if (pNMHDR->code!=notification) return false; 
	return true;
}

LRESULT Spin::SetRange(int minimum, int maximum)
{
	return ::SendMessage(this->hWnd, UDM_SETRANGE32, minimum, maximum);
}
	
LRESULT Spin::SetPosition(int position)
{
	return ::SendMessage(this->hWnd, UDM_SETPOS32, 0, position);
}

int Spin::GetPosition()
{
	LPBOOL pfError = NULL; 
	return (int)::SendMessage(this->hWnd, UDM_GETPOS32, 0,(LPARAM) (LPBOOL) pfError);
}
	
LRESULT Spin::SetBuddy(HWND hEditBox)
{
	return ::SendMessage(this->hWnd, UDM_SETBUDDY, (WPARAM)hEditBox, 0);
}

LRESULT Spin::SetBuddy(Win::Textbox& txbox)
{
	return ::SendMessage(this->hWnd, UDM_SETBUDDY, (WPARAM)txbox.GetHWND(), 0);
}

//_____________________________________________________________________ TreeView
bool TreeView::bInit = false;

TreeView::TreeView(void)
{
	if (bInit==false)
	{
		::InitCommonControls();
		bInit=true;
	}
}

TreeView::~TreeView(void)
{
}

bool TreeView::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_NOTIFY) return false;
	NMHDR* pNMHDR= (LPNMHDR)e.lParam; 
     if (pNMHDR->hwndFrom!=this->GetHWND()) return false;
     if (pNMHDR->code!=notification) return false; 
	return true;
}

HIMAGELIST TreeView::SetImageList(Win::ImageList& imageList)
{
	return (HIMAGELIST)::SendMessage(this->hWnd, (UINT) TVM_SETIMAGELIST, (WPARAM)TVSIL_NORMAL, (LPARAM)imageList.GetHImageList()); 
}

//hParent
//	Handle to the parent item. If this member is the TVI_ROOT value or NULL, the item is inserted at the root of the tree-view control. 
//
//hInsertAfter
//	Handle to the item after which the new item is to be inserted, or one of the following values: 
//	TVI_FIRST
//	Inserts the item at the beginning of the list.
//	TVI_LAST
//	Inserts the item at the end of the list.
//	TVI_ROOT
//	Add the item as a root item.
//	TVI_SORT
//	Inserts the item into the list in alphabetical order.
HTREEITEM TreeView::InserItem(HTREEITEM hParent, HTREEITEM hInsertAfter, const wchar_t *text)
{
	TVINSERTSTRUCT tvinsert;
	tvinsert.hParent = hParent;
	tvinsert.hInsertAfter = hInsertAfter;
	//
	TVITEMEX tvitem;
	tvitem.mask = TVIF_TEXT;
	tvitem.pszText = (wchar_t*)text;
	tvitem.cchTextMax = lstrlen(text)+1;
	//
	tvinsert.itemex = tvitem;
	return InsertItem(tvinsert);
}

//hParent
//	Handle to the parent item. If this member is the TVI_ROOT value or NULL, the item is inserted at the root of the tree-view control. 
//
//hInsertAfter
//	Handle to the item after which the new item is to be inserted, or one of the following values: 
//	TVI_FIRST
//	Inserts the item at the beginning of the list.
//	TVI_LAST
//	Inserts the item at the end of the list.
//	TVI_ROOT
//	Add the item as a root item.
//	TVI_SORT
//	Inserts the item into the list in alphabetical order.
HTREEITEM TreeView::InserItem(HTREEITEM hParent, HTREEITEM hInsertAfter, const wchar_t *text, int imageIndex)
{
	TVINSERTSTRUCT tvinsert;
	tvinsert.hParent = hParent;
	tvinsert.hInsertAfter = hInsertAfter;
	//
	TVITEMEX tvitem;
	tvitem.mask = TVIF_IMAGE | TVIF_TEXT;
	tvitem.cchTextMax = lstrlen(text);
	tvitem.pszText = (wchar_t*) text;
	tvitem.iImage = imageIndex,
	//
	tvinsert.itemex = tvitem;
	return InsertItem(tvinsert);
}

//hParent
//	Handle to the parent item. If this member is the TVI_ROOT value or NULL, the item is inserted at the root of the tree-view control. 
//
//hInsertAfter
//	Handle to the item after which the new item is to be inserted, or one of the following values: 
//	TVI_FIRST
//	Inserts the item at the beginning of the list.
//	TVI_LAST
//	Inserts the item at the end of the list.
//	TVI_ROOT
//	Add the item as a root item.
//	TVI_SORT
//	Inserts the item into the list in alphabetical order.
HTREEITEM TreeView::InserItem(HTREEITEM hParent, HTREEITEM hInsertAfter, const wchar_t *text, int imageIndex, LPARAM data)
{
	TVINSERTSTRUCT tvinsert;
	tvinsert.hParent = hParent;
	tvinsert.hInsertAfter = hInsertAfter;
	//
	TVITEMEX tvitem;
	tvitem.mask = TVIF_IMAGE | TVIF_TEXT | TVIF_PARAM;
	tvitem.cchTextMax = lstrlen(text);
	tvitem.pszText = (wchar_t*) text;
	tvitem.iImage = imageIndex;
	tvitem.lParam = data;
	//
	tvinsert.itemex = tvitem;
	return InsertItem(tvinsert);
}

BOOL TreeView::SetItemText(HTREEITEM hItem, const wchar_t* text)
{
	TVITEMEX tvitem;
	tvitem.mask = TVIF_HANDLE | TVIF_TEXT;
	tvitem.hItem = hItem;
	tvitem.pszText = (wchar_t*)text;
	tvitem.cchTextMax = lstrlen(text)+1;
	return SetItem(tvitem);
}

BOOL TreeView::SetItemImage(HTREEITEM hItem, int imageIndex)
{
	TVITEMEX tvitem;
	tvitem.mask = TVIF_HANDLE | TVIF_IMAGE;
	tvitem.hItem = hItem;
	tvitem.iImage = imageIndex;
	return SetItem(tvitem);
}

BOOL TreeView::SetItemData(HTREEITEM hItem, LPARAM data)
{
	TVITEMEX tvitem;
	tvitem.mask = TVIF_HANDLE | TVIF_PARAM;
	tvitem.lParam = data;
	return SetItem(tvitem);
}

BOOL TreeView::SetItem(const TVITEMEX& tvitem)
{
	return (BOOL)::SendMessage(this->hWnd, (UINT) TVM_SETITEM, (WPARAM)0, (LPARAM)&tvitem); 
}

HTREEITEM TreeView::InsertItem(TVINSERTSTRUCT& tvinsert)
{
	return (HTREEITEM)::SendMessage(this->hWnd, (UINT) TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvinsert); 
}

int TreeView::GetVisibleCount(void)
{
	return (int)::SendMessage(this->hWnd, (UINT) TVM_GETVISIBLECOUNT, (WPARAM)0, (LPARAM)0);  
}

int TreeView::GetCount(void)
{
	return (int)::SendMessage(this->hWnd, (UINT) TVM_GETCOUNT, (WPARAM)0, (LPARAM)0);  
}

BOOL TreeView::GetItemRect(RECT& rc, HTREEITEM hItem, bool onlyTextBox)
{
	BOOL flag = (onlyTextBox==true) ? TRUE : FALSE;
	*(HTREEITEM*)&rc = hItem;
	return (BOOL)::SendMessage(this->hWnd, (UINT) TVM_GETITEMRECT, (WPARAM)flag, (LPARAM)&rc);  
}

//TVGN_CARET
//Retrieves the currently selected item. You can use the TreeView_GetSelection macro to send this message.
//TVGN_CHILD
//Retrieves the first child item of the item specified by the hitem parameter. You can use the TreeView_GetChild macro to send this message.
//TVGN_DROPHILITE
//Retrieves the item that is the target of a drag-and-drop operation. You can use the TreeView_GetDropHilight macro to send this message.
//TVGN_FIRSTVISIBLE
//Retrieves the first item that is visible in the tree-view window. You can use the TreeView_GetFirstVisible macro to send this message.
//TVGN_LASTVISIBLE
//Version 4.71. Retrieves the last expanded item in the tree. This does not retrieve the last item visible in the tree-view window. You can use the TreeView_GetLastVisible macro to send this message.
//TVGN_NEXT
//Retrieves the next sibling item. You can use the TreeView_GetNextSibling macro to send this message.
//TVGN_NEXTVISIBLE
//Retrieves the next visible item that follows the specified item. The specified item must be visible. Use the TVM_GETITEMRECT message to determine whether an item is visible. You can use the TreeView_GetNextVisible macro to send this message.
//TVGN_PARENT
//Retrieves the parent of the specified item. You can use the TreeView_GetParent macro to send this message.
//TVGN_PREVIOUS
//Retrieves the previous sibling item. You can use the TreeView_GetPrevSibling macro to send this message.
//TVGN_PREVIOUSVISIBLE
//Retrieves the first visible item that precedes the specified item. The specified item must be visible. Use the TVM_GETITEMRECT message to determine whether an item is visible. You can use the TreeView_GetPrevVisible macro to send this message.
//TVGN_ROOT
//Retrieves the topmost or very first item of the tree-view control. You can use the TreeView_GetRoot macro to send this message. 
HTREEITEM TreeView::GetNextItem(UINT flag, HTREEITEM hItem)
{
	return (HTREEITEM)::SendMessage(this->hWnd, (UINT) TVM_GETNEXTITEM, (WPARAM)flag, (LPARAM)hItem);  
}

HTREEITEM TreeView::GetSelectedItem(HTREEITEM hItem)
{
	return GetNextItem(TVGN_CARET, hItem);
}

BOOL TreeView::GetItem(TVITEMEX& tvitem)
{
	return (BOOL)::SendMessage(this->hWnd, (UINT) TVM_GETITEM, (WPARAM)0, (LPARAM)&tvitem);  
}

BOOL TreeView::GetItemText(HTREEITEM hItem, wchar_t* buffer, int bufferSize)
{
	TVITEMEX tvitem;
	tvitem.mask = TVIF_HANDLE | TVIF_TEXT;
	tvitem.hItem = hItem;
	tvitem.pszText = buffer;
	tvitem.cchTextMax = bufferSize;
	return GetItem(tvitem);
}

BOOL TreeView::GetItemImage(HTREEITEM hItem, int& imageIndex)
{
	TVITEMEX tvitem;
	tvitem.mask = TVIF_HANDLE | TVIF_IMAGE;
	tvitem.hItem = hItem;
	BOOL f = GetItem(tvitem);
	imageIndex  = tvitem.iImage;
	return f;
}

BOOL TreeView::GetItemData(HTREEITEM hItem, LPARAM& lParam)
{
	TVITEMEX tvitem;
	tvitem.mask = TVIF_HANDLE | TVIF_PARAM;
	tvitem.hItem = hItem;
	BOOL f = GetItem(tvitem);
	lParam  = tvitem.lParam;
	return f;
}

//TVGN_CARET
//Sets the selection to the specified item. The tree-view control's parent window receives the TVN_SELCHANGING and TVN_SELCHANGED notification messages. 
//TVGN_DROPHILITE
//Redraws the specified item in the style used to indicate the target of a drag-and-drop operation.
//TVGN_FIRSTVISIBLE
//Ensures that the specified item is visible, and, if possible, displays it at the top of the control's window. Tree-view controls display as many items as will fit in the window. If the specified item is near the bottom of the control's hierarchy of items, it might not become the first visible item, depending on how many items fit in the window.
//TVSI_NOSINGLEEXPAND
BOOL TreeView::SelectItem(DWORD flag, HTREEITEM hItem)
{
	return (BOOL)::SendMessage(this->hWnd, (UINT) TVM_SELECTITEM, (WPARAM)flag, (LPARAM)hItem);  
}

BOOL TreeView::DeleteItem(HTREEITEM hItem)
{
	return (BOOL)::SendMessage(this->hWnd, (UINT) TVM_DELETEITEM, (WPARAM)0, (LPARAM)hItem);  
}

//_____________________________________________________________________ ListViewSubItem
ListViewSubItem::ListViewSubItem(void)
{
	index = -1;
	sub_index = -1;
	listControl = NULL;
}

ListViewSubItem::~ListViewSubItem(void)
{
}

int ListViewSubItem::GetItemText(wchar_t* buffer, int buffer_length)
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.mask = LVIF_TEXT;
	lvi.cchTextMax = buffer_length;
	lvi.iItem = index;
	lvi.iSubItem = sub_index;
	lvi.pszText = buffer;
	return (int)::SendMessage(this->listControl, (UINT)LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&lvi);
}

wstring ListViewSubItem::GetText()
{
	wchar_t buffer[256];
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.mask = LVIF_TEXT;
	lvi.cchTextMax = 256;
	lvi.iItem = index;
	lvi.iSubItem = sub_index;
	lvi.pszText = buffer;
	const int length =::SendMessage(this->listControl, (UINT)LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&lvi);
	return buffer;
}

void ListViewSubItem::SetText(const wstring& text)
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.mask = LVIF_TEXT;
	lvi.iItem = index;
	lvi.iSubItem = sub_index;
	lvi.pszText = (wchar_t*)text.c_str();
	::SendMessage(this->listControl, (UINT)LVM_SETITEMTEXT, (WPARAM)index, (LPARAM) (LPLVITEM)&lvi);
}

//_____________________________________________________________________ ListViewItem
ListViewItem::ListViewItem(void)
{
	index = -1;
	listControl= NULL;
}

ListViewItem::~ListViewItem(void)
{
}

Win::ListViewSubItem& ListViewItem::operator[](long index)
{
	_subItem.index = this->index;
	_subItem.sub_index = index;
	_subItem.listControl = this->listControl;
	return _subItem;
}

bool ListViewItem::Delete()
{
	return ((BOOL)::SendMessage(listControl, (UINT) LVM_DELETEITEM, (WPARAM)index, (LPARAM)0) == TRUE);
}

void ListViewItem::SetDropHiLited(bool on)
{
	this->SetState(on ? LVIS_DROPHILITED : 0, LVIS_DROPHILITED);
}

bool ListViewItem::GetBoundsRect(long index, RECT& output)
{
	output.left = LVIR_BOUNDS;
	return ((BOOL)::SendMessage(listControl, (UINT) LVM_GETITEMRECT, (WPARAM)index, (LPARAM)&output) == TRUE);
}

bool ListViewItem::GetIconRect(long index, RECT& output)
{
	output.left = LVIR_ICON;
	return ((BOOL)::SendMessage(listControl, (UINT) LVM_GETITEMRECT, (WPARAM)index, (LPARAM)&output) == TRUE);
}

bool ListViewItem::GetLabelRect(long index, RECT& output)
{
	output.left = LVIR_LABEL;
	return ((BOOL)::SendMessage(listControl, (UINT) LVM_GETITEMRECT, (WPARAM)index, (LPARAM)&output) == TRUE);
}

bool ListViewItem::GetSelectBoundsRect(long index, RECT& output)
{
	output.left = LVIR_SELECTBOUNDS;
	return ((BOOL)::SendMessage(listControl, (UINT) LVM_GETITEMRECT, (WPARAM)index, (LPARAM)&output) == TRUE);
}

int ListViewItem::GetImageIndex()
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.mask = LVIF_IMAGE;
	lvi.iItem = index;
	lvi.iSubItem = 0;
	if ((BOOL)::SendMessage(this->listControl, (UINT)LVM_GETITEM, 0, (LPARAM)&lvi))
	{
		return lvi.iImage;
	}
	return -1;
}

// Indexes start at 0
void ListViewItem::SetImageIndex(int imageIndex)
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.mask = LVIF_IMAGE;
	lvi.iItem = index;
	lvi.iSubItem = 0;
	lvi.iImage = imageIndex;
	::SendMessage(this->listControl, (UINT)LVM_SETITEM, (WPARAM)0, (LPARAM) (LPLVITEM)&lvi);
}

LPARAM ListViewItem::GetData()
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.mask = LVIF_PARAM;
	lvi.iItem = index;
	lvi.iSubItem = 0;
	if ((BOOL)::SendMessage(this->listControl, (UINT)LVM_GETITEM, 0, (LPARAM)&lvi))
	{
		return lvi.lParam;
	}
	return -1;
}

void ListViewItem::SetData(LPARAM data)
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.mask = LVIF_PARAM;
	lvi.iItem = index;
	lvi.iSubItem = 0;
	lvi.lParam = data;
	::SendMessage(this->listControl, (UINT)LVM_SETITEM, 0, (LPARAM)&lvi);
}

bool ListViewItem::GetChecked()
{
	//UINT tmp = this->GetState(LVIS_STATEIMAGEMASK);
	UINT state = ((((UINT)(this->GetState(LVIS_STATEIMAGEMASK))) >> 12) -1);
	if (state==TRUE) return true;
	return false;
}

LRESULT ListViewItem::SetState(UINT state, UINT stateMask)
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.mask =LVIF_STATE;
	lvi.iItem = index;
	lvi.state = state;
	lvi.stateMask = stateMask;
	return (BOOL)::SendMessage(this->listControl, (UINT)LVM_SETITEMSTATE, (WPARAM)index, (LPARAM)&lvi);
}

bool ListViewItem::GetSelected()
{
	UINT state = GetState(LVIS_SELECTED);
	return (state != 0);
}
	
void ListViewItem::SetSelected(bool selected)
{
	if (selected)
	{
		SetState(LVIS_SELECTED, LVIS_SELECTED);
	}
	else
	{
		SetState(0, LVIS_SELECTED);
	}
}

UINT ListViewItem::GetState(UINT mask)
{
	return (UINT)::SendMessage(this->listControl, (UINT)LVM_GETITEMSTATE, (WPARAM)index, (LPARAM)mask);
}

void ListViewItem::SetChecked(bool isChecked)
{
	this->SetState(INDEXTOSTATEIMAGEMASK((isChecked)?2:1), LVIS_STATEIMAGEMASK);
}

wstring ListViewItem::GetText(int subItemIndex)
{
	wchar_t buffer[256];
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.mask = LVIF_TEXT;
	lvi.cchTextMax = 256;
	lvi.iItem = index;
	lvi.iSubItem = subItemIndex;
	lvi.pszText = buffer;
	const int length =::SendMessage(this->listControl, (UINT)LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&lvi);
	return buffer;
}

void ListViewItem::SetText(int subItemIndex, const wstring& text)
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.mask = LVIF_TEXT;
	lvi.iItem = index;
	lvi.iSubItem = subItemIndex;
	lvi.pszText = (wchar_t*)text.c_str();
	::SendMessage(this->listControl, (UINT)LVM_SETITEMTEXT, (WPARAM)index, (LPARAM) (LPLVITEM)&lvi);
}

wstring ListViewItem::GetText()
{
	return this->GetText(0);
}

void ListViewItem::SetText(const wstring& text)
{
	this->SetText(0, text);
}

LRESULT ListViewItem::SetText(int subItemIndex, const wchar_t* text)
{	
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.mask = LVIF_TEXT;
	lvi.iItem = index;
	lvi.iSubItem = subItemIndex;
	lvi.pszText = (wchar_t*)text;
	return ::SendMessage(this->listControl, (UINT)LVM_SETITEMTEXT, (WPARAM)index, (LPARAM) (LPLVITEM)&lvi);
}

BOOL ListViewItem::GetText(int subItemIndex, wchar_t* buffer, int bufferSize)
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.mask = LVIF_TEXT;
	lvi.cchTextMax = bufferSize;
	lvi.iItem = index;
	lvi.iSubItem = subItemIndex;
	lvi.pszText = buffer;
	return (BOOL)::SendMessage(this->listControl, (UINT)LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&lvi);
}

//_____________________________________________________________________ ListViewItemCollection
ListViewItemCollection::ListViewItemCollection(void)
{
	this->iparent = NULL;
}

ListViewItemCollection::~ListViewItemCollection(void)
{
}

Win::ListViewItem& ListViewItemCollection::operator[](long index)
{
	_item.index = index;
	_item.listControl = this->iparent->GetHWND();
	return _item;
}

void ListViewItemCollection::SetParent(Win::IParent* iparent)
{
	this->iparent = iparent;
}

BOOL ListViewItemCollection::Set(LVITEM& lvitem)
{
	return (BOOL)::SendMessage(iparent->GetHWND(), (UINT)LVM_SETITEM, 0, (LPARAM)&lvitem);
}

BOOL ListViewItemCollection::Get(LVITEM& lvitem)
{
	return (BOOL)::SendMessage(iparent->GetHWND(), (UINT)LVM_GETITEM, 0, (LPARAM)&lvitem);
}

LRESULT ListViewItemCollection::Add(LVITEM& lvi)
{	
	return ::SendMessage(iparent->GetHWND(), (UINT) LVM_INSERTITEM, 0, (LPARAM) (LPLVITEM)&lvi);
}

LRESULT ListViewItemCollection::Add(int index, int imageIndex, const wchar_t* text)
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.pszText = (wchar_t*)text;
	lvi.iItem = index;
	lvi.mask = LVIF_TEXT | LVIF_IMAGE;// | LVIF_STATE ;
	lvi.iImage = imageIndex;
	return ::SendMessage(iparent->GetHWND(), (UINT) LVM_INSERTITEM, 0, (LPARAM) (LPLVITEM)&lvi);
}
	
LRESULT ListViewItemCollection::Add(int index, const wchar_t* text, int imageIndex, LPARAM userData)
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.pszText = (wchar_t*)text;
	lvi.iItem = index;
	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;// | LVIF_STATE ;
	lvi.iImage = imageIndex;
	lvi.lParam = userData;
	return ::SendMessage(iparent->GetHWND(), (UINT) LVM_INSERTITEM, 0, (LPARAM) (LPLVITEM)&lvi);
}

LRESULT ListViewItemCollection::Add(int index, const wchar_t* text)
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.pszText = (wchar_t*)text;
	lvi.iItem = index;
	lvi.mask = LVIF_TEXT;// | LVIF_STATE ;
	return ::SendMessage(iparent->GetHWND(), (UINT) LVM_INSERTITEM, 0, (LPARAM) (LPLVITEM)&lvi);
}
	
LRESULT ListViewItemCollection::Add(int index, const wchar_t* text, LPARAM userData)
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.pszText = (wchar_t*)text;
	lvi.iItem = index;
	lvi.mask = LVIF_TEXT | LVIF_PARAM;// | LVIF_STATE ;
	lvi.lParam = userData;
	return ::SendMessage(iparent->GetHWND(), (UINT) LVM_INSERTITEM, 0, (LPARAM) (LPLVITEM)&lvi);
}

LRESULT ListViewItemCollection::Add(int index, int imageIndex, const wstring& text)
{
	return Add(index, imageIndex, text.c_str());
}

LRESULT ListViewItemCollection::Add(int index, const wstring& text, int imageIndex, LPARAM data)
{
	return Add(index, text.c_str(), imageIndex, data);
}

LRESULT ListViewItemCollection::Add(int index, const wstring& text)
{
	return Add(index, text.c_str());
}

LRESULT ListViewItemCollection::Add(int index, const wstring& text, LPARAM data)
{
	return Add(index, text.c_str(), data);
}


LRESULT ListViewItemCollection::Add(int index, const wchar_t* text, int imageIndex, LPARAM data, int group_id)
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.pszText = (wchar_t*)text;
	lvi.iItem = index;
	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_GROUPID;// | LVIF_STATE ;
	lvi.iImage = imageIndex;
	lvi.lParam = data;
	lvi.iGroupId = group_id;
	return ::SendMessage(iparent->GetHWND(), (UINT) LVM_INSERTITEM, 0, (LPARAM) (LPLVITEM)&lvi);
}

LRESULT ListViewItemCollection::Add(int index, const wstring& text, int imageIndex, LPARAM data, int group_id)
{
	return Add(index, text.c_str(), imageIndex, data, group_id);
}

int ListViewItemCollection::GetCount()
{	
	return (int)::SendMessage(iparent->GetHWND(), (UINT)LVM_GETITEMCOUNT, (WPARAM)0, (LPARAM)0);
}

int ListViewItemCollection::GetIndex(const wchar_t* text)// Returns the index of the item or -1 if not found
{
	LVFINDINFO lvfi;
	lvfi.flags = LVFI_STRING;
	lvfi.psz = text;
	return (int)::SendMessage(iparent->GetHWND(), (UINT) LVM_FINDITEM, (WPARAM)-1, (LPARAM)&lvfi);  
}

LRESULT ListViewItemCollection::DeleteAll()
{	
	return ::SendMessage(iparent->GetHWND(), (UINT)LVM_DELETEALLITEMS, 0, 0);
}

LRESULT ListViewItemCollection::DeleteItem(int index)
{
	return ::SendMessage(iparent->GetHWND(), (UINT)LVM_DELETEITEM, (WPARAM)index, 0L);
}

//_____________________________________________________________________ ListViewColumn
ListViewColumn::ListViewColumn(void)
{
	this->iparent = NULL;
}

ListViewColumn::~ListViewColumn(void)
{
}

//LVCOLUMN lvcol;
//
//lvcol.mask = LVIF_FMT | LVIF_WIDTH | LVIF_TEXT;
//lvcol.fmt = LVCFMT_LEFT;
//lvcol.cx = 150;
//lvcol.pszText = L"Column 0";
//m_lv.Add(lvcol);
////
//lvcol.pszText = L"Column 1";
//m_lv.Add(lvcol);
////
//lvcol.pszText = L"Column 2";
//m_lv.Add(lvcol);
////
//lvcol.pszText = L"Column 3";
//m_lv.Add(lvcol);
LRESULT ListViewColumn::Add(LVCOLUMN& lvcolumn, int index)
{
	LRESULT lresult;
	
	lresult = ::SendMessage(iparent->GetHWND(), 
		(UINT) LVM_INSERTCOLUMN, 
		(WPARAM) (int) index, 
		(LPARAM) (LPLVCOLUMN)&lvcolumn);

	return (lresult != -1);
}

// format LVCFMT_LEFT, LVCFMT_RIGHT
LRESULT ListViewColumn::Add(int index, int format, int width, const wchar_t* text)
{
	LVCOLUMN lvcol;
	lvcol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	lvcol.fmt = format;
	lvcol.cx = width;
	lvcol.pszText = (wchar_t*)text;
	
	return ::SendMessage(iparent->GetHWND(), 
		(UINT) LVM_INSERTCOLUMN, 
		(WPARAM) (int) index, 
		(LPARAM) (LPLVCOLUMN)&lvcol);
}

// format LVCFMT_LEFT, LVCFMT_RIGHT
LRESULT ListViewColumn::Add(int index, int format, int width, const wstring& text)
{
	LVCOLUMN lvcol;
	lvcol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	lvcol.fmt = format;
	lvcol.cx = width;
	lvcol.pszText = (wchar_t*)text.c_str();
	
	return ::SendMessage(iparent->GetHWND(), 
		(UINT) LVM_INSERTCOLUMN, 
		(WPARAM) (int) index, 
		(LPARAM) (LPLVCOLUMN)&lvcol);
}


bool ListViewColumn::DeleteAll(void)
{
	const int cols = this->GetCount();
	for(int i=cols-1; i>=0; i--) 
	{
		if (Delete(i)!=TRUE) return false;
	}
	return true;
}

// Indexes start at 0
LRESULT ListViewColumn::Set(int index, LPLVCOLUMN pLvc)
{	
	return ::SendMessage(iparent->GetHWND(), (UINT)LVM_SETCOLUMN, (WPARAM)index, (LPARAM)pLvc);
}

// Indexes start at 0
LRESULT ListViewColumn::SetText(int index, const wchar_t* text)
{	
	LVCOLUMN lvcol;
	lvcol.cchTextMax = lstrlen(text);
	lvcol.mask = LVCF_TEXT;
	lvcol.pszText = (LPTSTR)text;
	return ::SendMessage(iparent->GetHWND(), (UINT)LVM_SETCOLUMN, (WPARAM)index, (LPARAM)&lvcol);
}

LRESULT ListViewColumn::GetText(int index, wchar_t* buffer, int buffer_size)
{	
	LVCOLUMN lvcol;
	lvcol.cchTextMax = buffer_size;
	lvcol.mask = LVCF_TEXT;
	lvcol.pszText = buffer;
	return ::SendMessage(iparent->GetHWND(), (UINT)LVM_GETCOLUMN, (WPARAM)index, (LPARAM)&lvcol);
}

int ListViewColumn::GetWidth(int index)
{	
	LVCOLUMN lvcol;
	lvcol.cx = 0;
	lvcol.mask = LVCF_WIDTH;
	::SendMessage(iparent->GetHWND(), (UINT)LVM_GETCOLUMN, (WPARAM)index, (LPARAM)&lvcol);
	return lvcol.cx;
}

LRESULT ListViewColumn::SetWidth(int index, int width)
{	
	LVCOLUMN lvcol;
	lvcol.cx = width;
	lvcol.mask = LVCF_WIDTH;
	return ::SendMessage(iparent->GetHWND(), (UINT)LVM_SETCOLUMN, (WPARAM)index, (LPARAM)&lvcol);
}


//if (lv.GetColFormat(0) & LVCFMT_RIGHT)
//{
//}
//else if (lv.GetColFormat(0)& LVCFMT_CENTER)
//{
//}
//else
//{
//}
int ListViewColumn::GetFormat(int index)
{	
	LVCOLUMN lvcol;
	lvcol.fmt = 0;
	lvcol.mask = LVCF_FMT;
	::SendMessage(iparent->GetHWND(), (UINT)LVM_GETCOLUMN, (WPARAM)index, (LPARAM)&lvcol);
	return lvcol.fmt;
}

int ListViewColumn::GetCount()
{
	HWND h = (HWND)::SendMessage(iparent->GetHWND(), (UINT)LVM_GETHEADER, (WPARAM)0, (LPARAM)0);
	return (int)::SendMessage(h, (UINT)HDM_GETITEMCOUNT, (WPARAM)0, (LPARAM)0); 
}

LRESULT ListViewColumn::Delete(int index)
{
	return ::SendMessage(iparent->GetHWND(), (UINT) LVM_DELETECOLUMN, (WPARAM)index, 0);
}

void ListViewColumn::SetParent(Win::IParent* iparent)
{
	this->iparent = iparent;
}

//_____________________________________________________________________ LVDropInfo

//_____________________________________________________________________ListView
bool ListView::bInit = false;

ListView::ListView(void)
{
	if (bInit==false)
	{
		INITCOMMONCONTROLSEX cc;
		cc.dwSize=sizeof(INITCOMMONCONTROLSEX);
		cc.dwICC=ICC_LISTVIEW_CLASSES;
		::InitCommonControlsEx(&cc);
		bInit=true;
	}
	Cols.SetParent(this);
	Items.SetParent(this);
	//imageList = NULL;
	//________________________ Drag & Drop
	isDragging = false;
	dragItemIndex = -1;
}

ListView::~ListView(void)
{
}

//LV_VIEW_ICON, LV_VIEW_DETAILS, LV_VIEW_SMALLICON, LV_VIEW_LIST, LV_VIEW_TILE, LV_VIEW_MAX  
void ListView::SetView(int view)
{
	::SendMessage(hWnd, LVM_SETVIEW, (WPARAM)(DWORD)(view), (LPARAM)0);
}

//LV_VIEW_ICON, LV_VIEW_DETAILS, LV_VIEW_SMALLICON, LV_VIEW_LIST, LV_VIEW_TILE, LV_VIEW_MAX  
int ListView::GetView()
{
	return (int)::SendMessage(hWnd, LVM_GETVIEW, (WPARAM)0, (LPARAM)0);
}

Win::ListViewColumn& ListView::GetColumns()
{
	return _cols;
}

//Win::ListViewItemCollection& ListView::GetItems()
//{
//	return Items;
//}

void ListView::ReportError(bool error, wchar_t* description)
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.pszText = description;
	lvi.iItem = 10000;
	lvi.mask = LVIF_TEXT | LVIF_IMAGE;// | LVIF_STATE ;
		
	if (error)
	{
		lvi.iImage = 1;
	}
	else
	{
		lvi.iImage = 0; // No error
	}
	::SendMessage(hWnd, (UINT) LVM_INSERTITEM, 0, (LPARAM) (LPLVITEM)&lvi);
	this->Scroll(0, 18);
}

void ListView::BeginDrag(Win::Event& e)
{
	NMLISTVIEW * nmlv = (NMLISTVIEW *)e.lParam;
	this->dragItemIndex = nmlv->iItem;
	//
	POINT point;
	point.x = 0;
	point.y = 0;
	//_______________________________________________ Option 1
	this->isDragging = true;
	cursor.CreateDragDrop(this->hInstance);
	::SetCapture(::GetParent(hWnd));
	::SetCursor(cursor.GetHCursor());
	::ShowCursor(TRUE);
	//_______________________________________________ Option 2
	//imageList = (HIMAGELIST)::SendMessage(hWnd, LVM_CREATEDRAGIMAGE, 
	//	(WPARAM)dragItemIndex, (LPARAM)&point);
	//if (imageList==NULL) return;
	//if (ImageList_BeginDrag(imageList, 0, 0, 0))
	//{
	//	ImageList_DragShowNolock(TRUE);
	//	::SetCapture(::GetParent(hWnd));
	//	::ShowCursor(FALSE);
	//	this->isDragging = true;
	//}
}

void ListView::Drag(Win::Event& e, Win::ListView& listViewTarget) // Call this on mouse move
{
	if (this->isDragging==false) return;
	int x = LOWORD(e.lParam);
	int y = HIWORD(e.lParam);
	//RECT rc;
	//::GetWindowRect(hWnd, &rc);
	//ImageList_DragMove(x+rc.left, y+rc.top);
	//ImageList_DragShowNolock(FALSE);

	::SetCursor(cursor.GetHCursor());
	::ShowCursor(TRUE);

	if (listViewTarget.dragItemIndex!=-1)
	{
		listViewTarget.Items[listViewTarget.dragItemIndex].SetState(0, LVIS_DROPHILITED);
		listViewTarget.Redraw(NULL, NULL, RDW_UPDATENOW);
	}

	POINT point;
	point.x = x;
	point.y = y;
	if (::ChildWindowFromPoint(::GetParent(hWnd), point)==listViewTarget.GetHWND())
	{
		RECT rcHeadCell;
		HWND header = listViewTarget.GetHeaderControl();
		::SendMessage(header, HDM_GETITEMRECT, (WPARAM)0, (LPARAM)&rcHeadCell);
		RECT rcParent;
		::GetWindowRect(::GetParent(listViewTarget), &rcParent);
		RECT rcTarget;
		::GetWindowRect(listViewTarget, &rcTarget);
		//listViewTarget.window.GetRect(rcTarget);
		const int offset = rcHeadCell.bottom-rcHeadCell.top;

		LVHITTESTINFO hitinfo;

		hitinfo.pt.x = x - (rcTarget.left-rcParent.left);
		hitinfo.pt.y = y - (rcTarget.top-rcParent.top)+offset;
		listViewTarget.dragItemIndex = listViewTarget.GetHitTestItemIndex(hitinfo);    
		if (listViewTarget.dragItemIndex!=-1)
		{
			listViewTarget.Items[listViewTarget.dragItemIndex].SetState(LVIS_DROPHILITED, LVIS_DROPHILITED);
			listViewTarget.Redraw(NULL, NULL, RDW_UPDATENOW);
		}
	}   
	//ImageList_DragShowNolock(TRUE);
}

// client coordinates
int ListView::GetHitTestItemIndex(LVHITTESTINFO& hitTestInfo)
{
	return (int)::SendMessage(this->hWnd, LVM_HITTEST, (WPARAM)0, (LPARAM)&hitTestInfo);
	//return hitTestInfo.iItem;
}

// Call this on Window_LButtonUp using the input list view, use return LVDropInfo
// when LVDropInfo.sourceItemIndex and LVDropInfo.targetItemIndex are -1 that user
// cancelled the operation by droping outside the the target list view control
LVDropInfo ListView::Drop(Win::Event& e, Win::ListView& listViewTarget)
{
	LVDropInfo di;
	di.sourceItemIndex = -1;
	di.targetItemIndex = -1;

	if (this->isDragging)
	{
		cursor.Delete();
		::SetCursor(::LoadCursor(NULL, IDC_ARROW));
		::ReleaseCapture();
		//ImageList_EndDrag();
		//ImageList_Destroy(this->imageList);
		//this->imageList = NULL;
		::ShowCursor(TRUE);
		this->isDragging = false;
		di.sourceItemIndex = this->dragItemIndex;
		this->dragItemIndex = -1;

		if (listViewTarget.dragItemIndex!=-1)
		{
			listViewTarget.Items[listViewTarget.dragItemIndex].SetState(0, LVIS_DROPHILITED);
			listViewTarget.Redraw(NULL, NULL, RDW_UPDATENOW);
			di.targetItemIndex = listViewTarget.dragItemIndex;
			listViewTarget.dragItemIndex = -1;
		}  
		if (di.targetItemIndex == -1)
		{
			RECT rectTarget;
			::GetWindowRect(listViewTarget.hWnd, &rectTarget);
			::MapWindowPoints(NULL, ::GetParent(listViewTarget.hWnd), (LPPOINT)&rectTarget, 2);
			POINT pt;
			pt.x = LOWORD(e.lParam);
			pt.y = HIWORD(e.lParam);
			if (::PtInRect(&rectTarget, pt) == TRUE)
			{
				//_________________________ Insert at the end
				di.targetItemIndex = listViewTarget.Items.Count;
			}
			else
			{
				//_________________________ Cancel
				di.sourceItemIndex = -1;
				di.targetItemIndex = -1;
			}
		}
		this->SetSelected(-1, false);
	}
	return di;
}

bool ListView::GetSubItemRect(int itemIndex, int subItemIndex, RECT& output)
{
	output.top = subItemIndex;
	output.left = LVIR_BOUNDS;
	return (::SendMessage(hWnd, LVM_GETSUBITEMRECT, itemIndex, (LPARAM)&output) != 0);
}

bool ListView::GetSubItemRect(int itemIndex, int subItemIndex, int flags, RECT& output) // flags: LVIR_BOUNDS, LVIR_ICON, LVIR_LABEL 
{
	output.top = subItemIndex;
	output.left = flags;
	return (::SendMessage(hWnd, LVM_GETSUBITEMRECT, itemIndex, (LPARAM)&output) != 0);
}

void ListView::Print(Win::Gdi& gdi, Win::PrintInfo pi)
{
	const int colCount = Cols.GetCount();
	int total_width = 0;
	int i;
	const int offsetX = (int)(pi.height*0.3+0.5);
	const int offsetY = (int)(pi.height*0.1+0.5);

	for(i=0; i<colCount; i++) total_width += Cols.GetWidth(i);

	
	Win::Gdi::Pen pen;
	bool isHeader = pi.index==0;
	//___________________________________________________________________ Font
	Win::Gdi::Font font;
	LOGFONT logfont;
	Win::Gdi::Font::InitializeLogfont(logfont); 
	HFONT hfont = (HFONT)::SendMessage(hWnd, WM_GETFONT, 0, 0);
	if (hfont == NULL)
	{
		font.Create(L"Arial", (int)(pi.height*0.7+0.5), isHeader, false, false, false);
	}
	else
	{
		if (::GetObject(hfont, sizeof(LOGFONT), &logfont)!=0 )
		{
			logfont.lfHeight = - (int)(pi.height*0.7+0.5);
			logfont.lfWeight = isHeader ? 700 : 0;
			font.Create(logfont);
		}
		else
		{
			font.Create(L"Arial", (int)(pi.height*0.7+0.5), isHeader, false, false, false);
		}
	}

	pen.Create(PS_SOLID, (int)2, RGB(0, 0, 0));
	gdi.SelectPen_(pen);
	//_________________________________________________ Vertical Lines
	gdi.Line(0, pi.position.y, 0, pi.position.y+pi.height);
	for(i=0; i<colCount-1; i++)
	{
		pi.position.x += (int)((double)Cols.GetWidth(i)*(double)pi.width/(double)total_width+0.5);
		gdi.Line(pi.position.x, pi.position.y, pi.position.x, pi.position.y+pi.height);
	}
	gdi.Line(pi.pageWidth, pi.position.y, pi.pageWidth, pi.position.y+pi.height);
	//_________________________________________________ Text
	wchar_t text[1024];
	SIZE size;
	gdi.SelectFont_(font);
	gdi.SetTextColor(RGB(0, 0, 0));
	pi.position.x = 0;
	int colWidth = 0;

	for(i=0; i<colCount; i++)
	{
		if (isHeader)
		{
			this->Cols.GetText(i, text, 1024);
		}
		else
		{
			this->Items[pi.index-1].GetText(i, text, 1024);
		}
		colWidth = (int)((double)Cols.GetWidth(i)*(double)pi.width/(double)total_width+0.5);
		if (Cols.GetFormat(i) & LVCFMT_RIGHT)
		{
			gdi.SetTextAlign(TA_RIGHT | TA_TOP);
			if (i==colCount-1)
			{
				//gdi.TextOut(pi.width-offsetX, pi.position.y+offsetY, text);
				gdi.TextOutTruncate(pi.width-offsetX, pi.position.y+offsetY, text, colWidth, true, false);
			}
			else
			{
				//gdi.TextOut(pi.position.x+colWidth-offsetX, pi.position.y+offsetY, text);
				gdi.TextOutTruncate(pi.position.x+colWidth-offsetX, pi.position.y+offsetY, text, colWidth, true, false);
			}
		}
		else if (Cols.GetFormat(i)& LVCFMT_CENTER)
		{
			gdi.SetTextAlign(TA_LEFT | TA_TOP);
			gdi.GetTextExtentPoint32W(text, size);
			//gdi.TextOut(pi.position.x+(colWidth-size.cx)/2, pi.position.y+offsetY, text);
			//gdi.TextOutTruncate(pi.position.x+(colWidth-size.cx)/2, pi.position.y+offsetY, text, colWidth, true, true);
			gdi.TextOutTruncate(pi.position.x, pi.position.y+offsetY, text, colWidth, true, true);
		}
		else //_________________________ LEFT
		{
			gdi.SetTextAlign(TA_LEFT | TA_TOP);
			//gdi.TextOut(pi.position.x+offsetX, pi.position.y+offsetY, text);
			gdi.TextOutTruncate(pi.position.x+offsetX, pi.position.y+offsetY, text, colWidth, true, false);
		}
		pi.position.x += colWidth;
	}
	//______________________________________________ top line
	if (pi.isFirst || pi.isFirstOnPage) 
	{
		gdi.Line(0, pi.position.y, pi.pageWidth, pi.position.y);
	}
	//______________________________________________ bottom line
	if (pi.isLast || pi.isLastOnPage || isHeader || (LVS_EX_GRIDLINES & GetExtStyle()) )
	{
		gdi.Line(0, pi.position.y+pi.height, pi.pageWidth, pi.position.y+pi.height);
	}
}

bool ListView::EnableGroupView(bool groupView)
{
	BOOL f = groupView ? TRUE : FALSE;
	return (::SendMessage(hWnd, LVM_ENABLEGROUPVIEW, (WPARAM)f, (LPARAM)NULL)!=-1);
}

// You need to call EnableGroupView for this API to work and have Windows XP styles enabled
// align: LVGA_HEADER_CENTER, LVGA_HEADER_LEFT, LVGA_HEADER_RIGHT
LRESULT ListView::InsertGroup(int index, int groupId, LPWSTR text, UINT align)
{
	LVGROUP lvg;

	lvg.cbSize = sizeof(LVGROUP);
	lvg.mask = LVGF_ALIGN | LVGF_GROUPID | LVGF_HEADER;
	lvg.pszHeader = text;
	lvg.cchHeader = (int)wcslen(text);
	lvg.pszFooter = NULL;
	lvg.cchFooter = 0;
	lvg.iGroupId = groupId;
	lvg.stateMask = 0;
	lvg.state = LVGS_NORMAL;
	lvg.uAlign = align;
	return ::SendMessage(hWnd, LVM_INSERTGROUP, (WPARAM)index, (LPARAM)(PLVGROUP) &lvg); 
}

LRESULT ListView::InsertItemIntoGroup(int index, wchar_t* text, int imageIndex, int groupId)
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.pszText = text;
	lvi.iItem = index;
	lvi.mask = LVIF_TEXT | LVIF_GROUPID | LVIF_IMAGE;
	lvi.iImage = imageIndex;
	lvi.iGroupId = groupId;
	return ::SendMessage(this->hWnd, (UINT) LVM_INSERTITEM, 0, (LPARAM) (LPLVITEM)&lvi);
}

LRESULT ListView::InsertItemIntoGroup(int index, wchar_t* text, int imageIndex, LPARAM userData, int groupId)
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.pszText = text;
	lvi.iItem = index;
	lvi.mask =  LVIF_TEXT | LVIF_GROUPID | LVIF_IMAGE | LVIF_PARAM;
	lvi.iImage = imageIndex;
	lvi.iGroupId = groupId;
	lvi.lParam = userData;
	return ::SendMessage(this->hWnd, (UINT) LVM_INSERTITEM, 0, (LPARAM) (LPLVITEM)&lvi);
}

LRESULT ListView::InsertItemIntoGroup(int index, wchar_t* text, int groupId)
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.pszText = text;
	lvi.iItem = index;
	lvi.mask = LVIF_TEXT | LVIF_GROUPID;// | LVIF_STATE ;
	lvi.iGroupId = groupId;
	return ::SendMessage(this->hWnd, (UINT) LVM_INSERTITEM, 0, (LPARAM) (LPLVITEM)&lvi);
}

LRESULT ListView::InsertItemIntoGroup(int index, wchar_t* text, LPARAM userData, int groupId)
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.pszText = text;
	lvi.iItem = index;
	lvi.mask = LVIF_TEXT | LVIF_GROUPID | LVIF_PARAM ;
	lvi.iGroupId = groupId;
	lvi.lParam = userData;
	return ::SendMessage(this->hWnd, (UINT) LVM_INSERTITEM, 0, (LPARAM) (LPLVITEM)&lvi);
}

// flags: LVNI_ALL, LVNI_FOCUSED, LVNI_SELECTED
// index should be -1 on the first call, next calls should use the returned index on the previous call to the function
int ListView::GetNextIndex(int index, DWORD flags)
{
	return (int)::SendMessage(hWnd, LVM_GETNEXTITEM, (WPARAM)index, MAKELPARAM((flags), 0));
}

// The selection is lost if another GUI is open
// Returns -1 when done
int ListView::GetNextSelectedIndex(int index) // Use this for multiple item selection:  index should be -1 the first time, next calls index must be the previous return value
{
	return (int)::SendMessage(hWnd, LVM_GETNEXTITEM, (WPARAM)index, MAKELPARAM((LVNI_SELECTED), 0));
	//return (int)::SendMessage(hWnd, LVM_GETNEXTITEM, (WPARAM)(index), LVNI_SELECTED | LVNI_BELOW);
}

// data[0] must be an integer primary key and it is stored as user data. Columns: data[1], data[2]...
void ListView::Enumerate(wchar_t** data, int colCount, int rowIndex)
{
	if (colCount==Cols.GetCount()+1)
	{
		LPARAM userData;

		userData = (LPARAM)_wtoi(data[0]);
		this->Items.Add(rowIndex, data[1], userData);
		for(int i=2; i<colCount; i++) this->Items[rowIndex].SetText(i-1, data[i]);
	}
	else if (colCount==Cols.GetCount())
	{
		this->Items.Add(rowIndex, data[0]);
		for(int i=1; i<colCount; i++) this->Items[rowIndex].SetText(i, data[i]);
	}
}

//LVS_EX_LABELTIP
//LVS_EX_FULLROWSELECT
//LVS_EX_CHECKBOXES
//SetExtStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
LRESULT ListView::SetExtStyle(DWORD dwExMask, DWORD dwExStyle)
{
	return  ::SendMessage(this->hWnd, 
		(UINT) LVM_SETEXTENDEDLISTVIEWSTYLE, 
		(WPARAM) (DWORD) dwExMask, 
		(LPARAM) (DWORD)dwExStyle);
}

//if (LVS_EX_GRIDLINES & GetExtStyle)
//{
//}
LRESULT ListView::GetExtStyle()
{
	return  ::SendMessage(this->hWnd, (UINT) LVM_GETEXTENDEDLISTVIEWSTYLE, (WPARAM)0, (LPARAM)0);
}

bool ListView::CopyToClipboard()
{
	const wchar_t * delimiter = L"\t";
	const wchar_t * newLine = L"\r\n";
	const int len_delimiter = lstrlen(delimiter);
	const int len_newLine = lstrlen(newLine);
	const int colCount = this->Cols.GetCount();
	const int rowCount = this->Items.GetCount();
	int i, j;
	int totalLength = 0;
	wchar_t texto[256];
	//____________________________________________ Compute Text Length
	for(j=0; j<colCount; j++)
	{
		this->GetHeaderText(j, texto, 256);
		totalLength+=(lstrlen(texto)+len_delimiter);
	}
	totalLength+=len_newLine;
	for(i=0; i<rowCount; i++)
	{
		for(j=0; j<colCount; j++)
		{
			this->Items[i].GetText(j, texto, 256);
			totalLength+=(lstrlen(texto)+len_delimiter);
		}
		totalLength+=len_newLine;
	}

	//____________________________________________ Copy text to clipboard
	HGLOBAL hGlobal;
	wchar_t* pGlobal;
	bool bOk = false;

	hGlobal = GlobalAlloc(GHND | GMEM_SHARE, (totalLength+1)*sizeof(wchar_t));
	if (hGlobal)
	{
		pGlobal = (wchar_t*)GlobalLock(hGlobal);
		pGlobal[0]='\0';
		for(j=0; j<colCount; j++)
		{
			this->GetHeaderText(j, texto, 256);
			lstrcat(pGlobal, texto);
			if (j == colCount-1) break;
			lstrcat(pGlobal, delimiter);
		}
		lstrcat(pGlobal, newLine);
		for(i=0; i<rowCount; i++)
		{
			for(j=0; j<colCount; j++)
			{
				this->Items[i].GetText(j, texto, 256);
				lstrcat(pGlobal, texto);
				if (j == colCount-1) break;
				lstrcat(pGlobal, delimiter);
			}
			lstrcat(pGlobal, newLine);
		}
		GlobalUnlock(hGlobal);
		if (OpenClipboard(hWnd))
		{
			if (EmptyClipboard())
			{
#ifdef UNICODE
				bOk = (SetClipboardData(CF_UNICODETEXT, hGlobal) != NULL);
#else
				bOk = (SetClipboardData(CF_TEXT, hGlobal) != NULL);
#endif
			}
			CloseClipboard();
		}
	}
	return bOk;
}

bool ListView::SaveWebFile(const wchar_t* pszFileName)
{
	return this->SaveToFile(pszFileName, L"<td bgcolor=#efffff>", L"</td>", L"<tr>", L"</tr>\r\n", 
		L"<html><head></head><body>\r\n<table border=1 bgcolor=#c0c0c0 cellpadding=3 cellspacing=3>",
		L"</table></body></html>"
		);
}

bool ListView::CopyLatexToCliboard(bool isNumber)
{
	const wchar_t * hdrIni = L"\\hline \\multicolumn{1}{|c|}{";
	const wchar_t * hdr = L"} & multicolumn{1}{|c|}{";
	const wchar_t * hdrEnd = L"}\\\\\r\n\\hline\r\n";
	const wchar_t * data = L" & ";
	const wchar_t *  dataEnd= L"\\\\\r\n";
	//
	const int len_hdrIni = lstrlen(hdrIni);
	const int len_hdr = lstrlen(hdr);
	const int len_hdrEnd = lstrlen(hdrEnd);
	const int len_data = lstrlen(data);
	const int len_dataEnd = lstrlen(dataEnd);
	//
	const int colCount = this->Cols.GetCount();
	const int rowCount = this->Items.GetCount();
	int i, j;
	int totalLength = len_hdrIni;

	if (isNumber) totalLength+=(colCount*rowCount*2);

	wchar_t texto[256];
	//____________________________________________ Compute Text Length
	for(j=0; j<colCount; j++)
	{
		this->GetHeaderText(j, texto, 256);
		totalLength+=lstrlen(texto);
		if (j==colCount-1)
		{
			totalLength+=len_hdrEnd;
		}
		else
		{
			totalLength+=len_hdr;
		}
	}
	for(i=0; i<rowCount; i++)
	{
		for(j=0; j<colCount; j++)
		{
			this->Items[i].GetText(j, texto, 256);
			totalLength+=lstrlen(texto);
			if (j==colCount-1)
			{
				totalLength+=len_dataEnd;
			}
			else
			{
				totalLength+=len_data;
			}
		}
	}

	//____________________________________________ Copy text to clipboard
	HGLOBAL hGlobal;
	wchar_t* pGlobal;
	bool bOk = false;

	hGlobal = GlobalAlloc(GHND | GMEM_SHARE, (totalLength+1)*sizeof(wchar_t));
	if (hGlobal)
	{
		pGlobal = (wchar_t*)GlobalLock(hGlobal);
		pGlobal[0]='\0';
		lstrcat(pGlobal, hdrIni);
		for(j=0; j<colCount; j++)
		{
			this->GetHeaderText(j, texto, 256);
			lstrcat(pGlobal, texto);
			if (j==colCount-1)
			{
				lstrcat(pGlobal, hdrEnd);
			}
			else
			{
				lstrcat(pGlobal, hdr);
			}
		}
		for(i=0; i<rowCount; i++)
		{
			for(j=0; j<colCount; j++)
			{
				if (isNumber) lstrcat(pGlobal, L"$");
				this->Items[i].GetText(j, texto, 256);
				lstrcat(pGlobal, texto);
				if (isNumber) lstrcat(pGlobal, L"$");
				if (j==colCount-1)
				{
					lstrcat(pGlobal, dataEnd);
				}
				else
				{
					lstrcat(pGlobal, data);
				}
			}

		}
		GlobalUnlock(hGlobal);
		if (OpenClipboard(hWnd))
		{
			if (EmptyClipboard())
			{
				bOk = (SetClipboardData(CF_UNICODETEXT, hGlobal) != NULL);
			}
			CloseClipboard();
		}
	}
	return bOk;
}

int ListView::GetSelectedCount()
{
	return (int)::SendMessage(this->hWnd, (UINT)LVM_GETSELECTEDCOUNT, 0, 0);
}

int ListView::GetSelectedIndex() // Returns -1 if error
{
	//int nIndex=-1;
	//int nCount=0;
	//int i=0;

	//nCount=GetSelectedCount();
	//if (nCount!=1) return -1;
	return (int)ListView_GetNextItem(this->hWnd, -1, LVNI_SELECTED);
	//for(i=0; i<nCount; i++)
	//{
	//	nIndex=ListView_GetNextItem(this->hWnd, i, LVNI_SELECTED);
	//	if (nIndex<0)
	//	{
	//		nIndex=0;
	//		break;
	//	}
	//}
	//return nIndex;
}

bool ListView::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_NOTIFY) return false;
	NMHDR* pNMHDR= (LPNMHDR)e.lParam; 
     if (pNMHDR->hwndFrom!=this->GetHWND()) return false;
     if (pNMHDR->code!=notification) return false; 
	return true;
}

bool ListView::SaveLatexToFile(const wchar_t* filename)
{
	int nColCount = this->Cols.GetCount();
	bool bOk = true;
	HANDLE h;
	DWORD  dwBytesWritten = 0;
	WORD wByteOrderMark = 0xFEFF;
	int nToWrite = 0;
	wchar_t sz[1024];

	h = ::CreateFile (filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (INVALID_HANDLE_VALUE == h) return false;

	#ifdef UNICODE
	::WriteFile (h, &wByteOrderMark, 2, &dwBytesWritten, NULL) ;
	#endif

	lstrcpy(sz, L"\\hline ");
	nToWrite = lstrlen(sz);
	::WriteFile (h, sz, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
	if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
	{
		return false;
	}

	//************************************************ Write Header
	for(int col = 0; col<nColCount; col++)
	{
		if (col ==0)
		{
			lstrcpy(sz, L"\\multicolumn{1}{|c||}{");
		}
		else
		{
			lstrcpy(sz, L"\\multicolumn{1}{|c|}{");
		}
		nToWrite = lstrlen(sz);
		::WriteFile (h, sz, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
		if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
		{
			bOk = false;
			break;
		}
		if (this->GetHeaderText(col, sz, 1024))
		{
			if (col <nColCount-1)
			{
				lstrcat(sz, L"} & ");
			}
			else
			{
				lstrcat(sz, L"}");
			}
			nToWrite = lstrlen(sz);
			::WriteFile (h, sz, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
			if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
			{
				bOk = false;
				break;
			}
		}
	}

	lstrcpy(sz, L"\\\\\r\n");
	nToWrite = lstrlen(sz);
	::WriteFile (h, sz, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
	if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
	{
		bOk = false;
	}

	//******************************************************* Write Data
	for(int row = 0; row<Items.GetCount(); row++)
	{
		lstrcpy(sz, L"\\hline ");
		nToWrite = lstrlen(sz);
		::WriteFile (h, sz, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
		if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
		{
			bOk = false;
			break;
		}
		for(int col = 0; col<nColCount; col++)
		{
			if (this->Items[row].GetText(col, sz, 1024))
			{
				if (col <nColCount-1)
				{
					lstrcat(sz, L" & ");
				}
				else
				{
					lstrcat(sz, L" ");
				}
				nToWrite = lstrlen(sz);
				::WriteFile (h, sz, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
				if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
				{
					bOk = false;
					break;
				}
			}
		}
		lstrcpy(sz, L"\\\\\r\n");
		nToWrite = lstrlen(sz);
		::WriteFile (h, sz, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
		if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
		{
			bOk = false;
			break;
		}
		if (bOk==false) break;
	}

	//
	 if (h) CloseHandle(h);
	 return bOk;
}


// Indexes start at 0. Use nItemIndex=-1 to affect all rows
LRESULT ListView::SetSelected(int itemIndex, bool selected)
{
	LVITEM lvi;
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.mask = LVIF_STATE;
	lvi.iItem = itemIndex;
	lvi.iSubItem = 0;
	lvi.state = selected ? LVIS_SELECTED : 0;
	lvi.stateMask = LVIS_SELECTED;
	return ::SendMessage(this->hWnd, (UINT)LVM_SETITEMSTATE, (WPARAM)itemIndex, (LPARAM) (LPLVITEM)&lvi);
}

BOOL ListView::Scroll(int deltaX, int deltaY)
{
	return (BOOL)::SendMessage(this->hWnd, (UINT) LVM_SCROLL, (WPARAM)deltaX, (LPARAM)deltaY);  
}

BOOL ListView::Scroll()
{
	return (BOOL)::SendMessage(this->hWnd, (UINT) LVM_SCROLL, (WPARAM)0, (LPARAM)16);  
}

BOOL ListView::RedrawItems(int indexIni, int indexEnd)
{
	BOOL b  = (BOOL)::SendMessage(this->hWnd, (UINT) LVM_REDRAWITEMS, 
		(WPARAM)indexIni, (LPARAM)indexEnd);
	this->Update();
	return b;  
}

HWND ListView::GetHeaderControl()
{	
	return (HWND)::SendMessage(this->hWnd, (UINT)LVM_GETHEADER, (WPARAM)0, (LPARAM)0);
}

BOOL ListView::GetHeaderText(int index, wchar_t* pszBuffer, int nBufferSize)
{	
	HWND h = GetHeaderControl();
	HDITEM hitem;
	hitem.mask = HDI_TEXT;
	hitem.cchTextMax = nBufferSize;
	hitem.pszText = pszBuffer;

	return (::SendMessage(h, (UINT)HDM_GETITEM, (WPARAM)index, (LPARAM)&hitem)==TRUE);
}

LRESULT ListView::SetBkColor_(COLORREF rgb)
{
	return ::SendMessage(this->hWnd, (UINT)LVM_SETBKCOLOR, (WPARAM)0, (LPARAM)rgb);
}

// Indexes start at 0
LRESULT ListView::SetImageList(HIMAGELIST hil, bool bSmall)
{
	return ::SendMessage(this->hWnd, (UINT)LVM_SETIMAGELIST, 
		(WPARAM)bSmall ? LVSIL_SMALL : LVSIL_NORMAL, 
		(LPARAM)hil);
}

//bool ListView::SaveCsvFile(const wchar_t* pszFileName)
//{
//	int colCount = this->GetColCount();
//	int rowCount = this->GetItemCount();
//	DWORD  dwBytesWritten = 0;
//	int nToWrite = 0;
//	char sz[1024];
//	int i, j;
//
//
//	//************************************************ Write Header
//	HWND h = GetHeaderControl();
//	HDITEMA hitem;
//	hitem.mask = HDI_TEXT;
//	hitem.cchTextMax = 1024;
//	hitem.pszText = sz;
//
//	for(j = 0; j<colCount; j++)
//	{
//		if (::SendMessage(h, (UINT)HDM_GETITEMA, (WPARAM)j, (LPARAM)&hitem))
//		{
//			if (j<colCount-2) strcat(sz, ", ";
//			nToWrite = (int)strlen(sz);
//			::WriteFile (hFile, sz, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
//			if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
//			{
//				return false;
//			}
//		}
//	}
//
//	strcpy(sz, "\r\n";
//	nToWrite = (int)strlen(sz);
//	::WriteFile (hFile, sz, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
//	if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
//	{
//		return false;
//	}
//
//	ZeroMemory(&m_lvi, sizeof(LVITEM));
//	m_lvi.mask = LVIF_TEXT;
//	m_lvi.cchTextMax = 1024;
//	m_lvi.pszText = sz;
//	m_lvi.iItem = row;
//	m_lvi.iSubItem = col;
//	return (BOOL)::SendMessage(this->hWnd, (UINT)LVM_GETITEMTEXT, (WPARAM)row, (LPARAM)&m_lvi);
//
//	for(i=0; i<rowCount; i++)
//	{
//		for(j = 0; j<colCount; j++)
//		{
//			if (GetItemText(i, j, sz, 1024))
//			{
//				if (j<colCount-2) strcat(sz, ", ";
//				nToWrite = (int)strlen(sz);
//				::WriteFile (hFile, sz, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
//				if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
//				{
//					return false;
//				}
//			}
//			if (i<rowCount-2) strcpy(sz, "\r\n";
//			nToWrite = (int)strlen(sz);
//			::WriteFile (hFile, sz, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
//			if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
//			{
//				return false;
//			}
//		}
//	}
//}

bool ListView::SaveToFile(const wchar_t* pszFileName)
{
	return this->SaveToFile(pszFileName, L"", L", ", L"", L"\r\n", NULL, NULL);
}

bool ListView::SaveToFile(HANDLE hFile, const wchar_t* colIni, const wchar_t* colEnd,
		const wchar_t* rowIni, const wchar_t* rowEnd, const wchar_t* headIni, const wchar_t* headEnd, bool includeHeader)
{
	int nColCount = this->Cols.GetCount();
	DWORD  dwBytesWritten = 0;
	int nToWrite = 0;
	wchar_t sz[1024];

	//********************************************************* headIni
	if (headIni)
	{
		nToWrite = lstrlen(headIni);
		::WriteFile (hFile, headIni, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
		if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
		{
			return false;
		}
	}


	if (includeHeader)
	{
		nToWrite = lstrlen(rowIni);
		::WriteFile (hFile, rowIni, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
		if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
		{
			return false;
		}

		//************************************************ Write Header
		for(int col = 0; col<nColCount; col++)
		{
			nToWrite = lstrlen(colIni);
			::WriteFile (hFile, colIni, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
			if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
			{
				return false;
			}
			if (this->GetHeaderText(col, sz, 1024))
			{
				nToWrite = lstrlen(sz);
				::WriteFile (hFile, sz, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
				if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
				{
					return false;
				}
				if (col!=nColCount-1 || wcschr(colEnd, ',')==NULL)
				{
					nToWrite = lstrlen(colEnd);
					::WriteFile (hFile, colEnd, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
					if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
					{
						return false;
					}
				}
			}
		}

		nToWrite = lstrlen(rowEnd);
		::WriteFile (hFile, rowEnd, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
		if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
		{
			return false;
		}
	}

	//******************************************************* Write Data
	for(int row = 0; row<Items.GetCount(); row++)
	{
		nToWrite = lstrlen(rowIni);
		::WriteFile (hFile, rowIni, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
		if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
		{
			return false;
		}
		for(int col = 0; col<nColCount; col++)
		{
			nToWrite = lstrlen(colIni);
			::WriteFile (hFile, colIni, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
			if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
			{
				return false;
			}
			if (this->Items[row].GetText(col, sz, 1024))
			{
				nToWrite = lstrlen(sz);
				::WriteFile (hFile, sz, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
				if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
				{
					return false;
				}
				if (col!=nColCount-1 || wcschr(colEnd, ',')==NULL)
				{
					nToWrite = lstrlen(colEnd);
					::WriteFile (hFile, colEnd, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
					if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
					{
						return false;
					}
				}
			}
		}
		nToWrite = lstrlen(rowEnd);
		::WriteFile (hFile, rowEnd, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
		if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
		{
			return false;
		}
	}

	//************************************************ headEnd
	if (headEnd)
	{
		nToWrite = lstrlen(headEnd);
		::WriteFile (hFile, headEnd, nToWrite * sizeof (wchar_t), &dwBytesWritten, NULL) ; 
		if ((nToWrite * sizeof (wchar_t)) != (int) dwBytesWritten) 
		{
			return false;
		}
	}
	return true;
}

bool ListView::SaveToFile(const wchar_t* filename, const wchar_t* colIni, const wchar_t* colEnd,
		const wchar_t* rowIni, const wchar_t* rowEnd, const wchar_t* docIni, const wchar_t* docEnd)
{
	bool bOk = true;
	HANDLE h;
	DWORD  dwBytesWritten = 0;
	WORD wByteOrderMark = 0xFEFF;

	h = ::CreateFile (filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (INVALID_HANDLE_VALUE == h) return false;

	#ifdef UNICODE
	::WriteFile (h, &wByteOrderMark, 2, &dwBytesWritten, NULL) ;
	#endif
	
	bOk = this->SaveToFile(h, colIni, colEnd, rowIni, rowEnd, docIni, docEnd, true);
	//
	if (h!=INVALID_HANDLE_VALUE) ::CloseHandle(h);
	 return bOk;
}

//__________________________________________________________ ASCII version
bool ListView::SaveToFileA(const wchar_t* filename)
{
	return this->SaveToFile(filename, "", ", ", "", "\r\n", NULL, NULL);
}

//__________________________________________________________ ASCII version
bool ListView::SaveToFile(HANDLE hFile, const char* colIni, const char* colEnd,
		const char* rowIni, const char* rowEnd, const char* headIni, const char* headEnd, bool includeHeader)
{
	int nColCount = this->Cols.GetCount();
	DWORD  dwBytesWritten = 0;
	int nToWrite = 0;
	char sz[1024];
	wchar_t szw[1024];

	//********************************************************* headIni
	if (headIni)
	{
		nToWrite = (int)strlen(headIni);
		::WriteFile (hFile, headIni, nToWrite * sizeof (char), &dwBytesWritten, NULL) ; 
		if ((nToWrite * sizeof (char)) != (int) dwBytesWritten) 
		{
			return false;
		}
	}

	if (includeHeader)
	{
		nToWrite = (int)strlen(rowIni);
		::WriteFile (hFile, rowIni, nToWrite * sizeof (char), &dwBytesWritten, NULL) ; 
		if ((nToWrite * sizeof (char)) != (int) dwBytesWritten) 
		{
			return false;
		}

		//************************************************ Write Header
		for(int col = 0; col<nColCount; col++)
		{
			nToWrite = (int)strlen(colIni);
			::WriteFile (hFile, colIni, nToWrite * sizeof (char), &dwBytesWritten, NULL) ; 
			if ((nToWrite * sizeof (char)) != (int) dwBytesWritten) 
			{
				return false;
			}
			if (this->GetHeaderText(col, szw, 1024))
			{
				_snprintf_s(sz, 1024, _TRUNCATE, "%S", szw);
				nToWrite = (int)strlen(sz);
				::WriteFile (hFile, sz, nToWrite * sizeof (char), &dwBytesWritten, NULL) ; 
				if ((nToWrite * sizeof (char)) != (int) dwBytesWritten) 
				{
					return false;
				}
				if (col!=nColCount-1 || strchr(colEnd, ',')==NULL)
				{
					nToWrite = (int)strlen(colEnd);
					::WriteFile (hFile, colEnd, nToWrite * sizeof (char), &dwBytesWritten, NULL) ; 
					if ((nToWrite * sizeof (char)) != (int) dwBytesWritten) 
					{
						return false;
					}
				}
			}
		}

		nToWrite = (int)strlen(rowEnd);
		::WriteFile (hFile, rowEnd, nToWrite * sizeof (char), &dwBytesWritten, NULL) ; 
		if ((nToWrite * sizeof (char)) != (int) dwBytesWritten) 
		{
			return false;
		}
	}

	//******************************************************* Write Data
	for(int row = 0; row<Items.GetCount(); row++)
	{
		nToWrite = (int)strlen(rowIni);
		::WriteFile (hFile, rowIni, nToWrite * sizeof (char), &dwBytesWritten, NULL) ; 
		if ((nToWrite * sizeof (char)) != (int) dwBytesWritten) 
		{
			return false;
		}
		for(int col = 0; col<nColCount; col++)
		{
			nToWrite = (int)strlen(colIni);
			::WriteFile (hFile, colIni, nToWrite * sizeof (char), &dwBytesWritten, NULL) ; 
			if ((nToWrite * sizeof (char)) != (int) dwBytesWritten) 
			{
				return false;
			}
			if (this->Items[row].GetText(col, szw, 1024))
			{
				_snprintf_s(sz, 1024, _TRUNCATE, "%S", szw);
				nToWrite = (int)strlen(sz);
				::WriteFile (hFile, sz, nToWrite * sizeof (char), &dwBytesWritten, NULL) ; 
				if ((nToWrite * sizeof (char)) != (int) dwBytesWritten) 
				{
					return false;
				}
				if (col!=nColCount-1 || strchr(colEnd, ',')==NULL)
				{
					nToWrite = (int)strlen(colEnd);
					::WriteFile (hFile, colEnd, nToWrite * sizeof (char), &dwBytesWritten, NULL) ; 
					if ((nToWrite * sizeof (char)) != (int) dwBytesWritten) 
					{
						return false;
					}
				}
			}
		}
		nToWrite = (int)strlen(rowEnd);
		::WriteFile (hFile, rowEnd, nToWrite * sizeof (char), &dwBytesWritten, NULL) ; 
		if ((nToWrite * sizeof (char)) != (int) dwBytesWritten) 
		{
			return false;
		}
	}

	//************************************************ headEnd
	if (headEnd)
	{
		nToWrite = (int)strlen(headEnd);
		::WriteFile (hFile, headEnd, nToWrite * sizeof (char), &dwBytesWritten, NULL) ; 
		if ((nToWrite * sizeof (char)) != (int) dwBytesWritten) 
		{
			return false;
		}
	}
	return true;
}

bool ListView::ExportToMsExcel(const wchar_t* filename)
{
	Win::HourGlassCursor hgc(true);
	::CoInitialize(NULL);
	try
	{
		_variant_t result;
		Com::Object Application;
		Com::Object Workbooks;
		Application.CreateInstance(L"Excel.Application", true);
		Application.Get(L"Workbooks", Workbooks);
		Workbooks.Method(L"Add");
		CopyToClipboard();
		Com::Object ActiveSheet;
		Application.Get(L"ActiveSheet", ActiveSheet);
		ActiveSheet.Method(L"SaveAs", filename, result);
		Application.Method(L"Quit");
	}
	catch(Com::Exception execep)
	{
		wchar_t text[512];
		execep.GetErrorText(text, 512);
		this->MessageBox(text, L"MS Excel", MB_OK | MB_ICONERROR);
		::CoUninitialize();
		return false;
	}
	::CoUninitialize();
	return true;
}

//__________________________________________________________ ASCII version
bool ListView::SaveToFile(const wchar_t* filename, const char* colIni, const char* colEnd,
		const char* rowIni, const char* rowEnd, const char* docIni, const char* docEnd)
{
	HANDLE h = ::CreateFile (filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (INVALID_HANDLE_VALUE == h) return false;
	
	bool bOk = this->SaveToFile(h, colIni, colEnd, rowIni, rowEnd, docIni, docEnd, true);
	//
	if (h!=INVALID_HANDLE_VALUE) ::CloseHandle(h);
	 return bOk;
}

//_____________________________________________________________________ Slider
bool Slider::bInit = false;

Slider::Slider(void)
{
	if (bInit ==false)
	{
		INITCOMMONCONTROLSEX cc;
		cc.dwSize=sizeof(INITCOMMONCONTROLSEX);
		cc.dwICC=ICC_BAR_CLASSES;
		::InitCommonControlsEx(&cc);
		bInit = true;
	}
	_position = 0;
}

Slider::~Slider(void)
{
}

bool Slider::IsEvent(Win::Event& e, int notification)
{
	switch(e.uMsg)
	{
	case WM_HSCROLL:
	case WM_VSCROLL:
		{
			if ((HWND)(e.lParam)!=this->GetHWND()) return false;
			 return true;
		}
	case WM_NOTIFY:
		{
			NMHDR* pNMHDR= (LPNMHDR)e.lParam; 
			 if (pNMHDR->hwndFrom!=this->GetHWND()) return false;
			 if (pNMHDR->code!=notification) return false; 
			 return true;
		}
		break;
	}
	return false;
}

void Slider::SetRange(int minimum, int maximum)
{
	_position = (minimum+maximum)/2;
	::SendMessage(this->hWnd, TBM_SETRANGE, TRUE, MAKELPARAM(minimum, maximum));
}

void Slider::SetPosition(int position)
{
	::SendMessage(this->hWnd, TBM_SETPOS, TRUE, (LPARAM)position);
}

int Slider::GetPosition()
{
	return (int)::SendMessage(this->hWnd, TBM_GETPOS, (WPARAM)0, (LPARAM)0);
}

void Slider::SetMinimumPosition(int position)
{
	::SendMessage(this->hWnd, TBM_SETRANGEMIN, TRUE, (LPARAM)position);
}

int Slider::GetMinimumPosition()
{
	return (int)::SendMessage(this->hWnd, TBM_GETRANGEMIN, (WPARAM)0, (LPARAM)0);
}

void Slider::SetMaximumPosition(int position)
{
	::SendMessage(this->hWnd, TBM_SETRANGEMAX, TRUE, (LPARAM)position);
}

int Slider::GetMaximumPosition()
{
	return (int)::SendMessage(this->hWnd, TBM_GETRANGEMAX, (WPARAM)0, (LPARAM)0);
}

// If the position has NOT changed, it returns -1.  If the position has changed, the function returns the new position
// Use this function when performance is important. Call this function from: sld_Hscroll() or sld_Vscroll()
int Slider::HasPositionChanged()
{
	const int newPosition = GetPosition();
	if (newPosition == _position) return -1;
	_position = newPosition;
	return _position;
}

//_____________________________________________________________________Toolbar
bool Toolbar::bInit = false;

Toolbar::Toolbar(void)
{
	if (bInit == false)
	{
		INITCOMMONCONTROLSEX cc;
		cc.dwSize=sizeof(INITCOMMONCONTROLSEX);
		cc.dwICC=ICC_BAR_CLASSES;
		::InitCommonControlsEx(&cc);
		bInit = true;
	}
}

Toolbar::~Toolbar(void)
{
}

bool Toolbar::IsEvent(Win::Event& e, int notification)
{
	 if (e.uMsg==WM_NOTIFY)
	{
		LPNMHDR pNMHDR = (LPNMHDR)e.lParam; 
		if (pNMHDR->code==notification) return true;
		return false;
	}
	return false;
}

void Toolbar::SetMaxTextRows(int count)
{
	::SendMessage(hWnd, TB_SETMAXTEXTROWS, (WPARAM)count, (LPARAM)0);
}

void Toolbar::AutoSize()
{
	::SendMessage(this->hWnd, (UINT)TB_AUTOSIZE, 0, 0);
}

UINT Toolbar::GetButtonCount() 
{
	return (UINT)::SendMessage(this->hWnd, (UINT)TB_BUTTONCOUNT, 0, 0);
}

UINT Toolbar::GetButtonState(int button_id)
{
	return (UINT)::SendMessage(this->hWnd, (UINT)TB_GETSTATE, (WPARAM)(int)button_id, 0);
}

BOOL Toolbar::Customize() // Requires OnNotify(...)
{
	return (BOOL)::SendMessage(this->hWnd, (UINT)TB_CUSTOMIZE, 0, 0);	
} 

bool Toolbar::CheckButton(int button_id, bool checked)
{
	BOOL f = checked ? TRUE : FALSE;
	return (::SendMessage(this->hWnd, (UINT)TB_CHECKBUTTON, (WPARAM)(int)button_id, 
		(LPARAM) MAKELONG (f, 0)) == TRUE);
}

bool Toolbar::PressButton(int button_id, bool pressed)
{
	BOOL f= pressed ? TRUE : FALSE;
	return (::SendMessage(this->hWnd, (UINT)TB_PRESSBUTTON, (WPARAM)(int)button_id, 
		(LPARAM) MAKELONG (f, 0)) == TRUE);
}

bool Toolbar::EnableButton(int button_id, bool enabled)
{
	BOOL f= enabled ? TRUE : FALSE;
	return (::SendMessage(this->hWnd, (UINT)TB_ENABLEBUTTON, (WPARAM)(int)button_id, 
		(LPARAM) MAKELONG (f, 0)) == TRUE);
}

bool Toolbar::HideButton(int button_id, bool hidden)
{
	BOOL f= hidden ? TRUE : FALSE;
	return (::SendMessage(this->hWnd, (UINT)TB_HIDEBUTTON, (WPARAM)button_id, 
		(LPARAM) MAKELONG (f, 0)) == TRUE);
}

BOOL Toolbar::DeleteButton(int index)
{
	return (BOOL)::SendMessage(this->hWnd, (UINT)TB_DELETEBUTTON, (WPARAM)index, 0);
}

BOOL Toolbar::GetButton(int index, LPTBBUTTON pButton)
{
	return (BOOL)::SendMessage(this->hWnd, (UINT)TB_GETBUTTON, (WPARAM)index, (LPARAM)(LPTBBUTTON)pButton);
}

BOOL Toolbar::GetItemRect(int index, LPRECT pRect)
{
	return (BOOL)::SendMessage(this->hWnd, (UINT)TB_GETITEMRECT, (WPARAM)index, (LPARAM)(LPRECT)pRect);
}

BOOL Toolbar::GetMaxSize(LPSIZE pSize)
{
	return (BOOL)::SendMessage(this->hWnd, (UINT)TB_GETMAXSIZE, 0, (LPARAM)(LPSIZE)pSize);
}

BOOL Toolbar::InsertButton(int index, LPTBBUTTON pButton)
{
	return (BOOL)::SendMessage(this->hWnd, (UINT)TB_INSERTBUTTON, (WPARAM)index, (LPARAM)pButton);
}

bool Toolbar::IsButtonChecked(int button_id)
{
	return (::SendMessage(this->hWnd, (UINT)TB_ISBUTTONCHECKED, (WPARAM)button_id, 0)!=0);
}

bool Toolbar::IsButtonPressed(int button_id)
{
	return (::SendMessage(this->hWnd, (UINT)TB_ISBUTTONPRESSED, (WPARAM)button_id, 0)!=0);
}

bool Toolbar::IsButtonEnabled(int button_id)
{
	return (::SendMessage(this->hWnd, (UINT)TB_ISBUTTONENABLED, (WPARAM)button_id, 0)!=0);
}

bool Toolbar::IsButtonHidden(int button_id)
{
	return (::SendMessage(this->hWnd, (UINT)TB_ISBUTTONHIDDEN, (WPARAM)button_id, 0)!=0);
}


////	Create(0, IDC_TOOLBAR, 8, hParent, NULL, IDB_TOOLBAR, tbButton, NUMBUTTONS);
//HWND Toolbar::Create(DWORD dwStyle, UINT toolbarID, UINT nBitmaps, HWND hParent, 
//					 HINSTANCE hInst, UINT bitmapID, LPCTBBUTTON lpButtons, UINT nButtons)
//{
//	if (dwStyle == 0) 
//	{
//		dwStyle = WS_VISIBLE | WS_CHILD | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT;
//	}
//	if (hInst == NULL) hInst = this->m_hInstance;
//	m_hWnd = CreateToolbarEx(hParent, dwStyle, toolbarID, 
//		nBitmaps, // Number of bitmaps
//		hInst, bitmapID, // the instance of the bitmap
//		lpButtons, // Array of TBBUTTON
//		nButtons, // Number of buttons
//		16, 16, // Button size
//		16, 16, // Image size
//		sizeof(TBBUTTON));
//		m_nID = (LONG_PTR)toolbarID;
//
//	if (m_hWnd==NULL)
//	{
//		wchar_t sz[255];
//		lstrcpy(sz, L"Unable to create ");
//		lstrcat(sz, L"TOOLBARCLASSNAME");
//		MessageBox(m_hWndApplication, sz, L"Win::Toolbar.Create", MB_ICONERROR);
//		return NULL;
//	}
//	return m_hWnd;
//}

//Create(TBSTYLE_LIST | WS_VISIBLE | WS_CHILD | TBSTYLE_TOOLTIPS, hParent, (HMENU)IDC_TOOLBAR);
//HWND Toolbar::Create(DWORD dwStyle, HWND hParent, HMENU id)
//{
//	if (dwStyle==0) dwStyle = WS_VISIBLE | WS_CHILD | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT;
//	m_hWnd = Module::Create(0, TOOLBARCLASSNAME, (const wchar_t *)NULL, dwStyle, 0, 0, 0, 0, hParent, id, NULL);
//	SendMessage(m_hWnd, TB_BUTTONSTRUCTSIZE, (WPARAM)(int)sizeof(TBBUTTON), 0); // Backward compatibility
//	return m_hWnd;
//}



// Returns the index of the string
//this->m_tb.Create(TBSTYLE_LIST | WS_VISIBLE | WS_CHILD | TBSTYLE_TOOLTIPS, hWnd, (HMENU)IDC_TOOLBAR);
//nIndex = m_tb.AddString(L"File");
// ....
//tbButton[i++].iString= nIndex;
LRESULT Toolbar::AddString(const wchar_t * szText)
{
	return ::SendMessage(this->hWnd, TB_ADDSTRING, 0, (LPARAM)szText);
}

LRESULT Toolbar::AddBitmap(HINSTANCE hInst, UINT idBitmap, UINT_PTR nImages)
{
	TBADDBITMAP tbAddBM;

	if (hInst == NULL) hInst = this->hInstance;
	tbAddBM.hInst=hInst;
	tbAddBM.nID=idBitmap;
	return ::SendMessage(this->hWnd, TB_ADDBITMAP, (WPARAM)(int)nImages, 
		(LPARAM)(LPTBADDBITMAP)&tbAddBM);
}

// You can use either AddStdBitmap or LoadStdImages
// Use these indexes for the TBBUTTON structure
//STD_COPY, STD_CUT,  STD_DELETE, STD_FILENEW, STD_FILEOPEN
//STD_FILESAVE, STD_HELP, STD_PASTE, STD_PRINT, STD_PRINTPRE 
//STD_PROPERTIES, STD_REDOW, STD_REPLACE, STD_UNDO
LRESULT Toolbar::AddStdBitmap(bool bLarge)
{
	TBADDBITMAP tbAddBM;

	tbAddBM.hInst=HINST_COMMCTRL;
	tbAddBM.nID= bLarge ? IDB_STD_LARGE_COLOR : IDB_STD_SMALL_COLOR;
	return ::SendMessage(this->hWnd, TB_ADDBITMAP, (WPARAM)0, 
		(LPARAM)(LPTBADDBITMAP)&tbAddBM);
}

// Use these indexes for the TBBUTTON structure
//STD_COPY, STD_CUT,  STD_DELETE, STD_FILENEW, STD_FILEOPEN
//STD_FILESAVE, STD_HELP, STD_PASTE, STD_PRINT, STD_PRINTPRE 
//STD_PROPERTIES, STD_REDOW, STD_REPLACE, STD_UNDO
LRESULT Toolbar::LoadStdImages(bool bLarge)
{
	WPARAM wp;
	
	if (bLarge)
	{
		SetBitmapSize(24, 24);
		SetButtonSize(24, 24);
		wp = (WPARAM)(INT)IDB_STD_LARGE_COLOR;
	}
	else
	{
		SetBitmapSize(16, 16);
		SetButtonSize(16, 16);
		wp = (WPARAM)(INT)IDB_STD_SMALL_COLOR;
	}
	return ::SendMessage(this->hWnd, (UINT)TB_LOADIMAGES, wp, (LPARAM)(HINSTANCE)HINST_COMMCTRL);		
}

// You can use either AddViewBitmap or LoadViewImages
// Use these indexes for the TBBUTTON structure
//VIEW_DETAILS, VIEW_LARGEICONS, VIEW_LIST, VIEW_SMALLICONS
//VIEW_SORTDATE, VIEW_SORTNAME, VIEW_SORTSIZE, VIEW_SORTTYPE
LRESULT Toolbar::AddViewBitmap(bool bLarge)
{
	TBADDBITMAP tbAddBM;

	tbAddBM.hInst=HINST_COMMCTRL;
	tbAddBM.nID= bLarge ? IDB_VIEW_LARGE_COLOR : IDB_VIEW_SMALL_COLOR;
	return ::SendMessage(this->hWnd, TB_ADDBITMAP, (WPARAM)0, 
		(LPARAM)(LPTBADDBITMAP)&tbAddBM);
}

// Use these indexes for the TBBUTTON structure
//VIEW_DETAILS, VIEW_LARGEICONS, VIEW_LIST, VIEW_SMALLICONS
//VIEW_SORTDATE, VIEW_SORTNAME, VIEW_SORTSIZE, VIEW_SORTTYPE
LRESULT Toolbar::LoadViewImages(bool bLarge)
{
	WPARAM wp;
	
	if (bLarge)
	{
		SetBitmapSize(24, 24);
		SetButtonSize(24, 24);
		wp = (WPARAM)(INT)IDB_VIEW_LARGE_COLOR;
	}
	else
	{
		SetBitmapSize(16, 16);
		SetButtonSize(16, 16);
		wp = (WPARAM)(INT)IDB_VIEW_SMALL_COLOR;
	}
	return ::SendMessage(this->hWnd, (UINT)TB_LOADIMAGES, wp, (LPARAM)(HINSTANCE)HINST_COMMCTRL);		
}

// Use these indexes for the TBBUTTON structure
//HIST_ADDTOFAVORITES, HIST_BACK, HIST_FAVORITES 
//HIST_FORWARD, HIST_VIEWTREE 
LRESULT Toolbar::LoadHistoryImages(bool bLarge)
{
	WPARAM wp;
	
	if (bLarge)
	{
		SetBitmapSize(24, 24);
		SetButtonSize(24, 24);
		wp = (WPARAM)(INT)IDB_HIST_LARGE_COLOR;
	}
	else
	{
		SetBitmapSize(16, 16);
		SetButtonSize(16, 16);
		wp = (WPARAM)(INT)IDB_HIST_SMALL_COLOR;
	}
	return ::SendMessage(this->hWnd, (UINT)TB_LOADIMAGES, wp, (LPARAM)(HINSTANCE)HINST_COMMCTRL);		
}


//TBBUTTON rgtb[5];
// rgtb[0].iBitmap = MAKELONG(0, 1); // 0 is the only image list
// rgtb[0].iBitmap = MAKELONG(0, 2); // 0 is the only image list
LRESULT Toolbar::SetImageList(Win::ImageList& imageList)
{
	return ::SendMessage(this->hWnd, (UINT)TB_SETIMAGELIST, 0, (LPARAM)(HIMAGELIST)imageList.GetHImageList());   
}

LRESULT Toolbar::SetDisabledImageList(Win::ImageList& imageList)
{
	return ::SendMessage(this->hWnd, (UINT)TB_SETDISABLEDIMAGELIST, 0, (LPARAM)(HIMAGELIST)imageList.GetHImageList());   
}

LRESULT Toolbar::SetBitmapSize(UINT width, UINT height)
{
	return ::SendMessage(this->hWnd, (UINT)TB_SETBITMAPSIZE, 0, (LPARAM) MAKELONG (width, height));   
}

//HIWORD returns Height and LOWORD return Width
LRESULT Toolbar::GetButtonSize()
{
	return ::SendMessage(this->hWnd, (UINT)TB_GETBUTTONSIZE, 0, (LPARAM)0);   
}

LRESULT Toolbar::SetButtonSize(UINT width, UINT height)
{
	return ::SendMessage(this->hWnd, (UINT)TB_SETBUTTONSIZE, 0, (LPARAM) MAKELONG (width, height));   
}

void Toolbar::SetButtonWidth(int mimimum, int maximum)
{
	::SendMessage(hWnd, TB_SETBUTTONWIDTH, (WPARAM)0, (LPARAM) MAKELONG (mimimum, maximum));
}

LRESULT Toolbar::AddButtons(LPCTBBUTTON lpButtons, UINT nButtons)
{
	return ::SendMessage(this->hWnd, TB_ADDBUTTONS, 
		(WPARAM)nButtons, (LPARAM)(LPTBBUTTON)&lpButtons[0]);
}

//void Toolbar::Window_Size(WPARAM wParam, LPARAM lParam)
//{
//	SendMessage(m_hWnd, WM_SIZE, wParam, lParam);
//	//SIZE size;
//	//GetMaxSize(&size);
//	//MoveAndResize(m_hWnd, 0, 0, parentWidth, size.cx, TRUE);
//}

//_____________________________________________________________________ Tooltip
Tooltip::Tooltip(void)
{
}

Tooltip::~Tooltip(void)
{
}

LRESULT Tooltip::AddTool(Win::Module& tool,wchar_t* tip)
{
	return AddTool(tool.GetHWND(), tool.GetID(), tip);
}

LRESULT Tooltip::DelTool(Win::Module& tool)
{
	return DelTool(tool.GetHWND(), tool.GetID());
}

LRESULT Tooltip::AddTool(HWND hWndTool, UINT tool_id, wchar_t* tip)
{
	TOOLINFO ti;
	RECT rect;
	::GetClientRect (hWndTool, &rect);

	/* INITIALIZE MEMBERS OF THE TOOLINFO STRUCTURE */
	ti.cbSize = sizeof(TOOLINFO);
	ti.uFlags = TTF_SUBCLASS;
	ti.hwnd = hWndTool;
	ti.hinst = Win::Module::hInstance;
	ti.uId = tool_id;
	ti.lpszText = tip;

	// ToolTip control will cover the whole window
	ti.rect.left = rect.left;    
	ti.rect.top = rect.top;
	ti.rect.right = rect.right;
	ti.rect.bottom = rect.bottom;

	return ::SendMessage(this->hWnd, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO)&ti);
}

LRESULT Tooltip::DelTool(HWND hWndTool, UINT tool_id)
{
	TOOLINFO ti;

	ti.cbSize = sizeof(TOOLINFO);
	ti.uFlags = TTF_SUBCLASS;
	ti.hwnd = hWndTool;
	ti.hinst = Win::Module::hInstance;
	ti.uId = tool_id;
	ti.lpszText = NULL;
	return ::SendMessage(this->hWnd, TTM_DELTOOL, 0, (LPARAM) (LPTOOLINFO)&ti);
}

HWND Tooltip::Create(DWORD dwExStyle, const wchar_t* pszWindowName, DWORD dwStyle, int x, int y, int width, int height, HWND hParent, int id)
{
	Win::Module::Create(WS_EX_TOPMOST, NULL, WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hParent, NULL);
	::SetWindowPos(this->hWnd,
        HWND_TOPMOST,
        0,
        0,
        0,
        0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	return this->hWnd;
}

HWND Tooltip::Create(HWND parent)
{
	return Create(0, NULL, 0, 0, 0, 0, 0, parent, -1);
}

//_____________________________________________________________________ TabItem
TabItem::TabItem(void)
{
	index = -1;
	tabControl= NULL;
}

TabItem::~TabItem(void)
{
}

bool TabItem::GetItemRect(int index, RECT& rect)
{
	return ((BOOL)::SendMessage(tabControl, TCM_GETITEMRECT, (WPARAM)index, (LPARAM) (RECT FAR *)&rect)==TRUE);
}


BOOL TabItem::Delete()
{
	return (BOOL)::SendMessage(tabControl, (UINT) TCM_DELETEITEM, (WPARAM)index, (LPARAM)0);  
}

int TabItem::GetImageIndex()
{
	TCITEM tci;
	ZeroMemory(&tci, sizeof(TCITEM));
	tci.mask = TCIF_IMAGE;
	tci.iImage = -1;
	if (::SendMessage(this->tabControl, TCM_GETITEM, index, (LPARAM)&tci)==TRUE) return tci.iImage;
	return -1;
}

// Indexes start at 0
void TabItem::SetImageIndex(int imageIndex)
{
	TCITEM tci;
	ZeroMemory(&tci, sizeof(TCITEM));
	tci.mask = TCIF_IMAGE;
	tci.iImage = imageIndex;
	::SendMessage(this->tabControl, TCM_SETITEM, index, (LPARAM)&tci); 
}

LPARAM TabItem::GetData()
{
	TCITEM tci;
	ZeroMemory(&tci, sizeof(TCITEM));
	tci.mask = TCIF_PARAM;
	tci.lParam = 0;
	if (::SendMessage(this->tabControl, TCM_GETITEM, index, (LPARAM)&tci) == TRUE) return tci.lParam;
	return -1;
}

void TabItem::SetData(LPARAM data)
{
	TCITEM tci;
	ZeroMemory(&tci, sizeof(TCITEM));
	tci.mask = TCIF_PARAM;
	tci.lParam = data;
	::SendMessage(this->tabControl, TCM_SETITEM, index, (LPARAM)&tci); 
}

wstring TabItem::GetText()
{
	wchar_t text[128];
	text[0] = '\0';

	TCITEM tci;
	ZeroMemory(&tci, sizeof(TCITEM));
	tci.mask = TCIF_TEXT;
	tci.pszText = text;
	tci.cchTextMax = 128;
	::SendMessage(this->tabControl, TCM_GETITEM, index, (LPARAM)&tci);
	return text;
}

void TabItem::SetText(const wstring& text)
{
	TCITEM tci;
	ZeroMemory(&tci, sizeof(TCITEM));
	tci.mask = TCIF_TEXT;
	tci.pszText = (LPWSTR)text.c_str();
	tci.cchTextMax = text.length()+1;
	::SendMessage(this->tabControl, TCM_SETITEM, index, (LPARAM)&tci); 
}

//_____________________________________________________________________ TabItemCollection
TabItemCollection::TabItemCollection(void)
{
	this->iparent = NULL;
}

TabItemCollection::~TabItemCollection(void)
{
}

Win::TabItem& TabItemCollection::operator[](long index)
{
	_item.index = index;
	_item.tabControl = this->iparent->GetHWND();
	return _item;
}

void TabItemCollection::SetParent(Win::IParent* iparent)
{
	this->iparent = iparent;
}

bool TabItemCollection::Set(TCITEM& item)
{
	return ((BOOL)::SendMessage(iparent->GetHWND(), TCM_SETITEM, (WPARAM)_item.index, (LPARAM) (LPTCITEM)&item)==TRUE); 
}

bool TabItemCollection::Get(TCITEM& item)
{
	return ((BOOL)::SendMessage(iparent->GetHWND(), TCM_GETITEM, (WPARAM)_item.index, (LPARAM) (LPTCITEM)&item)==TRUE); 
}

int TabItemCollection::Add(int index, TCITEM& item)
{	
	return (int)::SendMessage(iparent->GetHWND(), TCM_INSERTITEM, index, (LPARAM) (LPTCITEM)&item);
}

int TabItemCollection::Add(int index, int imageIndex, const wchar_t* text)
{
	TCITEM tci;
	ZeroMemory(&tci, sizeof(TCITEM));
	tci.pszText = (wchar_t*)text;
	tci.cchTextMax = wcslen(text)+1;
	tci.iImage = imageIndex;
	tci.mask = TCIF_TEXT | TCIF_IMAGE;// | TCIF_PARAM ;
	return ::SendMessage(iparent->GetHWND(), (UINT) TCM_INSERTITEM, index, (LPARAM) (LPTCITEM)&tci);
}
	
int TabItemCollection::Add(int index, const wchar_t* text, int imageIndex, LPARAM userData)
{
	TCITEM tci;
	ZeroMemory(&tci, sizeof(TCITEM));
	tci.pszText = (wchar_t*)text;
	tci.cchTextMax = wcslen(text)+1;
	tci.iImage = imageIndex;
	tci.lParam = userData;
	tci.mask = TCIF_TEXT | TCIF_IMAGE | TCIF_PARAM ;
	return ::SendMessage(iparent->GetHWND(), (UINT) TCM_INSERTITEM, index, (LPARAM) (LPTCITEM)&tci);
}

int TabItemCollection::Add(int index, const wchar_t* text)
{
	TCITEM tci;
	ZeroMemory(&tci, sizeof(TCITEM));
	tci.pszText = (wchar_t*)text;
	tci.cchTextMax = wcslen(text)+1;
	tci.mask = TCIF_TEXT;// | TCIF_IMAGE | TCIF_PARAM ;
	return ::SendMessage(iparent->GetHWND(), (UINT) TCM_INSERTITEM, index, (LPARAM) (LPTCITEM)&tci);
}
	
int TabItemCollection::Add(int index, const wchar_t* text, LPARAM userData)
{
	TCITEM tci;
	ZeroMemory(&tci, sizeof(TCITEM));
	tci.pszText = (wchar_t*)text;
	tci.cchTextMax = wcslen(text)+1;
	tci.lParam = userData;
	tci.mask = TCIF_TEXT | TCIF_PARAM ;
	return ::SendMessage(iparent->GetHWND(), (UINT) TCM_INSERTITEM, index, (LPARAM) (LPTCITEM)&tci);
}

int TabItemCollection::Add(int index, int imageIndex, const wstring& text)
{
	return Add(index, imageIndex, text.c_str());
}

int TabItemCollection::Add(int index, const wstring& text, int imageIndex, LPARAM data)
{
	return Add(index, text.c_str(), imageIndex, data);
}

int TabItemCollection::Add(int index, const wstring& text)
{
	return Add(index, text.c_str());
}

int TabItemCollection::Add(int index, const wstring& text, LPARAM data)
{
	return Add(index, text.c_str(), data);
}

int TabItemCollection::GetCount()
{	
	return (int)::SendMessage(iparent->GetHWND(), (UINT)TCM_GETITEMCOUNT, (WPARAM)0, (LPARAM)0);
}

LRESULT TabItemCollection::DeleteAll()
{	
	return ::SendMessage(iparent->GetHWND(), (UINT)TCM_DELETEALLITEMS, 0, 0);
}

//_____________________________________________________________________Tab
bool Tab::bInit = false;

Tab::Tab(void)
{
	if (bInit == false)
	{
		INITCOMMONCONTROLSEX cc;
		cc.dwSize=sizeof(INITCOMMONCONTROLSEX);
		cc.dwICC=ICC_TAB_CLASSES;
		::InitCommonControlsEx(&cc);
		bInit = true;
	}
	Items.SetParent(this);
}

Tab::~Tab(void)
{
}

bool Tab::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_NOTIFY) return false;
	NMHDR* pNMHDR= (LPNMHDR)e.lParam; 
     if (pNMHDR->hwndFrom!=this->GetHWND()) return false;
     if (pNMHDR->code!=notification) return false; 
	return true;
}

int  Tab::SetSelected(int index)
{
	return (int)::SendMessage(this->hWnd, TCM_SETCURSEL, (WPARAM)index, 0);
}

int Tab::GetSelectedIndex()
{
	return (int)::SendMessage(this->hWnd, TCM_GETCURSEL, 0, 0);
}

void Tab::SetSelectedByData(LPARAM data)
{
	const int count = ::SendMessage(hWnd, (UINT)TCM_GETITEMCOUNT, (WPARAM)0, (LPARAM)0);  
	for(int i=0; i<count; i++)
	{
		if (this->Items[i].GetData()==data)
		{
			this->SetSelected(i);
			break;
		}
	}
}

LPARAM Tab::GetSelectedData()
{
	const int index =  (int)::SendMessage(this->hWnd, TCM_GETCURSEL, 0, 0);
	TCITEM tci;
	ZeroMemory(&tci, sizeof(TCITEM));
	tci.mask = TCIF_PARAM;
	tci.lParam = 0;
	if (::SendMessage(this->hWnd, TCM_GETITEM, index, (LPARAM)&tci) == TRUE) return tci.lParam;
	return -1;
}

LRESULT Tab::HighLightItem(int index, bool bIsHighLight)
{
	return ::SendMessage(this->hWnd, TCM_HIGHLIGHTITEM, (WPARAM)index, (LPARAM) MAKELONG(bIsHighLight,0));
}

HIMAGELIST Tab::SetImageList(Win::ImageList& imageList)
{
	return (HIMAGELIST)::SendMessage(this->hWnd, TCM_SETIMAGELIST, (WPARAM)0, (LPARAM)(HIMAGELIST)imageList.GetHImageList());
}

//_____________________________________________________________________ProgressBar
bool ProgressBar::bInit = 0;

ProgressBar::ProgressBar(void)
{
	if (bInit==false)
	{
		INITCOMMONCONTROLSEX cc;
		cc.dwSize=sizeof(INITCOMMONCONTROLSEX);
		cc.dwICC=ICC_PROGRESS_CLASS;
		::InitCommonControlsEx(&cc);
		bInit=true;
	}
}

ProgressBar::~ProgressBar(void)
{
}

int ProgressBar::SetStep(int stepSize)
{
	return (int)::SendMessage(hWnd, PBM_SETSTEP, (WPARAM)stepSize, 0);
}

int ProgressBar::SetRange(int minimum, int maximum)
{
	return (int)::SendMessage(hWnd, PBM_SETRANGE32, (WPARAM)minimum, (LPARAM)maximum);
}

int ProgressBar::StepIt()
{
	return (int)::SendMessage(hWnd, PBM_STEPIT, (WPARAM)0, (LPARAM)0);
}

COLORREF ProgressBar::SetBarcolor(COLORREF rgb)
{
	return (COLORREF)::SendMessage(hWnd, PBM_SETBARCOLOR, 0, (LPARAM)rgb);
}

COLORREF ProgressBar::SetBkcolor(COLORREF rgb)
{
	return (COLORREF)::SendMessage(hWnd, PBM_SETBKCOLOR, 0, (LPARAM)rgb);
}

void ProgressBar::SetPosition(int position)
{
	::SendMessage(hWnd, PBM_SETPOS, (WPARAM)position, (LPARAM)0);
}

int ProgressBar::GetPosition()
{
	return (int)::SendMessage(hWnd, PBM_GETPOS, (WPARAM)0, (LPARAM)0);
}

void ProgressBar::SetMarquee(bool on, int milliseconds)
{
	BOOL f = on ? TRUE : FALSE;
	::SendMessage(hWnd, PBM_SETMARQUEE, (WPARAM)f, (LPARAM)milliseconds);
}


//_____________________________________________________________________StatusBar
bool StatusBar::bInit=false;

StatusBar::StatusBar(void)
{
	if (bInit==false)
	{
		INITCOMMONCONTROLSEX cc;
		cc.dwSize=sizeof(INITCOMMONCONTROLSEX);
		cc.dwICC=ICC_BAR_CLASSES;
		::InitCommonControlsEx(&cc);
		bInit=true;
	}
}

StatusBar::~StatusBar(void)
{
}

void StatusBar::SetMinHeight(int height)
{
	::SendMessage(this->hWnd, SB_SETMINHEIGHT, (WPARAM)height, (LPARAM)0);
}

int StatusBar::GetPartTextLength(int index)
{
	return (int)::SendMessage(this->hWnd, SB_GETTEXTLENGTH, (WPARAM)index, (LPARAM)0);
}

LRESULT StatusBar::GetPartText(int index, wchar_t* buffer)
{
	return ::SendMessage(this->hWnd, SB_GETTEXT, (WPARAM)index, (LPARAM)buffer);
}

LRESULT StatusBar::SetPartCount(int nCount, int* nPartWidth)
{
	return ::SendMessage(this->hWnd, SB_SETPARTS, (WPARAM)nCount, (LPARAM)nPartWidth);
}

// Set hIcon to NULL to remove the icon
BOOL StatusBar::SetPartIcon(INT index, HICON hIcon)
{
	return (BOOL)::SendMessage(this->hWnd, SB_SETICON, (WPARAM)index, (LPARAM)hIcon);
}

BOOL StatusBar::SetPartIcon(INT index, UINT resourceID, HINSTANCE hInst)
{
	if (hInst == NULL) hInst = this->hInstance;

	HICON hIcon = LoadIcon(hInst, MAKEINTRESOURCE(resourceID));
	return SetPartIcon(index, hIcon);
}

COLORREF StatusBar::SetBackcolor(COLORREF rgb)
{
	return (COLORREF)::SendMessage(this->hWnd, (UINT)SB_SETBKCOLOR, (WPARAM)0, (LPARAM)rgb); 
}

//_____________________________________________________________________Rebar
bool Rebar::bInit = 0;

Rebar::Rebar(void)
{
	if (bInit==false)
	{
		INITCOMMONCONTROLSEX cc;
		cc.dwSize=sizeof(INITCOMMONCONTROLSEX);
		cc.dwICC=ICC_BAR_CLASSES | ICC_COOL_CLASSES;
		::InitCommonControlsEx(&cc);
		bInit=true;
	}
}

Rebar::~Rebar(void)
{
}

UINT Rebar::GetBarHeight()
{
	return(UINT)::SendMessage(this->hWnd, (UINT)RB_GETBARHEIGHT, (WPARAM)0, (LPARAM)0);
}

UINT Rebar::GetBandCount()
{
	return(UINT)::SendMessage(this->hWnd, (UINT)RB_GETBANDCOUNT, 0, 0);
}	

BOOL Rebar::InsertBand(LPREBARBANDINFO rbBand)
{
	rbBand->cbSize = sizeof(REBARBANDINFO);
	return (0 != ::SendMessage(this->hWnd, (UINT)RB_INSERTBAND, (WPARAM)-1, (LPARAM)rbBand));
}

BOOL Rebar::InsertBand(int index, LPREBARBANDINFO rbBand)
{
	rbBand->cbSize = sizeof(REBARBANDINFO);
	return (0 != ::SendMessage(this->hWnd, (UINT)RB_INSERTBAND, (WPARAM)index, (LPARAM)rbBand));
}

BOOL Rebar::GetBandInfo(UINT index, LPREBARBANDINFO p)
{
	return (BOOL)::SendMessage(this->hWnd, RB_GETBANDINFO, (WPARAM)index, (LPARAM)p);
}

BOOL Rebar::SetBandInfo(UINT index, LPREBARBANDINFO p)
{
	return (BOOL)::SendMessage(this->hWnd, RB_GETBANDINFO, (WPARAM)index, (LPARAM)p);
}

BOOL Rebar::SetBarInfo(HIMAGELIST hImageList)
{
	REBARINFO rbi;
	//ZeroMemory(&rbi, sizeof(REBARINFO));
	rbi.cbSize = sizeof(REBARINFO);
	rbi.fMask  = 0;
	rbi.himl   = hImageList;

	if(!::SendMessage(this->hWnd, RB_SETBARINFO, 0, (LPARAM)&rbi))
	{
		this->Destroy();
		this->hWnd = NULL;
		return FALSE;
	}
	return TRUE;
}

//void Rebar::Window_Size(LPARAM lParam)
//{
//	REBARBANDINFO rbBand = {0};
//	UINT n = GetBandCount();
//	int cx = LOWORD(lParam);
//	int cy = HIWORD(lParam);
//
//	rbBand.cbSize = sizeof(REBARBANDINFO);
//	rbBand.fMask = RBBIM_SIZE|RBBIM_CHILD|RBBIM_CHILDSIZE|RBBIM_ID|RBBIM_STYLE|RBBIM_TEXT;
//
//	this->MoveWindowToFill(lParam);
//	for(int i = 0; i<n; i++)
//	{
//		this->GetBandInfo(i, &rbBand);
//		rbBand.cyChild = cy;
//		rbBand.cyMaxChild = cy;
//		this->SetBandInfo(i, &rbBand);
//	}
//}

//_____________________________________________________________________ ListImage
ListImage::ListImage(void)
{
	index = -1;
	listControl= NULL;
}

ListImage::~ListImage(void)
{
}

int ListImage::GetTextLength()
{
	return (int)::SendMessage(listControl, CB_GETLBTEXTLEN, index, 0);
}

void ListImage::SetData(DWORD data)
{
	::SendMessage(listControl, CB_SETITEMDATA, (WPARAM)index, (LPARAM)data);
}

DWORD ListImage::GetData()
{
	return (DWORD)::SendMessage(listControl, CB_GETITEMDATA, (WPARAM)index, (LPARAM)0);
}

void ListImage::GetText(wchar_t* text)
{
	::SendMessage(listControl, CB_GETLBTEXT, index, (LPARAM)text); 
}

wstring ListImage::GetText()
{
	const int length = GetTextLength();
	wstring tmp;
	tmp.resize(length+1);
	::SendMessage(listControl, CB_GETLBTEXT, index, (LPARAM)tmp.data()); 
	tmp.resize(length);
	return tmp;
}

int ListImage::Delete()
{
	return (int)::SendMessage(listControl, CB_DELETESTRING, index, 0);
}

//_____________________________________________________________________ ListImageCollection
ListImageCollection::ListImageCollection(void)
{
	iparent = NULL;
	used_data = false;
	_data = 0;
}

ListImageCollection::~ListImageCollection(void)
{
}

Win::ListImage& ListImageCollection::operator[](long index)
{
	_item.index = index;
	_item.listControl = this->iparent->GetHWND();
	return _item;
}

bool ListImageCollection::Add(COMBOBOXEXITEM cbei)
{
	if (::SendMessage(iparent->GetHWND(), CBEM_INSERTITEM, 0, (LPARAM)&cbei) == -1) return false;
		return true;
}

bool ListImageCollection::Add(int index, int indent, int image, int imageSelected, const wchar_t* text)
{	
	return Add(index, indent, image, imageSelected, text, 0);
}

bool ListImageCollection::Add(int index, int indent, int image, int imageSelected, const wstring& text)
{
	return Add(index, indent, image, imageSelected, text.c_str());
}

bool ListImageCollection::Add(int index, int indent, int image, int imageSelected, const wchar_t* text, LPARAM data)
{
	COMBOBOXEXITEM cbei;
	cbei.cchTextMax = lstrlen(text)+1;
	cbei.iImage = image;
	cbei.iIndent = indent;
	cbei.iItem = index;
	//cbei.iOverlay = 
	cbei.iSelectedImage = imageSelected;
	cbei.lParam = data;
	cbei.mask = CBEIF_IMAGE | CBEIF_INDENT | CBEIF_LPARAM | CBEIF_SELECTEDIMAGE | CBEIF_TEXT; //CBEIF_OVERLAY
	cbei.pszText = (wchar_t*)text;
	return Add(cbei);
}

bool ListImageCollection::Add(int index, int indent, int image, int imageSelected, const wstring& text, LPARAM data)
{
	return Add(index, indent, image, imageSelected, text.c_str(), data);
}

void ListImageCollection::DeleteAll()
{
	::SendMessage(iparent->GetHWND(), CB_RESETCONTENT, 0, 0);
}

int ListImageCollection::GetCount()
{
	return (int)::SendMessage(iparent->GetHWND(), CB_GETCOUNT, 0, 0);
}

void ListImageCollection::SetParent(Win::IParent* iparent)
{
	this->iparent = iparent;
}

//The return value is the zero-based index of the matching item. If the search is unsuccessful, it is CB_ERR
int ListImageCollection::GetIndex(wchar_t* text)
{
	return (int)::SendMessage(iparent->GetHWND(), CB_FINDSTRING,
		(WPARAM)-1, (LPARAM)text);
}

//_____________________________________________________________________ DropDownImageList
bool DropDownImageList::bInit = 0;
DropDownImageList::DropDownImageList(void)
{
	if (bInit==false)
	{
		INITCOMMONCONTROLSEX cc;
		ZeroMemory(&cc, sizeof(INITCOMMONCONTROLSEX));
		cc.dwICC = ICC_USEREX_CLASSES;
		cc.dwSize=sizeof(INITCOMMONCONTROLSEX);
		InitCommonControlsEx(&cc);
		bInit=true;
	}
	_items.SetParent(this);
}

DropDownImageList::~DropDownImageList(void)
{
}

LRESULT DropDownImageList::ShowDropDown(bool show)
{
	BOOL f = show ? TRUE : FALSE;
	return ::SendMessage(this->hWnd, CB_SHOWDROPDOWN, (WPARAM)f, (LPARAM)0);
}

ListImageCollection& DropDownImageList::GetItems()
{
	return _items;
}

bool DropDownImageList::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg==WM_COMMAND)
	{
		if (LOWORD(e.wParam)!=this->id) return false;
		if (HIWORD(e.wParam)!=notification) return false;
		return true;
	}
	else if (e.uMsg==WM_NOTIFY)
	{
		NMHDR* pNMHDR= (LPNMHDR)e.lParam; 
		 if (pNMHDR->hwndFrom!=this->GetHWND()) return false;
		 if (pNMHDR->code!=notification) return false; 
		return true;
	}
	return false;
}

// You may call GetWindowRect first to know the combobox position
void DropDownImageList::SetImageList(Win::ImageList& imageList, HWND parent)
{
	RECT rc;
	this->GetRelativeRect(parent, rc);
	//::GetWindowRect(hWnd, &rc);
	::SendMessage(hWnd, CBEM_SETIMAGELIST, 0, (LPARAM)imageList.GetHImageList());
    // Set size of control to make sure it's displayed correctly now that the image list is set.
	::SetWindowPos(hWnd, NULL, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.right, SWP_NOACTIVATE);
}

//The return value is the zero-based index of the matching item. If the search is unsuccessful, it is CB_ERR
int DropDownImageList::FindString(LPCSTR pszString)
{
	return (int)::SendMessage(this->hWnd, CB_FINDSTRING, (WPARAM)-1, (LPARAM)pszString);
}

LRESULT DropDownImageList::SetSelected(int nIndex)
{
	return ::SendMessage(this->hWnd, CB_SETCURSEL, nIndex, 0);
}

int DropDownImageList::GetSelectedIndex()
{
	return (int)::SendMessage(this->hWnd, CB_GETCURSEL, 0, 0);
}


void DropDownImageList::SetSelectedByData(const wchar_t* data)
{
	this->SetSelectedByData((DWORD)_wtoi(data));
}

DWORD DropDownImageList::GetSelectedData()
{
	if (this->hWnd == NULL) return 0;
	const int selectedIndex = this->GetSelectedIndex();
	return (DWORD)::SendMessage(this->hWnd, CB_GETITEMDATA, (WPARAM)selectedIndex, (LPARAM)0);
}

void DropDownImageList::SetSelectedByData(DWORD data)
{
	const int count = (int)::SendMessage(hWnd, CB_GETCOUNT, 0, 0);
	for(int i=0; i<count; i++)
	{
		if (this->_items[i].GetData()==data)
		{
			this->SetSelected(i);
			break;
		}
	}
}

//_____________________________________________________________________ Tray
Tray::Tray(void)
{
	m_hWndParent = NULL;
	m_id = 0;
	m_hInst = NULL;
	m_bAdd = false;
	m_WinMessage = 0;
}

Tray::~Tray(void)
{
	Delete();
}

void Tray::Create(HINSTANCE hInst, HWND hWndParent, UINT id) // Call this OnCreate
{
	m_hInst =  hInst;
	m_hWndParent = hWndParent;
	m_id = id;
	m_WinMessage = ::RegisterWindowMessage(L"TaskbarCreated");
}

// -> Create() -> Add() -> Modify() -> Delete()
BOOL Tray::ModifyTip(const wchar_t* pszTip)
{
	NOTIFYICONDATA nid;

	ZeroMemory(&nid, sizeof(NOTIFYICONDATA));
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.uFlags = NIF_TIP; 
	nid.uID = this->m_id;
	nid.hWnd = m_hWndParent;
	lstrcpyn(nid.szTip, pszTip, 64);
	return Shell_NotifyIcon(NIM_MODIFY, &nid);
}

BOOL Tray::ModifyIcon(UINT idIcon)
{
	NOTIFYICONDATA nid;

	ZeroMemory(&nid, sizeof(NOTIFYICONDATA));
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.uFlags = NIF_ICON; 
	nid.uID = this->m_id;
	nid.hWnd = m_hWndParent;
	nid.hIcon = LoadIcon(m_hInst,  MAKEINTRESOURCE(idIcon));
	return Shell_NotifyIcon(NIM_MODIFY, &nid);
}

// You need to call create before calling Add
// winMessage will be sent to the parent when the user clicks on the icon
BOOL Tray::Add(UINT idIcon, const wchar_t* pszTip)
{
	NOTIFYICONDATA nid;

	Delete();
	ZeroMemory(&nid, sizeof(NOTIFYICONDATA));
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE; 
	nid.hWnd = m_hWndParent;
	nid.hIcon = LoadIcon(m_hInst,  MAKEINTRESOURCE(idIcon));
	nid.uID = m_id;
	nid.uCallbackMessage = m_WinMessage;
	//HRESULT hr = StringCbCopyN(nid.szTip, sizeof(nid.szTip), pszTip, sizeof(nid.szTip));

	lstrcpyn(nid.szTip, pszTip, 64);
	m_bAdd = true;
	return Shell_NotifyIcon(NIM_ADD, &nid);
}

BOOL Tray::Delete() 
{ 
	if (m_bAdd)
	{
		NOTIFYICONDATA nid; 
	 
		nid.cbSize = sizeof(NOTIFYICONDATA); 
		nid.hWnd = m_hWndParent; 
		nid.uID = m_id; 
		nid.uFlags = 0;
	         
		return Shell_NotifyIcon(NIM_DELETE, &nid);  
	}
	m_bAdd = false;
	return false;
}

//____________________________________________________________________ ScrollBar
ScrollBar::ScrollBar()
{
	si.cbSize = sizeof(SCROLLINFO);
}

ScrollBar::~ScrollBar()
{
}

bool ScrollBar::IsEvent(Win::Event& e, int notification)
{
	if (notification != e.uMsg) return false;
	if ((HWND)(e.lParam)!=hWnd) return false;
	return true;
}

//WORD wScrollNotify = 0xFFFF; 
// 
//case WM_KEYDOWN: 
//    switch (wParam) 
//    { 
//        case VK_UP: 
//            wScrollNotify = SB_LINEUP; 
//            break; 
//        case VK_PRIOR: 
//            wScrollNotify = SB_PAGEUP; 
//            break; 
//        case VK_NEXT: 
//            wScrollNotify = SB_PAGEDOWN; 
//            break; 
//        case VK_DOWN: 
//            wScrollNotify = SB_LINEDOWN; 
//            break; 
//        case VK_HOME: 
//            wScrollNotify = SB_TOP; 
//            break; 
//        case VK_END: 
//            wScrollNotify = SB_BOTTOM; 
//            break; 
//    } 
//    if (wScrollNotify != -1) 
//        SendMessage(hwnd, WM_VSCROLL, MAKELONG(wScrollNotify, 0), 0L); 
//    break; 

int ScrollBar::SetScrollInfo(LPCSCROLLINFO lpsi, BOOL fRedraw)
{
	return ::SetScrollInfo(this->hWnd, SB_CTL, lpsi, fRedraw);
}

int ScrollBar::SetRange(int nMin, int nMax)
{
	si.fMask = SIF_RANGE;
	si.nMin = nMin;
	si.nMax = nMax;
	return ::SetScrollInfo(this->hWnd, SB_CTL, &si, TRUE);
}

int ScrollBar::SetPosition(int nPos)
{
	si.fMask = SIF_POS;
	si.nPos = nPos;
	return ::SetScrollInfo(this->hWnd, SB_CTL, &si, TRUE);
}

int ScrollBar::SetPage(int page)
{
	si.fMask = SIF_PAGE;
	si.nPage = page;
	return ::SetScrollInfo(this->hWnd, SB_CTL, &si, TRUE);
}

int ScrollBar::GetScrollInfo(LPSCROLLINFO lpsi)
{
	return ::GetScrollInfo(this->hWnd, SB_CTL, lpsi);
}

int ScrollBar::GetPosition(int& nPos)
{
	si.fMask = SIF_POS;
	int n = ::GetScrollInfo(this->hWnd, SB_CTL, &si);
	nPos = si.nPos;
	return n;
}

int ScrollBar::GetTrackPosition(int& nPos)
{
	si.fMask = SIF_TRACKPOS;
	int n = ::GetScrollInfo(this->hWnd, SB_CTL, &si);
	nPos = si.nTrackPos;
	return n;
}

int ScrollBar::GetPage(int& page)
{
	si.fMask = SIF_PAGE;
	int n = ::GetScrollInfo(this->hWnd, SB_CTL, &si);
	page = si.nPage;
	return n;
}

int ScrollBar::GetRange(int& nMin, int& nMax)
{
	si.fMask = SIF_RANGE;
	int n = ::GetScrollInfo(this->hWnd, SB_CTL, &si);
	nMin = si.nMin;
	nMax = si.nMax;
	return n;
}


//BOOL Example::Window_HScroll(Win::Event& e)
//{
//	int position = -1;
//	position=scrollbar.GetNewPosition(e);
//	if (position!=-1) 
//	{
//		Do something with position
//		return 0;
//	}
// Returns -1 if no position change
int ScrollBar::GetNewPosition(Win::Event& e) // Call this from Window_HScroll or Window_VScroll
{
	if (this->hWnd!=(HWND)e.lParam) return -1; //The message is for other scrollbar

	//_____________________________________________ Get current scroll information
	si.fMask  = SIF_ALL;
	::GetScrollInfo((HWND)e.lParam, SB_CTL, &si);
	int nPos = si.nPos;// Save the position for comparison later on

	switch (LOWORD (e.wParam))
	{
	case SB_TOP:
		si.nPos = si.nMin;
		break;	    
	case SB_BOTTOM:
		si.nPos = si.nMax;
		break;    
	case SB_LINEUP:
		si.nPos -= 1;
		break;	    
	case SB_LINEDOWN:
		si.nPos += 1;
		break;	    
	case SB_PAGEUP:
		si.nPos -= si.nPage;
		break;	    
	case SB_PAGEDOWN:
		si.nPos += si.nPage;
		break;	    
	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos;
		break;    
	default:
		break;         
	}
	// Set the position and then retrieve it.  Due to adjustments by Windows it may not be the same as the value set.
	si.fMask = SIF_POS;
	::SetScrollInfo ((HWND)e.lParam, SB_CTL, &si, TRUE);
	::GetScrollInfo ((HWND)e.lParam, SB_CTL, &si);

	// If the position has changed, scroll the window and update it
	if (si.nPos != nPos)
	{      
		return si.nPos;
	}
	return -1;
}

//_____________________________________________________________________ Metafile
Metafile::Metafile(void)
{
	m_hEMF = NULL;
	m_hdcEMF = NULL;
	m_hMF = NULL;
}

// Create() -> Gdi functions -> Close()
HDC Metafile::Create()
{
	Delete();
	m_hdcEMF = CreateEnhMetaFile(NULL, NULL, NULL, NULL);
	return m_hdcEMF;
}

bool Metafile::Create(HENHMETAFILE hEMF)
{
	Delete();
	m_hEMF = CopyEnhMetaFile(hEMF, NULL);
	return (m_hEMF != NULL);
}

// *.emf or *.wmf
bool Metafile::CreateFromFile(const wchar_t* fileName)
{
	Delete();
	 m_hEMF = GetEnhMetaFile(fileName);
	 if (m_hEMF == NULL)
	 {
		m_hMF = GetMetaFile(fileName);
		if (m_hMF) return false;
		else return true;
	 }
	 else
	 {
		 return true;
	 }
}

// Inclusive-inclusive bounds in device units
SIZE Metafile::GetSizeInDeviceUnits(void)
{
	ENHMETAHEADER header;
	SIZE size;
	::GetEnhMetaFileHeader(this->m_hEMF, sizeof(ENHMETAHEADER), &header);
	size.cx = (header.rclBounds.right - header.rclBounds.left);
	size.cy = (header.rclBounds.bottom - header.rclBounds.top);
	return size;
}

// Inclusive-inclusive Picture Frame of metafile in .01 mm units
SIZE Metafile::GetSizeIn0_01mm(void)
{
	ENHMETAHEADER header;
	SIZE size;
	::GetEnhMetaFileHeader(this->m_hEMF, sizeof(ENHMETAHEADER), &header);
	size.cx = (header.rclFrame.right - header.rclFrame.left);
	size.cy = (header.rclFrame.bottom - header.rclFrame.top);
	return size;
}

BOOL Metafile::Enumerate(HDC hdc, const RECT* pRect)
{
	return EnumEnhMetaFile(hdc, this->m_hEMF, EmfProc, NULL, pRect);
}

// This is just a sample a it is not usefult
int CALLBACK Metafile::EmfProc(HDC hdc, HANDLETABLE* phTable, const ENHMETARECORD* pEmfRecord,
		int nHandles, LPARAM lData)
{
	switch(pEmfRecord->iType)
	{
	case EMR_LINETO:
		break;
	case EMR_SELECTOBJECT:
		break;
	case EMR_RECTANGLE:
		break;
	case EMR_ELLIPSE:
		break;
	case EMR_CREATEPEN:
		break;
	}
	return TRUE;
}

UINT Metafile::GetHeader(ENHMETAHEADER& header)
{
	return GetEnhMetaFileHeader(this->m_hEMF, sizeof(ENHMETAHEADER), &header);
}

// hdc is the control hdc
// Rect is the size of the metafile
// Create(hdc, &rect, "picture.emf", "room\0detail\0" -> Gdi functions -> Close()
HDC Metafile::CreateToFile(HDC hdcRef, RECT* pRect, const wchar_t* filename, const wchar_t* pszMetafileDescription)
{
	Delete();
	//::DeleteFile(filename);
	m_hdcEMF = ::CreateEnhMetaFile(hdcRef, filename, pRect, pszMetafileDescription);
	return m_hdcEMF;
}

HDC Metafile::CreateToFile(HWND hWnd, const wchar_t* filename, int width, int height)
{
	Delete();
	HDC hdcRef = ::GetDC(hWnd);
	 
	// Convert client coordinates to .01-mm units. 
	RECT rect;
	rect.left = 0; 
	rect.top = 0; 
	rect.right =  100 * width * GetDeviceCaps(hdcRef, HORZSIZE)/GetDeviceCaps(hdcRef, HORZRES); 
	rect.bottom = 100 * height * GetDeviceCaps(hdcRef, VERTSIZE)/GetDeviceCaps(hdcRef, VERTRES);

	m_hdcEMF = ::CreateEnhMetaFile(hdcRef, filename, &rect, L"Wintempla Metafile");
	::ReleaseDC(hWnd, hdcRef);

	return m_hdcEMF;
}

HENHMETAFILE Metafile::Close()
{
	if (m_hEMF)
	{
		::DeleteEnhMetaFile(m_hEMF);
		m_hEMF = NULL;
	}
	m_hEMF = ::CloseEnhMetaFile(m_hdcEMF);
	return m_hEMF;
}

void Metafile::Delete()
{
	if (m_hMF)
	{
		::DeleteMetaFile(m_hMF);
		m_hMF = NULL;
	}
	if (m_hEMF)
	{
		::DeleteEnhMetaFile(m_hEMF);
		m_hEMF = NULL;
	}
}

Metafile::~Metafile(void)
{
	Delete();
}

HDC Metafile::GetHDC()
{
	return this->m_hdcEMF;
}

HENHMETAFILE Metafile::GetHandle()
{
	return m_hEMF;
}

//_____________________________________________________________________ DIBitmapP

DIBitmapP::DIBitmapP(void)
{
	Constructor();
}

DIBitmapP::~DIBitmapP(void)
{
	Destructor();
}

void DIBitmapP::Constructor(void)
{
	m_bIsValid = false;
	m_ppRow = NULL;
	m_nSignature = 0;
	m_hDDB = NULL;
	m_hDIB = NULL;
	m_pBits = NULL;
	m_pBmInfo = NULL;
	ZeroMemory(&m_ds, sizeof(DIBSECTION));
}

int DIBitmapP::GetNumBitsPerPixel()
{
	return m_ds.dsBm.bmBitsPixel;
}

// There is no color table for 24 bits DIB
int DIBitmapP::GetColorTableCount()
{
	if (m_ds.dsBmih.biClrUsed != 0)
	{
		return m_ds.dsBmih.biClrUsed;
	}
	else if (m_ds.dsBm.bmBitsPixel <= 8)
	{
		return 1<< m_ds.dsBm.bmBitsPixel;
	}
	return 0;
}

// Bytes
int DIBitmapP::GetRowLength()
{
	return 4 * ( (m_ds.dsBm.bmWidth * m_ds.dsBm.bmBitsPixel + 31) / 32);
}

int DIBitmapP::GetWidth()
{
	return abs(m_ds.dsBm.bmWidth);
}

int DIBitmapP::GetHeight()
{
	return abs(m_ds.dsBm.bmHeight);
}

void DIBitmapP::Destructor(void)
{
	if (m_ppRow)
	{
		delete [] m_ppRow;
		m_ppRow = NULL;
	}

	if (m_pBmInfo)
	{
		delete [] m_pBmInfo;
		m_pBmInfo = NULL;
	}

	//if (this->m_pBits)
	//{
	//	delete [] m_pBits;
	//	m_pBits = NULL;
	//}
	if (m_hDDB)
	{
		DeleteObject(m_hDDB);
		m_hDDB = NULL;
	}
	if (m_hDIB)
	{
		DeleteObject(m_hDIB);
		m_hDIB = NULL;
	}
	m_bIsValid = false;
}

bool DIBitmapP::IsValid()
{
	return m_bIsValid;
	//return (m_nSignature==*(int*)"Dib ";
}

DWORD DIBitmapP::GetMask(int n)
{
	if (n<0 || n>2) return 0;
	return m_ds.dsBitfields[n];
}

DWORD DIBitmapP::GetRShift(int n)
{
	if (n<0 || n>2) return 0;
	return this->m_nRShift[n];
}

DWORD DIBitmapP::GetLShift(int n)
{
	if (n<0 || n>2) return 0;
	return this->m_nLShift[n];
}

int DIBitmapP::GetCompression()
{
	return m_ds.dsBmih.biCompression;
}

bool DIBitmapP::IsCompressed()
{
	if (m_ds.dsBmih.biCompression == BI_RGB) return false;
	if (m_ds.dsBmih.biCompression == BI_BITFIELDS) return false;
	return true;
}

DWORD DIBitmapP::GetMaskSize()
{
	if (m_ds.dsBmih.biCompression == BI_BITFIELDS) return 3*sizeof(DWORD);
	return 0;
}

DWORD DIBitmapP::GetColorSize()
{
	return this->GetColorTableCount() * sizeof(RGBQUAD);
}

DWORD DIBitmapP::GetInfoHeaderSize()
{
	return m_ds.dsBmih.biSize;
}

DWORD DIBitmapP::GetInfoSize()
{
	return m_ds.dsBmih.biSize + GetMaskSize() + GetColorSize();
}

DWORD DIBitmapP::GetBitsSize()
{
	if (m_ds.dsBmih.biSizeImage != 0) return m_ds.dsBmih.biSizeImage;
	return GetHeight() * GetRowLength();
}

DWORD DIBitmapP::GetTotalSize()
{
	return GetInfoSize() + GetBitsSize();
}

const BITMAPINFOHEADER* DIBitmapP::GetInfoHeader()
{
	return &(m_ds.dsBmih);
}

void* DIBitmapP::GetBits()
{
	return this->m_pBits;
}

BOOL DIBitmapP::GetTableColor(int nIndex, RGBQUAD* pRGB)
{
	HDC hdc = CreateCompatibleDC (NULL);
	SelectObject (hdc, m_hDIB);
	int nResult = GetDIBColorTable(hdc, nIndex, 1, pRGB);
	DeleteDC(hdc);

	return nResult ? TRUE : FALSE;
}

BOOL DIBitmapP::SetTableColor(int nIndex, const RGBQUAD* pRGB)
{
     HDC hdc = CreateCompatibleDC(NULL);
     SelectObject(hdc, m_hDIB);
     int n = SetDIBColorTable(hdc, nIndex, 1, pRGB);
     DeleteDC(hdc);

     return n ? TRUE : FALSE;
}

BYTE* DIBitmapP::GetPixelPtr(int x, int y)
{
	if (this->IsCompressed()) return NULL;
	if (x < 0 || x >= m_ds.dsBm.bmWidth || y < 0 || y >= m_ds.dsBm.bmHeight) return NULL;
	return (this->m_ppRow[y]) + (x * m_ds.dsBm.bmBitsPixel >> 3);
}

DWORD DIBitmapP::GetPixel (int x, int y)
{
	PBYTE pPixel;

	//_________________________________________
	//if (!(pPixel = GetPixelPtr(x, y))) return 0;

	//if (this->IsCompressed()) return NULL;

#ifdef _DEBUG
	if (m_ds.dsBmih.biCompression != BI_RGB && m_ds.dsBmih.biCompression != BI_BITFIELDS) return 0;
	if (x < 0 || x >= m_ds.dsBm.bmWidth || y < 0 || y >= m_ds.dsBm.bmHeight) return 0;
#endif
	pPixel = (this->m_ppRow[y]) + (x * m_ds.dsBm.bmBitsPixel >> 3);
	//___________________________________
	
	switch (m_ds.dsBm.bmBitsPixel)
	{
	case  1:  return 0x01 & (* pPixel >> (7 - (x & 7)));
	case  4:  return 0x0F & (* pPixel >> (x & 1 ? 0 : 4));
	case  8:  return * pPixel;
	case 16:  return * (DWORD *) pPixel;
	case 24:  return 0x00FFFFFF & * (DWORD *) pPixel; 
	case 32:  return * (DWORD *) pPixel;
	}
	return 0;
}

bool DIBitmapP::ExtractPixels(vector<valarray<COLORREF> >& output)
{
	if (m_ds.dsBmih.biCompression != BI_RGB && m_ds.dsBmih.biCompression != BI_BITFIELDS)
	{
		output.clear();
		return true;
	}

	RGBTRIPLE value;
	const int countX = GetWidth();
	const int countY = GetHeight();
	int x= 0;
	int y = 0;
	//_______________________________ Memory allocation
	try
	{
		output.resize(countY);
		for(y=0; y<countY; y++) output[y].resize(countX);
	}
	catch(std::bad_alloc& )
	{
		return false;
	}
	for(y=0; y<countY; y++)
	{
		for(x=0; x<countX; x++)
		{
			value =*((RGBTRIPLE *) (this->m_ppRow[y] +  3*x  ));
			output[y][x] = RGB(value.rgbtRed, value.rgbtGreen, value.rgbtBlue);		
		}
	}
	return true;
}

bool DIBitmapP::ExtractGrayPixels(MATRIX& output)
{
	if (m_ds.dsBmih.biCompression != BI_RGB && m_ds.dsBmih.biCompression != BI_BITFIELDS)
	{
		output.clear();
		return true;
	}

	RGBTRIPLE value;
	const int countX = GetWidth();
	const int countY = GetHeight();
	int x= 0;
	int y = 0;
	//_______________________________ Memory allocation
	try
	{
		output.resize(countY);
		for(y=0; y<countY; y++) output[y].resize(countX);
	}
	catch(std::bad_alloc& )
	{
		return false;
	}
	for(y=0; y<countY; y++)
	{
		for(x=0; x<countX; x++)
		{
			value =*((RGBTRIPLE *) (this->m_ppRow[y] +  3*x  ));
			output[y][x] = (value.rgbtRed+value.rgbtGreen+value.rgbtBlue)/3.0;		
		}
	}
	return true;
}

bool DIBitmapP::ExtractColorPixels(MATRIX& outRed, MATRIX& outGreen, MATRIX& outBlue)
{
	if (m_ds.dsBmih.biCompression != BI_RGB && m_ds.dsBmih.biCompression != BI_BITFIELDS)
	{
		outRed.clear();
		outGreen.clear();
		outBlue.clear();
		return true;
	}

	RGBTRIPLE value;
	const int countX = GetWidth();
	const int countY = GetHeight();
	int x= 0;
	int y = 0;
	//_______________________________ Memory allocation
	try
	{
		outRed.resize(countY);
		outGreen.resize(countY);
		outBlue.resize(countY);
		for(y=0; y<countY; y++)
		{
			outRed[y].resize(countX);
			outGreen[y].resize(countX);
			outBlue[y].resize(countX);
		}
	}
	catch(std::bad_alloc& )
	{
		return false;
	}
	for(y=0; y<countY; y++)
	{
		for(x=0; x<countX; x++)
		{
			value =*((RGBTRIPLE *) (this->m_ppRow[y] +  3*x  ));
			outRed[y][x] = value.rgbtRed;
			outGreen[y][x] = value.rgbtGreen;
			outBlue[y][x] = value.rgbtBlue;		
		}
	}
	return true;
}

BOOL DIBitmapP::SetPixel (int x, int y, DWORD dw)
{
     PBYTE pPixel;

     if (!(pPixel = GetPixelPtr(x, y))) return FALSE;

	 switch (this->GetNumBitsPerPixel())
     {
     case  1:  * pPixel &= ~(1     << (7 - (x & 7)));
               * pPixel |= dw << (7 - (x & 7));
               break;

     case  4:  * pPixel &= 0x0F    << (x & 1 ? 4 : 0);
               * pPixel |= dw << (x & 1 ? 0 : 4);
               break;

     case  8:  * pPixel = (BYTE) dw;
               break;

     case 16:  * (DWORD *) pPixel = dw;
               break;

     case 24:  * (RGBTRIPLE *) pPixel = * (RGBTRIPLE *) &dw; 
               break;

     case 32:  * (DWORD *) pPixel = dw;
               break;
     default:
          return FALSE;
     }
     return TRUE;
}

BOOL DIBitmapP::GetPixelColor (int x, int y, RGBQUAD* pRgb)
{
     DWORD dwPixel;
	 int nBitCount = this->GetNumBitsPerPixel();
	
	 if (nBitCount ==0) return FALSE;

     dwPixel = GetPixel(x, y);

	if (nBitCount <= 8) 
	{
		return GetTableColor((int) dwPixel, pRgb);	// If the bit-count is 8 or less, index the color table
	}
	else if (nBitCount == 24)	// If the bit-count is 24, just use the pixel
	{
		* (RGBTRIPLE *) pRgb = * (RGBTRIPLE *) & dwPixel;
		pRgb->rgbReserved = 0;
	}
	else if (nBitCount == 32 && m_ds.dsBmih.biCompression == BI_RGB) 	// If the bit-count is 32 and the biCompression field is BI_RGB, just use the pixel
	{
		* pRgb = * (RGBQUAD *) & dwPixel;
	}
	else
	{
		// Otherwise, use the mask and shift values
		//   (for best performance, don't use DibMask and DibShift functions)
		pRgb->rgbRed   = (BYTE) (((m_ds.dsBitfields[0] & dwPixel) >> m_nRShift[0]) << m_nLShift[0]);
		pRgb->rgbGreen = (BYTE) (((m_ds.dsBitfields[1] & dwPixel) >> m_nRShift[1]) << m_nLShift[1]);
		pRgb->rgbBlue  = (BYTE) (((m_ds.dsBitfields[2] & dwPixel) >> m_nRShift[2]) << m_nLShift[2]);
	}
	return TRUE;
}

BOOL DIBitmapP::SetPixelColor (int x, int y, RGBQUAD* pRgb)
{
	DWORD dwPixel;
	int        iBitCount;
	// Don't do this function for DIBs with color tables

	iBitCount = this->GetNumBitsPerPixel();

	if (iBitCount <= 8)
	{
		return FALSE;
	}
	else if (iBitCount == 24)
	{
		* (RGBTRIPLE *) & dwPixel = * (RGBTRIPLE *) pRgb;
		dwPixel &= 0x00FFFFFF;
	}
	else if (iBitCount == 32 && m_ds.dsBmih.biCompression == BI_RGB)
	{
		* (RGBQUAD *) & dwPixel = * pRgb;
	}
	else
	{
		dwPixel  = (((DWORD) pRgb->rgbRed >> m_nLShift[0]) << m_nRShift[0]); 
		dwPixel |= (((DWORD) pRgb->rgbGreen >> m_nLShift[1])<< m_nRShift[1]); 
		dwPixel |= (((DWORD) pRgb->rgbBlue >> m_nLShift[2])<< m_nRShift[2]); 
	}
	SetPixel (x, y, dwPixel);
	return TRUE;
}

/*--------------------------------------------------------------
   Calculating shift values from color masks is required by the 
     DibCreateFromInfo function.
  --------------------------------------------------------------*/

int DIBitmapP::MaskToRShift (DWORD dwMask)
{
     int iShift;

     if (dwMask == 0) return 0;

     for (iShift = 0; !(dwMask & 1); iShift++) dwMask >>= 1;

     return iShift;
}

int DIBitmapP::MaskToLShift (DWORD dwMask)
{
     int iShift;
     if (dwMask == 0) return 0;

     while (!(dwMask & 1))dwMask >>= 1;

     for (iShift = 0; dwMask & 1; iShift++) dwMask >>= 1;

     return 8 - iShift;
}

bool DIBitmapP::CreateFromFile(const wchar_t* pszFileName)
{
	bool bOk = false;
	DWORD dwBytesRead, dwInfoSize, dwBitsSize;
	HANDLE hFile;
	BITMAPFILEHEADER bmfh;

	Destructor();
	hFile = ::CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
				OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (hFile == INVALID_HANDLE_VALUE) return false;

	if (ReadFile(hFile, &bmfh, sizeof(BITMAPFILEHEADER), &dwBytesRead, NULL))
	{
		if ( dwBytesRead == sizeof(BITMAPFILEHEADER) && bmfh.bfType == *(WORD*) "BM")
		{
			dwInfoSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
			if (m_pBmInfo = new BYTE[dwInfoSize])
			{
				if (ReadFile(hFile, m_pBmInfo, dwInfoSize, &dwBytesRead, NULL))
				{
					if (dwBytesRead == dwInfoSize)
					{
						if (CreateFromInfo((BITMAPINFO*)m_pBmInfo))
						{
							dwBitsSize = bmfh.bfSize - bmfh.bfOffBits;						
							if (ReadFile(hFile, m_pBits, dwBitsSize, &dwBytesRead, NULL))
							{
								if (dwBytesRead == dwBitsSize)
								{
									bOk = true;		
								}
							}
						}
					}
				}
			}
		}
	}
	CloseHandle(hFile);
	return bOk;
}

bool DIBitmapP::CreateFromInfo(BITMAPINFO* pBmInfo)
{
	int i;
	BYTE* pBits;

	HWND hWnd = ::GetDesktopWindow();
	HDC hdc = ::GetDC(hWnd);

	m_hDIB = CreateDIBSection (hdc, pBmInfo, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);

	if (m_hDIB == NULL)
	{
		if (hWnd != NULL && hdc!= NULL) ::ReleaseDC(hWnd, hdc);
		return false;
	}

	m_nSignature = (* (int*) "Dib ");
	GetObject(m_hDIB, sizeof (DIBSECTION), &this->m_ds);
	m_pBits = pBits;

	if (GetCompression() == BI_BITFIELDS)
	{
		for (i = 0; i < 3; i++)
		{
			m_nLShift[i] = MaskToLShift(m_ds.dsBitfields[i]);
			m_nRShift[i] = MaskToRShift(m_ds.dsBitfields[i]);
		}
	}
	else if (GetCompression() == BI_RGB)
	{
		if (m_ds.dsBm.bmBitsPixel == 16)
		{
			m_ds.dsBitfields[0] = 0x00007C00;
			m_ds.dsBitfields[1] = 0x000003E0;
			m_ds.dsBitfields[2] = 0x0000001F;

			m_nRShift[0] = 10;
			m_nRShift[1] =  5;
			m_nRShift[2] =  0; 

			m_nLShift[0] =  3;
			m_nLShift[1] =  3;
			m_nLShift[2] =  3;
		}
		else if (m_ds.dsBm.bmBitsPixel== 24 || m_ds.dsBm.bmBitsPixel == 32)
		{
			m_ds.dsBitfields[0] = 0x00FF0000;
			m_ds.dsBitfields[1] = 0x0000FF00;
			m_ds.dsBitfields[2] = 0x000000FF;

			m_nRShift[0] = 16;
			m_nRShift[1] =  8;
			m_nRShift[2] =  0; 

			m_nLShift[0] =  0;
			m_nLShift[1] =  0;
			m_nLShift[2] =  0;
		}
	}
	// Allocate an array of pointers to each row in the DIB
	this->m_nRow = GetHeight();
	m_ppRow = new BYTE*[m_nRow];
	int nRowLength = GetRowLength();

	if (pBmInfo->bmiHeader.biHeight > 0) // bottom up
	{
		for (size_t y = 0; y<m_nRow; y++) 
			m_ppRow[y] = pBits + (m_nRow - y - 1) * nRowLength;
	}
	else // top down
	{
		for (size_t y = 0; y < m_nRow; y++)
			m_ppRow[y] = pBits + y * nRowLength;
	}
	m_bIsValid = true;


	if (hWnd != NULL && hdc!= NULL) ::ReleaseDC(hWnd, hdc);
	return true;
}

// Creates an empty Device Independent Bitmap
bool DIBitmapP::Create(int width, int height, int nBitsPerPixel, int nColors)
{
	BITMAPINFO * pbmi;
	PBYTE p = NULL;
	DWORD  dwInfoSize;
	int cEntries;

	Destructor();

	if (width <= 0 || height <= 0 || 
	((nBitsPerPixel !=  1) && (nBitsPerPixel !=  4) && (nBitsPerPixel !=  8) && 
	(nBitsPerPixel != 16) && (nBitsPerPixel != 24) && (nBitsPerPixel != 32)))
	{
		return false;
	}

	if (nColors != 0) cEntries = nColors;
	else if (nBitsPerPixel <= 8) cEntries = 1 << nBitsPerPixel;

	dwInfoSize = sizeof (BITMAPINFOHEADER) + (cEntries - 1) * sizeof (RGBQUAD);

	if (NULL == (p = new BYTE[dwInfoSize]))
	{
		return false;
	}

	pbmi = (BITMAPINFO*)p;
	ZeroMemory (pbmi, dwInfoSize);

	pbmi->bmiHeader.biSize  = sizeof (BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = width;
	pbmi->bmiHeader.biHeight = height;
	pbmi->bmiHeader.biPlanes = 1;
	pbmi->bmiHeader.biBitCount  = nBitsPerPixel;
	pbmi->bmiHeader.biCompression  = BI_RGB;
	pbmi->bmiHeader.biSizeImage = 0;
	pbmi->bmiHeader.biXPelsPerMeter = 0;
	pbmi->bmiHeader.biYPelsPerMeter = 0;
	pbmi->bmiHeader.biClrUsed  = nColors;
	pbmi->bmiHeader.biClrImportant  = 0;

	this->CreateFromInfo(pbmi);

	if (p) delete [] p;

	return true;
}


// You must release the memory of the pointer returned
// It returns a BITMAPINFO*
PBYTE DIBitmapP::CreateBitmapInfo()
{
	PBYTE p = NULL;
	int          i, iNumColors;
	RGBQUAD    * prgb;

	if (this->m_bIsValid == false) return NULL;

	p = new BYTE[this->GetInfoSize()];
	if (p == NULL) return NULL;

	CopyMemory (p, this->GetInfoHeader(), sizeof (BITMAPINFOHEADER));
	prgb = (RGBQUAD *) ((BYTE *) p + sizeof (BITMAPINFOHEADER));

	if (this->GetMaskSize())
	{
		CopyMemory (prgb, m_ds.dsBitfields, 3 * sizeof (DWORD));
		prgb = (RGBQUAD *) ((BYTE *) prgb + 3 * sizeof (DWORD));
	}

	iNumColors = this->GetColorTableCount();

	for (i = 0; i < iNumColors; i++)
		this->GetTableColor(i, prgb + i);

	return p;
}


//   Copy:  Creates a new DIB section from an existing DIB section,
//    possibly swapping the DIB width and height.
//HDIB Copy(HDIB hdibSrc, bool bRotate)
//{
//	BITMAPINFO * pbmi;
//	BYTE       * pBitsSrc, * pBitsDst;
//	HDIB         hdibDst;
//
//	if (NULL == (pbmi = DibCopyToInfo (hdibSrc)))
//	return NULL;
//
//	if (bRotate)
//	{
//		pbmi->bmiHeader.biWidth = DibHeight (hdibSrc);
//		pbmi->bmiHeader.biHeight = DibWidth (hdibSrc);
//	}
//
//	hdibDst = DibCreateFromInfo (pbmi);
//	free (pbmi);
//
//	if (hdibDst == NULL) return NULL;
//
//	if (!bRotate)
//	{
//		pBitsSrc = DibBitsPtr (hdibSrc);
//		pBitsDst = DibBitsPtr (hdibDst);
//
//		CopyMemory (pBitsDst, pBitsSrc, DibBitsSize (hdibSrc));
//	}
//	return hdibDst;
//}

bool DIBitmapP::SaveToFile(const wchar_t* szFileName)
{
	BITMAPFILEHEADER bmfh;
	BOOL             bSuccess;
	DWORD            dwTotalSize, dwBytesWritten;
	HANDLE           hFile;
	PBYTE pBmInfo = NULL;

	hFile = CreateFile (szFileName, GENERIC_WRITE, 0, NULL,
					CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE) return false;

	dwTotalSize  = GetTotalSize();

	bmfh.bfType      = * (WORD *) "BM";
	bmfh.bfSize      = sizeof (BITMAPFILEHEADER) + dwTotalSize;
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits   = bmfh.bfSize - GetBitsSize();

	// Write the BITMAPFILEHEADER
	bSuccess = WriteFile(hFile, &bmfh, sizeof (BITMAPFILEHEADER), &dwBytesWritten, NULL);
	if (!bSuccess || (dwBytesWritten != sizeof (BITMAPFILEHEADER)))
	{
		CloseHandle (hFile);
		DeleteFile (szFileName);
		return false;
	}

	// Get entire DIB in packed DIB format
	pBmInfo = CopyToPackedDib (FALSE);
	if(pBmInfo == NULL)
	{
		CloseHandle (hFile);
		DeleteFile (szFileName);
		return false;
	}

	// Write out the packed-DIB
	bSuccess = WriteFile(hFile, pBmInfo, dwTotalSize, &dwBytesWritten, NULL);
	CloseHandle (hFile);
	if (pBmInfo) delete [] pBmInfo;

	if (!bSuccess || (dwBytesWritten != dwTotalSize))
	{
		DeleteFile (szFileName);
		return false;
	}
	return true;
}

//DibCopyToPackedDib is generally used for saving DIBs and for 
//  transferring DIBs to the clipboard. In the second case, the second 
//  argument should be set to TRUE so that the memory is allocated 
//  with the GMEM_SHARE flag.
// Release the memory return.  It returns a BITMAPINFO*
PBYTE DIBitmapP::CopyToPackedDib(bool bUseGlobalMemory)
{
	PBYTE pBmInfo = NULL;
	BYTE       * pBits;
	DWORD        dwDibSize;
	HDC          hdcMem;
	HGLOBAL      hGlobal = NULL;
	int          iNumColors;
	RGBQUAD    * prgb;

	if (m_bIsValid == false) return NULL;

	dwDibSize = GetTotalSize();

	if (bUseGlobalMemory)
	{
		hGlobal = GlobalAlloc (GHND | GMEM_SHARE, dwDibSize);
		pBmInfo = (PBYTE)GlobalLock(hGlobal);
	}
	else
	{
		pBmInfo = new BYTE[dwDibSize];
	}

	if (pBmInfo == NULL) return NULL;

	// Copy the information header
	CopyMemory(pBmInfo, &m_ds.dsBmih, sizeof (BITMAPINFOHEADER));
	prgb = (RGBQUAD *) ( pBmInfo + sizeof (BITMAPINFOHEADER));

	// Copy the possible color masks
	if (m_ds.dsBmih.biCompression == BI_BITFIELDS)
	{
		CopyMemory (prgb, m_ds.dsBitfields, 3 * sizeof (DWORD));
		prgb = (RGBQUAD *) ((BYTE *) prgb + 3 * sizeof (DWORD));
	}

	// Copy the color table
	if (iNumColors = this->GetColorTableCount())
	{
		hdcMem = CreateCompatibleDC (NULL);
		SelectObject (hdcMem, this->m_hDIB);
		GetDIBColorTable (hdcMem, 0, iNumColors, prgb);
		DeleteDC (hdcMem);
	}

	pBits = (BYTE *) (prgb + iNumColors);
	CopyMemory (pBits, m_pBits, GetBitsSize());

	// If last argument is TRUE, unlock global memory block and 
	//   cast it to pointer in preparation for return

	if (bUseGlobalMemory)
	{
		if (hGlobal != NULL) GlobalUnlock (hGlobal);
		pBmInfo = (BYTE *) hGlobal;     
	}
	return pBmInfo;
}

//CopyFromPackedDib is generally used for pasting DIBs from the clipboard.
BOOL DIBitmapP::CopyFromPackedDib (BITMAPINFO * pPackedDib)
{
	BYTE     * pBits;     
	DWORD      dwInfoSize, dwMaskSize, dwColorSize;
	int        iBitCount;
	BOOL bOk = FALSE;

	dwInfoSize = pPackedDib->bmiHeader.biSize;

	if (dwInfoSize != sizeof (BITMAPCOREHEADER) &&
	dwInfoSize != sizeof (BITMAPINFOHEADER) &&
	dwInfoSize != sizeof (BITMAPV4HEADER) &&
	dwInfoSize != sizeof (BITMAPV5HEADER))
	{
		return FALSE;
	}

	// Get the possible size of the color masks
	if (dwInfoSize == sizeof (BITMAPINFOHEADER) && pPackedDib->bmiHeader.biCompression == BI_BITFIELDS)
	{
		dwMaskSize = 3 * sizeof (DWORD);
	}
	else
	{
		dwMaskSize = 0;
	}

	// Get the size of the color table
	if (dwInfoSize == sizeof (BITMAPCOREHEADER))
	{
		iBitCount = ((BITMAPCOREHEADER *) pPackedDib)->bcBitCount;
		if (iBitCount <= 8) dwColorSize = (1 << iBitCount) * sizeof (RGBTRIPLE);
		else dwColorSize = 0;
	}
	else           // all non-OS/2 compatible DIBs
	{
		if (pPackedDib->bmiHeader.biClrUsed > 0)
		{
			dwColorSize = pPackedDib->bmiHeader.biClrUsed * sizeof (RGBQUAD);
		}
		else if (pPackedDib->bmiHeader.biBitCount <= 8)
		{
			dwColorSize = (1 << pPackedDib->bmiHeader.biBitCount) * sizeof (RGBQUAD);
		}
		else
		{
			dwColorSize = 0;
		}
	}

	// Finally, get the pointer to the bits in the packed-DIB
	pBits = (BYTE *) pPackedDib + dwInfoSize + dwMaskSize + dwColorSize;

	// Create the HDIB from the packed DIB pointer
	bOk = CreateFromInfo(pPackedDib);

	// Copy the pixel bits
	CopyMemory (m_pBits, pBits, GetBitsSize());

	return bOk;
}

bool DIBitmapP::CopyRotate(Win::DIBitmapP& dib, bool bRotate)
{
	PBYTE pBmInfo = NULL;
	BYTE       * pBitsSrc = NULL;
	bool bOk = false;

	if (dib.IsValid()==false) return false;

	pBmInfo = dib.CreateBitmapInfo();
	if (pBmInfo == NULL) return false;

	if (bRotate)
	{
		((BITMAPINFO*)pBmInfo)->bmiHeader.biWidth = dib.GetHeight();
		((BITMAPINFO*)pBmInfo)->bmiHeader.biHeight = dib.GetWidth();
	}

	bOk = this->CreateFromInfo((BITMAPINFO*)pBmInfo);
	if (pBmInfo) delete [] pBmInfo;
	if (bOk==false) return false;

	// Copy the bits
	if (!bRotate)
	{
		CopyMemory (m_pBits, dib.GetBits(), dib.GetBitsSize());
	}
	return true;
}

bool DIBitmapP::CreateFlip(Win::DIBitmapP& dib, bool bHorizontal)
{
	int  cx, cy, x, y;

	Destructor();
	if (dib.IsCompressed()) return false;
	if (CopyRotate(dib, false) == FALSE) return false;

	cx = dib.GetWidth();
	cy = dib.GetHeight();

	for (x = 0; x < cx; x++)
	for (y = 0; y < cy; y++)
	{
		if (bHorizontal)
			this->SetPixel(x, cy - 1 - y, dib.GetPixel(x, y));
		else
			this->SetPixel(cx -1 - x, y, dib.GetPixel(x, y));
	}
	return true;
}

bool DIBitmapP::CreateRotate(Win::DIBitmapP& dib)
{
	int  cx, cy, x, y;

	Destructor();
	if (dib.IsCompressed()) return false;
	if (CopyRotate(dib,true) == FALSE) return false;

	cx = dib.GetWidth();
	cy = dib.GetHeight();

	switch (dib.GetNumBitsPerPixel())
	{
	case  1:  
		for (x = 0; x < cx; x++)
		for (y = 0; y < cy; y++)
		SetPixel1(cy - y - 1, x, dib.GetPixel1(x, y));
		break;

	case  4:  
		for (x = 0; x < cx; x++)
		for (y = 0; y < cy; y++)
		SetPixel4(cy - y - 1, x, dib.GetPixel4(x, y));
		break;

	case  8:
		for (x = 0; x < cx; x++)
		for (y = 0; y < cy; y++)
		SetPixel8(cy - y - 1, x, dib.GetPixel8(x, y));
		break;

	case 16:  
		for (x = 0; x < cx; x++)
		for (y = 0; y < cy; y++)
		SetPixel16(cy - y - 1, x, dib.GetPixel16(x, y));
		break;

	case 24:
		for (x = 0; x < cx; x++)
		for (y = 0; y < cy; y++)
		SetPixel24(cy - y - 1, x, dib.GetPixel24 (x, y));
		break;

	case 32:  
		for (x = 0; x < cx; x++)
		for (y = 0; y < cy; y++)
		SetPixel32(cy - y - 1, x, dib.GetPixel32(x, y));
		break;
	}
	return true;
}

BYTE DIBitmapP::GetPixel1(int x, int y)
{
	return (0x01 & (* GetPixelPtr1 (x, y) >> (7 - ((x) & 7))));
}

BYTE DIBitmapP::GetPixel4(int x, int y)
{
	return (0x0F & (* GetPixelPtr4 (x, y) >> ((x) & 1 ? 0 : 4)));
}

BYTE DIBitmapP::GetPixel8(int x, int y)
{
	return (* GetPixelPtr8  (x, y));
}

WORD DIBitmapP::GetPixel16(int x, int y)
{
	return (* GetPixelPtr16 (x, y));
}

COLORREF DIBitmapP::GetPixelRgb24(int x, int y)
{
	//RGBTRIPLE value = (* GetPixelPtr24 (x, y));
#ifdef _DEBUG
	if (m_ds.dsBmih.biCompression != BI_RGB && m_ds.dsBmih.biCompression != BI_BITFIELDS) return 0;
	if (x < 0 || x >= m_ds.dsBm.bmWidth || y < 0 || y >= m_ds.dsBm.bmHeight) return 0;
#endif
	RGBTRIPLE value =*((RGBTRIPLE *) (this->m_ppRow[y] +  3*x  ));
	return RGB(value.rgbtRed, value.rgbtGreen, value.rgbtBlue);
}

RGBTRIPLE DIBitmapP::GetPixel24(int x, int y)
{
	return (* GetPixelPtr24 (x, y));
}

DWORD DIBitmapP::GetPixel32(int x, int y)
{
	return (* GetPixelPtr32(x, y));
}

void DIBitmapP::SetPixel1(int x, int y, BYTE p)
{
	(* GetPixelPtr1( x, y) &= ~( 1  << (7 - ((x) & 7)))), (* GetPixelPtr1(x, y) |=  ((p) << (7 - ((x) & 7))));
}

void DIBitmapP::SetPixel4(int x, int y, BYTE p)
{
	(* GetPixelPtr4(x, y) &= (0x0F << ((x) & 1 ? 4 : 0))), (* GetPixelPtr4(x, y) |= ((p)  << ((x) & 1 ? 0 : 4)));
}

void DIBitmapP::SetPixel8(int x, int y, BYTE p)
{
	*GetPixelPtr8(x, y) = p;
}

void DIBitmapP::SetPixel16(int x, int y, WORD p)
{
	*GetPixelPtr16(x, y) = p;
}

void DIBitmapP::SetPixel24(int x, int y, RGBTRIPLE p)
{
	*GetPixelPtr24(x, y) = p;
}

void DIBitmapP::SetPixel32(int x, int y, DWORD p)
{
	*GetPixelPtr32(x, y) = p;
}

//_____________________________________________________________________ DIBitmap
DIBitmap::DIBitmap(void)
{
	pData = NULL;
	pBmInfo = NULL;
	pBits = NULL;
	pBmFH = NULL;
	nWidth = 0;
	nHeight = 0;
}

DIBitmap::~DIBitmap(void)
{
	Destructor();
}

void DIBitmap::Destructor()
{
	if (pData)
	{
		delete pData;
		pData = NULL;
	}
	pBmInfo = NULL;
	pBits = NULL;
	pBmFH = NULL;
	nWidth = 0;
	nHeight = 0;
}

BOOL DIBitmap::CreateFromFile(const wchar_t* filename)
{
	BOOL bOk = FALSE;
	DWORD dwFileSize, dwHighSize, dwBytesRead;
	HANDLE hFile;

	Destructor();
	hFile = CreateFile (filename, GENERIC_READ, FILE_SHARE_READ, NULL,
				OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		dwFileSize = GetFileSize(hFile, &dwHighSize);
		if (dwHighSize == 0)
		{
			this->pData = new BYTE[(size_t)dwFileSize];
			if (pData)
			{
				bOk = ReadFile (hFile, pData, dwFileSize, &dwBytesRead, NULL);
				this->pBmFH = (BITMAPFILEHEADER*)pData;
				
				if (!bOk || (dwBytesRead != dwFileSize)         
						|| (this->pBmFH->bfType != * (WORD *) "BM") 
						|| (this->pBmFH->bfSize != dwFileSize))
				{
					bOk = false;
				}
				else
				{
					bOk = true;
					this->pBmInfo = (BITMAPINFO*)(pBmFH+1);
					this->pBits = (BYTE*)pBmFH+pBmFH->bfOffBits;
					if (this->pBmInfo->bmiHeader.biSize == sizeof(BITMAPCOREHEADER))
					{
						this->nWidth = ((BITMAPCOREHEADER*)pBmInfo)->bcWidth;
						this->nHeight = ((BITMAPCOREHEADER*)pBmInfo)->bcWidth;
					}
					else
					{
						this->nWidth = this->pBmInfo->bmiHeader.biWidth;
						this->nHeight = abs(this->pBmInfo->bmiHeader.biHeight);
					}
				}
			}
		}
		CloseHandle(hFile);
	}
	return bOk;
}

BOOL DIBitmap::SaveToFile(const wchar_t* filename)
{
     BOOL   bOk = FALSE;
     DWORD  dwBytesWritten;
     HANDLE hFile;

	 if (this->pBmFH)
	 {
		hFile = CreateFile(filename, GENERIC_WRITE, 0, NULL,
							CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL) ;

		if (hFile == INVALID_HANDLE_VALUE) return FALSE ;

		bOk = WriteFile (hFile, pBmFH, pBmFH->bfSize, &dwBytesWritten, NULL) ;
		CloseHandle (hFile);

		if (!bOk || (dwBytesWritten != pBmFH->bfSize))
		{
			DeleteFile (filename) ;
			return FALSE ;
		}
	 }
     return TRUE ;
}

int DIBitmap::GetWidth()
{
	return nWidth;
}

int DIBitmap::GetHeight()
{
	return nHeight;
}

//_____________________________________________________________________ DDBitmap
DDBitmap::DDBitmap(void)
{
	hBitmap = NULL;
	hdcMem = NULL;
	ZeroMemory(&bitmap, sizeof(BITMAP));
}

DDBitmap::~DDBitmap(void)
{
	Destructor();
}

HDC DDBitmap::GetBitmapDC()
{
	return this->hdcMem;
}

void DDBitmap::Create(HBITMAP hBitmap)
{
	Destructor();

	if (hBitmap)
	{
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		this->hBitmap = CreateBitmapIndirect(&bitmap);
		//
		HDC hdc = CreateCompatibleDC(NULL);
		HDC hdcm = CreateCompatibleDC(NULL);
		//
		SelectObject(hdcm, this->hBitmap); // Destination
		SelectObject(hdc, hBitmap); // Source
		//
		BitBlt(hdcm, 0, 0, bitmap.bmWidth, bitmap.bmHeight,
					hdc, 0, 0, SRCCOPY);
		DeleteDC(hdcm);
		DeleteDC(hdc);
	}
}

void DDBitmap::Copy(const DDBitmap& init)
{
	Destructor();

	if (init.hBitmap)
	{
		::GetObject(init.hBitmap, sizeof(BITMAP), &bitmap);
		this->hBitmap = CreateBitmapIndirect(&bitmap);
		//
		HDC hdc = CreateCompatibleDC(NULL);
		HDC hdcm = CreateCompatibleDC(NULL);
		//
		SelectObject(hdcm, this->hBitmap); // Destination
		SelectObject(hdc, init.hBitmap); // Source
		//
		BitBlt(hdcm, 0, 0, bitmap.bmWidth, bitmap.bmHeight,
					hdc, 0, 0, SRCCOPY);
		DeleteDC(hdcm);
		DeleteDC(hdc);
	}
}

DDBitmap::DDBitmap(const DDBitmap& init)
{
	Copy(init);
}

DDBitmap& DDBitmap::operator =(const DDBitmap&init)
{
	Copy(init);
	return *this;
}

int DDBitmap::GetWidth()
{
	return bitmap.bmWidth;
}

int DDBitmap::GetHeight()
{
	return bitmap.bmHeight;
}

HBITMAP DDBitmap::CreateFromDIB(HWND hWnd, Win::DIBitmap& dib)
{
	HDC hdc = GetDC(hWnd);
	CreateFromDIB(hdc, dib);
	ReleaseDC(hWnd, hdc);
	return hBitmap;
}

HBITMAP DDBitmap::CreateFromDIB(HWND hWnd, Win::DIBitmapP& dib)
{
	HDC hdc = GetDC(hWnd);
	CreateFromDIB(hdc, dib);
	ReleaseDC(hWnd, hdc);
	return hBitmap;
}

HBITMAP DDBitmap::CreateFromDIB(HDC hdc, Win::DIBitmapP& dib)
{
	Destructor();
	if (dib.IsValid() == false) return NULL;

	PBYTE pBmInfo = dib.CreateBitmapInfo();
	const BITMAPINFOHEADER* pBmFH = dib.GetInfoHeader();
	if (pBmFH)
	{
		hBitmap = CreateDIBitmap
		(
			hdc, 
			pBmFH, 
			CBM_INIT, 
			dib.GetBits(),
			(BITMAPINFO*)pBmInfo, 
			DIB_RGB_COLORS
		);
		if (pBmInfo) delete [] pBmInfo;
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	}
	return hBitmap;
}

HBITMAP DDBitmap::CreateFromDIB(HDC hdc, Win::DIBitmap& dib)
{
	Destructor();
	const BITMAPFILEHEADER* pBmFH = dib.GetFileHeader();
	if (pBmFH)
	{
		hBitmap = CreateDIBitmap
			(
				hdc, 
				(BITMAPINFOHEADER*)(pBmFH+1), 
				CBM_INIT, 
				(BYTE*)pBmFH+pBmFH->bfOffBits,
				(BITMAPINFO*)(pBmFH+1), 
				DIB_RGB_COLORS
			);
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	}
	return hBitmap;
}

// For monochrome bitmap:  nPlanes =1, nBitcount = 1
// i.e. BYTE bits[] = {...};
// CreateFromBits(20, 5, 1, 1, pBits)
HBITMAP DDBitmap::CreateFromBits(int width, int height, int nPlanes, int nBitCount, DWORD* bits)
{
	Destructor();
	return CreateBitmap(width, height, nPlanes, nBitCount, bits);
}

// It creates a bitmap compatible with the hdc.  The returned hdc can be used to draw over the bitmap
// Use BitBlt to copy the bitmap to another HDC
HDC DDBitmap::CreateCompatible(HDC hdc, int width, int height)
{
	Destructor();
	this->hBitmap = ::CreateCompatibleBitmap(hdc, width, height);
	hdcMem = ::CreateCompatibleDC(hdc);
	::SelectObject(hdcMem, hBitmap);
	this->bitmap.bmWidth = width;
	this->bitmap.bmHeight = height;
	return hdcMem;
}

// It creates a bitmap compatible with the hdc.  The returned hdc can be used to draw over the bitmap
// Use BitBlt to copy the bitmap to another HDC
HDC DDBitmap::CreateCompatible(HWND hWnd, int width, int height)
{
	HDC hdc = ::GetDC(hWnd);
	this->CreateCompatible(hdc, width, height);
	::ReleaseDC(hWnd, hdc);
	return hdcMem;
}

HDC DDBitmap::CreateCompatibleFromBits(HWND hWnd, int width, int height, DWORD* bits)
{
	HDC hdc = ::GetDC(hWnd);
	this->CreateCompatibleFromBits(hdc, width, height, bits);
	::ReleaseDC(hWnd, hdc);
	return hdcMem;
}

// It creates a bitmap compatible with the hdc.  bits is an array of COLORREF
HDC DDBitmap::CreateCompatibleFromBits(HDC hdc, int width, int height, DWORD* bits)
{
	Destructor();
	//
	this->hBitmap = ::CreateCompatibleBitmap(hdc, width, height);
	//
	BITMAPINFO bmi;
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth  = width;
    bmi.bmiHeader.biHeight = height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = 0;
    bmi.bmiHeader.biXPelsPerMeter = 0;
    bmi.bmiHeader.biYPelsPerMeter = 0;
    bmi.bmiHeader.biClrUsed = 0;
    bmi.bmiHeader.biClrImportant = 0;
	::SetDIBits(hdc, hBitmap, 0, height, bits, &bmi, DIB_RGB_COLORS);
	//
	hdcMem = ::CreateCompatibleDC(hdc);
	::SelectObject(hdcMem, hBitmap);
	this->bitmap.bmWidth = width;
	this->bitmap.bmHeight = height;
	return hdcMem;
}

HBITMAP DDBitmap::CreateFromWindow(HWND hWnd, bool clientEdge)
{
	Destructor();
	RECT rect;

	::GetWindowRect(hWnd, &rect);

	HDC hdcSource = GetDCEx(hWnd, NULL, DCX_CACHE | DCX_LOCKWINDOWUPDATE);
	HDC hdcm = CreateCompatibleDC(hdcSource);
	hBitmap = CreateCompatibleBitmap(hdcSource, rect.right-rect.left, rect.bottom-rect.top);
	GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	SelectObject(hdcm, hBitmap);
	LockWindowUpdate(hWnd);
	BitBlt(hdcm, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcSource, 0, 0, SRCCOPY);
	if (clientEdge)
	{
		RECT rcBorder = {0, 0, bitmap.bmWidth, bitmap.bmHeight};
		::DrawEdge(hdcm, &rcBorder, EDGE_SUNKEN, BF_RECT);
	}
	LockWindowUpdate(NULL);
	DeleteDC(hdcm);
	return hBitmap;
}

HBITMAP DDBitmap::CreateFromDesktop()
{
	HWND hWndDesktop = GetDesktopWindow();
	if (hWndDesktop==NULL) return NULL;

	Destructor();

	HDC hdcSource = GetDCEx(hWndDesktop, NULL, DCX_CACHE | DCX_LOCKWINDOWUPDATE);
	HDC hdcm = CreateCompatibleDC(hdcSource);
	hBitmap = CreateCompatibleBitmap(hdcSource, ::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN));
	GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	SelectObject(hdcm, hBitmap);
	BitBlt(hdcm, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcSource, 0, 0, SRCCOPY);
	LockWindowUpdate(NULL);
	DeleteDC(hdcm);
	return hBitmap;
}

HBITMAP DDBitmap::CreateFromFile(HINSTANCE hInst, const wchar_t * szFileName)
{
	Destructor();
	hBitmap = (HBITMAP)::LoadImage(hInst, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	::GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	return hBitmap;
}

HBITMAP DDBitmap::CreateFromResource(HINSTANCE hInst, int bitmap_id)
{
	Destructor();
	hBitmap = ::LoadBitmap(hInst, MAKEINTRESOURCE(bitmap_id));
	::GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	return hBitmap;
}

//Add the following line to stdafx.h -> #define OEMRESOURCE before the line #include <windows.h>
//OBM_UPARROW, OBM_DNARROW, OBM_RGARROW, OBM_LFARROW
//OBM_REDUCE, OBM_ZOOM, OBM_RESTORE, OBM_MNARROW, OBM_BTSIZE, OBM_SIZE
//OBM_BTNCORNERS, OBM_CLOSE,
//Flat:  OBM_UPARROWD, OBM_DNARROWD, OBM_RGARROWD, OBM_LFARROWD
//OBM_REDUCED, OBM_ZOOMD, OBM_RESTORED, 
//OBM_COMBO, OBM_CHECK, OBM_CHECKBOXES,
// Disabled:  OBM_UPARROWI, OBM_DNARROWI, OBM_RGARROWI, OBM_LFARROWI
HBITMAP DDBitmap::CreateWinPredefined(UINT idOBM)
{
	Destructor();
	hBitmap = LoadBitmap(NULL, MAKEINTRESOURCE(idOBM));
	GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	return hBitmap;
}

void DDBitmap::DeleteMemDC()
{
	if (hdcMem)
	{
		DeleteDC(hdcMem);
		hdcMem = NULL;
	}
}

void DDBitmap::Destructor()
{
	DeleteMemDC();
	if (hBitmap)
	{
		DeleteObject(hBitmap);
		hBitmap = NULL;
		ZeroMemory(&bitmap, sizeof(BITMAP));
	}
}

HBITMAP DDBitmap::Strech(int scaleX, int scaleY)
{
	BITMAP bm2;
	HBITMAP hBitmap2;
	HDC hdcMem1, hdcMem2;
	int nWidth = 0;

	if (hdcMem == NULL)
	{
		HDC hdc;
		hdc = CreateIC(L"DISPLAY", NULL, NULL, NULL);
		hdcMem1 = CreateCompatibleDC(hdc);
		hdcMem2 = CreateCompatibleDC(hdc);
		DeleteDC(hdc);
	}
	else
	{
		hdcMem1 = hdcMem;
		hdcMem2 = CreateCompatibleDC(hdcMem);
	}
	
	bm2 = bitmap;
	bm2.bmWidth = scaleX*bitmap.bmWidth;
	bm2.bmHeight = scaleY*bitmap.bmHeight;
	nWidth = (bm2.bmWidth*bm2.bmBitsPixel)/8;
	if (nWidth%2==1) nWidth++;
	bm2.bmWidthBytes = nWidth;// FIX

	hBitmap2 = CreateBitmapIndirect(&bm2);
	SelectObject(hdcMem1, hBitmap);
	SelectObject(hdcMem2, hBitmap2);
	StretchBlt(hdcMem2, 0, 0, bm2.bmWidth, bm2.bmHeight,
		hdcMem1, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	if (hdcMem == NULL)
	{
		DeleteDC(hdcMem1);
	}
	DeleteDC(hdcMem2);
	DeleteObject(hBitmap);
	hBitmap = hBitmap2;
	bitmap = bm2;

	return hBitmap;
}

//_____________________________________________________________________ ScrollControl
int ScrollControl::_isRegistered = false;

ScrollControl::ScrollControl(void)
{
	if (!_isRegistered)
	{
		this->RegisterClassEx(LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(NULL_BRUSH));
		_isRegistered = true;
	}
	//_accumWheelDelta = 0;
	

#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
	//************************************************* Get Mouse Wheel Info
	ULONG ulScrollLines;
	SystemParametersInfo (SPI_GETWHEELSCROLLLINES, 0, &ulScrollLines, 0);         
// ulScrollLines usually equals 3 or 0 (for no scrolling)
// WHEEL_DELTA equals 120, so iDeltaPerLine will be 40

	if (ulScrollLines)
		_deltaWheelPerLine = WHEEL_DELTA / ulScrollLines;
	else
		_deltaWheelPerLine = 0;
#endif
	_showHorizontalGrid = true;
	_showVerticalGrid = true;
	_hfont = NULL;
	_selectedRow = -1; // No selection
	_selectedCol = -1; // No selection
	_hasFocus = false;
	_hWndParent = NULL;
	_hasHeader = false;
	_selectFullRow = false;
	_hdrBackColor = RGB(240, 240, 255);
	_backColor = RGB(255, 255, 255);
	_textColor = RGB(0, 0, 0);
	_lineColor = RGB(225, 225, 255);
	_columnWidth = 80;
	_rowHeight = 20;
	_emfWidth = 0;
	_emfHeight = 0;
}

ScrollControl::~ScrollControl(void)
{
}

void ScrollControl::SetShowVerticalGrid(bool showGrid)
{
	if (_showVerticalGrid == showGrid) return;
	_showVerticalGrid = showGrid;
	::InvalidateRect(hWnd, NULL, TRUE);
}

bool ScrollControl::GetShowVerticalGrid()
{
	return _showVerticalGrid;
}

void ScrollControl::SetShowHorizontalGrid(bool showGrid)
{
	if (_showHorizontalGrid == showGrid) return;
	_showHorizontalGrid = showGrid;
	::InvalidateRect(hWnd, NULL, TRUE);
}

bool ScrollControl::GetShowHorizontalGrid()
{
	return _showHorizontalGrid;
}

void ScrollControl::SetSelectFullRow(bool selectFullRow)
{
	_selectFullRow = selectFullRow;
}

bool ScrollControl::GetSelectFullRow()
{
	return _selectFullRow;
}

int ScrollControl::GetRowHeight()
{
	return _rowHeight;
}

void ScrollControl::SetRowHeight(int rowHeight)
{
	if (_rowHeight == rowHeight) return;
	_rowHeight = rowHeight;
	UpdateScrollInfo();
}

int ScrollControl::GetColumnWidth()
{
	return _columnWidth;
}

void ScrollControl::SetColumnWidth(int columnWidth)
{
	if (_columnWidth == columnWidth) return;
	_columnWidth = columnWidth;
	UpdateScrollInfo();
}

void ScrollControl::CopyToClipboard()
{
	// Create a dummy bitmap to compute the emf width and height
	// We cannot use width and height as the emf is not completely full
	Win::DDBitmap bitmapTmp; 
	RECT rcPaint = {0, 0, width, height};
	Win::Gdi gdiBitmap(bitmapTmp, rcPaint, false);
	if (_hfont) gdiBitmap.SelectFont__(_hfont);
	OnPaintControl(gdiBitmap, true);

	Win::Metafile emf;
	HDC hdcEmf = NULL;
	HDC hdcRef = ::GetDC(hWnd);
	RECT rect;
	PAINTSTRUCT ps;
	rcPaint.right = _emfWidth;
	rcPaint.bottom = _emfHeight;

	// Determine the picture frame dimensions. 
	const int displayWidthMilimeter = GetDeviceCaps(hdcRef, HORZSIZE); 
	const int displayHeightMilimeter = GetDeviceCaps(hdcRef, VERTSIZE); 
	const int displayWidthPixel = GetDeviceCaps(hdcRef, HORZRES);
	const int displayHeightPixel = GetDeviceCaps(hdcRef, VERTRES);
	 
	// Convert client coordinates to .01-mm units.  
	rect.left = 0;
	rect.top = 0;
	rect.right = (_emfWidth * displayWidthMilimeter * 100)/displayWidthPixel; 
	rect.bottom = (_emfHeight * displayHeightMilimeter * 100)/displayHeightPixel;

	hdcEmf = emf.Create();
	ps.hdc = hdcEmf;
	ps.rcPaint = rcPaint;
	
	Win::Gdi gdi(ps, false);
	OnPaintControl(gdi, true);
	emf.Close();
	Win::Clipboard::CopyMetaFileToClipboard(hWnd, emf);
	::ReleaseDC(hWnd, hdcRef);
}

bool ScrollControl::SaveEmfImage(const wchar_t* filename)
{
	// Create a dummy bitmap to compute the emf width and height
	// We cannot use width and height as the emf is not completely full
	Win::DDBitmap bitmapTmp; 
	RECT rcPaint = {0, 0, width, height};
	Win::Gdi gdiBitmap(bitmapTmp, rcPaint, false);
	if (_hfont) gdiBitmap.SelectFont__(_hfont);
	OnPaintControl(gdiBitmap, true);
	//
	Win::Metafile emf;
	HDC hdcEmf = NULL;
	HDC hdcRef = ::GetDC(hWnd);
	RECT rect;
	PAINTSTRUCT ps;
	rcPaint.right = _emfWidth;
	rcPaint.bottom = _emfHeight;

	// Determine the picture frame dimensions. 
	const int displayWidthMilimeter = GetDeviceCaps(hdcRef, HORZSIZE); 
	const int displayHeightMilimeter = GetDeviceCaps(hdcRef, VERTSIZE); 
	const int displayWidthPixel = GetDeviceCaps(hdcRef, HORZRES);
	const int displayHeightPixel = GetDeviceCaps(hdcRef, VERTRES);
	 
	// Convert client coordinates to .01-mm units. 
	rect.left = 0;
	rect.top = 0;
	rect.right = (_emfWidth * displayWidthMilimeter * 100)/displayWidthPixel; 
	rect.bottom = (_emfHeight * displayHeightMilimeter * 100)/displayHeightPixel;

	hdcEmf = emf.CreateToFile(hdcRef, &rect, filename, L"xy chart\0graph\0");
	ps.hdc = hdcEmf;
	ps.rcPaint = rcPaint;
	
	Win::Gdi gdi(ps, false);
	OnPaintControl(gdi, true);
	emf.Close();
	gdi.Delete();
	::ReleaseDC(hWnd, hdcRef);
	return true;
}

COLORREF ScrollControl::GetBackColor()
{
	return _backColor;
}

void ScrollControl::SetBackColor(COLORREF color)
{
	_backColor = color;
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

COLORREF ScrollControl::GetHdrBackColor()
{
	return _hdrBackColor;
}

void ScrollControl::SetHdrBackColor(COLORREF color)
{
	_hdrBackColor = color;
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

void ScrollControl::HeaderSetup(bool hasHeader)
{
	if (_hasHeader == hasHeader) return;
	_hasHeader = hasHeader;
	UpdateScrollInfo();
	::InvalidateRect(hWnd, NULL, FALSE);
}

COLORREF ScrollControl::GetTextColor()
{
	return _textColor;
}

void ScrollControl::SetTextColor(COLORREF color)
{
	_textColor = color;
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

COLORREF ScrollControl::GetLineColor()
{
	return _lineColor;
}

void ScrollControl::SetLineColor(COLORREF color)
{
	_lineColor = color;
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

void ScrollControl::SetFont(Win::Gdi::Font& font)
{
	_hfont = font.GetHFONT();
	if (hWnd == NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

bool ScrollControl::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_COMMAND) return false;
	const int id = LOWORD(e.wParam);
	const int notificationd = HIWORD(e.wParam);
	if (id != this->id) return false;
	if (notificationd!=notification) return false;
	return true;
}

bool ScrollControl::SetSelectedCol(int col)
{
	if (col < 0) return false;
	Win::ITable::Info info;
	info.columnCount =0;

	this->OnTableRequestInfo(info);

	if (info.columnCount < 0) info.columnCount = 0;
	if (col>info.columnCount-1) return false;
	_selectedCol = col;
	_selectedRow = -1;
	::InvalidateRect(hWnd, NULL, FALSE);
	return true;
}

void ScrollControl::RemoveSelection()
{
	_selectedCol = -1;
	_selectedRow = -1;
	::InvalidateRect(hWnd, NULL, FALSE);
}

int ScrollControl::GetSelectedCol()
{
	return _selectedCol;
}

bool ScrollControl::SetSelectedRow(int row)
{
	if (row < 0) return false;
	Win::ITable::Info info;
	info.rowCount = 0;

	this->OnTableRequestInfo(info);
	if (info.rowCount < 0) info.rowCount = 0;
	if (row>info.rowCount-1) return false;
	_selectedRow = row;
	_selectedCol = -1;
	::InvalidateRect(hWnd, NULL, FALSE);
	return true;
}
	
int ScrollControl::GetSelectedRow(void)
{
	return _selectedRow;
}

void ScrollControl::GetSelectionRect(RECT& rect)
{
	if (_selectedRow < 0 && _selectedCol < 0) // Empty selection
	{
		rect.left  = 0;
		rect.top = 0;
		rect.right = 0;
		rect.bottom = 0;
		return;
	}
	int nIniColIndex, nEndColIndex, nIniRowIndex, nEndRowIndex;
	this->GetPageInfoH(nIniColIndex, nEndColIndex);
	this->GetPageInfoV(nIniRowIndex, nEndRowIndex);
	Win::ITable::Info info;
	info.rowCount = 0;
	info.columnCount = 0;

	this->OnTableRequestInfo(info);

	if (info.rowCount < 0) info.rowCount = 0;
	if (info.columnCount < 0) info.columnCount = 0;
	//

	if (_selectedRow < 0 && _selectedCol >= 0) // One column is selected
	{
		rect.top = 0;
		rect.bottom = height;
		rect.left = (_selectedCol - nIniColIndex) * _columnWidth;
		rect.right = rect.left + _columnWidth;
	}
	else if (_selectedRow >= 0 && _selectedCol < 0) // One row is selected
	{
		rect.top = (_selectedRow - nIniRowIndex)*_rowHeight;
		rect.bottom = rect.top + _rowHeight;
		rect.left = 0;
		rect.right = width;
	}
	else //__________________________________ // One cell is selected;
	{
		rect.top = (_selectedRow - nIniRowIndex)*_rowHeight;
		rect.bottom = rect.top + _rowHeight;
		rect.left = (_selectedCol - nIniColIndex) * _columnWidth;
		rect.right = rect.left + _columnWidth;
	}
}

void ScrollControl::Window_SetFocus(Win::Event& e)
{
	_hasFocus=true;
	RECT rect;
	this->GetSelectionRect(rect);
	::InvalidateRect(hWnd, &rect, FALSE);
}

void ScrollControl::Window_KillFocus(Win::Event& e)
{
	_hasFocus=false;
	RECT rect;
	this->GetSelectionRect(rect);
	::InvalidateRect(hWnd, &rect, FALSE);
}

void ScrollControl::RefreshCell(int row, int col)
{
	int nIniColIndex, nEndColIndex, nIniRowIndex, nEndRowIndex;
	this->GetPageInfoH(nIniColIndex, nEndColIndex);
	this->GetPageInfoV(nIniRowIndex, nEndRowIndex);
	if (row<nIniRowIndex || row>nEndRowIndex) return;
	if (col<nIniColIndex || col>nEndColIndex) return;
	Win::ITable::Info info;
	info.columnCount =0;
	info.rowCount = 0;
	RECT rc;

	this->OnTableRequestInfo(info);

	if (info.rowCount < 0) info.rowCount = 0;
	if (info.columnCount < 0) info.columnCount = 0;
	if (row>info.rowCount-1) return;
	if (col>info.columnCount-1) return;
	//
	rc.top = (row-nIniRowIndex)*_rowHeight;
	rc.bottom = rc.top + _rowHeight;
	rc.left = (col-nIniColIndex)*_columnWidth;
	rc.right = rc.left + _columnWidth;
	::InvalidateRect(hWnd, &rc, TRUE);
}


void ScrollControl::Window_Open(Win::Event& e)
{
	_hWndParent = ::GetParent(hWnd);
	this->SetFocus();
	_bitmap.CreateCompatible(hWnd, width, height);
}

void ScrollControl::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, false);
	Win::Gdi gdiBitmap(_bitmap, gdi.GetRcPaint(), false);
	if (_hfont) gdiBitmap.SelectFont__(_hfont);
	OnPaintControl(gdiBitmap, false);
	gdi.DrawDoubleBuffer(_bitmap);
	//OnPaintControl(gdi, false);
}

void ScrollControl::OnPaintControl(Win::Gdi& gdi, bool isMetafile)
{
	const int deltaColor = Win::Gdi::Color3D::IsCloseToBlack(_backColor) ? 7 : -7;
	const COLORREF colorSelectedFocus = Win::Gdi::Color3D::AddLight(_backColor, 2*deltaColor);
	const COLORREF colorSelectedNoFocus =  Win::Gdi::Color3D::AddLight(_backColor, deltaColor);
	//
	const int deltaHdrColor = Win::Gdi::Color3D::IsCloseToBlack(_hdrBackColor) ? 7 : -7;
	const COLORREF colorHdrSelectedFocus = Win::Gdi::Color3D::AddLight(_hdrBackColor, 2*deltaHdrColor);
	const COLORREF colorHdrSelectedNoFocus =  Win::Gdi::Color3D::AddLight(_hdrBackColor, deltaHdrColor);
	//
	Win::Gdi::Brush brushSelectedFocus(colorSelectedFocus);
	Win::Gdi::Brush brushSelectedNoFocus(colorSelectedNoFocus);
	Win::Gdi::Brush brushBackground;
	if (Enabled)
	{
		brushBackground.CreateSolid(_backColor);
	}
	else
	{
		brushBackground.CreateSolid(WIN_BACK_DISABLED);
	}
	//
	Win::Gdi::Brush brushHdrSelectedFocus(colorHdrSelectedFocus);
	Win::Gdi::Brush brushHdrSelectedNoFocus(colorHdrSelectedNoFocus);
	Win::Gdi::Brush brushHdrBackground(_hdrBackColor);

	const RECT rcPaint = gdi.GetRcPaint();
	Win::Gdi::Pen pluma(PS_SOLID, 1, _lineColor);
	if (_hfont) gdi.SelectFont__(_hfont);
	gdi.SetTextColor(_textColor);

	//____________________________________________________ Get Paint Info
	int posX, posY;
	RECT rc;
	int row1, row2, col1, col2;
	this->GetPaintInfo(gdi.GetPaintStruct(), posX, posY, row1, row2, col1, col2);

	Win::ITable::Info info;
	info.columnCount =0;
	info.rowCount = 0;

	this->OnTableRequestInfo(info);

	if (info.columnCount < 0 || info.rowCount < 0)
	{
		gdi.FillRect(rcPaint, brushBackground);
		return;
	}

	//___________________________________________ Computer rowNum and colNum
	const int countX = width / _columnWidth + 1;
	const int countY = height / _rowHeight +1;
	int rowNum = 0;
	int colNum = 0;
	if (_hasHeader == true)
	{
		if (posX+countX > info.columnCount-2)
		{
			colNum = info.columnCount - posX-1;
		}
		else
		{
			colNum = countX;
		}
		if (posY+countY > info.rowCount-2)
		{
			rowNum = info.rowCount - posY-1;
		}
		else
		{
			rowNum = countY;
		}
	}
	else
	{
		if (posX+countX > info.columnCount-1)
		{
			colNum = info.columnCount - posX;
		}
		else
		{
			colNum = countX;
		}
		if (posY+countY > info.rowCount-1)
		{
			rowNum = info.rowCount - posY;
		}
		else
		{
			rowNum = countY;
		}
	}

	//____________________________________________________ Paint background
	gdi.SelectBrush_(brushBackground);
	
	RECT rcIntersect;
	rc.left = 0;
	rc.top = 0;
	if (_hasHeader == true)
	{
		rc.right = _columnWidth * (colNum+1);
		rc.bottom = _rowHeight * (rowNum +1);
	}
	else
	{
		rc.right = _columnWidth * colNum;
		rc.bottom = _rowHeight * rowNum;
	}	

	if (isMetafile)
	{
		if (rc.right > width) rc.right = width;
		if (rc.bottom> height) rc.bottom = height;
		gdi.FillRect(rc, brushBackground);
		//
		_emfWidth = rc.right; // Store emf width
		_emfHeight = rc.bottom; // Store emf height
	}
	else
	{
		gdi.FillRect(rcPaint, brushBackground);
	}
	//_______________________________________________________ Headers
	if (_hasHeader == true)
	{
		//_____________ Top Header
		rc.right = _columnWidth * (colNum+1);
		rc.bottom = _rowHeight;
		::IntersectRect(&rcIntersect, &rc, &rcPaint);
		gdi.FillRect(rcIntersect, brushHdrBackground);
		//_____________ Left Header
		rc.right = _columnWidth;
		rc.bottom = _rowHeight * (rowNum +1);
		::IntersectRect(&rcIntersect, &rc, &rcPaint);
		gdi.FillRect(rcIntersect, brushHdrBackground);
	}
	
	
	//_________________________________________________ Paint Selection
	if (isMetafile == false)
	{
		GetSelectionRect(rc);
		if (::IsRectEmpty(&rc) == false)
		{
			::IntersectRect(&rcIntersect, &rc, &rcPaint);
			if (_hasFocus)
			{
				gdi.FillRect(rcIntersect, brushSelectedFocus);
			}
			else
			{
				gdi.FillRect(rcIntersect, brushSelectedNoFocus);
			}
		}
	}
	//_________________________________________________ Notify that it has begun cell painting
	rc.left = 0;
	rc.top = 0;
	rc.right = _columnWidth;
	rc.bottom = _rowHeight;
	this->OnTablePaint(WNT_PAINTCELLSBEGIN, gdi, rc, -1, -1, false);

	int i, j, x, y;
	bool isSelected = false;

	//________________________________ Paint Top Header
	if (_hasHeader == true)
	{
		rc.top = 0;
		rc.bottom = _rowHeight;
		for (j = col1; j<=(col2+1); j++) 
		{
			x = _columnWidth * (j - posX);
			rc.left = x;
			rc.right = x + _columnWidth;
			if (gdi.DoRcPaintOverlap(rc) == true)
			{
				isSelected = (_selectedRow < 0 && _selectedCol== j);
				if (isSelected) gdi.FillRect(rc, _hasFocus ? brushHdrSelectedFocus : brushHdrSelectedNoFocus);
				this->OnTablePaint(WNT_PAINTCELL, gdi, rc, 0, j, isSelected);
			}
		}
	}
	//________________________________ Paint Left Header
	if (_hasHeader == true)
	{
		rc.left = 0;
		rc.right = _columnWidth;
		for (i = row1; i<=(row2+1); i++)
		{
			if (i== posY) continue; // Skip this cell as it has already been painted
			y = _rowHeight * (i - posY);
			rc.top = y;
			rc.bottom = y + _rowHeight;
			if (gdi.DoRcPaintOverlap(rc) == true)
			{
				isSelected = (_selectedRow==i && _selectedCol < 0);
				if (isSelected) gdi.FillRect(rc, _hasFocus ? brushHdrSelectedFocus : brushHdrSelectedNoFocus);
				this->OnTablePaint(WNT_PAINTCELL, gdi, rc, i, 0, (_selectedRow==i && _selectedCol < 0));
			}
		}
	}
	//_____________________________ Paint the cells
	RECT rcFocus;
	if (_hasHeader == true)
	{
		 for (i = row1 ; i <= row2; i++)
		{
			y = _rowHeight * (i - posY)  +_rowHeight;
			rc.top = y;
			rc.bottom = y + _rowHeight;
			//
			rcFocus.top = rc.top+1;
			rcFocus.bottom = rc.bottom;
			if (y > height) break;

			for (j = col1; j<=col2; j++)
			{
				x = _columnWidth * (j - posX) + _columnWidth;
				rc.left = x;
				rc.right = x + _columnWidth;
				rcFocus.left = rc.left+1;
				rcFocus.right = rc.right;
				if (x > width) break;
				//____________________________________________ Paint the background
				if (_hasHeader)
				{
					if (i==_selectedRow-1 && j==_selectedCol-1) 
					{
						if (isMetafile == false)
						{
							if (_hasFocus)
							{
								gdi.FillRect(rc, brushSelectedFocus);
								gdi.SetBkColor(colorSelectedFocus);
							}
							else
							{
								gdi.FillRect(rc, brushSelectedNoFocus);
								gdi.SetBkColor(colorSelectedNoFocus);
							}
						}
					}
				}
				else
				{
					if (i ==_selectedRow && j ==_selectedCol) 
					{
						if (isMetafile == false)
						{
							if (_hasFocus)
							{
								gdi.FillRect(rc, brushSelectedFocus);
								gdi.SetBkColor(colorSelectedFocus);
							}
							else
							{
								gdi.FillRect(rc, brushSelectedNoFocus);
								gdi.SetBkColor(colorSelectedNoFocus);
							}
						}
					}
				}
				this->OnTablePaint(WNT_PAINTCELL, gdi, rc, i+1, j+1, (i ==_selectedRow && j ==_selectedCol));

				//____________________________________________ Paint theFocus
				if (_hasHeader)
				{
					if (i == _selectedRow-1 && j ==_selectedCol-1) 
					{
						if (isMetafile == false)
						{
							if (_hasFocus) gdi.DrawFocusRect(&rcFocus);
						}
					}
				}
				else
				{
					if (i == _selectedRow && j == _selectedCol) 
					{
						if (isMetafile == false)
						{
							if (_hasFocus) gdi.DrawFocusRect(&rcFocus);
						}
					}
				}
			}
		}
	}
	else //___________________________________________ without header
	{
		 for (i = row1; i <= row2; i++)
		{
			y = _rowHeight * (i - posY) ;
			rc.top = y;
			rc.bottom = y + _rowHeight;
			rcFocus.top = rc.top +1;
			rcFocus.bottom = rc.bottom;
			//
			for (j = col1; j<=col2; j++)
			{
				x = _columnWidth * (j - posX);
				rc.left = x;
				rc.right = x + _columnWidth;
				rcFocus.left = rc.left+1;
				rcFocus.right = rc.right;
				//____________________________________________ Paint the background
				if (i == _selectedRow && j ==_selectedCol) 
				{
					if (_hasFocus)
					{
						gdi.FillRect(rc, brushSelectedFocus);
						gdi.SetBkColor(colorSelectedFocus);
					}
					else
					{
						gdi.FillRect(rc, brushSelectedNoFocus);
						gdi.SetBkColor(colorSelectedNoFocus);
					}
				}
				this->OnTablePaint(WNT_PAINTCELL, gdi, rc, i, j, (i == _selectedRow && j ==_selectedCol));
	
				//______________________________________ Paint the Focus
				if (i==_selectedRow && j==_selectedCol) 
				{
					if (_hasFocus) gdi.DrawFocusRect(&rcFocus);
				}
			}
		}
	}

	 //_______________________________________________ Notify that it has finished painting
	rc.left = 0;
	rc.top = 0;
	rc.right = _columnWidth;
	rc.bottom = _rowHeight;
	this->OnTablePaint(WNT_PAINTCELLSEND, gdi, rc, -1, -1, false);

	if (_showHorizontalGrid == true || _showVerticalGrid == true )
	{
		rc.left = 0;
		rc.top = 0;
		gdi.SetBkMode(true);
		gdi.SelectPen_(pluma);
		if (_hasHeader == true)
		{
			rc.right = _columnWidth * (colNum+1);
			rc.bottom = _rowHeight * (rowNum +1);
		}
		else
		{
			rc.right = _columnWidth * colNum;
			rc.bottom = _rowHeight * rowNum;
		}	

		//______________________________________ Vertical Lines
		if (_showVerticalGrid == true )
		{	
			for (j = 1; ; j++)
			{
				x = _columnWidth * j;
				if (x > rc.right) break;
				if (isMetafile)
				{
					if (x > width) break;
					gdi.Line(x, rcPaint.top, x, MINIMUM(rc.bottom, height));
				}
				else
				{
					gdi.Line(x, rcPaint.top, x, MINIMUM(rc.bottom, rcPaint.bottom));
				}
			}
		}
		//_____________________________________ Horizontal Lines
		if (_showHorizontalGrid == true )
		{
			for (i = 1; ; i++)
			{
				y = _rowHeight * i;
				if (y > rc.bottom) break;
				if (isMetafile)
				{
					if (y > height) break;
					gdi.Line(rcPaint.left, y, MINIMUM(rc.right, width), y);
				}
				else
				{
					gdi.Line(rcPaint.left, y, MINIMUM(rc.right, rcPaint.right), y);
				}
			}
		}
	}
}

bool ScrollControl::ProcessMouse(HWND hWnd, Win::ITable::TableInfo& ti, LPARAM lParam)
{
	this->SetFocus();
	if (_hasHeader)//________________________________________________ With Header
	{
		Win::ITable::TableInfo ati;
		GetAbsoluteClickInfo(lParam, ati.row, ati.col, ati.cell);
		GetClickInfo(lParam, ti.row, ti.col, ti.cell);
		//_______________________________________ See if the click was on the header
		if (ati.row == 0 && ati.col == 0) // Remove selection
		{
			_selectedRow = -1;
			_selectedCol = -1;
			return true;
		}
		//
		Win::ITable::Info info;
		info.columnCount =0;
		info.rowCount = 0;

		this->OnTableRequestInfo(info);

		if (ti.row>=info.rowCount) return false;
		if (ti.col>=info.columnCount) return false;
		//
		ti.lParam = lParam;
		ti.hWnd = hWnd;
		if (ti.row<0) return false;
		if (ti.col<0) return false;
		if (ati.row == 0 && ati.col > 0) // Column selection
		{
			_selectedRow = -abs(ti.row+1);
			_selectedCol = ti.col;
		}
		else if (ati.row > 0 && ati.col == 0) // Row selection
		{
			_selectedRow = ti.row;
			_selectedCol = -abs(ti.col+1);
		}
		else if (ati.row > 0 && ati.col > 0) // Cell selection
		{
			_selectedRow = ti.row;
			_selectedCol = ti.col;
		}
	}
	else //______________________________________________________ Without Header
	{
		GetClickInfo(lParam, ti.row, ti.col, ti.cell);
		//
		Win::ITable::Info info;
		info.columnCount =0;
		info.rowCount = 0;

		this->OnTableRequestInfo(info);

		if (ti.row>=info.rowCount) return false;
		if (ti.col>=info.columnCount) return false;
		//
		ti.lParam = lParam;
		ti.hWnd = hWnd;
		if (ti.row<0) return false;
		if (ti.col<0) return false;

		if (_selectFullRow == true)
		{
			_selectedCol = -abs(ti.col+1);
			_selectedRow = ti.row;
		}
		else
		{
			_selectedCol = ti.col;
			_selectedRow = ti.row;
		}
	}
	return true;
}

void ScrollControl::OnTablePaint(int paintEvent, Win::Gdi& gdi, RECT& cell, int row, int col, bool isSelected)
{
	Win::ITable::PaintEvent tpe;
	tpe.gdi = &gdi;
	tpe.cell = cell;
	tpe.row = row;
	tpe.col = col;
	tpe.isSelected = isSelected;
	::SendMessage(_hWndParent, WM_COMMAND, MAKEWPARAM(this->id, paintEvent), (LPARAM)&tpe);
}

void ScrollControl::OnTableRequestInfo(Win::ITable::Info& info)
{
	::SendMessage(_hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_REQUESTINFO), (LPARAM)&info);
}

void ScrollControl::SetSelectedCell(int row, int col)
{
	Win::ITable::Info info;
	info.columnCount = 0;
	info.rowCount = 0;

	this->OnTableRequestInfo(info);
	//if (_itable)
	//{
	//	_itable->OnTableRequestInfo(info);
	//}
	//else
	//{	
	//	::SendMessage(_hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_REQUESTINFO), (LPARAM)&info);
	//}
	if (info.rowCount < 0) info.rowCount = 0;
	if (info.columnCount < 0) info.columnCount = 0;
	const int rows = info.rowCount;
	const int cols = info.columnCount;
	if (row>=rows) row = rows-1;
	if (row<0) row = 0;
	//
	if (col>=cols) col = cols-1;
	if (col<0) col = 0;
	//
	if (row == _selectedRow && col == _selectedCol) return;
	_selectedRow = row;
	_selectedCol = col;
	//
	::InvalidateRect(hWnd, NULL, FALSE);
}

void ScrollControl::Window_LButtonDown(Win::Event& e)
{
	::SetFocus(hWnd);
	if (Enabled==false) return;
	Win::ITable::TableInfo ti;
	//____________________________ Get Previous Selection
	RECT rcPreviousSelection;
	this->GetSelectionRect(rcPreviousSelection);
	//
	if (ProcessMouse(hWnd, ti, e.lParam)==false) return;
	//____________________________ Get New Selection
	RECT rcNewSelection;
	this->GetSelectionRect(rcNewSelection);
	//_____________________________ Change Selection
	RECT rc;
	::UnionRect(&rc, &rcPreviousSelection, &rcNewSelection);
	if (::IsRectEmpty(&rc) == false) ::InvalidateRect(hWnd, &rc, FALSE);
	//_____________________________ Notify parent
	::SendMessage(_hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_CLICK), e.lParam);
	::SetFocus(hWnd);
}

void ScrollControl::Window_RButtonDown(Win::Event& e)
{
	::SetFocus(hWnd);
	if (Enabled==false) return;
	Win::ITable::TableInfo ti;
	if (ProcessMouse(hWnd, ti, e.lParam)==false) return;
	::SendMessage(_hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_RCLICK), e.lParam);
}

void ScrollControl::Window_LButtonDblclk(Win::Event& e)
{
	if (Enabled==false) return;
	Win::ITable::TableInfo ti;
	if (ProcessMouse(hWnd, ti, e.lParam)==false) return;
	::SendMessage(_hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_DBLCLICK), e.lParam);
}

void ScrollControl::RefreshAll()
{
	::SendMessage(this->hWnd, WM_SIZE, (WPARAM)0, MAKELPARAM(this->width, this->height));
	::InvalidateRect(this->hWnd, NULL, FALSE);
}


// The control needs to have the focus
void ScrollControl::Window_KeyDown(Win::Event& e)
{
	switch (e.wParam)
	{
	case VK_HOME :
		::SendMessage (hWnd, WM_VSCROLL, SB_TOP, 0);
		break; 
	case VK_END :
		::SendMessage (hWnd, WM_VSCROLL, SB_BOTTOM, 0);
		break;	    
	case VK_PRIOR :
		::SendMessage (hWnd, WM_VSCROLL, SB_PAGEUP, 0);
		break;	    
	case VK_NEXT :
		::SendMessage (hWnd, WM_VSCROLL, SB_PAGEDOWN, 0);
		break;	    
	case VK_UP :
		::SendMessage (hWnd, WM_VSCROLL, SB_LINEUP, 0);
		break;    
	case VK_DOWN :
		::SendMessage (hWnd, WM_VSCROLL, SB_LINEDOWN, 0);
		break;    
	case VK_LEFT :
		::SendMessage (hWnd, WM_HSCROLL, SB_PAGEUP, 0);
		break;    
	case VK_RIGHT :
		::SendMessage (hWnd, WM_HSCROLL, SB_PAGEDOWN, 0);
		break;
	}
}

void ScrollControl::Window_GetDlgCode(Win::Event& e)
{
	e.returnValue = DLGC_WANTARROWS;
}

void ScrollControl::Window_HScroll(Win::Event& e)
{
	SCROLLINFO si;
	int nHorzPos = 0;
	si.cbSize = sizeof (SCROLLINFO);
	si.fMask  = SIF_ALL;

	// Save the position for comparison later on
	::GetScrollInfo(hWnd, SB_HORZ, &si);
	nHorzPos = si.nPos;

	switch (LOWORD (e.wParam))
	{
	case SB_LINELEFT:
		si.nPos -= 1;
		break;    
	case SB_LINERIGHT:
		si.nPos += 1;
		break;
	case SB_PAGELEFT:
		si.nPos -= si.nPage;
		break;	    
	case SB_PAGERIGHT:
		si.nPos += si.nPage;
		break;    
	//case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos;
		break;
	default:
		break;
	}
	// Set the position and then retrieve it.  Due to adjustments
	//   by Windows it may not be the same as the value set.
	si.fMask = SIF_POS;
	::SetScrollInfo (hWnd, SB_HORZ, &si, TRUE);
	::GetScrollInfo (hWnd, SB_HORZ, &si);
	
	if (si.nPos != nHorzPos)
	{
		::SendMessage(_hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_HSCROLL), e.lParam);
		RECT rcClip;
		rcClip.top = 0;
		rcClip.right = width;
		rcClip.bottom = height;
		if (_hasHeader == true)
		{
			rcClip.left = _columnWidth;
			::ScrollWindow (hWnd, _columnWidth * (nHorzPos - si.nPos), 0, NULL, &rcClip);
		}
		else
		{
			rcClip.left = 1;
			::ScrollWindowEx(hWnd, _columnWidth * (nHorzPos - si.nPos), 0, NULL, &rcClip, NULL, NULL, SW_INVALIDATE | SW_ERASE);
			//::ScrollWindowEx(hWnd, _columnWidth * (nHorzPos - si.nPos), 0, NULL, NULL, NULL, NULL, SW_INVALIDATE | SW_ERASE);
		}
		::UpdateWindow(hWnd);
	}
}

void ScrollControl::Window_VScroll(Win::Event& e)
{
	SCROLLINFO si;
	int nVertPos = 0;
	si.cbSize = sizeof (SCROLLINFO);
	si.fMask  = SIF_ALL;
	::GetScrollInfo(hWnd, SB_VERT, &si);

	// Save the position for comparison later on
	nVertPos = si.nPos;

	switch (LOWORD (e.wParam))
	{
	case SB_TOP:
		si.nPos = si.nMin;
		break;	    
	case SB_BOTTOM:
		si.nPos = si.nMax;
		break;    
	case SB_LINEUP:
		si.nPos -= 1;
		break;	    
	case SB_LINEDOWN:
		si.nPos += 1;
		break;	    
	case SB_PAGEUP:
		si.nPos -= si.nPage;
		break;	    
	case SB_PAGEDOWN:
		si.nPos += si.nPage;
		break;	    
	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos;
		break;    
	default:
		break;         
	}
	// Set the position and then retrieve it.  Due to adjustments
	//   by Windows it may not be the same as the value set.
	si.fMask = SIF_POS;
	::SetScrollInfo (hWnd, SB_VERT, &si, TRUE);
	::GetScrollInfo (hWnd, SB_VERT, &si);

	// If the position has changed, scroll the window and update it
	if (si.nPos != nVertPos)
	{  
		RECT rcClip;
		rcClip.left = 0;
		rcClip.top = _rowHeight;
		rcClip.right = width;
		rcClip.bottom = height;

		::SendMessage(_hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_VSCROLL), e.lParam);
		if (_hasHeader == true)
		{
			rcClip.top = _rowHeight;
			::ScrollWindow(hWnd, 0, _rowHeight * (nVertPos - si.nPos), NULL, &rcClip);	
		}
		else
		{
			rcClip.top = 1;
			::ScrollWindow(hWnd, 0, _rowHeight * (nVertPos - si.nPos), NULL, &rcClip);
			//::ScrollWindow(hWnd, 0, _rowHeight * (nVertPos - si.nPos), NULL, NULL);
		}
		::UpdateWindow(hWnd);
	}
}

// The control needs to have the focus
void ScrollControl::Window_MouseWheel(Win::Event& e)
{
	static int accumWheelDelta = 0;
	if (_deltaWheelPerLine == 0) return;

	accumWheelDelta += (short) HIWORD (e.wParam);     // 120 or -120

	while (accumWheelDelta >= _deltaWheelPerLine)
	{               
		::SendMessage (hWnd, WM_VSCROLL, SB_LINEUP, 0);
		accumWheelDelta -= _deltaWheelPerLine;
	}

	while (accumWheelDelta <= -_deltaWheelPerLine)
	{
		::SendMessage (hWnd, WM_VSCROLL, SB_LINEDOWN, 0);
		accumWheelDelta += _deltaWheelPerLine;
	}
}

void ScrollControl::UpdateScrollInfo()//Call this after inserting or removing columns or rows
{
	::SendMessage(hWnd, WM_SIZE, SIZE_MAXIMIZED, MAKELPARAM(width, height));
}

void ScrollControl::Window_Size(Win::Event& e)
{
	_bitmap.CreateCompatible(hWnd, width, height);
	//
	Win::ITable::Info info;
	info.columnCount =0;
	info.rowCount = 0;

	this->OnTableRequestInfo(info);
	//if (_itable)
	//{
	//	_itable->OnTableRequestInfo(info);
	//}
	//else
	//{	
	//	::SendMessage(::GetParent(hWnd), WM_COMMAND, MAKEWPARAM(this->id, WIN_REQUESTINFO), (LPARAM)&info);
	//}

	if (info.rowCount < 0) info.rowCount = 0;
	if (info.columnCount < 0) info.columnCount = 0;

	SCROLLINFO si;
	// ________________ Set vertical scroll bar range and page size
	si.cbSize = sizeof (SCROLLINFO);
	si.fMask  = SIF_RANGE | SIF_PAGE;
	si.nMin   = 0;
	if (_hasHeader == true)
	{
		si.nMax   = info.rowCount - 2;
		si.nPage  = (height - _rowHeight) / _rowHeight;
	}
	else
	{
		si.nMax   = info.rowCount - 1;
		si.nPage  = this->height / _rowHeight;
	}
	::SetScrollInfo (hWnd, SB_VERT, &si, TRUE);

	// _________________Set horizontal scroll bar range and page size
	si.cbSize = sizeof (SCROLLINFO);
	si.fMask  = SIF_RANGE | SIF_PAGE;
	si.nMin   = 0;
	if (_hasHeader == true)
	{
		si.nMax   = info.columnCount - 2;
		si.nPage  = (width -  _columnWidth) / _columnWidth;
	}
	else
	{
		si.nMax   = info.columnCount - 1;
		si.nPage  = this->width / _columnWidth;
	}
	::SetScrollInfo (hWnd, SB_HORZ, &si, TRUE);
}

// Call this function inside on paint to get Scroll Information
void ScrollControl::GetPaintInfo(const PAINTSTRUCT& ps, int& posX, int& posY, int&row1, int& row2, int& col1, int& col2)
{
	//___________________ set return values to zero
	posX = 0;
	posY = 0;
	row1 = 0;
	row2 = 0;
	col1 = 0;
	col2 = 0;
	//
	Win::ITable::Info info;
	info.columnCount =0;
	info.rowCount = 0;

	this->OnTableRequestInfo(info);
	if (info.rowCount < 0) return;
	if (info.columnCount < 0) return;
	SCROLLINFO si;
	si.cbSize = sizeof (SCROLLINFO);
	si.fMask  = SIF_POS;
	::GetScrollInfo (hWnd, SB_VERT, &si);
	posY = si.nPos;
	::GetScrollInfo (hWnd, SB_HORZ, &si);
	posX = si.nPos;
	int result = 0;

	if (_hasHeader == true)
	{
		if (ps.rcPaint.top > _rowHeight)
		{
			result = posY + (ps.rcPaint.top - _rowHeight) / _rowHeight;
			row1 = result > 0 ? result : 0;
		}
		else
		{
			row1 = posY;
		}
		//
		result = posY + (ps.rcPaint.bottom - _rowHeight) / _rowHeight;
		row2 = result  < (info.rowCount - 2) ? result : (info.rowCount - 2);
		//
		if (ps.rcPaint.left > _columnWidth)
		{
			result = posX + (ps.rcPaint.left - _columnWidth) / _columnWidth;
			col1 = result > 0 ? result : 0;
		}
		else
		{
			col1 = posX;
		}
		//
		result = posX + (ps.rcPaint.right - _columnWidth) / _columnWidth;
		col2 = result < (info.columnCount - 2) ? result : (info.columnCount - 2);
	}
	else
	{
		result = posY + ps.rcPaint.top / _rowHeight;
		row1 = result > 0 ? result : 0;
		//
		result = posY + ps.rcPaint.bottom / _rowHeight;
		row2 = result  < (info.rowCount - 1) ? result : (info.rowCount - 1);
		//
		result = posX + ps.rcPaint.left / _columnWidth;
		col1 = result > 0 ? result : 0;
		//
		result = posX + ps.rcPaint.right / _columnWidth;
		col2 = result < (info.columnCount - 1) ? result : (info.columnCount - 1); 
	}
}

// lParam is an input parameter on a mouse event, row, col and cell are output parameters
void ScrollControl::GetClickInfo(LPARAM lParam, int&row, int& col, RECT& cell)
{
	// Set return values to zero
	row = 0;
	col = 0;
	::memset(&cell, 0, sizeof(RECT));
	
	Win::ITable::Info info;
	info.columnCount =0;
	info.rowCount = 0;

	this->OnTableRequestInfo(info);
	//if (_itable)
	//{
	//	_itable->OnTableRequestInfo(info);
	//}
	//else
	//{	
	//	::SendMessage(::GetParent(hWnd), WM_COMMAND, MAKEWPARAM(this->id, WIN_REQUESTINFO), (LPARAM)&info);
	//}
	if (info.rowCount < 0) return;
	if (info.columnCount < 0) return;
	//
	int row1, row2, col1, col2;
	this->GetPageInfoH(col1, col2);
	this->GetPageInfoV(row1, row2);
	const int x=(int)(short)LOWORD(lParam);
	const int y=(int)(short)HIWORD(lParam);
	//
	const int n_x = x / _columnWidth;
	const int n_y = y / _rowHeight;
	//
	cell.left = n_x*_columnWidth;
	cell.right = cell.left + _columnWidth;
	cell.top = n_y*_rowHeight;
	cell.bottom = cell.top + _rowHeight;
	//
	row = n_y + row1;
	col = n_x + col1;
}

// lParam is an input parameter on a mouse event, row, col and cell are output parameters
void ScrollControl::GetAbsoluteClickInfo(LPARAM lParam, int&row, int& col, RECT& cell)
{
	// Set return values to zero
	row = 0;
	col = 0;
	::memset(&cell, 0, sizeof(RECT));
	
	Win::ITable::Info info;
	info.columnCount =0;
	info.rowCount = 0;

	this->OnTableRequestInfo(info);
	//if (_itable)
	//{
	//	_itable->OnTableRequestInfo(info);
	//}
	//else
	//{	
	//	::SendMessage(::GetParent(hWnd), WM_COMMAND, MAKEWPARAM(this->id, WIN_REQUESTINFO), (LPARAM)&info);
	//}
	if (info.rowCount < 0) return;
	if (info.columnCount < 0) return;
	//
	const int x=(int)(short)LOWORD(lParam);
	const int y=(int)(short)HIWORD(lParam);
	//
	col = x / _columnWidth;
	row = y / _rowHeight;
	//
	cell.left = col*_columnWidth;
	cell.right = cell.left + _columnWidth;
	cell.top = row*_rowHeight;
	cell.bottom = cell.top + _rowHeight;
}

// Return the first col and the last column of the current view
void ScrollControl::GetPageInfoH(int& nIniColIndex, int& nEndColIndex)
{
	//________________________ Set return values to zero
	nIniColIndex = 0;
	nEndColIndex = 0;
	//
	Win::ITable::Info info;
	info.columnCount =0;
	info.rowCount = 0;

	this->OnTableRequestInfo(info);
	//if (_itable)
	//{
	//	_itable->OnTableRequestInfo(info);
	//}
	//else
	//{	
	//	::SendMessage(_hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_REQUESTINFO), (LPARAM)&info);
	//}
	if (info.rowCount <= 0) return;
	if (info.columnCount <= 0) return;
	//_______________________
	SCROLLINFO si;
	si.cbSize = sizeof (SCROLLINFO);
	si.fMask  = SIF_POS;
	::GetScrollInfo (hWnd, SB_HORZ, &si);
	const int posX = si.nPos;
	nIniColIndex = posX > 0 ? posX : 0;
	int result = 0;
	if (_hasHeader == true)
	{
		const int colsPerPage = (int)ceil((double)(width - _columnWidth)/(double)_columnWidth);
		result = posX + colsPerPage;
		nEndColIndex = result < (info.columnCount-2) ? result : info.columnCount-2;
	}
	else
	{
		const int colsPerPage = (int)ceil((double)width/(double)_columnWidth);
		result = posX + colsPerPage;
		nEndColIndex = result < (info.columnCount-1) ? result : info.columnCount-1;
	}
}

// Return the first row and the last row of the current view
void ScrollControl::GetPageInfoV(int& nIniRowIndex, int& nEndRowIndex)
{
	//____________________ Set return values to zero
	nIniRowIndex = 0;
	nEndRowIndex = 0;
	//
	Win::ITable::Info info;
	info.columnCount =0;
	info.rowCount = 0;

	this->OnTableRequestInfo(info);
	if (info.rowCount <= 0) return;
	if (info.columnCount <= 0) return;
	//______________________________
	SCROLLINFO si;
	si.cbSize = sizeof (SCROLLINFO);
	si.fMask  = SIF_POS;
	::GetScrollInfo (this->hWnd, SB_VERT, &si);
	const int posY = si.nPos;
	//
	nIniRowIndex = posY > 0 ? posY : 0;
	int result = 0;
	if (_hasHeader == true)
	{
		const int rowsPerPage = (int)ceil((double)(height - _rowHeight)/(double)_rowHeight);
		result = posY + rowsPerPage;
		nEndRowIndex = result < (info.rowCount-2) ? result : info.rowCount-2;
	}
	else
	{
		const int rowsPerPage = (int)ceil((double)height/(double)_rowHeight);
		result = posY + rowsPerPage;
		nEndRowIndex = result < (info.rowCount-1) ? result : info.rowCount-1;
	}
}

//_____________________________________________________________________ ScrollText
ScrollText::ScrollText(void)
{

}

ScrollText::~ScrollText(void)
{
}

void ScrollText::OnTablePaint(int paintEvent, Win::Gdi& gdi, RECT& cell, int row, int col, bool isSelected)
{
	switch(paintEvent)
	{
	case WNT_PAINTCELLSBEGIN:
		break;
	case WNT_PAINTCELL:
		break;
	case WNT_PAINTCELLSEND:
		break;
	}
}

void ScrollText::OnTableRequestInfo(Win::ITable::Info& info)
{
	info.columnCount = this->GetColCount();
	info.rowCount = this->GetRowCount();
}

int ScrollText::GetColCount(void)
{
	HDC hdc = ::GetDC(hWnd);
	TEXTMETRIC tm;
	int cxCaps, nVirtualWidth;
	::GetTextMetrics (hdc, &tm);
	cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * tm.tmAveCharWidth / 2;
	nVirtualWidth = 40 * tm.tmAveCharWidth + 22 * cxCaps ; // 40 small letters and 22 capital letters
	::ReleaseDC (hWnd, hdc);
	return 3 + nVirtualWidth /tm.tmAveCharWidth;
}

int ScrollText::GetRowCount(void)
{
	return 75;
}

int ScrollText::GetCellWidth(void)
{
	HDC hdc = ::GetDC(hWnd);
	TEXTMETRIC tm;
	GetTextMetrics (hdc, &tm);
	::ReleaseDC (hWnd, hdc);
	return 50*tm.tmAveCharWidth;
}

int ScrollText::GetCellHeight(void)
{
	HDC hdc = ::GetDC(hWnd);
	TEXTMETRIC tm;
	::GetTextMetrics (hdc, &tm);
	::ReleaseDC (hWnd, hdc);
	return tm.tmHeight + tm.tmExternalLeading;
}

void ScrollText::Window_Open(Win::Event& e)
{
	this->SetFocus();
	this->SetRowHeight(GetCellHeight());
	this->SetColumnWidth(GetCellWidth());
}

void ScrollText::Window_Paint(Win::Event& e)
{
	Win::Sysmetrics sysmetrics[] =
	{
		SM_CXSCREEN,             L"SM_CXSCREEN",              
								L"Screen width in pixels",
		SM_CYSCREEN,             L"SM_CYSCREEN",              
								L"Screen height in pixels",
		SM_CXVSCROLL,            L"SM_CXVSCROLL",             
								L"Vertical scroll width",
		SM_CYHSCROLL,            L"SM_CYHSCROLL",             
								L"Horizontal scroll height",
		SM_CYCAPTION,            L"SM_CYCAPTION",             
								L"Caption bar height",
		SM_CXBORDER,             L"SM_CXBORDER",              
								L"Window border width",
		SM_CYBORDER,             L"SM_CYBORDER",              
								L"Window border height",
		SM_CXFIXEDFRAME,         L"SM_CXFIXEDFRAME",          
								L"Dialog window frame width",
		SM_CYFIXEDFRAME,         L"SM_CYFIXEDFRAME",          
								L"Dialog window frame height",
		SM_CYVTHUMB,             L"SM_CYVTHUMB",              
								L"Vertical scroll thumb height",
		SM_CXHTHUMB,             L"SM_CXHTHUMB",              
								L"Horizontal scroll thumb width",
		SM_CXICON,               L"SM_CXICON",                
								L"Icon width",
		SM_CYICON,               L"SM_CYICON",                
								L"Icon height",
		SM_CXCURSOR,             L"SM_CXCURSOR",              
								L"Cursor width",
		SM_CYCURSOR,             L"SM_CYCURSOR",              
								L"Cursor height",
		SM_CYMENU,               L"SM_CYMENU",                
								L"Menu bar height",
		SM_CXFULLSCREEN,         L"SM_CXFULLSCREEN",          
								L"Full screen client area width",
		SM_CYFULLSCREEN,         L"SM_CYFULLSCREEN",          
								L"Full screen client area height",
		SM_CYKANJIWINDOW,        L"SM_CYKANJIWINDOW",         
								L"Kanji window height",
		SM_MOUSEPRESENT,         L"SM_MOUSEPRESENT",          
								L"Mouse present flag",
		SM_CYVSCROLL,            L"SM_CYVSCROLL",             
								L"Vertical scroll arrow height",
		SM_CXHSCROLL,            L"SM_CXHSCROLL",             
								L"Horizontal scroll arrow width",
		SM_DEBUG,                L"SM_DEBUG",                 
								L"Debug version flag",
		SM_SWAPBUTTON,           L"SM_SWAPBUTTON",            
								L"Mouse buttons swapped flag",
		SM_CXMIN,                L"SM_CXMIN",                 
								L"Minimum window width",
		SM_CYMIN,                L"SM_CYMIN",                 
								L"Minimum window height",
		SM_CXSIZE,               L"SM_CXSIZE",                
								L"Min/Max/Close button width",
		SM_CYSIZE,               L"SM_CYSIZE",                
								L"Min/Max/Close button height",
		SM_CXSIZEFRAME,          L"SM_CXSIZEFRAME",           
								L"Window sizing frame width",
		SM_CYSIZEFRAME,          L"SM_CYSIZEFRAME",           
								L"Window sizing frame height",
		SM_CXMINTRACK,           L"SM_CXMINTRACK",            
								L"Minimum window tracking width",
		SM_CYMINTRACK,           L"SM_CYMINTRACK",            
								L"Minimum window tracking height",
		SM_CXDOUBLECLK,          L"SM_CXDOUBLECLK",           
								L"Double click x tolerance",
		SM_CYDOUBLECLK,          L"SM_CYDOUBLECLK",           
								L"Double click y tolerance",
		SM_CXICONSPACING,        L"SM_CXICONSPACING",         
								L"Horizontal icon spacing",
		SM_CYICONSPACING,        L"SM_CYICONSPACING",         
								L"Vertical icon spacing",
		SM_MENUDROPALIGNMENT,    L"SM_MENUDROPALIGNMENT",     
								L"Left or right menu drop",
		SM_PENWINDOWS,           L"SM_PENWINDOWS",            
								L"Pen extensions installed",
		SM_DBCSENABLED,          L"SM_DBCSENABLED",           
								L"Double-Byte Char Set enabled",
		SM_CMOUSEBUTTONS,        L"SM_CMOUSEBUTTONS",         
								L"Number of mouse buttons",
		SM_SECURE,               L"SM_SECURE",                
								L"Security present flag",
		SM_CXEDGE,               L"SM_CXEDGE",                
								L"3-D border width",
		SM_CYEDGE,               L"SM_CYEDGE",                
								L"3-D border height",
		SM_CXMINSPACING,         L"SM_CXMINSPACING",          
								L"Minimized window spacing width",
		SM_CYMINSPACING,         L"SM_CYMINSPACING",          
								L"Minimized window spacing height",
		SM_CXSMICON,             L"SM_CXSMICON",              
								L"Small icon width",
		SM_CYSMICON,             L"SM_CYSMICON",              
								L"Small icon height",
		SM_CYSMCAPTION,          L"SM_CYSMCAPTION",           
								L"Small caption height",
		SM_CXSMSIZE,             L"SM_CXSMSIZE",              
								L"Small caption button width",
		SM_CYSMSIZE,             L"SM_CYSMSIZE",              
								L"Small caption button height",
		SM_CXMENUSIZE,           L"SM_CXMENUSIZE",            
								L"Menu bar button width",
		SM_CYMENUSIZE,           L"SM_CYMENUSIZE",            
								L"Menu bar button height",
		SM_ARRANGE,              L"SM_ARRANGE",               
								L"How minimized windows arranged",
		SM_CXMINIMIZED,          L"SM_CXMINIMIZED",           
								L"Minimized window width",
		SM_CYMINIMIZED,          L"SM_CYMINIMIZED",           
								L"Minimized window height",
		SM_CXMAXTRACK,           L"SM_CXMAXTRACK",            
								L"Maximum draggable width",
		SM_CYMAXTRACK,           L"SM_CYMAXTRACK",            
								L"Maximum draggable height",
		SM_CXMAXIMIZED,          L"SM_CXMAXIMIZED",           
								L"Width of maximized window",
		SM_CYMAXIMIZED,          L"SM_CYMAXIMIZED",           
								L"Height of maximized window",
		SM_NETWORK,              L"SM_NETWORK",               
								L"Network present flag",
		SM_CLEANBOOT,            L"SM_CLEANBOOT",             
								L"How system was booted",
		SM_CXDRAG,               L"SM_CXDRAG",                
								L"Avoid drag x tolerance",
		SM_CYDRAG,               L"SM_CYDRAG",                
								L"Avoid drag y tolerance",
		SM_SHOWSOUNDS,           L"SM_SHOWSOUNDS",            
								L"Present sounds visually",
		SM_CXMENUCHECK,          L"SM_CXMENUCHECK",           
								L"Menu check-mark width",
		SM_CYMENUCHECK,          L"SM_CYMENUCHECK",           
								L"Menu check-mark height",
		SM_SLOWMACHINE,          L"SM_SLOWMACHINE",           
								L"Slow processor flag",
		SM_MIDEASTENABLED,       L"SM_MIDEASTENABLED",        
								L"Hebrew and Arabic enabled flag",
		SM_MOUSEWHEELPRESENT,    L"SM_MOUSEWHEELPRESENT",     
								L"Mouse wheel present flag",
		SM_XVIRTUALSCREEN,       L"SM_XVIRTUALSCREEN",        
								L"Virtual screen x origin",
		SM_YVIRTUALSCREEN,       L"SM_YVIRTUALSCREEN",        
								L"Virtual screen y origin",
		SM_CXVIRTUALSCREEN,      L"SM_CXVIRTUALSCREEN",       
								L"Virtual screen width",
		SM_CYVIRTUALSCREEN,      L"SM_CYVIRTUALSCREEN",       
								L"Virtual screen height",
		SM_CMONITORS,            L"SM_CMONITORS",             
								L"Number of monitors",
		SM_SAMEDISPLAYFORMAT,    L"SM_SAMEDISPLAYFORMAT",     
								L"Same color format flag"
	} ;
	Win::Gdi gdi(hWnd, true, false);
	int posX, posY;
	int x, y;
	int row1, row2, col1, col2;

	this->GetPaintInfo(gdi.GetPaintStruct(), posX, posY,row1, row2, col1, col2);

	wchar_t sz[255];
	//if (_itable==NULL) return;
	const int cellWidth = this->GetCellWidth();
	const int cellHeight = this->GetCellHeight();

     for (int i = row1 ; i <= row2; i++)
	{
		x = cellWidth * (1 - posX) ;
		y = cellHeight * (i - posY) ;

		gdi.TextOut(x, y, sysmetrics[i].szLabel) ;
		gdi.TextOut(x + 250, y, sysmetrics[i].szDesc);

		gdi.SetTextAlign(TA_RIGHT | TA_TOP) ;

		int metrics = ::GetSystemMetrics(sysmetrics[i].iIndex);
		_snwprintf_s (sz, 255, _TRUNCATE, L"%5d", metrics);
		gdi.TextOut(x + 650, y, sz);

		gdi.SetTextAlign(TA_LEFT | TA_TOP) ;
	}
}


//_____________________________________________________________________ Clipboard
Clipboard::Clipboard(void)
{
}

Clipboard::~Clipboard(void)
{
}

// returns true if the clipboard has a bitmap
bool Clipboard::HasDDBitmap(HWND hWnd)
{
	bool b = false;
	if (OpenClipboard(hWnd))
	{
		b =(GetClipboardData(CF_BITMAP)!=NULL);
		CloseClipboard();
	}
	return b;
}

// returns true if the clipboard has a metafile
bool Clipboard::HasMetafile(HWND hWnd)
{
	bool b = false;
	if (OpenClipboard(hWnd))
	{
		b =(GetClipboardData(CF_ENHMETAFILE)!=NULL);
		CloseClipboard();
	}
	return b;
}

// returns true if the clipboard has a bitmap
bool Clipboard::HasDIBitmap(HWND hWnd)
{
	bool b = false;
	if (OpenClipboard(hWnd))
	{
		b =(GetClipboardData(CF_DIB)!=NULL);
		CloseClipboard();
	}
	return b;
}

// returns true if the clipboard has text
bool Clipboard::HasText(HWND hWnd)
{
	bool b = false;
	if (OpenClipboard(hWnd))
	{
		b =(GetClipboardData(CF_TEXT)!=NULL);
		CloseClipboard();
	}
	return b;
}

bool Clipboard::CopyDDBFromClipboard(HWND hWnd, Win::DDBitmap& ddbitmap)
{
	bool bOk = false;

	if (OpenClipboard(hWnd))
	{
		HBITMAP hBitmapClipboard = (HBITMAP)GetClipboardData(CF_BITMAP);

		if (hBitmapClipboard)
		{
			ddbitmap.Create(hBitmapClipboard);
			bOk = true;
		}
		CloseClipboard();
	}

	return bOk;
}

bool Clipboard::CopyDDBToClipboard(HWND hWnd, Win::DDBitmap& ddbitmap)
{
	return CopyDDBToClipboard(hWnd, ddbitmap.GetHBITMAP());
}

bool Clipboard::CopyDDBToClipboard(HWND hWnd, HBITMAP hBitmap)
{
	HDC hdc, hdcMem;
	BITMAP bitmap;
	HBITMAP hbitmap;
	bool bOk = false;

	if (hBitmap != NULL)
	{
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		hbitmap = CreateBitmapIndirect(&bitmap);
		//
		hdc = CreateCompatibleDC(NULL);
		hdcMem = CreateCompatibleDC(NULL);
		//
		SelectObject(hdcMem, hbitmap); // Destination
		SelectObject(hdc, hBitmap); // Source
		//
		BitBlt(hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight,
					hdc, 0, 0, SRCCOPY);
		DeleteDC(hdcMem);
		DeleteDC(hdc);
		//
		if (OpenClipboard(hWnd))
		{
			if (EmptyClipboard())
			{
				bOk = true;
				SetClipboardData(CF_BITMAP, hbitmap);
				CloseClipboard();
			}
		}

	}
	return bOk;
}

BOOL Clipboard::CopyDIBFromClipboard(HWND hWnd, Win::DIBitmapP& dib)
{
	BOOL bOk = FALSE;
	if (OpenClipboard(hWnd))
	{
		HGLOBAL h = GetClipboardData(CF_DIB);
		PBYTE p = NULL;
		if (h)
		{
			p = (PBYTE)GlobalLock(h);
			dib.CopyFromPackedDib((BITMAPINFO*)p);
			GlobalUnlock(h);
			bOk = CloseClipboard();
		}
	}
	return bOk;
}

bool Clipboard::CopyDIBToClipboard(HWND hWnd, Win::DIBitmapP& dib)
{
	bool bOk = false;
	HGLOBAL h = (HGLOBAL)dib.CopyToPackedDib(TRUE);
	if (h)
	{
		if (OpenClipboard(hWnd))
		{
			if (EmptyClipboard())
			{
				bOk = true;
				SetClipboardData(CF_DIB, h);
				CloseClipboard();
			}
		}
	}
	return bOk;
}

//bool Clipboard::CopyTextFromClipboard(HWND hWnd, Data::Buffer& sb)
//{
//	bool bOk = false;
//	HGLOBAL hGlobal;
//	wchar_t* pGlobal;
//
//	if (OpenClipboard(hWnd))
//	{
//#ifdef UNICODE
//		hGlobal =GetClipboardData(CF_UNICODETEXT);
//#else
//		hGlobal =GetClipboardData(CF_TEXT);
//#endif
//		
//		if (hGlobal)
//		{
//			pGlobal = (wchar_t*)GlobalLock(hGlobal);
//			sb.SetSize(GlobalSize(hGlobal)/sizeof(wchar_t));
//			lstrcpy(const_cast<wchar_t*>(sb.Get()), pGlobal);
//			GlobalUnlock(hGlobal);
//			bOk = true;
//		}
//		CloseClipboard();
//	}
//	return bOk;
//}
//
//bool Clipboard::CopyTextFromClipboard(HWND hWnd, Data::String& ds)
//{
//	bool bOk = false;
//	HGLOBAL hGlobal;
//	wchar_t* pGlobal;
//
//	if (OpenClipboard(hWnd))
//	{
//#ifdef UNICODE
//		hGlobal =GetClipboardData(CF_UNICODETEXT);
//#else
//		hGlobal =GetClipboardData(CF_TEXT);
//#endif
//		
//		if (hGlobal)
//		{
//			pGlobal = (wchar_t*)GlobalLock(hGlobal);
//			ds.SetSize((int)(GlobalSize(hGlobal)/sizeof(wchar_t)));
//			lstrcpy(const_cast<wchar_t*>(ds.Get()), pGlobal);
//			GlobalUnlock(hGlobal);
//			bOk = true;
//		}
//		CloseClipboard();
//	}
//	return bOk;
//}

// text must be released manually
//	wchar_t * text = NULL;
//
//	if (Win::Clipboard::HasText(hWnd))
//	{
//		if (Win::Clipboard::CopyTextFromClipboard(hWnd, &text))
//		{
//			this->MessageBox(text);
//			delete [] text;
//		}
//	}
wchar_t* Clipboard::CopyTextFromClipboard(HWND hWnd, wchar_t** text)
{
	if (OpenClipboard(hWnd) == false) return L"Unable to open the clipboard";

	HGLOBAL hGlobal =GetClipboardData(CF_UNICODETEXT);

	if (hGlobal == NULL)
	{
		CloseClipboard();
		return L"Unable to get clipboard data";
	}

	wchar_t* pGlobal = (wchar_t*)GlobalLock(hGlobal);
	if (pGlobal == NULL)
	{
		CloseClipboard();
		return L"Unable to lock global data";
	}
	*text = new wchar_t[GlobalSize(hGlobal)/sizeof(wchar_t) +1];
	lstrcpy(*text, pGlobal);
	GlobalUnlock(hGlobal);
	CloseClipboard();
	
	return NULL;
}

void Clipboard::CopyTextFromClipboard(HWND hWnd, wstring& out_text)
{
	if (OpenClipboard(hWnd) == false) return;

	HGLOBAL hGlobal =GetClipboardData(CF_UNICODETEXT);

	if (hGlobal == NULL)
	{
		CloseClipboard();
		return;
	}

	wchar_t* pGlobal = (wchar_t*)GlobalLock(hGlobal);
	if (pGlobal == NULL)
	{
		CloseClipboard();
		return;
	}
	const int len = GlobalSize(hGlobal)/sizeof(wchar_t);//*text = new wchar_t[GlobalSize(hGlobal)/sizeof(wchar_t) +1];
	out_text.resize(len);
	lstrcpy((wchar_t*)out_text.c_str(), pGlobal);
	GlobalUnlock(hGlobal);
	CloseClipboard();
	out_text.resize(len-1);
}

void Clipboard::CopyTextFromClipboard(HWND hWnd, string& out_text)
{
	if (OpenClipboard(hWnd) == false) return;

	HGLOBAL hGlobal =GetClipboardData(CF_TEXT);

	if (hGlobal == NULL)
	{
		CloseClipboard();
		return;
	}

	char* pGlobal = (char*)GlobalLock(hGlobal);
	if (pGlobal == NULL)
	{
		CloseClipboard();
		return;
	}
	const int len = GlobalSize(hGlobal)/sizeof(char);//*text = new wchar_t[GlobalSize(hGlobal)/sizeof(wchar_t) +1];
	out_text.resize(len);
	strcpy_s((char*)out_text.c_str(), len, pGlobal);
	GlobalUnlock(hGlobal);
	CloseClipboard();
	out_text.resize(len-1);
}

wchar_t* Clipboard::CopyTextToClipboard(HWND hWnd, const wchar_t* text)
{
	if (text == NULL)
	{
		EmptyClipboard();
		return NULL;
	}
	const int len = wcslen(text)+1;
	if (len == 1)
	{
		EmptyClipboard();
		return NULL;
	}
	HGLOBAL hGlobal = GlobalAlloc(GHND | GMEM_SHARE, len*sizeof(wchar_t));
	if (hGlobal == NULL) return L"Unable to allocate global memory";

	wchar_t*pGlobal = (wchar_t*)GlobalLock(hGlobal);
	if (hGlobal == NULL) 
	{
		GlobalFree(hGlobal);
		return L"Unable to allocate global memory";
	}
	lstrcpy(pGlobal, text);
	GlobalUnlock(hGlobal);
	if (OpenClipboard(hWnd) == FALSE)
	{
		GlobalFree(hGlobal);
		return L"Unable to open the clipboard";
	}

	if (EmptyClipboard() == FALSE)
	{
		GlobalFree(hGlobal);
		CloseClipboard();
		return L"Unable to empty the clipboard";
	}

	if (SetClipboardData(CF_UNICODETEXT, hGlobal) == NULL)
	{
		GlobalFree(hGlobal);
		CloseClipboard();
		return L"Unable to set the clipboard data";
	}
	CloseClipboard();
	return NULL;
}

wchar_t* Clipboard::CopyTextToClipboard(HWND hWnd, const wstring& text)
{
	return CopyTextToClipboard(hWnd, text.c_str());
}

wchar_t* Clipboard::CopyTextToClipboard(HWND hWnd, const char* text)
{
	if (text == NULL)
	{
		EmptyClipboard();
		return NULL;
	}
	const int len = strlen(text)+1;
	if (len == 1)
	{
		EmptyClipboard();
		return NULL;
	}
	HGLOBAL hGlobal = GlobalAlloc(GHND | GMEM_SHARE, len);
	if (hGlobal == NULL) return L"Unable to allocate global memory";

	char* pGlobal = (char*)GlobalLock(hGlobal);
	if (hGlobal == NULL) 
	{
		GlobalFree(hGlobal);
		return L"Unable to allocate global memory";
	}
	strcpy_s(pGlobal, len, text);
	GlobalUnlock(hGlobal);
	if (OpenClipboard(hWnd) == FALSE)
	{
		GlobalFree(hGlobal);
		return L"Unable to open the clipboard";
	}

	if (EmptyClipboard() == FALSE)
	{
		GlobalFree(hGlobal);
		CloseClipboard();
		return L"Unable to empty the clipboard";
	}

	if (SetClipboardData(CF_TEXT, hGlobal) == NULL)
	{
		GlobalFree(hGlobal);
		CloseClipboard();
		return L"Unable to set the clipboard data";
	}
	CloseClipboard();
	return NULL;
}

wchar_t* Clipboard::CopyTextToClipboard(HWND hWnd, const string& text)
{
	return CopyTextToClipboard(hWnd, text.c_str());
}

//bool Clipboard::CopyHtmlToClipboard(HWND hWnd, const wchar_t* html)
//{
//}
//
//bool Clipboard::CopyHtmlToClipboard(HWND hWnd, const wstring& html)
//{
//	HGLOBAL hGlobal;
//	wchar_t* pGlobal;
//	bool bOk = false;
//
//	hGlobal = GlobalAlloc(GHND | GMEM_SHARE, (text.length()+1)*sizeof(wchar_t));
//	if (hGlobal)
//	{
//		pGlobal = (wchar_t*)GlobalLock(hGlobal);
//		lstrcpy(pGlobal, text.c_str());
//		GlobalUnlock(hGlobal);
//		if (OpenClipboard(hWnd))
//		{
//			if (EmptyClipboard())
//			{
//				bOk = (SetClipboardData(CF_HTML, hGlobal) != NULL);
//			}
//			CloseClipboard();
//		}
//	}
//	return bOk;
//}

bool Clipboard::CopyMetaFileToClipboard(HWND hWnd, Win::Metafile& mf)
{
	bool bOk = false;

	if (mf.GetHandle())
	{
		HENHMETAFILE h = CopyEnhMetaFile(mf.GetHandle(), NULL);
		if (OpenClipboard(hWnd))
		{
			if (EmptyClipboard())
			{
				bOk = (SetClipboardData(CF_ENHMETAFILE, h)!=NULL);
			}
			CloseClipboard();
		}
	}
	return bOk;
}
	
bool Clipboard::CopyMetaFileFromClipboard(HWND hWnd, Win::Metafile& mf)
{
	bool bOk = false;

	if (OpenClipboard(hWnd))
	{
		HENHMETAFILE h = (HENHMETAFILE)GetClipboardData(CF_ENHMETAFILE);
		if (h)
		{
			bOk = mf.Create(h);
		}
		CloseClipboard();
	}
	return bOk;
}

//_____________________________________________________________________Splitter
int Win::Splitter::m_nObjectCountVe = 0;
int Win::Splitter::m_nObjectCountHo = 0;

Splitter::Splitter(void)
{
	m_nSplitterWidth = 0;
	m_dSizeRatio = 0.5;
	m_hWndChild1 = NULL;
	m_hWndChild2 = NULL;
	m_bHorizontal = false;
	m_nParentWidth = 0;
	m_nParentHeight = 0;
	m_bBlocking = false;
	m_nChild1Size = 0;
	m_nChild2Size = 0;
	m_nPosition = 0;
	rebarHeight = 0;
}

Splitter::~Splitter(void)
{
}

const wchar_t * Splitter::GetClassName(void)
{
	return m_bHorizontal ? L"WINSPPLITERHO" : L"WINSPPLITERVE" ;
}

HWND Splitter::CreateHorizontal(HWND parent, HWND child1, HWND child2, double sizeRatio)
{
	cursor.CreateHorzSplit(this->hInstance);
	m_dSizeRatio = sizeRatio;
	m_hWndChild1 = child1;
	m_hWndChild2 = child2;
	m_bHorizontal = true;
	m_bBlocking = false;
	m_nPosition = 0;

	m_nSplitterWidth = 8*::GetSystemMetrics(SM_CYBORDER);
	if (m_nObjectCountHo==0)
	{
		m_nObjectCountHo++;
		this->RegisterClassEx(cursor.GetHCursor(), (HBRUSH)(COLOR_BTNFACE+1));
	}
	return Win::Window::Create(NULL, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, parent, -1);
}

HWND Splitter::CreateVertical(HWND parent, HWND child1, HWND child2, double sizeRatio)
{
	cursor.CreateVertSplit(this->hInstance);
	m_dSizeRatio = sizeRatio;
	m_hWndChild1 = child1;
	m_hWndChild2 = child2;
	m_bHorizontal = false;
	m_bBlocking = false;
	m_nPosition = 0;

	m_nSplitterWidth = 8*GetSystemMetrics(SM_CXBORDER);
	if (m_nObjectCountVe==0)
	{
		m_nObjectCountVe++;
		this->RegisterClassEx(cursor.GetHCursor(), (HBRUSH)(COLOR_BTNFACE+1));
	}
	return Win::Window::Create(NULL, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, parent, -1);
}

void Splitter::Adjust(int nSplitterPosition)
{
	int splitterX;
	int splitterY;
	int splitterWidth;
	int splitterHeight;

	if (nSplitterPosition<m_nSplitterWidth) nSplitterPosition = m_nSplitterWidth;
	if (m_bHorizontal)
	{
		if (nSplitterPosition>m_nParentHeight-m_nSplitterWidth*2)
		{
			nSplitterPosition = m_nParentHeight-m_nSplitterWidth*2;
		}
		splitterWidth = m_nParentWidth;
		splitterHeight = m_nSplitterWidth;
		splitterX = 0;
		splitterY = nSplitterPosition;
		this->Move(splitterX, rebarHeight+splitterY, splitterWidth, splitterHeight, TRUE);
		m_nChild1Size = splitterY;
		m_nChild2Size = m_nParentHeight-splitterY-splitterHeight;
		::MoveWindow(m_hWndChild1, 0, rebarHeight, m_nParentWidth, m_nChild1Size, TRUE);
		::MoveWindow(m_hWndChild2, 0, rebarHeight+splitterY+splitterHeight, m_nParentWidth, m_nChild2Size, TRUE);
	}
	else
	{
		if (nSplitterPosition>m_nParentWidth-m_nSplitterWidth*2)
		{
			nSplitterPosition = m_nParentWidth-m_nSplitterWidth*2;
		}
		splitterWidth = m_nSplitterWidth;
		splitterHeight = m_nParentHeight;
		splitterX = nSplitterPosition;
		splitterY = 0;
		this->Move(splitterX, splitterY, splitterWidth, splitterHeight, TRUE);
		m_nChild1Size = splitterX;
		m_nChild2Size = m_nParentWidth - splitterX-splitterWidth;
		::MoveWindow(m_hWndChild1, 0, 0, m_nChild1Size, m_nParentHeight, TRUE);
		::MoveWindow(m_hWndChild2, splitterX+splitterWidth, 0, m_nChild2Size, m_nParentHeight, TRUE);
	}
	::InvalidateRect(m_hWndChild1, NULL, TRUE);
	::InvalidateRect(m_hWndChild2, NULL, TRUE);
}

// Call this inside the parent Window_Size
void Splitter::OnParentSize(Win::Event& e, HWND rebar)//, HWND statusbar)
{
	m_nParentWidth = LOWORD(e.lParam);
	m_nParentHeight = HIWORD(e.lParam);
	rebarHeight = 0;
	if (m_bHorizontal)
	{
		if (rebar!=NULL) 
		{
			rebarHeight = (UINT)::SendMessage(rebar, (UINT)RB_GETBARHEIGHT, 0, 0);
			m_nParentHeight -=rebarHeight;
			::MoveWindow(rebar, 0, 0, m_nParentWidth, rebarHeight, TRUE);
		}
	}

	if (m_nPosition == 0) 
	{
		int available = m_bHorizontal ? m_nParentHeight : m_nParentWidth;
		 available-=m_nSplitterWidth;
		m_nPosition = (int)(this->m_dSizeRatio*available+0.5);
	}
	this->Adjust(m_nPosition);
}

void Splitter::Window_LButtonUp(Win::Event& e)
{
	if (m_bBlocking)
	{
		switch(m_position)
		{
		case Win::Splitter::child1:
			DrawBoxOutline(m_hWndChild1, m_nPosition);
			break;
		case Win::Splitter::splitter:
			DrawBoxOutline(this->hWnd, m_nPosition);
			break;
		case Win::Splitter::child2:
			DrawBoxOutline(m_hWndChild2, m_nPosition);
			break;
		}
		//
		// Move children
		ReleaseCapture();
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		m_nPosition = m_bHorizontal ? ((int)(short)HIWORD(e.lParam)) : ((int)(short)LOWORD(e.lParam));
		m_nPosition += m_nChild1Size;
		this->Adjust(m_nPosition);
		m_bBlocking = false;
	}
}

void Splitter::Window_LButtonDown(Win::Event& e)
{
	m_position = Win::Splitter::splitter;
	m_nPosition = m_bHorizontal ? ((int)(short)HIWORD(e.lParam)) : ((int)(short)LOWORD(e.lParam));
	DrawBoxOutline(hWnd, m_nPosition);
	::SetCapture(hWnd);
	::SetCursor(cursor.GetHCursor());
	m_bBlocking = true;
}

void Splitter::Window_MouseMove(Win::Event& e)
{
//	wchar_t sz[256];
	if (m_bBlocking)
	{
		::SetCursor(cursor.GetHCursor());
		switch(m_position)
		{
		case Win::Splitter::child1:
			DrawBoxOutline(m_hWndChild1, m_nPosition);
			break;
		case Win::Splitter::splitter:
			DrawBoxOutline(this->hWnd, m_nPosition);
			break;
		case Win::Splitter::child2:
			DrawBoxOutline(m_hWndChild2, m_nPosition);
			break;
		}
		
		m_nPosition = m_bHorizontal ? ((int)(short)HIWORD(e.lParam)) : ((int)(short)LOWORD(e.lParam));
		int nParentSize = m_bHorizontal ? m_nParentHeight : m_nParentWidth;

		if (m_nPosition>=0 && m_nPosition<m_nSplitterWidth) //******** Over the splitter
		 {
			 m_position = Win::Splitter::splitter;
			 DrawBoxOutline(this->hWnd, m_nPosition);
		 }
		 else if (m_nPosition>m_nSplitterWidth) //*********************** Over Child 2
		 {
			 m_nPosition -=m_nSplitterWidth;
			 if (m_nPosition>m_nChild2Size-3*m_nSplitterWidth)
			 {
				 m_nPosition = m_nChild2Size-3*m_nSplitterWidth;
			 }
			m_position = Win::Splitter::child2;
			DrawBoxOutline(m_hWndChild2, m_nPosition);
		 }
		 else if (m_nPosition<0) //************************************ Over Child 1
		 {
			 m_nPosition += (m_nChild1Size-m_nSplitterWidth);
			  if (m_nPosition<m_nSplitterWidth)
			 {
				 m_nPosition = m_nSplitterWidth;
			 }
			 m_position = Win::Splitter::child1;
			 DrawBoxOutline(m_hWndChild1, m_nPosition);
		 }
	}
}

void Splitter::DrawBoxOutline(HWND hWnd, int nPosition)
{
	HPEN hpenDef;
	HBRUSH hbrushDef;
	static WORD wData [] =
	{
		0xAA, //10101010First row
		0x55, //01010101Second row
	};
	HBITMAP hBitmap = CreateBitmap(8, 2, 1, 1, (LPVOID)wData);
	HBRUSH hbrush = ::CreatePatternBrush(hBitmap);
	HDC hdc = ::GetDC(hWnd);

	::SetROP2(hdc, R2_NOTXORPEN);//R2_NOT);//R2_NOTXORPEN
	hbrushDef = (HBRUSH)::SelectObject(hdc, hbrush);
	hpenDef = (HPEN)::SelectObject(hdc, (HPEN)GetStockObject(NULL_PEN));
	const int nLineWidth= 5;

	if (m_bHorizontal)
	{
		::Rectangle(hdc, 0, nPosition, m_nParentWidth, nPosition+nLineWidth);
	}
	else
	{
		::Rectangle(hdc, nPosition, 0, nPosition+nLineWidth, m_nParentHeight);
	}
	::ReleaseDC(hWnd, hdc);
	::SelectObject(hdc, hpenDef);
	::SelectObject(hdc, hbrushDef);
	::DeleteObject(hbrush);
	::DeleteObject(hBitmap);
}

//_____________________________________________________________________ Digit
bool Digit::m_bRegistered= false;

Digit::Digit(void)
{
	if (!m_bRegistered)
	{
		this->RegisterClassEx(LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(BLACK_BRUSH));
		m_bRegistered = true;
	}
	m_nValue = 0;
	color = RGB(0, 255, 0);
	colorBackground = RGB(0, 0, 0);
}

Digit::~Digit(void)
{
}

bool Digit::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_COMMAND) return false;
	const int id = LOWORD(e.wParam);
	const int notificationd = HIWORD(e.wParam);
	if (id != this->id) return false;
	if (notificationd!=notification) return false;
	return true;
}

void Digit::SetColor(COLORREF color)
{
	if (this->color!=color) this->color = color;
	::InvalidateRect(hWnd, NULL, TRUE);
}

COLORREF Digit::GetColor(void)
{
	return this->color;
}

COLORREF Digit::GetBackColor(void)
{
	return this->colorBackground;
}
	
void Digit::SetBackColor(COLORREF color)
{
	if (this->color!=colorBackground) this->colorBackground = color;
	::InvalidateRect(hWnd, NULL, TRUE);
}

void Digit::Window_LButtonDown(Win::Event& e)
{
	if (Enabled==false) return;
	HWND hWndParent = ::GetParent(hWnd);
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_CLICK), e.lParam);
}

void Digit::Window_RButtonDown(Win::Event& e)
{
	if (Enabled==false) return;
	HWND hWndParent = ::GetParent(hWnd);
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_RCLICK), e.lParam);
}

void Digit::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, false);
	if (m_nValue!=-1)
	{
		Win::Gdi::Font font(L"Times New Roman", L"8", this->width, this->height);
		wchar_t sz[2];
		RECT rect = {0, 0, this->width, this->height};

		gdi.SelectFont_(font);
		gdi.SetBkColor(colorBackground);
		gdi.SetTextColor(color);
		_snwprintf_s(sz, 2, _TRUNCATE, L"%d", m_nValue);
		gdi.TextOutCenter(rect, sz, true, true);
	}
}

void Digit::SetValue(int n)
{
	if (n==m_nValue) return;
	if (n<0 || n>9) n=-1;
	m_nValue = n;
	::InvalidateRect(hWnd, NULL, n==-1 ? TRUE : FALSE);
}

int Digit::GetValue()
{
	return m_nValue;
}

//_____________________________________________________________________ FlowDisplay
bool FlowDisplay::m_bRegistered= false;

FlowDisplay::FlowDisplay(void)
{
	if (!m_bRegistered)
	{
		this->RegisterClassEx(LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_BTNFACE+1));
		m_bRegistered = true;
	}
	color = RGB(0, 255, 0);
	m_flow = Win::FlowDisplay::None;
	m_bFlowing = false;
	m_bDisplayed = false;
}

FlowDisplay::~FlowDisplay(void)
{
}

bool FlowDisplay::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_COMMAND) return false;
	const int id = LOWORD(e.wParam);
	const int notificationd = HIWORD(e.wParam);
	if (id != this->id) return false;
	if (notificationd!=notification) return false;
	return true;
}

void FlowDisplay::SetColor(COLORREF color)
{
	if (this->color!=color) this->color = color;
	::InvalidateRect(hWnd, NULL, TRUE);
}

COLORREF FlowDisplay::GetColor(void)
{
	return this->color;
}

void FlowDisplay::Window_LButtonDown(Win::Event& e)
{
	if (Enabled==false) return;
	HWND hWndParent = ::GetParent(hWnd);
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_CLICK), e.lParam);
}

void FlowDisplay::Window_RButtonDown(Win::Event& e)
{
	if (Enabled==false) return;
	HWND hWndParent = ::GetParent(hWnd);
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_RCLICK), e.lParam);
}

void FlowDisplay::Window_Timer(Win::Event& e)
{
	m_bDisplayed = !m_bDisplayed;
	::InvalidateRect(hWnd, NULL, TRUE);
}

void FlowDisplay::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, false);
	Win::Gdi::Brush brush;

	//************************************************************* Paint Arrow
	if (m_flow!=Win::FlowDisplay::None)
	{
		POINT point[4];
		if (m_flow ==Win::FlowDisplay::Left)
		{
			point[0].x = (int)(0.80*this->width-0.5); //Left
			point[0].y = (int)(0.15*this->height-0.5);
			point[1].x = (int)(0.80*this->width-0.5);
			point[1].y = (int)(0.85*this->height-0.5);
			point[2].x = (int)(0.15*this->width-0.5);
			point[2].y = (int)(0.5*this->height-0.5);
			point[3].x = point[0].x;
			point[3].y = point[0].y;
		}
		else
		{ 
			point[0].x = (int)(0.20*this->width-0.5); // Right
			point[0].y = (int)(0.15*this->height-0.5);
			point[1].x = (int)(0.20*this->width-0.5);
			point[1].y = (int)(0.85*this->height-0.5);
			point[2].x = (int)(0.85*this->width-0.5);
			point[2].y = (int)(0.5*this->height-0.5);
			point[3].x = point[0].x;
			point[3].y = point[0].y;
		}
		if (this->m_bDisplayed)
		{
			brush.CreateSolid(color);
		}
		else
		{
			brush.CreateSolid(ReduceLuminance(color));
		}
		gdi.SelectBrush_(brush);
		gdi.Polygon(point, 4);
	}

	//******************************************************** Paint Stop Sign
	if (m_flow==Win::FlowDisplay::None)
	{
		// Red Hexagon
		POINT point[5];
		point[0].x = (int)(0.15*this->width-0.5);
		point[0].y = (int)(0.15*this->height-0.5);
		point[1].x = (int)(0.85*this->width-0.5);
		point[1].y = (int)(0.15*this->height-0.5);
		point[2].x = (int)(0.85*this->width-0.5);
		point[2].y = (int)(0.85*this->height-0.5);
		point[3].x = (int)(0.15*this->width-0.5);
		point[3].y = (int)(0.85*this->height-0.5);
		point[4].x = (int)(0.15*this->width-0.5);
		point[4].y = (int)(0.15*this->height-0.5);
		brush.CreateSolid(color);
		gdi.SelectBrush_(brush);
		gdi.Polygon(point, 5);

		////**************************** White STOP
		//int centerX = (int)(width/2.0+0.5);
		//int centerY = (int)(height/2.0+0.5);
		//Win::Gdi::Font font(L"Times New Roman", 4, (int)(0.4*width), (int)(0.4*height));
		////
		//gdi.SetTextColor(RGB(255, 255, 255));
		//gdi.SetBkMode(true);
		//gdi.SelectFont_(font);
		//gdi.TextOutCenter(centerX, centerY, L"STOP", true, true);
	}
}

COLORREF FlowDisplay::ReduceLuminance(COLORREF color)
{
	int rojo = GetRValue(color);
	rojo-=150; 
	if (rojo<0) rojo=0;
	//
	int verde = GetGValue(color);
	verde-=150; 
	if (verde<0) verde=0;
	//
	int azul = GetBValue(color);
	azul-=150; 
	if (azul<0) azul=0;
	COLORREF resultado;
	resultado = RGB(rojo, verde, azul);
	return resultado;
}

void FlowDisplay::SetFlow(Win::FlowDisplay::Flow flow)
{
	if (m_flow==flow) return;
	if (flow==Win::FlowDisplay::Left || flow==Win::FlowDisplay::None 
		|| flow==Win::FlowDisplay::Right)
	{
		m_flow = flow;
		switch(m_flow)
		{
		case Win::FlowDisplay::Left:
			if (!m_bFlowing)
			{
				this->timer.Set(1, 500);
				m_bDisplayed = true;
				m_bFlowing = true;
			}
			break;
		case Win::FlowDisplay::None:
			if (m_bFlowing)
			{
				this->timer.Kill(1);
				m_bFlowing = false;
			}
			break;
		case Win::FlowDisplay::Right:
			if (!m_bFlowing)
			{
				this->timer.Set(1, 500);
				m_bDisplayed = true;
				m_bFlowing = true;
			}
			break;
		}
		::InvalidateRect(hWnd, NULL, TRUE);
	}
}

//_____________________________________________________________________ SimulationView
bool SimulationView::m_bRegistered= false;

SimulationView::SimulationView(void)
{
	if (!m_bRegistered)
	{
		this->RegisterClassEx(LoadCursor(NULL, IDC_ARROW), (HBRUSH)::GetStockObject(NULL_BRUSH));
		m_bRegistered = true;
	}
	_backColor = RGB(150, 150, 255);
	_textColor = RGB(50, 50, 180);
	_hfont = NULL;
}

SimulationView::~SimulationView(void)
{
}

COLORREF SimulationView::GetBackColor()
{
	return _backColor;
}

void SimulationView::SetBackColor(COLORREF color)
{
	_backColor = color;
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

COLORREF SimulationView::GetTextColor()
{
	return _textColor;
}

void SimulationView::SetTextColor(COLORREF color)
{
	_textColor = color;
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

void SimulationView::SetFont(Win::Gdi::Font& font)
{
	_hfont = font.GetHFONT();
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

bool SimulationView::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_COMMAND) return false;
	const int id = LOWORD(e.wParam);
	const int notificationd = HIWORD(e.wParam);
	if (id != this->id) return false;
	if (notificationd!=notification) return false;
	return true;
}

void SimulationView::Window_LButtonDown(Win::Event& e)
{
	if (Enabled==false) return;
	HWND hWndParent = ::GetParent(hWnd);
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_CLICK), e.lParam);
}

void SimulationView::Window_RButtonDown(Win::Event& e)
{
	if (Enabled==false) return;
	HWND hWndParent = ::GetParent(hWnd);
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_RCLICK), e.lParam);
}

void SimulationView::Window_Open(Win::Event& e)
{
	RECT rc;
	::GetClientRect(hWnd, &rc);
	this->bitmap.CreateCompatible(hWnd, rc.right-rc.left, rc.bottom-rc.top);
}

void SimulationView::Window_Size(Win::Event& e)
{
	this->bitmap.CreateCompatible(hWnd, this->width, this->height);
}

void SimulationView::Window_Timer(Win::Event& e)
{
	PAINTSTRUCT ps;
	ps.hdc = bitmap.GetBitmapDC();
	ps.rcPaint.left = 0;
	ps.rcPaint.top = 0;
	ps.rcPaint.right = this->width;
	ps.rcPaint.bottom = this->height;
	Win::Gdi gdi(ps, false);
	Win::Gdi::Brush brushBack;
	if (Enabled)
	{
		brushBack.CreateSolid(_backColor);
	}
	else
	{
		brushBack.CreateSolid(WIN_BACK_DISABLED);
	}
	gdi.FillRect(ps.rcPaint, brushBack);
	if (_hfont) gdi.SelectFont__(_hfont);
	gdi.SetTextColor(_textColor);
	HWND hWndParent = ::GetParent(hWnd);
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_PAINT), (WPARAM)&gdi);
	::InvalidateRect(hWnd, NULL, FALSE);
}

void SimulationView::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, false);
	::BitBlt(gdi.GetHDC(), 0, 0, this->width, this->height, bitmap.GetBitmapDC(), 0, 0, SRCCOPY);
}

void SimulationView::Start(int refreshTime)
{
	this->timer.Set(1, refreshTime);
	time.Start();
	HWND hWndParent = ::GetParent(hWnd);
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_STARTED), 0);
}

void SimulationView::Stop()
{
	this->timer.Kill(1);
	HWND hWndParent = ::GetParent(hWnd);
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_STOPPED), 0);
}

//_____________________________________________________________________ Tank
Tank::Tank(void)
{
	_tankColor = RGB(0, 160, 0);
	_level = 0;
	_levelOld = 0;
	_minLevel = 0;
	_maxLevel = 100;
	//_backColor = RGB(0, 0, 0);
	_lineColor = RGB(150, 150, 150);
	//_textColor = RGB(120, 120, 190);
}

Tank::~Tank(void)
{
}

void Tank::Window_Open(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
}

void Tank::Window_Size(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
	OnSizePrivate();
}

void Tank::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, false);
	Win::Gdi gdiBitmap(bitmap, gdi.GetRcPaint(), false);
	if (_hfont) gdiBitmap.SelectFont__(_hfont);
	OnPaintControl(gdiBitmap);
	gdi.DrawDoubleBuffer(bitmap);
}

void Tank::SetTankColor(COLORREF color)
{
	if (_tankColor == color) return;
	_tankColor = color;
	if (hWnd) ::InvalidateRect(hWnd, &_rcCilinder, FALSE);
}

COLORREF Tank::GetTankColor(void)
{
	return _tankColor;
}

void Tank::SetRange(double minimum, double maximum)
{
	_minLevel = minimum;
	_maxLevel = maximum;
	if (hWnd) ::InvalidateRect(hWnd, &_rcCilinder, FALSE);
}

void Tank::SetLevel(double level)
{
	if (_level==level) return;
	if (level<_minLevel) level = _minLevel;
	if (level>_maxLevel) level = _maxLevel;
	_level = level;
	if (hWnd) ::InvalidateRect(hWnd, &_rcCilinder, FALSE);
}

double Tank::GetLevel()
{
	return _level;
}

void Tank::OnSizePrivate()
{
	//bitmap.CreateCompatible(hWnd, width, height);
	_markDelta = 0.63*height/10.0;
	_rcScale.top = (int)(0.27 * height - _markDelta/2.0+0.5);
	_rcScale.right = (int)(0.22*width+0.5);
	_rcScale.left = 0;
	_rcScale.bottom = (int)(0.90*height + _markDelta/2.0+0.5);
	//
	_rcMarks.top = (int)(0.27 * height+0.5);
	_rcMarks.right = (int)(0.30 * width+0.5);
	_rcMarks.left = (int)(0.22 * width+0.5);
	_rcMarks.bottom = (int)(0.90 * height+0.5);
	//
	_rcCilinder.top = 0;
	_rcCilinder.right = (int)(0.76 * width+0.5);
	_rcCilinder.left = (int)(0.30 * width+0.5);
	_rcCilinder.bottom = height;
	//
	_rcCaption.top = 0;
	_rcCaption.left = 0;
	_rcCaption.right = (int)(0.30 * width+0.5);
	_rcCaption.bottom = (int)(0.13 * height+0.5);
}

void Tank::OnPaintControl(Win::Gdi& gdi)
{
	//_____________________________________________ Font
	Win::Gdi::Font font;
	
	if (_printerFormat || height>WINFONT_MAXRES || width>WINFONT_MAXRES)
	{
		LOGFONT logfont;
		this->GetLogfont(logfont);
		logfont.lfHeight = -(int)(MINIMUM(width, height)*0.05+0.5);
		font.Create(logfont);
		gdi.SelectFont_(font);
	}
	else
	{
		if (_hfont) gdi.SelectFont__(_hfont);
	}

	//_____________________________________________ Line
	Win::Gdi::Pen penLine;
	if (_printerFormat)
	{
		penLine.Create(PS_SOLID, WINXYCHART_PRINTERPEN, _lineColor);
	}
	else
	{
		penLine.Create(PS_SOLID, 1, _lineColor);
	}


	//____________________________ Text
	if (this->Enabled)
	{
		gdi.SetBkColor(_backColor);
		gdi.SetTextColor(_textColor);
	}
	else
	{
		gdi.SetBkColor(WIN_BACK_DISABLED);
		gdi.SetTextColor(WIN_TEXT_DISABLED);
	}

	//_______________________________________________________ Background
	Win::Gdi::Brush brushBackground;
	const RECT rcPaint = gdi.GetRcPaint();
	if (_printerFormat==false)
	{
		if (this->Enabled)
		{
			brushBackground.CreateSolid(_backColor);
		}
		else
		{
			brushBackground.CreateSolid(WIN_BACK_DISABLED);
		}
		gdi.SelectBrush_(brushBackground);
		gdi.FillRect(rcPaint, brushBackground);
	}

	//_____________________________________________________ Marks
	if (gdi.DoRcPaintOverlap(_rcMarks))
	{
		int y = 0;
		gdi.SelectPen_(penLine);
		for(int i=0; i<11; i++)
		{
			y = (int)(0.27*this->height + i * _markDelta+0.5);
			gdi.MoveToEx((int)(_rcMarks.left*1.05+0.5), y); // Make the line a little shorter on the left
			gdi.LineTo(_rcMarks.right, y);
		}
	}

	//_______________________________________Scale
	wchar_t sz[64];
	if (gdi.DoRcPaintOverlap(_rcScale))
	{
		int y = 0;
		const double deltaY = (_maxLevel - _minLevel)/10.0;
		double value = 0;
		RECT rc = {0,  0, (int)(0.22* width+0.5), 0};//left, top, right, bottom
		for(int i=0; i<11; i++)
		{
			if (i%2 == 1) continue;
			y = (int)(0.27* height + i * _markDelta - _markDelta/2.0+0.5);
			rc.top = y;
			rc.bottom = (int)(y + _markDelta+0.5);
			value = _maxLevel - i*deltaY;
			_snwprintf_s(sz, 64, _TRUNCATE, L"%.1f", value);
			gdi.TextOutVCenterRight(rc, sz);
		}
	}

	if (gdi.DoRcPaintOverlap(_rcCilinder))
	{
		Win::Gdi::Brush brushTop(_lineColor);
		//HBRUSH hBrush = (HBRUSH)::GetStockObject(BLACK_BRUSH);
		//_____________________________________________________ Recipient without top
		gdi.SelectBrush_(brushTop);
		gdi.SelectPen_(penLine);
		gdi.Cilinder((int)(0.30* width+0.5), (int)(0.13* height+0.5), 
				(int)((_rcCilinder.right-_rcCilinder.left-1)/2.0+0.5), 0.77*this->height, false, true);

		//_____________________________________________________ Liquid 
		HPEN hPen = (HPEN)::GetStockObject(NULL_PEN);
		const double scale = (0.63*height) / (_maxLevel - _minLevel);
		double height = _level*scale;

		if (height>0.63*this->height) height = 0.63*this->height;  // prevents overflow 
		if (height<0) height = 0; //prevent underflow

		//** Paint background
		if (_level < _levelOld)
		{
			RECT rc = {(int)(0.30*this->width+0.5), 0, (int)(0.76*this->width+0.5), (int)(0.90*this->height-height+0.5)};//left, top, right, bottom
			gdi.FillRect(rc, brushBackground);
		}

		gdi.SelectPen__(hPen);
		gdi.SolidCilinder((int)(0.30*this->width+0.5+1), (int)(0.90*this->height-height-0.6), 
			(int)((_rcCilinder.right - _rcCilinder.left-1)/2.0+0.5), height, _tankColor);

		//_____________________________________________________ Recipient without bottom
		HBRUSH hBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
		gdi.SelectBrush__(hBrush);
		gdi.SelectPen_(penLine);
		gdi.Cilinder((int)(0.30*this->width+0.5), (int)(0.13*this->height+0.5), 
				(int)((_rcCilinder.right - _rcCilinder.left-1)/2.0+0.5), 0.77*this->height, true, false);
	}

	//_________________________________________________ Caption
	if (gdi.DoRcPaintOverlap(_rcCaption))
	{
		if (_text.length()>0) gdi.TextOut(_rcCaption.left + _fontHeight/2, _rcCaption.top + _fontHeight/4, _text.c_str());
	}

	_levelOld = _level;
}

//_____________________________________________________________________ ValueDisplay
ValueDisplay::ValueDisplay(void)
{
	_text = L"Temperature";
	_value = L"Value";
	::ZeroMemory(&_rectName, sizeof(RECT));
	::ZeroMemory(&_rectValue, sizeof(RECT));
	_lineColor = RGB(120, 110, 110);
}

ValueDisplay::~ValueDisplay(void)
{
}

void ValueDisplay::Window_Open(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
}

void ValueDisplay::Window_Size(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
	OnSizePrivate();
}

void ValueDisplay::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, false);
	Win::Gdi gdiBitmap(bitmap, gdi.GetRcPaint(), false);
	if (_hfont) gdiBitmap.SelectFont__(_hfont);
	OnPaintControl(gdiBitmap);
	gdi.DrawDoubleBuffer(bitmap);
}

double ValueDisplay::GetDouble()
{
	if (_value.length()<=0) return 0.0;
	return Sys::Convert::ToDouble(_value);
}

void ValueDisplay::SetDouble(double value)
{
	Value = Sys::Convert::ToString(value);
}

void ValueDisplay::OnSizePrivate()
{
	_rectName.top = 0;
	_rectName.right = this->width;
	_rectName.left = 0;
	_rectName.bottom = (int)(this->height*0.40+0.5);
	//
	_rectValue.top = _rectName.bottom;
	_rectValue.right = this->width;
	_rectValue.left = 0;
	_rectValue.bottom = this->height;
}

void ValueDisplay::OnPaintControl(Win::Gdi& gdi)
{
	//_____________________________________________ Font
	Win::Gdi::Font font;
	
	if (_printerFormat || height>WINFONT_MAXRES || width>WINFONT_MAXRES)
	{
		LOGFONT logfont;
		this->GetLogfont(logfont);
		logfont.lfHeight = -(int)((_rectName.bottom - _rectName.top)/1.5+0.5);
		font.Create(logfont);
		gdi.SelectFont_(font);
	}
	else
	{
		if (_hfont) gdi.SelectFont__(_hfont);
	}

	////_____________________________________________ Line
	//Win::Gdi::Pen penLine;
	//if (_printerFormat)
	//{
	//	penLine.Create(PS_SOLID, WINXYCHART_PRINTERPEN, _lineColor);
	//}
	//else
	//{
	//	penLine.Create(PS_SOLID, 1, _lineColor);
	//}


	//____________________________ Text
	if (this->Enabled)
	{
		gdi.SetBkColor(_backColor);
		gdi.SetTextColor(_textColor);
	}
	else
	{
		gdi.SetBkColor(WIN_BACK_DISABLED);
		gdi.SetTextColor(WIN_TEXT_DISABLED);
	}

	//_______________________________________________________ Background
	Win::Gdi::Brush brushBackground;
	const RECT rcPaint = gdi.GetRcPaint();
	if (_printerFormat==false)//gdi.DoRcPaintOverlap(m_box) && )
	{
		if (this->Enabled)
		{
			brushBackground.CreateSolid(_backColor);
		}
		else
		{
			brushBackground.CreateSolid(WIN_BACK_DISABLED);
		}
		gdi.SelectBrush_(brushBackground);
		gdi.FillRect(rcPaint, brushBackground);
	}

	//______________________________________________ Paint Name
	if (_text.length()>0 && gdi.DoRcPaintOverlap(_rectName))
	{
		gdi.SetTextColor(_lineColor);
		gdi.TextOutCenter(_rectName, _text.c_str(), true, true);
		////
		//gdi.SelectPen__(whitePen);
		//gdi.Line(m_rectName.left, m_rectName.bottom, m_rectName.right, m_rectName.bottom);
	}

	//______________________________________________ Paint Value
	if (_value.length()>0 && gdi.DoRcPaintOverlap(_rectValue))
	{
		gdi.SetTextColor(_textColor);
		gdi.TextOutCenter(_rectValue, _value.c_str(), true, true);
	}
}

void ValueDisplay::SetValue(const wstring& value)
{
	_value = value;
	if (hWnd) ::InvalidateRect(hWnd, &_rectValue, TRUE);
}

wstring& ValueDisplay::GetValue()
{
	return _value;
}

//_____________________________________________________________________ ColorDisplay
ColorDisplay::ColorDisplay(void)
{
	alignment = TA_CENTER;
	_blink = false;
	_on = false;
}

ColorDisplay::~ColorDisplay(void)
{
	this->SetBlink(false);
}

void ColorDisplay::Window_Open(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
}

void ColorDisplay::Window_Size(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
	OnSizePrivate();
}

void ColorDisplay::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, false);
	Win::Gdi gdiBitmap(bitmap, gdi.GetRcPaint(), false);
	if (_hfont) gdiBitmap.SelectFont__(_hfont);
	OnPaintControl(gdiBitmap);
	gdi.DrawDoubleBuffer(bitmap);
}

void ColorDisplay::SetBlink(bool blink)
{
	this->timer.Kill(1);
	_blink = false;
	_on = false;
	if (hWnd == NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
	::UpdateWindow(hWnd);
	if (blink)
	{
		_blink = true;
		this->timer.Set(1, 1000);
	}
}

bool ColorDisplay::GetBlink()
{
	return _blink;
}

void ColorDisplay::Window_Timer(Win::Event& e)
{
	if (e.wParam != 1) return;
	if (hWnd == NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

void ColorDisplay::SetAlignment(int alignment) //TA_LEFT, TA_CENTER, TA_RIGHT
{
	this->alignment = alignment;
	if (hWnd == NULL) return;
	::InvalidateRect(hWnd, NULL, false);
}

bool ColorDisplay::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_COMMAND) return false;
	const int id = LOWORD(e.wParam);
	const int notificationd = HIWORD(e.wParam);
	if (id != this->id) return false;
	if (notificationd!=notification) return false;
	return true;
}

void ColorDisplay::OnPaintControl(Win::Gdi& gdi)
{
	COLORREF backColor = _backColor;
	COLORREF textColor = _textColor;

	if (_blink) _on = (_on==false);
	
	//________________________ Fill background
	RECT rect = {0, 0, this->width, this->height};
	Win::Gdi::Brush brush;
	if (this->Enabled)
	{
		if (_blink)
		{
			if (_on)
			{
				if (Win::Gdi::Color3D::IsCloseToBlack(_backColor))
				{
					backColor = Win::Gdi::Color3D::GetLightColor(_backColor);
				}
				else
				{
					backColor = Win::Gdi::Color3D::GetShadowColor(_backColor);
				}
				if (Win::Gdi::Color3D::IsCloseToBlack(_textColor))
				{
					textColor = Win::Gdi::Color3D::GetHighLightColor(_textColor);
				}
				else
				{
					textColor = Win::Gdi::Color3D::GetDarkShadowColor(_textColor);
				}
			}
		}
	}
	else
	{
		backColor = WIN_BACK_DISABLED;
		textColor = WIN_TEXT_DISABLED;
	}
	brush.CreateSolid(backColor);
	gdi.FillRect(gdi.GetRcPaint(), brush);

	//______________________________Draw Text
	if (_text.length()<=0) return;
	
	DWORD dwStyle = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	DWORD dwExStyle = ::GetWindowLongPtr(hWnd, GWL_EXSTYLE);
	bool offset = (dwStyle & WS_BORDER) || (dwExStyle & WS_EX_CLIENTEDGE);
	if (offset)
	{
		rect.bottom-=2;
	}

	gdi.SetBkColor(backColor);
	gdi.SetTextColor(textColor);

	if (_hfont) gdi.SelectFont__(_hfont);

	switch(alignment)
	{
	case TA_LEFT:
		rect.left += gdi.tm.tmAveCharWidth;
		gdi.TextOutVCenterLeft(rect, _text.c_str());
		break;
	case TA_CENTER:
		gdi.TextOutCenter(rect, _text.c_str(), true, true);
		break;
	case TA_RIGHT:
		rect.right -= gdi.tm.tmAveCharWidth;
		gdi.TextOutVCenterRight(rect, _text.c_str());
		break;
	}
}

#ifdef WIN_DAC_ADC_SUPPORT
//_____________________________________________________________________ SignalView
SignalView::SignalView(void)
{
	for(int i=0; i<WIN_SIGNALVIEWER_MAX; i++)
	{
		_ptLeft[i].x = i;
		_ptLeft[i].y = 0;
		//
		_ptRight[i].x = i;
		_ptRight[i].y = 0;
	}
	_minimum = 0;
	_maximum = 0;
	_backColor = RGB(0, 0, 0);
	_lineColor = RGB(0, 0, 255);
	_textColor = RGB(10, 150, 10);
}

SignalView::~SignalView(void)
{
}

bool SignalView::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_COMMAND) return false;
	const int id = LOWORD(e.wParam);
	const int notificationd = HIWORD(e.wParam);
	//if (id != this->id) return false;
	if (notificationd!=notification) return false;
	OnData(e.lParam);
	return false;
}

void SignalView::SetToZero(void)
{
	for(int i=0; i<WIN_SIGNALVIEWER_MAX; i++)
	{
		_ptLeft[i].y = 0;
		_ptRight[i].y = 0;
	}
	if (hWnd) ::InvalidateRect(hWnd, NULL, true);
}

// buferSize must be bigger than WIN_SIGNALVIEWER_MAX 
// Call this function to update the signals on the control
void SignalView::OnData(LPARAM lParam)
{
	PWAVEHDR pwd = (PWAVEHDR)lParam;
	Sys::Sample16 *data = (Sys::Sample16 *)pwd->lpData;
	_minimum = 0;
	_maximum = 0;
	for(int i=0; i<WIN_SIGNALVIEWER_MAX; i++)
	{
		_ptLeft[i].y = data[i].channel_1;
		if (_minimum > _ptLeft[i].y) _minimum = _ptLeft[i].y;
		if (_maximum < _ptLeft[i].y) _maximum = _ptLeft[i].y;
		//
		_ptRight[i].y = data[i].channel_2;
		if (_minimum > _ptRight[i].y) _minimum = _ptRight[i].y;
		if (_maximum < _ptRight[i].y) _maximum = _ptRight[i].y;
	}
	::InvalidateRect(hWnd, NULL, true);
}

void SignalView::OnPaintControl(Win::Gdi& gdi)
{
	//_____________________________________________ Font
	Win::Gdi::Font font;
	
	if (_printerFormat || height>WINFONT_MAXRES || width>WINFONT_MAXRES)
	{
		LOGFONT logfont;
		this->GetLogfont(logfont);
		logfont.lfHeight = -(int)(MINIMUM(width, height)*0.05+0.5);
		font.Create(logfont);
		gdi.SelectFont_(font);
	}
	else
	{
		if (_hfont) gdi.SelectFont__(_hfont);
	}

	//_____________________________________________ Line
	Win::Gdi::Pen penLine;
	if (_printerFormat)
	{
		penLine.Create(PS_SOLID, WINXYCHART_PRINTERPEN, _lineColor);
	}
	else
	{
		penLine.Create(PS_SOLID, 1, _lineColor);
	}

	//____________________________ Text
	if (this->Enabled)
	{
		gdi.SetBkColor(_backColor);
		gdi.SetTextColor(_textColor);
	}
	else
	{
		gdi.SetBkColor(WIN_BACK_DISABLED);
		gdi.SetTextColor(WIN_TEXT_DISABLED);
	}

	//_______________________________________________________ Background
	Win::Gdi::Brush brushBackground;
	if (_printerFormat==false)
	{
		RECT rect = gdi.GetRcPaint();
		if (this->Enabled)
		{
			brushBackground.CreateSolid(_backColor);
		}
		else
		{
			brushBackground.CreateSolid(WIN_BACK_DISABLED);
		}
		gdi.SelectBrush_(brushBackground);
		gdi.FillRect(rect, brushBackground);
	}

	Win::Gdi::Pen penAzul(PS_SOLID, 1, Win::Gdi::Color3D::GetConstrastColor(_lineColor));
	Win::Gdi::Pen penRed(PS_SOLID, 1, RGB(255, 0, 0));
	_minimum = abs(_minimum);
	_maximum = abs(_maximum);
	int level = (_minimum > _maximum) ? _minimum : _maximum;
	bool saturation = (level >32760); 
	
	HDC hdc = gdi.GetHDC();
	//___________________________________  Text
	if (_text.length()>0) gdi.TextOut(0, 0, _text.c_str());

	::SetMapMode(hdc, MM_ANISOTROPIC);
	::SetWindowExtEx(hdc, WIN_SIGNALVIEWER_MAX/2, 32768, NULL); //32768
	::SetViewportExtEx(hdc, width/2, -height/2, NULL);
	::SetViewportOrgEx(hdc, 0, height/2, NULL);

	if (saturation)
		gdi.SelectPen_(penRed);
	else
		gdi.SelectPen_(penLine);
	gdi.Polyline(_ptLeft, WIN_SIGNALVIEWER_MAX);
	//
	if (saturation)
		gdi.SelectPen_(penRed);
	else
		gdi.SelectPen_(penAzul);
	gdi.Polyline(_ptRight, WIN_SIGNALVIEWER_MAX);
}
#endif

//_____________________________________________________________________ Graph
Graph::Graph(void)
{
	this->Contruction();
}

Graph::~Graph(void)
{
	Delete();
}

void Graph::Contruction(void)
{
	color = RGB(200, 60, 60);
	penWidth = 1;
	m_pScreenPoints = NULL;
	m_pDataPoints = NULL;
	m_pszCaption = NULL;
	m_type = Win::Graph::line;
	this->m_nPointCount = 0;
}

Graph::Graph(const Graph& init)
{
	this->Contruction();
	Copy(init);
}

void Graph::Copy(const Graph& init)
{
	color = init.color;
	penWidth = init.penWidth;
	m_type = init.m_type;
	this->SetPointCount(init.m_nPointCount);
	::memcpy(m_pScreenPoints, init.m_pScreenPoints, m_nPointCount*sizeof(POINT));
	::memcpy(m_pDataPoints, init.m_pDataPoints, m_nPointCount*sizeof(Win::Gdi::PointF));
	this->SetCaption(init.m_pszCaption);
}

Graph& Graph::operator =(const Graph& init)
{
	Copy(init);
	return *this;
}

void Graph::SetType(Win::Graph::Type type)
{
	this->m_type = type;
}

Win::Graph::Type Graph::GetType()
{
	return this->m_type;
}

int Graph::GetPointCount() 
{
	return m_nPointCount;
}

POINT* Graph::GetScreenPoints()
{
	return m_pScreenPoints;
}

Win::Gdi::PointF* Graph::GetDataPoints()
{
	return m_pDataPoints;
}

void Graph::Delete(void)
{
	if (m_pScreenPoints) delete [] m_pScreenPoints;
	if (m_pDataPoints) delete [] m_pDataPoints;
	if (m_pszCaption) delete [] m_pszCaption;
	//
	m_pScreenPoints = NULL;
	m_pDataPoints = NULL;
	m_pszCaption = NULL;
	this->m_nPointCount = 0;
}

Win::Gdi::PointF& Graph::Get(long index)
{
	if (index<0 || index>=(long) m_nPointCount) throw out_of_range("Invalid index");
	return m_pDataPoints[index];
}

void Graph::Set(long index, double x, double y)
{
	if (index<0 || index>=(long) m_nPointCount) throw out_of_range("Invalid index");
	m_pDataPoints[index].x = x;
	m_pDataPoints[index].y = y;
}

// Returns NULL if OK
wchar_t* Graph::SaveAsAnsiTextFile(const wchar_t* pszFileName, const char* pszFormat)
{
	 if (pszFormat==NULL) pszFormat = "%.7f, %.7f";
	char sz[255];
	wchar_t* pszError = NULL;
	int nWrite;
	DWORD dwBytesWritten;
	HANDLE hFile = CreateFile (pszFileName, GENERIC_WRITE, 0, NULL, 
		CREATE_ALWAYS, 0, NULL);

	if (hFile == INVALID_HANDLE_VALUE) 
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

		lstrcpyn(errorInformation, (wchar_t*)lpMsgBuf, 256);
		errorInformation[256-1]='\0';
		::LocalFree( lpMsgBuf );
		return errorInformation;
	}

	for(int i=0; i<m_nPointCount; i++)
	{
		nWrite =_snprintf_s(sz, 255, _TRUNCATE, pszFormat, m_pDataPoints[i].x, m_pDataPoints[i].y); // Write data
		::WriteFile (hFile, sz, nWrite, &dwBytesWritten, NULL);
		//
		if (i < m_nPointCount-1)
		{
			strcpy_s(sz, "\r\n");
			nWrite = (int)strlen(sz); // Write delimiter
			::WriteFile (hFile, sz, nWrite, &dwBytesWritten, NULL);
		}
	}
	::CloseHandle(hFile);
	return pszError;
}

bool Graph::SetPointCount(int nPointCount) 
{
	if (nPointCount>0)
	{
		if (nPointCount != m_nPointCount)
		{
			 if  (m_pScreenPoints) delete [] m_pScreenPoints;
			 if (m_pDataPoints) delete[] m_pDataPoints;
			m_pScreenPoints = NULL;
			m_pDataPoints = NULL;
			m_nPointCount = 0;
			//
			m_pScreenPoints = new POINT[nPointCount];
			m_pDataPoints = new Win::Gdi::PointF[nPointCount];
			if (m_pScreenPoints!=NULL && m_pDataPoints!=NULL)
				m_nPointCount = nPointCount;
		}
		return (m_pScreenPoints!=NULL && m_pDataPoints!=NULL);
	}
	else
	{
		if  (m_pScreenPoints) delete [] m_pScreenPoints;
		if (m_pDataPoints) delete[] m_pDataPoints;
		m_pScreenPoints = NULL;
		m_pDataPoints = NULL;
		m_nPointCount = 0;
		return true;
	}
	return false;
}

bool Graph::DownSample(int newLength)
{
	if (this->m_nPointCount==0) return false;
	if (newLength>=m_nPointCount) return false;
	double * x = new double[newLength];
	if (x==NULL) return false;

	double * y = new double[newLength];
	if (y==NULL) 
	{
		if (x) delete [] x;
		return false;
	}
	const int skip = m_nPointCount/newLength;
	int i;
	for(i=0; i<newLength; i++)
	{
		x[i] = m_pDataPoints[skip*i].x;
		y[i] = m_pDataPoints[skip*i].y;
	}
	if (SetPointCount(newLength)==false)
	{
		if (x) delete [] x;
		if (y) delete [] y;
	}
	for(i=0; i<newLength; i++)
	{
		m_pDataPoints[i].x = x[i];
		m_pDataPoints[i].y = y[i];
	}

	if (x) delete [] x;
	if (y) delete [] y;
	return true;
}

void Graph::SetData(double* x, double* y, int length)
{
	this->SetPointCount(length);
	for(int i = 0; i<length; i++)
	{
		m_pDataPoints[i].x = x[i];
		m_pDataPoints[i].y = y[i];
	}
}

void Graph::SetData(double* y, int length)
{
	this->SetPointCount(length);
	for(int i = 0; i<length; i++)
	{
		m_pDataPoints[i].x = i+1;
		m_pDataPoints[i].y = y[i];
	}
}

double Graph::GetMaxX(void)
{
	if (this->m_nPointCount==0) return 0.0;
	double maximum = m_pDataPoints[0].x;
	for(int i = 1; i<m_nPointCount; i++)
	{
		if (maximum<m_pDataPoints[i].x) maximum = m_pDataPoints[i].x;
	}
	return maximum;
}

double Graph::GetMaxY(void)
{
	if (this->m_nPointCount==0) return 0.0;
	double maximum = m_pDataPoints[0].y;
	for(int i = 1; i<m_nPointCount; i++)
	{
		if (maximum<m_pDataPoints[i].y) maximum = m_pDataPoints[i].y;
	}
	return maximum;
}

// x and y are on the plot coordinates
void Graph::SetCaption(const wchar_t* caption)
{
	if (m_pszCaption) 
	{
		delete [] m_pszCaption;
		m_pszCaption = NULL;
	}
	if (caption)
	{
		m_pszCaption = new wchar_t[lstrlen(caption)+1];
		lstrcpy(m_pszCaption, caption);
	}
}

void Graph::QuickDisplay(HWND hWnd, const wchar_t* pszFormat)
{
	wchar_t szT[4096];
	wchar_t sz[64];
	int n = 0;

	szT[0]='\0';

	if (pszFormat == NULL) pszFormat = L"[%d] =  (%.7f , %.7f), \t";
	for(int i=0; i<(int)m_nPointCount; i++)
	{
		n+= _snwprintf_s(sz, 64, _TRUNCATE, pszFormat, i, m_pDataPoints[i].x, m_pDataPoints[i].y);
		if (n<4096) lstrcat(szT, sz);
		else break;
	}
	if (lstrlen(szT)>3) szT[lstrlen(szT)-3] = '\0';
	::MessageBox(hWnd, szT, L"PointArray::Display", MB_OK);
}

const wchar_t* Graph::GetCaption()
{
	return m_pszCaption;
}

////_____________________________________________________________________ PolarChart Graph
//PolarGraph::PolarGraph(void)
//{
//}
//
//PolarGraph::~PolarGraph(void)
//{
//}
//
//bool PolarGraph::SetPointCount(int nPointCount) 
//{
//	if (nPointCount>0)
//	{
//		if (nPointCount != m_nPointCount)
//		{
//			 if  (m_pScreenPoints) delete [] m_pScreenPoints;
//			 if (m_pDataPoints) delete[] m_pDataPoints;
//			m_pScreenPoints = NULL;
//			m_pDataPoints = NULL;
//			m_nPointCount = 0;
//			//
//			m_pScreenPoints = new POINT[nPointCount+1]; // Allocate memory to close the graph
//			m_pDataPoints = new Win::Gdi::PointF[nPointCount];
//			if (m_pScreenPoints!=NULL && m_pDataPoints!=NULL)
//				m_nPointCount = nPointCount;
//		}
//		return (m_pScreenPoints!=NULL && m_pDataPoints!=NULL);
//	}
//	else
//	{
//		if  (m_pScreenPoints) delete [] m_pScreenPoints;
//		if (m_pDataPoints) delete[] m_pDataPoints;
//		m_pScreenPoints = NULL;
//		m_pDataPoints = NULL;
//		m_nPointCount = 0;
//		return true;
//	}
//	return false;
//}

//_____________________________________________________________________ GraphCollection
GraphCollection::GraphCollection()
{
}

GraphCollection::~GraphCollection()
{
}

int GraphCollection::GetCount()
{
	return _data.size();
}

int GraphCollection::Add()
{
	Win::Graph graph;
	_data.push_back(graph);
	return _data.size();
}

int GraphCollection::Add(int graphPointCount)
{
	Win::Graph graph;
	_data.push_back(graph);
	_data.back().SetPointCount(graphPointCount);
	return _data.size();
}

void GraphCollection::Delete(long index)
{
	vector<Win::Graph>::iterator p = _data.begin() +index;
	if (p == _data.end()) return;
	_data.erase(p);
}

void GraphCollection::DeleteAll()
{
	_data.clear();
}

Win::Graph& GraphCollection::operator[](long index)
{
	return _data[index];
}


//_____________________________________________________________________ XyChart
XyChart::XyChart(void)
{
	_isLogX = false;
	_isLogY = false;
	//
	_minX = 0.0;
	_maxX = 10.0;
	_minY = 0.0;
	_maxY = 10.0;
	_minXUser = 0.0;
	_maxXUser = 10.0;
	_minYUser = 0.0;
	_maxYUser = 10.0;
	_scaleX = 1.0;
	_scaleY = 1.0;
	_boxCaptionHeight = 1.0;
	_showGrid = true;
	//
	_originX = 0.0;
	_originY = 0.0;
	_formatX[0] = '\0';//lstrcpy(_formatX, L"%g");
	_formatY[0] = '\0';//lstrcpy(_formatY, L"%g");
	_divCountX = 5;
	_divCountY = 5;
	_subDivCountX = 4;//4;
	_subDivCountY = 4;//4;
	//
	_useCommaX = false;
	_useCommaY = false;
	//
	_textColor = RGB(0, 0, 200);
	_lineColor = RGB(235, 235, 255);
	_subgridColor = RGB(245, 245, 245);
	//
	_symbolCaptionX = false;
	_symbolCaptionY = false;
}

XyChart::~XyChart(void)
{
}

void XyChart::SetShowGrid(bool showGrid)
{
	_showGrid = showGrid;
	RefreshGraphArea();
}

bool XyChart::GetShowGrid()
{
	return _showGrid;
}

void XyChart::Window_Open(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
}

void XyChart::Window_Size(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
	OnSizePrivate();
}

void XyChart::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, false);

	//_________________________________________ One buffer
	//if (_hfont) gdi.SelectFont__(_hfont);
	//OnPaintControl(gdi);

	//_________________________________________ Double buffer
	RECT rect= {0, 0, width, height};
	Win::Gdi gdiBitmap(bitmap, gdi.GetRcPaint(), false);
	if (_hfont) gdiBitmap.SelectFont__(_hfont);
	//Win::Gdi::Brush brush(_backColor);
	//gdiBitmap.FillRect(rect, brush);
	OnPaintControl(gdiBitmap);
	gdi.DrawDoubleBuffer(bitmap);
}

void XyChart::SetSubgridColor(COLORREF color)
{
	_subgridColor = color;
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

 COLORREF XyChart::GetSubgridColor()
{
	return _subgridColor;
}

// When using log scales the value cannot be less or equal to zero
void XyChart::SetMinX(double minimum)
{
	_minXUser = minimum;
	OnSizePrivate();
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

double XyChart::GetMinX()
{
	return _minXUser;
}

// When using log scale the value cannot be less or equal to zero
void XyChart::SetMaxX(double maximum)
{
	_maxXUser = maximum;
	OnSizePrivate();
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

double XyChart::GetMaxX()
{
	return _maxXUser;
}

// When using log scale the value cannot be less or equal to zero
void XyChart::SetMinY(double minimum)
{
	_minYUser = minimum;
	OnSizePrivate();
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

double XyChart::GetMinY()
{
	return _minYUser;
}

// When using log scales the value cannot be less or equal to zero
void XyChart::SetMaxY(double maximum)
{
	_maxYUser = maximum;
	OnSizePrivate();
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

double XyChart::GetMaxY()
{
	return _maxYUser;
}

void XyChart::SetDivisionCountX(int count)
{
	_divCountX = count;
	OnSizePrivate();
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

int XyChart::GetDivisionCountX()
{
	return _divCountX;
}

void XyChart::SetDivisionCountY(int count)
{
	_divCountY = count;
	OnSizePrivate();
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

int XyChart::GetDivisionCountY()
{
	return _divCountY;
}

void XyChart::SetSubDivisionCountX(int count)
{
	_subDivCountX = count;
	OnSizePrivate();
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

int XyChart::GetSubDivisionCountX()
{
	return _subDivCountX;
}

void XyChart::SetSubDivisionCountY(int count)
{
	_subDivCountY = count;
	OnSizePrivate();
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

int XyChart::GetSubDivisionCountY()
{
	return _subDivCountY;
}

void XyChart::SetCaptionX(const wstring& caption)
{
	_captionX = caption;
	RECT rc;
	rc.top = _rcMain.bottom;
	rc.bottom = height;
	rc.left = _rcMain.left;
	rc.right = _rcMain.right;
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, &rc, FALSE);
}

wstring& XyChart::GetCaptionX()
{
	return _captionX;
}

void XyChart::SetCaptionY(const wstring& caption)
{
	_captionY = caption;
	RECT rc;
	rc.top = _rcMain.top;
	rc.bottom = _rcMain.bottom;
	rc.left = 0;
	rc.right = _rcMain.left;
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, &rc, FALSE);
}

wstring& XyChart::GetCaptionY()
{
	return _captionY;
}

void XyChart::SetLogScaleX(bool logScale)
{
	_isLogX = logScale;
	this->OnSizePrivate();
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

bool XyChart::GetLogScaleX()
{
	return _isLogX;
}

void XyChart::SetLogScaleY(bool logScale)
{
	_isLogY = logScale;
	this->OnSizePrivate();
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

bool XyChart::GetLogScaleY()
{
	return _isLogY;
}

void XyChart::RefreshGraphArea()
{
	RECT rcClipping = _rcMain;
	rcClipping.bottom++;
	rcClipping.right++;
	this->OnSizePrivate();
	if (hWnd==NULL) return;
	::InvalidateRect(this->hWnd, &rcClipping, FALSE);
}

void XyChart::RefreshAll()
{
	this->OnSizePrivate();
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

void XyChart::RefreshGraphCaption()
{
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = width;
	rect.bottom = _rcMain.top;
	::InvalidateRect(this->hWnd, &rect, FALSE);
}

double XyChart::TransformFromScreenCoordinatesX(int x) 
{
	return (x - _originX)/_scaleX + _minX;
}

double XyChart::TransformFromScreenCoordinatesY(int y) 
{
	return (y - _originY)/_scaleY + _minY;
}

bool XyChart::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_COMMAND) return false;
	const int id = LOWORD(e.wParam);
	const int notificationd = HIWORD(e.wParam);
	if (id != this->id) return false;
	if (notificationd!=notification) return false;
	return true;
}

void XyChart::SetCommaSeparatedFormat(bool useCommaX, bool useCommaY)
{
	_useCommaX = useCommaX;
	_useCommaY = useCommaY;
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, false);
}

void XyChart::AutoScaleX()
{
	double minX=0.0, maxX=0.0;
	const int graphCount = Graphs.Count;
	if (graphCount == 0) return;
	if (Graphs[0].GetPointCount()<=0) return;
	int i, j, n;
	
	minX = maxX = Graphs[0][0].x;
	for(i=0; i<graphCount; i++)
	{
		n = Graphs[i].GetPointCount();
		for(j = 0; j<n; j++)
		{
			if (Graphs[i][j].x<minX) minX = Graphs[i][j].x;
			if (Graphs[i][j].x>maxX) maxX = Graphs[i][j].x;
		}
	}
	if (minX==maxX)
	{
		minX = minX- minX/2;
		maxX = maxX + maxX/2;
		if (minX==maxX)
		{
			minX = 0.0;
			maxX = 10.0;
		}
	}
	else
	{
		//double tmp = maxX-minX;
		//minX = minX- tmp/20;
		//maxX = maxX + tmp/20;
	}
	SetMinX(minX);
	SetMaxX(maxX);
}

void XyChart::AutoScaleY()
{
	double minY=0.0, maxY=0.0;
	const int graphCount = Graphs.Count;
	if (graphCount== 0) return;
	if (Graphs[0].GetPointCount()<=0) return;
	int i, j, n;

	minY = maxY = Graphs[0][0].y;
	for(i=0; i<graphCount; i++)
	{
		n = Graphs[i].GetPointCount();
		for(j = 0; j<n; j++)
		{
			if (Graphs[i][j].y<minY) minY = Graphs[i][j].y;
			if (Graphs[i][j].y>maxY) maxY = Graphs[i][j].y;
		}
	}
	//minY = maxY = graph[0].y;
	//for(int i = 1; i<n; i++)
	//{
	//	if (graph[i].x<minX) minX = graph[i].x;
	//	if (graph[i].y<minY) minY = graph[i].y;
	//	//
	//	if (graph[i].x>maxX) maxX = graph[i].x;
	//	if (graph[i].y>maxY) maxY = graph[i].y;
	//}
	if (minY==maxY)
	{
		minY = minY- minY/2;
		maxY = maxY + maxY/2;
		if (minY==maxY)
		{
			minY = 0.0;
			maxY = 10.0;
		}
	}
	else if (fabs(maxY-minY)<fabs(maxY)/10000)
	{
		minY  = 0.0;
		maxY = 1.0;
	}
	else
	{
		//double tmp = maxY-minY;
		//minY = minY- tmp/20;
		//maxY = maxY + tmp/20;
	}
	this->SetMinY(minY);
	this->SetMaxY(maxY);
}

// Default is %g for both x and y
void XyChart::SetFormat(const wchar_t* formatX, const wchar_t* formatY)
{
	if (formatX == NULL)
	{
		_formatX[0] ='\0';
	}
	else
	{
		lstrcpyn(_formatX, formatX, 8);
	}
	if (formatY == NULL)
	{
		_formatY[0] ='\0';
	}
	else
	{
		lstrcpyn(_formatY, formatY, 8);
	}

	_formatX[7]='\0';
	_formatY[7]='\0';
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

void XyChart::OnSizePrivate(void)
{
	int i, j;
	int nPointCount;

	if (_isLogX)
	{
		if (_minXUser<=0.0)
		{
			_minX = -1.0;
		}
		else
		{
			_minX = log10(_minXUser);
		}
		if (_maxXUser<=0.0)
		{
			_maxX = 1.0;
		}
		else
		{
			_maxX = log10(_maxXUser);
		}
	}
	else
	{
		_minX = _minXUser;
		_maxX = _maxXUser;	
	}

	if (_isLogY)
	{
		if (_minYUser<=0.0)
		{
			_minY = -1.0;
		}
		else
		{
			_minY = log10(_minYUser);
		}
		if (_maxYUser<=0.0)
		{
			_maxY = 1.0;
		}
		else
		{
			_maxY = log10(_maxYUser);
		}
	}
	else
	{
		_minY = _minYUser;
		_maxY = _maxYUser;
	}

	if (_printerFormat || height>WINFONT_MAXRES || width>WINFONT_MAXRES)
	{
		_boxCaptionHeight = 0.05*this->height;
	} 
	else // Display
	{
		_boxCaptionHeight = 1.5*_fontHeight; // Each row is 1.5*_fontHeight
	}

	const double offsetLeft = _boxCaptionHeight + 7.0*_boxCaptionHeight/2.0;
	const double offsetRight = 7.0 * _boxCaptionHeight/4.0;
	const double offsetTop = _boxCaptionHeight;
	const double offsetBottom = 2.0 * _boxCaptionHeight;

	//m_originX = 0.189*this->height;
	//m_originY = 0.90*this->height;
	////
	//m_scaleX = (this->width-0.270*this->height)/(m_maxX-m_minX);
	//m_scaleY =  - (0.85*this->height)/(m_maxY-m_minY);

	if (_printerFormat == true)
	{
		_originX = offsetLeft + printInfo.position.x;
		_originY = this->height-offsetBottom+printInfo.position.y;
	}
	else
	{
		_originX = offsetLeft;
		_originY = this->height-offsetBottom;
	}
	//
	_scaleX = (this->width-offsetLeft-offsetRight)/(_maxX - _minX);
	_scaleY =  - (this->height-offsetBottom-offsetTop)/(_maxY - _minY);

	POINT *pScreenPoints = NULL;
	Win::Gdi::PointF *pDataPoints = NULL;
	const int graphCount = Graphs.Count;

	for(i = 0; i<graphCount; i++)
	{
		nPointCount = Graphs[i].GetPointCount();
		pScreenPoints = Graphs[i].GetScreenPoints();
		pDataPoints = Graphs[i].GetDataPoints();
		if (pDataPoints==NULL) continue;
		for(j = 0; j<nPointCount; j++)
		{
			//************************************************ Transform X
			if (_isLogX)
			{
				if (pDataPoints[j].x>0)
					pScreenPoints[j].x= this->TransformToScreenCoordinatesX(log10(fabs(pDataPoints[j].x)));
				else
					pScreenPoints[j].x= this->TransformToScreenCoordinatesX(_originX);
			}
			else
			{
				pScreenPoints[j].x= this->TransformToScreenCoordinatesX(pDataPoints[j].x);
			}
			//************************************************ Transform Y
			if (_isLogY)
			{
				if (pDataPoints[j].y>0)
					pScreenPoints[j].y= this->TransformToScreenCoordinatesY(log10(fabs(pDataPoints[j].y)));
				else
					pScreenPoints[j].y= this->TransformToScreenCoordinatesY(_originY);
			}
			else
			{
				pScreenPoints[j].y= this->TransformToScreenCoordinatesY(pDataPoints[j].y);
			}	
		}
	}

	//if (this->bPrintting) //____________________ Clip the graph
	//{
	//	for(i = 0; i<m_nGraphCount; i++)
	//	{
	//		nPointCount = m_pGraph[i]->GetPointCount();
	//		pScreenPoints = m_pGraph[i]->GetScreenPoints();
	//		pDataPoints = m_pGraph[i]->GetDataPoints();
	//		if (pDataPoints==NULL) continue;
	//		for(j = 0; j<nPointCount; j++)
	//		{
	//			if (pScreenPoints[j].y < TransformToScreenCoordinatesY(m_maxY))
	//			{
	//				pScreenPoints[j].y = TransformToScreenCoordinatesY(m_maxY);
	//			}
	//			if (pScreenPoints[j].y > TransformToScreenCoordinatesY(m_minY))
	//			{
	//				pScreenPoints[j].y = TransformToScreenCoordinatesY(m_minY);
	//			}
	//		}
	//	}
	//}

	//********************************************************** Graph Box
	_rcMain.top = TransformToScreenCoordinatesY(_maxY);
	_rcMain.left = TransformToScreenCoordinatesX(_minX);
	_rcMain.bottom = TransformToScreenCoordinatesY(_minY);
	_rcMain.right = TransformToScreenCoordinatesX(_maxX);
}

//void XyChart::PaintFrame(Win::Gdi& gdi)
//{
//	RECT rect;
//
//	//****************************************************** Foreground top
//	rect.top = 0;
//	rect.left = 0;
//	rect.right = this->width;
//	rect.bottom = m_rcMain.top;
//	if (gdi.DoRcPaintOverlap(rect)) gdi.FillRect(&rect, (HBRUSH)(COLOR_BTNFACE+1));
//
//	//****************************************************** Foreground bottom
//	rect.top = m_rcMain.bottom;
//	rect.left = 0;
//	rect.right = this->width;
//	rect.bottom = this->height;
//	if (gdi.DoRcPaintOverlap(rect)) gdi.FillRect(&rect, (HBRUSH)(COLOR_BTNFACE+1));
//
//	//****************************************************** Foreground left
//	rect.top = m_rcMain.top;
//	rect.left = 0;
//	rect.right = m_rcMain.left;
//	rect.bottom = m_rcMain.bottom;
//	if (gdi.DoRcPaintOverlap(rect)) gdi.FillRect(&rect, (HBRUSH)(COLOR_BTNFACE+1));
//
//	//****************************************************** Foreground right
//	rect.top = m_rcMain.top;
//	rect.left = m_rcMain.right;
//	rect.right = this->width;
//	rect.bottom = m_rcMain.bottom;
//	if (gdi.DoRcPaintOverlap(rect)) gdi.FillRect(&rect, (HBRUSH)(COLOR_BTNFACE+1));
//}

void XyChart::PaintCaptionX(Win::Gdi& gdi)
{
	if (_captionX.length()>0)
	{
		RECT rect;
		int captionHeight = 0;
		if (_printerFormat == true)
		{
			captionHeight =(int)((this->height-_rcMain.bottom+printInfo.position.y)/2.0+0.5);
			rect.bottom = this->height+printInfo.position.y;
		}
		else
		{
			captionHeight =(int)((this->height-_rcMain.bottom)/2.0+0.5);
			rect.bottom = this->height;
		}
		rect.top = _rcMain.bottom+captionHeight;
		rect.left = _rcMain.left;
		rect.right = _rcMain.right;
		
		if (gdi.DoRcPaintOverlap(rect)) gdi.TextOutCenter(rect, _captionX.c_str(), true, true);
	}
}

void XyChart::PaintCaptionY(Win::Gdi& gdi)
{
	if (_captionY.length()>0)
	{
		Win::Gdi::Font fontVertical;
		RECT rect;
		SIZE size;

		rect.top = _rcMain.top;
		rect.left =0;
		rect.right = (int)(_rcMain.left/2.0+0.5);
		rect.bottom = _rcMain.bottom;
		//
		if (gdi.DoRcPaintOverlap(rect)) 
		{
			LOGFONT logfont;
			GetLogfont(logfont);
			if (fontFamilyCaptionY.length() > 0)
			{
				Sys::TextAssistant::CopyTruncate(fontFamilyCaptionY.c_str(), logfont.lfFaceName, 32);
			}

			if (_printerFormat == true)
			{
				logfont.lfHeight = -(height-_rcMain.bottom + printInfo.position.y)/3;
			}
			else if (height>WINFONT_MAXRES || width>WINFONT_MAXRES)
			{
				logfont.lfHeight = -(height-_rcMain.bottom)/3;
			}

			logfont.lfEscapement = 900;
			logfont.lfOrientation = 900;
			fontVertical.Create(logfont);
			gdi.SelectFont_(fontVertical);
			gdi.GetTextExtentPoint32(_captionY.c_str(), size);
			gdi.SetTextAlign(TA_LEFT | TA_TOP);
			gdi.TextOut(0, //(int)((_rcMain.left/2.0 - size.cy)/2.0+0.5), //0, //x
				(int)((_rcMain.bottom + _rcMain.top)/2.0 + size.cx/2.0+0.5), //y
				_captionY.c_str());
		}
	}
}

void XyChart::PaintScaleX(Win::Gdi& gdi, double deltaX)
{
	RECT rect;

	int captionHeight = 0;
	if (_printerFormat == true)
	{
		captionHeight = (int)( (this->height-_rcMain.bottom+printInfo.position.y)/2.0+0.5);
	}
	else
	{
		captionHeight = (int)( (this->height-_rcMain.bottom)/2.0+0.5);
	}
	
	rect.top = _rcMain.bottom;
	rect.left = 0;
	rect.right = this->width;
	rect.bottom = _rcMain.bottom+ captionHeight;//(int)(0.95*this->height+0.5);

	if (gdi.DoRcPaintOverlap(rect))
	{
		double value;
		const double delta = (_maxX - _minX)/(_divCountX);

		for(int i = 0; i<_divCountX+1; i++)
		{
			value = _isLogX ? pow(10.0, _minX + i * delta) : _minX + i * delta;
			this->OnPaintScaleX(gdi, i, deltaX, value);
		}
	}
}

void XyChart::PaintScaleY(Win::Gdi& gdi, double deltaY)
{
	RECT rect;

	rect.top = _rcMain.top;//-(int)(0.10*m_nHeight/3.7+0.5);
	if (_printerFormat == true)
	{
		rect.left = (int)(0.05*this->height+0.5+printInfo.position.x);
	}
	else
	{
		rect.left = (int)(0.05*this->height+0.5);
	}
	rect.right = _rcMain.left;
	rect.bottom = _rcMain.bottom;

	if (gdi.DoRcPaintOverlap(rect))
	{
		const double delta = (_maxY - _minY)/ _divCountY;
		double value;

		for(int i=0; i<_divCountY+1; i++)
		{
			value = _isLogY ? pow(10.0, _minY + i * delta) : _minY + i * delta;
			this->OnPaintScaleY(gdi, i, deltaY, value);
		}
	}
}

void XyChart::OnPaintScaleX(Win::Gdi& gdi, int index, double delta, double value)
{
	wchar_t sz[256];
	RECT rc;
	rc.top = _rcMain.bottom;
	if (_printerFormat == true)
	{
		rc.bottom = (int)(rc.top + (this->height - _rcMain.bottom + printInfo.position.y)/2.0+0.5);
	}
	else
	{
		rc.bottom = (int)(rc.top + (this->height - _rcMain.bottom)/2.0+0.5);
	}
	rc.left = (int)(_originX + index * delta - delta/2.0 + 0.5);
	rc.right = (int)(rc.left+delta+0.5);

	//int x = (int)(m_originX + index * delta + 0.5);
	//int y = (int)(m_originY+ 0.0115*this->height +0.5);
	if (_useCommaX)
	{
		Sys::Convert::ToStringCommaSeparated((int)value, sz, 256);
	}
	else
	{
		if (_formatX[0] == '\0')
		{
			Sys::Convert::ToString(value, sz, 256, true);
		}
		else
		{
			_snwprintf_s(sz, 256, _TRUNCATE, _formatX, value);
		}
	}
	gdi.TextOutCenter(rc, sz, true, true);
	//gdi.TextOutCenter(x, y, sz, true, false);
}

void XyChart::OnPaintScaleY(Win::Gdi& gdi, int index, double delta, double value)
{
	wchar_t sz[256];
	SIZE size;
	if (_useCommaY)
	{
		Sys::Convert::ToStringCommaSeparated((int)value, sz, 256);
	}
	else
	{
		if (_formatY[0] == '\0')
		{
			Sys::Convert::ToString(value, sz, 256, true);
		}
		else
		{
			_snwprintf_s(sz, 256, _TRUNCATE, _formatY, value);
		}
	}
	//gdi.GetTextMetrics(&tm);
	gdi.GetTextExtentPoint32(sz, size);
	int x = (int)(_originX-size.cx+0.5-gdi.tm.tmAveCharWidth);
	int y = (int)(_originY-index*delta-size.cy/2.0+0.5);
	gdi.TextOut(x, y, sz);
}

void XyChart::PaintDivY(Win::Gdi& gdi)
{
	const double delta = (_maxY-_minY)/_divCountY;
	double deltaSub = 0.0;
	double y = 0;
	int j=0;
	int nY = 0;

	for(double d= _minY; d< _maxY; d+=delta)
	{
		y = TransformToScreenCoordinatesY(d);
		if (d != _minY) 
		{
			nY = (int)(y+0.5);
			gdi.MoveToEx(_rcMain.left, nY); 
			gdi.LineTo( _rcMain.right-1, nY);
		}
	}
}
	
void XyChart::PaintDivX(Win::Gdi& gdi)
{
	const double delta = (_maxX - _minX)/ _divCountX;
	double deltaSub = 0.0;
	double x = 0;
	int j=0;
	int nX = 0;

	for(double d= _minX; d < _maxX; d += delta)
	{
		x = TransformToScreenCoordinatesX(d);
		if (d !=  _minX) 
		{
			nX = (int)(x+0.5);
			gdi.MoveToEx(nX, _rcMain.top); 
			gdi.LineTo(nX,  _rcMain.bottom-1);
		}
	}
}

void XyChart::PaintSubDivY(Win::Gdi& gdi)
{
	const double delta = (_maxY - _minY)/ _divCountY;
	double deltaSub = 0.0;
	double y = 0;
	int j=0;
	int nY = 0;

	for(double d= _minY; d < _maxY; d += delta)
	{
		y = TransformToScreenCoordinatesY(d);	
		if (_isLogY) 
		{
			deltaSub = 9.0/_subDivCountY;
			for(j = 1; j<_subDivCountY; j++)
			{
				nY = (int)(y+ (delta * _scaleY)* log10(1.0+j*deltaSub) + 0.5);
				if (nY <= _rcMain.top) continue;
				if (nY >= _rcMain.bottom) continue; 
				gdi.MoveToEx(_rcMain.left, nY); 
				gdi.LineTo(_rcMain.right-1, nY);
			}	
		}
		else
		{
			deltaSub = _scaleY*delta/ _subDivCountY;
			for(j = 1; j < _subDivCountY; j++)
			{
				nY = (int)(y+ j*deltaSub+0.5);
				if (nY>_rcMain.top && nY<_rcMain.bottom)
				{
					gdi.MoveToEx(_rcMain.left, nY); 
					gdi.LineTo(_rcMain.right-1, nY);
				}
			}
		}
	}
}
	
void XyChart::PaintSubDivX(Win::Gdi& gdi)
{
	const double delta = (_maxX - _minX)/ _divCountX;
	double deltaSub = 0.0;
	double x = 0;
	int j=0;
	int nX = 0;

	for(double d = _minX; d < _maxX; d += delta)
	{
		x = TransformToScreenCoordinatesX(d);
		if (_isLogX)
		{
			deltaSub = 9.0/_subDivCountX;
			for(j = 1; j<_subDivCountX; j++)
			{
				nX = (int)(x+ (delta*_scaleX)* log10(1.0+j*deltaSub) + 0.5);
				if (nX <= _rcMain.left) continue;
				if (nX >= _rcMain.right) continue; 
				gdi.MoveToEx(nX, _rcMain.top); 
				gdi.LineTo(nX, _rcMain.bottom-1);
			}	
		}
		else
		{
			deltaSub = _scaleX*delta/_subDivCountX;
			for(j = 1; j < _subDivCountX; j++)
			{
				nX = (int)(x+j*deltaSub+0.5);
				if (nX>_rcMain.left && nX<_rcMain.right)
				{
					gdi.MoveToEx(nX, _rcMain.top); 
					gdi.LineTo(nX, _rcMain.bottom-1);
				}
			}
		}
	}
}


void XyChart::PaintGraphs(Win::Gdi& gdi)
{
	int i = 0;
	//Win::Gdi::Color3D color3D(bPrintting? RGB(220, 220, 220) : RGB(128, 128, 128));
	//Win::Gdi::Brush brocha(RGB(20, 20, 20));
	wchar_t *pszCaption = NULL;
	SIZE size;
	RECT rect;

	rect.top = 0;
	rect.left = 0;
	rect.right = this->width;
	rect.bottom = _rcMain.top;

	const int space = (int)(0.10*this->height/4.4+0.5);

	//******** Find graph caption width
	int nCaptionWidth = 0;
	const int graphCount = Graphs.Count;
	for(i = 0; i<graphCount; i++)
	{
		pszCaption = (wchar_t*)Graphs[i].GetCaption();
		if (pszCaption) 
		{
			gdi.GetTextExtentPoint32(pszCaption, size);
			nCaptionWidth+= (int)(size.cx+2*space);
		}
	}

	//_____________________________________________________Draw graph caption	
	int xCaption = _rcMain.left +  space + (int)((_rcMain.right - _rcMain.left +1 - nCaptionWidth)/2 + 0.5);
	//int yCaption = 0;//(LONG)((int)(0.10*this->height/3.7+0.5)*0.35);
	pszCaption = NULL;
	gdi.SetBkMode(true);
	//rect.top = yCaption;

	gdi.SetTextAlign(TA_LEFT | TA_BOTTOM);


	for(i = 0; i<graphCount; i++)
	{
		pszCaption = (wchar_t*)Graphs[i].GetCaption();
		gdi.SetTextColor(Graphs[i].color);
		if (pszCaption) 
		{
			gdi.GetTextExtentPoint32(pszCaption, size);
			if (_printerFormat == true)
			{
				//_originX = offsetLeft + printInfo.position.x;
				//_originY = this->height-offsetBottom+printInfo.position.y;
				gdi.TextOut(xCaption, (int)(_rcMain.top-0.12*_fontHeight), pszCaption);
			}
			else
			{
				gdi.TextOut(xCaption, (int)(_rcMain.top-0.12*_fontHeight), pszCaption);
			}
			xCaption+=(int)(size.cx + 2*space);
		}
	}
	gdi.SetTextAlign(TA_LEFT | TA_TOP);
	//************************************* Draw Graphs
	RECT rcClipping = _rcMain;
	rcClipping.top--;
	rcClipping.bottom++;
	rcClipping.right++;
	HRGN hRgn = CreateRectRgnIndirect(&rcClipping);
	Win::Gdi::Pen penGraph;
	if (!_printerFormat) gdi.SelectClipRgn(hRgn);
	for(i = 0; i<graphCount; i++)
	{
		penGraph.Create(PS_SOLID, _printerFormat ? WINXYCHART_PRINTERPENGRAPH : Graphs[i].penWidth, Graphs[i].color);
			//_printerFormat ? RGB(0, 0, 0) : Graphs[i].color);
		gdi.SelectPen_(penGraph);
		this->DrawGraph(gdi, i);
		//pszCaption = (wchar_t*)this->m_pGraph[i]->GetCaption();
		//gdi.SetTextColor(this->m_pGraph[i]->color);
	}
	if (!_printerFormat) gdi.SelectClipRgn(NULL);
	DeleteObject(hRgn);
}

void XyChart::DrawGraph(Win::Gdi& gdi, int graphIndex)
{
	Win::Graph& graph = Graphs[graphIndex];
	int i = 0;
	POINT * p = graph.GetScreenPoints();
	const int pointCount = graph.GetPointCount();
	if (pointCount==0) return;
	int dimension = (int)(((int)(0.10*this->height/3.7+0.5))/4.0 + 0.5);
	

	switch(graph.GetType())
	{
	case Win::Graph::circle:
			for(i = 0; i<pointCount; i++) gdi.Circle(p[i].x, p[i].y, dimension);
		break;
	case Win::Graph::cross:
		for(i = 0; i<pointCount; i++)
		{
			gdi.MoveToEx(p[i].x, (int)(p[i].y-dimension));
			gdi.LineTo(p[i].x, (int)(p[i].y+dimension+1));
			gdi.MoveToEx((int)(p[i].x-dimension), p[i].y);
			gdi.LineTo((int)(p[i].x+dimension+1), p[i].y);
		}
		break;
	case Win::Graph::dot:
		for(i = 0; i<pointCount; i++)
		{
			gdi.SetPixel(p[i].x, p[i].y, graph.color);
		}
		break;
	case Win::Graph::square:
		for(i = 0; i<pointCount; i++)
		{
			gdi.Rectangle(p[i].x-dimension, p[i].y-dimension,
				p[i].x+dimension+1, p[i].y+dimension+1);
		}
		break;
	case Win::Graph::line:
		gdi.Polyline(graph.GetScreenPoints(), pointCount);
		break;
	case Win::Graph::histogram:
		{
			const int yzero = _rcMain.bottom-1;
			for(i = 0; i<pointCount; i++)
			{
				gdi.Line(p[i].x, yzero, p[i].x, p[i].y);
			}
		}
		break;
	case Win::Graph::impulse:
		{
			const int yzero = TransformToScreenCoordinatesY(0.0);
			int lineLength;
			for(i = 0; i<pointCount; i++)
			{
				if (p[i].y > yzero)
				{
					lineLength = (p[i].y-dimension) - yzero;
					if (abs(lineLength)>dimension)
					{
						gdi.Line(p[i].x, yzero, p[i].x, p[i].y-dimension);
					}
				}
				else
				{
					lineLength = (p[i].y+dimension) - yzero;
					if (abs(lineLength)>dimension)
					{
						gdi.Line(p[i].x, yzero, p[i].x, p[i].y+dimension);
					}
				}
				gdi.Circle(p[i].x, p[i].y, dimension);
			}
		}
		break;
	case Win::Graph::number:
		{
			SIZE size;
			wchar_t text[32];
			COLORREF initialColor = gdi.SetTextColor(graph.color);
			for(i = 0; i<pointCount; i++)
			{
				_snwprintf_s(text, 32, _TRUNCATE, L"%d", i);
				gdi.GetTextExtentPoint32(text, size);
				gdi.TextOut(p[i].x-size.cx/2, p[i].y-size.cy/2, text);
			}
			gdi.SetTextColor(initialColor);
		}
		break;
	}
}

//IExportable
void XyChart::OnPaintControl(Win::Gdi& gdi)
{
	const double deltaX = (_rcMain.right-_rcMain.left)/(double)_divCountX;
	const double deltaY = (_rcMain.bottom-_rcMain.top)/(double)_divCountY;
	Win::Gdi::Pen penDiv(PS_SOLID, _printerFormat ? WINXYCHART_PRINTERPEN : 1, _lineColor);
	Win::Gdi::Pen penSubDiv(PS_SOLID, _printerFormat ? WINXYCHART_PRINTERPEN : 1,  _subgridColor);

	//_____________________________________________ Font
	Win::Gdi::Font font;
	const bool metafileFormat = (height>WINFONT_MAXRES || width>WINFONT_MAXRES);

	LOGFONT logFont;
	this->GetLogfont(logFont);
	const int fontHeight = abs(logFont.lfHeight);

	Win::Gdi::Font fontSymbol;
	if (_symbolCaptionX == true || _symbolCaptionY == true)
	{
		fontSymbol.Create(L"Symbol", fontHeight, false, false, false);
	}
	
	if (_printerFormat == true)
	{
		//LOGFONT logfont;
		//this->GetLogfont(logfont);
		logFont.lfHeight = -( (height +printInfo.position.y) -_rcMain.bottom)/3;
		font.Create(logFont);
		gdi.SelectFont_(font);
		//
		_snwprintf_s(logFont.lfFaceName, LF_FACESIZE, _TRUNCATE, L"Symbol");
		fontSymbol.Create(logFont);
	}
	else if (metafileFormat)
	{
		//LOGFONT logfont;
		//this->GetLogfont(logfont);
		logFont.lfHeight = -(height-_rcMain.bottom)/3;
		font.Create(logFont);
		gdi.SelectFont_(font);
		//
		_snwprintf_s(logFont.lfFaceName, LF_FACESIZE, _TRUNCATE, L"Symbol");
		fontSymbol.Create(logFont);
	}
	else
	{
		if (_hfont) gdi.SelectFont__(_hfont);
	}

	if (_printerFormat)
	{
		gdi.SetTextColor(_textColor);
		gdi.SetBkColor(RGB(255, 255, 255)); //_backColor);
	}
	else
	{
		if (this->Enabled)
		{
			gdi.SetTextColor(_textColor);
		}
		else
		{
			gdi.SetTextColor(WIN_TEXT_DISABLED);
		}
		gdi.SetBkMode(true);
		Win::Gdi::Brush brushBackground;
		RECT rect = gdi.GetRcPaint();
		if (this->Enabled)
		{
			brushBackground.CreateSolid(_backColor);
		}
		else
		{
			brushBackground.CreateSolid(WIN_BACK_DISABLED);
		}
		//gdi.SelectBrush_(brushBackground);
		gdi.FillRect(rect, brushBackground);
	}
	
	//_________________________________________________ Caption Y
	if (_symbolCaptionY == true)
	{
		gdi.SelectFont_(fontSymbol);
	}
	else
	{
		if (_printerFormat == true)
		{
			gdi.SelectFont_(font);
		}
		else if (metafileFormat)
		{
			gdi.SelectFont_(font);
		}
		else
		{
			if (_hfont) gdi.SelectFont__(_hfont);
		}
	}
	this->PaintCaptionY(gdi);

	//_________________________________________________ Caption X
	if (_symbolCaptionX == true)
	{
		gdi.SelectFont_(fontSymbol);
	}
	else
	{
		if (_printerFormat == true)
		{
			gdi.SelectFont_(font);
		}
		else if (metafileFormat)
		{
			gdi.SelectFont_(font);
		}
		else
		{
			if (_hfont) gdi.SelectFont__(_hfont);
		}
	}
	this->PaintCaptionX(gdi);

	
	//___________________________________________ Restore Font
	if (_printerFormat == true)
	{
		gdi.SelectFont_(font);
	}
	else if (metafileFormat)
	{
		gdi.SelectFont_(font);
	}
	else
	{
		if (_hfont) gdi.SelectFont__(_hfont);
	}
	this->PaintScaleX(gdi, deltaX);
	this->PaintScaleY(gdi, deltaY);
	if (gdi.DoRcPaintOverlap(_rcMain))
	{
		if (_showGrid == true)
		{
			gdi.SelectPen_(penSubDiv);
			this->PaintSubDivX(gdi);
			this->PaintSubDivY(gdi);
			gdi.SelectPen_(penDiv);
			this->PaintDivX(gdi);
			this->PaintDivY(gdi);
		}
		Win::Gdi::Pen penBlack(PS_SOLID, _printerFormat ? WINXYCHART_PRINTERPEN : 1, _textColor);
		gdi.SelectPen_(penBlack);
		gdi.SelectBrush__((HBRUSH)GetStockObject(NULL_BRUSH));
		gdi.Rectangle(_rcMain.left, _rcMain.top, _rcMain.right+1, _rcMain.bottom+1);
		this->PaintGraphs(gdi);
	}
}

// If uses the Symbol Font for caption X or caption Y
void XyChart::SetSymbolCaption(bool captionX, bool captionY)
{
	RECT rc;
	if (_symbolCaptionX != captionX)
	{
		_symbolCaptionX = captionX;
		//
		rc.top = _rcMain.bottom;
		rc.bottom = height;
		rc.left = _rcMain.left;
		rc.right = _rcMain.right;
		if (hWnd==NULL) return;
		::InvalidateRect(hWnd, &rc, FALSE);
	}

	if (_symbolCaptionY != captionY)
	{
		_symbolCaptionY = captionY;
		rc.top = _rcMain.top;
		rc.bottom = _rcMain.bottom;
		rc.left = 0;
		rc.right = _rcMain.left;
		if (hWnd==NULL) return;
		::InvalidateRect(hWnd, &rc, FALSE);		
	}
}

//_____________________________________________________________________ PolarChart
PolarChart::PolarChart(void)
{
	_scale = 1.0;
	_centerX = 100.0;
	_centerY = 100.0;
	_maxRadius = 1.0;
	_minRadius = 0.0;
	//
	//_lineColor = RGB(170, 170, 180);
	//_subgridColor = RGB(220, 220, 240);
	
	_lineColor = RGB(225, 225, 255);
	_subgridColor = RGB(245, 245, 245);

	_subgrid = true;
}

PolarChart::~PolarChart(void)
{
}

void PolarChart::Window_Open(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
}

void PolarChart::Window_Size(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
	OnSizePrivate();
}

void PolarChart::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, false);
	Win::Gdi gdiBitmap(bitmap, gdi.GetRcPaint(), false);
	if (_hfont) gdiBitmap.SelectFont__(_hfont);
	OnPaintControl(gdiBitmap);
	gdi.DrawDoubleBuffer(bitmap);
}

void PolarChart::Refresh()
{
	this->OnSizePrivate();
	if (hWnd) ::InvalidateRect(this->hWnd, NULL, TRUE);
}

void PolarChart::SetSubgridColor(COLORREF color)
{
	_subgridColor = color;
	if (hWnd) ::InvalidateRect(hWnd, NULL, false);
}

COLORREF PolarChart::GetSubgridColor()
{
	return _subgridColor;
}

// returns the next point index
int PolarChart::Line(Win::Gdi& gdi, double angle, int index, POINT* points)
{
	angle = M_PI*angle/180.0;
	const double radius = _maxRadius - _minRadius;
	const double x = radius* _scale*cos(angle);
	const double y = radius* _scale*sin(angle);
	points[index].x = (int)(_centerX-x+0.5);
	points[index].y = (int)(_centerY-y+0.5);
	index++;
	//
	points[index].x = (int)(_centerX+x+0.5);
	points[index].y = (int)(_centerY+y-0.5);
	index++;
	//
	points[index].x = (int)(_centerX-x+0.5);
	points[index].y = (int)(_centerY+y+0.5);
	index++;
	//
	points[index].x = (int)(_centerX+x+0.5);
	points[index].y = (int)(_centerY-y-0.5);
	index++;
	return index;
}

// returns the next point index
int PolarChart::ShortLine(Win::Gdi& gdi, double angle, int index, POINT* points)
{
	angle = M_PI*angle/180.0;
	const double radius = _maxRadius - _minRadius;
	const double x = radius* _scale*cos(angle);
	const double y = radius* _scale*sin(angle);
	const double lengthX = 2.0* _scale*cos(angle)*radius/5.0;
	const double lengthY = 2.0* _scale*sin(angle)*radius/5.0;
	points[index].x = (int)(_centerX-x+0.5);
	points[index].y = (int)(_centerY-y+0.5);
	index++;
	//
	points[index].x = (int)(_centerX-lengthX+0.5);
	points[index].y = (int)(_centerY-lengthY-0.5);
	index++;
	//
	points[index].x = (int)(_centerX+lengthX+0.5);
	points[index].y = (int)(_centerY+lengthY+0.5);
	index++;
	//
	points[index].x = (int)(_centerX+x+0.5);
	points[index].y = (int)(_centerY+y-0.5);
	index++;
	//
	points[index].x = (int)(_centerX-x+0.5);
	points[index].y = (int)(_centerY+y+0.5);
	index++;
	//
	points[index].x = (int)(_centerX-lengthX+0.5);
	points[index].y = (int)(_centerY+lengthY-0.5);
	index++;
	//
	points[index].x = (int)(_centerX+lengthX+0.5);
	points[index].y = (int)(_centerY-lengthY+0.5);
	index++;
	//
	points[index].x = (int)(_centerX+x+0.5);
	points[index].y = (int)(_centerY-y-0.5);
	index++;
	//
	return index;
	//gdi.Line((int)(centerX-x+0.5), (int)(centerY-y+0.5), (int)(centerX-lengthX+0.5), (int)(centerY-lengthY-0.5));
	//gdi.Line((int)(centerX+lengthX+0.5), (int)(centerY+lengthY+0.5), (int)(centerX+x+0.5), (int)(centerY+y-0.5));
	////
	//gdi.Line((int)(centerX-x+0.5), (int)(centerY+y+0.5), (int)(centerX-lengthX+0.5), (int)(centerY+lengthY-0.5));
	//gdi.Line((int)(centerX+lengthX+0.5), (int)(centerY-lengthY+0.5), (int)(centerX+x+0.5), (int)(centerY-y-0.5));
}

void PolarChart::ShowSubgrid(bool subgrid)
{
	_subgrid = subgrid;
	if (hWnd) ::InvalidateRect(hWnd, NULL, true);
}

void PolarChart::OnPaintControl(Win::Gdi& gdi)
{
	wchar_t texto[64];
	int i, index=0;
	const int markCount = 10;
	POINT point[48];
	DWORD pointInfo[48];
	for(i=0; i<40; i++) pointInfo[i]=2;
	Win::Gdi::Pen penSubgrid(PS_SOLID, 1, _subgridColor);
	const double radius = _maxRadius - _minRadius;
	//const int deltaMark = markCount*scale;
	const RECT rcPaint = gdi.GetRcPaint();

	//_____________________________________________ Font
	Win::Gdi::Font font;
	
	if (_printerFormat || height>WINFONT_MAXRES || width>WINFONT_MAXRES)
	{
		LOGFONT logfont;
		this->GetLogfont(logfont);
		logfont.lfHeight = -(MINIMUM(width, height)/25);
		font.Create(logfont);
		gdi.SelectFont_(font);
	}
	else
	{
		if (_hfont) gdi.SelectFont__(_hfont);
	}

	//_____________________________________________ Line
	Win::Gdi::Pen penGrid;
	if (_printerFormat)
	{
		penGrid.Create(PS_SOLID, WINXYCHART_PRINTERPEN, _lineColor);
	}
	else
	{
		penGrid.Create(PS_SOLID, 1, _lineColor);
	}


	//____________________________ Text
	if (this->Enabled)
	{
		if (_printerFormat == true)
		{
			gdi.SetBkColor(RGB(255, 255, 255));
			gdi.SetTextColor(_textColor);
		}
		else
		{
			gdi.SetBkColor(_backColor);
			gdi.SetTextColor(_textColor);
		}
	}
	else
	{
		gdi.SetBkColor(WIN_BACK_DISABLED);
		gdi.SetTextColor(WIN_TEXT_DISABLED);
	}

	//_______________________________________________________ Background
	Win::Gdi::Brush brushBackground;
	if (_printerFormat==false)//gdi.DoRcPaintOverlap(m_box) && )
	{
		if (this->Enabled)
		{
			brushBackground.CreateSolid(_backColor);
		}
		else
		{
			brushBackground.CreateSolid(WIN_BACK_DISABLED);
		}
		gdi.SelectBrush_(brushBackground);
		gdi.FillRect(rcPaint, brushBackground);
	}

	gdi.SelectBrush__((HBRUSH)::GetStockObject(NULL_BRUSH));

	//___________________________________________________ Sub Grid
	if (_subgrid)
	{
		index = 0;
		gdi.SelectPen_(penSubgrid);
		for(i=1; i<=markCount; i+=2) gdi.Circle((int)_centerX, (int)_centerY, (int)(i*radius* _scale/markCount+0.5));
		index = ShortLine(gdi, 10.0, index, point);
		index = ShortLine(gdi, 20.0, index, point);
		index = ShortLine(gdi, 40.0, index, point);
		index = ShortLine(gdi, 50.0, index, point);
		index = ShortLine(gdi, 70.0, index, point);
		index = ShortLine(gdi, 80.0, index, point);
		gdi.PolyPolyline(point, pointInfo, index/2);
	}

	//__________________________________________________ Grid
	gdi.SelectPen_(penGrid);
	for(i=2; i<=markCount; i+=2) gdi.Circle((int)_centerX, (int)_centerY, (int)(i*radius*_scale/markCount+0.5));
	index = 0;
	point[index].x =(int)(_centerX-radius* _scale+0.5);
	point[index].y =(int)(_centerY+0.5);
	index++;
	//
	point[index].x =(int)(_centerX+radius* _scale+0.5);
	point[index].y =(int)(_centerY+0.5);
	index++;
	//
	point[index].x =(int)(_centerX+0.5);
	point[index].y =(int)(_centerY-radius* _scale+0.5);
	index++;
	//
	point[index].x =(int)(_centerX+0.5);
	point[index].y =(int)(_centerY+radius* _scale+0.5);
	index++;

	index = Line(gdi, 30.0, index, point);
	index = Line(gdi, 60.0, index, point);
	gdi.PolyPolyline(point, pointInfo, index/2);

	//_______________________________________________________________ Paint Window Text
	if (_text.length()>0)
	{
		if (_printerFormat == true)
		{
			gdi.TextOut((int)(_centerX - radius*_scale -_fontHeight*2), _fontHeight/4+printInfo.position.y, _text.c_str());
		}
		else
		{
			gdi.TextOut(_fontHeight/2, _fontHeight/4, _text.c_str());
		}
	}
	//_______________________________________________________________ Paint Scale

	POINT position;
	const double cosp = cos(45.0*M_PI/180.0);
	const double sinp = sin(45.0*M_PI/180.0);
	for(i=2; i<=markCount; i+=2) 
	{
		position.x = (int)(_centerX+i*sinp*radius* _scale/markCount+0.5);
		position.y = (int)(_centerY+i*cosp*radius* _scale/markCount+0.5);
		OnPaintScaleR(gdi, position, _minRadius+i*radius/markCount);
	}
	//
	double tetha = 0;
	for(i=0; i<12; i++)
	{
		//if (i==9) continue; // skip 270
		tetha = i *(2*M_PI)/12;
		_snwprintf_s(texto, 64, _TRUNCATE, L"%d", i*30);
		gdi.TextOutCenter((int)(radius* _scale*cos(tetha)+ _centerX+0.5),
			(int)(-radius* _scale*sin(tetha)+ _centerY+0.5), texto, true, true);
	}
	this->PaintGraphs(gdi);
}

void PolarChart::OnPaintScaleR(Win::Gdi& gdi, POINT center, double value)
{
	wchar_t texto[64];
	Sys::Convert::ToString(value, texto, 64, true);
	//_snwprintf_s(texto, 64, _TRUNCATE, L"%g", value);
	gdi.TextOutCenter(center.x, center.y, texto, true, true);
}

void PolarChart::PaintGraphs(Win::Gdi& gdi)
{
	//************************************* Draw Graphs
	//HRGN hRgn = CreateRectRgnIndirect(&this->m_rcMain);
	Win::Gdi::Pen penGraph;
	//if (!bPrintting) gdi.SelectClipRgn(hRgn);
	int pointCount = 0;
	const int graphCount = Graphs.GetCount();
	for(int i = 0; i<graphCount; i++)
	{
		penGraph.Create(PS_SOLID, _printerFormat ? WINXYCHART_PRINTERPENGRAPH : Graphs[i].penWidth, Graphs[i].color);
			//_printerFormat ? RGB(0, 0, 0) : Graphs[i].color);
		gdi.SelectPen_(penGraph);
		this->DrawGraph(gdi, i);
	}
	//DeleteObject(hRgn);
}

void PolarChart::DrawGraph(Win::Gdi& gdi, int graphIndex)
{
	//Win::Graph* graph = pGraph[graphIndex];
	int i = 0;
	const int pointCount = Graphs[graphIndex].GetPointCount();
	POINT * p = Graphs[graphIndex].GetScreenPoints();
	if (pointCount==0) return;
	int dimension = (int)(((int)(0.10*this->height/3.7+0.5))/4.0 + 0.5);

	switch(Graphs[graphIndex].GetType())
	{
	case Win::Graph::circle:
			for(i = 0; i<pointCount; i++) gdi.Circle(p[i].x, p[i].y, dimension);
		break;
	case Win::Graph::cross:
		for(i = 0; i<pointCount; i++)
		{
			gdi.MoveToEx(p[i].x, (int)(p[i].y-dimension));
			gdi.LineTo(p[i].x, (int)(p[i].y+dimension+1));
			gdi.MoveToEx((int)(p[i].x-dimension), p[i].y);
			gdi.LineTo((int)(p[i].x+dimension+1), p[i].y);
		}
		break;
	case Win::Graph::dot:
		for(i = 0; i<pointCount; i++)
		{
			gdi.SetPixel(p[i].x, p[i].y, Graphs[graphIndex].color);
		}
		break;
	case Win::Graph::square:
		for(i = 0; i<pointCount; i++)
		{
			gdi.Rectangle(p[i].x-dimension-1, p[i].y-dimension-1,
				p[i].x+dimension, p[i].y+dimension);
		}
		break;
	case Win::Graph::line:
		//gdi.Polyline(pGraph[i]->GetScreenPoints(), (int)pGraph[i]->GetPointCount());
		gdi.Polyline(Graphs[graphIndex].GetScreenPoints(), pointCount);
		break;
	}
}

void PolarChart::AutoScaleRadius()
{
	double minR=0.0, maxR=0.0;
	const int graphCount = Graphs.Count;
	if (graphCount == 0) return;
	if (Graphs[0].GetPointCount()<=0) return;
	int i, j, n;
	
	minR = maxR = Graphs[0][0].y;
	for(i=0; i<graphCount; i++)
	{
		n = Graphs[i].GetPointCount();
		for(j = 0; j<n; j++)
		{
			if (Graphs[i][j].y<minR) minR = Graphs[i][j].y;
			if (Graphs[i][j].y>maxR) maxR = Graphs[i][j].y;
		}
	}
	SetRadius(minR, maxR);
}

void PolarChart::SetRadius(double minimum, double maximum)
{
	_minRadius = minimum;
	_maxRadius = maximum;
	this->OnSizePrivate();
	if (hWnd) ::InvalidateRect(hWnd, NULL, false);
}

void PolarChart::OnSizePrivate(void)
{
	const int max_r = (int)((MINIMUM(this->width, this->height))/2.1);
	if (_printerFormat == true)
	{
		_centerX = this->width/2 + printInfo.position.x;
		_centerY = this->height/2 + printInfo.position.y;
	}
	else
	{
		_centerX = this->width/2;
		_centerY = this->height/2;
	}
	int i, j;
	int nPointCount;
	
	//double maxRData=0.0, tmp;
	////___________________________________________________ Find an appropiate scale
	//for(i = 0; i<graphCount; i++)
	//{
	//	tmp = pGraph[i]->GetMaxX();
	//	if (maxRData<tmp) maxRData = tmp;
	//}
	_scale = max_r/(_maxRadius - _minRadius);

	POINT *pScreenPoints = NULL;
	Win::Gdi::PointF *pDataPoints = NULL;
	const int graphCount = Graphs.GetCount();
	for(i = 0; i<graphCount; i++)
	{
		nPointCount = Graphs[i].GetPointCount();
		pScreenPoints = Graphs[i].GetScreenPoints();
		pDataPoints = Graphs[i].GetDataPoints();
		if (pDataPoints==NULL) continue;
		for(j = 0; j<nPointCount; j++)
		{
			pScreenPoints[j].x= this->TransformToScreenCoordinatesX(pDataPoints[j].x, pDataPoints[j].y);
			pScreenPoints[j].y= this->TransformToScreenCoordinatesY(pDataPoints[j].x, pDataPoints[j].y);
		}
		//pScreenPoints[nPointCount] =  pScreenPoints[0]; // Close the graph
	}
}

//_____________________________________________________________________ View3D
bool View3D::_bRegistered= false;

View3D::View3D(void)
{
	if (!_bRegistered)
	{
		this->RegisterClassEx(LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(NULL_BRUSH));
		_bRegistered = true;
	}
	_axisLength = 150.0;
	_angle=0.0;
	_sinAngle = sin(_angle);
	_cosAngle = cos(_angle);
	_zoom=1.0;
	_centerX=0.0;
	_centerY=0.0;
	_perspective = (float)(30.0*M_PI/180.0);
	_cosPerspective = (float)cos(_perspective);
	_sinPerspective = (float)sin(_perspective);
	_deltaWheelPerLine= 0;
	_accumWheelDelta = 0;
	_hasFocus = false;
	_showBox = false;
	_lbuttonDown = false;
	_hWndParent = NULL;
	_backColor = RGB(250, 250, 250);
	_backColorx = RGB(250, 250, 250);
	_lineColor = RGB(240, 240, 250);
	_textColor = RGB(220, 220, 250);
	_hfont = NULL;

#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
	//************************************************* Get Mouse Wheel Info
	ULONG ulScrollLines;
	SystemParametersInfo (SPI_GETWHEELSCROLLLINES, 0, &ulScrollLines, 0);         
// ulScrollLines usually equals 3 or 0 (for no scrolling)
// WHEEL_DELTA equals 120, so iDeltaPerLine will be 40

	if (ulScrollLines)
		_deltaWheelPerLine = WHEEL_DELTA / ulScrollLines;
	else
		_deltaWheelPerLine = 0;
#endif
	_hCursor = NULL;

	_minX = -10.0;
	_maxX = 10.0;
	_minY = -10.0;
	_maxY = 10.0;
	_minZ = 0.0;
	_maxZ = 10.0;
	_divCountX = 5;
	_divCountY = 5;
	_divCountZ = 3;
}

View3D::~View3D(void)
{
	if (_hCursor)
	{
		::SetCursor(_hCursor);
		::ShowCursor(TRUE);
     }
}

void View3D::SetPerspective(double angleDegrees)
{
	_perspective = (float)(angleDegrees*M_PI/180.0);
	_sinPerspective = sin(_perspective);
	_cosPerspective = cos(_perspective);
	::InvalidateRect(hWnd, NULL, TRUE);
}

double View3D::GetPerspective(void)
{
	return _perspective*180.0/M_PI;
}

void View3D::SetMinX(double minimum)
{
	if (_minX == minimum) return;
	_minX = minimum;
	::InvalidateRect(hWnd, NULL, TRUE);
}

double View3D::GetMinX()
{
	return _minX;
}

void View3D::SetMaxX(double maximum)
{
	if (_maxX == maximum) return;
	_maxX = maximum;
	::InvalidateRect(hWnd, NULL, TRUE);
}

double View3D::GetMaxX()
{
	return _maxX;
}

void View3D::SetMinY(double minimum)
{
	if (_minY== minimum) return;
	_minY = minimum;
	::InvalidateRect(hWnd, NULL, TRUE);
}

double View3D::GetMinY()
{
	return _minY;
}

void View3D::SetMaxY(double maximum)
{
	if (_maxY == maximum) return;
	_maxY = maximum;
	::InvalidateRect(hWnd, NULL, TRUE);
}

double View3D::GetMaxY()
{
	return _maxY;
}

void View3D::SetMinZ(double minimum)
{
	if (_minZ == minimum) return;
	_minZ = minimum;
	::InvalidateRect(hWnd, NULL, TRUE);
}

double View3D::GetMinZ()
{
	return _minZ;
}

void View3D::SetMaxZ(double maximum)
{
	if (_maxZ == maximum) return;
	_maxZ = maximum;
	::InvalidateRect(hWnd, NULL, TRUE);
}

double View3D::GetMaxZ()
{
	return _maxZ;
}

void View3D::SetDivisionCountX(int count)
{
	if (_divCountX == count) return;
	if (count > WIN_VIEWER3D_MAX_DIV || count < 0) return;
	_divCountX = count;
	::InvalidateRect(hWnd, NULL, TRUE);
}

int View3D::GetDivisionCountX()
{
	return _divCountX;
}

void View3D::SetDivisionCountY(int count)
{
	if (_divCountY == count) return;
	if (count > WIN_VIEWER3D_MAX_DIV || count < 0) return;
	_divCountY = count;
	::InvalidateRect(hWnd, NULL, TRUE);
}

int View3D::GetDivisionCountY()
{
	return _divCountY;
}

void View3D::SetDivisionCountZ(int count)
{
	if (_divCountZ == count) return;
	if (count > WIN_VIEWER3D_MAX_DIV || count < 0) return;
	_divCountZ = count;
	::InvalidateRect(hWnd, NULL, TRUE);
}

int View3D::GetDivisionCountZ()
{
	return _divCountZ;
}

void View3D::SetShowBox(bool showBox)
{
	this->_showBox = showBox;
	::InvalidateRect(hWnd, NULL, TRUE);
}

bool View3D::GetShowBox(void)
{
	return _showBox;
}

bool View3D::CopyToClipboard()
{
	return Win::Exporter::CopyToClipboard(*this);
}

void View3D::Window_GetDlgCode(Win::Event& e)
{
	e.returnValue = DLGC_WANTARROWS;
}

void View3D::ResetView(bool resetZoom)
{
	SetAngle(0.0);
	if (resetZoom) SetZoom(1.0);
	_centerX=(float)(this->width/2.0);
	_centerY=(float)(this->height/2.0);
	::InvalidateRect(hWnd, NULL, true);
}

void View3D::SetFont(Win::Gdi::Font& font)
{
	_hfont = font.GetHFONT();
	//LOGFONT logfont;
	//this->GetLogfont(logfont);
	//_fontHeight = abs(logfont.lfHeight);
	//this->OnSizePrivate();
	if (hWnd == NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

COLORREF View3D::GetBackColor()
{
	return _backColor;
}

void View3D::SetBackColor(COLORREF color)
{
	if (_backColor == color) return;
	//
	_backColorx = RGBX(GetRValue(color), GetGValue(color), GetBValue(color));
	//
	_backColor = color;
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

COLORREF View3D::GetLineColor()
{
	return _lineColor;
}

void View3D::SetLineColor(COLORREF color)
{
	if (_lineColor == color) return;
	_lineColor = color;
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

COLORREF View3D::GetTextColor()
{
	return _textColor;
}

void View3D::SetTextColor(COLORREF color)
{
	if (_textColor == color) return;
	_textColor = color;
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

bool View3D::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_COMMAND) return false;
	const int id = LOWORD(e.wParam);
	const int notificationd = HIWORD(e.wParam);
	if (id != this->id) return false;
	if (notificationd!=notification) return false;
	return true;
}

void View3D::Print(Win::Gdi& gdi, Win::PrintInfo pi)
{
	int widthScreen; 
	int heightScreen; 

	//RECT rect = {0, 0, width, height}; 
	//gdi.Rectangle(&rect);

	gdi.SetTextColor(RGB(0, 0, 0));
	this->GetControlInfo(widthScreen, heightScreen); 
	this->SetControlSize(pi.width, pi.height); 
	//this->SetPrinterFormat(true); 
	this->OnPaintControl(gdi); 
	//this->SetPrinterFormat(false); 
	this->SetControlSize(widthScreen, heightScreen); 
	//this->RefreshAll(); 
}

void View3D::SetZoom(double zoom)
{
	_zoom = (float)zoom;
	//
	// Set vertical scroll bar range and page size
	SCROLLINFO si;
	si.cbSize = sizeof (SCROLLINFO);
	si.fMask  = SIF_POS;
	si.nPos = (int)((zoom *WIN_VIEWER3D_ZOOMRES)/100.0+0.5);
	::SetScrollInfo (hWnd, SB_VERT, &si, TRUE);
	::InvalidateRect(hWnd, NULL, FALSE);
}

double View3D::GetZoom(void)
{
	return _zoom;
}

void View3D::SetAngle(double angleDegrees)
{
	while(angleDegrees>360.0) angleDegrees-=360.0;
	while(angleDegrees<-360.0) angleDegrees+=360.0;
	_angle = (float)(M_PI*angleDegrees/180.0);
	_sinAngle = sin(_angle);
	_cosAngle = cos(_angle);
	//
	// Set horizontal scroll bar position
	SCROLLINFO si;
	si.cbSize = sizeof (SCROLLINFO);
	si.fMask  = SIF_POS;
	si.nPos = (int)angleDegrees;
	::SetScrollInfo (hWnd, SB_HORZ, &si, TRUE);
	::InvalidateRect(hWnd, NULL, FALSE);
}

double View3D::GetAngle(void)
{
	return 180.0*_angle/M_PI;
}

void View3D::Transform(const vector<Sys::Line3D>& input, vector<Sys::Line16X>& output)
{
	const float zsin =  _zoom*_sinAngle;
	const float zcos =  _zoom*_cosAngle;
	//_______________________________ Compute view point (by rotating in the inverse direction)
	const double ref_x = _maxX*zcos + zsin*_maxY;
	const double ref_y = -(_maxX*zsin) + zcos*_maxY;
	const double ref_z = _maxZ;
	//
	const int count = input.size();
	if (output.size() != count) output.resize(count);
	//
	double x1, y1;
	double x2, y2;
	int tmp;
	int index;

	int i;
	for(i=0; i<count; i++)
	{
		output[i].color = input[i].color;
		//___________________________________________ Rotate
		x1 = input[i].x1*zcos - input[i].y1*zsin;
		y1 = input[i].x1*zsin + input[i].y1*zcos;
		x2 = input[i].x2*zcos - input[i].y2*zsin;
		y2 = input[i].x2*zsin + input[i].y2*zcos;
		//___________________________________________ Transform to 2D and shift
		output[i].x1 = (__int16)(_centerX+(y1-x1)*_cosPerspective+0.5);
		output[i].y1 = (__int16)(_centerY+(x1+y1)*_sinPerspective - _zoom*input[i].z1+0.5);
		output[i].x2 = (__int16)(_centerX+(y2-x2)*_cosPerspective+0.5);
		output[i].y2 = (__int16)(_centerY+(x2+y2)*_sinPerspective - _zoom*input[i].z2+0.5);
		//___________________________________________Compute distance from view to line midpoint
		//
		index = (int)(abs(input[i].mid_x - ref_x));
		tmp = graphics.squared[index];
		//
		index = (int)(abs(input[i].mid_y - ref_y));
		tmp += graphics.squared[index];
		//
		index = (int)(abs(input[i].mid_z - ref_z));
		tmp += graphics.squared[index];
		//
		output[i].view_distance = graphics.squared[tmp];
	}
	std::sort(output.begin(), output.end());
}


//____________________________ Call this function inside OnPaint3D
void View3D::Transform(Sys::Point3D* input, POINT* output, const int count)
{
	double x;
	double y;
	int i;
	for(i=0; i<count; i++)
	{
		//___________________________________________ Rotate
		x = _zoom*input[i].x*_cosAngle - _zoom*input[i].y*_sinAngle;
		y = _zoom*input[i].x*_sinAngle + _zoom*input[i].y*_cosAngle;
		//___________________________________________ Transform to 2D and shift
		output[i].x = (int)(_centerX+(y-x)*_cosPerspective+0.5);
		output[i].y = (int)(_centerY+(x+y)*_sinPerspective - _zoom*input[i].z+0.5);
	}
}

//____________________________ Call this function inside OnPaint3D
void View3D::Transform(Sys::Point3D* input, Sys::Point* output, const int count)
{
	double x;
	double y;
	int i;
	for(i=0; i<count; i++)
	{
		//___________________________________________ Rotate
		x = _zoom*input[i].x*_cosAngle - _zoom*input[i].y*_sinAngle;
		y = _zoom*input[i].x*_sinAngle + _zoom*input[i].y*_cosAngle;
		//___________________________________________ Transform to 2D and shift
		output[i].x = (int)(_centerX+(y-x)*_cosPerspective+0.5);
		output[i].y = (int)(_centerY+(x+y)*_sinPerspective - _zoom*input[i].z+0.5);
	}
}

//____________________________ Call this function inside OnPaint3D
void View3D::Transform(Sys::Point3D* input, Sys::Point16* output, const int count)
{
	double x;
	double y;
	int i;
	for(i=0; i<count; i++)
	{
		//___________________________________________ Rotate
		x = _zoom*input[i].x*_cosAngle - _zoom*input[i].y*_sinAngle;
		y = _zoom*input[i].x*_sinAngle + _zoom*input[i].y*_cosAngle;
		//___________________________________________ Transform to 2D and shift
		output[i].x = (__int16)(_centerX+(y-x)*_cosPerspective+0.5);
		output[i].y = (__int16)(_centerY+(x+y)*_sinPerspective - _zoom*input[i].z+0.5);
	}
}

HWND View3D::GetControlInfo(int& width, int&height)
{
	width = this->width;
	height = this->height;
	return this->hWnd;
}

void View3D::OnPaint3D(Win::Gdi& gdi)
{
	::SendMessage(_hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_PAINT), (LPARAM)&gdi);
}

void View3D::Window_MouseMove(Win::Event& e)
{
	if (_lbuttonDown)
	{
		_centerX = (float)(- _mousePosition.x+(int)(short)LOWORD(e.lParam));
		_centerY = (float)(- _mousePosition.y+(int)(short)HIWORD(e.lParam));
		_hCursor = ::SetCursor(::LoadCursor(NULL, IDC_HAND));
		::ShowCursor(TRUE);
		::InvalidateRect(hWnd, NULL, FALSE);
	}
}

void View3D::Window_LButtonDown(Win::Event& e)
{
	this->SetFocus();
	_lbuttonDown= true;
	_mousePosition.x = (int)(short)LOWORD(e.lParam)-(int)_centerX;
	_mousePosition.y = (int)(short)HIWORD(e.lParam)-(int)_centerY;
	::SendMessage(_hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_CLICK), e.lParam);
	_hCursor = ::SetCursor(::LoadCursor(NULL, IDC_HAND));
	::ShowCursor(TRUE);
}

void View3D::Window_LButtonUp(Win::Event& e)
{
	if (Enabled==false) return;
	_lbuttonDown= false;
	if (_hCursor)
	{
		::SetCursor(_hCursor);
		::ShowCursor(TRUE);
		_hCursor=NULL;
	}
}

void View3D::Window_RButtonDown(Win::Event& e)
{
	if (Enabled==false) return;
	//::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_RCLICK), e.lParam);
	::SendMessage(::GetParent(hWnd), WM_COMMAND, MAKEWPARAM(this->id, WIN_RCLICK), e.lParam);
}

void View3D::SetControlSize(int width, int height)
{
	this->width = width;
	this->height = height;
	OnSizePrivate();
}

void View3D::Window_Size(Win::Event& e)
{
	OnSizePrivate();
}

void View3D::OnSizePrivate(void)
{
	graphics.Create(width, height);
	SCROLLINFO si;

	// Set vertical scroll bar range and page size
	si.cbSize = sizeof (SCROLLINFO);
	si.fMask  = SIF_RANGE | SIF_PAGE | SIF_POS;
	si.nMin   = 1;
	si.nMax   = WIN_VIEWER3D_ZOOMRES;
	si.nPage  = 1;
	si.nPos = (int)((_zoom *WIN_VIEWER3D_ZOOMRES)/100.0+0.5);
	::SetScrollInfo (hWnd, SB_VERT, &si, TRUE);

	// Set horizontal scroll bar range and page size
	si.cbSize = sizeof (SCROLLINFO);
	si.fMask  = SIF_RANGE | SIF_PAGE;
	si.nMin   = 0;
	si.nMax   = WIN_VIEWER3D_ANGLESTEPS;
	si.nPage  = 1;
	::SetScrollInfo (hWnd, SB_HORZ, &si, TRUE);

	//if (this->centerX==0.0) centerX = (int)(width/2.0+0.5);
	//if (this->centerY==0.0) centerY = (int)(height/2.0+0.5);
	//
	_centerX = (float)(this->width/2.0);
	_centerY = (float)(this->height/2.0);
}

void View3D::Window_KeyDown(Win::Event& e)
{
	switch (e.wParam)
	{
/*	case VK_HOME :
		::SendMessage (hWnd, WM_VSCROLL, SB_TOP, 0);
		break; 
	case VK_END :
		::SendMessage (hWnd, WM_VSCROLL, SB_BOTTOM, 0);
		break;	    
	case VK_PRIOR :
		::SendMessage (hWnd, WM_VSCROLL, SB_PAGEUP, 0);
		break;	    
	case VK_NEXT :
		::SendMessage (hWnd, WM_VSCROLL, SB_PAGEDOWN, 0);
		break;	*/    
	case VK_UP:
		_centerY--;
		::InvalidateRect(hWnd, NULL, false);
		break;    
	case VK_DOWN:
		_centerY++;
		::InvalidateRect(hWnd, NULL, false);
		break;    
	case VK_LEFT:
		_centerX--;
		::InvalidateRect(hWnd, NULL, false);
		break;    
	case VK_RIGHT:
		_centerX++;
		::InvalidateRect(hWnd, NULL, false);
		break;
	}
}

void View3D::Window_HScroll(Win::Event& e)
{
	int nHorzPos = 0;
	SCROLLINFO si;
	si.cbSize = sizeof (SCROLLINFO);
	si.fMask  = SIF_ALL;

	// Save the position for comparison later on
	::GetScrollInfo (hWnd, SB_HORZ, &si);
	nHorzPos = si.nPos;

	switch (LOWORD (e.wParam))
	{
	case SB_LINELEFT:
		si.nPos -= 1;
		break;    
	case SB_LINERIGHT:
		si.nPos += 1;
		break;
	case SB_PAGELEFT:
		si.nPos -= si.nPage;
		break;	    
	case SB_PAGERIGHT:
		si.nPos += si.nPage;
		break;    
	//case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos;
		break;
	}
	// Set the position and then retrieve it.  Due to adjustments
	//   by Windows it may not be the same as the value set.
	si.fMask = SIF_POS;
	::SetScrollInfo (hWnd, SB_HORZ, &si, TRUE);
	::GetScrollInfo (hWnd, SB_HORZ, &si);
	
	// If the position has changed, scroll the window 
	if (si.nPos != nHorzPos) 
	{
		//_angle = (si.nPos-WIN_VIEWER3D_ANGLESTEPS/2)*M_PI/180.0;
		_angle = (float)(si.nPos*M_PI/180.0);
		_sinAngle = sin(_angle);
		_cosAngle = cos(_angle);
		//wchar_t texto[256];
		//_snwprintf(texto, 256, L"%f", angle);
		//HWND hWndParent = this->GetParent();
		//::SetWindowText(hWndParent, texto);
		::InvalidateRect(hWnd, NULL, false);
	}
}

void View3D::Window_SetFocus(Win::Event& e)
{
	_hasFocus=true;
}

void View3D::Window_KillFocus(Win::Event& e)
{
	_hasFocus=false;
}

void View3D::Window_VScroll(Win::Event& e)
{
	int nVertPos = 0;
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask  = SIF_ALL;
	::GetScrollInfo(hWnd, SB_VERT, &si);

	// Save the position for comparison later on
	nVertPos = si.nPos;

	switch (LOWORD (e.wParam))
	{
	case SB_TOP:
		si.nPos = si.nMin;
		break;	    
	case SB_BOTTOM:
		si.nPos = si.nMax;
		break;    
	case SB_LINEUP:
		si.nPos -= 1;
		break;	    
	case SB_LINEDOWN:
		si.nPos += 1;
		break;	    
	case SB_PAGEUP:
		si.nPos -= si.nPage;
		break;	    
	case SB_PAGEDOWN:
		si.nPos += si.nPage;
		break;	    
	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos;
		break;         
	}
	// Set the position and then retrieve it.  Due to adjustments
	//   by Windows it may not be the same as the value set.
	si.fMask = SIF_POS;
	::SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
	::GetScrollInfo(hWnd, SB_VERT, &si);

	// If the position has changed, scroll the window and update it
	if (si.nPos != nVertPos) 
	{
		_zoom = (float)(100.0*si.nPos/(double)WIN_VIEWER3D_ZOOMRES);
		//if (si.nPos==WIN_VIEWER3D_ZOOMRES/2)
		//{
		//	this->zoom = 1.0;
		//}
		//if (si.nPos>WIN_VIEWER3D_ZOOMRES/2)
		//{
		//	this->zoom = (si.nPos-WIN_VIEWER3D_ZOOMRES/2);
		//}
		//else
		//{
		//	this->zoom = 1.0/(WIN_VIEWER3D_ZOOMRES/2-si.nPos);
		//}
		//wchar_t texto[256];
		//_snwprintf(texto, 256, L"%f", zoom);
		//HWND hWndParent = this->GetParent();
		//::SetWindowText(hWndParent, texto);
		::InvalidateRect(hWnd, NULL, false);
	}
}

// The control needs to have the focus
void View3D::Window_MouseWheel(Win::Event& e)
{
	if (_deltaWheelPerLine == 0)
	{
		e.returnValue = FALSE;
		return;
	}

	_accumWheelDelta += (short) HIWORD (e.wParam);     // 120 or -120

	while (_accumWheelDelta >= _deltaWheelPerLine)
	{               
		::SendMessage (hWnd, WM_VSCROLL, SB_LINEUP, 0);
		_accumWheelDelta -= _deltaWheelPerLine;
	}

	while (_accumWheelDelta <= - _deltaWheelPerLine)
	{
		::SendMessage (hWnd, WM_VSCROLL, SB_LINEDOWN, 0);
		_accumWheelDelta += _deltaWheelPerLine;
	}
}

// Use RGBX instead of RGB
void View3D::DrawCenter(COLORREF color)
{
	Sys::Point3D pin[6];
	Sys::Point16 pout[6];
	pin[0].x = - _axisLength;
	pin[0].y = 0.0;
	pin[0].z = 0.0;
	//
	pin[1].x = _axisLength;
	pin[1].y = 0.0;
	pin[1].z = 0.0;

	pin[2].x = 0.0;
	pin[2].y = - _axisLength;
	pin[2].z = 0.0;
	//
	pin[3].x = 0.0;
	pin[3].y = _axisLength;
	pin[3].z = 0.0;

	pin[4].x = 0.0;
	pin[4].y = 0.0;
	pin[4].z = 0.0;
	//
	pin[5].x = 0.0;
	pin[5].y = 0.0;
	pin[5].z = _axisLength;

	Transform(pin, pout, 6);
	//
	graphics.WuLine(pout[0].x, pout[0].y, pout[1].x, pout[1].y, color);
	graphics.WuLine(pout[2].x, pout[2].y, pout[3].x, pout[3].y, color);
	graphics.WuLine(pout[4].x, pout[4].y, pout[5].x, pout[5].y, color);
}

void View3D::OnPaintControl(Win::Gdi& gdi)
{
	//const RECT rcPaint = gdi.GetRcPaint();
	//RECT rect = {0, 0, this->width, this->height};

	//Win::Gdi::Brush brushBackground( Enabled ? _backColor : WIN_BACK_DISABLED);
	//gdi.FillRect(rcPaint, brushBackground);

	this->graphics.SetAllPixels(_backColorx);
	
	//Win::Gdi::Pen penLine(PS_SOLID, 1, _lineColor);



	//if (_hfont) gdi.SelectFont__(_hfont);
	//gdi.SetTextColor(_textColor);
	//int i;
	////____________________________________________________ Paint Box Bottom
	//if (_showBox == true)
	//{
	//	pin[0].x = _minX;
	//	pin[0].y = _minY;
	//	pin[0].z = _minZ;
	//	//
	//	pin[1].x = _minX;
	//	pin[1].y = _maxY;
	//	pin[1].z = _minZ;
	//	//
	//	pin[2].x = _maxX;
	//	pin[2].y = _maxY;
	//	pin[2].z = _minZ;
	//	//
	//	pin[3].x = _maxX;
	//	pin[3].y = _minY;
	//	pin[3].z = _minZ;
	//	//
	//	pin[4] = pin[0];
	//	//
	//	Transform(pin, pout, 5);
	//	gdi.Polyline(pout, 5);
	//	//
	//	for(i = 0; i < _divCountX; i++)
	//	{

	//	}
	//}



	this->OnPaint3D(gdi);

	////____________________________________________________ Paint Box Top
	//if (_showBox == true)
	//{
	//	pin[0].x = _minX;
	//	pin[0].y = _minY;
	//	pin[0].z = _maxZ;
	//	//
	//	pin[1].x = _minX;
	//	pin[1].y = _maxY;
	//	pin[1].z = _maxZ;
	//	//
	//	pin[2].x = _maxX;
	//	pin[2].y = _maxY;
	//	pin[2].z = _maxZ;
	//	//
	//	pin[3].x = _maxX;
	//	pin[3].y = _minY;
	//	pin[3].z = _maxZ;
	//	//
	//	pin[4] = pin[0];
	//	//
	//	Transform(pin, pout, 5);
	//	gdi.Polyline(pout, 5);
	//}
	
}

void View3D::SetCenter(double centerX, double centerY)
{
	_centerX = (float)centerX;
	_centerY = (float)centerY;
	::InvalidateRect(hWnd, NULL, TRUE);
}

void View3D::GetCenter(double& centerX, double& centerY)
{
	centerX = _centerX;
	centerY = _centerY;
}

void View3D::SetAxisLength(float length)
{
	_axisLength = length;
	::InvalidateRect(hWnd, NULL, true);
}

void View3D::Window_Paint(Win::Event& e)
{
	//Win::Gdi gdi(hWnd, true, false);
	//this->OnPaintControl(gdi);
	Win::Gdi gdi(hWnd, true, false);

	OnPaintControl(gdi);
	
	gdi.DrawGraphics(graphics, 0, 0);
}

void View3D::Window_Open(Win::Event& e)
{
	_hWndParent = ::GetParent(hWnd);
	graphics.Create(width, height);
}

void View3D::ConvertFromSphericalToCartesian(Sys::SphericalPoint* input, Sys::Point3D* output, const int count)
{
	double sinTheta;
	for(int i=0; i<count; i++)
	{
		sinTheta= sin(input[i].theta);
		output[i].x = (float)(input[i].r*cos(input[i].phi)*sinTheta); // x = r cos(phi) sin(theta)
		output[i].y = (float)(input[i].r*sin(input[i].phi)*sinTheta); // y = r sin(phi) sin(theta)
		output[i].z = (float)(input[i].r*cos(input[i].theta)); // z = r cos(theta)
	}
}

//_____________________________________________________________________ Bar
Bar::Bar()
{
	_value = 0.0;
	_text = L"-";
	_color = RGB(100, 100, 100);
	_index = -1;
	//
	barChart = NULL;
}

Bar::~Bar()
{
}

COLORREF Bar::GetColor()
{
	//return barChart->_bars[_index]._color
	return _color;
}

void Bar::SetColor(COLORREF color)
{
	_color = color;
	barChart->UpdateBar(_index);
}

double Bar::GetValue()
{
	return _value;
}

void Bar::SetValue(double value)
{
	_value = value;
	barChart->UpdateBar(_index);
}

wstring Bar::GetText()
{
	return _text;
}

void Bar::SetText(wstring text)
{
	_text = text;
	barChart->UpdateBarText(_index);
}

bool Bar::operator<(const Win::Bar& bar) const
{
	return (_value<bar._value);
}

//_____________________________________________________________________ BarCollection
BarCollection::BarCollection()
{
	barChart = NULL;
}

BarCollection::~BarCollection()
{
}

void BarCollection::Add(const wstring& text, COLORREF color, double value)
{
	Win::Bar bar;
	bar._color = color;
	bar._text = text;
	bar._value = value;
	bar._index = -1;
	_bars.push_back(bar);
	_bars.back().barChart = barChart;
	this->barChart->Refresh();
}

void BarCollection::DeleteAll()
{
	_bars.clear();
	this->barChart->Refresh();
}

int BarCollection::GetCount()
{
	return _bars.size();
}

Win::Bar& BarCollection::operator[](long index)
{
	_bars.at(index)._index = index;
	return _bars.at(index);
}

//_____________________________________________________________________BarChart
//bool BarChart::m_bRegistered= false;

BarChart::BarChart(void)
{
	//if (!m_bRegistered)
	//{
	//	this->RegisterClassEx(LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(NULL_BRUSH));
	//	m_bRegistered = true;
	//}
	_autoscale = true;

	_divCount = 5;
	pGridY = new int[_divCount-1];
	_deltaX = 0.0;
	_deltaY = 0.0;
	_barWidth = 0.0;
	_maxValue = 0.0;
	_minValue = 0.0;
	_scaleY = 0.0;
	//lstrcpyn(m_szCaptionYFormat, L"%.2f", 16);
	//m_nCaptionXLetterCount = WIN_BARCHART_SZ;
	m_bTickX = false;
	//gridYCount = 0;
	//
	//_backColor = RGB(245, 245, 245);
	//_textColor = RGB(50, 50, 50);
	//_lineColor = RGB(200, 200, 200);

	_bars.barChart = this;
}

BarChart::~BarChart(void)
{
	if (pGridY) delete [] pGridY;
}

void BarChart::Window_Open(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
}

void BarChart::Window_Size(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
	OnSizePrivate();
}

void BarChart::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, false);
	Win::Gdi gdiBitmap(bitmap, gdi.GetRcPaint(), false);
	if (_hfont) gdiBitmap.SelectFont__(_hfont);
	OnPaintControl(gdiBitmap);
	gdi.DrawDoubleBuffer(bitmap);
}

Win::BarCollection& BarChart::GetBars()
{
	return _bars;
}

void BarChart::UpdateBar(int index)
{
	double offset = (_deltaX-this->_barWidth)/2.0;
	RECT rect;
	rect.bottom = _box.bottom;
	rect.top = _box.top;
	rect.left = (int)(_box.left + _deltaX*index+offset - 1.5);
	rect.right = (int)(_box.left + _deltaX*(index+1)+offset + 1.5);
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, &rect, FALSE);
}

void BarChart::UpdateBarText(int index)
{
	RECT rect;
	rect.bottom = _rectCaptionX.bottom;
	rect.top = _rectCaptionX.top;
	rect.left = (int)(_rectCaptionX.left + _deltaX*index +0.5);
	rect.right = (int)(_rectCaptionX.left + _deltaX*(index+1) +0.5);
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, &rect, FALSE);
}

bool BarChart::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_COMMAND) return false;
	const int id = LOWORD(e.wParam);
	const int notificationd = HIWORD(e.wParam);
	if (id != this->id) return false;
	if (notificationd!=notification) return false;
	return true;
}

void BarChart::UpdateBarValues()
{
	if (_autoscale) 
	{
		vector<Win::Bar>::iterator p = std::max_element(_bars._bars.begin(), _bars._bars.end());
		if (p != _bars._bars.end())
		{
			_maxValue = p->_value;
		}
		else
		{
			_maxValue = 100.0;
		}
		//p = std::min_element(_bars._bars.begin(), _bars._bars.end());
		//if (p != _bars._bars.end())
		//{
		//	_minValue = p->_value;
		//}
		//else
		//{
		//	_minValue = 0.0;
		//}
	}
}

void BarChart::Refresh()
{
	this->UpdateBarValues();
	OnSizePrivate();
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, true);
}

void BarChart::OnSizePrivate(void)
{
	const int barCount = Bars.Count;
	
	LOGFONT logfont;
	GetLogfont(logfont);

	//_______________________________ Update m_box
	if (_printerFormat)
	{
		_box.left = (int)(printInfo.position.x + 0.09*this->width+0.5);
		_box.right = (int)(printInfo.position.x + 0.98*this->width+0.5);
		_box.top = (int)(printInfo.position.y + 0.05*this->height+0.5);
		_box.bottom = (int)(printInfo.position.y + 0.95*this->height+0.5);
	}
	else if (width>10000)
	{	
		_box.left = (int)(0.09*this->width+0.5);
		_box.right = (int)(0.98*this->width+0.5);
		_box.top = (int)(0.05*this->height+0.5);
		_box.bottom = (int)(0.95*this->height+0.5);
	}
	else
	{	
		const int charWidth = (int)(abs(logfont.lfHeight)/2.0+0.5);
		const int charHeight = abs(logfont.lfHeight);
		_box.left = 8*charWidth;
		_box.right = width - 4*charWidth;
		_box.top = 2*charHeight;
		_box.bottom = height-2*charHeight;
	}

	//******************************************* Update deltaX and deltaY
	if (barCount>0)
	{
		_deltaX = ((double)(_box.right-_box.left))/(double)barCount;
	}
	if (_divCount>0)
	{
		_deltaY = ((double)(_box.bottom-_box.top))/(double)_divCount;
	}
	_barWidth = 0.80*_deltaX;

	//******************************************* Update m_gridY
	if (_deltaY>0)
	{
		for(int i=0; i<_divCount-1; i++)
		{
			pGridY[i] = (int)(_box.bottom - (i+1)*_deltaY+0.5);
		}
	}

	//********************************************* Update m_rectCaptionY
	if (_printerFormat)
	{
		_rectCaptionY.bottom = (int)(this->_box.bottom + _deltaY/2.0 + 0.5);
		_rectCaptionY.top = printInfo.position.y;//(int)(this->m_box.bottom - (m_nDivCount+0.5)*m_deltaY + 0.5);
		_rectCaptionY.left = printInfo.position.x;
		_rectCaptionY.right = _box.left;
	}
	else
	{
		_rectCaptionY.bottom = (int)(this->_box.bottom + _deltaY/2.0 + 0.5);
		_rectCaptionY.top = 0;//(int)(this->m_box.bottom - (m_nDivCount+0.5)*m_deltaY + 0.5);
		_rectCaptionY.left = 0;
		_rectCaptionY.right = _box.left;
	}
	
	//********************************************* Update m_rectCaptionX
	if (_printerFormat)
	{
		_rectCaptionX.top = _box.bottom;
		_rectCaptionX.bottom = this->height + printInfo.position.y;
		_rectCaptionX.left = _box.left;
		_rectCaptionX.right = _box.right;
	}
	else
	{
		_rectCaptionX.top = _box.bottom;
		_rectCaptionX.bottom = this->height;
		_rectCaptionX.left = _box.left;
		_rectCaptionX.right = _box.right;
	}

	_scaleY = (_box.bottom-_box.top)/(_maxValue-_minValue);
}

void BarChart::SetMaxY(double value)
{
	_autoscale = false;
	_maxValue = value;
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

double BarChart::GetMaxY()
{
	return _maxValue;
}

void BarChart::SetMinY(double value)
{
	_autoscale = false;
	_minValue = value;
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

double BarChart::GetMinY()
{
	return _minValue;
}

void BarChart::SetAutoscale(bool autoscale)
{
	_autoscale = autoscale;
	if (autoscale)
	{
		this->UpdateBarValues();
		if (hWnd==NULL) return;
		::InvalidateRect(hWnd, NULL, FALSE);
	}
}

bool BarChart::GetAutoscale()
{
	return _autoscale;
}

//void BarChart::SetCaptionYFormat(const wchar_t* pszFormat)
//{
//	lstrcpyn(m_szCaptionYFormat, pszFormat, 16);
//	if (hWnd==NULL) return;
//	::InvalidateRect(hWnd, &m_rectCaptionY, false);
//}

void BarChart::SetDivYCount(int count)
{
	this->_divCount = count;
	if (pGridY) delete [] pGridY;
	pGridY = new int[_divCount-1];
	OnSizePrivate();
	if (hWnd==NULL) return;
	::InvalidateRect(hWnd, NULL, false);
}

int BarChart::GetDivYCount()
{
	return _divCount;
}

void BarChart::OnPaintControl(Win::Gdi& gdi)
{
	RECT rect;
	int i=0, index=0, x=0, y =0;
	//int nLeft, nRight, 
	int nTop, nBottom;
	int index1, index2;
	const int barCount = _bars._bars.size();

	//_____________________________________________ Font
	Win::Gdi::Font font;
	
	if (_printerFormat)
	{
		LOGFONT logfont;
		this->GetLogfont(logfont);
		logfont.lfHeight = (int)(-(height-_box.bottom+printInfo.position.y)/2.0+0.5);
		font.Create(logfont);
		gdi.SelectFont_(font);
	}
	else if (height>WINFONT_MAXRES || width>WINFONT_MAXRES)
	{
		LOGFONT logfont;
		this->GetLogfont(logfont);
		logfont.lfHeight = -(height-_box.bottom)/2;
		font.Create(logfont);
		gdi.SelectFont_(font);
	}
	else
	{
		if (_hfont) gdi.SelectFont__(_hfont);
	}

	//_____________________________________________ Line
	Win::Gdi::Pen penLine;
	if (_printerFormat)
	{
		penLine.Create(PS_SOLID, WINXYCHART_PRINTERPEN, _lineColor);
	}
	else
	{
		penLine.Create(PS_SOLID, 1, _lineColor);
	}

	//____________________________ Text
	if (this->Enabled)
	{
		gdi.SetBkColor(_backColor);
		gdi.SetTextColor(_textColor);
	}
	else
	{
		gdi.SetBkColor(WIN_BACK_DISABLED);
		gdi.SetTextColor(WIN_TEXT_DISABLED);
	}

	//_______________________________________________________ Background
	Win::Gdi::Brush brushBackground;
	const RECT rcPaint = gdi.GetRcPaint();
	if (_printerFormat==false)//gdi.DoRcPaintOverlap(m_box) && )
	{
		if (this->Enabled)
		{
			brushBackground.CreateSolid(_backColor);
		}
		else
		{
			brushBackground.CreateSolid(WIN_BACK_DISABLED);
		}
		gdi.SelectBrush_(brushBackground);
		gdi.FillRect(rcPaint, brushBackground);
	}

	////****************************************************** Foreground top
	//rect.top = 0;
	//rect.left = 0;
	//rect.right = this->width;
	//rect.bottom = m_box.top;
	//if (gdi.DoRcPaintOverlap(rect) && isPrintting==false) gdi.FillRect(rect, (HBRUSH)(COLOR_BTNFACE+1));

	////****************************************************** Foreground bottom
	//rect.top = m_box.bottom;
	//rect.left = 0;
	//rect.right = this->width;
	//rect.bottom = this->height;
	//if (gdi.DoRcPaintOverlap(rect) && isPrintting==false) gdi.FillRect(rect, (HBRUSH)(COLOR_BTNFACE+1));

	////****************************************************** Foreground left
	//rect.top = m_box.top;
	//rect.left = 0;
	//rect.right = m_box.left;
	//rect.bottom = m_box.bottom;
	//if (gdi.DoRcPaintOverlap(rect) && isPrintting==false) gdi.FillRect(rect, (HBRUSH)(COLOR_BTNFACE+1));

	////****************************************************** Foreground right
	//rect.top = m_box.top;
	//rect.left = m_box.right;
	//rect.right = this->width;
	//rect.bottom = m_box.bottom;
	//if (gdi.DoRcPaintOverlap(rect) && isPrintting==false) gdi.FillRect(rect, (HBRUSH)(COLOR_BTNFACE+1));


	//***************************************************************** Grid
	gdi.SetBkMode(true);
	gdi.SelectPen_(penLine);

	if (_printerFormat)
	{
		for(index = 0; index<_divCount-1; index++)
		{
			gdi.MoveToEx(_box.left, pGridY[index]);
			gdi.LineTo(_box.right, pGridY[index]);
		}
	}
	else
	{
		if (gdi.DoRcPaintOverlap(_box))
		{
			int index;
			int index1=0;
			int index2=0;
			int left, right;

			gdi.OnPaintLoopY_(_box, pGridY, _divCount, index1, index2, left, right);
			for(index = index1; index<=index2; index++)
			{
				gdi.MoveToEx(left, pGridY[index]);
				gdi.LineTo(right, pGridY[index]);
			}
		}
	}

	//******************************************************** CaptionX
	if (barCount>0)
	{
		if (_printerFormat)
		{
			rect.bottom = _rectCaptionX.bottom;
			rect.top = _rectCaptionX.top;
			//for(i=0; i<nBarCount; i++) // Fix this latter
			y = (int)(font.GetSize() * 0.1 /10.0+0.5);
			for(i=0; i<barCount; i++)
			{
				rect.left = (int)(_rectCaptionX.left + _deltaX*i +0.5);
				rect.right = (int)(_rectCaptionX.left + _deltaX*(i+1) +0.5);
				if (_bars._bars[i].Text.empty() == false)
					gdi.TextOutCenter(rect, _bars._bars[i].Text.c_str(), true, true);
				if (m_bTickX)
				{
					x = (int)((rect.left + rect.right)/2+0.5);
					gdi.MoveToEx(x, _box.bottom-y);
					gdi.LineTo(x, _box.bottom + y);
				}
			}
		}
		else
		{
			if (gdi.OnPaintLoopX(this->_deltaX, this->_rectCaptionX, nTop, nBottom, index1, index2))
			{
				rect.bottom = _rectCaptionX.bottom;
				rect.top = _rectCaptionX.top;
				y = (int)(font.GetSize() * 0.1 /10.0+0.5);
				for(i=index1; i<=index2; i++)
				{
					rect.left = (int)(_rectCaptionX.left + _deltaX*i +0.5);
					rect.right = (int)(_rectCaptionX.left + _deltaX*(i+1) +0.5);
					if (_bars._bars[i].Text.empty() == false)
						gdi.TextOutCenter(rect, _bars._bars[i].Text.c_str(), true, true);
					if (m_bTickX)
					{
						x = (int)((rect.left + rect.right)/2+0.5);
						gdi.MoveToEx(x, _box.bottom-y);
						gdi.LineTo(x, _box.bottom + y);
					}
				}
			}
		}
	}

	//_____________________________________________________ CaptionY
	if (barCount>0)
	{
		if (gdi.DoRcPaintOverlap(_rectCaptionY))//gdi.OnPaintLoopY(m_deltaY, m_rectCaptionY, nLeft, nRight, index1, index2))
		{
			SIZE size;
			double captionYScale = (_maxValue-_minValue)/_divCount;
			wchar_t sz[255];

			x= _box.left - _fontHeight  / 4;
			for(i= 0 ; i<=_divCount; i++) //for(i=index1; i<=index2; i++)
			{
				y = (int)(_box.top + i * _deltaY +0.5);
				if (y>_box.bottom) break;
				Sys::Convert::ToString(_maxValue - captionYScale*i, sz, 255, true);
				//_snwprintf_s(sz, 255, _TRUNCATE, m_szCaptionYFormat, m_maxValue - captionYScale*i);
				gdi.GetTextExtentPoint32W(sz, size);
				gdi.SetTextAlign(TA_RIGHT | TA_TOP);
				//gdi.TextOutCenter(x, y, sz, false, true);
				gdi.TextOut(x, y-size.cy/2, sz);
			}
		}
	}
	gdi.SetTextAlign(TA_LEFT | TA_TOP);

	//_____________________________________________________ Bars
	if (barCount>0)
	{
		bool paint = false;
		double dotsPerY = (_box.bottom - _box.top) / (_maxValue-_minValue);
		double barPositionX, barPositionY, barSizeY;
		double offset = (_deltaX-this->_barWidth)/2.0;
		Win::Gdi::Brush brush;
		Win::Gdi::Pen pen;
		COLORREF color = RGB(0, 0, 0);
		if (_printerFormat)
		{
			index1 = 0;
			index2 = _bars.GetCount()-1;
			paint = true;
		}
		else
		{
			paint = gdi.OnPaintLoopX(_deltaX, _box, nTop, nBottom, index1, index2);
		}
		if (paint == true)
		{
			for (i = index1; i <=index2; i++)
			{
				if (_bars._bars[i].Value > 0)
				{
					barPositionX = _deltaX * i + _box.left + offset;
					barSizeY = dotsPerY * (_bars._bars[i].Value-_minValue);
					barPositionY = _box.bottom  - (int) (barSizeY + 0.5);
					if (color != _bars._bars[i].Color)
					{
						brush.CreateSolid(_bars._bars[i].Color);
						color = _bars._bars[i].Color;
						gdi.SelectBrush_(brush);
					}
					rect.left = (int)barPositionX;
					rect.top = (int)barPositionY;
					rect.bottom = (int)(barPositionY+barSizeY+0.5);
					rect.right = (int)(barPositionX+this->_barWidth);
					gdi.Rectangle(rect);
				}
			}
		}
	}

	//_____________________________________________________ Sourrounding Box
	if (gdi.DoRcPaintOverlap(_box))
	{
		gdi.SelectBrush__((HBRUSH)GetStockObject(NULL_BRUSH));
		Win::Gdi::Pen pen(PS_SOLID, 1, _textColor);
		gdi.SelectPen_(pen);
		//gdi.SelectPen__((HPEN)GetStockObject(BLACK_PEN));
		gdi.Rectangle(this->_box);
	}

	//_____________________________________________________ Title
	//const int length = this->GetTextLength();//::GetWindowTextLength(hWnd);
	if (_text.length()>0)
	{
		if (_printerFormat == true)
		{
			rect.top = printInfo.position.y;
			rect.left = printInfo.position.x;
			rect.right = printInfo.position.x + this->width;
			rect.bottom = _box.top;
		}
		else
		{
			rect.top = 0;
			rect.left = 0;
			rect.right = this->width;
			rect.bottom = _box.top;
		}
		if (gdi.DoRcPaintOverlap(rect))
		{
			gdi.TextOutCenter(rect, _text.c_str(), true, true);
		}
	}
}

//_____________________________________________________________________ Pie
Pie::Pie()
{
	_value = 0.0;
	_text = L"-";
	_color = RGB(100, 100, 100);
	_index = -1;
	//
	pieChart = NULL;
}

Pie::~Pie()
{
}

COLORREF Pie::GetColor()
{
	return _color;
}

void Pie::SetColor(COLORREF color)
{
	pieChart->SetPieColor(_index, color);
}

double Pie::GetValue()
{
	return _value;
}

void Pie::SetValue(double value)
{
	_value = value;
	pieChart->Refresh();
	//pieChart->SetPieValue(_index, value);
}

wstring Pie::GetText()
{
	return _text;
}

void Pie::SetText(wstring text)
{
	_text = text;
	pieChart->Refresh();
	//pieChart->SetPieText(_index, text);
}

bool Pie::operator<(const Win::Pie& pie) const
{
	return (_value < pie._value);
}

//_____________________________________________________________________ PieCollection
PieCollection::PieCollection()
{
	pieChart = NULL;
}

PieCollection::~PieCollection()
{
}

void PieCollection::Add(const wstring& text, COLORREF color, double value)
{
	Win::Pie pie;
	pie._color = color;
	pie._text = text;
	pie._value = value;
	pie._index = -1;
	_pies.push_back(pie);
	_pies.back().pieChart = pieChart;
	this->pieChart->Refresh();
}

void PieCollection::DeleteAll()
{
	_pies.clear();
	this->pieChart->Refresh();
}

int PieCollection::GetCount()
{
	return _pies.size();
}

Win::Pie& PieCollection::operator[](long index)
{
	_pies.at(index)._index = index;
	return _pies.at(index);
}

//_____________________________________________________________________ PieChart
PieChart::PieChart(void)
{
	_x = 0;
	_y = 0; 
	_radius = 0;
	_xCenter = 0; 
	_yCenter = 0;
	_angleIni = 0;
	_xCaption = 0;
	_dimension=0.0;
	_yCaption = 0;
	_pies.pieChart = this;
	_lineColor = RGB(128, 128, 128);
}

PieChart::~PieChart(void)
{
}

void PieChart::Window_Open(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
}

void PieChart::Window_Size(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
	OnSizePrivate();
}

void PieChart::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, false);
	Win::Gdi gdiBitmap(bitmap, gdi.GetRcPaint(), false);
	if (_hfont) gdiBitmap.SelectFont__(_hfont);
	OnPaintControl(gdiBitmap);
	gdi.DrawDoubleBuffer(bitmap);
}


Win::PieCollection& PieChart::GetPies()
{
	return _pies;
}

void PieChart::Refresh()
{
	this->OnSizePrivate();
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

void PieChart::OnSizePrivate(void)
{
	_xCaption = (int)(8*_fontHeight);//(0.4*width+0.5);
	double pieWidth = width - _xCaption;
	_dimension = MINIMUM(pieWidth, height);
	_radius = (int)(_dimension*0.95/2+0.5);
	if (_printerFormat == true)
	{
		//_xCenter = (int)(_radius+0.05*_dimension+0.5+printInfo.position.x);
		_xCenter = (int)(width/2.0+0.5+printInfo.position.x);
		_yCenter = (int)(height/2.0+0.5+printInfo.position.y);
		_xCaption = (int)(1.05 * _dimension+0.5+printInfo.position.x);
		_xCaption = (int)(_xCenter+_radius +0.07*_dimension+0.5);
	}
	else
	{
		_xCenter = (int)(_radius+0.05*_dimension+0.5);
		_yCenter = (int)(height/2.0+0.5);
		_xCaption = (int)(1.05 * _dimension+0.5);
	}

    _x = _xCenter - _radius;
    _y = _yCenter - _radius;
}

void PieChart::SetPieValue(int index, double value)
{
	const int pieCount = _pies.GetCount();
	if (index<0 || index>=pieCount) return;
	_pies[index].SetValue(value);
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

void PieChart::SetPieColor(int index, COLORREF color)
{
	const int pieCount = _pies.GetCount();
	if (index<0 || index>=pieCount) return;
	_pies[index].SetColor(color);
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

void PieChart::SetPieText(int index, const wstring& text)
{
	SetPieText(index, text.c_str());
}

void PieChart::SetPieText(int index, const wchar_t* text)
{
	const int pieCount = _pies.GetCount();
	if (index<0 || index>=pieCount) return;
	_pies[index].SetText(text);
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

void PieChart::SetCaptionFormat(const wchar_t* format)
{
	lstrcpyn(captionFormat, format, WIN_PIECHART_SZ);
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

void PieChart::OnPaintControl(Win::Gdi& gdi)
{
    int i=0;
	_angleIni = 0.0;
	if (_printerFormat == true)
	{
		_yCaption = (int)(_dimension*0.05+0.5+printInfo.position.y);
	}
	else
	{
		_yCaption = (int)(_dimension*0.05+0.5);
	}
	const int pieCount = _pies.GetCount();

	//________________________________________compute total
	_total = 0.0;
	for(i=0; i<pieCount; i++)
    {
		_total += fabs(_pies[i].GetValue());
    }

	//_____________________________________________ Font
	Win::Gdi::Font font;
	
	if (_printerFormat || height>WINFONT_MAXRES || width>WINFONT_MAXRES)
	{
		LOGFONT logfont;
		this->GetLogfont(logfont);
		logfont.lfHeight = -(int)(_dimension/20.0+0.5);
		font.Create(logfont);
		gdi.SelectFont_(font);
	}
	else
	{
		if (_hfont) gdi.SelectFont__(_hfont);
	}

	//_____________________________________________ Line
	Win::Gdi::Pen penGrid;
	if (_printerFormat)
	{
		penGrid.Create(PS_SOLID, WINXYCHART_PRINTERPEN, _lineColor);
	}
	else
	{
		penGrid.Create(PS_SOLID, 1, _lineColor);
	}
	gdi.SelectPen_(penGrid);

	//____________________________ Text
	if (this->Enabled)
	{
		gdi.SetBkColor(_backColor);
		gdi.SetTextColor(_textColor);
	}
	else
	{
		gdi.SetBkColor(WIN_BACK_DISABLED);
		gdi.SetTextColor(WIN_TEXT_DISABLED);
	}

	//_______________________________________________________ Background
	Win::Gdi::Brush brushBackground;
	RECT rect;
	if (_printerFormat==false)//gdi.DoRcPaintOverlap(m_box) && )
	{
		rect = gdi.GetRcPaint();
		if (this->Enabled)
		{
			brushBackground.CreateSolid(_backColor);
		}
		else
		{
			brushBackground.CreateSolid(WIN_BACK_DISABLED);
		}
		gdi.SelectBrush_(brushBackground);
		gdi.FillRect(rect, brushBackground);
	}

	TEXTMETRIC tm;
	gdi.GetTextMetrics(&tm);

	//_________________________________________ title
	if (_text.length())
	{
		gdi.TextOut(_xCaption, _yCaption, _text.c_str());
		_yCaption+=tm.tmHeight+tm.tmExternalLeading;
	}

	for(i=0; i<pieCount; i++)
    {
		Pie_(gdi, _pies[i].GetText().c_str(), _pies[i].GetValue()*100.0/_total, _pies[i].GetColor(), tm.tmHeight+tm.tmExternalLeading);
	}
}

void PieChart::Pie_(Win::Gdi& gdi, const wchar_t* text, double percentaje, COLORREF color, int spacingY)
{
	wchar_t texto[128];
	double angleDelta = percentaje*360/100;
	double percentaje2=(int)(percentaje+0.5);
	Win::Gdi::Brush brush;
	//int radius = m_radius + 2*fontSize;

	brush.CreateSolid(color);
	gdi.SelectBrush_(brush);
	if (percentaje > 0)
	{
		gdi.PieCircle(_xCenter, _yCenter, _radius, (int)(_angleIni+0.5), (int)(angleDelta+0.5));
	}
	gdi.SetBkMode(true);
	if (percentaje>1.0)
	{
		_snwprintf_s(texto, 128, _TRUNCATE, L"%s %.0f%%", text, percentaje);
	}
	else
	{
		_snwprintf_s(texto, 128, _TRUNCATE, L"%s %.1f%%", text, percentaje);
	}

	RECT rect = {_xCaption, _yCaption, _xCaption+spacingY, _yCaption+spacingY}; 
	::InflateRect(&rect, (int)(-0.2*spacingY+0.5), (int)(-0.2*spacingY+0.5));
	gdi.Rectangle(rect);
	gdi.TextOut((int)(_xCaption+(1.05*spacingY)+0.5), _yCaption, texto);
	_angleIni+=angleDelta;
	_yCaption+=spacingY;
}

//_____________________________________________________________________Histogram
Histogram::Histogram(void)
{
	this->Graphs.Add();
	this->Graphs[0].SetType(Win::Graph::histogram);
}

Histogram::~Histogram(void)
{
}

void Histogram::SetData(valarray<double>& data, int resolution, bool percentDisplay)
{
	if (Graphs.Count != 1)
	{
		Graphs.DeleteAll();
		Graphs.Add();
	}
	int i;
	const int data_size = data.size();
	if (data_size <= 1) 
	{
		Graphs[0].SetPointCount(0);
		return;
	}
	if (resolution<=0)
	{
		Graphs[0].SetPointCount(0);
		return;
	}
	//_______________________________Find minimum and maximum
	double minimum = data[0];
	double maximum = data[0];
	for(i=0; i<data_size; i++)
	{
		if (data[i]<minimum) minimum = data[i];
		if (data[i]>maximum) maximum = data[i];
	}
	if (maximum==minimum)
	{
		Graphs[0].SetPointCount(0);
		return;
	}
	Graphs[0].SetPointCount(resolution);
	//_______________________________ compute x values and clean y
	const double deltaX = (maximum-minimum)/resolution;
	for(i=0; i<resolution; i++)
	{
		Graphs[0][i].x = minimum+i*deltaX+deltaX/2.0;
		Graphs[0][i].y = 0.0;
	}

	//______________________________ Find Histogram
	int index;
	for(i=0; i<data_size; i++)
	{
		index = (int)((data[i]-minimum)/deltaX);
		if (0<=index && index<resolution)
		{
			Graphs[0][index].y ++;
		}
	}
	if (percentDisplay)
	{
		for(i=0; i<resolution; i++)
		{
			Graphs[0][i].y = Graphs[0][i].y * 100.0 / data_size;
		}
		this->SetMinY(0.0);
		this->SetMaxY(100.0);
	}
	this->RefreshAll();
}

//_____________________________________________________________________LevelControl
LevelControl::LevelControl(void) : _blockWidth(4), _blockPadding(1)
{
	//if (!m_bRegistered)
	//{
	//	this->RegisterClassEx(LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(BLACK_BRUSH));
	//	m_bRegistered=true;
	//}
	_normalLevel = 0.75;
	_warningLevel = 0.95;
	_blockCount = 0;
	_blockHeight = 0;
	_padding = 0;
	_minLevel = 0.0;
	_maxLevel = 100.0;
	//scale = 0;
	_level = 0.0;
	//
	_lineColor = RGB(50, 240, 50);
	_backColor = RGB(0, 0, 0);
	_warningColor = RGB(250, 250, 10);
	_errorColor = RGB(250, 10, 10);
}

LevelControl::~LevelControl(void)
{
}

COLORREF LevelControl::GetWarningColor()
{
	return _warningColor;
}

void LevelControl::SetWarningColor(COLORREF color)
{
	_warningColor = color;
	if (hWnd == NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

COLORREF LevelControl::GetErrorColor()
{
	return _errorColor;
}

void LevelControl::SetErrorColor(COLORREF color)
{
	_errorColor = color;
	if (hWnd == NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

double LevelControl::GetLevel()
{
	return _level;
}

void LevelControl::SetRange(double minValue, double maxValue)
{
	if (maxValue<=minValue) return;
	_minLevel = minValue;
	_maxLevel = maxValue;
	if (hWnd == NULL) return;
	::InvalidateRect(hWnd, NULL, true);
}

void LevelControl::SetLevel(double level)
{
	if (_level==level) return;

	if (level>_maxLevel)
		level = _maxLevel;
	else if (level<_minLevel)
		level = _minLevel;

	RECT rc;
	double levelA = Normalize(level);
	double levelB =Normalize(_level);

	if (levelA>levelB)
	{
		double tmp = levelA;
		levelA = levelB;
		levelB = tmp;
	}

	//wchar_t texto[256];
	//_snwprintf(texto, 256, L"%f, %f, %f", level, levelA, levelB);
	//win.SetWindowText(texto);

	int indexA = (int)(levelA*_blockCount);
	int indexB = (int)(levelB*_blockCount);

	if (indexA==indexB)
	{
		indexA--;
		indexB++;
	}
	if (indexA>=_blockCount) indexA = _blockCount-1;
	if (indexB>=_blockCount) indexB = _blockCount-1;

	//wchar_t texto[256];
	//_snwprintf(texto, 256, L"%f, %d, %d", level, indexA, indexB);
	//win.SetWindowText(texto);
	
	rc = levels[indexA].rc;
	rc.right = levels[indexB].rc.right;
	_level = level;
	if (hWnd == NULL) return;
	::InvalidateRect(hWnd, &rc, false);
}

double LevelControl::Normalize(double level)
{
	double stdLevel = (level - _minLevel)/(_maxLevel - _minLevel);
	if (stdLevel<0.0) stdLevel = 0.0;
	if (stdLevel>1.0) stdLevel = 0.9999;
	return stdLevel;
}

COLORREF LevelControl::GetOffColor(COLORREF color)
{
	int red = GetRValue(color);
	int green = GetGValue(color);
	int blue = GetBValue(color);
	//

	if (red>100)
	{
		red -= 195;
		if (red<60) red = 60;
	}
	else
	{
		red = 0;
	}
	//
	if (green>100)
	{
		green -= 195;
		if (green<60) green = 60;
	}
	else
	{
		green = 0;
	}
	//
	if (blue>100)
	{
		blue -= 195;
		if (blue<60) blue = 60;

	}
	else
	{
		blue = 0;
	}
	return RGB(red, green, blue);
}

void LevelControl::OnPaintControl(Win::Gdi& gdi)
{
	int i;
	HBRUSH brush[6];
	brush[0] = CreateSolidBrush(GetOffColor(_lineColor));
	brush[1] = CreateSolidBrush(GetOffColor(_warningColor));
	brush[2] = CreateSolidBrush(GetOffColor(_errorColor));
	brush[3] = CreateSolidBrush(_lineColor);
	brush[4] = CreateSolidBrush(_warningColor);
	brush[5] = CreateSolidBrush(_errorColor);
	Win::Gdi::Brush brushBack(_backColor);

	double stdLevel = Normalize(_level);
	HDC hdc = gdi.GetHDC();
	RECT rcPaint = gdi.GetRcPaint();
	gdi.FillRect(rcPaint, brushBack);

	//________________________________________________ Paint blocks
	for(i=0; i<_blockCount; i++)
	{
		if (Win::Gdi::DoRectOverlap(levels[i].rc, rcPaint))
		{
			if (stdLevel<levels[i].level)
				::FillRect(hdc, &levels[i].rc, brush[levels[i].brushOffIndex]);
			else
				::FillRect(hdc, &levels[i].rc, brush[levels[i].brushOnIndex]);
		}
	}

	for(i = 0; i<6; i++) ::DeleteObject(brush[i]);
}

void LevelControl::OnSizePrivate()
{
	//______________________________________________ compute padding
	_padding = MINIMUM((int)(0.3*this->width + 0.5), (int)(0.15*this->height + 0.5));
	_padding = MAXIMUM(2, _padding);

	_blockHeight = this->height - 2 * _padding;
	if (_blockHeight<2) _blockHeight =1;
	//______________________________________________ compute blockCount
	_blockCount = (int)( (this->width-2* _padding - _blockPadding)/( _blockWidth + _blockPadding));
	if (_blockCount>WIN_LEVELCONTROL_MAX) _blockCount = WIN_LEVELCONTROL_MAX;

	//______________________________________________Fill levels
	const double delta = 1.0/ _blockCount;
	for(int i=0; i<_blockCount; i++)
	{
		levels[i].rc.top = _padding;
		levels[i].rc.bottom = this->height- _padding;
		levels[i].rc.left = _padding+i*(_blockWidth + _blockPadding);
		levels[i].rc.right = levels[i].rc.left + _blockWidth;
		levels[i].level = (i+1)*delta;
		if (levels[i].level <= _normalLevel)
		{
			levels[i].brushOffIndex = 0;
			levels[i].brushOnIndex = 3;
		}
		else if (levels[i].level <= _warningLevel)
		{
			levels[i].brushOffIndex = 1;
			levels[i].brushOnIndex = 4;
		}
		else
		{
			levels[i].brushOffIndex = 2;
			levels[i].brushOnIndex = 5;
		}
	}
}

void LevelControl::Setup(double normalLevel, double warningLevel)
{
	_normalLevel = normalLevel;
	_warningLevel = warningLevel;
	this->OnSizePrivate();
	if (hWnd == NULL) return;
	::InvalidateRect(hWnd, NULL, FALSE);
}

//_____________________________________________________________________ LevelState
LevelState::LevelState(void)
{
	_numDivisions = 5;
	_minValue = 0.0;
	_maxValue = 10.0;
	_level = 5.0;
	_lineColor = RGB(200, 200, 200);
	_logScale = false;
	_displayLevelValue = true;
	_minimum = 0.0;
	_scale = 1.0;
	SetStateCount(0);
}

LevelState::~LevelState(void)
{
}

//lsError.SetState(0, 1.0e-10, 1.0e-8, RGB(0, 0, 250), L"Excellent");
//lsError.SetState(1, 1.0e-8, 1.0e-6, RGB(0, 110, 250), L"Very Good");
//lsError.SetState(2, 1.0e-6, 1.0e-4, RGB(0, 210, 0), L"Good");
//lsError.SetState(3, 1.0e-4, 1.0e-2, RGB(210, 210, 0), L"Bad");
//lsError.SetState(4, 1.0e-2, 1.0e-0, RGB(210, 0, 0), L"Poor");
void LevelState::SetLogScale(bool logScale)
{
	if (_logScale == logScale) return;
	_logScale = logScale;
	OnSizePrivate();
	this->Repaint(NULL, true);
}

bool LevelState::GetLogScale()
{
	return _logScale;
}

void LevelState::SetDisplayLevelValue(bool displayLevelValue)
{
	if (_displayLevelValue == displayLevelValue) return;
	_displayLevelValue = displayLevelValue;
	InvalidateMiddle();
}

bool LevelState::GetDisplayLevelValue()
{
	return _displayLevelValue;
}

void LevelState::InvalidateMiddle()
{
	RECT rect;
	rect.top = 0;
	rect.bottom = this->height;
	const int widthArrow = (int)(WIN_LEVEL_STATE_WIDTH*this->width+0.5);
	const int line1X = (int)((this->width-widthArrow)/2.0+0.5);
	const int line2X = line1X+widthArrow;
	rect.left =line1X;
	rect.right = line2X;
	if (hWnd == NULL) return;
	::InvalidateRect(hWnd, &rect, true);
}

void LevelState::Window_Open(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
}

void LevelState::Window_Size(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
	OnSizePrivate();
}

void LevelState::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, false);
	Win::Gdi gdiBitmap(bitmap, gdi.GetRcPaint(), false);
	if (_hfont) gdiBitmap.SelectFont__(_hfont);
	OnPaintControl(gdiBitmap);
	gdi.DrawDoubleBuffer(bitmap);
}

void LevelState::SetStateCount(int count)
{
	if (count>WIN_LEVEL_STATE_STATES) count = WIN_LEVEL_STATE_STATES;
	_stateCount = count;
	for(int i = 0; i<WIN_LEVEL_STATE_STATES; i++)
	{
		_si[i].color = RGB(255, 255, 255);
		_si[i].minValue = 0.0;
		_si[i].maxValue = 0.0;
		_si[i].text[0]='\0';
	}
}
	
void LevelState::SetState(int index, double minValue, double maxValue, COLORREF color, wchar_t* caption)
{
	if (index<0 || index>= _stateCount) return;
	_si[index].color = color;
	_si[index].minValue = minValue;
	_si[index].maxValue = maxValue;
	lstrcpyn(_si[index].text, caption, 64);
	if (index ==0)
	{
		_minValue = minValue;
		_maxValue = maxValue;
	}
	else
	{
		if (minValue < _minValue) _minValue = minValue;
		if (maxValue > _maxValue) _maxValue = maxValue;
	}
	if (hWnd == NULL) return;
	::InvalidateRect(hWnd, NULL, true);
}

double LevelState::GetLevel()
{
	return _level;
}

void LevelState::SetLevel(double level)
{
	if (level == _level) return;
	_level = level;
	InvalidateMiddle();
}

void LevelState::OnPaintControl(Win::Gdi& gdi)
{
	RECT rect = {0, 0, this->width, this->height};
	RECT rcPaint = gdi.GetRcPaint();
	
	Win::Gdi::Brush brushBack(_backColor);
	gdi.FillRect(rcPaint, brushBack);

	const int widthArrow = (int)(WIN_LEVEL_STATE_WIDTH*this->width+0.5);
	const int line1X = (int)((this->width-widthArrow)/2.0+0.5);
	const int line2X = line1X+widthArrow;
	const int markWidth = (int)(0.1*line1X+0.5);
	Win::Gdi::Pen penGray(PS_SOLID, 1, _lineColor);

	gdi.SelectPen_(penGray);
	gdi.SetBkMode(true);
	//_________________________________________________ Paint main lines
	gdi.Line(line1X, 0, line1X, this->height);
	gdi.Line(line2X, 0, line2X, this->height);

	//_________________________________________________ Compute font height
	if (_hfont) gdi.SelectFont__(_hfont);
	TEXTMETRIC tm;
	gdi.GetTextMetrics(&tm);
	const int fontHeight = tm.tmHeight;

	int i, y;
	wchar_t text[256];
	const double delta = (double)(this->height-fontHeight)/(double) _numDivisions;
	if (_logScale == true)
	{
		_minimum = log10(fabs(_minValue));
		_scale =  _numDivisions*delta/(log10(fabs(_maxValue)) - _minimum);
	}
	else
	{
		_minimum = _minValue;
		_scale =  _numDivisions*delta/(_maxValue - _minValue);
	}
	//__________________________________________________ Paint marks
	const double deltaValue = (_logScale == true) ? (log10(fabs(_maxValue)) - log10(fabs(_minValue)))/ _numDivisions : (_maxValue - _minValue)/ _numDivisions;

	RECT rcMarks;
	rcMarks.top = 0;
	rcMarks.right = width;
	rcMarks.bottom = height;
	rcMarks.left = line1X;
	
	if (gdi.DoRcPaintOverlap(rcMarks))
	{
		gdi.SetTextColor(_textColor);
		double val = 0.0;
		for(i = 0; i< _numDivisions+1; i++)
		{
			y = (int)(i*delta+0.5+fontHeight*0.5);
			gdi.Line(line2X, y, line2X+markWidth, y);
			//	
			val = _minimum+(_numDivisions-i)*deltaValue;
			if (_logScale == true)
			{
				Sys::Convert::ToString(pow(10.0, val), text, 256, true);
				//_snwprintf_s(text, 256, _TRUNCATE, L"%g", pow(10.0, val));
			}
			else
			{
				Sys::Convert::ToString(val, text, 256, true);
				//_snwprintf_s(text, 256, _TRUNCATE, L"%g", val);
			}
			gdi.TextOut((int)(line2X+markWidth*1.5+0.5), (int)(y-fontHeight/2+0.5), text);
			//
			y = (int)((i+0.5)*delta+0.5+fontHeight*0.5);
			gdi.Line(line2X, y, (int)(line2X+markWidth/2+0.5), y);
		}
	}
	//__________________________________________________ Paint middle rectangule
	//Win::Gdi::Brush brushMiddle(RGB(230, 240, 255));
	//rect.top = 0;
	//rect.bottom = height;
	//rect.left = line1X+1;
	//rect.right = line2X;
	//gdi.FillRect(&rect, brushMiddle);
	
	
	//___________________________________________________ Paint level
	y = this->MapToScreen(_level, fontHeight);
	if (y < 0) y = 0;
	if (y > height) y = height;
	if (_displayLevelValue == true)
	{
		Sys::Convert::ToString(_level, text, 256, true);
		rect.top = (int)(y-1.2*fontHeight);
		rect.bottom = (int)(y-0.2*fontHeight+0.5);
		rect.left = line1X+1;
		rect.right = line2X;
		gdi.TextOutCenter(rect, text, true, true);

		//if (_logScale == true)
		//{
		//	//Sys::Convert::ToString(log10(fabs(value)
		//}
	}

	POINT triangle[11];
	Win::Gdi::Brush brushMark(_textColor);
	//gdi.SelectPen_(penBlue);
	gdi.SelectBrush_(brushMark);
	//gdi.Line(line1X, y, line2X, y);
	//gdi.RoundRect(line1X+WIN_LEVEL_STATE_LEVELWIDTH, y-WIN_LEVEL_STATE_LEVELWIDTH, line2X-WIN_LEVEL_STATE_LEVELWIDTH, y+WIN_LEVEL_STATE_LEVELWIDTH, WIN_LEVEL_STATE_LEVELWIDTH, WIN_LEVEL_STATE_LEVELWIDTH);
	//
	//_______________________________________________ left triangule
	triangle[0].x = line1X;
	triangle[0].y = y;
	//
	triangle[1].x = line1X+2*WIN_LEVEL_STATE_LEVELWIDTH;
	triangle[1].y = y-2*WIN_LEVEL_STATE_LEVELWIDTH;
	//
	triangle[2].x = line1X+2*WIN_LEVEL_STATE_LEVELWIDTH;
	triangle[2].y = y-WIN_LEVEL_STATE_LEVELWIDTH;
	//
	triangle[3].x = line2X-2*WIN_LEVEL_STATE_LEVELWIDTH;
	triangle[3].y = y-WIN_LEVEL_STATE_LEVELWIDTH;
	//
	triangle[4].x = line2X-2*WIN_LEVEL_STATE_LEVELWIDTH;
	triangle[4].y = y-2*WIN_LEVEL_STATE_LEVELWIDTH;
	//
	triangle[5].x = line2X;
	triangle[5].y = y;
	//
	triangle[6].x = line2X-2*WIN_LEVEL_STATE_LEVELWIDTH;
	triangle[6].y = y+2*WIN_LEVEL_STATE_LEVELWIDTH;
	//
	triangle[7].x = line2X-2*WIN_LEVEL_STATE_LEVELWIDTH;
	triangle[7].y = y+WIN_LEVEL_STATE_LEVELWIDTH;
	//
	triangle[8].x = line1X+2*WIN_LEVEL_STATE_LEVELWIDTH;
	triangle[8].y = y+WIN_LEVEL_STATE_LEVELWIDTH;
	//
	triangle[9].x = line1X+2*WIN_LEVEL_STATE_LEVELWIDTH;
	triangle[9].y = y+2*WIN_LEVEL_STATE_LEVELWIDTH;
	//
	triangle[10].x = line1X;
	triangle[10].y = y;
	//
	gdi.Polygon(triangle, 11);

	//________ Paint State Info
	rect.left = 0;
	rect.right = line1X;
	Win::Gdi::Brush brushStateInfo;

	for(i=0; i<WIN_LEVEL_STATE_STATES; i++)
	{
		rect.top = this->MapToScreen(_si[i].maxValue, fontHeight);
		rect.bottom = this->MapToScreen(_si[i].minValue, fontHeight);
		brushStateInfo.CreateSolid(_si[i].color);
		if (gdi.DoRcPaintOverlap(rect))
		{
			gdi.FillRect(rect, brushStateInfo);
			if (Win::Gdi::Color3D::IsCloseToBlack(_si[i].color))
				gdi.SetTextColor(RGB(255, 255, 255));
			else
				gdi.SetTextColor(RGB(0, 0, 0));
			gdi.TextOutCenter(rect, _si[i].text, true, true);
		}
	}

	//________________________________ Text
	if (_text.length()>0)
	{
		gdi.SetTextColor(_textColor);

		SIZE size;
		LOGFONT logfont;
		this->GetLogfont(logfont);
		logfont.lfEscapement = 900;
		logfont.lfOrientation = 900;

		Win::Gdi::Font fontVertical;
		fontVertical.Create(logfont);
		gdi.SelectFont_(fontVertical);
		gdi.GetTextExtentPoint32(_text.c_str(), size);
		gdi.SetTextAlign(TA_LEFT | TA_TOP);
		gdi.TextOut( (int)(width - 1.2*fontHeight+0.5), //x
			(int)(height/2.0 + size.cx/2.0+0.5), //y
			_text.c_str());
	}
}

int LevelState::GetStateCount()
{
	return _stateCount;
}

int LevelState::MapToScreen(double value, int fontHeight)
{
	if (_logScale == true) value = log10(fabs(value));
	return (int)( this->height - (value - _minimum)*_scale-0.5*fontHeight+0.5);
}

//_____________________________________________________________________ Monitor
Monitor::Monitor(void)
{
	_data = NULL;
	_dataSize = 0;
	_dataScreenCount = 0;
	_offsetData = 0;
	_min = 0;
	_max = 100;
	_lineOffset = 0;
	_squareSize = 4;  // in resolution X units
	_scale = 1.0;
	SetResolution(3);
	_backColor = RGB(0, 0, 0);
	_lineColor = RGB(0, 60, 0);
	_lineColor1 = RGB(0, 255, 0);
}

Monitor::~Monitor(void)
{
	if (_data) delete [] _data;
}

void Monitor::Window_Open(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
}

void Monitor::Window_Size(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
	OnSizePrivate();
}

void Monitor::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, false);
	Win::Gdi gdiBitmap(bitmap, gdi.GetRcPaint(), false);
	if (_hfont) gdiBitmap.SelectFont__(_hfont);
	OnPaintControl(gdiBitmap);
	gdi.DrawDoubleBuffer(bitmap);
}

COLORREF Monitor::GetLineColor1()
{
	return _lineColor1;
}

void Monitor::SetLineColor1(COLORREF color)
{
	_lineColor1 = color;
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

void Monitor::SetResolution(int resolution)
{
	_resolutionX = resolution;
	if (_data) delete [] _data;
	_dataSize = 1 + GetSystemMetrics(SM_CXSCREEN)/_resolutionX;
	_data = new double[_dataSize];
	ZeroMemory(_data, sizeof(double)*_dataSize);
	//
	_offsetData = 0;
	//m_nOffsetData = m_nDataSize-1;
}

void Monitor::SetAll(double value)
{
	if (_data==NULL) return;
	for(int i=0; i<_dataSize; i++) _data[i] = value;
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

void Monitor::SetSquareSize(int size)
{
	_squareSize = size;
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

void Monitor::SetRange(double minimum, double maximum)
{
	_min = minimum;
	_max = maximum;

	OnSizePrivate();
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

void Monitor::Clear()
{
	//m_nOffsetData = m_nDataSize-1;
	_offsetData=0;
	ZeroMemory(_data, sizeof(double)*_dataSize);
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

void Monitor::AddValue(double value)
{
	if(value < _min) value = _min-1;
	if (value> _max) value = _max+1;
	_lineOffset  += _resolutionX;
	if (_lineOffset >= _squareSize * _resolutionX) _lineOffset = 0;
	//
	_data[_offsetData] = value;
	_offsetData++;
	if (_offsetData >= _dataSize) _offsetData=0;

	RECT rect;
	this->Scroll(- _resolutionX, 0, &rect);
}

void Monitor::OnPaintControl(Win::Gdi& gdi)
{
	const int spacing = _squareSize * _resolutionX;
	Gdi::Pen penLine;
	Gdi::Pen penData;
	int i = 0, j = 0;
	const int horzLineCount = (int)(this->height/spacing+1.5);
	const int vertLineCount = (int)(this->width/spacing+1.5);
	const int dataCount = (int)(this->width/ _resolutionX+1.5);
	int x, y;

	const RECT rcPaint = gdi.GetRcPaint();

	Win::Gdi::Brush brushBack;
	if (Enabled)
	{
		brushBack.CreateSolid(_backColor);
		penLine.Create(PS_SOLID, 1, _lineColor);
	}
	else
	{
		brushBack.CreateSolid(WIN_BACK_DISABLED);
		penLine.Create(PS_SOLID, 1, WIN_TEXT_DISABLED);
	}
	gdi.FillRect(rcPaint, brushBack);

	penData.Create(PS_SOLID, 1, _lineColor1);
	gdi.SelectPen_(penLine);

	//************************************************************** Horz Lines
	for(i = 0; i< horzLineCount; i++)
	{
		y = this->height - i *spacing - 1;

		if (rcPaint.top<=y && y<=rcPaint.bottom) // Check if invalid
		{
			gdi.MoveToEx(rcPaint.left, y);
			gdi.LineTo(rcPaint.right, y);
		}
	}

	//************************************************************** Vert Lines
	int index1 = rcPaint.left/spacing-2;
	int index2 = rcPaint.right/spacing+2;

	for(i = index1; i< index2; i++)
	{
		x = i * spacing  - _lineOffset + 1;
		if (rcPaint.left<=x && x<=rcPaint.right) // Check if invalid
		{
			gdi.MoveToEx(x, rcPaint.top);
			gdi.LineTo(x, rcPaint.bottom);
		}
	} 

	//for(i = 0; i< nVertLineCount; i++)
	//{
	//	x = this->width - i * nSpacing  - m_nLineOffset -1;
	//	if (dc.GetRcPaint().left<=x && x<=dc.GetRcPaint().right) // Check if invalid
	//	{
	//		dc.MoveToEx(x, dc.GetRcPaint().top);
	//		dc.LineTo(x, dc.GetRcPaint().bottom);
	//	}
	//} 

	//************************************************************** Data
	gdi.SelectPen_(penData);

	//wchar_t texto[256];

	index1 = rcPaint.left/ _resolutionX - 4;
	if (index1<0) index1 = 0;
	index2 = rcPaint.right/_resolutionX+4;//m_nDataScreenCount;
	//if (index2>=m_nDataScreenCount) index2 = m_nDataScreenCount-1;
	//_snwprintf(texto, 256, L"%d, %d, %d", dc.GetRcPaint().left, index1, index2);
	//::SetWindowText(this->GetParent(), texto);
	for(i = index1; i< index2; i++)
	{
		if (_offsetData>_dataScreenCount)
		{
			j = _offsetData - _dataScreenCount+i;
		}
		else
		{
			if (_dataSize - (_dataScreenCount - _offsetData)+i < _dataSize)
				j = _dataSize - (_dataScreenCount - _offsetData)+i;
			else
				j = - _dataScreenCount + _offsetData+i;
		}

		x = i * _resolutionX+2;
		y =  (int)(this->height - _scale * (_data[j] - _min) - 0.5);

		if (i==index1)
		{
			gdi.MoveToEx(x, y);
		}
		else
		{
			if (rcPaint.left - _resolutionX<=x && x<=rcPaint.right+ _resolutionX) // Check if invalid
			{
				gdi.LineTo(x, y);
			}
		}
	} 

	////************************************************************** Data
	//dc.SelectPen_(penData);

	//if (m_nOffsetData>m_nDataScreenCount)
	//{
	//	j = m_nOffsetData - m_nDataScreenCount;
	//}
	//else
	//{
	//	j = m_nDataSize - (m_nDataScreenCount-m_nOffsetData);
	//}
	//if (j>=m_nDataSize) j = 0;
	//if (j<0) j = m_nDataSize-1; 

	////index1 = dc.GetRcPaint().left/nSpacing-2;
	////index2 = dc.GetRcPaint().right/nSpacing+2;
	//for(i = 0; i< nDataCount; i++)
	//{
	//	x = i * m_nResolutionX;
	//	y =  (int)(this->height - m_dScale * (m_pData[j]-m_dMin) - 0.5);
	//	j++;
	//	if (j>=m_nDataSize) j = 0;

	//	if (i==0)
	//	{
	//		dc.MoveToEx(x, y);
	//	}
	//	else
	//	{
	//		if (dc.GetRcPaint().left-m_nResolutionX<=x && x<=dc.GetRcPaint().right+m_nResolutionX) // Check if invalid
	//		{
	//			dc.LineTo(x, y);
	//		}
	//	}
	//} 

	////************************************************************** Data
	//dc.SelectPen_(penData);
	//j = m_nOffsetData -1;
	//if (j<0) j = m_nDataSize-1;
	//for(i = 0; i< nDataCount; i++)
	//{
	//	x = width - i * m_nResolutionX - 1;
	//	y =  (int)(this->height - m_dScale * (m_pData[j]-m_dMin) - 0.5);
	//	j--;
	//	if (j<0) j = m_nDataSize-1;
	//	if (i==0)
	//	{
	//		dc.MoveToEx(x, y);
	//	}
	//	else
	//	{
	//		if (dc.GetRcPaint().left-m_nResolutionX<=x && x<=dc.GetRcPaint().right+m_nResolutionX) // Check if invalid
	//		{
	//			dc.LineTo(x, y);
	//		}
	//	}
	//} 
}

void Monitor::OnSizePrivate()
{
	_scale = height/(_max - _min);
	_dataScreenCount = 1 + width/ _resolutionX;
}

//_____________________________________________________________________ Monitor3
Monitor3::Monitor3(void)
{
	_data1 = NULL;
	_data2 = NULL;
	_data3 = NULL;
	_dataSize = 0;
	_dataScreenCount = 0;
	_offsetData = 0;
	_min = 0;
	_max = 100;
	_lineOffset = 0;
	_squareSize = 4;  // in resolution X units
	_scale = 1.0;
	SetResolution(3);
	//
	_backColor = RGB(0, 0, 0);
	_lineColor = RGB(0, 60, 0);
	//
	_lineColor1 = RGB(0, 255, 0);
	_lineColor2 = RGB(200, 200, 0);
	_lineColor3 = RGB(230, 10, 10);
}

Monitor3::~Monitor3(void)
{
	if (_data1) delete []  _data1;
	if (_data2) delete [] _data2;
	if (_data3) delete [] _data3;
}

void Monitor3::Window_Open(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
}

void Monitor3::Window_Size(Win::Event& e)
{
	bitmap.CreateCompatible(hWnd, width, height);
	OnSizePrivate();
}

void Monitor3::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, false);
	Win::Gdi gdiBitmap(bitmap, gdi.GetRcPaint(), false);
	if (_hfont) gdiBitmap.SelectFont__(_hfont);
	OnPaintControl(gdiBitmap);
	gdi.DrawDoubleBuffer(bitmap);
}

COLORREF Monitor3::GetLineColor1()
{
	return _lineColor1;
}

void Monitor3::SetLineColor1(COLORREF color)
{
	_lineColor1 = color;
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

COLORREF Monitor3::GetLineColor2()
{
	return _lineColor2;
}

void Monitor3::SetLineColor2(COLORREF color)
{
	_lineColor2 = color;
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

COLORREF Monitor3::GetLineColor3()
{
	return _lineColor3;
}

void Monitor3::SetLineColor3(COLORREF color)
{
	_lineColor3 = color;
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}	

void Monitor3::SetResolution(int resolution)
{
	_resolutionX = resolution;
	if (_data1) delete [] _data1;
	if (_data2) delete [] _data2;
	if (_data3) delete [] _data3;
	_dataSize = 1 + GetSystemMetrics(SM_CXSCREEN)/ _resolutionX;
	_data1 = new double[_dataSize];
	_data2 = new double[_dataSize];
	_data3 = new double[_dataSize];
	ZeroMemory(_data1, sizeof(double)* _dataSize);
	ZeroMemory(_data2, sizeof(double)* _dataSize);
	ZeroMemory(_data3, sizeof(double)* _dataSize);
	//
	_offsetData = 0;
	//m_nOffsetData = m_nDataSize-1;
}

void Monitor3::SetAll(double value1, double value2, double value3)
{
	int i;
	if (_data1==NULL) return;
	for(i=0; i< _dataSize; i++) _data1[i] = value1;
	//
	if (_data1==NULL) return;
	for(i=0; i< _dataSize; i++) _data2[i] = value2;
	//
	if (_data1==NULL) return;
	for(i=0; i< _dataSize; i++) _data2[i] = value3;
	//
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

void Monitor3::SetSquareSize(int size)
{
	_squareSize = size;
	this->OnSizePrivate();
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

void Monitor3::SetRange(double minimum, double maximum)
{
	_min = minimum;
	_max = maximum;
	this->OnSizePrivate();
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

void Monitor3::Clear()
{
	//m_nOffsetData = m_nDataSize-1;
	_offsetData=0;
	ZeroMemory(_data1, sizeof(double)* _dataSize);
	ZeroMemory(_data2, sizeof(double)*_dataSize);
	ZeroMemory(_data3, sizeof(double)*_dataSize);
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

void Monitor3::AddValue(double value1, double value2, double value3)
{
	if(value1< _min) value1 = _min-1;
	if(value2<_min) value2 = _min-1;
	if(value3<_min) value3 = _min-1;
	if (value1> _max) value1 = _max+1;
	if (value2>_max) value2 = _max+1;
	if (value3>_max) value3 = _max+1;
	_lineOffset  += _resolutionX;
	if (_lineOffset>= _squareSize * _resolutionX) _lineOffset = 0;
	//
	_data1[_offsetData] = value1;
	_data2[_offsetData] = value2;
	_data3[_offsetData] = value3;
	_offsetData++;
	if (_offsetData >= _dataSize) _offsetData=0;
	//
	//***************************************************** Scroll Window
	RECT rect;
	this->Scroll(- _resolutionX, 0, &rect);
}

void Monitor3::OnPaintControl(Win::Gdi& gdi)
{
	const int spacing = _squareSize * _resolutionX;
	Gdi::Pen penLine;
	Gdi::Pen penData1, penData2, penData3;
	int i = 0, j = 0;
	const int horzLineCount = (int)(this->height/spacing+1.5);
	const int vertLineCount = (int)(this->width/spacing+1.5);
	const int dataCount = (int)(this->width/ _resolutionX+1.5);
	int x, y;
	const RECT rcPaint = gdi.GetRcPaint();
	Win::Gdi::Brush brushBack;
	if (Enabled)
	{
		brushBack.CreateSolid(_backColor);
		penLine.Create(PS_SOLID, 1, _lineColor);
	}
	else
	{
		brushBack.CreateSolid(WIN_BACK_DISABLED);
		penLine.Create(PS_SOLID, 1, WIN_TEXT_DISABLED);
	}
	gdi.FillRect(rcPaint, brushBack);

	penData1.Create(PS_SOLID, 1, _lineColor1);
	penData2.Create(PS_SOLID, 1, _lineColor2);
	penData3.Create(PS_SOLID, 1, _lineColor3);
	gdi.SelectPen_(penLine);

	//************************************************************** Horz Lines
	for(i = 0; i< horzLineCount; i++)
	{
		y = this->height - i *spacing - 1;

		if (rcPaint.top<=y && y<=rcPaint.bottom) // Check if invalid
		{
			gdi.MoveToEx(rcPaint.left, y);
			gdi.LineTo(rcPaint.right, y);
		}
	}

	//************************************************************** Vert Lines
	int index1 = rcPaint.left/spacing-2;
	int index2 = rcPaint.right/spacing+2;

	for(i = index1; i< index2; i++)
	{
		x = i * spacing  - _lineOffset + 1;
		if (rcPaint.left<=x && x<= rcPaint.right) // Check if invalid
		{
			gdi.MoveToEx(x, rcPaint.top);
			gdi.LineTo(x, rcPaint.bottom);
		}
	} 

	//for(i = 0; i< nVertLineCount; i++)
	//{
	//	x = this->width - i * nSpacing  - m_nLineOffset -1;
	//	if (dc.GetRcPaint().left<=x && x<=dc.GetRcPaint().right) // Check if invalid
	//	{
	//		dc.MoveToEx(x, dc.GetRcPaint().top);
	//		dc.LineTo(x, dc.GetRcPaint().bottom);
	//	}
	//} 

	//************************************************************** Data
	index1 = rcPaint.left/ _resolutionX-4;
	if (index1<0) index1 = 0;
	index2 = rcPaint.right/_resolutionX+4;//m_nDataScreenCount;
	//if (index2>=m_nDataScreenCount) index2 = m_nDataScreenCount-1;
	//_snwprintf(texto, 256, L"%d, %d, %d", dc.GetRcPaint().left, index1, index2);
	//::SetWindowText(this->GetParent(), texto);
	gdi.SelectPen_(penData1);
	this->PaintData(gdi, index1, index2, _data1);
	gdi.SelectPen_(penData2);
	this->PaintData(gdi, index1, index2, _data2);
	gdi.SelectPen_(penData3);
	this->PaintData(gdi, index1, index2, _data3);
	//for(i = index1; i< index2; i++)
	//{
	//	if (m_nOffsetData>m_nDataScreenCount)
	//	{
	//		j = m_nOffsetData - m_nDataScreenCount+i;
	//	}
	//	else
	//	{
	//		if (m_nDataSize - (m_nDataScreenCount-m_nOffsetData)+i<m_nDataSize)
	//			j = m_nDataSize - (m_nDataScreenCount-m_nOffsetData)+i;
	//		else
	//			j = - m_nDataScreenCount+m_nOffsetData+i;
	//	}

	//	x = i * m_nResolutionX+2;
	//	y =  (int)(this->height - m_dScale * (m_pData[j]-m_dMin) - 0.5);

	//	if (i==index1)
	//	{
	//		dc.MoveToEx(x, y);
	//	}
	//	else
	//	{
	//		if (dc.GetRcPaint().left-m_nResolutionX<=x && x<=dc.GetRcPaint().right+m_nResolutionX) // Check if invalid
	//		{
	//			dc.LineTo(x, y);
	//		}
	//	}
	//} 

	////************************************************************** Data
	//dc.SelectPen_(penData);

	//if (m_nOffsetData>m_nDataScreenCount)
	//{
	//	j = m_nOffsetData - m_nDataScreenCount;
	//}
	//else
	//{
	//	j = m_nDataSize - (m_nDataScreenCount-m_nOffsetData);
	//}
	//if (j>=m_nDataSize) j = 0;
	//if (j<0) j = m_nDataSize-1; 

	////index1 = dc.GetRcPaint().left/nSpacing-2;
	////index2 = dc.GetRcPaint().right/nSpacing+2;
	//for(i = 0; i< nDataCount; i++)
	//{
	//	x = i * m_nResolutionX;
	//	y =  (int)(this->height - m_dScale * (m_pData[j]-m_dMin) - 0.5);
	//	j++;
	//	if (j>=m_nDataSize) j = 0;

	//	if (i==0)
	//	{
	//		dc.MoveToEx(x, y);
	//	}
	//	else
	//	{
	//		if (dc.GetRcPaint().left-m_nResolutionX<=x && x<=dc.GetRcPaint().right+m_nResolutionX) // Check if invalid
	//		{
	//			dc.LineTo(x, y);
	//		}
	//	}
	//} 

	////************************************************************** Data
	//dc.SelectPen_(penData);
	//j = m_nOffsetData -1;
	//if (j<0) j = m_nDataSize-1;
	//for(i = 0; i< nDataCount; i++)
	//{
	//	x = width - i * m_nResolutionX - 1;
	//	y =  (int)(this->height - m_dScale * (m_pData[j]-m_dMin) - 0.5);
	//	j--;
	//	if (j<0) j = m_nDataSize-1;
	//	if (i==0)
	//	{
	//		dc.MoveToEx(x, y);
	//	}
	//	else
	//	{
	//		if (dc.GetRcPaint().left-m_nResolutionX<=x && x<=dc.GetRcPaint().right+m_nResolutionX) // Check if invalid
	//		{
	//			dc.LineTo(x, y);
	//		}
	//	}
	//} 
}

void Monitor3::PaintData(Win::Gdi& gdi, int index1, int index2, double* data)
{
	int i, j, x, y;
	const RECT rcPaint = gdi.GetRcPaint();

	for(i = index1; i< index2; i++)
	{
		if (_offsetData > _dataScreenCount)
		{
			j = _offsetData - _dataScreenCount+i;
		}
		else
		{
			if (_dataSize - (_dataScreenCount - _offsetData)+i < _dataSize)
				j = _dataSize - (_dataScreenCount - _offsetData)+i;
			else
				j = - _dataScreenCount + _offsetData+i;
		}

		x = i * _resolutionX+2;
		y =  (int)(this->height - _scale * (data[j] - _min) - 0.5);

		if (i==index1)
		{
			gdi.MoveToEx(x, y);
		}
		else
		{
			if (rcPaint.left - _resolutionX<=x && x <= rcPaint.right + _resolutionX) // Check if invalid
			{
				gdi.LineTo(x, y);
			}
		}
	} 
}

void Monitor3::OnSizePrivate()
{
	_scale = this->height/(_max- _min);
	_dataScreenCount = 1+this->width/ _resolutionX;
}

//____________________________________________________________SerialPort
//Example:
//class MyPort : public Mt::SerialPort
//{
//public:
//	MyPort(void){};
//	~MyPort(void){};
//	void RxNotify(int byteCount)
//	{
//		wchar_t text[256];
//		this->readBuffer(text, byteCount);
//		edit->AppendText(text);
//	}
//	void TxNotify(){};
//	Win::Textbox* edit;
//};
//
//LRESULT TestingSerial::OnCreate(Win::Event& e)
//{
//	edit.Create(0, 0, 
//		WS_VISIBLE|WS_CHILD|ES_RIGHT|ES_AUTOVSCROLL|WS_VSCROLL|ES_MULTILINE, 
//		0, 0, 100, 100, hWnd, (HMENU)IDC_STATIC, NULL);
//	myPort.edit = &edit;
//	DCB dcb;
//	myPort.InitializeDcbDlg(L"COM1", hWnd, dcb);
//	myPort.Open(L"COM1", dcb);
//	return 0;
//}
//
//LRESULT TestingSerial::OnChar(Win::Event& e)
//{
//	myPort.writeByte((char)wParam);
//	return 0;
//}

SerialPort::SerialPort(void)
{
	lstrcpyn(portName, L"No port", 32);
	port = INVALID_HANDLE_VALUE;
	hInputThread = INVALID_HANDLE_VALUE;
	hOutputThread = INVALID_HANDLE_VALUE;
	breakDuration=0;
	dwErrors=0;
	error_status=Win::SerialPort::Success;
	bInputThreadReading=false;
	iBreakDuration = 1000;
	byteCount = 0;
	//
	rxCount = 0;
	txCount = 0;
	isCts = false;
	isDsr = false;
	isCd = false;
	isRi = false;
	errorCaption = NULL;
}

bool SerialPort::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_COMMAND) return false;
	const int id = LOWORD(e.wParam);
	const int notificationd = HIWORD(e.wParam);
	if (id != this->id) return false;
	if (notificationd!=notification) return false;
	return true;
}

SerialPort::~SerialPort(void)
{
	if (port!=INVALID_HANDLE_VALUE) 
	{
		this->eventKillOutputThread.Set();
		this->eventKillInputThread.Set();
		HANDLE h[2]={this->hInputThread, this->hOutputThread};
		WaitForMultipleObjects(2, h, TRUE, INFINITE);
		::CloseHandle(port);
		port = INVALID_HANDLE_VALUE;
	}
}

void SerialPort::UpdateRow(int index)
{
	RECT rc;
	rc.left = 0;
	rc.right = this->width;
	rc.top = (int)(_fontHeight/2.0  + index * 1.5 * _fontHeight+0.5);
	rc.bottom = (int)(rc.top + 1.5 * _fontHeight + 0.5);
	::InvalidateRect(hWnd, &rc, FALSE);
}

void SerialPort::RxNotify(int byteCount)
{
	rxCount += byteCount;
	//errorCaption = L"";
	UpdateRow(1);
	//UpdateRow(7);
	//
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_RX), (LPARAM)byteCount);
}

void SerialPort::TxNotify()
{
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_TX), (LPARAM)0);
	txCount = 0;
	errorCaption = L"";
	UpdateRow(2);
	UpdateRow(7);
}

void SerialPort::BreakDetectNotify()
{
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_BREAKDETECT), (LPARAM)0);
	errorCaption = L"Break detect";
	UpdateRow(7);
}

void SerialPort::FramingErrorNotify()
{
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_FRAMINGERROR), (LPARAM)0);
	errorCaption = L"Framing error";
	UpdateRow(7);
}

void SerialPort::HardwareOverrunErrorNotify()
{
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_HARDWAREOVERRUN), (LPARAM)0);
	errorCaption = L"Hardware overrun";
	UpdateRow(7);
}

void SerialPort::ParityErrorNotify()
{
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_PARITYERROR), (LPARAM)0);
	errorCaption = L"Parity error";
	UpdateRow(7);
}

void SerialPort::SoftwareOverrunErrorNotify()
{
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_SOFTWAREOVERRUN), (LPARAM)0);
	errorCaption = L"Software overrun";
	UpdateRow(7);
}

void SerialPort::CtsNotify(bool status)
{
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_CTS), (LPARAM)status);
	isCts = status;
	UpdateRow(3);
}

void SerialPort::DsrNotify(bool status)
{
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_DSR), (LPARAM)status);
	isDsr = status;
	UpdateRow(4);
}

void SerialPort::CdNotify(bool status)
{
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_CD), (LPARAM)status);
	isCd = status;
	UpdateRow(5);
}

void SerialPort::RiNotify(bool status)
{
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_RI), (LPARAM)status);
	isRi = status;
	UpdateRow(6);
}

void SerialPort::Close()
{
	if (port!=INVALID_HANDLE_VALUE) 
	{
		this->eventKillOutputThread.Set();
		this->eventKillInputThread.Set();
		HANDLE h[2]={this->hInputThread, this->hOutputThread};
		WaitForMultipleObjects(2, h, TRUE, INFINITE);
		::CloseHandle(port);
		port = INVALID_HANDLE_VALUE;
	}
	::InvalidateRect(hWnd, NULL, true);
}

// portName: L"COM1", L"COM2", etc. for ports greater than 9 L"\\\\.\\COM10"
bool SerialPort::Open(wchar_t* portName, DCB& dcb)
{
	Close();
	if (port!=INVALID_HANDLE_VALUE) return false;
	port = CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);
	if (port==INVALID_HANDLE_VALUE)
	{
		Sys::DisplayLastError(NULL, L"Win::SerialPort Open CreateFile");
		return false;
	}
	breakDuration=0;
	dwErrors=0;
	SetLastError(0);
	COMMTIMEOUTS timeouts={0x01, 0, 0, 0, 0};
	SetCommTimeouts(port, &timeouts);
	SetupComm(port, 500, 500); // Set buffer sizes;
	error_status=SerialPort::Success;
	if (SetCommState(port, &dcb)==0)
	{
		errorCaption = L"Open error";
		UpdateRow(7);
		Sys::DisplayLastError(NULL, L"Win::SerialPort Open SetCommState");
		return false;
	}
	//
	rxCount = 0;
	txCount = 0;
	isCts = false;
	isDsr = false;
	isCd = false;
	isRi = false;
	errorCaption = NULL;
	lstrcpyn(this->portName, portName, 32);
	::InvalidateRect(hWnd, NULL, true);
	//
	unsigned int threadId;
	hInputThread = (HANDLE)_beginthreadex(NULL, 0, InputThreadFunc, (LPVOID)this, 0, &threadId);
	hOutputThread = (HANDLE)_beginthreadex(NULL, 0, OutputThreadFunc, (LPVOID)this, 0, &threadId);

	return true;
}

void SerialPort::InitializeDcbDefaults(DCB& dcb)
{
	dcb.BaudRate = 38400; // Default baud rate
	dcb.ByteSize = 8; //Default word size
	dcb.DCBlength = sizeof(DCB);
	dcb.EofChar = 0; // Not using EOF char
	dcb.ErrorChar = 0; //Not using error char
	dcb.EvtChar = 0; //Not uisng event char
	dcb.fAbortOnError = TRUE; // Always respond to errors
	dcb.fBinary = TRUE;
	dcb.fDsrSensitivity = FALSE; //Ignore incoming DSR
	dcb.fDtrControl = DTR_CONTROL_ENABLE; //Assert DTR
	dcb.fDummy2 = 0;
	dcb.fErrorChar = FALSE; //No special char on line errors
	dcb.fInX = FALSE; //No incoming XON/XOFF handshaking
	dcb.fNull = FALSE; //No null detection
	dcb.fOutX = FALSE; //No outbound XON/XOFF handshaking
	dcb.fOutxCtsFlow = FALSE; //No RTS/CTS flow control
	dcb.fOutxDsrFlow = FALSE; //No DTR/DSR flow control
	dcb.fParity = FALSE; //No parity
	dcb.Parity = NOPARITY; //NOPARITY, EVENPARITY, ODDPARITY, MARKPARITY, SPACEPARITY
	dcb.fRtsControl = RTS_CONTROL_ENABLE; //Assert RTS
	dcb.fTXContinueOnXoff = FALSE; //No special action on Xoff
	dcb.StopBits = ONESTOPBIT; //ONESTOPBIT, TWOSTOPBITS
	//dcb.wReserved = 0;
	dcb.wReserved1 = 0;
	dcb.XoffChar = 0x13; //XOFF is ^S
	dcb.XonChar = 0x11; //XON is ^Q
	dcb.XoffLim = 128; // Send XOFF when space left = 128
	dcb.XonLim = 128; //Send XON when 128 characters left
}

	
BOOL SerialPort::InitializeDcbDlg(const wchar_t * lpszName, HWND hWnd, DCB& dcb)
{
	COMMCONFIG cfg;
	memset(&cfg, 0, sizeof(COMMCONFIG));
	memset(&dcb, 0, sizeof(DCB));
	cfg.dwSize = sizeof(COMMCONFIG);
	BOOL f = CommConfigDialog(lpszName, hWnd, &cfg);
	if (f!=0) dcb = cfg.dcb;
	return f;
}

unsigned WINAPI SerialPort::InputThreadFunc(LPVOID param)
{
	SerialPort* sp = (SerialPort*)param;
	sp->check_modem_status(true, 0);
	sp->clear_error();
	Mt::OverlappedE readInfo;
	Mt::OverlappedE statusInfo;
	DWORD dwCommEvent;
	bool waiting_on_status = false;
	sp->bInputThreadReading = false;
	HANDLE handles[4] ={sp->eventKillInputThread.GetHandle(), readInfo.GetEventHandle(),
		statusInfo.GetEventHandle(), sp->eventReadRequest.GetHandle()};
	::SetCommMask(sp->port, EV_BREAK | EV_CTS | EV_DSR | EV_RXCHAR | EV_ERR |
		EV_RING | EV_RLSD);// | EV_RINGTE);
	for(bool done = false; !done; )
	{
		int bytes_to_read=0;
		char read_buffer[256];
		DWORD dwBytesRead;
		if (!sp->bInputThreadReading)
		{
			bytes_to_read = sp->rxQueue.GetSpaceFree();
			if (bytes_to_read>256) bytes_to_read=256;
			if (bytes_to_read>0)
			{
				if (!ReadFile(sp->port, read_buffer, bytes_to_read, &dwBytesRead, &readInfo))
				{
					sp->bInputThreadReading = true;
				}
				else
				{
					if (dwBytesRead)
					{
						sp->rxQueue.Insert(read_buffer, dwBytesRead);
						sp->RxNotify(dwBytesRead);
					}
				}
			}
			else
			{
				readInfo.ResetEvent();
			}
		}
		if (!waiting_on_status)
		{
			if (!WaitCommEvent(sp->port, &dwCommEvent, &statusInfo))
			{
				waiting_on_status=true;
			}
			else
			{
				sp->check_modem_status(false, dwCommEvent);
				sp->clear_error();
			}
		}
		if (waiting_on_status && (sp->bInputThreadReading || bytes_to_read==0))
		{
			DWORD result = WaitForMultipleObjects(4, handles, FALSE, INFINITE);
			switch(result)
			{
			case 0: //Kill thread event                         
				done = true;
				break;
			case 1: // Read data ready
				if (GetOverlappedResult(sp->port, &readInfo, &dwBytesRead, FALSE))
				{
					if (dwBytesRead)
					{
						sp->rxQueue.Insert(read_buffer, dwBytesRead);
						sp->RxNotify(dwBytesRead);
					}
				}
				sp->bInputThreadReading=false;
				break;
			case 2: //Status event
				{
					DWORD dwOverlappedResult;
					if (GetOverlappedResult(sp->port, &statusInfo, &dwOverlappedResult, FALSE))
					{
						sp->check_modem_status(false, dwCommEvent);
						sp->clear_error();
					}
					waiting_on_status = false;
				}
				break;
			//case 3://Input thread wake up event
			//	break;
			}
		}
	}

	return 0;
}

unsigned WINAPI SerialPort::OutputThreadFunc(LPVOID param)
{
	SerialPort* sp = (SerialPort*)param;
	HANDLE handles[3]={sp->eventKillOutputThread.GetHandle(),
		sp->eventWriteRequest.GetHandle(), sp->eventBreakRequest.GetHandle()};
	sp->TxNotify();
	for(bool done=false; !done; )
	{
		switch(WaitForMultipleObjects(3, handles, FALSE, INFINITE))
		{
		case 0: //evenKillOutputThread
			done=true;
			break;
		case 1: //eventWriteRequest
			done = sp->output_worker();
			break;
		case 2: // eventBreakRequest
			SetCommBreak(sp->port);
			SleepEx(sp->iBreakDuration, FALSE);
			ClearCommBreak(sp->port);
			break;
		}
	}
	return 0;
}

void SerialPort::clear_error(void) 
{
	COMSTAT c;
	DWORD errors;
	ClearCommError(port, &errors, &c);
	this->dwErrors |= errors;
	if (errors & CE_BREAK) BreakDetectNotify();
	if (errors & CE_FRAME) FramingErrorNotify();
	if (errors & CE_OVERRUN) HardwareOverrunErrorNotify();
	if (errors & CE_RXPARITY) ParityErrorNotify();
	if (errors & CE_RXOVER) SoftwareOverrunErrorNotify();
}

void SerialPort::check_modem_status(bool first_time, DWORD event_mask)
{
	if (::GetCommModemStatus(port, &dwModemStatus)==0)
	{
		Sys::DisplayLastError(NULL, L"Win::SerialPort check_modem_status");
		return;
	}
	if (first_time)
	{
		CtsNotify( (MS_CTS_ON & dwModemStatus)!=0);
		DsrNotify( (MS_DSR_ON & dwModemStatus)!=0);
		CdNotify( (MS_RLSD_ON & dwModemStatus)!=0);
		RiNotify(0);
	}
	else
	{
		if (event_mask &  EV_CTS) CtsNotify( (MS_CTS_ON & dwModemStatus)!=0);
		if (event_mask &  EV_DSR) DsrNotify( (MS_DSR_ON & dwModemStatus)!=0);
		if (event_mask &  EV_RLSD) CdNotify( (MS_RLSD_ON & dwModemStatus)!=0);
		if (event_mask &  (EV_RING))// | EV_RINGTE) 
		{
			if ( (MS_RING_ON & dwModemStatus)==0) RiNotify(0);
		}
	}
}

bool SerialPort::output_worker()
{
	Mt::OverlappedE writeInfo;
	HANDLE handles[2]={eventKillOutputThread.GetHandle(), writeInfo.GetEventHandle()};
	bool killed = false;
	
	for(bool done=false; !done; )
	{
		char data[500];
		int count = txQueue.Extract(data, 500);
		if (count==0)
		{
			TxNotify();
			break;
		}

		DWORD result_count;
		if (!WriteFile(port, data, count, &result_count, &writeInfo))
		{
			if (GetLastError()==ERROR_IO_PENDING)
			{
				switch(WaitForMultipleObjects(2, handles, FALSE, INFINITE))
				{
				case 0: // eventKillOutputThread
					done = true;
					killed = true;
					PurgeComm(port, PURGE_TXABORT);
					break;
				case 1: //writeInfo
					if (!GetOverlappedResult(port, &writeInfo, &result_count, FALSE))
					{
						if (GetLastError()==ERROR_IO_PENDING)
							clear_error();
						else
							done=true;
					}
					break;
				}
			}
			else
			{
				Sys::DisplayLastError(NULL, L"SerialPort output_worker()");
				done=true;
			}
		}
		else
		{
			if (result_count!=count)
			{
				Sys::DisplayLastError(NULL, L"SerialPort output_worker()");
				done=true;
			}
		}
	}
	return killed;
}

Win::SerialPort::Status SerialPort::writeByte(BYTE byte)
{
	if (port==INVALID_HANDLE_VALUE) return Win::SerialPort::Error;
	if (error_status!=SerialPort::Success) return error_status;
	if (txQueue.GetSpaceFree()<0) return Win::SerialPort::Timeout;
	txQueue.Insert(byte);
	eventWriteRequest.Set();
	txCount ++;
	UpdateRow(2);
	return Win::SerialPort::Success;
}

Win::SerialPort::Status SerialPort::writeBuffer(char* buffer, unsigned int count)
{
	if (port==INVALID_HANDLE_VALUE) return Win::SerialPort::Error;
	byteCount = 0;
	if (error_status!=Win::SerialPort::Success) return error_status;
	byteCount=txQueue.Insert(buffer, count);
	eventWriteRequest.Set();
	if (byteCount==count)
	{
		txCount += count;
		UpdateRow(2);
		return Win::SerialPort::Success;
	}
	else
	{
		//txCount = -1;
		//UpdateRow(2);
		return Win::SerialPort::Timeout;
	}
}

Win::SerialPort::Status SerialPort::readByte(BYTE& byte)
{
	if (port==INVALID_HANDLE_VALUE) return Win::SerialPort::Error;
	if (error_status!=Win::SerialPort::Success) return error_status;
	int ret_val = rxQueue.Extract();
	if (bInputThreadReading==false) eventReadRequest.Set();
	if (ret_val<0) 
	{
		//rxCount = -1;
		//UpdateRow(1);
		return Win::SerialPort::Timeout;
	}
	else
	{
		rxCount--;
		UpdateRow(1);
		return Win::SerialPort::Success;
	}
}

Win::SerialPort::Status SerialPort::readBuffer(char* buffer, unsigned int count)
{
	if (port==INVALID_HANDLE_VALUE) return Win::SerialPort::Error;
	byteCount = 0;
	if (error_status!=Win::SerialPort::Success) return error_status;
	byteCount=rxQueue.Extract(buffer, count);
	buffer[byteCount]='\0';
	if (bInputThreadReading==false) eventReadRequest.Set();
	if (byteCount<count)
	{
		return Win::SerialPort::Timeout;
	}
	else
	{
		rxCount-=count;
		UpdateRow(1);
		return Win::SerialPort::Success;
	}
}

void SerialPort::Window_Open(Win::Event& e)
{
	hWndParent = ::GetParent(hWnd);
}

void SerialPort::OnPaintControl(Win::Gdi& gdi)
{
	COLORREF colorOff = RGB(90, 90, 90);
	const int colWidth = _fontHeight*6;
	wchar_t text[64];
	//_____________________________________________ Font
	Win::Gdi::Font font;
	LOGFONT logfont;
	this->GetLogfont(logfont);
	
	if (_printerFormat || width>10000)
	{
		font.Create(logfont);
		gdi.SelectFont_(font);
	}
	else
	{
		if (_hfont) gdi.SelectFont__(_hfont);
	}

	//____________________________ Pen
	Win::Gdi::Pen pen(PS_SOLID, 1, _lineColor);
	gdi.SelectPen_(pen);

	//____________________________ Background
	RECT rect = gdi.GetRcPaint();//{0, 0, this->width, this->height};
	Win::Gdi::Brush brush;
	if (this->Enabled)
	{
		brush.CreateSolid(_backColor);
		gdi.SetBkColor(_backColor);
	}
	else
	{
		brush.CreateSolid(WIN_BACK_DISABLED);
		gdi.SetBkColor(WIN_BACK_DISABLED);
	}
	gdi.FillRect(rect, brush);
	

	//__________________________ Name Color
	COLORREF nameColor = _textColor;
	if (Enabled == false) 	nameColor = WIN_TEXT_DISABLED;

	//____________________________ Vertical Line
	gdi.Line(colWidth, rect.top, colWidth, rect.bottom);

	gdi.SetTextAlign(TA_LEFT | TA_TOP);
	//___________________________________________________________ Name 
	rect.left = 0;
	rect.top = _fontHeight/2;
	rect.right = colWidth;
	rect.bottom = (int)(rect.top + _fontHeight*1.5+0.5);
	if (gdi.DoRcPaintOverlap(rect))
	{
		gdi.SetTextColor(nameColor),
		gdi.TextOut(_fontHeight/2, rect.top, L"Port");
	}
	rect.left = colWidth;
	rect.right = width;
	if (gdi.DoRcPaintOverlap(rect))
	{
		if (port==INVALID_HANDLE_VALUE)
		{
			gdi.SetTextColor(colorOff);
		}
		else
		{
			gdi.SetTextColor(_textColor);
		}
		_snwprintf_s(text, 64, _TRUNCATE, L"%s", portName);
		_tcsupr_s(text, 64);
		gdi.TextOut(_fontHeight/2+colWidth, rect.top, text);
	}
	gdi.Line(0, rect.bottom-2, width, rect.bottom-2);

	//___________________________________________________________ RX
	rect.left = 0;
	rect.top = (int)(_fontHeight/2 + 1*1.5*_fontHeight+0.5);
	rect.right = colWidth;
	rect.bottom = (int)(rect.top + _fontHeight*1.5+0.5);
	if (gdi.DoRcPaintOverlap(rect))
	{
		gdi.SetTextColor(nameColor),
		gdi.TextOut(_fontHeight/2, rect.top, L"RX");
	}
	rect.left = colWidth;
	rect.right = width;
	if (gdi.DoRcPaintOverlap(rect))
	{
		if (rxCount>0)
		{
			gdi.SetTextColor(_textColor);
		}
		else
		{
			gdi.SetTextColor(colorOff);
		}
		_snwprintf_s(text, 64, _TRUNCATE, L"%d",  rxCount);	
		gdi.TextOut(_fontHeight/2+colWidth, rect.top, text);	
	}
	//___________________________________________________________ TX
	rect.left = 0;
	rect.top = (int)(_fontHeight/2 + 2*1.5*_fontHeight+0.5);
	rect.right = colWidth;
	rect.bottom = (int)(rect.top + _fontHeight*1.5+0.5);
	if (gdi.DoRcPaintOverlap(rect))
	{
		gdi.SetTextColor(nameColor),
		gdi.TextOut(_fontHeight/2, rect.top, L"TX");
	}
	rect.left = colWidth;
	rect.right = width;
	if (gdi.DoRcPaintOverlap(rect))
	{
		if (txCount>0)
		{
			gdi.SetTextColor(_textColor);
		}
		else
		{
			gdi.SetTextColor(colorOff);
		}
		_snwprintf_s(text, 64, _TRUNCATE, L"%d",  txCount);	
		gdi.TextOut(_fontHeight/2+colWidth, rect.top, text);	
	}

	DrawDataRow(gdi, 3, nameColor, L"CTS", isCts);
	DrawDataRow(gdi, 4, nameColor, L"DSR", isDsr);
	DrawDataRow(gdi, 5, nameColor, L"CD", isCd);
	DrawDataRow(gdi, 6, nameColor, L"RI", isRi);

	//____________________________________ error
	rect.left = 0;
	rect.top = (int)(_fontHeight/2 + 7*1.5*_fontHeight+0.5);
	rect.right = colWidth;
	rect.bottom = (int)(rect.top + _fontHeight*1.5+0.5);
	if (errorCaption)
	{
		gdi.SetTextColor(RGB(255, 0, 0));
		if (gdi.DoRcPaintOverlap(rect))
		{
			gdi.TextOut(_fontHeight/2, rect.top, L"ERROR");
		}
		rect.left = colWidth;
		rect.right = width;
		if (gdi.DoRcPaintOverlap(rect))
		{
			gdi.TextOut(_fontHeight/2+colWidth, rect.top, errorCaption);	
		}
	}
}

void SerialPort::DrawDataRow(Win::Gdi& gdi, int index, COLORREF nameColor, const wchar_t* text, bool active)
{
	RECT rect;
	const int colWidth = _fontHeight*6;

	rect.left = 0;
	rect.top = (int)(_fontHeight/2 + index * 1.5 *_fontHeight+0.5);
	rect.right = colWidth;
	rect.bottom = (int)(rect.top + _fontHeight*1.5+0.5);
	if (gdi.DoRcPaintOverlap(rect))
	{
		gdi.SetTextColor(nameColor),
		gdi.TextOut(_fontHeight/2, rect.top, text);
	}
	rect.left = colWidth;
	rect.right = width;
	if (gdi.DoRcPaintOverlap(rect))
	{
		if (active)
		{
			gdi.SetTextColor(_textColor);
			gdi.TextOut(_fontHeight/2+colWidth, rect.top, L"***");	
		}
	}
}

void SerialPort::Break(long milliseconds)
{
	if (milliseconds>1000)
		iBreakDuration = 1000;
	else
		 iBreakDuration= milliseconds;
	eventBreakRequest.Set();
}

Win::SerialPort::Status SerialPort::Peek(void* buffer, unsigned int count)
{
	if (error_status!=Win::SerialPort::Success) return error_status;
	byteCount = rxQueue.Peek((char*)buffer, count);
	( (char*)buffer)[byteCount]='\0';
	return Win::SerialPort::Success;
}

//________________________________________________________ ListDlg
void ListDlg::Window_Open(Win::Event& e)
{
	list<wstring>::iterator p = data.begin();
	const list<wstring>::iterator dend = data.end();
	wstring text;
	text.reserve(data.size()*128);
	for(; p != dend; p++)
	{
		if (p == data.begin()) // Show the first row in the Widow Title
		{
			this->Text = *p;
			continue;
		}
		text += *p;
		text += L"\r\n";
	}
	tbxData.SetWindowText(text.c_str());
	tbxData.SetSelection(-1, 1);
}

void ListDlg::btDummy_Click(Win::Event& e)
{
}


} //____________________________________________________ namespace Win::End

//____________________________________________________ namespace Mm::Ini
#ifdef WIN_DAC_ADC_SUPPORT
namespace Mm{

//_____________________________________________________________________ SoundResource
SoundResource::SoundResource(void)
{
	hRes = NULL;
}

SoundResource::~SoundResource(void)
{
	Delete();
}

void SoundResource::Delete()
{
	Stop();
	if (hRes)
	{
		UnlockResource(hRes); 
		FreeResource(hRes);
		hRes = NULL;
	}
}

bool SoundResource::Play(const wchar_t* name, HINSTANCE hInstance)
{
	Stop();
	Delete();
	HRSRC hResInfo;
    LPCWSTR lpRes; 
 
	hResInfo = ::FindResourceW(hInstance, name, L"WAVE"); 
    if (hResInfo == NULL) return false; 
 
	hRes = (HANDLE)::LoadResource(hInstance, hResInfo); 
    if (hRes == NULL) return false; 

	lpRes = (LPCWSTR)::LockResource(hRes); 
    if (lpRes == NULL) return false;
	return (sndPlaySoundW(lpRes, SND_MEMORY | SND_ASYNC)==TRUE);
}

void SoundResource::Stop()
{
	sndPlaySoundW(NULL, 0);
}

//_____________________________________________________________________ WaveFile
WaveFile::WaveFile(void)
{
	bitsPerSample = 0;
	samplesPerSec = 0;
	numChannels = 0;
	dataSize = 0;
	hmmio = NULL;
	isWritting = false;
}

WaveFile::~WaveFile(void)
{
	Close();
}

wchar_t* WaveFile::GetFileDuration(const wchar_t* fileName, double& durationSeconds)
{
	durationSeconds = 0.0;
	wchar_t * error = this->OpenForReading(fileName);
	if (error) return error;
	durationSeconds = (8.0*dataSize)/((double)bitsPerSample*samplesPerSec*numChannels);
	this->Close();
	return NULL;
}

wchar_t* WaveFile::Close(void)
{
	if (isWritting && hmmio!=NULL)
	{
		//____________________________________________ ascend out of the "data" subchunk
		if (mmioAscend(hmmio, &mmckinfoData, 0) != 0)
		{
			if (hmmio) mmioClose(hmmio, 0);
			hmmio = NULL;
			//
			bitsPerSample = 0;
			samplesPerSec = 0;
			numChannels = 0;
			dataSize = 0;
			return L"WaveFile::Close - Cannot ascend out of the data subchunk";
		}

		//________________________________ ascend out of the "WAVE" chunk -- causes size to be written
		if (mmioAscend(hmmio, &mmckinfoWave, 0) != 0)
		{
			if (hmmio) mmioClose(hmmio, 0);
			hmmio = NULL;
			//
			bitsPerSample = 0;
			samplesPerSec = 0;
			numChannels = 0;
			dataSize = 0;
			return L"WaveFile::Close - Cannot ascend out of the WAVE subchunk";
		}
	}

	if (hmmio) mmioClose(hmmio, 0);
	hmmio = NULL;
	//
	bitsPerSample = 0;
	samplesPerSec = 0;
	numChannels = 0;
	dataSize = 0;
	return NULL;
}

void WaveFile::GetInfo(unsigned int& bitsPerSample, DWORD& samplesPerSec, unsigned short&numChannels)
{
	bitsPerSample = this->bitsPerSample;
	samplesPerSec = this->samplesPerSec;
	numChannels = this->numChannels;
}

wchar_t* WaveFile::OpenForWritting(unsigned int samplesPerSec, bool bStereo, unsigned int bitsPerSample, const wchar_t* fileName)
{
	this->Close();
	this->isWritting = true;

	LONG lFmtSize;
	MMCKINFO mmckinfoFmt;
	PCMWAVEFORMAT pcmWaveFormat;

	//________________________________________ open the file
    hmmio = mmioOpen((LPTSTR)fileName, NULL, MMIO_ALLOCBUF | MMIO_WRITE | MMIO_CREATE );
    if (hmmio == NULL)
		return L"WaveFile::OpenForWritting - Unable to write file";

	//_________________________________________ create a "RIFF" chunk with a "WAVE" form type
    mmckinfoWave.fccType = mmioFOURCC( 'W','A','V','E' );
    if (mmioCreateChunk(hmmio, &mmckinfoWave, MMIO_CREATERIFF ) != 0)
		return L"WaveFile::OpenForWritting - Unable to create RIFF chunk";

	//_________________________________________ store size of the format subchunk
    lFmtSize = (LONG)sizeof(PCMWAVEFORMAT);
	// Create the format subchunk.
	// Since we know the size of this chunk, specify it in the
	// MMCKINFO structure so MMIO doesn't have to seek back and
	// set the chunk size after ascending from the chunk.

    mmckinfoFmt.ckid = mmioFOURCC( 'f', 'm', 't', ' ' );
    mmckinfoFmt.cksize = lFmtSize;
    if (mmioCreateChunk(hmmio, &mmckinfoFmt, 0 ) != 0)
		return L"WaveFile::OpenForWritting - Unable to write fmt chunk";

	//_________________________________________ initialize PCMWAVEFORMAT structure
	pcmWaveFormat.wf.wFormatTag = WAVE_FORMAT_PCM;
	pcmWaveFormat.wf.nChannels = bStereo? 2 : 1;
	pcmWaveFormat.wf.nSamplesPerSec  = samplesPerSec;
	pcmWaveFormat.wBitsPerSample  = bitsPerSample;

	if (bitsPerSample ==8)
	{
		pcmWaveFormat.wf.nAvgBytesPerSec = bStereo ? samplesPerSec*2 : samplesPerSec;
		pcmWaveFormat.wf.nBlockAlign = bStereo ? 2:1;
	}
	else
	{
		pcmWaveFormat.wf.nAvgBytesPerSec = bStereo ? samplesPerSec*4 : samplesPerSec*2;
		pcmWaveFormat.wf.nBlockAlign = bStereo ? 4:2;
	}

    //_______________________________________________ write the format subchunk
    if (mmioWrite(hmmio, (LPSTR)&pcmWaveFormat, lFmtSize ) != lFmtSize)
		return L"WaveFile::OpenForWritting - Unable to write PCMWAVEFORMAT";

    //_______________________________________________ ascend out of the format subchunk
    if (mmioAscend(hmmio, &mmckinfoFmt, 0 ) != 0)
		return L"WaveFile::OpenForWritting - Cannot ascend out fo the format subchunk";

    //_______________________________________________ create the "data" subchunk that holds the waveform samples
    mmckinfoData.ckid  = mmioFOURCC( 'd', 'a', 't', 'a' );

    if (mmioCreateChunk(hmmio, &mmckinfoData, 0 ) != 0)
		return L"WaveFile::OpenForWritting - Cannot create data subchunk";

	return NULL;
}

int WaveFile::GetNumChannels()
{
	return numChannels;
}

int WaveFile::GetBitsPerSample()
{
	return bitsPerSample;
}

int WaveFile::GetSamplesPerSecond()
{
	return samplesPerSec;
}

wchar_t* WaveFile::OpenForReading(const wchar_t* fileName)
{
	Close();
	isWritting = false;
	//_______________________________________ Open the file for reading
	MMCKINFO mmckinfoWave;
	MMCKINFO mmckinfoFmt;
	MMCKINFO mmckinfoData;
	PCMWAVEFORMAT pcmWaveFormat;
	LONG lFmtSize;
	//LONG          lDataSize;        // size of "data" chunk
	//LPSTR         lpData;           // pointer to data buffer

    hmmio = mmioOpen((LPTSTR)fileName, NULL, MMIO_ALLOCBUF | MMIO_READ);
	if (hmmio == NULL) 
		return L"WaveFile::OpenForReading - the file cannot be open";

    //____________________________________________ locate a chunk with a "WAVE" form type
    mmckinfoWave.fccType = mmioFOURCC('W','A','V','E');
    if (mmioDescend(hmmio, &mmckinfoWave, NULL, MMIO_FINDRIFF ) != 0)
		return L"WaveFile::OpenForReading - Cannot locate WAVE chunk";

    //____________________________________________ find the format subchunk
    mmckinfoFmt.ckid = mmioFOURCC('f','m','t',' ');
    if (mmioDescend(hmmio, &mmckinfoFmt, &mmckinfoWave, MMIO_FINDCHUNK ) != 0)
		return L"WaveFile::OpenForReading - Cannot find fmt chunk";

    //____________________________________________ read the format subchunk
    lFmtSize = (LONG)sizeof( PCMWAVEFORMAT );
    if (mmioRead(hmmio, (LPSTR)&pcmWaveFormat, lFmtSize ) != lFmtSize)
		return L"WaveFile::OpenForReading - Cannot read WAVEFORMAT";
	
	//____________________________________________ check for pcm format
	if (pcmWaveFormat.wf.wFormatTag != WAVE_FORMAT_PCM)
		return L"WaveFile::OpenForReading - Format is not supported";

    //____________________________________________ ascend out of the format subchunk
    if (mmioAscend(hmmio, &mmckinfoFmt, 0 ) != 0)
		return L"WaveFile::OpenForReading - Cannot ascend out of the format subchunk";

	//____________________________________________ Extract format information
	this->samplesPerSec = pcmWaveFormat.wf.nSamplesPerSec;
	this->bitsPerSample = pcmWaveFormat.wBitsPerSample;
	this->numChannels = pcmWaveFormat.wf.nChannels;

	if (bitsPerSample != 8 && bitsPerSample != 16)
		return L"WaveFile::OpenForReading - Invalid number of bits per sample";

	if (numChannels != 1 && numChannels != 2)
		return L"WaveFile::OpenForReading - Invalid number of channels";

    //____________________________________________ find the data subchunk
    mmckinfoData.ckid = mmioFOURCC('d','a','t','a');
    if (mmioDescend(hmmio, &mmckinfoData, &mmckinfoWave, MMIO_FINDCHUNK ) != 0)
		return L"WaveFile::OpenForReading - The file is corrupted";

    //____________________________________________ get the size of the data subchunk
    dataSize = (int)mmckinfoData.cksize;
    if (dataSize == 0)
		return L"WaveFile::OpenForReading - The file is empty";

	return NULL;
}

long WaveFile::WriteData(LPSTR buffer, unsigned int bufferSize)
{
	return  mmioWrite(hmmio, buffer, bufferSize);
}

double WaveFile::GetRemainingSeconds()
{
	if (bitsPerSample==0 || samplesPerSec==0 || numChannels==0) return 0.0;
	return  (8.0*dataSize)/((double)bitsPerSample*samplesPerSec*numChannels);
}

unsigned int WaveFile::GetRemainingByteCount(void)
{
	return dataSize;
}

long WaveFile::ReadData(LPSTR buffer, unsigned int bufferSize)
{
	if (dataSize<=0) return 0;
	long actualSize = mmioRead(hmmio, buffer, bufferSize);
	if (actualSize>0) dataSize-=actualSize;
	if (dataSize<0) dataSize = 0;
	return actualSize;
}

//_____________________________________________________________________ WaveBuffer
WaveBuffer::WaveBuffer(void)
{
	m_pWaveHdr = NULL;
	m_pBuffer = NULL;
	m_bExternalBuffer = false;
}

WaveBuffer::~WaveBuffer(void)
{
	Destroy();
}

bool WaveBuffer::Create(unsigned int nBufferSize)
{
	Destroy();
	m_bExternalBuffer = false;
	m_pWaveHdr = new WAVEHDR;
	m_pBuffer = new char[nBufferSize];
	if (m_pWaveHdr==NULL || m_pBuffer ==NULL) return false;
	m_pWaveHdr->dwBufferLength = nBufferSize;
	m_pWaveHdr->dwBytesRecorded = 0;
	m_pWaveHdr->dwFlags = 0;
	m_pWaveHdr->dwLoops = 1;
	m_pWaveHdr->dwUser = 0;
	m_pWaveHdr->lpData = m_pBuffer;
	m_pWaveHdr->lpNext = NULL;
	m_pWaveHdr->reserved = 0;
	return true;
}

bool WaveBuffer::CreateUsingExternalBuffer(char* pData, unsigned int nBufferSize)
{
	Destroy();
	m_bExternalBuffer = true;
	m_pWaveHdr = new WAVEHDR;
	m_pBuffer = pData;
	if (m_pWaveHdr==NULL || m_pBuffer ==NULL) return false;
	m_pWaveHdr->dwBufferLength = nBufferSize;
	m_pWaveHdr->dwBytesRecorded = 0;
	m_pWaveHdr->dwFlags = 0;
	m_pWaveHdr->dwLoops = 1;
	m_pWaveHdr->dwUser = 0;
	m_pWaveHdr->lpData = m_pBuffer;
	m_pWaveHdr->lpNext = NULL;
	m_pWaveHdr->reserved = 0;
	return true;
}

unsigned int WaveBuffer::GetBufferSize()
{
	if (this->m_pWaveHdr)
		return m_pWaveHdr->dwBufferLength;
	else
		return 0;
}

void WaveBuffer::Destroy()
{
	if (m_pWaveHdr) delete m_pWaveHdr;
	if (m_pBuffer != NULL && m_bExternalBuffer==false) delete [] m_pBuffer;
	m_pWaveHdr = NULL;
	m_pBuffer = NULL;
	m_bExternalBuffer = false;
}

// This function allows to see the content of the buffer
// Returns the number of characters written to pszBuffer
unsigned int WaveBuffer::GetString(wchar_t* pszBuffer,  int nBufferSize)
{
	unsigned int n = 0;
	wchar_t sz[32];
	//unsigned char c;

	if (m_pBuffer)
	{
		pszBuffer[0] = '\0';
		for(int i = 0; i<nBufferSize; i++)
		{
			//c = (LONG)(unsigned char)m_pBuffer[i];
			n++;
			_snwprintf_s(sz, 32, _TRUNCATE, L"%f ", (LONG)(unsigned char)m_pBuffer[i]);
			
			if (lstrlen(pszBuffer)+lstrlen(sz)<=nBufferSize-1)	
				lstrcat(pszBuffer, sz);
			else
				break;
		}
	}
	return n;
}

//_____________________________________________________________________ WaveIn
WaveIn::WaveIn(void)
{
	m_hWaveIn = NULL;
}

WaveIn::~WaveIn(void)
{
}

// nSamplesPerSec values 8000, 11025, 22050, 44100
MMRESULT WaveIn::OpenPCM8(HWND hWndParent, DWORD nSamplesPerSec, bool bStereo)
{
	m_wf.cbSize = 0;
	m_wf.nAvgBytesPerSec = bStereo ? nSamplesPerSec*2 : nSamplesPerSec;
	m_wf.nSamplesPerSec = nSamplesPerSec;
	m_wf.nChannels = bStereo ? 2:1;
	m_wf.wBitsPerSample = 8;
	m_wf.wFormatTag = WAVE_FORMAT_PCM;
	m_wf.nBlockAlign = bStereo ? 2:1;

	return ::waveInOpen((LPHWAVEIN)&m_hWaveIn, WAVE_MAPPER, &m_wf, (DWORD_PTR)hWndParent, 0, CALLBACK_WINDOW);
}

// nSamplesPerSec values 8000, 11025, 22050, 44100
MMRESULT WaveIn::OpenPCM8(DWORD nSamplesPerSec, bool bStereo, DWORD_PTR waveOutProc, DWORD_PTR dwCustomData)
{
	m_wf.cbSize = 0;
	m_wf.nAvgBytesPerSec = bStereo ? nSamplesPerSec*2 : nSamplesPerSec;
	m_wf.nSamplesPerSec = nSamplesPerSec;
	m_wf.nChannels = bStereo ? 2:1;
	m_wf.wBitsPerSample = 8;
	m_wf.wFormatTag = WAVE_FORMAT_PCM;
	m_wf.nBlockAlign = bStereo ? 2:1;

	return ::waveInOpen((LPHWAVEIN)&m_hWaveIn, WAVE_MAPPER, &m_wf, waveOutProc, dwCustomData, CALLBACK_FUNCTION);
}

// nSamplesPerSec values 8000, 11025, 22050, 44100
MMRESULT WaveIn::OpenPCM16(HWND hWndParent, DWORD nSamplesPerSec, bool bStereo)
{
	MMRESULT result = 0;

	m_wf.cbSize = 0;
	m_wf.nAvgBytesPerSec = bStereo ? nSamplesPerSec*4 : nSamplesPerSec*2;
	m_wf.nSamplesPerSec = nSamplesPerSec;
	m_wf.nChannels = bStereo ? 2:1;
	m_wf.wBitsPerSample = 16;
	m_wf.wFormatTag = WAVE_FORMAT_PCM;
	m_wf.nBlockAlign = bStereo ? 4:2;

	return ::waveInOpen((LPHWAVEIN)&m_hWaveIn, WAVE_MAPPER, &m_wf, (DWORD_PTR)hWndParent, 0, CALLBACK_WINDOW);
}

wchar_t* WaveIn::GetErrorDescr(MMRESULT mmresult)
{
	if (waveInGetErrorText(mmresult, this->m_pErrorDescr, MAXERRORLENGTH) != MMSYSERR_NOERROR)
	{
		return NULL;
	}
	else
	{
		return m_pErrorDescr;
	}
}

void WaveIn::ListLineControls(void)
{
	wchar_t sz[256];
	MIXERLINE ml;
	MMRESULT mmr;
	MIXERLINECONTROLS mxlc;
	MIXERCONTROL mxc;
	wchar_t *errorDsc = L"No error";

	ml.cbStruct = sizeof(MIXERLINE);
	ml.dwComponentType = MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY;//MIXERLINE_COMPONENTTYPE_SRC_LINE;
	mmr = ::mixerGetLineInfo((HMIXEROBJ)this->m_hWaveIn, &ml, MIXER_GETLINEINFOF_COMPONENTTYPE | MIXER_OBJECTF_HWAVEIN);
	if (mmr==MMSYSERR_NOERROR)
	{
		_snwprintf_s(sz, 256, _TRUNCATE, L"%d", ml.dwLineID);
		
		::MessageBox(NULL, sz, L"Mixercaps", MB_OK | MB_ICONINFORMATION);
		mxlc.cbStruct = sizeof(MIXERLINECONTROLS);
		mxlc.dwLineID = ml.dwLineID;
		mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
		mxlc.cControls = 1;
		mxlc.cbmxctrl = sizeof(MIXERCONTROL);
		mxlc.pamxctrl = &mxc;
		mmr = ::mixerGetLineControls((HMIXEROBJ)m_hWaveIn, &mxlc, MIXER_GETLINECONTROLSF_ONEBYTYPE | MIXER_OBJECTF_HWAVEIN);
		if (mmr!=MMSYSERR_NOERROR)
		{
			if (mmr==MIXERR_INVALCONTROL) errorDsc= L"MIXERR_INVALCONTROL";
			if (mmr==MIXERR_INVALLINE) errorDsc= L"MIXERR_INVALLINE";
			if (mmr==MMSYSERR_BADDEVICEID ) errorDsc= L"MMSYSERR_BADDEVICEID";
			if (mmr==MMSYSERR_INVALFLAG) errorDsc= L"MMSYSERR_INVALFLAG";
			if (mmr==MMSYSERR_INVALHANDLE) errorDsc= L"MMSYSERR_INVALHANDLE";
			if (mmr==MMSYSERR_INVALPARAM) errorDsc= L"MMSYSERR_INVALPARAM";
			if (mmr==MMSYSERR_NODRIVER ) errorDsc= L"MMSYSERR_NODRIVER";
			::MessageBox(NULL, errorDsc, L"WaveIn::SetLineVolume", MB_OK | MB_ICONERROR);

		}
		else
		{
		}
	}
	//#include <Mmsystem.h> and Winmm.lib
	UINT numbMixer = ::mixerGetNumDevs();
	if (numbMixer>=1)
	{
		MIXERCAPS mixercaps;

		MMRESULT mmr = ::mixerGetDevCaps(0, &mixercaps, sizeof(MIXERCAPS));
		if (mmr==MMSYSERR_NOERROR)
		{
			MIXERLINECONTROLS mxc;
			MIXERCONTROL mcontrol[WIN_MIX_CONTROLS];
			memset(mcontrol, 0, WIN_MIX_CONTROLS*sizeof(MIXERCONTROL));
			mxc.cbStruct = sizeof(MIXERLINECONTROLS);
			mxc.cControls = WIN_MIX_CONTROLS;
			mxc.cbmxctrl = sizeof(MIXERCONTROL);
			mxc.pamxctrl = mcontrol;
			//
			_snwprintf_s(sz, 256, _TRUNCATE, L"Device name: %s \r\n Number of destinations: %d", mixercaps.szPname,
				mixercaps.cDestinations);
			
			::MessageBox(NULL, sz, L"Mixercaps", MB_OK | MB_ICONINFORMATION);
			//
			mmr = mixerGetLineControls((HMIXEROBJ)this->m_hWaveIn, &mxc, MIXER_OBJECTF_HWAVEIN | MIXER_GETLINECONTROLSF_ALL);

			if (mmr==MMSYSERR_NOERROR)
			{
				for(int i = 0; i<WIN_MIX_CONTROLS; i++)
				{
					::MessageBox(NULL, mcontrol[i].szName, mcontrol[i].szShortName, MB_OK);
				}
			}
			else if (mmr==MMSYSERR_INVALHANDLE)
			{
				::MessageBox(NULL, L"Invalid Handle", L"Mixer line controls", MB_OK | MB_ICONINFORMATION);
			}
			else if (mmr==MMSYSERR_INVALFLAG)
			{
				::MessageBox(NULL, L"Invalid Flag", L"Mixer line controls", MB_OK | MB_ICONINFORMATION);
			}
			else if (mmr==MMSYSERR_INVALPARAM)
			{
				::MessageBox(NULL, L"Invalid Parameter", L"Mixer line controls", MB_OK | MB_ICONINFORMATION);
			}
   
		}
		else if (mmr==MMSYSERR_BADDEVICEID)
		{
		}
		else if (mmr==MMSYSERR_INVALHANDLE)
		{
		}
		else if (mmr==MMSYSERR_INVALPARAM)
		{
		}
		else
		{
		}
	}
}

//_____________________________________________________________________ WaveOut
WaveOut::WaveOut(void)
{
	m_hWaveOut = NULL;
}

WaveOut::~WaveOut(void)
{

}

// nSamplesPerSec values 8000, 11025, 22050, 44100
MMRESULT WaveOut::OpenPCM8(HWND hWndParent, DWORD nSamplesPerSec, bool bStereo)
{
	m_wf.cbSize = 0;
	m_wf.nAvgBytesPerSec = bStereo ? nSamplesPerSec*2 : nSamplesPerSec;
	m_wf.nSamplesPerSec = nSamplesPerSec;
	m_wf.nChannels = bStereo ? 2:1;
	m_wf.wBitsPerSample = 8;
	m_wf.wFormatTag = WAVE_FORMAT_PCM;
	m_wf.nBlockAlign = bStereo ? 2:1;

	return ::waveOutOpen((LPHWAVEOUT)&m_hWaveOut, WAVE_MAPPER, &m_wf, (DWORD_PTR)hWndParent, 0, CALLBACK_WINDOW);
}

// nSamplesPerSec values 8000, 11025, 22050, 44100
MMRESULT WaveOut::OpenPCM8(DWORD nSamplesPerSec, bool bStereo, DWORD_PTR waveOutProc, DWORD_PTR dwCustomData)
{
	m_wf.cbSize = 0;
	m_wf.nAvgBytesPerSec = bStereo ? nSamplesPerSec*2 : nSamplesPerSec;
	m_wf.nSamplesPerSec = nSamplesPerSec;
	m_wf.nChannels = bStereo ? 2:1;
	m_wf.wBitsPerSample = 8;
	m_wf.wFormatTag = WAVE_FORMAT_PCM;
	m_wf.nBlockAlign = bStereo ? 2:1;

	return ::waveOutOpen(&m_hWaveOut, WAVE_MAPPER, &m_wf, waveOutProc, dwCustomData, CALLBACK_FUNCTION);
}

// nSamplesPerSec values 8000, 11025, 22050, 44100
MMRESULT WaveOut::OpenPCM16(HWND hWndParent, DWORD nSamplesPerSec, bool bStereo)
{
	m_wf.cbSize = 0;
	m_wf.nAvgBytesPerSec = bStereo ? nSamplesPerSec*4 : nSamplesPerSec*2;
	m_wf.nSamplesPerSec = nSamplesPerSec;
	m_wf.nChannels = bStereo ? 2:1;
	m_wf.wBitsPerSample = 16;
	m_wf.wFormatTag = WAVE_FORMAT_PCM;
	m_wf.nBlockAlign = bStereo ? 4:2;

	return ::waveOutOpen((LPHWAVEOUT)&m_hWaveOut, WAVE_MAPPER, &m_wf, (DWORD_PTR)hWndParent, 0, CALLBACK_WINDOW);
}

MMRESULT WaveOut::PrepareHeader(Mm::WaveBuffer& waveBuffer)
{
	return ::waveOutPrepareHeader(m_hWaveOut, waveBuffer.m_pWaveHdr, sizeof(WAVEHDR));
}

//MMRESULT WaveOut::UnprepareHeader(Mm::WaveBuffer& waveBuffer)
//{
//	return ::waveOutUnprepareHeader(m_hWaveOut, waveBuffer.m_pWaveHdr, sizeof(WAVEHDR)) ;
//}

wchar_t* WaveOut::GetErrorDescr(MMRESULT mmresult)
{
	if (waveOutGetErrorText(mmresult, this->m_pErrorDescr, MAXERRORLENGTH) != MMSYSERR_NOERROR)
	{
		return NULL;
	}
	else
	{
		return m_pErrorDescr;
	}
}

//_____________________________________________________________________ Dac
//bool Dac::m_bRegistered= false;
Dac::Dac(void)
{
	//if (!m_bRegistered)
	//{
	//	this->RegisterClassEx(LoadCursor(NULL, IDC_ARROW), (HBRUSH)::GetStockObject(NULL_BRUSH));
	//	m_bRegistered = true;
	//}
	bPlaying = false;
	bEnding = false;
	hWndParent = NULL;
	preparedBufferCount = 0;
	sampleRate = 0;
	bufferSize = 0;
	b16Bits = true;
	bytesPerSample = 4;
	numChannels = 2;
	//numBufferReady = 0;
	info = L"Ready";
	//isLinearDisplay = false;
	idataTransfer = NULL;
	showData = false;
}

Dac::~Dac(void)
{
}

void Dac::OnPaintControl(Win::Gdi& gdi)
{
	colWidth = 8*_fontHeight;
	//_____________________________________________ Font
	Win::Gdi::Font font;
	
	if (_printerFormat || width>10000)
	{
		LOGFONT logfont;
		this->GetLogfont(logfont);
		logfont.lfHeight = -(height)/2;
		font.Create(logfont);
		gdi.SelectFont_(font);
	}
	else
	{
		if (_hfont) gdi.SelectFont__(_hfont);
	}

	wchar_t displayInfo[256];
	wchar_t caption[64];

	//____________________________ Pen
	Win::Gdi::Pen pen(PS_SOLID, 1, _lineColor);
	gdi.SelectPen_(pen);

	//____________________________ Background
	RECT rect = gdi.GetRcPaint();//{0, 0, this->width, this->height};
	Win::Gdi::Brush brush;
	if (this->Enabled)
	{
		brush.CreateSolid(_backColor);
	}
	else
	{
		brush.CreateSolid(WIN_BACK_DISABLED);
	}
	gdi.FillRect(rect, brush);

	//____________________________ Vertical Line
	gdi.Line(colWidth, rect.top, colWidth, rect.bottom);
	//____________________________ Text
	if (this->Enabled)
	{
		gdi.SetBkColor(_backColor);
		gdi.SetTextColor(_textColor);
	}
	else
	{
		gdi.SetBkColor(WIN_BACK_DISABLED);
		gdi.SetTextColor(WIN_TEXT_DISABLED);
	}
	gdi.SetTextAlign(TA_LEFT | TA_TOP);
	//___________________________________________________________ Name 
	rect.left = 0;
	rect.top = _fontHeight/2;
	rect.right = colWidth;
	rect.bottom = (int)(rect.top + _fontHeight*1.5+0.5);
	if (gdi.DoRcPaintOverlap(rect))
	{
		if (this->GetTextLength()>0)
		{
			this->GetWindowText(caption, 64);
		}
		else
		{
			_snwprintf_s(caption, 64, _TRUNCATE, L"%s", L"DAC");
		}
		caption[64-1] = '\0';
		gdi.TextOut(_fontHeight/2, rect.top, caption);
	}
	rect.left = colWidth;
	rect.right = width;
	if (gdi.DoRcPaintOverlap(rect))
	{
		if (info==NULL) info = L"OFF";
		gdi.TextOut(_fontHeight/2 + colWidth, rect.top, info);
	}
	gdi.Line(0, rect.bottom-2, width, rect.bottom-2);

	DrawDataRow(gdi, 1, L"Resolution", b16Bits ? L"16 bits" : L"8 bits");
	DrawDataRow(gdi, 2, L"Setup", numChannels == 2 ? L"2 channels" : L"1 channel");
	//
	_snwprintf_s(displayInfo, 256, _TRUNCATE, L"%d Hz", sampleRate);
	DrawDataRow(gdi, 3, L"Sample Rate", displayInfo);
	//
	DrawDataRow(gdi, 4, L"Data", showData ? L". . . ." : L" . . . .");

	//___________________________________________________________ FileName
	//if (wcslen(filename)==0) return;
	//rect.left = 0;
	//rect.top = (int)(_fontHeight/2 + 5 * 1.5 *_fontHeight+0.5);
	//rect.right = colWidth;
	//rect.bottom = (int)(rect.top + _fontHeight*1.5+0.5);
	//if (gdi.DoRcPaintOverlap(rect))
	//{
	//	gdi.TextOut(_fontHeight/2, rect.top, L"File name");
	//}
	//rect.left = colWidth;
	//rect.right = width;
	//rect.bottom = height;
	//if (gdi.DoRcPaintOverlap(rect))
	//{
	//	vector<wstring> path;
	//	Sys::Convert::PathToVectorOfStrings(fileName, path);
	//	int y = rect.top;
	//	gdi.TextOut(_fontHeight/2 + colWidth, y, path[path.size()-1].c_str());
	//	//for(size_t i = 0; i<path.size(); i++)
	//	//{
	//	//	//_snwprintf_s(displayInfo, 256, _TRUNCATE, L"%d Hz", samplesPerSec);
	//	//	gdi.TextOut(rect.left, y, path[i].c_str());
	//	//	y += (int)(1.5*_fontHeight+0.5);
	//	//}
	//}
}

void Dac::DrawDataRow(Win::Gdi& gdi, int row, const wchar_t* name, const wchar_t* value)
{
	RECT rect;

	rect.left = 0;
	rect.top = (int)(_fontHeight/2.0 + 1.5*_fontHeight * row+0.5);
	rect.right = colWidth;
	rect.bottom = (int)(rect.top + _fontHeight*1.5+0.5);
	if (gdi.DoRcPaintOverlap(rect))
	{
		gdi.TextOut(_fontHeight/2, rect.top, name);
	}
	rect.left = colWidth;
	rect.right = width;
	if (gdi.DoRcPaintOverlap(rect))
	{
		if (row == 4) rect.top -= _fontHeight/4;
		gdi.TextOut(_fontHeight/2+colWidth, rect.top, value);
	}
}

bool Dac::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_COMMAND) return false;
	const int id = LOWORD(e.wParam);
	const int notificationd = HIWORD(e.wParam);
	if (id != this->id) return false;
	if (notificationd!=notification) return false;
	return true;
}

bool Dac::EventHandler(Win::Event& e)
{
	if (e.uMsg!=WM_COMMAND) return false;
	const int notification = HIWORD(e.wParam);
	::SendMessage(::GetParent(hWnd), WM_COMMAND, MAKEWPARAM(id, notification), e.lParam);
	return true;
}

//void Dac::SetLinearDisplay(bool isLinearDisplay)
//{
//	this->isLinearDisplay = isLinearDisplay;
//	this->RefreshLinearDisplayInfo();
//}

//void Dac::UpdateDisplayInformation(void)
//{
//	wchar_t displayInfo[256];
//	wchar_t caption[128];
//
//	//wchar_t *cpu = NULL;
//
//	//switch(numBufferReady)
//	//{
//	//case 0: 
//	//	colorDisplay.SetColor(RGB(255, 0, 0));
//	//	cpu = L"dead";
//	//	break;
//	//case 1: 
//	//	colorDisplay.SetColor(RGB(255, 255, 0));
//	//	cpu = L"slow";
//	//	break;
//	//case 2: 
//	//	colorDisplay.SetColor(RGB(0, 0, 255));
//	//	cpu = L"good";
//	//	break;
//	//default:
//	//	colorDisplay.SetColor(RGB(0, 255, 0));
//	//	cpu = L"fast";
//	//}
//	if (this->GetTextLength()>1)
//	{
//		this->GetWindowText(caption, 128);
//	}
//	else
//	{
//		lstrcpy(caption, L"Mm::Dac");
//	}
//	if (info==NULL) info=L"Ready";
//	caption[127]='\0';
//	_snwprintf_s(displayInfo, 256, _TRUNCATE, L"%s - %s", caption, info);
//		colorDisplay.SetWindowText(displayInfo);
//}

// 8 bits -> level [0, 127], 16 bits -> level[0 32768]
void Dac::GetMaxLevel(LPSTR buffer, int bufferSize, bool bStereo, bool b16Bits, int& channel_1, int& channel_2)
{
	channel_1 = 0;
	channel_2 = 0;
	if (bufferSize == 0) return;

	int nBytesPerSample;
	int nSampleCount;
	int nValue, i;

	if (bStereo==true && b16Bits==true) //16 Bits stereo
	{
		nBytesPerSample = 4;
		nSampleCount = bufferSize/nBytesPerSample;
		Sys::Sample16 *samples_16s = (Sys::Sample16*) buffer;

		for (i=0; i<nSampleCount; i++)
		{
			nValue = abs(samples_16s[i].channel_1);//abs((int)int16Data);
			if (channel_1<nValue) channel_1 = nValue;
			//
			nValue = abs(samples_16s[i].channel_2);//abs((int)int16Data);
			if (channel_2<nValue) channel_2 = nValue;
		}
	}
	else if (bStereo==false && b16Bits==true) //16 Bits mono
	{
		nBytesPerSample = 2;
		nSampleCount = bufferSize/nBytesPerSample;
		__int16 *samples_16m = (__int16 *) buffer;

		for (i=0; i<nSampleCount; i++)
		{
			nValue = abs(samples_16m[i]);//abs((int)int16Data);
			if (channel_1<nValue) channel_1 = nValue;
		}
		channel_2 = channel_1;
	}
	else if (bStereo==true && b16Bits==false) //8 Bits stereo
	{
		nBytesPerSample = 2;
		nSampleCount = bufferSize/nBytesPerSample;
		Sys::Sample8 *sample_8s =(Sys::Sample8 *) buffer;

		for (i=0; i<nSampleCount; i++)
		{
			nValue = abs(sample_8s[i].channel_1);//abs((int)int8Data);
			nValue = abs(nValue -127);
			if (channel_1<nValue) channel_1 = nValue;
			//
			nValue = abs(sample_8s[i].channel_2);//abs((int)int8Data);
			nValue = abs(nValue -127);
			if (channel_2<nValue) channel_2 = nValue;
		}
	}
	else if (bStereo==false && b16Bits==false) //8 Bits mono
	{
		__int8 *sample_8m = (__int8*)buffer;
		for (i=0; i<(int)bufferSize; i++)
		{
			nValue = abs(sample_8m[i]);//abs((int)int8Data);
			nValue = abs(nValue -127);
			if (channel_1<nValue) channel_1 = nValue;
		}
		channel_2 = channel_1;
	}
}

//void Dac::Window_Size(Win::Event& e)
//{
//	const int height_ = (int)(height/3.0+0.5);
//	colorDisplay.Move(0, 0, width, height_, true);
//	levelLeft.Move(0, height_, width, height_, true);
//	levelRight.Move(0, 2*height_, width, height_, true);
//}

void Dac::DeleteBuffers(void)
{
	for(int i=0; i<MM_DAC_NUM_BUFFER; i++) wb[i].Destroy();
}

//void Dac::RefreshLinearDisplayInfo(void)
//{
//	if (isLinearDisplay)
//	{
//		if (this->b16Bits)
//		{
//			this->levelLeft.SetRange(0.0, 32767.0);
//			this->levelRight.SetRange(0.0, 32767.0);
//		}
//		else
//		{
//			this->levelLeft.SetRange(0.0, 127.0);
//			this->levelRight.SetRange(0.0, 127.0);
//		}
//	}
//	else
//	{
//		if (this->b16Bits)
//		{
//			this->levelLeft.SetRange(1.0, log10(32767.0));
//			this->levelRight.SetRange(1.0, log10(32767.0));
//		}
//		else
//		{
//			this->levelLeft.SetRange(1.0, log10(127.0));
//			this->levelRight.SetRange(1.0, log10(127.0));
//		}
//	}
//}

void Dac::SetIDataTransfer(Mm::IDataTransfer* idataTransfer)
{
	this->idataTransfer = idataTransfer;
}

wchar_t* Dac::Start(unsigned int sampleRate, int channels, int bitsPerSample, unsigned int bufferSize)
{
	if (IsPlaying()) return false;
	MMRESULT result;
	this->b16Bits = (bitsPerSample==16);
	this->numChannels = (channels==2) ? 2 : 1;
	const bool bStereo = (channels==2) ? true : false;
	this->sampleRate = sampleRate;
	info = L"ON";
	showData = true;
	bytesPerSample = b16Bits ? 2*numChannels : numChannels; 
	//this->UpdateDisplayInformation();
	this->bufferSize = bufferSize;
	int i;
	//this->RefreshLinearDisplayInfo();

	preparedBufferCount = 0;
	hWndParent = ::GetParent(this->hWnd);

	if (waveOut.IsOpen() == false)
	{
		for(i=0; i<MM_DAC_NUM_BUFFER; i++)
		{
			if (wb[i].Create(bufferSize)==false)
			{
				this->DeleteBuffers();
				return L"No enough memory to create buffers";
			}
		}
		this->bEnding = false;

		if (b16Bits)
			result = waveOut.OpenPCM16(this->hWnd, sampleRate, bStereo);
		else
			result = waveOut.OpenPCM8(this->hWnd, sampleRate, bStereo);

		if (result != MMSYSERR_NOERROR)
		{
			this->DeleteBuffers();
			return L"Error during opening output device";
		}
	}
	return NULL;
}

bool Dac::Stop()
{
	bool bOk = false;
	info = L"+++";
	if (hWnd != NULL) ::InvalidateRect(hWnd, NULL, FALSE);

	if (this->waveOut.IsOpen())
	{
		bEnding = true;
		bOk = (this->waveOut.Reset() != MMSYSERR_NOERROR);
	}
	return bOk;
}

bool Dac::IsPlaying()
{
	return bPlaying;
}

void Dac::Window_WomOpen(Win::Event& e)
{
	MMRESULT mmr;
	WAVEHDR whrd;
	bPlaying = true;
	bEnding = false;
	preparedBufferCount=0;
	unsigned int bytesFilled = 0;

	info = L"ON";
	//UpdateDisplayInformation();
	if (hWnd != NULL) ::InvalidateRect(hWnd, NULL, TRUE);

	if (idataTransfer)
	{
		idataTransfer->OnDataStarted();
	}
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_STARTED), e.lParam);
	
	for(int i=0; i<MM_DAC_NUM_BUFFER; i++)
	{
		mmr = waveOut.PrepareHeader(wb[i]);
		if (mmr!=MMSYSERR_NOERROR)
		{
			this->MessageBox(this->waveOut.GetErrorDescr(mmr), 
			L"Dac::OnMmWomOpen waveOut.PrepareHeader  wb", MB_OK | MB_ICONERROR);
		}
		else
		{
			preparedBufferCount++;
		}
		whrd.lpData = wb[i];
		whrd.dwBufferLength = wb[i].GetBufferSize();
		whrd.dwBytesRecorded = 0;
		if (idataTransfer) 
		{
			idataTransfer->OnData((LPARAM)&whrd);
		}
		else
		{
			::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_DAC_DATA), (LPARAM)&whrd);
		}
		bytesFilled = whrd.dwBytesRecorded;
		bEnding = (bytesFilled==0);
		wb[i].m_pWaveHdr->dwBytesRecorded = bytesFilled;
		//
		if (bEnding == true) return;
		//
		//this->UpdateLevels(wb[i].GetBuffer());
		mmr = waveOut.Write(wb[i]);
		if (mmr!=MMSYSERR_NOERROR)
		{
			this->MessageBox(waveOut.GetErrorDescr(mmr), 
			L"Mm::Dac::OnMmWomOpen waveOut.Write wb", MB_OK | MB_ICONERROR);
		}
	}
}

void Dac::Window_WomClose(Win::Event& e)
{
	if (idataTransfer)
	{
		idataTransfer->OnDataStopped();
	}
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_STOPPED), e.lParam);

	bPlaying = false;
	bEnding = false;
	this->DeleteBuffers();
	waveOut.ClearHandle();
	hWndParent = NULL;
	preparedBufferCount = 0;
	//sampleRate = 0;
	//b16Bits = false;
	info = L"OFF";
	showData = false;
	if (hWnd != NULL) ::InvalidateRect(hWnd, NULL, FALSE);
	//UpdateDisplayInformation();
	//this->levelLeft.SetLevel(0.0);
	//this->levelRight.SetLevel(0.0);
	//this->numBufferReady = 4;
}

void Dac::Window_WomDone(Win::Event& e)
{
	//numBufferReady--;
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_DATADONE), e.lParam);

	if (!waveOut.IsOpen())
	{
		e.returnValue = FALSE;
		return;
	}

	MMRESULT mmr;

	if (bEnding)
	{
		mmr = waveOut.UnprepareHeader((PWAVEHDR)e.lParam);
		if (mmr!=MMSYSERR_NOERROR)
		{
			this->MessageBox(waveOut.GetErrorDescr(mmr), 
			L"Dac::OnMmWomClose waveOut.UnpreparedHeader", MB_OK | MB_ICONERROR);
		}
		else
		{
			this->preparedBufferCount--;
		}

		if (preparedBufferCount==0) // Wait for all buffers to unprepare
		{
			mmr = waveOut.Close();
			if (mmr!=MMSYSERR_NOERROR)
			{
				this->MessageBox(waveOut.GetErrorDescr(mmr), 
				L"Dac::OnMmWomDone m_waveOut.Close()", MB_OK | MB_ICONERROR);
			}	
		}
	}
	else
	{
		PWAVEHDR p = (PWAVEHDR)e.lParam;
		unsigned int bytesFilled =  0;
		if (idataTransfer) 
		{
			idataTransfer->OnData(e.lParam);
		}
		else
		{
			::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_DAC_DATA), e.lParam);
		}
		bytesFilled = ((PWAVEHDR)e.lParam)->dwBytesRecorded;
		bEnding = (bytesFilled==0);
		p->dwBufferLength = bytesFilled;
		p->dwBytesRecorded = bytesFilled;

		if (true)//bEnding==false)
		{
			RefreshProgressInfo();
			mmr = waveOut.Write(((PWAVEHDR)e.lParam));
			if (mmr!=MMSYSERR_NOERROR)
				::MessageBox(hWnd, waveOut.GetErrorDescr(mmr), 
				L"Dac::OnMmWomDome waveOut.Write", MB_OK | MB_ICONERROR);
		}
	}
}

void Dac::RefreshProgressInfo()
{
	showData =  !showData;
	RepaintRect(4, 1);
}

void Dac::RepaintRect(const int row, const int col)
{
	RECT rect;
	rect.top = (int)(_fontHeight/2.0 + 1.5*_fontHeight * row+0.5);
	rect.bottom = (int)(rect.top + _fontHeight*1.5+0.5);

	if (col == 0)
	{
		rect.left = 0;
		rect.right = colWidth;
		
	}
	else if (col == 1)
	{
		rect.left = colWidth;
		rect.right = width;
	}
	::InvalidateRect(hWnd, &rect, FALSE);
}

//____________________________________________________________________ Adc
//bool Adc::bRegistered= false;

Adc::Adc(void)
{
	//if (!bRegistered)
	//{
	//	this->RegisterClassEx(LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_BTNFACE+1));
	//	bRegistered = true;
	//}

	bStopping = false;
	samplesPerSec = 0;
	b16Bits = true;
	bStereo = true;
	preparedBufferCount = 0;
	this->paused = false;
	hWndParent = NULL;
	info = NULL;
	showData = false;
	//isLinearDisplay = false;
	idataTransfer = NULL;
	fileName[0]='\0';
}

void Adc::SetIDataTransfer(Mm::IDataTransfer* idataTransfer)
{
	this->idataTransfer = idataTransfer;
}

double Adc::GetBufferDuration() // Call this function after Adc::Record
{
	int bitsPerSample = b16Bits ? 16 : 8;
	double bytesPerSecond = this->samplesPerSec*bitsPerSample/8;
	if (bStereo) bytesPerSecond = bytesPerSecond*2;
	return bufferSize/bytesPerSecond;
}

Adc::~Adc(void)
{
	Stop();
	Destructor();
}

bool Adc::EventHandler(Win::Event& e)
{
	if (e.uMsg!=WM_COMMAND) return false;
	const int notification = HIWORD(e.wParam);
	::SendMessage(::GetParent(hWnd), WM_COMMAND, MAKEWPARAM(id, notification), e.lParam);
	return true;
}

void Adc::DeleteBuffers(void)
{
	for(int i=0; i<MM_ADC_NUM_BUFFER; i++) wb[i].Destroy();
}

bool Adc::isSignDifferent(int x, int y)
{
	if (x>0 && y>0) return false;
	if (x<0 && y<0) return false;
	return true;
}

void Adc::GetZeroCrossings(LPSTR buffer, unsigned int bufferSize, int channels, int bitsPerSample, int& out_channel_1, int& out_channel_2)
{
	out_channel_1 = 0;
	out_channel_2 = 0;
	if (bufferSize == 0) return;
	int nBytesPerSample;
	int nSampleCount;
	int i;

	if (channels = 2 && bitsPerSample == 16) //16 Bits stereo
	{
		nBytesPerSample = 4;
		nSampleCount = bufferSize/nBytesPerSample;
		Sys::Sample16 *samples_16s = (Sys::Sample16*) buffer;
		
		for (i=1; i<nSampleCount; i++)
		{
			if (isSignDifferent(samples_16s[i].channel_1, samples_16s[i-1].channel_1)) out_channel_1++;
			if (isSignDifferent(samples_16s[i].channel_2, samples_16s[i-1].channel_2)) out_channel_2++;
		}
	}
	else if (channels == 1 && bitsPerSample == 16) //16 Bits mono
	{
		nBytesPerSample = 2;
		nSampleCount = bufferSize/nBytesPerSample;
		__int16 *samples_16m = (__int16 *)buffer;

		for (i=1; i<nSampleCount; i++)
		{
			if (isSignDifferent(samples_16m[i], samples_16m[i-1])) out_channel_1++;
		}
		out_channel_2 = out_channel_1;
	}
	else if (channels == 2 && bitsPerSample == 8) //8 Bits stereo
	{	
		nBytesPerSample = 2;
		nSampleCount = bufferSize/nBytesPerSample;
		Sys::Sample8 *sample_8s =(Sys::Sample8 *) buffer;

		for (i=1; i<nSampleCount; i++)
		{
			if (isSignDifferent(sample_8s[i].channel_1-127, sample_8s[i-1].channel_1-127)) out_channel_1++;
			if (isSignDifferent(sample_8s[i].channel_2-127, sample_8s[i-1].channel_2-127)) out_channel_2++;
		}
	}
	else if (channels == 1 && bitsPerSample == 8) //8 Bits mono
	{
		__int8 *sample_8m = (__int8*)buffer;
		for (i=1; i<(int)bufferSize; i++)
		{
			if (isSignDifferent(sample_8m[i]-127, sample_8m[i-1]-127)) out_channel_1++;
		}
		out_channel_2 = out_channel_1;
	}
}

void Adc::GetFrequency(LPSTR buffer, unsigned int bufferSize, int channels, int bitsPerSample, double& out_channel_1, double& out_channel_2)
{
	out_channel_1 = 0.0;
	out_channel_2 = 0.0;
	if (bufferSize == 0) return;
	int crossings_channel_1 = 0;
	int crossings_channel_2 = 0;
	Mm::Adc::GetZeroCrossings(buffer, bufferSize, channels, bitsPerSample, crossings_channel_1, crossings_channel_2);

	if (channels == 1 && bitsPerSample == 8)
	{
		out_channel_1 = 44100.0*crossings_channel_1/bufferSize;
		out_channel_2 = out_channel_1;
	} 
	else if (channels == 1 && bitsPerSample == 16)
	{
		out_channel_1 = 2.0*44100.0*crossings_channel_1/bufferSize;
		out_channel_2 = out_channel_1;
	}
	else if (channels == 2 && bitsPerSample == 8)
	{
		out_channel_1 = 2.0*44100.0*crossings_channel_1/bufferSize;
		out_channel_2 = 2.0*44100.0*crossings_channel_2/bufferSize;
	} 
	else if (channels == 2 && bitsPerSample == 16)
	{
		out_channel_1 = 2.0*44100.0*crossings_channel_1/bufferSize;
		out_channel_2 = 2.0*44100.0*crossings_channel_2/bufferSize;
	} 
}

void Adc::GetPhaseDifference(LPSTR buffer, unsigned int bufferSize, int channels, int& differenceCount)
{
	differenceCount = 0;
	if (bufferSize == 0) return;
	int nBytesPerSample;
	int nSampleCount;
	int i;
	bool isCounting = false;

	if (channels == 2) //16 Bits stereo
	{
		nBytesPerSample = 4;
		nSampleCount = bufferSize/nBytesPerSample;
		Sys::Sample16 *samples_16s = (Sys::Sample16*) buffer;
		
		for (i=1; i<nSampleCount; i++)
		{
			if (isSignDifferent(samples_16s[i].channel_1, samples_16s[i-1].channel_1)) isCounting = true;	
			if (isCounting) differenceCount++;
			if (isSignDifferent(samples_16s[i].channel_2, samples_16s[i-1].channel_2) && isCounting) break;
		}
	}
	else if (channels == 1)//8 Bits stereo
	{	
		nBytesPerSample = 2;
		nSampleCount = bufferSize/nBytesPerSample;
		Sys::Sample8 *sample_8s =(Sys::Sample8 *) buffer;

		for (i=1; i<nSampleCount; i++)
		{
			if (isSignDifferent(sample_8s[i].channel_1-127, sample_8s[i-1].channel_1-127)) isCounting = true;	
			if (isCounting) differenceCount++;
			if (isSignDifferent(sample_8s[i].channel_2-127, sample_8s[i-1].channel_2-127) && isCounting) break;
		}
	}
}

// 8 bits -> level [0, 127], 16 bits -> level[0 32768]
void Adc::GetMaxLevel(LPSTR buffer, unsigned int bufferSize, int channels, int bitsPerSample, int& out_channel_1, int& out_channel_2)
{
	out_channel_1 = 0;
	out_channel_2 = 0;
	if (bufferSize == 0) return;
	int nBytesPerSample;
	int nSampleCount;
	int nValue, i;

	if (channels == 2 && bitsPerSample == 16) //16 Bits stereo
	{
		nBytesPerSample = 4;
		nSampleCount = bufferSize/nBytesPerSample;
		Sys::Sample16 *samples_16s = (Sys::Sample16*) buffer;

		for (i=0; i<nSampleCount; i++)
		{
			nValue = abs(samples_16s[i].channel_1);
			if (out_channel_1<nValue) out_channel_1 = nValue;
			//
			nValue = abs(samples_16s[i].channel_2);
			if (out_channel_2<nValue) out_channel_2 = nValue;
		}
	}
	else if (channels ==1 && bitsPerSample == 16) //16 Bits mono
	{
		nBytesPerSample = 2;
		nSampleCount = bufferSize/nBytesPerSample;
		__int16 *samples_16m = (__int16 *)buffer;

		for (i=0; i<nSampleCount; i++)
		{
			nValue = abs(samples_16m[i]);
			if (out_channel_1<nValue) out_channel_1 = nValue;
		}
		out_channel_2 = out_channel_1;
	}
	else if (channels == 2 && bitsPerSample == 8) //8 Bits stereo
	{
		nBytesPerSample = 2;
		nSampleCount = bufferSize/nBytesPerSample;
		Sys::Sample8 *sample_8s =(Sys::Sample8 *) buffer;

		for (i=0; i<nSampleCount; i++)
		{
			nValue = abs(sample_8s[i].channel_1);
			nValue = abs(nValue -127);
			if (out_channel_1<nValue) out_channel_1 = nValue;
			//
			nValue = abs(sample_8s[i].channel_2);
			nValue = abs(nValue -127);
			if (out_channel_2<nValue) out_channel_2 = nValue;
		}
	}
	else if (channels == 1 && bitsPerSample == 8) //8 Bits mono
	{
		__int8 *sample_8m = (__int8*)buffer;
		for (i=0; i<(int)bufferSize; i++)
		{
			nValue = abs(sample_8m[i]);
			nValue = abs(nValue -127);
			if (out_channel_1<nValue) out_channel_1 = nValue;
		}
		out_channel_2 = out_channel_1;
	}
}

bool Adc::IsEvent(Win::Event& e, int notification)
{
	if (e.uMsg!=WM_COMMAND) return false;
	const int id = LOWORD(e.wParam);
	const int notificationd = HIWORD(e.wParam);
	if (id != this->id) return false;
	if (notificationd!=notification) return false;
	return true;
}

void Adc::GetRmsLevel(LPSTR buffer, unsigned int bufferSize, int channels, int bitsPerSample, double& out_channel_1, double& out_channel_2)
{
	out_channel_1 = 0.0;
	out_channel_2 = 0.0;
	if (bufferSize == 0) return;
	int nBytesPerSample;
	int nSampleCount;
	int nValue, i;

	if (channels == 2 && bitsPerSample == 16) //16 Bits stereo
	{
		nBytesPerSample = 4;
		nSampleCount = bufferSize/nBytesPerSample;
		Sys::Sample16 *samples_16s = (Sys::Sample16*)buffer;

		for (i=0; i<nSampleCount; i++)
		{
			nValue = samples_16s[i].channel_1;
			out_channel_1 += nValue*nValue;
			//
			nValue = samples_16s[i].channel_2;
			out_channel_2 += nValue*nValue;
		}
		out_channel_1/=(double)nSampleCount;
		out_channel_2/=(double)nSampleCount;
	}
	else if (channels ==1 && bitsPerSample ==16) //16 Bits mono
	{
		nBytesPerSample = 2;
		nSampleCount = bufferSize/nBytesPerSample;
		__int16 *samples_8m = (__int16*)buffer;

		for (i=0; i<nSampleCount; i++)
		{
			nValue = samples_8m[i];
			out_channel_1 += nValue*nValue;
		}
		out_channel_1/=(double)nSampleCount;
		out_channel_2 = out_channel_1;
	}
	else if (channels == 2 && bitsPerSample == 8) //8 Bits stereo
	{
		nBytesPerSample = 2;
		nSampleCount = bufferSize/nBytesPerSample;
		Sys::Sample8 *samples_8s = (Sys::Sample8*)buffer;

		for (i=0; i<nSampleCount; i++)
		{
			nValue = samples_8s[i].channel_1;
			nValue = nValue -127;
			out_channel_1 += nValue*nValue;
			//
			nValue = samples_8s[i].channel_2;
			nValue = nValue - 127;
			out_channel_2 += nValue*nValue;
		}
		out_channel_1/=(double)nSampleCount;
		out_channel_2/=(double)nSampleCount;
	}
	else if (channels == 1 && bitsPerSample == 8) //8 Bits mono
	{
		__int8 * samples_8m = (__int8*)buffer;
		for (i=0; i<(int)bufferSize; i++)
		{
			nValue = samples_8m[i];
			nValue = nValue -127;
			out_channel_1 += nValue * nValue;
		}
		out_channel_1/=(double)bufferSize;
		out_channel_2 = out_channel_1;
	}
	out_channel_2 = sqrt(out_channel_2);
	out_channel_1 = sqrt(out_channel_1);
}

void Adc::GetMaxLevel(LPARAM lParam, int channels, int bitsPerSample, int& out_channel_1, int& out_channel_2)
{
	PWAVEHDR pwd = (PWAVEHDR)lParam;
	GetMaxLevel(pwd->lpData, pwd->dwBytesRecorded, channels, bitsPerSample, out_channel_1, out_channel_2);
}

void Adc::GetRmsLevel(LPARAM lParam, int channels, int bitsPerSample, double& out_channel_1, double& out_channel_2)
{
	PWAVEHDR pwd = (PWAVEHDR)lParam;
	GetRmsLevel(pwd->lpData, pwd->dwBytesRecorded, channels, bitsPerSample, out_channel_1, out_channel_2);
}

void Adc::GetZeroCrossings(LPARAM lParam, int channels, int bitsPerSample, int& out_channel_1, int& out_channel_2)
{
	PWAVEHDR pwd = (PWAVEHDR)lParam;
	GetZeroCrossings(pwd->lpData, pwd->dwBytesRecorded, channels, bitsPerSample, out_channel_1, out_channel_2);
}

void Adc::GetFrequency(LPARAM lParam, int channels, int bitsPerSample, double& out_channel_1, double& out_channel_2)
{
	PWAVEHDR pwd = (PWAVEHDR)lParam;
	GetFrequency(pwd->lpData, pwd->dwBytesRecorded, channels, bitsPerSample, out_channel_1, out_channel_2);
}

void Adc::GetPhaseDifference(LPARAM lParam, int bitsPerSample, int& out_differenceCount)
{
	PWAVEHDR pwd = (PWAVEHDR)lParam;
	GetPhaseDifference(pwd->lpData, pwd->dwBytesRecorded, bitsPerSample, out_differenceCount);
}

bool Adc::IsRecording()
{
	return this->waveIn.IsOpen();
}

//void Adc::SetLinearDisplay(bool isLinearDisplay)
//{
//	this->isLinearDisplay = isLinearDisplay;
//	this->RefreshLinearDisplayInfo();
//}
//
//void Adc::RefreshLinearDisplayInfo(void)
//{
//	if (isLinearDisplay)
//	{
//		if (this->b16Bits)
//		{
//			this->levelLeft.SetRange(0.0, 32767.0);
//			this->levelRight.SetRange(0.0, 32767.0);
//		}
//		else
//		{
//			this->levelLeft.SetRange(0.0, 127.0);
//			this->levelRight.SetRange(0.0, 127.0);
//		}
//	}
//	else
//	{
//		if (this->b16Bits)
//		{
//			this->levelLeft.SetRange(1.0, log10(32767.0));
//			this->levelRight.SetRange(1.0, log10(32767.0));
//		}
//		else
//		{
//			this->levelLeft.SetRange(1.0, log10(127.0));
//			this->levelRight.SetRange(1.0, log10(127.0));
//		}
//	}
//}

wchar_t* Adc::Start(unsigned int sampleRate, int channels, int bitsPerSample, unsigned int bufferSize)
{
	if (waveIn.IsOpen()) return L"Adc is already ON";
	//this->RefreshLinearDisplayInfo();
	MMRESULT result;

	Destructor();
	//this->isLinearDisplay = isLinearDisplay;
	this->samplesPerSec = sampleRate;
	this->bufferSize = bufferSize;
	this->b16Bits = (bitsPerSample==16);
	this->bStereo = (channels==2);
	hWndParent = ::GetParent(this->hWnd);

	int i;

	for(i=0; i<MM_ADC_NUM_BUFFER; i++)
	{
		if (wb[i].Create(this->bufferSize)==false)
		{
			this->DeleteBuffers();
			return L"Adc::Start - Error during creating wb";
		}
	}

	if (b16Bits == false)
	{
		if (result = waveIn.OpenPCM8(this->hWnd, samplesPerSec, bStereo) != MMSYSERR_NOERROR)
			return L"Adc::Start - Error during opening waveIn";
	}
	else
	{
		if (result = waveIn.OpenPCM16(this->hWnd, samplesPerSec, bStereo) != MMSYSERR_NOERROR)
			return L"Adc::Start - Error during opening waveIn";
	}
	
	//______________________________________________________________ Prepare buffers
	for(i=0; i<MM_ADC_NUM_BUFFER; i++)
	{
		if (result = waveIn.PrepareHeader(wb[i]) != MMSYSERR_NOERROR)
		{
			this->DeleteBuffers();
			return L"Adc::Start - Unable to prepare header";
		}
		else
		{
			preparedBufferCount++;
		}
	}

	return NULL;
}

// To be call outside MM_WIM_ messages
bool Adc::Stop()
{
	MMRESULT result;

	bStopping = true;
	return true;
	if (this->waveIn.IsOpen())
	{
		if (result = this->waveIn.Reset() != MMSYSERR_NOERROR)
		{
			::MessageBox(hWndParent, waveIn.GetErrorDescr(result),
				L"Adc::Stop Error during m_waveIn.Reset()", MB_OK | MB_ICONERROR);
			return false;
		}
	}
	return true;
}

void Adc::Window_WimOpen(Win::Event& e)
{
	info = L"ON";
	::InvalidateRect(hWnd, NULL, FALSE);
	//this->UpdateDisplayInformation();

	MMRESULT result = 0;

	for(int i = 0; i<MM_ADC_NUM_BUFFER; i++)
	{
		if (result = this->waveIn.AddBuffer(wb[i]) != MMSYSERR_NOERROR)
		{
			::MessageBox(hWnd, waveIn.GetErrorDescr(result), 
				L"Adc::OnMmWimOpen Error during adding wb", MB_OK | MB_ICONERROR);
			return;
		}
	}
	if (idataTransfer)
	{
		idataTransfer->OnDataStarted();
	}
	::SendMessage(hWndParent, WM_COMMAND, MAKELPARAM(this->id, WIN_STARTED), e.lParam);

	bStopping = false;

	if (result = waveIn.Start() != MMSYSERR_NOERROR)
	{
		::MessageBox(hWnd, waveIn.GetErrorDescr(result), 
			L"Adc::OnMmWimOpen Error during  m_waveIn.Start()", MB_OK | MB_ICONERROR);
	}
}

void Adc::Window_WimClose(Win::Event& e)
{
	info = L"OFF";
	showData = false;
	//this->UpdateDisplayInformation();
	::InvalidateRect(hWnd, NULL, FALSE);
	this->DeleteBuffers();
	bStopping = false;
	this->waveIn.ClearHandle();
	if (idataTransfer)
	{
		idataTransfer->OnDataStopped();
	}
	::SendMessage(hWndParent, WM_COMMAND, MAKELPARAM(this->id, WIN_STOPPED), e.lParam);

	//this->levelLeft.SetLevel(0.0);
	//this->levelRight.SetLevel(0.0);
}

void Adc::Window_WimData(Win::Event& e)
{
	MMRESULT result;
	PWAVEHDR pwd = (PWAVEHDR)e.lParam;
	DWORD dwBytesRecorded = pwd->dwBytesRecorded;

	showData =  !showData;
	RECT rect; 
	rect.left = _fontHeight*8;
	rect.top = (int)(_fontHeight/2 + 6.0*_fontHeight+0.5);
	rect.right = rect.left + _fontHeight*8;
	rect.bottom = (int)(rect.top + _fontHeight*1.5+0.5);
	::InvalidateRect(hWnd, &rect, FALSE);

	if (dwBytesRecorded==0) return;
	if (this->paused==false)
	{
		//this->UpdateLevels(pwd->lpData);
		if (bStopping==false)
		{
			if (idataTransfer)
			{
				idataTransfer->OnData(e.lParam);
				bStopping = ( ((PWAVEHDR)e.lParam)->dwBytesRecorded==0);
			}
			::SendMessage(hWndParent, WM_COMMAND, MAKELPARAM(this->id, WIN_ADC_DATA), e.lParam);
		}
	}

	if (this->bStopping)
	{
		if (result = waveIn.UnprepareHeader(pwd) != MMSYSERR_NOERROR)
		{
			::MessageBox(hWnd, this->waveIn.GetErrorDescr(result),
				L"Adc::OnMmWimData m_waveIn.UnprepareHeader()", 
				MB_OK | MB_ICONERROR);
		}
		else
		{
			this->preparedBufferCount--;
		}

		if (preparedBufferCount==0)
		{
			if (result = this->waveIn.Close()!= MMSYSERR_NOERROR)
			{
				::MessageBox(hWnd, this->waveIn.GetErrorDescr(result),
				L"Adc::OnMmWimData m_waveIn.Close()", 
				MB_OK | MB_ICONERROR);
			}
			this->waveIn.ClearHandle();
		}
		return;
	}

	if (dwBytesRecorded==0) return;
	if (result = this->waveIn.AddBuffer(pwd) != MMSYSERR_NOERROR)
	{
		::MessageBox(hWnd, this->waveIn.GetErrorDescr(result),
			L"Adc::OnMmWimData Error during adding buffer pwd", MB_OK | MB_ICONERROR);		
		waveIn.Close();	
	}
}


void Adc::Destructor()
{
	bStopping = false;
	//
	this->DeleteBuffers();
	//
	hWndParent = NULL;
	//
	b16Bits = true;
	bStereo = true;
	preparedBufferCount = 0; 

}

//void Adc::UpdateLevels(LPSTR buffer)
//{
//	int channel_1, channel_2;
//	Mm::Adc::GetMaxLevel(buffer, this->bufferSize, bStereo, this->b16Bits, channel_1, channel_2);
//	if (this->isLinearDisplay)
//	{
//		this->levelLeft.SetLevel((double)channel_1);
//		this->levelRight.SetLevel((double)channel_2);
//	}
//	else
//	{
//		this->levelLeft.SetLevel(log10((double)channel_1));
//		this->levelRight.SetLevel(log10((double)channel_2));
//	}
//}

//void Adc::Window_Open(Win::Event& e)
//{
//	//colorDisplay.Create(0, L"Buffer: 0%", WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd, -1);
//	//levelLeft.Create(0, L"Buffer: 0%", WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd, -1);
//	//levelRight.Create(0, L"Buffer: 0%", WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd, -1);
//	//UpdateDisplayInformation();
//}
//
//void Adc::Window_Size(Win::Event& e)
//{
//	//const int height_ = (int)(height/3.0+0.5);
//	//colorDisplay.Move(0, 0, width, height_, true);
//	//levelLeft.Move(0, height_, width, height_, true);
//	//levelRight.Move(0, 2*height_, width, height_, true);
//}

//________________________________________________ IExportable
//void Adc::SetControlSize(int width, int height)
//{
//	this->width = width;
//	this->height = height;
//	//OnSizePrivate();
//}
//
//HWND Adc::GetControlInfo(int& width, int&height)
//{
//	width = this->width;
//	height = this->height;
//	return this->hWnd;
//}

void Adc::OnPaintControl(Win::Gdi& gdi)
{
	const int colWidth = _fontHeight*8;
	//_____________________________________________ Font
	Win::Gdi::Font font;
	LOGFONT logfont;
	this->GetLogfont(logfont);
	
	if (_printerFormat || width>10000)
	{
		font.Create(logfont);
		gdi.SelectFont_(font);
	}
	else
	{
		if (_hfont) gdi.SelectFont__(_hfont);
	}
	wchar_t displayInfo[256];
	wchar_t caption[64];

	//____________________________ Pen
	Win::Gdi::Pen pen(PS_SOLID, 1, _lineColor);
	gdi.SelectPen_(pen);

	//____________________________ Background
	RECT rect = gdi.GetRcPaint();//{0, 0, this->width, this->height};
	Win::Gdi::Brush brush;
	if (this->Enabled)
	{
		brush.CreateSolid(_backColor);
	}
	else
	{
		brush.CreateSolid(WIN_BACK_DISABLED);
	}
	gdi.FillRect(rect, brush);

	//____________________________ Vertical Line
	gdi.Line(colWidth, rect.top, colWidth, rect.bottom);
	//____________________________ Text
	if (this->Enabled)
	{
		gdi.SetBkColor(_backColor);
		gdi.SetTextColor(_textColor);
	}
	else
	{
		gdi.SetBkColor(WIN_BACK_DISABLED);
		gdi.SetTextColor(WIN_TEXT_DISABLED);
	}
	gdi.SetTextAlign(TA_LEFT | TA_TOP);
	//___________________________________________________________ Name 
	rect.left = 0;
	rect.top = _fontHeight/2;
	rect.right = colWidth;
	rect.bottom = (int)(rect.top + _fontHeight*1.5+0.5);
	if (gdi.DoRcPaintOverlap(rect))
	{
		if (this->GetTextLength()>0)
		{
			this->GetWindowText(caption, 64);
		}
		else
		{
			_snwprintf_s(caption, 64, _TRUNCATE, L"%s", L"ADC");
		}
		caption[64-1] = '\0';
		gdi.TextOut(_fontHeight/2, rect.top, caption);
	}
	rect.left = colWidth;
	rect.right = width;
	if (gdi.DoRcPaintOverlap(rect))
	{
		if (info==NULL) info = L"OFF";
		gdi.TextOut(colWidth + _fontHeight/2, rect.top, info);
	}
	gdi.Line(0, rect.bottom-2, width, rect.bottom-2);

	DrawDataRow(gdi, 1, L"Resolution", b16Bits ? L"16 bits" : L"8 bits");
	DrawDataRow(gdi, 2, L"Setup", bStereo ? L"2 channels" : L"1 channel");
	//
	_snwprintf_s(displayInfo, 256, _TRUNCATE, L"%d Hz", samplesPerSec);
	DrawDataRow(gdi, 3, L"Sample Rate", displayInfo);
	//
	DrawDataRow(gdi, 4, L"Data", showData ? L". . . ." : L" . . . .");
	//___________________________________________________________ FileName
	if (wcslen(fileName)==0) return;
	rect.left = 0;
	rect.top = (int)(_fontHeight/2 + 5*1.5*_fontHeight+0.5);
	rect.right = colWidth;
	rect.bottom = (int)(rect.top + _fontHeight*1.5+0.5);
	if (gdi.DoRcPaintOverlap(rect))
	{
		gdi.TextOut(rect.left, rect.top, L"File name");
	}
	rect.left = colWidth;
	rect.right = width;
	rect.bottom = height;
	if (gdi.DoRcPaintOverlap(rect))
	{
		vector<wstring> path;
		Sys::Convert::ToVectorOfStrings(fileName, '\\', path);
		int y = rect.top;
		gdi.TextOut(rect.left, y, path[path.size()-1].c_str());
		//for(size_t i = 0; i<path.size(); i++)
		//{
		//	//_snwprintf_s(displayInfo, 256, _TRUNCATE, L"%d Hz", samplesPerSec);
		//	gdi.TextOut(rect.left, y, path[i].c_str());
		//	y += (int)(1.5*_fontHeight+0.5);
		//}
	}
}

void Adc::DrawDataRow(Win::Gdi& gdi, int index, const wchar_t* name, const wchar_t* value)
{
	RECT rect;
	const int colWidth = 8*_fontHeight;

	rect.left = 0;
	rect.top = (int)(_fontHeight/2.0 + 1.5*_fontHeight * index+0.5);
	rect.right = colWidth;
	rect.bottom = (int)(rect.top + _fontHeight*1.5+0.5);
	if (gdi.DoRcPaintOverlap(rect))
	{
		gdi.TextOut(_fontHeight/2, rect.top, name);
	}
	rect.left = colWidth;
	rect.right = width;
	if (gdi.DoRcPaintOverlap(rect))
	{
		if (index == 4) rect.top -= _fontHeight/4;
		gdi.TextOut(_fontHeight/2+colWidth, rect.top, value);
	}
}

//_____________________________________________________________________ MidiOut
MidiOut::MidiOut(void)
{
	hMidiOut = NULL;
	index_ch0 = 0;
	index_ch1 = 0;
	duration_ch0 = 0;
	duration_ch1 = 0;
	active_ch0 = false;
	active_ch1 = false;
}

MidiOut::~MidiOut(void)
{
	Reset();
	Close();
}

void MidiOut::OnPaintControl(Win::Gdi& gdi)
{
	Win::Gdi::Brush brushBack(_backColor);
	wchar_t text[64];
	wchar_t alt_text[2];
	alt_text[0] = 0x266B;
	alt_text[1] ='\0';
	RECT rc = {0, 0, width, height};
	if (_hfont) gdi.SelectFont__(_hfont);
	gdi.FillRect(gdi.GetRcPaint(), brushBack);

	if (hMidiOut==NULL)
	{
		gdi.SetTextColor(RGB(100, 100, 100));
	}
	else
	{
		gdi.SetTextColor(_textColor);
	}
	gdi.SetBkMode(true);
	if (active_ch0 == false && active_ch1 == false)
	{
		_snwprintf_s(text, 64, _TRUNCATE, L"%s", alt_text);
	}
	else if (active_ch0 == false && active_ch1 == true)
	{
		_snwprintf_s(text, 64, _TRUNCATE, L"%s channel 1: %d", alt_text, index_ch1);
	}
	else if (active_ch0 == true && active_ch1 == false)
	{
		_snwprintf_s(text, 64, _TRUNCATE, L"%s channel 0: %d", alt_text, index_ch0);
	}
	if (active_ch0 == true && active_ch1 == true)
	{
		_snwprintf_s(text, 64, _TRUNCATE, L"%s ch 0: %d, ch 1: %d", alt_text, index_ch0 , index_ch1);
	}
	gdi.TextOutCenter(rc, text, true, true);
}

// uDeviceID = MIDIMAPPER, returns MMSYSERR_NOERROR if successful
MMRESULT MidiOut::Open(UINT uDeviceID)
{
	Reset();
	Close();
	MMRESULT mmr = ::midiOutOpen(&hMidiOut, uDeviceID, 0, 0 ,0);
	if (mmr!=MMSYSERR_NOERROR) hMidiOut = NULL;
	::InvalidateRect(hWnd, NULL, true);
	return mmr;
}

MMRESULT MidiOut::Close(void)
{
	MMRESULT mmresult = ::midiOutClose(hMidiOut);
	index_ch0 = 0;
	index_ch1 = 0;
	duration_ch0 = 0;
	duration_ch1 = 0;
	active_ch0 = false;
	active_ch1 = false;
	hMidiOut = NULL;
	if (hWnd) ::InvalidateRect(hWnd, NULL, true);
	return mmresult;
}

MMRESULT MidiOut::Reset(void)
{
	index_ch0 = 0;
	index_ch1 = 0;
	duration_ch0 = 0;
	duration_ch1 = 0;
	active_ch0 = false;
	active_ch1 = false;
	return ::midiOutReset(hMidiOut);
}

MMRESULT MidiOut::ShortMessage(int status, int channel, int data1, int data2)
{
	DWORD message = status | channel | (data1 << 8) | (data2 << 16) ;
     
	return ::midiOutShortMsg (hMidiOut, message);
}

void MidiOut::PlayNote(int channel, int note, int octave)
{
	if (note == NONE_MIDI) return;
	ShortMessage(0x90, channel, note+12*octave, MIDI_ON);
}

void MidiOut::StopNote(int channel, int note, int octave)
{
	if (note == NONE_MIDI) return;
	ShortMessage(0x90, channel, note+12*octave, MIDI_OFF);
}

void MidiOut::Play(int tempo)
{
	//_______________________________________________ channel 0
	active_ch0 = false;
	index_ch0 = 0;
	duration_ch0 = 0;
	if (ch0.size()>0)
	{
		PlayNote(0, ch0[index_ch0].note, ch0[index_ch0].octave);
		duration_ch0 = ch0[index_ch0].duration;
		active_ch0 = true;
	}

	//_______________________________________________ channel 1
	active_ch1 = false;
	index_ch1 = 0;
	duration_ch1 = 0;
	if (ch1.size()>0)
	{
		PlayNote(1, ch1[index_ch1].note, ch1[index_ch1].octave);
		duration_ch1 = ch1[index_ch1].duration;
		active_ch1 = true;
	}
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
	timer.Set(1, tempo);
}

void MidiOut::Window_Timer(Win::Event& e)
{
	//________________________________________________ ch 0
	if (active_ch0 == true)
	{
		duration_ch0--;
		if (duration_ch0 == 0)
		{
			StopNote(0, ch0[index_ch0].note, ch0[index_ch0].octave);
			//
			index_ch0++;
			if (index_ch0 >= (int)ch0.size()) 
			{
				StopSong();
				return;
			}
			PlayNote(0, ch0[index_ch0].note, ch0[index_ch0].octave);
			duration_ch0 = ch0[index_ch0].duration;
		}
	}
	//________________________________________________ ch 1
	if (active_ch1 == true)
	{
		duration_ch1--;
		if (duration_ch1 == 0)
		{
			StopNote(1, ch1[index_ch1].note, ch1[index_ch1].octave);
			//
			index_ch1++;
			if (index_ch1 >= (int)ch1.size()) 
			{
				StopSong();
				return;
			}
			PlayNote(1, ch1[index_ch1].note, ch1[index_ch1].octave);
			duration_ch1 = ch1[index_ch1].duration;
		}
	}
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

void MidiOut::StopSong()
{
	this->timer.Kill(1);
	index_ch0 = 0;
	index_ch1 = 0;
	duration_ch0 = 0;
	duration_ch1 = 0;
	active_ch0 = false;
	active_ch1 = false;
	if (hWnd) ::InvalidateRect(hWnd, NULL, FALSE);
}

//____________________________________________________________________ Mixer
// The mixer has several lines, each lines has several controls, each control has several control details
Mixer::Mixer(void)
{
	hMixer = NULL;
	src_waveout_control_id=0;
	main_volume_control_id=0;
	src_mic_control_id=0;
}

Mixer::~Mixer(void)
{
	Close();
}

wchar_t * Mixer::Open(void)
{
	MMRESULT mmr = ::mixerOpen((LPHMIXER)&hMixer, 0, NULL, NULL, MIXER_OBJECTF_MIXER);

	if (mmr!=MMSYSERR_NOERROR)
	{
		hMixer = NULL;
		if (mmr==MMSYSERR_ALLOCATED) return L"The specified resource is already allocated by the maximum number of clients possible.";
		if (mmr==MMSYSERR_BADDEVICEID) return L"The uMxId parameter specifies an invalid device identifier. ";
		if (mmr==MMSYSERR_INVALFLAG) return L"One or more flags are invalid. ";
		if (mmr==MMSYSERR_INVALHANDLE) return L"The uMxId parameter specifies an invalid handle. ";
		if (mmr==MMSYSERR_INVALPARAM) return L"One or more parameters are invalid. ";
		if (mmr==MMSYSERR_NODRIVER) return L"No mixer device is available for the object specified by uMxId. Note that the location referenced by uMxId will also contain the value – 1. ";
		if (mmr==MMSYSERR_NOMEM) return L"Unable to allocate resources. ";
	}

	wchar_t* error = this->Open_Src_Waveout();
	if (error) return error;
	error = this->Open_Main_Volume();
	if (error) return error;
	error = this->Open_Src_Mic();
	if (error) return error;
	error = this->Open_Src_Line();
	if (error) return error;

	return NULL;
}

void Mixer::Close(void)
{
	if (hMixer) ::mixerClose(hMixer);
	hMixer=NULL;
}

wchar_t * Mixer::Open_Src_Waveout(void)
{
	return this->GetControlID(MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT, src_waveout_control_id);
}

wchar_t * Mixer::Open_Src_Mic(void)
{
	return this->GetControlID(MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE, src_mic_control_id);
}

wchar_t * Mixer::Open_Src_Line(void)
{
	return this->GetControlID(MIXERLINE_COMPONENTTYPE_SRC_LINE, src_line_control_id);
}

wchar_t* Mixer::GetControlID(DWORD dwComponentType, DWORD& dwControlID)
{
	//*********************************************************************** GetLine
	MIXERLINE mxl;
	mxl.cbStruct = sizeof(MIXERLINE);
	mxl.dwComponentType = dwComponentType;
	MMRESULT mmr = ::mixerGetLineInfo((HMIXEROBJ)hMixer, &mxl, MIXER_GETLINEINFOF_COMPONENTTYPE);
	if (mmr!=MMSYSERR_NOERROR)
	{
		if (mmr==MIXERR_INVALLINE) return L"The audio line reference is invalid.";
		if (mmr==MMSYSERR_BADDEVICEID) return L"The hmxobj parameter specifies an invalid device identifier. ";
		if (mmr==MMSYSERR_INVALFLAG) return L"One or more flags are invalid. ";
		if (mmr==MMSYSERR_INVALHANDLE) return L"The hmxobj parameter specifies an invalid handle. ";
		if (mmr==MMSYSERR_INVALPARAM) return L"One or more parameters are invalid. ";
		if (mmr==MMSYSERR_NODRIVER) return L"No mixer device is available for the object specified by hmxobj."; 
	}
	//::MessageBox(hWnd, mxl.szName, mxl.szShortName, MB_OK);

	//******************************************************************** GetLineControls
	MIXERLINECONTROLS mxlc;
	MIXERCONTROL mxc[1];
	mxlc.cbStruct = sizeof(MIXERLINECONTROLS);
	mxlc.dwLineID =mxl.dwLineID;// 0xffff0000;//;//;//MIXER_GETLINEINFOF_LINEID;
	mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
	mxlc.cControls = 1;
	mxlc.cbmxctrl = sizeof(MIXERCONTROL);
	mxlc.pamxctrl = mxc;
	mmr = ::mixerGetLineControls((HMIXEROBJ)hMixer, &mxlc, MIXER_GETLINECONTROLSF_ONEBYTYPE);
	if (mmr!=MMSYSERR_NOERROR)
	{
		if (mmr==MIXERR_INVALCONTROL) return L"The control reference is invalid. ";
		if (mmr==MIXERR_INVALLINE) return L"The audio line reference is invalid. ";
		if (mmr==MMSYSERR_BADDEVICEID) return L"The hmxobj parameter specifies an invalid device identifier. ";
		if (mmr==MMSYSERR_INVALFLAG) return L"One or more flags are invalid. ";
		if (mmr==MMSYSERR_INVALHANDLE) return L"The hmxobj parameter specifies an invalid handle. ";
		if (mmr==MMSYSERR_INVALPARAM) return L"One or more parameters are invalid. ";
		if (mmr==MMSYSERR_NODRIVER) return L"No mixer device is available for the object specified by hmxobj. ";
	}
	dwControlID = mxc[0].dwControlID;

	return NULL;
}

wchar_t* Mixer::Open_Main_Volume(void)
{
	MIXERLINECONTROLS mxlc;
	MIXERCONTROL mxc[1];
	mxlc.cbStruct = sizeof(MIXERLINECONTROLS);
	mxlc.dwLineID = 0xffff0000;//;//;//MIXER_GETLINEINFOF_LINEID;
	mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
	mxlc.cControls = 1;
	mxlc.cbmxctrl = sizeof(MIXERCONTROL);
	mxlc.pamxctrl = mxc;
	MMRESULT mmr = ::mixerGetLineControls((HMIXEROBJ)hMixer, &mxlc, MIXER_GETLINECONTROLSF_ONEBYTYPE);
	if (mmr!=MMSYSERR_NOERROR)
	{
		if (mmr==MIXERR_INVALCONTROL) return L"The control reference is invalid. ";
		if (mmr==MIXERR_INVALLINE) return L"The audio line reference is invalid. ";
		if (mmr==MMSYSERR_BADDEVICEID) return L"The hmxobj parameter specifies an invalid device identifier. ";
		if (mmr==MMSYSERR_INVALFLAG) return L"One or more flags are invalid. ";
		if (mmr==MMSYSERR_INVALHANDLE) return L"The hmxobj parameter specifies an invalid handle. ";
		if (mmr==MMSYSERR_INVALPARAM) return L"One or more parameters are invalid. ";
		if (mmr==MMSYSERR_NODRIVER) return L"No mixer device is available for the object specified by hmxobj. ";
	}
	main_volume_control_id = mxc[0].dwControlID;

	return NULL;
}

wchar_t* Mixer::Set_Src_Waveout(DWORD level)
{
	return this->SetLevel(level, src_waveout_control_id);
}

wchar_t* Mixer::Get_Src_Waveout(DWORD& level)
{
	return this->GetLevel(level, src_waveout_control_id);
}

wchar_t* Mixer::Set_Src_Mic(DWORD level)
{
	return this->SetLevel(level, src_mic_control_id);
}

wchar_t* Mixer::Get_Src_Mic(DWORD& level)
{
	return this->GetLevel(level, src_mic_control_id);
}

wchar_t* Mixer::Set_Src_Line(DWORD level)
{
	return this->SetLevel(level, src_line_control_id);
}

wchar_t* Mixer::Get_Src_Line(DWORD& level)
{
	return this->GetLevel(level, src_line_control_id);
}

wchar_t* Mixer::Set_Main_Volume(DWORD level)
{
	return this->SetLevel(level, main_volume_control_id);
}

wchar_t* Mixer::Get_Main_Volume(DWORD& level)
{
	return this->GetLevel(level, main_volume_control_id);
}

wchar_t* Mixer::GetLevel(DWORD& level, DWORD controlID)
{
	MIXERCONTROLDETAILS mxcd;
	MIXERCONTROLDETAILS_UNSIGNED mxcdVol;
	mxcd.cChannels = 1;
	mxcd.cMultipleItems = 0;
	mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mxcd.paDetails = &mxcdVol;
	mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
	mxcd.dwControlID = controlID;

	MMRESULT mmr = ::mixerGetControlDetails((HMIXEROBJ)hMixer, &mxcd, MIXER_GETCONTROLDETAILSF_VALUE);
	if (mmr!=MMSYSERR_NOERROR)
	{
		if (mmr==MIXERR_INVALCONTROL) return L"The control reference is invalid. ";
		if (mmr==MMSYSERR_BADDEVICEID) return L"The hmxobj parameter specifies an invalid device identifier. ";
		if (mmr==MMSYSERR_INVALFLAG) return L"One or more flags are invalid. ";
		if (mmr==MMSYSERR_INVALHANDLE) return L"The hmxobj parameter specifies an invalid handle. ";
		if (mmr==MMSYSERR_INVALPARAM) return L"One or more parameters are invalid. ";
		if (mmr==MMSYSERR_NODRIVER) return L"No mixer device is available for the object specified by hmxobj. ";
	}
	level= mxcdVol.dwValue;
	return NULL;
}

wchar_t* Mixer::SetLevel(DWORD level, DWORD controlID)
{
	MIXERCONTROLDETAILS mxcd;
	MIXERCONTROLDETAILS_UNSIGNED mxcdVol;
	mxcd.cChannels = 1;
	mxcd.cMultipleItems = 0;
	mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mxcd.paDetails = &mxcdVol;
	mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
	mxcd.dwControlID = controlID;
	mxcdVol.dwValue = level;

	MMRESULT mmr = ::mixerSetControlDetails((HMIXEROBJ)hMixer, &mxcd, MIXER_SETCONTROLDETAILSF_VALUE);
	if (mmr!=MMSYSERR_NOERROR)
	{
		if (mmr==MIXERR_INVALCONTROL) return L"The control reference is invalid. ";
		if (mmr==MMSYSERR_BADDEVICEID) return L"The hmxobj parameter specifies an invalid device identifier. ";
		if (mmr==MMSYSERR_INVALFLAG) return L"One or more flags are invalid. ";
		if (mmr==MMSYSERR_INVALHANDLE) return L"The hmxobj parameter specifies an invalid handle. ";
		if (mmr==MMSYSERR_INVALPARAM) return L"One or more parameters are invalid. ";
		if (mmr==MMSYSERR_NODRIVER) return L"No mixer device is available for the object specified by hmxobj. ";
	}
	return NULL;
}

//
//	MIXERLINECONTROLS mxlc;
//	MIXERCONTROL mxc[1];	
////	HMIXER VolCtrlIDMtr;
//		//MIXER_SPEAKEROUT_LINEID
//		//UINT mxId;
//		//mmr = ::mixerGetID((HMIXEROBJ)m_hWaveIn, &mxId, MIXER_OBJECTF_HWAVEIN);
//		//if (mmr!=MMSYSERR_NOERROR)
//		//{
//			mxlc.cbStruct = sizeof(MIXERLINECONTROLS);
//			mxlc.dwLineID =mxl.dwLineID;// 0xffff0000;//;//;//MIXER_GETLINEINFOF_LINEID;
//			mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
//			mxlc.cControls = 1;
//			mxlc.cbmxctrl = sizeof(MIXERCONTROL);
//			mxlc.pamxctrl = mxc;
//			mmr = ::mixerGetLineControls((HMIXEROBJ)hMixer, &mxlc, MIXER_GETLINECONTROLSF_ONEBYTYPE);
//			if (mmr!=MMSYSERR_NOERROR)
//			{
//				if (mmr==MIXERR_INVALCONTROL) errorDsc= L"MIXERR_INVALCONTROL";
//				if (mmr==MIXERR_INVALLINE) errorDsc= L"MIXERR_INVALLINE";
//				if (mmr==MMSYSERR_BADDEVICEID ) errorDsc= L"MMSYSERR_BADDEVICEID";
//				if (mmr==MMSYSERR_INVALFLAG) errorDsc= L"MMSYSERR_INVALFLAG";
//				if (mmr==MMSYSERR_INVALHANDLE) errorDsc= L"MMSYSERR_INVALHANDLE";
//				if (mmr==MMSYSERR_INVALPARAM) errorDsc= L"MMSYSERR_INVALPARAM";
//				if (mmr==MMSYSERR_NODRIVER ) errorDsc= L"MMSYSERR_NODRIVER";
//				::MessageBox(hWnd, errorDsc, L"WaveIn::SetLineVolume", MB_OK | MB_ICONERROR);
//			}
//			else
//			{
//				DWORD VolCtrlIDMtr = mxc[0].dwControlID;
//				MIXERCONTROLDETAILS mxcd;
//				MIXERCONTROLDETAILS_UNSIGNED mxcdVol;
//				mxcd.cChannels = 1;
//				mxcd.cMultipleItems = 0;
//				mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
//				mxcd.paDetails = &mxcdVol;
//				mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
//				mxcd.dwControlID = VolCtrlIDMtr;
//				mmr = ::mixerGetControlDetails((HMIXEROBJ)hMixer, &mxcd, MIXER_GETCONTROLDETAILSF_VALUE);
//				if (mmr!=MMSYSERR_NOERROR)
//				{
//					::MessageBox(hWnd, this->GetErrorDescr(mmr), L"WaveIn::SetLineVolume", MB_OK | MB_ICONERROR);
//				}
//				wchar_t texto[256];
//				_snwprintf(texto, 256, L"%d", mxcdVol.dwValue);
//				::MessageBox(hWnd, texto, NULL, MB_OK);
//			}
//		//}
//	}


//____________________________________________________________________ FileAdc
FileAdc::FileAdc(void)
{
	this->paused = false;
	this->isBreaking = false;
	//this->SetLinearDisplay(false);
	this->SetIDataTransfer(this);
}

FileAdc::~FileAdc(void)
{
}

void FileAdc::Break(const wchar_t* fileName)//Starts storing data to a new file
{
	this->isBreaking = true;
	lstrcpyn(this->fileName, fileName, 1024);
	this->fileName[1023]='\0';
}

// This will generate a MM_WIM_OPEN message
wchar_t* FileAdc::Record(int samplesPerSec, int channels, int bitsPerSample, int bufferSize, const wchar_t* fileName)
{
	this->fileName[0]='\0';
	//
	wchar_t* error = waveFile.OpenForWritting(samplesPerSec, bStereo, bitsPerSample, fileName);
	if (error) return error;

	error = Start(samplesPerSec, channels, bitsPerSample, bufferSize);
	if (error) return error;

	lstrcpyn(this->fileName, fileName, 1024);
	this->fileName[1023]='\0';
	//
	//RECT rect; 
	//rect.left = _fontHeight*8;
	//rect.top = (int)(_fontHeight/2 + 7.5*_fontHeight+0.5);
	//rect.right = rect.left + _fontHeight*8;
	//rect.bottom = height;
	::InvalidateRect(hWnd, NULL, FALSE);

	return NULL;
}

void FileAdc::OnDataStarted()
{
}

void FileAdc::OnDataStopped()//It is called when the input device is closed
{
	waveFile.Close();
	//
	this->fileName[0]='\0';
	RECT rect; 
	rect.left = _fontHeight*8;
	rect.top = (int)(_fontHeight/2 + 7.5*_fontHeight+0.5);
	rect.right = rect.left + _fontHeight*8;
	rect.bottom = height;
	::InvalidateRect(hWnd, &rect, FALSE);
}

void FileAdc::OnData(LPARAM lParam)
{
	PWAVEHDR pwd = (PWAVEHDR)lParam;
	unsigned int bytesRecorded = pwd->dwBytesRecorded;

	if (this->isBreaking)
	{
		this->isBreaking = false;
		//
		wchar_t *error = waveFile.OpenForWritting(44100, true, 16, this->fileName);
		if (error)
		{
			this->fileName[0]='\0';
			this->MessageBox(L"Unable to open file for writting", L"FileAdc::OnData", MB_OK | MB_ICONERROR);
		}
		RECT rect; 
		rect.left = _fontHeight*8;
		rect.top = (int)(_fontHeight/2 + 7.5*_fontHeight+0.5);
		rect.right = rect.left + _fontHeight*8;
		rect.bottom = height;
		::InvalidateRect(hWnd, &rect, FALSE);
	}

	if (bytesRecorded>0)
	{
		if (this->paused==false)
		{
			if  (waveFile.WriteData(pwd->lpData, bytesRecorded)==false)
			{
				this->MessageBox(L"Unable to write file", L"FileAdc::ProcessData", MB_OK | MB_ICONERROR);
			}
		}
	}
}

//____________________________________________________________________ FileDac
FileDac::FileDac(void)
{
	overlapGain = 1.0;
	overlapFactor = 1.0;
	bufferA = NULL;
	bufferB = NULL;
	//overlapIndex = 0;
	filename[0]='\0';
	ClearSongInfo(si);
	state = WIN_FILEDAC_CHA;
	smoothFileTransition = true;
	this->SetIDataTransfer(this);
	//file.CreateForWritting(L"C:\\hola.csv");
}

FileDac::~FileDac(void)
{
	if (bufferA) delete [] bufferA;
	if (bufferB) delete [] bufferB;
}

void FileDac::Reset()
{
	state = WIN_FILEDAC_CHA;
	filename[0]='\0';
	ClearSongInfo(si);
	::InvalidateRect(hWnd, NULL, FALSE);
}

void FileDac::RefreshProgressInfo()
{
	//showData =  !showData;
	RepaintRect(0, 0);
}

void FileDac::ModifySamples(CHAR* buffer, int numSamples, int bitsPerSample, int numChannels, int sampleRate)
{
	FileDac::DataInfo di;
	di.samples = buffer;
	di.numSamples = numSamples;
	di.bitsPerSample = bitsPerSample;
	di.numChannels = numChannels;
	di.sampleRate = sampleRate;
	::SendMessage(::GetParent(hWnd), WM_COMMAND, MAKEWPARAM(this->id, WIN_MODIFYSAMPLES), (LPARAM)(FileDac::DataInfo*)&di);
}

void FileDac::OnPaintControl(Win::Gdi& gdi)
{
	colWidth = 6*_fontHeight;
	//_____________________________________________ Font
	Win::Gdi::Font font;
	
	if (_printerFormat || width>10000)
	{
		LOGFONT logfont;
		this->GetLogfont(logfont);
		logfont.lfHeight = -(height)/2;
		font.Create(logfont);
		gdi.SelectFont_(font);
	}
	else
	{
		if (_hfont) gdi.SelectFont__(_hfont);
	}

	wchar_t displayInfo[64];
	//wchar_t caption[64];

	//____________________________ Pen
	Win::Gdi::Pen pen(PS_SOLID, 1, _lineColor);
	gdi.SelectPen_(pen);

	//____________________________ Background
	RECT rect = gdi.GetRcPaint();//{0, 0, this->width, this->height};
	Win::Gdi::Brush brush;
	if (this->Enabled)
	{
		brush.CreateSolid(_backColor);
	}
	else
	{
		brush.CreateSolid(WIN_BACK_DISABLED);
	}
	gdi.FillRect(rect, brush);

	//____________________________ Vertical Line
	gdi.Line(colWidth, rect.top, colWidth, rect.bottom);
	//____________________________ Text
	if (this->Enabled)
	{
		gdi.SetBkColor(_backColor);
		gdi.SetTextColor(_textColor);
	}
	else
	{
		gdi.SetBkColor(WIN_BACK_DISABLED);
		gdi.SetTextColor(WIN_TEXT_DISABLED);
	}
	gdi.SetTextAlign(TA_LEFT | TA_TOP);
	//___________________________________________________________ Name 
	int seconds = (int)GetRemainingSeconds();
	_snwprintf_s(displayInfo, 64, _TRUNCATE, L"%02d:%02d", seconds/60, seconds%60);
	//
	DrawDataRow(gdi, 0, displayInfo, si.songName);
	DrawDataRow(gdi, 1, b16Bits ? L"16 bits" : L"8 bits", si.album);
	DrawDataRow(gdi, 2, numChannels == 2 ? L"stereo" : L"mono", si.artist);
	//
	_snwprintf_s(displayInfo, 64, _TRUNCATE, L"%.1f KHz", sampleRate/1000.0);
	DrawDataRow(gdi, 3, displayInfo, si.details);
}

void FileDac::ClearSongInfo(Mm::FileDac::SongInfo& si)
{
	si.songName[0] = '\0';
	si.album[0] = '\0';
	si.artist[0] = '\0';
	si.details[0] = '\0';
}

void FileDac::SeparateSongInfo(const wchar_t* filename, wchar_t separator, Mm::FileDac::SongInfo& si)
{
	ClearSongInfo(si);
	const int len = wcslen(filename);
	if (len == 0) return;
	vector<wstring> list;
	Sys::Convert::ToVectorOfStrings(filename, separator, list);
	const int count = list.size();
	if (separator == '\\') //_____________________________ file path
	{
		if (count >= 1) CleanString(list[count-1], si.songName);
		if (count >= 2) CleanString(list[count-2], si.album);
		if (count >= 3) CleanString(list[count-3], si.artist);
		if (count >= 4) CleanString(list[count-4], si.details);
	}
	else if (separator == ' ') //__________________________ error
	{
		if (count %2 == 0)
		{
			if (count >=2) _snwprintf_s(si.songName, 32, _TRUNCATE, L"%s %s", list[0].c_str(), list[1].c_str());
			if (count >=4) _snwprintf_s(si.album, 32, _TRUNCATE, L"%s %s", list[2].c_str(), list[3].c_str());
			if (count >=6) _snwprintf_s(si.artist, 32, _TRUNCATE, L"%s %s", list[4].c_str(), list[5].c_str());
			if (count >=8) _snwprintf_s(si.artist, 32, _TRUNCATE, L"%s %s", list[6].c_str(), list[7].c_str());
		}
		else
		{
			if (count ==1)
			{
				_snwprintf_s(si.songName, 32, _TRUNCATE, L"%s", list[0].c_str());
				return;
			}
			else if (count >=2)
			{
				_snwprintf_s(si.songName, 32, _TRUNCATE, L"%s %s", list[0].c_str(), list[1].c_str());
			}
			//
			if (count ==3)
			{
				_snwprintf_s(si.album, 32, _TRUNCATE, L"%s", list[2].c_str());
				return;
			}
			else if (count >=4)
			{
				_snwprintf_s(si.album, 32, _TRUNCATE, L"%s %s", list[2].c_str(), list[3].c_str());
			}
			//
			if (count ==5)
			{
				_snwprintf_s(si.artist, 32, _TRUNCATE, L"%s", list[4].c_str());
				return;
			}
			else if (count >=6)
			{
				_snwprintf_s(si.artist, 32, _TRUNCATE, L"%s %s", list[4].c_str(), list[5].c_str());
			}
			//
			if (count == 7)
			{
				_snwprintf_s(si.details, 32, _TRUNCATE, L"%s", list[6].c_str());
			}
			else if (count >=8) 
			{
				_snwprintf_s(si.details, 32, _TRUNCATE, L"%s %s", list[6].c_str(), list[7].c_str());
			}
		}
	}
}

void FileDac::CleanString(wstring& input, wchar_t* output)
{
	bool firstTime = true;
	const int len = input.length();
	if (len ==0)
	{
		output[0] = '\0';
		return;
	}
	wchar_t c;
	int i = 0, j = 0;
	//_____________________ If all of them are numbers or _ copy them
	bool areAllNumbers = true;
	for(i= 0; i<len; i++)
	{
		if (input[i] == '.') break; // stop if there is a point
		if (isdigit(input[i])==false && input[i] != '_')
		{
			areAllNumbers = false;
			break;
		}
	}
	if (areAllNumbers)
	{
		for(i = 0, j = 0; i<len && j<31; i++)
		{
			output[j++] = input[i];
		}
		output[j] = '\0';
		return;
	}

	//________________ Copy all, only letters at the beginning
	for(i = 0, j = 0; i<len && j<31; i++)
	{
		c = input[i];
		if (firstTime)
		{
			if (iswalpha(c) == false)
			{
				continue;
			}
			else
			{
				firstTime = false;
			}
		}
		if (c == '.' && i == len-4) break;
		if (c == '(' || c == ')') break;
		output[j++] = c;
	}
	output[j] = '\0';
}

void FileDac::OnDataStarted()
{
	SeparateSongInfo(filename, '\\', si);
	::InvalidateRect(hWnd, NULL, FALSE);
}

void FileDac::OnDataStopped()
{
	SeparateSongInfo(filename, '\\', si);
	::InvalidateRect(hWnd, NULL, FALSE);
}

wchar_t* FileDac::Play(unsigned int bufferSize, bool smoothFileTransition)
{
	if (bufferA) delete [] bufferA;
	if (bufferB) delete [] bufferB;
	bufferA = NULL;
	bufferB = NULL;
	//
	this->smoothFileTransition = smoothFileTransition;
	state = WIN_FILEDAC_CHA;
	//filename[0]='\0';
	//
	if (wcslen(filename)<=0)
	{
		if (GetFilename(filename, 1024)==false) 
		{
			filename[0]='\0';
			ClearSongInfo(si);
			_snwprintf_s(si.songName, 32, _TRUNCATE, L"%s", L"Invalid filename");
			::InvalidateRect(hWnd, NULL, FALSE);
			return L"Invalid filename";
		}
	}

	wchar_t* error = waveFileA.OpenForReading(filename);

	if (error != NULL) 
	{
		filename[0]='\0';
		SeparateSongInfo(error, ' ', si);
		::InvalidateRect(hWnd, NULL, FALSE);
		return error;
	}

	//________________________________________ We get here when everything is OK
	SeparateSongInfo(filename, '\\', si);
	::InvalidateRect(hWnd, NULL, FALSE);
	
	//________________________________________ Reserve memory for smooth transition buffers
	if (smoothFileTransition)
	{
		bufferA = new CHAR[bufferSize];
		if (bufferA == NULL) return L"No enough memory to create buffer A";
		bufferB = new CHAR[bufferSize];
		if (bufferB == NULL) return L"No enough memory to create buffer B";
	}
	//__________________________________________
	unsigned int bitsPerSample = 0;
	DWORD samplesPerSec = 0;
	unsigned short numChannels = 0;
	waveFileA.GetInfo(bitsPerSample, samplesPerSec, numChannels);
	this->bufferSize = bufferSize;
	const int bytesPerSample = b16Bits ? 2*numChannels : numChannels;
	overlapFactor = pow(10.0, WIN_FILEDAC_OVERLAP_GAIN/(20.0*(bufferSize/bytesPerSample)));
	return Start(samplesPerSec, numChannels, bitsPerSample, bufferSize);
}

double FileDac::GetRemainingSeconds(void)
{
	if (this->IsPlaying()==false) return 0.0;
	if (state==WIN_FILEDAC_CHA || state==WIN_FILEDAC_FROM_A_TO_B) return waveFileA.GetRemainingSeconds();
	return waveFileB.GetRemainingSeconds();
}

bool FileDac::GetFilename(wchar_t * filename, int filename_length)
{
	::SendMessage(::GetParent(hWnd), WM_COMMAND, MAKEWPARAM(this->id, WIN_GETFILENAME), (LPARAM)filename);
	filename[1023]='\0';
	if (wcslen(filename)<5) return false;
	return true;
}

void FileDac::OnDataSimple(LPARAM lParam)
{
		const int bitsPerSample = b16Bits ? 16 : 8;
	PWAVEHDR pwd = (PWAVEHDR)lParam;
	LPSTR buffer = pwd->lpData;
	pwd->dwBytesRecorded = 0;
	unsigned int bytesRead = 0;
	wchar_t * error = NULL;
	for(int tries = 0; pwd->dwBytesRecorded < bufferSize && tries < 5; tries++)
	{
		bytesRead = waveFileA.ReadData(buffer+pwd->dwBytesRecorded, bufferSize-pwd->dwBytesRecorded);
		if (bytesRead==0)
		{
			if (GetFilename(filename, 1024) == true)
			{
				SeparateSongInfo(filename, '\\', si);
				error = waveFileA.OpenForReading(this->filename);
				if (error != NULL)
				{
					filename[0]='\0';
					SeparateSongInfo(error, ' ', si);
					::InvalidateRect(hWnd, NULL, FALSE);
					pwd->dwBytesRecorded = 0;
					return;
				}
				SeparateSongInfo(filename, '\\', si);
				::InvalidateRect(hWnd, NULL, FALSE);
			}
			else
			{
				pwd->dwBytesRecorded = 0;
				return;
			}
		}
		else
		{
			pwd->dwBytesRecorded += bytesRead;	
		}
	}
	ModifySamples(buffer, pwd->dwBytesRecorded/(numChannels*bitsPerSample/8), bitsPerSample, numChannels, sampleRate);
}

void FileDac::OnDataSmooth(LPARAM lParam)
{
	//wchar_t text[256];
	const int bitsPerSample = b16Bits ? 16 : 8;
	PWAVEHDR pwd = (PWAVEHDR)lParam;
	LPSTR buffer = pwd->lpData;
	//___________________________________________ File overlapping
	if (sizeof(short int) !=2)
	{
		filename[0]='\0';
		ClearSongInfo(si);
		_snwprintf_s(si.songName, 32, _TRUNCATE, L"%s", L"The size of short int");
		_snwprintf_s(si.album, 32, _TRUNCATE, L"%s", L"is not two.");
		::InvalidateRect(hWnd, NULL, FALSE);
		pwd->dwBytesRecorded = 0;
		return;
	}
	unsigned int remainingBytes = 0;
	unsigned int bytesFilled = 0;
	Sys::Sample16 * x = (Sys::Sample16 *)buffer;
	int numSamples = 0;
	int remainingTime = 0;
	int nextIndex = 0;
	double gainA, gainB;
	int bytesToRead;
	wchar_t *error = NULL;
	const int overlap_size = bufferSize;
	int i;
	if (state==WIN_FILEDAC_CHA || state==WIN_FILEDAC_CHB)//________________________________________
	{
		if (state==WIN_FILEDAC_CHA)
			remainingBytes = waveFileA.GetRemainingByteCount();
		else
			remainingBytes = waveFileB.GetRemainingByteCount();

		if (remainingBytes>=bufferSize + overlap_size)
		{
			//_______________________________________________ normal reading
			if (state==WIN_FILEDAC_CHA)
			{
				remainingTime = (int)(waveFileA.GetRemainingSeconds()+0.5);
				bytesFilled = waveFileA.ReadData(buffer, bufferSize);
			}
			else
			{
				remainingTime = (int)(waveFileB.GetRemainingSeconds()+0.5);
				bytesFilled = waveFileB.ReadData(buffer, bufferSize);
			}
			numSamples = bytesFilled/bytesPerSample;
			ModifySamples(buffer, numSamples, bitsPerSample, numChannels, sampleRate);
			pwd->dwBytesRecorded = bytesFilled;
			return;
		}
		else
		{
			//____________________________________ process buffer in two blocks
			remainingBytes -=overlap_size;
			if (state==WIN_FILEDAC_CHA)
				bytesFilled = waveFileA.ReadData(buffer, remainingBytes);
			else
				bytesFilled = waveFileB.ReadData(buffer, remainingBytes);
			//
			if (this->GetFilename(filename, 1024))
			{
				if (state==WIN_FILEDAC_CHA)
					error = waveFileB.OpenForReading(filename);
				else
					error = waveFileA.OpenForReading(filename);
				if (error != NULL)
				{
					filename[0]='\0';
					SeparateSongInfo(error, ' ', si);
					::InvalidateRect(hWnd, NULL, FALSE);
					pwd->dwBytesRecorded = 0;
					return;
				}
				SeparateSongInfo(filename, '\\', si);
				::InvalidateRect(hWnd, NULL, FALSE);
				bytesToRead = bufferSize-remainingBytes;

				if (bytesToRead!=waveFileA.ReadData(bufferA, bytesToRead))
				{
					filename[0]='\0';
					ClearSongInfo(si);
					_snwprintf_s(si.songName, 32, _TRUNCATE, L"%s", L"Unable to read");
					_snwprintf_s(si.album, 32, _TRUNCATE, L"%s", L"CH A file");
					::InvalidateRect(hWnd, NULL, FALSE);
					pwd->dwBytesRecorded = 0;
					return;
				}
				if (bytesToRead!=waveFileB.ReadData(bufferB, bytesToRead))
				{
					filename[0]='\0';
					ClearSongInfo(si);
					_snwprintf_s(si.songName, 32, _TRUNCATE, L"%s", L"Unable to read");
					_snwprintf_s(si.album, 32, _TRUNCATE, L"%s", L"CH B file");
					::InvalidateRect(hWnd, NULL, FALSE);
					pwd->dwBytesRecorded = 0;
					return;
				}
				// both files are open
				overlapGain = 1.0;
				for(i=0 /*overlapIndex=0*/; i<bytesToRead/bytesPerSample; i++)//, overlapIndex++)
				{
					overlapGain*= overlapFactor;
					if (state==WIN_FILEDAC_CHA)
					{
						//gainB = i*4.0/overlap_size;//WIN_FILEDAC_OVERLAP_GAIN;
						//gainA = 1.0-gainB;
						gainA = overlapGain;
						gainB = 1.0 - gainA;
					}
					else
					{
						//gainA = i*4.0/overlap_size;//WIN_FILEDAC_OVERLAP_GAIN;
						//gainB = 1.0-gainA;
						gainB = overlapGain;
						gainA = 1.0-gainB;
					}
					//_snwprintf_s(text, 256, _TRUNCATE, L"%f, %f\r\n", gainA, gainB);
					//file.WriteText(text);
					nextIndex = i+remainingBytes/bytesPerSample;
					x[nextIndex].channel_1= (short)(gainA*((Sys::Sample16 *)bufferA)[i].channel_1+gainB*((Sys::Sample16*)bufferB)[i].channel_1);
					x[nextIndex].channel_2 = (short)(gainA*((Sys::Sample16 *)bufferA)[i].channel_2+gainB*((Sys::Sample16*)bufferB)[i].channel_2);
				}
				numSamples = bytesFilled/bytesPerSample;
				ModifySamples(buffer, numSamples, bitsPerSample, numChannels, sampleRate);
				if (state==WIN_FILEDAC_CHA)
					state = WIN_FILEDAC_FROM_A_TO_B;
				else
					state = WIN_FILEDAC_FROM_B_TO_A;
			}
		}
	}
	else if (state==WIN_FILEDAC_FROM_A_TO_B || state==WIN_FILEDAC_FROM_B_TO_A) //_________________
	{
		if (state==WIN_FILEDAC_FROM_A_TO_B)
			remainingBytes = waveFileA.GetRemainingByteCount();
		else
			remainingBytes = waveFileB.GetRemainingByteCount();
		if (remainingBytes!=waveFileA.ReadData(bufferA, remainingBytes))
		{
			filename[0]='\0';
			ClearSongInfo(si);
			_snwprintf_s(si.songName, 32, _TRUNCATE, L"%s", L"Unable to read");
			_snwprintf_s(si.album, 32, _TRUNCATE, L"%s", L"CH A file");
			::InvalidateRect(hWnd, NULL, FALSE);
			pwd->dwBytesRecorded = 0;
			return;
		}
		if (remainingBytes!=waveFileB.ReadData(bufferB, remainingBytes))
		{
			filename[0]='\0';
			ClearSongInfo(si);
			_snwprintf_s(si.songName, 32, _TRUNCATE, L"%s", L"Unable to read");
			_snwprintf_s(si.album, 32, _TRUNCATE, L"%s", L"CH B file");
			::InvalidateRect(hWnd, NULL, FALSE);
			pwd->dwBytesRecorded = 0;
			return;
		}

		for(i=0; i<(int)remainingBytes/bytesPerSample; i++)//, overlapIndex++)
		{
			overlapGain*= overlapFactor;
			if (state==WIN_FILEDAC_FROM_A_TO_B)
			{
				//gainB = overlapIndex*4.0/overlap_size;//WIN_FILEDAC_OVERLAP_GAIN;
				//gainA = 1.0-gainB;
				gainA = overlapGain;
				gainB = 1.0 - gainA;
			}
			else
			{
				//gainA = overlapIndex*4.0/overlap_size;//WIN_FILEDAC_OVERLAP_GAIN;
				//gainB = 1.0-gainA;
				gainB = overlapGain;
				gainA = 1.0 - gainB;
			}
/*			_snwprintf_s(text, 256, _TRUNCATE, L"%f, %f\r\n", gainA, gainB);
			file.WriteText(text)*/;
			x[i].channel_1 = (short)(gainA*((Sys::Sample16 *)bufferA)[i].channel_1+gainB*((Sys::Sample16*)bufferB)[i].channel_1);
			x[i].channel_2 = (short)(gainA*((Sys::Sample16 *)bufferA)[i].channel_2+gainB*((Sys::Sample16*)bufferB)[i].channel_2);
		}

		if (state==WIN_FILEDAC_FROM_A_TO_B)
		{
			waveFileA.Close();
			state=WIN_FILEDAC_CHB;
		}
		else
		{
			waveFileB.Close();
			state=WIN_FILEDAC_CHA;
		}

		// Process remaining part of file
		bytesToRead = overlap_size-remainingBytes;
		if (state==WIN_FILEDAC_CHA)
			bytesFilled = waveFileA.ReadData(buffer+remainingBytes, bytesToRead);
		else
			bytesFilled = waveFileB.ReadData(buffer+remainingBytes, bytesToRead);
		numSamples = (remainingBytes+bytesToRead)/(numChannels*bitsPerSample/8);;
		ModifySamples(buffer, numSamples, bitsPerSample, numChannels, sampleRate);
		//return remainingBytes+bytesToRead;
		pwd->dwBytesRecorded = remainingBytes+bytesToRead;
		return;
	}
	else
	{
		filename[0]='\0';
		ClearSongInfo(si);
		_snwprintf_s(si.songName, 32, _TRUNCATE, L"%s", L"Internal error");
		::InvalidateRect(hWnd, NULL, FALSE);
		pwd->dwBytesRecorded = 0;
		return;
	}
	pwd->dwBytesRecorded = bytesFilled;
	ModifySamples(buffer, bytesFilled/(numChannels*bitsPerSample/8), bitsPerSample, numChannels, sampleRate);
}

void FileDac::OnData(LPARAM lParam)
{
	if (smoothFileTransition == true)
	{
		OnDataSmooth(lParam);
	}
	else
	{
		OnDataSimple(lParam);
	}
}

//____________________________________________________________________ FmDemodulator
FmDemodulator::FmDemodulator(void)
{
	dataLeft = NULL;
	dataRight = NULL;
	bufferSize = 0;
	isStereo = true;
}

void FmDemodulator::Delete(void)
{
	if (dataLeft) delete [] dataLeft;
	dataLeft = NULL;
	if (dataRight) delete [] dataRight;
	dataRight = NULL;
	bufferSize = 0;
	data_size = 0;
	isStereo = true;
	is16Bits = false;
}

int* FmDemodulator::GetLeft(void)
{
	return dataLeft;
}

int* FmDemodulator::GetRight(void)
{
	if (isStereo) dataRight;
	return dataLeft;
}

FmDemodulator::~FmDemodulator(void)
{
	if (dataLeft) delete [] dataLeft;
	if (dataRight) delete [] dataRight;
}

bool FmDemodulator::Create(unsigned int bufferSize, bool isStereo, bool is16Bits)
{
	Delete();
	this->bufferSize = bufferSize;
	this->isStereo = isStereo;
	this->is16Bits = is16Bits;
	if (isStereo)
	{
		data_size = bufferSize/4+1;
		dataLeft = new int[data_size];
		if (dataLeft==NULL) return false;
		//
		dataRight = new int[data_size];
		if (dataRight==NULL) return false;
	}
	else
	{
		data_size = bufferSize/2+1;
		dataLeft = new int[data_size];
		if (dataLeft==NULL) return false;
	}
	return true;
}

// demodulated_left and demodulate_right are arrays of the size return by this function
// This function may be called OnWimData
int FmDemodulator::Demodulate(LPSTR buffer, unsigned int bytesRecorded)
{
	int countLeft = 0;
	int countRight = 0;
	int indexLeft = 0;
	int indexRight = 0;

	if (bytesRecorded == 0) return 0;
	int nBytesPerSample;
	int nSampleCount;
	int i;

	if (isStereo==true && is16Bits==true) //16 Bits stereo
	{
		nBytesPerSample = 4;
		nSampleCount = bytesRecorded/nBytesPerSample;
		Sys::Sample16 *samples_16s = (Sys::Sample16*) buffer;
		
		for (i=1; i<nSampleCount; i++)
		{
			if (Adc::isSignDifferent(samples_16s[i].channel_1, samples_16s[i-1].channel_1))
			{
				dataLeft[indexLeft++] = countLeft;
				countLeft = 0;
			}
			else
			{
				countLeft ++;
			}
			if (Adc::isSignDifferent(samples_16s[i].channel_2, samples_16s[i-1].channel_2)) 
			{
				dataRight[indexRight++] = countRight;
				countRight = 0;
			}
			else
			{
				countRight ++;
			}
		}
	}
	else if (isStereo==false && is16Bits==true) //16 Bits mono
	{
		nBytesPerSample = 2;
		nSampleCount = bytesRecorded/nBytesPerSample;
		__int16 *samples_16m = (__int16 *)buffer;

		for (i=1; i<nSampleCount; i++)
		{
			if (Adc::isSignDifferent(samples_16m[i], samples_16m[i-1])) 
			{
				dataLeft[indexLeft++] = countLeft;
				indexRight++;
				countLeft = 0;
			}
			else
			{
				countLeft ++;
			}
		}
		countRight = countLeft;
	}
	else if (isStereo==true && is16Bits==false) //8 Bits stereo
	{	
		nBytesPerSample = 2;
		nSampleCount = bytesRecorded/nBytesPerSample;
		Sys::Sample8 *sample_8s =(Sys::Sample8 *) buffer;

		for (i=1; i<nSampleCount; i++)
		{
			if (Adc::isSignDifferent(sample_8s[i].channel_1-127, sample_8s[i-1].channel_1-127))
			{
				dataLeft[indexLeft++] = countLeft;
				indexRight++;
				countLeft = 0;
			}
			else
			{
				countLeft ++;
			}
			if (Adc::isSignDifferent(sample_8s[i].channel_2-127, sample_8s[i-1].channel_2-127)) 
			{
				dataRight[indexRight++] = countRight;
				countRight = 0;
			}
			else
			{
				countRight ++;
			}
		}
	}
	else if (isStereo==false && is16Bits==false) //8 Bits mono
	{
		__int8 *sample_8m = (__int8*)buffer;
		for (i=1; i<(int)bytesRecorded; i++)
		{
			if (Adc::isSignDifferent(sample_8m[i]-127, sample_8m[i-1]-127)) 
			{
				dataLeft[indexLeft++] = countLeft;
				dataRight[indexLeft++] = countLeft;
				countLeft = 0;
			}
			else
			{
				countLeft ++;
			}
		}
		countRight = countLeft;
	}
	return MINIMUM(indexLeft, indexRight);
}

// demodulated_left and demodulate_right are arrays of the size return by this function
// This function may be called OnWimData
int FmDemodulator::Demodulate(LPARAM lParam)
{
	PWAVEHDR pwd = (PWAVEHDR)lParam;
	return Demodulate(pwd->lpData, pwd->dwBytesRecorded);
}

}
#endif
//____________________________________________________ namespace Mm::End

namespace Game //________________________________________ namespace Game::Ini
{

//_____________________________________________________________________ Object2D
Object2D::Object2D()
{
	_x = 0.0f;
	_y = 0.0f;
	_type = -1;
	_visible = true;
	_rotationAngle = 0.0f;
	_minX = 0.0f;
	_maxX = 1000.0f;
	_minY = 0.0f;
	_maxY = 1000.0f;
	_speed = 0.0f; // This variable is here just to be able to call ComputeState
	//
	shape.resize(5);
	shape[0].x = -50.0f;
	shape[0].y = -100.0f;
	//
	shape[1].x = 50.0f;
	shape[1].y = -100.0f;
	//
	shape[2].x = 50.0f;
	shape[2].y = 100.0f;
	//
	shape[3].x = -50.0f;
	shape[3].y = 100.0f;
	//
	shape[4].x = -50.0f;
	shape[4].y = -100.0f;
	UpdateBounds(0.0f);
}

Object2D::~Object2D()
{
}

bool Object2D::IsCollision(Game::Object2D& object)
{
	return Sys::Bound2D::DoIntersect(_bounds, object._bounds);
}

vector<Sys::Bound2D>& Object2D::GetBounds()
{
	return _bounds;
}

#ifdef WIN_DIRECTX
void Object2D::Render(IDirect3DDevice9Ptr d3dDevice, float deltaTimeSec)
{
	if (deltaTimeSec != 0.0f) ComputeState(deltaTimeSec, _x, _y, _rotationAngle, _speed);
	if (_visible == false) return;
	//_____________________________________________________ Set World Transform


	InternalRender(d3dDevice, deltaTimeSec);
}
#else
void Object2D::Render(Win::Gdi& gdi, float deltaTimeSec)
{
	if (deltaTimeSec != 0.0f) ComputeState(deltaTimeSec, _x, _y, _rotationAngle, _speed);
	if (_visible == false) return;
	//_____________________________________________________ Set World Transform
	const int state = gdi.SaveDC();
	XFORM tf;
	const float sinx = sin(_rotationAngle);
	const float cosx = cos(_rotationAngle);
	tf.eM11 = cosx;
	tf.eM12 = sinx;
	tf.eM21 = -sinx;
	tf.eM22 = cosx;
	tf.eDx = _x;
	tf.eDy = _y;
	::SetWorldTransform(gdi.GetHDC(), &tf);  //x' = x * eM11 + y * eM21 + eDx, y' = x * eM12 + y * eM22 + eDy,
	InternalRender(gdi, deltaTimeSec);
	gdi.RestoreDC(state);
}
#endif

#ifdef WIN_DIRECTX
void Object2D::InternalRender(IDirect3DDevice9Ptr d3dDevice, float deltaTimeSec)
{
}
#else
void Object2D::InternalRender(Win::Gdi& gdi, float deltaTimeSec)
{
	RECT rect;
	rect.left = (int)(shape[0].x + 0.5);
	rect.right = (int)(shape[1].x+0.5);
	rect.top = (int)(shape[0].y +0.5);
	rect.bottom = (int)(shape[2].y +0.5);
	gdi.Rectangle(rect);
}
#endif

void Object2D::ComputeState(float deltaTimeSec, float& out_nextPositionX, float& out_nextPositionY, float& out_nextAngle, float& out_nextSpeed)
{
	// Do nothing
}

void Object2D::SetPositionX(float x)
{
	_x = x;
}

float Object2D::GetPositionX()
{
	return _x;
}

void Object2D::SetPositionY(float y)
{
	_y = y;
}

float Object2D::GetPositionY()
{
	return _y;
}

void Object2D::SetMinX(float minX)
{
	_minX = minX;
	if (_x < _minX) _x = _minX;
}

float Object2D::GetMinX()
{
	return _minX;
}

void Object2D::SetMaxX(float maxX)
{
	_maxX = maxX;
	if (_x > _maxX) _x = _maxX;
}

float Object2D::GetMaxX()
{
	return _maxX;
}

void Object2D::SetMinY(float minY)
{
	_minY = minY;
	if (_y < _minY) _y = _minY;
}

float Object2D::GetMinY()
{
	return _minY;
}

void Object2D::SetMaxY(float maxY)
{
	_maxY = maxY;
	if (_y > _maxX) _x = _maxX;
}

float Object2D::GetMaxY()
{
	return _maxY;
}

void Object2D::SetRotationAngle(float radians)
{
	const float twopi = (float)(2.0*M_PI);
	//________________________________________ Limit from: -2pi to 2pi
	if (radians > twopi)
	{
		while (radians > twopi)
		{
			radians -= twopi;
		}
	}
	else if (radians < -twopi)
	{
		while (radians < - twopi)
		{
			radians += twopi;
		}
	}
	_rotationAngle = radians;
}

float Object2D::GetRotationAngle()
{
	return _rotationAngle;
}

void Object2D::SetType(int type)
{
	_type = type;
}

int Object2D::GetType()
{
	return _type;
}

void Object2D::UpdateBounds(float positionX, float positionY, float rotationAngle)
{
	const int count = shape.size();
	if (count == 0)
	{
		_bounds.clear();
		return;
	}
	_bounds.resize(count);
	const float sinx = sin(rotationAngle);
	const float cosx = cos(rotationAngle);
	
	vector<Sys::Bound2D>::iterator b;
	vector<Sys::Point2D>::iterator s;
	const vector<Sys::Point2D>::iterator shapeEnd = shape.end();
	float x = 0.0f, y = 0.0f;
	//_________________________________________________ Traslate and rotate points + Compute Deltas
	for(b = _bounds.begin(), s = shape.begin(); s != shapeEnd; b++, s++)
	{
		(b->x) = positionX + (s->x) * cosx - (s->y) * sinx;
		(b->y) = positionY + (s->x) * sinx + (s->y) * cosx;
		b->dx = (b->x) - x;
		b->dy = (b->y) - y;
		x = b->x;
		y = b->y;
	}
}

void Object2D::UpdateBounds(float deltaTimeSec)
{
	UpdateBounds(_x, _y, _rotationAngle);
}

void Object2D::SetVisible(bool visible)
{
	_visible = visible;
}

bool Object2D::IsVisible()
{
	return _visible;
}

//_____________________________________________________________________ Mobile2D
Mobile2D::Mobile2D()
{
	_maxSpeed = 10000.0f;
	_acceleration = 0.0f;
	_maxAcceleration = 100.0f;
	_rotationSpeed = 0.0f;
	_maxRotationSpeed = 100.0f;
}

Mobile2D::~Mobile2D()
{
}

void Mobile2D::SetSpeed(float speed)
{
	if (speed > 0)
	{
		if (speed > _maxSpeed)
		{
			speed = _maxSpeed;
		}
	}
	else if (speed < 0)
	{
		if (speed < -_maxSpeed)
		{
			speed = -_maxSpeed;
		}
	}
	_speed = speed;
}

float Mobile2D::GetSpeed()
{
	return _speed;
}

void Mobile2D::SetMaxSpeed(float maxSpeed)
{
	_maxSpeed = fabs(maxSpeed);
	//____________________ Correct current speed if bigger
	if (_speed > 0)
	{
		if (_speed > _maxSpeed)
		{
			_speed = _maxSpeed;
		}
	}
	else if (_speed < 0)
	{
		if (_speed < -_maxSpeed)
		{
			_speed = -_maxSpeed;
		}
	}
}

float Mobile2D::GetMaxSpeed()
{
	return _maxSpeed;
}

void Mobile2D::SetAcceleration(float acceleration)
{
	if (acceleration > 0.0f)
	{
		if (acceleration > _maxAcceleration)
		{
			acceleration = _maxAcceleration;
		}
	}
	else if (acceleration < 0.0f)
	{
		if (acceleration < -_maxAcceleration)
		{
			acceleration = -_maxAcceleration;
		}
	}
	_acceleration = acceleration;
}

float Mobile2D::GetAcceleration()
{
	return _acceleration;
}

void Mobile2D::SetMaxAcceleration(float maxAcceleration)
{
	_maxAcceleration = fabs(maxAcceleration);
	//____________________ Correct current acceleration if bigger
	if (_acceleration > 0.0f)
	{
		if (_acceleration > _maxAcceleration)
		{
			_acceleration = _maxAcceleration;
		}
	}
	else if (_acceleration < 0.0f)
	{
		if (_acceleration < -_maxAcceleration)
		{
			_acceleration = -_maxAcceleration;
		}
	}
}

float Mobile2D::GetMaxAcceleration()
{
	return _maxAcceleration;
}

void Mobile2D::SetRotationSpeed(float rotationSpeed)
{
	if (rotationSpeed > 0.0f)
	{
		if (rotationSpeed > _maxRotationSpeed)
		{
			rotationSpeed = _maxRotationSpeed;
		}
	}
	else if (rotationSpeed < 0.0f)
	{
		if (rotationSpeed < -_maxRotationSpeed)
		{
			rotationSpeed = -_maxRotationSpeed;
		}
	}
	_rotationSpeed = rotationSpeed;
}

float Mobile2D::GetRotationSpeed()
{
	return _rotationSpeed;
}

void Mobile2D::SetMaxRotationSpeed(float maxRotationSpeed)
{
	_maxRotationSpeed = fabs(maxRotationSpeed);
	//____________________ Correct current speed if bigger
	if (_rotationSpeed > 0.0f)
	{
		if (_rotationSpeed > _maxRotationSpeed)
		{
			_rotationSpeed = _maxRotationSpeed;
		}
	}
	else if (_rotationSpeed < 0.0f)
	{
		if (_rotationSpeed < -_maxRotationSpeed)
		{
			_rotationSpeed = -_maxRotationSpeed;
		}
	}
}

float Mobile2D::GetMaxRotationSpeed()
{
	return _maxRotationSpeed;
}

void Mobile2D::UpdateBounds(float deltaTimeSec)
{
	float next_x = 0.0f;
	float next_y = 0.0f;
	float next_angle = 0.0f;
	float next_speed = 0.0f;
	ComputeState(deltaTimeSec, next_x, next_y, next_angle, next_speed);
	Game::Object2D::UpdateBounds(next_x, next_y, next_angle);
}

void Mobile2D::ComputeState(float deltaTimeSec, float& out_nextPositionX, float& out_nextPositionY, float& out_nextAngle, float& out_nextSpeed)
{
	const float twopi = (float)(2.0*M_PI);
	if (deltaTimeSec == 0.0f)
	{
		out_nextAngle = _rotationAngle;
		out_nextPositionX = _x;
		out_nextPositionY = _y;
		out_nextSpeed = _speed;
		return;
	}
	out_nextAngle = _rotationSpeed * deltaTimeSec + _rotationAngle;
	//________________________________________ Limit out_nextAngle
	if (out_nextAngle > twopi)
	{
		while (out_nextAngle > twopi)
		{
			out_nextAngle -= twopi;
		}
	}
	else if (out_nextAngle < -twopi)
	{
		while (out_nextAngle < - twopi)
		{
			out_nextAngle += twopi;
		}
	}
	//______________________________________ No movement
	if (_acceleration == 0.0f && _speed == 0.0f)
	{
		out_nextPositionX = _x;
		out_nextPositionY = _y;
		out_nextSpeed = _speed;
	}
	else if (_acceleration == 0.0f) //_______________ Constant speed
	{
		const float vx = _speed * cos(out_nextAngle);
		const float vy = _speed * sin(out_nextAngle);
		out_nextPositionX = _x + vx*deltaTimeSec;
		out_nextPositionY = _y + vy*deltaTimeSec;
		out_nextSpeed = _speed;
		//
		if (out_nextPositionX > _maxX) out_nextPositionX = _maxX;
		if (out_nextPositionX < _minX) out_nextPositionX = _minX;
		if (out_nextPositionY > _maxY) out_nextPositionY = _maxY;
		if (out_nextPositionY < _minY) out_nextPositionY = _minY;
	}
	else //____________________________________ Variable speed
	{
		out_nextSpeed = _speed + _acceleration*deltaTimeSec;
		if (out_nextSpeed > 0.0f)
		{
			if (out_nextSpeed > _maxSpeed) out_nextSpeed = _maxSpeed;
		}
		else if (out_nextSpeed < 0.0f)
		{
			if (out_nextSpeed < -_maxSpeed) out_nextSpeed = -_maxSpeed;
		}
		const float vx = _speed * cos(out_nextAngle);
		const float vy = _speed * sin(out_nextAngle);
		const float ax = _acceleration * cos(out_nextAngle);
		const float ay = _acceleration * sin(out_nextAngle);
		const float t2 = deltaTimeSec*deltaTimeSec;
		out_nextPositionX = _x + vx*deltaTimeSec+0.5f*ax*t2;
		out_nextPositionY = _y + vy*deltaTimeSec+0.5f*ay*t2;
		//
		if (out_nextPositionX > _maxX) out_nextPositionX = _maxX;
		if (out_nextPositionX < _minX) out_nextPositionX = _minX;
		if (out_nextPositionY > _maxY) out_nextPositionY = _maxY;
		if (out_nextPositionY < _minY) out_nextPositionY = _minY;
	}
}

//_____________________________________________________________________ Game::Window
Window::Window(void)
{
	isGameMode = true;
#ifdef WIN_DAC_ADC_SUPPORT
	currentTime = timeGetTime();
	currentTimeSec = currentTime/1000.0f;
#else
	currentTime = 0;
	currentTimeSec = 0.0f;
#endif
	deltaTimeSec = 0.0f;

	for(int i=0; i<256; i++) keyboard[i] = false;
	isActive = false;
}

Window::~Window(void)
{
}

void Window::GetRegisterClass(WNDCLASSEX& wcex)
{
	wcex.style = CS_CLASSDC;
	wcex.hbrBackground = NULL;
}

void Window::Window_Size(Win::Event& e)
{
	if (width==0) width = 1;
	if (height==0) height = 1;
	bitmap.CreateCompatible(hWnd, width, height);
}

void Window::Window_Destroy(Win::Event& e)
{
	::PostQuitMessage(0);
}

void Window::Window_Activate(Win::Event& e)
{
	if (HIWORD(e.wParam)==0)	//______________deactivated 
	{ 
		isActive=true;	
		e.returnValue = 0;
	}
	else//_______________________________activated
	{
		isActive=false;
		e.returnValue = 0;
	}
}

void Window::Window_KeyDown(Win::Event& e)
{
	if (e.wParam>255) return;
	keyboard[e.wParam] =true;
}

void Window::Window_KeyUp(Win::Event& e)
{
	if (e.wParam>255) return;
	keyboard[e.wParam] =false;
}

void Window::Window_SysCommand(Win::Event& e)
{
	switch (e.wParam)
	{
	case SC_SCREENSAVE://Stop the screen saver
		e.returnValue = FALSE;
		return;
	case SC_MONITORPOWER://Stop the monitor power		
		e.returnValue = FALSE;
		return;
	}
	e.returnValue =  ::DefWindowProc(e.hWnd, WM_SYSCOMMAND, e.wParam, e.lParam);
}

int Window::MessageLoop(WORD aceleratorsID)
{
	this->_isMainWindow = true;
	this->SetForeground();
	this->SetFocus();

	MSG msg;		
	::ZeroMemory(&msg, sizeof(MSG));

	while(msg.message != WM_QUIT)
	{
		if (isGameMode == true)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	//Check for a pending message in the application queue
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				//if (isActive == false) continue;
				//if (keyboard[VK_ESCAPE]==true) break; 
				RECT rcPaint = {0, 0, width, height};
				Win::Gdi gdi(bitmap, rcPaint, false);
				gdi.SetAdvancedMode(true);
				//_______________________________________________ Update the time
#ifdef WIN_DAC_ADC_SUPPORT
				deltaTimeSec = currentTimeSec;
				currentTime = timeGetTime();
				currentTimeSec = currentTime/1000.0f;
				deltaTimeSec = currentTimeSec - deltaTimeSec;
#endif
				if (RenderScene(gdi)==false) break;
				//_______________________________________________ Slow down the frames per second
#ifdef WIN_DAC_ADC_SUPPORT
				while (timeGetTime()-currentTime<8) Sleep(1);//while (FPS>62.5)
#endif
				//_____________________________________________ Present
				HDC screen = ::GetDC(hWnd);
				::BitBlt(screen, 0, 0, width, height, bitmap.GetBitmapDC(), 
					0, 0, SRCCOPY);
				::ReleaseDC(hWnd, screen);
			}
		}
		else //__________________________________________________ Normal Window
		{
			if (GetMessage(&msg, NULL, 0, 0)) 
			{			
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	return (int) msg.wParam;
}

void Window::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(hWnd, true, false);
	gdi.DrawDoubleBuffer(bitmap);
}

//_____________________________________________________________________ DxWindow
DxWindow::DxWindow(void)
{
	isGameMode = true;
#ifdef WIN_DIRECTX
	d3d = NULL;
	d3dDevice = NULL;
#endif
}

DxWindow::~DxWindow(void)
{
}

int DxWindow::MessageLoop(WORD aceleratorsID)
{
	this->_isMainWindow = true;
	this->SetForeground();
	this->SetFocus();

	MSG msg;		
	::ZeroMemory(&msg, sizeof(MSG));

	while(msg.message != WM_QUIT)
	{
		if (isGameMode == true)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	//Check for a pending message in the application queue
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
#ifdef WIN_DIRECTX
				if(d3dDevice == NULL) continue;
#endif
				//_______________________________________________ Update the time
#ifdef WIN_DAC_ADC_SUPPORT
				deltaTimeSec = currentTimeSec;
				currentTime = timeGetTime();
				currentTimeSec = currentTime/1000.0f;
				deltaTimeSec = currentTimeSec - deltaTimeSec;
#endif
				if (RenderScene() == false) break;
				//_______________________________________________ Slow down the frames per second
#ifdef WIN_DAC_ADC_SUPPORT
				while (timeGetTime()-currentTime<8) Sleep(1);//while (FPS>62.5)
#endif
			//_____________________________________________ Present
#ifdef WIN_DIRECTX
				d3dDevice->Present(NULL, NULL, NULL, NULL);
#endif
			}
		}
		else //__________________________________________________ Normal Window
		{
			if (GetMessage(&msg, NULL, 0, 0)) 
			{			
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	return (int) msg.wParam;
}

void DxWindow::GetRegisterClass(WNDCLASSEX& wcex)
{
	wcex.style = CS_CLASSDC;
	wcex.hbrBackground = NULL;
}

void DxWindow::Window_Destroy(Win::Event& e)
{
#ifdef WIN_DIRECTX
	d3dDevice = NULL;
	d3d = NULL;
#endif
	::PostQuitMessage(0);
}


} //____________________________________________________ namespace Game::End

//____________________________________________________ namespace Ogl::Ini
#ifdef WIN_OPENGL_SUPPORT
namespace Ogl{

//_____________________________________________________________________ ViewManager
ViewManager::ViewManager(void)
{
	angleXZ = 0.0;
	deltaAngleXZ = 0.0;
	x = 10.0;
	y = 0.0;
	z = 24.0;
	deltaX = 0.0;
	deltaY = 0.0;
	deltaZ = 0.0;
}

ViewManager::~ViewManager(void)
{
	
}

void ViewManager::AdjustView(void)
{
	deltaX *= 0.8;
	deltaY *= 0.8;
	deltaZ *= 0.8;
	deltaAngleXZ *= 0.9;
	//
	x += deltaX/10.0;
	y += deltaY/10.0;
	z += deltaZ/10.0;
	angleXZ += deltaAngleXZ/10.0;
	if (angleXZ>100*M_PI || angleXZ<-100*M_PI) angleXZ = 0.0;
	//
	glLoadIdentity();
	//glRotated(view.mouse3dY, 1.0f, 0, 0);
	glRotated(2*M_PI-angleXZ, 0, 1.0f, 0);
	glTranslated(-x, -y, -z);
}

void ViewManager::incrementX(void)
{
	deltaX += 5.0 * sin(angleXZ);	
	deltaZ += 5.0 * cos(angleXZ);
}

void ViewManager::decrementX(void)
{
	deltaX -= 5.0 * sin(angleXZ);	
	deltaZ -= 5.0 * cos(angleXZ);
}

void ViewManager::incrementY(void)
{
	deltaY -= 1.0;
}

void ViewManager::decrementY(void)
{
	deltaY += 1.0;
}

void ViewManager::incrementZ(void)
{
	deltaX += 5.0 * sin(angleXZ+M_PI_2);	
	deltaZ += 5.0 * cos(angleXZ+M_PI_2);
}

void ViewManager::decrementZ(void)
{
	deltaX += 5.0 * sin(angleXZ-M_PI_2);	
	deltaZ += 5.0 * cos(angleXZ-M_PI_2);
}

void ViewManager::incrementAngleXZ(void)
{
	deltaAngleXZ -= 0.1;
}

void ViewManager::decrementAngleXZ(void)
{
	deltaAngleXZ += 0.1;
}

//_____________________________________________________________________ Object
Object::Object(void)
{
	id = -1;
}

Object::~Object(void)
{
	id = -1;
}

GLuint Object::GetID()
{
	return id;
}

//_____________________________________________________________________ List
Lists::Lists(void)
{
	size = 0;
}

Lists::~Lists(void)
{
	Delete();
}

void Lists::Delete(void)
{
	if (id!=-1) glDeleteLists(id, size);
	id=-1;
	size=0;
}

GLuint Lists::Generate(GLsizei size)
{
	Delete();
	id = glGenLists(size);
	return id;
}

//_____________________________________________________________________ Texture
Texture::Texture(void)
{
	width = 0;
	height = 0;
}

void Texture::Delete(void)
{
	id = -1;
	width = 0;
	height = 0;
}

Texture::~Texture(void)
{
	Delete();
}

GLuint Texture::GetWidth()
{
	return width;
}

GLuint Texture::GetHeight()
{
	return height;
}

wchar_t* Texture::CreateFromBitmap(const wchar_t* filename, GLfloat minFilter, GLfloat magFilter, GLint components)
{
	this->Delete();
	//AUX_RGBImageRec* image = auxDIBImageLoad(filename);
	Win::DIBitmap bitmap;
	if (bitmap.CreateFromFile(filename)==FALSE) return L"Unable to read the file";
	this->width = bitmap.GetSize().cx;
	this->height = bitmap.GetSize().cy;
	//this->width = image->sizeX;
	//this->width = image->sizeY;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);//Linear filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);//Linear filtered
	gluBuild2DMipmaps(GL_TEXTURE_2D, components, width, height, 
		GL_RGB, GL_UNSIGNED_BYTE, bitmap.GetBits());
	//gluBuild2DMipmaps(GL_TEXTURE_2D, components, width, height, 
	//	GL_RGB, GL_UNSIGNED_BYTE, image->data);
	return NULL;
}

wchar_t* Texture::CreateFromBitmap(const wchar_t* filename)
{
	return CreateFromBitmap(filename, GL_LINEAR, GL_LINEAR, GL_RGB);
}

//wchar_t* Texture::CreateFromTGA(const wchar_t* filename)
//{
//	this->Delete();
//	Win::DataFile file;
//	if (file.CreateForReading(filename)==false) return L"Unable to open file";
//
//	TgaHeader header;
//	if (file.Read(&header, sizeof(TgaHeader))!=sizeof(TgaHeader)) return L"Unable to read file header";
//
//	//____________________________________________________ Check if for an uncompressed header
//	if (header.identsize != 0) return L"Invalid indent size in file header";
//	if (header.colourmaptype != 0) return L"Unsupported colour map type";// type of colour map 0=none, 1=has palette
//	if (header.imagetype != 2) return L"Unsupported image type";// type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed
//	if (header.colourmapstart != 0) return L"Unsupported colour map start";// first colour map entry in palette
//	if (header.colourmaplength != 0) return L"Invalid colour map length";    // number of colours in palette
//	if (header.colourmapbits != 0) return L"Invalid colour map bits";// number of bits per palette entry 15,16,24,32
//	if (header.xstart != 0) return L"Invalid image x origin"; // image x origin
//	if (header.ystart != 0) return L"Invalid image y origin";// image y origin
//	if (header.width <=0) return L"Image width is invalid";
//	if (header.height <=0) return L"Image height is invalid";
//	if (header.bitsPerPixel != 24 || header.bitsPerPixel != 32) return L"Invalid bit per pixel";
//
//	this->width = header.width;
//	this->height = header.height;
//	this->bitsPerPixel = header.bitsPerPixel;
//
//	const int bytesData = bitsPerPixel*width*height/8;
//	data = new BYTE[bytesData];
//	if (data==NULL) return L"No enough memory to read file";
//	if (file.Read(data, bytesData) != bytesData) return L"Unable to read file data";
//
//	return NULL;
//}

//_____________________________________________________________________ Font
Font::Font(void) : ROWS(16), COLS(16)
{
}

Font::~Font(void)
{
}

//The bitmap must have 16 rows and 16 cols
wchar_t* Font::CreateFromBitmap(const wchar_t* filename)
{
	texture.Delete();
	Lists::Delete();
	//
	wchar_t *error = texture.CreateFromBitmap(filename);
	if (error) return error;
	const int fontHeight = texture.GetHeight()/ROWS;
	const int fontWidth = texture.GetWidth()/COLS;
	const double offsetX = 1.0/COLS;
	const double offsetY = 1.0/ROWS;
	double x, y;
	Generate(ROWS*COLS);
	glBindTexture(GL_TEXTURE_2D, texture.GetID());

	unsigned int i, j;

	for(i=0; i<ROWS; i++)
	{
		y = 1.0-i*fontHeight/(double)texture.GetHeight();
		for(j=0; j<COLS; j++)
		{
			x = j*fontWidth/(double)texture.GetWidth();
			glNewList(id+i*COLS+j, GL_COMPILE);
				glBegin(GL_QUADS);
					//__________________________ bottom left
					glTexCoord2f((GLfloat)x, (GLfloat)(y-offsetY));
					glVertex2d(0, fontHeight);
					//__________________________ bottom right
					glTexCoord2f((GLfloat)(x+offsetX), (GLfloat)(y-offsetY));
					glVertex2d(fontWidth, fontHeight);
					//__________________________ top right
					glTexCoord2f((GLfloat)(x+offsetX), (GLfloat)(y-0.001));
					glVertex2d(fontWidth, 0);
					//__________________________ top left
					glTexCoord2f((GLfloat)x, (GLfloat)(y-0.001));
					glVertex2d(0, 0);
					//
				glEnd();
				glTranslated(fontWidth-2, 0, 0); //Move to the right of the character
			glEndList();
		}
	}

	return NULL;
}

//_____________________________________________________________________ GLWindow
GLWindow::GLWindow(void)
{
	hDC = NULL;
	hGLRC = NULL;
	isFullScreen = false;
	bitsPerPixel = 32;
	for(int i=0; i<256; i++) keyboard[i] = false;
	isActive = false;
	//
	displayedFramesPerSecond = true;
	frames = 0;
	//QueryPerformanceCounter(&currentTime);
	//QueryPerformanceFrequency(&frequency);
	//QueryPerformanceCounter(&startTime);
	//QueryPerformanceCounter(&lastTime);
}

GLWindow::~GLWindow(void)
{
}

void GLWindow::Window_Size(Win::Event& e)
{
	if (width==0) width = 1;
	if (height==0) height = 1;
	glViewport(0, 0, width, height);

	//______________________________ Reset The Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();									

	//_____________________ Calculate The Aspect Ratio Of The Window	
	gluPerspective(60.0f, (GLdouble)width/(GLdouble)height, 1.0f, 1250.0f);

	//_______________________________Reset The Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
}

void GLWindow::Window_Destroy(Win::Event& e)
{
	this->DestroyGL();
	::PostQuitMessage(0);
}

void GLWindow::Window_Activate(Win::Event& e)
{
	if (HIWORD(e.wParam)==0)	//______________deactivated 
	{ 
		isActive=true;	
		e.returnValue = 0;
	}
	else//_______________________________activated
	{
		isActive=false;
		e.returnValue = 0;
	}
}

void GLWindow::Window_KeyDown(Win::Event& e)
{
	if (e.wParam>255) return;
	keyboard[e.wParam] =true;
}

void GLWindow::Window_KeyUp(Win::Event& e)
{
	if (e.wParam>255) return;
	keyboard[e.wParam] =false;
}

void GLWindow::Window_SysCommand(Win::Event& e)
{
	switch (e.wParam)
	{
	case SC_SCREENSAVE://Stop the screen saver
		e.returnValue = FALSE;
		return;
	case SC_MONITORPOWER://Stop the monitor power		
		e.returnValue = FALSE;
		return;
	}
	e.returnValue =  ::DefWindowProc(e.hWnd, WM_SYSCOMMAND, e.wParam, e.lParam);
}

void GLWindow::DestroyGL()
{
	if (hGLRC)
	{
		if (wglMakeCurrent(NULL, NULL) == FALSE)
		{
			this->MessageBox(L"Failed to release DC and RC.", L"Ogl::OpenGL::Destroy", MB_OK | MB_ICONERROR);
		}

		if (wglDeleteContext(hGLRC) == FALSE)
		{
			this->MessageBox(L"Failed to release the rendering context.", L"Ogl::OpenGL::Destroy", MB_OK | MB_ICONERROR);
		}
		hGLRC=NULL;	
	}

	if (hDC)
	{
		if (::ReleaseDC(hWnd, hDC)==FALSE)	
			this->MessageBox(L"Failed to release the device context.", L"Ogl::OpenGL::Destroy", MB_OK | MB_ICONERROR);
		hDC=NULL;	
	}

	if (isFullScreen)	
	{
		ChangeDisplaySettings(NULL, 0);	//Restore normal display mode
		ShowCursor(TRUE);
	}
}

bool GLWindow::ActivateFullScreen()
{
	if (width<=0) width = ::GetSystemMetrics(SM_CXSCREEN);
	if (height<=0) height = ::GetSystemMetrics(SM_CYSCREEN);
	isFullScreen = true;
	DEVMODE dmScreenSettings;
	memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
	dmScreenSettings.dmSize=sizeof(dmScreenSettings);
	dmScreenSettings.dmPelsWidth	= width;
	dmScreenSettings.dmPelsHeight	= height;
	dmScreenSettings.dmBitsPerPel	= bitsPerPixel;
	dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

	if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		if (::MessageBox(NULL, L"The fullscreen mode is not supported by your video card. \r\nWould you like to use windowed mode instead?",
			L"Win::OpenGL", MB_YESNO | MB_ICONQUESTION)==IDYES)
		{
			isFullScreen = false;
			return false;
		}
	}
	return true;
}

void GLWindow::DrawCube(void)
{
	//glPushMatrix();
	glBegin(GL_POLYGON);
		//_________________________ top face
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, 0.0f, 0.0f);
		//_________________________ front face
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(0.0f, -1.0f, 0.0f);
		//_________________________ right face
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -1.0f, 0.0f);
		glVertex3f(0.0f, -1.0f, -1.0f);
		glVertex3f(0.0f, 0.0f, -1.0f);
		//_________________________ left face
		glVertex3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		//_________________________ bottom face
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		//_________________________ back face
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(0.0f, -1.0f, -1.0f);
	glEnd();
	//glPopMatrix();
}

void GLWindow::DrawFramesPerSecond(GLdouble x, GLdouble y, Ogl::Font& font)
{
	static double fps = 0.0;
	glDisable(GL_DEPTH_TEST);
	frames++;
	if (frames%10 == 0)
	{
		static DWORD currentTime = timeGetTime();
		DWORD now = timeGetTime();
		const double delta= (now- currentTime)/(1000.0);
		currentTime = timeGetTime();
		fps = 1.0/delta;
	}
	wchar_t text[256];
	_snwprintf_s(text, 256, _TRUNCATE, L"FPS: %4.0f", fps);
	this->Print(x, y, font, text);
	//
	displayedFramesPerSecond = true; //Flag to slow down the FPS 
	glEnable(GL_DEPTH_TEST);
}

void GLWindow::Print(Ogl::Font& font, const wchar_t * text)
{
	glRotatef(180, 0, 0, 1);
	glRotatef(180, 0, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glListBase(font.GetID()- '!'+1);
	const int length = lstrlen(text);
	char *data = new char[length];
	::WideCharToMultiByte(CP_ACP, 0, text, -1, data, length, NULL, NULL );
	glCallLists(length, GL_UNSIGNED_BYTE, data);
	if (data) delete [] data;
	glDisable(GL_TEXTURE_2D);
}

void GLWindow::Print(GLdouble x, GLdouble y, Ogl::Font& font, const wchar_t * text)
{
	//glLoadIdentity();
	glPushMatrix();
		glTranslated(x, y, -500);
		Print(font, text);
	glPopMatrix();
}

int GLWindow::MessageLoop(WORD aceleratorsID)
{
	this->_isMainWindow = true;
	this->SetForeground();
	this->SetFocus();

	MSG	 msg;
	memset(&msg, 0, sizeof(MSG));

	while(msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	//Check for a pending message in the application queue
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//if (isActive == false) continue;
			//if (keyboard[VK_ESCAPE]==true) break; 
			this->displayedFramesPerSecond = false;
			if (this->RenderScene()==false) break;
			//_______________________________________________ Slow down the frames per second
			if (displayedFramesPerSecond==false)
			{
				static DWORD currentTime = timeGetTime();
				while (timeGetTime()-currentTime<8) Sleep(1);//while (FPS>62.5)
				currentTime = timeGetTime();
			}
			if (frames>300000000) frames = 0;
			::SwapBuffers(hDC);
		}
	}
	return (int) msg.wParam;
}

void GLWindow::SetGLSize()
{
	if (this->width==0 || this->height==0)
	{
		RECT rect;
		::GetWindowRect(hWnd, &rect);
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}
}

wchar_t* GLWindow::SetupGL(PIXELFORMATDESCRIPTOR& pfd)
{
	this->hDC = ::GetDC(hWnd);
	if (hDC==NULL)	return L"Failed to get a permanent device context";
	int pixelFormatIndex = ::ChoosePixelFormat(hDC, &pfd);
	if (pixelFormatIndex==0) return L"Failed to get an appropriate pixel format"	;
	if (::SetPixelFormat(hDC, pixelFormatIndex, &pfd)==FALSE) return L"Failed to set the pixel format";
	this->hGLRC = ::wglCreateContext(hDC);
	if (hGLRC==NULL) return L"Failed to get a rendering context";
	if (::wglMakeCurrent(hDC, hGLRC)== FALSE) return L"Failed to make the current rendering context";
	return NULL; //We get here when there are not errors
}

}
#endif
//____________________________________________________ namespace Ogl::End

//____________________________________________________ namespace Com::Ini
namespace Com
{

//___________________________________________________________________ Container
bool Container::m_bRegistered= false;

Container::Container(void)
{
	if (!m_bRegistered)
	{
		this->RegisterGlobalClassEx(LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(NULL_BRUSH));
		m_bRegistered = true;
	}
	::CoInitialize(NULL);
	this->refCount = 0;
	//
	this->visible = true;
	this->allowResize = false;
	this->miscStatus = 0;
	this->inplaceActive = false;
	this->isInPlace = false;
	this->rectPosition.left = 0;
	this->rectPosition.top = 0;
	this->rectPosition.right = 0;
	this->rectPosition.bottom = 0;
	//
	this->_backColor = (OLE_COLOR)::GetSysColor(COLOR_WINDOW);
	this->_textColor = (OLE_COLOR)::GetSysColor(COLOR_WINDOWTEXT );
	this->_userMode = true;
	this->_localeId = LOCALE_USER_DEFAULT;
	//
	activex.oleObject = NULL;
	activex.viewObject = NULL;
	activex.viewObject2 = NULL;
	activex.viewObjectEx = NULL;
	activex.dataObject = NULL;
	activex.unknown = NULL;
	activex.oleInPlaceObject = NULL;
	activex.oleInPlaceObjectWindowless = NULL;
}

Container::~Container(void)
{
	//Delete() is called on Window_Destroy
	::CoUninitialize();
}

void Container::DisplayInterfaceFunctions(HWND hWnd, Com::Object& object)
{
	Win::ListDlg dlg;
	object.GetFuncInfo(dlg.data);
	dlg.BeginDialog(hWnd);
}

void Container::Window_LButtonDown(Win::Event& e)
{
	if (Enabled==false) return;
	HWND hWndParent = ::GetParent(hWnd);
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_CLICK), e.lParam);
}

void Container::Window_RButtonDown(Win::Event& e)
{
	if (Enabled==false) return;
	HWND hWndParent = ::GetParent(hWnd);
	::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM(this->id, WIN_RCLICK), e.lParam);
}

int Container::GetActivexInfo(vector<Com::ActiveXInfo>& info)
{
	Sys::Key key(HKEY_CLASSES_ROOT);
	Sys::Key keyActiveX(HKEY_CLASSES_ROOT);
	Sys::Key keyControl(HKEY_CLASSES_ROOT);
	Sys::Key keyProgID(HKEY_CLASSES_ROOT);
	Sys::Key keyVersionIndependentProgID(HKEY_CLASSES_ROOT);
	if (key.Open(L"CLSID", KEY_READ) == false) return 0;
	wchar_t * name = NULL;
	int i = 0;
	Com::ActiveXInfo axi;
	bool versionIndependentProgID = false;
	
	wchar_t buffer[512];
	wchar_t * value = NULL;

	for(i = 0; ; i++)
	{
		name = key.Enumerate(i);
		if (name == NULL) break;
		_snwprintf_s(buffer, 512, _TRUNCATE, L"CLSID\\%s\\Control", name);
		if (keyControl.Open(buffer, KEY_READ)==false) continue;
		//
		_snwprintf_s(buffer, 512, _TRUNCATE, L"CLSID\\%s", name);
		if (keyActiveX.Open(buffer, KEY_READ)==false) continue;
		//
		_snwprintf_s(buffer, 512, _TRUNCATE, L"CLSID\\%s\\ProgID", name);
		if (keyProgID.Open(buffer, KEY_READ)==false) continue;
		//
		_snwprintf_s(buffer, 512, _TRUNCATE, L"CLSID\\%s\\VersionIndependentProgID", name);
		versionIndependentProgID = keyVersionIndependentProgID.Open(buffer, KEY_READ);
		//
		value = keyActiveX.ReadStringValue(L"");
		if (value==NULL) continue;
		axi.descr = value;
		//
		value = keyProgID.ReadStringValue(L"");
		if (value==NULL) continue;
		axi.ProgID = value;
		//
		if (versionIndependentProgID == true)
		{
			value = keyVersionIndependentProgID.ReadStringValue(L"");
			if (value==NULL) continue;
			axi.VersionIndependentProgID = value;
		}
		else
		{
			axi.VersionIndependentProgID.clear();
		}
		info.push_back(axi);
	}
	std::sort(info.begin(), info.end());
	return info.size();
}

bool Container::GetFuncInfo(HWND hWnd, const wchar_t* text, list<Com::FuncInfo>& result)
{
	::CoInitialize(NULL);
	{
		try
		{
			Com::Object object;
			object.CreateInstance(text, false);
			object.GetFuncInfo(result);
		}
		catch(Com::Exception excep)
		{
			wchar_t text[512];
			excep.GetErrorText(text, 512);
			::MessageBox(hWnd, text, L"Container::GetFuncInfo", MB_OK | MB_ICONERROR);
			::CoUninitialize();
			return false;
		}
	}
	::CoUninitialize();
	return true;
}

void Container::SetVisible(bool visible)
{
	this->visible = visible;
	::ShowWindow(hWnd, visible ? SW_SHOWNORMAL:SW_HIDE);
}

bool Container::IsVisible()
{
	return this->visible;
}

void Container::SetAllowResize(bool resizable)
{
	this->allowResize = resizable;
}

bool Container::GetAllowResize()
{
	return this->allowResize;
}

COLORREF Container::GetBackColor()
{
	return Sys::Convert::OleColorToColorRef(_backColor);
}

void Container::SetBackColor(COLORREF color)
{
	_backColor = (OLE_COLOR)color;
	IOleControlPtr oleControlPtr(activex.unknown);
	if (oleControlPtr==NULL) return;
	oleControlPtr->OnAmbientPropertyChange(DISPID_AMBIENT_BACKCOLOR);
}

COLORREF Container::GetTextColor()
{
	return Sys::Convert::OleColorToColorRef(_textColor);
}

void Container::SetTextColor(COLORREF color)
{
	_textColor = (OLE_COLOR)color;
	IOleControlPtr oleControlPtr(activex.unknown);
	if (oleControlPtr==NULL) return;
	oleControlPtr->OnAmbientPropertyChange(DISPID_AMBIENT_FORECOLOR);
}

bool Container::GetUserMode()
{
	return _userMode;
}

void Container::SetUserMode(bool userMode)
{
	_userMode = userMode;
	IOleControlPtr oleControlPtr(activex.unknown);
	if (oleControlPtr==NULL) return;
	oleControlPtr->OnAmbientPropertyChange(DISPID_AMBIENT_USERMODE);
}

//void Container::Window_LButtonDblclk(Win::Event& e)
//{
//	//this->SetActivate(true);
//	//::PostMessage(hh,AX_INPLACE,1,0);
//}

void Container::Window_Size(Win::Event& e)
{
	e.returnValue = ::DefWindowProc(e.hWnd, WM_SIZE, e.wParam, e.lParam);
	//return;
	if (isInPlace == true)
	{
		this->SetActivate(false);
		::InvalidateRect(hWnd, NULL, TRUE);
		this->SetActivate(true);
	}

	if (activex.oleObject==NULL) return;
	IOleInPlaceObjectPtr oleInPlaceObject(activex.unknown);

	if (oleInPlaceObject==NULL) return;
	RECT rc1, rc2;
	::GetClientRect(hWnd, &rc1);
	rc2 = rc1;
	oleInPlaceObject->SetObjectRects(&rc1, &rc2);
	oleInPlaceObject = NULL;
	this->SetExtent();
}

void Container::Window_Paint(Win::Event& e)
{
	Win::Gdi gdi(e.hWnd, true, false);
//	if (gdi.GetPaintStruct().fErase)
//	{
//		        HBRUSH hBrush = reinterpret_cast<HBRUSH>( ::GetClassLongPtr(hWnd, GCLP_HBRBACKGROUND) );
//        hBrush = ( (hBrush != NULL) ? hBrush : HBRUSH(COLOR_3DFACE+1) );
//#pragma warning(pop)
//#else
//        HBRUSH hBrush = HBRUSH(COLOR_3DFACE+1);
//#endif
//        ::FillRect(hDC, lpRect, hBrush);
//	}
	this->ProcessPaint(gdi.GetHDC(), NULL);
}

HRESULT Container::Activate()
{
	if (activex.oleObject == NULL) return E_UNEXPECTED;

	HRESULT hr = activex.oleObject->GetMiscStatus(DVASPECT_CONTENT, &miscStatus);
	if (FAILED(hr)) return hr;
	if ( (miscStatus & OLEMISC_SETCLIENTSITEFIRST) != 0)
	{
		hr = activex.oleObject->SetClientSite((IOleClientSite*)this);
		if (FAILED(hr)) return hr;
		//
		IPersistStreamInitPtr persistStreamInit(activex.unknown);
		if (persistStreamInit) 
		{
			hr = persistStreamInit->InitNew();
			persistStreamInit = NULL;
			if (FAILED(hr)) 
			{
				activex.oleObject->SetClientSite(NULL);
				return hr;
			}
		}
	}
	return InplaceActivate();
}

HRESULT Container::Activate(vector<Property>& properties)
{
	if (activex.oleObject == NULL) return E_UNEXPECTED;

	HRESULT hr = activex.oleObject->GetMiscStatus(DVASPECT_CONTENT, &miscStatus);
	if (FAILED(hr)) return hr;
	if ( (miscStatus & OLEMISC_SETCLIENTSITEFIRST) != 0)
	{
		hr = activex.oleObject->SetClientSite((IOleClientSite*)this);
		if (FAILED(hr)) return hr;
		//
		Com::PersistPropertyBag persistPropertyBag;
		hr = persistPropertyBag.Create(properties, this->activex.unknown);
		if (FAILED(hr))
		{
			if ( (miscStatus & OLEMISC_SETCLIENTSITEFIRST) != 0)
			{
				activex.oleObject->SetClientSite(NULL);
            }
        }
	}
	return InplaceActivate();
}


void Container::SetActivate(bool activate)
{
	if (activex.oleObject==NULL) return;

	if (isInPlace == false && activate == true)
	{
		isInPlace = true;
		this->DoVerb(OLEIVERB_INPLACEACTIVATE);
		::InvalidateRect(hWnd, NULL, TRUE);
	}

	if (isInPlace == true && activate == false)
	{
		isInPlace = false;
		IOleInPlaceObjectPtr oleInPlaceObject(activex.unknown);
		if (oleInPlaceObject)
		{
			oleInPlaceObject->UIDeactivate();
			oleInPlaceObject->InPlaceDeactivate();
			oleInPlaceObject = NULL;
			::InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	this->SetExtent();
}

HRESULT Container::OleObjectQueryInterface(REFIID riid, void** pvvObject)
{
	if (activex.oleObject==NULL) return E_FAIL;
	return activex.oleObject->QueryInterface(riid, pvvObject);
}

void Container::Window_Destroy(Win::Event& e)
{
	this->Delete();
}

HRESULT Container::InplaceActivate()
{
	HRESULT hr = S_OK;
	try
	{
		activex.viewObjectEx = activex.unknown;
		if (activex.viewObjectEx == NULL) 
		{
			activex.viewObject2 = activex.unknown;
			if (activex.viewObject2 == NULL) 
			{
				activex.viewObject = activex.unknown;
			}
		}

		IAdviseSinkPtr adviseSink;
		this->QueryInterface(IID_IAdviseSink, (void**)&adviseSink);
		if (adviseSink==NULL)
		{
			this->MessageBox(L"Unable to get IAdviseSink", L"Com::Container", MB_OK | MB_ICONERROR);
			return S_OK;
		}
		if (activex.viewObjectEx)
		{
			hr = activex.viewObjectEx->SetAdvise(DVASPECT_CONTENT, 0, adviseSink);
		}
		else if (activex.viewObject2)
		{
			hr = activex.viewObject2->SetAdvise(DVASPECT_CONTENT, 0, adviseSink);
		}
		else if (activex.viewObject)
		{
			hr = activex.viewObject->SetAdvise(DVASPECT_CONTENT, 0, adviseSink);
		}
	}
	catch(_com_error ex)
	{
		Com::Exception::Display(hWnd, ex, L"Com::Container");
		return E_FAIL;
	}

	if (FAILED(hr))
	{
		this->MessageBox(L"Error: IAdviseSink.SetAdvise", L"Com::Container", MB_OK | MB_ICONERROR);
		return S_OK;
	}

	this->SetActivexRect(this->_initialRect);
	return DoVerb(OLEIVERB_INPLACEACTIVATE);
 }

HRESULT Container::DoVerb(long verb)
{
	if ((miscStatus & (OLEMISC_INVISIBLEATRUNTIME | OLEMISC_NOUIACTIVATE)) != 0) return S_FALSE;
	if (activex.oleObject == NULL) return E_UNEXPECTED;
	
	RECT rect;
	::GetClientRect(hWnd, &rect);
	HRESULT hr = activex.oleObject->DoVerb(verb, NULL, (IOleClientSite*)this, 0, hWnd, &rect);
	if (verb == OLEIVERB_INPLACEACTIVATE && SUCCEEDED(hr)) inplaceActive = true;
    return hr;
}

HRESULT Container::SetActivexRect(const RECT& rc)
{
	HRESULT hr = S_FALSE;
	if (::EqualRect(&rectPosition, &rc) == FALSE)
	{
		rectPosition = rc;
		RECT tmp;
		::GetClientRect(hWnd, &tmp);
		if (activex.oleInPlaceObject) 
		{
			hr = activex.oleInPlaceObject->SetObjectRects(&tmp, &tmp);
			if (FAILED(hr))
			{
				this->MessageBox(L"Error:  IOleInPlaceObject.SetObjectRects", L"Com::Container", MB_OK | MB_ICONERROR);
				return hr;
			}
		}
		if (activex.oleObject ==NULL) return E_UNEXPECTED;
		SetExtent();
	}
	return hr;
}

HRESULT Container::SetExtent()
{
	SIZEL pixelSize = {width, height};
    SIZEL hiMetricsSize;
	hiMetricsSize.cx = 0;
	hiMetricsSize.cy = 0;
	Sys::Convert::PixelToHiMetric(pixelSize, hiMetricsSize);
	//
	HRESULT hr = activex.oleObject->SetExtent(DVASPECT_CONTENT, &hiMetricsSize);
	if (FAILED(hr))
	{
		this->MessageBox(L"Error:  IOleObject.SetExtent", L"Com::Container", MB_OK | MB_ICONERROR);
		return hr;
	}
	hr = activex.oleObject->GetExtent(DVASPECT_CONTENT, &pixelSize);
	if (FAILED(hr))
	{
		this->MessageBox(L"Error:  IOleObject.GetExtent", L"Com::Container", MB_OK | MB_ICONERROR);
		return hr;
	}
	//
	Sys::Convert::HiMetricToPixel(hiMetricsSize, pixelSize);
	rectPosition.right = rectPosition.left + pixelSize.cx;
	rectPosition.bottom = rectPosition.top + pixelSize.cy;
	return S_OK;
}

void Container::Window_Open(Win::Event& e)
{
	wchar_t texto[256];
	::GetWindowTextW(hWnd, texto, 256);

	try
	{
		activex.unknown.CreateInstance(texto, NULL, CLSCTX_INPROC_SERVER);
		activex.oleObject = activex.unknown;
		activex.oleInPlaceObject = activex.unknown;
		activex.oleInPlaceObjectWindowless = activex.unknown;
		//
		//hr = StgCreateDocfile(0, STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT | STGM_CREATE, 0, &activex.storage);
		//if (FAILED(hr)) throw _com_error(hr);
	}
	catch(_com_error ex)
	{
		Com::Exception::Display(hWnd, ex, L"Com::Container");
	}
	//this->Activate();	
	//if (activex.oleObject) activex.oleObject->QueryInterface(IID_IDispatch, (void**)&disp);
	this->unknown = activex.unknown;
	this->comobj.dispatch = unknown;
}

void Container::Delete(void)
{
	//if (isInPlace == true)
	//{
	//	isInPlace = false;
	//	IOleInPlaceObject* iib = NULL;
	//	if (info.oleObject)
	//	info.oleObject->QueryInterface(IID_IOleInPlaceObject, (void**)&iib);
	//	if (iib)
	//	{
	//		iib->UIDeactivate();
	//		iib->InPlaceDeactivate();
	//		iib->Release();
	//	}
	//}
	this->unknown = NULL;
	this->comobj.destroy(true);
	if (activex.viewObject)
    {
        activex.viewObject->SetAdvise(DVASPECT_CONTENT, 0, NULL);
       activex.viewObject = NULL;
    }
	if (activex.viewObject2)
    {
        activex.viewObject2->SetAdvise(DVASPECT_CONTENT, 0, NULL);
       activex.viewObject2 = NULL;
    }
	if (activex.viewObjectEx)
    {
        activex.viewObjectEx->SetAdvise(DVASPECT_CONTENT, 0, NULL);
       activex.viewObjectEx = NULL;
    }
    activex.oleInPlaceObjectWindowless = NULL;

	if (activex.oleInPlaceObject) 
	{
		if (inplaceActive)
		{
			activex.oleInPlaceObject->InPlaceDeactivate();
			inplaceActive = false;
		}
		activex.oleInPlaceObject = NULL;
	}
 
    if (activex.oleObject)
    {
        activex.oleObject->SetClientSite(NULL);
        activex.oleObject->Close(OLECLOSE_NOSAVE);
        activex.oleObject = NULL;
    }

	activex.dataObject = NULL;
	activex.unknown = NULL;
}

//_____________________________________________________________ IUnknown
STDMETHODIMP_ (ULONG) Container::AddRef()
{
	//return 1;
	refCount++;
	return refCount;
}

STDMETHODIMP_(ULONG) Container::Release()
{
	//return 0;
	refCount--;
	return refCount;
}

STDMETHODIMP Container::QueryInterface(REFIID iid, void** ppvObject)
{
	*ppvObject = NULL;

	if (iid == IID_IOleClientSite) *ppvObject = (IOleClientSite*)this;
	else if (iid == IID_IUnknown) *ppvObject = (IUnknown*)(IDispatch*)this;
	else if (iid == IID_IOleWindow) *ppvObject = (IOleWindow*)(IOleInPlaceSiteWindowless*)this;
	else if (iid == IID_IAdviseSink) *ppvObject = (IAdviseSink*)this;
	else if (iid == IID_IDispatch) *ppvObject = (IDispatch*)this;
	else if (iid == IID_IServiceProvider) *ppvObject = (IServiceProvider*)this;
	else if (iid == IID_IOleControlSite) *ppvObject = (IOleControlSite*)this;
	else if (iid == IID_IOleInPlaceSite) *ppvObject = (IOleInPlaceSite*)this;
	else if (iid == IID_IOleInPlaceSiteEx) *ppvObject = (IOleInPlaceSiteEx*)this;
	else if (iid == IID_IOleInPlaceSiteWindowless) *ppvObject = (IOleInPlaceSiteWindowless*)this;
	//
	else if (iid == IID_IOleInPlaceFrame) *ppvObject = (IOleInPlaceFrame*)this;
	else if (iid == IID_IOleInPlaceUIWindow) *ppvObject = (IOleInPlaceUIWindow*)this;
	else if (iid == IID_IOleContainer) *ppvObject = (IOleContainer*)this;
	else if (iid == IID_IParseDisplayName) *ppvObject = (IParseDisplayName*)this;
	else if (iid == IID_IBindHost) *ppvObject = (IBindHost*)this;
	//else if (iid == IID_IOleObject)
	//{
	//	this->MessageBox(L"Hola", L"Que pasa", MB_OK);
	//}

	if (*ppvObject)
	{
		AddRef();
		return S_OK;
	}
	return E_NOINTERFACE;
}

//_______________________________________________________ IDispatch
STDMETHODIMP Container::GetTypeInfoCount(UINT *pctinfo)
{
	*pctinfo = 0;
	return S_OK;
}

STDMETHODIMP Container::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
{
	return E_NOTIMPL;
}

STDMETHODIMP Container::GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
	return E_NOTIMPL;
}

STDMETHODIMP Container::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, 
							   DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
	if (riid != IID_NULL) return E_INVALIDARG;
	if ((DISPATCH_PROPERTYGET & wFlags)==0 ) return DISP_E_MEMBERNOTFOUND;

	bool m_bUserMode = false;
	VARIANT varResult;

	if (NULL==pVarResult) pVarResult = &varResult;

	VariantInit(pVarResult);

	switch (dispIdMember)
	{
	case DISPID_AMBIENT_BACKCOLOR:
		V_I4(pVarResult)= _backColor;
		V_VT(pVarResult)= VT_I4;
		break;
	case DISPID_AMBIENT_FORECOLOR:
		V_I4(pVarResult)= _textColor;
		V_VT(pVarResult)= VT_I4;
		break;
	case DISPID_AMBIENT_LOCALEID:
		V_I4(pVarResult)= _localeId;
		V_VT(pVarResult)= VT_I4;
		break;
	case DISPID_AMBIENT_USERMODE:
		V_BOOL(pVarResult)= _userMode ? VARIANT_TRUE : VARIANT_FALSE;
		break;
	case DISPID_AMBIENT_UIDEAD:
		V_BOOL(pVarResult)= VARIANT_FALSE;
		break;
	case DISPID_AMBIENT_SUPPORTSMNEMONICS:
		V_BOOL(pVarResult)= VARIANT_FALSE;
		break;
	case DISPID_AMBIENT_SHOWGRABHANDLES:
		V_BOOL(pVarResult)= _userMode ? VARIANT_FALSE : VARIANT_TRUE;
		break;
	case DISPID_AMBIENT_SHOWHATCHING:
		V_BOOL(pVarResult)= _userMode ? VARIANT_FALSE : VARIANT_TRUE;
		break;
	default:
		V_VT(pVarResult)=VT_BOOL;
		return DISP_E_MEMBERNOTFOUND;
	}
	return S_OK;
}

//_____________________________________________________________ IOleClientSite
STDMETHODIMP Container::SaveObject()
{
	return E_NOTIMPL;
}

STDMETHODIMP Container::GetMoniker(DWORD dwA, DWORD dwW, IMoniker**pMoniker)
{
	*pMoniker = NULL;
	if (hostUrl.empty()) return E_UNEXPECTED;
	if (dwW != OLEWHICHMK_CONTAINER) return E_UNEXPECTED;

	IBindHostPtr bindHost;

	HRESULT hr = this->QueryInterface(__uuidof(IBindHost), (void**)&bindHost);
	if ( SUCCEEDED(hr) )
	{
		hr = bindHost->CreateMoniker((LPOLESTR)hostUrl.c_str(), NULL, pMoniker, 0);
	}
	return hr;
}

STDMETHODIMP Container::GetContainer(IOleContainer** oleContainer)
{
	if (oleContainer == NULL) return E_POINTER;
	HRESULT hr = this->QueryInterface(IID_IOleContainer, (void**)oleContainer);
	return hr;
}

STDMETHODIMP Container::ShowObject()
{
	if (width<=0) return S_OK;
	if (height<=0) return S_OK;
	//if (::IsRectEmpty(&rectPosition)) return S_OK;
	this->visible = true;

	if (this->inplaceActive)
	{
		HDC hDC = ::GetDC(hWnd);
		if (activex.oleInPlaceObjectWindowless)
		{
			ProcessPaint(hDC, NULL);
		}
		else
		{
			RECT rect;
			::GetClientRect(hWnd, &rect);
			ProcessPaint(hDC, &rect);
		}
		
		if (::ReleaseDC(hWnd, hDC) == 1) return S_OK;
		return E_FAIL;
	}
	else if (activex.oleInPlaceObjectWindowless)
	{
		HWND hWndControl = NULL;
		activex.oleInPlaceObjectWindowless->GetWindow(&hWndControl);
	}
	return S_OK;
}

STDMETHODIMP Container::OnShowWindow(BOOL fShow)
{
	visible = ( fShow != FALSE );
	::InvalidateRect(hWnd, NULL, TRUE);
	//
	RECT rect;
	HWND parent = ::GetParent(hWnd);
	::GetWindowRect(hWnd, &rect);
	::MapWindowPoints(NULL, parent, (LPPOINT)&rect, 2);
	::InvalidateRect(parent, &rect, TRUE);
	return S_OK;
}

STDMETHODIMP Container::RequestNewObjectLayout()
{
	//return S_OK;
	return E_NOTIMPL;
}

void Container::ProcessPaint(HDC hdc, LPCRECT lpClipRect)
{
	if ( lpClipRect && !InsideClippingRegion(*lpClipRect)) return;
	if (visible==false) return;

	RECT rc = {0, 0, width, height};
	//RECT rcPos;
	//::GetWindowRect(hWnd, &rcPos);
	//::MapWindowPoints(HWND_DESKTOP, ::GetParent(hWnd), (LPPOINT)&rcPos, 2);
	HRESULT hr;
	if (activex.viewObjectEx)
	{
		hr = activex.viewObjectEx->Draw(DVASPECT_CONTENT, -1, NULL, NULL, NULL, hdc, 
			 reinterpret_cast<LPCRECTL>(&rc), NULL, NULL, 0);
		//hr = activex.viewObjectEx->Draw(DVASPECT_CONTENT, -1, NULL, NULL, NULL, hdc, 
		//	 (LPCRECTL)&rc, NULL, NULL, 0);
		return;
	}
	else if (activex.viewObject2)
	{
		hr = activex.viewObject2->Draw(DVASPECT_CONTENT, -1, NULL, NULL, NULL, hdc, 
			 reinterpret_cast<LPCRECTL>(&rc), NULL, NULL, 0);
		return;
	}
	else if (activex.viewObject)
	{
		hr = activex.viewObject->Draw(DVASPECT_CONTENT, -1, NULL, NULL, NULL, hdc, 
			 reinterpret_cast<LPCRECTL>(&rc), NULL, NULL, 0);
		return;
	}
}

bool Container::InsideClippingRegion(const RECT& rcClip) const
{
    // true when window overlaps with clipping region
    RECT rc = { 0 };
	RECT rcPos;
	::GetWindowRect(hWnd, &rcPos);
    return ( ::IntersectRect(&rc, &rcClip, &rcPos) != FALSE );
}

//_______________________________________________________ IOleControlSite
STDMETHODIMP Container::OnControlInfoChanged(void)
{
	return S_OK;
}

STDMETHODIMP Container::LockInPlaceActive(BOOL fLock)
{
	return E_NOTIMPL;
}

STDMETHODIMP Container::GetExtendedControl(IDispatch **ppDisp)
{
	if (ppDisp == NULL ) return E_POINTER;
	HRESULT hr = this->QueryInterface(IID_IDispatch, (void**)ppDisp);
	return hr;
}

STDMETHODIMP Container::TransformCoords(POINTL *pPtlHimetric, POINTF *pPtfContainer, DWORD dwFlags)
{
	return E_NOTIMPL;
}

STDMETHODIMP Container::TranslateAccelerator(MSG *pMsg, DWORD grfModifiers)
{
	return S_FALSE;
}

STDMETHODIMP Container::OnFocus(BOOL fGotFocus)
{
	//if (fGotFocus) 
	//{
	//	::SetFocus(hWnd);
	//}
	//else
	//{
	//	::SendMessage(hWnd, WM_KILLFOCUS, (WPARAM)0, (LPARAM)0);
	//}
	return S_OK;
}

STDMETHODIMP Container::ShowPropertyFrame(void)
{
	return E_NOTIMPL;
}


//_______________________________________________________ IAdviseSink
STDMETHODIMP_(void) Container::OnDataChange(FORMATETC *pFormatEtc, STGMEDIUM *pStgMedium)
{
}

STDMETHODIMP_(void) Container::OnViewChange(DWORD dwAspect, LONG lIndex)
{
}

STDMETHODIMP_(void) Container::OnRename(IMoniker * pMoniker)
{
}

STDMETHODIMP_(void) Container::OnSave()
{
}

STDMETHODIMP_(void) Container::OnClose()
{
}

//_______________________________________________________ IServiceProvider
STDMETHODIMP Container::QueryService(REFGUID guidService, REFIID riid, void **ppvObject)
{	
	*ppvObject = NULL;

	static const GUID GUID_IWebBrowserApp = // {0002DF05-0000-0000-C000-000000000046}
	{ 0x0002DF05, 0x0000, 0x0000, { 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 } };

	static const GUID GUID_IXcpControlHost = // {1B36028E-B491-4BB2-8584-8A9E0A677D6E}
	{ 0x1B36028E, 0xB491, 0x4BB2, { 0x85, 0x84, 0x8A, 0x9E, 0x0A, 0x67, 0x7D, 0x6E } };

	HRESULT hr = E_FAIL;
	if (guidService == IID_IBindHost || guidService == GUID_IWebBrowserApp || guidService == GUID_IXcpControlHost)
	{
		return this->QueryInterface(riid, ppvObject);
	}
	//else
	//{
	//	return E_NOTIMPL;
	//}
	return hr;
}

//_______________________________________________________ IOleInPlaceSiteWindowless
STDMETHODIMP Container::CanWindowlessActivate()
{
	return S_OK;
}

STDMETHODIMP Container::GetCapture()
{
	return S_OK;
}

STDMETHODIMP Container::SetCapture(BOOL fCapture)
{
	if (fCapture == FALSE)
	{
		if (hWnd == ::GetCapture()) ::ReleaseCapture();
	}

	return S_OK;
}

STDMETHODIMP Container::GetFocus()
{
	return S_OK;
}

STDMETHODIMP Container::SetFocus(BOOL fFocus)
{
	return S_OK;
}

STDMETHODIMP Container::GetDC(LPCRECT pRect, DWORD grfFlags, HDC *phDC)
{
	*phDC = NULL;
	if ( (grfFlags & OLEDC_OFFSCREEN) != 0 ) return E_OUTOFMEMORY;
	if (phDC != NULL) *phDC = ::GetDC(hWnd);
	return S_OK;
}

STDMETHODIMP Container::ReleaseDC(HDC hDC)
{
	if (::ReleaseDC(hWnd, hDC) == 1) return S_OK;
	return E_FAIL;
}

STDMETHODIMP Container::InvalidateRect(LPCRECT pRect, BOOL fErase)
{
	::InvalidateRect(hWnd, pRect, fErase);
	return S_OK;
}

STDMETHODIMP Container::InvalidateRgn(HRGN hRGN, BOOL fErase)
{
	::InvalidateRgn(hWnd, hRGN, fErase);
	return S_OK;
}

STDMETHODIMP Container::ScrollRect(INT dx, INT dy, LPCRECT pRectScroll, LPCRECT pRectClip)
{
	::ScrollWindowEx(hWnd, dx, dy, pRectScroll, pRectClip, NULL, NULL, SW_ERASE);
	return S_OK;
}

STDMETHODIMP Container::AdjustRect(LPRECT prc)
{
	return S_OK;
}

STDMETHODIMP Container::OnDefWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam, LRESULT *plResult)
{
	if (plResult)
	{
		*plResult = ::DefWindowProc(hWnd, msg, wParam, lParam);
		return S_OK;
	}
	return E_POINTER;
}

//_____________________________________________________________ IOleInPlaceSiteEx
STDMETHODIMP Container::OnInPlaceActivateEx(BOOL *pfNoRedraw, DWORD dwFlags)
{
	OleLockRunning(activex.oleObject, TRUE, FALSE);
	if (pfNoRedraw) *pfNoRedraw = FALSE;
	if ((dwFlags & ACTIVATE_WINDOWLESS) != 0) 
	{
		if (activex.oleInPlaceObjectWindowless) inplaceActive = true;
	} 
	else
	{
		inplaceActive = false;
	}
	return S_OK;
}

STDMETHODIMP Container::OnInPlaceDeactivateEx(BOOL fNoRedraw)
{
	inplaceActive = false;
	return S_OK;
}

STDMETHODIMP Container::RequestUIActivate(void)
{
	return S_OK;
}

//_____________________________________________________________ IOleInPlaceSite
STDMETHODIMP Container::CanInPlaceActivate()
{
	return S_OK;
}

STDMETHODIMP Container::OnInPlaceActivate()
{
	return S_OK;
}

STDMETHODIMP Container ::OnUIActivate()
{
 return S_OK;
}

STDMETHODIMP Container::GetWindowContext(IOleInPlaceFrame** ppFrame, IOleInPlaceUIWindow **ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo)
{
	HRESULT hr;
	if (ppFrame)
	{
		hr = this->QueryInterface(__uuidof(IOleInPlaceFrame), (void**)ppFrame);
		//if (FAILED(hr)) return hr;
	}

	if (ppDoc) *ppDoc = NULL;
	RECT rc;
	::GetClientRect(hWnd, &rc);

	if (lprcPosRect) *lprcPosRect = rc;
	if (lprcClipRect) *lprcClipRect = rc;
	//if (lprcPosRect) *lprcPosRect = rectPosition;
	//if (lprcClipRect) *lprcClipRect = rectPosition;

	if (lpFrameInfo)
	{
		lpFrameInfo->cb = sizeof(OLEINPLACEFRAMEINFO);
		lpFrameInfo->fMDIApp = FALSE;
		lpFrameInfo->hwndFrame = ::GetParent(hWnd);
		lpFrameInfo->haccel = 0;
		lpFrameInfo->cAccelEntries = 0;
	}
	return hr;
}

STDMETHODIMP Container::Scroll(SIZE scrollExtant)
{
	//if (size.cx>0)
	//{
	//	::SendMessage(hWnd, WM_HSCROLL, MAKEWPARAM(SB_THUMBPOSITION, scrollExtant.cx), (LPARAM)0);
	//	return S_OK;
	//}
	//if (size.cy>0)
	//{
	//	::SendMessage(hWnd, WM_VSCROLL, MAKEWPARAM(SB_THUMBPOSITION, scrollExtant.cy), (LPARAM)0);
	//	return S_OK;
	//}
	return E_NOTIMPL;
}

STDMETHODIMP Container::OnUIDeactivate(BOOL fUndoable)
{
	return S_OK;
}

STDMETHODIMP Container::OnInPlaceDeactivate()
{
	return OnInPlaceDeactivateEx(TRUE);
}

STDMETHODIMP Container::DiscardUndoState()
{
	return E_NOTIMPL;
}

STDMETHODIMP Container::DeactivateAndUndo()
{
	return E_NOTIMPL;
}

STDMETHODIMP Container::OnPosRectChange(LPCRECT lprcPosRect)
{
	if (lprcPosRect==NULL) return E_POINTER;

	if (allowResize)
	{
		HRESULT hr;
		rectPosition = *lprcPosRect;
		if (activex.oleInPlaceObject)
		{
			RECT rcClient;
			::GetClientRect(hWnd, &rcClient);
			POINT pointLeftTop;
			POINT pointRightBottom;
			pointLeftTop.x = lprcPosRect->left;
			pointLeftTop.y = lprcPosRect->top;
			pointRightBottom.x = lprcPosRect->right;
			pointRightBottom.y = lprcPosRect->bottom;
			
			if ( ::PtInRect(&rcClient, pointLeftTop) && ::PtInRect(&rcClient, pointRightBottom) )
			{
				rectPosition = *lprcPosRect;
				hr = activex.oleInPlaceObject->SetObjectRects(&rectPosition, &rectPosition);
				if (FAILED(hr)) return hr;
				::MoveWindow(hWnd, rectPosition.left, rectPosition.top, rectPosition.right-rectPosition.left, rectPosition.bottom-rectPosition.top, TRUE);
			} 
			else 
			{
				return E_INVALIDARG;
			}
		}
		return SetExtent();
	}
	return S_OK;
}

//_______________________________________________________ IOleWindow
STDMETHODIMP Container::GetWindow(HWND *phWnd)
{
	*phWnd = hWnd;
	return S_OK;
}

STDMETHODIMP Container::ContextSensitiveHelp(BOOL f)
{
	return E_NOTIMPL;
}

//_______________________________________________________ IOleInPlaceFrame
STDMETHODIMP Container::InsertMenus(HMENU hmenuShared, LPOLEMENUGROUPWIDTHS lpMenuWidths)
{
	return E_NOTIMPL;
}

STDMETHODIMP Container::SetMenu(HMENU hmenuShared, HOLEMENU holemenu, HWND hwndActiveObject)
{
	return E_NOTIMPL;
}

STDMETHODIMP Container::RemoveMenus(HMENU hmenuShared)
{
	HMENU hMenu = ::GetMenu(hWnd);
	HMENU hSubMenu = NULL;
	if (hMenu==NULL) return S_OK;
	const int menuItemCount = ::GetMenuItemCount(hMenu);
	for (int i = menuItemCount; i >= 0; i--)
	{
		hSubMenu = ::GetSubMenu(hMenu, i);
		if (hSubMenu == ::GetMenu(hWnd)) ::RemoveMenu(hMenu, i, MF_BYPOSITION);
	}
	if (hMenu == ::GetMenu(hWnd)) ::DestroyMenu(hMenu);
	::DrawMenuBar(::GetParent(hWnd));
	return S_OK;
}

STDMETHODIMP Container::SetStatusText(LPCOLESTR pszStatusText)
{
	return E_NOTIMPL;
}

STDMETHODIMP Container::EnableModeless(BOOL fEnable)
{
	return E_NOTIMPL;
}

STDMETHODIMP Container::TranslateAccelerator(LPMSG lpmsg, WORD wID)
{
	return E_NOTIMPL;
}

//_______________________________________________________ IOleInPlaceUIWindow
STDMETHODIMP Container::GetBorder(LPRECT lprectBorder)
{
	//	::GetClientRect(hWnd, lprectBorder);
	return INPLACE_E_NOTOOLSPACE;
}

STDMETHODIMP Container::RequestBorderSpace(LPCBORDERWIDTHS pborderwidths)
{
	//return E_NOTIMPL;
	return INPLACE_E_NOTOOLSPACE;
}

STDMETHODIMP Container::SetBorderSpace(LPCBORDERWIDTHS pborderwidths)
{
	return S_OK;
}

STDMETHODIMP Container::SetActiveObject(IOleInPlaceActiveObject *pActiveObject, LPCOLESTR pszObjName)
{
	//activex.oleInPlaceActiveObject = pActiveObject;
	return S_OK;
}

//_______________________________________________________ IOleContainer
STDMETHODIMP Container::EnumObjects(DWORD grfFlags, IEnumUnknown **ppenum)
{
	return E_NOTIMPL;
}

STDMETHODIMP Container::LockContainer(BOOL fLock)
{
	return E_NOTIMPL;
}

STDMETHODIMP Container::ParseDisplayName(IBindCtx *pbc, LPOLESTR pszDisplayName, ULONG *pchEaten, IMoniker **ppmkOut)
{
	return E_NOTIMPL;
}

//_______________________________________________________ IBindHost
STDMETHODIMP Container::CreateMoniker(LPOLESTR szName, IBindCtx *pBC, IMoniker **ppmk, DWORD dwReserved)
{
	HRESULT hr = CreateURLMonikerEx(NULL, szName, ppmk, URL_MK_UNIFORM);
	return hr;
}

STDMETHODIMP Container::MonikerBindToStorage(IMoniker *pMk, IBindCtx *pBC, IBindStatusCallback *pBSC, REFIID riid, void **ppvObj)
{
	if (pBC == NULL) return S_OK;
	IBindCtxPtr bindCtx(pBC);
	if (bindCtx == NULL) return S_OK;
	HRESULT hr = CreateBindCtx(0, &bindCtx);
	if (FAILED(hr)) return hr;
	//
	hr = RegisterBindStatusCallback(bindCtx, pBSC, NULL, 0);
	if (FAILED(hr)) return hr;
	//
	if (pMk == NULL) return E_POINTER;
	return pMk->BindToStorage(bindCtx, NULL, riid, ppvObj);
}

STDMETHODIMP Container::MonikerBindToObject(IMoniker *pMk, IBindCtx *pBC, IBindStatusCallback *pBSC, REFIID riid, void **ppvObj)
{
	return E_NOTIMPL;
}

}

//____________________________________________________ namespace Com::End
