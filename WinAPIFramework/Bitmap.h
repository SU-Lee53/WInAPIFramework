#pragma once

class Bitmap
{
public:
	Bitmap() {}
	~Bitmap() {}

	BOOL LoadFromResource(int bitmapMacro);
	BOOL LoadFromFile(const std::wstring& bitmapPath);

	BOOL Draw(HDC hDC, POINT destXY, POINT srcSize = {-1, -1}, POINT srcXY = {0,0}, DWORD Rop = SRCCOPY);
	BOOL DrawInRect(HDC hDC, RECT r, RECT srcRect = {0,0,-1,-1}, DWORD Rop = SRCCOPY);

	BITMAP GetInfo() { return m_Info; }

private:
	HBITMAP m_hBitmap;
	BITMAP m_Info = {};
};

struct BitmapRect
{
	std::shared_ptr<Bitmap> pBitmap;
	RECT drawRect;
	RECT imageRect;

	void CreateFromResource(int bitmapMacro, RECT draw, RECT image = { 0,0,-1,-1 })
	{
		pBitmap = std::make_shared<Bitmap>();
		pBitmap->LoadFromResource(bitmapMacro);
		drawRect = draw;
		if (image.left == 0 && image.top == 0 && image.right == -1 && image.bottom == -1)
		{
			imageRect = C_RECT(0, 0, pBitmap->GetInfo().bmWidth, pBitmap->GetInfo().bmHeight);
		}
		else
		{
			imageRect = image;
		}
	}

	void CreateFromFile(const std::wstring& bitmapPath, RECT draw, RECT image = { 0,0,-1,-1 })
	{
		pBitmap = std::make_shared<Bitmap>();
		pBitmap->LoadFromFile(bitmapPath);
		drawRect = draw;
		if (image.left == 0 && image.top == 0 && image.right == -1 && image.bottom == -1)
		{
			imageRect = C_RECT(0, 0, pBitmap->GetInfo().bmWidth, pBitmap->GetInfo().bmHeight);
		}
		else
		{
			imageRect = image;
		}
	}

	void Draw(HDC hDC, DWORD Rop = SRCCOPY)
	{
		pBitmap->DrawInRect(hDC, drawRect, imageRect, Rop);
	}

};

struct TiledBitmap
{
	std::shared_ptr<Bitmap> pBitmap;
	std::vector<RECT> dividedRects;
	RECT drawRect;
	int nRows;
	int nCols;

private:
	void Devide()
	{
		dividedRects.clear();

		SIZE bitmapSize = SIZE{ pBitmap->GetInfo().bmWidth, pBitmap->GetInfo().bmHeight };
		SIZE rectSize = SIZE{ bitmapSize.cx / nCols, bitmapSize.cy / nRows };

		for (int row = 0; row < nRows; row++)
		{
			for (int col = 0; col < nCols; col++)
			{
				RECT divided = C_RECT(rectSize.cx * col, rectSize.cy * row, (rectSize.cx * col) + rectSize.cx, (rectSize.cy * row) + rectSize.cy);
				dividedRects.push_back(divided);
			}
		}
	}

public:
	void CreateFromResource(int bitmapMacro, RECT draw, int _nRows, int _nCols)
	{
		pBitmap = std::make_shared<Bitmap>();
		pBitmap->LoadFromResource(bitmapMacro);
		drawRect = draw;
		nRows = _nRows;
		nCols = _nCols;

		Devide();
	}

	void CreateFromFile(const std::wstring& bitmapPath, RECT draw, int _nRows, int _nCols)
	{
		pBitmap = std::make_shared<Bitmap>();
		pBitmap->LoadFromFile(bitmapPath);
		drawRect = draw;
		nRows = _nRows;
		nCols = _nCols;

		Devide();
	}

