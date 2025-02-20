#include "pch.h"
#include "Application.h"

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
