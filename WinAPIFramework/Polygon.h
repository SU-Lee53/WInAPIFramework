#pragma once

_SHAPES_BEGIN

class Polygon
{
public:
	Polygon() {}
	~Polygon() {}

public:
	BOOL Create(std::vector<POINT>& points, COLORREF frameColor = 0x000000, COLORREF bkColor = 0xffffff, PenInfo penInfo = PenInfo{ PS_SOLID, 1, RGB(0,0,0) });
	BOOL Draw(HDC hDC);
	BOOL DrawHatched(HDC hDC, int iHatch);

	BOOL DrawPolyLine(HDC hDC);

public:
	void AddPoints(POINT p) { m_Points.push_back(p); }
	void SetPoints(std::vector<POINT>& p) { m_Points.assign(p.begin(), p.end()); }
	void InsertPoints(size_t pos, POINT p) { m_Points.insert(m_Points.begin() + pos, p); }
	void RemovePoint(size_t index);
	BOOL RemovePoint(POINT p);
	
	std::vector<POINT>& GetPoints() { return m_Points; }
	POINT GetPoints(size_t index) { return m_Points[index]; }

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
		POINT screenCenter = POINT{ (LONG)CORE.GetWindowSize().width / 2, (LONG)CORE.GetWindowSize().height };
		POINT computedOffset = POINT{ offset.x - screenCenter.x, offset.y - screenCenter.y };
		m_Offset = computedOffset;
	}

	COLORREF GetFrameColor() { return m_FrameColor; }
	COLORREF GetBackgroundColor() { return m_BkColor; }
	PenInfo GetPenInfo() { return m_penInfo; }

	POINT GetOffset() { return m_Offset; }
	POINT GetScale() { return m_Scale; }

private:
	void CalculateTransfrom();
	void CalculateToScreen(std::vector<POINT>& newPos);

public:
	static BOOL DrawPolygon(HDC hDC, std::vector<POINT>& points);

private:
	std::vector<POINT> m_Points;
	std::vector<POINT> m_OriginPoints;

	POINT m_Offset = { 0,0 };
	POINT m_Scale = { 1,1 };

	COLORREF m_FrameColor = 0xffffff;
	COLORREF m_BkColor = 0xffffff;

	PenInfo m_penInfo;

	BOOL bOffsetUpdated = FALSE;
	BOOL bScaleUpdated = FALSE;

};

_SHAPES_END