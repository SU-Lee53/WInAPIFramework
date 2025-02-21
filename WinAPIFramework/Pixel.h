#pragma once

_SHAPES_BEGIN

class Pixel
{
public:
	Pixel() {}
	~Pixel() {}

public:
	BOOL Create(POINT position, COLORREF color = 0xffffff);
	void Draw(HDC hDC);

public:
	void SetPos(POINT position) { m_Position = position; }

	POINT GetPos() { return m_Position; }

	void SetColor(COLORREF color) { m_Color = color; }
	COLORREF GetColor() { return m_Color; }

private:
	POINT m_Position = { 0,0 };
	COLORREF m_Color = 0xffffff;
	
};


_SHAPES_END
