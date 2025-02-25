#include "pch.h"
#include "GameBoard.h"

using namespace std;

BOOL GameBoard::Create(UINT nRows, UINT nCols, UINT offsetX, UINT offsetY, UINT cellWidth, UINT cellHeight)
{
	m_nRows = nRows;
	m_nCols = nCols;
	m_offsetX = offsetX;
	m_offsetY = offsetY;
    m_cellSize.width = cellWidth;
    m_cellSize.height = cellHeight;
	m_pBoardRect = make_shared<shapes::Rectangle>();
	m_pBoardRect->Create(C_RECT(0,0,cellWidth, cellHeight));

    m_cellColor.assign(nRows * nCols, RGB(255, 255, 255));

	return TRUE;
}

BOOL GameBoard::Draw(HDC hDC)
{
    WndSize size = m_pBoardRect->GetSize();

    for (int i = 0; i < m_nRows; i++)
    {
        m_pBoardRect->SetOffset({ m_offsetX, (LONG)(m_offsetY + (size.height * i)) });
        for (int j = 0; j < m_nCols; j++)
        {
            int colorIndex = (i * m_nCols) + j;
            COLORREF color = m_cellColor[colorIndex];
            
            m_pBoardRect->SetBackgroundColor(color);
            m_pBoardRect->DrawInWindowCoord(hDC);
            m_pBoardRect->AddOffset({ (LONG)size.width,0 });
        }
    }


	return 0;
}

void GameBoard::SetCellColor(UINT row, UINT col, COLORREF color)
{
    int index = (row * m_nCols) + col;
    m_cellColor[index] = color;
}

COLORREF GameBoard::GetCellColor(UINT row, UINT col)
{
    int index = (row * m_nCols) + col;
    return m_cellColor[index];
}

RECT GameBoard::GetCellRect(UINT row, UINT col)
{
    RECT rect;
    WndSize size = m_pBoardRect->GetSize();

    rect.left = m_offsetX + (col * size.width);
    rect.top = m_offsetY + (row * size.height);
    rect.right = rect.left + size.width;
    rect.bottom = rect.top + size.height;

    return rect;
}
