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

private:
	HBITMAP m_hBitmap;
	BITMAP m_Info = {};
};

