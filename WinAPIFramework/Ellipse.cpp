#include "pch.h"
#include "Ellipse.h"
#include <numbers>

using namespace shapes;

BOOL Ellipse::Create(WndSize size, COLORREF frameColor, COLORREF bkColor, PenInfo penInfo)
{
    m_OriginRect.left = 0 - (size.width / 2);
    m_OriginRect.top = 0 - (size.height / 2);
    m_OriginRect.right = 0 + (size.width / 2);
    m_OriginRect.bottom = 0 + (size.height / 2);

    m_Size = size;

    CalculateCenter();
    CalculateTransfrom();

    m_FrameColor = frameColor;
    m_BkColor = bkColor;

    m_penInfo = penInfo;
    m_penInfo.color = frameColor;

    return TRUE;
}

BOOL Ellipse::Create(RECT rect, COLORREF frameColor, COLORREF bkColor, PenInfo penInfo)
{
    m_OriginRect = rect;

    m_Size.width = (rect.right - rect.left);
    m_Size.height = (rect.bottom - rect.top);

    CalculateCenter();
    CalculateTransfrom();

    m_FrameColor = frameColor;
    m_BkColor = bkColor;

    m_penInfo = penInfo;
    m_penInfo.color = frameColor;

    return TRUE;
}

void Ellipse::Update()
{
    CalculateTransfrom();
    CalculateCenter();
    CalculateSize();
}

BOOL Ellipse::Draw(HDC hDC)
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
    bResult = ::Ellipse(hDC, r.left, r.top, r.right, r.bottom);

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}

BOOL Ellipse::DrawHatched(HDC hDC, int iHatch)
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
    bResult = ::Ellipse(hDC, r.left, r.top, r.right, r.bottom);

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}

BOOL Ellipse::DrawInWindowCoord(HDC hDC)
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
    bResult = ::Ellipse(hDC, r.left, r.top, r.right, r.bottom);

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}

BOOL Ellipse::DrawHatchedInWindowCoord(HDC hDC, int iHatch)
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
    bResult = ::Ellipse(hDC, r.left, r.top, r.right, r.bottom);

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}

BOOL Ellipse::DrawArc(HDC hDC, float beginDegree, float endDegree)
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

    POINT begin = DegreeToPoint(beginDegree);
    POINT end = DegreeToPoint(endDegree);

    begin.x = begin.x + CORE.GetWindowSize().width / 2;
    begin.y = begin.y + CORE.GetWindowSize().height / 2;

    end.x = end.x + CORE.GetWindowSize().width / 2;
    end.y = end.y + CORE.GetWindowSize().height / 2;

    bResult = ::Arc(hDC, 
        r.left,
        r.top,
        r.right,
        r.bottom,
        begin.x,
        begin.y,
        end.x,
        end.y
    );

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}

BOOL Ellipse::DrawChord(HDC hDC, float beginDegree, float endDegree)
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

    POINT begin = DegreeToPoint(beginDegree);
    POINT end = DegreeToPoint(endDegree);

    begin.x = begin.x + CORE.GetWindowSize().width / 2;
    begin.y = begin.y + CORE.GetWindowSize().height / 2;

    end.x = end.x + CORE.GetWindowSize().width / 2;
    end.y = end.y + CORE.GetWindowSize().height / 2;

    bResult = ::Chord(hDC,
        r.left,
        r.top,
        r.right,
        r.bottom,
        begin.x,
        begin.y,
        end.x,
        end.y
    );

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}

BOOL Ellipse::DrawPie(HDC hDC, float beginDegree, float endDegree)
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

    POINT begin = DegreeToPoint(beginDegree);
    POINT end = DegreeToPoint(endDegree);

    begin.x = begin.x + CORE.GetWindowSize().width / 2;
    begin.y = begin.y + CORE.GetWindowSize().height / 2;

    end.x = end.x + CORE.GetWindowSize().width / 2;
    end.y = end.y + CORE.GetWindowSize().height / 2;

    bResult = ::Pie(hDC,
        r.left,
        r.top,
        r.right,
        r.bottom,
        begin.x,
        begin.y,
        end.x,
        end.y
    );

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}

