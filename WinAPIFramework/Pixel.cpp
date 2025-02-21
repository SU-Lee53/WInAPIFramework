#include "pch.h"
#include "Pixel.h"

using namespace shapes;

BOOL Pixel::Create(POINT position, COLORREF color)
{
    m_Position = position;
    m_Color = color;

    return TRUE;
}

void Pixel::Draw(HDC hDC)
{
    ::SetPixel(hDC, m_Position.x, m_Position.y, m_Color);
}