	void DrawAll(HDC hDC, int Rop = SRCCOPY)
	{
		SIZE rectSize = SIZE{ (drawRect.right - drawRect.left) / nCols, (drawRect.bottom - drawRect.top) / nRows };

		for (int row = 0; row < nRows; row++)
		{
			for (int col = 0; col < nCols; col++)
			{
				RECT imgRect = dividedRects[(row * nCols) + col];
				RECT draw = C_RECT(rectSize.cx * col, rectSize.cy * row, (rectSize.cx * col) + rectSize.cx, (rectSize.cy * row) + rectSize.cy);
				pBitmap->DrawInRect(hDC, draw, imgRect, Rop);
			}
		}
	}

	void Draw(HDC hDC, int index, int Rop = SRCCOPY)
	{
		POS p = GetIndexToPos(index);
		SIZE rectSize = SIZE{ (drawRect.right - drawRect.left) / nCols, (drawRect.bottom - drawRect.top) / nRows };
		RECT draw = C_RECT(rectSize.cx * p.col, rectSize.cy * p.row, (rectSize.cx * p.col) + rectSize.cx, (rectSize.cy * p.row) + rectSize.cy);
		RECT img = dividedRects[index];
		pBitmap->DrawInRect(hDC, draw, img);
	}

	void Draw(HDC hDC, POS p, int Rop = SRCCOPY)
	{
		SIZE rectSize = SIZE{ (drawRect.right - drawRect.left) / nCols, (drawRect.bottom - drawRect.top) / nRows };
		RECT draw = C_RECT(rectSize.cx * p.col, rectSize.cy * p.row, (rectSize.cx * p.col) + rectSize.cx, (rectSize.cy * p.row) + rectSize.cy);
		RECT img = dividedRects[GetPosToIndex(p)];
		pBitmap->DrawInRect(hDC, draw, img);
	}

	void ReDivide(int _nRows, int _nCols, const LPRECT pDrawRect = NULL)
	{
		nRows = _nRows;
		nCols = _nCols;
		if (pDrawRect)
		{
			drawRect = *pDrawRect;
		}

		Devide();
	}

	BitmapRect GetBitmapRect(POS p)
	{
		int index = GetPosToIndex(p);
		SIZE rectSize = SIZE{ (drawRect.right - drawRect.left) / nCols, (drawRect.bottom - drawRect.top) / nRows };
		RECT draw = C_RECT(rectSize.cx * p.col, rectSize.cy * p.row, (rectSize.cx * p.col) + rectSize.cx, (rectSize.cy * p.row) + rectSize.cy);

		BitmapRect ret;
		ret.pBitmap = pBitmap;
		ret.drawRect = draw;
		ret.imageRect = dividedRects[index];

		return ret;
	}

	BitmapRect GetBitmapRect(int index)
	{
		SIZE rectSize = SIZE{ (drawRect.right - drawRect.left) / nCols, (drawRect.bottom - drawRect.top) / nRows };
		POS p = GetIndexToPos(index);
		RECT draw = C_RECT(rectSize.cx * p.col, rectSize.cy * p.row, (rectSize.cx * p.col) + rectSize.cx, (rectSize.cy * p.row) + rectSize.cy);

		BitmapRect ret;
		ret.pBitmap = pBitmap;
		ret.drawRect = draw;
		ret.imageRect = dividedRects[index];

		return ret;
	}

	RECT GetRect(POS p)
	{
		SIZE rectSize = SIZE{ (drawRect.right - drawRect.left) / nCols, (drawRect.bottom - drawRect.top) / nRows };
		return C_RECT(rectSize.cx * p.col, rectSize.cy * p.row, (rectSize.cx * p.col) + rectSize.cx, (rectSize.cy * p.row) + rectSize.cy);
	}

	RECT GetRect(int index)
	{
		SIZE rectSize = SIZE{ (drawRect.right - drawRect.left) / nCols, (drawRect.bottom - drawRect.top) / nRows };
		POS p = GetIndexToPos(index);
		return C_RECT(rectSize.cx * p.col, rectSize.cy * p.row, (rectSize.cx * p.col) + rectSize.cx, (rectSize.cy * p.row) + rectSize.cy);
	}

	int GetPosToIndex(POS p)
	{
		return (p.row * nRows) + p.col;
	}

	POS GetIndexToPos(int index)
	{
		return POS{ (ULONG)(index / nRows), (ULONG)(index % nRows) };
	}
};