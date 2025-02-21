#pragma once

_SHAPES_BEGIN

class Rectangle
{
public:
	Rectangle() {}
	~Rectangle() {}

public:
	BOOL Create(WndSize size, COLORREF frameColor = 0x000000, COLORREF bkColor = 0xffffff, PenInfo penInfo = PenInfo{PS_SOLID, 1, RGB(0,0,0)});
	BOOL Draw(HDC hDC);
	BOOL DrawHatched(HDC hDC, int iHatch);

	BOOL DrawRound(HDC hDC, int width, int height);
	BOOL DrawRoundHatched(HDC hDC, int iHatch, int width, int height);

public:
	void SetFrameColor(COLORREF color) { m_FrameColor = color; }
	void SetBackgroundColor(COLORREF color) { m_BkColor = color; }
	void SetPenInfo(PenInfo info) { m_penInfo = info; }

	void SetFrameWidth(int width) { m_penInfo.width = width; }
	void SetFrameStyle(int style) { m_penInfo.style = style; }

	void SetOffset(POINT offset) 
	{ 
		m_Offset = offset;
	}

	void AddOffset(POINT offset)
	{
		m_Offset.x += offset.x;
		m_Offset.y += offset.y;
	}

	void SetScale(POINT scale)
	{
		m_Scale = scale;
	}

	void SetOffsetByWindowCoord(POINT offset)
	{
		POINT screenCenter = POINT{ (LONG)CORE.GetWindowSize().width / 2, (LONG)CORE.GetWindowSize().height / 2 };
		POINT computedOffset = POINT{ offset.x - screenCenter.x, offset.y - screenCenter.y };
		m_Offset = computedOffset;
	}

	POINT GetLeftTop() { return POINT{ m_Rect.left, m_Rect.top }; }
	POINT GetRightBottom() { return  POINT{ m_Rect.right, m_Rect.bottom }; }
	RECT GetRect() { return m_Rect; }

	POINT GetCenter() { return m_Center; }
	WndSize GetSize() { return m_Size; }

	COLORREF GetFrameColor() { return m_FrameColor; }
	COLORREF GetBackgroundColor() { return m_BkColor; }
	PenInfo GetPenInfo() { return m_penInfo; }

	POINT GetOffset() { return m_Offset; }
	POINT GetScale() { return m_Scale; }

public:
	BOOL Intersects(RECT other, OUT RECT& outIntersected);
	BOOL Union(RECT other, OUT RECT& outIntersected);
	BOOL IsInRect(POINT p);

private:
	void CalculateCenter();	// Fix Later
	void CalculateSize();
	void CalculateTransfrom();
	void CalculateToScreen(RECT& outRect);


public:
	static BOOL DrawRectangle(HDC hDC, POINT leftTop, POINT rightBottom);

private:
	RECT m_OriginRect = {};
	RECT m_Rect = {};
	POINT m_Offset = { 0,0 };
	POINT m_Scale = { 1,1 };

	POINT m_Center = { 0,0 };
	WndSize m_Size = { 0,0 };

	COLORREF m_FrameColor = 0xffffff;
	COLORREF m_BkColor = 0xffffff;

	PenInfo m_penInfo;

};


_SHAPES_END