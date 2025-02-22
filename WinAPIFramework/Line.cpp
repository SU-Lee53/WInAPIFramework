#include "pch.h"
#include "Line.h"

using namespace shapes;

BOOL Line::Create(POINT startPos, POINT endPos, int frameStype, int frameWidth, COLORREF frameColor)
{
    m_OriginStartPos = startPos;
    m_OriginEndPos = endPos;

	m_penInfo.style = frameStype;
	m_penInfo.width = frameWidth;
	m_FrameColor = frameColor;

    return TRUE;
}

BOOL Line::Draw(HDC hDC)
{
    BOOL bResult = TRUE;

    C_HPEN hPen(m_penInfo.style, m_penInfo.width, m_FrameColor);

    HPEN oldPen = (HPEN)::SelectObject(hDC, hPen);

    CalculateTransfrom();

    POINT start = m_startPos;
    POINT end = m_endPos;
    CalculateToScreen(start, end);

    bResult = ::MoveToEx(hDC, start.x, start.y, NULL);
    bResult = ::LineTo(hDC, end.x, end.y);

    ::SelectObject(hDC, oldPen);

    hPen.Destroy();

    return bResult;
}

BOOL Line::DrawInWindowCoord(HDC hDC)
{
    BOOL bResult = TRUE;

    C_HPEN hPen(m_penInfo.style, m_penInfo.width, m_FrameColor);

    HPEN oldPen = (HPEN)::SelectObject(hDC, hPen);

    CalculateTransfrom();

    POINT start = m_startPos;
    POINT end = m_endPos;
    bResult = ::MoveToEx(hDC, start.x, start.y, NULL);
    bResult = ::LineTo(hDC, end.x, end.y);

    ::SelectObject(hDC, oldPen);

    hPen.Destroy();

    return bResult;
}

BOOL Line::DrawLine(HDC hDC, POINT start, POINT end)
{
    BOOL bResult = TRUE;

    bResult = ::MoveToEx(hDC, start.x, start.y, NULL);
    bResult = ::LineTo(hDC, end.x, end.y);

    return bResult;
}

void Line::CalculateTransfrom()
{
    // Calc Scale
    m_startPos.x = m_OriginStartPos.x * m_Scale.x;
    m_startPos.y = m_OriginStartPos.y * m_Scale.y;
    m_endPos.x = m_OriginEndPos.x * m_Scale.x;
    m_endPos.y = m_OriginEndPos.y * m_Scale.y;

    // Calc Translate
    m_startPos.x = m_startPos.x + m_Offset.x;
    m_startPos.y = m_startPos.y + m_Offset.y;
    m_endPos.x = m_endPos.x + m_Offset.x;
    m_endPos.y = m_endPos.y + m_Offset.y;
}

void Line::CalculateToScreen(POINT& start, POINT& end)
{
    start.x = m_startPos.x + CORE.GetWindowSize().width / 2;
    start.y = m_startPos.y + CORE.GetWindowSize().height / 2;

    end.x = m_endPos.x + CORE.GetWindowSize().width / 2;
    end.y = m_endPos.y + CORE.GetWindowSize().height / 2;
}
