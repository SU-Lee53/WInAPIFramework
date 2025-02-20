#include "pch.h"
#include "TextBox.h"

using namespace std;

TextBox::TextBox()
{
}

TextBox::~TextBox()
{
	//__debugbreak();
}

BOOL TextBox::Initialize(RECT rect, UINT flags, COLORREF textColor, COLORREF bkColor)
{
	m_Rect = rect;
	m_uiFlags = flags;
	m_TextColor = textColor;
	m_BkColor = bkColor;

	return TRUE;
}

void TextBox::Draw(HDC hDC, const std::wstring& wstrText, TEXTBOX_DRAW_TYPE drawType)
{
	if (!(drawType & TEXTBOX_DRAW_TYPE_NONE))
	{
		FillRectByFlags(hDC, drawType);
	}

	::SetTextColor(hDC, m_TextColor);
	::SetBkColor(hDC, m_BkColor);
	::DrawText(hDC, wstrText.c_str(), wstrText.size(), &m_Rect, m_uiFlags);
}

void TextBox::FillRectByFlags(HDC hDC, TEXTBOX_DRAW_TYPE drawType)
{
	C_SOLID_HBRUSH brush(m_BkColor);
	
	if (drawType & TEXTBOX_DRAW_TYPE_FILL_RECT)
	{
		FillRect(hDC, &m_Rect, brush);
	}

	if (drawType & TEXTBOX_DRAW_TYPE_DRAW_OUTLINE)
	{
		FrameRect(hDC, &m_Rect, brush);
	}

	brush.Destroy();
}

void TextBox::DrawFormattedString(HDC hDC, WndPosition pos, LPCTSTR fmt, ...)
{
	TCHAR lpOut[100];

	va_list fmtArgs;
	va_start(fmtArgs, fmt);

	::_vsnwprintf_s(lpOut, _countof(lpOut), _TRUNCATE, fmt, fmtArgs);
	::TextOut(hDC, pos.x, pos.y, lpOut, lstrlen(lpOut));

	va_end(fmtArgs);
}

SIZE TextBox::GetTextExtent(HDC hDC, const std::wstring& wstrText)
{
	SIZE outSize;
	GetTextExtentPoint32(hDC, wstrText.data(), wstrText.size(), &outSize);
	
	return outSize;
}
