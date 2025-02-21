#include "pch.h"
#include "Line.h"

using namespace shapes;

BOOL Line::Create(POINT startPos, POINT endPos)
{
    m_startPos = startPos;
    m_endPos = endPos;

    return TRUE;
}

BOOL Line::Draw(HDC hDC)
{
    BOOL bResult = TRUE;
    
    bResult = ::MoveToEx(hDC, m_startPos.x, m_startPos.y, NULL);
    bResult = ::LineTo(hDC, m_endPos.x, m_endPos.y);

    return bResult;
}

BOOL Line::DrawLine(HDC hDC, POINT start, POINT end)
{
    BOOL bResult = TRUE;

    bResult = ::MoveToEx(hDC, start.x, start.y, NULL);
    bResult = ::LineTo(hDC, end.x, end.y);

    return bResult;
}
