#pragma once

enum TEXTBOX_DRAW_TYPE
{
	TEXTBOX_DRAW_TYPE_NONE = 0,
	TEXTBOX_DRAW_TYPE_FILL_RECT = 1,
	TEXTBOX_DRAW_TYPE_DRAW_OUTLINE = TEXTBOX_DRAW_TYPE_FILL_RECT << 1,

};

class TextBox
{
public:
	TextBox();
	~TextBox();

public:
	BOOL Initialize(RECT rect, UINT flags, COLORREF textColor = 0x000000, COLORREF bkColor = 0xffffff);
	void Draw(HDC hDC, const std::wstring& wstrText, TEXTBOX_DRAW_TYPE drawType = TEXTBOX_DRAW_TYPE_NONE);

public:
	void SetFlag(UINT flag) { m_uiFlags |= flag; }
	void ClearFlag() { m_uiFlags = 0; }

	void SetRect(const RECT& rect) { m_Rect = rect; }
	void SetTextColor(COLORREF color) { m_TextColor = color; }
	void SetBackgroundColor(COLORREF color) { m_BkColor = color; }

	RECT& GetRect() { return m_Rect; }
	COLORREF& GetTextColor() { return m_TextColor; }
	COLORREF& GetBackgroundColor() { return m_BkColor; }

private:
	void FillRectByFlags(HDC hDC, TEXTBOX_DRAW_TYPE drawType);

public:
	// Static Text Functions
	static void DrawFormattedString(HDC hDC, WndPosition pos, LPCTSTR fmt, ...);
	static SIZE GetTextExtent(HDC hDC, const std::wstring& wstrText);

private:
	RECT m_Rect		= {};
	UINT m_uiFlags	= 0;

	COLORREF m_TextColor	= 0xffffff;
	COLORREF m_BkColor		= 0xffffff;

};

