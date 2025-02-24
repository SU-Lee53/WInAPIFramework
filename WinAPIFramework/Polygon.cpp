#include "pch.h"
#include "Polygon.h"

using namespace std;
using namespace shapes;

BOOL Polygon::Create(std::vector<POINT>& points, COLORREF frameColor, COLORREF bkColor, PenInfo penInfo)
{
    m_OriginPoints.assign(points.begin(), points.end());

    m_FrameColor = frameColor;
    m_BkColor = bkColor;

    m_penInfo = penInfo;
    m_penInfo.color = frameColor;

    return TRUE;
}

void Polygon::Update()
{
    CalculateTransfrom();
}

BOOL Polygon::Draw(HDC hDC)
{
    BOOL bResult = TRUE;

    C_SOLID_HBRUSH hBrush(m_BkColor);
    C_HPEN hPen(m_penInfo.style, m_penInfo.width, m_FrameColor);

    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    HPEN oldPen = (HPEN)::SelectObject(hDC, hPen);

    CalculateTransfrom();

    std::vector<POINT> screenPos = {};
    CalculateToScreen(screenPos);
    bResult = ::Polygon(hDC, screenPos.data(), screenPos.size());

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}

BOOL Polygon::DrawHatched(HDC hDC, int iHatch)
{
    BOOL bResult = TRUE;

    C_HATCH_HBRUSH hBrush(iHatch, m_BkColor);
    C_HPEN hPen(m_penInfo.style, m_penInfo.width, m_FrameColor);

    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    HPEN oldPen = (HPEN)::SelectObject(hDC, hPen);

    CalculateTransfrom();

    std::vector<POINT> screenPos = {};
    CalculateToScreen(screenPos);
    bResult = ::Polygon(hDC, screenPos.data(), screenPos.size());

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}

BOOL Polygon::DrawInWindowCoord(HDC hDC)
{
    BOOL bResult = TRUE;

    C_SOLID_HBRUSH hBrush(m_BkColor);
    C_HPEN hPen(m_penInfo.style, m_penInfo.width, m_FrameColor);

    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    HPEN oldPen = (HPEN)::SelectObject(hDC, hPen);

    CalculateTransfrom();

    bResult = ::Polygon(hDC, m_Points.data(), m_Points.size());

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}

BOOL Polygon::DrawHatchedInWindowCoord(HDC hDC, int iHatch)
{
    BOOL bResult = TRUE;

    C_HATCH_HBRUSH hBrush(iHatch, m_BkColor);
    C_HPEN hPen(m_penInfo.style, m_penInfo.width, m_FrameColor);

    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    HPEN oldPen = (HPEN)::SelectObject(hDC, hPen);

    CalculateTransfrom();

    bResult = ::Polygon(hDC, m_OriginPoints.data(), m_OriginPoints.size());

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}

BOOL Polygon::DrawPolyLine(HDC hDC)
{
    BOOL bResult = TRUE;

    C_SOLID_HBRUSH hBrush(m_BkColor);
    C_HPEN hPen(m_penInfo.style, m_penInfo.width, m_FrameColor);

    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    HPEN oldPen = (HPEN)::SelectObject(hDC, hPen);

    CalculateTransfrom();

    std::vector<POINT> screenPos = {};
    CalculateToScreen(screenPos);
    bResult = ::Polyline(hDC, screenPos.data(), screenPos.size());

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;

}

void Polygon::RemovePoint(size_t index)
{
    m_Points.erase(m_Points.cbegin() + index);
}

BOOL Polygon::RemovePoint(POINT p)
{
    auto it = std::find_if(m_Points.begin(), m_Points.end(), [&p](POINT& point) -> bool 
        { 
            return (p.x == point.x) && (p.y == point.y);
        }
    );

    if (it == m_Points.end()) return FALSE;

    m_Points.erase(it);

    return TRUE;
}

void Polygon::CalculateTransfrom()
{
    m_Points.clear();
    m_Points.resize(m_OriginPoints.size());
    for (int i = 0; i < m_OriginPoints.size(); i++)
    {
        // Scale
        m_Points[i].x = m_OriginPoints[i].x * m_Scale.x;
        m_Points[i].y = m_OriginPoints[i].y * m_Scale.y;

        // Translate
        m_Points[i].x = m_Points[i].x + m_Offset.x;
        m_Points[i].y = m_Points[i].y + m_Offset.y;
    }
}

void Polygon::CalculateToScreen(std::vector<POINT>& newPos)
{
    newPos.resize(m_Points.size());

    for (int i = 0; i < m_Points.size(); i++)
    {
        newPos[i].x = m_Points[i].x + CORE.GetWindowSize().width / 2;
        newPos[i].y = m_Points[i].y + CORE.GetWindowSize().height / 2;
    }
}

BOOL Polygon::DrawPolygon(HDC hDC, std::vector<POINT>& points, COLORREF bkColor, int frameStyle, int frameWidth, COLORREF frameColor)
{
    BOOL bResult = TRUE;

    C_SOLID_HBRUSH hBrush(bkColor);
    C_HPEN hPen(frameStyle, frameWidth, frameColor);

    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    HPEN oldPen = (HPEN)::SelectObject(hDC, hPen);

    bResult = ::Polygon(hDC, points.data(), points.size());

    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);

    hBrush.Destroy();
    hPen.Destroy();

    return bResult;
}