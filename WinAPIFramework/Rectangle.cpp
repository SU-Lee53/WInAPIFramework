#include "pch.h"
#include "Rectangle.h"

using namespace shapes;

BOOL Rectangle::Create(WndSize size, COLORREF frameColor, COLORREF bkColor, PenInfo penInfo)
{
    m_OriginRect.left = 0 - (size.width / 2);
    m_OriginRect.top = 0 - (size.height / 2);
    m_OriginRect.right = 0 + (size.width / 2);
    m_OriginRect.bottom = 0 + (size.height / 2);

    m_Size = size;

    CalculateCenter();
    //CalculateTransfrom();

    m_FrameColor = frameColor;
    m_BkColor = bkColor;

    m_penInfo = penInfo;
    m_penInfo.color = frameColor;

    return TRUE;
}

BOOL Rectangle::Draw(HDC hDC)
{
    BOOL bResult = TRUE;

    C_SOLID_HBRUSH hBrush(m_BkColor);
    C_HPEN hPen(m_penInfo.style, m_penInfo.width, m_FrameColor);

    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    HPEN oldPen = (HPEN)::SelectObject(hDC, hPen);

    CalculateTransfrom();
    CalculateCenter();
    CalculateSize();

    RECT r = m_Rect;
    CalculateToScreen(r);
    bResult = ::Rectangle(hDC, r.left, r.top, r.right, r.bottom);

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}

BOOL Rectangle::DrawHatched(HDC hDC, int iHatch)
{
    BOOL bResult = TRUE;

    C_HATCH_HBRUSH hBrush(iHatch, m_BkColor);
    C_HPEN hPen(m_penInfo.style, m_penInfo.width, m_FrameColor);

    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    HPEN oldPen = (HPEN)::SelectObject(hDC, hPen);

    CalculateTransfrom();
    CalculateCenter();
    CalculateSize();

    RECT r = m_Rect;
    CalculateToScreen(r);
    bResult = ::Rectangle(hDC, r.left, r.top, r.right, r.bottom);

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}

BOOL Rectangle::DrawRound(HDC hDC, int width, int height)
{
    BOOL bResult = TRUE;

    C_SOLID_HBRUSH hBrush(m_BkColor);
    C_HPEN hPen(m_penInfo.style, m_penInfo.width, m_FrameColor);

    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    HPEN oldPen = (HPEN)::SelectObject(hDC, hPen);

    CalculateTransfrom();
    CalculateCenter();
    CalculateSize();

    RECT r = m_Rect;
    CalculateToScreen(r);
    bResult = ::RoundRect(hDC, r.left, r.top, r.right, r.bottom, width, height);

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}

BOOL Rectangle::DrawRoundHatched(HDC hDC, int iHatch, int width, int height)
{
    BOOL bResult = TRUE;

    C_HATCH_HBRUSH hBrush(iHatch, m_BkColor);
    C_HPEN hPen(m_penInfo.style, m_penInfo.width, m_FrameColor);

    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    HPEN oldPen = (HPEN)::SelectObject(hDC, hPen);

    CalculateTransfrom();
    CalculateCenter();
    CalculateSize();

    RECT r = m_Rect;
    CalculateToScreen(r);
    bResult = ::RoundRect(hDC, r.left, r.top, r.right, r.bottom, width, height);

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}

void Rectangle::CalculateCenter()
{
    m_Center = { (m_Rect.right + m_Rect.left) / 2, (m_Rect.bottom + m_Rect.top) / 2 };
}

void Rectangle::CalculateSize()
{
    m_Size.width = m_Rect.right - m_Rect.left;
    m_Size.height = m_Rect.bottom - m_Rect.top;

    assert(m_Size.width > 0);
    assert(m_Size.height > 0);
}

void Rectangle::CalculateTransfrom()
{
    // Calc Scale
    m_Rect.left = m_OriginRect.left * m_Scale.x;
    m_Rect.top = m_OriginRect.top * m_Scale.y;
    m_Rect.right = m_OriginRect.right * m_Scale.x;
    m_Rect.bottom = m_OriginRect.bottom * m_Scale.y;

    // Calc Translate
    m_Rect.left = m_Rect.left + m_Offset.x;
    m_Rect.top = m_Rect.top + m_Offset.y;
    m_Rect.right = m_Rect.right + m_Offset.x;
    m_Rect.bottom = m_Rect.bottom + m_Offset.y;
}

void Rectangle::CalculateToScreen(RECT& outRect)
{
    // Calc to ScreenSpace
    outRect.left += CORE.GetWindowSize().width / 2;
    outRect.top += CORE.GetWindowSize().height / 2;
    outRect.right += CORE.GetWindowSize().width / 2;
    outRect.bottom += CORE.GetWindowSize().height / 2;
}

BOOL Rectangle::Intersects(RECT other, OUT RECT& outIntersected)
{
    BOOL bResult = TRUE;

    RECT rect = GetRect();

    bResult = ::IntersectRect(&outIntersected, &rect, &other);

    return bResult;
}

BOOL Rectangle::Union(RECT other, OUT RECT& outIntersected)
{
    BOOL bResult = TRUE;

    RECT rect = GetRect();

    bResult = ::UnionRect(&outIntersected, &rect, &other);

    return bResult;
}

BOOL Rectangle::IsInRect(POINT p)
{
    RECT rect = GetRect();
    return ::PtInRect(&rect, p);
}

BOOL Rectangle::DrawRectangle(HDC hDC, POINT leftTop, POINT rightBottom)
{
    return ::Rectangle(hDC, leftTop.x, leftTop.y, rightBottom.x, rightBottom.y);
}
