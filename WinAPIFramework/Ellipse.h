#pragma once
#include "Shapes.h"

_SHAPES_BEGIN

class Ellipse : public Shapes
{
public:
	Ellipse() {}
	~Ellipse() {}

public:
	BOOL Create(WndSize size, COLORREF frameColor = 0x000000, COLORREF bkColor = 0xffffff, PenInfo penInfo = PenInfo{ PS_SOLID, 1, RGB(0,0,0) });
	BOOL Create(RECT rect, COLORREF frameColor = 0x000000, COLORREF bkColor = 0xffffff, PenInfo penInfo = PenInfo{ PS_SOLID, 1, RGB(0,0,0) });

public:
	virtual void Update() override;

public:
	virtual BOOL Draw(HDC hDC) override;
	virtual BOOL DrawHatched(HDC hDC, int iHatch) override;

	virtual BOOL DrawInWindowCoord(HDC hDC) override;
	virtual BOOL DrawHatchedInWindowCoord(HDC hDC, int iHatch) override;

	BOOL DrawArc(HDC hDC, float beginDegree, float endDegree);
	BOOL DrawChord(HDC hDC, float beginDegree, float endDegree);
	BOOL DrawPie(HDC hDC, float beginDegree, float endDegree);

	BOOL DrawChordHatched(HDC hDC, int iHatch, float beginDegree, float endDegree);
	BOOL DrawPieHatched(HDC hDC, int iHatch, float beginDegree, float endDegree);

private:
	POINT DegreeToPoint(float degree);

public:
	POINT GetLeftTop() { return POINT{ m_Rect.left, m_Rect.top }; }
	POINT GetRightBottom() { return  POINT{ m_Rect.right, m_Rect.bottom }; }
	RECT GetRect() { return m_Rect; }

	POINT GetCenter() { return m_Center; }
	WndSize GetSize() { return m_Size; }

	void SetRectAndReset(RECT rect)
	{
		m_OriginRect = rect;
		m_Offset = POINT{ 0,0 };
		m_Scale = POINT{ 1,1 };
	}

public:
	BOOL Intersects(RECT other, OUT RECT& outIntersected);
	BOOL Union(RECT other, OUT RECT& outIntersected);
	BOOL IsInRect(POINT p);

private:
	void CalculateCenter();
	void CalculateSize();
	void CalculateTransfrom();
	void CalculateToScreen(RECT& outRect);

public:
	static BOOL DrawEllipse(HDC hDC, RECT rect, COLORREF bkColor = 0xffffff, int frameStyle = PS_SOLID, int frameWidth = 1, COLORREF frameColor = RGB(0, 0, 0));

private:
	RECT m_OriginRect = {};
	RECT m_Rect = {};
	POINT m_Center = { 0,0 };
	WndSize m_Size = { 0,0 };

};


_SHAPES_END