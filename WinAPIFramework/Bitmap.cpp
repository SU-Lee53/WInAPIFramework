#include "pch.h"
#include "Bitmap.h"
#include <filesystem>

namespace fs = std::filesystem;

BOOL Bitmap::LoadFromResource(int bitmapMacro)
{
	m_hBitmap = LoadBitmap(CORE.GetDesc().hInstance, MAKEINTRESOURCE(bitmapMacro));

	if (!m_hBitmap)
		return FALSE;

	GetObject(m_hBitmap, sizeof(BITMAP), &m_Info);

	return TRUE;
}

BOOL Bitmap::LoadFromFile(const std::wstring& bitmapPath)
{
	m_hBitmap = (HBITMAP)LoadImage(CORE.GetDesc().hInstance, bitmapPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (!m_hBitmap)
		return FALSE;

	GetObject(m_hBitmap, sizeof(BITMAP), &m_Info);

	return TRUE;
}

BOOL Bitmap::Draw(HDC hDC, POINT destXY, POINT srcSize, POINT srcXY, DWORD Rop)
{
	BOOL bResult = TRUE;

	HDC memDC = CreateCompatibleDC(hDC);

	POINT size = srcSize;

	if(size.x == -1 || size.y == -1)
	{
		size = POINT{ m_Info.bmWidth, m_Info.bmHeight };
	}
	

	SelectObject(memDC, m_hBitmap);
	bResult = BitBlt(hDC, destXY.x, destXY.y, size.x, size.y, memDC, srcXY.x, srcXY.y, Rop);

	bResult = DeleteObject(memDC);

	return bResult;
}

BOOL Bitmap::DrawInRect(HDC hDC, RECT r, RECT srcRect, DWORD Rop)
{
	BOOL bResult = TRUE;

	HDC memDC = CreateCompatibleDC(hDC);

	POINT size = { srcRect.right - srcRect.left, srcRect.bottom - srcRect.top };

	if (size.x == -1 || size.y == -1)
	{
		size = POINT{ m_Info.bmWidth, m_Info.bmHeight };
	}


	SelectObject(memDC, m_hBitmap);
	bResult = StretchBlt(hDC, r.left, r.top, r.right - r.left, r.bottom - r.top, memDC, srcRect.left, srcRect.top, size.x, size.y , Rop);

	bResult = DeleteObject(memDC);

	return bResult;
}

