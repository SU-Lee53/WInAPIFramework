#pragma once
#include "Shapes.h"

_SHAPES_BEGIN

class Line : public Shapes
{
public:
	Line() {}
	~Line() {}

public:
	BOOL Create(POINT startPos, POINT endPos, int lineStype = PS_SOLID, int lineWidth = 1, COLORREF lineColor = RGB(0, 0, 0));
	virtual BOOL Draw(HDC hDC) override;
	virtual BOOL DrawInWindowCoord(HDC hDC) override;

public:
	void SetStartPos(POINT startPos) { m_startPos = startPos; }
	void SetEndPos(POINT endPos) { m_endPos = endPos; }

	POINT GetStartPos() { return m_startPos; }
	POINT GetEndPos() { return m_endPos; }

public:
	static BOOL DrawLine(HDC hDC, POINT start, POINT end, int lineStyle = PS_SOLID, int lineWidth = 1, COLORREF lineColor = RGB(0, 0, 0));

private:
	void CalculateTransfrom();
	void CalculateToScreen(POINT& start, POINT& end);

private:
	POINT m_startPos = { 0,0 };
	POINT m_endPos = { 0,0 };

	POINT m_OriginStartPos = { 0,0 };
	POINT m_OriginEndPos = { 0,0 };

};



_SHAPES_END

