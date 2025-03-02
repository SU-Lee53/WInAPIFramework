#pragma once
#include "../Application.h"

class TextBox;
class Caret;
class GameBoard;

class Demo4_2 : public Application
{
public:
	Demo4_2() {}
	virtual ~Demo4_2() {}

public:
	virtual BOOL Initialize() override;
	virtual void Update() override;
	virtual void Draw(HDC hDC) override;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void OnCreate(HWND hWnd);
	void HandleMenu(WORD param);
	
public:
	void ProcessKeyboard();
	void ProcessMouse();

public:
	void DrawRects(HDC hDC);

private:
	std::shared_ptr<GameBoard> m_pBoard = nullptr;
	std::vector<std::shared_ptr<shapes::Rectangle>> m_pRects = {};

	int m_Seleted = 0;

	RECT m_tempDrawRect = {};

	BOOL m_bLDrag = FALSE;
	POINT m_LMouseDragBeginPoint = POINT{ 0,0 };
	POINT m_LMouseDragEndPoint = POINT{ 0,0 };
	COLORREF m_CurrentColor = RGB(0, 0, 0);

	BOOL m_bRDrag = FALSE;
	POINT m_RMouseDragBeginPoint = POINT{ 0,0 };
	POINT m_RMouseDragEndPoint = POINT{ 0,0 };
	std::weak_ptr<shapes::Rectangle> m_wpRClicked;

	int m_FrameWidth = 2;

public:
	const static int m_cellWidth = 20;
	const static int m_cellHeight = 20;
	const static int MAX_RECT_COUNT = 4;
};

