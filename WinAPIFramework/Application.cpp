#include "pch.h"
#include "Application.h"

BOOL Application::BeginAppPaint()
{
    m_PaintResource.hDC = ::BeginPaint(CUR_HWND, &m_PaintResource.paintStruct);

    return m_PaintResource.hDC ? TRUE : FALSE;
}

BOOL Application::EndAppPaint()
{
    return ::EndPaint(CUR_HWND, &m_PaintResource.paintStruct) ? TRUE : FALSE;
}
