#pragma once

struct PaintResource
{
	PAINTSTRUCT paintStruct;
	HDC hDC;
};

struct C_RECT : public RECT
{
	C_RECT() = default;
	explicit C_RECT(const RECT& rect) noexcept
		:RECT(rect)
	{}

	C_RECT(LONG left, LONG top, LONG right, LONG bottom)
	{
		Initialize(left, top, right, bottom);
	}

	inline void Initialize(LONG left, LONG top, LONG right, LONG bottom)
	{
		Initialize(*this, left, top, right, bottom);
	}

	static inline void Initialize(RECT& rect, LONG left, LONG top, LONG right, LONG bottom)
	{
		rect.left = left;
		rect.top = top;
		rect.right = right;
		rect.bottom = bottom;
	}

};

struct C_SOLID_HBRUSH
{
	C_SOLID_HBRUSH() = default;
	explicit C_SOLID_HBRUSH(const HBRUSH& brush) noexcept
		: hBrush(brush)
	{}

	C_SOLID_HBRUSH(COLORREF rgb)
	{
		Initialize(rgb);
	}

	inline void Initialize(COLORREF rgb)
	{
		Initialize(*this, rgb);
	}

	static inline void Initialize(C_SOLID_HBRUSH& brush, COLORREF rgb)
	{
		brush.hBrush = CreateSolidBrush(rgb);
	}

	~C_SOLID_HBRUSH()
	{
	}

	inline void Destroy()
	{
		DeleteObject(hBrush);
	}

	operator HBRUSH() const { return hBrush; }

	HBRUSH hBrush;
};

struct C_HATCH_HBRUSH
{
	C_HATCH_HBRUSH() = default;
	explicit C_HATCH_HBRUSH(const HBRUSH& brush) noexcept
		: hBrush(brush)
	{}

	C_HATCH_HBRUSH(int iHatch, COLORREF rgb)
	{
		Initialize(iHatch, rgb);
	}

	inline void Initialize(int iHatch, COLORREF rgb)
	{
		Initialize(*this, iHatch, rgb);
	}

	static inline void Initialize(C_HATCH_HBRUSH& brush, int iHatch, COLORREF rgb)
	{
		brush.hBrush = CreateHatchBrush(iHatch, rgb);
	}

	~C_HATCH_HBRUSH()
	{
	}

	inline void Destroy()
	{
		DeleteObject(hBrush);
	}

	operator HBRUSH() const { return hBrush; }

	HBRUSH hBrush;
};

struct C_HPEN
{
	C_HPEN() = default;
	explicit C_HPEN(const HPEN& pen) noexcept
		:hPen(pen)
	{}

	C_HPEN(int penStyle = PS_SOLID, int width = 1, COLORREF color = RGB(0,0,0))
	{
		Initialize(penStyle, width, color);
	}

	inline void Initialize(int penStyle, int width, COLORREF color)
	{
		Initialize(*this, penStyle, width, color);
	}

	static inline void Initialize(C_HPEN& pen, int penStyle, int width, COLORREF color)
	{
		pen.hPen = CreatePen(penStyle, width, color);
	}

	~C_HPEN()
	{
	}

	inline void Destroy()
	{
		DeleteObject(hPen);
	}

	operator HPEN() const { return hPen; }


	HPEN hPen;
};