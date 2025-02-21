#pragma once


_SHAPES_BEGIN

class Line
{
public:
	Line() {}
	~Line() {}

public:
	BOOL Create(POINT startPos, POINT endPos);
	BOOL Draw(HDC hDC);

public:
	void SetStartPos(POINT startPos) { m_startPos = startPos; }
	void SetEndPos(POINT endPos) { m_endPos = endPos; }

	POINT GetStartPos() { return m_startPos; }
	POINT GetEndPos() { return m_endPos; }

public:
	static BOOL DrawLine(HDC hDC, POINT start, POINT end);

private:
	POINT m_startPos = { 0,0 };
	POINT m_endPos = { 0,0 };

};



_SHAPES_END

