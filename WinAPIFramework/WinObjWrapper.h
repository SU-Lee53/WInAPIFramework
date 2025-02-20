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
		Create(left, top, right, bottom);
	}

	inline void Create(LONG left, LONG top, LONG right, LONG bottom)
	{
		Create(*this, left, top, right, bottom);
	}

	static inline void Create(RECT& rect, LONG left, LONG top, LONG right, LONG bottom)
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
		Create(rgb);
	}

	inline void Create(COLORREF rgb)
	{
		Create(*this, rgb);
	}

	static inline void Create(C_SOLID_HBRUSH& brush, COLORREF rgb)
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