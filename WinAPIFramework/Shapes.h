#pragma once


class Shapes
{
public:
	Shapes() {}
	~Shapes() {}

public:
	virtual void Update() {}

public:
	virtual BOOL Draw(HDC hDC) { __debugbreak(); return FALSE; }
	virtual BOOL DrawHatched(HDC hDC, int iHatch) { __debugbreak(); return FALSE; }
	
	virtual BOOL DrawInWindowCoord(HDC hDC) { __debugbreak(); return FALSE; }
	virtual BOOL DrawHatchedInWindowCoord(HDC hDC, int iHatch) { __debugbreak(); return FALSE; }

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

	void AddScale(POINT scale)
	{
		m_Scale.x += scale.x;
		m_Scale.y += scale.y;
	}

	void SetOffsetByWindowCoord(POINT offset)
	{
		POINT screenCenter = POINT{ (LONG)CORE.GetWindowSize().width / 2, (LONG)CORE.GetWindowSize().height / 2 };
		POINT computedOffset = POINT{ offset.x - screenCenter.x, offset.y - screenCenter.y };
		m_Offset = computedOffset;
	}

	COLORREF GetFrameColor() { return m_FrameColor; }
	COLORREF GetBackgroundColor() { return m_BkColor; }
	PenInfo GetPenInfo() { return m_penInfo; }

	int GetFrameStype() { return m_penInfo.style; }
	int GetFrameWidth() { return m_penInfo.width; }


	POINT GetOffset() { return m_Offset; }
	POINT GetScale() { return m_Scale; }

protected:
	POINT m_Offset = { 0,0 };
	POINT m_Scale = { 1,1 };

	COLORREF m_FrameColor = 0xffffff;
	COLORREF m_BkColor = 0xffffff;

	PenInfo m_penInfo;


};

