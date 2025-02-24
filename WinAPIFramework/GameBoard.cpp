#include "pch.h"
#include "GameBoard.h"

using namespace std;

BOOL GameBoard::Create(UINT nRows, UINT nCols, UINT offsetX, UINT offsetY, UINT cellWidth, UINT cellHeight)
{
	m_nRows = nRows;
	m_nCols = nCols;
	m_offsetX = offsetX;
	m_offsetY = offsetY;
	m_pBoardRect = make_shared<shapes::Rectangle>();
	m_pBoardRect->Create(C_RECT(0,0,cellWidth, cellHeight));

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
            m_pBoardRect->DrawInWindowCoord(hDC);
            m_pBoardRect->AddOffset({ (LONG)size.width,0 });
        }
    }


	return 0;
}
