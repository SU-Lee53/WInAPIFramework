#pragma once

class GameBoard
{
public:
	GameBoard() {}
	~GameBoard() {}

public:
	BOOL Create(UINT nRows, UINT nCols, UINT offsetX, UINT offsetY, UINT cellWidth, UINT cellHeight);
	BOOL Draw(HDC hDC);

public:
	void SetRows(UINT nRows) { m_nRows = nRows; }
	void SetCols(UINT nCols) { m_nCols = nCols; }
	void SetOffsetX(UINT offsetX) { m_offsetX = offsetX; }
	void SetOffsetY(UINT offsetY) { m_offsetY = offsetY; }
	void SetCellSize(UINT cellWidth, UINT cellHeight) { m_pBoardRect->SetRectAndReset(C_RECT(0,0,cellWidth, cellHeight)); }

	UINT GetRows() { return m_nRows; }
	UINT GetCols() { return m_nCols; }
	int GetOffsetX() { return m_offsetX; }
	int GetOffsetY() { return m_offsetY; }

public:
	POINT PointToBoardCoord(POINT pt)
	{
		POINT ret = { 0,0 };
		ret.x = (pt.x - m_offsetX) / m_pBoardRect->GetSize().width;
		ret.y = (pt.y - m_offsetY) / m_pBoardRect->GetSize().height;
		return ret;
	}

private:
	std::shared_ptr<shapes::Rectangle> m_pBoardRect;
	UINT m_nRows = 0;
	UINT m_nCols = 0;

	int m_offsetX = 0;
	int m_offsetY = 0;
};

