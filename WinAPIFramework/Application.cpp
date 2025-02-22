#include "pch.h"
#include "Application.h"

void Application::Destroy()
{
	if (m_AppDesc.appRunMode == APP_RUN_MODE_GAME_LOOP)
	{
		DeleteDC(m_hMemDC);
		DeleteObject(m_hMemBitmap);
	}
}

HDC Application::BeginAppPaint(HWND hWnd)
{
    m_PaintResource.hDC = ::BeginPaint(hWnd, &m_PaintResource.paintStruct);

    return m_PaintResource.hDC;
}

BOOL Application::EndAppPaint(HWND hWnd)
{
    return ::EndPaint(hWnd, &m_PaintResource.paintStruct) ? TRUE : FALSE;
}

HDC Application::BeginDC(HWND hWnd)
{
    return ::GetDC(hWnd);
}

BOOL Application::EndDC(HWND hWnd, HDC hDC)
{
    return ::ReleaseDC(hWnd, hDC) ? TRUE : FALSE;
}

BOOL Application::BeginDoubleBuffering(HWND hWnd)
{
	GetClientRect(hWnd, &m_Rect);
	m_hCurDC = GetDC(hWnd);

	m_hMemDC = ::CreateCompatibleDC(m_hCurDC);
    m_hMemBitmap = ::CreateCompatibleBitmap(m_hCurDC, m_Rect.right, m_Rect.bottom);
	::SelectObject(m_hMemDC, m_hMemBitmap);

	C_SOLID_HBRUSH hBrush(RGB(255, 255, 255));
	m_Rect = C_RECT(0, 0, m_AppDesc.wndSize.width, m_AppDesc.wndSize.height);
	FillRect(m_hMemDC, &m_Rect, hBrush);
	hBrush.Destroy();

    return 0;
}

BOOL Application::EndDoubleBuffering(HWND hWnd)
{
	::BitBlt(m_hCurDC, 0, 0, m_Rect.right, m_Rect.bottom, m_hMemDC, 0, 0, SRCCOPY);
    return 0;
}
