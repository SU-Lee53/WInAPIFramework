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