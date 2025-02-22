#pragma once
#include "Shapes.h"

_SHAPES_BEGIN

class Polygon : public Shapes
{
public:
	Polygon() {}
	~Polygon() {}

public:
	BOOL Create(std::vector<POINT>& points, COLORREF frameColor = 0x000000, COLORREF bkColor = 0xffffff, PenInfo penInfo = PenInfo{ PS_SOLID, 1, RGB(0,0,0) });
	
public:
	virtual BOOL Draw(HDC hDC) override;
	virtual BOOL DrawHatched(HDC hDC, int iHatch) override;

	virtual BOOL DrawInWindowCoord(HDC hDC) override;
	virtual BOOL DrawHatchedInWindowCoord(HDC hDC, int iHatch) override;

	BOOL DrawPolyLine(HDC hDC);

public:
	void AddPoints(POINT p) { m_Points.push_back(p); }
	void SetPoints(std::vector<POINT>& p) { m_Points.assign(p.begin(), p.end()); }
	void InsertPoints(size_t pos, POINT p) { m_Points.insert(m_Points.begin() + pos, p); }
	void RemovePoint(size_t index);
	BOOL RemovePoint(POINT p);

private:
	void CalculateTransfrom();
	void CalculateToScreen(std::vector<POINT>& newPos);

public:
	static BOOL DrawPolygon(HDC hDC, std::vector<POINT>& points, COLORREF bkColor = 0xffffff, int frameStype = PS_SOLID, int frameWidth = 1, COLORREF frameColor = RGB(0, 0, 0));

private:
	std::vector<POINT> m_Points;
	std::vector<POINT> m_OriginPoints;

};

_SHAPES_END