BOOL Ellipse::DrawChordHatched(HDC hDC, int iHatch, float beginDegree, float endDegree)
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

    POINT begin = DegreeToPoint(beginDegree);
    POINT end = DegreeToPoint(endDegree);

    begin.x = begin.x + CORE.GetWindowSize().width / 2;
    begin.y = begin.y + CORE.GetWindowSize().height / 2;

    end.x = end.x + CORE.GetWindowSize().width / 2;
    end.y = end.y + CORE.GetWindowSize().height / 2;

    bResult = ::Chord(hDC,
        r.left,
        r.top,
        r.right,
        r.bottom,
        begin.x,
        begin.y,
        end.x,
        end.y
    );

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}

BOOL Ellipse::DrawPieHatched(HDC hDC, int iHatch, float beginDegree, float endDegree)
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

    POINT begin = DegreeToPoint(beginDegree);
    POINT end = DegreeToPoint(endDegree);

    begin.x = begin.x + CORE.GetWindowSize().width / 2;
    begin.y = begin.y + CORE.GetWindowSize().height / 2;

    end.x = end.x + CORE.GetWindowSize().width / 2;
    end.y = end.y + CORE.GetWindowSize().height / 2;

    bResult = ::Pie(hDC,
        r.left,
        r.top,
        r.right,
        r.bottom,
        begin.x,
        begin.y,
        end.x,
        end.y
    );

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}

POINT Ellipse::DegreeToPoint(float degree)
{
    float rad = -((degree) * (3.14159265358979f / 180.0f));

    POINT p;
    p.x = m_Center.x + (int)((m_Size.width / 2) * cos(rad));
    p.y = m_Center.y + (int)((m_Size.height / 2) * sin(rad));

    return p;
} 

BOOL Ellipse::Intersects(RECT other, OUT RECT& outIntersected)
{
    BOOL bResult = TRUE;

    RECT rect = GetRect();
    
    bResult = ::IntersectRect(&outIntersected, &rect, &other);

    return bResult;
}

BOOL Ellipse::Union(RECT other, OUT RECT& outIntersected)
{
    BOOL bResult = TRUE;

    RECT rect = GetRect();

    bResult = ::UnionRect(&outIntersected, &rect, &other);

    return bResult;
}

BOOL Ellipse::IsInRect(POINT p)
{
    RECT rect = GetRect();
    return ::PtInRect(&rect, p);
}

void Ellipse::CalculateCenter()
{
    m_Center = { (m_Rect.right + m_Rect.left) / 2, (m_Rect.bottom + m_Rect.top) / 2 };
}

void Ellipse::CalculateSize()
{
    m_Size.width = m_Rect.right - m_Rect.left;
    m_Size.height = m_Rect.bottom - m_Rect.top;

    assert(m_Size.width > 0);
    assert(m_Size.height > 0);
}

void Ellipse::CalculateTransfrom()
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

void Ellipse::CalculateToScreen(RECT& outRect)
{
    // Calc to ScreenSpace
    outRect.left += CORE.GetWindowSize().width / 2;
    outRect.top += CORE.GetWindowSize().height / 2;
    outRect.right += CORE.GetWindowSize().width / 2;
    outRect.bottom += CORE.GetWindowSize().height / 2;
}

BOOL Ellipse::DrawEllipse(HDC hDC, RECT rect, COLORREF bkColor, int frameStyle, int frameWidth, COLORREF frameColor)
{
    BOOL bResult = TRUE;

    C_SOLID_HBRUSH hBrush(bkColor);
    C_HPEN hPen(frameStyle, frameWidth, frameColor);

    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    HPEN oldPen = (HPEN)::SelectObject(hDC, hPen);

    bResult = ::Ellipse(hDC, rect.left, rect.top, rect.right, rect.bottom);

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}

