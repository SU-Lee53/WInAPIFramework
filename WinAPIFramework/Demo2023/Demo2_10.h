#pragma once
#include "../Application.h"

class TextBox;
class Caret;
class Demo2_10;

class Demo2_10_Player
{
public:
	Demo2_10_Player() {}
	~Demo2_10_Player() {}

public:
	BOOL Create(std::shared_ptr<Application> pDemo)
	{
		m_wpDemo = pDemo;
		return TRUE;
	}
	void Draw(HDC hDC);

public:
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void UpdateScale()
	{
		if (m_bScaleUpdateMode)
		{
			m_Scale.x++;
			m_Scale.y++;
		}
		else
		{
			m_Scale.x--;
			m_Scale.y--;
		}

		if (m_Scale.x < 2 || m_Scale.y < 2)
		{
			m_bScaleUpdateMode = TRUE;
		}
		if (m_Scale.x > 12 || m_Scale.y > 12)
		{
			m_bScaleUpdateMode = FALSE;
		}
	}

	void SetPos(POINT pos) { m_Pos = pos; }
	void SetColor(COLORREF color) { m_Color = color; }
	void SetPlayerModel(UINT num) { m_PlayerModel = num; }

	POINT GetPos() { return m_Pos; }

private:
	POINT CalculatePlayerPos()
	{
		POINT p;
		p.x = m_Pos.x * m_moveOffset - 500;
		p.y = m_Pos.y * m_moveOffset - 500;
		return p;
	}

private:
	POINT m_Pos = { 0,0 };
	POINT m_Scale = { 12,12 };
	UINT m_PlayerModel = 0;
	COLORREF m_Color = RGB(0, 0, 0);

	const LONG m_moveOffset = 26;

	std::weak_ptr<Application> m_wpDemo;

	BOOL m_bScaleUpdateMode = FALSE;
};

enum DEMO2_10_CELL_TYPE
{
	CELL_TYPE_CHANGE_COLOR = 0,
	CELL_TYPE_OBSTACLE,
	CELL_TYPE_CHANGE_SIZE,
	CELL_TYPE_CHANGE_MODEL,
	CELL_TYPE_NONE
};

class Demo2_10 : public Application
{
public:
	Demo2_10() {}
	virtual ~Demo2_10() {}

public:
	virtual BOOL Initialize() override;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void OnCreate(HWND hWnd);
	void OnPaint();
	void OnChar(HWND hWnd, WPARAM wParam, LPARAM lParam);
	void OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

private:
	void SetGame();
	void CreatePlayerModel();

private:
	void ProcessKeyboard(WPARAM wParam);
	void ProcessGameStatus();

public:
	DEMO2_10_CELL_TYPE GetCellInfo(int row, int col) { return m_pCellInfo[row][col]; }
	
	std::shared_ptr<shapes::Polygon>& GetPlayerModel0() { return m_pPlayerModel0; }
	std::shared_ptr<shapes::Polygon>& GetPlayerModel1() { return m_pPlayerModel1; }
	std::shared_ptr<shapes::Ellipse>& GetPlayerModel2() { return m_pPlayerModel2; }
	std::shared_ptr<shapes::Ellipse>& GetPlayerModel3() { return m_pPlayerModel3; }

	BOOL CheckWhosKeyDowned(WPARAM wParam, BOOL& who);

private:
	std::shared_ptr<shapes::Rectangle> m_pBoardRect = nullptr;

	std::shared_ptr<Demo2_10_Player> m_pPlayer1 = nullptr;
	std::shared_ptr<Demo2_10_Player> m_pPlayer2 = nullptr;

	std::shared_ptr<shapes::Polygon> m_pPlayerModel0 = nullptr;
	std::shared_ptr<shapes::Polygon> m_pPlayerModel1 = nullptr;
	std::shared_ptr<shapes::Ellipse> m_pPlayerModel2 = nullptr;
	std::shared_ptr<shapes::Ellipse> m_pPlayerModel3 = nullptr;

	std::wstring m_wstrErrString = L"";

	DEMO2_10_CELL_TYPE m_pCellInfo[40][40] = {};

	// T : p1 | F : p2
	BOOL m_bPlayerTurn = TRUE;

};

